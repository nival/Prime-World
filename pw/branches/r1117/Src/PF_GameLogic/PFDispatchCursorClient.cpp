#include "stdafx.h"
#include "PFDispatchCursorClient.h"
#include "../System/RandomGen.h"
#include "../PF_Core/EffectsPool.h"
#include "../PF_Core/RecolorableTexture.h"
#include "PFBaseUnit.h"
#include "PFClientBaseUnit.h"
#include "../Core/Scheduler.h"

#ifndef VISUAL_CUTTED
#include "PFClientApplicators.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

#include "../Render/debugrenderer.h"
#include "../Render/AOERenderer.h"

#include "AdventureScreen.h"
#include "PFClientVisibilityMap.h"
#include "PFHero.h"

namespace NGameX
{

static NDb::EffectBase const *GetDispatchEffectDB( const NWorld::PFDispatch* dispatch )
{
  if (!IsValid(dispatch))
  {
    return NULL;
  }

  int teamID = dispatch->GetSender()->GetOriginalTeamId();
  if (teamID == -1)
  {
    teamID = NDb::TEAMID_A;
  }
  if ( dispatch->GetDBBase()->dispatchEffect[teamID].IsEmpty() )
  {
    teamID = teamID == NDb::TEAMID_B ? NDb::TEAMID_A : NDb::TEAMID_B;
  }

  return dispatch->GetDBBase()->dispatchEffect[teamID];
}

PFDispatchCursorClient::PFDispatchCursorClient( PF_Core::WorldObjectRef pWO, NScene::IScene *pScene )
: NWorld::PFClientObjectBase(pWO)
, pScene(pScene)
, dest(VNULL3)
, currentPos(VNULL3)
, startMatrix(QNULL, VNULL3)
, updateCursorTime( 0.0f )
, needSendCommandUpdateCursor( false )
, aoeIsVisible(false)
{
  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( advScreen )
  {
    if ( NWorld::PFBaseHero* hero = dynamic_cast<NWorld::PFBaseHero*>(WorldObject()->GetSender().GetPtr()) )
      needSendCommandUpdateCursor = hero->IsLocal();
  }
  bool bOk = GetStartPos(currentPos, startMatrix);
  NI_ASSERT(bOk, NStr::StrFmt("Failed to retrieve dispatch start pos for %s !", GetFormattedDbId(WorldObject()->GetDB().GetDBID()).c_str()) );
  Start();
}

void PFDispatchCursorClient::OnWorldObjectDie()
{
  if (pEffect)
  {
    pEffect->Die();
    pEffect = 0;
  }

  if ( pLinkEffect )
  {
    pLinkEffect->Die();
    pLinkEffect = 0;
  }

  if ( aoeIsVisible )
  {
    aoeIsVisible = false;
    if (Render::AOERenderer* pAOE = Render::GetAOERenderer())
      pAOE->ResetArea(Render::AOERenderer::CHANNEL_RANGE2);
  }

  PFClientObjectBase::OnWorldObjectDie();
}

void PFDispatchCursorClient::Update( float timeDelta )
{
  updateCursorTime += timeDelta;

  float updateFrequency = WorldObject()->GetDB().cursorUpdateFrequency;
  if ( updateFrequency * pScene->GetStepLengthInSeconds() < updateCursorTime )
  {
    UpdateCursor();
    updateCursorTime = 0.0f;
  }

  if ( !pEffect )
  {
    return;
  }

  RetrieveTargetCoords();

  const float linkRange = WorldObject()->GetDB().linkRange;

  CVec2 delta2d = ( dest - currentPos ).AsVec2D();
  float dist2d = fabs( delta2d );
  float speed = dist2d * WorldObject()->GetSpeed();
  speed = Min( speed, WorldObject()->GetMaxSpeed() );
  Normalize( &delta2d );

  CVec2 source = WorldObject()->GetSender()->ClientObject()->GetPosition().pos.AsVec2D();
  CVec2 newPos = currentPos.AsVec2D() + delta2d * speed * timeDelta;
  CVec2 dirFromSender = newPos - source;

  bool showLinkEffect = false;
  if ( linkRange > EPS_VALUE && fabs2( dirFromSender ) > fabs2( linkRange ) )
  {
    Normalize( &dirFromSender );
    newPos = dirFromSender * linkRange + source;
    showLinkEffect = true;
  }

  currentPos = CVec3( newPos, 0.0f );

  pScene->GetHeightsController().GetHeight( currentPos.x, currentPos.y, 1, &currentPos.z, 0 );
  currentPos.z += WorldObject()->GetDB().height;

  Placement placement;
  placement.pos = currentPos;
  pEffect->SetPosition(placement);

  const NDb::Ptr<NDb::LightningEffect>& pDBLinkEffect = WorldObject()->GetDB().linkEffect;

  if ( showLinkEffect && !pLinkEffect && pDBLinkEffect )
  {
    pLinkEffect = NGameX::CreateLightningEffect( pDBLinkEffect, WorldObject()->GetSender()->GetSkinId() );
    if ( pLinkEffect )
      pLinkEffect->Apply( this, WorldObject()->GetSender()->ClientObject() ); // considering sender is actually a source
  }
  else if ( !showLinkEffect && pLinkEffect )
  {
    pLinkEffect->Die();
    pLinkEffect = 0;
  }

  UpdateVisibility( GetSceneObject(), this );

  NDb::Ptr<NDb::AOEMaterial> const& pDBMaterial = WorldObject()->GetDB().maxRangeMaterial;
  Render::AOERenderer* pAOE = Render::GetAOERenderer();
  if ( pDBMaterial && pAOE )
  {
    if ( showLinkEffect )
    {
      if( NWorld::PFBaseHero* hero = dynamic_cast<NWorld::PFBaseHero*>( WorldObject()->GetSender().GetPtr() ) )
      {
        if( hero->IsLocal() )
        {
          if ( !aoeIsVisible )
          {
            aoeIsVisible = true;
            pAOE->SetAreaParams( Render::AOERenderer::CHANNEL_RANGE2, Render::AOERenderer::AREA_DISK, pDBMaterial, linkRange + WorldObject()->GetDB().size, 0 );
          }
          if ( PFClientLogicObject const* pClient = WorldObject()->GetSender()->ClientObject() )
          {
            pAOE->SetAreaPosition( Render::AOERenderer::CHANNEL_RANGE2, pClient->GetPosition().pos, CVec3( dirFromSender, 0.0f ), true );
          }
        }
      }
    }
    else if ( aoeIsVisible )
    {
      aoeIsVisible = false;
      pAOE->ResetArea(Render::AOERenderer::CHANNEL_RANGE2);
    }
  }
}

bool PFDispatchCursorClient::GetStartPos( CVec3& result, Matrix43& matrix ) const
{
  const NWorld::PFDispatchCursor* pWorldObject = WorldObject();
  if( NULL == pWorldObject )
    return false;

  CPtr<NWorld::PFBaseUnit> const pSender = pWorldObject->GetSender();
  if( !IsValid( pSender ) )
    return false;

  if ( pWorldObject->GetSource().IsPosition() )
  {
    result = pWorldObject->GetSource().GetPosition();
    return true;
  }

  CPtr<NWorld::PFBaseUnit> const pSource = pWorldObject->GetSource().GetUnit();
  if( !IsValid( pSource ) )
    return false;

  PFClientLogicObject* pClient = pSource->ClientObject();
  if( NULL == pClient)
    return false;

  NScene::SceneObject *pSO = pClient->GetSceneObject();
  if ( NULL == pSO )
    return false;

  result = pSO->GetPosition().pos;
  if ( pSender == pSource )
  {
    if ( NScene::Locator const* pL = pSO->FindLocator( pWorldObject->GetDB().fromLocator.c_str() ) )
    {
      matrix = Matrix43(QNULL, result);
      pSO->CalculateLocatorWorldMatrix(*pL, matrix, pClient->IsVisible() );
      result.Set(matrix._14, matrix._24, matrix._34);
      const NWorld::Target& target = WorldObject()->GetTarget();
      if ( target.IsPosition() )
      {
        if ( fabs(pSO->GetPosition().pos - target.GetPosition()) < fabs(pSO->GetPosition().pos - result) )
        {
          result = pSO->GetPosition().pos;
        }
      }
    }
  }

  NI_ASSERT( result.IsFinite(), NStr::StrFmt("Invalid dispatch start pos. Retrieved from %s !", pSO->FormatDescription()) );
  NI_ASSERT( matrix.IsFinite(), NStr::StrFmt("Invalid dispatch start matrix. Retrieved from %s !", pSO->FormatDescription()) );

  return true;
}

void PFDispatchCursorClient::Start()
{
  UpdateCursor();
  const NWorld::PFDispatchCursor* pWorldObject = WorldObject();
  NWorld::PFBaseUnit const* pSender = pWorldObject->GetSender().GetPtr();
  NDb::EffectBase const *dispatchEffect = GetDispatchEffectDB(pWorldObject);

  if ( !dispatchEffect )
  {
    Subscribe();
    return;
  }

  GetStartPos(currentPos, startMatrix);
  RetrieveTargetCoords();
  Placement placement;
  placement.pos = currentPos;

  pEffect = RetrieveStandaloneEffect( dispatchEffect, pSender );
  if (!pEffect)
    return;

  pEffect->SetPosition(placement);
  pEffect->AddToScene(pScene);
  InitVisibility( GetSceneObject() );

  if (pEffect->GetSceneObject() &&
    IsValid(pSender->ClientObject()))
  {
    PF_Core::RecolorSceneObject(*pEffect->GetSceneObject(), pSender->ClientObject()->GetRecolor());
  }

  UpdateVisibility( GetSceneObject(), this );

  // Subscribe for updates
  Subscribe();
}

void PFDispatchCursorClient::RetrieveTargetCoords()
{
  NI_ASSERT( IsValid( WorldObject() ), "World dispatch should be valid" );
  dest = WorldObject()->GetTarget().AcquirePosition();
  pScene->GetHeightsController().GetHeight( dest.x, dest.y, 1, &dest.z, 0 );
  dest.z += WorldObject()->GetDB().height;
}

NScene::SceneObject * PFDispatchCursorClient::GetSceneObject() const
{
  if (!IsValid(pEffect))
  {
    return NULL;
  }
  return pEffect->GetSceneObject();
}

void PFDispatchCursorClient::UpdateCursor()
{
  if ( !needSendCommandUpdateCursor )
    return;

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( advScreen )
  {
    NCore::WorldCommand * cmd = NWorld::CreateCmdUpdateCursorPos( const_cast<NWorld::PFDispatchCursor *>( WorldObject() ), advScreen->GetCurrentCursorPosOnTerrain().AsVec2D() );
    advScreen->SendGameCommand( cmd, true );
  }
}
}

