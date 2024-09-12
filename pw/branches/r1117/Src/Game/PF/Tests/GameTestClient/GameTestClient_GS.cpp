#include "stdafx.h"
#include "GameTestClient_GS.h"
#include <HybridServer/LPeered.auto.h>
#include "Network/LoginClientVersion.h"
#include "LagsStats.h"


const int GAME_STEP_LENGTH = 100;

static void FormatCommand( void * command, unsigned size, int clientId, NRandom::RandomGenerator & rnd )
{
  memset( command, 0, sizeof(int) );  // Set first part to zero (message typeID, used only by a real client)
  memcpy( (byte *)command + sizeof(int), &clientId, sizeof(clientId) );

  unsigned dataleft = size - 2 * sizeof( int );
  unsigned * target = (unsigned*)command + 2;
  for ( unsigned i = 0; i < ( dataleft / 4 ); ++i )
    target[i] = rnd.Next();

  for ( unsigned i = 4 * ( dataleft / 4 ); i < dataleft; ++i )
    ((byte *)command)[i] = rnd.Next( 256 );
}


namespace gtc
{

//Class needed only to resolve cyclic references: GameClient - GateKeeper - R-GameServer
class GameClientWrapper : public Peered::IGameClient, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( GameClientWrapper, Peered::IGameClient, BaseObjectMT );
public:
  GameClientWrapper( Client_GS * cl ) : owner( cl ) {}

private:
  //  Peered::IGameClient
  virtual void Start(const Peered::ClientStartInfo& clientStartInfo, Peered::RIGameServerReconnect * gameServerReconnect) {
    if ( StrongMT<Client_GS> locked = owner.Lock() )
      locked->Start( clientStartInfo );
  }

  virtual void Step(
    int step, 
    int lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<Peered::BriefClientInfo>& statuses,
    const nstl::vector<Peered::GapInfo>& clientGaps,
    const Transport::MessageMiscInfo& __miscInfo__) {
    if ( StrongMT<Client_GS> locked = owner.Lock() )
      locked->Step( step, commands, statuses, clientGaps, __miscInfo__ );
  }
  virtual void StepLoading(
    int step, 
    int lastConfirmedStep,
    const nstl::vector<rpc::MemoryBlock>& commands, 
    const nstl::vector<Peered::BriefClientInfo>& statuses,
    const nstl::vector<Peered::GapInfo>& clientGaps) {
    // Just forward this call to a regular Step. Currently we have separate StepLoading for rpc calls statistics only.
    Step( step, lastConfirmedStep, commands, statuses, clientGaps, Transport::MessageMiscInfo() );
  }

  virtual void StepBatch(
    int lastConfirmedStep,
    const nstl::vector<Peered::ClientStepData>& stepData)
  {
    if ( StrongMT<Client_GS> locked = owner.Lock() )
      locked->StepBatch( stepData );
  }
  virtual void ApplySnapshot(int step, uint worldCrc, const nstl::vector<Peered::BriefEntityInfo>& entitiesIds, const nstl::vector<rpc::MemoryBlock>& entitiesData) {
    if ( StrongMT<Client_GS> locked = owner.Lock() )
      locked->ApplySnapshot( step, worldCrc, entitiesIds, entitiesData );
  }
  virtual void OnAsync(int step, const nstl::vector<Peered::AsyncInfo>& async) {
    if ( StrongMT<Client_GS> locked = owner.Lock() )
      locked->OnAsync( step, async );
  }
  virtual void OnStart(int step) {
    if ( StrongMT<Client_GS> locked = owner.Lock() )
      locked->OnStart( step );
  }
  virtual void SetTimeScale(float scale) {}
  virtual void OnChangeClientStatus(const nstl::vector<Peered::BriefClientInfo>& clientStatuses) {
    if ( StrongMT<Client_GS> locked = owner.Lock() )
      locked->OnChangeClientStatus( clientStatuses );
  }
  virtual void OnDisconnect( int reason ) {} // EDisconnectReason::Enum
  virtual void ApplyWorldDataInfo(const Peered::WorldDataInfo& worldDataInfo) {};
  virtual void ApplyWorldDataPart(const rpc::MemoryBlock& worldDataPart) {};

