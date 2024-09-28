/******************************************************************************

Класс GameStatisticsWrapper - затычка для нескольких 'временных' проблем:

1. Сервер статистики запущен на отдельной машине отдельно от кластера серверов
  поэтому приходится заводить свой экземпляр транспорта, гейта и ноду.
  Что бы не мусорить в GameContext, я вынес этот временный код в отдельный класс

  Со временем нужно будет включить сервер статистики в кластер и получать R-указатель
  через общий транспорт и RPC


2. Есть проблема с фабриками R объектов, используемых в разных проектах VS
  Мы не можем линковать cpp файл R-объекта в Pf_GameLogic, а использовать его в PF_Game.
  Линковать cpp сразу в PF_Game тоже нельзя, ибо указатель активно используется в логике и возникают
  проблемы линковки с CastToObjectImpl

******************************************************************************/

#ifndef GAMESTATISTICSWRAPPER_H_INCLUDED
#define GAMESTATISTICSWRAPPER_H_INCLUDED

#include <rpc/GateKeeper.h>
#include "DebugVarUpdate/DebugVarReporter.h"

namespace rpc
{
  struct LocalEntityFactory;
}

namespace Game
{
  namespace EGameStatStatus
  {
    enum Enum;
  }
}

namespace StatisticService
{

namespace RPC
{
  class RStatisticWriter;
  class RStatisticDebugWriter;
}

namespace EStage
{
  enum Enum
  {
    Init,
    RequestNode,
    RequestObject,
    Work
  };
}

namespace EResult
{
  enum Enum
  {
    CorruptedData = -3,
    ChannelClosed = -2,
    Failed = -1,
    Success = 0,
    InProgress = 1,
    None = 2
  };
}

template <class T>
class GameStatisticsWrapper : public rpc::IGateKeeperCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( GameStatisticsWrapper, rpc::IGateKeeperCallback, BaseObjectMT );

public:
  GameStatisticsWrapper( const char * _nodeName, const char * _interfaceName, float _interfaceQueryTimeout ) :
  stage(EStage::Init),
  lastResult(EResult::None),
  nodeName(_nodeName),
  interfaceName( _interfaceName ),
  interfaceRequestTime(0),
  interfaceQueryTimeout(_interfaceQueryTimeout)
  {}

  ~GameStatisticsWrapper() {}

  void Poll( float deltaTime )
  {
    if (getLastResult() < 0)
    {
      //  if we wanna retry - set here init state
      return;
    }

    switch(stage)
    {
    case EStage::Init:
      {
        Init();
        statNode = gateKeeper->RequestNode(nodeName.c_str());
        setStage(EStage::RequestNode, EResult::InProgress);
      }
      break;

    case EStage::RequestNode:
      {
        setStage(EStage::RequestNode, EResult::Success);

        if ( interfaceName.empty() )
        {
          statistics = statNode->Create<T>();
          if (!statistics)
          {
            setStage(EStage::RequestObject, EResult::Failed);
            LOG_E(0).Trace("Can't create game statistic writer object");
          }
          else
          {
            setStage(EStage::RequestObject, EResult::InProgress);
            LOG_M(0).Trace("Game statistics writer object created");
          }
        }
        else
        {
          statNode->Query<T>( interfaceName.c_str(), this, &GameStatisticsWrapper<T>::OnPtr );
          setStage( EStage::RequestObject, EResult::InProgress );
          interfaceRequestTime = NHPTimer::GetScalarTime();
          LOG_M(0).Trace("Game statistics interface requested");
        }
      }
      break;

    case EStage::RequestObject:
      {
        if ( !statistics )
        {
          threading::MutexLock lock( mutex );

          if (interfaceRequestTime > 0)
          {
            NHPTimer::FTime currentTime = NHPTimer::GetScalarTime();
            if (currentTime - interfaceRequestTime >= interfaceQueryTimeout)
            {
              interfaceRequestTime = 0;
              setStage( EStage::RequestObject, EResult::Failed );
              LOG_M(0).Trace("Game statistic interface request timed out");
            }
          }
          break;
        }

        if ( getLastResult() == EResult::InProgress )
        {
          if ( statistics->GetStatus() == rpc::Connected )
          {
            setStage( EStage::Work, EResult::Success );
            LOG_M(0).Trace("Game statistic writer object requested successfully");
          }
          else if ( statistics->GetStatus() == rpc::Disconnected )
          {
            setStage( EStage::RequestObject, EResult::Failed );
            LOG_E(0).Trace("Game statistic writer object request is FAILED");
          }
        }
        else
        {
          //  retry request object ?
        }
      }
      break;

    case EStage::Work:
      {
        if (statistics->GetStatus() != rpc::Connected &&
            getLastResult() >= 0)
        {
          LOG_M(0).Trace("Game statistic writer is NOT connected");
          setStage(EStage::Work, EResult::Failed);
        }
      }
      break;

    default:
      LOG_E(0).Trace("%s: unknown stage", __FUNCTION__);
      break;
    }
  }

