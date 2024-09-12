#ifndef SELECTGAMEMODESCREEN__H_INCLUDED
#define SELECTGAMEMODESCREEN__H_INCLUDED

#include "Client/DefaultScreenBase.h"
#include "IGameContext.h"

namespace UI
{
  class SelectGameModeLogic;
}


namespace NGameX
{

class SelectGameModeScreen : public NMainLoop::DefaultScreenBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( SelectGameModeScreen, NMainLoop::DefaultScreenBase );

public:
  SelectGameModeScreen( Game::IGameContextUiInterface * _ctx );

  StrongMT<Game::IGameContextUiInterface> GameCtx() { return gameCtx.Lock(); }
  
  virtual bool Init( UI::User * uiUser );
  virtual void Step( bool bAppActive );

  bool IsModal() const { return false; }

private:
  WeakMT<Game::IGameContextUiInterface> gameCtx;
  Strong<UI::SelectGameModeLogic> logic;
};

} //namespace NGameX

#endif //SELECTGAMEMODESCREEN__H_INCLUDED
