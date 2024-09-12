#include "stdafx.h"

#include "CommandIdResolver.h"
#include "System/DebugTraceDumper.h"
#include "System/StdOutDumper.h"
#include "System/CmdLine.h"
#include "System/ChunklessSaver.h"
#include "Core/CommandSerializer.h"
#include "Core/GameCommand.h"
#include "Core/WorldCommand.h"

class ReplayReader
{
public:
  ReplayReader( const char* fileName ) : state( None ), segment( -1 ), commandsLeft( 0 )
  {
    stream = new FileStream( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    NI_VERIFY( stream->IsOk(), NStr::StrFmt( "Cannot open file \"%s\"", fileName ), return );

    Reset();
  }

  void Reset()
  {
    if ( !IsOk() )
      return;

    stream->Seek( 0, SEEKORIGIN_BEGIN );
    
    int sign = 0;
    stream->Read( &sign, sizeof( sign ) );
    NI_VERIFY( sign == replSign, "Invalid replay signature", { stream = 0; return; } );

    state = Segment;
  }

  int ReadSegment()
  {
    if ( IsFinished() || state != Segment )
      return segment;
    
    char sign;
    stream->Read( &sign, sizeof( sign ) );
    if ( sign == 'R' )
    {
      int sign2 = 0;
      stream->Read( &sign2, sizeof( sign2 ) );
      NI_VERIFY( sign2 == replSign2, "Invalid data found in replay", { state = None; return -1; } );
      
      MessageTrace( "REPL mark found at offset %d", stream->GetPosition() - 5 );
    }
    else
    {
      NI_VERIFY( sign == 0, "Invalid data found in replay", { state = None; return -1; } );
    }

    stream->Read( &segment, 4 );
    stream->Read( &commandsLeft, sizeof( commandsLeft ) ); 
    state = Command;
    return segment;
  }

  NCore::PackedWorldCommand* ReadCommand()
  {
    if ( IsFinished() || state != Command )
      return 0;

    --commandsLeft;
    if ( commandsLeft == 0 )
      state = Segment;

    WORD size = 0;
    stream->Read( &size, sizeof( size ) );
    const int endPos = stream->GetPosition() + size;

    int id = 0;
    stream->Read( &id, sizeof( id ) );
	  CObjectBase *command = NObjectFactory::MakeObject( id );
    NI_VERIFY( command, NStr::StrFmt( "Cannot create command object with id = 0x%08X", id ), { stream->Seek( endPos, SEEKORIGIN_BEGIN ); return 0; } );

    {
	    CObj<IBinSaver> saver = CreateChunklessSaver( stream, 0, true );
	    saver->AddPolymorphicBase( 1, command );
    }
    NI_ASSERT( stream->GetPosition() == endPos, "Command's data size mismatch" );

    return dynamic_cast<NCore::PackedWorldCommand*>( command );
  }

  bool IsOk() const { return stream && stream->IsOk(); }

  bool IsFinished() const { return !IsOk() || state == None || stream->GetPosition() == stream->GetSize(); }

private:
  enum { replSign = 0x4C504552, }; // "REPL" signature
  enum { replSign2 = 0x004C5045, }; // "EPL"\0 signature (if REPL occured in the middle of file)
  enum ReplayReaderState { None, Segment, Command, };

  CObj<Stream> stream;
  ReplayReaderState state;

  int segment;
  WORD commandsLeft;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ExtractCommands( ReplayReader& replay )
{
  if ( !replay.IsOk() )
    return;

  replay.Reset();

  while ( !replay.IsFinished() )
  {
    int segment = replay.ReadSegment();
    MessageTrace( "Segment: %d", segment );
    while ( CObj<NCore::PackedWorldCommand> command = replay.ReadCommand() )
    {
      string commandStr = ReplayPlayer::ResolveCommandId( command->GetStream() );
      MessageTrace( "  Command: 0x%08X (%s) from %06d (%d bytes)", command->GetCommandId(), commandStr.c_str(), command->ClientId(), command->GetCommandSize() );
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ExtarctStatistics( ReplayReader& replay )
{
  if ( !replay.IsOk() )
    return;

  replay.Reset();

  int segmentsCount      = 0;

  struct CommandStatistics
  {
    int totalSize;
    int totalCount;
    int maxSizePerSegment;
    int maxSizePerSegmentSegmentNo;
    int maxCountPerSegment;
    int maxCountPerSegmentSegmentNo;

    CommandStatistics() : totalSize(0), totalCount(0), maxSizePerSegment(0), 
      maxSizePerSegmentSegmentNo(0), maxCountPerSegment(0), maxCountPerSegmentSegmentNo(0) {}
  };

  CommandStatistics statistics;
  nstl::hash_map<int, CommandStatistics> statisticsPerUser;
  nstl::hash_map<nstl::string, CommandStatistics> statisticsPerCommand;

  while ( !replay.IsFinished() )
  {
    int segment = replay.ReadSegment();

    int totalSizeInSegment = 0;
    int totalCountInSegment = 0;

    nstl::hash_map<int, CommandStatistics> statisticsPerUserInSegment;
    nstl::hash_map<nstl::string, CommandStatistics> statisticsPerCommandInSegment;

    ++segmentsCount;

    while ( CObj<NCore::PackedWorldCommand> command = replay.ReadCommand() )
    {
      nstl::string commandName = ReplayPlayer::ResolveCommandId( command->GetStream(), true );
      int commandSize = command->GetCommandSize();
      int clientId = command->ClientId();

      totalSizeInSegment += commandSize;
      statistics.totalSize += commandSize;
      statisticsPerUser[clientId].totalSize += commandSize;
      statisticsPerUserInSegment[clientId].totalSize += commandSize;
      statisticsPerCommand[commandName].totalSize += commandSize;
      statisticsPerCommandInSegment[commandName].totalSize += commandSize;

      ++totalCountInSegment;
      ++statistics.totalCount;
      ++statisticsPerUser[clientId].totalCount;
      ++statisticsPerUserInSegment[clientId].totalCount;
      ++statisticsPerCommand[commandName].totalCount;
      ++statisticsPerCommandInSegment[commandName].totalCount;
    }

    for (nstl::hash_map<int, CommandStatistics>::iterator it = statisticsPerUserInSegment.begin(); 
          it != statisticsPerUserInSegment.end(); ++it)
    {
      if (statisticsPerUser[it->first].maxSizePerSegment < it->second.totalSize)
      {
        statisticsPerUser[it->first].maxSizePerSegment = it->second.totalSize;
        statisticsPerUser[it->first].maxSizePerSegmentSegmentNo = segment;
      }
      if (statisticsPerUser[it->first].maxCountPerSegment < it->second.totalCount)
      {
        statisticsPerUser[it->first].maxCountPerSegment = it->second.totalCount;
        statisticsPerUser[it->first].maxCountPerSegmentSegmentNo = segment;
      }
    }

    for (nstl::hash_map<nstl::string, CommandStatistics>::iterator it = statisticsPerCommandInSegment.begin(); 
          it != statisticsPerCommandInSegment.end(); ++it)
    {
      if (statisticsPerCommand[it->first].maxSizePerSegment < it->second.totalSize)
      {
        statisticsPerCommand[it->first].maxSizePerSegment = it->second.totalSize;
        statisticsPerCommand[it->first].maxSizePerSegmentSegmentNo = segment;
      }
      if (statisticsPerCommand[it->first].maxCountPerSegment < it->second.totalCount)
      {
        statisticsPerCommand[it->first].maxCountPerSegment = it->second.totalCount;
        statisticsPerCommand[it->first].maxCountPerSegmentSegmentNo = segment;
      }
    }

    if (statistics.maxSizePerSegment < totalSizeInSegment)
    {
      statistics.maxSizePerSegment = totalSizeInSegment;
      statistics.maxSizePerSegmentSegmentNo = segment;
    }
    if (statistics.maxCountPerSegment < totalCountInSegment)
    {
      statistics.maxCountPerSegment = totalCountInSegment;
      statistics.maxCountPerSegmentSegmentNo = segment;
    }
  }

  MessageTrace( "===============================================================================" );
  MessageTrace( "| General command statistics for replay.                                      |" );
  MessageTrace( "===============================================================================" );
  MessageTrace( "Total segments count:         %8d", segmentsCount );
  MessageTrace( "Total commands size :         %8d", statistics.totalSize);
  MessageTrace( "Total commands count:         %8d", statistics.totalCount);
  MessageTrace( "Max commands size  per segment:  %5d (at %5d)", statistics.maxSizePerSegment, statistics.maxSizePerSegmentSegmentNo);
  MessageTrace( "Max commands count per segment:  %5d (at %5d)", statistics.maxCountPerSegment, statistics.maxCountPerSegmentSegmentNo);
  MessageTrace( "Avg commands size  per segment:  %5.1f", (float)statistics.totalSize / segmentsCount);
  MessageTrace( "Avg commands count per segment:  %5.1f", (float)statistics.totalCount / segmentsCount);
  MessageTrace( "===============================================================================" );
  MessageTrace( "| Per user command statistics for replay.                                     |" );
  MessageTrace( "===============================================================================" );
  for (nstl::hash_map<int, CommandStatistics>::iterator it = statisticsPerUser.begin(); 
        it != statisticsPerUser.end();)
  {
    MessageTrace( "Statistics for user %i:", it->first );
    MessageTrace( "Total commands size :         %7d", it->second.totalSize);
    MessageTrace( "Total commands count:         %7d", it->second.totalCount);
    MessageTrace( "Max commands size  per segment:  %4d (at %5d)", it->second.maxSizePerSegment, it->second.maxSizePerSegmentSegmentNo);
    MessageTrace( "Max commands count per segment:  %4d (at %5d)", it->second.maxCountPerSegment, it->second.maxCountPerSegmentSegmentNo);
    ++it;
    if (it != statisticsPerUser.end())
    {
      MessageTrace( "-------------------------------------------------" );
    }
  }
  MessageTrace( "===============================================================================" );
  MessageTrace( "| Per command statistics for replay.                                          |" );
  MessageTrace( "===============================================================================" );
  for (nstl::hash_map<nstl::string, CommandStatistics>::iterator it = statisticsPerCommand.begin(); 
        it != statisticsPerCommand.end();)
  {
    MessageTrace( "Statistics for command %s:", it->first.c_str() );
    MessageTrace( "Total commands size :         %7d", it->second.totalSize);
    MessageTrace( "Total commands count:         %7d", it->second.totalCount);
    MessageTrace( "Max commands size  per segment:  %4d (at %5d)", it->second.maxSizePerSegment, it->second.maxSizePerSegmentSegmentNo);
    MessageTrace( "Max commands count per segment:  %4d (at %5d)", it->second.maxCountPerSegment, it->second.maxCountPerSegmentSegmentNo);
    ++it;
    if (it != statisticsPerCommand.end())
    {
      MessageTrace( "-------------------------------------------------" );
    }
  }
  MessageTrace( "===============================================================================" );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ExtractTraffic( ReplayReader& replay, bool countCommands )
{
  if ( !replay.IsOk() )
    return;

  replay.Reset();

  hash_map<int, int> clients;
  while ( !replay.IsFinished() )
  {
    replay.ReadSegment();
    while ( CObj<NCore::PackedWorldCommand> command = replay.ReadCommand() )
    {
      if ( clients.find( command->ClientId() ) == clients.end() )
        clients.insert( make_pair<int, int>( command->ClientId(), 0 ) );
    }
  }

  string header = "segment";
  for( hash_map<int, int>::const_iterator it = clients.begin(); it != clients.end(); ++it )
    header += NStr::StrFmt( ",%d", it->first );

  MessageTrace( "%s", header.c_str() );

  replay.Reset();
  int endSegment = 10;
  while ( !replay.IsFinished() )
  {
    int segment = replay.ReadSegment();
    while ( segment > endSegment )
    {
      string line = NStr::StrFmt( "%d", endSegment - 10 );
      for( hash_map<int, int>::iterator it = clients.begin(); it != clients.end(); ++it )
      {
        line += NStr::StrFmt( ";%d", it->second );
        it->second = 0;
      }
      MessageTrace( "%s", line.c_str() );

      endSegment += 10;
    }
    while ( CObj<NCore::PackedWorldCommand> command = replay.ReadCommand() )
    {
      if ( countCommands )
        clients[command->ClientId()] += 1;
      else
        clients[command->ClientId()] += ( command->GetCommandSize() + 8 ); //8 bytes for clientId and timeSent from PackedWorldCommand
    }
  }

  string line = NStr::StrFmt( "%d", endSegment - 10 );
  for( hash_map<int, int>::iterator it = clients.begin(); it != clients.end(); ++it )
  {
    line += NStr::StrFmt( ";%d", it->second );
    it->second = 0;
  }
  MessageTrace( "%s", line.c_str() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
  //NLogg::CDebugTraceDumper debugTraceDumper( &GetSystemLog() );
  NLogg::CStdOutDumper stdOutDumper( &GetSystemLog() );

	string replayFileName;
	bool list = false;
	bool traffic = false;
	bool commands = false;
  bool statistics = false;

	NCmdLine::CCmdLine cl( "" );
	cl.AddOption( "--replay", &replayFileName, "Specify file name with replay" );
	cl.AddOption( "--list", &list, true, "Extract commands for every segement from replay" );
	cl.AddOption( "--traffic", &traffic, true, "Extract traffic statistics from replay" );
	cl.AddOption( "--commands", &commands, true, "Extract commands statistics from replay" );
  cl.AddOption( "--statistics", &statistics, true, "Extract general statistics from replay" );
	
	if ( cl.Process( argc, argv ) != NCmdLine::CCmdLine::PROC_RESULT_OK )
		return cl.PrintUsage( "Usage: ReplayPlayer.exe --replay <replay_file_name> --info | --player <player_index> | --client <client_id>" );

  ReplayReader replay( replayFileName.c_str() );

  if ( list )
    ExtractCommands( replay );

  if ( traffic )
    ExtractTraffic( replay, false );

  if ( commands )
    ExtractTraffic( replay, true );

  if ( statistics )
    ExtarctStatistics( replay );

  return 0;
}