  T * Get() const { return statistics; }

  void Attach(StrongMT<rpc::GateKeeperClient> & _gateKeeper, bool registerDebugVarReporter = false)
  {
    gateKeeper = _gateKeeper;

    gateKeeper->attachNotificationCallback( this );

    if (registerDebugVarReporter)
    {
      factory = new rpc::LocalEntityFactory(&gateKeeper->GetGate());
      // регистрируемся, чтобы динамически создавать DebugVarReporter по запросу с той стороны
      NDebug::DebugVarReporter::AttachTo( factory );
    }
  }

  EStage::Enum getStage() const { return stage; }
  EResult::Enum getLastResult() const { return lastResult; }

  Game::EGameStatStatus::Enum GetGameStatisticsStatus() const
  {
    if ( ( getStage() == StatisticService::EStage::Work ) && 
       ( StatisticService::EResult::Success == getLastResult() ) )
    {
      return Game::EGameStatStatus::Ready;
    }

    if ( getLastResult() < 0 )
    {
      return Game::EGameStatStatus::Failed;
    }

    return Game::EGameStatStatus::Waiting;
  }

private:
  // IGateKeeperCallback
  virtual void OnNewNode( StrongMT<Transport::IChannel> const & channel, StrongMT<rpc::Node> const & node ) {}
  virtual void OnChannelClosed( StrongMT<Transport::IChannel> const & channel, StrongMT<rpc::Node> const & node ) {
    if (node.Get() == statNode.Get())
    {
      LOG_M(0).Trace("Channel to game statistic service is closed");
      setLastResult(EResult::ChannelClosed);
    }
  }
  virtual void OnCorruptData( StrongMT<Transport::IChannel> const & channel, StrongMT<rpc::Node> const & node ) {
    if (node.Get() == statNode.Get())
    {
      LOG_M(0).Trace("Corrupted data on game statistic service's channel");
      setLastResult(EResult::CorruptedData);
    }
  }

  void setStage(EStage::Enum s, EResult::Enum r) { stage = s; lastResult = r; }
  void setLastResult(EResult::Enum r) { lastResult = r; }

  void Init() {
    statistics = 0;
    statNode = 0;
  }

  void OnPtr( T * _ptr )
  {
    threading::MutexLock lock( mutex );
    NI_VERIFY( stage == EStage::RequestObject && interfaceRequestTime > 0, "", return );
    interfaceRequestTime = 0;
    if ( _ptr ) {
      LOG_M(0).Trace("Got remote statistics pointer");
      setStage( EStage::Work, EResult::Success );
      statistics = _ptr;
    }
    else {
      LOG_E(0).Trace("Log null remote statistics pointer");
      setStage( EStage::RequestObject, EResult::Failed );
    }
  }

private:

  StrongMT<rpc::GateKeeperClient> gateKeeper;
  rpc::LocalEntityFactory* factory;
  StrongMT<rpc::Node> statNode;
  StrongMT<T> statistics;
  string nodeName;
  string interfaceName;

  timer::Time interfaceRequestTime;
  float interfaceQueryTimeout;
  threading::Mutex  mutex;

  volatile EStage::Enum stage;
  volatile EResult::Enum lastResult;
};

} //namespace StatisticService

#endif //GAMESTATISTICSWRAPPER_H_INCLUDED
