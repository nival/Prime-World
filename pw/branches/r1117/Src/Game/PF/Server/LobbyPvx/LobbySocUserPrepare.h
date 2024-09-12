#ifndef LOBBYSOCUSERPREPARE_H_INCLUDED
#define LOBBYSOCUSERPREPARE_H_INCLUDED

#include "Server/LobbySocial/SocialLobbyTypes.h"
#include "Network/SessionKeyRegisterIface.h"
#include "LobbyConfig.h"


namespace lobby
{

struct SSocialUserPrepare
{
  socialLobby::TUserIdPvX   pvxUid;
  string                    login;
  Cluster::TGameId          gameId;

  SSocialUserPrepare() :
  pvxUid( 0 ),
  gameId(Cluster::INVALID_GAME_ID)
  {}
};


class ISessionLoginWrapper;


namespace ESocUserPreparation
{
  enum Enum { Initial, WaitingAnswer, Done, Failed };
}

class SocUserPrepareItem : public Login::IAddSessionKeyCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SocUserPrepareItem, Login::IAddSessionKeyCallback, BaseObjectMT );

public:
  SocUserPrepareItem( const Transport::TServiceId & _svcId, const SSocialUserPrepare & _data, timer::Ticks _startTicks ) :
  serviceId( _svcId ),
  data( _data ),
  startTicks( _startTicks ),
  state( ESocUserPreparation::Initial ),
  loginAckTimeout( 0 )
  {}

  const SSocialUserPrepare & Data() const { return data; }
  const string & Key() const { return key; }

  ESocUserPreparation::Enum Poll( ISessionLoginWrapper * loginSvcAgent, timer::Time now );

private:
  const Transport::TServiceId serviceId;
  const SSocialUserPrepare    data;
  const timer::Ticks          startTicks;
  ESocUserPreparation::Enum   state;
  string                      key;
  string                      tmpPassword;
  timer::Time                 now;
  timer::Time                 loginAckTimeout;

  void CreateSessionKey( ISessionLoginWrapper * loginSvcAgent );

  //Login::IAddSessionKeyCallback
  virtual void OnAddSessionKey( int _rc, const  nstl::string & _loginSvcAddr, Cluster::TUserId _userid );
};

} //namespace lobby

#endif //LOBBYSOCUSERPREPARE_H_INCLUDED
