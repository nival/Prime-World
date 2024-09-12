#pragma once

namespace NCore
{
  struct ClientStatus;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
  _interface ISessionRunner : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1(ISessionRunner, IBaseInterfaceMT);
    virtual void ProcessAsyncMessage( IObjectBase *pMsg ) = 0;
    virtual void ProcessAsyncStatus( ClientStatus & status ) = 0;
  };

}