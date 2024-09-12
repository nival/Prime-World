#pragma once

#include "EaselSoundsInterface.h"
#include "EaselFModEvent.h"

namespace NDb
{
  struct DBEaselSoundsData;
}

namespace FMOD
{
  class Event;
}

namespace NSoundScene
{
  class FMODGroup;
}

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// sound processor class, working with the FMod Designer events
//
//////////////////////////////////////////////////////////////////////////
class EaselEventSounds : public IEaselSounds, public CObjectBase
{
  OBJECT_METHODS( 0x9D6BBBC9, EaselEventSounds );

  typedef nstl::vector<CObj<EaselFModEvent>> SoundEvents;
  typedef SoundEvents::iterator                   SEIter;

public:
  EaselEventSounds();
  ~EaselEventSounds();

  // common init/uninit
  virtual int InitSounds( const NDb::DBEaselSoundsData* _data );
  virtual int UninitSounds();
  
  // sound playback methods
  virtual int PlaySound(NDb::EEaselSoundType soundType);
  virtual int StopSound(NDb::EEaselSoundType soundType);
  virtual int PauseSound(NDb::EEaselSoundType soundType,bool _pause);
  virtual int StopAllSounds();
  virtual int StopMusic( const bool stop );

  virtual int PauseAllPlayingSounds(bool _fPause);

  virtual void OnGamePaused();
  virtual void OnGameResumed();

private:
  EaselEventSounds(const EaselEventSounds &rhs);
  EaselEventSounds& operator=(const EaselEventSounds &rhs);

  NSoundScene::FMODGroup *pMinigameGrp;  

  void PausePlayingSounds();
  void UnPausePlayingSounds();

  bool inited;

  SoundEvents soundEvents;

protected:

};

//////////////////////////////////////////////////////////////////////////
//
// NULL sounds processor
//
//////////////////////////////////////////////////////////////////////////
class EaselEventNullSounds : public IEaselSounds, public CObjectBase
{
  OBJECT_METHODS( 0x9D6BBBCA, EaselEventNullSounds );

public:
  EaselEventNullSounds();
  ~EaselEventNullSounds();

  // common init/uninit
  virtual int InitSounds( const NDb::DBEaselSoundsData* _data );
  virtual int UninitSounds();

  // sound playback methods
  virtual int PlaySound(NDb::EEaselSoundType soundType);
  virtual int StopSound(NDb::EEaselSoundType soundType);
  virtual int PauseSound(NDb::EEaselSoundType soundType,bool _pause);
  virtual int StopAllSounds();
  virtual int StopMusic(const bool stop);

  virtual int PauseAllPlayingSounds(bool _fPause);

  virtual void OnGamePaused() {}
  virtual void OnGameResumed() {}
};

}