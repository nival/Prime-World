#include "stdafx.h"
#include "RDebugVarReporter.auto.h"

DEFINE_RE_FACTORY( NDebug, RDebugVarReporter );

namespace rpc
{

template<>
void RegisterRemoteFactory(NDebug::RDebugVarReporter* factory)
{
  &factory_NDebug_RDebugVarReporter;
}

} // rpc

NI_DEFINE_REFCOUNT( NDebug::RDebugVarReporter )
