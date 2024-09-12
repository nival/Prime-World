#pragma once

#include "../System/Singleton.h"
#include "../Sound/SoundScene.h"
#include "../Sound/EventScene.h"

namespace NSound
{
class Sound2D
{
public:
  Sound2D (const string fileName, int _cycleCount, float _startOffset );

  float Play();

  NSoundScene::SoundDescription desc;
  float offset;
  float startOffset;
  int cycleCount;
  float volume;
  int soundID;
private:
};

class AskCommands : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( AskCommands, BaseObjectST );
public:
  AskCommands();
  ~AskCommands();

  void Init( const NDb::DBFMODEventDesc &desc );
  bool PlaySound();
  bool IsAllreadyPlayed();
  bool Stop( bool immediately );
  float GetAskTime();

private:
  NSoundScene::FMODEvent* fmodEvent;
};
} // end of namespace NSound
