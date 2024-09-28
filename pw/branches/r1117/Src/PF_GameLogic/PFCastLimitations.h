#pragma once


struct ICustomFormulaPars;

namespace NWorld
{

class PFAbilityData;

class PFPositionObject : public ICustomFormulaPars
{
public:
  PFPositionObject(){}
  explicit PFPositionObject(const CVec3& objPos) : pos(objPos){}

  virtual CVec2 GetPos2D() const
  {
    return pos.AsVec2D();
  }

  ZNOPARENT(ICustomFormulaPars)
private:
  CVec3 pos;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,&pos);  return 0; }
};

class CastLimitationsCheckParams
{
public:
	CastLimitationsCheckParams( const PFAbilityData& ability, const Target& target ) : pAbility( &ability ), pTarget( &target ) {}

	const PFAbilityData* pAbility;
	const Target* pTarget;
};

const PFAbilityData* CheckTargetLimitation(    NDb::TargetCastLimitation    const& dbLimit, CastLimitationsCheckParams const& cp );
const PFAbilityData* CheckConditionLimitation( NDb::ConditionCastLimitation const& dbLimit, CastLimitationsCheckParams const& cp );
const PFAbilityData* CheckDispellLimitation(   NDb::DispellCastLimitation   const& dbLimit, CastLimitationsCheckParams const& cp );
const PFAbilityData* CheckPositionLimitation(   NDb::PositionCastLimitation   const& dbLimit, CastLimitationsCheckParams const& cp );

}
