#pragma once

#ifdef _DEBUG
  //#define _DEBUG_LOCKS
#endif // _DEBUG

#ifdef _DEBUG_LOCKS
  uint GetLockCall(void* _pBuff);
  #define DEBUG_LOCKS(a) a
#else // _DEBUG_LOCKS
  #define DEBUG_LOCKS(a)
#endif // _DEBUG_LOCKS
