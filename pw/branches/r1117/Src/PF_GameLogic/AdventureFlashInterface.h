#pragma once

#include "../UI/FlashInterface.h"
#include "IFlashChat.h"
#include "System/StarForce/HiddenVars.h"

namespace avmplus
{
  class DisplayObjectObject;
}


namespace NDb
{
  enum EStat;
  enum EDerivativeStat;
  enum EApplicatorDamageType;
  enum EErrorMessageType;
  enum EMinimapEffects;
}

namespace ShopItemState
{
  enum EShopItemState
  {
    CanBuy = 0,
    NotEnoughPrime = 1
  };
}

namespace TalentUIState
{
  enum ETalentUIState
  {
    Bought = 0,
    CanBuy = 1,
    NotEnoughDevPoints = 2,
    NotEnoughPrime = 3
  };
};

namespace ActionBarSlotState
{
  enum EActionBarSlotState
  {
    Active = 0,
    ActiveSpecial = 1,
    ActivetedSpecial = 2,
    NotEnoughMana = 3,
    Disabled = 4, 
    Chosen = 5,
    NotEnoughLife = 6,
  };
};


namespace FlashWindowsType
{ 
  enum Enum
  {
    Talents = 0,
    CharStat = 1,
    Inventory = 2,
    QuestLog = 3,
    SocialBar = 4,
    CurStatistics = 5,
    Portal = 6,
    //EscMenu = 7, we dont open this directly
    //Shop = 8,
    Chat = 9,
    SmartChat = 10,
  };
}

namespace PlayerLeaveType
{ 
	enum Enum
	{
		Left = 0,
		Disconnected = 1
	};
}



namespace NGameX
{

struct HeroInfoParams
{
 Protection::HiddenVar<int, 14>::T level;
 Protection::HiddenVar<int, 15>::T curHealth;
 Protection::HiddenVar<int, 16>::T maxHealth;
 Protection::HiddenVar<int, 17>::T curMana;
 Protection::HiddenVar<int, 18>::T maxMana;
 bool isVisible;
 bool isPickable;
 int timeToRessurect;
 float ultimateCoolDown;
 float channgeling;
 float healthRegen;
 float manaRegen;
 bool isCameraLocked;
};

}

inline void Recrypt( NGameX::HeroInfoParams &a )
{
  Recrypt( a.level );
  Recrypt( a.curHealth );
  Recrypt( a.maxHealth );
  Recrypt( a.curMana );
  Recrypt( a.maxMana );
}

namespace NGameX
{

inline bool operator==( const HeroInfoParams &a, const HeroInfoParams &b ) 
{ 
  return 
    a.level == b.level &&
    a.ultimateCoolDown == b.ultimateCoolDown &&
    a.curHealth == b.curHealth &&
    a.maxHealth == b.maxHealth &&
    a.curMana == b.curMana &&
    a.maxMana == b.maxMana &&
    a.isVisible == b.isVisible &&
    a.isPickable == b.isPickable &&
    a.timeToRessurect == b.timeToRessurect &&
    a.channgeling == b.channgeling &&
    a.healthRegen == b.healthRegen &&
    a.manaRegen == b.manaRegen;
}

//This class is a C++ communication wrapper for MainInterface.as
class AdventureFlashInterface : public UI::FlashInterface, public IFlashChat, public IFlashSmartChat
{
  NI_DECLARE_REFCOUNT_CLASS_3( AdventureFlashInterface, UI::FlashInterface, IFlashChat, IFlashSmartChat);

public:
  AdventureFlashInterface( UI::FlashContainer2 * _flashWnd, const char* _className );

public:

  //dragonwald
  void ShowAlwaysHeroesLevels(bool show);
  void ShowCTEUI(bool show);
  void SetCTEAltarStatus( NDb::EFaction faction, int curHealth, int maxHealth, int damageIntensityType);


  //team info
  void SetForceColorTable(const vector<int> & forceTable,const vector<uint> & colorTable);
  void SetOurHeroIdententity( int heroID, NDb::EFaction faction, NDb::EApplicatorDamageType damageType, int leagueIndex, int ownLeaguePlace, const vector<int>& leaguePlaces);
 
