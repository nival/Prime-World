#pragma once

namespace Cluster
{
  typedef int TUserId;
  TUserId const INVALID_USER_ID = 0;

  typedef unsigned long long TGameId;
  TGameId const INVALID_GAME_ID = 0;

  const char * FmtGameId( TGameId _id );
}
