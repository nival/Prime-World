#pragma once

#include "Minigames.h"
#include "MinigameWorldObject.h"

namespace PF_Minigames
{

class ClinicCreep;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CreepState : public CObjectBase
{
	OBJECT_ABSTRACT_METHODS( CreepState );
public:
	CreepState();
	virtual ~CreepState();

	void SetCreep( ClinicCreep* _creep );
	virtual CreepState* Step( float deltaTime ) = 0;

	virtual float GetStateProgress();
  virtual bool IsWaiting() { return false; }
  virtual bool IsWorking() { return false; }
	
	virtual void WantAtAnyPlace();
	virtual void OnWakeUp();
	virtual bool IsSleeping() const;

  virtual bool IsInPlaceCreepWants() const { return false; }

	virtual wstring GetText() const = 0;

protected:
	virtual void Init();

	CPtr<ClinicCreep> creep;

  ZDATA
  ZNOPARENT(CObjectBase)
	float	currentTime;	
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&currentTime); return 0; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CreepState::GetStateProgress() { return 0.f; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CreepThinks : public CreepState
{
	OBJECT_METHODS( 0x9D61B400, CreepThinks )
public:
	CreepThinks();
	virtual ~CreepThinks();

	virtual void WantAtAnyPlace();

	virtual wstring GetText() const;
	virtual CreepState* Step( float deltaTime );

protected:
	virtual void Init();

  ZDATA_(CreepState)
	float duration;
	bool wantToAnyPlace;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(CreepState*)this); f.Add(2,&duration); f.Add(3,&wantToAnyPlace); return 0; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CreepWaits : public CreepState
{
	OBJECT_METHODS( 0x9D61B401, CreepWaits )
public:
	CreepWaits();
	virtual ~CreepWaits();

  virtual float GetStateProgress();
  virtual bool IsWaiting() { return true; }

  virtual void WantAtAnyPlace();
	virtual void OnWakeUp();
	virtual bool IsSleeping() const;
  virtual bool IsInPlaceCreepWants() const;

	virtual wstring GetText() const;
	virtual CreepState* Step( float deltaTime );

protected:
	virtual void Init();
	
  ZDATA_(CreepState)
	float currentTimeUntilSleep;
	float currentTimeUntilWakeup;
	float durationWaitPhase;
	float durationUntilAsleep;
	float durationUntilWakeup;
	bool wakingUp;
	bool comfortableCarpetUsed;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(CreepState*)this); f.Add(2,&currentTimeUntilSleep); f.Add(3,&currentTimeUntilWakeup); f.Add(4,&durationWaitPhase); f.Add(5,&durationUntilAsleep); f.Add(6,&durationUntilWakeup); f.Add(7,&wakingUp); f.Add(8,&comfortableCarpetUsed); return 0; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CreepWorks : public CreepState
{
	OBJECT_METHODS( 0x9D61B402, CreepWorks )
public:
	CreepWorks();
	virtual ~CreepWorks();

  virtual bool IsWorking() { return true; }
  virtual float GetStateProgress();

	virtual wstring GetText() const;
	virtual CreepState* Step( float deltaTime );

protected:
	virtual void Init();
  ZDATA_(CreepState)
	bool friendNearChecked;
	float durationWorkPhase;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(CreepState*)this); f.Add(2,&friendNearChecked); f.Add(3,&durationWorkPhase); return 0; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CreepWantsOut : public CreepState
{
	OBJECT_METHODS( 0x9D61B403, CreepWantsOut )
public:
	CreepWantsOut();
	virtual ~CreepWantsOut();

	virtual bool IsWaiting() { return true; }

	virtual wstring GetText() const;
	virtual CreepState* Step( float deltaTime );

protected:
	virtual void Init();
  ZDATA_(CreepState)
	float durationWaitPhase;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(CreepState*)this); f.Add(2,&durationWaitPhase); return 0; }
};

} // namespace PF_Minigames

