#pragma once

#include "PFApplBuff.h"
#include "PFBaseUnit.h"
#include "PFBaseUnitEvent.h"

namespace NWorld
{

class PFBaseUnit;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplDelegateDamage: public DBLinker<PFApplBuff, NDb::DelegateDamageApplicator>, public PFBaseUnitEventListener
{
  WORLD_OBJECT_METHODS(0xE7873441, PFApplDelegateDamage);

protected:
  ZDATA_(DBLinker)
  ZNOPARENT(PFBaseUnitEventListener)
  float totalDamage;
  CObj<PFTargetSelector> pTargetSelector;
  bool stopByCondition;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&totalDamage); f.Add(3,&pTargetSelector); f.Add(4,&stopByCondition); return 0; }

  PFApplDelegateDamage(PFApplCreatePars const &cp);

  virtual float GetVariable(const char* sVariableName) const;

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds);
  virtual void Enable();
  virtual void Disable();
  virtual unsigned int OnEvent( const PFBaseUnitEvent* pEvent );

private:
  PFApplDelegateDamage() {}
  void DelegateDamage( PFBaseUnitDamageEvent const* pEvent, vector<PFBaseUnit*> const& delegateTargets );
  bool DelegateIsOver();

  float damageToDelegate; // doesn't need to be serialized, used only in instant formula call
};

}