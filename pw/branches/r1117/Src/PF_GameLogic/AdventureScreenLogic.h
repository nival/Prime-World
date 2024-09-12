#pragma once

#include "../Client/Messages.h"
#include "../Client/ScreenUILogicBase.h"
#include "QuestsController.h"
#include "AwardsController.h"
#include "UI/PreferencesProcessor.h"
#include "System/HPTimer.h"

namespace UI
{
  class Button;
  class ImageLabel;
  class FlashContainer2;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
  class HeightsController;
}

namespace NDb
{
	struct FWODVisualInfo;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NGameX
{ 
  class  AdventureScreen;
  struct EffectArea;
  class  PauseTimer;
  class  UIFlyTexts;
  class  PFUISignAnnouncement;
    
  class  AdventureFlashInterface;
  class  TeamInfoNew;
  class  TalentPanelNew;
  class  ActionBarController;
  class  SelectionInfo;
  class  MinimapController;
  class  ShopController;
  class  InventoryController;
  class  ImpulseBuffsController;
  class  EscMenuController;
  class  StatisticsController;
  class  CharInfoContainer;
  class  DebugCharStat;
  class  BuffsController;
  class  FinalStatisticsController;
  class  AnnouncementController;
  class  AwardsController;
  class  CommonCombatController;
  class  HeroTitleCalculator;
  class  VotingForSurrenderController;
  class  DialogController;
  class  CTE_Controller;
  class  FriendsController;
  class  IgnoreListController;
  class  IgnoreListStorage;
  class  ComplainController;
  class  SmartChatController;

  int PlayerIndex2Collor(int nPlayerIndex); //@todo Oleg. WTF?!

  class AdventurepreferencesProcessor : public UI::PreferencesProcessor
  {
    NI_DECLARE_REFCOUNT_CLASS_1( AdventurepreferencesProcessor, UI::PreferencesProcessor );
    
  public:
    AdventurepreferencesProcessor( UI::FlashContainer2 * flashWnd, const char* className ) : 
        PreferencesProcessor(flashWnd, className) {};
    virtual ~AdventurepreferencesProcessor() {};
    virtual void Apply();
    virtual void ApplyShortcuts();
    virtual void Cancel();
    virtual void ShortcutRebind( const wchar_t* command );
  };

  namespace
  {
    class PartyInfo
    {
    public:
      typedef vector<int> MemberVector;

      PartyInfo();
      explicit PartyInfo(const PartyInfo& other);

      PartyInfo& operator=(const PartyInfo& other);

      void AddMember(const NCore::PlayerStartInfo& psi);

      int GetMemberCount() const;
      const MemberVector& GetMembers() const;

      bool IsPartyLeader(const NWorld::PFPlayer* const player) const;
      bool IsPartyMember(const NWorld::PFPlayer* const player) const;
    private:
      static bool IsValidMemberId(const int id);

      static int GetMemberId(const NCore::PlayerStartInfo& psi);
      static int GetMemberId(const NWorld::PFPlayer* const player);

      void AddMemberImpl(const int id, const bool leader);
      bool IsLeaderImpl(const int id) const;
      bool IsMemberImpl(const int id) const;

