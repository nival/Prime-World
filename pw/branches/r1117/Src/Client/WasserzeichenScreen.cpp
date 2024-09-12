#include "stdafx.h"
#include "WasserzeichenScreen.h"
#include "ScreenCommands.h"
#include "../UI/Window.h"
#include "../Version.h"

static bool SHOW_WATERMARK = false;
REGISTER_DEV_VAR( "show_wasserzeichen", SHOW_WATERMARK, STORAGE_NONE );

NI_DEFINE_REFCOUNT( client::WasserzeichenScreen );

namespace client
{


class WasserzeichenNamemap : public BaseObjectST, public NNameMap::IMap
{
  NI_DECLARE_REFCOUNT_CLASS_2( WasserzeichenNamemap, BaseObjectST, NNameMap::IMap )
  NAMEMAP_DECLARE

public:
  wstring   version, login, title, company, copyright;

  WasserzeichenNamemap()
  {
    version = NStr::StrFmtW( L"%S - %d.%d.%02d.%04d", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );
    login = L"";

    title = NStr::StrFmtW( L"%S", PRODUCT_TITLE );
    company = NStr::StrFmtW( L"%S", ENTERPRISE_COMPANY );
    copyright = NStr::StrFmtW( L"%S", ENTERPRISE_COPYRIGHT );
  }
};

NAMEMAP_BEGIN( WasserzeichenNamemap )
  NAMEMAP_VAR( version )
  NAMEMAP_VAR( title )
  NAMEMAP_VAR( login )
  NAMEMAP_VAR( company )
  NAMEMAP_VAR( copyright )
NAMEMAP_END




void WasserzeichenScreen::CreateScreen( const wchar_t * login )
{
  WasserzeichenScreen * pScreen = new WasserzeichenScreen( login );

  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( pScreen ) );
}



bool WasserzeichenScreen::Init( UI::User * uiUser )
{
  m_nmap = new WasserzeichenNamemap;
  m_nmap->login = m_login;

  m_logic = new UI::ClientScreenUILogicBase;
  SetLogic( m_logic );
  m_logic->SetUser( uiUser );
  m_logic->LoadScreenLayout( "Wasserzeichen" );

  m_logic->GetBaseWindow()->Show( SHOW_WATERMARK );

  UI::Window * main = UI::GetChildChecked<UI::Window>( m_logic->GetBaseWindow(), "Main", true );
  NI_VERIFY( main, "", return false );
  main->AssignNameMap( m_nmap );
  m_logic->UpdateWindowsByNameMap( m_nmap );

  return true;
}



void WasserzeichenScreen::Step( bool bAppActive )
{
  DefaultScreenBase::Step( bAppActive );

  m_logic->GetBaseWindow()->Show( SHOW_WATERMARK );
}

} //client
