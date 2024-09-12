// Unified target for commands and game logic
#pragma once

#include "LuaValueSettable.h"

namespace NWorld
{
class PFBaseUnit;
class PFLogicObject;

template<typename TUnit>
bool IsUnitValid( const TUnit * pUnit )
{
  return IsValid( pUnit ) && !pUnit->IsDead();
}

template<typename TUnit>
bool IsUnitValid( const CPtr<TUnit> & unit )
{
  return IsUnitValid( unit.GetPtr() );
}

template<typename TUnit>
bool IsUnitValid( const CObj<TUnit> & unit )
{
  return IsUnitValid( unit.GetPtr() );
}

template<typename TUnit>
bool IsTargetValid( const TUnit * pTarget )
{
  return IsUnitValid( pTarget ) && pTarget->IsVulnerable();
}

template<typename TUnit>
bool IsTargetValid( const CPtr<TUnit> & target )
{
  return IsTargetValid( target.GetPtr() );
}

template<typename TObject>
bool IsObjectValid( const TObject pObject )
{
  return IsValid(pObject) && !pObject->IsObjectDead();
}

template<typename TObject>
bool IsObjectValid( const CPtr<TObject> & object )
{
  return IsObjectValid( object.GetPtr() );
}


class Target : public ILuaValueSettable
{
public:

  LUA_VALUE_SETTABLE_DECLARE

	enum TARGET_TYPE
	{
		INVALID = -1,
		UNIT,
		OBJECT,
		POSITION
	};

	enum 
	{
		FLAG_UNIT = 1 << UNIT,
		FLAG_OBJECT = 1 << OBJECT,
		FLAG_POSITION = 1 << POSITION,
		FLAG_ALL = (FLAG_UNIT | FLAG_OBJECT | FLAG_POSITION)
	};

	Target() : type(INVALID), vPosition(VNULL3) {}
	explicit Target(CVec3 _vPosition) : pUnit(NULL), vPosition(_vPosition), type(POSITION) {}
  explicit Target(CVec2 _vPosition) : pUnit(NULL), vPosition(_vPosition, 0.0f), type(POSITION) {}
  explicit Target(PFBaseUnit * _pUnit);
  explicit Target(PFLogicObject * _pObject);
  explicit Target(PFLogicObject * _pObject, CVec3 _vPosition);

  // Checkers
  bool IsObject() const { return type == OBJECT || type == UNIT; }
  bool IsUnit() const { return type == UNIT; }
  bool IsPosition() const { return type == POSITION; }
  bool IsUnitValid(bool deadUnitsAllowed = false) const;
  bool IsObjectValid(bool deadUnitsAllowed = false) const;
  bool IsValid(bool deadUnitsAllowed = false) const { return IsPosition() || IsObjectValid(deadUnitsAllowed); }
  bool IsUnitMounted(bool deadUnitsAllowed = false) const;

	TARGET_TYPE GetType() const { return type; }

	bool IsVisibleForFaction( const PFWorld* world, int faction ) const;

  // Access to real target
  CPtr<PFBaseUnit> const &GetUnit() const
  {
    NI_ASSERT(IsUnit(), "You should check target type before access");
    return pUnit;
  }
  CPtr<PFLogicObject> const & GetObject() const
  {
    NI_ASSERT( IsObject()||IsUnit() , "You should check target type before access" );
    return pObject;
  }
  const CVec3& GetPosition() const
  {
    NI_ASSERT(IsPosition(), "You should check target type before access");
    return vPosition;
  }
  CVec2 GetPos() const { return vPosition.AsVec2D(); }
  CVec3 AcquirePosition() const;
  CVec3 MakeTargetingPos(const char *locator = NULL) const;
  void SetPosition(const CVec3 &pos);
  void SetUnit(const CPtr<PFBaseUnit> &pUnit_);

	bool operator==(const Target &targ) const
	{
		if (GetType() != targ.GetType())
			return false;

		if (GetType() != Target::POSITION)
		{
			return GetObject() == targ.GetObject();
		}
		else
		{
			return fabs2(GetPosition() - targ.GetPosition()) < 1.0e-6f;
		}
	}

  virtual NDb::AlternativeTarget const* GetDBAlternativeTarget() const { return 0; }
  virtual void SetDBAlternativeTarget( NDb::AlternativeTarget const* ) { }

protected:
  friend class AbilityTarget;

  ZDATA
  ZNOPARENT( ILuaValueSettable )
  CPtr<PFBaseUnit>    pUnit;
  CPtr<PFLogicObject> pObject;
  CVec3               vPosition;
	TARGET_TYPE					type;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&pUnit); f.Add(3,&pObject); f.Add(4,&vPosition); f.Add(5,&type); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AbilityTarget : public Target
{
public:
  virtual NDb::AlternativeTarget const* GetDBAlternativeTarget() const { return dbAlternativeTarget; }
  virtual void SetDBAlternativeTarget( NDb::AlternativeTarget const* dbAlternativeTarget_ ) { dbAlternativeTarget = dbAlternativeTarget_; }
  AbilityTarget() : Target() {}
  AbilityTarget( Target const& target );
  explicit AbilityTarget(PFLogicObject * _pObject, CVec3 _vPosition, NDb::AlternativeTarget const* dbAlternativeTarget_ );

private:
  ZDATA_(Target)
  NDb::Ptr<NDb::AlternativeTarget> dbAlternativeTarget;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(Target*)this); f.Add(2,&dbAlternativeTarget); return 0; }
};

}
