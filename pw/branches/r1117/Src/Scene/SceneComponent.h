#pragma once
#include "Scene.h"
#include "TimeMutator.h"
#include "TimeController.h"
#include "DBScene.h"
#include "../System/nalgoritm.h"
#include "../System/Placement.h"
#include "../Render/RenderComponent.h"
#include "AnimatedPlacement.h"

class DiAnimGraph;
struct DiAnGrCallbackParams;
typedef long int (*AnimationCallback)(DiAnGrCallbackParams const &cpParams);

#ifndef _SHIPPING
#define SCENECOMPONENT_STATS
#endif // _SHIPPING

namespace Render 
{ 
	struct AABB; 
	struct SceneConstants;
}

namespace NScene
{

class GroundHitEvent;

struct Locator : public NonCopyable
{
  NDb::Locator   locator;
  SceneComponent *pSC;

  Locator() : pSC(NULL) {}
  Locator(Locator const &l) { locator = l.locator; pSC = l.pSC; }
  ~Locator() {}
  void operator= (Locator const l) { locator = l.locator; pSC = l.pSC; }

  void DebugRender( Render::IDebugRender* _debugRenderer ) const;
  void MakeAttachementPlacement(Placement &pl) const;
  void CalculateWorldMatrix(Matrix43 &m) const;
  void CalculateWorldPlacement(Placement &pl) const;
  void CalculateWorldPosition(CVec3 &pos) const;
};

class SceneComponent : public CObjectBase
{
  OBJECT_BASIC_METHODS( SceneComponent );

public:
  enum InternalGroupFlags
  {
    // This enum uses part of the bit range, the lower bits are used by NDb::EGroupFlags.
    GROUPFLAGS_EFFECT = (1 << 3),
    GROUPFLAGS_CASTSHADOW = (1 << 4),
    GROUPFLAGS_REFLECTINWATER = (1 << 5),
    GROUPFLAGS_GROUND_ATTACH = (1 << 6),
  };

	struct UpdatePars : public NonCopyable
	{
		UpdatePars(Render::AABB &objectAABB_, IScene *pScene_, float timeDiff_, bool isUnfreeze_, bool isClientVisible_ = true ) 
			: objectAABB(objectAABB_), pScene(pScene_), timeDiff(timeDiff_), isUnfreeze(isUnfreeze_), isClientVisible(isClientVisible_)
		{}

		Render::AABB &objectAABB; 
		IScene       *pScene; 
		float        timeDiff;
    bool         isUnfreeze;
    bool         isClientVisible;
	};

	SceneComponent();
	SceneComponent(const NDb::DBSceneComponent* pDBComponent, const NDb::AttachedSceneComponent* pObj, 
								 const Placement& pos);

  virtual ~SceneComponent();

  string const &GetId() const { return id; }
  void SetId(string const &_id) { id = _id; }

	int GetGroupFlags() const { return groupFlags; }
	void SetGroupFlags(int flags) { groupFlags = flags; }

	// Should be called after creation
	virtual void Init();

	// Is called on reinitialization of scene component
	virtual void Reinit();

	// Reinits component and all it's children
	void ReinitSubTree();

	// Deinits component and all it's children
	void DeinitSubTree();

  // init enabled/disabled (strong) state of the component which is enabled/disabled by events
  void InitDisabledState();

  // Is called when time goes back to zero (loops)
	virtual void OnTimeLooped(float time2StartWith) { SetAnimatedsTime(time2StartWith); }

	// Is called on removing scene component
	virtual void Deinit() {} 

	virtual void SetWorldMatrixForWorldSpace() {}

	virtual void Update( UpdatePars &pars, const Placement& parentPos, float timeDelta );

	virtual void RenderToQueue( class Render::BatchQueue& /*queue*/, const Render::SceneConstants& /*sceneConstants*/ ) {}

	const Render::AABB &GetWorldAABB() const { return worldAABB; }

	const Render::AABB &GetLocalAABB() const { return localAABB; }

