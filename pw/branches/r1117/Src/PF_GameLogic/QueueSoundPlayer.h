#pragma once

#include "../Sound/SoundUI.h"

namespace NDb
{
  struct DBFMODEventDesc;
}

namespace NGameX
{
//public for sorting
struct QueueElement
{
  Strong<NSound::AskCommands> sound;
  int priority;
  bool isStarted;

  QueueElement(const NDb::DBFMODEventDesc &desc, int _priority);
  QueueElement(NSound::AskCommands *ask, int _priority);
};

class QueueSoundPlayer: public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( QueueSoundPlayer, BaseObjectST );
public:
  void AddSoundToQueue(const NDb::DBFMODEventDesc &desc, int priority);
  void AddAskToQueue(NSound::AskCommands *ask, int priority);
  void Update(float dt);
private:
  void StartTopSoundIfNeeded();
  nstl::list<QueueElement> soundQueue;
};

}