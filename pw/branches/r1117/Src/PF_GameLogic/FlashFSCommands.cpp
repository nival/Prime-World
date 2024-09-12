#include "StdAfx.h"
#include "FlashFSCommands.h"

namespace
{
  static vector<string> commands;
  static hash_map<string, int> commandsByString;

  
  void InitCommands()
  {
    commands.resize(FlashFSCommands::Last);

    commands[FlashFSCommands::TalentClicked]          = "TalentClicked";
    commands[FlashFSCommands::HeroClicked]            = "HeroClicked";
    commands[FlashFSCommands::HeroDoubleClicked]      = "HeroDoubleClicked";
    commands[FlashFSCommands::SelectionClicked]       = "SelectionClicked";
    commands[FlashFSCommands::SelectionDoubleClicked] = "SelectionDoubleClicked";
    commands[FlashFSCommands::LostFocusFromAvatar]    = "LostFocusFromAvatar";
    commands[FlashFSCommands::TalentToolTip]          = "TalentToolTip";
    commands[FlashFSCommands::TalentActionToolTip]    = "TalentActionToolTip";

    commands[FlashFSCommands::MinimapMouseOver]    = "MinimapMouseOver";
    commands[FlashFSCommands::MinimapMouseDown]    = "MinimapMouseDown";
    commands[FlashFSCommands::MinimapMouseUp]      = "MinimapMouseUp";
    commands[FlashFSCommands::SignalMouseClick]    = "SignalMouseClick";
    commands[FlashFSCommands::CameraMouseClick]    = "CameraMouseClick";
    commands[FlashFSCommands::MinimapActionMove]   = "MinimapActionMove";

    commands[FlashFSCommands::ShopItemToolTip]     = "ShopItemToolTip";
    commands[FlashFSCommands::ShopItemClicked]     = "ShopItemClicked";
    commands[FlashFSCommands::ShopClosed]		       = "ShopClosed";


    commands[FlashFSCommands::InventoryItemToolTip] = "InventoryItemToolTip";
    commands[FlashFSCommands::InventoryItemClicked] = "InventoryItemClicked";

    commands[FlashFSCommands::ItemActionToolTip]     = "ItemActionToolTip";

    commands[FlashFSCommands::PortalTooltip]      = "PortalTooltip";
    commands[FlashFSCommands::PortalClick]        = "PortalClick";

    commands[FlashFSCommands::ActionBarLock] = "ActionBarLock";

    commands[FlashFSCommands::BuyImpulseBuff]		  = "BuyImpulseBuff";
    commands[FlashFSCommands::ImpulseBuffClose]		= "ImpulseBuffClose";
    commands[FlashFSCommands::ImpulseBuffToolTip] = "ImpulseBuffToolTip";

    commands[FlashFSCommands::EscMenuAbortLevel]	 = "EscMenuAbortLevel";
    commands[FlashFSCommands::EscMenuExitGame]     = "EscMenuExitGame";
    commands[FlashFSCommands::ReturnToLobby]       = "ReturnToLobby";
    commands[FlashFSCommands::SkipTutorial]        = "SkipTutorial";
    commands[FlashFSCommands::DisableHotkeys]      = "DisableHotkeys";
    
    commands[FlashFSCommands::MinigameMenuClosed]	 = "MinigameMenuClosed";
    commands[FlashFSCommands::MinigameMenuOpened]  = "MinigameMenuOpened";

    commands[FlashFSCommands::OurBuffTooltip]	       = "OurBuffTooltip";
    commands[FlashFSCommands::SelectionBuffTooltip]  = "SelectionBuffTooltip";

    commands[FlashFSCommands::TitleTooltip]	       = "TitleTooltip";
    commands[FlashFSCommands::ExploitTooltip]      = "ExploitTooltip";
    commands[FlashFSCommands::ShareFinalStatistics] = "ShareFinalStatistics";

    commands[FlashFSCommands::BaseStatTooltip]	       = "BaseStatTooltip";
    commands[FlashFSCommands::DerivativeStatTooltip]   = "DerivativeStatTooltip";

    commands[FlashFSCommands::SelectionBaseStatTooltip]	       = "SelectionBaseStatTooltip";
    commands[FlashFSCommands::SelectionDerivativeStatTooltip]   = "SelectionDerivativeStatTooltip";

    commands[FlashFSCommands::FillCharStatForUnit]    = "FillCharStatForUnit";
    commands[FlashFSCommands::OpenTalentsForUnit]     = "OpenTalentsForUnit";
    commands[FlashFSCommands::SelectionTalentToolTip] = "SelectionTalentToolTip";

    commands[FlashFSCommands::SendMessage]            = "SendMessage";
    commands[FlashFSCommands::ActivateChatInput]      = "ActivateChatInput";

    commands[FlashFSCommands::AwardTooltip]      = "AwardTooltip";
    
    commands[FlashFSCommands::ResetTargetState]  = "ResetTargetState";

    commands[FlashFSCommands::StartSpectate]  = "StartSpectate";
    
    commands[FlashFSCommands::IgnoreUser]  = "IgnoreUser";
    commands[FlashFSCommands::RemoveIgnoreFromUser]  = "RemoveIgnoreFromUser";

    commands[FlashFSCommands::QuestClicked] = "QuestClicked";

    commands[FlashFSCommands::EscMenuContinue] = "EscMenuContinue";
    commands[FlashFSCommands::EscMenuShow] = "EscMenuShow";

    commands[FlashFSCommands::BubbleNextButtonClick] = "BubbleNextButtonClick";
    commands[FlashFSCommands::CinematicNextButtonClick] = "CinematicNextButtonClick";

    commands[FlashFSCommands::MessageBoxButtonClick] = "MessageBoxButtonClick";

    commands[FlashFSCommands::AddToFriends] = "AddToFriends";

    commands[FlashFSCommands::ModeDescriptionTooltip] = "ModeDescriptionTooltip";

    commands[FlashFSCommands::ExitLoadingScreen] = "ExitLoadingScreen";
        
    commands[FlashFSCommands::SendReportOnUser] = "ReportWindowSendReport";
    
    commands[FlashFSCommands::ReportWindowOpened] = "ReportWindowOpened";
    commands[FlashFSCommands::ExitHintDialog] = "ExitHintDialog";

    commands[FlashFSCommands::ActivateSmartChat] = "ActivateSmartChat";
    commands[FlashFSCommands::ActivateSmartChatCategory] = "ActivateSmartChatCategory";
    commands[FlashFSCommands::DeactivateSmartChat] = "DeactivateSmartChat";
    commands[FlashFSCommands::ClickSmartChatItem] = "ClickSmartChatItem";

    commands[FlashFSCommands::PlaySameTeam] = "PlaySameTeam";

    for (int i =0; i< commands.size(); i++)
    {
      commandsByString[commands[i]] = i;
    }
  }

}

namespace FlashFSCommands
{

const char * ConvertToString( EFlashFSCommands command )
{
  if (commands.empty())
    InitCommands();

  return commands[command].c_str();
}

bool Equals( EFlashFSCommands command, const char * commandID )
{
  return strcmp(ConvertToString(command), commandID) == 0;
}

EFlashFSCommands ConvertToFSCommand( const char * command)
{
  if (commands.empty())
    InitCommands();

  return (EFlashFSCommands)commandsByString[command];
}
}