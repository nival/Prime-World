#pragma once

#include "DBEasel.h"

namespace NDb
{
  struct DBEaselSoundsData;
}

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// internal EaselSound interface
//
//////////////////////////////////////////////////////////////////////////
class IEaselSounds : public IObjectBase
{
public:
  IEaselSounds() {};
  virtual ~IEaselSounds() {};

  virtual int InitSounds( const NDb::DBEaselSoundsData* _data ) = 0;
  virtual int UninitSounds()                                         = 0;

  virtual int PlaySound(NDb::EEaselSoundType soundType)              = 0;
  virtual int StopSound(NDb::EEaselSoundType soundType)              = 0;
  virtual int PauseSound(NDb::EEaselSoundType soundType,bool _pause) = 0;
  virtual int StopAllSounds()                                        = 0;
  virtual int StopMusic(const bool stop)                             = 0;

  virtual int PauseAllPlayingSounds(bool _fPause)       = 0;

  virtual void OnGamePaused() = 0;
  virtual void OnGameResumed() = 0;
};


}