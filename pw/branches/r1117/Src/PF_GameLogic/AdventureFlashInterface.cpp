#include "StdAfx.h"

#include "AdventureFlashInterface.h"


#define FLASH_INTERFACE_ENTER_FUNCTION(_funcName) \
  CallMethod( _funcName

#define PUSH_ARG(arg) \
  , arg

#define CALL_FUNCTION );
 
namespace NGameX
{

AdventureFlashInterface::AdventureFlashInterface( UI::FlashContainer2 * _flashWnd, const char* _className ) :
  FlashInterface( _flashWnd, _className )
{

}


void AdventureFlashInterface::SetForceColorTable( const vector<int> & forceTable,const vector<uint> & colorTable )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetForceColors")
  PUSH_ARG(forceTable)
  PUSH_ARG(colorTable)
  CALL_FUNCTION;
}


//dragonwald (CTE)
void AdventureFlashInterface::ShowAlwaysHeroesLevels( bool show )
{
    CallMethod( "ShowAlwaysHeroesLevels", show );
}

void AdventureFlashInterface::ShowCTEUI( bool show )
{
  CallMethod( "ShowCTEUi", show );
}

void AdventureFlashInterface::SetCTEAltarStatus( NDb::EFaction faction, int curHealth, int maxHealth, int damageIntensityType )
{
  CallMethod( "SetCTEAltarStatus", faction, curHealth, maxHealth, damageIntensityType );
}


void AdventureFlashInterface::SetOurHeroIdententity( int heroID, NDb::EFaction faction, NDb::EApplicatorDamageType damageType, int leagueIndex, int ownLeaguePlace, const vector<int>& leaguePlaces)
{
  CallMethod( "SetOurHeroIdententity", heroID, faction, (int)damageType, leaguePlaces, leagueIndex, ownLeaguePlace);
}

void AdventureFlashInterface::SetHeroIdentity( 
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
										 bool isPremium, uint partyId, string & flagIcon, wstring & flagTooltip, bool isAnimatedAvatar, int leagueIndex, int ownLeaguePlace, const vector<int>& leaguePlaces)
{
  CallMethod( isEnemy?  "SetEnemyHeroIdentity" :"SetFriendlyHeroIdentity", 
    heroID,
    heroName,
    heroClass,
    path,
    isMale,
    isBot,
    force,
    faction,
    originalFaction,
    raiting,
    leaguePlaces,
    rankPath,
    rankTooltip,
    isPremium, 
	(int)partyId, flagIcon, flagTooltip, isAnimatedAvatar, leagueIndex, ownLeaguePlace);
  
}
void AdventureFlashInterface::ShowHeroPortrait( int heroID, bool isEnemy )
{
  CallMethod( "ShowHeroPortrait", heroID, isEnemy );
}

void AdventureFlashInterface::SetHeroParams( int heroID, const HeroInfoParams & unitParams)
{
  CallMethod( "SetHeroParams", heroID, unitParams.level, unitParams.curHealth, unitParams.maxHealth, 
    unitParams.curMana, unitParams.maxMana, unitParams.isVisible, unitParams.isPickable, unitParams.timeToRessurect,
	unitParams.channgeling, unitParams.healthRegen, unitParams.manaRegen, unitParams.isCameraLocked, unitParams.ultimateCoolDown);
}


void AdventureFlashInterface::SetFriendship( int heroID, bool areFriends, bool requestSent)
{
  CallMethod( "SetFriendship", heroID, areFriends, requestSent );
}

//public function SetHeroChatMuted(heroId:int, chatMuted:Boolean):void
void AdventureFlashInterface::SetHeroChatMuted(int heroID, bool chatMuted)
{
  CallMethod("SetHeroChatMuted", heroID, chatMuted);
}

//public function SetHeroCustomEnergy(heroID:int, name:String, color:uint):void
void AdventureFlashInterface::SetHeroCustomEnergy(int heroID, const wstring& name, const unsigned color)
{
  CallMethod("SetHeroCustomEnergy", heroID, name, color);
}

//public function SetSelectionParams(heroName:String,level:int,curHealth:int,maxHealth:int,curMana:int,maxMana:int,isEnemy:Boolean,channelingProgress:Number,healthRegen:Number=0,manaRegen:Number =0, heroID:int = -1):void
void AdventureFlashInterface::SetSelectionParams( const wstring & unitName, const HeroInfoParams & unitParams, bool isEnemy, int heroId )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetSelectionParams")
  PUSH_ARG(unitName)
  PUSH_ARG(unitParams.level)
  PUSH_ARG(unitParams.curHealth)
  PUSH_ARG(unitParams.maxHealth)
  PUSH_ARG(unitParams.curMana)
  PUSH_ARG(unitParams.maxMana)
  PUSH_ARG(isEnemy)
  PUSH_ARG(unitParams.channgeling)
  PUSH_ARG(unitParams.healthRegen)
  PUSH_ARG(unitParams.manaRegen)
  PUSH_ARG(heroId)
  CALL_FUNCTION;
}

