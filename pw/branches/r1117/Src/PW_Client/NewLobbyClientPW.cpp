#include "stdafx.h"
#include "NewLobbyClientPW.h"
#include "PF_GameLogic/MapCollection.h"
#include "PF_GameLogic/StringExecutor.h"
#include "PF_GameLogic/AdventureScreen.h"
#include "Client/ScreenCommands.h"

#include "SelectGameModeScreen.h"
#include "SelectHeroScreen.h"
#include "FastReconnectCtxPW.h"


bool g_needNotifyLobbyClients = false;
string g_selectedHeroes[10];

namespace lobby
{

ClientPW::ClientPW( Transport::TClientId _clientId, bool _socialMode, Game::IGameContextUiInterface * _gameCtx, FastReconnectCtxPW * _fastReconnectCtx ) :
ClientBase( _clientId, _socialMode ),
gameCtx( _gameCtx ),
fastReconnectCtxPw( _fastReconnectCtx ),
lastRememberedPlayers ( -1 ) 
{
	fillHeroNeme();
}



void ClientPW::OnStatusChange( EClientStatus::Enum newStatus )
{
  ClientBase::OnStatusChange( newStatus );

  if ( newStatus == EClientStatus::Connected )
  {
    if ( fastReconnectCtxPw )
      mapCollection = fastReconnectCtxPw->Maps();
    else
    {
      StrongMT<NWorld::PWMapCollection> maps = new NWorld::PWMapCollection;
      maps->ScanForMaps();
      mapCollection = maps;
    }

    if ( !InSocialMode() )
      GotoFirstLobbyScreen();
  }
  else if ( newStatus == EClientStatus::InCustomLobby )
  {
    RemoveFirstLobbyScreen();

    if ( !fastReconnectCtxPw ) {
      heroScreen = new NGameX::SelectHeroScreen( gameCtx.Lock() );
      NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( heroScreen ) );
    }
  }
  else if ( newStatus == EClientStatus::InGameSession )
  {
    RemoveFirstLobbyScreen(); // Needed here for custom game reconnect, where we skip InCustomLobby

    if ( heroScreen )
      NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( heroScreen ) );
  }
}



void ClientPW::OnLobbyDataChange()
{
  ClientBase::OnLobbyDataChange();

  if ( Status() == EClientStatus::InCustomLobby )
  {
    set<int> empty;
    UpdateCustomLobbyPlayers( empty );
  }
}



void ClientPW::CreateGame( const char * mapId, int maxPlayers, int autostartPlayers /*= -1*/ )
{
  StrongMT<NWorld::IMapLoader> mapLoader = mapCollection->CreateMapLoader( mapId );
  NI_DATA_VERIFY( mapLoader, NStr::StrFmt( "Could not load map '%s'", mapId ), return );

  ClientBase::CreateGame( mapId, maxPlayers, mapLoader->GetMaxPlayersPerTeam(), autostartPlayers );
}



void ClientPW::GotoFirstLobbyScreen()
{
  if ( fastReconnectCtxPw )
    return;

  //Lobby server requested Player interface, we ready to show GUI
  lobbyScreen = new NGameX::SelectGameModeScreen( gameCtx.Lock() );

  NScreenCommands::PushCommand( NScreenCommands::CreatePushScreenCommand( lobbyScreen ) );
}



void ClientPW::RemoveFirstLobbyScreen()
{
  if ( lobbyScreen )
    NScreenCommands::PushCommand( NScreenCommands::CreatePopScreenCommand( lobbyScreen ) );
}

