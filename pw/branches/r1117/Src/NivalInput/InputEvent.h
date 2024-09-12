#ifndef INPUTEVENT_H_INCLUDED
#define INPUTEVENT_H_INCLUDED

namespace Input
{

_interface ICommandInstance;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EEventType
{
  enum Enum { Null, Activation, ScalarDelta, ScalarValue, System };
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Params for translating some windows messages
struct SSysParams
{
  struct Mouse
  {
    short x;
    short y;
  };

  union //Используется вместо масок, для корректной обработки отрицательных чисел
  {
    int   first;
    Mouse mouse;
  };
  int second;

  SSysParams( int _first = 0, int _second = 0 ) : first( _first ), second( _second ) {}
  SSysParams( int mouseX, int mouseY, int mouseFlags ):  second( mouseFlags ) { mouse.x = mouseX; mouse.y = mouseY; } 

  int GetMouseX() const { return mouse.x; }
  int GetMouseY() const { return mouse.y; }
  int GetMouseFlags() const { return second; }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ex. SGameMessage
//FIXME: nasty data overload
class Event
{
public:
  Event(); //Default

  Event( ICommandInstance * cmd ); //'Activated' contr
  Event( ICommandInstance * cmd, float _scalar, bool deltaMode ); //'Scalar' contr
  Event( ICommandInstance * cmd, const SSysParams & sys ); //'System' contr

  ICommandInstance * Command() const { return command; }

  EEventType::Enum Type() const { return type; }
  bool      Activated() const { return type == EEventType::Activation; }
  float     Delta() const { NI_ASSERT( type == EEventType::ScalarDelta, "" ); return scalar; }
  float     Value() const { NI_ASSERT( type == EEventType::ScalarValue, "" ); return scalar; }
  const SSysParams & SysParams() const { NI_ASSERT( type == EEventType::System, "" ); return sysParams; }

private:
  CPtr<ICommandInstance> command;
  EEventType::Enum  type;

  float             scalar;
  SSysParams        sysParams;
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Interface to identify CommandInstance for external classes
_interface ICommandInstance : public IObjectBase
{
public:
  virtual const string & Name() const = 0;
  virtual bool IsActiveNow() const = 0;
};


} //namespace Input

#endif //INPUTEVENT_H_INCLUDED
