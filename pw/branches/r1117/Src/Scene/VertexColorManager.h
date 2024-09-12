#pragma once

namespace Render
{
	class MeshVertexColors;
}

namespace NScene
{

class StaticSceneComponent;

// On the level of StaticSceneComponent or AnimatedSceneComponent
class MeshVertexColorsManager
{
public:
  MeshVertexColorsManager(bool bEditorMode) : m_curAdvMapObjIdx(-1), m_curSceneObjDBIDHash(0), m_bEditorMode(bEditorMode) {}

	AutoPtr<Render::MeshVertexColors> RequestVertexColorStream(int componentIdx, StaticSceneComponent *comp);

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Storage interface
  void AdvMapObjectVCBegin(int advMapObjIdx)
  {
    NI_ASSERT(m_curAdvMapObjIdx == -1, "Another AdvMapObject processing in progress");
    m_curAdvMapObjIdx = advMapObjIdx;
  }
  void AdvMapObjectVCEnd(int advMapObjIdx)
  {
    NI_ASSERT(m_curAdvMapObjIdx == advMapObjIdx, "This AdvMapObject processing wasn't started");
    m_curAdvMapObjIdx = -1;
  }

  void SceneObjectVCBegin(const NDb::DBID *pObj)
  {
    NI_ASSERT(m_curSceneObjDBIDHash == 0, "Another SceneObject processing in progress");
    m_curSceneObjDBIDHash = pObj->GetHashKey();
  }
  void SceneObjectVCEnd(const NDb::DBID *pObj)
  {
    NI_ASSERT(m_curSceneObjDBIDHash == pObj->GetHashKey(), "This SceneObject processing wasn't started");
    m_curSceneObjDBIDHash = 0;
  }
  void SceneComponentVCStore(int componentIdx, StaticSceneComponent *comp);

  void Save( const string& fileName );
  void Load( const string& fileName );

private:
  bool m_bEditorMode;
  int  m_curAdvMapObjIdx;
  unsigned int m_curSceneObjDBIDHash;

  // database
  struct TSceneCompColors
  {
    ZDATA
    DWORD                   sign;
    vector<Render::Color>   colors0;
    vector<Render::Color>   colors1;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&sign); f.Add(3,&colors0); f.Add(4,&colors1); return 0; }
  };

  typedef vector<TSceneCompColors>   TSceneObjColors;
  typedef hash_map<unsigned int, TSceneObjColors>  TObjectColors;
  
  vector<TObjectColors>  m_objects;
};


}