void ClientPW::UpdateCustomLobbyPlayers( const set<int> & hilitePlayers )
{
  if ( !heroScreen )
    return;
  vector<wstring> lines;
  vector<int> linesIds;

  for (int i = 0; i < 10; ++i) {
    g_selectedHeroes[i].clear();
  }

  int readyPlayers = 0;
  int heroCounter = 0;

  for( int i = 0; i < 2; ++i )
  {
    ETeam::Enum team = i ? ETeam::Team2 : ETeam::Team1;

    lines.push_back( i ? L"Команда Адорнийцев:" : L"Команда Доктов:" );
    linesIds.push_back( -1 );
    for ( int j = 0; j < GameLineup().size(); ++j )
    {
      const SGameMember & memb = GameLineup()[j];
      if( memb.context.team != team )
        continue;
      
      const bool ready = ( ReadyPlayers().find( memb.user.userId ) != ReadyPlayers().end() );
      readyPlayers += ready ? 1 : 0;
      g_selectedHeroes[heroCounter] = memb.context.hero.c_str();

      string newHeroName;

	    if(HeroNameLobby.count(g_selectedHeroes[heroCounter])){
		    newHeroName = (memb.context.original_team == lobby::ETeam::Team2) ? HeroNameLobby[g_selectedHeroes[heroCounter]].HeroNameB : HeroNameLobby[g_selectedHeroes[heroCounter]].HeroNameA;
	    }
      wstring line = NStr::StrFmtW( L"<space:2>%s (%d)  %s %s, %s",
        memb.user.nickname.c_str(),
        memb.user.userId,
        NStr::ToUnicode( newHeroName ).c_str(),
        //memb.context.original_team == lobby::ETeam::Team2 ? L"(Адорниец)" : L"(Докт)",
        memb.context.original_team == lobby::ETeam::Team2 ? L"" : L"", // disabled for some time since skins are random
        ready ? L"<style:green>ready</style>" : L"<style:money>not ready</style>" );

      lines.push_back( line );
      linesIds.push_back( memb.user.userId );
      heroCounter++;
    }
  }

  int totalPlayers = lines.size();
  if (lastRememberedPlayers != totalPlayers) {
    // Notify all members to be ready only if new not every player is ready
    // In other case all players will be ready to play, but someone left the game
    if (totalPlayers == readyPlayers) {
      g_needNotifyLobbyClients = true;
    }
  }
  // If someone just connected - notify
  if (lastRememberedPlayers < totalPlayers) {
    g_needNotifyLobbyClients = true;
  }
  lastRememberedPlayers = totalPlayers;

  heroScreen->UpdatePlayers( lines, linesIds, hilitePlayers );
}

void ClientPW::Award( const vector<roll::SAwardInfo> & _awards )
{
  if (advScreen)
    advScreen->AwardUser(_awards);
}

void ClientPW::CleanUIScreens()
{
  RemoveFirstLobbyScreen();
}

ClientPW::HeroName::HeroName(string nameA, string nameB)
{
	ClientPW::HeroName::HeroNameA = nameA;
	ClientPW::HeroName::HeroNameB = nameB;
}

ClientPW::HeroName::HeroName(){}

