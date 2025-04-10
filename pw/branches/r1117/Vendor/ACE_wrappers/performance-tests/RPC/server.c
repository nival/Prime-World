/*
 * $Id: server.c 80826 2008-03-04 14:51:23Z wotte $
 */

#include "ping.h"
#include <rpc/rpc.h>
#include <stdio.h>

static int return_value = 0;

int* ping_1_svc (int* value, struct svc_req* r)
{
  return_value = *value;
  return &return_value;
}
