#include "stdafx.h"
#include "SceneObject.h"
#include "Scene.hpp"

#include "SceneObjectCreation.h"

#include "../Render/DebugRenderer.h"
#include "LightingScene.h"
#include "SceneObjectUtils.h"

#include "../System/InlineProfiler.h"

// Variables for debugging
static int g_invisibleMode = 0;
REGISTER_DEV_VAR( "scene_invis_mode", g_invisibleMode, STORAGE_NONE );

static bool showSCAABB = false;
static bool showLocators = false;

REGISTER_DEV_VAR( "show_locators", showLocators, STORAGE_NONE );
REGISTER_DEV_VAR( "show_sc_aabb", showSCAABB, STORAGE_NONE );

namespace NScene
{

const float c_maxTimeBeingInvisibleAllowed = 1.0f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectBase::AddToScene( IScene *pScene_, UpdatePriority priority /*= UPDATEPRIORITY_NORMAL*/ )
{ 
  NI_VERIFY(pScene_ != NULL, "Scene should not be NULL", return;);
  pScene = pScene_; 
	pScene->AddSceneObject(this, priority); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObjectBase::RemoveFromScene()
{ 
	if (pScene)
		pScene->RemoveObject(this); 
	pScene = 0; 
}

void SceneObjectBase::EnableRender(bool bEnable)
{
  if (IsValid(pScene))
  {
    pScene->SceneObjectRenderEnable(this, bEnable);
  }
}

const char* SceneObjectBase::FormatDescription()
{
  return "unknown";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneObject::SceneObject(IScene *pScene_, const NDb::DBSceneObject* db) 
// please, specify in order they declared (to prevent bugs) [8/26/2010 smirnov]
: SceneObjectBase( pScene_ )
, worldAABB()
, rootComponent( 0 )
, locators()
, ownerID(-1)
, componentsVersion(0)
, dwDBHash(0xffffffff)
, placement()
, whenWasRendered(0)
, freezeCount(0)
, flags(FLAGS_MOVED | FLAGS_VISIBLE)
, timeBeingInvisible(0.0f)
, pUpdateHook(0)
, pSHConsts(0)
, dbResource(db)
, animatedTrack()
, pCollisionHull(0)
, pSmallCollisionHull(0)
, hasCollisionGeometry(false)
, forbidPick(false)
, rotationLockCounter(0U)
{
  worldAABB.Init2Empty();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SceneObject::IsRendered() const
{
  CDynamicCast<Scene> pScene(this->pScene);
  return pScene ? whenWasRendered == pScene->GetUpdateCount() : false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SceneObject::IsVisible() const
{
#ifdef _DEBUG
	if (g_invisibleMode == 0)
		return (flags & FLAGS_VISIBLE) != 0;
	else
		return g_invisibleMode == 2;
#else
	return (flags & FLAGS_VISIBLE) != 0;
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::MarkRendered()
{
	// @BVS@ Static cast should be removed after some refactoring
  CDynamicCast<Scene> pScene(this->pScene);
  NI_ASSERT(pScene != NULL, NStr::StrFmt( "Attempt to render object outside from scene %s", FormatDescription() ) );
  if(pScene)
  {
	  whenWasRendered = pScene->GetUpdateCount();
	  //flags |= FLAGS_VISIBLE;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::MarkAsVisible()
{ 
  MarkRendered(); 
  // We are becoming visible now
  if (pUpdateHook)
    pUpdateHook->OnSceneObjectBecomeVisible(*this, 0.0f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::SetPlacement( const Matrix43& pos ) 
{ 
  NI_ASSERT(CVec3(pos._14, pos._24, pos._34).IsFinite(), NStr::StrFmt( "Invalid placement passed %s", FormatDescription() ) );
	worldAABB.center += CVec3(pos._14, pos._24, pos._34) - placement.pos;

  const CQuat rotation(placement.rot);

	placement.FromMatrix( pos ); 

  if (IsRotationLocked())
    placement.rot = rotation;

	flags |= FLAGS_MOVED;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::SetPlacement( const Placement& pos ) 
{ 
  NI_ASSERT(pos.IsValid(), NStr::StrFmt( "Invalid placement passed %s", FormatDescription() ) );
	worldAABB.center += pos.pos - placement.pos;

  const CQuat rotation(placement.rot);

	placement = pos;

  if (IsRotationLocked())
    placement.rot = rotation;

	flags |= FLAGS_MOVED;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::SetPosition( const CVec3& pos )
{
	worldAABB.center += pos - placement.pos;

	placement.pos = pos;

	flags |= FLAGS_MOVED;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::SetPositionAndRotation( const Placement& pos )
{
  NI_ASSERT(pos.IsValid(), NStr::StrFmt( "Invalid placement passed %s", FormatDescription() ) );
	worldAABB.center += pos.pos - placement.pos;

	placement.pos = pos.pos;

  if (!IsRotationLocked())
    placement.rot = pos.rot;

	flags |= FLAGS_MOVED;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::SetScale( const CVec3& scale )
{
  NI_ASSERT(scale.IsFinite(), NStr::StrFmt( "Invalid scale passed %s", FormatDescription() ) );
  NI_ASSERT(fabs2(scale) > EPS_VALUE, NStr::StrFmt( "Scale shouldn't be zero", FormatDescription() ) );
  placement.scale = scale;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::SetupForLighting()
{
  NI_PROFILE_FUNCTION

  // may use this for different lighting types, but only SH is implemented here now [3/5/2010 smirnov]
  // todo: think about moving dynamic lighting here

	// Create spherical harmonics
	if ( !pSHConsts )
  {
    Reset( pSHConsts, new Render::SHShaderConstants );

    if (pSHConsts && IsValid(pScene))
      pScene->CalculateSH(worldAABB.center.AsVec2D(), *pSHConsts);
  }

  if ( pSHConsts )
    flags |= FLAGS_MOVED;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::ProcessMovement()
{
  NI_PROFILE_FUNCTION

  // Move object in voxel world
	move(); 
  UpdateSH();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::SetFreeze( bool freeze /* = true */ )
{
	if (freeze)
		++freezeCount;
	else
	{
		if (freezeCount > 0)
			--freezeCount;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::SynchronizeToVisibleState()
{
  NI_PROFILE_FUNCTION

	if (!pUpdateHook)
		return;
	
	if (pUpdateHook->OnSceneObjectBecomeVisible(*this, timeBeingInvisible))
		timeBeingInvisible = 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::UpdateForced( float timeDiff, bool isUnfreeze, bool isClientVisible /* = true */ )
{
  NI_PROFILE_FUNCTION

  timeDiff += timeBeingInvisible;
	timeBeingInvisible = 0.0f;

  animatedTrack.Update( timeDiff );

	if ( rootComponent )
	{
		CVec3 oldCenter = worldAABB.center;
		
		worldAABB.Init2Empty();

	  SceneComponent::UpdatePars updatePars( worldAABB, pScene, timeDiff, isUnfreeze, isClientVisible );
		
		SceneComponent* it = rootComponent;
		do
		{
      if ( animatedTrack.IsValid() )
      {
        UpdateWithAnimatedTrack( it, updatePars, timeDiff );
      }
      else
      {
			  it->Update( updatePars, placement, timeDiff );
      }
			it = it->GetBrother();
		} while ( it && ( it != rootComponent ) );

		if (worldAABB.halfSize.x < 0.0f) // No active component present
		{
			worldAABB.center  = oldCenter;
			worldAABB.halfSize = VNULL3;
		}

    if( pCollisionHull && hasCollisionGeometry )
    {
      Matrix43 m;
      rootComponent->GetWorldPlacement().GetMatrix(&m);
      pCollisionHull->SetPosition(m, 0);
    }
    else if ( pCollisionHull )
    {
      Matrix43 m;
      GetPosition().GetMatrix(&m);
      pCollisionHull->SetPosition(m, 0);
    }
    if ( pSmallCollisionHull )
    {
      Matrix43 m;
      GetPosition().GetMatrix(&m);
      pSmallCollisionHull->SetPosition(m, 0);
    }

    NI_ASSERT(worldAABB.IsValid(), NStr::StrFmt( "Resulting AABB should be valid %s", FormatDescription() ) );
	}

	// @BVS@TODO Incorrect because AABB can change according to animation. Subject to refactor.
	if (flags & FLAGS_MOVED)
		ProcessMovement();

	flags = FLAGS_VISIBLE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::Update( float timeDiff, bool isForcedUpdate )
{
  //Вызывается более 5000 раз
  //NI_PROFILE_HEAVY_FUNCTION

  if (!pScene) 
    return;

	Scene *pScn = static_cast<Scene*>(pScene.GetPtr());

	// Update visibility
	bool bVisible = WasRendered();
#ifdef _DEBUG
	if (g_invisibleMode > 0)
		bVisible = g_invisibleMode == 2;
#endif

	if ( bVisible || isForcedUpdate )
	{ 
		// Call update hook
		if (pUpdateHook)
		{
			if ((flags & FLAGS_VISIBLE) == 0)
				SynchronizeToVisibleState();
			pUpdateHook->OnSceneObjectUpdate(*this, timeDiff);
		}

		if (freezeCount == 0)
		{
			pScn->AccountFullyUpdatedObject();
			UpdateForced(timeDiff);
		}
	}
	else
	{
		// Become invisible
		if (pUpdateHook && (flags & FLAGS_VISIBLE) != 0)
			pUpdateHook->OnSceneObjectBecomeInvisible(*this);

		if (freezeCount == 0)
		{
			// Do job for invisible SceneObject
			timeBeingInvisible += timeDiff;
			timeBeingInvisible = Min(timeBeingInvisible, c_maxTimeBeingInvisibleAllowed);
		}

		// @BVS@TODO Incorrect because AABB can change according to animation. Subject to refactor.
		if (flags & FLAGS_MOVED)
			move();

		flags = 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::DebugDraw( Render::IDebugRender* _debugRenderer )
{
  if ( showLocators )
    DebugDrawLocators( _debugRenderer );

  if ( showSCAABB )
    DebugDrawAABBs( _debugRenderer, Render::Color(0xFF, 0xFF, 0x0) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SceneObject::NeedDebugRender()
{
  return showLocators || showSCAABB;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::DebugDrawLocators( Render::IDebugRender* _debugRenderer )
{
  struct Func : public NonCopyable
  {
    Render::IDebugRender &debugRenderer;

    Func(Render::IDebugRender &debugRenderer) : debugRenderer(debugRenderer) {}

    void operator() (Locator const &l)
    {
      l.DebugRender( &debugRenderer );
    }
  };

  if ( !_debugRenderer )
    return;

  Func f(*_debugRenderer);
  ForAllLocators(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::DebugDrawAABBs( Render::IDebugRender* _debugRenderer, const Render::Color &color )
{
  if ( !_debugRenderer )
    return;

	struct RenderAABBFunc : public GenericTraverser, private NonCopyable
	{
    const Render::Color &color;
    Render::IDebugRender* debugRenderer;

		RenderAABBFunc( const Render::Color &_color, Render::IDebugRender* _debugRenderer ) : color(_color), debugRenderer(_debugRenderer) {}

		void operator()(SceneComponent *sc)
		{
  	  debugRenderer->DrawAABB( sc->GetWorldAABB(), color, true );
		}
	} f(color, _debugRenderer);

	Traverse(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::Render( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter /* = NDb::GROUPFLAGS_ALL*/ )
{
  // Trying to render object that was invisible => need to update
  if ((flags & FLAGS_VISIBLE) == 0)
  {
		SynchronizeToVisibleState();
    UpdateForced( 0.0f, true );
  }

	RenderDirectly(queue, sceneConstants, groupFlagsFilter);
	MarkRendered();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::RenderDirectly( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter /*= 0*/ )
{
	struct RenderFunc : public GenericTraverser, private NonCopyable
	{
    Render::BatchQueue& queue;
    const Render::SceneConstants& sceneConstants;
    int groupFlagsFilter;

		RenderFunc(Render::BatchQueue& queue_, const Render::SceneConstants& sceneConstants_, int groupFlagsFilter_) :
			queue(queue_), sceneConstants(sceneConstants_), groupFlagsFilter(groupFlagsFilter_) {}

		void operator()(SceneComponent *sc)
		{
      if ( !sc->IsHide() )
      {
        if ((groupFlagsFilter == GROUPFLAGS_ALL) || (sc->GetGroupFlags() & groupFlagsFilter))
        {
#ifdef SCENECOMPONENT_STATS
          SceneComponent::StatisticsRenderAdd(groupFlagsFilter);
#endif // SCENECOMPONENT_STATS
          sc->RenderToQueue(queue, sceneConstants);
        }
      }
		}
  } f(queue, sceneConstants, groupFlagsFilter);

  // Set current spherical harmonics coefficients pointer
	const Render::SHShaderConstants *pSH = pSHConsts ? Get(pSHConsts) : &sceneConstants.envLighting;
	queue.SetCurrentSHShaderConstants(pSH);

	// Set current sorting value
	queue.SetCurrentSortingValue( SceneComponent::CalculateSortingValue(worldAABB, sceneConstants) );

	Traverse(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::GetBound(SBound &bound) const
{
  bound.BoxExInit(worldAABB.center, worldAABB.halfSize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::AddToScene( IScene *pScene_, UpdatePriority priority /*= UPDATEPRIORITY_NORMAL*/ ) 
{ 
	SceneObjectBase::AddToScene( pScene_, priority );
	MarkRendered();
	// Calculate spherical harmonics coefficients
	if (pSHConsts)
		pScene->CalculateSH(worldAABB.center.AsVec2D(), *pSHConsts);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::RemoveFromScene() 
{ 
	SceneObjectBase::RemoveFromScene();
	flags &= ~FLAGS_VISIBLE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::EnableRender( bool bEnable )
{ 
  SceneObjectBase::EnableRender( bEnable );
  
  if (bEnable)
    UpdateSH();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::UpdateWorldAABB()
{
	struct GetWorldAABBFunc : public GenericTraverser, private NonCopyable
	{
		GetWorldAABBFunc() { m_aabb.Init2Empty(); }

		Render::AABB m_aabb;

		void operator()(SceneComponent *sc)
		{
			m_aabb.Grow(sc->GetWorldAABB());
		}

		void GetAABB(Render::AABB &aabb)
		{
			aabb = m_aabb;
		}
	} f;

	Traverse(f);
	f.GetAABB(worldAABB);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneObject::NotifyAttach(SceneComponent* pComponent)
{
	struct NotifyAttachTraverser : public FullTraverser
	{
		SceneObject *pObject;
		NotifyAttachTraverser(SceneObject* pObject) : pObject(pObject) {}
		void operator()(SceneComponent* p)
		{
			p->OnAfterAdded(pObject);
		}
	} onAfterAdded(this);
	pComponent->Traverse( onAfterAdded );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::Add( SceneComponent* _component )
{
	if ( rootComponent )
	{
		rootComponent->AddBrother( _component );
	}
	else
	{
		rootComponent = _component;
	}

	componentsVersion++;

	NotifyAttach(_component);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::AttachTo( SceneComponent* _component )
{
	if ( rootComponent )
	{
		rootComponent->Attach( _component );
	}
	else
	{
		rootComponent = _component;
	}

	componentsVersion++;

	NotifyAttach(_component);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Locator *SceneObject::FindLocator( const char *name ) const
{
  struct Func : public NonCopyable
  {
    const char *name;
    Locator const *found;

    Func(const char *name) : name(name), found(NULL) {}

    void operator() (Locator const &l)
    {
      if (l.locator.name == name)
      {
        found = &l;
      }
    }
  } f(name);

  ForAllLocators(f);
	return f.found;
}

bool SceneObject::IgnoreAttachesToNonDefaultLocators() const
{
  return dbResource && dbResource->ignoreAttachesToNonDefaultLocators;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::AttachToByLocator( const char* name, SceneComponent *_component, Placement* _placement )
{
	const Locator *pL = FindLocator(name);
	NI_DATA_VERIFY(pL, NStr::StrFmt("Can't find needed locator '%s' (owner id = %d, root component = '%s', dbid = '%s')", 
		name, ownerID, rootComponent->GetId().empty() ? "unknown" : rootComponent->GetId().c_str(), NDb::GetFormattedDbId( rootComponent->GetDBID() ).c_str() ), return; );

	AttachToByLocator(pL, _component, _placement);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::AttachToByLocator( const Locator *pL, SceneComponent *_component, Placement* _placement )
{
  NI_ASSERT(pL, NStr::StrFmt( "Locator should be valid %s", FormatDescription() ) );

	Placement pl;
	pl = pL->locator.offset2.GetPlace();
  if ( _placement )
  {
    pl = *_placement + pl;
  }

  //_component->SetPlacement(pl);
  _component->SetLocatorPos(pl.pos, pl.rot, pl.scale);
  _component->SetLocatorName(pL->locator.name, pL->locator.flags);

  SceneComponent* it = _component->GetBrother();
  while ( it && it != _component )
  {
    //it->SetPlacement(pl);
    it->SetLocatorPos(pl.pos, pl.rot, pl.scale);
    it->SetLocatorName(pL->locator.name, pL->locator.flags);
    it = it->GetBrother();
  }

  pL->pSC->Attach(_component);

	componentsVersion++;

	NotifyAttach(_component);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::Detach( SceneComponent* _component )
{
  _component->Detach();

  if ( _component == rootComponent )
  {
    rootComponent = NULL;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::SetOwner( SceneObject* so )
{
	if ( rootComponent )
	{
			so->AttachTo( rootComponent );
			rootComponent = 0;
	}

	componentsVersion++;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::SetOwnerID( int id )
{
	ownerID = id;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::Reinit()
{
	struct Func : public FullTraverser, NonCopyable
	{
		void operator()(SceneComponent *pSC) { pSC->Reinit(); }
	} func;

	Traverse(func);

	// Reinit internal variables
	timeBeingInvisible = 0.0f;
	flags   = FLAGS_VISIBLE | FLAGS_MOVED;
  // We are becoming visible now
  if (pUpdateHook)
    pUpdateHook->OnSceneObjectBecomeVisible(*this, 0.0f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::Deinit()
{
	struct Func : public GenericTraverser, NonCopyable
	{
		void operator()(SceneComponent *pSC) { pSC->Deinit(); }
	} func;

	Traverse(func);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::AddLocator(NDb::Locator const &l, SceneComponent *pSC)
{
  Locator &locator = pSC->RegisterLocator(l);
  locators.push_back( &locator );
}

void SceneObject::RemoveLocator( const Locator& l)
{
  for ( TLocators::iterator it = locators.begin(); it != locators.end(); it++ )
  {
    if ( (*it)->locator.name == l.locator.name )
    {
      locators.erase( it );
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::CalculateLocatorWorldMatrix(const Locator &locator, Matrix43 &m, const bool isVisible)
{
	if (timeBeingInvisible > 0.0f)
	{
		SynchronizeToVisibleState();
		UpdateForced(0.0f, false, isVisible );
	}

	locator.CalculateWorldMatrix(m);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::CalculateLocatorWorldPlacement(const Locator &locator, Placement &pl)
{
	if (timeBeingInvisible > 0.0f)
	{
		SynchronizeToVisibleState();
		UpdateForced(0.0f);
	}

	locator.CalculateWorldPlacement(pl);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::CalculateLocatorWorldPosition(const Locator &locator, CVec3 &pos, const bool isVisible/* = true*/)
{
	if (timeBeingInvisible > 0.0f)
	{
		SynchronizeToVisibleState();
		UpdateForced(0.0f, false, isVisible );
	}

	locator.CalculateWorldPosition(pos);
}

const char* SceneObject::FormatDescription()
{
	if (rootComponent)
		return NStr::StrFmt("%s", GetFormattedDbId(rootComponent->GetDBID()).c_str());
	else
		return "empty";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::ProcessExternalEvent(const char *eventName)
{
  struct EventTraverser : public FullTraverser
  {
    const char *eventName;

    EventTraverser(const char *eventName) : eventName(eventName) {}

    void operator() (SceneComponent *pSC)
    {
      pSC->ProcessExternalEvent(eventName);
    }
  } et(eventName);

  Traverse(et);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::CalculateLighting(Render::SceneConstants const &sceneConst)
{
  UpdateSH();

  struct CalcLightingTraverser : public NScene::FullTraverser, public NonCopyable
  {
    Render::SceneConstants const &sceneConst;

    CalcLightingTraverser(Render::SceneConstants const &sceneConst_) : sceneConst(sceneConst_) {}

    void operator() (NScene::SceneComponent *sc)
    {
      NScene::StaticSceneComponent *ssc = dynamic_cast<NScene::StaticSceneComponent*>(sc);
      if (ssc)
      {
        ssc->CalculateLighting(sceneConst);
      }
    }
  } f(sceneConst);

  Traverse(f);
}

void SceneObject::CalculateLightingEx(Render::SceneConstants const &sceneConst, NDb::ELightEnvironment const selector)
{
  UpdateSH();

  struct CalcLightingTraverser : public NScene::FullTraverser, public NonCopyable
  {
    Render::SceneConstants const &sceneConst;
    NDb::ELightEnvironment selector;

    CalcLightingTraverser(Render::SceneConstants const &sceneConst_, NDb::ELightEnvironment const selector_)
      : sceneConst(sceneConst_)
      , selector(selector_)
    {
    }

    void operator()(NScene::SceneComponent *sc)
    {
      NScene::StaticSceneComponent *ssc = dynamic_cast<NScene::StaticSceneComponent*>(sc);
      if (ssc)
      {
        ssc->CalculateLightingEx(sceneConst, selector);
      }
    }
  } f(sceneConst, selector);

  Traverse(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::UpdateSH()
{
  if (pSHConsts && IsValid(pScene))
    pScene->CalculateSH(worldAABB.center.AsVec2D(), *pSHConsts);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::Dump() const
{
	DebugTrace("Scene Object State:");
	if (pScene)
	{
		DebugTrace("  Update Cnt   : %d", static_cast<Scene*>(pScene.GetPtr())->GetUpdateCount());
	}
	else
	{
		DebugTrace("  Scene pointer not present");
	}
	DebugTrace("  Rendered at  : %d", whenWasRendered);
	DebugTrace("  Freeze Cnt   : %d", freezeCount);
	DebugTrace("  Flags state  : %s %s", (flags & FLAGS_VISIBLE) != 0 ? "vis" : "invis", (flags & FLAGS_MOVED) != 0 ? "moved" : "");
	DebugTrace("  Time in invis: %f", timeBeingInvisible);

	struct DumperTraverser : public NScene::FullTraverser, public NonCopyable
	{
		DumperTraverser() {}
		void operator() (NScene::SceneComponent *sc)
		{
			sc->Dump();
		}
	} f;

	Traverse(f);
}

float SceneObject::ApplyTrack( const nstl::string& track )
{
  if ( dbResource.IsEmpty() || dbResource->tracksList.IsEmpty() )
    return 0.0f;
  for ( int i = 0; i < dbResource->tracksList->animatedTracks.size(); i++ )
  {
    NDb::Ptr<NDb::SceneObjectTrack> tr = dbResource->tracksList->animatedTracks[i];
    if ( tr->name == track )
      return ApplyTrack(tr);
  }
  return 0.0f;
}

float SceneObject::ApplyTrack( const NDb::SceneObjectTrack* track )
{
  if ( !track )
    return 0.0f;

  animatedTrack.Reinit( track );

  return animatedTrack.GetLength();
}

void SceneObject::UpdateWithAnimatedTrack( SceneComponent* it, SceneComponent::UpdatePars& updatePars, float timeDiff )
{
  Placement animatedTrackPlacement = placement+animatedTrack.GetCurrentPlacement();
  Render::HDRColor mulColor( 1.f, 1.f, 1.f, animatedTrack.GetCurrentOpacity() );

  struct Coloriser : public NScene::TraverserByGroupFlags
  { 
    mutable NScene::MaterialColorAndOpacityChanger mproc;

    Coloriser( Render::HDRColor const& mulColor ) 
      : NScene::TraverserByGroupFlags( 0, true ), mproc( mulColor, Render::HDRColor(0.0f,0.0f,0.f,0.f) ) 
    {
    }

    bool NeedToProcess(const SceneComponent* comp)const
    {
      return true;
    }

    void operator()( NScene::SceneComponent* comp ) const 
    {
      comp->ForAllMaterials(mproc);
    }

  } coloriser( mulColor );
  coloriser.mproc.specialTransparency = true;

  Traverse(coloriser);

  it->Update( updatePars, animatedTrackPlacement, timeDiff );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::RegisterCollisionGeometry( const NDb::CollisionGeometry* colgeom )
{
  UnregisterCollisionGeometry();

  pCollisionHull = MakeCollisionHullForObject(*this, colgeom);
  if ( colgeom )
  {
    hasCollisionGeometry = true;
  }

  if( pCollisionHull )
  {
    if ( hasCollisionGeometry && rootComponent )
    {
      Matrix43 m;
      rootComponent->GetWorldPlacement().GetMatrix(&m);
      pCollisionHull->SetPosition(m, 0);
    }
    else
    {
      Matrix43 m;
      GetPosition().GetMatrix(&m);
      pCollisionHull->SetPosition(m, 0);
    }
  }

  if ( !hasCollisionGeometry && pCollisionHull && pCollisionHull->GetPieceId() == 1 )
  {
    pSmallCollisionHull = MakeSmallCollisionHullForObject(*this, colgeom);
    if( pSmallCollisionHull )
    {
      Matrix43 m;
      GetPosition().GetMatrix(&m);
      pSmallCollisionHull->SetPosition(m, 0);
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneObject::UnregisterCollisionGeometry()
{
  if ( IsValid( pCollisionHull ) && IsValid( GetScene() ) )
    GetScene()->GetCollisionMap()->RemoveHull( pCollisionHull );
  pCollisionHull = 0;
  if ( IsValid( pSmallCollisionHull ) && IsValid( GetScene() ) )
    GetScene()->GetCollisionMap()->RemoveHull( pSmallCollisionHull );
  pSmallCollisionHull = 0;
}

CollisionHull* SceneObject::GetCollision() const
{
  return pCollisionHull;
}

void SceneObject::SetCollision( CollisionHull* collisionHull, CollisionHull* collisionSmallHull )
{
  pCollisionHull = collisionHull;
  pSmallCollisionHull = collisionSmallHull;
}

CollisionHull* SceneObject::GetSmallCollision() const
{
  return pSmallCollisionHull;
}

void SceneObject::ResetTrack()
{
	if ( !pScene )
		return;
	animatedTrack.Reset();
	if ( rootComponent )
	{
		Render::AABB FakeAABB;
		FakeAABB.Init2Empty();
		SceneComponent::UpdatePars updatePars( FakeAABB, pScene, 0.0f, false );
		SceneComponent* it = rootComponent;
		do
		{
			UpdateWithAnimatedTrack( it, updatePars, 0.0f );
			it = it->GetBrother();
		} while ( it && ( it != rootComponent ) );
	}
}

void SceneObject::SetNodeName( const nstl::string& nodeName )
{
	struct NodeNameSetter : public FullTraverser
	{
		nstl::string nodeName;

		NodeNameSetter( const nstl::string& nodeName ) : nodeName(nodeName) {}

		void operator()(NScene::SceneComponent *pSC)
		{
			pSC->SetNodeName( nodeName );
		}
	} setter(nodeName);
	Traverse(setter);
}

bool SceneObject::WasRendered()
{
	if (!pScene) 
		return false;

	Scene *pScn = static_cast<Scene*>(pScene.GetPtr());

	return (pScn->GetUpdateCount() == whenWasRendered) && (getVoxelGrid() != NULL);
}

void SceneObject::DestoroyAllComponents()
{
	if ( rootComponent )
	{
    CObj<SceneComponent> it(rootComponent->GetBrother());
    while (it)
    {
      it->DetachFromSiblings();
      it = rootComponent->GetBrother();
    }

		rootComponent = 0;
	}
}

} //namespace NScene
