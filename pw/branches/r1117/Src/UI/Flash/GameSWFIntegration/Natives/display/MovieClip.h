#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "Sprite.h"

namespace avmplus
{
class ArrayObject;
class ScriptObject;
class MovieClipClass;


struct FrameScript: public MMgc::GCRoot
{
  FrameScript(MMgc::GC * gc, FunctionObject * _script): GCRoot(gc)
  {
    script = _script;
  }
  DRC(FunctionObject*) script;
};

typedef GCRootWrapper<FrameScript> FrameScriptWrapper;


class MovieClipObject: public SpriteObject
{
public:
  MovieClipObject(MovieClipClass * classType);
  MovieClipObject(VTable* ivtable, ScriptObject* prototype);
  ~MovieClipObject(void);

  // AS methods

  void _Init();

  void set_enabled(bool value) { enabled = value; }
  bool get_enabled() { return enabled; }

  int get_totalFrames();
  int get_framesLoaded() { return GetFrameCount(); }

  int get_currentFrame() 
  { 
    return GetNextFrameToPlay()-1; 
  }

  void stop();
  void play();

  void gotoAndPlay(AvmBox frame, AvmString scene);
  void gotoAndStop(AvmBox frame, AvmString scene);

  void prevFrame();
  void nextFrame();

  void addFrameScript( AvmBox* argv, int argc );

  AvmString get_currentFrameLabel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MovieClipObject", "get_currentFrameLabel" );
    return (AvmString)0;
  }

  ArrayObject* get_scenes()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MovieClipObject", "get_scenes" );
    return (ArrayObject*)0;
  }

  void nextScene()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MovieClipObject", "nextScene" );
    return (void)0;
  }

  ScriptObject/*Scene*/ * get_currentScene()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MovieClipObject", "get_currentScene" );
    return (ScriptObject/*Scene*/ *)0;
  }

  void set_trackAsMenu(bool value)
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MovieClipObject", "set_trackAsMenu" );
    return (void)0;
  }

  void prevScene()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MovieClipObject", "prevScene" );
    return (void)0;
  }

  bool get_trackAsMenu()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MovieClipObject", "get_trackAsMenu" );
    return (bool)0;
  }

  AvmString get_currentLabel()
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "MovieClipObject", "get_currentLabel" );
    return (AvmString)0;
  }

  // own methods
  void SetFrameTime( float _frameTime ) { frameTime = _frameTime; }
  float GetFrameTime() const  { return frameTime; }

  void AdvanceNextFrame();
  void RunThisFrameScript();

  virtual const char* GetDumpName() { return "<MovieClip>"; }

  bool IsPlaying() const { return isPlaying; }

  virtual void OnAddedToDisplayList();
  virtual void OnRemovedFromDisplayList();

protected:
  virtual void RunFrameScript( int frameId );

private:

  int ConvertAtomToFrameNumber( AvmBox frame );
  
  bool enabled; // [TODO] implement functionality
  bool isPlaying;
  bool firstAdvance;

  float frameTime;
  float currentFrameTime;

  typedef nstl::hash_map<int, Strong<FrameScriptWrapper>> FrameScripts;
  //typedef List<FunctionObject*, LIST_RCObjects, ListAllocPolicy_InsideRCObject> FrameScripts;
  FrameScripts frameScripts;

  DECLARE_SLOTS_MovieClipObject;
};

DECLARE_AS_CLASS_WITH_CACHE( MovieClipClass, SpriteClass, MovieClipObject )

}