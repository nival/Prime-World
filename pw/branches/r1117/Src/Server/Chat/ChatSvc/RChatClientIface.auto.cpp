#include "stdafx.h"
#include "RChatClientIface.auto.h"

DEFINE_RE_FACTORY( chat, RIChatClient );

namespace rpc
{

template<>
void RegisterRemoteFactory(chat::RIChatClient* factory)
{
  &factory_chat_RIChatClient;
}

} // rpc

NI_DEFINE_REFCOUNT( chat::RIChatClient )
