#ifndef NEWLOGIN_CLIENTAUTHINTERFACE_H_INCLUDED
#define NEWLOGIN_CLIENTAUTHINTERFACE_H_INCLUDED

#include "NewLoginTypes.h"

namespace newLogin
{

class IClientAuth : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IClientAuth, IBaseInterfaceMT );

public:
  virtual void AuthorizeClient( LoginReply & _reply, const LoginHello & _hello ) = 0;
};

} //namespace newLogin

#endif //NEWLOGIN_CLIENTAUTHINTERFACE_H_INCLUDED
