#pragma once

#include <System/ScopedPtr.h>
#include <ServerAppBase/ServerAppBase.h>
#include <System/Node/NodeManager.h>

class UniServerApp: public Transport::ServerAppBase
{
  nvl::CNodeManagerPtr m_cpNodeManager;

public:
  UniServerApp(); 

  virtual bool OnInitServerFactory( Transport::NivalServer * _serverFactory );

  virtual bool  OnInit(int argc, char* argv[]);
  virtual int   OnExit();
};
