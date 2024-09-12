#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "InteractiveObject.h"

namespace avmplus
{
class DisplayObjectObject;
class SoundTransformObject;


class SimpleButtonObject: public InteractiveObjectObject
{
public:

  SimpleButtonObject( SimpleButtonClass * classType );
  SimpleButtonObject( VTable* ivtable, ScriptObject* prototype );
  ~SimpleButtonObject();

  bool get_enabled() { return enabled; }
  void set_enabled(bool value) { enabled = value; }

  void _updateButton();

  DisplayObjectObject* get_hitTestState() { return hitTestState; }
  void set_hitTestState(DisplayObjectObject* value) { hitTestState = value; }

  void set_upState(DisplayObjectObject* value) { upState = value; }
  DisplayObjectObject* get_upState()  { return upState; }

  void set_downState(DisplayObjectObject* value) { downState = value; }
  DisplayObjectObject* get_downState() { return downState; }

  void set_overState(DisplayObjectObject* value) { overState = value; }
  DisplayObjectObject* get_overState() { return overState; }

  void set_soundTransform(SoundTransformObject* sndTransform) { soundTransform = sndTransform; }
  SoundTransformObject* get_soundTransform() { return soundTransform; }

  void set_useHandCursor(bool value) { useHandCursor = value; }
  bool get_useHandCursor() { return useHandCursor; }

  void set_trackAsMenu(bool value) { trackAsMenu = value; }
  bool get_trackAsMenu() { return trackAsMenu; }

  virtual const char* GetDumpName() { return "<SimpleButton>"; }

protected:

  virtual void DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode );
  virtual void GetBounds( flash::SWF_RECT& _rect );

private:

  bool enabled;
  bool useHandCursor;
  bool trackAsMenu;

  DRCWB( DisplayObjectObject* ) hitTestState;
  DRCWB( DisplayObjectObject* ) upState;
  DRCWB( DisplayObjectObject* ) downState;
  DRCWB( DisplayObjectObject* ) overState;

  DRCWB( DisplayObjectObject* ) currentState;

  DRCWB( SoundTransformObject* ) soundTransform;

  DECLARE_SLOTS_SimpleButtonObject;
};

DECLARE_AS_CLASS_WITH_CACHE( SimpleButtonClass, InteractiveObjectClass, SimpleButtonObject )
  
}