#pragma once

#include "../UI/FlashInterface.h"
#include "../PF_GameLogic/IFlashChat.h"

namespace NDb
{
  enum EFaction;
}


namespace Game
{

  class LoadingFlashInterface:public UI::FlashInterface, public NGameX::IFlashChat
{
  NI_DECLARE_REFCOUNT_CLASS_2( LoadingFlashInterface, UI::FlashInterface, NGameX::IFlashChat );

public:
  LoadingFlashInterface( UI::FlashContainer2 * _flashWnd, const char* _className );

public:

  //public function SetHeroIdentity(heroID:int, fraction:int, heroName:String, iconPath:String,heroLevel:int,isMale:Boolean):void
  void SetHeroIdentity( int heroID, NDb::EFaction faction, const wstring& heroName, const char * iconPath, int heroLevel, bool isMale, const char * classIcon, uint partyId, string & flagIcon, wstring & flagTooltip, bool isAnimatedAvatar, int leagueIndex);
  
  //public function SetHeroLoadProgress(heroId:int, loadProgress:Number, isLeftGame:Boolean):void
  void SetHeroLoadProgress(int heroId, float loadProgress, bool isLeftGame);
  void SetOurHeroId(int heroID, NDb::EFaction faction);
  void SetHeroLevel(int heroId, int level);
  void SetPlayersFaction(NDb::EFaction leftFaction, NDb::EFaction rightFaction);
  void SetMapBack(const char* back, const char* logo); 

  void SetForceColorTable(const vector<int> & forceTable,const vector<uint> & colorTable);
  void SetTeamForce(const wstring & forceLeft,const wstring & forceRight);
  void SetHeroForce(int heroId, int force);
  void SetHeroRaiting(int heroId, int raiting, float deltaWin, float deltaLose, bool isNovice, const char* rankIcon, const wstring & rankName);
	void SetHeroPremium(int heroId, bool hasPremium, NDb::EFaction originalFraction);

  void AddModeDescription(const char * modeImage, int id) ;

  void SetLoadingStatusText( const wstring & statusText);
	void SetLocales(const char* imageLeft,const wstring & toolTipLeft, const char* imageRight, const wstring & toolTipRight);
  void SetLoadingState (bool isPreloading);

  void SetTip(const wstring & tip);

  void SwitchToSpectatorMode();

  //chat
  virtual void AddChannel(NDb::EChatChannel channel,  const wstring & channelName, uint channelColor, bool showChannelName, bool showPlayerName, bool canWrite2Channel);
  virtual void AddChannelShortCut(NDb::EChatChannel channel, const wstring & shortcut);
  virtual void AddMessage(NDb::EChatChannel channel, const wstring & playerName, const wstring & message);
  virtual void AddMessage(NDb::EChatChannel channel, const wstring & playerName, const wstring & message, const int playerId);
  virtual void SetDefaultChannel(NDb::EChatChannel channelID);
  virtual void SetChatVisible(bool visible);
  virtual void SetChatOff(bool isChatOff);
  virtual void SetPlayerIcon(const int playerId, const string& path);
  virtual void SetPlayerHeroId(const int playerId, const int heroId, const int teamId);
  virtual void IgnoreUser(const int playerId);
  virtual void RemoveIgnore(const int playerId);

  void OpenCloseChat();
	void OpenChanel(int channelID);
  void OnEscape();
};

}





