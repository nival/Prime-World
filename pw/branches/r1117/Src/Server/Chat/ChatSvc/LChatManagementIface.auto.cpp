#include "stdafx.h"
#include "LChatManagementIface.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace chat
{




    bool LIOpenSessionCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("chat::IOpenSessionCallback::OnOpenSession/0");rpc::VCall( stack, localObject.Get(), &chat::IOpenSessionCallback::OnOpenSession, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(chat::IOpenSessionCallback* api, rpc::IEntityMap* entityMap)
{
  return new chat::LIOpenSessionCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( chat::LIOpenSessionCallback )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace chat
{




    bool LIOpenChannelCallback::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("chat::IOpenChannelCallback::OnOpenChannel/0");rpc::VCall( stack, localObject.Get(), &chat::IOpenChannelCallback::OnOpenChannel, popResult); } break;

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
rpc::ILocalEntity* CreateLocalEntity(chat::IOpenChannelCallback* api, rpc::IEntityMap* entityMap)
{
  return new chat::LIOpenChannelCallback(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( chat::LIOpenChannelCallback )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace chat
{


	typedef void (chat::IChatManagement::*TOpenSession)( chat::SessionInfo const * _si, NI_LPTR chat::IOpenSessionCallback* _cb);
	typedef void (chat::IChatManagement::*TOpenChannel)( ChannelInfo const * _chinfo, chat::SessionId _sid, CustomId _ctmid, NI_LPTR chat::IOpenChannelCallback* _cb);
	typedef Result::Enum (chat::IChatManagement::*TAddUser2Channel)( chat::CustomId _useridGlobal, chat::SessionId _sid, bool channelMuted, chat::ChannelName const * _chnlname);
	typedef Result::Enum (chat::IChatManagement::*TRemoveUser)( chat::CustomId _useridGlobal, chat::SessionId _sid, chat::ChannelName const * _chnlname);


    bool LIChatManagement::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("chat::IChatManagement::OpenSession/0");rpc::VCall( stack, localObject.Get(), TOpenSession(&chat::IChatManagement::OpenSession), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("chat::IChatManagement::CloseSession/1");rpc::VCall( stack, localObject.Get(), &chat::IChatManagement::CloseSession, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("chat::IChatManagement::OpenChannel/2");rpc::VCall( stack, localObject.Get(), TOpenChannel(&chat::IChatManagement::OpenChannel), popResult); } break;
			case 3: { NI_PROFILE_BLOCK("chat::IChatManagement::CloseChannel/3");rpc::VCall( stack, localObject.Get(), &chat::IChatManagement::CloseChannel, popResult); } break;
			case 4: { NI_PROFILE_BLOCK("chat::IChatManagement::AddUser2Channel/4");
			{
				Result::Enum result = rpc::VCall( stack, localObject.Get(), TAddUser2Channel(&chat::IChatManagement::AddUser2Channel), popResult); 
				call.Prepare(4).PushByValue(result);
			}
			} break;
			case 5: { NI_PROFILE_BLOCK("chat::IChatManagement::RemoveUser/5");
			{
				Result::Enum result = rpc::VCall( stack, localObject.Get(), TRemoveUser(&chat::IChatManagement::RemoveUser), popResult); 
				call.Prepare(5).PushByValue(result);
			}
			} break;

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
rpc::ILocalEntity* CreateLocalEntity(chat::IChatManagement* api, rpc::IEntityMap* entityMap)
{
  return new chat::LIChatManagement(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( chat::LIChatManagement )


