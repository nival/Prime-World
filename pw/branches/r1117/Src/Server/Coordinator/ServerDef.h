#pragma once
#include "RPC/RPC.h"
#include "Network/TransportTypes.h"
#include "Coordinator/ServiceRole.h"
#if defined( NV_LINUX_PLATFORM )
#include <unistd.h>
#endif // defined( NV_LINUX_PLATFORM )

namespace Coordinator
{

struct MachineInfo
{
  ZDATA
  int numCores;
  nstl::string machineName;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&numCores); f.Add(3,&machineName); return 0; }

  MachineInfo() :
  numCores( 1 )
  {
#if defined( NV_WIN_PLATFORM )
    char buf[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD bufsize = sizeof(buf);
    if ( ::GetComputerName(&buf[0], &bufsize ) )
      machineName.assign(buf, bufsize);
    else
      machineName.assign("Machine name is not available");
#elif defined( NV_LINUX_PLATFORM )
    char buf[256];
    if ( ::gethostname( buf, sizeof( buf ) ) == 0 )
    {
      machineName.assign( buf );
    }
    else
    {
      machineName.assign("Machine name is not available");
    }
#endif
  }
};



struct ServiceDef
{
  ZDATA
  Transport::TServiceId svcid;
  TServiceRole role;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&svcid); f.Add(3,&role); return 0; }

  ServiceDef(Transport::TServiceId const & _svcid, TServiceRole const & _role = Coordinator::defaultServiceRole) :
  svcid(_svcid),
  role(_role)
  {}

  ServiceDef() :
  role(Coordinator::defaultServiceRole)
  {}
};



struct ServerDef : public rpc::Data
{
  SERIALIZE_ID();

  typedef vector<ServiceDef> ServiceDefsT;

  ZDATA
  ZNOPARENT(rpc::Data)
  ServiceDefsT svcdefs;
  MachineInfo machineInfo;
  Transport::TServiceId svcPathBase;  //  сервисы запущенные в этом сервере будут находится по этому пути
  unsigned int pid;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&svcdefs); f.Add(3,&machineInfo); f.Add(4,&svcPathBase); f.Add(5,&pid); return 0; }

  ServerDef() : pid(0) {}
};

} //namespace Coordinator
