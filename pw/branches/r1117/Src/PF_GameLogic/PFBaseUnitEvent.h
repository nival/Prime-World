#ifndef PFBASEUNITEVENT_H_INCLUDED
#define PFBASEUNITEVENT_H_INCLUDED

#include "PFApplicator.h"

namespace NDb
{
struct Unit;
}

struct lua_State;

namespace NWorld
{

struct PFBaseUnitDamageDesc;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitEvent
{
public:
	PFBaseUnitEvent(NDb::EBaseUnitEvent evt_) : evt(evt_) {}
  virtual ~PFBaseUnitEvent() {}

	NDb::EBaseUnitEvent GetType() const { return evt; }

  virtual int PushArgsForScript( lua_State *L ) const { return 0; }
  virtual bool IsEventHostileTo( PFBaseUnit const* ) const { return false; }
  virtual PFAbilityInstance const* GetAbility() const { return 0; }

protected:
	NDb::EBaseUnitEvent evt;
};

class PFBaseUnitPickupEvent : public PFBaseUnitEvent
{
public:
  PFBaseUnitPickupEvent( NDb::EBaseUnitEvent evt_, bool isGlyph, int glyphNumber, string scriptName_ ) 
  : PFBaseUnitEvent(evt_), scriptName(scriptName_), isGlyph(isGlyph), needActivate(true), glyphNumber(glyphNumber) {}
  virtual int PushArgsForScript( lua_State *L ) const;
  bool NeedActivate() const { return needActivate; }
  void SetNeedActivate( bool val ) const { needActivate = val; }
  int GetGlyphNumber() const { return glyphNumber; }

private:
  string scriptName;
  bool isGlyph;
  int glyphNumber;
  mutable bool needActivate;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitApplicatorEvent : public PFBaseUnitEvent
{
public:
	PFBaseUnitApplicatorEvent(NDb::EBaseUnitEvent evt_, const PFBaseApplicator *pAppl_) 
		: PFBaseUnitEvent(evt_), pAppl(pAppl_) {}

	const PFBaseApplicator *GetAppl() const { return pAppl; }
  virtual bool IsEventHostileTo( PFBaseUnit const* pListenerUnit ) const;

protected:
	const PFBaseApplicator *pAppl;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitDispatchEvent : public PFBaseUnitEvent
{
public:
	PFBaseUnitDispatchEvent(NDb::EBaseUnitEvent evt_, const PFDispatch *pDispatch_) 
		: PFBaseUnitEvent(evt_), pDispatch(pDispatch_), cancelDispatch(false) {}

	const PFDispatch *GetDispatch() const { return pDispatch; }
  void CancelDispatch() const { cancelDispatch = true; }
  bool IsDispatchCancelled() const { return cancelDispatch; }

protected:
	const PFDispatch *pDispatch;
  mutable bool cancelDispatch;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitUseAbilityEvent : public PFBaseUnitEvent
{
public:
  PFBaseUnitUseAbilityEvent(NDb::EBaseUnitEvent evt, PFAbilityInstance const* pAbility) 
    : PFBaseUnitEvent(evt), pAbility(pAbility) {}

  virtual PFAbilityInstance const* GetAbility() const { return pAbility; }
  virtual int PushArgsForScript( lua_State *L ) const;
protected:
  PFAbilityInstance const* pAbility;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitAbilityStartEvent : public PFBaseUnitEvent
{
public:
  PFBaseUnitAbilityStartEvent( PFAbilityInstance const* pAbility ) 
    : PFBaseUnitEvent(NDb::BASEUNITEVENT_ABILITYSTART), pAbility(pAbility) {}

  virtual PFAbilityInstance const* GetAbility() const { return pAbility; }
  virtual int PushArgsForScript( lua_State *L ) const;
protected:
  PFAbilityInstance const* pAbility;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitApplicatorAppliedEvent : public PFBaseUnitEvent
{
public:
  PFBaseUnitApplicatorAppliedEvent(PFBaseApplicator* pApplicator) 
    : PFBaseUnitEvent(NDb::BASEUNITEVENT_APPLICATORAPPLIED), pApplicator(pApplicator), cancelApplicator(false) {}

  PFBaseApplicator* GetApplicator() const { return pApplicator; }

  void CancelApplicator() const { cancelApplicator = true; }
  bool IsApplicatorCancelled() const { return cancelApplicator; }

protected:
  PFBaseApplicator* pApplicator;
  mutable bool cancelApplicator;
};

class PFBaseUnitEventUnitDeath : public PFBaseUnitEvent // sends to all heroes around dieing unit
{
public:
  PFBaseUnitEventUnitDeath( 
    CPtr<PFBaseUnit> const& _pVictim, 
    CPtr<PFBaseUnit> const& _pKiller, 
    CPtr<PFBaseUnit> const& _pQualifiedKiller, 
    bool bUnsummoned = false )
    : PFBaseUnitEvent( bUnsummoned ? NDb::BASEUNITEVENT_UNSUMMON : NDb::BASEUNITEVENT_DEATH )
    , pVictim(_pVictim)
    , pKiller(_pKiller)
    , pQualifiedKiller(_pQualifiedKiller)
  {
  }
  CPtr<PFBaseUnit> const& GetVictim() const { return pVictim; }
  CPtr<PFBaseUnit> const& GetKiller() const { return pKiller; }
  CPtr<PFBaseUnit> const& GetQualifiedKiller() const { return pQualifiedKiller; }

  virtual bool IsEventHostileTo( PFBaseUnit const* pListenerUnit ) const { return pListenerUnit == pVictim; } // Actually meaningless for such event
  virtual int PushArgsForScript( lua_State *L ) const;

private:
  CPtr<PFBaseUnit> pVictim;
  CPtr<PFBaseUnit> pKiller;
  CPtr<PFBaseUnit> pQualifiedKiller;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitLastHitEvent : public PFBaseUnitEvent
{
public:
  PFBaseUnitLastHitEvent( CPtr<PFBaseUnit> const& pAttacker )
    : PFBaseUnitEvent(NDb::BASEUNITEVENT_LASTHIT), pAttacker(pAttacker) {}

  CPtr<PFBaseUnit> const& GetAttacker() const { return pAttacker; }
  virtual bool IsEventHostileTo( PFBaseUnit const* ) const { return true; }
private:
  CPtr<PFBaseUnit> pAttacker;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFOutgoingDamageEvent : public PFBaseUnitEvent
{
public:
  PFOutgoingDamageEvent( const PFBaseUnit * _pTaker, const PFBaseUnitDamageDesc &desc, float _damage )
    : PFBaseUnitEvent(NDb::BASEUNITEVENT_OUTGOINGDAMAGE), pTaker(_pTaker), pDesc(&desc), damage(_damage) {}

  const PFBaseUnitDamageDesc * pDesc;
  const PFBaseUnit * pTaker;
  mutable float damage;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitEventListener : public IObjectBase
{
public:

  PFBaseUnitEventListener() : isAlive(true) {}

	enum 
	{
		FLAGS_REMOVE = (1 << 1)
	};

  enum EListenerType
  {
    LISTENER_DEFAULT = 0,
    LISTENER_SHIELD,
    LISTENER_DAMAGETRIGGER,
  };

	virtual unsigned int OnEvent(const PFBaseUnitEvent *pEvent) = 0;
  virtual float GetListenerPriority() const { return 0; }
  virtual EListenerType GetListenerType() const { return LISTENER_DEFAULT; }

  bool IsAlive(){return isAlive;}
  void SetAlive(bool isAliveOrNot) {isAlive = isAliveOrNot;}

private:
  bool isAlive;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitHeroKillOrAssistEvent : public PFBaseUnitEvent
{
public:
  PFBaseUnitHeroKillOrAssistEvent( CPtr<PFBaseUnit> const& pAttacker )
    : PFBaseUnitEvent(NDb::BASEUNITEVENT_HEROKILLORASSIST), pAttacker(pAttacker) {}

  CPtr<PFBaseUnit> const& GetAttacker() const { return pAttacker; }
  virtual bool IsEventHostileTo( PFBaseUnit const* ) const { return true; }
private:
  CPtr<PFBaseUnit> pAttacker;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitMinigameEvent : public PFBaseUnitEvent
{
public:
  PFBaseUnitMinigameEvent( NDb::EBaseUnitEvent evt, CPtr<PFBaseUnit> _unit ) 
  : PFBaseUnitEvent(evt), unit(_unit) {}

  virtual PFBaseUnit const* GetUnit() const { return unit; }
protected:
  CPtr<PFBaseUnit> unit;
};



} // namespace NWorld

#endif //PFBASEUNITEVENT_H_INCLUDED
