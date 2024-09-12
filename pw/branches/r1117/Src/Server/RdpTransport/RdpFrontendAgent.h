#ifndef RDPFRONTENDAGENT_H_INCLUDED
#define RDPFRONTENDAGENT_H_INCLUDED

#include "RdpFrontendAgentInterface.h"
#include "Network/Transport.h"
#include <map>

namespace rdp_transport
{

class FrontendAgent : public IFrontendAgent, public Transport::IFrontendTransportAuth, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( FrontendAgent, IFrontendAgent, BaseObjectMT );

public:
  FrontendAgent( timer::Time _now );

  void Poll( timer::Time _now );

  bool GetActiveUserLogin( Transport::TClientId _uid, string & _login );

protected:
  //IFrontendAgent
  virtual void PrepareUser( Transport::TClientId _uid, const string & _login, const string & _key, IFrontendAgentRemote * _callback );
  virtual void KickUser( Transport::TClientId _uid );

  //IFrontendTransportAuth
  virtual bool AuthorizeUser( Transport::TClientId _uid, const string & _key, Transport::IFrontendTransportKickCallback * _cb );

private:
  struct UserCtx : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( UserCtx, BaseObjectST );
  public:
    UserCtx( IFrontendAgentRemote * _cb, const string & _login, const string & _key, timer::Time _now ) :
    login( _login ),
    callback( _cb ),
    key( _key ),
    created( _now ),
    authorized( false )
    {}

    const string                    login;
    StrongMT<IFrontendAgentRemote>  callback;
    WeakMT<Transport::IFrontendTransportKickCallback> kickCallback;
    string                          key;
    timer::Time                     created;
    bool                            authorized;
  };

  typedef std::map<Transport::TClientId, Strong<UserCtx> >  Users;

  threading::Mutex mutex;
  Users   users;
  timer::Time now;
};

}; //namespace rdp_transport

#endif //RDPFRONTENDAGENT_H_INCLUDED
