#pragma once

#include "PFApplBuff.h"
#include "PFBaseUnitEvent.h"

namespace NWorld
{

class PFWorld;
class PFBaseUnit;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplChannelling : public DBLinker<PFApplBuff, NDb::ChannellingApplicator>, public PFBaseUnitEventListener
{
  WORLD_OBJECT_METHODS(0x9E67B281, PFApplChannelling);

	enum State
	{
		STATE_CHANNELLING = 0,
		STATE_CANCEL, 
		STATE_FIRE,
    STATE_INTERRUPT,
	};

  ZDATA_(DBLinker)
	ZNOPARENT(PFBaseUnitEventListener)
	CObj<PFTargetSelector> pTargetSelector;
	float									 scale;
	State                  state;
	float                  timer;
	float                  period;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); f.Add(3,&scale); f.Add(4,&state); f.Add(5,&timer); f.Add(6,&period); return 0; }

  PFApplChannelling(PFApplCreatePars const &cp) : Base(cp), scale(1.0f), state(STATE_CHANNELLING), timer(0.0f), period(0.0f) {}
  PFApplChannelling() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  float GetVariable( const char* varName ) const;
protected:
	virtual bool Start();
	virtual void Stop();
	virtual bool Step(float /*dtInSeconds*/);
	virtual float GetScale() const;

  virtual void Strike();
  virtual void Fire();
  virtual void Cancel();

	virtual unsigned int OnEvent(const PFBaseUnitEvent *pEvent);
	virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }

	void SetOwnerProgress(float progress);
	float CalculateProgress() const;
  bool IsChannelingTargetValid() const;
};

}