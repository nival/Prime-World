#include "stdafx.h"
#include <Network/Transport.h>
#include "RpcGate.h"
#include "System/InlineProfiler.h"
#include "System/ported/types.h"
#include "System/ported/cwfn.h"


NI_DEFINE_REFCOUNT(rpc::Gate);


namespace rpc
{

Gate::Gate(IPipeProcessor* _processor, int _threadCount):
pool(_threadCount),
_server(dataProcessing, _processor, pool)
{
}



Gate::~Gate()
{
}



StrongMT<Node> Gate::AddPipe( rpc::IPacketPipe * pipe, const GUID * id )
{
  return _server.AddNode(pipe, id);
}

void Gate::Poll()
{
  NI_PROFILE_FUNCTION;

  _server.Build();
}

} // rpc

