#pragma once

#include "json/reader.h"
#include "json/writer.h"
#include "Server/LobbySocial/SocialLobbyTypes.h"
#include "Server/LobbySocial/ISocialLobbyNotify.h"
#include "system/SpinLock.h"

namespace socialLobby
{
  class RISocialLobby;
}

namespace HttpGateway
{

class PingContext;

namespace EContextState
{
  enum Enum
  {
    New,
    ApprovedByLobby,
    Restored,
    Condemned
  };
}


class PingContext : public BaseObjectMT, public socialLobby::INotify
{
  NI_DECLARE_REFCOUNT_CLASS_2( PingContext, BaseObjectMT, socialLobby::INotify );

public:
  static socialLobby::TUId StrToUid( const char * str );

  PingContext( timer::Time _now, socialLobby::TUId _uid, const char * _sessionId, EContextState::Enum _ctxState, socialLobby::ERequestStatus::Enum _initialStatus );

  bool ResetRestored( timer::Time _now, const char * _sessionId, EContextState::Enum _ctxState, socialLobby::ERequestStatus::Enum _status );

  socialLobby::TUId Uid() const { return uid; }
  const std::string & UidString() const { return uidString; }
  EContextState::Enum CtxState() const;

  void Condemn();
  std::string SessionId();

  void RenewLastAcessTime( timer::Time _now );
  bool Poll( timer::Time _now );

  //Json processing
  void HandlePingRequest( Json::Value & pvxReply );
  void HandleLeaveRequest();
  void HandleReconnectRequest();
  bool HandleAcceptRequest( const socialLobby::SPlayerData & playerData );
  bool HandleHeroChangeRequest( const socialLobby::SPlayerData & playerData );
  bool HandleGuardReadyRequest();
  void HandleCancelRequest( bool partyCancel );

private:
  const socialLobby::TUId     uid;
  const std::string           uidString;
  EContextState::Enum         ctxState;
  StrongMT<socialLobby::IUserContext> lobbyCtx;
  timer::Time                 creationTime;
  timer::Time                 now;
  timer::Time                 lastPingTime;
  timer::Time                 lastUpdateTime;
  threading::SpinLock         mutex;
  socialLobby::SMatchmakingStatus data;

  //socialLobby::INotify
  virtual void Open( socialLobby::IUserContext * _ctx );
  virtual void Failure();
  virtual void UpdateStatus( const socialLobby::SMatchmakingStatus & _status );
  virtual void Close();

  void _ChangeState( EContextState::Enum _st );
  void _Condemn();
};

} //namespace HttpGateway
