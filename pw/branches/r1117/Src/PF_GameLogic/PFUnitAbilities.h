#pragma once

#include "PFBaseUseState.h"

namespace NWorld
{

class PFAbilityData;
class PFBaseUnit;
struct DropCooldownParams;

class PFUnitAbilities
{
private:
  struct AbilityData
  {
    ZDATA;
    CObj<PFAbilityData> pAbility;
    bool                isInProgress; // do not place this into Z D A T A // wtf? why??
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&pAbility); f.Add(3,&isInProgress); return 0; }

    AbilityData(CObj<PFAbilityData> pAbility = NULL) : pAbility(pAbility), isInProgress(false){}
  };

  typedef vector<AbilityData> TAbilities;

  ZDATA()
  bool                useAbilitiesMicroAI;
  TAbilities          abilities;
  float               globalCooldownTime;
  float               globalActionsCooldown;
  float               channellingProgress;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&useAbilitiesMicroAI); f.Add(3,&abilities); f.Add(4,&globalCooldownTime); f.Add(5,&globalActionsCooldown); f.Add(6,&channellingProgress); return 0; }

  PFUnitAbilities() 
    : useAbilitiesMicroAI(true) 
    , globalCooldownTime(0)
    , globalActionsCooldown(0)
    , channellingProgress(0.0f)
  {}

  PFAbilityData*          GetAbility(int id);
  PFAbilityData const*    GetAbility(int id) const;
  void                    SetAbility(int id, PFAbilityData *pAbility);
  int                     GetAbilitiesCount() const;
  int                     GetAbilityIndex(PFAbilityData const *pAbility) const;

  bool                    IsAbilityInProgress(int id) const;
  void                    SetAbilityInProgress(int id, bool isInProgress); // wanna to hide this :(
  bool                    HaveAbilityInProgress() const;

  void                    DropAbilitiesCooldowns( DropCooldownParams const& dropCooldownParams );

  bool                    IsMicroAiEnabled() const { return useAbilitiesMicroAI; }
  void                    EnableAbilityAI(bool enable) { useAbilitiesMicroAI = enable; }
  
  //
  bool                    IsAbilityAvailable(int id) const;
  float                   GetAbilityPreparedness(int id) const;
  float                   GetGlobalPreparedness() const;
  float                   GetGlobalActionsCooldown() const {return globalActionsCooldown;};
  void                    StartGlobalCooldown() { globalActionsCooldown = globalCooldownTime; }
  float                   GetGlobalCooldown() const {return globalCooldownTime;} 

  // Channelling
  float                   GetChannellingProgress() const { return channellingProgress; }
  void                    SetChannellingProgress(float prog) { channellingProgress = prog; }
  bool                    IsInChannelling() const { return channellingProgress > 0.0f; }

  virtual CObj<IPFState>  InvokeAbility(int id, Target const &target) { return CObj<IPFState>(0); };
protected:
  void                    CreateAbilities(PFBaseUnit *pOwner, const NDb::Unit &unitDesc);
  void                    DestroyAbilities();
  void                    UpdateAbilities(float dtInSeconds, bool isDead);
  void                    DropAbilitiesProgress();
  void                    UpgradeAbilities();
};


class PFBaseUnitUseAbilityState : public PFBaseUseState
{
  WORLD_OBJECT_METHODS(0xB777381, PFBaseUnitUseAbilityState)
public:
  PFBaseUnitUseAbilityState(CPtr<PFWorld> const& pWorld, CPtr<PFBaseUnit> const& pOwner, int id, Target const &target);
  virtual NDb::Ability const* GetDBDesc() const;
protected:
  
  virtual void OnEnter();
  virtual bool OnStep( float dt );
  virtual void OnLeave();

  PFBaseUnitUseAbilityState() {}
protected:

  virtual float GetUseRange() const {return -1;}
  ZDATA_(PFBaseUseState)
  CPtr<PFWorld>	   pWorld;
  int              abilityID;
  bool             wait4channeling;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseUseState*)this); f.Add(2,&pWorld); f.Add(3,&abilityID); f.Add(4,&wait4channeling); return 0; }
};


}