  void SetHeroIdentity( 
    const wstring& heroName, 
    const wstring& heroClass, 
    int heroID, 
    const char * path, 
    bool isMale, 
    bool isEnemy, 
    bool isBot, 
    int force, 
    NDb::EFaction faction, 
    NDb::EFaction originalFaction, 
    float raiting, 
    const char * rankPath, 
    const wstring & rankTooltip,
		bool isPremium, uint partyId,
    string & flagIcon, wstring & flagTooltip, bool isAnimatedAvatar, int leagueIndex, int ownLeaguePlace, const vector<int>& leaguePlaces);

  void ShowHeroPortrait( int heroID, bool isEnemy );

  void SetHeroParams( int heroID, const HeroInfoParams & unitParams);
  void SetFriendship(int heroID, bool areFriends, bool requestSent);

  void SetHeroChatMuted(int heroID, bool chatMuted);
  void SetHeroCustomEnergy(int heroID, const wstring& name, const unsigned color);

  //selection info
  void SetSelectionParams(const wstring & unitName, const HeroInfoParams & unitParams, bool isEnemy, int heroId);
  void SetSelectionInfoIcon(const char* path, int heroID, bool isMale, bool isAnimatedAvatar);

  //talent bar
//public function SetTalentIcon(column:int, raw:int, path:String, isActive:Boolean,desiredIndex:int, upgradeLevel:int, isClassTalent:Boolean):void
  void SetTalentIcon(int column, int raw, const char * path, const char * altPath, bool isActive, int desiredIndex, int upgradeLevel, bool isClassTalent, int cost);
  void SetTalentState(int column, int raw, TalentUIState::ETalentUIState talentState);
  void NotifyTalentsStateChaged();

  //selection talent bar
  void SetSelectionTalentIcon( int column, int raw, const char* path, bool isActive, int upgradeLevel );
  void SetSelectionTalentState( int column, int raw, TalentUIState::ETalentUIState talentState );
  void SetSelectionTalentBarUnitID( int heroId );

  //action bar
  void SetTalentStatus(int column, int raw, ActionBarSlotState::EActionBarSlotState status, float cooldown, float maxCooldownValue, bool isAlternativeStateOn);
  void SetPortalStatus(ActionBarSlotState::EActionBarSlotState status, float cooldown, float maxCooldownValue);

  void SetGlobalCooldown(float preparedness, float maxCooldownValue);
  void UseSlot(int slot);
  void LockActionBar(bool lock);
  void TempUnlockActionBar(bool unlock);

  void SetHeroDevelopmentParams(int prime, int zzGold);

  //minimap
  void AddSignal(float x, float y);
  void AddSignal(float x, float y, unsigned color);
  void AddSignal(float x, float y, unsigned color, float lifeTime);
  void SetCameraLock(bool lock);
  void SetMinimapEffect( int index, NDb::EMinimapEffects effect );
  void UpdateMinimapEffect( int index, float x, float y );

  //shop
  void SetShopItemsCount(int count);
  void SetShopItemIcon(int index, const char * path);
  void ShowShop(bool show );
  void SetShopItemState(int index, ShopItemState::EShopItemState state);

  //inventory
  void AddInventoryItemToActionBar(int index);
  void SetInventoryItemIcon(int index, const char * path);
  void SetInventoryItemState(int index, int count, ActionBarSlotState::EActionBarSlotState state, float cooldown, float maxCooldownValue);

  //impulse buffs
  void ShowImpulseBuff(const char * path);
  void ResetImpulsBuff(const char * path);
  void HideImpulseBuff(bool wasBought, bool fromKeyboard);

  //windows
  void HideAllWindows();

  //esc
  bool OnEscape();
  void OpenEscMenu();

  //close
  void ShowTryExit();

  //minigame
  void EnterMinigame();
  void LeaveMinigame();

  //victory/defeat
  void GameEnd(bool isVictory, const char * endImage, bool dontShowStatistics, bool dontShowDialog);
  void ConfigurePlaySameTeamFeature(bool available, int timeOut);
  void HandlePlaySameTeamDecision(const int id, const bool agreed);
  void SetFirstWin(const char * iconPath, const wstring & tooltip);

