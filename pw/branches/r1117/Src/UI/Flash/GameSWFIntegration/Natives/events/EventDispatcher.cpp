#include "TamarinPCH.h"

#include "EventDispatcher.h"
#include "../display/DisplayObject.h"
#include "../display/DisplayObjectContainer.h"
#include "Event.h"

#include "../../FlashMovie.h"

namespace avmplus
{

EventDispatcherObject::EventDispatcherObject( EventDispatcherClass * eventDispatcherClass, ScriptObject * targetDisp ):
  FlashScriptObject(eventDispatcherClass->ivtable(), eventDispatcherClass->prototype)
{
  targetDispatcher = targetDisp ? targetDisp->GetWeakRef() : this->GetWeakRef();
}

EventDispatcherObject::EventDispatcherObject( VTable* ivtable, ScriptObject* prototype ) : 
  FlashScriptObject(ivtable, prototype)
{
  targetDispatcher = this->GetWeakRef();
}

void EventDispatcherObject::addEventListener( AvmString type, FunctionObject* listener, bool useCapture, int priority, bool useWeakReference )
{
  if ( FlashCore()->GetMovie()->IsBroadcastEvent( type->atom() ) )
  {
    FlashCore()->GetMovie()->AddBroadcastListner( type->atom(), listener, this );
    return;
  }

  Atom typeKey = type->atom();

  Listeners::iterator it = listeners.find( typeKey );

  if ( it == listeners.end() )
    it = listeners.insert( typeKey );

  ListenerList & activeList = it->second;

  ListenerList::iterator itC = activeList.begin();
  ListenerList::iterator lastC = activeList.end();

  for ( ; itC != lastC; ++itC )
  {
    Listener * currListener = (*itC)->Get();;
    if ( currListener->FunctionToCall == listener && currListener->UseCapture == useCapture )
      return;
  }

  ListenerList::iterator currentListener =  activeList.end();
  
  while (currentListener!=activeList.begin())
  {
    currentListener--;
    if((*currentListener)->Get()->Priority>=priority)  break;
  }

  ListenerWrapper * wrapper = new ListenerWrapper (new Listener(core()->GetGC(), listener,priority, useCapture));
  activeList.insert(currentListener, wrapper);
}


bool EventDispatcherObject::hasEventListener( AvmString type )
{
  if ( FlashCore()->GetMovie()->IsBroadcastEvent( type->atom() ) )
    return FlashCore()->GetMovie()->HasBroadcastListner( type->atom(), this );

  Atom eventType = type->atom();
  Listeners::iterator listenerList = listeners.find(eventType);
  if (listenerList == listeners.end()) return false;
  //NI_ASSERT(listenerList->second.size(), "listeners size should be greater than 0");
  return true;
}


void EventDispatcherObject::removeEventListener( AvmString type, FunctionObject* listener, bool useCapture )
{
  if ( FlashCore()->GetMovie()->IsBroadcastEvent( type->atom() ) )
  {
    FlashCore()->GetMovie()->RemoveBroadcastListner( type->atom(), listener, this );
    return;
  }

  Atom typeKey = type->atom();

  Listeners::iterator listenerList = listeners.find(typeKey);

  if (listenerList==listeners.end())
    return; // means that we have nothing to remove

  ListenerList & activeList = (*listenerList).second;
  for (ListenerList::iterator i=activeList.begin(); i!=activeList.end(); i++)
  {
    Listener * curListener = (*i)->Get();
    if (curListener->FunctionToCall == listener && curListener->UseCapture == useCapture)
    {
      activeList.erase(i);

      break;
    }
  }

  /*int indexOf = listnersCache.indexOf( listener );

  if ( indexOf != -1 )
    listnersCache.removeAt( indexOf );*/
}



bool EventDispatcherObject::willTrigger( AvmString type )
{
  if (!AsDisplayObject())
  {
    //that means that target dispatcher is not included in the display list
    return hasEventListener(type);
  }

  nstl::vector<DisplayObjectObject *> ancestors( 10 );

  BuildAncestorList( ancestors, 0 );

  for ( int i = 0 ; i < ancestors.size(); ++i )
  {
    if ( ancestors[i]->hasEventListener(type) ) 
      return true;
  }

  return false;
}

void EventDispatcherObject::DispathOnlyForThisObject( EventObject* event )
{
  AvmString eventType = event->get_type();

  event->SetTarget( (ScriptObject*)targetDispatcher->get() );

  if ( hasEventListener(eventType) )
  {
    event->SetEventPhase( EventPhase::Targeting ); 
    ProcessPhaseTwo( event );
  }
}

//NOTE that return value can be void(bool->void) if not preventDefault behavior
bool EventDispatcherObject::dispatchEventFunction( EventObject* event )
{
  event->SetTarget((ScriptObject*)targetDispatcher->get());

  //that means that target dispatcher is not included in the display list and has event listeners attached
  if (!AsDisplayObject())
  {
    DispathOnlyForThisObject( event );
    return true;
  }
  
  //verifies/builds ancestors list
  nstl::vector<DisplayObjectObject *> ancestors( 10 );

  BuildAncestorList( ancestors, event->GetRelatedObject() );

  //now process capturing phase
  event->SetEventPhase(EventPhase::Capturing); 

  for(int i = ancestors.size()-1 ; i>=0; i--)
  {
    if ( !ProcessDispatcher(event, ancestors[i]) ) 
      return true;
  }

  //targeting phase
  event->SetEventPhase(EventPhase::Targeting); 

  if ( !ProcessPhaseTwo(event) ) 
    return true;

  //bubbling phase must be skipped if the event doesn't support it
  if ( !event->get_bubbles() ) 
    return true;

  //bubbling phase
  event->SetEventPhase(EventPhase::Bubbling); 

  for( int i = 0; i < ancestors.size(); i++ )
  {
    if ( !ProcessDispatcher(event, ancestors[i]) ) 
      return true;
  }

  return true;
}



void EventDispatcherObject::BuildAncestorList( nstl::vector<DisplayObjectObject *>& ancestors, DisplayObjectObject * relatedObject )
{
  if (!AsDisplayObject()) return;

  ancestors.clear();

  DisplayObjectObject * curDisplayObject = AsDisplayObject()->get_parent();
  //now iterate till the root. check whether they have listeners 
  while( curDisplayObject)
  {
    if ( relatedObject && relatedObject->IsAncestor( curDisplayObject ) )
      break;

    ancestors.push_back(curDisplayObject);
    curDisplayObject = curDisplayObject->get_parent();
  }
}

bool EventDispatcherObject::ProcessDispatcher( EventObject* event, DisplayObjectObject * ancestor )
{
  event->SetCurrentTarget(ancestor);
  if (!ancestor->hasEventListener(event->get_type())) return true;
  ancestor->ProcessEvent(event);

  if(event->IsPropagationStopped())
    return false;

  return true;
}

bool EventDispatcherObject::ProcessPhaseTwo( EventObject* event )
{
  if (!hasEventListener(event->get_type())) 
    return true;

  event->SetCurrentTarget((ScriptObject*)targetDispatcher->get());
  ProcessEvent(event);

  if(event->IsPropagationStopped())
    return false;
  
  return true;
}

void EventDispatcherObject::ProcessEvent(EventObject * event)
{
  Atom eventType = event->get_type()->atom();

  ListenerList & listenerList = listeners.find(eventType)->second;

  //NI_ASSERT(listenerList.size(), "listeners size should be greater than 0");

  ListenerList cachedList;
  cachedList.insert(cachedList.begin(), listenerList.begin(), listenerList.end());

  for (ListenerList::iterator i = cachedList.begin(); i!=cachedList.end();i++)
  {
    CallListener(*(*i)->Get(), event);
    if (event->IsImmediatePropagationStopped())
      return;
  }
}

void EventDispatcherObject::CallListener( Listener & listener, EventObject * event )
{
  FunctionObject * callbackFunction = listener.FunctionToCall;

  //TODO can it be more compact?
  switch (event->get_eventPhase() )
  {
  case EventPhase::Capturing:
    {
      callbackFunction = listener.UseCapture? callbackFunction: 0;
      break;
    }
  case EventPhase::Bubbling:
    {
      callbackFunction = !listener.UseCapture? callbackFunction: 0;
      break;
    }
  }

  if (!callbackFunction) return;

  Atom argv[2] = { callbackFunction->atom(), event->atom()};
  int argc = 1;
 
  callbackFunction->call(argc, argv);
}

DisplayObjectObject * EventDispatcherObject::AsDisplayObject()
{
  return dynamic_cast<DisplayObjectObject *> ((ScriptObject*)targetDispatcher->get());
}

void EventDispatcherObject::DispatchEvent( AvmString eventType )
{
  dispatchEventFunction(FlashCore()->CreateSimpleEvent(eventType));
}

Atom EventDispatcherClass::construct( int argc, Atom* argv )
{
  AvmCore* core = this->core();

  //0  means that event dispatcher object will be target itself
  ScriptObject * _targetDispatcher = 0;

  if (argc==1 && (core->isObject(argv[1])))
  {
    _targetDispatcher = core->atomToScriptObject(argv[1]);
  }

  EventDispatcherObject * eventDispatcherObject = new (core->GetGC(), ivtable()->getExtraSize()) EventDispatcherObject(this, _targetDispatcher);
  return eventDispatcherObject->atom();
}

ScriptObject* EventDispatcherClass::createInstance( VTable* ivtable, ScriptObject* prototype )
{
   return new (core()->GetGC(), ivtable->getExtraSize()) EventDispatcherObject(ivtable, prototype);
}
}

NI_DEFINE_REFCOUNT(avmplus::ListenerWrapper);