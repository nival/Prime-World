#include "stdafx.h"
#include "AnimatedSceneComponent.h"
#include "RenderableScene.h"
#include "../Render/SkeletalMesh.h"
#include "../Render/SkeletalAnimationBlender.h"
#include "../Render/SkeletonWrapper.h"
#include "../Render/RenderInterface.h"
#include "SceneObject.h"

#include "../System/InlineProfiler.h"


namespace NScene
{

template <class T>
void AnimatedSceneComponent::InternalConstructor( const T* pObject, const Placement& pos, const nstl::string& nodeName )
{
  animGraph     = NULL;
  extPars       = NULL;
  agApplicator  = NULL;
  agBlender     = NULL;
  
	for ( int i = 0; i < maxSkinsCount; i++ )
	{
		fragmentsCount[i] = 99999;
	}

  Render::SkeletalMesh* model = new Render::SkeletalMesh();
  agApplicator = new AnimGraphApplicator(pObject, model);
	agApplicator->GetModel()->SetDBID(dbid);
  //NI_VERIFY(agApplicator != NULL, "No MEM", return;);
  //agApplicator->Initialize(pObject);
    
  agBlender = new AnimGraphBlender(agApplicator);
  animGraph = DiAnimGraph::CreateByData(pObject->animGraph, pObject->animations, agBlender, NULL);
  NI_VERIFY(animGraph != NULL, "Failed to create animation graph", return;);
	SetNodeName( nodeName );
  animGraph->Restart( animGraph->GetDefNode(), true );
  // External parameters for AnimGraph
  extPars = new DiAnGrExtPars(pObject->animGraph, animGraph);

  extPars->applyParamsToGraph();
  animGraph->StoreDefaultValues();
    
  //CRAP{
  for ( int i = 0; i < pObject->skins.size(); ++i )
  {
    ShowSkin( i, true );
  }
  //CRAP}

	// @BVS@TODO Default AABB. Should be calculated according to bones position
	localAABB.center   = CVec3( 0.0f, 0.0f, 1.0f );
	localAABB.halfSize = CVec3( 1.0f, 1.0f, 2.0f );
}

AnimatedSceneComponent::AnimatedSceneComponent( const NDb::Skeleton* pObject, const Placement& pos )
: SceneComponent(0, 0, pos)
, curAnim(0)
, oldTime(0.0f)
, animSpeed(1.0f)
{
	pDBObject = pObject;

  InternalConstructor<NDb::Skeleton>( pObject, pos, "idle" );
}

#include "TestBB.h"

AnimatedSceneComponent::AnimatedSceneComponent( const NDb::DBAnimatedSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos, const nstl::string& nodeName )
: SceneComponent(pObject, pObj, pos)
, curAnim(0)
, oldTime(0.0f)
, animSpeed(1.0f)
{
  pDBObject2 = pObject;

  InternalConstructor<NDb::DBAnimatedSceneComponent>( pObject, pos, nodeName );

  animationCallbackHelpers.resize( pDBObject2->skins.size() );

  for ( int i = 0; i < pDBObject2->skins.size(); ++i )
  {
    animationCallbackHelpers[i].component = this;
    animationCallbackHelpers[i].skinID = i;

    if ( pDBObject2->skins[i].events.IsEmpty() )
      continue;

    if ( pDBObject2->skins[i].events->enableEvents.size() > 0 && 
         pDBObject2->skins[i].events->order == NDb::ENABLEDISABLEORDER_ENABLETHENDISABLE )
    {
      ShowSkin( i, false );
    }
  }

  const bool isAABBValid = pObject->aabb.minX < pObject->aabb.maxX && 
			                     pObject->aabb.minY < pObject->aabb.maxY && 
			                     pObject->aabb.minZ < pObject->aabb.maxZ;
  //NI_ASSERT( isAABBValid, NStr::StrFmt("AABB should be valid %s", FormatDescription()) );
  TEST_BB_UNIQUE(isAABBValid);
  if(isAABBValid) {
		// User specified fixed AABB for this component
		localAABB.Set(pObject->aabb);
    agApplicator->GetModel()->SetLocalAABB(localAABB);
	}
}

bool AnimatedSceneComponent::RetrieveJointPlacement(const string& name, Placement &pos)
{
  NI_ASSERT(!name.empty(), NStr::StrFmt( "joint name should present %s",FormatDescription() ) );
	unsigned int jointIdx_ = 0;
  NI_ASSERT(agApplicator, NStr::StrFmt( "Animation graph should present %s",FormatDescription() ) );
	if (!agApplicator->GetModel()->GetSkeletonWrapper()->GetJointIndexByName( name.c_str(), jointIdx_ ))
		return false;

	const Matrix43* bmat = agApplicator->GetModel()->GetSkeletonWrapper()->GetBoneWorldMatrices();
	pos.FromMatrix( bmat[jointIdx_] );
	return true;
}

void AnimatedSceneComponent::OnTimeLooped(float time2StartWith)
{
	SceneComponent::OnTimeLooped(time2StartWith);
	agBlender->Restart(agBlender->GetMainGraph()->GetNearestNode());
	agBlender->Update(time2StartWith);
}

void AnimatedSceneComponent::Init()
{
  SceneComponent::Init();

  if ( agBlender )
    agBlender->SetAnimGraphs(GetMainAnimGraph(), GetAdditionalAnimGraph());
}


void AnimatedSceneComponent::Reinit()
{
	SceneComponent::Reinit();
  agBlender->Restart( GetMainAnimGraph()->GetDefNode() );
  
  if(extPars)
    extPars->restart();
  
  ResetCurAnimTime();
}

void AnimatedSceneComponent::Update( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  NI_PROFILE_FUNCTION

  float timeDelta = 0;
	if (!UpdateBasics( pars, parentPos, timeDiff, timeDelta ))
		return;

  // Make matrix
  Matrix43 worldMatrix;
  worldPlacement.GetMatrix( &worldMatrix );

  // Update world AABB & grow object AABB
  worldAABB.Transform(worldMatrix, localAABB);
  NI_ASSERT(worldAABB.IsValid(), NStr::StrFmt( "AABB should be valid %s", FormatDescription() ) );
  agApplicator->GetModel()->SetWorldAABB(worldAABB);

  pars.objectAABB.Grow(worldAABB);

  Render::SkeletalMesh *pSkeletalMesh;

  UpdateExtParams();
  agApplicator->SetCurPlacement(worldMatrix );

  agBlender->Update(timeDelta);

  // ATTENTION: Here I'll update add world matrices for bones & skinning
  pSkeletalMesh = agApplicator->GetModel();
  pSkeletalMesh->Update(false);
  //agApplicator->FixModelPlacement( worldMatrix );

  {
    NI_PROFILE_BLOCK( "Child Updates" );
      
    const float scaledTimeDelta = timeDelta * agBlender->GetMainGraph()->GetGraphSpeedUpCoeff();
	  if ( child )
	  {
		  SceneComponent* it = GetChild();
		  do
		  {
        const float dt = (it->GetParentTransformUsageFlags() & NDb::ATTACHFLAGS_USEAGSPEEDCOEFF) ? scaledTimeDelta : timeDelta;
        int jointIdx   = it->GetJointIdx();
			  if ( jointIdx != -1 )
			  {
          NI_ASSERT( jointIdx < pSkeletalMesh->GetSkeletonWrapper()->GetBonesCount(), NStr::StrFmt( "Invalid joint index %d in %s", jointIdx, GetDBID().GetFileName().c_str() ) );
				  const Matrix43* bmat = pSkeletalMesh->GetSkeletonWrapper()->GetBoneWorldMatrices();
				  Placement jointPos;
				  jointPos.FromMatrix( bmat[jointIdx] );

          if ( !it->GetLocatorName().empty() )
          {
            if ( !(it->GetLocatorFlags() & NDb::LOCATORATTACHFLAGS_USEJOINTPOSITION) )
            {
              jointPos.pos = worldPlacement.pos;
            }
            if ( !(it->GetLocatorFlags() & NDb::LOCATORATTACHFLAGS_USEJOINTROTATION) )
            {
              jointPos.rot = worldPlacement.rot;
            }
            if ( !(it->GetLocatorFlags() & NDb::LOCATORATTACHFLAGS_USEJOINTSCALE) )
            {
              jointPos.scale = worldPlacement.scale;
            }
          }

				  it->Update( pars, jointPos, dt );
			  }
			  else
			  {
				  it->Update( pars, worldPlacement, dt );
			  }

			  it = it->GetBrother();

		  }	while ( it && it != GetChild() );
	  }
	}
}

void AnimatedSceneComponent::UpdateExtParams()
{
  if ( extPars )
    extPars->applyParamsToGraph();
}

void AnimatedSceneComponent::RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants )
{
  if (!agApplicator->GetRenderable())
		return;

	SceneComponent::RenderToQueue(queue, sceneConstants);
  agApplicator->GetRenderable()->RenderToQueue(queue);
}

