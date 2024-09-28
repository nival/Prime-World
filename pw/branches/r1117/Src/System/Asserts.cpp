#include "stdafx.h"
#include "Asserts.h"

static bool isEnabledAsserts = true;

void EnableDebugAsserts()
{
  isEnabledAsserts = true;
}

void DisableDebugAsserts()
{
  isEnabledAsserts = false;
}


bool NiIsDebuggerPresent()
{
#ifdef WIN32
  return IsDebuggerPresent();
#else
  // if ppid != sid, some process spawned our app, probably a debugger.
  //result = getsid(getpid()) != getppid();
  bool result = false;
  char s[256];
  snprintf(s, 256, "/proc/%d/cmdline", getppid());
  FILE * fp = fopen(s, "r");
  if (fp != NULL) {
    fread(s, 256, 1, fp);
    fclose(fp);
    result = (0 == strncmp(s, "gdb", 3));
  }
  return result;
#endif
}



bool TraceAssertMsg( NLogg::ELevel level, const char* msg, const char* user_text, const char *szFileName, const unsigned long dwLine )
{
  if ( msg )
  {
    systemLogEx( level, szFileName, dwLine ).Trace( "%s (%s)", msg, user_text );
  }
  else
  {
    systemLogEx( level, szFileName, dwLine ).Trace( "%s", user_text );
  }

  return NiIsDebuggerPresent() && isEnabledAsserts;
}

void TraceMsg( const char * msg )
{
  DebugTrace( msg );
}