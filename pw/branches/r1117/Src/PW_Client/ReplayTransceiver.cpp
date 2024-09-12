#include "stdafx.h"
#include "ReplayTransceiver.h"

#include "Core/Replay.h"
#include "Core/WorldBase.h"
#include "Core/WorldCommand.h"

#include "System/ChunklessSaver.h"
#include "System/SyncProcessorState.h"
#include "System/ConfigFiles.h"

#include "PF_GameLogic/GameMaps.h"
#include "PF_GameLogic/IAdventureScreen.h"

#include "Client/MainTimer.h"
#include "HybridServer/PeeredTypes.h"
#include "Network/LoginClientVersion.h"
#include "PW_Client/LoadingStatusHandler.h"
#include "Version.h"


namespace
{
DEV_VAR_STATIC int g_saveWorldForReplayStep = NCore::INVALID_STEP;
DEV_VAR_STATIC int g_skipAllUntilReplayStep = NCore::INVALID_STEP;

const static float g_replayMsgTime = 3000.0f;
const static float g_replaySpeedIncStep = 2.0f;
const static float g_replaySpeedDecStep = 0.5f;

static float g_replaySpeedIncLimit = 4.0f;
static float g_replaySpeedDecLimit = 0.25f;
}


namespace NWorld
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ReplayStorage2::ReplayStorage2(NCore::ReplayBufferMode mode, 
                               const char * fileName, 
                               NWorld::IMapCollection * _mapCollection, 
                               NGameX::LoadingStatusHandler * _loadingStatusHandler)
  : mapCollection(_mapCollection)
  , loadingStatusHandler(_loadingStatusHandler)
  , startStep(NCore::INVALID_STEP)
  , currentStep(NCore::INVALID_STEP)
  , nextStep(NCore::INVALID_STEP)
  , isFinished(false)
{
  if (mode == NCore::REPLAY_BUFFER_READ)
  {
    replayFile = new FileStream( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    NI_ASSERT(replayFile->IsOk(), NStr::StrFmt( "Cannot open file \"%s\"", fileName ));
    SetLoadingStatus(Game::EReplayStatus::Failure);
  }
  else
  {
    NI_ALWAYS_ASSERT( "ReplayStorage2 don't support replay writing!" );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReplayStorage2::GetNextSegment( NCore::SyncSegment & segOut )
{
  NI_PROFILE_FUNCTION;

  if (isFinished)
    return false;

  ushort commandsCount;
  ushort statusesCount;

  if (startStep == NCore::INVALID_STEP)
  {
    replayFile->Read( &startStep, sizeof(int) );
    replayFile->Read( &nextStep, sizeof(int) );
    currentStep = startStep;
  }
  else
  {
    ++currentStep;
  }

  segOut.commands.clear();
  segOut.statuses.clear();
  segOut.step = (uint)currentStep;

  if (currentStep < nextStep)
    return true;

  replayFile->Read( &commandsCount, sizeof(ushort) );
  replayFile->Read( &statusesCount, sizeof(ushort) );

  segOut.commands.reserve(commandsCount);

  for (int i = 0; i < commandsCount; ++i)
  {
    ushort size;
    replayFile->Read( &size, sizeof(ushort) );
    const int endPos = replayFile->GetPosition() + size;
    int id = 0;
    replayFile->Read( &id, sizeof( id ) );
    CObjectBase * command = NObjectFactory::MakeObject( id );
    NI_VERIFY( command, NStr::StrFmt( "Can not create command object with id = 0x%08X!", id ), 
                  isFinished = true; return false; );
    CObj<IBinSaver> saver = CreateChunklessSaver( replayFile, 0, true );
    saver->AddPolymorphicBase( 1, command );
    NI_VERIFY( replayFile->GetPosition() == endPos, "Command's data size mismatch!", 
                  isFinished = true; return false; );
    // Dynamic cast will return null for loading status commands - they should be ignored
    if (NCore::PackedWorldCommand * packedCommand = dynamic_cast<NCore::PackedWorldCommand *>(command) )
      segOut.commands.push_back( packedCommand );
  }

  segOut.statuses.reserve(statusesCount);

  for (int i = 0; i < statusesCount; ++i)
  {
    ushort size;
    replayFile->Read( &size, sizeof(ushort) );
    NI_VERIFY( sizeof(NCore::ClientStatus) == size, "Wrong status data in replay!", 
                  isFinished = true; return false; );
    NCore::ClientStatus & status = segOut.statuses.push_back();
    replayFile->Read( &status, sizeof(NCore::ClientStatus) );
    status.step = status.step - startStep;  // Translate server step to world step
  }

  if (replayFile->GetPosition() == replayFile->GetSize())
  {
    isFinished = true;
    return false;
  }

  replayFile->Read( &nextStep, sizeof(int) );

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReplayStorage2::GetHeader(NCore::MapStartInfo * info, 
                               int * clientId, int * stepLength, 
                               NCore::ClientSettings * clientSettings, 
                               lobby::SGameParameters* gameParams )
{
  if (!mapCollection )
  {
    NI_ALWAYS_ASSERT("No map collection!");
    SetLoadingStatus(Game::EReplayStatus::Failure);
    return false;
  }

  int marker;
  replayFile->Seek( 0, SEEKORIGIN_BEGIN );
  replayFile->Read( &marker, sizeof(int) );
  if (marker != 'PRWP')
  {
    SetLoadingStatus(Game::EReplayStatus::WrongFormat);
    return false;
  }

  CObj<IBinSaver> pLoader = CreateChunklessSaver( replayFile, 0, true );

  Login::ClientVersion currentClientVersion(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION);
  Login::ClientVersion replayClientVersion;
  pLoader->Add( 1, &replayClientVersion );
  if (currentClientVersion != replayClientVersion && NGlobal::GetVar( "ignore_replay_version", 0 ).GetInt64() == 0)
  {
    NI_ALWAYS_ASSERT(NStr::StrFmt("Wrong replay client version (%d.%d.%d.%d)", replayClientVersion.major_, 
                        replayClientVersion.minor_, replayClientVersion.patch_, replayClientVersion.revision_));
    SetLoadingStatus(Game::EReplayStatus::WrongVersion);
    return false;
  }

  lobby::TGameLineUp gameLineUp;
  vector<Peered::ClientInfo> clientInfos;

  pLoader->Add( 2, clientId );
  pLoader->Add( 3, &gameLineUp );
  pLoader->Add( 4, gameParams );
  pLoader->Add( 5, stepLength );
  pLoader->Add( 6, clientSettings );
  pLoader->Add( 7, &clientInfos );

  StrongMT<NWorld::IMapLoader> mapLoader = mapCollection->CreateMapLoader( gameParams->mapId.c_str() );
  if ( !mapLoader )
  {
    // CreateMapLoader will assert on error, so just set status and return here
    SetLoadingStatus(Game::EReplayStatus::Failure);
    return false;
  }

  mapLoader->FillMapStartInfo( *info, gameLineUp, *gameParams );
  mapLoader->FillPlayersInfo( *info, clientInfos );

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayStorage2::SetLoadingStatus(Game::EReplayStatus::Enum status)
{
  if (loadingStatusHandler)
    loadingStatusHandler->OnReplayStatus(status);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ReplayTransceiver::ReplayTransceiver( NCore::IReplayStorage* _replay, int _stepLength /*= DEFAULT_GAME_STEP_LENGTH*/ )
: replay(_replay)
, time(0.0f)
, useServerReplay(false)
, stepLength(_stepLength)
, replayMsgTimer(0.0f)
, isPaused(false)
{
  NI_SYNC_FPU_START;
  stepLengthInSeconds = _stepLength/1000.0f;
  NI_SYNC_FPU_END;

  NGlobal::RegisterContextCmd( "timescale", this, &ReplayTransceiver::SetTimeScale );

  NGlobal::RegisterContextCmd( "replay_speed_inc", this, &ReplayTransceiver::ReplaySpeedInc );
  NGlobal::RegisterContextCmd( "replay_speed_dec", this, &ReplayTransceiver::ReplaySpeedDec );
  NGlobal::RegisterContextCmd( "replay_speed_rst", this, &ReplayTransceiver::ReplaySpeedRst );

  NGlobal::RegisterContextCmd( "replay_pause", this, &ReplayTransceiver::ReplayPause );

  NGlobal::ExecuteConfig( "replay.cfg",	NProfile::FOLDER_GLOBAL );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayTransceiver::OnDestroyContent()
{
  NGlobal::UnregisterCmd( "timescale" );
  NGlobal::UnregisterCmd( "replay_speed_inc" );
  NGlobal::UnregisterCmd( "replay_speed_dec" );
  NGlobal::UnregisterCmd( "replay_speed_rst" );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayTransceiver::Step( float dt )
{
  NI_PROFILE_FUNCTION;

  StepReplayMessage( dt );

  if (isPaused)
    return;

  time += dt;

  if ( time < stepLength || !world )
    return;

  time = time - stepLength;

  bool replayEnded = false;
  bool ignoreStep = false;

  int step = NCore::INVALID_STEP;

  do
  {
    if (useServerReplay)
    {
      NCore::SyncSegment segment;
      if ( replay->GetNextSegment( segment ) )
      {
        ignoreStep = g_skipAllUntilReplayStep != NCore::INVALID_STEP && (int)segment.step < g_skipAllUntilReplayStep;
        if (!ignoreStep)
        {
          world->ExecuteCommands(segment.commands);
          world->UpdatePlayerStatuses(segment.statuses);
          step = segment.step;
        }
      }
      else
        replayEnded = true;
    }
    else
    {
      NCore::ReplaySegment segment;
      if ( replay->GetNextSegment( segment ) )
        world->ExecuteCommands(segment.seg);
      else
        replayEnded = true;
    }


    if (replayEnded)
    {
      NI_ASSERT(IsValid(adventureScreen), "SetAdventureScreenInterface wasn't called");
      adventureScreen->OnReplayEnded();
    }
    else
    {
      if (!ignoreStep)
      {
        world->Step( stepLengthInSeconds, stepLengthInSeconds );
        if (g_saveWorldForReplayStep > 0 && step == g_saveWorldForReplayStep)
          world->Save();
      }
    }
  } while (ignoreStep);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ReplayTransceiver::GetWorldStep() const
{
  return IsValid(world) ? world->GetStepNumber() : 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayTransceiver::SetWorld( NCore::IWorldBase * _world )
{
  world = _world;
  ptrHolder = world->GetPointerSerialization();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayTransceiver::SetTimeScale(float timeScale)
{
  NMainLoop::SetTimeScale( timeScale );

  adventureScreen->ShowReplaySpeed(timeScale);
  replayMsgTimer = g_replayMsgTime;
  MessageTrace("timescale: %f", timeScale);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReplayTransceiver::SetTimeScale( const char *name, const vector<wstring> &args )
{
  if ( args.size() != 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " scale" << endl;
    return true;
  }

  string arg = NStr::ToMBCS( args[0] );
  float scale = NStr::ReadFloat( arg.c_str(), arg.size() );
  if ( scale < 0.01f )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "timescale: " << arg << " is not valid value" << endl;
    return true;
  }

  SetTimeScale( scale );
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReplayTransceiver::ReplaySpeedInc( const char *name, const vector<wstring> &args )
{
  float timeScale = NMainLoop::GetTimeScale();
  timeScale *= g_replaySpeedIncStep;
  if (timeScale <= g_replaySpeedIncLimit)
    SetTimeScale( timeScale );
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReplayTransceiver::ReplaySpeedDec( const char *name, const vector<wstring> &args )
{
  float timeScale = NMainLoop::GetTimeScale();
  timeScale *= g_replaySpeedDecStep;
  if (timeScale >= g_replaySpeedDecLimit)
    SetTimeScale( timeScale );
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReplayTransceiver::ReplaySpeedRst( const char *name, const vector<wstring> &args )
{
  float timeScale = NMainLoop::GetTimeScale();
  if (timeScale != 1.0f)
    SetTimeScale( 1.0f );
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReplayTransceiver::ReplayPause( const char *name, const vector<wstring> &args )
{
  isPaused = !isPaused;

  if (isPaused)
  {
    adventureScreen->ProcessGamePause( NGameX::PAUSE_HARD, 0 );
    adventureScreen->ShowReplayPause();
    replayMsgTimer = g_replayMsgTime;
    MessageTrace("Pause: On");
  }
  else
  {
    adventureScreen->ProcessGamePause( NGameX::PAUSE_OFF, 0 );
    MessageTrace("Pause: Off");
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayTransceiver::StepReplayMessage( float dt )
{
  if (replayMsgTimer > 0.0f)
  {
    replayMsgTimer -= dt / NMainLoop::GetTimeScale();
    if (replayMsgTimer <= 0.0f)
    {
      adventureScreen->HideReplayMsg();
    }
  }
}

} //namespace NWorld


REGISTER_DEV_VAR( "save_world_for_replay_step", g_saveWorldForReplayStep, STORAGE_NONE );
REGISTER_DEV_VAR( "skip_all_until_replay_step", g_skipAllUntilReplayStep, STORAGE_NONE );

REGISTER_VAR( "replay_speed_inc_limit", g_replaySpeedIncLimit, STORAGE_NONE );
REGISTER_VAR( "replay_speed_dec_limit", g_replaySpeedDecLimit, STORAGE_NONE );

NI_DEFINE_REFCOUNT( NWorld::ReplayTransceiver );
