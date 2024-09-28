#include "StdAfx.h"
#include "QueueSoundPlayer.h"

namespace 
{
  bool CompareElements (const NGameX::QueueElement & a, const NGameX::QueueElement & b) 
  { 
    if (a.isStarted)
      return false;

    if (b.isStarted)
      return true;

    return (a.priority<b.priority); 
  }

  const int MaxQueueSize = 4;
}

namespace NGameX
{

void QueueSoundPlayer::StartTopSoundIfNeeded()
{
  if (soundQueue.empty())
    return;

  QueueElement & topSound = soundQueue.back();

  if (!topSound.isStarted)
  {
    topSound.isStarted = true;
    topSound.sound->PlaySound();
  }
}

void QueueSoundPlayer::AddSoundToQueue( const NDb::DBFMODEventDesc &desc, int priority )
{
  if (soundQueue.size()>= MaxQueueSize)
    return;

  QueueElement newElement(desc, priority);
  soundQueue.push_back(newElement);
  nstl::sort(soundQueue.begin(), soundQueue.end(), CompareElements);
 
  StartTopSoundIfNeeded();
}

void QueueSoundPlayer::AddAskToQueue( NSound::AskCommands *ask, int priority )
{
  if (soundQueue.size()>= MaxQueueSize)
    return;

  QueueElement newElement(ask, priority);
  soundQueue.push_back(newElement);
  nstl::sort(soundQueue.begin(), soundQueue.end(), CompareElements);
 
  StartTopSoundIfNeeded();
}

void QueueSoundPlayer::Update( float dt )
{
  if (soundQueue.empty())
    return;

  QueueElement & topSound = soundQueue.back();
  
  if ( !topSound.sound->IsAllreadyPlayed() )
  {
    soundQueue.pop_back();
    StartTopSoundIfNeeded();
  }
}

QueueElement::QueueElement( const NDb::DBFMODEventDesc &desc, int _priority )
: priority(_priority)
{
  sound = new NSound::AskCommands();
  sound->Init(desc);
  isStarted = false;
}

QueueElement::QueueElement( NSound::AskCommands *ask, int _priority )
: priority(_priority)
{
  sound = ask;
  isStarted = false;
}

}

NI_DEFINE_REFCOUNT(NGameX::QueueSoundPlayer)


