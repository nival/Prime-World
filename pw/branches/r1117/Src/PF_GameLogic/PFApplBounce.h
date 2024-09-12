#pragma once

#include "PFApplBuff.h"
#include "PFDispatch.h"

namespace NWorld
{

class PFWorld;
class PFBaseUnit;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplBounce: public DBLinker<PFApplBuff, NDb::BounceApplicator>
{
  WORLD_OBJECT_METHODS(0xE7792381, PFApplBounce);

  explicit PFApplBounce() {}

protected:
  ZDATA_(DBLinker)
  int targetsNumber;
  int targetCounter;
  Target currentTarget;
  CPtr<PFDispatch> pDispatch;
  CObj<PFSingleTargetSelector> pTargetSelector;
  float timeToNextBounce;
  float bounceDelay;
  bool finished;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&targetsNumber); f.Add(3,&targetCounter); f.Add(4,&currentTarget); f.Add(5,&pDispatch); f.Add(6,&pTargetSelector); f.Add(7,&timeToNextBounce); f.Add(8,&bounceDelay); f.Add(9,&finished); return 0; }

  PFApplBounce(PFApplCreatePars const &cp) : Base(cp), targetsNumber(0), targetCounter(0), timeToNextBounce(0), bounceDelay(0), finished(false) {}

  void SetNewTarget( const Target & _target );

  virtual float GetVariable(const char* sVariableName) const;

  virtual void OnDispatchTargetDropped( const PFDispatch * pDispatch );
protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds);
  virtual void Stop();

  bool ExecuteNext();
  bool IsFinished() const;

	// From IMiscFormulaPars
  //virtual float GetScale() const { return scale * Base::GetScale(); }

private:
};

}