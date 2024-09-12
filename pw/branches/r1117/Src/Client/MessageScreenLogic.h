#pragma once

#include "ScreenUILogicBase.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NMainLoop
{
  class MessageScreen;
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{

class MessageScreenLogic : public ClientScreenUILogicBase
{
private:
	NI_DECLARE_REFCOUNT_CLASS_1( MessageScreenLogic, ClientScreenUILogicBase );
  DECLARE_LUA_TYPEINFO( MessageScreenLogic );

public:
  MessageScreenLogic();

  void SetScreen(NMainLoop::MessageScreen * pScreen) { screen = pScreen; }
  Window * GetBaseWindow() { return pBaseWindow; }

  void EscapeKeyPressed();


  ///Lua///
	void YesButtonPressed();
  void NoButtonPressed();

private:
  Weak<NMainLoop::MessageScreen> screen;
};

} //namespace UI
