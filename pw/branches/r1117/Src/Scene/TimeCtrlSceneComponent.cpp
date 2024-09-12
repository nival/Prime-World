#include "stdafx.h"
#include "DiAnGr.h"
#include "AnimatedSceneComponent.h"
#include "TimeCtrlSceneComponent.h"

namespace NScene
{

namespace
{

DiInt32 ActivateCB(DiAnGrCallbackParams const &cpParams)
{
  ((TimeCtrlSceneComponent*)cpParams.vpUserData)->Activate();
  return DIOBJMSG_CONTINUE;
}

DiInt32 DeactivateCB(DiAnGrCallbackParams const &cpParams)
{
  ((TimeCtrlSceneComponent*)cpParams.vpUserData)->Deactivate();
  return DIOBJMSG_CONTINUE;
}

}

void TimeCtrlSceneComponent::OnAfterAttached()
{
  // initialize callbacks
  for (int i = 0; i < pDBObject->activateEvents.size(); ++i)
  {
    NDb::DBAnimEvent const &evt = pDBObject->activateEvents[i];
    SetupTriggeredAction( evt.type, evt.name.c_str(), evt.animParam, ACTION_ACTIVATE );
  }

  for (int i = 0; i < pDBObject->deactivateEvents.size(); ++i)
  {
    NDb::DBAnimEvent const &evt = pDBObject->deactivateEvents[i];
    SetupTriggeredAction( evt.type, evt.name.c_str(), evt.animParam, ACTION_DEACTIVATE );
  }
}

void TimeCtrlSceneComponent::Update( IScene *pScene, const Placement& parentPos, Render::AABB &objectAABB, float timeDiff )
{
  if (duration < 0.f)
  {
    // calculate duration
    duration = GetSubTreeAnimLength();
    loopTime = duration - pDBObject->fadeInTime - pDBObject->fadeOutTime;
  }

  lastUpdateLocalTime = curLocalTime;

	float timeDelta;
	UpdateBasics( parentPos, timeDiff, timeDelta );

  if (activeState != ST_INACTIVE)
  {
    curLocalTime += timeDelta;

    // update active state
    switch (activeState)
    {
      case ST_PLAY:
      {
        if (numLoopsToPlay >= 0)
        {
          if (loopTime > 0.f)
          {
            while (curLocalTime > pDBObject->fadeInTime + loopTime)
            {
              curLocalTime -= loopTime;
              ++numLoops;
            }         
          }

          if (numLoops >= numLoopsToPlay)
          {
            activeState = ST_FADE_OUT;
          }
        }
        break;
      }
      case ST_FADE_OUT:
      {
        if (curLocalTime > pDBObject->fadeInTime + loopTime + pDBObject->fadeOutTime)
        {
          // time to deactivate
          curLocalTime = pDBObject->fadeInTime + loopTime + pDBObject->fadeOutTime;
          activeState = ST_INACTIVE;

          if (onDeactivateCB)
          {
            onDeactivateCB(*this, pUserData);
          }
        }
        break;
      }
    }
  }
  
  curLocalTime = Clamp(curLocalTime, 0.f, duration);

  // update sub-tree
  if ( child )
  {
	  float timeDiffNew = curLocalTime - lastUpdateLocalTime;
    if (timeDiffNew < 0)
    {
      timeDiffNew += duration;
      NI_ASSERT(timeDiffNew > 0.0f, "Logic failed in TimeCtrlComp!");
    }
    child->Update( pScene, worldPlacement, objectAABB, timeDiffNew );

	  SceneComponent* it = child->GetBrother();
	  while (it && it != GetChild() )
	  {
		  it->Update( pScene, worldPlacement, objectAABB, timeDiffNew );
		  it = it->GetBrother();
	  }
  }
}

void TimeCtrlSceneComponent::Activate()
{
  if (activeState != ST_INACTIVE)
  {
    return;
  }

  activationTime = timeController.GetTime();
  lastUpdateLocalTime = curLocalTime = 0.f;
  numLoops = 0;
  
  if (loopTime > 0.f)
  {
    numLoopsToPlay = pDBObject->maxNumLoops;
  }
  else
  {
    numLoopsToPlay = -1; // infinite
  }
  
  activeState = ST_PLAY;
}

void TimeCtrlSceneComponent::Deactivate()
{
  if (activeState != ST_PLAY)
  {
    return;
  }

  // current loop is the last one
  numLoopsToPlay = numLoops;
}

bool TimeCtrlSceneComponent::SetupTriggeredAction(NDb::EAnimEventType evt, char const *name, float param, Action act)
{
  DiAnimGraph *graph = GetAnimGraph();
  if (!graph)
  {
    return false;
  }

  DiAnGrCallback cb;

  switch (act)
  {
    case ACTION_ACTIVATE:   cb = ActivateCB; break;
    case ACTION_DEACTIVATE: cb = DeactivateCB; break;
    default: return false;
  }

  switch (evt)
  {
    case NDb::ANIMEVENTTYPE_NODEENTER:
    {
      int id = graph->GetNodeIDByName(name);
      if (id < 0)
      {
        return false;
      }
      // register callback on entering into anim graph node
      return graph->RegisterCallback(DIANGR_NODE, id, cb, DIANGR_CF_ELEMENT_ENTER, this);
    }
    case NDb::ANIMEVENTTYPE_NODELEAVE:
    {
      int id = graph->GetNodeIDByName(name);
      if (id < 0)
      {
        return false;
      }
      // register callback on leaving anim graph node
      return graph->RegisterCallback(DIANGR_NODE, id, cb, DIANGR_CF_ELEMENT_LEAVE, this);
    }
    case NDb::ANIMEVENTTYPE_NODEPARAM:
    {
      int id = graph->GetNodeIDByName(name);
      if (id < 0)
      {
        return false;
      }
      // register callback on exact param in anim graph node
      return graph->RegisterCallback(DIANGR_NODE, id, cb, DIANGR_CF_EXACT_PARAM, this, param);
    }
    case NDb::ANIMEVENTTYPE_MARKER:
    {
      const DiAnGrMarker* marker = graph->FindMarkerByName(name);
      if (!marker)
      {
        return false;
      }
      return graph->RegisterCallback(*marker, cb, this);
    }
  }

  return false;
}

// find "main" anim graph of the whole SceneComponent tree
DiAnimGraph *TimeCtrlSceneComponent::GetAnimGraph()
{
  // find root
  SceneComponent *root = this;
  while ( root->GetParent() )
  {
    root = root->GetParent();
  }

  AnimatedSceneComponent *asc = dynamic_cast<AnimatedSceneComponent*>(root);
  
  if (!asc)
  {
    return NULL;
  }
  
  return asc->GetAnimGraph();
}

} // namespace NScene
