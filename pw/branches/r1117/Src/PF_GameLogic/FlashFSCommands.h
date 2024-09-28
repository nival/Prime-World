#pragma once

namespace FlashFSCommands
{
  enum EFlashFSCommands
  {
    TalentClicked          , // [%d %d]
    HeroClicked            , // [%d]
    HeroDoubleClicked      , // [%d]
    SelectionClicked       , // 
    SelectionDoubleClicked , // 
    LostFocusFromAvatar    , // 
    TalentToolTip          , // [%d %d %d]
    TalentActionToolTip    , // [%d %d %d]
    MinimapMouseOver       , // [%d]
    MinimapMouseDown       , // [%d %d %d]
    SignalMouseClick       ,// 	 
    CameraMouseClick       ,//  	 
    MinimapActionMove      ,// [%d %d]
    MinimapMouseUp         ,// 

    ShopItemToolTip        ,// [%d %d]
    ShopItemClicked        ,// [%d]
    ShopClosed			       ,// [%d]

    InventoryItemToolTip   ,// [%d %d]
    InventoryItemClicked   ,// [%d]

    ItemActionToolTip      ,// [%d %d]

    PortalTooltip         ,// [%d]
    PortalClick           ,
    
    ActionBarLock         ,//[%d]        

    BuyImpulseBuff		     ,	
    ImpulseBuffClose		   ,	
    ImpulseBuffToolTip	   ,// [%d]

    EscMenuAbortLevel      , 
    EscMenuExitGame        ,
    ReturnToLobby          ,
    SkipTutorial           ,
    DisableHotkeys         , //[%d]

    MinigameMenuClosed     ,
    MinigameMenuOpened     ,

    OurBuffTooltip         ,// [%d %d]
    SelectionBuffTooltip   ,// [%d %d]

    TitleTooltip           ,// [%d %d]
    ExploitTooltip         ,// [%d %d]
    ShareFinalStatistics   , 

    BaseStatTooltip,           // [%d %d] 
    DerivativeStatTooltip,     // [%d %d] 

    SelectionBaseStatTooltip,           // [%d %d] 
    SelectionDerivativeStatTooltip,     // [%d %d] 

    FillCharStatForUnit,                // [%d %d] 

    OpenTalentsForUnit,                 // [%d %d] 
    SelectionTalentToolTip,             // [%d] 

    SendMessage,                        // [%d %s]

    ActivateChatInput,                  // [%d]

    AwardTooltip,                       // [%d %d]
    ResetTargetState,

    IgnoreUser,                         //[%s]
    RemoveIgnoreFromUser,               //[%s]
    StartSpectate,                      //[%d]

    QuestClicked,

    EscMenuContinue,
    EscMenuShow,

    BubbleNextButtonClick,              //[%d]
    CinematicNextButtonClick,

    MessageBoxButtonClick,              //[%d]


    AddToFriends,                       //[%d]

    ModeDescriptionTooltip,             // [%d %d]

    ExitLoadingScreen,

	SendReportOnUser,

	ReportWindowOpened,
  
  ExitHintDialog,

    ActivateSmartChat,
    ActivateSmartChatCategory,  // [%u]
    DeactivateSmartChat,
    ClickSmartChatItem, // [%u]

    PlaySameTeam,

    Last

  };

  const char * ConvertToString(EFlashFSCommands command);
  EFlashFSCommands ConvertToFSCommand(const char * command);
  bool Equals(EFlashFSCommands command, const char * commandID);
};
