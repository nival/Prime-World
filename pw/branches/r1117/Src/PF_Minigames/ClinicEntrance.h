#pragma once

#include "MinigameWorldObject.h"
#include "MinigamesMain.h"

namespace NDb
{
	struct PlaceDesc;
}

namespace PF_Minigames
{

class Clinic;
class ClinicCreep;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ClinicEntrance : public MinigameWorldObject 
{
	OBJECT_METHODS( 0x9A678C00, ClinicEntrance )

public:
	ClinicEntrance();
	virtual ~ClinicEntrance();

  void SetPlaceDesc( const NDb::PlaceDesc * desc ) { placeDesc = desc; }
  const NDb::PlaceDesc * GetPlaceDesc() const { return placeDesc; }

	void SetClinic( Clinic* _clinic );
	void SetCreepsNumber( int _numMelee, int _numRange, int _numSiege );
	void StopQueue();

  bool IsInRoute() const;

	// from MinigameWorldObject
	virtual void Step( float deltaTime );
	virtual bool OnClick();
	virtual bool OnTouched( MinigameWorldObject* _other );
	virtual void Clear();

private:

	CPtr<Clinic> clinic;
	CPtr<ClinicCreep> creepAtEntrance;

	struct CreepInQueueDesc
	{
		ECreepType::Enum type;
		int friendshipID;

		CreepInQueueDesc();
		explicit CreepInQueueDesc( ECreepType::Enum _type );
	};

	typedef nstl::list<CreepInQueueDesc> CreepsQueue;

  ZDATA_(MinigameWorldObject)
	CreepsQueue creepsQueue;
	bool queueStoped;
	float timeToNextCreep;
	int creepsOut;

  bool isInRoute;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(MinigameWorldObject*)this); f.Add(2,&creepsQueue); f.Add(3,&queueStoped); f.Add(4,&timeToNextCreep); f.Add(5,&creepsOut); f.Add(6,&isInRoute); return 0; }
  const NDb::PlaceDesc * placeDesc;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ClinicEntrance::SetClinic( Clinic* _clinic ) { clinic = _clinic; }
inline bool ClinicEntrance::IsInRoute() const { return isInRoute; }

} // namespace PF_Minigames

