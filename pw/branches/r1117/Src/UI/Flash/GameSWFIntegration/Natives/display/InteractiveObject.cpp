#include "TamarinPCH.h"

#include "InteractiveObject.h"

namespace avmplus
{

InteractiveObjectObject::InteractiveObjectObject(InteractiveObjectClass * classType) : 
DisplayObjectObject((DisplayObjectClass *) classType) 
{
  Initialize();
}

InteractiveObjectObject::InteractiveObjectObject(VTable* ivtable, ScriptObject* prototype) : 
DisplayObjectObject(ivtable, prototype) 
{
  Initialize();
}

void InteractiveObjectObject::Initialize()
{
  mouseEnabled = true;
  doubleClickEnabled = true;
  tabEnabled = false;
  tabIndex = -1;
  focusRect = trueAtom;
}


InteractiveObjectObject::~InteractiveObjectObject() 
{

}

void InteractiveObjectObject::set_focusRect(AvmBox _focusRect)
{
  focusRect = _focusRect;
}

AvmBox InteractiveObjectObject::get_focusRect()
{
  return focusRect;
}

void InteractiveObjectObject::set_contextMenu(ContextMenuObject* cm)
{
  contextMenu = cm;
}

ContextMenuObject* InteractiveObjectObject::get_contextMenu()
{
  return contextMenu;
}

void InteractiveObjectObject::set_accessibilityImplementation(ScriptObject/*AccessibilityImplementation*/ * value)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
}

ScriptObject/*AccessibilityImplementation*/ * InteractiveObjectObject::get_accessibilityImplementation()
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return 0;
}

DisplayObjectObject* InteractiveObjectObject::GetTopMostObject( const flash::SWF_POINT & point )
{
  if ( !mouseEnabled )
    return 0;

  return DisplayObjectObject::GetTopMostObject( point );
}


}