  //cur game statistics
  void ShowStatistics(bool show); 
  void SetGameProgress(float humanTerrain, float elfTerrain, int gameTime, int timeToCreepSpawn);
  void SetHeroGameProgress(int heroID, int kills, int deaths, int assists, int score, int prime);
  void SetHeroExperience(int curExp, int earnedExp, const vector<int> & levelsTabel);

  //char stat
  void SetCharStatUnit(bool isSelection, int heroID, const char * iconPath, const wstring& unitName, NDb::EFaction faction, NDb::EApplicatorDamageType damageType );
  void SetCharStatUnitParams(bool isSelection,  int heroID, int level,  int curHealth, int maxHealth, int curMana, int maxMana, bool isVisible);

  void SetBaseStat(bool isSelection, NDb::EStat valueType, int value, int addition, bool isImportant);
  void SetDerivativeStat(bool isSelection, NDb::EDerivativeStat valueType, int value);

  //buffs
  void SetBuffIcon(bool isSelection, const char * path, int index, bool isPositive);
  void SetBuffStatus(bool isSelection, int index, float cooldown, int count);

  //final stat
  void SetFinalHeroTitle(int heroID, const wstring & heroTitle, const char * heroTitleIcon, int tooltipID);
  void AddHeroExploit(int heroID, const char * exploitIcon, int tooltipID);
  void AddHeroResults(int heroID, const char* resultIcon, int resultCount, const wstring & resultName);
	void AwardDeltaRaiting(float deltaRaiting, const char * rankPath, const wstring & rankTooltip);

  //error messages

  void SetErrorMessage(NDb::EErrorMessageType msgType, const wstring & msg, bool playSound, float lifeTime);
  void ShowErrorMessage(NDb::EErrorMessageType msgType, bool show);
  void ShowErrorEvent(const wstring & msg, bool playSound, float lifeTime);

  //player left
  void MarkPlayerLeft(int heroID, PlayerLeaveType::Enum type );
  void MarkPlayerReconnected(int heroID);

  //Win management
  void ShowHideWindow(FlashWindowsType::Enum winType);

  //announcements
  void ShowAnnouncement(const wstring & announcementText, float lifeTime, int priority);
  void SetAnnouncementPart(bool right, const char * portraitIcon, int level, const wstring & name, int fraction,int heroId);
  void ShowSpawnCreepsAnnouncement(const char *  leftIcon, const char * rightIcon, const wstring & announcementText);

  //chat IFlashChat
  virtual void AddChannel(NDb::EChatChannel channel,  const wstring & channelName, uint channelColor, bool showChannelName, bool showPlayerName, bool canWrite2Channel);
  virtual void AddChannelShortCut(NDb::EChatChannel channel, const wstring & shortcut);
  virtual void AddMessage(NDb::EChatChannel channel, const wstring & playerName, const wstring & message);
  virtual void AddMessage(NDb::EChatChannel channel, const wstring & playerName, const wstring & message, const int playerId);
  virtual void SetDefaultChannel(NDb::EChatChannel channelID);
  virtual void SetChatVisible(bool visible);
  virtual void SetChatOff(bool isChatOff);
  virtual void SetPlayerIcon(const int playerId, const string& path);
  virtual void SetPlayerHeroId(const int playerId, const int heroId, const int teamId);
	virtual void OpenChatChannel(NDb::EChatChannel channelID);

  //hot keys
  void OpenCloseChat();

  //awards
	void AddOurHeroAward(int awardID, const char * awardIcon, int awardCount, bool isTasty, bool thanksToPremium);
	void FinishAwarding();
  void StartAwarding();

  //IgnoreList
  void IgnoreUser(const int playerId);
  void RemoveIgnore(const int playerId);

