#include "stdafx.h"

#include "PFClientFlagpole.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "../PF_Core/EffectsPool.h"
#include <Render\SkeletalMesh.h>

#include "PFClientApplicators.h"
#include "AdventureScreen.h"
#include "Minimap.h"

#include "../System/InlineProfiler.h"

namespace NGameX
{

PFClientFlagpole::PFClientFlagpole(PF_Core::WorldObjectRef pWO, const NDb::AdvMapObject &mapObject, NScene::IScene* pScene)
: PFClientBaseUnit(pWO, CreatePars(pScene, BADNODENAME, mapObject))
, pAnimatedRoot(NULL)
, pAG(NULL)
, teamId( 0 )
, startNodeID(DIANGR_NO_SUCH_ELEMENT)
, idleNodeID(DIANGR_NO_SUCH_ELEMENT)
, waitNodeID(DIANGR_NO_SUCH_ELEMENT)
{
  NScene::SceneObject* pSO = GetSceneObject();

  pAnimatedRoot = pSO ? dynamic_cast<NScene::AnimatedSceneComponent *> (pSO->GetRootComponent()): NULL;
  pAG           = pAnimatedRoot ? pAnimatedRoot->GetMainAnimGraph() : NULL;

  idleNodeID = GetStateIdByName( "idle" );
  startNodeID = GetStateIdByName( "start" );
  waitNodeID = GetStateIdByName( "wait" );

  pAG->Restart( startNodeID, true );
  pAG->RegisterCallback( DIANGR_NODE, idleNodeID, PFClientFlagpole::OnFlagRaised,  DIANGR_CF_ELEMENT_ENTER, this, 0, 100.0f );
  pAG->RegisterCallback( DIANGR_NODE, idleNodeID, PFClientFlagpole::OnFlagDropped, DIANGR_CF_ELEMENT_LEAVE, this, 0, 100.0f );

  // Preload buildings
  NGameX::AdventureScreen::Instance()->PreloadEffectsInResourceTree(NDb::Ptr<NDb::DbResource>(mapObject.gameObject), BADNODENAME);
  
}

DiInt32 PFClientFlagpole::OnFlagRaised( const DiAnGrCallbackParams& params )
{
  NGameX::PFClientFlagpole* flag = reinterpret_cast<NGameX::PFClientFlagpole*>( params.vpUserData );
  flag->OnRaised();
  return DIOBJMSG_CONTINUE;
}

DiInt32 PFClientFlagpole::OnFlagDropped( const DiAnGrCallbackParams& params )
{
  NGameX::PFClientFlagpole* flag = reinterpret_cast<NGameX::PFClientFlagpole*>( params.vpUserData );
  
  if ( flag->pEffect )
  {
    flag->pEffect->Die();
    flag->pEffect = 0;
  }

  return DIOBJMSG_CONTINUE;
}

void PFClientFlagpole::OnEffectAttach(PF_Core::BasicEffectAttached *pEffect)
{
  if( AdventureScreen* pAdvScreen = AdventureScreen::Instance() )
  {
    Render::Texture2DRef emblemTexture;

    if( pAdvScreen->GetEmblemTextureForTeam(teamId, emblemTexture) )
    {
      struct ChandeTexProc : public Render::IMaterialProcessor
      {
        Render::Texture2D *tex;

        ChandeTexProc(Render::Texture2D *_tex) : tex(_tex) {}

        virtual void operator()(Render::BaseMaterial &material)
        {
          if( const NDb::Material* pNDbMaterial = material.GetDBMaterial() )
            if( pNDbMaterial->caption == "flag" )
            {
              if( Render::Sampler* sampler = material.GetDiffuseMap() )
              {
                sampler->SetTexture(tex);
                material.MarkMaterialUpdated();
              }
            }
        }
      } chandeTexProc(emblemTexture);

      pEffect->ForAllMaterials(chandeTexProc);
    }
  }
}

void PFClientFlagpole::OnRaiseFlag( int _teamId )
{
  SetAnimStateId( idleNodeID );
  teamId = _teamId;
}

void PFClientFlagpole::OnStartRaiseFlag()
{
  SetAnimStateId( waitNodeID );
}

void PFClientFlagpole::OnRaised()
{
  // obtain DB
  const NDb::Flagpole* db = dynamic_cast<const NDb::Flagpole*> ( WorldObject()->DbUnitDesc() );
  NI_DATA_VERIFY( db, NStr::StrFmt( "Invalid object type \"%s\" for flagpole \"%s\"", WorldObject()->DbUnitDesc()->GetTypeName(), NDb::GetFormattedDbId(  WorldObject()->DbUnitDesc()->GetDBID() ).c_str() ), return );
 
  // get effect from DB
  pEffect = PF_Core::EffectsPool::Get()->Retrieve( db->effect[teamId] );
  NI_DATA_VERIFY( pEffect, NStr::StrFmt( "Cannot retrive effect for flagpole \"%s\" fro team %d", NDb::GetFormattedDbId(  WorldObject()->DbUnitDesc()->GetDBID() ).c_str(), teamId ), return );

  // apply it depens on fation
  pEffect->Apply( this );
}

void PFClientFlagpole::OnDropFlag()
{
  SetAnimStateId( startNodeID );
}

void PFClientFlagpole::OnAfterReset( bool isRaised, int _teamId )
{
  if( isRaised )
  {
    teamId = _teamId;
    if (DIANGR_NO_SUCH_ELEMENT != idleNodeID && NULL != pAG)
      pAG->Restart( idleNodeID, true );
  }
  else
    OnDropFlag();
}

void PFClientFlagpole::Hide(bool hide)
{
  static CPtr<NScene::IScene> pOldScene;

  if ( NScene::SceneObject * pSceneObject = GetSceneObject() )
  {
    if (pSceneObject->IsInScene())
    {
      if (hide)
      {
        pOldScene = pSceneObject->GetScene();
        pSceneObject->RemoveFromScene();
      }
    }
    else
    {
      if (!hide && IsValid(pOldScene))
      {
        pSceneObject->AddToScene(pOldScene);
      }
    }

    if ( pSceneObject->GetCollision() )
      pSceneObject->GetCollision()->SetEnabled(!hide);
    if ( pSceneObject->GetSmallCollision() )
      pSceneObject->GetSmallCollision()->SetEnabled(!hide);
  }
}

unsigned  PFClientFlagpole::GetCurrentStateId() const
{
  return pAG ? pAG->GetCurNodeUnsafe() : DIANGR_NO_SUCH_ELEMENT;
}

unsigned  PFClientFlagpole::GetNextStateId() const
{
  return pAG ? pAG->GetNextNode() : DIANGR_NO_SUCH_ELEMENT;
}

unsigned  PFClientFlagpole::GetStateIdByName(char const* name) const
{
  return pAG ? pAG->GetNodeIDByNameSlowQuite(name) : DIANGR_NO_SUCH_ELEMENT;
}

unsigned  PFClientFlagpole::GetNumNodes() const
{
  return pAG ? pAG->GetNumNodes() : 0;
}

bool PFClientFlagpole::SetAnimStateId(unsigned int nodeId)
{
  if (DIANGR_NO_SUCH_ELEMENT != nodeId && NULL != pAG)
    return pAG->SetTargetNode(nodeId);

  return false;
}

bool PFClientFlagpole::ReachStateMarker(char const* sMarker, float time, bool preferShortestPath, bool preferDefaultNextNode)
{
  if (pAG)
    return pAG->ReachMarkerByTime(sMarker, static_cast<int>(time * 1e+3f), preferShortestPath, preferDefaultNextNode );
  return false;
}

void PFClientFlagpole::Update( float timeDiff )
{
  NI_PROFILE_FUNCTION

  PFClientBaseUnit::Update( timeDiff );
  if ( GetSceneObject() && !GetSceneObject()->IsVisible() )
    GetSceneObject()->Update( timeDiff, true );
}

void PFClientFlagpole::UpdateMinimap() const
{
  static DI_WEAK(NGameX::Minimap) minimap;

  if (!IsValid(minimap))
    return;

  const NWorld::PFFlagpole* const pWorldUnit = WorldObject();

  if (!pWorldUnit)
    return;

  if (const NDb::Flagpole* const dbFlagpole = dynamic_cast<const NDb::Flagpole*>(pWorldUnit->DbUnitDesc()))
    minimap->AddObject(pWorldUnit, pWorldUnit->GetMinimapIcon());
  else
    minimap->AddObject(pWorldUnit, -1);
}

void PFClientFlagpole::SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc )
{
	if ( sceneObjectDesc )
	{
    NI_ALWAYS_ASSERT( NStr::StrFmt("Error SetSceneObject for flag: %s", sceneObjectDesc->GetDBID().GetFileName()) );
	}
	else
	{
    NI_ALWAYS_ASSERT( "Error SetSceneObject for flag: NULL" );
	}
}

void PFClientFlagpole::OnWorldObjectDie()
{
	PFClientBaseUnit::OnWorldObjectDie();
	if (pAG)
	{
		pAG->UnregisterCallback( DIANGR_NODE, idleNodeID, PFClientFlagpole::OnFlagRaised,  this);
		pAG->UnregisterCallback( DIANGR_NODE, idleNodeID, PFClientFlagpole::OnFlagDropped, this);
	}
}
}