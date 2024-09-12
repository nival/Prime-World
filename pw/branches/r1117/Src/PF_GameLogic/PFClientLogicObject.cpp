#pragma once

#include "stdafx.h"

#include "PFClientLogicObject.h"

#include "PFClientSceneObjectsHolders.h"

#include "../Scene/AnimatedSplitSceneComponent.h"
#include "../Scene/ParticleSceneComponent.h"
#include "../Scene/SceneObjectCreation.h"
#include "../PF_Core/EffectsPool.h"
#include "../System/InlineProfiler.h"

#include "ClientVisibilityHelper.h"

using namespace NScene;

namespace 
{
    //CBM_Normal,       // newColor = current * (1 - opacity) + previous * opacity
    //CBM_Multiply,     // newColor = current * previous
    //CBM_FullPrevious, // newColor = current * (1 - opacity) + previous
    
  void BlendNormal(Render::HDRColor* pMulAccum, Render::HDRColor* pAddAccum, Render::HDRColor const& mulCurrent, Render::HDRColor const& addCurrent, const float opacity)
  {
    if( pMulAccum )
      pMulAccum->Lerp(*pMulAccum, mulCurrent, (1.0f - opacity));
    if( pAddAccum )
      pAddAccum->Lerp(*pAddAccum, addCurrent, (1.0f - opacity));
  }

  void BlendMultiply(Render::HDRColor* pMulAccum, Render::HDRColor* pAddAccum, Render::HDRColor const& mulCurrent, Render::HDRColor const& addCurrent, const float /*opacity*/)
  {
    if( pMulAccum )
      pMulAccum->Mul(*pMulAccum, mulCurrent);
    if( pAddAccum )
      pAddAccum->Mad(*pAddAccum, mulCurrent, addCurrent);
  }

  void BlendFullPrevious(Render::HDRColor* pMulAccum, Render::HDRColor* pAddAccum, Render::HDRColor const& mulCurrent, Render::HDRColor const& addCurrent, const float opacity)
  {
    if( pMulAccum )
      pMulAccum->Add(*pMulAccum, mulCurrent * (1.0f - opacity));
    if( pAddAccum )
      pAddAccum->Add(*pAddAccum, addCurrent * (1.0f - opacity));
  }
  
