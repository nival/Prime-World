#pragma once

#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../media/SoundTransform.h"
#include "../../DisplayList.h"
#include "../../DisplayTags.h"

#include "DisplayObjectContainer.h"
#include "Graphics.h"

namespace flash
{
  class SpriteCharacter;
}

namespace avmplus
{
class DisplayObjectObject;
class SoundTransformObject;

class SpriteObject: public DisplayObjectContainerObject
{
public:
  SpriteObject(SpriteClass * classType);
  SpriteObject(VTable* ivtable, ScriptObject* prototype);
  ~SpriteObject(void);

  // AS methods

  void set_buttonMode(bool value) { buttonMode = value; }
  bool get_buttonMode() { return buttonMode; }

  void set_useHandCursor(bool value) { useHandCursor = value; }
  bool get_useHandCursor() { return useHandCursor; }

  DisplayObjectObject* get_dropTarget() { return dropTarget; }

  // other hit area
  void set_hitArea(SpriteObject* value) { hitArea = value; }
  SpriteObject* get_hitArea() { return hitArea; }

  void set_soundTransform(SoundTransformObject* sndTransform) { soundTransform = sndTransform; }
  SoundTransformObject* get_soundTransform() { return soundTransform; }

  GraphicsObject* get_graphics() { return graphics; }

  void constructChildren();  
  void stopDrag();
  void startDrag(bool lockCenter, ScriptObject/*Rectangle*/ * bounds);

  // own methods
  virtual const char* GetDumpName() { return "<Sprite>"; }

  void SetCharacter( flash::SpriteCharacter* _character );
  
  void GotoFrame( int frameId );
  int  GetFrameCount() { return frameCount; }
  int  GetNextFrameToPlay() { return nextFrameToPlay; }

  void SetDropTarget( DisplayObjectObject* _dropTarget ) { dropTarget = _dropTarget; }

protected:
  void AdvanceCharacterList( int frameId );
  virtual void RunFrameScript( int frameId ) {}

  Weak<flash::SpriteCharacter> spriteCharacter;

private:
  void Initialize();

  // depth -> cgaracter ID map
  typedef nstl::hash_map<int, int> FirstFrameCharacters;

  int frameCount;
  int nextFrameToPlay; // 1 - based
  
  DRCWB( GraphicsObject* ) graphics;
  DRCWB( DisplayObjectObject* ) dropTarget;
  DRCWB( SpriteObject* ) hitArea;  // [TODO] implement functionality
  DRCWB( SoundTransformObject* ) soundTransform;  // [TODO] implement functionality

  bool buttonMode; // [TODO] implement functionality
  bool useHandCursor; // [TODO] implement functionality

  DECLARE_SLOTS_SpriteObject;
};
  
DECLARE_AS_CLASS_WITH_CACHE( SpriteClass, DisplayObjectContainerClass, SpriteObject )

}