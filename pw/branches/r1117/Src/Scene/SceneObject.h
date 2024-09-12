#pragma once
#include "SceneComponent.h"
#include "Scene.h"
#include "SceneObjectsPool.h"
#include "RenderableScene.h"
#include "../Render/SHCoeffs.h"
#include "../System/Ring.h"

#include "../System/Singleton4DLL.h"
#include "SceneObjectTrack.h"
#include "CollisionHull.h"

namespace NDb { struct Locator; }

namespace NScene
{

class LightingScene;

_interface ISceneObjectUpdateHook
{
	virtual void OnSceneObjectUpdate(class SceneObject &/*sceneObject*/, float /*timeDiff*/) {}
	virtual bool OnSceneObjectBecomeVisible(class SceneObject &/*sceneObject*/, float /*timeBeingInvisible*/) { return false; } // Return true if inv
	virtual void OnSceneObjectBecomeInvisible(class SceneObject &/*sceneObject*/) {}
};

class SceneObjectBase : public RenderableSceneObj
{
public:
	seDECLARE_RING( SceneObjectBase, part, Ring );

  SceneObjectBase(IScene *pScene_ = 0) : pScene( pScene_ ) {}

  virtual ~SceneObjectBase() 
  {
    RemoveFromScene();
  }

  IScene* GetScene() const { return pScene; }

	virtual void AddToScene( IScene *pScene_, UpdatePriority priority = UPDATEPRIORITY_NORMAL );
  virtual void RemoveFromScene();
  virtual void EnableRender(bool bEnable);

  virtual void Update( float timeDiff, bool isForcedUpdate = false ) {}

  virtual const char* FormatDescription();

	bool IsInScene() const { return part.isLinked(); }

protected:
	CPtr<IScene> pScene;
};

__declspec(align(16))
class SceneObject : public SceneObjectBase
{
protected:
	enum
	{
		FLAGS_VISIBLE = (1L << 0),
		FLAGS_MOVED   = (1L << 1)
	};

	Render::AABB worldAABB;


	CObj<SceneComponent> rootComponent;

  typedef list<Locator *> TLocators;
  TLocators locators;

	int  ownerID;

	// 
	int componentsVersion;

	void MarkRendered();

	void NotifyAttach(SceneComponent* pComponent);

	void ProcessMovement();

  bool forbidPick;

public:
	DECLARE_NEWDELETE_ALIGN16(SceneObject)

  SceneObject(IScene *pScene_ = 0, const NDb::DBSceneObject* db = 0);

	virtual ~SceneObject() 
	{
    DestoroyAllComponents();
    pUpdateHook = 0;
	}

    bool IsRendered() const;
	bool IsVisible() const;
	void MarkAsVisible();

  void Add( SceneComponent* _component );
	void AttachTo( SceneComponent* _component );

  void AttachToByLocator( const char *name, SceneComponent *_component, Placement* _placement = 0 );
	void AttachToByLocator( const Locator *pLocator, SceneComponent *_component, Placement* _placement = 0 );

  void Detach( SceneComponent* _component );

	const Locator *FindLocator( const char *name ) const;

  bool IgnoreAttachesToNonDefaultLocators() const;

	void Reinit();
	void Deinit();

	virtual void Update( float timeDiff, bool isForcedUpdate = false );

	void UpdateForced( float timeDiff = 0.0f, bool isUnfreeze = false, bool isClientVisible = true );

  void UpdateWithAnimatedTrack( SceneComponent* it, SceneComponent::UpdatePars& updatePars, float timeDiff );
  void SetFreeze( bool freeze = true );
	bool IsFrozen() const { return freezeCount > 0; }

  virtual void Render( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter = GROUPFLAGS_ALL );
  void RenderDirectly( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter = GROUPFLAGS_ALL );

	virtual const Render::AABB &GetWorldAABB() const { return worldAABB; }

  void UpdateWorldAABB();

  void GetBound(SBound &bound) const;

	void SetupForLighting();

	void SetPlacement( const Matrix43& pos );
	void SetPlacement( const Placement& pos );
	void SetPositionAndRotation( const Placement& pos );
	void SetPosition( const CVec3& pos );
	void SetScale( const CVec3& scale );
	const Placement& GetPosition() const { return placement; }
	SceneComponent* GetRootComponent() { return rootComponent; }
  const SceneComponent * GetRootComponent() const { return rootComponent; }
	void SetOwner( SceneObject* so );

	int GetListOfComponentsVersion() { return componentsVersion; }

	void SetUpdateHook(ISceneObjectUpdateHook *pHook) { pUpdateHook = pHook; }

  virtual void AddToScene( IScene *pScene_, UpdatePriority priority = UPDATEPRIORITY_NORMAL );
  virtual void RemoveFromScene();
  virtual void EnableRender(bool bEnable);

  void AddLocator(NDb::Locator const &l, SceneComponent *pSC);
  void AddLocator(Locator &l) { AddLocator(l.locator, l.pSC); }
  void RemoveLocator( const Locator& l);
  template<typename Func> void ForAllLocators(Func &func) const;

	void CalculateLocatorWorldMatrix(const Locator &locator, Matrix43 &m, const bool isVisible);
	void CalculateLocatorWorldPlacement(const Locator &locator, Placement &pl);
	void CalculateLocatorWorldPosition(const Locator &locator, CVec3 &pos, const bool isVisible = true);

  float ApplyTrack( const NDb::SceneObjectTrack* track );
  float ApplyTrack( const nstl::string& track );

  void SetTrackDirection( const CVec3& direction ) { animatedTrack.SetDirection( direction ); }

