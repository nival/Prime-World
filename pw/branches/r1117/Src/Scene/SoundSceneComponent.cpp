#include "stdafx.h"
#include "SoundSceneComponent.h"
#include "RenderableScene.h"
#include "../Render/debugrenderer.h"

#include "../System/InlineProfiler.h"

namespace
{
  float s_timeReset = 4.f;
}
namespace NScene
{

SoundSceneComponent::SoundSceneComponent( const NDb::DBSoundSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos )
: SceneComponent(pObject, pObj, pos), isInited(false), soundEvent(0), timerInterval( pObject->timeInterval ), timer(0.0f)
{
  if (!pObject->desc.projectName.length() || !pObject->desc.eventName.length())
  {
    systemLog( NLogg::LEVEL_ASSERT ) << "Sound component in " << pObject->GetDBID().GetFileName() << " file has sound with empty project/event description" << endl; 
  }

  desc.projectName = pObject->desc.projectName;
  desc.groupName   = pObject->desc.groupName;
  desc.eventName   = pObject->desc.eventName;

  position = pos;

  int _length = 0;
  NSoundScene::GetEventLength(NSoundScene::GetEvent(desc), _length, true);
  soundLength = ((float)_length)/1000.0f;
}

void SoundSceneComponent::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  NI_PROFILE_FUNCTION

  if ( pars.isUnfreeze )
  {
    isInited = true;
    return;
  }

  if ( fabs2(position.pos - parentPos.pos) > 0.1f )
  {
    position = parentPos;
    if ( isInited )
    {
      NSoundScene::SetEventPos( soundEvent, &position.pos );
    }
  }

  if (timeDiff > s_timeReset)
  {
    NSoundScene::EventStop(soundEvent);
    soundEvent = 0;                              
    isInited = false;
  }

  timer += timeDiff;

  if (!isInited && timer > timerInterval && pars.isClientVisible && !IsHide())
  {
    soundEvent = NSoundScene::EventStart( desc, position.pos );
    isInited = true;
    timer = 0.0f;
  }
}

void SoundSceneComponent::Reinit()
{
	SceneComponent::Reinit();
  if (isInited)
  {
    NSoundScene::EventStop(soundEvent);
    soundEvent = 0;                              
    isInited = false;
  }
}

void SoundSceneComponent::Deinit()
{
  SceneComponent::Deinit();

  if (isInited)
  {
    NSoundScene::EventStop(soundEvent);
    soundEvent = 0;                              
    isInited = false;
  }
}

void SoundSceneComponent::RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants )
{
	//if (Need2DrawEntitiesWithoutVisual())
	//{
	//	Render::DebugRenderer::DrawBox3D(worldPlacement, 1.0f, Render::Color(0, 0xFF, 0), true);
	//}
}

void SoundSceneComponent::ForceSoundPlay()
{
  if (isInited)
  {
    NSoundScene::EventStop(soundEvent);
    soundEvent = 0;                              
  }

  soundEvent = NSoundScene::EventStart( desc, position.pos );
  isInited = true;
}

float SoundSceneComponent::GetPureAnimLength()
{
	NI_ASSERT( soundLength<1000.0f, NStr::StrFmt( "Bad animation length %s", GetDBID().GetFileName() ) );
  return Max(SceneComponent::GetPureAnimLength(), soundLength);
}

SoundSceneComponent::~SoundSceneComponent()
{
  if (isInited)
  {
    NSoundScene::EventStop(soundEvent);
    soundEvent = 0;                              
    isInited = false;
  }
}

void SoundSceneComponent::OnTraversibleChanged()
{
  if ( disabledCount > 0 && isInited )
  {
    NSoundScene::EventStop(soundEvent);
    soundEvent = 0;                              
    isInited = false;
  }
}
}
