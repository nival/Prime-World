#include "TamarinPCH.h"

#include "BuiltinPools.h"
//NOTE that in media only sound transform is included
#include "../Natives/media/SoundTransform.h"
#include "../Natives/media/SoundChannel.h"
#include "../Natives/media/Sound.h"

#include "sound.cpp"

namespace avmplus
{
  PoolObject * BuiltinPools::GetSoundPool( AvmCore * core )
  {
    return AVM_INIT_BUILTIN_ABC(sound, core);
  }
}