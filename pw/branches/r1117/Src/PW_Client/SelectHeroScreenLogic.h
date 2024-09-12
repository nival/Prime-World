#pragma once

#include "../Client/ScreenUILogicBase.h"

namespace NGameX { class SelectHeroScreen; }

namespace UI
{

class SelectHeroScreenLogic : public ClientScreenUILogicBase
{
private:
  NI_DECLARE_REFCOUNT_CLASS_1( SelectHeroScreenLogic, ClientScreenUILogicBase );
  DECLARE_LUA_TYPEINFO( SelectHeroScreenLogic );

  Weak<NGameX::SelectHeroScreen> screen;
 
public:
  SelectHeroScreenLogic() {}

  void SetOwner( NGameX::SelectHeroScreen * _screen ) { screen = _screen; }    

  //Lua
  void SelectHero( const char * heroId );
  void PlayerReady();
  void ChangeTeam( int team );
  void ChangeFaction( int faction );
  void SetDeveloperParty(int party);

  void DebugDisplayPlayers ( const wstring & status );
};

}