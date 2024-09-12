#include "stdafx.h"
#include "RChatManagementIface.auto.h"

DEFINE_RE_FACTORY( chat, RIOpenSessionCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(chat::RIOpenSessionCallback* factory)
{
  &factory_chat_RIOpenSessionCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( chat::RIOpenSessionCallback )
DEFINE_RE_FACTORY( chat, RIOpenChannelCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(chat::RIOpenChannelCallback* factory)
{
  &factory_chat_RIOpenChannelCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( chat::RIOpenChannelCallback )
DEFINE_RE_FACTORY( chat, RIChatManagement );

namespace rpc
{

template<>
void RegisterRemoteFactory(chat::RIChatManagement* factory)
{
  &factory_chat_RIChatManagement;
}

} // rpc

NI_DEFINE_REFCOUNT( chat::RIChatManagement )