void AnimatedSceneComponent::ShowSkin( const string& skinName, bool show )
{
	if ( pDBObject.IsEmpty() )
	{
		if ( show )
		{
			const NDb::SkinPart* pSkin = 0;
			for ( int i = 0; i < pDBObject2->skins.size(); ++i )
			{
				if ( pDBObject2->skins[i].skinPartName == skinName )
				{
					pSkin = &pDBObject2->skins[i];
					if ( !IsSkinActive(i) )
						agApplicator->GetModel()->AddSkinPart( pSkin, &fragments[i][0], &fragmentsCount[i] );
					break;
				}
			}

			NI_ASSERT( pSkin, NStr::StrFmt( "Skin %s not found in %s", skinName.c_str(), FormatDescription() ) );
		}
		else
		{
			for ( int i = 0; i < pDBObject2->skins.size(); ++i )
			{
				if ( pDBObject2->skins[i].skinPartName == skinName )
				{
					if ( IsSkinActive(i) )
					{
						agApplicator->GetModel()->RemoveSkinPart( fragmentsCount[i], &fragments[i][0] );
						fragmentsCount[i] = 0;
					}
					break;
				}
			}
		}
	}
	else
	{
		if ( show )
		{
			const NDb::SkinPartBase* pSkin = 0;
			for ( int i = 0; i < pDBObject->skins.size(); ++i )
			{
				if ( pDBObject->skins[i].skinPartName == skinName )
				{
					pSkin = &pDBObject->skins[i];
					if ( !IsSkinActive(i) )
					{
	          agApplicator->GetModel()->AddSkinPart( pSkin, &fragments[i][0], &fragmentsCount[i] );
					}
					break;
				}
			}

			NI_ASSERT( pSkin, NStr::StrFmt( "Skin %s not found in %s", skinName.c_str(), FormatDescription() ) );
		}
		else
		{
			for ( int i = 0; i < pDBObject->skins.size(); ++i )
			{
				if ( pDBObject->skins[i].skinPartName == skinName )
				{
					if ( IsSkinActive(i) )
					{
	          agApplicator->GetModel()->RemoveSkinPart( fragmentsCount[i], &fragments[i][0] );
						fragmentsCount[i] = 0;
					}
					break;
				}
			}
		}
	}
}

