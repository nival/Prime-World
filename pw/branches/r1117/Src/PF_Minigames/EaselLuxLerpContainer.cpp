#include "stdafx.h"

#include "EaselLuxLerpContainer.h"

namespace PF_Minigames
{
//////////////////////////////////////////////////////////////////////////
//
// class LuxViewLerpContainer implementation
//
//////////////////////////////////////////////////////////////////////////
LuxViewLerpContainer::LuxViewLerpContainer()
{
  
}

LuxViewLerpContainer::~LuxViewLerpContainer()
{ 

}

void LuxViewLerpContainer::AddLerpProcessor( ILuxViewLerp* wpProcessor )
{
  if ( IsValid( wpProcessor ) )
    listLerps.push_back(wpProcessor);
}

void LuxViewLerpContainer::Step(float deltaTime)
{
  LVLIter listIter = listLerps.begin();

  while(listIter != listLerps.end())
  {
    if ( !IsValid( *listIter ) )  // object is expired (ball is probably destroyed)
      listIter = listLerps.erase(listIter);
    else
    {
      if(((*listIter)->vStep(deltaTime)) == false)   // step processing failed on object (object is dead)
        listIter = listLerps.erase(listIter);
      else
        listIter++;
    }
  }
}

} // namespace PF_Minigames