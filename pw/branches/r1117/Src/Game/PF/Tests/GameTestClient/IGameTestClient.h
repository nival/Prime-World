#pragma once

#include "network/TransportTypes.h"

namespace GtcSocial
{
  class SocialClient;
}

namespace gtc
{

namespace Stage
{
  enum
  {
    NONE,
    INVALID,

    LOGIN_STARTED,
    LOGIN_FINISHED,
    LOGIN_WAIT_AFTER,

    CHAT_START,
    CHAT_START_WAIT,
    CHAT_SEND,
    CHAT_LOOPBACK_WAIT,

    STATISTICS_START,
    STATISTICS_START_WAIT,
    STATISTICS_SEND,
    STATISTICS_SEND_WAIT,
    STATISTICS_FINISH,

    LOBBY_ENTERING,
    LOBBY_CONNECTED,
    LOBBY_WAITING_MM,

    REQ_MATCH_MAKING_MANAGER_STARTED,
    REQ_MATCH_MAKING_MANAGER_FINISHED,
    REQ_MATCH_MAKING_STARTED,
    REQ_MATCH_MAKING_FINISHED,
    MATCH_MAKING_COMPLETED,
    PLAYER_READY_TO_PLAY,
    GAME_STARTING,
    JOIN_GAME_SESSION_STARTED,
    JOIN_GAME_SESSION_FINISHED,
    LOAD_MAP_STARTED,
    LOAD_MAP_FINISHED,
    CLIENT_READY_TO_PLAY,
    GAME,
    GAME_SESSION_FINISHED,
    REQ_RPC_TEST_ECHO_SRV_STARTED,
    REQ_RPC_TEST_ECHO_SRV_FINISHED,
    RPC_SEQUENCE_TEST_CALL_STARTED,
    RPC_SEQUENCE_TEST_CALL_FINISHED,
    //SERVER_OBJ_REQ_STARTED,
    //SERVER_OBJ_REQ_FINISHED,
    //REGISTER_CLIENT_STARTED,
    //REGISTER_CLIENT_FINISHED,
    //CLIENT_ONLINE = REGISTER_CLIENT_FINISHED,
  };
};



namespace Result
{
  enum 
  {
    NONE = -1,
    SUCCESS = 0,
    FAIL,
    IN_PROGRESS
  };
};



class StepResult
{
public:
  StepResult() : handled( false ), ok( true ) {}
  StepResult( bool _handled, bool _ok ) : handled( _handled ), ok( _ok ) {}
  void Failed() { ok = false; }
  void Handle() { handled = true; }
  bool Ok() const { return ok; }
  bool Handled() const { return handled; }
private:
  bool  handled;
  bool  ok;
};



class StepResultOk : public StepResult {
public:
  StepResultOk() : StepResult( true, true ) {}
};



class IGameTestClient : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IGameTestClient, IBaseInterfaceMT );

public:
  virtual StepResult MainStep() = 0;
  virtual void TerminatePvx() = 0;
  virtual int Stage() const = 0;
  virtual Transport::TClientId UserId() const = 0;

  //FIXME: it should be in lobby-specific class
  virtual void SetSocialClient( GtcSocial::SocialClient * _socClient ) = 0;
  virtual GtcSocial::SocialClient * SocialClient() const  = 0;
};

}; //namespace gtc
