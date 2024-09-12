#pragma once

#include "stdafx.h"
#include "PFClientBaseUnit.h"

#include "AdventureScreen.h"
#include "AdventureCameraController.hpp"
#include "Minimap.h"
#include "ObjectsInfo2d.h"

#include "PF_Core/EffectsPool.h"
#include "PF_Core/RecolorableTexture.h"
#include "PFHero.h"

#include "Render/debugrenderer.h"

#include "Scene/GeometryBuilders.h"

#include "Terrain/Terrain.h"

#include "UI/Resolution.h"
#include "System/InlineProfiler.h"
#ifndef VISUAL_CUTTED
#include "AdventureScreenEvents.h"
#include "UnitNameMap.h"
#endif

#include "ClientVisibilityHelper.h"

using namespace NScene;

namespace
{
  DEV_VAR_STATIC bool g_showTargets = false;
  char const* const g_sDamageEventName = "OnDamage";

	int EvaluateAuraEffectType(int allyCnt, int enemyCnt)
	{
		NI_ASSERT(allyCnt >= 0 && enemyCnt >= 0, "Invalid aura counters");
		if (allyCnt > 0)
		{
			return (enemyCnt > 0) ? NDb::AURAEFFECTTYPE_MIXED : NDb::AURAEFFECTTYPE_ALLY;
		}
		else
		{
			return (enemyCnt > 0) ? NDb::AURAEFFECTTYPE_ENEMY : -1;
		}
	}
}

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientBaseUnit::PFClientBaseUnit( const PF_Core::WorldObjectRef &pWO, const CreatePars &cp, const NDb::GameObject* gameObject /*= 0*/ ) :
	PFClientSingleStateObject( pWO, cp, gameObject ),
	recolor( 0.0f ),
	uiBarsScreenSize( 0 ), uiBarsWorldSize( 0 ),
	allyAuraCount(0), enemyAuraCount(0),
  castingAllyAuraCount(0), castingEnemyAuraCount(0)
{
  NI_PROFILE_FUNCTION

  if ( GetSceneObject() && GetSceneObject()->GetCollision() )
  {
    CVec3 halfBox = GetSceneObject()->GetCollision()->GetBoundsHalfBox();
    uiBarsWorldSize = Max( 2.0f * Max( halfBox.x, halfBox.y ), 1.0f );
  }

  InitializeUIBars( cp.pScene );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::InitializeUIBars( NScene::IScene * scene)
{
  //world space size first
  NWorld::PFBaseUnit * pUnit = RetrieveWorldObject<NWorld::PFBaseUnit>();
  NI_ASSERT( pUnit, "" );
  uiBarsScreenSize = pUnit->DbUnitDesc()->overtipBarsWidth;

  if ( !uiBarsScreenSize && uiBarsWorldSize )
  {
    //Let's try to find screen space size
    ICamera * cam = scene->GetCamera();
    NI_VERIFY( cam, "", return );
  
    NScene::SCameraPosition camPos;
    cam->GetPosition( &camPos );

    SHMatrix mtx = cam->GetProjectiveMatrix() * cam->GetViewMatrix();

    UI::Point uiPoint;
    UI::LinearCoord uiSize = 0;
    float depth = UI::GetWindowPlacement( &uiPoint, &uiSize, camPos.vAnchor, uiBarsWorldSize, mtx );
    NI_ASSERT( depth > 1e-3f, "" );

    uiBarsScreenSize = uiSize;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::Update( const float timeDiff )
{
  NI_PROFILE_FUNCTION

  PFClientSingleStateObject::Update(timeDiff);

  const NWorld::PFBaseUnit *pWorldUnit = WorldObject();

  UpdateMinimap();

  if ( IsValid(pWorldUnit) && !pWorldUnit->IsDead() && bVisible )	
  {
    if ( GetSceneObject()->IsVisible() )
    {
      ObjectsInfo2dLogic *man = AdventureScreen::Instance()->GetObjInfo2d();
      if (man)
      {
        man->UpdateObject( pWorldUnit, false, false );
      }
    }
  }

#ifndef _SHIPPING
	// display debug information for units
  RenderDebug();
#endif
}

void PFClientBaseUnit::UpdateMinimap() const
{
  static DI_WEAK(NGameX::Minimap) minimap;

  if (!IsValid(minimap))
    return;

  if (!bVisible)
    return;

  const NWorld::PFBaseUnit* const pWorldUnit = WorldObject();

  if (!pWorldUnit)
    return;
  if (pWorldUnit->IsDead())
    return;

  minimap->AddObject(pWorldUnit);
}

void PFClientBaseUnit::OnDamage(float health, float damage)
{
  if( NScene::SceneObject* pSO = GetSceneObject() )
    pSO->ProcessExternalEvent( g_sDamageEventName );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::RenderDebug()
{
  if(g_showTargets)
  {
    if( const NWorld::PFBaseUnit* pWorldUnit = WorldObject() )
    {
      if( CPtr<NWorld::PFBaseUnit> pTarget = pWorldUnit->GetCurrentTarget() )
      {
        CVec3 start = pWorldUnit->GetPosition(), end = pTarget->GetPosition();
        Terrain::TerrainHeightManager& heights = pScene->GetTerrain()->GetHeightManager();

        heights.GetHeight(start.x, start.y, &start.z); 
        heights.GetHeight(end.x, end.y, &end.z);
        
        NDb::EFaction const faction = pWorldUnit->GetFaction();
        Render::Color const color   = Render::Color( NDb::FACTION_FREEZE  == faction ? 255 : 0, 
                                                     NDb::FACTION_NEUTRAL == faction ? 255 : 0, 
                                                     NDb::FACTION_BURN    == faction ? 255 : 0); 
        
        Render::DebugRenderer::DrawLine3D( start, end, color, color, false);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::OnMiss(CPtr<NWorld::PFBaseUnit> const &pTarget)
{
  // process UI message
  if ( NDb::Ptr<NDb::UIEventsCustom> pEvents = NDb::SessionRoot::GetRoot()->visualRoot->uiEvents )
  {
    if ( pEvents->evMiss )
    {
#ifndef VISUAL_CUTTED
      CObj<NGameX::PFUITwoUnitsEvent> pUIEvent;
      pUIEvent = new NGameX::PFUITwoUnitsEvent( pEvents->evMiss, pTarget );
      
      if (pUIEvent)
      {
        pUIEvent->SetSender(WorldObject());
        pUIEvent->SetReciever(pTarget);

        SingleValueNameMapWstring nameMap(L"empty miss message");
        AdventureScreen::Instance()->OnUIEvent( pUIEvent.GetPtr(), &nameMap );
      }
#endif
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFClientBaseUnit::OnLevelUp(int level)
{
	// Unit scale depends on level
	// Commented upon designers request
	//scalePermanent = 1.0f + 0.02f * (level - 1);

	// Don't play level up for invisible objects
	if (!bVisible)
		return false;

  // play levelup for heroes only
  // CObj<PF_Core::BasicEffect> pTemp = PF_Core::EffectsPool::Get()->Retrieve(NDb::EFFECTS_LEVELUP);
  // pTemp->Apply(this);

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::OnHide(bool hide)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::Recolor(const Render::HDRColor& _recolor )
{
  recolor = _recolor;
  UpdateColor();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::ResetColor()
{
  recolor = Render::HDRColor( 0.0f );
  if ( GetSceneObject() )
  {
		PF_Core::ResetSceneObjectRecolor( *GetSceneObject() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::UpdateColor()
{
  if ( GetSceneObject() )
  {
    if ( recolor.A != 0.0f )
    {
      PF_Core::RecolorSceneObject( *GetSceneObject(), recolor );
    }
    else
    {
      PF_Core::ResetSceneObjectRecolor( *GetSceneObject() );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::EnableById( string id, bool bEnable )
{
  PFClientLogicObject::EnableById( id, bEnable );
  UpdateColor();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::ProcessExternalEvent( const char* externalEvent )
{
  PFClientLogicObject::ProcessExternalEvent( externalEvent );
  UpdateColor();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::AcknowledgeAuraChange(bool isAlly, bool isEnabled)
{
	int auraTypeIndex = EvaluateAuraEffectType(allyAuraCount, enemyAuraCount);

	int *pValue = isAlly ? &allyAuraCount : &enemyAuraCount;
	if (isEnabled)
		(*pValue)++;
	else
		(*pValue)--;

	const NDb::AuraEffects &auraEffects = NDb::SessionRoot::GetRoot()->visualRoot->auraEffects;

	int newAuraTypeIndex = EvaluateAuraEffectType(allyAuraCount, enemyAuraCount);
	if (newAuraTypeIndex != auraTypeIndex) // Change effect
	{
		// Remove old effect
		if (pAuraEffect)
		{
			pAuraEffect->Die();
			pAuraEffect = 0;
		}

		// Make new one
		if (newAuraTypeIndex >= 0)
		{
			NI_ASSERT(newAuraTypeIndex < 3, "Invalid aura effect logic");
			NDb::Ptr<NDb::BasicEffectAttached> pEff = auraEffects.auraEffects[newAuraTypeIndex];
			if (pEff)
			{
				pAuraEffect = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectAttached>(pEff);
				pAuraEffect->Attach(GetSceneObject());
			}
		}
	}

	if (!pAuraEffect)
		return;

	// Change effect intencity
	float intencity = auraEffects.minimalEffectIntencity;
	if (auraEffects.maximalAuraCount > 1)
	{
		float interpParam = float(min(allyAuraCount + enemyAuraCount, auraEffects.maximalAuraCount)-1) / float(auraEffects.maximalAuraCount-1);
		intencity += (1 - auraEffects.minimalEffectIntencity) * interpParam;
	}

	Render::HDRColor mul(intencity, intencity, intencity);
	pAuraEffect->ModifyColor(mul, Render::HDRColor());
}

void PFClientBaseUnit::OnSelfAuraChange( bool isAlly, bool isEnabled )
{
   int auraTypeIndex = EvaluateAuraEffectType( castingAllyAuraCount, castingEnemyAuraCount );

  int *pValue = isAlly ? &castingAllyAuraCount : &castingEnemyAuraCount;
  if (isEnabled)
    (*pValue)++;
  else
    (*pValue)--;

  const vector<NDb::Ptr<NDb::BasicEffectAttached>> &selfAuraEffects = NDb::SessionRoot::GetRoot()->visualRoot->selfAuraEffects;

  int newAuraTypeIndex = EvaluateAuraEffectType(castingAllyAuraCount, castingEnemyAuraCount);
  if (newAuraTypeIndex != auraTypeIndex) // Change effect
  {
    // Remove old effect
    if (pSelfAuraEffect)
    {
      pSelfAuraEffect->Die();
      pSelfAuraEffect = 0;
    }

    // Make new one
    if (newAuraTypeIndex >= 0)
    {
      NI_ASSERT(newAuraTypeIndex < 3, "Invalid aura effect logic");
      NDb::Ptr<NDb::BasicEffectAttached> pEff = selfAuraEffects[newAuraTypeIndex];
      if (pEff)
      {
        pSelfAuraEffect = PF_Core::EffectsPool::Get()->Retrieve<PF_Core::BasicEffectAttached>(pEff);
        pSelfAuraEffect->Attach(GetSceneObject());
      }
    }
  }

  if (!pSelfAuraEffect)
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::SetSelfAuras( int allyAurasCount, int enemyAurasCount )
{
  castingAllyAuraCount = allyAurasCount;
  castingEnemyAuraCount = enemyAurasCount; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientBaseUnit::OnAddGold(const CPtr<NWorld::PFBaseUnit> & pSender, const float amount)
{
	if (amount < 1.0f)
		return; // nothing to show

  if ( pSender->IsDead() && WorldObject() == pSender.GetPtr() )
    return; // don't show anything if adding gold ourselves being dead

	const NWorld::PFBaseUnit* pUnit = WorldObject()->GetMasterUnit();
	if (pUnit)
	{
		const NWorld::PFBaseHero* pHero = dynamic_cast<const NWorld::PFBaseHero*>(pUnit);
		if (pHero && !pHero->IsLocal())
			return;
	}

#ifndef VISUAL_CUTTED
  // process UI message
  if ( NDb::Ptr<NDb::UIEventsCustom> pEvents = NDb::SessionRoot::GetRoot()->visualRoot->uiEvents )
  {
    if ( pEvents->evGetNafta )
    {
      CObj<NGameX::PFUITwoUnitsEvent> pUIEvent;
      pUIEvent = new NGameX::PFUITwoUnitsEvent( pEvents->evGetNafta, pSender );

      if ( IsValid( pUIEvent ) )
      {
        pUIEvent->SetSender(pSender);
        pUIEvent->SetReciever(WorldObject());
      }

      SingleValueNameMapFloat eventData(amount);
      AdventureScreen::Instance()->OnUIEvent( pUIEvent.GetPtr(), &eventData );
    }
  }
#endif
}

const NDb::DBSceneObject* PFClientBaseUnit::GetSceneObjectDesc()
{
	if ( pSceneObjectsHolder )
		return pSceneObjectsHolder->GetDBObject();
	return 0;
}

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DEV_VAR("show_targets", g_showTargets,    STORAGE_NONE);
