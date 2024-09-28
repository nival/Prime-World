#include "stdafx.h"

#include "../System/FileStreamDumper.h"
#include "../System/DebugTraceDumper.h"

#include "PFGameLogicLog.h"

NLogg::CChannelLogger &GetGameLogicLog()
{
  static NLogg::CChannelLogger s_log( "Game Logic" );
  return s_log;
}
