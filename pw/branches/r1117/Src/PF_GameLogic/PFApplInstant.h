#pragma once

#include "PFApplicator.h"
#include "PFTargetSelector.h"
#include "PFUIEvent.h"

namespace NWorld
{

class PFWorld;
class PFBaseUnit;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplDamage: public DBLinker<PFBaseApplicator, NDb::DamageApplicator>
{
  WORLD_OBJECT_METHODS(0xE5CC385, PFApplDamage);
protected:
  ZDATA_(DBLinker)
  float damage;
  float damageDealed;
  bool  isCritical;
  bool  ignoreDefences;
  float delegatedDamage;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&damage); f.Add(3,&damageDealed); f.Add(4,&isCritical); f.Add(5,&ignoreDefences); f.Add(6,&delegatedDamage); return 0; }
  
  PFApplDamage(PFApplCreatePars const &cp);
  PFApplDamage() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
  float GetDamageDealed() const { return damageDealed; }
  virtual float GetVariable(const char* sVariableName) const;
  void SetDelegated( PFBaseUnit::DamageDesc const* desc );
protected:
  virtual bool Start();
  virtual bool Step(float /*dtInSeconds*/)
  {
    NI_ALWAYS_ASSERT("Must not get here");
    return true;
  }

  virtual void LogDamage(PFBaseUnit const * pOwner, PFBaseUnit const * pReceiver) const;

	virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
  virtual int  GetAcceptableUnitTypeFlags() const { return NDb::SPELLTARGET_ALL | NDb::SPELLTARGET_SHOP; }

  virtual void DumpInfo(NLogg::CChannelLogger &logger) const;
  CObj<NGameX::PFUITwoUnitsEvent> pUIEvent;
private:
  PFBaseUnit::DamageDesc const* delegateDamageDesc; // doesn't need to be serialized
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplHeal: public DBLinker<PFBaseApplicator, NDb::HealApplicator>
{
  WORLD_OBJECT_METHODS(0xA0617B81, PFApplHeal);
protected:
  ZDATA_(DBLinker)
  float amount;
  float amountRestored;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&amount); f.Add(3,&amountRestored); return 0; }

  PFApplHeal(PFApplCreatePars const &cp);
  PFApplHeal() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  virtual float GetVariable(const char* sVariableName) const;

  float GetAmountRestored() const { return amountRestored; }

protected:
  virtual bool Start();
  virtual bool Step(float /*dtInSeconds*/)
  {
    NI_ALWAYS_ASSERT("Must not get here");
    return true;
  }

	virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }

  NDb::Ptr<NDb::HealApplicator> pDBApplicator;
  CObj<NGameX::PFUIEvent> pUIEvent;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplKill: public DBLinker<PFBaseApplicator, NDb::KillApplicator>
{
	WORLD_OBJECT_METHODS(0x9E678B01, PFApplKill);
  ZDATA_(DBLinker)

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
	PFApplKill(PFApplCreatePars const &cp) : Base(cp) {}
	PFApplKill() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
	virtual bool Start();
	virtual bool Step(float dtInSeconds)
	{
		NI_ALWAYS_ASSERT("Must not get here");
		return true;
	}
	virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplRefreshCooldown: public DBLinker<PFBaseApplicator, NDb::RefreshCooldownApplicator>
{
  WORLD_OBJECT_METHODS(0x9E15812, PFApplRefreshCooldown);
  ZDATA_(DBLinker)

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
  PFApplRefreshCooldown(PFApplCreatePars const &cp) : Base(cp) {}
  PFApplRefreshCooldown() {}

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds)
  {
    NI_ALWAYS_ASSERT("Must not get here");
    return true;
  }

	virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
	virtual int  GetAcceptableUnitTypeFlags() const { return NDb::SPELLTARGET_HEROFEMALE | NDb::SPELLTARGET_HEROMALE; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplSpell: public DBLinker<PFBaseApplicator, NDb::SpellApplicator>
{
	WORLD_OBJECT_METHODS(0x9E677241, PFApplSpell);
protected:
  ZDATA_(DBLinker)
  int numSpellsSent;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&numSpellsSent); return 0; }
	PFApplSpell(PFApplCreatePars const &cp) : Base(cp), numSpellsSent(0) {}
	PFApplSpell() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  float GetVariable(const char* sVariableName) const;

protected:
	CVec3 pos;

	virtual bool Start();
	virtual bool Step(float dtInSeconds)
	{
		NI_ALWAYS_ASSERT("Must not get here");
		return true;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplAbilityEnd: public DBLinker<PFBaseApplicator, NDb::AbilityEndApplicator>
{
  WORLD_OBJECT_METHODS(0xB75FB80, PFApplAbilityEnd);
  ZDATA_(DBLinker)

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
  PFApplAbilityEnd(PFApplCreatePars const &cp) : Base(cp) {}
  PFApplAbilityEnd() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds)
  {
    NI_ALWAYS_ASSERT("Must not get here");
    return true;
  }
  virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplDispell: public DBLinker<PFBaseApplicator, NDb::DispellApplicator>
{
	WORLD_OBJECT_METHODS(0x9E67DB01, PFApplDispell);
  ZDATA_(DBLinker)
  int effectsDispelled;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&effectsDispelled); return 0; }
	PFApplDispell(PFApplCreatePars const &cp) : Base(cp), effectsDispelled(0) {}
	PFApplDispell() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  static int SearchStatus2Dispell(const vector<const PFBaseUnit*> &targetsToDispell, const int dispellFactionFlags, const Target& requester, vector<PFBaseApplicator*> &statuses);

  float GetVariable(const char* sVariableName) const;

protected:
	virtual bool Start();
	virtual bool Step(float dtInSeconds)
	{
		NI_ALWAYS_ASSERT("Must not get here");
		return true;
	}
  virtual int GetAcceptableTargetFlags() const { return Target::FLAG_UNIT | Target::FLAG_POSITION; }

	int DispellOneEffect( const int dispellFactionFlags, const vector<const PFBaseUnit*> &targetsToDispell );
};

