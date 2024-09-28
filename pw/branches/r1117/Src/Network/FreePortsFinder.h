#pragma once

namespace Network
{

class IFreePortsFinder : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IFreePortsFinder, IBaseInterfaceMT );
public:

  virtual int GetFreePort() = 0;
};

IFreePortsFinder * NewFreePortsFinder( int firstFreePort );

}
