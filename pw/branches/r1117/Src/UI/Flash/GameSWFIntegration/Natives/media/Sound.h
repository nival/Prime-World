#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace flash
{
  class SoundData;
}

namespace NSoundScene
{
  _interface ISimpleSound;
}


namespace avmplus
{
class ByteArrayObject;
class URLRequestObject;
class SoundChannelObject;
class SoundTransformObject;
class ScriptObject;


class SoundObject: public EventDispatcherObject
{
public:
  SoundObject(VTable *ivtable, ScriptObject *delegate):EventDispatcherObject(ivtable, delegate) {}
  ~SoundObject(void) {}

  void SetSoundData(flash::SoundData * _soundData);

  double extract(ByteArrayObject* target, double length, double startPosition);
  void _load(URLRequestObject* stream, bool checkPolicyFile, double bufferTime);

  void close();
  SoundChannelObject* play(double startTime, int loops, SoundTransformObject* sndTransform);

  AvmString get_url();
  uint get_bytesLoaded();
  double get_length();
  ScriptObject/*ID3Info*/ * get_id3();
  int get_bytesTotal();
  bool get_isBuffering();

private:

  CPtr<NSoundScene::ISimpleSound> simpleSound;
  DECLARE_SLOTS_SoundObject;
};
  

class SoundClass : public EventDispatcherClass
{
public:
  SoundClass(VTable *vtable): EventDispatcherClass(vtable)
  {
    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();
    flashCore->GetClassCache().RegisterClass( EFlashClassID::SoundClass, this );
  }
  ~SoundClass(){}

  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
     return new (core()->GetGC(), ivtable->getExtraSize()) SoundObject(ivtable, prototype);
  }

private:
  DECLARE_SLOTS_SoundClass;
};
}