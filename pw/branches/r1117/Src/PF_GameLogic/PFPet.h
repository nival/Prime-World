#pragma once

#include "PFCreature.h"
#include "PFWorld.h"

#include "DBUnit.h"

namespace NGameX 
{
  class PFClientCreature; 
}

namespace NWorld
{
class PFBaseHero;
class PFBasePetUnit;


class PFPetAIBaseState
  : public PFBasePetUnitState
  , public PFHFSM
{
public:
  PFPetAIBaseState(CPtr<PFBasePetUnit> const& pPet);

protected:
  virtual bool OnStep(float dt);
  PFPetAIBaseState() {}

private:
  WORLD_OBJECT_METHODS(0x11626B81, PFPetAIBaseState);
  ZDATA_(PFBasePetUnitState);
  ZPARENT(PFHFSM);
  CPtr<PFBaseHero> pPetKeeper;
  float            maxEscortDistance;
  float            minEscortDistance;

  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBasePetUnitState*)this); f.Add(2,(PFHFSM*)this); f.Add(3,&pPetKeeper); f.Add(4,&maxEscortDistance); f.Add(5,&minEscortDistance); return 0; }
};

class PFBasePetUnit : public PFCreature
{
public:
  PFBasePetUnit(CPtr<PFWorld> pWorld, const NDb::BasePet &petObj, CPtr<PFBaseHero> pKeeper_);

  CPtr<PFBaseHero> const& GetKeeper() const { return pKeeper; }

protected:
  //virtual void OnDestroyContents();
  //virtual bool Step(float dtInSeconds);
  explicit PFBasePetUnit() {}

private:
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x11624C41, PFBasePetUnit, NGameX::PFClientCreature);
  ZDATA_(PFCreature)
  CPtr<PFBaseHero> pKeeper;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFCreature*)this); f.Add(2,&pKeeper); return 0; }
	virtual void Reset();
};

// Direct pet create
PFBasePetUnit *CreateTestPet( PFWorld* pWorld, const char *name, const CPtr<PFBaseHero>& pKeeper);

} //namespace NWorld