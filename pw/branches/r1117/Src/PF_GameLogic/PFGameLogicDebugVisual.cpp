#include "stdafx.h"

#include "PFGameLogicDebugVisual.h"

#ifndef VISUAL_CUTTED

#include "PFClientBaseUnit.h"
#include "../PF_Core/LightningEffect.h"
#include "../PF_Core/EffectsPool.h"

#include "../System/nhash_table.h"

namespace
{

bool g_debugTargeting = false;

class ClientUnitPositionGenerator : public PF_Core::PositionGenerator
{
public:
  ClientUnitPositionGenerator(const CPtr<NGameX::PFClientBaseUnit>& pUnit) : pUnit(pUnit) {}
  virtual bool GetPos(CVec3 &pos) const
  {
    if (!IsValid(pUnit))
      return false;
    pUnit->MakeTargetingPos(pos);
    return true; 
  }
private:
  CPtr<NGameX::PFClientBaseUnit> pUnit;
};

class LogicDebugManager : public Singleton<LogicDebugManager>
{
public:
  struct UnitDebugInfo
  {
    CPtr<PF_Core::BasicEffect> autoTargetOffsetEffect;
  };
  UnitDebugInfo& GetUnitInfo( NWorld::PFBaseUnit* pUnit )
  {
    UnitDebugInfo* pInfo = NULL;
    UnitsMap::iterator iUnit =  unitsMap.find( reinterpret_cast<DWORD>(pUnit) );
    if ( iUnit != unitsMap.end() )
    {
      pInfo = iUnit->second;
    }
    else
    {
      pInfo = new UnitDebugInfo();
      unitsMap.insert( make_pair(reinterpret_cast<DWORD>(pUnit), pInfo) );
    }

    NI_ASSERT( pInfo, "Unit info not found!" );
    return *pInfo;
  }
private:
  typedef hash_map< DWORD, UnitDebugInfo* > UnitsMap;
  UnitsMap unitsMap;
};

} //unnamed namespace

REGISTER_DEV_VAR("debug_targets", g_debugTargeting, STORAGE_NONE);

#endif //VISUAL_CUTTED

namespace NWorld
{

void InitLogicDebugManager()
{
#ifndef VISUAL_CUTTED
  LogicDebugManager::Init();
#endif //VISUAL_CUTTED
};

void DeinitLogicDebugManager()
{
#ifndef VISUAL_CUTTED
  LogicDebugManager::Term();
#endif //VISUAL_CUTTED
}

void DebugShowScreamEffect( const CPtr<PFBaseUnit>& pSender, const CPtr<PFBaseUnit>& pTarget, ScreamTarget::ScreamType st )
{
#ifndef VISUAL_CUTTED
  if (!g_debugTargeting)
    return;
  NDb::Ptr<NDb::EffectBase> pDBEffect = NDb::Get<NDb::EffectBase>( NDb::DBID( "/Debug/Effects/Arrows/ScreamArrow.EFFT" ) );
  CObj<PF_Core::BasicEffect> effect = PF_Core::EffectsPool::Get()->Retrieve(pDBEffect);
  if ( effect )
  {
    PF_Core::LightningEffect* pEff = dynamic_cast<PF_Core::LightningEffect*>(effect.GetPtr());
    NI_ASSERT(pEff, "!!!");
    pEff->SetPositionGeneratorEnd( new ClientUnitPositionGenerator( pSender->ClientObject() ) );
    pEff->SetPositionGeneratorBegin( new ClientUnitPositionGenerator( pTarget->ClientObject() ) );
    pEff->AddToScene( pSender->GetWorld()->GetScene() );
  }
#endif //VISUAL_CUTTED
}

void DebugShowAttackEffect( const CPtr<PFBaseUnit>& pUnit, const CPtr<PFBaseUnit>& pTarget, float revisionTimeOffset )
{
#ifndef VISUAL_CUTTED
  if (!g_debugTargeting)
    return;
  NDb::Ptr<NDb::EffectBase> pDBEffectArrow = NDb::Get<NDb::EffectBase>( NDb::DBID( "/Debug/Effects/Arrows/TargetingArrow.EFFT" ) );
  CObj<PF_Core::BasicEffect> effectArrow = PF_Core::EffectsPool::Get()->Retrieve(pDBEffectArrow);
  if ( effectArrow )
  {
    PF_Core::LightningEffect* pEff = dynamic_cast<PF_Core::LightningEffect*>(effectArrow.GetPtr());
    NI_ASSERT(pEff, "!!!");
    pEff->SetPositionGeneratorEnd( new ClientUnitPositionGenerator( pUnit->ClientObject() ) );
    pEff->SetPositionGeneratorBegin( new ClientUnitPositionGenerator( pTarget->ClientObject() ) );
    pEff->AddToScene( pUnit->GetWorld()->GetScene() );
  }

  NScene::SceneObject* pSO = pUnit->GetClientSceneObject();
  if ( pSO && pSO->FindLocator( "Above" ) )
  {
    NDb::Ptr<NDb::EffectBase> pDBEffectSphere = NDb::Get<NDb::EffectBase>( NDb::DBID( "/Debug/Effects/Targeting/TargetingTimer.EFFT" ) );
    CObj<PF_Core::BasicEffectAttached> effectSphere = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectAttached>(pDBEffectSphere);
    {
      NScene::SceneComponent* pRootComp = effectSphere->GetRootComponent();
      NI_ASSERT(pRootComp, "Error in effect '/Debug/Effects/Targeting/TargetingTimer.EFFT'!");
      pRootComp->SetSpeed( 1 / revisionTimeOffset );
      effectSphere->SetDeathType( NDb::EFFECTDEATHTYPE_MANUAL, 0 );
      effectSphere->Apply( pUnit->ClientObject() );

      LogicDebugManager::UnitDebugInfo& info = LogicDebugManager::Get()->GetUnitInfo( pUnit );
      if ( IsValid(info.autoTargetOffsetEffect) && info.autoTargetOffsetEffect->IsActive() )
        info.autoTargetOffsetEffect->DieImmediate();
      info.autoTargetOffsetEffect = effectSphere;
    }
  }

#endif //VISUAL_CUTTED
}

}//namespace NWorld
