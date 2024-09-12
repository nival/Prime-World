#pragma once

#include "PFBaseUnit.h"
#include "DBAdvMap.h"

namespace NDb
{
  struct Flagpole;
}

namespace NGameX
{
  class PFClientFlagpole;
}

namespace NWorld
{
class PFFlagpole;

class PFFlagpole : public PFBaseUnit
{
  OBJECT_ABSTRACT_METHODS( PFFlagpole );
  WORLD_OBJECT_CLIENT( NGameX::PFClientFlagpole );

public:
  PFFlagpole(PFWorld *pWorld, const NDb::AdvMapObject &_dbObject);

  bool IsNeutral() const { return ( faction == NDb::FACTION_NEUTRAL ); }

  virtual bool CanRaise( NDb::EFaction _faction ) const = 0;

  void OnStartRaise( int _teamId, const float raiseTime );
  void OnCancelRaise();
  virtual void OnRaise( NDb::EFaction _faction, PFBaseUnit * unitWhoRaised);
  virtual void OnDropFlag(PFBaseUnit * unitWhoDropped);

  virtual void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags = UNITDIEFLAGS_NONE, PFBaseUnitDamageDesc const* pDamageDesc = 0);

  virtual bool IsOutermost( const NDb::EFaction _faction ) const = 0;
  virtual bool IsProtectedByTower( const NDb::EFaction _faction ) const = 0;
  virtual bool IsProtectedByNext() const = 0;

  virtual bool IsProtected() const { return ( IsProtectedByTower(faction) || IsProtectedByNext() ); }

  bool IsRising() const { return isRising; }

  virtual const NDb::Texture* GetUiAvatarImage() const;
  virtual const wstring& GetDescription() const;

  virtual PFFlagpole* GetPrevFlagpole( const NDb::EFaction _faction ) = 0;
  virtual PFFlagpole* GetNextFlagpole( const NDb::EFaction _faction ) = 0;

  const PFFlagpole* GetPrevFlagpole( const NDb::EFaction _faction ) const;
  const PFFlagpole* GetNextFlagpole( const NDb::EFaction _faction ) const;

	virtual void Reset();
	virtual void OnAfterReset();
  virtual void Hide(bool hide);

protected:
  PFFlagpole() {}
  virtual float  OnDamage(const DamageDesc &desc);
  virtual void LogFlagEvent(NDb::EFaction _faction, PFBaseUnit * unit, bool raised) {}

  void UpdateVulnerable();

  static NDb::ETeamID GetTeamId( NDb::EFaction faction );
private:

  ZDATA_(PFBaseUnit)
  bool lastSetVulnerable;
  bool isRising;
  ZNOCRC
  ZNOMAPOBJECT
  NDb::AdvMapObject dbObject;
  vector<SVector> occupiedTiles;
  ZNOMAPOBJECTEND
  ZNOCRCEND
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseUnit*)this); f.Add(2,&lastSetVulnerable); f.Add(3,&isRising);  if(!f.IsChecksum()){  if(!IsMapObject()){ f.Add(4,&dbObject); f.Add(5,&occupiedTiles);  }  } return 0; }

}; // End of PFFlagpole

} // End of namespace NWorld