void AnimatedSceneComponent::ShowSkin( int skinIdx, bool show )
{
  if ( pDBObject.IsEmpty() )
	{
		if ( show )
		{
			const NDb::SkinPart* pSkin = 0;
			pSkin = &pDBObject2->skins[skinIdx];
			if ( !IsSkinActive(skinIdx) )
			{
	      agApplicator->GetModel()->AddSkinPart(pSkin, &fragments[skinIdx][0], &fragmentsCount[skinIdx]);
			}
    }
		else
		{
			if ( IsSkinActive(skinIdx) )
			{
	      agApplicator->GetModel()->RemoveSkinPart(fragmentsCount[skinIdx], &fragments[skinIdx][0]);
				fragmentsCount[skinIdx] = 0;
			}
		}
	}
	else
	{
		if ( show )
		{
			const NDb::SkinPartBase* pSkin = 0;
			pSkin = &pDBObject->skins[skinIdx];
			if ( !IsSkinActive(skinIdx) )
			{
	      agApplicator->GetModel()->AddSkinPart( pSkin, &fragments[skinIdx][0], &fragmentsCount[skinIdx] );
			}
		}
		else
		{
			if ( IsSkinActive(skinIdx) )
			{
	      agApplicator->GetModel()->RemoveSkinPart( fragmentsCount[skinIdx], &fragments[skinIdx][0] );
				fragmentsCount[skinIdx] = 0;
			}
		}
	}
}