  virtual void OnTimeScaleChanged(float scale) {}
  virtual void OnRejoin(uint clientId) {}
  virtual void RequestWorldData(Peered::RIGameServerReconnect * gameServerReconnect) {}
  virtual void RequestCrcData(int step) {}
  virtual void Award( const vector<roll::SAwardInfo> & _awards ) {}
  virtual void OnSpectate(const Peered::SpectatorInfo&) {}
  virtual void OnPlaySameTeamDecision(const Transport::TClientId, const bool) {}
  virtual void OnBadBehaviourComplaint(const Transport::TClientId, const Transport::TClientId, int) {}
  virtual void OnProtectionAsync(int) {}

  WeakMT<Client_GS> owner;
};






Client_GS::Client_GS( const TestClientBaseParams & _params ) :
TestClientBase( _params ),
gameDurationSteps( 0 ),
pvxTerminationTime( 0 ),
sessionClientIdx_(-1),
initialStep_(NCore::INVALID_STEP),
currentStep_(NCore::INVALID_STEP),
sendStep_(NCore::INVALID_STEP),
serverId_(-1),
confirmFrequency(0),
startLoadMapTime_(0.0),
packetSizeRandom( GetTickCount() ),
dataRandom( GetTickCount() ),
stats(NHPTimer::Milliseconds2Time(GAME_STEP_LENGTH*2), true),
queueTimeStats(NHPTimer::Milliseconds2Time(GAME_STEP_LENGTH-5), true),
chatSendStep(NCore::INVALID_STEP)
{
  gameClientWrapper = new GameClientWrapper( this );
}



Client_GS::~Client_GS()
{
  gamesrv_ = 0;
  gameClientWrapper = 0;
}



void Client_GS::SetupGameFinish( int _durationInSeconds )
{
  gameDurationSteps = _durationInSeconds * 10;

  gameFinishData.sideWon = lobby::ETeam::Team1;

  MessageTrace( "Client '%s' will finish game in %d steps, team %d wins, key=%s", params.user.c_str(), gameDurationSteps, (int)gameFinishData.sideWon, params.sessionKey.c_str() );
}



void Client_GS::SetupGameFinishClientStats( const Peered::ClientStartInfo & clientStartInfo )
{
  gameFinishData.players.resize( clientStartInfo.clientsInfos.size() );

  for ( int i = 0; i < clientStartInfo.clientsInfos.size(); ++i )
  {
    Transport::TClientId userid = clientStartInfo.clientsInfos[i].clientId;
    gameFinishData.players[i].userid = userid;
    gameFinishData.players[i].scoring.score = 200;
    gameFinishData.players[i].scoring.finalLevel = 1 + userid % 19;
  }
}



StepResult Client_GS::MainStep()
{
  NI_PROFILE_FUNCTION;

  StepResult result = TestClientBase::MainStep();
  if ( !result.Ok() || result.Handled() )
    return result;

  if ( pvxTerminationTime && ( timer::Now() > pvxTerminationTime ) ) {
    ErrorTrace( "PvX client terminated by social client! userId=%d, stage=%d, currentStep=%d", userId_, stage_, currentStep_ );
    return StepResult( false, false );
  }

  switch ( stage_ )
  {
    default:
      return StepResult( false, true );

    case Stage::PLAYER_READY_TO_PLAY:
      return StepResult( true, Result::FAIL != checkSessionStarted() );

    case Stage::GAME_STARTING:
      return StepResult( true, Result::FAIL != startJoinGameSession() );

    case Stage::JOIN_GAME_SESSION_STARTED:
      return StepResult( true, Result::FAIL != checkJoinGameSession() );

    case Stage::JOIN_GAME_SESSION_FINISHED:
    case Stage::LOAD_MAP_STARTED:
      {
        PollMulticast();
        //  так поступаем для того, чтобы если loadMapTimeout_ == 0,
        //  сразу начать следующий степ без sleep'а
        if (0 == params.mapLoadTimeout)
        {
          systemLog(NLogg::LEVEL_MESSAGE) << "Map loading stage skipped(user=" << userId_ << ")" << endl;
          stage_ = Stage::LOAD_MAP_FINISHED;
          //intentional fall through 'case' here
        }
        else
        {
          return StepResult( true, Result::FAIL != LoadMapSimulate() );
        }
      }

    case Stage::LOAD_MAP_FINISHED:
    {
      PollMulticast();
      return StepResult( true, Result::FAIL != ClientReadyToPlay() );
    }

    case Stage::CLIENT_READY_TO_PLAY:
    {
      PollMulticast();
      return StepResult( true, Result::FAIL != checkGameSessionStarted() );
    }


    case Stage::GAME:
    {
      NI_PROFILE_BLOCK( "Stage::GAME" );
      PollMulticast();
      return PollGame();
    }

    case Stage::GAME_SESSION_FINISHED:
    {
      //TODO: Hang in this state a little, let the game finish on the server side, not counting us as a leaver...
      MessageTrace( "Client %d has finished game. userId=%d", params.localid, userId_ );
      return StepResult( true, false );
    }
  } //case ends
}



