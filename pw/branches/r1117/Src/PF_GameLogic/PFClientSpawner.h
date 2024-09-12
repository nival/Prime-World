#pragma once

/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PFClientObjectBase.h"
#include "PFNeutralCreep.h"

namespace NWorld 
{ 
  class PFNeutralCreepSpawner;
}

namespace NGameX
{

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFClientNeutralCreepSpawner : public NWorld::PFClientObjectBase
{
  CLIENT_OBJECT_METHODS( 0x22844440, PFClientNeutralCreepSpawner, NWorld::PFNeutralCreepSpawner )

  explicit PFClientNeutralCreepSpawner() {}

public:
  PFClientNeutralCreepSpawner(const PF_Core::WorldObjectRef &pWO);

  void ShowMinimapIcon(const bool value) { showMinimapIcon = value; }

private:
  virtual void Update(float timeDelta);
  virtual void UpdateVisibility();
  virtual void UpdateMinimap() const;

  NDb::Ptr<NDb::AdvMapNeutralCreepSpawner> pDBDesc;

  CVec3 position;

  bool showMinimapIcon;
  bool visibleLastFrame;

  bool sharedVision;
  bool sharedVisionShowMinimapIcon;
};

}