  virtual void AddBrother( SceneComponent* _component );

  SceneComponent* GetBrother() const { return rightBrother; }
  SceneComponent* GetChild() const { return child; }
  SceneComponent* GetParent() const { return parent; }

  void DetachFromSiblings();

  virtual void Attach( SceneComponent* toadd );

  virtual void Detach();

  // called after this component has been attached as a child to some other component
  virtual void OnAfterAttached();

	// called after this component has been added to a SceneObject // smirnov [2009/1/22]: may need refactoring in future
	virtual void OnAfterAdded(class SceneObject *pObject) {}

	void SetPlacement( const Placement& newplace ) { offset.SetPlacement( newplace ); }
  const Placement& GetPlacement() { return offset.GetPlacement(); }
  
  // hack to retrieve original offset (without locator etc.)
  const Placement& GetOriginalPlacement() { return offset.GetOriginal(); }

  Locator &RegisterLocator(NDb::Locator const &l);
  void SwapLocators(SceneComponent &sc);
  const nstl::vector<Locator*>& GetLocators() const
  {
    return locators;
  }

	void SetSpeed( float speed ) { timeController.SetSpeed( speed ); }
	void ResetSpeed() { timeController.ResetSpeed(); }

	void SetTimeController( const NDb::Ptr<NDb::TimeController> pTimeController );
  NDb::Ptr<NDb::TimeController> GetTimeControllerDesc() const;
  // Выдает текущее номинальное время
  // Т.е. если у нас есть анимация в 10с, но она ускорена в 2 раза (длина = 5с),
  // и прошло 2.5секунды, то мы находимся в середине анимации. В этом случае функция
  // вернет 5с.
  float GetAnimatedTime() const;
  // Выдает текущее время
  // Т.е. если у нас есть анимация в 10с, но она ускорена в 2 раза (длина = 5с),
  // и прошло 2.5секунды, то мы находимся в середине анимации. В этом случае функция
  // вернет 2.5с.
  virtual float GetCurTime() const;

  // Возвращает длину неускореной анимации
  // Т.е. если у нас есть анимация в 10с, но она ускорена в 2 раза (длина = 5с),
  // то функция вернет 10с.
  virtual float GetPureAnimLength() /*const*/; // @BVS@HACK
  // Возвращает длину анимации
  // Т.е. если у нас есть анимация в 10с, но она ускорена в 2 раза (длина = 5с),
  // то функция вернет 5с.
  float CalculateTransformedAnimLength() const;
  // Возвращает длину анимации всего поддерева вниз, включая текущий узел
  float GetSubTreeAnimLength() const;
  // Возвращает ускорение этой SceneComponent, вызванное родительскими TimeController'ами
  float GetParentSpeedCoeff() const;

  const string& GetLocatorName() { return locatorName; }
  unsigned int GetLocatorFlags() { return locatorFlags; }
  void SetLocatorName( const string& name, unsigned int _locatorFlags=0 ) 
  { 
    locatorName = name;
    locatorFlags = _locatorFlags;
  }

  virtual bool IsStayInWorld()
  {
    return parentTransformUsage & NDb::ATTACHFLAGS_STAYINWORLD;
  }

  int GetJointIdx() { return jointIdx; }
  void SetJointIdx( int idx ) { jointIdx = idx; }

  virtual vector<string> GetJointsList() const
  {
    return vector<string>();
  }

	void SetParentTransformUsageFlags( unsigned int flags ) { parentTransformUsage = flags; }
  unsigned int GetParentTransformUsageFlags() const { return parentTransformUsage; } 

  virtual void ForAllMaterials(Render::IMaterialProcessor &/*proc*/) {}

	Placement const &GetWorldPlacement() const { return worldPlacement; }

  virtual bool RetrieveJointPlacement(const string& /*name*/, Placement &/*pos*/)
	{
		return false;
	}
	
  void SetDBID( const NDb::DBID& _dbid )
  {
	  dbid = _dbid;
  }

  const NDb::DBID& GetDBID() const
  {
	  return dbid;
  }

