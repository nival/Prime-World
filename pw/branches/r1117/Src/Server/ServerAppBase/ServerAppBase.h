#ifndef SERVERAPPBASE_H_9E53EB61_3DB0_4E
#define SERVERAPPBASE_H_9E53EB61_3DB0_4E

#include <System/ServerStdOutDumper.h>
#include <System/DebugTraceDumper.h>
#include <System/TextFileDumper.h>
#include "System/SyncTextFileDumper.h"
#include <System/EventDumper.h>
#include <Server/AppFramework/Interfaces.h>

namespace Transport 
{

class NivalServer;

class ServerAppBase : public AppFramework::ITimedInstance, public BaseObjectMT 
{
  NI_DECLARE_REFCOUNT_CLASS_2(ServerAppBase, AppFramework::ITimedInstance, BaseObjectMT );
public:
  ServerAppBase();
  virtual ~ServerAppBase();

  virtual bool  OnInit(int argc, char* argv[]);
  virtual int   OnRun();
  virtual int   OnExit();

  virtual bool OnInitServerFactory( NivalServer * _serverFactory ) { return true; }
  virtual int Step(int delta); 
  virtual int GetId() const;

private:
  StrongMT<NivalServer>  server;

  StrongMT<NLogg::CServerStdOutDumper> stdoutDumper;
  StrongMT<NLogg::BasicTextFileDumper> textLogDumper;
  StrongMT<NLogg::CDebugTraceDumper> debugTraceDumper;

  int stepsCounter;
};

} // namespace Transport


#endif //#define SERVERAPPBASE_H_9E53EB61_3DB0_4E