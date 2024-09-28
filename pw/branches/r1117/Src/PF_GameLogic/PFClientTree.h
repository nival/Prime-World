#pragma once

/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../PF_Core/ClientObject.h"

#include "PFClientMultistateObject.h"

#include "../Scene/RenderableScene.h"
#include "../Render/RenderInterface.h"
#include "../Render/Renderer.h"
#include "../Render/batch.h"
#include "../Render/texture.h"

#include "../Scene/SceneObject.h"

#include "../Terrain/TerrainLayerManager.h"

namespace NWorld 
{ 
	class PFTree; 
	class PFBaseUnit;
}

namespace PF_Core
{
  class BasicEffectAttached;
}

namespace NGameX
{

  /////////////////////////////////////////////////////////////////////////////////
  // Classes
  /////////////////////////////////////////////////////////////////////////////////
  
  enum TreeState
  {
    TreeState_Tree,
    TreeState_Stub,
  };

  class PFClientTree : public PFClientMultiStateObject
  {
    CLIENT_OBJECT_METHODS( 0x16616C41, PFClientTree, NWorld::PFTree )
    explicit PFClientTree() {}
  public:
    PFClientTree(const PF_Core::WorldObjectRef &pWO, const NDb::AdvMapObject &mapObject, NScene::IScene* pScene_, int faction);

		void          DropTree( const CVec2& dir, const CPtr<NWorld::PFBaseUnit>& pUnitThatDropsTree );
    void          RestoreTree();
    virtual void  SetState(const int _natureType, const bool _night);
		virtual void  SetVisibility(bool bVisible);

    void Switch2StubImmediately();

    virtual void OnEffectAttach( PF_Core::BasicEffectAttached * pEffect );

  private:
    virtual void  Update(float timeDelta);
    
    void UpdateEffectsVisibility( bool bVisible );
		
		void Switch2Stub();
		void Switch2Tree();
    void SelectActualHolder();
    
    virtual bool NeedToUpdate() const;
    
    bool      wonderfulTree;

    TreeState state;
    TreeState lastVisibleState;

    AutoPtr<ISceneObjectsHolder> pTreeSceneObjectsHolder;
    AutoPtr<ISceneObjectsHolder> pStubsSceneObjectsHolder;

    // Drop
    bool      fallingTree;
    
		// For the visibility check
		bool visibilityCheckPoints[4];
    NDb::Ptr<NDb::TreeObject> pDBDesc;
    bool startDrop;
    CVec2 dropDir;
    bool dropByAlly;
    list<CPtr<PF_Core::BasicEffectAttached>> attachedEffects;
  };

}
