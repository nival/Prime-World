#pragma once

// ===================================================================
//
// Scene Passability mask description.
// Can be edited on AdvMap editor
// ===================================================================

// ===================================================================
// Includes
// ===================================================================
#include "Scene.h"
#include "CollisionMap.h"

#include "../Render/DBRender.h"
#include "../Render/renderstates.h"
#include "../Render/renderer.h"
#include "../Render/sceneconstants.h"
#include "../Render/omnilight.h"
#include "../Terrain/TerrainGeometryManager.h"
#include "../System/ScopedArray.h"
#include "RenderableScene.h"

#include "../Terrain/Terrain.h"

#include "SceneObject.h"
#include "EditorSceneObject.h"


// ===================================================================
// Classes
// ===================================================================

namespace NWorld { struct Node; }
namespace Terrain { class TerrainElement; }

namespace NScene
{

  class ScenePassabilityMask: public CObjectBase
  {
    private:
      OBJECT_METHODS(0x1661D440, ScenePassabilityMask)

  
    public:  
      // Type for map entry element data
      typedef BYTE CellType;
      
      enum PassabilityValue
      {
        PASSABILITY_FREE      = 3,
        PASSABILITY_ENABLE    = 0,
        PASSABILITY_DISABLE   = 1
      };
      
      ScenePassabilityMask() { }
      ScenePassabilityMask(int sizeX, int sizeY);
     ~ScenePassabilityMask();
     
      bool                  Allocate(int mapWidth, int mapHeight, float metersPerTile);
     
      void                  ApplyHeightMap(::Terrain::Terrain *terrain);
      void                  ApplyObject(NDb::GameObject   *obj);
      
      CellType             *GetMapResult()                  { return Get(m_mapResult);              }
      CellType              GetCellResult(int x, int y)     { Get(m_mapResult)[x + y *  m_width];   }
      CellType              GetCellUser(int x, int y)       { Get(m_mapUser)[x + y *  m_width];     }
      CellType              GetCellObjects(int x, int y)    { Get(m_mapObjects)[x + y *  m_width];  }
      CellType              GetCellHeights(int x, int y)    { Get(m_mapHeights)[x + y *  m_width];  }
      
      void                  SetCellUser(int x, int y, CellType val);
      void                  SetCellObjects(int x, int y, CellType val);
      void                  SetCellHeights(int x, int y, CellType val);
      
      void                  UpdateResultMap();
      
    private:
    
      int                   m_width;
      int                   m_height;
      float                 m_metersPerTile;
      
      // 3 logical layers for map
      ScopedPtr<CellType>   m_mapResult;      // Result map, made automatically from User + Objects + Heights maps
      ScopedPtr<CellType>   m_mapUser;        // User modified layer, default is PASSABILITY_FREEE
      ScopedPtr<CellType>   m_mapObjects;     // Objects affected layer, builded automatically (can be ENABLE/DISABLE)
      ScopedPtr<CellType>   m_mapHeights;     // Heights affected layer, builded automatically (can be ENABLE/DISABLE)
  };
  
} // name space

  
