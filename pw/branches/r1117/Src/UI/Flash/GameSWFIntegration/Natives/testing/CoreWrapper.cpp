#include "TamarinPCH.h"

#include "../../FlashMovie.h"

#include "CoreWrapper.h"

namespace avmplus
{
  void CoreWrapperClass::Advance( double deltaTime )
  {
    SwfDebugLog::CallLog("CoreWrapperClass", "Advance");
    FlashCore()->GetMovie()->Advance(deltaTime);
  }
}