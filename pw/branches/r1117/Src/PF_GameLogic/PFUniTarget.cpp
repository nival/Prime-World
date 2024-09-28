// Unified target for commands and game logic

#include "stdafx.h"
#include "PFUniTarget.h"

#include "PFBaseUnit.h"

#ifndef VISUAL_CUTTED
#include "PFClientLogicObject.h"
#endif

#include "TileMap.h"
#include "WarFog.h"

namespace NWorld
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Target::Target(PFLogicObject * _pObject) 
	: pObject(_pObject), vPosition(0.0f, 0.0f, 0.0f)
{
	PFBaseUnit* pBaseUnit = dynamic_cast<PFBaseUnit*>(_pObject);
	if (pBaseUnit)
	{
		pUnit = pBaseUnit;
		type  = UNIT;
	}
	else
		type  = OBJECT;
}

// Auto-ctor, for simple use
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Target::Target(PFLogicObject * _pObject, CVec3 _vPosition)
  : vPosition(_vPosition)
  , type(POSITION)
{
  if ( ::IsValid(_pObject) )
  {
    pObject = _pObject;
    PFBaseUnit* pBaseUnit = dynamic_cast<PFBaseUnit*>(_pObject);
    if ( pBaseUnit )
    {
      pUnit = pBaseUnit;
      type = UNIT;
    }
    else
    {
      type = OBJECT;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Target::Target(PFBaseUnit * _pUnit)
  : pUnit(_pUnit)
  , pObject( _pUnit )
  , vPosition(0.0f, 0.0f, 0.0f)
  , type(UNIT)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 Target::AcquirePosition() const
{
  NI_VERIFY(IsValid(true), "Target is invalid", return VNULL3; );

  if (type == POSITION)
		return vPosition;
	else
		return pObject->GetPosition();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 Target::MakeTargetingPos(const char *locator) const
{
	if (type == POSITION)
		return vPosition; // ktodo is it correct?
	else
  {
#ifndef VISUAL_CUTTED
    if (IsValid(pObject->ClientObject()) && pObject->ClientObject()->IsVisible())
    {
      CVec3 pos;
      pObject->ClientObject()->MakeTargetingPos(pos);
      
      if (locator && strlen(locator) > 0)
      {
        NScene::SceneObject* pSO = pObject->GetClientSceneObject();
        if (pSO)
        {
          NScene::Locator const *pLocator = pSO->FindLocator( locator );
          if (pLocator)
          {
            pSO->CalculateLocatorWorldPosition(*pLocator, pos, true );
          }
        }
      }

      return pos;
    }
#endif
    //NI_ALWAYS_ASSERT(""); // ktodo is it needed?
    return pObject->GetPosition();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Target::SetUnit(const CPtr<PFBaseUnit> &pUnit_)
{
	pUnit   = pUnit_;
	pObject = pUnit_;
	type    = UNIT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Target::SetPosition(const CVec3 &pos)
{
	pUnit     = NULL;
	pObject   = NULL;
  vPosition = pos;
	type      = POSITION;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Target::IsUnitValid(bool deadUnitsAllowed) const { return IsUnit() && ::IsValid( pUnit.GetPtr() ) && ( deadUnitsAllowed || !pUnit->IsDead() ); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Target::IsObjectValid(bool deadUnitsAllowed) const { return IsUnit() ? IsUnitValid(deadUnitsAllowed) : (IsObject() && NWorld::IsObjectValid(pObject) ); }

bool Target::IsVisibleForFaction( const PFWorld* world, int faction ) const
{
	if ( IsUnit() )
		return GetUnit()->IsVisibleForFaction( faction );
	if ( IsObject() )
		return GetObject()->IsVisibleForFaction( faction );
	if ( IsPosition() )
	{
		if ( world )
		{
			SVector tilePos = world->GetTileMap()->GetTile( GetPosition().AsVec2D() );
			return world->GetFogOfWar()->IsTileVisible( tilePos, faction );
		}
	}
	return false;
}

bool Target::IsUnitMounted(bool deadUnitsAllowed) const
{
  return IsUnit() ? IsUnitValid(deadUnitsAllowed) && GetUnit()->IsMounted(): false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AbilityTarget::AbilityTarget( Target const& target )
{
  pUnit = target.pUnit;
  pObject = target.pObject;
  vPosition = target.vPosition;
  type = target.type;
  dbAlternativeTarget = target.GetDBAlternativeTarget();
}

AbilityTarget::AbilityTarget(PFLogicObject * _pObject, CVec3 _vPosition, NDb::AlternativeTarget const* dbAlternativeTarget_ )
: Target( _pObject, _vPosition ), dbAlternativeTarget(dbAlternativeTarget_)
{
}


} // namespace NWorld
