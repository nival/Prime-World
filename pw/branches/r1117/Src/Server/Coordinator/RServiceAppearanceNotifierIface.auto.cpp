#include "stdafx.h"
#include "RServiceAppearanceNotifierIface.auto.h"

DEFINE_RE_FACTORY( Coordinator, RIServiceAppearanceSubscriber );

namespace rpc
{

template<>
void RegisterRemoteFactory(Coordinator::RIServiceAppearanceSubscriber* factory)
{
  &factory_Coordinator_RIServiceAppearanceSubscriber;
}

} // rpc

NI_DEFINE_REFCOUNT( Coordinator::RIServiceAppearanceSubscriber )
DEFINE_RE_FACTORY( Coordinator, RIServiceAppearancePublisher );

namespace rpc
{

template<>
void RegisterRemoteFactory(Coordinator::RIServiceAppearancePublisher* factory)
{
  &factory_Coordinator_RIServiceAppearancePublisher;
}

} // rpc

NI_DEFINE_REFCOUNT( Coordinator::RIServiceAppearancePublisher )
