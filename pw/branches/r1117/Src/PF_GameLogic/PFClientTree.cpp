/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "DBStats.h"
#include "PFBaseUnitStates.h"
#include "PFClientMultistateObject.h"
#include "PFClientNatureSceneObjectsHolder.h"

#include "../Render/dxutils.h"
#include "../Render/renderer.h"
#include "../Render/smartrenderer.h"
#include "../Render/vertexformatdescriptor.h"
#include "../Render/renderresourcemanager.h"
#include "../Render/GlobalMasks.h"
#include "../Render/ImmediateRenderer.h"

#include "PFClientTree.h"
#include "PFTree.h"
#include "TileMap.h"
#include "WarFog.h"

#include "../Scene/SceneObjectCreation.h"

#include "AdventureScreen.h"
//#include "PFClientVisibilityMap.h"

#include "../System/InlineProfiler.h"

/////////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////////

#define   PI_DIV_2                (3.1415f/2.0f)
#define   TREE_ROT_SPEED          (PI_DIV_2/2.0f)
#define   TREE_MOVE_DOWN_SPEED    (0.1f/2.0f)
#define   TREE_GROW_TIME          10

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientTree::PFClientTree(const PF_Core::WorldObjectRef &pWO, const NDb::AdvMapObject &mapObject, NScene::IScene* pScene, int faction)
  : PFClientMultiStateObject( pWO, pScene, mapObject, faction )
  , state(TreeState_Tree)
	, lastVisibleState(TreeState_Tree)
  , fallingTree(false)
  , startDrop(false)
  , dropByAlly(false)
{
  NI_ASSERT( dynamic_cast<const NDb::TreeObject*>( mapObject.gameObject.GetPtr() ), "Bad cast to NDb::TreeObject!" ) ;
  pDBDesc = static_cast<const NDb::TreeObject*>( mapObject.gameObject.GetPtr() );

  wonderfulTree = pDBDesc->wonderfulTree;

  Reset(pStubsSceneObjectsHolder, NatureSceneObjectsHolder::CreateWithTreeStubs(pScene, this, GetPosition(), pWO->GetObjectId(), pDBDesc));

  const bool night = WorldObject() ? WorldObject()->GetWorld()->IsNight() : false;

  pStubsSceneObjectsHolder->SetActive(SelectSceneObjectIndex(faction, night), false);
  pStubsSceneObjectsHolder->Enable(false);

  if ( wonderfulTree )
  {
    pSceneObjectsHolder->Enable(false);
    Reset(pSceneObjectsHolder->GetActive(), NULL);
    pStubsSceneObjectsHolder->Enable(false);
    Reset(pStubsSceneObjectsHolder->GetActive(), NULL);
  }
  pStubsSceneObjectsHolder->SetActive(SelectSceneObjectIndex(NDb::NATURETYPE_N, night), bVisible);
  
  // закоменировано по просьбе дизайнеров - деревья теперь не интерактивны..
  //NScene::SceneObject* pSceneObject = GetSceneObject();
  //if ( pSceneObject )
  //{
  //  pCollisionHull = MakeCollisionHullForObject( pSceneObject, pDBTree->collisionGeometry );
  //}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFClientTree::NeedToUpdate() const
{
  return startDrop || ( ( pSceneObjectsHolder && pSceneObjectsHolder->NeedUpdateTransactions() ) ||
          ( pStubsSceneObjectsHolder && pStubsSceneObjectsHolder->NeedUpdateTransactions() ) ||
          ( pTreeSceneObjectsHolder && pTreeSceneObjectsHolder->NeedUpdateTransactions() ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientTree::Update(float timeDelta)
{
  NI_PROFILE_FUNCTION

  if ( startDrop )
  {
    startDrop = false;

    if ( !bVisible )
    {
      if ( dropByAlly )
      {
        SetVisibility( true );
      }
    }

    if ( pSceneObjectsHolder )
    {
      if ( bVisible )
      {
        pSceneObjectsHolder->DropTree( dropDir, pDBDesc );
        fallingTree = true;
      }
    }

    state = TreeState_Stub;

    if ( bVisible )
    {
      SelectActualHolder();
    }

    SubscribeToUpdate();
  }
  else
  {
    if (pTreeSceneObjectsHolder && pTreeSceneObjectsHolder->NeedUpdateTransactions())
      pTreeSceneObjectsHolder->Update(timeDelta);
    if (pStubsSceneObjectsHolder && pStubsSceneObjectsHolder->NeedUpdateTransactions())
      pStubsSceneObjectsHolder->Update(timeDelta);

    if ( state == TreeState_Stub && fallingTree )
    {
      if ( !pTreeSceneObjectsHolder || pTreeSceneObjectsHolder->NeedUpdateTransactions() )
        fallingTree = false;
    }

    PFClientMultiStateObject::Update(timeDelta);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientTree::SetState(const int _natureType, const bool _night)
{
  const int sceneObjectIndex = SelectSceneObjectIndex(_natureType, _night);

  if ( pTreeSceneObjectsHolder )
    pTreeSceneObjectsHolder->SetActive(sceneObjectIndex, bVisible);
  if ( pStubsSceneObjectsHolder )
    pStubsSceneObjectsHolder->SetActive(sceneObjectIndex, bVisible);

  PFClientMultiStateObject::SetState(_natureType, _night);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientTree::Switch2Stub()
{
  NI_ASSERT( pSceneObjectsHolder && !pTreeSceneObjectsHolder && pStubsSceneObjectsHolder, "Switch2Stub : SceneObjectsHolders state invalid!" );
  
  // Replace tree to stub
  if ( !fallingTree )
    pSceneObjectsHolder->Enable(false); // keep tree object visible while it fall to ground
  
  pTreeSceneObjectsHolder = pSceneObjectsHolder;
  pSceneObjectsHolder = pStubsSceneObjectsHolder;

  pSceneObjectsHolder->Enable(true, false);    // show stub scene object

	// Remove collision
  if ( GetSceneObject() && GetSceneObject()->GetCollision() )
    GetSceneObject()->GetCollision()->SetEnabled(false);
  if ( GetSceneObject() && GetSceneObject()->GetSmallCollision() )
    GetSceneObject()->GetSmallCollision()->SetEnabled(false);
}

//////////////////////////////////////////////////////////////////////////
void PFClientTree::Switch2StubImmediately()
{
  state = TreeState_Stub;
  lastVisibleState = TreeState_Stub;

  fallingTree = false;
  dropByAlly = false;
  startDrop = false;

  NI_ASSERT( pSceneObjectsHolder && !pTreeSceneObjectsHolder && pStubsSceneObjectsHolder, "Switch2Stub : SceneObjectsHolders state invalid!" );

  pSceneObjectsHolder->Enable(false); // keep tree object visible while it fall to ground

  pTreeSceneObjectsHolder = pSceneObjectsHolder;
  pSceneObjectsHolder = pStubsSceneObjectsHolder;
  pSceneObjectsHolder->Enable(true, true);    // show stub scene object

  // Remove collision
  if ( GetSceneObject() && GetSceneObject()->GetCollision() )
    GetSceneObject()->GetCollision()->SetEnabled(false);
  if ( GetSceneObject() && GetSceneObject()->GetSmallCollision() )
    GetSceneObject()->GetSmallCollision()->SetEnabled(false);
  
  SubscribeToUpdate();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientTree::Switch2Tree()
{
  NI_ASSERT( pSceneObjectsHolder && pTreeSceneObjectsHolder && !pStubsSceneObjectsHolder, "Switch2Tree : SceneObjectsHolders state invalid!" );
  
  //const NScene::SceneObjectRef& tree = pTreeSceneObjectsHolder->GetActive();
	
  pTreeSceneObjectsHolder->Enable(true, false);  // show tree scene object
  
  // Replace stub to tree 
  pStubsSceneObjectsHolder = pSceneObjectsHolder;
  pSceneObjectsHolder = pTreeSceneObjectsHolder;
  
  pStubsSceneObjectsHolder->Enable(false, false);        // hide stub scene object
  
  // Enable collision
  if ( GetSceneObject() && GetSceneObject()->GetCollision() )
    GetSceneObject()->GetCollision()->SetEnabled(true);
  if ( GetSceneObject() && GetSceneObject()->GetSmallCollision() )
    GetSceneObject()->GetSmallCollision()->SetEnabled(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientTree::SelectActualHolder()
{
  if (lastVisibleState != state)
  {
    if ( state == TreeState_Tree )
      Switch2Tree();
    else
      Switch2Stub();
    lastVisibleState = state;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientTree::DropTree( const CVec2& dir, const CPtr<NWorld::PFBaseUnit>& pUnitThatDropsTree )
{
  NI_ASSERT( state == TreeState_Tree, "Need to be in Tree state to drop!" );

	//Finish transaction if needed
	if ( active )
  {
    for ( int i = 0; i < 5; i++ )
    {
      Update( 1.0f );
    }
  }

  startDrop = true;
  dropDir = dir;
  dropByAlly = pUnitThatDropsTree->GetFaction() == AdventureScreen::Instance()->GetPlayerFaction();

  // start drop tree next frame only 
  if ( !active )
  {
    active = true;
    Subscribe();
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientTree::RestoreTree()
{
	state = TreeState_Tree;
  fallingTree = false;
  if (bVisible)
    SelectActualHolder();
	
  SubscribeToUpdate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientTree::SetVisibility(bool bVisible_)
{
  if (DoCheckVisible(bVisible_))
    return;

  UpdateEffectsVisibility( bVisible_ );
  
  if (bVisible_)
    SelectActualHolder();

  PFClientMultiStateObject::SetVisibility( bVisible_ );
}

void PFClientTree::OnEffectAttach( PF_Core::BasicEffectAttached * pEffect )
{
  PFClientMultiStateObject::OnEffectAttach( pEffect );

  attachedEffects.push_back( pEffect );

  if ( !bVisible )
  {
    pEffect->Hide( true );
  }
}

void PFClientTree::UpdateEffectsVisibility( bool bVisible )
{
  for ( list<CPtr<PF_Core::BasicEffectAttached>>::iterator it = attachedEffects.begin(); it != attachedEffects.end(); ++it )
  {
    PF_Core::BasicEffectAttached* pEffect = *it;
    if ( IsValid(pEffect) && !pEffect->IsDead() && pEffect->GetSceneObject() == GetSceneObject() )
      pEffect->Hide( !bVisible );
    else
      it = attachedEffects.erase( it );
  }
}

} // namespace


