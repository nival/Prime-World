#pragma once
#include "../Client/DefaultScreenBase.h"
#include "../ui/Window.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{
	class TooltipsScreenLogic;
}

namespace NMainLoop
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TooltipsScreen : public NMainLoop::DefaultScreenBase
{
	NI_DECLARE_REFCOUNT_CLASS_1( TooltipsScreen, NMainLoop::DefaultScreenBase );

	Strong<UI::TooltipsScreenLogic> pLogic;

public:
  static void CreateScreen();
  static TooltipsScreen * Instance();

	TooltipsScreen();

  virtual NMainLoop::EScreenLayer::Enum GetScreenLayer() const { return NMainLoop::EScreenLayer::Highest; }
	virtual bool Init( UI::User * uiUser );

  virtual bool IsTransparent() const { return true; }
	virtual bool IsModal() const { return false; }
  virtual void OnNewFront( IScreenBase *pScreen );

  virtual void CommonStep( bool bAppActive );

  void AddTooltip( const wstring & text, const UI::STooltipDesc & desc );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
