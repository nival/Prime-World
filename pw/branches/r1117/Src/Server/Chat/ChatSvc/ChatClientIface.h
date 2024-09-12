#pragma once
#include <Server/Chat/ChatSvc/ChatClientIfaceCallback.h>

namespace chat
{
  REMOTE class IChatClient : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IChatClient, IBaseInterfaceMT );
    RPC_ID();

  public:
    REMOTE virtual int RegisterUser(chat::CustomId _sidGlobal, chat::CustomId _useridGlobal, chat::NickName const & _nickname, NI_LPTR IChatClientCallback* _cb) = 0;
    REMOTE virtual void SendMsg(chat::SessionId _sid, chat::ChannelName const & _chnlname, chat::UserId _from, wstring const & _msg) = 0;
    REMOTE virtual void UnregisterUser(chat::CustomId _sidGlobal, chat::UserId _useridLocal) = 0;
  };
}
