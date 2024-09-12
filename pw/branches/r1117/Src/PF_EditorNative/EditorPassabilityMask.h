#pragma once
// ==============================================================================
// Editor passability mask
// Managed C++ code
// ==============================================================================

// ==============================================================================
// Includes
// ==============================================================================

#include "../System/Basic.h"

/*
#include "../EditorNative/GraphicElement.h"
#include "../EditorNative/Vector2.h"
#include "../EditorNative/Vector3.h"
#include "../EditorNative/ManipulatorElement.h"
#include "../EditorNative/ManipulatorsController.h"
#include "../EditorNative/IObjectTransformControllersProvider.h"
#include "../EditorNative/EditorTerrain.h"
#include "../EditorNative/PickResult.h"
#include "../EditorNative/Camera.h"
#include "../EditorNative/EditorLightEnvironment.h"
#include "../EditorNative/CinemaMode.h"
#include "../EditorNative/EditorDebugVars.h"


#include "../EditorNative/EditorTerrain.h"
#include "../EditorNative/EditorScene.h"
*/
#include "../Scene/ScenePassabilityMask.h"


#include "../Terrain/Terrain.h"

typedef ::Terrain::Terrain    NativeTerrain;

// ==============================================================================
// Classes
// ==============================================================================

namespace PF_EditorNative
{

  public ref class EditorPassabilityMask
  {
  private:
    CPtr<NScene::ScenePassabilityMask>    *m_scenePassabilityMask;
    
  public:
    EditorPassabilityMask();
   ~EditorPassabilityMask();

   NScene::ScenePassabilityMask *GetScenePassabilityMask()
   {
     return (*m_scenePassabilityMask);
   }
   
   bool   AllocateScenePassabilityMask(int width, int height, float metersPerTile)
   {
      bool                          ret;
      NScene::ScenePassabilityMask  *scene;
      
      scene = GetScenePassabilityMask();
      ret = scene->Allocate(width, height, metersPerTile);
      return ret;
   }   
  };

} // namespace