void ClientPW::fillHeroNeme()
{
	HeroNameLobby["healer"] = ClientPW::HeroName("Целительница", "Жрица");
	HeroNameLobby["rockman"] = ClientPW::HeroName("Человек-гора", "Рокот");
	HeroNameLobby["mowgly"] = ClientPW::HeroName("Егерь", "Танцующий с волками");
	HeroNameLobby["ratcatcher"] = ClientPW::HeroName("Крысолов", "Повелитель крыс");
	HeroNameLobby["thundergod"] = ClientPW::HeroName("Молниеносный", "Громовержец");
	HeroNameLobby["manawyrm"] = ClientPW::HeroName("Чарозмей", "Магозавр");
	HeroNameLobby["witchdoctor"] = ClientPW::HeroName("Ведун", "Лесовик");
	HeroNameLobby["faceless"] = ClientPW::HeroName("Безликий", "Белая маска");
	HeroNameLobby["highlander"] = ClientPW::HeroName("Горец", "Бессмертный");
	HeroNameLobby["night"] = ClientPW::HeroName("Царица Ночи", "Черная пантера");
	HeroNameLobby["firefox"] = ClientPW::HeroName("Огненная лиса", "Рыжий хвост");
	HeroNameLobby["unicorn"] = ClientPW::HeroName("Дева", "Нимфа");
	HeroNameLobby["frogenglut"] = ClientPW::HeroName("Жабий наездник", "Болотный царь");
	HeroNameLobby["prince"] = ClientPW::HeroName("Дуэлянт", "Принц воров");
	HeroNameLobby["warlord"] = ClientPW::HeroName("Воевода", "Предводитель");
	HeroNameLobby["hunter"] = ClientPW::HeroName("Стрелок", "Охотник");
	HeroNameLobby["mage"] = ClientPW::HeroName("Заклинатель", "Чародей");
	HeroNameLobby["naga"] = ClientPW::HeroName("Мастер клинков", "Отмеченный змеем");
	HeroNameLobby["werewolf"] = ClientPW::HeroName("Клык", "Коготь");
	HeroNameLobby["invisible"] = ClientPW::HeroName("Тень", "Невидимка");
	HeroNameLobby["assassin"] = ClientPW::HeroName("Чистильщик", "Ассасин");
	HeroNameLobby["ghostlord"] = ClientPW::HeroName("Жнец душ", "Душелов");
	HeroNameLobby["marine"] = ClientPW::HeroName("Комбат", "Мейдзин");
	HeroNameLobby["snowqueen"] = ClientPW::HeroName("Крио", "Вьюга");
	HeroNameLobby["archeress"] = ClientPW::HeroName("Лучница", "Амазонка");
	HeroNameLobby["inventor"] = ClientPW::HeroName("Изобретатель", "Изобретатель");
	HeroNameLobby["bard"] = ClientPW::HeroName("Бард", "Муза");
	HeroNameLobby["fairy"] = ClientPW::HeroName("Фикси", "Королева фей");
	HeroNameLobby["artist"] = ClientPW::HeroName("Художница", "Художница");
	HeroNameLobby["witcher"] = ClientPW::HeroName("Ведьмак", "Ведьмак");
	HeroNameLobby["demonolog"] = ClientPW::HeroName("Демонолог", "Демонолог");
	HeroNameLobby["alchemist"] = ClientPW::HeroName("Доктрина", "Доктрина");
	HeroNameLobby["vampire"] = ClientPW::HeroName("Вампир", "Акшар");
	HeroNameLobby["witch"] = ClientPW::HeroName("Ведьма", "Мойра");
	HeroNameLobby["crusader_A"] = ClientPW::HeroName("Да'Ка", "Да'Ка");
	HeroNameLobby["crusader_B"] = ClientPW::HeroName("Ха'Ка", "Ха'Ка");
	HeroNameLobby["monster"] = ClientPW::HeroName("Геноморф", "Химера");
	HeroNameLobby["angel"] = ClientPW::HeroName("Заступница", "Хранительница");
	HeroNameLobby["freeze"] = ClientPW::HeroName("Фриз", "Фриз");
	HeroNameLobby["gunslinger"] = ClientPW::HeroName("Головорез", "Головорез");
	HeroNameLobby["reaper"] = ClientPW::HeroName("Ту'Реху", "Ту'Реху");
	HeroNameLobby["fluffy"] = ClientPW::HeroName("Мими", "Мими");
	HeroNameLobby["rifleman"] = ClientPW::HeroName("Путник", "Путник");
	HeroNameLobby["magicgirl"] = ClientPW::HeroName("Луна", "Луна");
	HeroNameLobby["pinkgirl"] = ClientPW::HeroName("Хулиганка", "Хулиганка");
	HeroNameLobby["ironknight"] = ClientPW::HeroName("Берсерк", "Берсерк");
	HeroNameLobby["fallenangel"] = ClientPW::HeroName("Аггель", "Аггель");
	HeroNameLobby["bladedancer"] = ClientPW::HeroName("Асур", "Асур");
	HeroNameLobby["ent"] = ClientPW::HeroName("Дуболом", "Дуболом");
	HeroNameLobby["plaguedoctor"] = ClientPW::HeroName("Чумной доктор", "Чумной доктор");
	HeroNameLobby["katana"] = ClientPW::HeroName("Катана", "Катана");
	HeroNameLobby["plane"] = ClientPW::HeroName("Авиатор", "Авиатор");
	HeroNameLobby["zealot"] = ClientPW::HeroName("Фанатик", "Фанатик");
	HeroNameLobby["wraithking"] = ClientPW::HeroName("Павший владыка", "Павший владыка");
	HeroNameLobby["dryad"] = ClientPW::HeroName("Дриада", "Дриада");
	HeroNameLobby["stalker"] = ClientPW::HeroName("Странник", "Странник");
	HeroNameLobby["gunner"] = ClientPW::HeroName("Канонир", "Канонир");
	HeroNameLobby["chronicle"] = ClientPW::HeroName("Хроника", "Хроника");
	HeroNameLobby["brewer"] = ClientPW::HeroName("Медовар", "Медовар");
	HeroNameLobby["shadow"] = ClientPW::HeroName("Кара", "Кара");
	HeroNameLobby["wendigo"] = ClientPW::HeroName("Вендиго", "Вендиго");
	HeroNameLobby["trickster"] = ClientPW::HeroName("Трикстер", "Трикстер");
	HeroNameLobby["banshee"] = ClientPW::HeroName("Банши", "Банши");
	HeroNameLobby["shaman"] = ClientPW::HeroName("Шаман", "Шаман");
	HeroNameLobby["bomber"] = ClientPW::HeroName("Подрывница", "Подрывница");
}

} //namespace lobby
