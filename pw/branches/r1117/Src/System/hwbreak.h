#ifndef _HWBREAK_H_
#define _HWBREAK_H_


class HWBreak
{
public:
  typedef enum { ReadWrite, Write } BreakPointType;

  // Set an available hardware breakpoint to halt on reads/writes to the dword at [address]

  //
  // For example:
  //  int i = 0;
  //  HWBreak(&i);
  //  int x = i + 2; (break on read)
  //  int i++;       (break on write)
  // 
  // NB: The debugger will probably stop on the line /after/ the breakpoint.
  HWBreak(void *address,  BreakPointType events = ReadWrite);

  ~HWBreak();
private:
#ifdef WIN32
  HANDLE m_main_thread_id;
  DWORD m_break_address;
  BreakPointType m_events;    
  DWORD m_bp_num; // Which hw breakpoint are we using? (0 - 3, or -1 if we didn't set a bp)

  bool m_enable; // Current worker thread action

  enum { THREAD_FAILED, THREAD_SUCCESS };

  void         RunHelperThread();
  static int   FindFreeBreakpoint(const CONTEXT &context);
  static DWORD WINAPI threadFn(void *data);
#endif
};

#endif // _HWBREAK_H_
