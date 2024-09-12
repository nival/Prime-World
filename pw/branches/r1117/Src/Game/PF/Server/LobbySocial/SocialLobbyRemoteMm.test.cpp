//!Component("Server/LobbySocial/SocialLobby")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "SocialLobbyRemoteMm.h"
#include "SocialLobbyConfig.h"
#include "SocialLobbyMaps.h"
#include "ISocialLobbyPvxSvc.h"
//#include "Server/LiveMMaking/IMMakingLogic.h"
#include "Server/LiveMMaking/ILiveMMaking.h"
#include "Server/LiveMMaking/ILiveMMakingClient.h"
#include "Db/DBServer.auto.h"


struct Test_SocialLobbyMmLogix : public CxxTest::TestSuite
{
  struct MockLiveMM : public mmaking::ILiveMMaking, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( MockLiveMM, mmaking::ILiveMMaking, BaseObjectMT );

    const Transport::TServiceId svcid;
    const bool logicSetupResult;
    Weak<socialLobby::MmLogix> logix;
    bool logicWasSetUp;
    rpc::Status mockConnStatus;

    MockLiveMM( socialLobby::MmLogix * _logix, const Transport::TServiceId & _svcid, const bool _logicSetupResult ) :
    svcid( _svcid ),
    logicSetupResult( _logicSetupResult ),
    logix( _logix ),
    logicWasSetUp( false ),
    mockConnStatus( rpc::Connected )
    {}

    virtual void SetupLogic( const string & _mapId, mmaking::ILiveMMakingClient* _client ) {
      TS_ASSERT( logix );
      logix->SetupResult( svcid, logicSetupResult );
      logicWasSetUp = true;
    }

    virtual void AddMmRequest( mmaking::TRequestUId _requestUId, const mmaking::SRequestCommonData & _commonData, const vector<mmaking::SRequestMember> & _members, timer::Time _waitTime ) {}
    virtual void RemoveMmRequest( mmaking::TRequestUId _requestUId ) {}
    virtual void AddGameForReconnect( lobby::TGameId _gameId, const mmaking::SGame & _gameData ) {}
    virtual void RemoveGame( lobby::TGameId _gameId ) {}

    virtual rpc::Status GetStatus() { return mockConnStatus; }
  };



  class MockMaps : public socialLobby::IMaps, public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2( MockMaps, IMaps, BaseObjectST );

    NDb::Ptr<NDb::AdvMapDescription> map;

  public:
    MockMaps() {
      map = new NDb::AdvMapDescription;
      NDb::AdvMapDescription * hacked = const_cast<NDb::AdvMapDescription *>( map.GetPtr() );
      hacked->productionMode = true;
    }

    virtual size_t Size() const { return 2; }

    virtual const char * GetMapId( size_t idx ) const { 
      if ( idx == 0 )
        return "mockmap0";
      else if ( idx == 1 )
        return "mockmap1";
      else
        TS_ASSERT( false );
      return 0;
    }

    virtual const NDb::AdvMapDescription * GetMap( size_t idx ) const
    {
      TS_ASSERT( idx < 2 );
      return map;
    }

    virtual const NDb::AdvMapDescription * FindMap( const char * mapId ) const
    {
      if ( !stricmp( mapId, "mockmap0" ) )
        return map;
      if ( !stricmp( mapId, "mockmap1" ) )
        return map;
      return 0;
    }
  };



  class MockMmClient : public mmaking::ILiveMMakingClient, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( MockMmClient, ILiveMMakingClient, BaseObjectMT );

  public:
    MockMmClient() {}

    void MmLogicSetupResult( const Transport::TServiceId & _svcId, bool _result ) {}
    void GameMatchmaked( const mmaking::SGame & _game ) {}
    void GameMatchmakedForReconnect( const mmaking::SReconnectSlot & _slot ) {}
    void MmResultAddRequest( mmaking::TRequestUId _requestUId, bool _ok ) {}
    void MmResultRemoveRequest( mmaking::TRequestUId _requestUId, bool _ok ) {}
    void MmResultAddReconnectGame( lobby::TGameId _gameId, bool _ok ) {}
    void MmResultRemoveReconnectGame( lobby::TGameId _gameId, bool _ok ) {}
    void MmDebugStatus( const char * _status ) {}
  };

  virtual void setUp()
  {}

  virtual void tearDown()
  {}

  void test_1()
  {
    Strong<MockMaps> maps = new MockMaps;
    StrongMT<MockMmClient> mockMmClient = new MockMmClient;
    Strong<socialLobby::MmLogix> logix = new socialLobby::MmLogix( socialLobby::CreateConfigFromStatics(), maps, mockMmClient );

    StrongMT<MockLiveMM> mm0 = new MockLiveMM( logix, "svc0", true );
    logix->RegisterMmLogic( "svc0", mm0, mmaking::EServiceGameModes::Any );

    StrongMT<MockLiveMM> mmx = new MockLiveMM( logix, "svc1", false );
    logix->RegisterMmLogic( "svc1", mmx, mmaking::EServiceGameModes::Any );

    StrongMT<MockLiveMM> mm1 = new MockLiveMM( logix, "svc2", true );
    logix->RegisterMmLogic( "svc2", mm1, mmaking::EServiceGameModes::Any );

    StrongMT<MockLiveMM> mmSpare = new MockLiveMM( logix, "svc3", true );
    logix->RegisterMmLogic( "svc3", mmSpare, mmaking::EServiceGameModes::Any );

    logix->Poll( 1.0 );

    TS_ASSERT( mm0->logicWasSetUp );
    TS_ASSERT( mmx->logicWasSetUp );
    TS_ASSERT( !mmSpare->logicWasSetUp );
    TS_ASSERT( !mm1->logicWasSetUp );

    logix->Poll( 2.0 );
    TS_ASSERT( !mm1->logicWasSetUp );

    logix->Poll( 3.0 );
    TS_ASSERT( mm1->logicWasSetUp );
  }
};