//public function setSelectionInfoIcon(path:String):void
void AdventureFlashInterface::SetSelectionInfoIcon( const char* path, int heroID, bool isMale, bool isAnimatedAvatar )
{
  FLASH_INTERFACE_ENTER_FUNCTION("setSelectionInfoIcon")
  PUSH_ARG(path)
  PUSH_ARG(heroID)
  PUSH_ARG(isMale)
  PUSH_ARG(isAnimatedAvatar)
  CALL_FUNCTION;
}



void AdventureFlashInterface::SetTalentIcon( int column, int raw, const char * path, const char * altPath, bool isActive, int desiredIndex, int upgradeLevel, bool isClassTalent, int cost)
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetTalentIcon")
  PUSH_ARG(column)
  PUSH_ARG(raw)
  PUSH_ARG(path)
  PUSH_ARG(altPath)
  PUSH_ARG(isActive)
  PUSH_ARG(desiredIndex)
  PUSH_ARG(upgradeLevel)
  PUSH_ARG(isClassTalent)
  PUSH_ARG(cost)
  CALL_FUNCTION;
}

//public function SetTalentState(column:int, raw:int, state:int)
void AdventureFlashInterface::SetTalentState( int column, int raw, TalentUIState::ETalentUIState talentState )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetTalentState")
  PUSH_ARG(column)
  PUSH_ARG(raw)
  PUSH_ARG((int)talentState)
  CALL_FUNCTION;
}

//public function OnTalentsStateChanged()
void AdventureFlashInterface::NotifyTalentsStateChaged()
{
  CallMethod("OnTalentsStateChanged");
}

//public function SetTalentStatus(column:int, raw:int, status:int, cooldown:Number)
void AdventureFlashInterface::SetTalentStatus(int column, int raw, ActionBarSlotState::EActionBarSlotState status, float cooldown, float maxCooldownValue, bool isAlternativeStateOn)
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetTalentStatus")
  PUSH_ARG(column)
  PUSH_ARG(raw)
  PUSH_ARG((int)status)
  PUSH_ARG(cooldown)
  PUSH_ARG(maxCooldownValue)
	PUSH_ARG(isAlternativeStateOn)
  CALL_FUNCTION;  
}


void AdventureFlashInterface::SetPortalStatus( ActionBarSlotState::EActionBarSlotState status, float cooldown, float maxCooldownValue )
{
  CallMethod( "SetPortalStatus", (int)status, cooldown, maxCooldownValue );
}

//public function SetSelectionTalentIcon(column:int, raw:int, path:String)
void AdventureFlashInterface::SetSelectionTalentIcon( int column, int raw, const char* path, bool isActive, int upgradeLevel )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetSelectionTalentIcon")
    PUSH_ARG(column)
    PUSH_ARG(raw)
    PUSH_ARG(path)
    PUSH_ARG(isActive)
    PUSH_ARG(upgradeLevel)
    CALL_FUNCTION;
}

//public function SetSelectionTalentState(column:int, raw:int, state:int)
void AdventureFlashInterface::SetSelectionTalentState( int column, int raw, TalentUIState::ETalentUIState talentState )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetSelectionTalentState")
    PUSH_ARG(column)
    PUSH_ARG(raw)
    PUSH_ARG((int)talentState)
    CALL_FUNCTION;
}

//public function SetSelectionTalentBarUnitID(heroId:int)
void AdventureFlashInterface::SetSelectionTalentBarUnitID( int heroId )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetSelectionTalentBarUnitID")
    PUSH_ARG(heroId)
    CALL_FUNCTION;
}

void AdventureFlashInterface::SetGlobalCooldown( float preparedness, float maxCooldownValue)
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetGlobalCooldown")
  PUSH_ARG(preparedness)
  PUSH_ARG(maxCooldownValue)
  CALL_FUNCTION;
}

//public function UseSlot(cooldown:int)
void AdventureFlashInterface::UseSlot( int slot )
{
  FLASH_INTERFACE_ENTER_FUNCTION("UseSlot")
  PUSH_ARG(slot)
  CALL_FUNCTION;
}


void AdventureFlashInterface::LockActionBar( bool lock )
{
  CallMethod( "LockActionBar", lock );
}

void AdventureFlashInterface::TempUnlockActionBar( bool unlock )
{
   CallMethod( "TempUnlockActionBar", unlock );
}




//public function SetHeroDevelopmentParams(prime:int,zzGold:int):void
void AdventureFlashInterface::SetHeroDevelopmentParams( int prime, int zzGold )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetHeroDevelopmentParams")
  PUSH_ARG(prime)
  PUSH_ARG(zzGold)
  CALL_FUNCTION;
}


void AdventureFlashInterface::AddSignal( float x, float y)
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddSignal")
  PUSH_ARG(x)
  PUSH_ARG(y)
  CALL_FUNCTION;
}

void AdventureFlashInterface::AddSignal(float x, float y, unsigned color)
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddSignal")
  PUSH_ARG(x)
  PUSH_ARG(y)
  PUSH_ARG((color & 0x00FFFFFF))
  CALL_FUNCTION;
}

