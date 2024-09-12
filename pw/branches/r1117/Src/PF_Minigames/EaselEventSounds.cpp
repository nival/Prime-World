#include "stdafx.h"
#include "EaselEventSounds.h"

#include "../Sound/EventScene.h"

#include "LuxDef.h"

namespace PF_Minigames
{

const nstl::string g_FMODProject  = "PF";
const nstl::string g_FMODCatagory = "Minigame02";

//////////////////////////////////////////////////////////////////////////
//
// class EaselEventSounds implementation
//
//////////////////////////////////////////////////////////////////////////
EaselEventSounds::EaselEventSounds()
: IEaselSounds()
, inited(false)
, pMinigameGrp(0)
{
 
}

EaselEventSounds::~EaselEventSounds()
{
  UninitSounds();
}

int EaselEventSounds::InitSounds( const NDb::DBEaselSoundsData* _data )
{
  NI_VERIFY( !inited, "EaselEventSounds: already inited", return LUX_ALREADY_INIT );

  int numEvents = NDb::KnownEnum<NDb::EEaselSoundType>::SizeOf();

  pMinigameGrp = NSoundScene::CreateFMODGroup();
  pMinigameGrp->Init( g_FMODProject, g_FMODCatagory );
  if ( !pMinigameGrp->IsValid() )
    return LUX_ERROR;    

  EaselFModEventFactory factory( _data, pMinigameGrp );

  soundEvents.reserve(numEvents);
  for(int i=0; i<numEvents; i++)
  {
    CObj<EaselFModEvent> fmodEvent = factory.CreateEvent( (NDb::EEaselSoundType)i );
    soundEvents.push_back(fmodEvent);  // sorted by order
  }

  inited = true;

  StopMusic(false);

  return LUX_OK;
}

int EaselEventSounds::UninitSounds()
{
  if(inited == false)
    return LUX_OK;

  StopAllSounds();
  soundEvents.clear();

  NSoundScene::ReleaseFMODGroup(pMinigameGrp);
  
  inited = false;
  return LUX_OK;
}

int EaselEventSounds::PlaySound(NDb::EEaselSoundType soundType)
{
  if(inited == false)
    return LUX_NOT_INIT;

  soundEvents[soundType]->Play();
  return LUX_OK;
}

int EaselEventSounds::StopSound(NDb::EEaselSoundType soundType)
{
  if(inited == false)
    return LUX_NOT_INIT;

  soundEvents[soundType]->Stop();
  return LUX_OK;
}

int EaselEventSounds::PauseSound(NDb::EEaselSoundType soundType,bool _pause)
{
  if(inited == false)
    return LUX_NOT_INIT;

  soundEvents[soundType]->Pause(_pause);
  return LUX_OK;
}

int EaselEventSounds::StopAllSounds()
{
  if(inited == false)
    return LUX_NOT_INIT;

  SEIter soundIter = soundEvents.begin();
  for(; soundIter != soundEvents.end(); ++soundIter)
  {
    (*soundIter)->Stop();
  }

  return LUX_OK;
}

int EaselEventSounds::StopMusic( const bool stop ) 
{ 
  if( !stop )
    NSoundScene::UnPauseMusic();
  else
    NSoundScene::PauseMusic();
  
  return LUX_OK; 
};

int EaselEventSounds::PauseAllPlayingSounds(bool _fPause)
{
  if(inited == false)
    return LUX_NOT_INIT;

  if ( _fPause  )
    PausePlayingSounds();
  else
    UnPausePlayingSounds();
  
  return LUX_OK;
}

void EaselEventSounds::PausePlayingSounds()
{
  SEIter soundIter = soundEvents.begin();
  for(; soundIter != soundEvents.end(); ++soundIter)
  {
    if ( (*soundIter)->IsPlaying()  )
      (*soundIter)->Pause(true);
  }
}

void EaselEventSounds::UnPausePlayingSounds()
{
  SEIter soundIter = soundEvents.begin();
  for(; soundIter != soundEvents.end(); ++soundIter)
  {
    if ( (*soundIter)->IsPaused()  )
      (*soundIter)->Pause(false);
  }
}

void EaselEventSounds::OnGamePaused()
{
  PauseAllPlayingSounds(true);
  StopMusic(true);

  // workaround ... for medals (temp)
  PauseSound(NDb::EASELSOUNDTYPE_RESULT_GOLD_MEDAL,false);
  PauseSound(NDb::EASELSOUNDTYPE_RESULT_SILVER_MEDAL,false);
  PauseSound(NDb::EASELSOUNDTYPE_LEVEL_SCROLL_END,false);
}

void EaselEventSounds::OnGameResumed()
{
  StopMusic(false);
  PauseAllPlayingSounds(false);
}


//////////////////////////////////////////////////////////////////////////
//
// class EaselEventNullSounds implementation
//
//////////////////////////////////////////////////////////////////////////
EaselEventNullSounds::EaselEventNullSounds() : IEaselSounds()
{

}

EaselEventNullSounds::~EaselEventNullSounds()
{

}

int EaselEventNullSounds::InitSounds( const NDb::DBEaselSoundsData* _data )
{
  return LUX_OK;
}

int EaselEventNullSounds::UninitSounds()
{
  return LUX_OK;
}

int EaselEventNullSounds::PlaySound(NDb::EEaselSoundType soundType)
{
  return LUX_OK;
}

int EaselEventNullSounds::StopSound(NDb::EEaselSoundType soundType)
{
  return LUX_OK;
}

int EaselEventNullSounds::PauseSound(NDb::EEaselSoundType soundType,bool _pause)
{
  return LUX_OK;
}

int EaselEventNullSounds::StopAllSounds()
{
  return LUX_OK;
}

int EaselEventNullSounds::StopMusic(const bool stop)
{ 
  return LUX_OK;
}

int EaselEventNullSounds::PauseAllPlayingSounds(bool _fPause)
{
  return LUX_OK;
}

}

REGISTER_SAVELOAD_CLASS_NM( EaselEventNullSounds, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselEventSounds, PF_Minigames )
