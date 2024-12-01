package
{

	import ActionBar.ActionBarContainer;
	import BaseClasses.MateInfoBase;
	import Chat.ChatBar;
	import classes.Controllers.BubbleVisabilityController
	import classes.Events.ShareFinalStatisticEvent;
	import classes.MainScreen.QuestHint;
	import classes.SmartChat.SmartChat;
	import classes.SmartChat.SmartChatEvent;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import flash.display.Shape;

	import Enums.EBubbledElements;
	import Components.ButtonRound;

	import Events.ShowDialogEvent;
	import Events.PrepareReportWindowEvent;
	
	
	import ReportWindow.ReportWindow;
	import Tutorial.DownNpcDialogLine;
	import Tutorial.UpperNpcDialogLine;
	import Controllers.TutorialHighlighter;
	import Controllers.TutorialShower;
	import ContMenu.ContextMenu;
	import Controllers.SoundController;
	import Controllers.TutorialShower;
	import Enums.ETutorialBlocks;
	import Enums.ETutorialHighlitedObjects;
	import EscMenu.OptionsWindow;
	import Events.ContextMenuEvent;
	import Events.MouseRightEvents;
	import flash.display.Stage;
	import flash.display.MovieClip;
	import flash.display.StageScaleMode;
	import flash.display.StageAlign;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.Sprite;
	import flash.text.TextField;
	import flash.utils.Dictionary;
	import TalantBarSelection.SelectionTalentBar;
	
	import flash.geom.Point;
	import flash.display.DisplayObject;
	
	import flash.events.KeyboardEvent;
	
	import ActionBar.ActionBar;
	import Announcements.Announcement;
	import ShopBar.ShopBar;
	import MainScreen.*;
	import InventoryBar.InventoriesBar;
	
	import Components.ButtonSquare;
	import EscMenu.EscapeMenuBar;
	import EscMenu.Preferences;
	import ActionBar.ActionButton;
	import CharStat.CharStats;
	import Controllers.WinVisabilityController;
	
	import src.ButtonTooltipEvent;
	import src.FPSCounter;
	import src.WButton;
	
	import Events.ErrorEvent;
	import Datas.PlayerStatisticData;
	import DragAndDrop.DnDController;
	import TalentBar.Talent;
	import Enums.EWindows;
	import Enums.TalentUIState;
	import Components.icoDrag;
	import StatisticBars.FinalStatisticsBar;
	import StatisticBars.StatisticsBar;
	import TalentBar.TalentsBar;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	import Strokes.HeroOvertipStroke;
	
	public class Main extends MovieClip
	{
		private var DELETE_ALL_NOT_TRUNK_THINGS_TOOLTIPS:Boolean = false; //Сделаешь true и нету флешовых тултипов!
		
		private var m_startRezW:uint;
		private var m_startRezH:uint;
		
		private var m_currScreenW:Number;
		
		private var m_currScreenH:Number;
		private var m_lastMouseX:uint;
		private var m_lastMouseY:uint;
		
		private var _mainInterFace:MainInterface;
		
		private var _preferencesInterFace:Preferences;
		
		private var talentClick:Talent;
		private var actionClick:ActionButton;
		
		private var globalPoint:Point;
		
		//references
		public var tooltip:ToolTip; //визуальный объект тултипа
		public var teamInfoFrendly_mc:TeamInfoFriendly;
		public var teamInfoEnemy_mc:TeamInfoEnemy;
		public var heroInfo_mc:HeroInfo;
		public var font1:TextField;
		public var font2:TextField;
		public var selectionInfo_mc:SelectionInfo;
		public var talentsBar_mc:TalentsBar;
		public var talentsBarContext_mc:SelectionTalentBar;
		public var actionBarContainer:ActionBar.ActionBarContainer;
		public var miniMap_mc:MiniMapWraper;
		public var dayNight_mc:DayNightWrapper;
		public var chatBar:ChatBar;
		public var smartChat:SmartChat;
		public var shopBar_mc:ShopBar;
		public var inventoriesBar_mc:InventoriesBar;
		public var decor_lines_down_mc:DecorLine;
		public var EscMenuNonclickable_mc:NonClickable;
		public var charStats_mc:CharStats;
		public var socialBar_mc:MovieClip;
		public var statisticsBar_mc:StatisticsBar;
		public var selectionCharStats_mc:CharStats;
		public var escMenu_mc:EscapeMenuBar;
		public var announcement_mc:Announcement;
		public var impulsShop_mc:ImpulsShop;
		public var contextMenu_pnl:ContextMenu;
		public var optionsWindow:OptionsWindow;
		public var voting_mc:VoteMenu;
		public var messageBox:MessageBox;
		public var endGameScreen_mc:EndGameScreen;
		public var reportWindow:ReportWindow;
		
		public var NPCLineUp_mc:UpperNpcDialogLine;
		public var NPCLineDown_mc:DownNpcDialogLine;
		
		public var questTracker_mc:QuestTracker;
		public var version_mc:Version;
		public var questHint:QuestHint;
//		public var bubble:BubbleControl;
		
		/////////////////////////////////////////////////////////
		private var CloseBarsButtons:Array;
		private var buttonArr:Array;
		
		private var miniGameOpened:Boolean = false;
		
		private var fpsCounter:FPSCounter;
		
		public var finalStat:FinalStatisticsBar;
		public var LeavedPlayers:Array = [];
		public var TutorialBlocks:Dictionary = new Dictionary();
		public var TutorialHighlighters:Dictionary = new Dictionary();
		
		private var windows:Array = [];
		private var winVisabilityController:WinVisabilityController;
		private var playersDatas:Array = [];
		private var This:Main;
		public var BubleControls:Dictionary;
		
		public var ObjectsForGreyMask:Dictionary = new Dictionary();
		
		public var bubbleVisabilityController:BubbleVisabilityController;
		
		private var tutorialOvertipHighlight:HeroOvertipStroke;
		private var reportedUsers:Array = new Array();
	
		public function get LocalizationResources():Class
		{
			return Localization;
		}
		
		public function Main()
		{
			This = this;
			this.addEventListener(Event.ADDED_TO_STAGE, thisAdded);
			
			this.mouseEnabled = false;
			
			function thisAdded(e:Event):void
			{
				This.removeChild(font1);
				This.removeChild(font2);
				font1 = null;
				font2 = null;
				
				selectionCharStats_mc.isSelectionCharStats = true;
				
				var scale:Number = 1.0000;
				stage.scaleMode = StageScaleMode.NO_SCALE;
				stage.align = StageAlign.TOP_LEFT;
				stage.quality = "low";
				
				decor_lines_down_mc.mouseEnabled = false;
				
				_mainInterFace = new MainInterface(This);
				_preferencesInterFace = new Preferences(This);
				
				m_startRezW = 1280;
				m_startRezH = 1024;
				
				m_currScreenW = m_startRezW;
				m_currScreenH = m_startRezH;
				
				stage.addEventListener(MouseEvent.MOUSE_UP, actionMouseUp);
				stage.addEventListener(ContextMenuEvent.EVENT_TYPE, ShowContextMenu);
				stage.addEventListener(MouseEvent.MOUSE_DOWN, actionMouseDown);
				stage.addEventListener(MouseRightEvents.MOUSE_RIGHT_DOWN, actionMouseDown);
				addEventListener(MouseRightEvents.MOUSE_RIGHT_DOWN, ResetTargetState);
				
				addEventListener(ShareFinalStatisticEvent.EVENT_TYPE, OnShareFinalStatistic);
				addEventListener(SmartChatEvent.TOGGLE, OnToggleSmartChat, true);
				
				buttonArr = actionBarContainer.actionBar_mc.BarButtonsArray;
				windows = [talentsBar_mc, charStats_mc, inventoriesBar_mc, null, socialBar_mc, statisticsBar_mc, escMenu_mc, shopBar_mc, selectionCharStats_mc, talentsBarContext_mc, optionsWindow, messageBox, reportWindow, questHint]
				for (var i:int = 0; i < windows.length; i++)
				{
					if (windows[i] != null)
						windows[i].WindowIndex = i;
				}
				
				winVisabilityController = new WinVisabilityController(windows, buttonArr, This);
				winVisabilityController.NonClickableMov = EscMenuNonclickable_mc;
				
				reportWindow.ReportedUsers = reportedUsers;
				
				HideAllWindows();
				
				talentsBar_mc.ImpulseShower = actionBarContainer.actionBar_mc;
				
				SoundController.Init();
				
				//tooltip = new ToolTip();
				tooltip.mainContainer = This;
				//addChild(tooltip);
				
				if (!DELETE_ALL_NOT_TRUNK_THINGS_TOOLTIPS)
					stage.addEventListener(ButtonTooltipEvent.EVENT_TYPE, tooltip.tooltipHandler);
				
				stage.addEventListener(ErrorEvent.SHOW_ERROR, ShowErrorMessageFromFlash);
				finalStat = new FinalStatisticsBar();
				
				var myIcoDrag:icoDrag = new icoDrag();
				myIcoDrag.visible = false;
				addChild(myIcoDrag);
				DnDController.iconObject = myIcoDrag;
				
				selectionCharStats_mc.ChangeSelectionCharStatTooltipCommands(true);
				
				heroInfo_mc.heroInfoAnim_mc.healthBar = actionBarContainer.actionBar_mc.healthBar_mc;
				heroInfo_mc.heroInfoAnim_mc.manaBar = actionBarContainer.actionBar_mc.manaBar_mc;
				
				CloseButtonTooltip = Localization.Tooltip_AllWindowsCloseBtn;
				if (Localization.CompleteEventDispatcher != null)
					Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
				
				TutorialBlocks[ETutorialBlocks.ActionBarBlock] = new TutorialShower([actionBarContainer.actionBar_mc]);
				TutorialBlocks[ETutorialBlocks.ActionBarCharStatBtn] = new TutorialShower([actionBarContainer.actionBar_mc.char_btn]);
				TutorialBlocks[ETutorialBlocks.ActionBarEscBtn] = new TutorialShower([actionBarContainer.actionBar_mc.esc_btn]);
				TutorialBlocks[ETutorialBlocks.ActionBarInventoryBtn] = new TutorialShower([actionBarContainer.actionBar_mc.inventory_btn]);
				//TutorialBlocks[ETutorialBlocks.ActionBarQuestBtn] = new TutorialShower([actionBarContainer.actionBar_mc.questlog_btn]);
				//TutorialBlocks[ETutorialBlocks.ActionBarSocialBtn] = new TutorialShower([actionBarContainer.actionBar_mc.social_btn]);
				TutorialBlocks[ETutorialBlocks.ActionBarStatisticBtn] = new TutorialShower([actionBarContainer.actionBar_mc.statistics_btn]);
				TutorialBlocks[ETutorialBlocks.ActionBarTalentBtn] = new TutorialShower([actionBarContainer.actionBar_mc.talents_btn]);
				TutorialBlocks[ETutorialBlocks.MiniMapBlock] = new TutorialShower([miniMap_mc]);
				TutorialBlocks[ETutorialBlocks.MoneyBlock] = new TutorialShower([actionBarContainer.actionBar_mc.naftaGold_mc]);
				TutorialBlocks[ETutorialBlocks.PlayerHeroBlock] = new TutorialShower([heroInfo_mc]);
				TutorialBlocks[ETutorialBlocks.TopPlayerBlock] = new TutorialShower([teamInfoFrendly_mc.teamMate1_mc])
				TutorialBlocks[ETutorialBlocks.SelectionBlock] = new TutorialShower([selectionInfo_mc]);
				TutorialBlocks[ETutorialBlocks.FriendlyTeamMateBlock] = new TutorialShower([teamInfoFrendly_mc]);
				TutorialBlocks[ETutorialBlocks.EnemyTeamMateBlock] = new TutorialShower([teamInfoEnemy_mc]);
				TutorialBlocks[ETutorialBlocks.ChatBlock] = new TutorialShower([chatBar]);
				TutorialBlocks[ETutorialBlocks.ImpulseTalent] = new TutorialShower([actionBarContainer.actionBar_mc.impulsTalent_mc]);
				TutorialBlocks[ETutorialBlocks.ActionBarPortalBtn] = new TutorialShower([actionBarContainer.actionBar_mc.portalBtn]);
				TutorialBlocks[ETutorialBlocks.TalentsSet] = new TutorialShower([talentsBar_mc]);
				TutorialBlocks[ETutorialBlocks.CharStats] = new TutorialShower([charStats_mc]);
				TutorialBlocks[ETutorialBlocks.SelectionTalents] = new TutorialShower([talentsBarContext_mc]);
				TutorialBlocks[ETutorialBlocks.SelectionCharStats] = new TutorialShower([selectionCharStats_mc]);
				TutorialBlocks[ETutorialBlocks.Inventory] = new TutorialShower([inventoriesBar_mc]);
				TutorialBlocks[ETutorialBlocks.LockActionBar] = new TutorialShower([actionBarContainer.actionBar_mc.lockBtn]);
				
				TutorialBlocks[ETutorialBlocks.EscMenuOptionsButton] = new TutorialShower([escMenu_mc.options_btn]);
				TutorialBlocks[ETutorialBlocks.EscMenuContinueButton] = new TutorialShower([escMenu_mc.continue_btn]);
				TutorialBlocks[ETutorialBlocks.EscMenuExitButton] = new TutorialShower([escMenu_mc.exit_btn]);
				TutorialBlocks[ETutorialBlocks.EscMenuRunToCastleButton] = new TutorialShower([escMenu_mc.run_btn]);
				TutorialBlocks[ETutorialBlocks.EscMenuStopZumaLevelButton] = new TutorialShower([escMenu_mc.stopLevel_btn]);
				TutorialBlocks[ETutorialBlocks.EscMenuSurrenderButton] = new TutorialShower([escMenu_mc.surrender_btn]);
				

				TutorialHighlighters[ETutorialHighlitedObjects.CAMERA_BTN] = new TutorialHighlighter(miniMap_mc.miniMapAnim_mc.cameraBtn,null,TutorialHighlighter.RoundStrokeType,0,0);
				TutorialHighlighters[ETutorialHighlitedObjects.ALERT_BTN] = new TutorialHighlighter(miniMap_mc.miniMapAnim_mc.signalBtn,null,TutorialHighlighter.RoundStrokeType,0,0);
				TutorialHighlighters[ETutorialHighlitedObjects.HEALTHBAR] = new TutorialHighlighter(actionBarContainer.actionBar_mc.healthBar_mc,actionBarContainer.actionBar_mc.healthBar_mc.myScaleBitmap, TutorialHighlighter.SquadStrokeType, -3, -2, 4);
				TutorialHighlighters[ETutorialHighlitedObjects.MANABAR] = new TutorialHighlighter(actionBarContainer.actionBar_mc.manaBar_mc,actionBarContainer.actionBar_mc.manaBar_mc.myScaleBitmap, TutorialHighlighter.SquadStrokeType, -3, -2, 4);
				TutorialHighlighters[ETutorialHighlitedObjects.TOPLEVELHIGHLIGHT] = new TutorialHighlighter(teamInfoFrendly_mc.teamMate1_mc.levelHighLight,null, TutorialHighlighter.RoundStrokeType);
				TutorialHighlighters[ETutorialHighlitedObjects.DOWNLEVELHIGHLIGHT] = new TutorialHighlighter(heroInfo_mc.heroInfoAnim_mc.levelHighLight,null, TutorialHighlighter.RoundStrokeType);

				TutorialHighlighters[ETutorialHighlitedObjects.ACTIONBARTALENTBTN] = new TutorialHighlighter(actionBarContainer.actionBar_mc.talents_btn.toggleButtonSmall_mc,null, TutorialHighlighter.SquadStrokeType,0,0,-1);
				TutorialHighlighters[ETutorialHighlitedObjects.ACTIONBARCHARSTATBTN] = new TutorialHighlighter(actionBarContainer.actionBar_mc.char_btn.toggleButtonSmall_mc,null, TutorialHighlighter.SquadStrokeType,0,0,-1);
				TutorialHighlighters[ETutorialHighlitedObjects.ACTIONBARESCBTN] = new TutorialHighlighter(actionBarContainer.actionBar_mc.esc_btn.toggleButtonSmall_mc,null, TutorialHighlighter.SquadStrokeType,0,0,-1);
				TutorialHighlighters[ETutorialHighlitedObjects.ACTIONBARINVENTORYBTN] = new TutorialHighlighter(actionBarContainer.actionBar_mc.inventory_btn.toggleButtonSmall_mc,null, TutorialHighlighter.SquadStrokeType,0,0,-1);
				TutorialHighlighters[ETutorialHighlitedObjects.ACTIONBARSTATISTICBTN] = new TutorialHighlighter(actionBarContainer.actionBar_mc.statistics_btn.toggleButtonSmall_mc,null, TutorialHighlighter.SquadStrokeType, 0, 0, -1);
				TutorialHighlighters[ETutorialHighlitedObjects.TALENT_SET_SECOND_LEVEl] = new TutorialHighlighter(talentsBar_mc.secondRawHighlighter,null, TutorialHighlighter.SquadStrokeType,-30);
				TutorialHighlighters[ETutorialHighlitedObjects.PortalButton] = new TutorialHighlighter(actionBarContainer.actionBar_mc.portalBtn, actionBarContainer.actionBar_mc.portalBtn.toggleButton_mc, TutorialHighlighter.SquadStrokeType);
				
				BubleControls = new Dictionary();
				BubleControls[EBubbledElements.BUBBLED_BOTTLE] = actionBarContainer.actionBar_mc.naftaGold_mc.bottle_mc;//actionBarContainer.actionBar_mc.naftaGold_mc.bottle_mc;
				BubleControls[EBubbledElements.IMPULSETALENT] = actionBarContainer.actionBar_mc.impulsTalent_mc;
				BubleControls[EBubbledElements.TALENT_SET_SECOND_LEVEl] = talentsBar_mc.secondRawHighlighter;
				BubleControls[EBubbledElements.ACTIONBARCHARSTATBTN] = actionBarContainer.actionBar_mc.char_btn;
				BubleControls[EBubbledElements.ACTIONBARESCBTN] = actionBarContainer.actionBar_mc.esc_btn;;
				BubleControls[EBubbledElements.ACTIONBARINVENTORYBTN] = actionBarContainer.actionBar_mc.inventory_btn;
				BubleControls[EBubbledElements.ACTIONBARSTATISTICBTN] = actionBarContainer.actionBar_mc.statistics_btn;
				BubleControls[EBubbledElements.ACTIONBARTALENTBTN] = actionBarContainer.actionBar_mc.talents_btn;
				BubleControls[EBubbledElements.BUBBLED_QUEST_TRACKER] = questTracker_mc;
				BubleControls[EBubbledElements.CAMERA_BTN] = miniMap_mc.miniMapAnim_mc.cameraBtn;
				BubleControls[EBubbledElements.BUBBLED_SIGNAL_BUTTON] = miniMap_mc.miniMapAnim_mc.signalBtn;
				BubleControls[EBubbledElements.BUBBLED_CHANNELIN_BAR] = actionBarContainer.actionBar_mc.channelBar;
				BubleControls[ETutorialHighlitedObjects.PortalButton] = actionBarContainer.actionBar_mc.portalBtn;
				
				addEventListener(PrepareReportWindowEvent.CONTEXT_REPORT, OnPrepareReportWindow);
				
				bubbleVisabilityController = new BubbleVisabilityController(This);
				
				SetDisplayObjectsForGreyMask();
			}
		}
		
		private function OnShareFinalStatistic(e:ShareFinalStatisticEvent):void 
		{
			if (finalStat == null)
				return;
			
			winVisabilityController.HideAllWindows();
			chatBar.ForcedHide();
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
		
			finalStat.x = stage.stageWidth  / 2;
			finalStat.y = stage.stageHeight  / 2;
			
			FSCommands.Send(FSCommands.SHARE_FINAL_STATISTICS);
		}
		
		private function OnToggleSmartChat(e:Event):void
		{
			e.stopPropagation();
			
			smartChat.Toggle();
		}
		
	
		private function SetDisplayObjectsForGreyMask():void 
		{
			ObjectsForGreyMask[ETutorialHighlitedObjects.CAMERA_BTN] = miniMap_mc.miniMapAnim_mc.cameraBtn
			ObjectsForGreyMask[ETutorialHighlitedObjects.ALERT_BTN] = miniMap_mc.miniMapAnim_mc.signalBtn
			ObjectsForGreyMask[ETutorialHighlitedObjects.HEALTHBAR] = actionBarContainer.actionBar_mc.healthBar_mc
			ObjectsForGreyMask[ETutorialHighlitedObjects.MANABAR] = actionBarContainer.actionBar_mc.manaBar_mc;
			ObjectsForGreyMask[ETutorialHighlitedObjects.TOPLEVELHIGHLIGHT] = teamInfoFrendly_mc.teamMate1_mc.levelHighLight;
			ObjectsForGreyMask[ETutorialHighlitedObjects.DOWNLEVELHIGHLIGHT] = heroInfo_mc.heroInfoAnim_mc.levelHighLight;

			ObjectsForGreyMask[ETutorialHighlitedObjects.ACTIONBARTALENTBTN] = actionBarContainer.actionBar_mc.talents_btn;
			ObjectsForGreyMask[ETutorialHighlitedObjects.ACTIONBARCHARSTATBTN] = actionBarContainer.actionBar_mc.char_btn;
			ObjectsForGreyMask[ETutorialHighlitedObjects.ACTIONBARESCBTN] = actionBarContainer.actionBar_mc.esc_btn;
			ObjectsForGreyMask[ETutorialHighlitedObjects.ACTIONBARINVENTORYBTN] = actionBarContainer.actionBar_mc.inventory_btn;
			ObjectsForGreyMask[ETutorialHighlitedObjects.ACTIONBARSTATISTICBTN] = actionBarContainer.actionBar_mc.statistics_btn;
			
			ObjectsForGreyMask[ETutorialHighlitedObjects.HINTLINE] = actionBarContainer.hintMessage_mc;
			ObjectsForGreyMask[ETutorialHighlitedObjects.IMPULSETALENT] = actionBarContainer.actionBar_mc.impulsTalent_mc;
			ObjectsForGreyMask[ETutorialHighlitedObjects.NAFTABTN] = actionBarContainer.actionBar_mc.naftaGold_mc;
			ObjectsForGreyMask[ETutorialHighlitedObjects.TALENTBAR] = talentsBar_mc;
			ObjectsForGreyMask[ETutorialHighlitedObjects.INVENTORYBAR] = inventoriesBar_mc;
			ObjectsForGreyMask[ETutorialHighlitedObjects.SHOPBAR] = shopBar_mc;
			ObjectsForGreyMask[ETutorialHighlitedObjects.ESCMENU] = escMenu_mc;
			ObjectsForGreyMask[ETutorialHighlitedObjects.CONFIRMATIONDIALOG] = messageBox;
			ObjectsForGreyMask[ETutorialHighlitedObjects.TALENT_SET_SECOND_LEVEl] = talentsBar_mc.secondRawHighlighter;
			ObjectsForGreyMask[ETutorialHighlitedObjects.PortalButton] = actionBarContainer.actionBar_mc.portalBtn;
			ObjectsForGreyMask[EBubbledElements.BUBBLED_QUEST_TRACKER] = questTracker_mc;
			ObjectsForGreyMask[ETutorialHighlitedObjects.OPTIONSWINDOW] = optionsWindow;
			ObjectsForGreyMask[ETutorialHighlitedObjects.QUESTHINT] = questHint;
		}
		
		public function ProcessSpecialUiBlock(id:String, show:Boolean):Boolean 
		{
			if (id == ETutorialBlocks.TalentsSetBlock) 
			{
				winVisabilityController.ShowTalentsSet(show);
				return true;
			}
			
			if (id == ETutorialBlocks.Buffs)
			{
				actionBarContainer.actionBar_mc.ShowBuffsForTutorial(show);
				return true;
			}
			
			return false;
		}
		
		private function actionMouseDown(e:MouseEvent):void
		{
			if (contextMenu_pnl.visible && contextMenu_pnl.MouseIsOut)
			{
				SoundController.PlaySound(SoundController.UI_CLOSE);
				contextMenu_pnl.visible = false;
			}
		}
		
		private function ShowContextMenu(e:ContextMenuEvent):void
		{
			SoundController.PlaySound(SoundController.UI_OPEN_SMALL);
			contextMenu_pnl.subject = e.target as MovieClip;
			contextMenu_pnl.ShowMenu(e.items);
			setChildIndex(contextMenu_pnl, numChildren - 1);
		}
		
		private function FillLocalization(e:Event):void
		{
			CloseButtonTooltip = Localization.Tooltip_AllWindowsCloseBtn;
			chatBar.chatInput_mc.FillLocalization(Localization.ChatInputComboBox_EnterName, Localization.RestrictedChatSymbols, Localization.Tooltip_PreferenceMenu_ReceiveRegularChatMessages);
			chatBar.chatInput_mc.chatOutput_cbText.text = Localization.PreferenceMenu_ReceiveRegularChatMessages;
			chatBar.CantFindPlayer = Localization.ChatBar_CantFindPlayer;
		}
		
		public function get CloseButtonTooltip():String
		{
			return winVisabilityController.CloseButtonTooltip;
		}
		
		public function set CloseButtonTooltip(value:String):void
		{
			winVisabilityController.CloseButtonTooltip = value;
			endGameScreen_mc.CloseButtonTooltip = value;
		}
		
		public function get Players():Array
		{
			return playersDatas;
		}
		
		public function AddPlayerData(player:PlayerStatisticData):void
		{
			playersDatas.push(player);
		}
		
		public function addFinalStatistic(isVictory:Boolean):void
		{
			finalStat.Players = playersDatas;
			finalStat.BatleStat = statisticsBar_mc.CurrentGameStatistic;
			finalStat.Victory = isVictory;
			
			addChild(finalStat);
			
			this.setChildIndex(finalStat, this.numChildren - 1);
			this.setChildIndex(chatBar, this.numChildren - 1);
		}
		
		public function skipFinalStatistic():void
		{
			FSCommands.Send(FSCommands.ESCMENU_RETURN_TO_LOBBY);
		}
		
		public function get mainInterface():MainInterface
		{
			return _mainInterFace;
		}
		
		public function get PreferencesInterface():Preferences
		{
			return _preferencesInterFace;
		}
		
		public function ShowFPS(show:Boolean):void
		{
			if (fpsCounter == null)
			{
				addChild(fpsCounter = new FPSCounter());
				fpsCounter.visible = false;
			}
			
			if (show)
				fpsCounter.visible = true;
			else
				fpsCounter.visible = false;
		}
		
		private function actionMouseUp(e:MouseEvent):void
		{
			if (DnDController.isDragging)
			{
				if (DnDController.DraggingObject.CanDragOutside)
					DnDController.DraggingObject.DragOutSide();
				DnDController.EndDrag();
			}
		}
		
		private function ResetTargetState(e:MouseEvent):void
		{
			FSCommands.Send(FSCommands.RESET_TARGET_STATE);
		}
		
		public function MiniGameOpen(enter:Boolean):void
		{
			if (enter)
				HideAllWindows();
			miniGameOpened = enter;
			actionBarContainer.actionBar_mc.ShowCentral(!enter);
			escMenu_mc.miniGameOn(enter);
			miniMap_mc.MiniGameOn = enter;
			heroInfo_mc.MiniGameOn = enter;
		}
		
		public function ShowImpulseBuff(path:String):void
		{
			if (escMenu_mc.visible == true)
				this.setChildIndex(impulsShop_mc, this.numChildren - 3);
			else
				this.setChildIndex(impulsShop_mc, this.numChildren - 1);
			
			impulsShop_mc.ShowImpulsBuff(path);
		}
		
		public function IsWindowVisible(winNum:int):Boolean
		{
			return winVisabilityController.IsWindowVisible(winNum);
		}
		
		public function ShowHideWindow(winNum:int):void
		{
			contextMenu_pnl.visible = false;
			winVisabilityController.SwitchWindowState(winNum);
		}
		
		private function HideAllWindows():void
		{
			winVisabilityController.HideAllWindows();
			
			selectionInfo_mc.HideWithoutSound();
			
			SoundController.PlaySound(SoundController.UI_CLOSE);
			
			impulsShop_mc.HideImpulseBuff(false, false);
		}
		
		public function OnEscapeBtnClick():Boolean
		{
			if (smartChat.visible)
			{
				smartChat.Hide();
				return true;
			}
			
			if (chatBar.chatInput_mc.visible)
			{
				chatBar.EscPressed();
				return true;
			}
			
			contextMenu_pnl.visible = false;
			
			if (optionsWindow.visible)
			{
				optionsWindow.OnCloseByEsc();
				winVisabilityController.HideSomeWindow(EWindows.WINDOW_OPTIONSBAR);
				return true;
			}
			
			if (messageBox.visible)
			{
				messageBox.OnNoBtnClick(null);
				return true;
			}
			
			if (questHint.visible) 
			{
				questHint.OnEscPressed();
				return true;
			}
			
			for (var i:int = 0; i < windows.length; i++)
			{
				if (windows[i] != null && windows[i].visible)
				{
					HideAllWindows();
					return true;
				}
			}
			if (selectionInfo_mc.visible || impulsShop_mc.visible)
			{
				selectionInfo_mc.SetIcon("", false);
				return true;
			}
			
			return false;
		}
		
		public function OpenEscMenu():void
		{
			winVisabilityController.ShowSomeWindow(EWindows.WINDOW_ESCMENUBAR);
		}
		
		public function OpenWindow(winNum:int):void
		{
			winVisabilityController.ShowSomeWindow(winNum);
		}
		
		public function UseSlot(slot:int)
		{
			if (EscMenuNonclickable_mc.visible)
				return;
			actionBarContainer.actionBar_mc.UseSlot(slot);
		}
		
		//CharStat----------------------------------------
		
		public function SetBaseStat(isSelection:Boolean, valueType:int, value:int, addition:int, isImportant:Boolean):void
		{
			var fillingStatistica:CharStats = isSelection ? selectionCharStats_mc : charStats_mc;
			
			if (fillingStatistica == null)
				return;
			
			fillingStatistica.SetBaseStat(valueType, value, addition, isImportant);
		}
		
		public function SetDerivativeStat(isSelection:Boolean, valueType:int, value:int):void
		{
			var fillingStatistica:CharStats = isSelection ? selectionCharStats_mc : charStats_mc;
			
			if (fillingStatistica == null)
				return;
			
			fillingStatistica.SetDerivativeStat(valueType, value)
		}
		
		public function SetCharStatUnit(isSelection:Boolean, heroID:int, iconPath:String, heroName:String, fraction:int, damageType:int ):void
		{
			var fillingStatistica:CharStats = isSelection ? selectionCharStats_mc : charStats_mc;
			
			if (fillingStatistica == null)
				return;
			
			var player:PlayerStatisticData = GetPlayerData(heroID);
			
			fillingStatistica.ShowingDamageType = damageType;

			if (player == null)
			{
				fillingStatistica.SetCreapIdentity(iconPath, heroName, fraction, damageType);
				return
			}
			
			fillingStatistica.SetHeroIdentity(player);
		}
		
		private function GetPlayerData(heroId:int):PlayerStatisticData
		{
			for each (var playerData:PlayerStatisticData in playersDatas)
			{
				if (playerData.HeroId == heroId)
					return playerData;
			}
			
			return null;
		}
		
		public function SetCharStatUnitParams(isSelection:Boolean, level:int, curHealth:int, maxHealth:int, curMana:int, maxMana:int):void
		{
			var fillingStatistica:CharStats = isSelection ? selectionCharStats_mc : charStats_mc;
			
			if (fillingStatistica == null)
				return;
			
			fillingStatistica.SetHeroParams(level, curHealth, maxHealth, curMana, maxMana);
		}
		
		//SetBuff-------------------------------
		
		public function SetBuffIcon(isSelection:Boolean, path:String, index:int, isPositive:Boolean):void
		{
			if (!isSelection)
				actionBarContainer.actionBar_mc.SetBuffIcon(isSelection, path, index, isPositive);
			else
				selectionInfo_mc.SetBuffIcon(isSelection, path, index, isPositive);
		}
		
		public function SetBuffStatus(isSelection:Boolean, index:int, cooldown:Number, count:int):void
		{
			if (!isSelection)
				actionBarContainer.actionBar_mc.SetBuffStatus(index, cooldown, count);
			else
				selectionInfo_mc.SetBuffStatus(index, cooldown, count);
		}
		
		//Всё по статистике ------------------------------
			
		public function ShowStatisticsBar(show:Boolean):void
		{
			contextMenu_pnl.visible = false;
			if (show)
				winVisabilityController.ShowSomeWindow(EWindows.WINDOW_STATISTICBAR)
			else
				winVisabilityController.HideSomeWindow(EWindows.WINDOW_STATISTICBAR);
		}
		
		public function ShowShop(show):void
		{
			if (show)
				winVisabilityController.ShowSomeWindow(EWindows.WINDOW_SHOPBAR);
			else
				winVisabilityController.HideSomeWindow(EWindows.WINDOW_SHOPBAR);
		}
		
		//------------------------------------------------------
		
		public function GameEnd(ourFraction:int, isVictory:Boolean, screen:String, dontShowStatistics:Boolean, dontShowDialog:Boolean):void
		{
			actionBarContainer.hintMessage_mc.visible = false;
			
			statisticsBar_mc.allStats_mc.SetGameEnded(isVictory);
			contextMenu_pnl.visible = false;
			actionBarContainer.ShowFinalAnimation();
			miniMap_mc.ShowFinalAnimation();
			dayNight_mc.ShowFinalAnimation();
			heroInfo_mc.ShowFinalAnimation();
			selectionInfo_mc.ShowFinalAnimation();
			teamInfoFrendly_mc.ShowFinalAnimation();
			teamInfoEnemy_mc.ShowFinalAnimation();
			questTracker_mc.ShowFinalAnimation();
			
			winVisabilityController.ShowFinalAnimation();
			
			announcement_mc.CloseAtTheEndOfTheGame();
			
			EscMenuNonclickable_mc.alpha = 0;
			EscMenuNonclickable_mc.visible = true;
			
			this.setChildIndex(EscMenuNonclickable_mc, this.numChildren - 1);
			this.setChildIndex(chatBar, this.numChildren - 1);
			
			if (dontShowDialog)
			{
				var cover:Shape = new Shape();
			
				cover.graphics.beginFill(0x000000, 1);
				cover.graphics.drawRect(0, 0, stage.stageWidth, stage.stageHeight);
				cover.graphics.endFill();
				
				this.addChildAt(cover, this.numChildren - 2);
				
//				cover.x = -0.5 * cover.width;
//				cover.y = -0.5 * cover.height;
				cover.alpha = 0;
				
				var tween:Tween = new Tween(cover, 'alpha', Strong.easeOut, 0, 1, stage.frameRate);
				
				tween.start();
			}
			else
			{
				this.setChildIndex(endGameScreen_mc, this.numChildren - 2);
				
				function showFinalStatistic():void
				{
					addFinalStatistic(isVictory);
					
					DoProcessDeferredPlaySameTeamDecisions();
				}
				
				function startPlaySameTeamCountdown():void
				{
					if (finalStat == null)
						return;
					if (finalStat.playSameTeam == null)
						return;
					
					finalStat.playSameTeam.StartCountdown();
				}
				
				if (dontShowStatistics)
				{
					endGameScreen_mc.ShowEndScreen(screen, isVictory, skipFinalStatistic);
				}
				else
				{
					startPlaySameTeamCountdown();
					
					endGameScreen_mc.ShowEndScreen(screen, isVictory, showFinalStatistic);
				}
			}
		}
		
		public function ConfigurePlaySameTeamFeature(available:Boolean, timeOut:int):void
		{
			if (finalStat == null)
				return;
			
			if (finalStat.playSameTeam != null)
				finalStat.playSameTeam.Configure(available, timeOut);
		}
		
		private var _deferredPlaySameTeamDecisions:Array = new Array();
		
		public function HandlePlaySameTeamDecision(id:int, agreed:Boolean):void
		{
			if (finalStat == null)
				return;
				
			if (finalStat.parent == null)
			{
				var decision:Object = { id: id, agreed: agreed };
				
				_deferredPlaySameTeamDecisions.push(decision);
			}
			else
			{
				DoHandlePlaySameTeamDecision(id, agreed)
			}
		}
		
		private function DoHandlePlaySameTeamDecision(id:int, agreed:Boolean):void
		{
			if (finalStat.batleStatistic != null)
				finalStat.batleStatistic.SetHeroAgreedToPlaySameTeam(id, agreed);
				
			if (finalStat.playSameTeam != null && finalStat.IsOurHero(id))
				finalStat.playSameTeam.Agreed = agreed;
		}
		
		private function DoProcessDeferredPlaySameTeamDecisions():void
		{
			for each (var decision:Object in _deferredPlaySameTeamDecisions)
			{
				DoHandlePlaySameTeamDecision(decision.id, decision.agreed);
			}
			
			_deferredPlaySameTeamDecisions = new Array();
		}
		
		public function SetOurHeroParams(level:int, curHealth:int, maxHealth:int, curMana:int, maxMana:int, timeToRessurect:int, channelingProgress:Number,healthRegen:Number,manaRegen:Number,isCameraLocked:Boolean)
		{
			actionBarContainer.actionBar_mc.ChannelingProgress = channelingProgress;
			
			var bottomMate:HeroMateInfo = heroInfo_mc.heroInfoAnim_mc;
			bottomMate.level = level;
			bottomMate.SetHeroParams(curHealth,maxHealth,curMana,maxMana,healthRegen,manaRegen);
		
			var isOurRessurecting:Boolean = timeToRessurect > 0;
					
			if (isOurRessurecting) 
			{
				bottomMate.SetHeroParams(0, maxHealth, 0, maxMana, healthRegen,manaRegen, false);
			}
			
			miniMap_mc.HeroIsDead = curHealth <= 0 || timeToRessurect > 0;
			miniMap_mc.CameraBtnStatus = isCameraLocked;

			actionBarContainer.actionBar_mc.actionBarDisable(curHealth <= 0 || timeToRessurect > 0);
			talentsBar_mc.HeroIsDead(curHealth <= 0 || timeToRessurect > 0)
							
			charStats_mc.SetHeroParams(level, curHealth, maxHealth, curMana, maxMana);
			charStats_mc.SetGreyMask(isOurRessurecting);
			charStats_mc.SetDeathTimeOut(timeToRessurect);
			
			talentsBar_mc.Level = level
		}
		
		public function ResetData():void
		{
			actionBarContainer.actionBar_mc.ResetActionBar();
			inventoriesBar_mc.ResetInventory();
			shopBar_mc.ResetShopItems();
			talentsBar_mc.ResetTalentBar();
			HideAllWindows();
		}
		
		public function SetErrorMessage(errorID:int, msg:String, playSound:Boolean, lifeTime:Number):void
		{
			actionBarContainer.actionBar_mc.SetErrorMessage(errorID, msg, playSound, lifeTime);
		}
		
		public function ShowErrorMessage(errorID:int, show:Boolean):void
		{
			actionBarContainer.actionBar_mc.ShowErrorMessage(errorID, show);
		}
		
		private function ShowErrorMessageFromFlash(e:ErrorEvent):void
		{
			
			ShowErrorMessage(e.id, true);
		}
		
		public function ShowErrorEvent(mes:String, playSound:Boolean, lifeTime:Number):void
		{
			actionBarContainer.actionBar_mc.ShowErrorEvent(mes, playSound, lifeTime);
		}
		
		public function ShowAnnouncement(announcementText:String, lifeTime:Number, priority:int):void
		{
			announcement_mc.SetAnouncementData(announcementText, lifeTime, priority);
		}
		
		public function SetAnnouncementPart(right:Boolean, portraitIcon:String, level:int, name:String, fraction:int):void
		{
			announcement_mc.SetAnnouncementPart(right, portraitIcon, level, name, fraction);
		}
		
		public function ShowExitGameDialog(isGameWithBots:Boolean, spectatorMode:Boolean):void
		{
			FSCommands.Send(FSCommands.ESCMENU_DISABLEHOTKEYS, FSCommands.ENABLE);
			dispatchEvent(new ShowDialogEvent(Localization.MessageBox_Header, isGameWithBots || spectatorMode? Localization.MessageBox_ExitTrainingGame : Localization.MessageBox_ExitGame, OnExitGameOk, OnExitGameCancel));
		}
		
		private function OnExitGameOk():void
		{
			FSCommands.Send(FSCommands.ESCMENU_EXITGAME);
			
			if (!escMenu_mc.visible && !optionsWindow.visible)
				FSCommands.Send(FSCommands.ESCMENU_DISABLEHOTKEYS, FSCommands.DISABLE);
		}
		
		private function OnExitGameCancel():void
		{
			FSCommands.Send(FSCommands.ESCMENU_CONTINUE);
			
			if (!escMenu_mc.visible && !optionsWindow.visible)
				FSCommands.Send(FSCommands.ESCMENU_DISABLEHOTKEYS, FSCommands.DISABLE);
		}
		
		public function ShowMessageBox(header : String, text : String, isOk:Boolean = false):void
		{
			dispatchEvent(new ShowDialogEvent(header, text, OnMessageBoxYes, OnMessageBoxNo, isOk));
		}

		private function OnMessageBoxYes():void 
		{
			FSCommands.Send(FSCommands.MESSAGEBOX_BUTTON_CLICK, "1");
		}

		private function OnMessageBoxNo():void 
		{
			FSCommands.Send(FSCommands.MESSAGEBOX_BUTTON_CLICK, "2");
		}
		
		public function ShowTutorialOvertipLevelHighlight(show:Boolean, x:Number, y:Number):void 
		{
			if (show)
			{
				if (tutorialOvertipHighlight == null)
				{
					tutorialOvertipHighlight = new HeroOvertipStroke();
					this.addChild(tutorialOvertipHighlight);
				}
				
				tutorialOvertipHighlight.x = x - tutorialOvertipHighlight.width * 0.5;
				tutorialOvertipHighlight.y = y - tutorialOvertipHighlight.height * 0.5;
			}
			else
			{
				if (tutorialOvertipHighlight != null)
					this.removeChild(tutorialOvertipHighlight);
			}
		}
		
		private function OnPrepareReportWindow(e:PrepareReportWindowEvent):void 
		{
			trace ("Report Catched!");
			for (var i:int = 0; i < reportedUsers.length; i++) 
			{
				if (reportedUsers[i] == e.heroID) 
				{
					ShowMessageBox(Localization.ReportWindow_MessageBoxHeader, Localization.ReportWindow_MessageBoxText, true);
					return;
				}
			}
			
			if (reportWindow.TrySetHeroReportParams(e.heroID, e.playerName))
				winVisabilityController.ShowSomeWindow(EWindows.WINDOW_REPORT);
			else
				ShowMessageBox(Localization.ReportWindow_MessageNoReportDataHeader, Localization.ReportWindow_MessageNoReportDataText, true);
		}
		
	}
}