void AdventureFlashInterface::AddSignal(float x, float y, unsigned color, float lifeTime)
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddSignal")
  PUSH_ARG(x)
  PUSH_ARG(y)
  PUSH_ARG((color & 0x00FFFFFF))
  PUSH_ARG(lifeTime)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetCameraLock( bool lock )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetCameraMode")
  PUSH_ARG(lock)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetMinimapEffect( int index, NDb::EMinimapEffects effect )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetMinimapEffect")
  PUSH_ARG(index)
  PUSH_ARG(effect)
  CALL_FUNCTION;
}

void AdventureFlashInterface::UpdateMinimapEffect( int index, float x, float y)
{
  FLASH_INTERFACE_ENTER_FUNCTION("UpdateMinimapEffect")
  PUSH_ARG(index)
  PUSH_ARG(x)
  PUSH_ARG(y)
  CALL_FUNCTION;
}

//////////////////////////////////////////////////////////////////////////
void AdventureFlashInterface::SetShopItemsCount( int count )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetShopItemsCount")
  PUSH_ARG(count)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetShopItemIcon( int index, const char * path )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetShopItemIcon")
  PUSH_ARG(index)
  PUSH_ARG(path)
  CALL_FUNCTION;
}

void AdventureFlashInterface::ShowShop( bool show )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowShop")
  PUSH_ARG(show)
  CALL_FUNCTION;
}


void AdventureFlashInterface::SetShopItemState( int index, ShopItemState::EShopItemState state )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetShopItemState")
  PUSH_ARG(index)
  PUSH_ARG((int)state)
  CALL_FUNCTION;
}

//////////////////////////////////////////////////////////////////////////
void AdventureFlashInterface::AddInventoryItemToActionBar( int index )
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddInventoryItemToActionBar")
  PUSH_ARG(index)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetInventoryItemIcon( int index, const char * path )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetInventoryItemIcon")
  PUSH_ARG(index)
  PUSH_ARG(path)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetInventoryItemState( int index, int count, ActionBarSlotState::EActionBarSlotState state, float cooldown, float maxCooldownValue )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetInventoryItemState")
  PUSH_ARG(index)
  PUSH_ARG(count)
  PUSH_ARG((int)state)
  PUSH_ARG(cooldown)
  PUSH_ARG(maxCooldownValue)
  CALL_FUNCTION;
}

//////////////////////////////////////////////////////////////////////////
//Impulse Buffs
//////////////////////////////////////////////////////////////////////////
void AdventureFlashInterface::ShowImpulseBuff( const char * path )
{
	FLASH_INTERFACE_ENTER_FUNCTION("ShowImpulseBuff")
	PUSH_ARG(path)
	CALL_FUNCTION;
}

void AdventureFlashInterface::ResetImpulsBuff( const char * path )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ResetImpulsBuff")
  PUSH_ARG(path)
  CALL_FUNCTION;
}

void AdventureFlashInterface::HideImpulseBuff( bool wasBought, bool fromKeyboard )
{
	FLASH_INTERFACE_ENTER_FUNCTION("HideImpulseBuff")
	PUSH_ARG(wasBought)
	PUSH_ARG(fromKeyboard)
	CALL_FUNCTION;
}

//////////////////////////////////////////////////////////////////////////
//others
//////////////////////////////////////////////////////////////////////////
void AdventureFlashInterface::HideAllWindows()
{
	FLASH_INTERFACE_ENTER_FUNCTION("HideAllWindows")
	CALL_FUNCTION;
}

bool AdventureFlashInterface::OnEscape()
{
  return AtomGetBool(CallMethod("OnEscape"));
}

void AdventureFlashInterface::OpenEscMenu()
{
  CallMethod( "OpenEscMenu");
}

void AdventureFlashInterface::ShowTryExit()
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowTryExit")
  CALL_FUNCTION;
}

void AdventureFlashInterface::EnterMinigame()
{
  FLASH_INTERFACE_ENTER_FUNCTION("EnterMinigame")
  CALL_FUNCTION;
}

void AdventureFlashInterface::LeaveMinigame()
{
  FLASH_INTERFACE_ENTER_FUNCTION("LeaveMinigame")
  CALL_FUNCTION;
}

//////////////////////////////////////////////////////////////////////////
void AdventureFlashInterface::GameEnd( bool isVictory, const char * endImage, bool dontShowStatistics, bool dontShowDialog )
{
  CallMethod("GameEnd", isVictory, endImage, dontShowStatistics, dontShowDialog);
}

void AdventureFlashInterface::ConfigurePlaySameTeamFeature(bool available, int timeOut)
{
  CallMethod("ConfigurePlaySameTeamFeature", available, timeOut);
}

void NGameX::AdventureFlashInterface::HandlePlaySameTeamDecision(const int id, const bool agreed)
{
  CallMethod("HandlePlaySameTeamDecision", id, agreed);
}

void AdventureFlashInterface::SetFirstWin( const char * iconPath, const wstring & tooltip )
{
 CallMethod( "SetFirstWin", iconPath,  tooltip);
}


