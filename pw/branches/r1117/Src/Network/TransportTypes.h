#pragma once

#include "System/fixedString.h"
#include "System/nfixed_string.h"

namespace Transport
{
  typedef FixedString<64> TServiceId;
  const TServiceId EmptySvcId = "";
  typedef int TClientId;

  //User session instance id
  //'couse there in cluster can be multiple sessions of the same user 
  //i.g. while re-entering cluster and kicking previous instances
  typedef int TUserSid;
  const TClientId autoAssignClientId = -1;

  struct Ping
  {
    Ping() : value(-1), count(0) {}
    Ping(long ping) : value(ping), count(0) {}
    Ping(long ping, unsigned long _count) : value(ping), count(_count) {}

    long value;
    unsigned long count;
  };
}