void Client_GS::TerminatePvx()
{
  pvxTerminationTime = timer::Now() + 10.0;
}



StepResult Client_GS::PollGame()
{
  NI_PROFILE_FUNCTION;

  if ( !gamesrv_ )
    return StepResult( true, false );

  if ( gamesrv_->GetStatus() != rpc::Connected ) {
    ErrorTrace( "Connection to game server lost! userId=%d, currentStep=%d", userId_, currentStep_ );
    return StepResult( true, false );
  }

  if ( currentStep_ > sendStep_ )
  {
    if ( !( currentStep_ % params.sendFreq ) )
    {
      //LOG_M(0).Trace("SendCommand(c=%d cidx=%d sid=%d step=%d sendfreq=%d)",
      //  userId_, sessionClientIdx_, serverId_, currentStep_, sendFreq_);

      unsigned sendSize = params.sendDataSize;
      if ( sendSize < 12 )
      {
        //More or less realistic random
        int roll = packetSizeRandom.Next( 100 );
        if ( roll <= 1 )
          sendSize = 152;
        else if ( roll <= 2 )
          sendSize = 112;
        else if ( roll <= 3 )
          sendSize = 82;
        else if ( roll <= 5 )
          sendSize = 71;
        else if ( roll <= 7 )
          sendSize = 69;
        else if ( roll <= 9 )
          sendSize = 67;
        else if ( roll <= 11 )
          sendSize = 65;
        else if ( roll <= 15 )
          sendSize = 36;
        else if ( roll <= 50 )
          sendSize = 34;
        else if ( roll <= 75 )
          sendSize = 32;
        else
          sendSize = 12;
      }

      char * commandData = new char[sendSize];
      FormatCommand( commandData, sendSize, userId_, dataRandom );
      rpc::MemoryBlock block(commandData, sendSize);
      gamesrv_->SendCommand(sessionClientIdx_, block, true);
      sendStep_ = currentStep_;
      delete [] commandData;
    }

    if ( stage_ == Stage::GAME )
      if ( gameDurationSteps && ( currentStep_ >= gameDurationSteps ) ) {
        MessageTrace( "Finishing game! userId=%d, currentStep=%d, finishStep=%d", userId_, currentStep_, gameDurationSteps );
        gamesrv_->OnGameFinish( sessionClientIdx_, gameDurationSteps, gameFinishData );
        stage_ = Stage::GAME_SESSION_FINISHED;
      }
  }

  if(chatClient)
  {
    chatClient->Step();
    vector<gamechat::ChatMessage> newMessages;
    chatClient->GetNewMessages( newMessages );
    for ( vector<gamechat::ChatMessage>::iterator it = newMessages.begin();it != newMessages.end() ; ++it )
    {
      //if (it->messageType != gamechat::ChatMessage::Predefined)
      //  continue;

      // Check it here
      MessageTrace("Recv chat message: from=%s to=%d msg=%s", it->nickname, static_cast<int>(it->channel), it->message);
    }

    if (currentStep_ > chatSendStep && !(currentStep_ % params.chatMsgsInterval)) // Temp. 2 seconds interval
    {
      // send something
      wstring message = NStr::StrFmtW(L"test%dx%d", userId_, currentStep_);
      chatClient->SendMsg(message, gamechat::ChannelType::MyTeam);
      MessageTrace("Send chat message: from=%d msg=%s", userId_, message);
      chatSendStep = currentStep_;
    }
  }

  return StepResultOk();
}



