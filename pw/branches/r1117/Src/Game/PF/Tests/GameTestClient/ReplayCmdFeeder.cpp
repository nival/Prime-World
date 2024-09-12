#include "stdafx.h"
#include "ReplayCmdFeeder.h"
#include "Server/LobbyPvx/CommonTypes.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// находим внутри файла replay первый event для данного clientId, соответственно рассчитываем "время старта проигрывания"
bool ReplayCommandFeeder::GetReplayStartTime()
{
  if( replay )
  {
	  DWORD segmentTime = 0;
    while ( !replay->IsEof() )
    {
      replay->GetNextSegment( segment );
      for( command = segment.seg.begin(); command != segment.seg.end(); ++command )
      {
	      if ( (*command)->ClientId() == clientId )
	      {
		      startTime = (*command)->TimeSent() - segmentTime;
		      return true;
	      }
      }
      segmentTime += segment.deltaTime * 1000;
    }
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// грузим файл с replay клиентских событий, находим там первую команду указанного клиента (и ее стартовое время) 
// (если не нашли, или что-то еще не так, сразу прибиваем replay, чтоб не отсвечивал)
bool ReplayCommandFeeder::LoadReplay( const char * replayFileName, int clientId_ )
{
	NGlobal::SetVar( "ignore_replay_version", true, STORAGE_NONE );

  clientId = clientId_;
  replay = new NCore::ReplayStorage( NCore::REPLAY_BUFFER_READ, replayFileName );
  if ( replay && replay->GetManager())
  {
    if ( replay->GetManager()->GetError() == NCore::REPLAY_ERROR_OK )
      LOG_M(0) << "Replay file loaded ok";
    else
    {
      LOG_C(0) << "Replay load ERROR: " << replay->GetManager()->GetError();
      replay = 0;
      return false;
    }
  }
  else
  {
    LOG_C(0) << "FAILED to initialize replay";
    replay = 0;
    return false;
  }

  systemLog( NLogg::LEVEL_MESSAGE ) << "Replay length: " << replay->GetNumberOfSegments() << " segments, " << replay->GetGameLength() << " sec.";
  NCore::MapStartInfo mapStart;
  int clientId;
  int stepLength;
  NCore::ClientSettings clientSettings;
  lobby::SGameParameters gameParams;
  replay->GetHeader( &mapStart, &clientId, &stepLength, &clientSettings, &gameParams );
  systemLog( NLogg::LEVEL_MESSAGE ) << "Map: \"" << mapStart.mapDescName << "\"";

  for( vector<NCore::PlayerStartInfo>::const_iterator player = mapStart.playersInfo.begin(); player != mapStart.playersInfo.end(); ++player )
  {
    if ( player->userID <= 0 )
	    continue;
    systemLog( NLogg::LEVEL_MESSAGE ) << "player [" << player->playerID << "] " << player->nickname << ", clientId: " << player->userID;
  }

  // находим стартовое время (== время первого евента данного игрока)
	bool startTimeFound = GetReplayStartTime();
  
  if( startTimeFound )
    LOG_M(0) << "Replay start time=" << startTime << " for clientId=" << clientId;
  else
  {
    LOG_C(0) << "No replay events found for clientId " << clientId;
    replay = 0;
    return false;
  }

  return (replay != 0);
}

bool ReplayCommandFeeder::GetCurrentCommand( NCore::ReplaySegment::Commands::iterator & outCommand )
{
  if( replay && 
      command != segment.seg.end() )
  {
    outCommand = command;
    return true;
  }

  return false;
}

bool ReplayCommandFeeder::GetNextCommand( NCore::ReplaySegment::Commands::iterator & outCommand )
{
  if( replay )
  {
    while ( !replay->IsEof() )
    {
      if ( command == segment.seg.end() )
      {
	      replay->GetNextSegment( segment );
        command = segment.seg.begin(); 
      }
      else
        command++;

	    if( command != segment.seg.end() )
      {
        outCommand = command;
        return true;
      }
    }
  }

  return false;
}
