#include "stdafx.h"
#include "EaselFModEvent.h"

#include "DBEasel.h"

#include "../Sound/EventScene.h"

namespace PF_Minigames
{

//const nstl::string g_FMODProject  = "PF";
//const nstl::string g_FMODCatagory = "Minigame02";

//////////////////////////////////////////////////////////////////////////
//
// class FModEvent implementation
//
//////////////////////////////////////////////////////////////////////////
EaselFModEvent::EaselFModEvent(NDb::EEaselSoundType _type, FMOD::Event *_pEvent)
: pFMODEvent(_pEvent)
, fIsLooped(false)
, eventLenght(0)
, soundType(_type)
{
  //NI_ASSERT(pFMODEvent != 0,"FModEvent - passed FMOD::Event ptr cannot be null");
  if(pFMODEvent != 0)
  {
    if(NSoundScene::GetEventLength(pFMODEvent,eventLenght, true) == true && eventLenght == -1)
      fIsLooped = true;
  } 
}

EaselFModEvent::~EaselFModEvent()
{
  // Pavel<GnoM>Cherniavski
  // need not to stop event playing due to the possibility of
  // having another FModEvent copy with the same FMOD::Event
  // who can be playing
  
  fIsLooped   = false;
  eventLenght = 0;

  pFMODEvent = 0;
}

bool EaselFModEvent::Play()
{
  if(pFMODEvent == 0)
    return false;

  if ( fIsLooped  )
  {
    if ( IsPlaying()  )
      return true;
    else
      return NSoundScene::EventStart(pFMODEvent);
  }
  else
  {
    Stop(true);
    return NSoundScene::EventStart(pFMODEvent);
  }
}

bool EaselFModEvent::Stop(bool fImmediately /*= true*/)
{
  if(pFMODEvent == 0)
    return false;

  if ( IsPlaying()  )
    return NSoundScene::EventStop(pFMODEvent,fImmediately);
  
  return true;
}

bool EaselFModEvent::Pause(bool _pause)
{
  if(pFMODEvent == 0)
    return true;

  return NSoundScene::EventPause(pFMODEvent,_pause);
}

bool EaselFModEvent::IsPlaying() const
{
  if(pFMODEvent == 0)
    return false;

  return NSoundScene::IsEventPlaying(pFMODEvent);
}

bool EaselFModEvent::IsPaused() const
{
  if(pFMODEvent == 0)
    return false;

  return NSoundScene::IsEventPaused(pFMODEvent);
}

//////////////////////////////////////////////////////////////////////////
//
// class EaselFModEventFactory implementation
//
//////////////////////////////////////////////////////////////////////////
EaselFModEventFactory::EaselFModEventFactory( const NDb::DBEaselSoundsData* _data, NSoundScene::FMODGroup *_group )
: pMinigameGrp(_group)
{
  soundsData = _data;
}

EaselFModEventFactory::~EaselFModEventFactory()
{

}

EaselFModEvent* EaselFModEventFactory::CreateEvent(NDb::EEaselSoundType _eventType)
{
  if(!IsValid(soundsData) || pMinigameGrp == 0 || !pMinigameGrp->IsValid() )
    return CreateEmptyEvent(_eventType);

  //FMOD::Event *pEvent = NSoundScene::GetEvent(g_FMODProject,g_FMODCatagory,soundsData->sounds[_eventType].eventName);
  
  if ( soundsData->sounds[_eventType].eventName.empty() )
    return CreateEmptyEvent(_eventType);
  FMOD::Event *pEvent = NSoundScene::GetEvent(pMinigameGrp->GetGroup(),soundsData->sounds[_eventType].eventName.c_str());
  if(pEvent == 0)
    return CreateEmptyEvent(_eventType);

  return new EaselFModEvent(_eventType,pEvent);
}

EaselFModEvent* EaselFModEventFactory::CreateEmptyEvent(NDb::EEaselSoundType _eventType)
{
  return new EaselFModEvent(_eventType,0);
}

}

BASIC_REGISTER_CLASS( PF_Minigames::EaselFModEvent )
