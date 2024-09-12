#pragma once
#include "UserManagerSvc/UserEnvInfo.h"

namespace UserManager
{
  class IUserRegister : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IUserRegister, IBaseInterfaceMT );

  public:
    virtual int RegisterUser(UserEnvInfo const & _uei) = 0;
    virtual bool IsUserRegistered(Cluster::TUserId const & _userId) = 0;
    virtual int UnregisterUser(Cluster::TUserId const & _userId) = 0;
  };
}
