#include "stdafx.h"
#include "NetworkStatusScreen.h"

#include "UI/ImageLabel.h"
#include "Client/MainTimer.h"

#include "HybridServer/Peered.h"
#include "Client/LobbyPvx/LobbyClientBase.h"
#include "RPC/Interfaces.h"
#include "System/MainFrame.h"


static bool SHOW_NETWORK_STATUS = false;
REGISTER_VAR( "show_network_status", SHOW_NETWORK_STATUS, STORAGE_NONE );

NI_DEFINE_REFCOUNT( Game::NetworkStatusScreen );

namespace Game
{

NetworkStatusScreen::NetworkStatusScreen() :
m_errorOpa( 1.0f ),
m_async( false ),
m_fastReconnectTryIndex( 0 ),
m_gsConnectionIsDead( false ),
m_lobbyErrorCode( lobby::EClientError::NoError ),
m_gsGracefullDisconnectReason( Peered::EDisconnectReason::None )
{
}



bool NetworkStatusScreen::Init( UI::User * uiUser )
{
  m_logic = new UI::ClientScreenUILogicBase;
  SetLogic( m_logic );
  m_logic->SetUser( uiUser );
  m_logic->LoadScreenLayout( "NetworkStatus" );

  m_main = m_logic->GetUIWindow<UI::ImageLabel>( "Main" );

  UpdateUi();

  return true;
}



void NetworkStatusScreen::Step( bool bAppActive )
{
  DefaultScreenBase::Step( bAppActive ) ;

  UpdateUi();
}



void NetworkStatusScreen::ResetErrors()
{
  m_async = false;
  m_fastReconnectTryIndex = 0;
  m_gsConnectionIsDead = false;
  m_lobbyErrorCode = lobby::EClientError::NoError;
  m_gsGracefullDisconnectReason = Peered::EDisconnectReason::None;
}



bool NetworkStatusScreen::IsItOk() const
{
  if ( m_async || m_fastReconnectTryIndex > 0 )
    return false;

  if ( m_gsGracefullDisconnectReason != Peered::EDisconnectReason::None )
    return false;

//  if ( m_lobbyErrorCode != lobby::EClientError::NoError )
//    return false;
  
  return true;
}



void NetworkStatusScreen::UpdateUi()
{
  NI_VERIFY( IsValid( m_main ), "", return );

  const char * newState = "";

  if ( m_async )
    newState = "Async";
  else if ( m_fastReconnectTryIndex == 1 )
    newState = "Reconnecting";
  else if ( m_fastReconnectTryIndex > 1 )
    newState = "Reconnecting2";
  else if ( m_gsGracefullDisconnectReason == Peered::EDisconnectReason::ClientAway )
    newState = "Away";
  else if ( ( m_gsGracefullDisconnectReason == Peered::EDisconnectReason::ClientPerfomance ) || ( m_gsGracefullDisconnectReason == Peered::EDisconnectReason::NetworkPerfomance ) )
    newState = "TooSlow";
  else if ( m_gsGracefullDisconnectReason == Peered::EDisconnectReason::GameFinished )
    newState = "GameFinished";
  else if ( m_gsGracefullDisconnectReason == Peered::EDisconnectReason::ServerError )
    newState = "ServerError";
  else if ( m_gsConnectionIsDead || ( m_gsGracefullDisconnectReason != Peered::EDisconnectReason::None ) )
    newState = "NetworkFailure";

  //FIXME: We do not indicate 'm_lobbyErrorCode', because it has no impact on gameplay

  bool show = SHOW_NETWORK_STATUS || ( newState[0] ? true : false );

  m_main->Show( show );
  if ( !m_text || ( newState != m_main->GetState() ) )
  {
    m_main->SetState( newState );
    m_text = m_logic->GetUISubWindow<UI::ImageLabel>( m_main, "Text" );
    m_errorOpa = 1.0f;
    NMainFrame::ShowCursor( true );
  }

  if ( show )
    UpdateTooltipText();

  if ( m_text && newState )
  {
    if ( m_errorOpa < 0.5f )
      m_errorOpa = 1.0f;
    m_errorOpa -= NMainLoop::GetTimeDelta() * 0.4f;
    m_text->SetOpacity( m_errorOpa );
  }
}



void NetworkStatusScreen::UpdateTooltipText()
{
  NI_VERIFY( IsValid( m_main ), "", return );

  m_channelsTooltip = NStr::StrFmtW( 
    L"Network status:<br>\n"
    L"Async: %s<br>\n"
    L"Fast reconnect try: %d<br>\n"
    L"Lobby client error: %d<br>\n"
    L"GS connection is dead: %s<br>\n"
    L"GS disconnect reason: %d<br>\n",
    m_async ? L"yes" : L"no",
    m_fastReconnectTryIndex,
    (int)m_lobbyErrorCode,
    m_gsConnectionIsDead ? L"yes" : L"no",
    (int)m_gsGracefullDisconnectReason );

  m_main->SetTooltipTextW( m_channelsTooltip );
}

} //Game
