#pragma once

namespace NDb
{
  struct DbAdvMapCTESettings;
}

namespace NWorld
{
  class PFBaseUnit;
  class PFAIContainer;
  class PFNeutralCreepSpawner;
}



namespace NGameX
{
  class AdventureFlashInterface;

  class CTE_Controller: public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( CTE_Controller, BaseObjectST );
  public:
    CTE_Controller(AdventureFlashInterface* _flashInterface, const NDb::DbAdvMapCTESettings * _cteSettings, NWorld::PFAIContainer * _aiContainer );

    void Update(float dt);
  private:
    void UpdateAltars();
    bool IsValidData();
    void  UpdateAltar ( NWorld::PFBaseUnit * altar, float & cachedHealth, float & cachedChange);
    
    Weak<AdventureFlashInterface> flashInterface;

    float healthA;
    float healthB;

    float healthChangeA;
    float healthChangeB;
    
    string damageVariableName;
    bool isInterfaceVisible;
    ConstPtr<NWorld::PFBaseUnit> altarA;
    ConstPtr<NWorld::PFBaseUnit> altarB;
    ConstPtr<NWorld::PFNeutralCreepSpawner> dragonSpawner;
    nstl::vector<float> damageAnimationTalbe;
  };
}


