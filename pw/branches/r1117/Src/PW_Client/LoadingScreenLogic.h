#ifndef LOADINGSCREENLOGIC_H_INCLUDED
#define LOADINGSCREENLOGIC_H_INCLUDED

#include "../UI/FSCommandListner.h"

#include "UI/ScreenLogicBase.h"
#include "UI/PreferencesProcessor.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include <map>
class LoadingProgress;

namespace NCore
{
  namespace ETeam
  {
    enum Enum;
  }

  struct PlayerStartInfo;
  struct ClientSettings;
  namespace EBasket
  {
    enum Enum;
  }
}

namespace NDb
{
  struct DBUIData;
  struct HeroesDB;
  struct DBLevelToExperience;
  struct AdvMapDescription;
  struct AdvMapSettings;
  struct AdvMapModeDescription;
  enum EMapType;
}


namespace UI
{
  class ImageLabel;
  class FlashInterface;
}


namespace NGameX
{
  class LoadingStatusHandler;
  class AdventureTooltip;
  class ChatUiController;
  class IgnoreListStorage;
  class IgnoreListController;
  class HeroRankCalculator;

  _interface IPlayerIdMapper;
}

namespace Peered
{
  struct ClientSettings;
}


namespace Game
{

class LoadingFlashInterface;
class LoadingUserUI;
class LoadingHeroes;


struct HeroInfo
{
  HeroInfo(): isProcessed(false), exp(0), isBot(false), force(0),
    raiting(0), winDeltaRaiting(0), loseDeltaRaiting(0), isNovice(false), isPremium(false), heroId(0), partyId(0),
    isAnimatedAvatar(true), leagueIndex(0), ownLeaguePlace(0) {}
  bool isProcessed;
  bool isBot;
  int  exp;
  float force;
  int raiting;
  float winDeltaRaiting;
  float loseDeltaRaiting;
  bool isNovice;
	bool isPremium;
	uint partyId;
	string locale;
  NCore::ETeam::Enum team;
	NCore::ETeam::Enum originalTeam;
  string skinId;
  uint heroId;
  uint userId;
  NCore::EBasket::Enum  basket;
  bool isAnimatedAvatar;
  int  leagueIndex;
  int               ownLeaguePlace;
  nstl::vector<int> leaguePlaces;
};

typedef hash_map<int, Game::HeroInfo> TLineUpHeroesInfo;


class LoadingScreenLogic : public UI::ScreenLogicBase, public UI::IFSCommandListner
{
  NI_DECLARE_REFCOUNT_CLASS_2( LoadingScreenLogic, UI::ScreenLogicBase, UI::IFSCommandListner );

public:
  DECLARE_LUA_TYPEINFO( LoadingScreenLogic );

  LoadingScreenLogic(NGameX::LoadingStatusHandler * statusHandler, const NDb::DBUIData* _uiData, const bool _isSpectator, const bool _isTutorial );
  ~LoadingScreenLogic();

  virtual void OnLoadedScreenLayout();
  virtual void Step( float deltaTime );

  void SetChat (const Strong<NGameX::IPlayerIdMapper>& playerIdMapper, NGameX::ChatUiController * _chatController, NGameX::IgnoreListStorage* _ignoreListStorage, const bool muted, const bool leaver, const bool leaverParty);
  
  // from UI::IFSCommandListner
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

  void SetTempMapBack(const char* back, const char* logo);
  void SetMap( const NDb::AdvMapDescription * _advMapDescription, const NDb::AdvMapSettings * _advMapSettings );
  void SetProgress( float pro );

  void SetOurUserId(int userId, NCore::ETeam::Enum team, NCore::ETeam::Enum original_team, bool isGuardGame,bool isGuildGame, bool isCustomGame);
  void AddPlayer( int index, const NCore::PlayerStartInfo& info, const HeroInfo& heroInfo);
  void SetPlayerProgress( int userId, float pro );

  void DisconnectUser(int userId);
  void ReconnectUser(int userId);

  void MsgChatOpenClose();
	void OpenChanel(int channelID);
  bool CmdCancel();
  void SetHeroInfo( int userId, const HeroInfo & heroInfo, const NCore::ClientSettings & _clientSettings );
  void ShowTeamForce();
  LoadingFlashInterface * GetLoadingFlashInterface() {return flashInterface;}

private:
  bool isShowTeamForce, partyFlag, tamburFlag;
  uint leftTeamForce, rightTeamForce;
  std::map<int, uint> forces;
  void AddModeVisual(const NDb::AdvMapModeDescription * modeDescription);
  void recalcTeamForce(const HeroInfo& heroInfo);

  CObj<NGameX::AdventureTooltip> tooltip;

  NDb::Ptr<NDb::DBUIData> uiData;

  NDb::Ptr<NDb::HeroesDB>   m_heroDb;
  NDb::Ptr<NDb::DBLevelToExperience> levelToExp;

  nstl::vector<NDb::Ptr<NDb::AdvMapModeDescription>> modeDescriptions;

  NDb::Ptr<NDb::AdvMapModeDescription> manoeuvresModeDesc;
  NDb::Ptr<NDb::AdvMapModeDescription> guardModeDesc;
	NDb::Ptr<NDb::AdvMapModeDescription> guildModeDesc;
  NDb::Ptr<NDb::AdvMapModeDescription> customGameDescription;
  NDb::Ptr<NDb::AdvMapDescription>  advMapDescription;

  Weak<UI::FlashContainer2> flashWnd;
  const bool isSpectator;
  const bool isTutorial;

  //flash UI
  Strong<LoadingFlashInterface>   flashInterface;
  Strong<UI::PreferencesProcessor>  preferencesProcessor; 
  Strong<LoadingHeroes> loadingHeroes;
  Weak<NGameX::ChatUiController> chatController;
  Strong<NGameX::HeroRankCalculator>        rankCalculator;
  Strong<NGameX::HeroRankCalculator>        rankMMCalculator;

  Weak<NGameX::LoadingStatusHandler>        loadingStatusHandler;
};




} //Game

#endif //LOADINGSCREENLOGIC_H_INCLUDED
