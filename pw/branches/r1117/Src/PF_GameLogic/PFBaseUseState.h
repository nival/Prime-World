#pragma once

#include "PFFsm.h"
#include "PFUniTarget.h"
#include "ValueWithModifiers.hpp"

namespace NDb
{
  struct Ability;
}

namespace NWorld
{

class PFAbilityInstance;
class PFBaseUnit;

class PFBaseUseState : public PFBaseUnitState, public PFHFSM
{
public:
  PFBaseUseState( CPtr<PFBaseUnit> const& _owner, Target const& _target );

  virtual bool IsEjecting() const;
  virtual int  GetNumSubStates() const { return GetStackSize(); }
  virtual bool IsBlocking() const;
  virtual bool CanBeInterrupted() const { return !IsBlocking(); }
 
  bool NeedToGetClose() const;
  bool IsCastFinished() const;
  bool IsAbilityFinished() const;
  virtual void DumpStateToConsole(int depths);
  virtual void OnLeave();

  const AbilityTarget& GetTarget() const { return target; }

  unsigned int GetAbilityFlags() const;
  virtual NDb::Ability const* GetDBDesc() const = 0;
protected:
  PFBaseUseState() {}

  //return negative value in case of some error
  virtual float GetUseRange() const = 0;
 
  ZDATA_(PFBaseUnitState);
  ZPARENT( PFHFSM );
  AbilityTarget  target;
  CObj<PFAbilityInstance> pAbilityInstance;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseUnitState*)this); f.Add(2,( PFHFSM *)this); f.Add(3,&target); f.Add(4,&pAbilityInstance); return 0; }
};
}