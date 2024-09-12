#include "stdafx.h"

#include "Compatibility.h"


namespace Compatibility
{
static bool g_isRunnedUnderWine = false;
static bool g_isCrossOverWine = false;

static bool s_forceWine = false;
REGISTER_DEV_VAR("forceWineCompatibility", s_forceWine, STORAGE_NONE);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef const char *(WINAPI *TGetVersionProc)(void);

void Init()
{ 
  //http://wiki.winehq.org/DeveloperFaq#head-96551a33b168826cd805c2f62c4ea705ac02f350
  HMODULE hDll = LoadLibrary( TEXT( "ntdll.dll") );
  
  if ( !hDll )
    return;

  TGetVersionProc getVersion = (TGetVersionProc) GetProcAddress( hDll, TEXT( "wine_get_version" ) );
  
  g_isRunnedUnderWine = getVersion != 0;
  g_isCrossOverWine = getVersion != 0 ? strstr( (*getVersion)(), "CXG" ) != NULL : false; 
  
  FreeLibrary( hDll );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsRunnedUnderWine()
{
  return s_forceWine || g_isRunnedUnderWine;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsRunnedUnderCrossOverWine()
{
  return g_isCrossOverWine;
}

}