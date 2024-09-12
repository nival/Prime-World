#pragma once

#include "../PF_Core/ClientObject.h"

#include "PFClientCreature.h"
#include "PFClientObjectBase.h"

#include "PFCreep.h"

namespace NGameX
{

class PFCreep : public PFClientCreature
{
  CLIENT_OBJECT_METHODS( 0x1E59D440, PFCreep, NWorld::PFCreature )
public:
	PFCreep(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp);

  // NScene::IUpdateable via PF_Core::ClientObjectBase<NWorld::PFCreep>
	virtual void Update(float timeDelta);
  virtual void UpdateMinimap() const;
  virtual void UpdateVisibility();

protected:
  explicit PFCreep() {}
};


} // namespace NGameX
