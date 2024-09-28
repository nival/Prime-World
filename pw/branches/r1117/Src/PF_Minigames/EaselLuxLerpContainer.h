#pragma once

#include "EaselLuxLerp.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// Luxor view Lerp container class, stores weak pointers
// container element is created is weak_pointer is Empty
//
//////////////////////////////////////////////////////////////////////////
class LuxViewLerpContainer
{
  typedef nstl::list<CPtr<ILuxViewLerp>> LuxViewLerps;
  typedef LuxViewLerps::iterator            LVLIter;

public:
  LuxViewLerpContainer();
  ~LuxViewLerpContainer();

  // common insertion/deletion methods
  void AddLerpProcessor( ILuxViewLerp* wpProcessor );

  // engine step processing
  void Step(float deltaTime);

private:
  LuxViewLerpContainer(const LuxViewLerpContainer &rhs);
  LuxViewLerpContainer& operator=(const LuxViewLerpContainer &rhs);

  LuxViewLerps listLerps;

protected:

};

} // namespace PF_Minigames