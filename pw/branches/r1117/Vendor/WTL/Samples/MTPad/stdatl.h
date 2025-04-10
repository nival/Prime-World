#ifndef _WIN32_WCE

#define WINVER		0x0500
#define _WIN32_WINNT	0x0500
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0200

#else // _WIN32_WCE

#define WINVER		0x0400
#define _WIN32_IE	0x0400

#endif // _WIN32_WCE

#define _WTL_USE_CSTRING

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>
