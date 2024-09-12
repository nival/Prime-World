#include "TamarinPCH.h"

#include "FlashEnterFunction.h"
#include "FlashMovie.h"
#include <System/SyncProcessorState.h>

namespace flash
{

FlashEnterFunction::FlashEnterFunction()
{
  SaveFloatState();
}

FlashEnterFunction::~FlashEnterFunction()
{
  LoadFloatState();
}

void FlashEnterFunction::SaveFloatState()
{
  WORD _nFPUStatus;

  __asm 
  {
    fstcw _nFPUStatus
    wait
  }

  nFPUStatus = GetProcessorState();

  SetProcessorState( UI_PROCESSOR_STATE, 0xffffffff );
}

void FlashEnterFunction::LoadFloatState()
{
  SetProcessorState( nFPUStatus );
}

}