  void BlendColors(PF_Core::ColorBlendMode mode, Render::HDRColor* pMulAccum, Render::HDRColor* pAddAccum, Render::HDRColor const& mulCurrent, Render::HDRColor const& addCurrent, const float opacity)
  {
    switch(mode)
    {
    case PF_Core::CBM_Normal:
      BlendNormal(pMulAccum, pAddAccum, mulCurrent, addCurrent, opacity);
      return;
    case PF_Core::CBM_Multiply:
      BlendMultiply(pMulAccum, pAddAccum, mulCurrent, addCurrent, opacity);
      return;
    case PF_Core::CBM_FullPrevious:
      BlendFullPrevious(pMulAccum, pAddAccum, mulCurrent, addCurrent, opacity);
      return;
    }

    NI_ALWAYS_ASSERT("Unsupported color blend mode!");
  }
};

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientLogicObject::CreatePars::CreatePars(NScene::IScene* pScene, const nstl::string& nodeName, NDb::Ptr<NDb::GameObject> const& gameObject)
: pScene(pScene)
, placement(NULL)
, nodeName(nodeName)
{
  if ( gameObject )
  {
    NDb::SingleStateObject const* sso = dynamic_cast<NDb::SingleStateObject const*>(gameObject.GetPtr());
    if ( sso )
    {
      sceneObject = sso->sceneObject;
      pCollision = sceneObject->collisionGeometry;
    }
    else
    {
      //NI_ALWAYS_ASSERT("GameObject have no scene objects to attach!");
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientLogicObject::CreatePars::CreatePars(NScene::IScene *pScene, const nstl::string& nodeName, NDb::AdvMapObject const& advMapObject)
: pScene(pScene)
, placement(NULL)
, nodeName(nodeName)
{
  if ( advMapObject.gameObject )
  {
    placement = &advMapObject.offset;
    
    NDb::SingleStateObject const* sso = dynamic_cast<NDb::SingleStateObject const*>(advMapObject.gameObject.GetPtr());
    if ( sso )
    {
      sceneObject = sso->sceneObject;
      pCollision = sceneObject->collisionGeometry;
    }
    else
    {
      //NI_ALWAYS_ASSERT("GameObject have no scene objects to attach!");
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AutoPtr<NScene::SceneObject> PFClientLogicObject::MakeSceneObject(const NDb::DBSceneObject& dbSceneObject, const Placement& pl, const nstl::string& nodeName )
{
  AutoPtr<NScene::SceneObject> pResult = NScene::CreateSceneObject(pScene, dbSceneObject, nodeName);
  pResult->SetPlacement( pl );
  pResult->UpdateForced();
  pResult->SetOwnerID( WorldObject()->GetObjectId() );

  return pResult;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientLogicObject::PFClientLogicObject(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp)
  : NWorld::PFClientObjectBase(pWO)
  , bVisible(true)
  , scalePermanent(CVec3(1.0f, 1.0f, 1.0f))
  , scaleTemporary(1.0f)
  , unitSize(1.0f)
  , pScene(cp.pScene)
  , colorChanged(false)
{
  NI_PROFILE_FUNCTION

  if (cp.placement)
  {
    scalePermanent = cp.placement->GetPlace().scale;
  }

  Subscribe();
}

PFClientLogicObject::PFClientLogicObject()
{
}

PFClientLogicObject::~PFClientLogicObject()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::SetRotation(CQuat const &quat)
{
  if( GetSceneObject() )
  {
    Placement pl = GetSceneObject()->GetPosition();
    pl.rot = quat;
    GetSceneObject()->SetPlacement(pl);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::Update( const float timeDiff )
{
  NI_PROFILE_FUNCTION

  if (pSceneObjectsHolder)
    pSceneObjectsHolder->Update(timeDiff);

  if( GetSceneObject() )
  {
    // Set scale of an object
    GetSceneObject()->SetScale(scaleTemporary * scalePermanent);

    if(colorChanged)
    {
      ProcessColorModifications();
      colorChanged = false;
    }
  }

  Recrypt(bVisible);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::SetPlacement(const Placement& placement)
{
  if( GetSceneObject() )
  {
    // Pass position to object
    GetSceneObject()->SetPositionAndRotation( placement );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::UpdatePlacement(Placement& placement)
{
  NScene::PlaceOnTerrain( pScene->GetHeightsController(), placement.pos, 1 );
  SetPlacement(placement);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::UpdateVisibility()
{
  const bool visible = ClientVisibilityHelper::IsVisibleForPlayer(WorldObject());

  SetVisibility(visible);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::SetVisibilityAsBuilding(bool bVisible_)
{
  const NWorld::PFLogicObject* pWorldLogicObject = WorldObject();
  NI_ASSERT ( pWorldLogicObject, " World object is null " );
  bVisible_ &= !pWorldLogicObject->GetHiddenCounter();

  if (!DoSetVisible(bVisible_))
    return;

  if ( GetSceneObject() && GetSceneObject()->GetCollision() )
    GetSceneObject()->GetCollision()->SetEnabled(bVisible);
  if ( GetSceneObject() && GetSceneObject()->GetSmallCollision() )
    GetSceneObject()->GetSmallCollision()->SetEnabled(bVisible);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::SetVisibilityAsObject(bool bVisible_)
{
  const NWorld::PFLogicObject* pWorldLogicObject = WorldObject();
  NI_ASSERT ( pWorldLogicObject, " World object is null " );
  bVisible_ &= !pWorldLogicObject->GetHiddenCounter();
  //bVisible_ &= !hiddenCounter;

  if (!DoSetVisible(bVisible_))
    return;

  pSceneObjectsHolder->SetVisibility( bVisible_ );
  
  if ( GetSceneObject() && GetSceneObject()->GetCollision() )
    GetSceneObject()->GetCollision()->SetEnabled(bVisible_);
  if ( GetSceneObject() && GetSceneObject()->GetSmallCollision() )
    GetSceneObject()->GetSmallCollision()->SetEnabled(bVisible_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::OnWorldObjectDie()
{
  ClearColorModifications();
  if( GetSceneObject() )
  {
    GetSceneObject()->UnregisterCollisionGeometry();
  }

  //TryCreateStandaloneEffect();

  pSceneObjectsHolder->Reset();
  pScene = 0;
  PFClientObjectBase::OnWorldObjectDie();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::MakeTargetingPos(CVec3 &pos)
{
  NScene::SceneObject* pSO = GetSceneObject();
  pos = NULLPLACEMENT.pos;
  if ( pSO )
  {
    pos = pSO->GetCollision() ? pSO->GetCollision()->GetBoundsCenter() : pSO->GetWorldAABB().center;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NScene::SceneObject* PFClientLogicObject::GetSceneObject()const
{
  NI_VERIFY(pSceneObjectsHolder != NULL, "pSceneObjectsHolder must be valid!", return NULL;);
  const NScene::SceneObjectRef& obj = pSceneObjectsHolder->GetActive();
  return obj ? Get(obj) : NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::EnableById( string id, bool bEnable )
{
  struct EnablerById : public NScene::TraverserById
  {
    EnablerById( string id, bool bEnable ) : NScene::TraverserById( id.c_str() ), bEnable(bEnable) { }

    void operator()( NScene::SceneComponent* sc )
    {
      sc->EnableWeak( bEnable );
    }

    bool bEnable;
  }traverser( id, bEnable );

  GetSceneObject()->Traverse( traverser );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PF_Core::ColorModificationChannel* PFClientLogicObject::CreateColorModificationChannel(PF_Core::ColorModificationPriority priority, bool fullRecolor /* = false */ )
{
	int insertIdx = 0;
	for ( ; insertIdx < colorModifications.size(); insertIdx++ )
	{
		if( priority <= colorModifications[insertIdx]->GetPriority() )
			break;
	}
  
  PF_Core::ColorModificationChannel* pNew = new PF_Core::ColorModificationChannel(priority, &colorChanged);
  colorModifications.insert( colorModifications.begin()+insertIdx, pNew );

  if ( fullRecolor )
  {
    pNew->SetFullRecolor( true );
    int insertIdx = 0;
	  for ( ; insertIdx < fullColorModifications.size(); insertIdx++ )
	  {
		  if( priority <= fullColorModifications[insertIdx]->GetPriority() )
			  break;
	  }
    fullColorModifications.insert( fullColorModifications.begin()+insertIdx, pNew );
  }

  colorChanged = true;

  return pNew;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::RemoveColorModificationChannel(PF_Core::ColorModificationChannel* pChannel)
{
	for ( int i = 0; i < colorModifications.size(); i++ )
	{
		if ( colorModifications[i] == pChannel )
		{
			colorModifications[i] = 0;
			colorModifications.erase( colorModifications.begin() + i );
			colorChanged = true;
			break;
		}
	}

  if ( pChannel->IsSetFullRecolor() )
  {
  	for ( int i = 0; i < fullColorModifications.size(); i++ )
	  {
		  if ( fullColorModifications[i] == pChannel )
		  {
			  fullColorModifications[i] = 0;
			  fullColorModifications.erase( fullColorModifications.begin() + i );
        colorChanged = true;
			  break;
		  }
	  }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientLogicObject::ProcessColorModifications()
{
  ProcessColorModifications( colorModifications );
  ProcessColorModifications( fullColorModifications, true );
}

void PFClientLogicObject::ProcessColorModifications( vector<CObj<PF_Core::ColorModificationChannel>>& colorModifications, bool fullCM /* = false */ )
{
  // colorModifications is a method param!
	PF_Core::ColorModificationChannel* blendChannel = 0;
	int mainIdx = 0;

	if ( !colorModifications.empty() )
	{
		blendChannel = colorModifications[0];
		for( int i = 1; i < colorModifications.size(); i++ )
		{
			PF_Core::ColorModificationChannel* next = colorModifications[i];
			if( (blendChannel->GetOpacity() < EPS_VALUE && PF_Core::CBM_Multiply != blendChannel->GetMixMode() ) )
				break;

			blendChannel = next;
			mainIdx = i;
		}
	}

  Render::HDRColor mulColor(1.0f, 1.0f, 1.0f, 1.0f);
  Render::HDRColor addColor(0.0f, 0.0f, 0.0f, 0.0f);
  bool isSetDefaultBlendMode = true;
  NDb::BlendMode blendMode = NDb::BLENDMODE_LERPBYALPHA;
  if ( !colorModifications.empty() && blendChannel->IsSetBlendMode() )
  {
    blendMode = blendChannel->GetBlendMode();
    isSetDefaultBlendMode = false;
  }
  bool specialTransparency = false;
  if(!colorModifications.empty())
  {
    for( int i = mainIdx; ; blendChannel = colorModifications[i] )
    {
      const float opacity                = blendChannel->GetOpacity();
      const PF_Core::ColorBlendMode mode = blendChannel->GetMixMode();
      specialTransparency = specialTransparency || blendChannel->IsSpecialTransparency();
      
      BlendColors(mode, &mulColor, &addColor, blendChannel->GetMulColor(), blendChannel->GetAddColor(), opacity);

      if( colorModifications[0] == blendChannel)
        break;
			i--;
    }
  }

  struct Coloriser : public NScene::TraverserByGroupFlags
  { 
    mutable NScene::MaterialColorAndOpacityChangerWithBlend mproc;
    bool fullCM;

    Coloriser( Render::HDRColor const& mulColor, Render::HDRColor const& addColor, NDb::BlendMode mode, bool isSetDefaultBlendMode, bool _fullCM ) 
    : NScene::TraverserByGroupFlags( 0, true ), mproc( mulColor, addColor, mode, isSetDefaultBlendMode ), fullCM( _fullCM )
    {
    }

    bool NeedToProcess(const SceneComponent* comp)const
    {
      enum
      {
        flagEffectIgnoreColorModification = NDb::EFFECTGROUPFLAGS_IGNORECOLORMODIFICATION | NScene::SceneComponent::GROUPFLAGS_EFFECT,
        flagEffectRecolorable = NDb::GROUPFLAGS_RECOLORABLE | NScene::SceneComponent::GROUPFLAGS_EFFECT,
        flagRecolorable = NDb::GROUPFLAGS_RECOLORABLE,
      };

      const int flags = comp->GetGroupFlags();

      if ((flags & flagEffectIgnoreColorModification) == flagEffectIgnoreColorModification)
        return false;

      const bool recolorable = ((flags & flagEffectRecolorable) == flagRecolorable);

      // TODO: действительно так? получается, что fullCM делает выбор между 2 непересекающимися наборами.
      return fullCM ? !recolorable : recolorable;
    }
    
    void operator()( NScene::SceneComponent* comp ) const 
    {
      comp->ForAllMaterials(mproc);
    }

  }coloriser( mulColor, addColor, blendMode, isSetDefaultBlendMode, fullCM );
  coloriser.mproc.specialTransparency = specialTransparency;

  GetSceneObject()->Traverse(coloriser);
}

void PFClientLogicObject::OnDestroyContents()
{
	NWorld::PFClientObjectBase::OnDestroyContents();
}

static void HideComponents( SceneComponent* sc )
{
  if ( !sc->IsTraversable() )
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

void PFClientLogicObject::CreateStandaloneEffect()
{
  GetSceneObject()->UnregisterCollisionGeometry();
  SceneObject* so = Release(pSceneObjectsHolder->GetActive());
  so->SetOwnerID( -3 );
  so->SetUpdateHook( 0 );

  struct AnimatedComponentInfo
  {
    NDb::DBID dbid;
    nstl::vector<int> passiveSkins;
    AnimatedComponentInfo( const NDb::DBID& _dbid, const nstl::vector<int>& _passiveSkins ) : dbid( _dbid ), passiveSkins( _passiveSkins ) { }
  };

  struct PassiveSkinsFinder : public NScene::GenericTraverser
  {
    SceneObject* so;
    nstl::vector<AnimatedComponentInfo> animatedComponentsInfo;

    PassiveSkinsFinder( SceneObject* _so ) : so( _so ) { }
    virtual void operator()( SceneComponent* pSceneComponent )
    {
      if ( !pSceneComponent->IsHide() )
      {
        AnimatedSceneComponent* pAnimatedSceneComponent = dynamic_cast<AnimatedSceneComponent*>( pSceneComponent );
        if ( pAnimatedSceneComponent )
        {
          nstl::vector<int> passiveSkins = pAnimatedSceneComponent->GetPassiveSkins();
          if ( !passiveSkins.empty() )
          {
            animatedComponentsInfo.push_back( AnimatedComponentInfo( pAnimatedSceneComponent->GetDBID(), passiveSkins ) );
          }
        }
      }
    }

    bool FindAnimatedComponentPassiveSkins ( const NDb::DBID& dbid, nstl::vector<int>& passiveSkins )
    {
      for ( nstl::vector<AnimatedComponentInfo>::iterator iter = animatedComponentsInfo.begin(); iter < animatedComponentsInfo.end(); iter++ )
      {
        if ( iter->dbid == dbid )
        {
          passiveSkins = iter->passiveSkins;
          return true;
        }
      }
       return false;
    }
  } finder( so );

  so->Traverse( finder );

  if ( so->GetRootComponent() )
  {
    SceneComponent* itFront = so->GetRootComponent();
    if ( itFront )
    {
      SceneComponent* it = itFront;
      do
      {
        HideComponents( it );
        it = it->GetBrother();
      } while ( it && it != itFront );
    }
  }

  struct Proc : public NScene::GenericTraverser
  {
    float animTime;

    Proc() : animTime( 0.0f ) { }
    virtual void operator()( SceneComponent* pSC )
    {
      if ( !pSC->IsHide() )
      {
        //TODO
        animTime = Max( animTime, pSC->GetSubTreeAnimLength() );
        if ( ( animTime == 0.0f ) && pSC->GetTimeControllerDesc() )
        {
          animTime = pSC->GetTimeControllerDesc()->cycleLength/pSC->GetTimeControllerDesc()->speed - pSC->GetCurTime();
        }

				if ( pSC->IsStayInWorld() )
				{
					if ( NScene::ParticleSceneComponent* particleSC = dynamic_cast<NScene::ParticleSceneComponent*>( pSC ) )
					{
						particleSC->DisableStrongWithWaitingForFinish();
					}
				}
      }
    }
  } proc;
  so->Traverse( proc );

  NDb::Ptr<NDb::BasicEffectStandalone> tempEffects = NDb::Get<NDb::BasicEffectStandalone>( NDb::DBID( "Tech/Default/Default.EFFT" ) );
  CObj<PF_Core::BasicEffect> effect = PF_Core::EffectsPool::Get()->Retrieve( tempEffects.GetPtr() );
  if ( PF_Core::BasicEffectStandalone* eff = dynamic_cast<PF_Core::BasicEffectStandalone*>(effect.GetPtr()) )
  {
    eff->SetSceneObject( so );
    eff->SetDeathType(NDb::EFFECTDEATHTYPE_TIME, proc.animTime );
  }
  else
  {
    NI_ALWAYS_ASSERT("Can not create BasicEffectStandalone");
  }

  pSceneObjectsHolder->Recreate( so->GetPosition(), DEADNODE );

  // Updating log
#ifndef _SHIPPING
  if ( DiAnimGraph* pAG = DiAnimGraph::GetGraphToLog() )
  {
    DiAnimGraph::DebugSetGraph( pAG );
  }
#endif

  struct PassiveSkinsHider : public NScene::GenericTraverser
  {
    PassiveSkinsFinder finder;

    PassiveSkinsHider( const PassiveSkinsFinder& _finder ) : finder( _finder ) { }
    virtual void operator()( SceneComponent* pSceneComponent )
    {
      if ( !pSceneComponent->IsHide() )
      {
        AnimatedSceneComponent* pAnimatedSceneComponent = dynamic_cast<AnimatedSceneComponent*>( pSceneComponent );
        if ( pAnimatedSceneComponent )
        {
          nstl::vector<int> passiveSkins;
          if ( finder.FindAnimatedComponentPassiveSkins( pAnimatedSceneComponent->GetDBID(), passiveSkins ) )
          {
            for ( int i = 0; i < passiveSkins.size(); i++ )
            {
              pAnimatedSceneComponent->ShowSkin( passiveSkins[i], false );
            }
          }
        }
      }
    }
  } hider( finder );
  GetSceneObject()->Traverse( hider );

  GetSceneObject()->RegisterCollisionGeometry( pSceneObjectsHolder->GetCollision() );
}

bool PFClientLogicObject::TryCreateStandaloneEffect()
{
  NI_ASSERT(pSceneObjectsHolder, "pSceneObjectsHolder must be valid!");

  if ( pSceneObjectsHolder->GetActive().__gEt__() )
  {
    struct FindStayInWorldComponent : public NScene::GenericTraverser, private NonCopyable
    {
      bool isFound;
      FindStayInWorldComponent() : GenericTraverser(), isFound(false) {}
      void operator() (NScene::SceneComponent *sc) 
      {
        if ( sc->IsStayInWorld() && !sc->IsHide() )
        {
          isFound = true;
        }
      }
    } finder;

    pSceneObjectsHolder->GetActive()->Traverse(finder);
    if ( finder.isFound )
    {
      CreateStandaloneEffect();
      return true;
    }
  }
  return false;
}

const nstl::string& PFClientLogicObject::GetNodeName() const
{
	static const nstl::string nodeName = BADNODENAME;
	NI_VERIFY(pSceneObjectsHolder != NULL, "pSceneObjectsHolder must be valid!", return nodeName;);
	return pSceneObjectsHolder->GetNodeName();
}

void PFClientLogicObject::ClearColorModifications()
{
  for(int i = 0; i < colorModifications.size(); i++ )
  {
    colorModifications[i] = 0;
  }
  colorModifications.clear();

  for(int i = 0; i < fullColorModifications.size(); i++ )
  {
    fullColorModifications[i] = 0;
  }
  fullColorModifications.clear();

  if( GetSceneObject() )
  {
    ProcessColorModifications();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientSingleStateObject::PFClientSingleStateObject(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp, const NDb::GameObject* gameObject /*= 0*/ )
  : PFClientLogicObject(pWO, cp)
{
  NI_PROFILE_FUNCTION

  // Make placement
  Placement place = NULLPLACEMENT;
  if ( cp.placement )
  {
    place = cp.placement->GetPlace();
  }
  else
  {
    place.pos = WorldObject()->GetPosition();
  }

  // Place it on terrain
  if ( gameObject && gameObject->heightObject )
  {
    NScene::PlaceOnTerrain( pScene->GetHeightsController(), place.pos, 0 );
  }
  else
  {
    NScene::PlaceOnTerrain( pScene->GetHeightsController(), place.pos, 1 );
  }

  InitInternal(place, pWO, cp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFClientSingleStateObject::PFClientSingleStateObject(const PF_Core::WorldObjectRef &pWO, const CreatePars &cp, const NGameX::PFClientLogicObject* unitClientObject )
  : PFClientLogicObject(pWO, cp)
{
  // receive placement from original client object
  Placement place = unitClientObject->GetPosition();
  const float yaw = place.rot.GetYaw();
  place.rot.FromEulerAngles( yaw, 0.0f, 0.0f );
  
  // Place it on terrain
  place.pos.z = 0.0f;
  NScene::PlaceOnTerrain(pScene->GetHeightsController(), place.pos);

  InitInternal(place, pWO, cp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientSingleStateObject::InitInternal( Placement& place, const PF_Core::WorldObjectRef &pWO, const CreatePars &cp )
{
  NI_PROFILE_FUNCTION

  // Create single scene object holder
  pSceneObjectsHolder = AutoPtr<ISceneObjectsHolder>( new SingleSceneObjectHolder(pScene, pWO->GetObjectId(), place, cp.sceneObject, cp.pCollision, cp.nodeName) );
  
  const NScene::SceneObjectRef& so = pSceneObjectsHolder->GetActive();
  if ( so )
  {
    // Make size of unit
    if ( so->GetRootComponent() )
    {
      CVec3 halfSize = so->GetWorldAABB().halfSize;
      unitSize = 2 * max( halfSize.x, halfSize.y );
    }
		so->RegisterCollisionGeometry( cp.pCollision );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientSingleStateObject::OnMove(const CVec3& position)
{
  NI_VERIFY( GetSceneObject(), "Have no scene object!", return; );
  Placement place = GetSceneObject()->GetPosition();
  place.pos = position;
  UpdatePlacement(place);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFClientSingleStateObject::RemoveCollision()
{
  if( GetSceneObject() && GetSceneObject()->GetSmallCollision() )
  {
    GetSceneObject()->GetSmallCollision()->SetEnabled(false);
  }
  if( GetSceneObject() && GetSceneObject()->GetCollision() )
  {
    GetSceneObject()->GetCollision()->SetEnabled(false);
    GetSceneObject()->UnregisterCollisionGeometry();
  }
}

}
