#pragma once

#include "PFApplBuff.h"

namespace NWorld
{

class PFWorld;
class PFBaseUnit;
//class PFAbility;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplAura : public DBLinker<PFApplBuff, NDb::AuraApplicator>
{
	typedef vector<CPtr<PFBaseUnit> > AffectedUnits;
  WORLD_OBJECT_METHODS(0xE5CC383, PFApplAura);

  ZDATA_(DBLinker)
protected:
	int activeBuffer;
	AffectedUnits appliedApplicator1;
	AffectedUnits appliedApplicator2;
	CObj<PFTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&activeBuffer); f.Add(3,&appliedApplicator1); f.Add(4,&appliedApplicator2); f.Add(5,&pTargetSelector); return 0; }

  PFApplAura(PFApplCreatePars const &cp)
    : Base(cp), activeBuffer(0) {}
  PFApplAura() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

	void ProcessUnit(const Target &target);

  virtual float GetVariable(const char* sVariableName) const;

protected:
	virtual bool Start();
  virtual void Enable();
  virtual void Disable();
  virtual void Reset();
  virtual bool Step(float dtInSeconds);

	virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT | Target::FLAG_POSITION; }

private:
	void RemoveApplicatorsFromUnits();
	AffectedUnits& GetAffectedUnit( int idx );
  AffectedUnits const& GetAffectedUnit( int idx ) const;

};

}