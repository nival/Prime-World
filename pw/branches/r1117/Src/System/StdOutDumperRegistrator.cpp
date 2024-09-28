#include "stdafx.h"
#include "StdOutDumper.h"

namespace NLogg
{
  static NLogg::CStdOutDumper g_stdoutDumper( &GetSystemLog() );
}