void AnimatedSceneComponent::EnableSkin( int skinIdx, bool val )
{
  agApplicator->GetModel()->SetEnableSkinPart( fragmentsCount[skinIdx], &fragments[skinIdx][0], val);
}

void AnimatedSceneComponent::TurnOffSkins()
{
	if ( pDBObject )
	{
		for ( int i = 0; i < pDBObject->skins.size(); ++i )
		{
			ShowSkin( i, false );
		}
	}
	else if ( pDBObject2 )
	{
		for ( int i = 0; i < pDBObject2->skins.size(); ++i )
		{
			ShowSkin( i, false );
		}
	}
}

// This functionality is used ONLY in editor, in "View->Show Animations" menu
void AnimatedSceneComponent::StartAnimSequence(int animationIndex)
{
  diUSE_PARAM(animationIndex);
  return;
/*
  if ( NULL == animGraph )
  {
    NI_ALWAYS_ASSERT("Strange behaviour of AGEditor - no AnimGraph!");
    return;
  }

  // NOTE: we are setting not node but animation sequence in current node - this means that we are changing AnimGraph "on the fly"
  
  // Temporary message! All places in the code conserning this problem: search for ///eugbel///AGvsAN
  static int s_warnCounter = 0;
  if (0 == s_warnCounter)
  {
    //MessageBox(NULL, "ATTENTION! After previewing animations in \"Animations\" panel do not work with AnimatonGraph - the results are unpredictable!\nTo work with AnimGraph - reload SOBJ!", "Animation graph", MB_OK | MB_ICONWARNING);
    s_warnCounter++;
  }
  
  animGraph->SetConcreteAnimSeqInCurrentLoopedNodeEDITORONLY( animationIndex );
*/
}

void AnimatedSceneComponent::StartAnimation(int animationIndex)
{
  curAnim = animationIndex;
	agBlender->Restart(curAnim);
  //agBlender->SetMainAGTargetNode(curAnim);
  ResetCurAnimTime();
  animSpeed = 1.0f;
}

void AnimatedSceneComponent::StartAnimation( string const& animName, EAnimAction mode)
{
  curAnim = agBlender->GetMainGraph()->GetNodeIDByNameSlow(animName.c_str());
  agBlender->SetMainAGTargetNode(curAnim);
  ResetCurAnimTime();
  animSpeed = 1.0f;
}

bool AnimatedSceneComponent::IsAnimationPlaying( string const& animName ) const
{	
  return (agBlender->GetMainGraph()->GetCurNodeUnsafe() == agBlender->GetMainGraph()->GetNodeIDByNameSlow(animName.c_str()) /*namesLinker->GetID(_nodesNames[i].enumID)*/); ///AGLINKER///
}

float AnimatedSceneComponent::GetPureAnimLength()
{
  //TODO!!!!!!
  unsigned int curNode = GetMainAnimGraph()->GetNearestNode();
  float nodeDuration = animGraph->GetNodeDuration(curNode);
	NI_ASSERT( nodeDuration<1000.0f, NStr::StrFmt( "Bad animation length %s", GetDBID().GetFileName() ) );
	return nodeDuration;
}

