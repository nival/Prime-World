#ifndef SYSTEMINPUTEVENTS_H_INCLUDED
#define SYSTEMINPUTEVENTS_H_INCLUDED

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Input
{

_interface ICommandInstance;
class Binds;
class Event;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SystemEvents : public CObjectBase
{
  OBJECT_BASIC_METHODS( SystemEvents );

public:
  SystemEvents( Binds * binds );

  void Pump( vector<Input::Event> & events );

private:
  CPtr<ICommandInstance>   cmdChar, cmdKeyDown, cmdKeyUp;
  CPtr<ICommandInstance>   cmdMouseMove, cmdMouseOut, cmdMouseDisabled, cmdWheelDown, cmdWheelUp;
  CPtr<ICommandInstance>   cmdMouseLeftDblClick, cmdMouseRightDblClick;
  CPtr<ICommandInstance>   cmdMouseLeftDown, cmdMouseLeftUp, cmdMouseRightDown, cmdMouseRightUp;

  SystemEvents() {}

  ICommandInstance * DefineCommandMock( Binds * binds, const char * name );
};

} //namespace Input

#endif //SYSTEMINPUTEVENTS_H_INCLUDED
