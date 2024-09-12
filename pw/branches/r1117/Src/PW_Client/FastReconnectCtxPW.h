#ifndef FASTRECONNECTCTXPW_H_INCLUDED
#define FASTRECONNECTCTXPW_H_INCLUDED

#include "Client/LobbyPvx/FastReconnectCtx.h"

namespace NGameX
{
  class AdventureScreen;
  class ChatUiController;
}

namespace NWorld
{
  class PFResourcesCollection;
}

namespace StatisticService
{
  class GameStatistics;
}

namespace lobby
{

namespace EFastReconnStage
{
  enum Enum { Idle, WarmUp, InProgress };
}

class FastReconnectCtxPW : public FastReconnectCtx
{
  NI_DECLARE_REFCOUNT_CLASS_1( FastReconnectCtxPW, FastReconnectCtx )

public:
  FastReconnectCtxPW( Transport::TClientId _clientid, int _maxRetries, timer::Time _delay, timer::Time _retryDelay ) :
  FastReconnectCtx( _clientid ),
  maxRetries( _maxRetries ),
  delayBeforeFirstRetry( _delay ),
  delayBeforeRetry( _retryDelay ),
  tryIndex( 0 ),
  nextTryTime( 0 ),
  stage( EFastReconnStage::Idle )
  {}

  void SetAdvScreen( NGameX::AdventureScreen * _advScr )
  {
    advScreen = _advScr;
  }

  void SetChatController( NGameX::ChatUiController * _chatController )
  {
    chatController = _chatController;
  }

  void SetSmartChatController( NGameX::SmartChatController * _smartChatController )
  {
    smartChatController = _smartChatController;
  }

  void SetStatistics( StatisticService::GameStatistics * stat )
  {
    statistics = stat;
  }

  void SetResourcesCollection(NWorld::PFResourcesCollection * _resourceCollection)
  {
    resourceCollection = _resourceCollection;
  }

  bool BeginNextTry()
  {
    NI_VERIFY( stage == EFastReconnStage::Idle, "", return false );

    ++tryIndex;
    if ( tryIndex > maxRetries )
      return false;

    stage = EFastReconnStage::WarmUp;
    nextTryTime = timer::Now() + ( ( tryIndex == 1 ) ? delayBeforeFirstRetry : delayBeforeRetry );
    return true;
  }

  bool CanTryNow()
  {
    if ( stage != EFastReconnStage::WarmUp )
      return false;

    timer::Time t = timer::Now();
    if ( t < nextTryTime )
      return false;

    stage = EFastReconnStage::InProgress;
    nextTryTime = 0;
    return true;
  }

  void TryFailed()
  {
    if ( stage == EFastReconnStage::InProgress )
      stage = EFastReconnStage::Idle;
  }

  EFastReconnStage::Enum Stage() const { return stage; }
  int TryIndex() const { return tryIndex; }
  NGameX::AdventureScreen * AdvScreen() const { return advScreen; }
  NGameX::ChatUiController * ChatController() const { return chatController; }
  NGameX::SmartChatController * SmartChatController() const { return smartChatController; }
  StatisticService::GameStatistics * Statistics() const { return statistics; }
  NWorld::PFResourcesCollection * GetResourcesCollection() const { return resourceCollection; }

private:
  const int                                   maxRetries;
  const timer::Time                           delayBeforeFirstRetry;
  const timer::Time                           delayBeforeRetry;

  EFastReconnStage::Enum                      stage;
  int                                         tryIndex;
  timer::Time                                 nextTryTime;
  Weak<NGameX::AdventureScreen>               advScreen;
  Strong<NGameX::ChatUiController>            chatController;
  Strong<NGameX::SmartChatController>         smartChatController;
  StrongMT<StatisticService::GameStatistics>  statistics;
  CObj<NWorld::PFResourcesCollection>         resourceCollection;
};

} //namespace lobby

#endif //FASTRECONNECTCTXPW_H_INCLUDED