void AnimatedSceneComponent::Attach( SceneComponent* toadd )
{
  if ( !toadd )
    return;

  SceneComponent* it = toadd;
  do 
  {
    it->SetJointIdx( -1 );
    if ( it->GetLocatorName().length() && !pDBObject2.IsEmpty() && !pDBObject2->locatorList.IsEmpty() )
    {
      for ( int i = 0; i < pDBObject2->locatorList->locators.size(); i++ )
      {
        if ( pDBObject2->locatorList->locators[i].name == it->GetLocatorName() )
        {
          unsigned int boneIdx = 0;
          const NDb::Locator& locator = pDBObject2->locatorList->locators[i];
          const Placement& offset = locator.offset2.GetPlace();
          it->SetLocatorPos( offset.pos, offset.rot, offset.scale );
          it->SetLocatorName( it->GetLocatorName(), pDBObject2->locatorList->locators[i].flags );
          if ( agApplicator->GetModel()->GetSkeletonWrapper()->GetJointIndexByName( locator.jointName.c_str(), boneIdx ) )
          {
            it->SetJointIdx( boneIdx );
          }
          break;
        }
      }
    }
    it = it->GetBrother();
  } while ( it && it != toadd );

	SceneComponent::Attach( toadd );
}

float AnimatedSceneComponent::GetAnimDuration( int animIdx ) const
{
  return agApplicator->GetAnimDuration( animIdx );
}

int AnimatedSceneComponent::GetAnimDurationInFrames( int animIdx ) const
{
  return int(GetAnimDuration(animIdx) * (float)s_standardAnimationFPSInMaya);
}

void AnimatedSceneComponent::ForAllMaterials(Render::IMaterialProcessor &proc)
{
  Render::SkeletalMesh* pMesh = agApplicator->GetModel();

  if (pMesh)
    pMesh->ForAllMaterials(proc);
}

AnimatedSceneComponent::~AnimatedSceneComponent()
{
  NI_ASSERT( agApplicator != NULL && agBlender->GetMainGraph() != NULL, NStr::StrFmt( "AnimGraph and Applicator should always present! %s", FormatDescription() ) );

  if (agBlender != NULL)
  {
    delete agBlender;
    agBlender = NULL;
  }

  if (agApplicator != NULL)
  {
    delete agApplicator;
    agApplicator = NULL;
  }

  if (animGraph != NULL)
  {
    DiAnimGraph::Destroy(animGraph);
    animGraph = NULL;
  }

  if (extPars != NULL)
  {
    delete extPars;
    extPars = NULL;
  }
}

nstl::vector<int> AnimatedSceneComponent::GetActiveSkins()
{
  nstl::vector<int> result;
  if ( pDBObject.IsEmpty() )
  {
    for ( int i = 0; i < pDBObject2->skins.size(); i++ )
    {
      if ( ( fragmentsCount[i] > 0 ) && ( fragmentsCount[i] < 10 ) )
      {
        result.push_back( i );
      }
    }
  }
  else
  {
    for ( int i = 0; i < pDBObject->skins.size(); ++i )
    {
      if ( ( fragmentsCount[i] > 0 ) && ( fragmentsCount[i] < 10 ) )
      {
        result.push_back( i );
      }
    }
  }
  return result;
}

nstl::vector<int> AnimatedSceneComponent::GetPassiveSkins()
{
  nstl::vector<int> result;
  if ( pDBObject.IsEmpty() )
  {
    for ( int i = 0; i < pDBObject2->skins.size(); ++i )
    {
      if ( ( fragmentsCount[i] <= 0 ) || ( fragmentsCount[i] >= 10 ) )
      {
        result.push_back( i );
      }
    }
  }
  else
  {
    for ( int i = 0; i < pDBObject->skins.size(); ++i )
    {
      if ( ( fragmentsCount[i] <= 0 ) || ( fragmentsCount[i] >= 10 ) )
      {
        result.push_back( i );
      }
    }
  }
  return result;
}

