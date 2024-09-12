#pragma once

#include "DebugStateDump.h"
#include "PFWorldObjectBase.h"

namespace NWorld
{
class PFBaseUnit;
class PFBaseMovingUnit;
class PFBaseHero;
class PFMainBuilding;
class PFBasePetUnit;

_interface IPFState : public IObjectBase
{
  virtual bool DoStep(float dt)           = 0;
  virtual bool IsEjecting()       const = 0;
  virtual bool CanBeInterrupted() const = 0;
  virtual int  GetNumSubStates()  const = 0;
  virtual bool IsBlocking()       const = 0;
  virtual bool IsEscaping()       const = 0;
	virtual void DoLeave( bool = false ) = 0;
  virtual void InformStatePassingThrough() = 0;

  //for debug
  virtual void DumpStateToConsole(int  depths) =0;
  virtual ~IPFState(){}
  ZDATA
  ZEND int operator&( IBinSaver &f ) { return 0; }
};

template<typename T>
class TPFState : public IPFState
{
public:
  TPFState(T * pOwner) : pOwner(pOwner), started(false) {}
  virtual bool OnStep(float dt) { return true; }
  virtual void OnEnter() {}
  virtual void OnLeave() {}
  virtual void OnAfterLeave() {}
  virtual int  GetNumSubStates() const { return -1; }
  virtual bool IsEjecting() const { return true; } 
  virtual bool IsBlocking() const { return false; } 
  virtual bool IsEscaping() const { return false; }
  virtual void InformStatePassingThrough() { }
  
  virtual bool CanBeInterrupted() const { return true; }

  virtual void DumpStateToConsole( int depths )
  {
    DumpSimpleState(this, depths);
  }

protected:
	virtual void DoLeave( bool cleanupLeave = false ) 
	{
		DumpState( "OnLeave" );
		OnLeave();
    if ( !cleanupLeave && !IsEjecting() )
    {
      OnAfterLeave();
    }
	}
  TPFState() {}
  bool IsStateStarted() const { return started; }
	virtual void DumpState( const char* state ) = 0;
private:
  virtual bool DoStep(float dt)
  {
    if (!started)
    {
      DumpState( "OnEnter" );
      //DevTrace("%08x : OnEnter", int (this));
      OnEnter();
      started = true;
    }
    DumpState( "OnStep" );
    //DevTrace("%08x : OnStep", int (this));
    return OnStep(dt);
  }

  ZDATA_(IPFState)
  ZNOPARENT( CObjectBase)
  bool started;
protected:
  CPtr<T> pOwner;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(IPFState*)this); f.Add(2,&started); f.Add(3,&pOwner); return 0; }
};

class PFBaseUnitState : public TPFState<PFBaseUnit>, public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS( 0x8D7C1AC0, PFBaseUnitState )

protected:
	PFBaseUnitState() {}
	virtual void DumpState( const char* state );

public:
	PFBaseUnitState( PFBaseUnit* unit );
	ZDATA_(TPFState<PFBaseUnit>)
	ZPARENT(PFWorldObjectBase)
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(TPFState<PFBaseUnit>*)this); f.Add(2,(PFWorldObjectBase*)this); return 0; }
	virtual bool NeedToBeStepped() { return false; }
};

class PFBaseMovingUnitState : public TPFState<PFBaseMovingUnit>, public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS( 0x8D7C1AC1, PFBaseMovingUnitState )

protected:
	PFBaseMovingUnitState() {}
	virtual void DumpState( const char* state );

public:
	PFBaseMovingUnitState( PFBaseMovingUnit* unit );
	ZDATA_(TPFState<PFBaseMovingUnit>)
	ZPARENT(PFWorldObjectBase)
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(TPFState<PFBaseMovingUnit>*)this); f.Add(2,(PFWorldObjectBase*)this); return 0; }
	virtual bool NeedToBeStepped() { return false; }
};

class PFBaseHeroState : public TPFState<PFBaseHero>, public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS( 0x8D7C1AC2, PFBaseHeroState )

protected:
	PFBaseHeroState() {}
	virtual void DumpState( const char* state );

public:
	PFBaseHeroState( PFBaseHero* unit );
	ZDATA_(TPFState<PFBaseHero>)
	ZPARENT(PFWorldObjectBase)
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(TPFState<PFBaseHero>*)this); f.Add(2,(PFWorldObjectBase*)this); return 0; }
	virtual bool NeedToBeStepped() { return false; }
};

class PFMainBuildingState : public TPFState<PFMainBuilding>, public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS( 0x8D7C1AC3, PFMainBuildingState )

protected:
	PFMainBuildingState() {}
	virtual void DumpState( const char* state );

public:
	PFMainBuildingState( PFMainBuilding* unit );
	ZDATA_(TPFState<PFMainBuilding>)
	ZPARENT(PFWorldObjectBase)
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(TPFState<PFMainBuilding>*)this); f.Add(2,(PFWorldObjectBase*)this); return 0; }
	virtual bool NeedToBeStepped() { return false; }
};

class PFBasePetUnitState : public TPFState<PFBasePetUnit>, public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS( 0x8D7C1AC4, PFBasePetUnitState )

protected:
	PFBasePetUnitState() {}
	virtual void DumpState( const char* state );

public:
	PFBasePetUnitState( PFBasePetUnit* unit );
	ZDATA_(TPFState<PFBasePetUnit>)
	ZPARENT(PFWorldObjectBase)
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(TPFState<PFBasePetUnit>*)this); f.Add(2,(PFWorldObjectBase*)this); return 0; }
	virtual bool NeedToBeStepped() { return false; }
};

} // namespace NWorld
