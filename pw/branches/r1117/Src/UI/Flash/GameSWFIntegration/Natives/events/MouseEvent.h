#pragma once

#include <System/SystemLog.h>

#include "../PlayerGlobalIncludes.h"

#include "../display/DisplayObject.h"

#include "Event.h"

namespace avmplus
{

class MouseEventObject: public EventObject
{
public:
  MouseEventObject(VTable *ivtable, ScriptObject *delegate);
  ~MouseEventObject(void);

  // AS 3 methods

  void updateAfterEvent();

  void set_localX(double value) { localX = value; }
  double get_localX() { return localX; }

  void set_localY(double value) { localY = value; }
  double get_localY() { return localY; }

  double getStageX() { return stageX; }
  double getStageY() { return stageY; }

  // own methods

  virtual void SetCurrentTarget( ScriptObject * currentDispatcher );

  virtual DisplayObjectObject* GetRelatedObject();
  void SetRelatedObject( DisplayObjectObject* relatedObject );

  void SetStageXY( float x, float y ) { stageX = x; stageY = y; }



private:

  DRCWB(DisplayObjectObject*) relatedObject;

  double localX;
  double localY;
  double stageX;
  double stageY;

  DECLARE_SLOTS_MouseEventObject;
};

class MouseEventClass : public EventClass
{
public:
  MouseEventClass(VTable *vtable);
  ~MouseEventClass(){}

  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype);

  // CreateEvent - name reserved by windows
  MouseEventObject * CreateMouseEvent(  const char * _type, 
                                        float _stageX, float _stageY, 
                                        float _localX, float _localY, 
                                        bool primaryButton, DisplayObjectObject* _relatedObject, int mouseWheelDelta = 0 );

private:
  DECLARE_SLOTS_MouseEventClass;
};

}