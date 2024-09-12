#ifndef _SYNC_PROCESSOR_STATE_H_
#define _SYNC_PROCESSOR_STATE_H_

static const DWORD LOGIC_PROCESSOR_STATE = _EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW | _EM_UNDERFLOW | _EM_INEXACT | _EM_DENORMAL | _PC_24	| _RC_NEAR;
static const DWORD UI_PROCESSOR_STATE = _EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW | _EM_UNDERFLOW | _EM_INEXACT | _EM_DENORMAL | _PC_64	| _RC_NEAR;

void SyncProcessorState();
unsigned int GetProcessorState();
void SetProcessorState( unsigned int newState, unsigned int mask = 0xffffffff );
bool IsProcessorStateForLogic();
bool IsProcessorStateForUI();


#if !defined( NI_PLATF_LINUX )

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NI_SYNC_FPU_START   \
  WORD nFPUStatus;          \
  __asm                     \
  {                         \
    __asm fstcw nFPUStatus  \
    __asm wait              \
  }                         \
  SyncProcessorState();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NI_SYNC_FPU_END     \
  __asm                     \
  {                         \
    __asm fldcw nFPUStatus  \
    __asm wait              \
  }

#endif  // !defined( NI_PLATF_LINUX )


namespace utils
{

bool GetMemoryStatus( size_t & virtualSize );
int GetThreadCount();

} //namespace utils

#endif  // _SYNC_PROCESSOR_STATE_H_