//////////////////////////////////////////////////////////////////////////
void AdventureFlashInterface::ShowStatistics( bool show )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowStatistics")
  PUSH_ARG(show)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetGameProgress( float humanTerrain, float elfTerrain, int gameTime, int timeToCreepSpawn )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetGameProgress")
  PUSH_ARG(humanTerrain)
  PUSH_ARG(elfTerrain)
  PUSH_ARG(gameTime)
  PUSH_ARG(timeToCreepSpawn)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetHeroGameProgress( int heroID, int kills, int deaths, int assists, int score, int prime )
{
	CallMethod( "SetHeroGameProgress", heroID, kills, deaths, assists,  score, prime);
}

void AdventureFlashInterface::SetHeroExperience( int curExp, int earnedExp,const vector<int> & levelsTabel )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetStatisticExperienceBar")
  PUSH_ARG(curExp)
  PUSH_ARG(earnedExp)
  PUSH_ARG(levelsTabel)
  CALL_FUNCTION;
}


//////////////////////////////////////////////////////////////////////////
void AdventureFlashInterface::SetBaseStat( bool isSelection, NDb::EStat valueType, int value, int addition, bool isImportant )
{
 	CallMethod( "SetBaseStat", isSelection, (int)valueType, value, addition,  isImportant);
}

void AdventureFlashInterface::SetDerivativeStat( bool isSelection, NDb::EDerivativeStat valueType, int value )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetDerivativeStat")
  PUSH_ARG(isSelection)
  PUSH_ARG((int)valueType)
  PUSH_ARG(value)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetCharStatUnit( bool isSelection, int heroID, const char * iconPath, const wstring& unitName, NDb::EFaction faction, NDb::EApplicatorDamageType damageType )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetCharStatUnit")
  PUSH_ARG(isSelection)
  PUSH_ARG(heroID)
  PUSH_ARG(iconPath)
  PUSH_ARG(unitName)
  PUSH_ARG((int)faction)
  PUSH_ARG((int)damageType)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetCharStatUnitParams( bool isSelection, int heroID,int level, int curHealth, int maxHealth, int curMana, int maxMana, bool isVisible )
{
  CallMethod( "SetCharStatUnitParams", isSelection, heroID, level, curHealth,  maxHealth, curMana, maxMana, isVisible );
}

//////////////////////////////////////////////////////////////////////////
void AdventureFlashInterface::SetBuffIcon( bool isSelection, const char * path, int index, bool isPositive )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetBuffIcon")
  PUSH_ARG(isSelection)
  PUSH_ARG(path)
  PUSH_ARG(index)
  PUSH_ARG(isPositive)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetBuffStatus( bool isSelection, int index, float cooldown, int count )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetBuffStatus")
  PUSH_ARG(isSelection)
  PUSH_ARG(index)
  PUSH_ARG(cooldown)
  PUSH_ARG(count)
  CALL_FUNCTION;
}

//////////////////////////////////////////////////////////////////////////
void AdventureFlashInterface::SetFinalHeroTitle( int heroID,  const wstring & heroTitle, const char * heroTitleIcon, int tooltipID )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetFinalHeroTitle")
  PUSH_ARG(heroID)
  PUSH_ARG(heroTitle)
  PUSH_ARG(heroTitleIcon)
  PUSH_ARG(tooltipID)
  CALL_FUNCTION;
}


void AdventureFlashInterface::AddHeroExploit( int heroID, const char * exploitIcon, int tooltipID )
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddHeroExploit")
  PUSH_ARG(heroID)
  PUSH_ARG(exploitIcon)
  PUSH_ARG(tooltipID)
  CALL_FUNCTION;
}

void AdventureFlashInterface::AddHeroResults( int heroID, const char* resultIcon, int resultCount,  const wstring & resultName )
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddHeroResults")
  PUSH_ARG(heroID)
  PUSH_ARG(resultIcon)
  PUSH_ARG(resultCount)
  PUSH_ARG(resultName)
  CALL_FUNCTION;
}

void AdventureFlashInterface::AwardDeltaRaiting( float deltaRaiting, const char * rankPath, const wstring & rankTooltip )
{
	CallMethod( "SetAwardDeltaRaiting", deltaRaiting, rankPath, rankTooltip );
}


//////////////////////////////////////////////////////////////////////////
void AdventureFlashInterface::SetErrorMessage( NDb::EErrorMessageType msgType, const wstring & msg, bool playSound, float lifeTime )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetErrorMessage")
  PUSH_ARG((int)msgType)
  PUSH_ARG(msg)
  PUSH_ARG(playSound)
  PUSH_ARG(lifeTime)
  CALL_FUNCTION;
}

void AdventureFlashInterface::ShowErrorMessage( NDb::EErrorMessageType msgType, bool show )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowErrorMessage")
  PUSH_ARG((int)msgType)
  PUSH_ARG(show)
  CALL_FUNCTION;
}