void Client_GS::PollMulticast()
{
  if (!inputChannel)
  {
    Transport::TChannels channels;
    transport_->GetNewAcceptedChannels(channels);
    if (channels.size())
    {
      inputChannel = *(channels.begin());
      MessageTrace("Multicast channel accepted. userId=%d", userId_);
    }
  }
  else if (inputChannel->GetStatus() == Network::ConnectionState::Connected)
  {
    vector<byte> data;
    if (inputChannel->ReceiveRaw(&data))
    {
      rpc::MemoryBlock mcData((void*)&data[0], data.size());
      Step2(mcData);
    }
  }
  else if(inputChannel->GetStatus() == Network::ConnectionState::Closed)
  {
    inputChannel = 0;
    MessageTrace("Multicast channel closed. userId=%d", userId_);
  }
}



int Client_GS::checkSessionStarted()
{
  NI_PROFILE_FUNCTION;

  lastresult_ = Result::IN_PROGRESS;
  return lastresult_;
}



int Client_GS::startJoinGameSession()
{
  NI_PROFILE_FUNCTION;

  if ( !gamesrv_ )
    return Result::NONE;

  nstl::string playerName("player_");
  char tmp[16];
  _itoa_s(transport_->GetUserId(), tmp, sizeof(tmp) - 1, 10);
  playerName += nstl::string(tmp);

  factory_->RegisterAttach<Peered::IGameClient, Peered::LIGameClient>();

  Login::ClientVersion clientVersion;

  //FIXME: Здесь образуется циклическая ссылка:
  // - GameServer держит R-ссылку на Client (как на Peered::IGameClient)
  // - Client держит R-ссылку на GameServer
  gamesrv_->AddClient( playerName.c_str(), transport_->GetUserId(), clientVersion, gameClientWrapper );

  stage_ = Stage::JOIN_GAME_SESSION_STARTED;
  lastresult_ = Result::IN_PROGRESS;
  return lastresult_;
}



int Client_GS::checkJoinGameSession()
{
  NI_PROFILE_FUNCTION;
  return lastresult_;
}



int Client_GS::LoadMapSimulate()
{
  NI_PROFILE_FUNCTION;

  lastresult_ = Result::SUCCESS;
  if (0.0 == startLoadMapTime_)
  {
    systemLog(NLogg::LEVEL_MESSAGE) << "Map load started(user=" << userId_ << ")" << endl;
    stage_ = Stage::LOAD_MAP_STARTED;
    startLoadMapTime_ = timer::Now();
  }
  else
  {
    NHPTimer::FTime delta = timer::Now() - startLoadMapTime_;
    if (delta > params.mapLoadTimeout)
    {
      systemLog(NLogg::LEVEL_MESSAGE) << "Map loading finished(user=" << userId_ << ")" << endl;
      stage_ = Stage::LOAD_MAP_FINISHED;
    }
  }

  return lastresult_;
}



void Client_GS::UpdateStepStatistics(int step)
{
  if (stats.IsStarted())
  {
    NHPTimer::STime stepTime = stats.Stop();
    if (params.logEveryLagFromMs > 0)
    {
      int stepTimeMs = NHPTimer::Time2Milliseconds(stepTime);
      if (stepTimeMs > params.logEveryLagFromMs)
      {
        DebugTrace("Client_GS: Step lag detected:%d (uid=%d)", stepTimeMs, UserId());
      }
    }
  }

  if (stats.GetCount() == 50)
  {
    const AppFramework::InstanceStatistics::ValueAccumulator& info = stats.Finish();
    int avgValueTimeMs = NHPTimer::Time2Milliseconds(info.averageValue);

    if ((avgValueTimeMs-GAME_STEP_LENGTH) > 2 || stats.GetLongTimeCount() > 0)
    {
      int minValueTimeMs = NHPTimer::Time2Milliseconds(info.minValue);
      int maxValueTimeMs = NHPTimer::Time2Milliseconds(info.maxValue);

      if (StrongMT<IClientsContainer> locked = params.clientsContainer.Lock())
        locked->GetLagsStatsContainer().AddLag(ELagType::Step, stats, minValueTimeMs, 
                                                avgValueTimeMs, maxValueTimeMs, step, UserId());
    }
    stats.Reset();
  }

  stats.Start();
}



