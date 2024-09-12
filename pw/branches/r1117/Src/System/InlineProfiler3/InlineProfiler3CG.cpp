#include "stdafx.h"
#include "InlineProfiler3CG.h"
#include "InlineProfilerTLD.h"


namespace profiler3
{

struct SRecord
{
  bool                isStarting;
  bool                hasMemoryInfo;
  TEventId            eventId;
  TTime               time;
  ni_detail::UInt32   allocs;
  ni_detail::SInt32   allocsDelta, memoryDelta;

  SRecord() :
  isStarting( false ), hasMemoryInfo( false ), eventId( 0 ), time( 0 ),
  allocs( 0 ), allocsDelta( 0 ), memoryDelta( 0 ) {}
};



static size_t ReadRecord( const ni_detail::Byte * data, size_t dataSize, SRecord & record )
{
  size_t size = 8;
  if ( dataSize < size )
    return 0;

  ni_detail::UInt64 firstChunk = *(ni_detail::UInt64 *)data;

  ni_detail::UInt64 code = firstChunk & ThreadLocalData::EventCode_MASK;

  record.isStarting = ( code == ThreadLocalData::EventCode_Start ) || ( code == ThreadLocalData::EventCode_StartWithMem );
  record.hasMemoryInfo = ( code == ThreadLocalData::EventCode_StartWithMem ) || ( code == ThreadLocalData::EventCode_FinishWithMem );

  record.eventId = (TEventId)( ( firstChunk & ThreadLocalData::EventId_MASK ) >> ThreadLocalData::EventId_ROLL );

  record.time = firstChunk & ThreadLocalData::EventCode_TIME_MASK;

  if ( record.hasMemoryInfo )
  {
    size += 12;
    if ( dataSize < size )
      return 0;

    ni_detail::UInt32 * memData = (ni_detail::UInt32 *)( data + 8 );
    record.allocs           = memData[0];
    record.allocsDelta      = memData[1];
    record.memoryDelta      = memData[2];
  }

  return size;
}



static size_t ParseCallgraph( Strong<CallGraphNodeImpl> & parent, const ni_detail::Byte * data, size_t dataSize, SRecord parentRec, int depth )
{
  size_t parsedData = 0;
  while ( true )
  {
    SRecord record;
    size_t parsed = ReadRecord( data + parsedData, dataSize - parsedData, record );
    parsedData += parsed;
    if ( !parsed )
    {
      NI_ASSERT( ( depth == 0 ) && parent, "Unexpected end of data" );
      return parsedData;
    }

    if ( record.isStarting )
    {
      Strong<CallGraphNodeImpl> subNode;
      if ( !parent )
      {
        parent = new CallGraphNodeImpl( record.eventId );
        parentRec = record;
        subNode = parent;
      }
      else
      {
        NI_VERIFY( depth != 0, "Duplicate root events", return parsedData );
        Strong<CallGraphNode> & node = parent->MapSubnode( record.eventId );
        if ( !node )
          node = new CallGraphNodeImpl( record.eventId );
        subNode = dynamic_cast<CallGraphNodeImpl *>( node.Get() );
      }

      parsedData += ParseCallgraph( subNode, data + parsedData, dataSize - parsedData, record, depth + 1 );
      
    }
    else //Finishing event
    {
      NI_ASSERT( parent, "Unexpected end marker" );
      parent->Add( record.time - parentRec.time );

      NI_ASSERT( record.hasMemoryInfo == parentRec.hasMemoryInfo, "Wrong memory events" );
      if ( record.hasMemoryInfo && parentRec.hasMemoryInfo )
        parent->AddMemory(  record.allocs - parentRec.allocs,
                            record.allocsDelta - parentRec.allocsDelta,
                            record.memoryDelta - parentRec.memoryDelta );

      return parsedData;
    }
  }
}



static void DebugParseCallgraph( const ni_detail::Byte * data, size_t dataSize )
{
  int index = 0;
  size_t parsedData = 0;
  while ( true )
  {
    SRecord rec;
    size_t parsed = ReadRecord( data + parsedData, dataSize - parsedData, rec );
    if ( !parsed )
      return;
    parsedData += parsed;

    string memDump;
    if ( rec.hasMemoryInfo )
      memDump = NI_STRFMT( "Allocs: %u, delta: %d bytes in %d allocs", rec.allocs, rec.memoryDelta, rec.allocsDelta );

    const SEventInfo & nodeInfo = GetControl()->GetEventInfo( rec.eventId );

    DebugTrace( "%03d: %s %s (%d), time %.5f, %s", index,
      rec.isStarting ? "Start" : "Finish", nodeInfo.name.c_str(), rec.eventId,
      (double)rec.time / 2.5e9 * 1e3, //Rough clock rate estim
      rec.hasMemoryInfo ? memDump.c_str() : "No memory info" );

    ++index;
  }

  DebugTrace( "%d total events" );
}



static unsigned PostProcessCallgraph( CallGraphNodeImpl * node, vector<TEventId> & callstack, TTotalEventInfos & totals, FTime timeFactor )
{
  node->CalculateSpan( timeFactor );

  unsigned totalCalls = 0;

  //Collect total per-event times
  bool reEntry = false;
  for ( int i = 0; i < callstack.size(); ++i )
    if ( callstack[i] == node->Data().eventId )
    {
      reEntry = true;
      break;
    }

  if ( !node->Subnodes().empty() )
    callstack.push_back( node->Data().eventId );

  //Process subnodes
  double subnodesTime = 0;
  for ( TCallGraphNodes::iterator it = node->Subnodes().begin(); it != node->Subnodes().end(); ++it )
  {
    totalCalls += PostProcessCallgraph( dynamic_cast<CallGraphNodeImpl * >( it->second.Get() ), callstack, totals, timeFactor );
    totalCalls += it->second->Data().calls;

    subnodesTime += it->second->Data().span;
  }

  if ( !node->Subnodes().empty() )
    callstack.pop_back();

  node->SetMeTime( node->Data().span - subnodesTime );

  STotalEventInfo & tt = totals[node->Data().eventId];
  tt.calls += node->Data().calls;
  if ( !reEntry )
  {
    tt.time += node->Data().span;

    if ( node->Data().hasAllocsInfo )
    {
      tt.hasAllocsInfo = true;
      tt.allocs += node->Data().allocs;
      tt.allocsDelta += node->Data().allocsDelta;
      tt.memoryDelta += node->Data().memoryDelta;
    }
  }
  tt.ownTime += node->Data().meTime;

  return totalCalls;
}



static void DumpNode( CallGraphNode * node, int indent, int filenameWidth, IDumpCallback * callback, bool dumpFilenames, int leftBraces, int rightBraces )
{
  const SEventInfo & nodeInfo = GetControl()->GetEventInfo( node->Data().eventId );

  const char * cLeftBraces = "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{", * cRightBraces = "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}";
  const int bracesLimit = 32;
  NI_VERIFY( ( strlen( cLeftBraces ) == bracesLimit ) && ( strlen( cRightBraces ) == bracesLimit ), "", return );

  leftBraces = Min( leftBraces, bracesLimit );
  rightBraces = Min( rightBraces, bracesLimit );

  char text[1024] = "";
  NStr::Printf( text, sizeof( text ), "%*s%s: %.3f(%.3f) ms in %u call(s) %s%s", 
      indent * 2, "", 
      nodeInfo.name.c_str(),
      1e3 * node->Data().span, 1e3 * node->Data().meTime,
      node->Data().calls,
      cLeftBraces + bracesLimit - leftBraces, cRightBraces + bracesLimit - rightBraces );

  if ( dumpFilenames )
  {
    char location[256] = "";
    NStr::Printf( location, sizeof( location ), "%s(%d): ", nodeInfo.file.c_str(), nodeInfo.line );

    char buf[256 + 1024] = "";
    NStr::Printf( buf, sizeof( buf ), "%-*s%s", filenameWidth + 4, location, text );
    callback->DumpLine( buf );
  }
  else
    callback->DumpLine( text );
}



static void DumpCallgraphRecursive( CallGraphNode * node, int indent, int filenameWidth, IDumpCallback * callback, bool dumpFilenames, int rightBracesCount )
{
  DumpNode( node, indent, filenameWidth, callback, dumpFilenames, node->Subnodes().empty() ? 0 : 1, node->Subnodes().empty() ? rightBracesCount : 0 );

  vector<Strong<CallGraphNode> > sorted;
  sorted.reserve( node->Subnodes().size() );
  for ( TCallGraphNodes::const_iterator it = node->Subnodes().begin(); it != node->Subnodes().end(); ++it )
    sorted.push_back( it->second );

  for ( int i = 0; i < sorted.size(); ++i )
    for ( int j = i + 1; j < sorted.size(); ++j )
      if ( sorted[i]->Data().span < sorted[j]->Data().span )
        swap( sorted[i], sorted[j] );

  for ( int i = 0; i < sorted.size(); ++i )
  {
    int subRightBraces = ( i == sorted.size() - 1 ) ? ( rightBracesCount + 1 ) : 0;
    DumpCallgraphRecursive( sorted[i], indent + 1, filenameWidth, callback, dumpFilenames, subRightBraces );
  }
}



static void PrepareForDumpRecursive( CallGraphNode * node, int & maxFilenameLength )
{
  const SEventInfo & nodeInfo = GetControl()->GetEventInfo( node->Data().eventId );

  int len = nodeInfo.file.length();

  if ( nodeInfo.line < 10 )
    len += 1;
  else if ( nodeInfo.line < 100 )
    len += 2;
  else if ( nodeInfo.line < 1000 )
    len += 3;
  else
    len += 4;

  maxFilenameLength = Max( maxFilenameLength, len );

  for ( TCallGraphNodes::const_iterator it = node->Subnodes().begin(); it != node->Subnodes().end(); ++it )
  {
    int tmpMax = maxFilenameLength;
    PrepareForDumpRecursive( it->second, tmpMax );
    maxFilenameLength = Max( maxFilenameLength, tmpMax );
  }
}



static void DumpNodeTotals( TEventId eventId, const STotalEventInfo & totals, int filenameWidth, IDumpCallback * callback, bool dumpFilenames )
{
  const SEventInfo & nodeInfo = GetControl()->GetEventInfo( eventId );

  char text[1024];
  NStr::Printf( text, sizeof( text ), "  %s: %.3f (%.3f) ms, %d (%d) memory delta, %u allocs in %d calls",
        nodeInfo.name.c_str(), 1e3 * totals.time, 1e3 * totals.ownTime,
        totals.memoryDelta, totals.allocsDelta, totals.allocs,
        totals.calls );

  if ( dumpFilenames )
  {
    char location[256] = "";
    NStr::Printf( location, sizeof( location ), "%s(%d): ", nodeInfo.file.c_str(), nodeInfo.line );

    char buf[256 + 1024] = "";
    NStr::Printf( buf, sizeof( buf ), "%-*s%s", filenameWidth + 4, location, text );
    callback->DumpLine( buf );
  }
  else
    callback->DumpLine( text );
}



static void DumpLinearNodes( const TTotalEventInfos & totals, int filenameWidth, IDumpCallback * callback, bool dumpFilenames )
{
  vector<pair<TEventId, STotalEventInfo> > toSort;
  toSort.reserve( totals.size() );

  for ( TTotalEventInfos::const_iterator it = totals.begin(); it != totals.end(); ++it )
    toSort.push_back( pair<TEventId, STotalEventInfo>( it->first, it->second ) );

  enum ESortMode { eSortByTotalTime, eSortByOwnTotalTime, eSortByTotalCalls };
  static struct { ESortMode sortBy; const char * header; } sortModes[] =
  {
    { eSortByTotalTime, "total time" },
    { eSortByOwnTotalTime, "total own time" },
    { eSortByTotalCalls, "total calls" },
    { eSortByTotalTime, 0 },
  };

  for ( int modeIdx = 0; sortModes[modeIdx].header; ++modeIdx )
  {
    //FIXME: nstl::sort is a crippy sucks :-( bubbles rocks!
    //TODO: use adult STL
    for ( int i = 0; i < toSort.size(); ++i )
      for ( int j = i + 1; j < toSort.size(); ++j )
      {
        bool swapIt = false;
        if ( sortModes[modeIdx].sortBy == eSortByTotalTime )
        {
          if ( toSort[i].second.time < toSort[j].second.time )
            swapIt = true;
        }
        else if ( sortModes[modeIdx].sortBy == eSortByOwnTotalTime )
        {
          if ( toSort[i].second.ownTime < toSort[j].second.ownTime )
            swapIt = true;
        }
        else if ( sortModes[modeIdx].sortBy == eSortByTotalCalls )
        {
          if ( toSort[i].second.calls < toSort[j].second.calls )
            swapIt = true;
        }
        if ( swapIt )
          swap( toSort[i], toSort[j] );
      }

    callback->DumpLine( NI_STRFMT( "Dumping all %d nodes by %s:", toSort.size(), sortModes[modeIdx].header ) );

    for ( int i = 0; i < toSort.size(); ++i )
      DumpNodeTotals( toSort[i].first, toSort[i].second, filenameWidth, callback, dumpFilenames );
  }
}




Strong<CallGraphNode> CollectCallGraph( const ni_detail::Byte * data, size_t dataSize, TTotalEventInfos & totals, FTime timeFactor )
{
  NI_ASSERT( dataSize, "" );

  if ( 0 )
    DebugParseCallgraph( data, dataSize );

  Strong<CallGraphNodeImpl> rootNode;
  SRecord record;
  ParseCallgraph( rootNode, data, dataSize, record, 0 );

  vector<TEventId> callstack;
  callstack.reserve( 128 );
  unsigned calls = PostProcessCallgraph( rootNode, callstack, totals, timeFactor );
  rootNode->SetCalls( calls );

  return rootNode.Get();
}



void DumpCallgraph( CallGraphNode * node, const TTotalEventInfos & totals, IDumpCallback * callback, bool dumpFilenames )
{
  int filenameWidth = 0;
  PrepareForDumpRecursive( node, filenameWidth );

  DumpCallgraphRecursive( node, 0, filenameWidth, callback, dumpFilenames, 0 );

  DumpLinearNodes( totals, filenameWidth, callback, dumpFilenames );
}

} //namespace profiler3