void AdventureFlashInterface::ShowErrorEvent( const wstring & msg, bool playSound, float lifeTime )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowErrorEvent")
  PUSH_ARG(msg)
  PUSH_ARG(playSound)
  PUSH_ARG(lifeTime)
  CALL_FUNCTION;
}

void AdventureFlashInterface::MarkPlayerLeft( int heroID, PlayerLeaveType::Enum type )
{
  FLASH_INTERFACE_ENTER_FUNCTION("PlayerLeft")
  PUSH_ARG(heroID)
	PUSH_ARG((int)type)
  CALL_FUNCTION;
}

void NGameX::AdventureFlashInterface::MarkPlayerReconnected( int heroID )
{
  FLASH_INTERFACE_ENTER_FUNCTION("PlayerRecconected")
  PUSH_ARG(heroID)
  CALL_FUNCTION;
}


void AdventureFlashInterface::ShowHideWindow( FlashWindowsType::Enum winType )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowHideWindow")
  PUSH_ARG((int)winType)
  CALL_FUNCTION;
}

void AdventureFlashInterface::ShowAnnouncement( const wstring & announcementText, float lifeTime, int priority )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowAnnouncement")
  PUSH_ARG(announcementText)
  PUSH_ARG(lifeTime)
  PUSH_ARG(priority)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetAnnouncementPart( bool right, const char * portraitIcon, int level, const wstring & name, int fraction ,int heroId)
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetAnnouncementPart")
  PUSH_ARG(right)
  PUSH_ARG(portraitIcon)
  PUSH_ARG(level)
  PUSH_ARG(name)
  PUSH_ARG(fraction)
  PUSH_ARG(heroId)
  CALL_FUNCTION;
}

void AdventureFlashInterface::ShowSpawnCreepsAnnouncement( const char * leftIcon, const char * rightIcon, const wstring & announcementText )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowSpawnCreepsAnnouncement")
  PUSH_ARG(leftIcon)
  PUSH_ARG(rightIcon)
  PUSH_ARG(announcementText)
  CALL_FUNCTION;
}

//chat
void AdventureFlashInterface::AddChannel( NDb::EChatChannel channel, const wstring & channelName, uint channelColor, bool showChannelName, bool showPlayerName, bool canWrite2Channel )
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddChannel")
  PUSH_ARG(channel)
  PUSH_ARG(channelName)
  PUSH_ARG(channelColor)
  PUSH_ARG(showChannelName)
  PUSH_ARG(showPlayerName)
  PUSH_ARG(canWrite2Channel)
  CALL_FUNCTION;
}


void AdventureFlashInterface::AddChannelShortCut( NDb::EChatChannel channel, const wstring & shortcut )
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddChannelShortCut")
  PUSH_ARG(channel)
  PUSH_ARG(shortcut)
  CALL_FUNCTION;
}

void AdventureFlashInterface::AddMessage( NDb::EChatChannel channel, const wstring & playerName, const wstring & message )
{
  CallMethod("AddMessage", channel, playerName, message);
}

void AdventureFlashInterface::AddMessage(NDb::EChatChannel channel, const wstring & playerName, const wstring & message, const int playerId)
{
  CallMethod("AddMessageEx", channel, playerName, message, playerId);
}

void AdventureFlashInterface::SetDefaultChannel( NDb::EChatChannel channelID )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetDefaultChannel")
  PUSH_ARG(channelID)
  CALL_FUNCTION;
}


void AdventureFlashInterface::SetChatVisible( bool visible )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetChatVisible")
  PUSH_ARG(visible)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetChatOff( bool isChatOff )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetChatOff")
  PUSH_ARG(isChatOff)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetPlayerIcon(const int playerId, const string& path)
{
  CallMethod("SetPlayerIcon", playerId, path);
}

void AdventureFlashInterface::SetPlayerHeroId(const int playerId, const int heroId, const int teamId)
{
  CallMethod("SetPlayerHeroId", playerId, heroId, teamId);
}

void AdventureFlashInterface::OpenCloseChat()
{
  FLASH_INTERFACE_ENTER_FUNCTION("EnterPressed")
  CALL_FUNCTION;
}

void AdventureFlashInterface::OpenChatChannel(NDb::EChatChannel channelID)
{
		CallMethod( "OpenChanel", channelID );
}

//////////////////////////////////////////////////////////////////////////////

void AdventureFlashInterface::AddOurHeroAward( int awardID, const char * awardIcon, int awardCount, bool isTasty, bool thanksToPremium )
{
	CallMethod( "AddOurHeroAward", awardID, awardIcon, awardCount, isTasty, thanksToPremium );
}

void AdventureFlashInterface::FinishAwarding()
{
  FLASH_INTERFACE_ENTER_FUNCTION("FinishAwarding")
  CALL_FUNCTION;
}

void AdventureFlashInterface::StartAwarding()
{
  FLASH_INTERFACE_ENTER_FUNCTION("StartAwarding")
  CALL_FUNCTION;
}


//IgnoreList
void AdventureFlashInterface::IgnoreUser( const int playerId )
{
  CallMethod("IgnoreUser", playerId);
}

