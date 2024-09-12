#pragma once

#include "../Scene/SceneObject.h"
#include "../Scene/CollisionHull.h"
#include "PFChest.h"
#include "PFClientLogicObject.h"
#include "PFGlyph.h"

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PFClientChest : public PFClientSingleStateObject
{
  CLIENT_OBJECT_WORLD( PFClientChest, NWorld::PFPickupableObjectBase )
public:
  PFClientChest(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp) : PFClientSingleStateObject(pWO, cp) {}
  
  virtual void Update( float timeDiff );

protected:
  PFClientChest() {}
  virtual void SetVisibility(bool bVisible_) { SetVisibilityAsObject(bVisible_); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PFClientGlyph : public PFClientSingleStateObject
{
  CLIENT_OBJECT_WORLD( PFClientGlyph, NWorld::PFGlyph )
public:
  PFClientGlyph(const PF_Core::WorldObjectRef &pWO, const CreatePars& cp, const Render::HDRColor& color);

  virtual void Update( float timeDiff );
  virtual void UpdateMinimap() const;

protected:
  PFClientGlyph() {}
  virtual void SetVisibility(bool bVisible_) { SetVisibilityAsObject(bVisible_); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}