#pragma once

#include "stdafx.h"

#include "../Scene/SceneComponent.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "../Scene/SceneObjectUtils.h"
#include "../Scene/Scene.h"
#include "BasicEffect.h"
#include "../PF_GameLogic/DBPFEffect.h"
#include "../PF_GameLogic/DBAbility.h"
#include "SpectatorEffectsPool.h"


using namespace NScene;

//#define DEBUG_TRACES

#ifdef DEBUG_TRACES
extern NDebug::DebugVar<unsigned int> g_traceCount;
#endif

namespace
{
	float s_uncontrolledEffectMaxDyingTime = 15.0f;

  bool IsLocatorNameDefault( string locatorName )
  {
    for ( int loc = 0, knownLocsSize = NDb::KnownEnum<NDb::EEffectAttachType>::sizeOf; loc < knownLocsSize; loc++ )
    {
      if ( locatorName == NDb::EnumToString( (NDb::EEffectAttachType)loc ) )
        return true;
    }

    return false;
  }
}

namespace PF_Core
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffect::Init()
{ 
	Subscribe();

	bDying     = false;
  timePassed = 0.0f;
  isDead      = false;

  SetDeathType(pDBObj->deathType, pDBObj->lifeTime);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffect::SetDeathType(NDb::EEffectDeathType deathType_, float lifeTime_)
{
  NI_ASSERT( !(deathType_ == NDb::EFFECTDEATHTYPE_TIME && lifeTime_ <= 0.0f), NStr::StrFmt("You should specify life time for this death type. (%s)", NDb::GetFormattedDbId(pDBObj->GetDBID()).c_str()) )
  deathType = deathType_;
  lifeTime = lifeTime_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffect::Update(float timeDelta) 
{
	timePassed += timeDelta;

	// Special debug code
	if ( ( ( nObjCount + nRefCount ) == 1 ) && ( deathType == NDb::EFFECTDEATHTYPE_MANUAL ) && ( pDBObj->GetObjectTypeID() != NDb::EffectSwitcher::typeId ) )
	{
		if (!bDying)
		{
      //TODO: Fix effects and uncomment this assert
			//NI_DATA_ALWAYS_ASSERT(NStr::StrFmt("Effect (%s) is has manual deathType, while used as uncontrolled. Ask data manager to change!", 
			//																	 NDb::GetFormattedDbId(pDBObj->GetDBID()).c_str()));
			Die();
			return;
		}
		else
		{
			if (timePassed > s_uncontrolledEffectMaxDyingTime) // Effect is dying more then 15 sec - too suspicious
			{
        if ( Ready2Die() )
        {
          DebugTrace("DEATH ASSERT DIAG. Ready to die.");
        }
        else
        {
          DebugTrace("DEATH ASSERT DIAG. Not ready to die.");
        }
        // NUM_TASK
        // Такие случаи были раньше не редки, из-за ошибок как в коде, так и в сборке эффектов/апликаторов.
        // Но похоже, все такие проблемы были решены.
        // Так же эта функция сильно спамит, если вызывается. Будет нужна - раскомментим.
				//OnUncontrolledDyingEvent();
				NI_DATA_ALWAYS_ASSERT(NStr::StrFmt("Effect (%s) has manual deathType and is dying uncontrolled for too long (%f sec). Ask data manager to check %p", 
															    					NDb::GetFormattedDbId(pDBObj->GetDBID()).c_str(), s_uncontrolledEffectMaxDyingTime, (void*)this) );
				DieImmediate();
				return;
			}
		}
	}
	
	if (!bDying)
	{
		// Update as alive
		if ((deathType == NDb::EFFECTDEATHTYPE_TIME || deathType == NDb::EFFECTDEATHTYPE_ANIM) &&
        timePassed > lifeTime)
			Die();
	}
	else
	{
		if (Ready2Die())
			DieImmediate();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffect::Die() 
{
  // prevent double death
  if (bDying)
    return;

  bDying = true;
  DieImmediate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffect::DieImmediate()
{ 
  if ( isDead )
    return;

  timePassed = 0.0f;

  SetEnableCallback(0);

	Release2Pool();
  isDead = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffect::ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add) 
{
  MaterialColorChanger f(mul, add);
  ForAllMaterials(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffect::SetOpacity(float opacity)
{
  struct Func : public Render::IMaterialProcessor, public NonCopyable
  {
    float opacity;

    Func(float o) : opacity(o) {}
    virtual void operator()(Render::BaseMaterial &material)
    {
      material.ModifyOpacity(opacity);
    }
  } f(opacity);

  ForAllMaterials(f);
}

void BasicEffect::SetInterrupted( bool interrupted )
{
  isInterrupted = interrupted;
}

bool BasicEffect::IsInterrupted()
{
  return isInterrupted;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponentsEffect::Init()
{
	BasicEffect::Init();

  // init opacity
  if (GetDBEffect().fadeIn > 0.f)
  {
    SetOpacity(0.f);
  }
  else
  {
    SetOpacity(1.f);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponentsEffect::SetDeathType(NDb::EEffectDeathType deathType_, float lifeTime_)
{
  if (deathType_ == NDb::EFFECTDEATHTYPE_ANIM)
  {
    struct Proc : ISceneComponentProcessor
    {
      float animTime;

      Proc() : animTime(0.0f) {}
      virtual void operator()(SceneComponent *pSC)
      {
        animTime = Max(animTime, pSC->GetSubTreeAnimLength());
				NI_ASSERT( animTime<1000.0f, NStr::StrFmt( "Bad animation length %s", pSC->GetDBID().GetFileName() ) );
      }
    } f;
    ForAllRootSceneComponents(f);

    lifeTime_ = timePassed + f.animTime;
  }

  BasicEffect::SetDeathType(deathType_, lifeTime_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponentsEffect::Update(float timeDelta)
{
  BasicEffect::Update(timeDelta);

  NDb::BasicEffect const &db = GetDBEffect();

  float opacity = 1.f;

  if (db.fadeIn > 0.f)
  {
    opacity = timePassed / db.fadeIn;
  }

  if (db.fadeOut > 0.f)
  {
    if (bDying)
    {
      opacity = 1.f - timePassed / db.fadeOut;
    }
    else if ((deathType == NDb::EFFECTDEATHTYPE_ANIM) &&
             timePassed > lifeTime - db.fadeOut)
    {
      opacity = (lifeTime - timePassed) / db.fadeOut;
    }
  }

  if (db.fadeIn > 0.f ||
      db.fadeOut > 0.f)
  {
    SetOpacity(Clamp(opacity, 0.f, 1.f));
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SceneComponentsEffect::Ready2Die()
{
  struct Trav : public ISceneComponentProcessor
	{
		bool atLeastOneComponentRemains;

		Trav() : atLeastOneComponentRemains(false) {}

    virtual bool IsTraversable(const SceneComponent* pSC) const
    {
      return !pSC->IsStronglyDisabled();
    }

		virtual void operator()(SceneComponent *pSC) 
		{ 
			if (!pSC->IsStronglyDisabled())
				atLeastOneComponentRemains = true;
		}
	} f;
	ForAllRootSceneComponents(f);

  bool isReady = false;

  if (GetDBEffect().fadeOut > 0.f)
  {
		isReady = !(f.atLeastOneComponentRemains && (deathType == NDb::EFFECTDEATHTYPE_MANUAL || deathType == NDb::EFFECTDEATHTYPE_TIME)&& timePassed < GetDBEffect().fadeOut);
  }
  else
  {
    isReady = !f.atLeastOneComponentRemains;
  }

  return isReady;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponentsEffect::OnUncontrolledDyingEvent()
{
  struct Trav : public ISceneComponentProcessor
  {
    Trav() {}

    virtual void operator()(SceneComponent *pSC) 
    { 
      if (!pSC->IsStronglyDisabled())
        DebugTrace(" DEBUG READY TO DIE (not ready): %s", pSC->FormatDescription() );
    }
  } f;

  ForAllRootSceneComponents(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponentsEffect::Die() 
{
  if (bDying)
    return;

  bDying = true;
  timePassed = 0.0f;

  struct Trav : public ISceneComponentProcessor
	{
		virtual void operator()(SceneComponent *pSC) 
		{ 
      struct Disabler : public ISceneComponentProcessor
	    {
		    virtual void operator()(SceneComponent *pSC) 
		    { 
			    pSC->DisableStrongWithWaitingForFinish();
		    }
	    } d;

      pSC->Traverse( d );
			pSC->DisableStrongWithWaitingForFinish();
		}
	} f;

  if ( deathType == NDb::EFFECTDEATHTYPE_ANIM ||
      GetDBEffect().fadeOut == 0.f)
  {
	  // disable all components
    ForAllSceneComponents(f);
  }

	if (Ready2Die())
		DieImmediate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponentsEffect::ForAllMaterials(Render::IMaterialProcessor &proc)
{
  struct Trav : public ISceneComponentProcessor, public NonCopyable
  {
    struct InnerTrav : public FullTraverser, public NonCopyable
    {
      Render::IMaterialProcessor &proc;

      InnerTrav(Render::IMaterialProcessor &proc) : proc(proc) {}
      virtual void operator()(NScene::SceneComponent *pSC)
      {
        pSC->ForAllMaterials(proc);
      }
    } trav;

    Trav(Render::IMaterialProcessor &proc) : trav(proc) {}

    virtual void operator()(NScene::SceneComponent *pSC) 
    { 
      pSC->Traverse(trav); 
    }
  } f(proc);
  
  ForAllRootSceneComponents(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponentsEffect::ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)
{
  struct Trav : public ISceneComponentProcessor, public NonCopyable
  {
    const Render::HDRColor &mul;
    const Render::HDRColor &add;

    Trav(const Render::HDRColor &mul_, const Render::HDRColor &add_) : mul(mul_), add(add_) {}

    virtual void operator()(NScene::SceneComponent *pSC) 
    { 
      struct InnerTrav : public MaterialColorChanger, public FullTraverser
      {
        InnerTrav(const Render::HDRColor &mul_, const Render::HDRColor &add_) : MaterialColorChanger(mul_, add_) {}
        virtual void operator()(NScene::SceneComponent *pSC)
        {
          pSC->ForAllMaterials(*this);
        }
      };

      InnerTrav changer(mul, add);
      pSC->Traverse(changer); 
    }
  } f(mul, add);

  ForAllRootSceneComponents(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NScene::AnimatedSceneComponent *SceneComponentsEffect::GetAnimRoot() const
{
  struct FindFirstById : TraverserById
  {
    SceneComponent *pFound;

    FindFirstById(const char* id) : TraverserById(id), pFound(NULL) {}

    void operator() (SceneComponent *pSC)
    {
      if (!pFound)
      {
        pFound = pSC;
      }
    }
  };

  NScene::AnimatedSceneComponent *pAnimRoot = NULL;
  if (GetRootComponent())
  {
    FindFirstById f("animRoot");
    GetRootComponent()->Traverse(f);
    pAnimRoot = dynamic_cast<NScene::AnimatedSceneComponent *>(f.pFound);
  }

  NI_DATA_ASSERT(pAnimRoot, NStr::StrFmt("Effect \"%s\" should include animated scene component with id = \"animRoot\"",
                                         NDb::GetFormattedDbId( GetDBEffect().GetDBID() ).c_str()));

  return pAnimRoot;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BasicEffectStandalone::BasicEffectStandalone(const NDb::EffectBase &dbEffect)
	: EffectBase(dbEffect), pObject(new SceneObject()), opacity(1.f), isSwitched(false)
{
	// Add scene components to scene object
	if (GetDBEffect().component)
		AppendComponentsToSceneObject(*pObject, *GetDBEffect().component);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::Init()
{
	SceneComponentsEffect::Init();
	pObject->Reinit();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::AddToScene(IScene *pScene)
{
	pObject->UpdateForced();
	pObject->AddToScene(pScene);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::Update(float timeDelta)
{
  bool bEffectivelyVisible = !GetDBEffect().visibilityLimited ||
                             (timePassed < GetDBEffect().visibleTime);
  
  SceneComponentsEffect::Update(timeDelta);
  
  if ( bEffectivelyVisible &&
       GetDBEffect().visibilityLimited &&
       timePassed > GetDBEffect().visibleTime )
  {
    if (GetSceneObject())
    {
      GetSceneObject()->SetOwnerID(GetSceneObject()->GetOwnerID() & 0x7FFFFFFF);
    }
  }
}

void BasicEffectStandalone::SwitchEffect( const NDb::Ptr<NDb::EffectBase>& newEffect )
{
  NScene::IScene* scene = pObject->GetScene();

  if ( scene )
  {
    float elapsedTime = timePassed;
    Placement pl = pObject->GetPosition();
  
    struct Trav : public ISceneComponentProcessor
	  {
		  virtual void operator()(SceneComponent *pSC) 
		  { 
			  pSC->SetHide(false);
		  }
	  } f;

	  ForAllSceneComponents(f);

	  pObject->Deinit();
	  pObject->RemoveFromScene();

    isSwitched = !isSwitched;

    if ( isSwitched )
      originalDB = pDBObj;

    pDBObj = newEffect;
   
    Reset( pObject, new SceneObject );

    if (GetDBEffect().component)
		  AppendComponentsToSceneObject(*pObject, *GetDBEffect().component);

	  bDying     = false;
    timePassed = 0.0f;
    isDead      = false;
    SetDeathType(pDBObj->deathType, pDBObj->lifeTime);
    if (GetDBEffect().fadeIn > 0.f)
    {
      SetOpacity(0.f);
    }
    else
    {
      SetOpacity(1.f);
    }
    pObject->Reinit();

    pObject->SetPlacement( pl );
    AddToScene( scene );

    while ( elapsedTime > 0.0f )
    {
      Update( 0.01f );
      pObject->UpdateForced( 0.01f );
      elapsedTime -= 0.01f;
    };
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BasicEffectStandalone::Ready2Die()
{
  if ( !pObject )
    return true;

	if ( !pObject->IsVisible() || pObject->IsFrozen() || !pObject->GetScene() )
		return true;

	return SceneComponentsEffect::Ready2Die();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::DieImmediate()
{
  if ( SpectatorEffectsPool::Get() && SpectatorEffectsPool::Get()->IsSpectator() )
    SpectatorEffectsPool::Get()->UnregisterBasicEffectStandalone( this );

  struct Trav : public ISceneComponentProcessor
	{
		virtual void operator()(SceneComponent *pSC) 
		{ 
			pSC->SetHide(false);
		}
	} f;

	ForAllSceneComponents(f);

	pObject->Deinit();
	pObject->RemoveFromScene();
	BasicEffect::DieImmediate();

  if ( isSwitched )
  {
    pDBObj = originalDB;

    Reset( pObject, new SceneObject );

    if (GetDBEffect().component)
		  AppendComponentsToSceneObject(*pObject, *GetDBEffect().component);
  }

#ifdef DEBUG_TRACES
  // check if it was trace effect
  if (GetSceneObject() &&
      (GetSceneObject()->GetOwnerID() & 0x7FFFFFFF) == 1)
  {
    g_traceCount.DecValue(1);
  }
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::ForAllRootSceneComponents(ISceneComponentProcessor &proc)
{
  pObject->ForAllRoots(proc);
}

void BasicEffectStandalone::ForAllSceneComponents(ISceneComponentProcessor &proc)
{
  pObject->Traverse(proc);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::SetPosition(const Placement &placement)
{
  pObject->SetPlacement(placement);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::SetRotation(const CQuat &rot)
{
	Placement place = pObject->GetPosition();
  place.rot = rot;
  pObject->SetPlacement(place);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::Apply(CPtr<ClientObjectBase> const &pUnit)
{
	SceneObject *pSO = pUnit->GetSceneObject();
	if ( pSO && pSO->GetScene())
	{
    Apply( pSO );
	}
}

void BasicEffectStandalone::Apply(const NScene::SceneObject *pSO)
{
  if ( !pSO || !IsEffectEnabled(*this) )
    return;

  const char *locatorName = GetDBEffect().parentType.c_str();
  const NScene::Locator *pL = pSO->FindLocator( locatorName );
  Placement pos;
  if (pL)
  {
    pL->CalculateWorldPlacement(pos);
  }
  else
  {
    pos = pSO->GetPosition();
  }

  if ( !(GetDBEffect().parentFlags & NDb::STANDALONEEFFECTFLAGS_USEPARENTROTATION) )
  {
    pos.rot = QNULL;
  }
  if ( !(GetDBEffect().parentFlags & NDb::STANDALONEEFFECTFLAGS_USEPARENTSCALE) )
  {
    pos.scale = CVec3( 1.0f, 1.0f, 1.0f );
  }

  SetPosition( pos );
  AddToScene( pSO->GetScene() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectStandalone::OnUncontrolledDyingEvent()
{
	SceneComponentsEffect::OnUncontrolledDyingEvent();
	pObject->Dump();
}

static void HideComponents( SceneComponent* sc )
{
	if ( !sc->IsTraversable() )
		return;

	if ( !sc->Ready2Die() )
		return;

	if ( sc->IsStayInWorld() && !sc->IsHide() )
	{
		return;
	}
	else
	{
		sc->SetHide( true );
	}

	SceneComponent* itFront = sc->GetChild();
	if ( itFront )
	{
		SceneComponent* it = itFront;
		do
		{
			HideComponents(it);
			it = it->GetBrother();
		} while ( it && it != itFront );
	}
}

void BasicEffectStandalone::Die()
{
	if (bDying)
		return;

	bDying = true;
	timePassed = 0.0f;

	struct Trav : public ISceneComponentProcessor
	{
		virtual void operator()(SceneComponent *pSC) 
		{ 
			pSC->DisableStrongWithWaitingForFinish();
		}
	} f;

	if ( deathType == NDb::EFFECTDEATHTYPE_ANIM ||
		GetDBEffect().fadeOut == 0.f)
	{
    // See NUM_TASK
		//if ( GetRootComponent() )
		//{
		//	SceneComponent* itFront = GetRootComponent();
		//	if ( itFront )
		//	{
		//		SceneComponent* it = itFront;
		//		do
		//		{
		//			HideComponents(it);
		//			it = it->GetBrother();
		//		} while ( it && it != itFront );
		//	}
		//}

		// disable all components
		ForAllSceneComponents(f);
	}

	if (Ready2Die())
		DieImmediate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BasicEffectAttached::BasicEffectAttached(const NDb::EffectBase &dbEffect)
	: EffectBase(dbEffect), 
  bAuxRoot(false),
  pSceneObject(0) // PLEASE DO NOT FORGET INITIALIZE POINTERS
{
  CreateRootComponent();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::Init()
{
	SceneComponentsEffect::Init();
  if ( root )
  {
    root->ReinitSubTree();

    // Mark attached effect as 'effect'
    struct EffectFlagSetter : public FullTraverser
    {
      int additionalGroupFlags;

      EffectFlagSetter(const int additionalGroupFlags = 0)
        : additionalGroupFlags(additionalGroupFlags)
      {
      }

      void operator()(NScene::SceneComponent *pSC) const
      {
        pSC->SetHide( false );
        pSC->SetGroupFlags( additionalGroupFlags | NScene::SceneComponent::GROUPFLAGS_EFFECT | pSC->GetGroupFlags() );
      }
    } setter(GetDBEffect().groupFlags);

    root->Traverse(setter);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::Apply(CPtr<ClientObjectBase> const &pUnit)
{
  if ( !IsValid( pUnit ))
    return;

  if(!IsEffectEnabled(*this))
  {
    DevTrace("Effect %s was disabled by condition", this->GetDBDesc()->GetDBID().GetFileName());
    return;
  }

	Attach(pUnit->GetSceneObject());
	pUnit->OnEffectAttach(this);
}

void BasicEffectAttached::Die() 
{
  SceneComponentsEffect::Die();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::Attach(NScene::SceneObject *pObj)
{
  // building can have empty sceneobject (ruins), so a check should be
  if ( !root || !pObj )
  {
    return;
  }

	// Save scene object
	pSceneObject = pObj;

	NI_ASSERT(pDBObj, "Effect should have DB prototype");

  for ( int i = 0; i < locators.size(); i++ )
  {
    NDb::Locator& loc = locators[i].locator;
    
    if ( const NScene::Locator* locat = pSceneObject->FindLocator( loc.name.c_str() ) )
      pSceneObject->RemoveLocator( *locat );

    pSceneObject->AddLocator( locators[i].locator, locators[i].pSC );
  }

  root->SetParentTransformUsageFlags(GetDBEffect().attachFlags);

	struct WorldSpaceMatrixSetter : public FullTraverser
	{
		void operator()(NScene::SceneComponent* sc)
		{
			sc->SetWorldMatrixForWorldSpace();
		}
	} setter;
	root->Traverse(setter);

  if (GetDBEffect().attachType ==  NDb::EnumToString( NDb::EFFECTATTACHTYPE_GENERAL ) )
  {
    pObj->AttachTo( root );
    return;
  }

  const char *locatorName = GetDBEffect().attachType.c_str();
  const NScene::Locator *pL = pObj->FindLocator( locatorName );
  if (!pL)
  {
    // SceneObject ignores effect with non-default locator attaches
    if ( pObj->IgnoreAttachesToNonDefaultLocators() && !IsLocatorNameDefault( locatorName ) )
      return;

    // Message
    if ( pObj->GetRootComponent() )
    {
      const char *rootCompName = pObj->GetRootComponent()->GetId().empty() ? "unknown" : pObj->GetRootComponent()->GetId().c_str();
      NI_ALWAYS_ASSERT( NStr::StrFmt( "Locator: %s isn't found in SObj with root component %s Efft: %s SObj: %s", 
        locatorName, rootCompName, NDb::GetFormattedDbId( pDBObj->GetDBID() ).c_str(), NDb::GetFormattedDbId( pObj->GetRootComponent()->GetDBID() ).c_str() ) );
    }
    pL = pObj->FindLocator(NDb::EnumToString(NDb::EFFECTATTACHTYPE_ABOVE));
    if (!pL)
    {
      pObj->AttachTo( root );
      return;
    }
  }

  pObj->AttachToByLocator(pL, root );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::ForAllRootSceneComponents(ISceneComponentProcessor &proc)
{
  struct Func : public FullTraverser, NonCopyable
  {
    ISceneComponentProcessor &proc;

    Func(ISceneComponentProcessor &proc) : proc(proc) {}
    void operator()(SceneComponent *pSC)
    {
      proc(pSC);
      pSC->Traverse(proc);
    }
  } func(proc);
  
  if ( root )
  {
    if (bAuxRoot)
    {
      NI_ASSERT(root->GetChild(), "Should have children");
      ForAllBrothers(root->GetChild(), func);
    }
    else
    {
      func( root );
    }
  }
}

void BasicEffectAttached::ForAllSceneComponents(ISceneComponentProcessor &proc)
{
  ForAllRootSceneComponents(proc);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BasicEffectAttached::Ready2Die()
{
  if ( !pSceneObject )
    return true;

  if ( !pSceneObject->IsVisible() || pSceneObject->IsFrozen() || !pSceneObject->GetScene() || !root || !root->IsTraversable() )
		return true;

	return SceneComponentsEffect::Ready2Die();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::DieImmediate()
{
  if ( pSceneObject )
  {
    for ( int i = 0; i < locators.size(); i++ )
    {
      NDb::Locator& loc = locators[i].locator;
      
      if ( const NScene::Locator* locat = pSceneObject->FindLocator( loc.name.c_str() ) )
      {
        pSceneObject->RemoveLocator( *locat );
      }
    }
  }

  if ( root )
  {
    root->DeinitSubTree();
	  root->Detach();
  }

	pSceneObject = 0;

  SceneComponentsEffect::DieImmediate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::SetPosition(const Placement &placement)
{
  if ( root )
  {
    root->AddBase(placement.pos, placement.rot, placement.scale);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::SetRotation(const CQuat &rot)
{
  if ( root )
  {
    root->AddLocator( VNULL3, rot, CVec3(1.f, 1.f, 1.f) );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::AddLocator( const Placement& placement )
{
  if ( root )
  {
    root->AddLocator( placement.pos, placement.rot, placement.scale );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::SetHeightAboveLocator( float height )
{
  if ( root && !root->IsLocatorRised() )
  {
    Placement placement;
    placement.pos.z = height;
    root->AddLocator( placement.pos, placement.rot, placement.scale );
    root->SetLocatorRised( true );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::SetScale(float scale)
{
  if ( root )
  {
    Placement pl;
    pl.scale = CVec3(scale, scale, scale);
		root->SetPlacement(pl);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::OnUncontrolledDyingEvent()
{
	SceneComponentsEffect::OnUncontrolledDyingEvent();
	if (pSceneObject)
		pSceneObject->Dump();
	else
	{
		DebugTrace("  SceneObject is not present in BasicEffectAttached");
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicEffectAttached::SwapHierarchy(BasicEffectStandalone &standalone)
{
  struct SwapLocators
  {
    void operator() (SceneComponent &sc1, SceneComponent &sc2)
    {
      sc1.SwapLocators(sc2);
    }
  } f;

  NI_ASSERT(pSceneObject, "Attached effect should be in attached state");

  NI_DATA_ASSERT(standalone.GetRootComponent()->GetDBID() == root->GetDBID(),
                 NStr::StrFmt("These effects should reference the same component:\n%s\n%s",
                 NDb::GetFormattedDbId( GetDBEffect().GetDBID() ).c_str(),
                 NDb::GetFormattedDbId( standalone.GetDBEffect().GetDBID() ).c_str()));

  CObj<SceneComponent> saRoot(standalone.GetRootComponent());
  CObj<SceneComponent> atRoot(GetRootComponent());
  CObj<SceneComponent> atParent(atRoot->GetParent());
  standalone.GetSceneObject()->Detach( saRoot );
  
  // detach attached effect from the object
  atRoot->Detach();
  atRoot->SetLocatorPos(VNULL3, QNULL, CVec3(1.f, 1.f, 1.f));
  SceneObject *pSO = pSceneObject;
  pSceneObject = NULL;
  
  standalone.GetSceneObject()->AttachTo( atRoot );

  root = saRoot;

  // reattach attached effect
  Attach(pSO);

  // restore broken SceneObject -> Locator references
  SceneComponent::SyncTraverse( *atRoot, *saRoot, f);
}

void BasicEffectAttached::CreateRootComponent()
{
  LocatorInfoFunc lf( locators );
  vector<CObj<NScene::SceneComponent>> components = NScene::ParseSceneComponent( GetDBEffect().component.GetPtr(), lf );

  if (components.size() == 0)
    return;

  if (components.size() == 1)
  {
    root = components[0];

    if (root->GetBrother())
    {
      CObj<NScene::SceneComponent> newRoot = new NScene::SceneComponent();
      bAuxRoot = true;

      // attach all siblings
      NScene::SceneComponent *sc = root;
      do 
      {
        newRoot->Attach(sc);
        sc = sc->GetBrother();
      } while ( sc && ( sc != root ) );

      root = newRoot;
    }
  }
  else
  {
    root = new NScene::SceneComponent();
    bAuxRoot = true;

    // attach all siblings
    for (int i = 0; i < components.size(); ++i)
    {
      root->Attach( components[i] );
    }
  }
}

void BasicEffectAttached::Hide( bool hide )
{
  struct Hider : public ISceneComponentProcessor
  {
    bool hide;
    Hider( bool _hide ) : hide(_hide) {}
    void operator()(NScene::SceneComponent *pSC)
    {
      pSC->SetHide( hide );
    }
  } hider( hide );
  ForAllSceneComponents( hider );
}

} //namespace PF_Core

BASIC_REGISTER_CLASS( PF_Core::BasicEffect );
BASIC_REGISTER_CLASS( PF_Core::BasicEffectAttached );
BASIC_REGISTER_CLASS( PF_Core::BasicEffectStandalone );

REGISTER_DEV_VAR( "effect_max_dying_time", s_uncontrolledEffectMaxDyingTime, STORAGE_NONE );
