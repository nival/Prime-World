#include "GameChatController/stdafx.h"
#include "GameChatController/GameChatContext.h"

NI_DEFINE_REFCOUNT(gamechat::GameChatContext);

namespace gamechat
{
  GameChatContext::GameChatContext()
    :gameid_(INVALID_GAME_SESSION_ID),
    sid_(chat::INVALID_SESSION_ID)
  {
  }

  GameChatContext::GameChatContext(GameSessionId const & _gameid, IOpenGameChatCallback * _cb)
    :gameid_(_gameid),
    cb_(_cb)
  {
  }

  GameChatContext::~GameChatContext()
  {
  }

  void GameChatContext::OnOpenSession(chat::Result::Enum _rc, chat::SessionId _sid)
  {
    LOG_M(CHATCTRLLOG).Trace("%s(rc=%d gameid=%016x sid=%d)", __FUNCTION__, (int)_rc, gameid_, _sid);

    if (_rc < 0)
    {
      LOG_E(CHATCTRLLOG).Trace("%s: open session FAILED(rc=%d gameid=%016x sid=%d)", __FUNCTION__, (int)_rc, gameid_, _sid);
    }
    else
    {
      sid_ = _sid;
      if ( StrongMT<IOpenGameChatCallback> locked = cb_.Lock() )
        locked->OnOpenSessionChat(gameid_, _rc);
    }
  }

  void GameChatContext::OnAddUser2Channel(chat::Result::Enum _rc, GameSessionId _gameid, rpc::CallStatus _rpcsts)
  {
    LOG_M(CHATCTRLLOG).Trace("%s(rc=%d gameid=%016x sid=%d rpcsts=%d)", __FUNCTION__, (int)_rc, _gameid, sid_, (int)_rpcsts);

    NI_ASSERT(gameid_ == _gameid, "");

    if (_rpcsts != rpc::CallSuccessful)
    {
      LOG_E(CHATCTRLLOG).Trace("%s. RPC call FAILED(rpcsts=%d gameid=%016x sid=%d)", __FUNCTION__, (int)_rpcsts, _gameid, sid_);
      return;
    }

    if (_rc < 0)
    {
      LOG_E(CHATCTRLLOG).Trace("%s. Add user to channel FAILED(rc=%d gameid=%016x sid=%d)", __FUNCTION__, (int)_rc, _gameid, sid_);
    }
  }
}
