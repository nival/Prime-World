#pragma once

#include "PFWorld.h"
#include "PFBaseUnit.h"
#include "PFBuildings.h"
#include "PFTower.h"
#include "System\StarForce\StarForce.h"

namespace NGameX
{
	class PFClientMainBuilding;
};

class HWBreak;

namespace NWorld
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFMainBuilding : public PFBattleBuilding
  {
    WORLD_OBJECT_METHODS_WITH_CLIENT( 0x2C5BE402, PFMainBuilding, NGameX::PFClientMainBuilding );

    enum EMainBuildingAttack
    {
      Invalid = -1,
      Ranged, 
      Melee,
      AOE,
    };
  
    ZDATA_(PFBattleBuilding)
    bool                         activated;
    float                        aoeCooldown;

    EMainBuildingAttack          selectedAttack;

		// these fields are taken from NDb: no need to syncronize them!
		int   aoeUnitsCount;
		float aoeRadius;
		float minAOEDelay;  
		float maxAOEDelay;
		int   aoeUnitsTypes;
		int   aoeUnitsFactions;

    CObj<PFBaseAttackData>       pRangedAttack;
    CObj<PFAbilityData>          pAOEAttack;
    CObj<PFAbilityInstance>      pAOEInstance; 
		NDb::Ptr<NDb::MainBuilding>  pDesc;

    bool                         aoePending;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBattleBuilding*)this); f.Add(2,&activated); f.Add(3,&aoeCooldown); f.Add(4,&selectedAttack); f.Add(5,&aoeUnitsCount); f.Add(6,&aoeRadius); f.Add(7,&minAOEDelay); f.Add(8,&maxAOEDelay); f.Add(9,&aoeUnitsTypes); f.Add(10,&aoeUnitsFactions); f.Add(11,&pRangedAttack); f.Add(12,&pAOEAttack); f.Add(13,&pAOEInstance); f.Add(14,&pDesc); f.Add(15,&aoePending); return 0; }

    explicit                 PFMainBuilding() {}
    STARFORCE_EXPORT  PFMainBuilding(PFWorld* pWorld, NDb::AdvMapObject const& dbObject);
    
    virtual ~PFMainBuilding();

		virtual void Reset();

    virtual bool             Step(float dtInSeconds);

    bool                     IsActivated() const { return activated; } 
    void                     Activate(bool activate);
    
    void                     SelectAttack();
    EMainBuildingAttack      GetSelectedAttack() const { return selectedAttack; }
    bool                     IsAOEReady() const { return aoeCooldown < EPS_VALUE; }
    bool                     CanUseAOE() const;
    void                     UseAOE();
    bool                     IsAOEInProcess() const;
    void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc = 0);
  private:
    void                     OnActivated(bool activated);
    void                     StartAOECooldown();
    bool                     IsAOEAttackReady() const;
    virtual void             OnDie(); 
  };

};