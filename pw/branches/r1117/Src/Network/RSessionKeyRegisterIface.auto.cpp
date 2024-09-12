#include "stdafx.h"
#include "RSessionKeyRegisterIface.auto.h"

DEFINE_RE_FACTORY( Login, RIAddSessionKeyCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(Login::RIAddSessionKeyCallback* factory)
{
  &factory_Login_RIAddSessionKeyCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( Login::RIAddSessionKeyCallback )
DEFINE_RE_FACTORY( Login, RISessionKeyRegister );

namespace rpc
{

template<>
void RegisterRemoteFactory(Login::RISessionKeyRegister* factory)
{
  &factory_Login_RISessionKeyRegister;
}

} // rpc

NI_DEFINE_REFCOUNT( Login::RISessionKeyRegister )
