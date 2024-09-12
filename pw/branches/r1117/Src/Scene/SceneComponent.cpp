#include "stdafx.h"
#include "../Render/MaterialSpec.h"
#include "../Render/sceneconstants.h"
#include "../Render/DebugRenderer.h"
#include "HeightsController.h"
#include "SceneObject.h"
#include "SceneObjectUtils.h"
#include "SceneComponent.h"
#include "DiAnGr.h"
#include "Camera.h"

namespace NScene
{

unsigned long SceneComponent::s_numComponents = 0;
unsigned long SceneComponent::s_numComponentsCastShadow = 0;
unsigned long SceneComponent::s_numComponentsReflectInWater = 0;
unsigned long SceneComponent::s_numRendered = 0;
unsigned long SceneComponent::s_numRenderedCastShadow = 0;
unsigned long SceneComponent::s_numRenderedReflectInWater = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GroundHitEvent
{
private:
	float heightAboveGround;
	bool  isAboveGround;

public:		
  GroundHitEvent *pNext;
  bool  activate;

public:		
	GroundHitEvent(bool activate_, float height) 
		: pNext(0), activate(activate_), heightAboveGround(height), isAboveGround(true) 
	{}

	virtual bool HasHappen(IScene *pScene, SceneComponent &sc)
	{
		NI_ASSERT(pScene, "Scene should present");
		if (!sc.IsTraversable())
		{
      const Placement& parPl = sc.GetParent() ? sc.GetParent()->GetWorldPlacement() : Placement();
			sc.ConstructWorldPlacement( parPl, pScene );
		}
		const CVec3 &pos = sc.GetWorldPlacement().pos;
		float groundZ = 0.0f;
		pScene->GetHeightsController().GetHeight(pos.x, pos.y, 0, &groundZ, 0);
		bool isNowAboveGround = pos.z > (heightAboveGround + groundZ);
		bool eventHappen = isAboveGround && !isNowAboveGround;
		isAboveGround = isNowAboveGround;
		return eventHappen;
	}
};

namespace
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiInt32 ActivateSceneComponent(DiAnGrCallbackParams const &cpParams)
{
	SceneComponent *pSC = reinterpret_cast<SceneComponent*>(cpParams.vpUserData);
	pSC->EnableByEvent();
	return DIOBJMSG_CONTINUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DiInt32 DeactivateSceneComponent(DiAnGrCallbackParams const &cpParams)
{
	SceneComponent *pSC = reinterpret_cast<SceneComponent*>(cpParams.vpUserData);
	pSC->DisableByEvent();
	return DIOBJMSG_CONTINUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SetupAnimEvent(DiAnimGraph *graph, const NDb::AnimationSCEvent &evt, DiAnGrCallback _callback, void *_userData)
{
	switch (evt.type)
	{
	case NDb::ANIMEVENTTYPE_NODEENTER:
		{
			int id = graph->GetNodeIDByNameSlowQuite(evt.name.c_str());
			if (id == DIANGR_NO_SUCH_ELEMENT)
			{
				return false;
			}
			// register callback on entering into anim graph node
			return graph->RegisterCallback(DIANGR_NODE, id, _callback, DIANGR_CF_ELEMENT_ENTER, _userData, DIANGR_INVALID_FLOAT_VALUE, evt.probability);
		}
	case NDb::ANIMEVENTTYPE_NODELEAVE:
		{
			int id = graph->GetNodeIDByNameSlowQuite(evt.name.c_str());
			if (id == DIANGR_NO_SUCH_ELEMENT)
			{
				return false;
			}
			// register callback on leaving anim graph node
			return graph->RegisterCallback(DIANGR_NODE, id, _callback, DIANGR_CF_ELEMENT_LEAVE, _userData, DIANGR_INVALID_FLOAT_VALUE, evt.probability);
		}
	case NDb::ANIMEVENTTYPE_NODEPARAM:
		{
			int id = graph->GetNodeIDByNameSlowQuite(evt.name.c_str());
			if (id == DIANGR_NO_SUCH_ELEMENT)
			{
				return false;
			}
			// register callback on exact param in anim graph node
			return graph->RegisterCallback(DIANGR_NODE, id, _callback, DIANGR_CF_EXACT_PARAM, _userData, evt.animParam, evt.probability);
		}
	case NDb::ANIMEVENTTYPE_MARKER:
		{
      return graph->RegisterCallbackForAllSameMarkers(evt.name.c_str(), _callback, _userData);
		}
	}

	return false;
}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneComponent::SceneComponent() 
: locatorName("")
, jointIdx(-1)
,	child(0)
, parent(0)
, leftBrother(0)
, rightBrother(0)
, parentTransformUsage(NDb::ATTACHFLAGS_USEPARENTSCALE | NDb::ATTACHFLAGS_USEPARENTROTATION | NDb::ATTACHFLAGS_USEPARENTTIME | NDb::ATTACHFLAGS_USEAGSPEEDCOEFF)
, disabledCount(0)
, groupFlags(0)
, pGroundHitEvents(0)
, isHide( false )
, orientation(NDb::SCORIENTATION_DEFAULT)
{}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneComponent::SceneComponent(const NDb::DBSceneComponent* pDBObj, const NDb::AttachedSceneComponent* pObj, 
															 const Placement& pos)
: locatorName("")
, jointIdx(-1)
, child(0)
, parent(0)
, leftBrother(0)
, rightBrother(0)
, timeController(pObj ? pObj->timeController : 0)
, parentTransformUsage(NDb::ATTACHFLAGS_USEPARENTSCALE | NDb::ATTACHFLAGS_USEPARENTROTATION | NDb::ATTACHFLAGS_USEPARENTTIME | NDb::ATTACHFLAGS_USEAGSPEEDCOEFF)
, pDBEvents(pObj ? pObj->events : 0)
, pGroundHitEvents(0)
, disabledCount(0)
, groupFlags(pDBObj ? pDBObj->groupFlags : 0)
, isHide( false )
, orientation(NDb::SCORIENTATION_DEFAULT)
, isLocatorRised( false )
{ 
  if ( !pDBObj )
    return;

  SetDBID(pDBObj->GetDBID());
  orientation = pDBObj->orientation;

  if ( !pObj )
		return;

	timeController.Reinit(*this);
	offset.Init( pObj->placement, timeController.GetTime() );
	offset.SetPlacement( offset.GetPlacement() + pos );
	SetId(pObj->id);

	// Disable component if it has enable events
	if (pDBEvents)
	{
		SetupOtherEvents(pDBEvents->enableEvents, true);
		SetupOtherEvents(pDBEvents->disableEvents, false);

		// Disable component if it has enable events
		if ( Need2DisableComponentOnStart() )
			DisableStrong(true);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::Init()
{
	timeController.Reinit(*this);
	timeController.SetPureAnimationLength(GetPureAnimLength());

  // if any material wants to cast shadows or be reflected in water, set flag
  struct CheckFlags : public Render::IMaterialProcessor
  {
    int foundCaster;
    int foundReflect;
    CheckFlags() : foundCaster(0), foundReflect(0) {}
    virtual void operator()(Render::BaseMaterial &material)
    {
      foundCaster  |= (material.GetMaterialFlags() & NDb::MATERIALFLAGS_SHADOWCASTER);
      foundReflect |= (material.GetMaterialFlags() & NDb::MATERIALFLAGS_REFLECTINWATER);
    }
  } checkFlags;
  ForAllMaterials(checkFlags);

  if (!checkFlags.foundCaster)
    groupFlags &= ~GROUPFLAGS_CASTSHADOW;
  else
    groupFlags |= GROUPFLAGS_CASTSHADOW;

  if (!checkFlags.foundReflect)
    groupFlags &= ~GROUPFLAGS_REFLECTINWATER;
  else
    groupFlags |= GROUPFLAGS_REFLECTINWATER;

#ifdef SCENECOMPONENT_STATS
  s_numComponents++;
  if (groupFlags & GROUPFLAGS_CASTSHADOW)
    s_numComponentsCastShadow++;
  if (groupFlags & GROUPFLAGS_REFLECTINWATER)
    s_numComponentsReflectInWater++;
#endif // SCENECOMPONENT_STATS
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SceneComponent::Need2DisableComponentOnStart() const
{
	return pDBEvents && pDBEvents->enableEvents.size() > 0 && 
			   pDBEvents->order == NDb::ENABLEDISABLEORDER_ENABLETHENDISABLE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::Reinit()
{ 
	disabledCount = 0;
	parentTransformUsage &= ~WORLDPLACE_ALREADY_UPDATED;

	timeController.Reinit(*this);
	SetAnimatedsTime(0.0f);

	// Disable component if needed
	if ( Need2DisableComponentOnStart() )
		DisableStrong(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::ReinitSubTree()
{
	struct Func : public FullTraverser, NonCopyable
	{
		void operator()(SceneComponent *pSC) { pSC->Reinit(); }
	} func;

	Traverse(func);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::DeinitSubTree()
{
	struct Func : public FullTraverser, NonCopyable
	{
		void operator()(SceneComponent *pSC) { pSC->Deinit(); }
	} func;

	Traverse(func);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::InitDisabledState()
{
  NDb::EnableDisableSCEvents const *events = pDBEvents.GetPtr();

  if (events && events->enableEvents.size() > 0)
  {
    if (events->order == NDb::ENABLEDISABLEORDER_ENABLETHENDISABLE)
    {
      DisableStrong(true);
    }
    else
    {
      NI_ASSERT(events->order == NDb::ENABLEDISABLEORDER_DISABLETHENENABLE, "Unknown enable/disable order");
      DisableStrong(false);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::EnableByEvent()
{
	NI_ASSERT(pDBEvents, "Events should present");
	if (pDBEvents->restartComponent)
		ReinitSubTree();

  DisableStrong(false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::DisableByEvent()
{
	NI_ASSERT(pDBEvents, "Events should present");
	if (pDBEvents->restartComponent)
		DeinitSubTree();

  struct Func : public FullTraverser, NonCopyable
	{
		void operator()(SceneComponent *pSC) { pSC->DisableStrongWithWaitingForFinish(); }
	} func;
	Traverse(func);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::ProcessExternalEvent(const char *eventName)
{
  if (pDBEvents)
  {
    int i;

    // check for enable event
    for (i = 0; i < pDBEvents->enableEvents.size(); ++i)
    {
      if ( pDBEvents->enableEvents[i]->GetObjectTypeID() == NDb::NamedSCEvent::typeId )
      {
        NDb::NamedSCEvent const *pEvent = dynamic_cast<NDb::NamedSCEvent const *>(pDBEvents->enableEvents[i].GetPtr());
        NI_ASSERT(pEvent, "Invalid DB resource");
        if ( strcmp(pEvent->name.c_str(), eventName) == 0 )
        {
          EnableByEvent();
          break;
        }
      }
    }

    // check for disable event
    for (i = 0; i < pDBEvents->disableEvents.size(); ++i)
    {
      if ( pDBEvents->disableEvents[i]->GetObjectTypeID() == NDb::NamedSCEvent::typeId )
      {
        NDb::NamedSCEvent const *pEvent = dynamic_cast<NDb::NamedSCEvent const *>(pDBEvents->disableEvents[i].GetPtr());
        NI_ASSERT(pEvent, "Invalid DB resource");
        if ( strcmp(pEvent->name.c_str(), eventName) == 0 )
        {
          DisableByEvent();
          break;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SceneComponent::~SceneComponent()
{
	// Kill list of events
	while (pGroundHitEvents)
	{
		GroundHitEvent *pE = pGroundHitEvents;
		pGroundHitEvents = pGroundHitEvents->pNext;
		delete pE;
	}

  if ( child )
  {
    // release all children
    CObj<SceneComponent> it = child->rightBrother;
    while (it && it != child)
    {
      CObj<SceneComponent> next = it->rightBrother;

      it->leftBrother  = 0;
      it->rightBrother = 0;
      it->parent       = 0;

      it = next;
    }

    child->leftBrother  = 0;
    child->rightBrother = 0;
    child->parent       = 0;
    child = 0;
  }

  // destroy locators
  for (int i = 0; i < locators.size(); ++i)
  {
    delete locators[i];
  }
  locators.clear();

#ifdef SCENECOMPONENT_STATS
  if (groupFlags & GROUPFLAGS_REFLECTINWATER)
    s_numComponentsReflectInWater--;
  if (groupFlags & GROUPFLAGS_CASTSHADOW)
    s_numComponentsCastShadow--;
  s_numComponents--;
#endif // SCENECOMPONENT_STATS
}

void SceneComponent::ConstructWorldPlacement(const Placement& _parentPos, IScene *pScene)
{
  NI_ASSERT(_parentPos.IsValid(), NStr::StrFmt("Invalid parent place passed to scene component %s !", FormatDescription() ) );
  NI_ASSERT(offset.IsValid(), NStr::StrFmt("Invalid offset placement stored in scene component %s !", FormatDescription() ) );
	// Take only position from parent

  Placement parentPos = _parentPos;

	if (parentTransformUsage & NDb::ATTACHFLAGS_STAYINWORLD)
	{
		if ((parentTransformUsage & WORLDPLACE_ALREADY_UPDATED) == 0)
    {
      stayInWorldPlace = parentPos;
			parentTransformUsage |= WORLDPLACE_ALREADY_UPDATED;
    }
		else
			parentPos = stayInWorldPlace;
	}

  worldPlacement.rot = offset.GetPlacement().rot;

  if ( parentTransformUsage & NDb::ATTACHFLAGS_CANCELOFFSETSCALING )
  {
    CVec3 original;
    parentPos.rot.Rotate( &original, offset.GetOriginal().pos );
    
    CVec3 position;
    position = offset.GetPlacement().pos - offset.GetOriginal().pos;
    parentPos.rot.Rotate( &worldPlacement.pos, position );
    worldPlacement.pos.Mul( worldPlacement.pos, parentPos.scale );

    worldPlacement.pos += parentPos.pos;
    worldPlacement.pos += original;

    if ( locatorFlags & NDb::LOCATORATTACHFLAGS_CANCELNORMALLEVELLING )
    {
      worldPlacement.pos = parentPos.pos;

      CVec3 parent;
      CVec3 position = offset.GetPlacement().pos - offset.GetOriginal().pos;
      parent.Mul( parentPos.scale, position );

      worldPlacement.pos += parent;
      worldPlacement.pos += offset.GetOriginal().pos;
    }
  }
  else
  {
    parentPos.Transform(offset.GetPlacement().pos, worldPlacement.pos);

    if ( locatorFlags & NDb::LOCATORATTACHFLAGS_CANCELNORMALLEVELLING )
    {
      worldPlacement.pos = parentPos.pos;
      CVec3 parent;
      parent.Mul( parentPos.scale, offset.GetPlacement().pos );
      worldPlacement.pos += parent;
    }
  }

  switch(orientation)
  {
    case NDb::SCORIENTATION_CAMERA:
    {
      if (pScene)
      {
        // convert camera matrix to object world matrix (only rotation part matters)
        SHMatrix m = pScene->GetCamera()->GetViewMatrix();
        CVec3 t = m.GetY().AsVec3D();
        m._21 = m._31; m._22 = m._32; m._23 = m._33;
        m._31 = t.x;   m._32 = t.y;   m._33 = t.z;
        Transpose(&m, m);

        // for verification
        // SetLookAtZ(&m, VNULL3, pScene->GetCamera()->GetViewMatrix().GetZ().AsVec3D());

        worldPlacement.rot.FromEulerMatrix(m);
        worldPlacement.rot = worldPlacement.rot * offset.GetPlacement().rot;
      }
      break;
    }
    case NDb::SCORIENTATION_CAMERAFIXEDZ:
    {
      if (pScene)
      {
        // convert camera matrix to object world matrix (only rotation part matters)
        SHMatrix m = pScene->GetCamera()->GetViewMatrix();
        
        CVec3 zaxis = V3_AXIS_Z;
        CVec3 yaxis = m.GetZ().AsVec3D();
        CVec3 xaxis = yaxis ^ zaxis;
        Normalize(&xaxis);
        yaxis = zaxis ^ xaxis;

        m._11 = xaxis.x; m._21 = xaxis.y; m._31 = xaxis.z;
        m._12 = yaxis.x; m._22 = yaxis.y; m._32 = yaxis.z;
        m._13 = zaxis.x; m._23 = zaxis.y; m._33 = zaxis.z;

        worldPlacement.rot.FromEulerMatrix(m);
        worldPlacement.rot = worldPlacement.rot * offset.GetPlacement().rot;
      }
      break;
    }
    case NDb::SCORIENTATION_DEFAULT:
    {
      if (parentTransformUsage & NDb::ATTACHFLAGS_USEPARENTROTATION)
      {
        worldPlacement.rot = parentPos.rot * offset.GetPlacement().rot;
      }
      break;
    }
    default:
      NI_ALWAYS_ASSERT("Invalid SC orientation");
  }

  // scale
  if (parentTransformUsage & NDb::ATTACHFLAGS_USEPARENTSCALE)
  {
    worldPlacement.scale.Mul(parentPos.scale, offset.GetPlacement().scale);
  }
  else
  {
    worldPlacement.scale = offset.GetPlacement().scale;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::PassUpdate2Children( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
	if ( !child )
		return;

	child->Update( pars, parentPos, timeDiff );

	SceneComponent* it = child->GetBrother();
	while ( it && it != GetChild() )
	{
		it->Update( pars, parentPos, timeDiff );
		it = it->GetBrother();
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SceneComponent::UpdateBasics( UpdatePars &pars, const Placement& parentPos, float timeAdvance, float &timeDelta ) 
{
	// Ignore incoming time
	if ( (parentTransformUsage & NDb::ATTACHFLAGS_USEPARENTTIME) == 0 )
		timeAdvance = pars.timeDiff;

	if (!IsTraversable())
	{
		// Events that can enable component
		if (pGroundHitEvents && pars.pScene)
		{
			GroundHitEvent *pCurEvent = pGroundHitEvents;
			while (pCurEvent)
			{
				if (pCurEvent->activate && pCurEvent->HasHappen(pars.pScene, *this))
				{
					EnableByEvent();
					break;
				}
				pCurEvent = pCurEvent->pNext;
			}
		}
	}

  if ( !IsTraversable() )
  {
    if (timeController.GetTime() < 0.0f) // If we are in delay state - still update time
      timeController.Update(*this, timeAdvance, timeDelta);

    if ( !IsTraversable() )
      return false;
  }
  else
  {
  	// Update time
	  timeController.Update(*this, timeAdvance, timeDelta);
  }

	// Animate placement
	offset.Step(timeDelta);
	// Update world placement
	ConstructWorldPlacement(parentPos, pars.pScene);

	// Process events that can disable component
	if (pGroundHitEvents && pars.pScene)
	{
		GroundHitEvent *pCurEvent = pGroundHitEvents;
		while (pCurEvent)
		{
			if (!pCurEvent->activate && pCurEvent->HasHappen(pars.pScene, *this))
			{
				DisableByEvent();
				break;
			}
			pCurEvent = pCurEvent->pNext;
		}
	}

	// Animate materials
	MaterialUpdater updater(timeDelta);
	ForAllMaterials(updater);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::Update( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
	float timeDelta;
	if (!UpdateBasics(pars, parentPos, timeDiff, timeDelta))
		return;
	UpdateComponent(pars, parentPos, timeDelta);

	PassUpdate2Children(pars, worldPlacement, timeDelta);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Locator &SceneComponent::RegisterLocator(NDb::Locator const &l)
{
  Locator *locator = new Locator;
  locators.push_back(locator);
  locator->locator = l;
  locator->pSC = this;
  return *locator;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::SwapLocators(SceneComponent &sc)
{
  // exchange locators lists
  vector<Locator*> temp = locators;
  locators = sc.locators;
  sc.locators = temp;

  // restore component back-reference
  int i;
  for (i = 0; i < locators.size(); ++i)
  {
    locators[i]->pSC = this;
  }

  for (i = 0; i < sc.locators.size(); ++i)
  {
    sc.locators[i]->pSC = &sc;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::AddBrother( SceneComponent* _component )
{
	if ( !rightBrother )
	{
		rightBrother = _component;
		leftBrother = _component;
		_component->leftBrother = this;
		_component->rightBrother = this;
	}
	else
	{
		CObj<SceneComponent> olRB = rightBrother;
		rightBrother = _component;
		_component->leftBrother = this;
		_component->rightBrother = olRB;
		olRB->leftBrother = _component;
	}

  NI_ASSERT(rightBrother != this, NStr::StrFmt(" Invalid hierarchy %s", FormatDescription() ) );
  NI_ASSERT(_component->rightBrother != _component, NStr::StrFmt( "Invalid hierarchy %s", FormatDescription() ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::DetachFromSiblings()
{
	if ( rightBrother )
	{
		if (rightBrother == leftBrother)
		{
			rightBrother->leftBrother = 0;
			leftBrother->rightBrother = 0;
		}
		else
		{
			rightBrother->leftBrother = leftBrother;
			leftBrother->rightBrother = rightBrother;
		}

		leftBrother = 0;
		rightBrother = 0;
	}

  parent = 0;

  NI_ASSERT(rightBrother != this, NStr::StrFmt( "Invalid hierarchy %s", FormatDescription() ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::Attach( SceneComponent* toadd )
{
	toadd->parent = this;

	if ( child )
	{
		CObj<SceneComponent> it = toadd->rightBrother;
		while ( it && it != toadd )
		{
			CObj<SceneComponent> tosave = it->rightBrother;
			child->AddBrother( it );
			it = tosave;
		}

		child->AddBrother( toadd );
	}
	else
	{
		child = toadd;
	}

	toadd->OnAfterAttached();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::Detach()
{
	jointIdx = -1;

  if ( parent )
	{
		if ( parent->child == this )
		{
			if ( rightBrother )
			{
				parent->child = rightBrother;
			}
			else
			{
				parent->child = 0;
			}
		}

		DetachFromSiblings();

		parent = 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::SetupOtherEvents(const vector<NDb::Ptr<NDb::SCEvent>> &events, bool enable)
{
	for (int i = 0; i < events.size(); ++i)
	{
		const NDb::Ptr<NDb::SCEvent> &pE = events[i];
		if (!pE || pE->GetObjectTypeID() != NDb::GroundHitSCEvent::typeId)
			continue;
		// Create event & add to list
		const NDb::GroundHitSCEvent *pGHE = static_cast<const NDb::GroundHitSCEvent*>(pE.GetPtr());
		GroundHitEvent *pNewEvent = new GroundHitEvent(enable, pGHE->heightAboveGround);
		pNewEvent->pNext = pGroundHitEvents;
		pGroundHitEvents = pNewEvent;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::SetupAnimEvents(const vector<NDb::Ptr<NDb::SCEvent>> &events, AnimationCallback _callback, void* _userData, bool findFirst)
{
  bool hasAnimEvents = false;

  for (int i = 0; i < events.size(); ++i)
  {
    const NDb::Ptr<NDb::SCEvent> &pE = events[i];

    if (pE && pE->GetObjectTypeID() == NDb::AnimationSCEvent::typeId)
      hasAnimEvents = true;
  }

  if ( !hasAnimEvents )
    return;

  // Find root
  SceneComponent *root = this;
  // Get animation graphs
  DiAnimGraph* pAG = root->GetAG(true);
  DiAnimGraph* pAdditionalAG = root->GetAG(false);

  if ( findFirst )
  {
    while ( !pAG && root->GetParent() )
    {
      root = root->GetParent();
      pAG = root->GetAG(true);
      pAdditionalAG = root->GetAG(false);
    }
  }
  else
  {
    while ( root->GetParent() )
      root = root->GetParent();
    pAG = root->GetAG(true);
    pAdditionalAG = root->GetAG(false);
  }

  NI_DATA_VERIFY(pAG, NStr::StrFmt("Scene component(%s) that uses animation events should have AnimatedSceneComponent as a root(%s) of tree", FormatDescription(), GetFormattedDbId(root->GetDBID()).c_str() ), return; )

  for (int i = 0; i < events.size(); ++i)
	{
		const NDb::Ptr<NDb::SCEvent> &pE = events[i];
		if (!pE || pE->GetObjectTypeID() != NDb::AnimationSCEvent::typeId)
			continue;

		const NDb::AnimationSCEvent *pAE = static_cast<const NDb::AnimationSCEvent*>(pE.GetPtr());

		SetupAnimEvent(pAG, *pAE, _callback, _userData);

    if( pAdditionalAG )
      SetupAnimEvent(pAdditionalAG, *pAE, _callback, _userData);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::OnAfterAttached()
{
	// Control events
	if (!pDBEvents)
		return;

	// Setup actions
	SetupAnimEvents(pDBEvents->enableEvents, ActivateSceneComponent, this, false);
	SetupAnimEvents(pDBEvents->disableEvents, DeactivateSceneComponent, this, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SceneComponent::GetPureAnimLength()
{
	struct MaxMaterialLenFinder : public Render::IMaterialProcessor
	{
		MaxMaterialLenFinder() : animLen(0.0f) {}
		virtual void operator()(Render::BaseMaterial &material) { animLen = max(animLen, material.GetAnimLength()); }
		float animLen;
	} f;

	ForAllMaterials(f);

	NI_ASSERT( f.animLen<1000.0f && offset.EvaluateAnimationLength()<1000.0f, NStr::StrFmt( "Bad animation length %s", GetDBID().GetFileName() ) );
	return max( offset.EvaluateAnimationLength(), f.animLen );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SceneComponent::CalculateTransformedAnimLength() const
{
  return timeController.EvaluateAnimLength( *this ) / GetParentSpeedCoeff();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SceneComponent::GetSubTreeAnimLength() const
{
  float time = CalculateTransformedAnimLength();

  SceneComponent *it = GetChild();
  
  if (it)
  {
    do
    {
      time = Max(time, it->GetSubTreeAnimLength());
      it = it->GetBrother();
    } while (it && it != GetChild());
  }

  return time;
}


float SceneComponent::GetParentSpeedCoeff() const
{
  float res = 1.0f;
  SceneComponent* p = parent;
  while ( p )
  {
    res *= p->timeController.GetSpeed();
    p = p->parent;
  }
  return res;
}


float SceneComponent::GetCurTime() const
{
  return GetAnimatedTime() / timeController.GetSpeed() / GetParentSpeedCoeff();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::SetAnimatedsTime(float time)
{
	offset.SetStartTime(time);

	struct MaterialReinitter : public Render::IMaterialProcessor
	{
		float t;
		
		MaterialReinitter(float t_) : t(t_) {}
		virtual void operator()(Render::BaseMaterial &material) { material.SetStartTime(t); }
	} f(time);
	ForAllMaterials(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::DisableStrongWithWaitingForFinish()
{
	timeController.Finish(*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::SetTimeController( const NDb::Ptr<NDb::TimeController> pTimeController )
{
	timeController.Set(pTimeController);
	timeController.Reinit(*this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::Ptr<NDb::TimeController> SceneComponent::GetTimeControllerDesc() const
{
  return timeController.GetDBDesc();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SceneComponent::GetAnimatedTime() const
{
  return timeController.GetTime();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float SceneComponent::CalculateSortingValue(const Render::AABB &worldAABB, const Render::SceneConstants &sceneConstants)
{
	CVec3 dir = worldAABB.center - CVec3(sceneConstants.invView.xw, sceneConstants.invView.yw, sceneConstants.invView.zw);
	return dir * CVec3(sceneConstants.invView.xz, sceneConstants.invView.yz, sceneConstants.invView.zz);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)
{
  MaterialColorChanger changer(mul, add);
  ForAllMaterials(changer);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneComponent::Dump() const // Debug functionality
{
	DebugTrace("  %s @ %s state:", typeid(*this).name(), GetFormattedDbId(dbid).c_str());
	DebugTrace("    disabled     : %d %s", disabledCount & ~STRONG_DISABLE_FLAG, 
																		    (disabledCount & STRONG_DISABLE_FLAG) != 0 ? "strong" : "");
	DebugTrace("    time         : %f", timeController.GetTime());
	DebugTrace("    speed        : %f", timeController.GetSpeed());
	DebugTrace("    cycles       : %d", timeController.GetCyclesToLoop());
	DebugTrace("    parent xform : %08X", parentTransformUsage);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SCENECOMPONENT_STATS
void SceneComponent::StatisticsGet(unsigned long* pNumTotal, unsigned long* pNumShadows, unsigned long* pNumReflections)
{
  *pNumReflections = s_numComponentsReflectInWater;
  *pNumShadows = s_numComponentsCastShadow;
  *pNumTotal = s_numComponents;
}
void SceneComponent::StatisticsRenderGet(unsigned long* pNumTotal, unsigned long* pNumShadows, unsigned long* pNumReflections)
{
  *pNumReflections = s_numRenderedReflectInWater;
  *pNumShadows = s_numRenderedCastShadow;
  *pNumTotal = s_numRendered;
}
void SceneComponent::StatisticsRenderReset()
{
  s_numRendered = 0;
  s_numRenderedCastShadow = 0;
  s_numRenderedReflectInWater = 0;
}
void SceneComponent::StatisticsRenderAdd(int groupFlagsFilter)
{
  s_numRendered++;
  if (groupFlagsFilter == GROUPFLAGS_CASTSHADOW)
    s_numRenderedCastShadow++;
  else if (groupFlagsFilter == GROUPFLAGS_REFLECTINWATER)
    s_numRenderedReflectInWater++;
}
#endif // SCENECOMPONENT_STATS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Locator::MakeAttachementPlacement(Placement &pl) const
{
  if (locator.jointName.empty())
  {
    pl = pSC->GetWorldPlacement();
  }
  else
  {
    if (!pSC->RetrieveJointPlacement(locator.jointName, pl))
      pl = pSC->GetWorldPlacement();

		if ( !(locator.flags & NDb::LOCATORATTACHFLAGS_USEJOINTPOSITION) )
		{
			pl.pos = VNULL3;
		}
		if ( !(locator.flags & NDb::LOCATORATTACHFLAGS_USEJOINTROTATION) )
		{
			pl.rot = QNULL;
		}
		if ( !(locator.flags & NDb::LOCATORATTACHFLAGS_USEJOINTSCALE) )
		{
			pl.scale = CVec3( 1.0f, 1.0f, 1.0f );
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Locator::CalculateWorldMatrix(Matrix43 &m) const
{
  Placement pl;
  MakeAttachementPlacement(pl);

  pl.GetMatrix(&m);
  m = m * locator.offset2.GetMatrix();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Locator::CalculateWorldPlacement(Placement &pl) const
{
  MakeAttachementPlacement(pl);
  pl += locator.offset2.GetPlace();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Locator::CalculateWorldPosition(CVec3 &pos) const
{
  Placement pl;
  MakeAttachementPlacement(pl);

  const Matrix43 &m = locator.offset2.GetMatrix();
  pl.Transform( CVec3(m._14, m._24, m._34), pos );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Locator::DebugRender( Render::IDebugRender* _debugRenderer ) const
{
  using namespace Render;

  // build L2W matrix
  Matrix43 m;
  CalculateWorldMatrix(m);

  static Render::CrossColorTable colorTable = { { Color(0xFF2F0000UL), Color(0xFF002F00UL), Color(0xFF00002FUL) }, 
  { Color(0xFFFF0000UL), Color(0xFF00FF00UL), Color(0xFF0000FFUL) } };

  if ( _debugRenderer )
    _debugRenderer->DrawCross3D( m, 1.f, 0.7f, colorTable, true );
}

}
