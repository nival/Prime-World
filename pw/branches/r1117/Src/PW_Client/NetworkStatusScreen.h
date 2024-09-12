#ifndef NETWORKSTATUSSCREEN_H_INCLUDED
#define NETWORKSTATUSSCREEN_H_INCLUDED

#include "../Client/DefaultScreenBase.h"
#include "../Client/ScreenUILogicBase.h"



namespace rpc
{
  _interface INode;
}


namespace UI
{
  class ImageLabel;
}



namespace Peered
{
  namespace EDisconnectReason { enum Enum; }
}


namespace lobby
{
  namespace EClientError { enum Enum; }
}

namespace Game
{

class NetworkStatusScreen : public NMainLoop::DefaultScreenBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( NetworkStatusScreen, NMainLoop::DefaultScreenBase );

public:
  NetworkStatusScreen();

  //NMainLoop::IScreenBase
  virtual NMainLoop::EScreenLayer::Enum GetScreenLayer() const { return NMainLoop::EScreenLayer::AboveTopmost; }
  virtual bool Init( UI::User * uiUser );
  virtual void Step( bool bAppActive );
  virtual bool IsTransparent() const { return true; }

  void SetClientAsync() { m_async = true; }
  void SetFastReconnectTryIndex( int idx ) { m_fastReconnectTryIndex = idx; }
  void SetLobbyErrorCode( lobby::EClientError::Enum code ) { m_lobbyErrorCode = code; }
  void SetGsGracefullDisconnectReason( Peered::EDisconnectReason::Enum reason ) { m_gsGracefullDisconnectReason = reason; }
  void GsConnectionIsDead() { m_gsConnectionIsDead = true; }

  void ResetErrors();

private:
  Strong<UI::ClientScreenUILogicBase> m_logic;
  Weak<UI::ImageLabel>                m_main, m_text;
  float                               m_errorOpa;

  bool                                m_async;
  int                                 m_fastReconnectTryIndex;
  bool                                m_gsConnectionIsDead;

  lobby::EClientError::Enum           m_lobbyErrorCode;
  Peered::EDisconnectReason::Enum     m_gsGracefullDisconnectReason;

  wstring                             m_channelsTooltip;

  bool IsItOk() const;
  void UpdateUi();
  void UpdateTooltipText();
};

} //Game

#endif //NETWORKSTATUSSCREEN_H_INCLUDED
