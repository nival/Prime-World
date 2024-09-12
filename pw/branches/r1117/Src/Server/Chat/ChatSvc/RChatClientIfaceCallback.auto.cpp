#include "stdafx.h"
#include "RChatClientIfaceCallback.auto.h"

DEFINE_RE_FACTORY( chat, RIChatClientCallback );

namespace rpc
{

template<>
void RegisterRemoteFactory(chat::RIChatClientCallback* factory)
{
  &factory_chat_RIChatClientCallback;
}

} // rpc

NI_DEFINE_REFCOUNT( chat::RIChatClientCallback )