	template<typename Traverser> void Traverse( Traverser& traverser );
	template<typename Traverser> void Traverse( Traverser& traverser ) const;

	template<typename Traverser> void ForAllRoots( Traverser& traverser )
	{
		ForAllBrothers( rootComponent, traverser);
	}

  static bool NeedDebugRender();
  virtual void DebugDraw( Render::IDebugRender* _debugRenderer );

  void DebugDrawLocators( Render::IDebugRender* _debugRenderer );
  void DebugDrawAABBs( Render::IDebugRender* _debugRenderer, const Render::Color &color );

	void Dump() const;

	int  GetOwnerID() const { return ownerID; }
	void SetOwnerID(int id );

  virtual const char* FormatDescription();

  void ProcessExternalEvent(const char *eventName);

  void CalculateLighting(Render::SceneConstants const &sceneConst);
  void CalculateLightingEx(Render::SceneConstants const &sceneConst, NDb::ELightEnvironment const selector);
  void UpdateSH();
  void ResetTimeBeingInvisible() { timeBeingInvisible=0.0f; }

  void RegisterCollisionGeometry( const NDb::CollisionGeometry* colgeom );
  void UnregisterCollisionGeometry();

  CollisionHull* GetCollision() const;
  void SetCollision( CollisionHull* collisionHull, CollisionHull* collisionSmallHull );
  CollisionHull* GetSmallCollision() const;

  bool IsForbidPick() const { return forbidPick; }
  void SetForbidPick( bool value ) { forbidPick = value; }

	void ResetTrack();

	void SetNodeName( const nstl::string& nodeName );

  nstl::string GetDBIDName() { return IsValid(dbResource) ? dbResource->GetDBID().GetFileName() : "none"; }

  void DestoroyAllComponents();

  void LockRotation(const bool lock)
  {
    if (lock)
    {
      ++rotationLockCounter;
    }
    else if (rotationLockCounter > 0U)
    {
      --rotationLockCounter;
    }
  }
private:

	void SynchronizeToVisibleState();

	bool WasRendered();

  bool IsRotationLocked() const
  {
    return (rotationLockCounter > 0U);
  }

	friend class SceneObjectsPool;

	DWORD     dwDBHash;
	Placement placement;
	int       whenWasRendered;
	int       freezeCount;
	int       flags;
	float     timeBeingInvisible;
	ISceneObjectUpdateHook *pUpdateHook; // SceneObject doesn't own this hook!
	ScopedPtr<Render::SHShaderConstants> pSHConsts;
  NDb::Ptr<NDb::DBSceneObject> dbResource;
  SceneObjectTrack animatedTrack;
  CObj<NScene::CollisionHull>  pCollisionHull;
  CObj<NScene::CollisionHull>  pSmallCollisionHull;
  bool hasCollisionGeometry;

  unsigned rotationLockCounter;
};

//////////////////////////////////////////////////////////////////////////
// Traversers
//////////////////////////////////////////////////////////////////////////

struct GenericTraverser
{
	bool IsTraversable(const SceneComponent* comp) const
	{
		return comp->IsTraversable();
	}
	bool NeedToProcess(const SceneComponent* comp) const
	{
		return true;
	}
};

struct FullTraverser : public GenericTraverser
{
	// always traversable
	virtual bool IsTraversable(const SceneComponent*) const { return true; }
};

struct TraverserById : public FullTraverser, private NonCopyable
{
	const char* id;
	TraverserById(const char* id) : id(id) {}
	bool NeedToProcess(const SceneComponent* comp)const
	{
		return comp->GetId() == id;
	}
};

struct TraverserByGroupFlags : public GenericTraverser
{
  int groupFlags;
  bool fullTraverse;
  TraverserByGroupFlags(int groupFlags, bool fullTraverse) : groupFlags(groupFlags), fullTraverse(fullTraverse) {}
  bool IsTraversable(const SceneComponent* comp) const { return fullTraverse || comp->IsTraversable(); }
  bool NeedToProcess(const SceneComponent* comp)const
  {
    return (comp->GetGroupFlags() & groupFlags) == groupFlags;
  }
};

struct TraverserIgnoreGroupFlags : public TraverserByGroupFlags
{
  TraverserIgnoreGroupFlags(int groupFlags, bool fullTraverse) : TraverserByGroupFlags(groupFlags, fullTraverse) {}
  bool NeedToProcess(const SceneComponent* comp)const
  {
    return (comp->GetGroupFlags() & groupFlags) == 0;
  }
};


//////////////////////////////////////////////////////////////////////////
template<typename Traverser>
void SceneObject::Traverse( Traverser& traverser )
{
	if ( rootComponent )
	{
		SceneComponent* itFront = rootComponent;
    if ( itFront )
    {
		  SceneComponent* it = itFront;
		  do
		  {
			  it->Traverse( traverser );
			  it = it->GetBrother();
		  } while ( it && it != itFront );
    }
	}
}
template<typename Traverser>
void SceneObject::Traverse( Traverser& traverser ) const
{
	if ( rootComponent )
	{
		SceneComponent* itFront = rootComponent;
    if ( itFront )
    {
		  SceneComponent* it = itFront;
		  do
		  {
			  it->Traverse( traverser );
			  it = it->GetBrother();
		  } while ( it && it != itFront );
    }
	}
}

template<typename Func>
void SceneObject::ForAllLocators(Func &func) const
{
  for ( TLocators::const_iterator it = locators.begin(); it != locators.end(); )
  {
    const Locator * l = *it;
    ++it;
    func( *l );
  }
}

}
