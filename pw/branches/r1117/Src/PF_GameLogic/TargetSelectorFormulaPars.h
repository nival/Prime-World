#pragma once

namespace NWorld
{

struct TargetSelectorFormulaPars : public IMiscFormulaPars
{
  TargetSelectorFormulaPars( const IMiscFormulaPars* _pMisc ) : pMisc(_pMisc) {}

  virtual bool  IsAbilityOn() const { return pMisc->IsAbilityOn(); }
  virtual bool  IsTalentBought() const { return pMisc->IsTalentBought(); }
  virtual int   GetRank() const { return pMisc->GetRank(); }
  virtual float GetDist2Target() const { return pMisc->GetDist2Target(); }
  virtual float GetScale() const { return pMisc->GetScale(); }
  virtual float GetParentScale() const { return pMisc->GetParentScale(); }
  virtual float GetManaCost() const { return pMisc->GetManaCost(); }
  virtual float GetPreparedness() const { return pMisc->GetPreparedness(); }
  virtual int   GetAbilityType() const { return pMisc->GetAbilityType(); }
  virtual bool  Roll(float probability) const { return pMisc->Roll(probability); }
  virtual int   GetTerrainType() const { return pMisc->GetTerrainType(); }
  virtual int   GetRefineRate() const { return pMisc->GetRefineRate(); }
  virtual int   GetTalentLevel() const { return pMisc->GetTalentLevel(); }
  virtual int   GetTalentDevPoints() const { return pMisc->GetTalentDevPoints(); }
  virtual int   GetNaftaCost() const { return pMisc->GetNaftaCost(); }
  virtual float GetCooldown() const { return pMisc->GetCooldown(); }
  virtual int   GetScrollLevel() const { return pMisc->GetScrollLevel(); }
  virtual bool  IsNight() const { return pMisc->IsNight(); }
  virtual bool  CheckUpgradePerCastPerTarget() const { return pMisc->CheckUpgradePerCastPerTarget(); }

  virtual const IUnitFormulaPars* GetObjectOwner() const { return pMisc->GetObjectOwner(); }
  virtual const IMiscFormulaPars* GetObjectParent() const { return pMisc->GetObjectParent(); }     

  virtual const IUnitFormulaPars* GetObject( char const *name ) const { return pMisc->GetObject(name); }
  virtual float GetConstant(const char *name, IUnitFormulaPars const *pSender, IUnitFormulaPars const* pReceiver) const
    { return pMisc->GetConstant( name, pSender, pReceiver ); }

  virtual float GetVariable(const char *name) const { return pMisc->GetVariable(name); }

  virtual CVec2 GetTargetPos() const { return pMisc->GetTargetPos(); }

  virtual int   GetRandom(int from, int to)const { return pMisc->GetRandom( from, to ); }
  virtual float GetAbilityScale( bool isDamage, float statValue, EAbilityScaleMode abScaleMode, float valueLeft, float valueRight, bool bRound = true ) const
    { return pMisc->GetAbilityScale( isDamage, statValue, abScaleMode, valueLeft, valueRight, bRound ); }
  virtual bool  GetSmartRoll( float probability, int maxFailReps, int maxSuccessReps, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const
    { return pMisc->GetSmartRoll( probability, maxFailReps, maxSuccessReps, pFirst, pSecond ); }
  virtual int   GetSmartRandom( int outcomesNumber, float probDecrement, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const
  { return pMisc->GetSmartRandom( outcomesNumber, probDecrement, pFirst, pSecond ); } 
  virtual float GetRefineAbilityScale( float valueAtRefineLevel0, float valueAtRefineLevel6  ) const
    { return pMisc->GetRefineAbilityScale( valueAtRefineLevel0, valueAtRefineLevel6 ); }
  virtual int   GetAlternativeTargetIndex() const { return pMisc->GetAlternativeTargetIndex(); }
  virtual float GetTerrainPart(int faction) const { return pMisc->GetTerrainPart( faction ); }
  virtual int   GetActivatedWithinKit() const { return pMisc->GetActivatedWithinKit(); }
  virtual int   GetTalentsWithinKit() const { return pMisc->GetTalentsWithinKit(); }
  virtual float GetStatusDispellPriority( const IUnitFormulaPars* pUnitToCheck, bool returnDuration ) const
    { return pMisc->GetStatusDispellPriority( pUnitToCheck, returnDuration ); }
  virtual CVec2 GetVectorVariable(const char *name) const { return pMisc->GetVectorVariable(name); }

  const IMiscFormulaPars* GetMisc() const { return pMisc; }

  virtual int GetTerrianTypeUnderCursor() const { return pMisc->GetTerrianTypeUnderCursor(); }
  virtual int GetNatureTypeInPos(CVec2 pos) const {return pMisc->GetNatureTypeInPos(pos); }


private:
  const IMiscFormulaPars* pMisc;
};

}