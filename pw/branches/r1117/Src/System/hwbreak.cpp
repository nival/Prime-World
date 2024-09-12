#include "stdafx.h"
#include "hwbreak.h"

#ifdef WIN32
HWBreak::HWBreak(void *address,  BreakPointType events) 
{ 
  m_break_address = (DWORD)address;
  m_events        = events;

  // Get a real handle to the current thread
  ::DuplicateHandle( ::GetCurrentProcess(), ::GetCurrentThread(), ::GetCurrentProcess(),  
    &m_main_thread_id, 0, FALSE, DUPLICATE_SAME_ACCESS);
  
  m_enable = true;
  RunHelperThread();
}

HWBreak::~HWBreak()
{
  if (m_bp_num != -1) 
  {
    m_enable = false;
    RunHelperThread();
  }

  ::CloseHandle(m_main_thread_id);
}

void HWBreak::RunHelperThread()
{ 
  // Start the helper thread
  DWORD thread_id = 0;
  HANDLE hThread = ::CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)threadFn, this, 0, &thread_id );

  // Wait until the thread has exited (ie. has updated our registers)
  DWORD status = ::WaitForSingleObject(hThread, INFINITE);

  if (status != WAIT_OBJECT_0) 
  { 
    ::MessageBoxA(0, "Helper thread didn't exit cleanly", "HWBreakpoint", MB_OK);
  }

  DWORD exit_code = 0;
  if (!::GetExitCodeThread(hThread, &exit_code)) 
  {
    ::MessageBoxA(0, "Failed to get worked thread exit code", "HWBreakPoint", MB_OK);
  }

  if (exit_code == THREAD_FAILED) 
  {
    ::MessageBoxA(0, "Worker thread returned failure code", "HWBreakPoint", MB_OK);
  }


  if (m_bp_num == -1) 
  {
    ::MessageBoxA(0, "All four hardware breakpoints are in use - breakpoint not set.", "HWBreakPoint", MB_OK);
  } 

  ::CloseHandle(hThread);
}

int HWBreak::FindFreeBreakpoint(const CONTEXT &context)
{
  for (int bp = 0; bp <= 3; ++bp) 
  {
    int mask = 1 << (bp * 2);
    if ((context.Dr7 & mask) == 0) 
      return bp;
  }

  return -1;
}

// The thread gets the required action from that->m_enable.
// If we're enabling a breakpoint, it'll write the breakpoint number (0-3) into that->m_bp_num (or -1 if there's none free)
// If we're disabling a breakpoint, it finds the breakpoint number from that->m_bp_num
DWORD WINAPI HWBreak::threadFn(void *data)
{
  HWBreak *that = (HWBreak *) data;

  // Suspend the main thread
  DWORD suspend_count = ::SuspendThread(that->m_main_thread_id);

  if (suspend_count ) 
    return THREAD_FAILED;

  CONTEXT context;
  context.ContextFlags = CONTEXT_DEBUG_REGISTERS;

  DWORD ok = ::GetThreadContext(that->m_main_thread_id, &context);

  if (ok)
  {
    if (that->m_enable) {
      int bp = FindFreeBreakpoint(context);

      if (bp != -1)
      {            
        DWORD enable = 0x1 << (bp *2);
        DWORD rw = (that->m_events == ReadWrite ? 0x000f0000 : 0x000d0000) << (bp * 4);
        DWORD mask = enable | rw;


        switch (bp)
        {
        case 0: 
          context.Dr0 = that->m_break_address;  
          break;
        case 1: 
          context.Dr1 = that->m_break_address;  
          break;
        case 2: 
          context.Dr2 = that->m_break_address;  
          break;
        case 3: 
          context.Dr3 = that->m_break_address;  
          break;
        }

        context.Dr7 |= mask;

        ok = ::SetThreadContext(that->m_main_thread_id, &context);
      }

      that->m_bp_num = bp;

    } else {
      DWORD enable = 0x1 << (that->m_bp_num *2);
      context.Dr7 &= ~enable;
      ok = ::SetThreadContext(that->m_main_thread_id, &context);
    }
  }

  // Resume the main thread
  suspend_count = ::ResumeThread(that->m_main_thread_id);
  if (suspend_count == 0xFFFFFFFF) return THREAD_FAILED;

  return ok ? THREAD_SUCCESS : THREAD_FAILED;
}   

#else

HWBreak::HWBreak(void *address,  BreakPointType events){}
HWBreak::~HWBreak() {}

#endif