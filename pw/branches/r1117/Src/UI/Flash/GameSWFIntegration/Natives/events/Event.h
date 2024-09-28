#pragma once

#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../../FlashBaseClasses.h"


namespace EventPhase
{
  enum Phase
  {
    Bubbling = 3,
    Targeting = 2,
    Capturing = 1
  };
}

namespace avmplus
{

class EventClass : public FlashClassClosure
{
public:
  EventClass(VTable *vtable);
  ~EventClass(){}

  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype); 

private:
  DECLARE_SLOTS_EventClass;
};


class EventObject: public FlashScriptObject
{
public:
   EventObject(VTable* ivtable, ScriptObject* prototype);
  ~EventObject(void) {}

  // AS3 methods

  AvmString get_type() { return eventType;}

  bool get_bubbles() { return bubbles;}
  bool get_cancelable() { return cancelable;}
  
  uint get_eventPhase() {return eventPhase; }

  Atom get_target() {return (target)? target->atom(): 0; }
  Atom get_currentTarget() { return (curTarget)? curTarget->atom() : 0;}

  bool isDefaultPrevented() { return defaultPrevented;}
  void preventDefault() { defaultPrevented = cancelable;}

  void stopPropagation() { propagationStopped = true;}
  void stopImmediatePropagation() {immediatePropagationStopped = true;}

  // own methods

  virtual void SetEventPhase( EventPhase::Phase phase ) { eventPhase = phase; }
  virtual void SetTarget( ScriptObject * dispatcher ) { target = dispatcher; }
  virtual void SetCurrentTarget( ScriptObject * currentDispatcher ) { curTarget = currentDispatcher; }

  void Init(AvmString type, bool bubbles, bool cancelable);
  bool IsPropagationStopped() const { return propagationStopped || immediatePropagationStopped; }
  bool IsImmediatePropagationStopped() const { return immediatePropagationStopped; }

  // for MouseEvent related object to modify propogation list
  virtual DisplayObjectObject* GetRelatedObject() { return 0; }

private:
  //mostly these are used for getters and setters. so event is pretty dummy.
  EventPhase::Phase eventPhase;
  bool bubbles;
  bool cancelable;

  bool defaultPrevented;

  DRCWB(AvmString) eventType;
  DRCWB(ScriptObject*) target;
  DRCWB(ScriptObject*) curTarget;

  bool immediatePropagationStopped;
  bool propagationStopped;

  DECLARE_SLOTS_EventObject;
};
  

}