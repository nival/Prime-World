#include "stdafx.h"
#include "LChatClientIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace chat
{


	typedef int (chat::IChatClient::*TRegisterUser)( chat::CustomId _sidGlobal, chat::CustomId _useridGlobal, chat::NickName const * _nickname, NI_LPTR IChatClientCallback* _cb);
	typedef void (chat::IChatClient::*TSendMsg)( chat::SessionId _sid, chat::ChannelName const * _chnlname, chat::UserId _from, wstring const * _msg);


    bool LIChatClient::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("chat::IChatClient::RegisterUser/0");
			{
				int result = rpc::VCall( stack, localObject.Get(), TRegisterUser(&chat::IChatClient::RegisterUser), popResult); 
				call.Prepare(0).Push(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("chat::IChatClient::SendMsg/1");rpc::VCall( stack, localObject.Get(), TSendMsg(&chat::IChatClient::SendMsg), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("chat::IChatClient::UnregisterUser/2");rpc::VCall( stack, localObject.Get(), &chat::IChatClient::UnregisterUser, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(chat::IChatClient* api, rpc::IEntityMap* entityMap)
{
  return new chat::LIChatClient(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( chat::LIChatClient )


