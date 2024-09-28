#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <new.h>
#include "NewHandler.h"
#include "UserMessage.h"

namespace ni_detail
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CheckPtr(void* _p)
{
  if(_p)
    return;

  // WARNING! This MessageBox will be displayed in low memory conditions. Take great care moving it to resource strings. 
  UserMessage::ShowMessageAndTerminate( 
    EXCEPTION_ARRAY_BOUNDS_EXCEEDED, 
    "The program ran out of memory.\nTry to free some memory and restart application."
  );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int handle_memory_depletion( size_t )
{
  CheckPtr(0);
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetNewHandler(HWND _hWnd) // declared in newdelete.h
{
  UserMessage::Init(_hWnd);
  _set_new_handler(handle_memory_depletion);
  _set_new_mode(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG_TERMINATE
void DebugTerminate()
{
  CheckPtr(0);
}
#endif // _DEBUG_TERMINATE

} // namespace ni_detail
