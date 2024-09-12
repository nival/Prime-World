#pragma once

#include "PFApplBuff.h"

namespace PF_Core
{
	class ControlledStatusEffect;
}

namespace NWorld
{

class PFWorld;
class PFBaseUnit;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplSpellProbability: public DBLinker<PFBaseApplicator, NDb::SpellProbabilityApplicator>
{
  WORLD_OBJECT_METHODS(0x11621CC1, PFApplSpellProbability);

protected:
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplSpellProbability(PFApplCreatePars const &cp) : Base(cp) {}
  PFApplSpellProbability() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds)
  {
    NI_ALWAYS_ASSERT("Must not get here");
    return true;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplSpellPeriodically : public DBLinker<PFApplBuff, NDb::SpellPeriodicallyApplicator>
{
	WORLD_OBJECT_METHODS(0xE5CC391, PFApplSpellPeriodically);

protected:
  ZDATA_(DBLinker)
	float period;
	float startOffset;
	float curPeriod;
	float timer;
	int   strikeCount;
	CObj<PFTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&period); f.Add(3,&startOffset); f.Add(4,&curPeriod); f.Add(5,&timer); f.Add(6,&strikeCount); f.Add(7,&pTargetSelector); return 0; }

  PFApplSpellPeriodically(PFApplCreatePars const &cp) : Base(cp), period(0.0f), startOffset(0.0f), curPeriod(0.0f), timer(0.0f), strikeCount(0), pTargetSelector(NULL) {}
  PFApplSpellPeriodically(): period(0.0f), startOffset(0.0f), curPeriod(0.0f), timer(0.0f), strikeCount(0), pTargetSelector(NULL) {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  void DoStrike();

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds);
	virtual float GetScale() const;

	virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT | Target::FLAG_POSITION; }

	float GetTime2Strike() const { return curPeriod - timer; }
	float GetPeriod() const { return period; }
	float GetStartOffset() const { return startOffset; }

private:
	void Strike();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplSpellPeriodicallyVisual : public DBLinker<PFApplSpellPeriodically, NDb::SpellPeriodicallyVisualApplicator>
{
	WORLD_OBJECT_METHODS(0x9E6CF401, PFApplSpellPeriodicallyVisual);

  vector<CObj<PF_Core::ControlledStatusEffect>> controlledEffects;
	int  strikeCountMarker;

	ZDATA_(DBLinker)
	float attackTimeOffset;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&attackTimeOffset); return 0; }

	PFApplSpellPeriodicallyVisual(PFApplCreatePars const &cp) : Base(cp), attackTimeOffset(0.0f), strikeCountMarker(0) {}
	PFApplSpellPeriodicallyVisual() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
	virtual bool Start();
	virtual void Disable();
	virtual bool Step(float dtInSeconds);
  virtual void Recalculate() {}
  virtual void AfterStartEffects();
};

}