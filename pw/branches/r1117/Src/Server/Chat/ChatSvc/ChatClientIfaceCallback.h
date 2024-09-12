#pragma once
#include <RPC/RPC.h>
#include <ChatTypes.h>

namespace chat
{
  REMOTE class IChatClientCallback : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IChatClientCallback, IRemoteEntity );
    RPC_ID();

  public:
    REMOTE virtual void OnRegisterUser(SessionId _sid, UserId _userid, int _rc) = 0;
    REMOTE virtual void OnJoinChannel(SessionId _sid, const ChannelName &_chnlname) = 0;
    REMOTE virtual void OnNewMessage(SessionId _sid, const ChannelName &_chnlname, const NickName &_nickname, CustomId _useridGlobal, const wstring &_sourceMsg, const wstring &_fiteredMsg) = 0;
  };
}
