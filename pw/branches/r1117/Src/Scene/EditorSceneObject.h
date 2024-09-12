#pragma once
#include "SceneObject.h"
#include "DiAnGr.h"
#include "AnimGraphApplicator.hpp"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{

enum HighlightType
{
	HT_OFF,
	HT_COLLISION,
	HT_COLOR,
};

struct BasicMaterialProc : public Render::IMaterialProcessor, public NonCopyable
{
  float opacity;

  BasicMaterialProc(float o) : opacity(o) {}
  virtual void operator()(Render::BaseMaterial &material)
  {
    if (material.GetDBMaterial() && material.GetDBMaterial()->GetObjectTypeID() == NDb::BasicMaterial::typeId)
      material.ModifyOpacity(opacity);
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EditorSceneObject : public SceneObject
{
	//CObj<CollisionHull> pCollisionHull;
	Placement           originalPlacement;
	HighlightType highlightType;
  NDb::Ptr<NDb::DbResource> pHoldResource;
  int selectedLocator;
  bool isPlaceOnTerrain;
  int layer;

	EditorSceneObject() : highlightType( HT_OFF ), selectedLocator(-1), isPlaceOnTerrain( true ), layer( 1 ) {}

public:
	DECLARE_NEWDELETE_ALIGN16(EditorSceneObject)

	//seDECLARE_RING( EditorSceneObject, part, Ring );

  EditorSceneObject( IScene *pScene, const NDb::DbResource* pHoldResource, const vector<CObj<SceneComponent>>& components, const Placement& placement, const NDb::DBSceneObject* db );
	EditorSceneObject( IScene *pScene, const NDb::DbResource* pHoldResource, CObj<SceneComponent> pComponent, const Placement& placement, const NDb::DBSceneObject* db );
	virtual ~EditorSceneObject();

	void Highlight( HighlightType _highlight );

	void ShowSkin( const string& skinName, bool show );
	void ShowSkin( int skinName, bool show );
	void ShowSkin( const NDb::DBID& dbid, int skinName, bool show );
  nstl::vector<int> GetActiveSkins( const NDb::DBID& dbid );
	void TurnOffSkins();
	void TurnOffSkins( const NDb::DBID& dbid );
	void StartAnimation( int animationIndex );
	void StartAnimation( const NDb::DBID& dbid, int animationIndex );
	::DiAnimGraph const           * GetAnimationGraph() const;
	::DiAnimGraph                 * GetAnimationGraph();
	::DiAnimGraph                 * GetAnimationGraph( const NDb::DBID& dbid );
	::DiAnGrExtPars const         * GetExternalParameters() const;
	::DiAnGrExtPars               * GetExternalParameters();
	::DiAnGrExtPars               * GetExternalParameters( const NDb::DBID& dbid );
	NScene::AnimationVector const * GetAnimations() const;

  void SelectLocator( int i ) { selectedLocator = i; }

  void GetEditorSimpleBound(SBound &bound) const;

	void SetPositionWithPlacingOnTerrain( const Placement& pos );
  void ReplaceObjectOnTerrain();

  void SetParentTransformUsageFlags( unsigned int _flags );

  void SetLayer( int val )
  {
    layer = val;
  }

  void SetPlaceOnTerrain( bool val )
  {
    isPlaceOnTerrain = val;
  }

  virtual void Update( float timeDiff, bool isForcedUpdate = false );
  virtual void Render( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants, int groupFlagsFilter = GROUPFLAGS_ALL );

  vector<string const *> GetLocatorsNames();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorSceneObject* CreateEditorSceneObject( IScene *pScene, const NDb::Effect* pVisual, const Placement& placement );
EditorSceneObject* CreateEditorSceneObject( IScene *pScene, const NDb::StaticMesh* pVisual, const Placement& placement );
EditorSceneObject* CreateEditorSceneObject( IScene *pScene, const NDb::Skeleton* pVisual, const Placement& placement );
EditorSceneObject* CreateEditorSceneObject( IScene *pScene, const NDb::DBSceneObject* pVisual, const Placement& placement, bool addToScene, bool isStaticAndAnimatedOnly );
EditorSceneObject* CreateEditorSceneObject( IScene *pScene, const NDb::DBSceneComponent* pVisual, const Placement& placement );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
