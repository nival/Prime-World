#ifndef SelectHeroScreen_HEADER
#define SelectHeroScreen_HEADER

#include "Client/DefaultScreenBase.h"
#include "IGameContext.h"

namespace UI
{
  class SelectHeroScreenLogic;
}


namespace NGameX
{

class SelectHeroScreen : public NMainLoop::DefaultScreenBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( SelectHeroScreen, NMainLoop::DefaultScreenBase )

public:
  SelectHeroScreen( Game::IGameContextUiInterface * _ctx );
  
  virtual bool Init( UI::User * uiUser );
  virtual void CommonStep( bool bAppActive );

  void UpdatePlayers( const vector<wstring> & lines, const vector<int> & linesIds , const set<int> & hiliteIds );

  WeakMT<Game::IGameContextUiInterface> & GameCtx() { return gameCtx; }

private:
  void DebugFormatPlayerInfo();

  WeakMT<Game::IGameContextUiInterface> gameCtx;
  Strong<UI::SelectHeroScreenLogic>   logic;

  ///TEMP///
  vector<wstring>   debugPlayerLines;
  vector<int>       debugPlayerIds;
  map<int, float>   debugHiliteTimes;
  wstring           debugPlayerStatus;
};

} // End of namespace Game

#endif