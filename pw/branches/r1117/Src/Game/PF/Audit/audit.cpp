#include "stdafx.h"
#include "audit.h"

#include "Version.h"

#include "../Core/CoreFSM.h"
#include "../Core/MessagesAudit.h"
#include "../Core/MessagesInGame.h"

#include "../PF_GameLogic/DBUnit.h"
#include "../PF_GameLogic/PFHero.h"
#include "../PF_GameLogic/PFAIController.h"

#include "../System/SyncProcessorState.h"
#include "../System/WinFileSystem.h"
#include "../System/meminfo.h"

#include "../PF_GameLogic/MapStartup.hpp"

#include "SceneStub.h"

//////////////////////////////////////////////////////////////////////////

#define     GAME_STEP_LEN      0.1f

//////////////////////////////////////////////////////////////////////////


namespace AuditCore
{

AuditGameHolder::AuditGameHolder( const NCore::StartAuditGameInfo& info )
{
  pScene = AuditScene::Scene::Create();

  pWorld = new NWorld::PFWorld( pScene, info.mapInfo );
  pWorld->GetAIContainer()->Init(info.nodes, info.mapInfo);
  
  for ( vector<NCore::PlayerStartInfo>::const_iterator iPlayer = info.mapInfo.playersInfo.begin(), iEnd = info.mapInfo.playersInfo.end(); iPlayer != iEnd; ++iPlayer )
  {
    if ( iPlayer->nodeID == info.clientId )
      playerId = iPlayer->playerID;
  }
  
  NCore::GetGlobalGameFSM()->PushMessageToCore( new NCore::AuditGameStarted( info.clientId, pWorld.GetPtr(),new NWorld::Commands::StartMap(info.mapInfo), NCore::Transceiver::TM_GAME, "") );
}

void AuditGameHolder::InitAIContainer()
{
  NI_VERIFY( pWorld, "World must be valid!", return; );
  
  NWorld::PFPlayer* pPlayer = pWorld->GetPlayer( playerId );
  NI_VERIFY( pPlayer && pPlayer->GetHero(), "Invalid player or hero!", return; );
  
  pWorld->GetAIContainer()->Add( pPlayer->GetHero() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AuditCore::AuditCore()
  : m_pause(false)
  , m_playSpeed(1.0f)
  , m_timeInitialized(false)
  , m_curTime(0)
  , m_lastTimeDelta(0)
  , m_maxTimeDelta(1)
  , m_lastTime(0)
  , m_playersCount(maxPlayers)
  , m_textLogDumper( &GetSystemLog(), "TextLog" )
  , m_assertDumper( &GetSystemLog(), "Assert" )
  , m_consoleDumper( &GetSystemLog(), "Console" )
{
}

int AuditCore::Open()
{
  SyncProcessorState();
  //NDebug::SetProductNameAndVersion( PRODUCT_TITLE_SHORT, VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD, VERSION_REVISION );
  NFile::InitBaseDir();
  //NBSU::InitUnhandledExceptionHandler();	

  const string szMutexName( PRODUCT_TITLE_SHORT );
  //bool bSecondInstance = false;
  // при выходе система сама уничтожит этот mutex
  CreateMutex( 0, TRUE, szMutexName.c_str() );

  // мы сначала прочитаем cfg файлы, а потом решим что надо делать, может хочетс€ запустить две экземпл€ра игры на двух мониторах
  const bool bAlreadyRunned = ( GetLastError() == ERROR_ALREADY_EXISTS );
  const string szMutexName2 = szMutexName + "_2";
  if ( bAlreadyRunned )
  {
    return 0xDEAD;
  }

  m_textLogDumper.SetFileName("output");
  
  RootFileSystem::RegisterFileSystem( new WinFileSystem( NFile::GetBaseDir() + "Data", false ) );
  NDb::SetResourceCache( NDb::CreateGameResourceCache( RootFileSystem::GetRootFileSystem(), &RootFileSystem::GetChangesProcessor() ) );

  NProfile::Init( "Primal Forces" );

  SubscribeUpdates();

  NGlobal::ExecuteConfig( "default.cfg", NProfile::FOLDER_GLOBAL );
  NGlobal::ExecuteConfig( "user.cfg", NProfile::FOLDER_USER );
  if ( !NGlobal::ExecuteConfig( "audit.cfg", NProfile::FOLDER_GLOBAL ) )
    return -1;

  NDebug::SetMainThreadID( GetCurrentThreadId() );

  return 0;
}

int AuditCore::Close()
{
  for( int i = 0; i < maxPlayers; ++i )
    Reset(m_holders[i], NULL);

  NCore::ReleaseGlobalGameFSM();

  NGlobal::SaveConfig( NProfile::GetFullFilePath( "user.cfg", NProfile::FOLDER_USER ), STORAGE_USER );
  return 0;
}

bool AuditCore::Update()
{
  NHPTimer::UpdateHPTimerFrequency();
  
  if ( !m_timeInitialized )
  {
    NHPTimer::GetTime( m_lastTime );
    m_curTime = 0;
    m_lastTimeDelta = 0;
    m_timeInitialized = true;
  }

  float timeDelta = Min(m_maxTimeDelta, float(NHPTimer::GetTimePassedAndUpdateTime( m_lastTime )));

	if (m_pause)
		return true;

	m_lastTimeDelta += timeDelta;
  m_curTime += timeDelta;
  
  // step game state machine
  float gameDelta = GAME_STEP_LEN / m_playSpeed;
  while ( m_lastTimeDelta > gameDelta )
  {
    NCore::GetGlobalGameFSM()->Step( GAME_STEP_LEN * 1000.0f ); // @BVS@TIME
		m_lastTimeDelta -= gameDelta;
  }

  return true;    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AuditCore::SubscribeUpdates()
{
  NCore::GetGlobalGameFSM()->RegisterProcessorFromCore(this);
  Subscribe( &AuditCore::OnStartingAudit );
  Subscribe( &AuditCore::OnStartAuditGame );
  Subscribe( &AuditCore::OnAuditStarted );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AuditCore::OnStartingAudit( const struct NCore::StartingAudit& )
{
  const string mapName = NStr::ToMBCS( NGlobal::GetVar("map_name").GetString() );
  const int playersCount = static_cast<int>( NGlobal::GetVar("players_count").GetFloat() );

  if ( playersCount > 1 && playersCount <= maxPlayers )
    m_playersCount = playersCount;
  
  NCore::MapStartInfo startInfo;
  if ( !FillMapStartInfo(&startInfo, mapName, m_playersCount) )
    return;

  NCore::GetGlobalGameFSM()->PushMessageToCore( new NCore::AuditStartInfo( startInfo ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AuditCore::OnStartAuditGame( const NCore::StartAuditGame& info )
{
  int clientId = info.startInfo.clientId;
  NI_VERIFY( clientId >= 0 && clientId < m_playersCount, "Wrong player ID or max players count exceeded!", return; );
  NI_VERIFY( !m_holders[clientId], "Game for that client alreary started!", return; );
  
  m_holders[clientId] = AutoPtr<AuditGameHolder>( new AuditGameHolder(info.startInfo) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AuditCore::OnAuditStarted( const struct NCore::AuditStarted& )
{
  for (int i = 0; i < m_playersCount; ++i )
    m_holders[i]->InitAIContainer();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AuditCore::FillMapStartInfo( NCore::MapStartInfo* pRes, const string& mapName, const int playersCount)
{
  NI_VERIFY( NULL != pRes, "Invalid argument!", return false; );

  NDb::Ptr<NDb::AdvMap> pAdvMap = NDb::Get<NDb::AdvMap>( NDb::DBID( mapName ) );
  NI_VERIFY( pAdvMap, NStr::StrFmt( "Cannot load map from \"{0}\"", mapName.c_str() ), return false );
  NI_VERIFY( pAdvMap->heroes, NStr::StrFmt( "There is no heroes on map \"{0}\"", mapName.c_str() ), return false );
  //NI_VERIFY( pAdvMap->structureDefinition, NStr::StrFmt( "There is no structureDefinition on map \"{0}\"", mapName.c_str() ), return false );

  vector<NCore::PlayerStartInfo> players;

  int team1Players = 0, team2Players = 0;
  int const uniqueHeroes = pAdvMap->heroes->heroes.size(); 

  vector<NDb::AdvMapObject> const& objects = pAdvMap->objects;
  for ( vector<NDb::AdvMapObject>::const_iterator it = objects.begin(), end = objects.end(); it != end; ++it )
  {
    NDb::Ptr<NDb::GameObject> pGO = it->gameObject;
    if( IsValid( pGO ) && NDb::HeroPlaceHolder::typeId == pGO->GetObjectTypeID() )
    {
      NDb::HeroPlaceHolder const* pSpawner = dynamic_cast<NDb::HeroPlaceHolder const*>(pGO.GetPtr());
      NI_VERIFY( pSpawner, "Invalid gameobject!", continue; );

      if( NDb::TEAMID_A == pSpawner->teamId )
        ++team1Players;
      else
        if( NDb::TEAMID_B == pSpawner->teamId )
          ++team2Players;

      NCore::EPlayerType playerType = ( playersCount < 0 || playersCount < (team1Players + team2Players) ) ? 
        NCore::PLAYER_INVALID : NCore::PLAYER_COMPUTER ;

      players.push_back( NCore::PlayerStartInfo(players.size(), pSpawner->teamId, players.size() % uniqueHeroes, playerType) );
    }
  }

  NI_VERIFY( 0 < team1Players && 0 < team2Players, "Invalid map: no placeholders found for one or both team(s)", return false; );

  pRes->playersInfo.swap(players);
  pRes->mapName = mapName;

  systemLog(NLogg::LEVEL_MESSAGE) << "Loaded info for map:" << mapName << endl
    << "  max players:" << team1Players << "x" << team2Players << endl;

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CommandAuditGame(const char *name, const vector<wstring> &params)
{
  NCore::GetGlobalGameFSM()->PushMessageToCore( new NCore::SetInAuditState() );		
  return true;
}

REGISTER_CMD( audit, CommandAuditGame );

} //namespace AuditCore
