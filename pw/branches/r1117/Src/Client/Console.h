#pragma once

#include "../Client/DefaultScreenBase.h"
#include "../UI/Window.h"
#include "ConsoleLogic.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NMainLoop
{

class DebugTextDraw;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Console : public NMainLoop::DefaultScreenBase
{
	NI_DECLARE_REFCOUNT_CLASS_1( Console, NMainLoop::DefaultScreenBase );

public:
  static void CreateScreen();

	Console();
  ~Console();

  virtual NMainLoop::EScreenLayer::Enum GetScreenLayer() const { return NMainLoop::EScreenLayer::Highest; }
	virtual bool Init( UI::User * uiUser );
	virtual void Step( bool bAppActive );
  virtual void Draw( bool bAppActive );
	virtual bool ProcessUIEvent( const Input::Event & message );

	virtual bool IsTransparent() const { return true; }
	virtual bool IsInited() const { return inited; }
	virtual bool IsModal() const;

	bool OpenClose();

private:
  bool inited;

	Strong<UI::ConsoleLogic> logic;

	bool consoleActive;

  CObj<DebugTextDraw> debugTextDraw;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
