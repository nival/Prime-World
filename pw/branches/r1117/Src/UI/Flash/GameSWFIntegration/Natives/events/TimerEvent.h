#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "Event.h"

namespace avmplus
{



class TimerEventObject: public EventObject
{
public:

  TimerEventObject(VTable *ivtable, ScriptObject *delegate);
  ~TimerEventObject(void) {}


  //TODO Alexandr implement this please =)
  void updateAfterEvent();


private:
  DECLARE_SLOTS_TimerEventObject;
};
  

class TimerEventClass : public EventClass
{
public:
  TimerEventClass(VTable *vtable);
  ~TimerEventClass(){}

  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype);

private:
  DECLARE_SLOTS_TimerEventClass;
};


}