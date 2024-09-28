#include "StdAfx.h"
#include "BinSaverStatsCollector.h"
#include "InlineProfiler3\InlineProfilerTLD.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline BinSaverStatsCollector::TTickCount BinSaverStatsCollector::GetCpuTickCount()
{
  return profiler3::ThreadLocalData::GetCpuTickCount();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline double BinSaverStatsCollector::TickToMSec( TTickCount tc )
{
  return double(tc) / 2000; //Примерное значение времени, нам нужны относительные значения
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinSaverStatsCollector::Reset()
{
  ResetRecursive( root );
  
  callStack.clear();
  callStack.push_back( StackItem(&root, GetCpuTickCount()) );
  
  isDataGathering = false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinSaverStatsCollector::ResetRecursive( ChildredNodes::value_type &cur )
{
  if( cur.second.pChildren != 0)
  {
    for( ChildredNodes::iterator it = cur.second.pChildren->begin(); it != cur.second.pChildren->end(); ++it )
      ResetRecursive(*it);
      
    delete cur.second.pChildren;
    cur.second.pChildren = 0;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinSaverStatsCollector::StartTypeImpl( const std::type_info &ti )
{
  if( !isDataGathering ) return;

  NI_ASSERT( !callStack.empty(), "" );
  
  ChildredNodes *&pChildren = callStack.back().pNode->second.pChildren;
  
  if( pChildren == 0 )
    pChildren = new ChildredNodes;
  
  const ChildredNodes::key_type key( ti );
  
  //Оптимизация: Ищем только один раз
  ChildredNodes::iterator it = pChildren->lower_bound(key);
  
  if( it != pChildren->end() && !pChildren->key_comp()(key, it->first) )
    ++it->second.count;
  else
    it = pChildren->insert( it, ChildredNodes::value_type(key, Node()) );

  callStack.push_back( StackItem(&*it, GetCpuTickCount()) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinSaverStatsCollector::FinishTypeImpl( const std::type_info &ti )
{
  if( !isDataGathering ) return;
  
  NI_ASSERT( !callStack.empty(), "" );
  NI_ASSERT( callStack.back().pNode->first == ti, "" );
  
    
  callStack.back().pNode->second.workedTime += 
    GetCpuTickCount() - callStack.back().startTypeTime;
    
  callStack.pop_back();
  
  NI_ASSERT( !callStack.empty(), "" );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinSaverStatsCollector::DataWrited( size_t size )
{
  if( !isDataGathering ) return;
  
  NI_ASSERT( !callStack.empty(), "" );
  callStack.back().pNode->second.selfSize += size;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

size_t BinSaverStatsCollector::CollectDataRecursive( ChildredNodes::value_type &cur )
{
  size_t childrenSize = 0;

  if( cur.second.pChildren != 0 )
    for( ChildredNodes::iterator it = cur.second.pChildren->begin(); it != cur.second.pChildren->end(); ++it )
      childrenSize += CollectDataRecursive(*it);

  return cur.second.totalSize = cur.second.selfSize + childrenSize;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinSaverStatsCollector::CollectSize()
{
  NI_ASSERT( isDataGathering, "" );
  NI_ASSERT( callStack.size() == 1, "" );
  NI_ASSERT( callStack.back().pNode == &root, "" );
  NI_ASSERT( root.second.count == 1, "" );
  
  CollectDataRecursive( root );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinSaverStatsCollector::FlatterProfileRecursive( const ChildredNodes::value_type &cur, FlateredNodes &out ) const
{
  if( cur.second.pChildren != 0 )
    for( ChildredNodes::const_iterator it = cur.second.pChildren->begin(); it != cur.second.pChildren->end(); ++it )
      FlatterProfileRecursive( *it, out );

  FlateredNodes::iterator it = out.lower_bound(cur.first);

  if( it != out.end() && !out.key_comp()(cur.first, it->first) )
    it->second += cur.second;
  else
    out.insert( it, ChildredNodes::value_type(cur.first, cur.second) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinSaverStatsCollector::DumpData() 
{
  NI_ASSERT( isDataGathering, "" );
  
  DebugTrace( "------------------------------" );
  
  CollectSize();
  DumpDataRecursize( 0, root );
  
  DebugTrace( "------------------------------" );
  
  FlateredNodes flateredNodes;
  DebugTrace( "name;count;totalSize;selfSize;time;" );
  FlatterProfileRecursive( root, flateredNodes );
  DumpFlattered( flateredNodes );
  
  DebugTrace( "------------------------------" );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinSaverStatsCollector::DumpFlattered( const FlateredNodes &flatNodes ) const
{
  for( FlateredNodes::const_iterator it = flatNodes.begin(); it !=  flatNodes.end(); ++it )
  {
    DebugTrace( "%s;%u;%u;%u;%.3f;",
      it->first.name(), it->second.count, it->second.totalSize, it->second.selfSize,
      TickToMSec(it->second.workedTime)
    );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinSaverStatsCollector::DumpDataRecursize( int level, const ChildredNodes::value_type &cur ) const
{  
  DebugTrace( "%*sN %7u S %7u(%u) T %10.3f %s %s", level * 2, "", 
    cur.second.count, cur.second.totalSize, cur.second.selfSize,
    TickToMSec(cur.second.workedTime),
    cur.first.name(),
    cur.second.pChildren != 0 ? " {" : "" 
  );
  
  if( cur.second.pChildren != 0 )
  {
    for( ChildredNodes::const_iterator it = cur.second.pChildren->begin(); it != cur.second.pChildren->end(); ++it )
      DumpDataRecursize( level + 1, *it );
      
    DebugTrace( "%*s}", level * 2, "" );
  }
  
  //Убрать префикс строк в Notepad++:
  //  "\.\\BinSaverStatsCollector\.cpp\(\d+\): d: "
}
