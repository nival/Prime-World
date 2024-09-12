#pragma once

#include "System/SystemLog.h"

#include "../PlayerGlobalIncludes.h"

#include "DisplayObjectContainer.h"

#include "StageEnums.h"
#include "StageProvider.h"

namespace flash
{
  _interface IStageProvider;
  _interface IStageFocusHandler;
}

namespace avmplus
{
class InteractiveObjectObject;
class ScriptObject;
class DisplayObjectObject;

class StageObject: public DisplayObjectContainerObject
{
public:
  StageObject(StageClass * classType);
  StageObject(VTable* ivtable, ScriptObject* prototype);
  ~StageObject(void);

  void SetStageProvider( flash::IStageProvider* _provider ) { stageProvider = _provider; }
  void SetStageFocusHandler( flash::IStageFocusHandler* _focusHandler) { stageFocusHandler = _focusHandler; }

  // AS methods

  void set_stageWidth( int value ) { NI_ALWAYS_ASSERT("Not implemented"); }
  int get_stageWidth();

  void set_stageHeight(int value) { NI_ALWAYS_ASSERT("Not implemented"); }
  int get_stageHeight();

  uint get_fullScreenWidth() { NI_ALWAYS_ASSERT("Not implemented"); return 100; }
  uint get_fullScreenHeight() { NI_ALWAYS_ASSERT("Not implemented"); return 100; }

  void set_fullScreenSourceRect(ScriptObject/*Rectangle*/ * value) { NI_ALWAYS_ASSERT("Not implemented"); }
  ScriptObject/*Rectangle*/ * get_fullScreenSourceRect() { NI_ALWAYS_ASSERT("Not implemented"); return 0; }

  void set_stageFocusRect(bool on) { stageFocusRect = on; }
  bool get_stageFocusRect() { return stageFocusRect; }

  bool isFocusInaccessible() { return false; } // Security issue. not used.

  void set_frameRate(double value) { frameRate = value; }
  double get_frameRate() { return frameRate; }

  void set_showDefaultContextMenu(bool value) { showDefaultContextMenu = value; }
  bool get_showDefaultContextMenu() { return showDefaultContextMenu; }

  void set_align(AvmString value) { align->SetStringValue( value ); }
  AvmString get_align() { return align->GetStringValue(); }

  void set_scaleMode(AvmString value) { scaleMode->SetStringValue( value ); }
  AvmString get_scaleMode() { return scaleMode->GetStringValue(); }

  void set_quality(AvmString value) { quality->SetStringValue( value ); }
  AvmString get_quality() { return quality->GetStringValue(); }

  void set_displayState(AvmString value) { displayState->SetStringValue( value ); }
  AvmString get_displayState() { return displayState->GetStringValue(); }

  void set_colorCorrection(AvmString value) { colorCorrection->SetStringValue( value ); }
  AvmString get_colorCorrection() { return colorCorrection->GetStringValue(); }
  AvmString get_colorCorrectionSupport() { return colorCorrectionSupport->GetStringValue(); }

  void set_focus(InteractiveObjectObject* newFocus);
  InteractiveObjectObject* get_focus() { return focusObject; }

  void Stage_swapChildrenAt(int index1, int index2);
  DisplayObjectObject* Stage_removeChildAt(int index);

  void requireOwnerPermissions() {} // Security issue. not used.

  void invalidate() { stageProvider->Invalidate(); }

  // events
  DECLARE_EVENT(RESIZE)

  void FireResolutionScaleCoeff(float coeff);

private:

  void Initialize();

  Weak<flash::IStageProvider> stageProvider;
  Weak<flash::IStageFocusHandler> stageFocusHandler;

  bool showDefaultContextMenu;
  bool stageFocusRect; // [TODO] implement functionality
  double frameRate; // [TODO] implement functionality
  
  StageAlign * align; // [TODO] implement functionality
  StageScaleMode * scaleMode; // [TODO] implement functionality
  StageQuality * quality; // we don't care about it
  StageDisplayState * displayState; // we don't care about it
  ColorCorrection * colorCorrection; // we don't care about it
  ColorCorrectionSupport * colorCorrectionSupport; // we don't care about it

  DRCWB(InteractiveObjectObject*) focusObject;

  DECLARE_SLOTS_StageObject;
};

DECLARE_AS_CLASS_WITH_CACHE( StageClass, DisplayObjectContainerClass, StageObject )

}