  const char* FormatDescription() const
  {
    return NStr::StrFmt("%s", GetFormattedDbId(GetDBID()).c_str());
  }

  bool IsTraversable() const { return (disabledCount <= 0); }
	bool IsStronglyDisabled() const { return (disabledCount & STRONG_DISABLE_FLAG) != 0; }
  
  void EnableWeak(bool bVal) // User oriented
  {
    if (bVal)
      --disabledCount;
    else
      ++disabledCount;
    OnTraversibleChanged();
  }

	void DisableStrong(bool bVal) // System based
	{
		if (bVal)
			disabledCount |= STRONG_DISABLE_FLAG;
		else
			disabledCount &= ~STRONG_DISABLE_FLAG;
    OnTraversibleChanged();
	}

	virtual void SetNodeName( const nstl::string& nodeName ) {}
	virtual void DisableStrongWithWaitingForFinish();
  virtual bool Ready2Die()
  {
    return true;
  }

	template<typename Traverser> void Traverse( Traverser& traverser );
	template<typename Traverser> void Traverse( Traverser& traverser ) const;
  
  // synchronous traversal for duplicate hierarchies
  template<typename STraverser> static void SyncTraverse( SceneComponent &root1, SceneComponent &root2, STraverser& traverser );

  Placement const &GetBase() const
  {
		return offset.GetBase();
  }

  void SetBase( const CVec3& pos, const CQuat& rot, const CVec3& scale )
  {
		offset.SetBase( pos, rot, scale );
  }

  void SetLocatorPos( const CVec3& pos, const CQuat& rot, const CVec3& scale )
  {
    offset.SetLocator( pos,
      (parentTransformUsage & NDb::ATTACHFLAGS_USEPARENTROTATION) ? rot : QNULL,
      (parentTransformUsage & NDb::ATTACHFLAGS_USEPARENTSCALE) ? scale : CVec3(1.f, 1.f, 1.f));
  }

  void AddBase( const CVec3& pos, const CQuat& rot, const CVec3& scale )
  {
    Placement newbase( pos, rot, scale );
    newbase += offset.GetBase();
    offset.SetBase( newbase.pos, newbase.rot, newbase.scale );
  }

  void AddLocator( const CVec3& pos, const CQuat& rot, const CVec3& scale )
  {
    Placement newlocator( pos, rot, scale );
    newlocator += offset.GetLocator();
    offset.SetLocator( newlocator.pos, newlocator.rot, newlocator.scale );
  }

  bool IsLocatorRised() const { return isLocatorRised; }

  void SetLocatorRised( bool isRised ) { isLocatorRised = isRised; }

	static float CalculateSortingValue(const Render::AABB &worldAABB, const Render::SceneConstants &sceneConstants);

  void SetHide( bool val )
  {
    isHide = val;
  }

  bool IsHide()
  {
    return isHide;
  }

	void EnableByEvent();
	void DisableByEvent();

  virtual void ProcessExternalEvent(const char *eventName);

  virtual void ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add);

#ifdef SCENECOMPONENT_STATS
  static void StatisticsGet(unsigned long* pNumTotal, unsigned long* pNumShadows, unsigned long* pNumReflections);
  static void StatisticsRenderGet(unsigned long* pNumTotal, unsigned long* pNumShadows, unsigned long* pNumReflections);
  static void StatisticsRenderReset();
  static void StatisticsRenderAdd(int groupFlagsFilter);
#endif // SCENECOMPONENT_STATS

	// Debug functionality
	virtual void Dump() const;

protected:
	enum 
	{ 
		STRONG_DISABLE_FLAG        = 0x40000000, // for disabledCount
		WORLDPLACE_ALREADY_UPDATED = 0x40000000  // parentTransformUsage
	};

	void ConstructWorldPlacement(const Placement& _parentPos, IScene *pScene = NULL);
	void SetAnimatedsTime(float time);

