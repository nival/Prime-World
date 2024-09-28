#pragma once

#include "PFTargetSelector.h"

namespace NWorld
{

class PFHighlanderA1TargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::HighlanderA1TargetSelector>
{
  WORLD_OBJECT_METHODS(0xB76C241, PFHighlanderA1TargetSelector);
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFHighlanderA1TargetSelector() {}
	PFHighlanderA1TargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFHighlanderA1TargetSelector(const NDb::TargetSelector &db, PFWorld* world) : Base(db, world) {}
  
protected:
  virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};

} // End of namespace NWorld
