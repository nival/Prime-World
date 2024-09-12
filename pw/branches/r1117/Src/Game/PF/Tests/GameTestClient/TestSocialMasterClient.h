#pragma once

#include "Game/PF/Tests/GTCBase/GTCBase.h"
#include "rpc/IfaceRequester.h"
#include "Server/LobbySocial/RISocialLobby.auto.h"
#include "TestSocialTransport.h"
#include "System/RandomGenerator.h"
#include "System/EnumToString.h"
#include "System/SafeTextFormat.h"
#include <map>

namespace GtcSocial
{

namespace ESocialTestState
{
  enum Enum
  {
    Start = GameTestClient2::BaseStage::LOGIN_FINISHED_POST_STEP,
    WaitingSocTransport,
    WaitingDevSLPtr,
    Working
  };
};


namespace ESocClSt { enum Enum; }


class SocialClient;


struct SCounters
{
  unsigned    totalSpawned;
  unsigned    succeeded;
  unsigned    failed;
  unsigned    timedOut;

  SCounters() : totalSpawned( 0 ), succeeded( 0 ), failed( 0 ), timedOut( 0 ) {}
};



class SocialMasterClient : public GameTestClient2::ClientBase, public BaseObjectMT, public ITransportCommonCallback
{
  NI_DECLARE_REFCOUNT_CLASS_3( SocialMasterClient, GameTestClient2::ClientBase, BaseObjectMT, ITransportCommonCallback );

public:
  SocialMasterClient( Network::INetworkDriver * _driver, TransportLayer::TransportModule * _sptm,
                            const string & _loginaddr, const string & _user, const string & _pswd,
                            int _clientsCount, const SSocialConfig & _socConfig, unsigned _firstUdpPort, unsigned _udpPortSearchRange );

  ~SocialMasterClient() {}

public:
  int Poll();

  StrongMT<SocialClient> PopToPvx();

  void DumpStatistics();
  void DumpStates();
  void DumpStatesStatistics();
  void AppendStatesDebugText( string & _dest );

  int SocialClientsCount() const { return clients.size(); }

private:
  typedef  list<StrongMT<SocialClient>> TSocClients;

  typedef vector<socialLobby::SMatchmakingRequest> TPartyData;

  struct SSpawnedParty : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( SSpawnedParty, BaseObjectST );
    
    SSpawnedParty() : ready( false ) {}

    explicit SSpawnedParty( const socialLobby::SMatchmakingRequest & req ) : ready( false ) {
      members.push_back( req );
      CleanupUid( members.back() );
    }

    TPartyData                  members;
    bool                        ready;
  };

  struct SRecycledParty : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( SRecycledParty, BaseObjectST );
    
    explicit SRecycledParty( const socialLobby::SMatchmakingRequest & req ) :
    size( req.partyLineup.size() ), lastUpdate( timer::Now() ) {
      members.reserve( req.partyLineup.size() );
      members.push_back( req );
      CleanupUid( members.back() );
    }

    const int                   size;
    TPartyData                  members;
    timer::Time                 lastUpdate;
  };


  struct StateTimingInfo {
    unsigned      count;
    timer::Time   sum, tmin, tmax;

    StateTimingInfo() { Reset(); }

    void Reset() {
      count = 0;
      sum = tmin = tmax = 0;
    }

    void Count( timer::Time t ) {
      if ( !count )
        sum = tmin = tmax = t;
      else {
        sum += t;
        tmin = Min( tmin, t );
        tmax = Max( tmax, t );
      }
      ++count;
    }

    void Format( text::IBuffer * buffer, const text::SFormatSpecs & specs ) const {
      text::PrintfFormatterBufferPtr formatter( buffer );
      if ( !count )
        formatter.Trace( "<no data>" );
      else
        formatter.Trace( "%.3f (%d/%.3f/%.3f)", sum/count, count, tmin, tmax );
    }
  };

  struct StateTimingSlot {
    StateTimingInfo   total, last;
    StateTimingSlot() {}
  };

  typedef map<socialLobby::TPartyId, Strong<SRecycledParty>> TPartyRecycle;
  typedef list<Strong<SSpawnedParty>> TRecycledRequests;

  typedef std::map<ESocClSt::Enum, StateTimingSlot> StatesTimingStatistics;

  const int                   clientsCount;
  const SSocialConfig         socConfig;
  StrongMT<ITransport>        socTransport;
  StrongMT<rpc::IfaceRequester<socialLobby::RIDevSocLobby>> devSocLobby;
  TSocClients                 clients;
  timer::Time                 nextClientSpawn;
  lobby::ETeam::Enum          teamSwitch;

  TRecycledRequests           requestsRecycle;
  TPartyRecycle               partyRecycleCollector;

  Strong<SSpawnedParty>       spawningParty;
  int                         spawningPartyCounter;

  NRandom::RandomGenerator    rnd;
  TSocClients                 readyForPvX;

  socialLobby::SDevUidRange   uidRange;
  socialLobby::TUId           currentUIdRangeIndex;
  bool                        userIdRangeRequested;
  int                         nextSessionContextId;

  timer::Time                 nextServerStatusRequest;

  SCounters                   counters;

  StatesTimingStatistics      statesTimingStatistics;

  void PollSocClients();
  void SpawnClients();
  bool SpawnClient();
  bool GetNewClientData( socialLobby::SMatchmakingRequest & data );
  Strong<SSpawnedParty> GetNewParty();
  void RecycleRequest( const socialLobby::SMatchmakingRequest & req );
  socialLobby::TUId GetNextUid();
  void SetupUid( socialLobby::SMatchmakingRequest & data, socialLobby::TUId uid );
  static void CleanupUid( socialLobby::SMatchmakingRequest & data );
  void OnUIdRangeArrival( socialLobby::SDevUidRange range );
  void PollServerStatus();

  //ITransportCommonCallback, just to get server status
  virtual void OnServerStatus( const socialLobby::SServerStatus & status );
};

} //namespace GtcSocial
