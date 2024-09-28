#ifndef LOBBYSERVERLOGINWRAPPER_H_INCLUDED
#define LOBBYSERVERLOGINWRAPPER_H_INCLUDED

#include "ILoginSvcWrapper.h"
#include "rpc/IfaceRequester.h"
#include <list>


namespace rpc
{
  class GateKeeper;
}

namespace Login
{
  class RISessionKeyRegister;
}


namespace clientCtl
{
  class RIInterface;
}

namespace lobby
{

class TcpLoginWrapper : public ISessionLoginWrapper, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( TcpLoginWrapper, ISessionLoginWrapper, BaseObjectMT);

public:
  TcpLoginWrapper( rpc::GateKeeper * _gateKeeper );

  void Poll();
  void AddSessionKey( const string & sessionLogin, const Transport::TServiceId & sessionPath, const string & zzLogin, int zzUserId, Cluster::TGameId gameid, Login::IAddSessionKeyCallback * callback );

private:
  StrongMT<rpc::IfaceRequester<Login::RISessionKeyRegister>> loginSvc;
};




class RdpLoginWrapper : public ISessionLoginWrapper, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( RdpLoginWrapper, ISessionLoginWrapper, BaseObjectMT);

public:
  RdpLoginWrapper( rpc::GateKeeper * _gateKeeper );

  void Poll();
  void AddSessionKey( const string & sessionLogin, const Transport::TServiceId & sessionPath, const string & zzLogin, int zzUserId, Cluster::TGameId gameid, Login::IAddSessionKeyCallback * callback );

private:
  class Request;

  typedef std::list<StrongMT<Request> > Requests;

  StrongMT<rpc::IfaceRequester<clientCtl::RIInterface>> clientControl;
  Requests requests;
};

} //namespace lobby

#endif //LOBBYSERVERLOGINWRAPPER_H_INCLUDED
