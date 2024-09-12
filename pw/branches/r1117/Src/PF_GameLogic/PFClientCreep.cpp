#include "stdafx.h"

#include "PFClientCreep.h"

#include "Minimap.h"

#include "PFClientBaseUnit.h"
#include "PFCreep.h"

#include "../PF_Core/ClientObject.h"
#include "../PF_Core/EffectsPool.h"
#include "../System/InlineProfiler.h"

#include "AdventureScreen.h"

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFCreep::PFCreep(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp)
  : PFClientCreature(pWO, cp)
{
  NI_PROFILE_FUNCTION

  const NWorld::PFBaseMovingUnit* pWorldObject = WorldObject();
  NI_ASSERT(cp.pScene && pWorldObject, "Invalid initialization of client object");

  NI_VERIFY( PFClientCreature::Initialize( GetSceneObject(), &cp.pAnimSet, 1, cp.startIdleAnimation, 0, false ), "Animated creature failed to initialize properly!", return; );

  //look to the world object direction
  LookTo( pWorldObject->GetMoveDirection() );

	ResetColor();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCreep::Update(float timeDelta)
{ 
  NI_PROFILE_FUNCTION

  PFClientCreature::Update(timeDelta); 
}

void PFCreep::UpdateMinimap() const
{
  if( (WorldObject())->GetOpenWarFog() )
    PFClientCreature::UpdateMinimap();
}

void PFCreep::UpdateVisibility()
{
  if( !(WorldObject())->GetOpenWarFog() )
  {
    if (const NGameX::AdventureScreen * const screen = NGameX::AdventureScreen::Instance())
    {
      const VisibilityMapClient* visMap = screen->GetClientVisibilityMap();

      const bool isAlly = WorldObject()->GetFaction() == screen->GetPlayerFaction();
      const bool isVisible = isAlly ? ( WorldObject()->GetUnitType() == NDb::UNITTYPE_PET 
                                        || visMap && visMap->IsPointVisible( WorldObject()->GetPosition().AsVec2D() ) )
                                    : WorldObject()->IsVisibleForEnemy( screen->GetPlayerFaction() ) 
                                        && visMap && visMap->IsPointVisible( WorldObject()->GetPosition().AsVec2D() );
      
      SetVisibility( isVisible );
    }

    return;
  }
  
  PFClientCreature::UpdateVisibility();
}

}
