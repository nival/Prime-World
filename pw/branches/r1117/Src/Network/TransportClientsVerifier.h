#pragma once
#include "TransportAddress.h"
#include "TransportLoginData.h"

namespace Transport
{
  struct IClientsVerifier : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1(IClientsVerifier, IBaseInterfaceMT);
    virtual bool VerifyNewClientConnected( int userId, const TLoginData& loginData ) = 0; 
    virtual void NotifyClientDisconnected( int userId ) = 0;
    virtual void Step() = 0;
  };
}
