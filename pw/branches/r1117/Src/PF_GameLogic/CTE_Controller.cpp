#include "StdAfx.h"
#include "CTE_Controller.h"

#include "PFBaseUnit.h"
#include "PFNeutralCreep.h"
#include "PFAIContainer.h"
#include "DBAdvMap.h"

#include "AdventureFlashInterface.h"

namespace
{
  float const UpdateDuration = 1;
}

namespace NGameX
{
  CTE_Controller::CTE_Controller(AdventureFlashInterface* _flashInterface, const NDb::DbAdvMapCTESettings * _cteSettings, NWorld::PFAIContainer * _aiContainer)
    : flashInterface(_flashInterface)
    , isInterfaceVisible(false)
    , healthA(0)
    , healthB (0)
    , healthChangeA(0)
    , healthChangeB()
  {
    _flashInterface->ShowAlwaysHeroesLevels(true);

    if (!IsValid(_aiContainer) || !_cteSettings)
      return;

    altarA = _aiContainer->FindUnit(_cteSettings->altarName_A.c_str());
    altarB = _aiContainer->FindUnit(_cteSettings->altarName_B.c_str());
    dragonSpawner = dynamic_cast<NWorld::PFNeutralCreepSpawner*> (_aiContainer->FindObject(_cteSettings->dragonSpawnerName.c_str()));
    damageAnimationTalbe = _cteSettings->damageAnimationTable;
    damageVariableName = _cteSettings->damageVariableName;

  }

  void CTE_Controller::Update( float dt )
  {
    if (!IsValidData() || !flashInterface)
      return;
    
    if (dragonSpawner->GetLastWave()>0 && dragonSpawner->GetSpawnedCreepsCount() == 0 && !isInterfaceVisible)
    {
      isInterfaceVisible = true;
      flashInterface->ShowCTEUI(true);

      UpdateAltars();
    }

    if (!isInterfaceVisible)
      return;

    UpdateAltars();
  }

  void CTE_Controller::UpdateAltars()
  {
    //DebugTrace("AltarA");
    UpdateAltar(altarA, healthA, healthChangeA);
    //DebugTrace("\nAltarB");
    UpdateAltar(altarB, healthB, healthChangeB);
  
  }

  void CTE_Controller::UpdateAltar( NWorld::PFBaseUnit * altar, float & cachedHealth, float & cachedChange )
  {
    float healthChange = -altar->GetVariableValue( damageVariableName.c_str() );
    float health = altar->GetHealth();
	
    if (healthChange == cachedChange && health == cachedHealth)
      return;

    cachedChange = healthChange;
    cachedHealth = cachedHealth;

    int damageIntensity = 0;

    //получает дамаг
    if (healthChange < 0)
    {
      for (int i = 0; i< damageAnimationTalbe.size(); i++)
      {
        if (damageAnimationTalbe[i] < -healthChange)
          damageIntensity = i+1;
      }
    }

    int uiHealth = Round(altar->GetHealth());
    if (altar->GetHealth() > 0 && uiHealth == 0)
      uiHealth = 1;

    //DebugTrace("Altar  change=%f, dmg=%d", healthChange, damageIntensity);
    flashInterface->SetCTEAltarStatus(altar->GetOriginalFaction(), uiHealth, Round(altar->GetMaxHealth()), damageIntensity);
  }

   bool CTE_Controller::IsValidData()
  {
    return IsValid(altarA) && IsValid(altarB ) && IsValid(dragonSpawner);
  }
}


NI_DEFINE_REFCOUNT(NGameX::CTE_Controller)



