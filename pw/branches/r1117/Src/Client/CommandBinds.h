#ifndef COMMANDBINDS_H_INCLUDED
#define COMMANDBINDS_H_INCLUDED

namespace Input
{
  class Event;
}

namespace CommandBinds
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ProcessEvent( const Input::Event & event );

} //namespace CommandBinds

#endif //COMMANDBINDS_H_INCLUDED