void AdventureFlashInterface::RemoveIgnore( const int playerId )
{
  CallMethod("RemoveIgnore", playerId);
}

//////////////////////////////////////////////////////////////////////////////

void AdventureFlashInterface::ShowTutorialTalentHighlight( int column, int raw, bool show )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowTutorialTalentHighlight")
    PUSH_ARG(column)
    PUSH_ARG(raw)
    PUSH_ARG(show)
    CALL_FUNCTION;
}

void AdventureFlashInterface::ShowTutorialInventoryItemHighlight( int slot, bool show )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowTutorialInventoryItemHighlight")
    PUSH_ARG(slot)
    PUSH_ARG(show)
    CALL_FUNCTION;
}

void AdventureFlashInterface::ShowTutorialShopItemHighlight( int slot, bool show )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowTutorialShopItemHighlight")
    PUSH_ARG(slot)
    PUSH_ARG(show)
    CALL_FUNCTION;
}

void AdventureFlashInterface::ShowTutorialActionBarItemHighlight( int slot, bool show )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowTutorialActionBarItemHighlight")
    PUSH_ARG(slot)
    PUSH_ARG(show)
    CALL_FUNCTION;
}

void AdventureFlashInterface::ShowTutorialElementHighlight( string elementName, bool show )
{
  NI_ASSERT( elementName=="CameraBtn" || 
    elementName=="AlertBtn" || elementName=="HealthBar" || 
    elementName=="ManaBar" || elementName=="TopPlayerLevelHighlight" || 
    elementName=="BottomPlayerLevelHighlight" ||
    elementName=="ActionBarTalentBtn" ||
    elementName=="ActionBarCharStatBtn" ||
    elementName=="ActionBarInventoryBtn" ||
    elementName=="ActionBarStatisticBtn" ||
    elementName=="TalentSetSecondLevel" ||
    elementName=="ActionBarEscBtn" ||
    elementName=="SelectionLevel" ||
    elementName=="PortalBtn", "Bad elementName argument")
  
    FLASH_INTERFACE_ENTER_FUNCTION("ShowTutorialElementHighLight")
    PUSH_ARG(elementName)
    PUSH_ARG(show)
    CALL_FUNCTION;
}

void AdventureFlashInterface::ShowTutorialHeroHighlight( int heroID, bool show )
{
  NI_ASSERT( heroID >= 0 && heroID < 10 , "Bad heroID argument")

    FLASH_INTERFACE_ENTER_FUNCTION("ShowTutorialHeroHighlight")
    PUSH_ARG(heroID)
    PUSH_ARG(show)
    CALL_FUNCTION;
}

void AdventureFlashInterface::ShowTutorialHeroLevelHighlight( int heroID, bool show )
{
  NI_ASSERT( heroID >= 0 && heroID < 10 , "Bad heroID argument")

  CallMethod( "ShowTutorialHeroLevelHighlight", heroID, show );
}

void AdventureFlashInterface::ShowTutorialOvertipLevelHighlight( bool show, float x, float y )
{
  CallMethod( "ShowTutorialOvertipLevelHighlight", show, x, y );
}

//////////////////////////////////////////////////////////////////////////////

void AdventureFlashInterface::AddQuest( int questId, bool primary, wstring text, int totalGoals )
{
  FLASH_INTERFACE_ENTER_FUNCTION("AddQuest")
    PUSH_ARG(questId)
    PUSH_ARG(primary)
    PUSH_ARG(text)
    PUSH_ARG(totalGoals)
    CALL_FUNCTION;
}

void AdventureFlashInterface::UpdateQuest( int questId, int complitedGoals )
{
  FLASH_INTERFACE_ENTER_FUNCTION("UpdateQuest")
    PUSH_ARG(questId)
    PUSH_ARG(complitedGoals)
    CALL_FUNCTION;
}
void AdventureFlashInterface::UpdateQuestText( int questId, wstring text )
{
  FLASH_INTERFACE_ENTER_FUNCTION("UpdateQuestText")
    PUSH_ARG(questId)
    PUSH_ARG(text)
    CALL_FUNCTION;
}
void AdventureFlashInterface::RemoveQuest( int questId )
{
  FLASH_INTERFACE_ENTER_FUNCTION("RemoveQuest")
    PUSH_ARG(questId)
    CALL_FUNCTION;
}

//////////////////////////////////////////////////////////////////////////////

void AdventureFlashInterface::ShowUIBlock( const char* id, bool show )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowUIBlock")
  PUSH_ARG(id)
  PUSH_ARG(show)
  CALL_FUNCTION;
}

void AdventureFlashInterface::ShowAllUIBlocks( bool show )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowAllUIBlocks")
  PUSH_ARG(show)
  CALL_FUNCTION;
}

void AdventureFlashInterface::BlockActionBar( bool block )
{
  FLASH_INTERFACE_ENTER_FUNCTION("BlockActionBar")
  PUSH_ARG(block)
  CALL_FUNCTION;
}

void NGameX::AdventureFlashInterface::SetClientVersion( const wstring & version )
{
  FLASH_INTERFACE_ENTER_FUNCTION("SetClientVersion")
  PUSH_ARG(version)
  CALL_FUNCTION;
}

