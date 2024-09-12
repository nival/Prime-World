#include "stdafx.h"

#include "AdventureScreen.h"
#include "ObjectsInfo2d.h"
#include "PFClientChest.h"
#include "Minimap.h"

#include "../System/InlineProfiler.h"

namespace NGameX
{

PFClientGlyph::PFClientGlyph(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp, const Render::HDRColor &color )
  : PFClientSingleStateObject(pWO, cp)
{
  static const Render::HDRColor s_addZero;
  
  SetVisibility( false );

  if ( GetSceneObject() )
  {
    CPtr<PF_Core::ColorModificationChannel> pColorChanel = PFClientLogicObject::CreateColorModificationChannel( PF_Core::CMC_EFFECT1 );
    pColorChanel->SetMulColor( color );
  }
} 

void PFClientChest::Update( float timeDiff )
{
  NI_PROFILE_FUNCTION

  PFClientSingleStateObject::Update( timeDiff );
}

void PFClientGlyph::Update( float timeDiff )
{
  NI_PROFILE_FUNCTION;

  UpdateVisibility();
  UpdateMinimap();
  PFClientSingleStateObject::Update( timeDiff );
}

void PFClientGlyph::UpdateMinimap() const
{
  static DI_WEAK(NGameX::Minimap) minimap;

  if (!IsValid(minimap))
    return;

  if (!bVisible)
    return;

  const NWorld::PFGlyph* const pWorldObject = WorldObject();

  if (!pWorldObject)
    return;

  minimap->AddObject(pWorldObject, pWorldObject->GetDBDesc()->minimapIcon);
}

} // End of namespace NGameX