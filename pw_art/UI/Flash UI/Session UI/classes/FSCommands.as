package
{
	import Events.FsCommandEvent;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.system.fscommand;
	
	public class FSCommands
	{
		
		public static var MyEventDispatcher:EventDispatcher = new EventDispatcher();
		public static var testing:Boolean = false;
		
		public static var TOOLTIP_SHOW:String = "1 ";
		public static var TOOLTIP_HIDE:String = "0 ";
		
		public static var DISABLE:String = '0';
		public static var ENABLE:String = '1';
		
		
		
		//Minimap.as-------------------------------------------------------------------
		public static const MINIMAP_MOUSEOVER:String = 'MinimapMouseOver';
		public static const MINIMAP_MOUSEDOWN:String = 'MinimapMouseDown';
		public static const MINIMAP_MOUSEUP:String = 'MinimapMouseUp';
		public static const MINIMAP_ACTIONMOVE:String = 'MinimapActionMove';
		public static const SIGNAL_MOUSECLICK:String = 'SignalMouseClick';
		public static const CAMERA_MOUSECLICK:String = 'CameraMouseClick';
		//-----------------------------------------------------------------------------
		//EndScreen.as, EscMenuBar.as--------------------------------------------------
		public static const ESCMENU_EXITGAME:String = 'EscMenuExitGame';
		public static const ESCMENU_ABORTLEVEL:String = 'EscMenuAbortLevel';
		public static const ESCMENU_DISABLEHOTKEYS:String = 'DisableHotkeys';
		public static const ESCMENU_RETURN_TO_LOBBY:String = 'ReturnToLobby';
		public static const ESCMENU_VOTE_FOR_SURRENDER:String = 'VoteForSurrender';
		public static const ESCMENU_CONTINUE:String = 'EscMenuContinue';
		public static const ESCMENU_SHOW:String = 'EscMenuShow';
		public static const ESCMENU_SKIP_TUTORIAL:String = 'SkipTutorial';
		//-----------------------------------------------------------------------------
		//VoteMenu.as--------------------------------------------------
		public static const VOTEMENU_SURRENDER_VOTE:String = 'SurrenderVote';
		//-----------------------------------------------------------------------------
		//TalentShortCut.as------------------------------------------------------------
		public static const TALENT_ACTIONTOOLTIP:String = 'TalentActionToolTip';
		//-----------------------------------------------------------------------------
		//Talent.as----------------------------------------------
		public static const TALENT_CLICK:String = 'TalentClicked';
		public static const TALENT_TOOLTIP:String = 'TalentToolTip';
		//-----------------------------------------------------------------------------
		//SelectionTalent.as-----------------------------------------------------------------
		public static const SELECTION_TALENT_TOOLTIP:String = 'SelectionTalentToolTip';
		//-----------------------------------------------------------------------------
		//HeroMateInfo.as. MateInfo.as. SelectionMateInfo.as---------------------------
		public static const HERO_CLICK:String = 'HeroClicked';
		public static const HERO_DOUBLECLICK:String = 'HeroDoubleClicked';
		public static const HERO_LOSTFOCUS:String = 'LostFocusFromAvatar';
		public static const SELECTION_CLICK:String = 'SelectionClicked';
		public static const SELECTION_DOUBLECLICK:String = 'SelectionDoubleClicked';
		
		
		//-----------------------------------------------------------------------------
		//ImpulsShop.as----------------------------------------------------------------
		public static const IMPULSBUFF_CLOSE:String = 'ImpulseBuffClose';
		public static const IMPULSBUFF_TOOLTIP:String = 'ImpulseBuffToolTip';
		public static const IMPULSBUFF_BUY:String = 'BuyImpulseBuff';
		//-----------------------------------------------------------------------------
		//InventoryButton.as-----------------------------------------------------------
		public static const INVENTORYITEM_CLICK:String = 'InventoryItemClicked';
		public static const INVENTORYITEM_TOOLTIP:String = 'InventoryItemToolTip';
		public static const DROP_ITEM_OUTSIDE:String = 'DropItemOutside';
		//-----------------------------------------------------------------------------
		//InventoryItemShortcut.as-----------------------------------------------------
		public static const INVENTORYITEMSHORTCUT_TOOLTIP:String = 'ItemActionToolTip';
		//-----------------------------------------------------------------------------
		//Main.as----------------------------------------------------------------------
		public static const MINIGAMEMENU_CLOSED:String = 'MinigameMenuClosed';
		public static const MINIGAMEMENU_OPENED:String = 'MinigameMenuOpened';
		public static const SHOP_CLOSED:String = 'ShopClosed';
		public static const RESET_TARGET_STATE:String = 'ResetTargetState';
		//-----------------------------------------------------------------------------
		//ShopBarButton.as-------------------------------------------------------------
		public static const SHOPITEM_TOOLTIP:String = 'ShopItemToolTip';
		public static const SHOPITEM_CLICK:String = 'ShopItemClicked';
		//-----------------------------------------------------------------------------
		//ActionBar.as-------------------------------------------------------------
		public static const OURBUFF_TOOLTIP:String = 'OurBuffTooltip';
		public static const PortalTooltip:String = "PortalTooltip";
		public static const PortalClick:String = "PortalClick";
		public static const ActionBarLock:String = "ActionBarLock";
		
		//-----------------------------------------------------------------------------
		//SelectionInfo.as-------------------------------------------------------------
		public static const SELECTIONBUFF_TOOLTIP:String = 'SelectionBuffTooltip';
		//-----------------------------------------------------------------------------
		//CharStats.as-----------------------------------------------------------------
		public static const CHARSTAT_BASE_TOOLTIP:String = 'BaseStatTooltip';
		public static const CHARSTAT_DERIVATIVE_TOOLTIP:String = 'DerivativeStatTooltip';
		//-----------------------------------------------------------------------------
		//SelectionCharStats.as-----------------------------------------------------------------
		public static const SELECTION_CHARSTAT_BASE_TOOLTIP:String = 'SelectionBaseStatTooltip';
		public static const SELECTION_CHARSTAT_DERIVATIVE_TOOLTIP:String = 'SelectionDerivativeStatTooltip';
		//-----------------------------------------------------------------------------
		//FinalStatistics -------------------------------------------------------------
		public static const TITLE_TOOLTIP:String = "TitleTooltip";
		public static const EXPLOIT_TOOLTIP:String = "ExploitTooltip";
		public static const AWARD_TOOLTIP:String = "AwardTooltip";
		
		//ContextMenu
		public static const FILL_CHARSTAT_FORUNIT:String = "FillCharStatForUnit";
		public static const FOLLOW_UNIT:String = "FollowUnit";
		public static const WATCH_UNIT:String = "WatchForUnit";
		public static const OPEN_TALANTS_FORUNIT:String = "OpenTalentsForUnit";
		public static const ADD_TO_FRIENDS:String = "AddToFriends";
		public static const PRIVATE_MESSAGE:String = "PrivateMessage";
		public static const IGNORE_USER:String = "IgnoreUser";
		public static const REMOVE_IGNORE:String = "RemoveIgnoreFromUser";
		public static const START_SPECTATE:String = "StartSpectate";
		
		//ChatBar
		public static const CHATBAR_SENDMESSAGE:String = "SendMessage";
		public static const ACTIVATE_CHAT_INPUT:String = 'ActivateChatInput';
		
		// SmartChat
		public static const SMART_CHAT_ACTIVATE:String = 'ActivateSmartChat';
		public static const SMART_CHAT_DEACTIVATE:String = 'DeactivateSmartChat';
		public static const SMART_CHAT_ACTIVATE_CATEGORY:String = 'ActivateSmartChatCategory';
		public static const SMART_CHAT_ITEM_CLICK:String = 'ClickSmartChatItem';
		
		//Options
		static public const PREFERENCE_COMPONENT_SET_VALUE:String = "PreferenceComponentSetValue";
		static public const PREFERENCE_COMPONENT_APPLY:String = "PreferenceComponentsApply";
		public static const PREFERENCE_COMPONENT_CANCEL:String = "PreferenceComponentsCancel";
		public static const PREFERENCE_SHORTCUT_REBIND:String = "PreferenceShortcutRebind";		
		public static const PREFERENCE_SHORTCUTS_APPLY:String = "PreferenceShortcutsApply";		
		
		//Quest
		public static const QUEST_CLICKED:String = "QuestClicked";
		public static const BubbleNextButtonClick:String = "BubbleNextButtonClick";
		public static const CinematicNextButtonClick:String = "CinematicNextButtonClick";
		
		//MessageBox
		public static const MESSAGEBOX_BUTTON_CLICK:String = 'MessageBoxButtonClick';
		
		//Modificator 
		public static const ModeDescriptionTooltip:String = 'ModeDescriptionTooltip';
		
		static public const ExitLoadingScreen:String = 'ExitLoadingScreen';
		
		//Report Window
		
		public static const REPORT_WINDOW_SEND_REPORT:String = "ReportWindowSendReport";
		static public const REPORT_WINDOW_OPENED:String = "ReportWindowOpened";
		
		public static const SHARE_FINAL_STATISTICS: String = "ShareFinalStatistics";
		
		public static const PLAY_SAME_TEAM:String = "PlaySameTeam";
		
		public static const EXITHINTDIALOG:String = "ExitHintDialog";
		
		public static function Send(command:String,args:String=null):void
		{
			if (testing) 
			{
				trace(command + " " + args);
				
				MyEventDispatcher.dispatchEvent(new FsCommandEvent(command,args ));
				return;
			}
			
			if (args == null) args = "";
			fscommand(command, args);
		}
	}
	
}