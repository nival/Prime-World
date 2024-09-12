//!Component("Server/LobbySocial/SocialLobby")
//!Component("Server/LiveMMaking/SimpleMMaking")
//!Component('Server/LiveMMaking/MmTesting')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "SocialLobby.h"
#include "ISocialLobbyUserCtx.h"
#include "ISocialLobbyNotify.h"
#include "ISocialLobbyPvxAck.h"
#include "ISocialLobbyPvxSvc.h"
#include "SocialLobbyConfig.h"
#include "SocialLobbyMaps.h"
#include "Server/LiveMMaking/SimpleMMaking.h"
#include "Server/LiveMMaking/MMakingLog.h"
#include "Server/LiveMMaking/HeroesTable.h"
#include "Db/DBServer.auto.h"
#include "Server/LiveMMaking/MmTesting.h"
#include "System/TestAssertDumper.h"
#include "TestSet.h"


using namespace socialLobby;

struct Test_SocialLobby : public CxxTest::TestSuite, public MMakingTestBase
{
  struct EResponse
  {
    enum Enum {
      Open,
      Failure,
      Ping,
      Close
    };
  };



  enum {
    Ping_All_Fields       = 0xffffffff,
    Ping_Status           = 1,
    Ping_SessionContextId = 2,
    Ping_AcceptedPlayers  = 4,
    Ping_TotalPlayers     = 8,
    Ping_SessionKey       = 16,
    Ping_Winner           = 32,
    Ping_IsLeaver         = 64,
    Ping_Basket           = 128,
    Ping_GuardFoes        = 256,
    Ping_GuardAllies      = 512
  };


  class Response
  {
  public:
    Response( EResponse::Enum _type ) : type( _type ), ignoreFields( 0 ) {}

    Response( const SMatchmakingStatus & _ping, unsigned _ignoreFields = 0 ) :
    type( EResponse::Ping ), pingData( _ping ), ignoreFields( _ignoreFields ) {}

    void SetupSessionCtx( const string & sessId ) {
      pingData.sessionContextId = sessId;
    }

    EResponse::Enum Type() const { return type; }
    const SMatchmakingStatus & PingData() const { return pingData; }
    SMatchmakingStatus & PingData() { return pingData; }

    void CheckPing( const SMatchmakingStatus & subj )
    {
      if ( !( ignoreFields & Ping_Status ) )
        TS_ASSERT_EQUALS( pingData.progress, subj.progress );

      if ( !( ignoreFields & Ping_SessionContextId ) )
        TS_ASSERT_EQUALS( pingData.sessionContextId, subj.sessionContextId );

      if ( !( ignoreFields & Ping_AcceptedPlayers ) )
        TS_ASSERT_EQUALS( pingData.requestsAccepted, subj.requestsAccepted );

      if ( !( ignoreFields & Ping_TotalPlayers ) )
        TS_ASSERT_EQUALS( pingData.totalPlayers, subj.totalPlayers );

      if ( !( ignoreFields & Ping_SessionKey ) )
        TS_ASSERT_EQUALS( pingData.pvxSessionKey.empty(), subj.pvxSessionKey.empty() );

      if ( !( ignoreFields & Ping_Winner ) )
        TS_ASSERT_EQUALS( pingData.gameResults.winner, subj.gameResults.winner );

      if ( !( ignoreFields & Ping_IsLeaver ) )
        TS_ASSERT_EQUALS( pingData.gameResults.playerIsLeaver, subj.gameResults.playerIsLeaver );

      if ( !( ignoreFields & Ping_Basket ) )
        TS_ASSERT_EQUALS( pingData.gameBasket, subj.gameBasket );

      if ( !( ignoreFields & Ping_GuardFoes ) )
        TS_ASSERT_EQUALS( pingData.preGameLobbyInfo.foesReady, subj.preGameLobbyInfo.foesReady );

      if ( !( ignoreFields & Ping_GuardAllies ) )
        TS_ASSERT_EQUALS( pingData.preGameLobbyInfo.allies, subj.preGameLobbyInfo.allies );
    }

  private:
    EResponse::Enum type;
    SMatchmakingStatus pingData;
    unsigned ignoreFields;
  };

  class ResponseOpen : public Response {
  public:
    ResponseOpen() : Response( EResponse::Open ) {}
  };

  class ResponseFailure : public Response {
  public:
    ResponseFailure() : Response( EResponse::Failure ) {}
  };

  class ResponseClose : public Response {
  public:
    ResponseClose() : Response( EResponse::Close ) {}
  };



  struct CreateParams
  {
    int                     count;
    lobby::ETeam::Enum      team;
    mmaking::EBasket::Enum  basket;
    bool                    tossTeams;
    int                     heroRating;
    bool                    enterPvX;
    string                  mapId;
    bool                    expectOpen;

    void ConstructDefault() {
      count = 10;
      team = lobby::ETeam::Team1;
      basket = mmaking::EBasket::Normal;
      tossTeams = true;
      heroRating = 1500;
      enterPvX = true;
      mapId = "mockmap0";
      expectOpen = true;
    }

    CreateParams() { ConstructDefault(); }

    CreateParams( int c, lobby::ETeam::Enum t )
    {
      ConstructDefault();
      count = c;
      team = t;
    }

    CreateParams & Count( int c ) { count = c; return *this; }
    CreateParams & Team( lobby::ETeam::Enum t ) { team = t; return *this; }
    CreateParams & Basket( mmaking::EBasket::Enum b ) { basket = b; return *this; }
    CreateParams & EnterPvx( bool e ) { enterPvX = e; return *this; }
    CreateParams & HeroRating( int r ) { heroRating = r; return *this; }
    CreateParams & TossTeams( bool toss ) { tossTeams = toss; return *this; }
    CreateParams & ExpectOpen( bool expect ) { expectOpen = expect; return *this; }
  };


  class Request;

  typedef StrongMT<Request> ReqPtr;
  typedef TTestSet<ReqPtr, std::vector<ReqPtr>, ni_detail::TestVectorPolicy<ReqPtr>> Requests;

  typedef TestIntSet Set;


  class Request : public socialLobby::INotify, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( Request, socialLobby::INotify, BaseObjectMT );

  public:
    Request( socialLobby::TUId _uid, const CreateParams & params ) :
    auxParam( 0 ),
    readyAsAGuard( false )
    {
      data.uid = _uid;
      data.userIdPvx = 100500 - _uid;
      data.sessionContextId = NStr::StrFmt( "session%lld", _uid * 2 );
      data.map = params.mapId;
      data.faction = params.team;
      data.heroId = "M1";
      data.zzimaSex = lobby::ESex::Male;
      data.basket = params.basket;
      data.heroRating = params.heroRating;
      data.playerRating = 1000;
      data.guardRating = 1000;
      data.login = NStr::StrFmt( "User%lld", _uid );
      data.nickname = NStr::StrFmtW( L"Player%lld", _uid );
      data.partyId = 0;
      data.geoInfo = mmaking::SGeoInfo( "ru" );
      data.geoInfo.pings.push_back( mmaking::SLocationPing( "ru0", 10 ) );
    }

    Request( const SMatchmakingRequest & _data ) :
    data( _data ), auxParam( 0 ), readyAsAGuard( false )
    {}

    ~Request() {
      TS_ASSERT( expectedResponses.empty() );
    }

    //WTF???
    void SetAuxParam( int _auxParam ) { auxParam = _auxParam; }
    int AuxParam() const { return auxParam; }

    void SetupParty( TPartyId partyid, const Requests & allyParty, const Requests & enemyParty )
    {
      data.partyId = partyid;

      for ( Requests::const_iterator it = allyParty.begin(); it != allyParty.end(); ++it )
        data.partyLineup.push_back( (*it)->Data().userIdPvx );

      for ( Requests::const_iterator it = enemyParty.begin(); it != enemyParty.end(); ++it )
        data.enemyPartyLineup.push_back( (*it)->Data().userIdPvx );
    }

    const SMatchmakingRequest & Data() const { return data; }

    void Expect( const Response & r ) {
      expectedResponses.push_back( r );
      if ( r.Type() == EResponse::Ping )
      {
        expectedResponses.back().SetupSessionCtx( data.sessionContextId );
      }
    }

    Response & GetLastResponse() {
      TS_ASSERT( !expectedResponses.empty() );
      return expectedResponses.back();
    }

    void FlushExpectations() { expectedResponses.clear(); }

    IUserContext * Context() {
      TS_ASSERT( context );
      return context;
    }

    bool ReadyAsAGuard() const { return readyAsAGuard; }
    void SetGuardReadiness( bool rdy ) { readyAsAGuard = rdy; }

  private:
    SMatchmakingRequest     data;
    std::list<Response>     expectedResponses;
    StrongMT<IUserContext>  context;
    int                     auxParam;
    bool                    readyAsAGuard;

    Response PopExpectedResponse() {
      TS_ASSERT( !expectedResponses.empty() );
      Response r = expectedResponses.front();
      expectedResponses.pop_front();
      return r;
    }

    void CheckResponse( EResponse::Enum type ) {
      Response r = PopExpectedResponse();
      TS_ASSERT_EQUALS( r.Type(), type );
    }

    //socialLobby::INotify
    virtual void Open( IUserContext * _ctx ) {
      CheckResponse( EResponse::Open );
      context = _ctx;
    }

    virtual void Failure() {
      CheckResponse( EResponse::Failure );
      context = 0;
    }

    virtual void UpdateStatus( const SMatchmakingStatus & _status ) {
      Response r = PopExpectedResponse();
      TS_ASSERT_EQUALS( r.Type(), EResponse::Ping );
      r.CheckPing( _status );
    }

    virtual void Close() {
      CheckResponse( EResponse::Close );
      context = 0;
    }