void AdventureFlashInterface::ShowNPC( const char* icon, const wstring& name )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowNPC")
  PUSH_ARG(icon)
  PUSH_ARG(name)
  CALL_FUNCTION;
}

void AdventureFlashInterface::HideNPC()
{
  FLASH_INTERFACE_ENTER_FUNCTION("HideNPC")
  CALL_FUNCTION;
}

void AdventureFlashInterface::StartCinematic()
{
  FLASH_INTERFACE_ENTER_FUNCTION("StartCinematic")
  CALL_FUNCTION;
}

void AdventureFlashInterface::StopCinematic()
{
  FLASH_INTERFACE_ENTER_FUNCTION("StopCinematic")
  CALL_FUNCTION;
}

void AdventureFlashInterface::ShowCinematicNPC( const char* icon, const wstring& name )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowCinematicNPC")
  PUSH_ARG(icon)
  PUSH_ARG(name)
  CALL_FUNCTION;
}

void AdventureFlashInterface::ShowCinematicMessage( const wstring& text, uint color )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowCinematicMessage")
  PUSH_ARG(text)
  PUSH_ARG(color)
  CALL_FUNCTION;
}

void AdventureFlashInterface::SetQuestHintLine( const wstring& text, const char* bubbleViewType )
{
  CallMethod( "SetQuestHintLine", text, bubbleViewType );
}

void AdventureFlashInterface::ShowCinematicNextButton( const bool show )
{
  CallMethod( "ShowCinematicNextButton", show );
}

void AdventureFlashInterface::EnableCinematicNextButton( const bool enable )
{
  CallMethod( "EnableCinematicNextButton", enable );
}

void AdventureFlashInterface::ShowCinematicNextButtonAnim( const bool show )
{
  CallMethod( "ShowCinematicNextButtonAnim", show );
}

void AdventureFlashInterface::ShowMessageBox( const wstring& header, const wstring& text )
{
  FLASH_INTERFACE_ENTER_FUNCTION("ShowMessageBox")
  PUSH_ARG(header)
  PUSH_ARG(text)
  CALL_FUNCTION;
}


avmplus::Atom AdventureFlashInterface::GetNamedDisplayObject( const char* name, bool withBubble )
{
  return CallMethod( "GetNamedDisplayObject", name, withBubble );
}

avmplus::Atom AdventureFlashInterface::GetTalentBarItemDisplayObject( int column, int raw, bool withBubble )
{
  return CallMethod( "GetTalentBarItemDisplayObject", column, raw, withBubble );
}

avmplus::Atom AdventureFlashInterface::GetActionBarItemDisplayObject( int slot, bool withBubble )
{
  return CallMethod( "GetActionBarItemDisplayObject", slot, withBubble );
}

avmplus::Atom AdventureFlashInterface::GetHeroDisplayObject( int playerId, bool withBubble )
{
  return CallMethod( "GetHeroDisplayObject", playerId, withBubble );
}

avmplus::Atom AdventureFlashInterface::GetShopItemDisplayObject( int slot, bool withBubble ) 
{
	return CallMethod( "GetShopBarItemDisplayObject", slot, withBubble );
}
avmplus::Atom AdventureFlashInterface::GetInventoryItemDisplayObject( int slot, bool withBubble ) 
{
	return CallMethod( "GetInventoryBarItemDisplayObject", slot, withBubble );;
}

// Bubbles
void AdventureFlashInterface::ShowTalentBubble( int column, int row, bool show, const wstring& text, string bubbleViewType, int bubbleIndex )
{
  CallMethod( "ShowTalentBubble", column, row, show, text, bubbleViewType, bubbleIndex );
}

void AdventureFlashInterface::ShowActionBarButtonBubble( int index, bool show, const wstring& text, string bubbleViewType, int bubbleIndex )
{
  CallMethod( "ShowActionBarButtonBubble", index, show, text, bubbleViewType, bubbleIndex );
}

void AdventureFlashInterface::ShowInventoryBarButtonBubble( int index, bool show, const wstring& text, string bubbleViewType, int bubbleIndex )
{
  CallMethod( "ShowInventoryBarButtonBubble", index, show, text, bubbleViewType, bubbleIndex );
}

void AdventureFlashInterface::ShowShopBarButtonBubble( int index, bool show, const wstring& text, string bubbleViewType, int bubbleIndex )
{
  CallMethod( "ShowShopBarButtonBubble", index, show, text, bubbleViewType, bubbleIndex );
}

void AdventureFlashInterface::ShowHeroBubble( int index, bool show, const wstring& text, string bubbleViewType, int bubbleIndex )
{
  CallMethod( "ShowHeroBubble", index, show, text, bubbleViewType, bubbleIndex );
}

void AdventureFlashInterface::ShowBubble( string elementName, bool show, const wstring& text, string bubbleViewType, int bubbleIndex )
{
  CallMethod( "ShowBubble", elementName, show, text, bubbleViewType, bubbleIndex );
}

