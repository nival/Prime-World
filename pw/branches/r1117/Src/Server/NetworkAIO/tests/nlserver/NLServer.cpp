#include "stdafx.h"
#include "NLServer.h"

namespace NetworkLayer
{
  int Server::Run()
  {
    naio::DriverSP spdrv(new naio::Driver);
    if (!spdrv->Init(naiocfg_))
      return -1;

    naio::AcceptorHandle h = spdrv->OpenAcceptor(ACE_INET_Addr(listenAddr.c_str()), 0);
    if (h.invalid())
      return -1;

    printf("Press 'Q' to quit");

    int ch = 0;
    while ((ch = _getch()) != 'Q');

    spdrv->CloseAcceptor(h);
    spdrv->Fini();
    return true;
  }
}