vector<string> AnimatedSceneComponent::GetJointsList() const
{
  vector<string> res;

  NI_ASSERT(agApplicator, NStr::StrFmt( "Animation graph should present %s", FormatDescription() ) );
  res = agApplicator->GetModel()->GetSkeletonWrapper()->GetJointsList();

  return res;
}

// 0 - main graph, 1 - additional graph
AnimGraphController *AnimatedSceneComponent::CreateAnimGraphController( int agIdx ) 
{
  DiAnimGraph *graph(NULL);
  
  if (0 == agIdx)
    graph = agBlender->GetMainGraph();
  else if (1 == agIdx)
    graph = agBlender->GetAdditionalGraph();
  else
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt( "Wrong graph index! %s",FormatDescription() ) );
  }

  if (NULL == graph)
    return NULL;

  AnimGraphController *agc(NULL);
  if (pDBObject != NULL)
    agc = new AnimGraphController(graph, pDBObject->animations);
  else if (pDBObject2 != NULL)
    agc = new AnimGraphController(graph, pDBObject2->animations);

  return agc;
}

nstl::vector<nstl::string> AnimatedSceneComponent::GetAnimations()
{
  nstl::vector<nstl::string> result;
  if ( pDBObject.IsEmpty() )
  {
    for ( int i = 0; i < pDBObject2->animations.size(); ++i )
    {
      result.push_back(pDBObject2->animations[i].name);
    }
  }
  else
  {
    for ( int i = 0; i < pDBObject->animations.size(); ++i )
    {
      result.push_back(pDBObject->animations[i].name);
    }
  }
  return result;
}

void AnimatedSceneComponent::SetAnimGraphs( DiAnimGraph* main, DiAnimGraph* additional, DiAnGrExtPars *firstGraphExtPars )
{
  NI_ASSERT(main != NULL, NStr::StrFmt( "%s", FormatDescription() ) );

  if (animGraph != NULL)
  {
    DiAnimGraph::Destroy(animGraph);
    animGraph = NULL;
  }
  animGraph = main;
  agBlender->SetGraphs(main, additional);

  if (extPars != NULL)
  {
    delete extPars;
    extPars = NULL;
  }
  extPars = firstGraphExtPars;
  
  if (extPars != NULL)
  {
    NI_ASSERT(extPars->hasGraph(), NStr::StrFmt( "External parameters should have graph or function applyToGraph() will fail! %s", FormatDescription() ) );
  }
}

void AnimatedSceneComponent::SetFakeAnimGraphs( DiAnimGraph* main, DiAnimGraph* additional, DiAnGrExtPars *firstGraphExtPars )
{
  NI_ASSERT(main != NULL, NStr::StrFmt( "%s", FormatDescription() ) );
  animGraph = main;
  agBlender->SetGraphs(main, additional);
  extPars = firstGraphExtPars;

  if (extPars != NULL)
  {
    NI_ASSERT(extPars->hasGraph(), NStr::StrFmt( "External parameters should have graph or function applyToGraph() will fail! %s", FormatDescription() ) );
  }
}

