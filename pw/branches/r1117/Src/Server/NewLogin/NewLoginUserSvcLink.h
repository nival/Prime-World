#ifndef NEWLOGINUSERSVCLINK_H_INCLUDED
#define NEWLOGINUSERSVCLINK_H_INCLUDED

#include "NewLoginTypes.h"
#include "RdpTransport/RdpFrontendAgentRemote.h"
#include "NewLoginConfig.h"
#include "System/NiTimer.h"


namespace rdp_transport
{
  class IFrontendAgent;
  class PacketWriter;
}


namespace newLogin
{

class ISvcLinkDict;
class ISvcLink;

class UserSvcLink : public rdp_transport::IFrontendAgentRemote, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( UserSvcLink, rdp_transport::IFrontendAgentRemote, BaseObjectMT );

public:
  UserSvcLink( IConfigProvider * _config, ISvcLink * _link, rdp_transport::PacketWriter * _writer, const ServiceRequest & _data, Transport::TClientId _uid, const string & _login );

  const ServiceRequest & Data() const { return data; }

  bool Poll( timer::Time _now );

  void KickUser();

  static void SendReply( rdp_transport::PacketWriter * _writer, const ServiceRequest & _req, ESvcConnectionResult::Enum _code, const char * _addr, const char * _key );

protected:
  //rdp_transport::IFrontendAgentRemote
  virtual void UserPrepared( Transport::TClientId _uid );
  virtual void UserConnected( Transport::TClientId _uid );
  virtual void UserTimedOut( Transport::TClientId _uid );
  virtual void UserKicked( Transport::TClientId _uid );
  virtual void UserDropped( Transport::TClientId _uid );

private:
  struct EState
  {
    enum Enum {
      WaitingSvcLink,
      PreparingUser,
      WaitingSvcAck,
      Active,
      KickingUser,
      Closed,
    };
  };

  const ServiceRequest                    data;
  const Transport::TClientId              uid;
  const string                            login;
  EState::Enum                            state;
  WeakMT<ISvcLink>                        link;
  StrongMT<rdp_transport::PacketWriter>   writer;
  timer::MemberPtrTimer<UserSvcLink>      timeout;
  string                                  key;
  string                                  frontendAddr;

  void Switch( EState::Enum _st );
  void OnTimeout();
  void Close();
  void SetupKey();
};

} //namespace newLogin

#endif //NEWLOGINUSERSVCLINK_H_INCLUDED
