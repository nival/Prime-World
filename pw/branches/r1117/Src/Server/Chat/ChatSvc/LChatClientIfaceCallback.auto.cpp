#include "stdafx.h"
#include "LChatClientIfaceCallback.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace chat
{


	typedef void (chat::IChatClientCallback::*TOnJoinChannel)( SessionId _sid, const ChannelName* _chnlname);
	typedef void (chat::IChatClientCallback::*TOnNewMessage)( SessionId _sid, const ChannelName* _chnlname, const NickName* _nickname, CustomId _useridGlobal, const wstring* _sourceMsg, const wstring* _fiteredMsg);


    bool LIChatClientCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("chat::IChatClientCallback::OnRegisterUser/0");rpc::VCall( stack, localObject.Get(), &chat::IChatClientCallback::OnRegisterUser, popResult); } break;
			case 1: { NI_PROFILE_BLOCK("chat::IChatClientCallback::OnJoinChannel/1");rpc::VCall( stack, localObject.Get(), TOnJoinChannel(&chat::IChatClientCallback::OnJoinChannel), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("chat::IChatClientCallback::OnNewMessage/2");rpc::VCall( stack, localObject.Get(), TOnNewMessage(&chat::IChatClientCallback::OnNewMessage), popResult); } break;

        default:
            popResult = false;
            break;
        }
        return popResult;
    }

}


namespace rpc
{
template<>
rpc::ILocalEntity* CreateLocalEntity(chat::IChatClientCallback* api, rpc::IEntityMap* entityMap)
{
  return new chat::LIChatClientCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( chat::LIChatClientCallback )