const nstl::vector<NDb::Animation>& AnimatedSceneComponent::GetDBAnimations()
{
  if ( pDBObject.IsEmpty() )
  {
    return pDBObject2->animations;
  }
  return pDBObject->animations;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedSceneComponent::OnAfterAdded(class SceneObject *pObject)
{
  if (agApplicator->GetModel()->NeedLightingSH())
    pObject->SetupForLighting();

  RegisterSkinEvents();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedSceneComponent::ProcessExternalEvent( const char *eventName )
{
  SceneComponent::ProcessExternalEvent( eventName );

  if ( pDBObject2.IsEmpty() )
    return;

  nstl::vector<NDb::SkinPart>::const_iterator it = pDBObject2->skins.begin();
  nstl::vector<NDb::SkinPart>::const_iterator last = pDBObject2->skins.end();

  for ( int skinID = 0; it != last; ++it, ++skinID )
  {
    if ( it->events.IsEmpty() )
      continue;

    // check for enable event
    for (int i = 0; i < it->events->enableEvents.size(); ++i)
    {
      if ( it->events->enableEvents[i]->GetObjectTypeID() == NDb::NamedSCEvent::typeId )
      {
        NDb::NamedSCEvent const *pEvent = dynamic_cast<NDb::NamedSCEvent const *>(it->events->enableEvents[i].GetPtr());
        NI_ASSERT(pEvent, "Invalid DB resource");
        if ( strcmp(pEvent->name.c_str(), eventName) == 0 )
        {
          ShowSkin( skinID, true );
          break;
        }
      }
    }

    // check for disable event
    for (int i = 0; i < it->events->disableEvents.size(); ++i)
    {
      if ( it->events->disableEvents[i]->GetObjectTypeID() == NDb::NamedSCEvent::typeId )
      {
        NDb::NamedSCEvent const *pEvent = dynamic_cast<NDb::NamedSCEvent const *>(it->events->disableEvents[i].GetPtr());
        NI_ASSERT(pEvent, "Invalid DB resource");
        if ( strcmp(pEvent->name.c_str(), eventName) == 0 )
        {
          ShowSkin( skinID, false );
          break;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static DiInt32 ActivateSkinCallback(DiAnGrCallbackParams const &cpParams)
{
  AnimatedSceneComponent::AnimationCallbackHelper *helper 
    = reinterpret_cast<AnimatedSceneComponent::AnimationCallbackHelper*>(cpParams.vpUserData);

  helper->component->ShowSkin( helper->skinID, true );

  return DIOBJMSG_CONTINUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static DiInt32 DeactivateSkinCallback(DiAnGrCallbackParams const &cpParams)
{
  AnimatedSceneComponent::AnimationCallbackHelper *helper 
    = reinterpret_cast<AnimatedSceneComponent::AnimationCallbackHelper*>(cpParams.vpUserData);

  helper->component->ShowSkin( helper->skinID, false );

  return DIOBJMSG_CONTINUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimatedSceneComponent::OnAfterAttached()
{
  SceneComponent::OnAfterAttached();
  RegisterSkinEvents();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  AnimatedSceneComponent::RegisterSkinEvents()
{
  if ( pDBObject2.IsEmpty() )
    return;

  nstl::vector<NDb::SkinPart>::const_iterator it = pDBObject2->skins.begin();
  nstl::vector<NDb::SkinPart>::const_iterator last = pDBObject2->skins.end();

  for ( int skinID = 0; it != last; ++it, ++skinID )
  {
    if ( it->events.IsEmpty() )
      continue;

    // Setup actions
    SetupAnimEvents( it->events->enableEvents, ActivateSkinCallback, &animationCallbackHelpers[skinID], true );
    SetupAnimEvents( it->events->disableEvents, DeactivateSkinCallback, &animationCallbackHelpers[skinID], true );
  }

}

bool AnimatedSceneComponent::IsSkinActive( int skinIdx )
{
	if ( skinIdx >= 0 && skinIdx < maxSkinsCount && fragmentsCount[skinIdx] > 0 && fragmentsCount[skinIdx] < 10 )
	{
		return true;
	}
	return false;
}

float AnimatedSceneComponent::GetCurTime() const
{
	float time = GetAnimatedTime();
	float res = (time-oldTime)*animSpeed;
	return res;
}

void AnimatedSceneComponent::SetAnimSpeed( float val )
{
	animSpeed = val;
}

void AnimatedSceneComponent::SetNodeName( const nstl::string& nodeName )
{
	if ( !animGraph )
		return;

	DiInt32 defNode = animGraph->GetNodeIDByNameSlowQuite(nodeName.c_str());
	if ( defNode == DIANGR_NO_SUCH_ELEMENT )
		defNode = animGraph->GetDefNode();
	animGraph->SetDefNode( defNode );
}
} // namespace NScene
