#pragma once

#include <System/Basic.h>
#include <Server/RPC/P2PNode.h>
#include <Server/RPC/GateKeeper.h>
#include <Server/rpc/LocalEntityFactory.h>
#include <Server/Network/ClientTransportSystemIntf.h>
#include <Server/Network/FreePortsFinder.h>

#include "Server/DebugVarUpdate/DebugVarReporter.h" // DAN
#include "Server/DebugVarUpdate/DebugVarRequester.h" // DAN

#include "Server/Network/TransportTypes.h" 
#include "Server/Coordinator/CoordinatorClient.h" 

namespace TransportLayer
{
  class TransportModule;
}

namespace lobbyTest
{
  class TestClientRunner;
}

namespace DebugConsole
{

  namespace Stage
  {
    enum
    {
      NONE,
      INVALID,
      LOGIN_STARTED,
      LOGIN_FINISHED,

      // отдельный набор стейтов для консольного ввода
      LOOP,
      WAIT,
      INPUT,
    };
  };

  namespace Result
  {
    enum 
    {
      NONE = -1,
      SUCCESS = 0,
      FAIL,
      IN_PROGRESS
    };
  };

  class Client :  public BaseObjectMT, 
                  rpc::IGateKeeperCallback
  {
    NI_DECLARE_REFCOUNT_CLASS_2( Client, BaseObjectMT, rpc::IGateKeeperCallback );

  public:
    Client();

    // для нового транспорта (серверного, через CoordinatorClient)
    Client( int localId, 
      StrongMT<Transport::ITransportSystem> clusterTransport, 
      StrongMT<Coordinator::CoordinatorClient> coord,
      const NDebug::DebugVarRequesterMap::TScenarioVars& vars_vector,
      const char * service_name );

    ~Client();

    int stage() const;
    int lastResult() const;

    void Poll();

    // var update
    bool StepVarUpdate_Cluster();

  protected:
    int startLogin_(string const & loginaddr, string const & username, string const & pswd);

    void OnSetVarReporter(NDebug::RDebugVarReporter* mr);
    void OnGetDebugVar(const wchar_t *ws);

    //  rpc::IGateKeeperCallback
    virtual void OnNewNode( StrongMT<Transport::IChannel> const & channel, StrongMT<rpc::Node> const & node );
    virtual void OnChannelClosed( StrongMT<Transport::IChannel> const & channel, StrongMT<rpc::Node> const & node );
    virtual void OnCorruptData( StrongMT<Transport::IChannel> const & channel, StrongMT<rpc::Node> const & node );

    void NextInput(); // чистим строку ввода, выводим приглашение "CMD >"
    void PrintCompletions(); // выводим списки текущих переменных и доступных сервисов
  
  private:
    StrongMT<Network::INetworkDriver> netdriver_;
    StrongMT<TransportLayer::TransportModule> sptm_;
    Transport::TServiceId svcname_;
    StrongMT<Transport::IClientTransportSystem>  transport_; // старый, клиентский
    StrongMT<Coordinator::CoordinatorClient> coordClient_;
    int userid_;
    StrongMT<rpc::GateKeeperClient> gateKeeper_;

    int lastresult_;

    DWORD pingInterval_;
    DWORD lastPing_;
    nstl::string loginAddr_;
    nstl::string user_;
    nstl::string pswd_;

    int localid_;
    int stage_;
    bool bexit_;

    DWORD loadMapTimeout_; //  seconds
    NHPTimer::FTime startLoadMapTime_;

    NDebug::DebugVarRequesterMap varRequester_;
    
    nstl::string input_; // user console input
    
    Transport::TServiceId varService_; // имя сервиса, к которому будем коннектиться (Requester/Reporter добавляют к нему ".var")
    nstl::string varImmediateIP_; // прямой адрес (IP:port) куда будем коннектиться, минуя нормальный кластерный AddressTranslator

    // ставится после любых изменений service/varlist, чтобы при запуске loop создать заново connect и реквестеры
    bool need_stage_reset_; 

    // новый транспорт, через CoordinatorClient
    StrongMT<Transport::ITransportSystem> transportCluster_; 
    StrongMT<rpc::GateKeeper> gateKeeperCluster_;

  };

  inline int Client::stage() const
  {
    return stage_;
  }

  inline int Client::lastResult() const
  {
    return lastresult_;
  }

} // namespace DebugConsole
