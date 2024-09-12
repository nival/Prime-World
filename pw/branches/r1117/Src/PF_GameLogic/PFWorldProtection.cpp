#include "stdafx.h"
#include "PFWorldProtection.h"

#ifdef STARFORCE_PROTECTED

#include "PFWorldRealProtection.hpp"

#else // STARFORCE_PROTECTED

#include "PFWorldDummyProtection.hpp"

#endif // STARFORCE_PROTECTED

#pragma code_seg(push, "~")

namespace NWorld
{
  STARFORCE_EXPORT CObj<PFWorldProtection> PFWorldProtection::Create(PFWorld* const world)
  {
    CObj<PFWorldProtection> p;

#ifdef STARFORCE_PROTECTED
    p = new ::PFWorldRealProtection(world);
#else // STARFORCE_PROTECTED
    p = new ::PFWorldDummyProtection(world);
#endif // STARFORCE_PROTECTED

    NI_ASSERT(IsValid(p), "Failed to create protection!");

    return p;
  }

  STARFORCE_EXPORT void PFWorld::ProtectionCheck()
  {
#ifdef STARFORCE_PROTECTED
    if (protection->IsOK())
      return;

    if (!IsValid(adventureScreen))
      return;

    adventureScreen->OnProtectionError();
#endif // STARFORCE_PROTECTED
  }
}

#pragma code_seg(pop)