  //Tutorial
  void ShowUIBlock( const char* id, bool show );
  void ShowAllUIBlocks( bool show );
  void BlockActionBar( bool block );
  //Highlight
  void ShowTutorialTalentHighlight( int column, int raw, bool show );
  void ShowTutorialInventoryItemHighlight( int slot, bool show );
  void ShowTutorialShopItemHighlight( int slot, bool show );
  void ShowTutorialActionBarItemHighlight( int slot, bool show );
  void ShowTutorialElementHighlight( string elementName, bool show );
  void ShowTutorialHeroHighlight( int heroID, bool show );
  void ShowTutorialHeroLevelHighlight( int heroID, bool show );
  void ShowTutorialOvertipLevelHighlight( bool show, float x, float y );
  //Quests
  void AddQuest( int questId, bool primary, wstring text, int totalGoals );
  void UpdateQuest( int questId, int complitedGoals );
  void UpdateQuestText( int questId, wstring text );
  void RemoveQuest( int questId );
  //Debug info
  void SetClientVersion(const wstring & version);

  //Dialogs and cinematic
  void ShowNPC( const char* icon, const wstring& name );
  void HideNPC();
  void StartCinematic();
  void StopCinematic();
  void ShowCinematicNPC( const char* icon, const wstring& name );
  void ShowCinematicMessage( const wstring& text, uint color );
  void SetQuestHintLine( const wstring& text, const char* bubbleViewType );
  void ShowCinematicNextButton( const bool show );
  void EnableCinematicNextButton( const bool enable );
  void ShowCinematicNextButtonAnim( const bool show );
  //Script message box
  void ShowMessageBox( const wstring& header, const wstring& text );

  avmplus::Atom GetNamedDisplayObject( const char* name, bool withBubble );
  avmplus::Atom GetTalentBarItemDisplayObject( int column, int raw, bool withBubble );
  avmplus::Atom GetActionBarItemDisplayObject( int slot, bool withBubble );
  avmplus::Atom GetShopItemDisplayObject( int slot, bool withBubble );
  avmplus::Atom GetInventoryItemDisplayObject( int slot, bool withBubble );
  avmplus::Atom GetHeroDisplayObject( int playerId, bool withBubble );

  // Bubbles
  void ShowTalentBubble( int column, int row, bool show, const wstring& text, string bubbleViewType, int bubbleIndex );
  void ShowActionBarButtonBubble( int index, bool show, const wstring& text, string bubbleViewType, int bubbleIndex );
  void ShowInventoryBarButtonBubble( int index, bool show, const wstring& text, string bubbleViewType, int bubbleIndex );
  void ShowShopBarButtonBubble( int index, bool show, const wstring& text, string bubbleViewType, int bubbleIndex );
  void ShowHeroBubble( int index, bool show, const wstring& text, string bubbleViewType, int bubbleIndex );
  void ShowBubble( string elementName, bool show, const wstring& text, string bubbleViewType, int bubbleIndex );

  bool IsWindowVisible( int winId );
  int GetTalentActionBarIndex( int column, int row );
  int GetInventoryItemActionBarIndex( int index );
  void HideSurrenderButtonForEscMenu();
  void SwitchToTutorialMode();

  void SetStatisticBackImages(const char * normal, const char * loose, const char * win );

  void SwitchToSpectatorMode();
	void RaitingPenaltyEnabled(bool enabled);
	void SetComplainsCount( int complaintsToday, int complaintsMax );
	void SetComplainsItem(int index, const wstring & name);

  void SetBindString(string element);

  void ShowHintDialog(const string& dialogId, const wstring &title, const wstring& hintText, const string &picture);
  int GetSpectatePlayerId( int hotkeyIdx );

  // IFlashSmartChat
  void SmartChatActivate();
  void SmartChatActivateCategory(const unsigned id);
  void SmartChatDeactivate();
  void SmartChatBeginUpdate();
  void SmartChatEndUpdate();
  void SmartChatBeginCategory(const unsigned id, const string& key, const wstring& name);
  void SmartChatEndCategory();
  void SmartChatAddMessage(const unsigned id, const string& key, const wstring& text);
  void SmartChatAddCancel(const unsigned id, const string& key);

  //
  void SetMinimapTargetZoneColor(const unsigned value);
  void SetMinimapTargetZoneThickness(const unsigned value);
  void ShowMinimapTargetZone(const float x, const float y, const float radius);
  void HideMinimapTargetZone();

  //
  void DayNightUpdateState(const bool night, const float stateFraction);
  void DayNightHideUI(const bool hide);
};

}
