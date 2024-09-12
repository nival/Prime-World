#pragma once

#include "../PF_Core/World.h"
#include "../PF_Core/ClientObject.h"
#include "../PF_Core/WorldObject.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
	class PFBaseUnit;
	class TileMap;
	class PFVoxelMap;
} // namespace NWorld
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EBaseUnitEvent
{
	BASEUNITEVENT_MOVE = 0,
	BASEUNITEVENT_CASTMAGIC = 1,
	BASEUNITEVENT_USECONSUMABLE = 2,
	BASEUNITEVENT_USEAMULET = 3,
	BASEUNITEVENT_ATTACK = 4,
	BASEUNITEVENT_FORBIDMOVE = 5,
	BASEUNITEVENT_FORBIDATTACK = 6,
	BASEUNITEVENT_FORBIDCAST = 7,
	BASEUNITEVENT_FORCEDMOVE = 8,
	BASEUNITEVENT_DISPATCHAPPLIED = 9,
	BASEUNITEVENT_DISPATCHEVADED = 10,
	BASEUNITEVENT_DAMAGE = 11,
	BASEUNITEVENT_ISOLATE = 12,
	BASEUNITEVENT_APPLICATORSTEP = 13,
	BASEUNITEVENT_APPLICATORAPPLIED = 14,
	BASEUNITEVENT_DEATH = 15,
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EForbidType
{
	FORBIDTYPE_MOVE = 0,
	FORBIDTYPE_SELECTTARGET = 1,
	FORBIDTYPE_ATTACK = 2,
	FORBIDTYPE_CAST_ABILITY1 = 3,
	FORBIDTYPE_CAST_ABILITY2 = 4,
	FORBIDTYPE_CAST_ABILITY3 = 5,
	FORBIDTYPE_CAST_ABILITY4 = 6,
	FORBIDTYPE_TAKEDAMAGE = 7,
	FORBIDTYPE_AUTOTARGETME = 8,
	FORBIDTYPE_USECONSUMABLES = 9,
	FORBIDTYPE_USEAMULETS = 10,
	FORBIDTYPE_INVISIBLE = 11,
	FORBIDTYPE_CANSEEINVISIBLE = 12,
	FORBIDTYPE_STUN = 13,
	FORBIDTYPE_LIFERESTORE = 14,
	FORBIDTYPE_ENERGYRESTORE = 15,
	FORBIDTYPE_IGNOREINVISIBLE = 16,
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EStat
{
	STAT_LIFE = 0,
	STAT_ENERGY = 1,
	STAT_POWER = 2,
	STAT_RANGE = 3,
	STAT_ENERGYDEFENCE = 4,
	STAT_SUBSTANCEDEFENCE = 5,
	STAT_MOVESPEED = 6,
	STAT_ATTACKSPEED = 7,
	STAT_CRITICALCHANCE = 8,
	STAT_CRITICALMULTIPLIER = 9,
	STAT_LIFEDRAIN = 10,
	STAT_ENERGYDRAIN = 11,
	STAT_EVASION = 12,
	STAT_LIFEREGENERATION = 13,
	STAT_LIFEREGENERATIONABSOLUTE = 14,
	STAT_ENERGYREGENERATION = 15,
	STAT_ENERGYREGENERATIONABSOLUTE = 16,
	STAT_ARMOR = 17,
	STAT_ABILITYPROBABILITY = 18,
	STAT_GAINEDEXPERIENCEMULTIPLIER = 19,
	STAT_EXPERIENCEFORKILL = 20,
	STAT_GOLDFORKILL = 21,
	STAT_TEAMGOLDFORKILL = 22,
	STAT_VISIBILITYRANGE = 23,
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct AILogicParameters
{
	float baseMoveSpeed;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Unit
{
	float objectSize;
	int objectTileSize;
	bool isRounded;

	Unit( float _objectSize, int _objectTileSize, bool _isRounded ) :
		objectSize( _objectSize ), objectTileSize( _objectTileSize ), isRounded( _isRounded ) {}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ObjectCollision
{
	float xMin;
	float xMax;
	float yMin;
	float yMax;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ObjectLockItem
{
	int x;
	int y;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ObjectLockMask
{
	float tileSize;
	vector<ObjectLockItem> mask;
};
} // namespace NDb
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NGameX
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFClientBaseUnit : public PF_Core::ClientObjectBase
{
	CLIENT_OBJECT_WORLD( PFClientBaseUnit, NWorld::PFBaseUnit )

  bool isMoving;
  CVec3 position;

public:
	virtual void OnMoveTo( const CVec3& newpos, bool animate = true ) { position = newpos; isMoving = true; }
	virtual void OnStop() { isMoving = false; }
	virtual void OnTeleportTo(CVec3 const& target) { position = target; isMoving = false; }

  bool IsMoving() const { return isMoving; }
  const CVec3& GetPosition() const { return position; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFClientBaseMovingUnit : public PFClientBaseUnit
{
	OBJECT_METHODS( 0x1E59D440, PFClientBaseMovingUnit )
public:
	PFClientBaseMovingUnit() {}
	PFClientBaseMovingUnit( PF_Core::WorldObjectBase* worldObject ) { }
};
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
class PFWorld : public PF_Core::IWorld
{
  OBJECT_METHODS( 0x2C5BDC80, PFWorld );

	NDb::AILogicParameters aiParams;
	NCore::RandomGenerator rnd;
	CObj<PFVoxelMap> voxelMap;
	CObj<TileMap> tileMap;
	vector<CObj<PF_Core::WorldObjectBase>> objects;
public:
	PFWorld() {}

	// mapSize defines size in tile its 820x820 for currently used PFMap or 16x16 for PlaneMap
	// metersPerTile
	PFWorld( const SVector& mapSize, float baseMoveSpeed );

	virtual void RegisterObject(PF_Core::WorldObjectBase* pObject, bool immediately);
	virtual void UnregisterObject(PF_Core::WorldObjectBase* pObject);
	virtual CPtr<PF_Core::IWorldObject> GetObjectById(int id) const { return 0; }

	// IWorld implementation
	virtual void ExecuteCommand( NCore::WorldCommand* pCommand ) { }
	virtual IPointerHolder* GetPointerSerialization() { return 0; }

	// behavior of this function in real-game is different
	virtual bool Step( float dtInSeconds, float dtLocal );

	virtual void SetAccounting( Lobby::Accounting*) {}
	virtual void SetCRCThread(CObj<NCore::CRCThread>&) {}
	virtual void DumpObjectsNames(const char *) const {}
	virtual void SetSlowdownHint(float) {}
	virtual float GetSlowdownHint() const { return 1.0f; }

	virtual bool ProcessAddRemove() { return true; }

	virtual NCore::RandomGenerator *GetRndGen() { return &rnd; }

	void RegisterInAIWorld( PFBaseUnit* pObject );

	TileMap* GetTileMap() const;
	PFVoxelMap* GetVoxelMap() const;
	const NDb::AILogicParameters& GetAIParameters() const { return aiParams; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFDispatchUniformLinearMove : public CObjectBase
{
	OBJECT_METHODS(0x1E5C64C1, PFDispatchUniformLinearMove)
public:
	seDECLARE_CPTRRING( PFDispatchUniformLinearMove, unitDispatchesPart, UnitDispatchesRing );
	virtual void OnTargetTeleport() { }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFVisMap
{
public:
	void  OnMove( CVec3 const& position) { }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitEvent
{
public:
	PFBaseUnitEvent( NDb::EBaseUnitEvent ev ) { }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFLogicObject : public PF_Core::WorldObjectBase
{
protected:
	PFLogicObject() { }

	CVec3 position;

public:
	PFLogicObject( PFWorld* pWorld, const CVec3& pos );

	seDECLARE_COBJRING(PFLogicObject, ringField,      LORing);
	seDECLARE_CPTRRING(PFLogicObject, visMapRingPart, VisMapLORing);

	const CVec3& GetPosition() const { return position; }
	PFWorld* GetWorld() const { return static_cast<PFWorld*>(PF_Core::WorldObjectBase::GetWorld()); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnit : public PFLogicObject
{
	WORLD_OBJECT_METHODS(0xE5CBCC0, PFBaseUnit, NGameX::PFClientBaseUnit);

protected:
	PFBaseUnit() { }

	float objectSize;
	int objectTileSize;
	bool isRounded;
	PFVisMap visMap;
public:
	PFBaseUnit( PFWorld* pWorld, const CVec3& pos, const NDb::Unit* unitDesc );

	float GetObjectSize() const { return objectSize; }
	int GetObjectTileSize() const { return objectTileSize; }
	bool IsDead() const { return false; }
  char const* GetDebugDescription() const { return 0; }
	unsigned int EventHappened(const PFBaseUnitEvent &evt) { return 0; }
	virtual void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags) { }
	const float PFBaseUnit::GetStatValue( NDb::EStat const stat ) const { return 1.0f; }
	bool PFBaseUnit::CheckForbidType(NDb::EForbidType type) const { return false; }

	TileMap* GetTileMap() const { return GetWorld()->GetTileMap(); }
	PFVoxelMap* GetVoxelMap() const { return GetWorld()->GetVoxelMap(); }
	const NDb::AILogicParameters& GetAIParameters() const { return GetWorld()->GetAIParameters(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TUnit>
bool IsUnitValid(CPtr<TUnit> const& pUnit)
{
	return IsValid(pUnit) && !pUnit->IsDead();
}
} // namespace NWorld