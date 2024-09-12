#pragma once

#include "MinigameWorldObject.h"

namespace PF_Minigames
{

class ClinicBonus;
class ClinicCreep;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ClinicPlayer : public MinigameWorldObject 
{
	OBJECT_METHODS( 0x9A678C03, ClinicPlayer )

public:
	ClinicPlayer();
	virtual ~ClinicPlayer();

	void SetClinic( Clinic* _clinic );
	Clinic* GetClinic();

	ClinicCreep* GiveToPlayer( ClinicPlace* _clinicPlace, ClinicCreep* _clinicCreep );
	void GiveToPlayer( ClinicBonus* _clinicBonus );

	ClinicCreep* GetCreep();	
	ClinicBonus* GetBonus();	

	void MoveTo( MinigameWorldObject* _targetObject, float _velocity, float _tolerance, bool pushBack = true );
  void CancelQueue();

	// from MinigameWorldObject
	virtual void Step( float deltaTime );
	virtual void Clear();

  virtual bool ReceiveClicks() { return false; }

  virtual const Placement& GetTarget( bool& goInstantly ) const;
  virtual float GetLinearVelocity() const;

private:
	struct DestDesc
	{
    ZDATA
		CPtr<MinigameWorldObject> targetObject;

    float velocity;
		float tolerance;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&targetObject); f.Add(3,&velocity); f.Add(4,&tolerance); return 0; }
		DestDesc() : velocity(1.f), tolerance(1.f) {}
	};

	typedef nstl::list<DestDesc> Destinations;

  ZDATA_(MinigameWorldObject)
	Destinations destinations;

	CPtr<Clinic> clinic;
	CPtr<ClinicCreep> creep;
	CPtr<ClinicBonus> bonus;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(MinigameWorldObject*)this); f.Add(2,&destinations); f.Add(3,&clinic); f.Add(4,&creep); f.Add(5,&bonus); return 0; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ClinicPlayer::SetClinic( Clinic* _clinic ) { clinic = _clinic; }
inline Clinic* ClinicPlayer::GetClinic() { return clinic; }

} // namespace PF_Minigames

