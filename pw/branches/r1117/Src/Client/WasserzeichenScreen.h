#ifndef WASSERZEICHENSCREEN_H_INCLUDED
#define WASSERZEICHENSCREEN_H_INCLUDED

#include "../Client/DefaultScreenBase.h"
#include "../Client/ScreenUILogicBase.h"

namespace client
{

class WasserzeichenNamemap;

class WasserzeichenScreen : public NMainLoop::DefaultScreenBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( WasserzeichenScreen, NMainLoop::DefaultScreenBase );

public:
  static void CreateScreen( const wchar_t * login );

  WasserzeichenScreen() {}
  WasserzeichenScreen( const wchar_t * login ) : m_login( login ) {}

  virtual NMainLoop::EScreenLayer::Enum GetScreenLayer() const { return NMainLoop::EScreenLayer::Highest; }
  virtual bool Init( UI::User * uiUser );
  virtual void Step( bool bAppActive );
  virtual bool IsTransparent() const { return true; }

private:
  Strong<UI::ClientScreenUILogicBase> m_logic;
  Strong<WasserzeichenNamemap> m_nmap;
  wstring m_login;
};

} //client

#endif //WASSERZEICHENSCREEN_H_INCLUDED
