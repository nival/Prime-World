#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"

namespace avmplus
{
class FunctionObject;


class TimerObject: public EventDispatcherObject
{
  bool isRunnung;
  double delay;
  double timePassed;

  DRCWB(FunctionObject*) callback;

public:
  TimerObject(VTable *ivtable, ScriptObject *delegate);
  ~TimerObject(void);

  void Advance(float deltaTime);

  void _timerDispatch();
  void _start(double delay, FunctionObject* closure);
  void stop();
  bool get_running();

  void SetTimerID( int id ) { timerID = id; }
  int GetTimerID() const { return timerID; }

private:
  int timerID;

  DECLARE_SLOTS_TimerObject;
};
  
class TimerClass : public EventDispatcherClass
{
public:
  TimerClass(VTable *vtable);
  ~TimerClass(){}
  
  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype);  
  virtual Atom construct(int argc, Atom* argv);
  
private:
  DECLARE_SLOTS_TimerClass;
};

}