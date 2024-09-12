#ifndef INPUTCOMMANDREF_H_INCLUDED
#define INPUTCOMMANDREF_H_INCLUDED

namespace Input
{

_interface ICommandInstance;
class Event;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ex. CBind
class CommandReference
{
public:
  CommandReference() : lastDelta( 0 ), value( 0 ) {}
  CommandReference( const char * commandName );

  bool ProcessEvent( const Event & event );

  float RetrieveDelta() { float result = lastDelta; lastDelta = 0; return result; }
  float GetValue() const { return value; }

  void ClearDelta() { lastDelta = 0; }

  bool IsActiveNow() const;

private:
  CPtr<ICommandInstance>  command;
  float                   lastDelta;
  float                   value;
};

} //namespace Input

#endif //INPUTCOMMANDREF_H_INCLUDED
