#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "FunctionClass.h"
#include "../../FlashBaseClasses.h"
#include "EventTypes.h"
#include "../../GCRootWrapper.h"

namespace avmplus
{
class FunctionObject;
class ArrayObject;
class DisplayObjectObject;

class EventDispatcherClass : public FlashClassClosure
{
public:
  EventDispatcherClass(VTable *vtable): FlashClassClosure(vtable){}
  ~EventDispatcherClass(){}

  virtual Atom construct(int argc, Atom* argv);  

  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype); 

private:
  DECLARE_SLOTS_EventDispatcherClass;
};


struct Listener: public flash::SafeGCRoot<Listener>
{
  Listener(MMgc::GC * gc, FunctionObject * callback, int priority, bool usecapture): flash::SafeGCRoot<Listener>(gc), Priority(priority) , UseCapture (usecapture) 
  {
    FunctionToCall = callback;
  }
  DRC(FunctionObject*) FunctionToCall;
  int Priority;
  bool UseCapture;

  Listener& operator = ( const Listener& _other ) 
  {
    FunctionToCall = _other.FunctionToCall;
    Priority = _other.Priority;
    UseCapture = _other.UseCapture;

    return *this;
  }
};

typedef GCRootWrapper<Listener> ListenerWrapper;

class EventDispatcherObject: public FlashScriptObject
{
  typedef nstl::list<Strong<ListenerWrapper>> ListenerList;
  typedef nstl::map<Atom, ListenerList> Listeners; // String->atom() to list of Listeners

  Listeners listeners;

  DWB(MMgc::GCWeakRef*) targetDispatcher; // ScriptObject* //object which is used as an event target

public:
  EventDispatcherObject(EventDispatcherClass * eventDispatcherClass, ScriptObject * targetDispathcer);
  EventDispatcherObject(VTable* ivtable, ScriptObject* prototype);

  ~EventDispatcherObject(void) {}

  // AS3 methods

  bool willTrigger(AvmString type);
  bool dispatchEventFunction( EventObject* event );

  bool hasEventListener(AvmString type);
  void addEventListener(AvmString type, FunctionObject* listener, bool useCapture, int priority, bool useWeakReference);
  void removeEventListener(AvmString type, FunctionObject* listener, bool useCapture);

  ArrayObject* get_listeners()
  {
    //NOTE its private and isn't used. so it seems that we don't need that method
    //TODO then why its here?!
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "EventDispatcherObject", "get_listeners" );
    return (ArrayObject*)0;
  }

  // own methods

  void DispatchEvent( AvmString eventType );
  void DispathOnlyForThisObject( EventObject* event );

private:

  DisplayObjectObject * AsDisplayObject();

  void BuildAncestorList( nstl::vector<DisplayObjectObject *>& ancestors, DisplayObjectObject * relatedObject );
  void ProcessEvent(EventObject * event);
  void CallListener( Listener & listener, EventObject * event );
  bool ProcessPhaseTwo( EventObject* event );
  bool ProcessDispatcher( EventObject* event, DisplayObjectObject * ancestor );

  DECLARE_SLOTS_EventDispatcherObject;
};
  


}