class PFUIMessageApplicator : public DBLinker<PFBaseApplicator, NDb::UIMessageApplicator> 
{
  WORLD_OBJECT_METHODS(0x2C6C83C3, PFUIMessageApplicator);
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
  
  PFUIMessageApplicator(PFApplCreatePars const& cp);

  virtual bool CanBeAppliedOnDead() {return true;}
private:
  explicit PFUIMessageApplicator() {}
  virtual bool Start();
};

class PFResurrectApplicator : public DBLinker<PFBaseApplicator, NDb::ResurrectApplicator> 
{
  WORLD_OBJECT_METHODS(0x2C6C8441, PFResurrectApplicator);
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFResurrectApplicator(PFApplCreatePars const& cp);
private:
  explicit PFResurrectApplicator() {}
  virtual bool Start();

	virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
	virtual int  GetAcceptableUnitTypeFlags() const { return NDb::SPELLTARGET_HEROFEMALE | NDb::SPELLTARGET_HEROMALE; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFAddNaftaApplicator : public DBLinker<PFBaseApplicator, NDb::AddNaftaApplicator>
{
  WORLD_OBJECT_METHODS(0xE7764C40, PFAddNaftaApplicator);
protected:
  ZDATA_(DBLinker)
  float nafta;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&nafta); return 0; }

  PFAddNaftaApplicator(PFApplCreatePars const &cp);

  float GetVariable(const char* sVariableName) const;

private:
  explicit PFAddNaftaApplicator() {}
  virtual bool Start();
  virtual void DumpInfo(NLogg::CChannelLogger &logger) const;

  virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
  virtual int  GetAcceptableUnitTypeFlags() const { return NDb::SPELLTARGET_HEROFEMALE | NDb::SPELLTARGET_HEROMALE; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplVariableProxy : public DBLinker<PFBaseApplicator, NDb::VariableProxyApplicator>
{
  WORLD_OBJECT_METHODS(0xE778BC82, PFApplVariableProxy);

protected:
  ZDATA_(DBLinker)
  vector<vector<float> > variables;
  int currentAppl;
  int applicatorCount;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&variables); f.Add(3,&currentAppl); f.Add(4,&applicatorCount); return 0; }

  PFApplVariableProxy(PFApplCreatePars const &cp);

  float GetVariable(const char* sVariableName) const;

  virtual bool NeedToStopOnSenderDeath() const { return false; }
  virtual bool NeedToDisableOnDeath() const { return false; }
private:
  explicit PFApplVariableProxy() {}
  virtual bool Start();
  virtual bool Step(float dtInSeconds);
  virtual void Stop();
  virtual void OnNotification( PFBaseApplicator &appl, NDb::EParentNotification note );

  virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplCreateGlyph : public DBLinker<PFBaseApplicator, NDb::CreateGlyphApplicator>
{
  WORLD_OBJECT_METHODS(0xE77AF501, PFApplCreateGlyph);
protected:
  ZDATA_(DBLinker)
  CVec2 originalParentDir;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&originalParentDir); return 0; }

  PFApplCreateGlyph(PFApplCreatePars const &cp);
private:
  explicit PFApplCreateGlyph() {}
  virtual bool Start();
  virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_POSITION | Target::FLAG_UNIT; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplVictory : public DBLinker<PFBaseApplicator, NDb::VictoryApplicator>
{
  WORLD_OBJECT_METHODS(0xE77B4C81, PFApplVictory);
protected:
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplVictory(PFApplCreatePars const &cp) : Base(cp) {}
private:
  explicit PFApplVictory() {}
  virtual bool Start();
  virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplChangeState : public DBLinker<PFBaseApplicator, NDb::ChangeStateApplicator>
{
  WORLD_OBJECT_METHODS(0xE7958BC1, PFApplChangeState);
protected:
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplChangeState(PFApplCreatePars const &cp) : Base(cp) {}
private:
  explicit PFApplChangeState() {}
  virtual bool Start();
  virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplGiveConsumable : public DBLinker<PFBaseApplicator, NDb::GiveConsumable>
{
  WORLD_OBJECT_METHODS(0xE79BA401, PFApplGiveConsumable);
protected:
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplGiveConsumable(PFApplCreatePars const &cp) : Base(cp) {}
private:
  explicit PFApplGiveConsumable() {}
  virtual bool Start();
  virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
};

}