void Client_GS::UpdateQueueTimeStatistics(int step, const Transport::MessageMiscInfo & miscInfo)
{
  if (miscInfo.queueAbsTime <= 0)
    return;

  queueTimeStats.Start(miscInfo.queueAbsTime);
  queueTimeStats.Stop();

  if (queueTimeStats.GetCount() == 50)
  {
    if (queueTimeStats.GetLongTimeCount() > 0)
    {
      const AppFramework::InstanceStatistics::ValueAccumulator& info = queueTimeStats.Finish();

      int minValueTimeMs = NHPTimer::Time2Milliseconds(info.minValue);
      int maxValueTimeMs = NHPTimer::Time2Milliseconds(info.maxValue);
      int avgValueTimeMs = NHPTimer::Time2Milliseconds(info.averageValue);

      if (StrongMT<IClientsContainer> locked = params.clientsContainer.Lock())
        locked->GetLagsStatsContainer().AddLag(ELagType::Queue, stats, minValueTimeMs, 
                                                avgValueTimeMs, maxValueTimeMs, step, UserId());
    }
    queueTimeStats.Reset();
  }
}



int Client_GS::checkGameSessionStarted()
{
  NI_PROFILE_FUNCTION;
  return lastresult_;
}



int Client_GS::ClientReadyToPlay()
{
  NI_PROFILE_FUNCTION;

  gamesrv_->OnClientReady(sessionClientIdx_);
  lastresult_ = Result::SUCCESS;
  stage_ = Stage::CLIENT_READY_TO_PLAY;

  return lastresult_;
}



void Client_GS::StartGame( Peered::IGameServer * gsrv )
{
  if (gsrv)
  {
    gamesrv_ = gsrv;
    lastresult_ = Result::SUCCESS;
  }
  else
  {
    lastresult_ = Result::FAIL;
  }
  stage_ = Stage::GAME_STARTING;
}



void Client_GS::Start(const Peered::ClientStartInfo& clientStartInfo)
{
  LOG_M(0).Trace("%s(index=%d serverid=%d confirmFreq=%d userid=%d)", 
    __FUNCTION__, clientStartInfo.index, clientStartInfo.serverId, clientStartInfo.confirmFrequency, userId_);

  if (-1 != clientStartInfo.index)
  {
    sessionClientIdx_ = clientStartInfo.index;
    serverId_ = clientStartInfo.serverId;
    lastresult_ = Result::SUCCESS;
    confirmFrequency = clientStartInfo.confirmFrequency;

    if (params.chatMsgsInterval > 0)
      chatClient = new gamechat::Client(serverId_, transport_->GetUserId(), NStr::ToUnicode(params.user), gateKeeper_);
  }
  else
  {
    lastresult_ = Result::FAIL;
  }

  SetupGameFinishClientStats( clientStartInfo );

  stage_ = Stage::JOIN_GAME_SESSION_FINISHED;
}



void Client_GS::OnStart(int step)
{
  systemLog(NLogg::LEVEL_MESSAGE) << "OnStart(step=" << step << ") user(" << userId_ << ") " << " clientIndex(" << sessionClientIdx_ << ")" << endl;

  initialStep_ = step;

  stage_ = Stage::GAME;
  lastresult_ = Result::SUCCESS;
}



