#include "stdafx.h"
#include "NLClient.h"
#include <naio/ConnectionContext.h>
#include "DefaultLogCallback.h"

namespace NetworkLayer
{
  int Client::Run()
  {
    naio::DriverSP spdrv(new naio::Driver);
    cfg_.naiocfg_.spLogMsgCb_.reset(new LogCallback(::GetSystemLog()));

    cfg_.naiocfg_.checkActivityTimeout_ = 3;
    if (!spdrv->Init(cfg_.naiocfg_))
      return -1;

    naio::ConnectionContextSP connctx = spdrv->OpenConnection(ACE_INET_Addr(cfg_.serverAddr_.c_str()), 0);
    if (connctx.null())
    {
      spdrv->Fini();
      return -1;
    }

    printf("Press 'Q' to quit");

    int ch = 0;
    while ((ch = _getch()) != 'Q');

    spdrv->CloseConnection(connctx);
    spdrv->Fini();
    return 0;
  }
}
