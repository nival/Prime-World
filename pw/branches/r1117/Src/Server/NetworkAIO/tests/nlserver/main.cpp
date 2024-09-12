#include "stdafx.h"
#include "System/StdOutDumper.h"
#include "System/ThreadHelpers.h"
#include "System/FileSystem/FileUtils.h"
#include "System/ProfileManager.h"
#include "System/ConfigFiles.h"
#include "NLServer.h"
#include "NLProtocolHandlerFactory.h"

int ACE_TMAIN(int argc, char* argv[])
{      
  NDebug::SetProductNameAndVersion(NFile::GetCurrDir(), "NLServer", "private", 0, 0, 0, 0);
  ScopedPtr<NLogg::CServerStdOutDumper> stdoutDumper;
  Reset( stdoutDumper, new NLogg::CServerStdOutDumper( &GetSystemLog() ) );
  ScopedPtr<NLogg::BasicTextFileDumper> textLogDumper;
  Reset( textLogDumper,  NLogg::BasicTextFileDumper::New( &GetSystemLog(), "" ) );
  NBSU::InitUnhandledExceptionHandler();

  GetSystemLog().AddChannel("nlserver");

  NetworkLayer::ProtocolHandlerFactory phf;
  NetworkLayer::Server srv;
  srv.naiocfg_.loglvl_ = 1;
  srv.naiocfg_.phf_ = &phf;
  srv.listenAddr = "35000";

  srv.Run();

  return 0;
}