void Client_GS::Step(int step, const nstl::vector<rpc::MemoryBlock>& commands,
  const nstl::vector<Peered::BriefClientInfo>& statuses, const nstl::vector<Peered::GapInfo>& clientGaps,
  const Transport::MessageMiscInfo& miscInfo)
{
  // Ignore repetitive steps, which are possible when establishing multicast
  if (step <= currentStep_)
    return;

  if (initialStep_ >= 0 && params.logGSStepLags)
  {
    UpdateStepStatistics(step);
    UpdateQueueTimeStatistics(step, miscInfo);
  }

  // Ignore blocked steps
  if (step == NCore::INVALID_STEP)
    return;

  if (currentStep_ != NCore::INVALID_STEP)
    NI_ASSERT((currentStep_ + 1 == step), 
              NStr::StrFmt("server(%d) client(%d), wrong step received(laststep=%d, recvstep=%d)", 
              serverId_, sessionClientIdx_, currentStep_, step));

  currentStep_ = step;

  if ((currentStep_ < 100 /*&& 0 == currentStep_%20*/) || 0 == currentStep_%100)
    systemLog(NLogg::LEVEL_MESSAGE).Trace("Client::Step(c=%d cidx=%d sid=%d step=%d)",
      userId_, sessionClientIdx_, serverId_, step);

  if (initialStep_ >= 0 && confirmFrequency > 0 && step % confirmFrequency == 0)
  {
    if (params.traceStepConfirmation)
      LOG_M(0).Trace("Step confirmation(c=%d cidx=%d sid=%d step=%d)",
        userId_, sessionClientIdx_, serverId_, step);

    gamesrv_->SendProtectionMagic(sessionClientIdx_, currentStep_, 0U);
    gamesrv_->OnFinishStep(sessionClientIdx_, currentStep_, step);
  }
}


void Client_GS::StepBatch(const nstl::vector<Peered::ClientStepData>& stepData)
{
  for (int i = 0; i < stepData.size(); ++i)
  {
    const Peered::ClientStepData & step = stepData[i];
    Step(step.step, step.commands, step.statuses, step.clientGaps, Transport::MessageMiscInfo());
  }
}


void Client_GS::Step2(const rpc::MemoryBlock& stepData)
{
  char * src = (char *)stepData.memory;

  int step;
  memcpy(&step, src, sizeof(int));
  src += sizeof(int);

  int lastConfirmedStep;
  memcpy(&lastConfirmedStep, src, sizeof(int));
  src += sizeof(int);

  int size;
  memcpy(&size, src, sizeof(int));
  src += sizeof(int);
  vector<rpc::MemoryBlock> commands(size);
  for (int i = 0; i < size; ++i)
  {
    int commandSize;
    memcpy(&commandSize, src, sizeof(int));
    src += sizeof(int);
    commands[i].size = commandSize;
    commands[i].memory = src;
    src += commandSize;
  }

  memcpy(&size, src, sizeof(int));
  src += sizeof(int);
  vector<Peered::BriefClientInfo> statuses(size);
  for (int i = 0; i < size; ++i)
  {
    statuses[i] = *(Peered::BriefClientInfo*)src;
    src += sizeof(Peered::BriefClientInfo);
  }

  memcpy(&size, src, sizeof(int));
  src += sizeof(int);
  vector<Peered::GapInfo> gapInfo(size);
  for (int i = 0; i < size; ++i)
  {
    gapInfo[i] = *(Peered::GapInfo*)src;
    src += sizeof(Peered::GapInfo);
  }

  Step(step, /*lastConfirmedStep,*/ commands, statuses, gapInfo, Transport::MessageMiscInfo());
}



void Client_GS::ApplySnapshot(int step, uint worldCrc, const nstl::vector<Peered::BriefEntityInfo>& entitiesIds, const nstl::vector<rpc::MemoryBlock>& entitiesData)
{
}



void Client_GS::OnChangeClientStatus(const nstl::vector<Peered::BriefClientInfo>& clientStatuses)
{
  for (int i=0;i<clientStatuses.size();++i)
  {
    systemLog(NLogg::LEVEL_MESSAGE).Trace("Client::OnChangeClientStatus (cid=%d status=%d)", clientStatuses[i].clientId, (int)clientStatuses[i].status);
  }
}



void Client_GS::OnAsync(int step, const nstl::vector<Peered::AsyncInfo>& async)
{
  ASSERT(!"ASYNC!");
}

} //namespace gtc

NI_DEFINE_REFCOUNT( gtc::Client_GS );
