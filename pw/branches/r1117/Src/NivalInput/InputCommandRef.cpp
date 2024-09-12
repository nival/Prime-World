#include "stdafx.h"
#include "InputCommandRef.h"

#include "Binds.h"
#include "InputEvent.h"


namespace Input
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CommandReference::CommandReference( const char * commandName ) :
lastDelta( 0 ), value( 0 )
{
  command = 0;

  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
  if(binds)
    command = binds->FindCommand( commandName );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandReference::ProcessEvent( const Event & event )
{
  if ( command != event.Command() )
    return false;

  switch ( event.Type() )
  {
    default:
    case EEventType::Activation:
    case EEventType::System: //We do not store windows messages info
      break;

    case EEventType::ScalarDelta:
      lastDelta += event.Delta();
      break;

    case EEventType::ScalarValue:
      value = event.Value();
      break;
  }

  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandReference::IsActiveNow() const
{
  return IsValid( command ) ? command->IsActiveNow() : false;
}

} //namespace Input
