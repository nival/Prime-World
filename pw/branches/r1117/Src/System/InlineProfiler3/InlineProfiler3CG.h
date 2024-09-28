#ifndef INLINEPROFILER3CG_H_INCLUDED
#define INLINEPROFILER3CG_H_INCLUDED

#include "InlineProfiler3Control.h"

namespace profiler3
{

//FXIME: Move to .cpp ?
class CallGraphNodeImpl : public CallGraphNode
{
  NI_DECLARE_REFCOUNT_CLASS_1( CallGraphNodeImpl, CallGraphNode );

public:
  explicit CallGraphNodeImpl( TEventId _eventId ) :
  CallGraphNode( _eventId ),
  spanInTicks()
  {}

  Strong<CallGraphNode> & MapSubnode( TEventId eventId ) { return subnodes[eventId]; }

  void Add( TTime _spanInTicks ) {
    spanInTicks += _spanInTicks;
    ++data.calls;
  }

  void CalculateSpan( FTime cpuTicksRate ) {
    data.span = spanInTicks / cpuTicksRate;
  }

  void SetMeTime( FTime _meTime ) {
    data.meTime = _meTime;
  }

  void SetCalls( unsigned _calls ) {
    data.calls = _calls;
  }

  void AddMemory( unsigned allocs, int allocsDelta, int memoryDelta ) {
    data.hasAllocsInfo = true;
    data.allocs += allocs;
    data.allocsDelta += allocsDelta;
    data.memoryDelta += memoryDelta;
  }

private:
  TTime spanInTicks;
};



Strong<CallGraphNode> CollectCallGraph( const ni_detail::Byte * data, size_t dataSize, TTotalEventInfos & totals, FTime timeFactor );
void DumpCallgraph( CallGraphNode * node, const TTotalEventInfos & totals, IDumpCallback * callback, bool dumpFilenames );

} //namespace profiler3

#endif //INLINEPROFILER3CG_H_INCLUDED