	// Updates time, placement & materials
	bool UpdateBasics( UpdatePars &pars, const Placement& parentPos, float timeAdvance, float &timeDelta );
	void PassUpdate2Children( UpdatePars &pars, const Placement& parentPos, float timeDelta );

	virtual void UpdateComponent( UpdatePars &/*pars*/, const Placement& /*parentPos*/, float /*timeDiff*/ ) {}

	bool Need2DisableComponentOnStart() const;

  virtual void OnTraversibleChanged() {}

  void SetupAnimEvents(const vector<NDb::Ptr<NDb::SCEvent>> &events, AnimationCallback _callback, void* _userData, bool findFirst);
  void SetupOtherEvents(const vector<NDb::Ptr<NDb::SCEvent>> &events, bool enable);

public:
	virtual DiAnimGraph* GetAG( bool /*mainGraph*/ ) { return 0; } ///eugbel///

protected:
  static unsigned long s_numComponents;
  static unsigned long s_numComponentsCastShadow;
  static unsigned long s_numComponentsReflectInWater;
  static unsigned long s_numRendered;
  static unsigned long s_numRenderedCastShadow;
  static unsigned long s_numRenderedReflectInWater;

	Render::AABB localAABB;
	Render::AABB worldAABB;
	AnimatedPlacement	offset;
  bool              isLocatorRised;
	Placement					worldPlacement;

	CObj<SceneComponent> leftBrother;
	CObj<SceneComponent> rightBrother;
	CObj<SceneComponent> child;
	SceneComponent* parent;

  Placement          stayInWorldPlace;

	TimeController     timeController;
	int                jointIdx;
	string             locatorName;
	unsigned int       parentTransformUsage;
  unsigned int       locatorFlags;

	string  id;
	int     disabledCount;
	int     groupFlags; // flags counted in NDb::EGroupFlags
  NDb::ESCOrientation orientation;

	NDb::DBID dbid;

  vector<Locator*> locators;

private:
	NDb::Ptr<NDb::EnableDisableSCEvents> pDBEvents;
	class GroundHitEvent *pGroundHitEvents;
  bool isHide;

	friend class SceneObject;
	friend class GroundHitEvent;
};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
template<typename Traverser>
void SceneComponent::Traverse( Traverser& traverser )
{
	if ( !traverser.IsTraversable(this) )
		return;

	if ( traverser.NeedToProcess(this) )
		traverser(this);

	SceneComponent* itFront = GetChild();
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

template<typename Traverser>
void SceneComponent::Traverse( Traverser& traverser ) const
{
	if ( !traverser.IsTraversable(this) )
		return;

	if ( traverser.NeedToProcess(this) )
		traverser(this);

	SceneComponent* itFront = GetChild();
	if ( itFront )
	{
		SceneComponent* it = itFront;
		do
		{
			it->Traverse( traverser );
			it = it->GetBrother();
		} while ( it && it != itFront )
	}
}

template<typename Traverser>
void ForAllBrothers( SceneComponent *pSC, Traverser& traverser )
{
	SceneComponent* it = pSC;
  if ( it )
  {
	  do
	  {
		  if ( traverser.NeedToProcess(it) )
			  traverser(it);

		  it = it->GetBrother();
	  } while ( it && it != pSC );
  }
}

template<typename STraverser>
void SceneComponent::SyncTraverse( SceneComponent &root1, SceneComponent &root2, STraverser& traverser )
{
  NI_ASSERT(root1.dbid == root2.dbid, "Trying to synchronously traverse different hierarchies");
  traverser(root1, root2);

  SceneComponent* itFront1 = root1.GetChild();
  SceneComponent* itFront2 = root2.GetChild();
  if ( itFront1 && itFront2 )
  {
    SceneComponent* it1 = itFront1;
    SceneComponent* it2 = itFront2;
    do
    {
      SyncTraverse( *it1, *it2, traverser );
      it1 = it1->GetBrother();
      it2 = it2->GetBrother();
    } while ( it1 && it1 != itFront1 &&
              it2 && it2 != itFront2 );
  }
}

} // namespace NScene