bool AdventureFlashInterface::IsWindowVisible( int winId )
{
  return AtomGetBool( CallMethod( "IsWindowVisible", winId ) );
}

int AdventureFlashInterface::GetTalentActionBarIndex( int column, int row )
{
  return AtomGetInt( CallMethod( "GetTalentActionBarIndex", column, row ) );
}

int AdventureFlashInterface::GetInventoryItemActionBarIndex( int index )
{
  return AtomGetInt( CallMethod( "GetInventoryItemActionBarIndex", index ) );
}

void AdventureFlashInterface::HideSurrenderButtonForEscMenu()
{
  CallMethod( "HideSurrenderButtonForEscMenu" );
}

void AdventureFlashInterface::SwitchToTutorialMode()
{
  CallMethod( "SwitchToTutorialMode" );
}

void AdventureFlashInterface::SetStatisticBackImages( const char * normal, const char * loose, const char * win )
{
  CallMethod( "SetPveBacks", win, normal, loose );
}


void AdventureFlashInterface::SwitchToSpectatorMode()
{
  CallMethod( "SwitchToSpectatorMode" );
}

void AdventureFlashInterface::RaitingPenaltyEnabled(bool enabled)
{
	CallMethod("RaitingPenaltyEnabled",enabled);
}


void NGameX::AdventureFlashInterface::SetComplainsCount( int complaintsToday, int complaintsMax )
{
	CallMethod("SetReportCounters",complaintsToday,complaintsMax);
}

void NGameX::AdventureFlashInterface::SetComplainsItem(int index, const wstring & name)
{
	CallMethod("AddReportItem",index,name);
}

void NGameX::AdventureFlashInterface::SetBindString(string element)
{
  CallMethod("SetBindString",element);
}

 void NGameX::AdventureFlashInterface::ShowHintDialog(const string& dialogId, const wstring &title, const wstring& hintText, const string &picture)
 {
   CallMethod("ShowQuestHint",dialogId, title, hintText, picture);
 }

 int AdventureFlashInterface::GetSpectatePlayerId( int hotkeyIdx )
 {
   return AtomGetInt( CallMethod( "GetPlayerIdxByHeroIdx", hotkeyIdx ) );
 }

  //////////////////////////////////////////////////////////////////////////

  void AdventureFlashInterface::SmartChatActivate()
  {
    CallMethod("SmartChatActivate");
  }

  void NGameX::AdventureFlashInterface::SmartChatActivateCategory(const unsigned id)
  {
    CallMethod("SmartChatActivateCategory", id);
  }

  void NGameX::AdventureFlashInterface::SmartChatDeactivate()
  {
    CallMethod("SmartChatDeactivate");
  }

  void AdventureFlashInterface::SmartChatBeginUpdate()
  {
    CallMethod("SmartChatBeginUpdate");
  }

  void AdventureFlashInterface::SmartChatEndUpdate()
  {
    CallMethod("SmartChatEndUpdate");
  }

  void AdventureFlashInterface::SmartChatBeginCategory(const unsigned id, const string& key, const wstring& name)
  {
    CallMethod("SmartChatBeginCategory", id, key, name);
  }

  void AdventureFlashInterface::SmartChatEndCategory()
  {
    CallMethod("SmartChatEndCategory");
  }

  void AdventureFlashInterface::SmartChatAddMessage(const unsigned id, const string& key, const wstring& text)
  {
    CallMethod("SmartChatAddMessage", id, key, text);
  }

  void AdventureFlashInterface::SmartChatAddCancel(const unsigned id, const string& key)
  {
    CallMethod("SmartChatAddCancel", id, key);
  }

  // public function SetMinimapTargetZoneColor(value:uint):void
  void AdventureFlashInterface::SetMinimapTargetZoneColor(const unsigned value)
  {
    CallMethod("SetMinimapTargetZoneColor", value);
  }

  // public function SetMinimapTargetZoneThickness(value:uint):void
  void AdventureFlashInterface::SetMinimapTargetZoneThickness(const unsigned value)
  {
    CallMethod("SetMinimapTargetZoneThickness", value);
  }

  // public function ShowMinimapTargetZone(X:Number, Y:Number, radius:Number):void
  void AdventureFlashInterface::ShowMinimapTargetZone(const float x, const float y, const float radius)
  {
    CallMethod("ShowMinimapTargetZone", x, y, radius);
  }

  // public function HideMinimapTargetZone():void
  void AdventureFlashInterface::HideMinimapTargetZone()
  {
    CallMethod("HideMinimapTargetZone");
  }

  // public function DayNightUpdateState(night:Boolean, stateFraction:Number):void
  void AdventureFlashInterface::DayNightUpdateState(const bool night, const float stateFraction)
  {
    CallMethod("DayNightUpdateState", night, stateFraction);
  }

  // public function DayNightHideUI(hide:Boolean):void
  void AdventureFlashInterface::DayNightHideUI(const bool hide)
  {
    CallMethod("DayNightHideUI", hide);
  }

}

NI_DEFINE_REFCOUNT( NGameX::AdventureFlashInterface );
