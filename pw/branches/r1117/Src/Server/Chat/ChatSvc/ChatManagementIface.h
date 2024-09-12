#pragma once
#include <RPC/RPC.h>
#include <Network/Address.h>
#include <Network/TransportTypes.h>
#include <Network/LoginData.h>
#include <ClusterTypes/ClusterTypes.h>
#include <ChatTypes.h>

namespace chat
{
  namespace Result
  {
    enum Enum
    {
      ALREADY_EXISTS = -2,
      FAIL = -1,
      SUCCESS = 0,
      IN_PROGRESS = 1,
    };

    inline
    char const * const ToString(Enum err)
    {
      switch(err)
      {
      case FAIL:
        return "Ti kto takoi, davai dosvidaniya";
      case SUCCESS:
        return "Success";
      case IN_PROGRESS:
        return "In progress";
      default:
        return "Unknown error";
      }
    }
  }

  struct ChatUserInfo : public rpc::Data
  {
    SERIALIZE_ID();

    ZDATA
    ZNOPARENT(rpc::Data)
    chat::UserId userid_;
    chat::NickName nickname_;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&userid_); f.Add(3,&nickname_); return 0; }

    ChatUserInfo() : userid_(chat::INVALID_USER_ID) {}
  };
  typedef vector<ChatUserInfo> UserInfosT;

  struct ChannelInfo : public rpc::Data
  {
    SERIALIZE_ID();

    ZDATA
    ZNOPARENT(rpc::Data)
    wstring name_;
    UserInfosT users_;
    bool ignoreUserMute_;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&name_); f.Add(3,&users_); f.Add(4,&ignoreUserMute_); return 0; }

    ChannelInfo() {}
    ChannelInfo(wstring const & _name, bool const _ignoreUserMute = false)
      :name_(_name)
      ,ignoreUserMute_(_ignoreUserMute)
    {}
  };
  typedef vector<ChannelInfo> ChannelInfosT;

  struct SessionInfo : public rpc::Data
  {
    SERIALIZE_ID();

    ZDATA
    ZNOPARENT(rpc::Data)
    CustomId sidGlobal_;
    ChannelInfosT channels_;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&sidGlobal_); f.Add(3,&channels_); return 0; }

    SessionInfo()
      :sidGlobal_(chat::DEFAULT_CUSTOM_ID)
    {
    }

    SessionInfo(CustomId const & _sidGlobal)
      :sidGlobal_(_sidGlobal)
    {
    }
  };

  REMOTE class IOpenSessionCallback : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IOpenSessionCallback, IRemoteEntity );
    RPC_ID();

  public:
    REMOTE virtual void OnOpenSession(Result::Enum _rc, SessionId _sid) = 0;
  };

  REMOTE class IOpenChannelCallback : public rpc::IRemoteEntity
  {
    NI_DECLARE_CLASS_1( IOpenChannelCallback, IRemoteEntity );
    RPC_ID();

  public:
    REMOTE virtual void OnOpenChannel(Result::Enum _rc, SessionId _sid, ChannelId chnlid, CustomId _ctmid) = 0;
  };

  REMOTE class IChatManagement : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IChatManagement, IBaseInterfaceMT );
    RPC_ID();

  public:
    REMOTE virtual void OpenSession(chat::SessionInfo const & _si, NI_LPTR chat::IOpenSessionCallback* _cb) = 0;
    REMOTE virtual void CloseSession(chat::SessionId _sid) = 0;

    REMOTE virtual void OpenChannel(ChannelInfo const & _chinfo, chat::SessionId _sid, CustomId _ctmid, NI_LPTR chat::IOpenChannelCallback* _cb) = 0;
    REMOTE virtual void CloseChannel(ChannelId _chnlid, chat::SessionId _sid) = 0;

    REMOTE virtual Result::Enum AddUser2Channel(chat::CustomId _useridGlobal, chat::SessionId _sid, bool channelMuted, chat::ChannelName const & _chnlname) = 0;
    REMOTE virtual Result::Enum RemoveUser(chat::CustomId _useridGlobal, chat::SessionId _sid, chat::ChannelName const & _chnlname) = 0;
  };
}