    //rpc::IRemoteEntity
    virtual rpc::Status GetStatus() { return rpc::Connected; } //TODO: write test for disconnected notify
  };


  static bool Equals( const Requests & _refGame, const mmaking::SGame & _game, bool checkTeams )
  {
    size_t total = 0;
    for ( int pi = 0; pi < _game.humans.size(); ++pi )
      total += (size_t)_game.humans[pi].members.size();

    if ( _refGame.size() != total )
      return false;

    for ( size_t i = 0; i < _refGame.size(); ++i )
    {
      const TUserIdPvX userId = _refGame[i]->Data().userIdPvx;
      const lobby::ETeam::Enum team = _refGame[i]->Data().faction;

      bool found = false;
      for ( int pi = 0; !found && pi < _game.humans.size(); ++pi )
        if ( !checkTeams || ( _game.humans[pi].common.team == team ) )
          for ( int mi = 0; !found && mi < _game.humans[pi].members.size(); ++mi )
            if ( _game.humans[pi].members[mi].mmId == userId )
              found = true;

      if ( !found )
        return false;
    }
    return true;
  };


  static bool Equals( const SMatchmakingStatus & one, const SMatchmakingStatus & another )
  {
    return 
      ( one.pvxSessionKey.empty() == another.pvxSessionKey.empty() ) &&
      ( one.sessionContextId.empty() || another.sessionContextId.empty() || ( one.sessionContextId == another.sessionContextId ) ) &&
      ( one.progress == another.progress ) &&
      ( one.requestsAccepted == another.requestsAccepted ) &&
      ( one.totalPlayers == another.totalPlayers ) &&
      ( one.gameResults.winner == another.gameResults.winner ) &&
      ( one.gameResults.playerIsLeaver == another.gameResults.playerIsLeaver );
  }



  Requests Subset( const Requests & requests, const Set & indices )
  {
    Requests result;
    result.reserve( indices.size() );
    for ( Set::const_iterator it = indices.begin(); it != indices.end(); ++it )
    {
      int idx = *it;
      TS_ASSERT( idx >= 0 && idx < (int)requests.size() );
      result.push_back( requests[idx] );
    }
    return result;
  }



  Requests SubsetInv( const Requests & requests, const Set & indices )
  {
    Requests result;
    result.reserve( requests.size() );
    for ( size_t i = 0; i < requests.size(); ++i )
    {
      if ( indices.find( i ) != indices.end() )
        continue;
      result.push_back( requests[i] );
    }
    return result;
  }


  struct Ping : public SMatchmakingStatus
  {
    Ping() {
    }

    Ping( ERequestStatus::Enum _prog ) {
      progress = _prog;
    }

    Ping( ERequestStatus::Enum _prog, int _accepted, int _total ) {
      progress = _prog;
      requestsAccepted = _accepted;
      totalPlayers = _total;
      gameBasket = mmaking::EBasket::Normal;
    }

    Ping( ERequestStatus::Enum _prog, int _total, const string & _sessLogin ) {
      progress = _prog;
      requestsAccepted = 0;
      totalPlayers = _total;
      pvxSessionKey = _sessLogin;
      gameBasket = mmaking::EBasket::Normal;
    }

    Ping( ERequestStatus::Enum _prog, lobby::ETeam::Enum _winner, bool _leaver ) {
      progress = _prog;
      gameResults.winner = _winner;
      gameResults.playerIsLeaver = _leaver;
    }

    Ping & SetSessionId( socialLobby::TUId _uid ) {
      sessionContextId = NStr::StrFmt( "session%lld", _uid * 2 );
      return *this;
    }

    Ping & SetBasket( mmaking::EBasket::Enum _basket ) {
      gameBasket = _basket;
      return *this;
    }

    Ping & SetFoes( int _number ) {
      preGameLobbyInfo.foesReady = _number;
      return *this;
    }
  };



  struct MockLiveMM : public mmaking::ILiveMMaking, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( MockLiveMM, mmaking::ILiveMMaking, BaseObjectMT );

    StrongMT<mmaking::StubMMaking> pvpLogic;
    StrongMT<MMakingLogicCallbackMock> logicCallback;
    const Transport::TServiceId svcid;
    string mapId;
    bool mockSetupResult;
    rpc::Status mockConnStatus;

    MockLiveMM( mmaking::StubMMaking * _pvpLogic, MMakingLogicCallbackMock * _logicCallback, const Transport::TServiceId & _svcid ) :
    pvpLogic( _pvpLogic ),
    logicCallback( _logicCallback ),
    svcid( _svcid ),
    mockSetupResult( true ),
    mockConnStatus( rpc::Connected )
    {}

    virtual void SetupLogic( const string & _mapId, mmaking::ILiveMMakingClient* _client ) {
      mapId = _mapId;
      _client->MmLogicSetupResult( svcid, mockSetupResult );
    }

    virtual void AddMmRequest( mmaking::TRequestUId _requestUId, const mmaking::SRequestCommonData & _commonData, const vector<mmaking::SRequestMember> & _members, timer::Time _waitTime ) {
      pvpLogic->AddGroupRequest( _requestUId, _commonData, _members, _waitTime, logicCallback );
    }

    virtual void RemoveMmRequest( mmaking::TRequestUId _requestUId ) {
      pvpLogic->RemoveRequest( _requestUId, logicCallback );
    }

    virtual void AddGameForReconnect( lobby::TGameId _gameId, const mmaking::SGame & _gameData ) {
      TS_ASSERT( _gameData.mapId == mapId );
      pvpLogic->AddGameForReconnect( _gameId, _gameData, logicCallback );
    }

    virtual void RemoveGame( lobby::TGameId _gameId ) {
      pvpLogic->RemoveGame( _gameId, logicCallback );
    }

    virtual rpc::Status GetStatus() { return mockConnStatus; }
  };



  class SocialStatisticsMock : public socialLobby::IGameStatistics, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( SocialStatisticsMock, socialLobby::IGameStatistics, BaseObjectMT );
  public:
    virtual void LogMMakingCancelled( const StatisticService::RPC::MMakingCanceled & _data ) {}
    virtual void LogMMakingGame( const StatisticService::RPC::MMakingGame & _game ) {}
  };



  class PvxAckMock : public socialLobby::IPvxAcknowledge, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( PvxAckMock, socialLobby::IPvxAcknowledge, BaseObjectMT );

  public:
    virtual void NewGameAck( lobby::TSocialGameId _gameId ) {
    }
    virtual void NewReconnectingUserAck( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId ) {
    }
    virtual void NewSpectatorAck( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId ) {
    }
    virtual void UserLeftTheGameInCastleAck( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId ) {
    }
  };


  class PvxSvcMock : public socialLobby::IPvxSvc, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( PvxAckMock, socialLobby::IPvxSvc, BaseObjectMT );

  public:
    PvxSvcMock() {}

    virtual void NewGame( lobby::TSocialGameId _gameId, const mmaking::SGame & _game, const socialLobby::PvxGameDetails & _gameDetails, socialLobby::IPvxAcknowledge* _ack ) {
      newGames.push_back();
      NewGameLog & G = newGames.back();
      G.gameId = _gameId;
      G.game = _game;
      G.gameDetails = _gameDetails;
    }

    virtual void NewReconnectingUser( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, socialLobby::IPvxAcknowledge* _ack ) {
      newReconnects.push_back();
      UserGameRecord & R = newReconnects.back();
      R.gameId = _gameId;
      R.userId = _userId;
    }

    virtual void NewSpectator( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, const string& _login, NI_LPTR IPvxAcknowledge* _ack, const wstring& nickname )
    {
      newSpectators.push_back();
      NewSpect & S = newSpectators.back();
      S.gameId = _gameId;
      S.userId = _userId;
      S.login = _login;
    }

    virtual void UserLeftTheGameInCastle( lobby::TSocialGameId _gameId, socialLobby::TUserIdPvX _userId, socialLobby::IPvxAcknowledge* _ack )
    {
      newUsersLeftTheGame.push_back();
      UserGameRecord & R = newUsersLeftTheGame.back();
      R.gameId = _gameId;
      R.userId = _userId;
    }


    struct NewGameLog {
      lobby::TSocialGameId  gameId;
      mmaking::SGame        game;
      socialLobby::PvxGameDetails gameDetails;
      NewGameLog() : gameId( 0 ) {}
    };

    struct UserGameRecord {
      lobby::TSocialGameId  gameId;
      socialLobby::TUserIdPvX userId;
      UserGameRecord() : gameId( 0 ), userId( 0 ) {}
    };

    struct NewSpect {
      lobby::TSocialGameId  gameId;
      socialLobby::TUserIdPvX userId;
      string login;
      NewSpect() : gameId( 0 ), userId( 0 ) {}
    };

    //rpc::IRemoteEntity
    virtual rpc::Status GetStatus() { return rpc::Connected; }

    list<NewGameLog>      newGames;
    list<UserGameRecord>  newReconnects;
    list<NewSpect>        newSpectators;
    list<UserGameRecord>  newUsersLeftTheGame;
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

      hacked->rollSettings = new NDb::ModeRollSettings;
      NDb::ModeRollSettings * hackedRs = const_cast<NDb::ModeRollSettings *>( hacked->rollSettings.GetPtr() );
      hackedRs;
    }

    virtual size_t Size() const { return 2; }

    virtual const char * GetMapId( size_t idx ) const { 
      if ( idx == 0 )
        return "mockmap0";
      if ( idx == 1 )
        return "mockmap1";
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
      return map;
    }
  };


  StrongMT<mmaking::StubMMaking> logic;
  std::list<StrongMT<MockLiveMM>> mmLogics;
  Strong<Config> slConfig;
  StrongMT<SocialLobby> socLobby;
  StrongMT<PvxSvcMock> pvxMock;
  StrongMT<PvxAckMock> pvxAckMock;
  Strong<MockMaps> mockMaps;
  float currentTestTime;

  ISocialInterface * GetSocialInterface() { return socLobby; }
  IPvxInterface * GetPvxLobbyInterface() { return socLobby; }
  mmaking::ILiveMMakingClient * GetAsLiveMMakingClient() { return socLobby; }

  socialLobby::TUId nextUId;
  int nextPartyId;

  SPlayerData mockPlayerData;

  Set All;

  virtual void setUp()
  {
    NLogg::FailTestOnLogLevel( NLogg::LEVEL_WARNING, false );
    NLogg::FailTestOnLogLevel( NLogg::LEVEL_ERROR, false );

    setUpMmTest();

    currentTestTime = 0;

    mmConfig->logLevel = mmaking::ELogLevel::Verbose;
    mmConfig->mockMinimumUserWait = 10.0;
    logic = new mmaking::StubMMaking( settings, mmConfig, heroes, 5, NDb::MAPTYPE_PVP, "MyMapId", 0 );
    logic->EnableAlgoStartRotation( false );

    slConfig = CreateConfigFromStatics();
    slConfig->acceptTimeout = 120.0f;
    slConfig->backupTimeoutLong = 60.0f; //in munutes

    //TODO: Setup 'mockPlayerData'

    NDb::Ptr<NDb::RollSettings> rollSett = new NDb::RollSettings;
    NDb::RollSettings * hackedRoll = const_cast<NDb::RollSettings *>( rollSett.GetPtr() );
    hackedRoll->ratingModifiers;

    pvxAckMock = new PvxAckMock;
    mockMaps = new MockMaps;
    socLobby = new SocialLobby( slConfig, new SocialStatisticsMock, pvxAckMock, mockMaps, rollSett, 0 );

    //Logic one
    mmLogics.push_back( new MockLiveMM( logic, logicCallback, "mmsvcid0" ) );
    GetSocialInterface()->RegisterMmLogic( mmLogics.back()->svcid, mmLogics.back(), mmaking::EServiceGameModes::Any );

    //Fail one setup
    mmLogics.push_back( new MockLiveMM( logic, logicCallback, "mmsvcid1" ) );
    mmLogics.back()->mockSetupResult = false;
    GetSocialInterface()->RegisterMmLogic( mmLogics.back()->svcid, mmLogics.back(), mmaking::EServiceGameModes::Any );

    //Logic two
    mmLogics.push_back( new MockLiveMM( logic, logicCallback, "mmsvcid2" ) );
    GetSocialInterface()->RegisterMmLogic( mmLogics.back()->svcid, mmLogics.back(), mmaking::EServiceGameModes::Any );

    //One extra logic (we have only two mock maps)
    mmLogics.push_back( new MockLiveMM( logic, logicCallback, "mmsvcid3" ) );
    GetSocialInterface()->RegisterMmLogic( mmLogics.back()->svcid, mmLogics.back(), mmaking::EServiceGameModes::Any );

    pvxMock = new PvxSvcMock;
    TS_ASSERT( GetPvxLobbyInterface()->PvxInstance( pvxMock, "A", "svc0", 1000, vector<socialLobby::TUId>(), 0 ) );

    socLobby->Poll( currentTestTime );
    socLobby->Poll( currentTestTime );

    nextUId = 1;
    nextPartyId = 1;

    All = Set( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 );
  }



  virtual void tearDown()
  {
    currentTestTime = 0;
    mockPlayerData = SPlayerData();
    mmLogics.clear();
    logic = 0;
    socLobby = 0;
    mockMaps = 0;
    nextUId = 0;
    nextPartyId = 0;

    tearDownMmTest();
  }


  void PumpGames()
  {
    while ( true )
    {
      mmaking::SGame game;
      string mapId;
      if ( !logic->PopGame( game ) )
        break;
      static_cast<mmaking::ILiveMMakingClient*>(socLobby)->GameMatchmaked( game );
    }
  }


  void AdvanceTimeAndPoll( float delta )
  {
    TS_ASSERT( delta > .5f );

    logic->SetTime( currentTestTime );
    logic->Poll(); //Double poll to pull the imcoming requests with right time values
    PumpGames();

    currentTestTime += delta;

    logic->SetTime( currentTestTime );
    logic->Poll();
    PumpGames();

    socLobby->Poll( currentTestTime );
  }



  ReqPtr Create( socialLobby::TUId _uid, const CreateParams & params )
  {
    ReqPtr req = new Request( _uid, params );
    if ( params.expectOpen )
      req->Expect( ResponseOpen() );
    return req;
  }

  ReqPtr Create( const CreateParams & params ) {
    return Create( nextUId++, params );
  }



  Requests CreateParty( const CreateParams & params = CreateParams() )
  {
    Requests requests;

    for ( int i = 0; i < params.count; ++i )
      requests << Create( nextUId++, params );

    SetupNewParty( params, requests, Requests() );

    return requests;
  }


  void Expect( const Requests & requests, const Response & response, lobby::ETeam::Enum faction = lobby::ETeam::None ) {
    for ( Requests::const_iterator it = requests.begin(); it != requests.end(); ++it ) {
      if ( ( faction != lobby::ETeam::None ) && ( (*it)->Data().faction != faction ) )
        continue;
      (*it)->Expect( response );
    }
  }


  void ExpectPing( const Requests & requests, const Ping & ping, lobby::ETeam::Enum faction = lobby::ETeam::None ) {
    Expect( requests, Response( ping ), faction );
  }


  void SetupGuardLobbyExpectations( const Requests & requests )
  {
    for ( Requests::const_iterator it = requests.begin(); it != requests.end(); ++it ) {
      Response & R = (*it)->GetLastResponse();
      TS_ASSERT( R.Type() == EResponse::Ping );
      TS_ASSERT( R.PingData().progress == ERequestStatus::PreGameLobby );
    }

    for ( Requests::const_iterator it = requests.begin(); it != requests.end(); ++it )
    {
      Request * req = (*it);
      SMatchmakingStatus & ping = req->GetLastResponse().PingData();
      int foesRdy = 0;
      for ( Requests::const_iterator it = requests.begin(); it != requests.end(); ++it )
      {
        Request * tmpReq = (*it);
        if ( req->Data().faction == tmpReq->Data().faction ) {
          ping.preGameLobbyInfo.allies.push_back( SAllyStatus( tmpReq->Data().uid, tmpReq->ReadyAsAGuard() ) );
        }
        else {
          if ( tmpReq->ReadyAsAGuard() )
            ++foesRdy;
        }
      }
      ping.preGameLobbyInfo.foesReady = foesRdy;
    }
  }


  void Add1( Request * req )
  {
    GetSocialInterface()->AddRequest( req->Data(), req );
  }


  void Add( const Requests & requests ) {
    for ( Requests::const_iterator it = requests.begin(); it != requests.end(); ++it )
      Add1( *it );
  }


  ReqPtr CreateAndAdd( socialLobby::TUId _uid, const CreateParams & params )
  {
    ReqPtr req = Create( _uid, params );
    Add( req );
    return req;
  }


  Requests CreateAndAddParty( const CreateParams & params )
  {
    Requests requests = CreateParty( params );
    Add( requests );
    return requests;
  }


  Requests CreateAndAddParty( const CreateParams & params, const Set & indices )
  {
    Requests requests = CreateParty( params );
    Add( Subset( requests, indices ) );
    return requests;
  }


  Requests CreateSome( const CreateParams & params ) {
    Requests requests;
    CreateParams newParams = params;
    for ( int i = 0; i < params.count; ++i ) {
      requests << Create( nextUId++, newParams );
      if ( params.tossTeams )
        newParams.team = ( newParams.team == lobby::ETeam::Team1 ) ? lobby::ETeam::Team2 : lobby::ETeam::Team1;
    }
    return requests;
  }


  Requests CreateAndAddSome( const CreateParams & params ) {
    Requests requests = CreateSome( params );
    Add( requests );
    return requests;
  }


  void SetupNewParty( const CreateParams & params, const Requests & team1, const Requests & team2 )
  {
    int partyid = nextPartyId++;

    for ( Requests::const_iterator it = team1.begin(); it != team1.end(); ++it )
      (*it)->SetupParty( partyid, team1, team2 );

    for ( Requests::const_iterator it = team2.begin(); it != team2.end(); ++it )
      (*it)->SetupParty( partyid, team1, team2 );
  }


  void Cancel1( Request * req )
  {
    req->Expect( ResponseClose() );
    req->Context()->CancelRequest();
  }


  void Cancel( const Requests & requests ) {
    for ( Requests::const_iterator it = requests.begin(); it != requests.end(); ++it )
      Cancel1( *it );
  }


  void Spectate1( Request * req, TUId _targetUid )
  {
    GetSocialInterface()->Spectate( req->Data(), _targetUid, req );
  }


  void Spectate( const Requests & requests, TUId _targetUid )
  {
    for ( Requests::const_iterator it = requests.begin(); it != requests.end(); ++it )
      Spectate1( *it, _targetUid );
  }
  

  Requests AddSomeAndWaitGame( const CreateParams & params )
  {
    Requests requests = CreateAndAddSome( params );
    WaitGame( requests, params );
    return requests;
  }


  void WaitGame( const Requests & requests, const CreateParams & params )
  {
    ExpectPing( requests, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0f );
    ExpectPing( requests, Ping( ERequestStatus::WaitingAccept, 0, requests.size() ).SetBasket( params.basket ) );
    AdvanceTimeAndPoll( 20.0f );
  }


  void Accept1( Request * req )
  {
    req->Context()->AcceptGameSession( mockPlayerData );
  }


  void Accept( const Requests & requests )
  {
    for ( Requests::const_iterator it = requests.begin(); it != requests.end(); ++it )
      Accept1( *it );
  }


  void AcceptGame( const Requests & game )
  {
    Accept( game );
    ExpectPing( game, Ping( ERequestStatus::PreparingPvX, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );
  }


  void GuardReady1( Request * req )
  {
    req->Context()->ChangeGuardHero( mockPlayerData );
    //TODO: Write separate test for ChangeGuardHero() !!!

    req->Context()->GuardReady();
    req->SetGuardReadiness( true );
  }


  void GuardReady( const Requests & requests )
  {
    for ( Requests::const_iterator it = requests.begin(); it != requests.end(); ++it )
      GuardReady1( *it );
  }


  Requests AddAndAcceptGame( const CreateParams & params )
  {
    Requests game = AddSomeAndWaitGame( params );
    AdvanceTimeAndPoll( 1.0 );
    AcceptGame( game );
    return game;
  }


  PvxSvcMock::NewGameLog PopGame( const Requests & refGame, mmaking::EBasket::Enum basket = mmaking::EBasket::Normal, bool checkTeams = true )
  {
    TS_ASSERT( !pvxMock->newGames.empty() );
    PvxSvcMock::NewGameLog newGame = pvxMock->newGames.front();
    pvxMock->newGames.pop_front();

    TS_ASSERT( Equals( refGame, newGame.game, checkTeams ) );
    TS_ASSERT( newGame.game.mapType != NDb::MAPTYPE_NONE );

    for ( size_t i = 0; i < refGame.size(); ++i ) {
      const socialLobby::PlayerDetails * details = newGame.gameDetails.FindPlayer( refGame[i]->Data().userIdPvx );
      TS_ASSERT( details );
      TS_ASSERT( details->nick == wstring( NStr::StrFmtW( L"Player%d", refGame[i]->Data().uid ) ) );

      //TODO: Check party ids in socialLobby::PlayerDetails
    }

    PvxPrepared( refGame );

    ExpectPing( refGame, Ping( ERequestStatus::WaitingInPvX, refGame.size(), "Not empty" ).SetBasket( basket ) );
    AdvanceTimeAndPoll( 1.0 );

    return newGame;
  }



  void PvxPrepared1( Request * req ) {
    TS_ASSERT( GetPvxLobbyInterface()->PvXPreparedForUser( req->Data().userIdPvx, "Key" ) );
  }


  void PvxPrepared( const Requests & requests ) {
    for ( size_t i = 0; i < requests.size(); ++i )
      PvxPrepared1( requests[i] );
  }


  void EnterPvX1( Request * req ) {
    TS_ASSERT( GetPvxLobbyInterface()->UserEnteredPvX( req->Data().userIdPvx ) );
  }


  void EnterPvX( const Requests & requests ) {
    for ( size_t i = 0; i < requests.size(); ++i )
      EnterPvX1( requests[i] );
  }


  void DropFromPvX1( Request * req, bool intentional ) {
    TS_ASSERT( GetPvxLobbyInterface()->UserDroppedFromPvX( req->Data().userIdPvx, intentional ) );
  }


  void DropFromPvX( const Requests & requests, bool intentional ) {
    for ( size_t i = 0; i < requests.size(); ++i )
      DropFromPvX1( requests[i], intentional );
  }


  void Leave( const Requests & requests ) {
    for ( size_t i = 0; i < requests.size(); ++i )
      requests[i]->Context()->LeaveGame();
  }


  void Reconnect( const Requests & requests ) {
    for ( size_t i = 0; i < requests.size(); ++i )
      requests[i]->Context()->ReconnectToGame();
  }


  Requests CreateGame( lobby::TSocialGameId & _mmGameId, const CreateParams & params )
  {
    Requests game = AddAndAcceptGame( params );
    _mmGameId = PopGame( game, params.basket ).gameId;
    if ( params.enterPvX ) {
      EnterPvX( game );
      ExpectPing( game, Ping( ERequestStatus::InGame, 0, game.size() ) );
      AdvanceTimeAndPoll( 1.0 );
    }
    return game;
  }


  void FinishGame( const Requests & _game, lobby::TSocialGameId _gameId, lobby::ETeam::Enum _winner )
  {
    TS_ASSERT( GetPvxLobbyInterface()->GameFinished( _gameId, _winner ) );
  }


  void CheckGameResults( const Requests & _game, lobby::ETeam::Enum _winner, const Set & _leavers = Set() )
  {
    lobby::ETeam::Enum loser = lobby::ETeam::Invert( _winner );

    ExpectPing( SubsetInv( _game, _leavers ),   Ping( ERequestStatus::GameFinished, _winner, false ), _winner );
    ExpectPing( Subset( _game, _leavers ),      Ping( ERequestStatus::GameFinished, _winner, true ), _winner );

    if ( _winner != lobby::ETeam::None ) {
      ExpectPing( SubsetInv( _game, _leavers ), Ping( ERequestStatus::GameFinished, _winner, false ), loser );
      ExpectPing( Subset( _game, _leavers ),    Ping( ERequestStatus::GameFinished, _winner, true ), loser );
    }

    AdvanceTimeAndPoll( 1.0 );
  }


  void EnsureNoGame()
  {
    TS_ASSERT( pvxMock->newGames.empty() );
  }

  //-------------------------------------
  //           The tests itself
  //-------------------------------------
  void test_trivial()
  {
    ReqPtr r1 = CreateAndAdd( 100, CreateParams( 0, lobby::ETeam::Team1 ) );
    ReqPtr r2 = CreateAndAdd( 101, CreateParams( 0, lobby::ETeam::Team2 ) );
    ExpectPing( r1, ERequestStatus::InLine );
    ExpectPing( r2, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );
    Cancel( r1 );
    AdvanceTimeAndPoll( 1.0 );
    Cancel( r2 );
  }



  void test_get_request_ok()
  {
    Requests party = CreateAndAddParty( CreateParams( 2, lobby::ETeam::Team1 ), 0 );
    ExpectPing( party[0], ERequestStatus::WaitingPartyMembers );
    AdvanceTimeAndPoll( 1.0 );

    ReqPtr copy = new Request( party[0]->Data() );
    copy->Expect( ResponseOpen() );
    GetSocialInterface()->GetRequest( copy->Data().uid, copy );
    TS_ASSERT( copy->Context() );

    //Test that 'copy' is fully functional
    Add( party[1] );
    ExpectPing( party[1], ERequestStatus::InLine );
    ExpectPing( copy, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( copy );
  }


  void test_get_request_failed()
  {
    ReqPtr r = new Request( 0, CreateParams( 0, lobby::ETeam::None ) );
    r->Expect( ResponseFailure() );
    GetSocialInterface()->GetRequest( 100500, r );
  }


  void test_status_timeout_long()
  {
    Requests requests = CreateAndAddSome( CreateParams().Count( 4 ) );
    ExpectPing( requests, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 31.0f );
    AdvanceTimeAndPoll( 60.0f * 59.0f );
    Expect( requests, ResponseClose() );
    AdvanceTimeAndPoll( 31.0f );
  }


  void test_status_timeout_short()
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams() );
    FinishGame( game, mmGameId, lobby::ETeam::Team1 );
    CheckGameResults( game, lobby::ETeam::Team1 );
    AdvanceTimeAndPoll( 590.0 );
    //No reaction yet
    Expect( game, ResponseClose() );
    AdvanceTimeAndPoll( 11.0 );
  }


  void test_create_game()
  {
    AddSomeAndWaitGame( CreateParams() );
  }


  void test_accept()
  {
    Requests game = AddSomeAndWaitGame( CreateParams() );

    Accept( game[2] );
    ExpectPing( game[2], Ping( ERequestStatus::Accepted, 1, 10 ) );
    ExpectPing( SubsetInv( game, 2 ), Ping( ERequestStatus::WaitingAccept, 1, 10 ) );
    AdvanceTimeAndPoll( 1.0 );

    Accept( game[5] );
    ExpectPing( Subset( game, Set( 2, 5 ) ), Ping( ERequestStatus::Accepted, 2, 10 ) );
    ExpectPing( SubsetInv( game, Set( 2, 5 ) ), Ping( ERequestStatus::WaitingAccept, 2, 10 ) );
    AdvanceTimeAndPoll( 1.0 );

    Accept( SubsetInv( game, Set( 2, 5 ) ) );
    ExpectPing( game, Ping( ERequestStatus::PreparingPvX, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( game );
  }


  void test_pop_game()
  {
    Requests game = AddSomeAndWaitGame( CreateParams() );
    Accept( game );

    ExpectPing( game, Ping( ERequestStatus::PreparingPvX, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    PopGame( game );
    Cancel( game );
  }


  void test_smoke()
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams() );
    FinishGame( game, mmGameId, lobby::ETeam::Team1 );
    CheckGameResults( game, lobby::ETeam::Team1 );
    DropFromPvX( game, false );
    AdvanceTimeAndPoll( 1.0 );
    Cancel( game );
  }



  void test_many_smoke()
  {
    for ( int i = 0; i < 10; ++i )
      test_smoke();
  }



  void test_cancel_then_add()
  {
    Requests R = CreateAndAddSome( CreateParams().Count( 4 ) );
    ExpectPing( R, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( Subset( R, Set( 2, 3 ) ) );
    AdvanceTimeAndPoll( 1.0 );
    Expect( Subset( R, Set( 2, 3 ) ), ResponseOpen() );
    Add( Subset( R, Set( 2, 3 ) ) );
    ExpectPing( Subset( R, Set( 2, 3 ) ), ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );
  }



  void test_cancel_game()
  {
    Requests game = AddSomeAndWaitGame( CreateParams() );

    Cancel( Subset( game, Set( 3, 4, 5 ) ) );
    ExpectPing( SubsetInv( game, Set( 3, 4, 5 ) ), Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( SubsetInv( game, Set( 3, 4, 5 ) ) );
    AdvanceTimeAndPoll( 1.0 );
  }



  ////////////////////////
  // Accept and Disband //
  ////////////////////////
  void test_partial_game_accept_when_accept_comes_last()
  {
    Requests game = AddSomeAndWaitGame( CreateParams() );

    Cancel( Subset( game, Set( 0, 1, 2, 3, 4 ) ) );
    ExpectPing( Subset( game, Set( 5, 6, 7, 8, 9 ) ), Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    AdvanceTimeAndPoll( 1.0 );

    Accept( Subset( game, Set( 5, 6, 7, 8 ) ) );
    ExpectPing( game[9], Ping( ERequestStatus::WaitingAccept, 4, 10 ) );
    ExpectPing( Subset( game, Set( 5, 6, 7, 8 ) ), Ping( ERequestStatus::Accepted, 4, 10 ) );
    AdvanceTimeAndPoll( 1.0 );

    Accept( game[9] ); //With last accept game is destroyed
    ExpectPing( Subset( game, Set( 5, 6, 7, 8, 9 ) ), ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( Subset( game, Set( 5, 6, 7, 8, 9 ) ) );
  }



  void test_partial_game_accept_when_cancel_comes_last()
  {
    Requests game = AddSomeAndWaitGame( CreateParams() );

    Accept( Subset( game, Set( 5, 6, 7, 8, 9 ) ) );
    ExpectPing( Subset( game, Set( 0, 1, 2, 3, 4 ) ), Ping( ERequestStatus::WaitingAccept, 5, 10 ) );
    ExpectPing( Subset( game, Set( 5, 6, 7, 8, 9 ) ), Ping( ERequestStatus::Accepted, 5, 10 ) );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( Subset( game, Set( 1, 2, 3, 4 ) ) );
    ExpectPing( game[0], Ping( ERequestStatus::WaitingAccept, 5, 10 ) );
    ExpectPing( Subset( game, Set( 5, 6, 7, 8, 9 ) ), Ping( ERequestStatus::Accepted, 5, 10 ) );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( game[0] );
    ExpectPing( Subset( game, Set( 5, 6, 7, 8, 9 ) ), ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( Subset( game, Set( 5, 6, 7, 8, 9 ) ) );
  }



  void test_accept_timeout()
  {
    Requests game = AddSomeAndWaitGame( CreateParams() );
    AdvanceTimeAndPoll( 1.0 );

    Accept( Subset( game, Set( 4, 7 ) ) );
    ExpectPing( Subset( game, Set( 4, 7 ) ), Ping( ERequestStatus::Accepted, 2, 10 ) );
    ExpectPing( SubsetInv( game, Set( 4, 7 ) ), Ping( ERequestStatus::WaitingAccept, 2, 10 ) );

    //Nothing to happen in next 2 minutes
    AdvanceTimeAndPoll( 119.0 );

    ExpectPing( Subset( game, Set( 4, 7 ) ), ERequestStatus::InLine );
    ExpectPing( SubsetInv(  game, Set( 4, 7 ) ), ERequestStatus::AcceptTimedOut );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( game );
  }



  void test_accept_timeout_with_cancel()
  {
    Requests game = AddSomeAndWaitGame( CreateParams() );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( game[8] );
    Accept( Subset( game, Set( 4, 7 ) ) );
    ExpectPing( Subset( game, Set( 4, 7 ) ), Ping( ERequestStatus::Accepted, 2, 10 ) );
    ExpectPing( SubsetInv( game, Set( 4, 7, 8 ) ), Ping( ERequestStatus::WaitingAccept, 2, 10 ) );

    //Nothing to happen in next 2 minutes
    AdvanceTimeAndPoll( 119.0 );

    ExpectPing( Subset( game, Set( 4, 7 ) ), ERequestStatus::InLine );
    ExpectPing( SubsetInv( game, Set( 4, 7, 8 ) ), ERequestStatus::AcceptTimedOut );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( SubsetInv( game, Set( 4, 7, 8 ) ) );
  }



  void test_cancel_game_then_repeat_request_and_succeed()
  {
    Requests game = AddSomeAndWaitGame( CreateParams() );
    AdvanceTimeAndPoll( 1.0 );

    ExpectPing( SubsetInv( game, 9 ), Ping( ERequestStatus::Accepted, 9, 10 ) );
    ExpectPing( game[9], Ping( ERequestStatus::WaitingAccept, 9, 10 ) );
    Accept( SubsetInv( game, 9 ) );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( Subset( game, Set( 5, 9 ) ) );
    ExpectPing( SubsetInv( game, Set( 5, 9 ) ), ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );

    Expect( game[5], ResponseOpen() );
    Add1( game[5] ); //Return requests as is

    game[9] = Create( 209, CreateParams( 0, game[9]->Data().faction ) ); //Create new request instead of 9th
    Add1( game[9] ); //Return requests as is
    ExpectPing( Subset( game, Set( 5, 9 ) ), ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );

    ExpectPing( game, Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    AdvanceTimeAndPoll( 10.0 );

    Accept( game );
    ExpectPing( game, Ping( ERequestStatus::PreparingPvX, 0, 10 ) );
    AdvanceTimeAndPoll( 1.0 );

    PopGame( game );
  }


  void test_game_removal()
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams().EnterPvx( false ) ); //DO NOT enter PvX

    FinishGame( game, mmGameId, lobby::ETeam::None );
    CheckGameResults( game, lobby::ETeam::None );

    Cancel( game );
  }



  //////////////////////////////
  // Client Leave & Reconnect //
  //////////////////////////////
  void test_client_drop()
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams() );

    DropFromPvX( Subset( game, Set( 5, 6, 7, 8 ) ), false );
    ExpectPing( Subset( game, Set( 5, 6, 7, 8 ) ), Ping( ERequestStatus::ClientDropped, 0, game.size() ) );
    AdvanceTimeAndPoll( 10.0 );

    Cancel( game );
  }


  void test_dropped_clients_cookies()
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams() );

    DropFromPvX( Subset( game, Set( 5, 6, 7, 8 ) ), false );
    ExpectPing( Subset( game, Set( 5, 6, 7, 8 ) ), Ping( ERequestStatus::ClientDropped, 0, game.size() ) );
    AdvanceTimeAndPoll( 30.0 );

    //Reconnect timeout has not passed, users get all cookies
    FinishGame( game, mmGameId, lobby::ETeam::None );
    CheckGameResults( game, lobby::ETeam::None );

    Cancel( game );
  }


  void test_client_fast_reconnect()
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams() );

    Set set = Set( 2, 6 );
    DropFromPvX( Subset( game, set ), false );
    ExpectPing( Subset( game, set ), Ping( ERequestStatus::ClientDropped, 0, game.size() ) );
    AdvanceTimeAndPoll( 5.0 );
    EnterPvX( Subset( game, set ) );
    ExpectPing( Subset( game, set ), Ping( ERequestStatus::InGame, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( game );
  }


  void helper_dropped_client_reconnect_timeout( bool _enterPvX )
  {
    Set S( 5, 6, 7 );

    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams().EnterPvx( _enterPvX ) );

    DropFromPvX( Subset( game, S ), false );

    ExpectPing( Subset( game, S ), Ping( ERequestStatus::ClientDropped, 0, 10 ) );
    AdvanceTimeAndPoll( 1.0 );

    AdvanceTimeAndPoll( 170.0 ); //Nothing to happen

    ExpectPing( Subset( game, S ), Ping( ERequestStatus::WaitingGameFinish, 0, 10 ) );
    AdvanceTimeAndPoll( 10.0 ); //Reconnect timeout should happen

    FinishGame( game, mmGameId, lobby::ETeam::Team1 );
    CheckGameResults( game, lobby::ETeam::Team1, S );

    Cancel( game );
  }


  void test_dropped_client_reconnect_timeout()
  {
    helper_dropped_client_reconnect_timeout( true );
  }


  void test_waiting_in_lobby_dropped_reconnect_timeout()
  {
    helper_dropped_client_reconnect_timeout( false );
  }






  void CheckLeavers( const Requests & requests, lobby::TSocialGameId mmGameId )
  {
    std::set<TUserIdPvX> poppedIds;
    for ( size_t i = 0; i < requests.size(); ++i )
    {
      TS_ASSERT( !pvxMock->newUsersLeftTheGame.empty() );
      PvxSvcMock::UserGameRecord R = pvxMock->newUsersLeftTheGame.front();
      pvxMock->newUsersLeftTheGame.pop_front();

      TS_ASSERT_EQUALS( R.gameId, mmGameId );
      poppedIds.insert( R.userId );
    }

    PvxUidSet checkIds = PvxUids( requests );
    TS_ASSERT_EQUALS( poppedIds, checkIds );
  }



  void helper_leave_from_in_game( const Set & leavers )
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams() );

    DropFromPvX( Subset( game, leavers ), true );
    ExpectPing( Subset( game, leavers ), Ping( ERequestStatus::WaitingGameFinish, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    FinishGame( game, mmGameId, lobby::ETeam::Team2 );
    CheckGameResults( game, lobby::ETeam::Team2, leavers );
    Cancel( game );
  }


  void test_leave_from_in_game_full() { helper_leave_from_in_game( All ); }
  void test_leave_from_in_game_half() { helper_leave_from_in_game( Set( 0, 1, 3, 4 ) ); }


  void helper_drop_from_in_game_then_leave( const Set & leavers )
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams() );

    DropFromPvX( Subset( game, leavers ), false );
    ExpectPing( Subset( game, leavers ), Ping( ERequestStatus::ClientDropped, 0, game.size() ) );
    AdvanceTimeAndPoll( 10.0 );

    Leave( Subset( game, leavers ) );
    ExpectPing( Subset( game, leavers ), Ping( ERequestStatus::WaitingGameFinish, 0, game.size() ) );
    AdvanceTimeAndPoll( 10.0 );

    CheckLeavers( Subset( game, leavers ), mmGameId );

    FinishGame( game, mmGameId, lobby::ETeam::Team2 );
    CheckGameResults( game, lobby::ETeam::Team2, leavers );
    Cancel( game );
  }


  void test_drop_then_leave_from_in_game_full() { helper_drop_from_in_game_then_leave( All ); }
  void test_drop_then_leave_from_in_game_half() { helper_drop_from_in_game_then_leave( All / Set( 1, 2, 5, 7, 8 ) ); }


  void helper_drop_from_waiting_in_lobby_then_leave( const Set & leavers )
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams().EnterPvx( false ) );

    EnterPvX( SubsetInv( game, leavers ) );
    DropFromPvX( Subset( game, leavers ), false );
    ExpectPing( SubsetInv( game, leavers ), Ping( ERequestStatus::InGame, 0, game.size() ) );
    ExpectPing( Subset( game, leavers ), Ping( ERequestStatus::ClientDropped, 0, game.size() ) );
    AdvanceTimeAndPoll( 5.0 );

    Leave( Subset( game, leavers ) );
    ExpectPing( Subset( game, leavers ), Ping( ERequestStatus::WaitingGameFinish, 0, game.size() ) );
    AdvanceTimeAndPoll( 5.0 );

    CheckLeavers( Subset( game, leavers ), mmGameId );

    FinishGame( game, mmGameId, lobby::ETeam::Team1 );
    CheckGameResults( game, lobby::ETeam::Team1, leavers );
    Cancel( game );
  }


  void test_drop_from_waiting_in_lobby_then_leave_half() { helper_drop_from_waiting_in_lobby_then_leave( All ); }
  void test_drop_from_waiting_in_lobby_then_leave_full() { helper_drop_from_waiting_in_lobby_then_leave( All / Set( 0, 2, 4, 8 ) ); }


  typedef std::set<TUserIdPvX> PvxUidSet;

  PvxUidSet PvxUids( const Requests & requests )
  {
    PvxUidSet result;
    for ( size_t i = 0; i < requests.size(); ++i )
      result.insert( requests[i]->Data().userIdPvx );
    return result;
  }



  void CheckReconnectedUsers( const Requests & requests, lobby::TSocialGameId mmGameId )
  {
    std::set<TUserIdPvX> poppedIds;
    for ( size_t i = 0; i < requests.size(); ++i )
    {
      TS_ASSERT( !pvxMock->newReconnects.empty() );
      PvxSvcMock::UserGameRecord R = pvxMock->newReconnects.front();
      pvxMock->newReconnects.pop_front();

      TS_ASSERT_EQUALS( R.gameId, mmGameId );
      poppedIds.insert( R.userId );
    }

    PvxUidSet checkIds = PvxUids( requests );
    TS_ASSERT_EQUALS( poppedIds, checkIds );
  }



  void helper_reconnect( bool _enterPvX, lobby::ETeam::Enum _winner )
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams().EnterPvx( _enterPvX ) );

    Set S( 2, 3, 4 );

    DropFromPvX( Subset( game, S ), false );
    ExpectPing( Subset( game, S ), Ping( ERequestStatus::ClientDropped, 0, game.size() ) );
    AdvanceTimeAndPoll( 10.0 );

    Reconnect( Subset( game, S ) );
    ExpectPing( Subset( game, S ), Ping( ERequestStatus::PreparingPvX, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    CheckReconnectedUsers( Subset( game, S ), mmGameId );

    AdvanceTimeAndPoll( 1.0 );

    PvxPrepared( Subset( game, S ) );
    ExpectPing( Subset( game, S ), Ping( ERequestStatus::WaitingInPvX, game.size(), "Not Empty" ) );
    AdvanceTimeAndPoll( 1.0 );

    FinishGame( game, mmGameId, _winner );
    ExpectPing( game, Ping( ERequestStatus::GameFinished, _winner, false ), _winner );
    ExpectPing( game, Ping( ERequestStatus::GameFinished, _winner, false ), lobby::ETeam::Invert( _winner ) );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( game );
  }


  void test_reconnect_waiting_in_lobby()
  {
    helper_reconnect( false, lobby::ETeam::Team2 );
  }


  void test_reconnect_in_game()
  {
    helper_reconnect( true, lobby::ETeam::Team1 );
  }


  /////////////
  // Parties //
  /////////////
  void test_parties_trivial()
  {
    Requests party = CreateAndAddParty( CreateParams( 4, lobby::ETeam::Team1 ) );
    ExpectPing( party, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );
  }


  void test_party_opimistic()
  {
    Requests p1 = CreateAndAddParty( CreateParams( 3, lobby::ETeam::Team2 ) );
    ExpectPing( p1, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0f );

    Requests p2 = CreateParty( CreateParams( 5, lobby::ETeam::Team1 ) );
    Add( Subset( p2, Set( 0, 1, 2 ) ) );
    ExpectPing( Subset( p2, Set( 0, 1, 2 ) ), ERequestStatus::WaitingPartyMembers );
    AdvanceTimeAndPoll( 1.0f );

    Add( Subset( p2, Set( 3, 4 ) ) );
    ExpectPing( p2, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0f );

    Requests p3 = CreateAndAddParty( CreateParams( 2, lobby::ETeam::Team2 ) );
    ExpectPing( p3, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0f );

    Requests game = p1 + p2 + p3;

    ExpectPing( game, Ping( ERequestStatus::WaitingAccept, 0, game.size() ) );
    AdvanceTimeAndPoll( 10.0f );

    AcceptGame( game );
    lobby::TSocialGameId gameId = PopGame( game ).gameId;
    EnterPvX( game );

    FinishGame( game, gameId, lobby::ETeam::Team1 );
    CheckGameResults( game, lobby::ETeam::Team1, Set() );
    Cancel( game );
  }


  void test_incomplete_party()
  {
    Requests party = CreateAndAddParty( CreateParams( 4, lobby::ETeam::Team2 ), Set( 1, 2, 3 ) );
    ExpectPing( Subset( party, Set( 1, 2, 3 ) ), ERequestStatus::WaitingPartyMembers );
    AdvanceTimeAndPoll( 1.0f );

    AdvanceTimeAndPoll( 25.0f );

    ExpectPing( Subset( party, Set( 1, 2, 3 ) ), ERequestStatus::IncompleteParty );
    AdvanceTimeAndPoll( 5.0f ); //Timeout has passed
    AdvanceTimeAndPoll( 1.0f ); //Needed to fix Social Lobby internal poll order

    party[0]->FlushExpectations();
    Cancel( Subset( party, Set( 1, 2, 3 ) ) );
  }


  void test_party_fall_apart_in_line()
  {
    Requests party = CreateAndAddParty( CreateParams( 4, lobby::ETeam::Team1 ) );
    ExpectPing( party, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( Subset( party, 2 ) );
    ExpectPing( Subset( party, Set( 0, 1, 3 ) ), ERequestStatus::PartyCameApart );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( Subset( party, Set( 0, 1, 3 ) ) );
  }


  void utility_party_fall_apart_ater_mm_begin( Requests & party1, Requests & party2 )
  {
    party1 = CreateAndAddParty( CreateParams( 5, lobby::ETeam::Team1 ) );
    party2 = CreateAndAddParty( CreateParams( 5, lobby::ETeam::Team2 ) );
    ExpectPing( party1, ERequestStatus::InLine );
    ExpectPing( party2, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0f );

    ExpectPing( party1, Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    ExpectPing( party2, Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    AdvanceTimeAndPoll( 10.0f );

    for ( int i = 0; i < 5; ++i ) {
      party1[i]->SetAuxParam( ERequestStatus::WaitingAccept );
      party2[i]->SetAuxParam( ERequestStatus::WaitingAccept );
    }
  }


  void utility_party_fall_apart_ater_mm_finish( Requests & party1, Requests & party2 )
  {
    ExpectPing( party1, ERequestStatus::InLine );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), ERequestStatus::PartyCameApart );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( party1 );
    Cancel( Subset( party2, Set( 0, 1 ) ) );
  }


  void test_party_fall_apart_ater_mm_v1()
  {
    Requests party1, party2;
    utility_party_fall_apart_ater_mm_begin( party1, party2 );

    Cancel( Subset( party2, Set( 2, 3, 4 ) ) );
    ExpectPing( party1, Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( Subset( party2, Set( 0, 1 ) ) );
    ExpectPing( party1, Ping( ERequestStatus::WaitingAccept, 2, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::Accepted, 2, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( Subset( party1, Set( 0, 1, 2, 3 ) ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::Accepted, 6, 10 ) );
    ExpectPing( Subset( party1, Set( 0, 1, 2, 3 ) ), Ping( ERequestStatus::Accepted, 6, 10 ) );
    ExpectPing( party1[4], Ping( ERequestStatus::WaitingAccept, 6, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( party1[4] );
    utility_party_fall_apart_ater_mm_finish( party1, party2 );
  }


  void test_party_fall_apart_ater_mm_v11() 
  {
    Requests party1, party2;
    utility_party_fall_apart_ater_mm_begin( party1, party2 );

    Cancel( Subset( party2, Set( 2, 3, 4 ) ) );
    ExpectPing( party1, Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( party1 );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::WaitingAccept, 5, 10 ) );
    ExpectPing( party1, Ping( ERequestStatus::Accepted, 5, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( party2[0] );
    ExpectPing( party1, Ping( ERequestStatus::Accepted, 6, 10 ) );
    ExpectPing( party2[0], Ping( ERequestStatus::Accepted, 6, 10 ) );
    ExpectPing( party2[1], Ping( ERequestStatus::WaitingAccept, 6, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( party2[1] );
    utility_party_fall_apart_ater_mm_finish( party1, party2 );
  }


  void test_party_fall_apart_ater_mm_v2()
  {
    Requests party1, party2;
    utility_party_fall_apart_ater_mm_begin( party1, party2 );

    Accept( Subset( party2, Set( 0, 1 ) ) );
    ExpectPing( party1, Ping( ERequestStatus::WaitingAccept, 2, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::Accepted, 2, 10 ) );
    ExpectPing( Subset( party2, Set( 2, 3, 4 ) ), Ping( ERequestStatus::WaitingAccept, 2, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( Subset( party2, Set( 2, 3, 4 ) ) );
    ExpectPing( party1, Ping( ERequestStatus::WaitingAccept, 2, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::Accepted, 2, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( Subset( party1, Set( 0, 1, 2, 3 ) ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::Accepted, 6, 10 ) );
    ExpectPing( Subset( party1, Set( 0, 1, 2, 3 ) ), Ping( ERequestStatus::Accepted, 6, 10 ) );
    ExpectPing( party1[4], Ping( ERequestStatus::WaitingAccept, 6, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( party1[4] );
    utility_party_fall_apart_ater_mm_finish( party1, party2 );
  }


  void test_party_fall_apart_ater_mm_v22()
  {
    Requests party1, party2;
    utility_party_fall_apart_ater_mm_begin( party1, party2 );

    Accept( party1 );
    ExpectPing( party1, Ping( ERequestStatus::Accepted, 5, 10 ) );
    ExpectPing( party2, Ping( ERequestStatus::WaitingAccept, 5, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( Subset( party2, Set( 2, 3, 4 ) ) );
    ExpectPing( party1, Ping( ERequestStatus::Accepted, 5, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::WaitingAccept, 5, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( party2[0] );
    ExpectPing( party1, Ping( ERequestStatus::Accepted, 6, 10 ) );
    ExpectPing( party2[0], Ping( ERequestStatus::Accepted, 6, 10 ) );
    ExpectPing( party2[1], Ping( ERequestStatus::WaitingAccept, 6, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( party2[1] );
    utility_party_fall_apart_ater_mm_finish( party1, party2 );
  }


  void test_party_fall_apart_ater_mm_v3()
  {
    Requests party1, party2;
    utility_party_fall_apart_ater_mm_begin( party1, party2 );

    Accept( Subset( party2, Set( 0, 1 ) ) );
    ExpectPing( party1, Ping( ERequestStatus::WaitingAccept, 2, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::Accepted, 2, 10 ) );
    ExpectPing( Subset( party2, Set( 2, 3, 4 ) ), Ping( ERequestStatus::WaitingAccept, 2, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( party1 );
    ExpectPing( party1, Ping( ERequestStatus::Accepted, 7, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::Accepted, 7, 10 ) );
    ExpectPing( Subset( party2, Set( 2, 3, 4 ) ), Ping( ERequestStatus::WaitingAccept, 7, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( Subset( party2, Set( 2, 3 ) ) );
    ExpectPing( party1, Ping( ERequestStatus::Accepted, 7, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::Accepted, 7, 10 ) );
    ExpectPing( party2[4], Ping( ERequestStatus::WaitingAccept, 7, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( party2[4] );
    utility_party_fall_apart_ater_mm_finish( party1, party2 );
  }


  void test_party_fall_apart_ater_mm_v33()
  {
    Requests party1, party2;
    utility_party_fall_apart_ater_mm_begin( party1, party2 );

    Accept( party1 );
    ExpectPing( party1, Ping( ERequestStatus::Accepted, 5, 10 ) );
    ExpectPing( party2, Ping( ERequestStatus::WaitingAccept, 5, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Accept( Subset( party2, Set( 0, 1 ) ) );
    ExpectPing( party1, Ping( ERequestStatus::Accepted, 7, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::Accepted, 7, 10 ) );
    ExpectPing( Subset( party2, Set( 2, 3, 4 ) ), Ping( ERequestStatus::WaitingAccept, 7, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( Subset( party2, Set( 2, 3 ) ) );
    ExpectPing( party1, Ping( ERequestStatus::Accepted, 7, 10 ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::Accepted, 7, 10 ) );
    ExpectPing( party2[4], Ping( ERequestStatus::WaitingAccept, 7, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( party2[4] );
    utility_party_fall_apart_ater_mm_finish( party1, party2 );
  }



  void test_party_cancel_special()
  {
    Requests party = CreateAndAddParty( CreateParams( 4, lobby::ETeam::Team1 ) );
    ExpectPing( party, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0f );

    Expect( party, ResponseClose() );
    party[2]->Context()->CancelPartyRequest();
  }



  void test_party_cancel_special_from_accept()
  {
    Requests party1 = CreateAndAddParty( CreateParams( 5, lobby::ETeam::Team1 ) );
    Requests party2 = CreateAndAddParty( CreateParams( 5, lobby::ETeam::Team2 ) );

    ExpectPing( party1 + party2, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0f );

    ExpectPing( party1 + party2, Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    AdvanceTimeAndPoll( 10.0f );

    Expect( party2, ResponseClose() );
    party2[4]->Context()->CancelPartyRequest();

    ExpectPing( party1, Ping( ERequestStatus::WaitingAccept, 0, 10 ) );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( party1 );
    AdvanceTimeAndPoll( 1.0f );
  }



  ///////////////////
  // Officer lobby //
  ///////////////////
  void test_officer_lobby_smoke()
  {
    Requests game;
    game += CreateAndAddSome( CreateParams().HeroRating( slConfig->officerLobbyRating + 1 ).Count( 4 ) );
    game += CreateAndAddSome( CreateParams().HeroRating( slConfig->officerLobbyRating - 1 ).Count( 6 ) );
    WaitGame( game, CreateParams() );
    AdvanceTimeAndPoll( 1.0 );
    
    Accept( game );
    ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
    SetupGuardLobbyExpectations( game );
    AdvanceTimeAndPoll( 1.0 );

    GuardReady( game );
    //ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
    //SetupGuardLobbyExpectations( game );
    ExpectPing( game, Ping( ERequestStatus::PreparingPvX, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    PopGame( game );
    Cancel( game );
  }



  void help_test_officer_lobby_timeout( const Set & readyGuards )
  {
    Requests game = AddSomeAndWaitGame( CreateParams().HeroRating( slConfig->officerLobbyRating + 1 ) );
    AdvanceTimeAndPoll( 1.0 );
    Accept( game );
    ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
    SetupGuardLobbyExpectations( game );
    AdvanceTimeAndPoll( 1.0 );

    if ( !readyGuards.empty() ) {
      GuardReady( Subset( game, readyGuards ) );
      ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
      SetupGuardLobbyExpectations( game );
      AdvanceTimeAndPoll( 1.0 );
    }

    EnsureNoGame();
    AdvanceTimeAndPoll( 55.0 );

    ExpectPing( Subset( game, readyGuards ), Ping( ERequestStatus::InLine ) );
    ExpectPing( SubsetInv( game, readyGuards ), Ping( ERequestStatus::AcceptTimedOut ) );
    AdvanceTimeAndPoll( 6.0 ); //Guard lobby timeout
    AdvanceTimeAndPoll( 1.0 );

    Cancel( game );
  }



  void test_officer_lobby_timeout1() {
    help_test_officer_lobby_timeout( Set() );
  }

  void test_officer_lobby_timeout2() {
    help_test_officer_lobby_timeout( Set( 0, 1, 5, 8 ) );
  }



  void test_pre_game_lobby_party_timeout()
  {
    Requests party1 = CreateAndAddParty( CreateParams( 5, lobby::ETeam::Team1 ).HeroRating( slConfig->officerLobbyRating + 1 ) );
    ExpectPing( party1, ERequestStatus::InLine );

    Requests party2 = CreateAndAddParty( CreateParams( 5, lobby::ETeam::Team2 ).HeroRating( slConfig->officerLobbyRating + 1 ) );
    ExpectPing( party2, ERequestStatus::InLine );

    AdvanceTimeAndPoll( 1.0 );

    Requests game = party1 + party2;
    ExpectPing( game, Ping( ERequestStatus::WaitingAccept, 0, game.size() ) );
    AdvanceTimeAndPoll( 20.0f );
    
    Accept( game );
    ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
    SetupGuardLobbyExpectations( game );
    AdvanceTimeAndPoll( 1.0 );

    GuardReady( Subset( game, Set( 0, 1, 2, 3, 4, 5, 6 ) ) );
    ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
    SetupGuardLobbyExpectations( game );
    AdvanceTimeAndPoll( 1.0 );

    AdvanceTimeAndPoll( 60.0 );

    ExpectPing( party1, Ping( ERequestStatus::InLine ) );
    ExpectPing( Subset( party2, Set( 0, 1 ) ), Ping( ERequestStatus::PartyCameApart ) );
    ExpectPing( Subset( party2, Set( 2, 3, 4 ) ), Ping( ERequestStatus::AcceptTimedOut ) );
    AdvanceTimeAndPoll( 1.0 );
  }



  void test_officer_lobby_come_apart()
  {
    Requests game = AddSomeAndWaitGame( CreateParams().HeroRating( slConfig->officerLobbyRating + 1 ) );
    AdvanceTimeAndPoll( 1.0 );
    
    Accept( game );
    ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
    SetupGuardLobbyExpectations( game );
    AdvanceTimeAndPoll( 1.0 );

    GuardReady( game[1] );
    ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
    SetupGuardLobbyExpectations( game );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( game[5] );
    ExpectPing( SubsetInv( game, 5 ), Ping( ERequestStatus::InLine ) );
    AdvanceTimeAndPoll( 1.0 );
  }



  void test_officer_lobby_party_come_apart()
  {
    Requests party1 = CreateAndAddParty( CreateParams( 2, lobby::ETeam::Team1 ).HeroRating( slConfig->officerLobbyRating + 1 ) );
    ExpectPing( party1, ERequestStatus::InLine );

    Requests party2 = CreateAndAddParty( CreateParams( 3, lobby::ETeam::Team1 ).HeroRating( slConfig->officerLobbyRating + 1 ) );
    ExpectPing( party2, ERequestStatus::InLine );

    Requests singles;
    for ( int i = 0; i < 5; ++i )
      singles.push_back( Create( CreateParams( 0, lobby::ETeam::Team2 ).HeroRating( slConfig->officerLobbyRating + 1 ) ) );
    Add( singles );
    ExpectPing( singles, ERequestStatus::InLine );

    AdvanceTimeAndPoll( 1.0 );

    Requests game = party1 + party2 + singles;
    ExpectPing( game, Ping( ERequestStatus::WaitingAccept, 0, game.size() ) );
    AdvanceTimeAndPoll( 20.0f );
    
    Accept( game );
    ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
    SetupGuardLobbyExpectations( game );
    AdvanceTimeAndPoll( 1.0 );

    GuardReady( Subset( game, Set( 1, 8 ) ) );
    ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
    SetupGuardLobbyExpectations( game );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( party2[1] );
    ExpectPing( party1, Ping( ERequestStatus::InLine ) );
    ExpectPing( Subset( party2, Set( 0, 2 ) ), Ping( ERequestStatus::PartyCameApart ) );
    ExpectPing( singles, Ping( ERequestStatus::InLine ) );
    AdvanceTimeAndPoll( 1.0 );
  }



  void test_officer_lobby_low_rating_in_party()
  {
    Requests game;

    for ( int i = 0; i < 4; ++i )
      game << Create( nextUId++, CreateParams().HeroRating( slConfig->officerLobbyRating + 1 ) );
    game << Create( nextUId++, CreateParams().HeroRating( slConfig->officerLobbyRating - 1 ) );

    SetupNewParty( CreateParams(), game, Requests() );

    Add( game );

    game += CreateAndAddParty( CreateParams().HeroRating( slConfig->officerLobbyRating + 1 ).Count( 5 ).Team( lobby::ETeam::Team2 ) );

    ExpectPing( game, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0f );
    ExpectPing( game, Ping( ERequestStatus::WaitingAccept, 0, game.size() ) );
    AdvanceTimeAndPoll( 20.0f );

    Accept( game );
    ExpectPing( game, Ping( ERequestStatus::PreGameLobby, 0, game.size() ) );
    SetupGuardLobbyExpectations( game );
    AdvanceTimeAndPoll( 1.0 );

    GuardReady( game );
    ExpectPing( game, Ping( ERequestStatus::PreparingPvX, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    PopGame( game );
    Cancel( game );
  }



  ////////////////
  // Spectators //
  ////////////////
  void CheckSpectator( const ReqPtr req, lobby::TSocialGameId mmGameId )
  {
    TS_ASSERT( !pvxMock->newSpectators.empty() );

    PvxSvcMock::NewSpect S = pvxMock->newSpectators.front();
    pvxMock->newSpectators.pop_front();

    TS_ASSERT_EQUALS( S.gameId, mmGameId );
    TS_ASSERT_EQUALS( S.userId, req->Data().userIdPvx );
    TS_ASSERT_EQUALS( S.login, req->Data().login );
  }



  Requests helper_add_spect( TUId targetUid, lobby::TSocialGameId mmGameId, size_t gameSize )
  {
    Requests spectator = CreateSome( CreateParams().Count( 1 ) );

    ExpectPing( spectator, Ping( ERequestStatus::PreparingPvX, 0, gameSize ) );
    Spectate( spectator, targetUid );
    AdvanceTimeAndPoll( 1.0 );

    CheckSpectator( spectator[0], mmGameId );

    ExpectPing( spectator, Ping( ERequestStatus::WaitingInPvX, gameSize, "Not empty" ) );
    PvxPrepared( spectator );
    AdvanceTimeAndPoll( 1.0 );

    ExpectPing( spectator, Ping( ERequestStatus::InGame, 0, gameSize ) );
    EnterPvX( spectator );
    AdvanceTimeAndPoll( 1.0 );

    return spectator;
  }



  void test_spectator_smoke()
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams() );

    Requests spectator = helper_add_spect( game[0]->Data().uid, mmGameId, game.size() );

    FinishGame( game, mmGameId, lobby::ETeam::Team1 );

    ExpectPing( spectator, Ping( ERequestStatus::GameFinished, lobby::ETeam::Team1, false ) );
    CheckGameResults( game, lobby::ETeam::Team1 );

    DropFromPvX( game, false );
    DropFromPvX( spectator, false );

    AdvanceTimeAndPoll( 1.0 );
    Cancel( game );
    Cancel( spectator );
  }




  void test_spectator_too_many()
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams() );

    Requests spectators1 = CreateSome( CreateParams().Count( 2 ) );
    Spectate( spectators1, game[0]->Data().uid );
    
    ExpectPing( spectators1, Ping( ERequestStatus::PreparingPvX, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    //Third spectator
    ReqPtr specFail2 = new Request( 334, CreateParams() );
    specFail2->Expect( ResponseFailure() );
    Spectate1( specFail2, game[3]->Data().uid );

    PvxPrepared( spectators1 );
    ExpectPing( spectators1, Ping( ERequestStatus::WaitingInPvX, game.size(), "Not empty" ) );
    AdvanceTimeAndPoll( 1.0 );

    EnterPvX( spectators1 );
    ExpectPing( spectators1, Ping( ERequestStatus::InGame, 0, game.size() ) );
    AdvanceTimeAndPoll( 5.0 );

    //Forth spectator
    ReqPtr specFail3 = new Request( 335, CreateParams() );
    specFail3->Expect( ResponseFailure() );
    Spectate1( specFail3, game[3]->Data().uid );
    AdvanceTimeAndPoll( 1.0 );

    FinishGame( game, mmGameId, lobby::ETeam::Team1 );

    ExpectPing( spectators1, Ping( ERequestStatus::GameFinished, lobby::ETeam::Team1, false ) );
    CheckGameResults( game, lobby::ETeam::Team1 );

    DropFromPvX( game, false );
    DropFromPvX( spectators1, false );

    AdvanceTimeAndPoll( 1.0 );
    Cancel( game );
    Cancel( spectators1 );
  }



  void test_two_spectators()
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams().EnterPvx( true ) );

    AdvanceTimeAndPoll( 10.0 );

    Requests spectator1 = helper_add_spect( game[4]->Data().uid, mmGameId, game.size() );

    DropFromPvX( spectator1, false );
    ExpectPing( spectator1, Ping( ERequestStatus::ClientDropped, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( spectator1 );
    AdvanceTimeAndPoll( 1.0 );

    Requests spectator2 = helper_add_spect( game[6]->Data().uid, mmGameId, game.size() );

    DropFromPvX( spectator2, true );
    ExpectPing( spectator2, Ping( ERequestStatus::WaitingGameFinish, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( spectator2 );
    AdvanceTimeAndPoll( 1.0 );

    FinishGame( game, mmGameId, lobby::ETeam::Team1 );
    ExpectPing( game, Ping( ERequestStatus::GameFinished, lobby::ETeam::Team1, false ), lobby::ETeam::Team1 );
    ExpectPing( game, Ping( ERequestStatus::GameFinished, lobby::ETeam::Team1, false ), lobby::ETeam::Team2 );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( game );
  }



  void test_spectator_and_reconnect()
  {
    lobby::TSocialGameId mmGameId = 0;
    Requests game = CreateGame( mmGameId, CreateParams().EnterPvx( true ) );

    AdvanceTimeAndPoll( 10.0 );

    Requests spectator = CreateSome( CreateParams().Count( 1 ) );
    Spectate( spectator, game[3]->Data().uid );
    CheckSpectator( spectator[0], mmGameId );
    PvxPrepared( spectator );
    EnterPvX( spectator );
    ExpectPing( spectator, Ping( ERequestStatus::InGame, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );

    Set S( 2, 3, 4 );

    DropFromPvX( Subset( game, S ), false );
    ExpectPing( Subset( game, S ), Ping( ERequestStatus::ClientDropped, 0, game.size() ) );
    AdvanceTimeAndPoll( 10.0 );

    Reconnect( Subset( game, S ) );
    ExpectPing( Subset( game, S ), Ping( ERequestStatus::PreparingPvX, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );
    CheckReconnectedUsers( Subset( game, S ), mmGameId );

    PvxPrepared( Subset( game, S ) );
    ExpectPing( Subset( game, S ), Ping( ERequestStatus::WaitingInPvX, game.size(), "Not Empty" ) );
    AdvanceTimeAndPoll( 1.0 );

    ExpectPing( spectator, Ping( ERequestStatus::GameFinished, lobby::ETeam::Team1, false ), lobby::ETeam::None );

    FinishGame( game, mmGameId, lobby::ETeam::Team1 );
    ExpectPing( game, Ping( ERequestStatus::GameFinished, lobby::ETeam::Team1, false ), lobby::ETeam::Team1 );
    ExpectPing( game, Ping( ERequestStatus::GameFinished, lobby::ETeam::Team1, false ), lobby::ETeam::Team2 );
    AdvanceTimeAndPoll( 1.0 );

    Cancel( game );
    Cancel( spectator );
  }


  //////////////////
  // Custom games //
  //////////////////
  void help_test_custom( lobby::ETeam::Enum srcFaction1, lobby::ETeam::Enum srcFaction2, lobby::ETeam::Enum resultingFaction1, lobby::ETeam::Enum resultingFaction2 )
  {
    Requests team1 = CreateSome( CreateParams( 5, srcFaction1 ).TossTeams( false ) );
    Requests team2 = CreateSome( CreateParams( 5, srcFaction2 ).TossTeams( false ) );
    SetupNewParty( CreateParams(), team1, team2 );
    Requests game = team1 + team2;
    Add( game );
    ExpectPing( game, Ping( ERequestStatus::WaitingAccept, 0, game.size() ) );
    AdvanceTimeAndPoll( 1.0 );
    AcceptGame( game );
    AdvanceTimeAndPoll( 1.0 );

    bool checkTeams = ( srcFaction1 == resultingFaction1 ) && ( srcFaction2 == resultingFaction2 );
    PvxSvcMock::NewGameLog gameData = PopGame( game, mmaking::EBasket::Normal, checkTeams );

    TS_ASSERT( gameData.game.humans.size() == 2 );
    if ( srcFaction1 == srcFaction2 )
      TS_ASSERT( gameData.game.manoeuvresFaction == srcFaction1 );
    TS_ASSERT( gameData.game.humans[0].members.size() == 5 );
    TS_ASSERT( gameData.game.humans[1].members.size() == 5 );
    TS_ASSERT( gameData.game.humans[0].common.team == resultingFaction1 );
    TS_ASSERT( gameData.game.humans[1].common.team == resultingFaction2 );

    EnterPvX( game );
    ExpectPing( game, Ping( ERequestStatus::InGame, 0, game.size() ) );
    AdvanceTimeAndPoll( 300.0 );
    AdvanceTimeAndPoll( 1.0 );

    FinishGame( game, gameData.gameId, lobby::ETeam::Team1 );
    CheckGameResults( game, lobby::ETeam::Team1, Set() );

    Cancel( game );
  }


  void test_custom_game_smoke() {
    help_test_custom( lobby::ETeam::Team1, lobby::ETeam::Team2, lobby::ETeam::Team1, lobby::ETeam::Team2 );
  }

  void test_custom_game_reverse_factions() {
    help_test_custom( lobby::ETeam::Team2, lobby::ETeam::Team1, lobby::ETeam::Team2, lobby::ETeam::Team1 );
  }

  void test_custom_game_manoeuvres1() {
    help_test_custom( lobby::ETeam::Team1, lobby::ETeam::Team1, lobby::ETeam::Team1, lobby::ETeam::Team2 );
  }

  void test_custom_game_manoeuvres2() {
    help_test_custom( lobby::ETeam::Team2, lobby::ETeam::Team2, lobby::ETeam::Team2, lobby::ETeam::Team1 );
  }


  ///////////////
  // Special K //
  ///////////////
  void test_crash_case_34697() //NUM_TASK
  {
    Requests party = CreateAndAddParty( CreateParams( 5, lobby::ETeam::Team1 ) );
    ExpectPing( party, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 10.0f );

    Cancel( Subset( party, Set( 1, 2, 3, 4 ) ) );
    ExpectPing( party[0], ERequestStatus::PartyCameApart );
    AdvanceTimeAndPoll( 1.0f );

    //Simulate two wrong additions; To test this one need to comment out a pair of asserts
    Expect( Subset( party,  Set( 1, 4 ) ), ResponseFailure() );
    Add( Subset( party, Set( 1, 4 ) ) );
    AdvanceTimeAndPoll( 1.0f );

    Cancel( party[0] );
  }



  void test_accept_then_immidiate_cancel_34858() //NUM_TASK
  {
    Requests game = AddSomeAndWaitGame( CreateParams() );
    Accept( game );
    Cancel( game[5] );

    TS_ASSERT( !pvxMock->newGames.empty() );
    PvxSvcMock::NewGameLog newGame = pvxMock->newGames.front();
    pvxMock->newGames.pop_front();

    TS_ASSERT( Equals( game, newGame.game, true ) );
    TS_ASSERT( newGame.game.mapType != NDb::MAPTYPE_NONE );

    Cancel( SubsetInv( game, 5 ) );
  }



  ////////////////////////
  // Matchmaking logics //
  ////////////////////////
  void test_mm_refuse()
  {
    ReqPtr r = CreateAndAdd( 100, CreateParams( 0, lobby::ETeam::Team1 ) );
    ExpectPing( r, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );
    r->Expect( ResponseClose() );
    GetAsLiveMMakingClient()->MmResultAddRequest( 1, false );
  }


  void test_mm_drop()
  {
    ReqPtr r = CreateAndAdd( 100, CreateParams( 0, lobby::ETeam::Team1 ) );
    ExpectPing( r, ERequestStatus::InLine );
    AdvanceTimeAndPoll( 1.0 );

    TS_ASSERT( mmLogics.front()->mapId == CreateParams().mapId );
    mmLogics.front()->mockConnStatus = rpc::Disconnected;

    r->Expect( ResponseClose() );

    AdvanceTimeAndPoll( 1.0 );
    AdvanceTimeAndPoll( 1.0 );//double poll
  }


  void test_mm_drop_and_replace() //Single dropped MM will be replaced by spare logic
  {
    {
      ReqPtr r = CreateAndAdd( 100, CreateParams( 0, lobby::ETeam::Team1 ) );
      ExpectPing( r, ERequestStatus::InLine );
      AdvanceTimeAndPoll( 1.0 );
      Cancel( r );
    }

    //Drop first logics
    TS_ASSERT( mmLogics.front()->mapId == CreateParams().mapId );
    mmLogics.front()->mockConnStatus = rpc::Disconnected;
    AdvanceTimeAndPoll( 1.0 );

    //But it should still be working
    {
      ReqPtr r = CreateAndAdd( 100, CreateParams( 0, lobby::ETeam::Team1 ) );
      ExpectPing( r, ERequestStatus::InLine );
      AdvanceTimeAndPoll( 1.0 );
      Cancel( r );
    }
  }


  void test_mm_all_logics_drop()
  {
    {
      ReqPtr r = CreateAndAdd( 100, CreateParams( 0, lobby::ETeam::Team1 ) );
      ExpectPing( r, ERequestStatus::InLine );
      AdvanceTimeAndPoll( 1.0 );
      Cancel( r );
    }

    for ( std::list<StrongMT<MockLiveMM>>::iterator it = mmLogics.begin(); it != mmLogics.end(); ++it )
      (*it)->mockConnStatus = rpc::Disconnected;
    AdvanceTimeAndPoll( 1.0 );

    {
      ReqPtr r = Create( 100, CreateParams( 0, lobby::ETeam::Team1 ).ExpectOpen( false ) );
      r->Expect( ResponseFailure() );
      r->Expect( ResponseClose() );
      Add( r );
    }
  }
}; //struct Test_SocialLobby