      MemberVector members;
    };
  }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class AdventureScreenLogic : public UI::ClientScreenUILogicBase
	{
    NI_DECLARE_REFCOUNT_CLASS_1( AdventureScreenLogic, UI::ClientScreenUILogicBase );

		enum ECloseTag { CLOSE_NO, CLOSE_SCREEN, CLOSE_QUIT };

		ECloseTag closeTag;

	private:
		Weak<NGameX::AdventureScreen> m_owner; //TODO: insert IsValid() where needed
    NDb::Ptr<NDb::DBUIData>       uiData;
		NDb::Ptr<NDb::FWODVisualInfo> fwodVisualInfo;

    //Weak<UI::ImageLabel>          m_messages; //TODO: insert IsValid() where needed
    Weak<UI::ImageLabel>          debugMessageWindow;
    Weak<UI::ImageLabel>          generalTooltip;
    Weak<UI::ImageLabel>          actionBarTooltip;

    Weak<UI::Window>              lowSpeedWnd;
    Weak<UI::Window>              noConnectWnd;

    Weak<UI::FlashContainer2>      flashWnd;

    //new flash interface controllers
    Strong<AdventureFlashInterface>   flashInterface;
    Strong<AdventurepreferencesProcessor>  preferencesProcessor; 

    Strong<SelectionInfo>             selectionInfo;
    Strong<TeamInfoNew>               newTeamInfo;
    Strong<TalentPanelNew>            talentPanel;
    Strong<ActionBarController>       actionBarController;
    Strong<MinimapController>         minimapController;
    Strong<ShopController>            shopController;
    Strong<InventoryController>       inventoryController;
	  Strong<ImpulseBuffsController>	  impulseBuffsController;
    Strong<EscMenuController>         escMenuController;
    Strong<StatisticsController>      statisticsController;
    
    Strong<CharInfoContainer>         charInfoContainer;
    
    CObj<DebugCharStat>               debugCharStat;
    Strong<BuffsController>           ourHeroBuffs;
    Strong<BuffsController>           selectionBuffs;
    Strong<FinalStatisticsController> finalStatisticsController;
    Strong<AnnouncementController>    announcementController;
    Strong<AwardsController>          awardsController;
    Strong<CommonCombatController>    commonCombatController;
    Strong<VotingForSurrenderController> votingForSurrenderController;
    Strong<DialogController>          dialogController;
    Strong<QuestsController>          questsController;
    Strong<CTE_Controller>            cteController;
    Strong<FriendsController>         friendsController;
	  Strong<ComplainController>        complainController;
    Weak<IgnoreListStorage>           ignoreListStorage;
    Weak<IgnoreListController>        ignoreListController;
    

    Weak<ChatUiController> chatController;
    Weak<SmartChatController> smartChatController;
    Weak<BindsController> bindsController;
    vector<NCore::PlayerStartInfo> playerStartInfos;
    Weak<ISocialConnection> socialConnection;
  
    AutoPtr<PauseTimer>             m_pPauseTimer;
    CObj<UIFlyTexts>                m_flyTexts;
        
    NDb::EMapType                   mapType;
    NWorld::PFBaseUnit * m_selectedUnit;

    bool isGameEnded;
 
    enum HeroState { HS_Invalid, HS_Dead, HS_Resurrecting, HS_Living };
    
    HeroState            GetHeroState() const;  

    HeroState                      m_heroState;
  	float                          m_fTimerRqstDlg;

    struct LastTalentClicked
    {
      int level;
      int column;
      LastTalentClicked() : level(-1), column(-1) { }
    };

    LastTalentClicked lastTalentClicked;
    string lastItemClicked;

    typedef map<uint, PartyInfo> PartyInfoMap;

    PartyInfoMap partyInfos;

    timer::Time playSameTeamDecisionDeadline;

  public:
		AdventureScreenLogic( ChatUiController * _chatController, SmartChatController * _smartChatController, BindsController* _bindsController );
		~AdventureScreenLogic();

    virtual void RenderWindows();
    
    void UpdatePreferences();

		ECloseTag GetCloseTag() const { return closeTag; }

    NWorld::PFBaseUnit * GetSelectedUnit() { return m_selectedUnit; }

    void AwardUser(const nstl::vector<roll::SAwardInfo> & _awards);

    void SetHero(NWorld::PFBaseHero const *pHero);
    void SetSelectedUnit( const NWorld::PFBaseUnit * pUnit );
    //void UpdateLogic(const unsigned long & dt);
    void SetDialogs( NWorld::PFBaseHero const *pHero, NDb::Ptr<NDb::DialogsCollection> const& dialogs, NDb::Ptr<NDb::HintsCollection> const& hints, NDb::Ptr<NDb::SessionQuestsCollection> const& quests );

  	void SetOwner( NGameX::AdventureScreen * owner, const NDb::DBUIData * _uiData, const vector<NCore::PlayerStartInfo> & _playersInfo, ISocialConnection * _socialConnection  );
		void DoCustomEvents(float deltaTime );
    UI::Window * getBaseWindow() { return pBaseWindow; }
		void CloseAdventureScreen();
  
    void GetLastTalentClicked( int& level, int& column ) { level = lastTalentClicked.level; column = lastTalentClicked.column; lastTalentClicked.level = -1; lastTalentClicked.column = -1; }
    void SetLastTalentClicked( const int level, const int column ) { lastTalentClicked.level = level; lastTalentClicked.column = column; }
    void SetLastItemClicked( const string& item ) { lastItemClicked = item; }
    void GetLastItemClicked( string& item ) { item = lastItemClicked; lastItemClicked.clear(); }

    void OnSessionStart(lobby::TGameId sessionId);

		void OnMapLoaded( const NDb::AdvMapDescription * advMapDescription, const NDb::AdvMapSettings * settings,bool isCustomGame);

    void ShowGameOverMessage( NDb::EFaction failedFaction, HeroTitleCalculator const* heroTitleCalculator, bool dontShowStatistics, bool dontShowDialog = false );

    void ConfigurePlaySameTeamFeature(const NDb::AdvMapDescription* const advMapDescription, const bool available, const bool enabled);
    void HandlePlaySameTeamDecision(const NWorld::PFPlayer* const localPlayer, const NWorld::PFPlayer* const player, const bool agreed);
    bool CanDecideToPlaySameTeam(const NDb::AdvMapDescription* const advMapDescription, const NWorld::PFPlayer* const localPlayer) const;
    unsigned GetPlaySameTeamTimeLeft() const;

		void SetFirstWinVisual( NWorld::PFBaseHero * ourHero );
	  void SetComplains(int complaintsToday, int complaintsMax, NCore::TComplaintInfo const&  complaintsInfo);
    __int64 GetPlayerAuid() const;

    void UpdateTooltipsSaturation();
 
    void OnDenyTower(int action);

    void EmulateImpulsiveBuffButton( bool on );
    void ActivateImpulsiveBuff();
  
    void SetMessage( const wstring & msg );
    void SetMessage( const wstring & msg, bool playSound, float lifeTime );
    void SetErrorMessage(NDb::EErrorMessageType msgType, bool show = true, const NNameMap::Map* values = 0 );
    void ShowAnnouncement(PFUISignAnnouncement const * sign ,  AnnouncementParams * announcementParams);

    virtual void SetDebugMessage(string const & msg);
    void ClearDebugMessage();
 
   
    ActionBarController * GetActionBarController() {return actionBarController;}
    AdventureFlashInterface * GetFlashInterface() {return flashInterface;}
    ShopController * GetShopController() {return shopController;}
    InventoryController * GetInventoryController() {return inventoryController;}
    EscMenuController * GetEscMenuController() {return escMenuController;}
    StatisticsController * GetStatisticsController() {return statisticsController;}
    DialogController * GetDialogController() {return dialogController;}
    QuestsController * GetQuestsController() {return questsController;}
    FinalStatisticsController* GetFinalStatisticsController() const { return finalStatisticsController; }

    TeamInfoNew* GetTeamInfo() { return newTeamInfo; }

    UI::FlashContainer2* GetFlashContainer() { return flashWnd; }

    virtual void    OnScreenResolutionChanged();

    bool IsMouseUnderWindow();

    bool IsGameEnded() { return isGameEnded; }

    void UpdateDayNightState(const class NWorld::DayNightController* const dayNightController);
    void SetDayNightWidgetVisible(const bool value);

    //DEBUG
    void ShowPauseTimer(bool bShow, NWorld::PFBaseHero const *pWho);
    void DebugAwardExperience(int experience, float raiting);
#ifndef _SHIPPING
    void DebugAwardUser(const vector<AwardData> & _awards);
#endif
    void PressRemovePauseButton();

    void ActivateChat();
    void ActivateChatChannel(const NDb::EChatChannel channel);
    void ActivateSmartChat();

    bool ProcessUIEvent(const Input::Event& event);

  private:
    void CheckWasCrossAidsRiver();
    void HeroStartedResurrect();
    void HeroDied();
    void InitErrorMessages(AdventureFlashInterface * _flashInterface, NDb::Ptr<NDb::DBUIData> dbUIData);
    void UpdateErrorMessageTextByVariant( NDb::EErrorMessageType message, const NNameMap::Map* values );
    void UpdateConnectionAndSpeedWindows();

    void CollectPartyInfos();
    const PartyInfo* GetPlayerPartyInfo(const NWorld::PFPlayer* const player) const;

    friend class AdventureScreen;
    class PrefCommonGraphicsQuality;
	};
}
