#include "stdafx.h"
#include "soundui.h"

namespace 
{
  bool g_bDisableAsks = false;
}

namespace NSound
{
Sound2D::Sound2D (const string fileName, int _cycleCount, float _startOffset)
  : cycleCount(_cycleCount)
  , startOffset(_startOffset)
{
  desc.soundFilename = fileName;
  desc.looped = _cycleCount == 0;
  offset = 0;
  soundID = NSoundScene::INVALID_SOUND_ID;
}

float Sound2D::Play()
{
  float time;
  soundID = NSoundScene::PlaySound(desc, &time);

  string ouput = string("Invalid sound file: <") + desc.soundFilename + ">";
  NI_DATA_VERIFY(NSoundScene::INVALID_SOUND_ID != soundID, ouput.c_str(), return 0.f)

  if (time < offset)
  {
    NSoundScene::DeleteSound(soundID);
    time = 0.f;
  }

  return time;
}

AskCommands::AskCommands() : fmodEvent(0)
{
  fmodEvent = NSoundScene::CreateFMODEvent();
}

AskCommands::~AskCommands()
{
  if ( fmodEvent )
  {
    Stop(true);
    ReleaseFMODEvent( fmodEvent );
    fmodEvent = 0;
  }
}

bool AskCommands::IsAllreadyPlayed()
{
  if ( fmodEvent )
    return fmodEvent->IsAllreadyPlayed();

  return false;
}

bool AskCommands::Stop( bool immediately = false )
{
  if ( fmodEvent )
    return fmodEvent->Stop( immediately );

  return false;
}

bool AskCommands::PlaySound()
{
  if(g_bDisableAsks)
    return false;

  if ( fmodEvent )
    return fmodEvent->PlaySound();

  return false;
}

void AskCommands::Init ( const NDb::DBFMODEventDesc &_desc )
{
  if ( fmodEvent )
    fmodEvent->Init( _desc );
}

float AskCommands::GetAskTime()
{
  if (fmodEvent)
      return fmodEvent->GetDuration();

  return 0;
}
} // end of namespace NSound

NI_DEFINE_REFCOUNT(NSound::AskCommands);

REGISTER_DEV_VAR( "disable_ask_sounds", g_bDisableAsks, STORAGE_NONE );
