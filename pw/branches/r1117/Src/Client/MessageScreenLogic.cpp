#include "stdafx.h"
#include "MessageScreenLogic.h"
#include "MessageScreen.h"
#include "../Client/ScreenCommands.h"


namespace UI
{
using namespace NScript;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO( MessageScreenLogic, ClientScreenUILogicBase )
  LUA_METHOD( YesButtonPressed )
  LUA_METHOD( NoButtonPressed )
END_LUA_TYPEINFO( MessageScreenLogic )


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MessageScreenLogic::MessageScreenLogic()
{
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MessageScreenLogic::YesButtonPressed()
{
  if(NMainLoop::IMessageScreenCallback * cb = screen->GetCallback())
    cb->OnYesButton();

  NScreenCommands::PushCommand(NScreenCommands::CreatePopScreenCommand("MessageScreen"));
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MessageScreenLogic::NoButtonPressed()
{
  if(NMainLoop::IMessageScreenCallback * cb = screen->GetCallback())
    cb->OnNoButton();

  NScreenCommands::PushCommand(NScreenCommands::CreatePopScreenCommand("MessageScreen"));
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MessageScreenLogic::EscapeKeyPressed()
{
  if(NMainLoop::IMessageScreenCallback * cb = screen->GetCallback())
    if(cb->OnEscapeKey())
      NScreenCommands::PushCommand(NScreenCommands::CreatePopScreenCommand("MessageScreen"));
}


} //namespace UI
