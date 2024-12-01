package EscMenu
{
	import Events.ChatBarChannelSelectEvent;
	import Events.ShowDialogEvent;
	import Controllers.WinVisabilityController;
	import Enums.EWindows;
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Rectangle;
	import flash.text.TextField;
	import BaseClasses.BaseDragObject;
	import Components.ButtonStandart;
	import Events.WindowVisibleControllerEvent;
	
	public class EscapeMenuBar extends BaseDragObject
	{
		public var options_btn:ButtonStandart;
		public var surrender_btn:ButtonStandart;
		public var run_btn:ButtonStandart;
		public var exit_btn:ButtonStandart;
		public var stopLevel_btn:ButtonStandart;
		public var continue_btn:ButtonStandart;
		public var skip_btn:ButtonStandart;
		
		public var header_txt:TextField;
		
		private var firstTime:Boolean = true;
		private var _isPlayngMiniGame:Boolean = false;
		private var exitDialogText:String = "Выйти из игры.";
		private var exitTrainDialogText:String = "Выйти из игры c ботами.";
		private var exitToLoobyDialogText:String = "Выйти в город";
		private var exitToLoobyFromTrainingDialogText:String = "Выйти в город";
		public var IsCurrentGameIsTraining:Boolean = false;
		public var IsSpectatorModeOn:Boolean = false;
		
		private var _tutorialMode:Boolean = false;
		
		public function EscapeMenuBar()
		{
			options_btn.addEventListener("Up", OptionsBtn);
			surrender_btn.addEventListener("Up", SurenderBtn);
			run_btn.addEventListener("Up", RunToTheCity);
			exit_btn.addEventListener("Up", ExitBtnClick);
			continue_btn.addEventListener("Up", CloseEscMenu);
			skip_btn.addEventListener("Up", SkipTutorialBtn);
			
			function onAddedToStage(e:Event):void
			{
				tutorialMode = false;
				
				removeEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
			}
			
			{
				addEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
			}
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
		}
		
		private function FillLocalization(e:Event):void
		{
			header_txt.text = Localization.EscMenuBar_HeaderText;

			options_btn.LocalizeText = Localization.EscMenuBar_OptionsBtnLabel;
			surrender_btn.LocalizeText = Localization.EscMenuBar_SurrenderBtnLabel;
			run_btn.LocalizeText = Localization.EscMenuBar_RunToCityBtnLabel;	
			exit_btn.LocalizeText = _isPlayngMiniGame? Localization.EscMenuBar_StopLevelBtnLabel : Localization.EscMenuBar_ExitBtnLabel;
			continue_btn.LocalizeText = Localization.EscMenuBar_ContinueBtnLabel;
			skip_btn.LocalizeText = Localization.EscMenuBar_SkipBtnLabel;
			
			exitDialogText = Localization.MessageBox_ExitGame;
			exitTrainDialogText = Localization.MessageBox_ExitTrainingGame;
			exitToLoobyDialogText = Localization.MessageBox_LeaveToLobby;
			exitToLoobyFromTrainingDialogText = Localization.MessageBox_LeaveToLobbyFromTraining;
		}
		
		public function get isPlayingMiniGame():Boolean
		{
			return _isPlayngMiniGame;
		}
		
		public function set tutorialMode(value:Boolean):void
		{
			_tutorialMode = value;
			
			if (_tutorialMode)
			{
				surrender_btn.disable();
				surrender_btn.visible = false;
				
				skip_btn.enable();
				skip_btn.visible = true;
			}
			else
			{
				surrender_btn.enable();
				surrender_btn.visible = true;
				
				skip_btn.disable();
				skip_btn.visible = false;
			}
		}
		
		public function miniGameOn(isInMinigame:Boolean):void
		{	
			_isPlayngMiniGame = isInMinigame;
			
			exit_btn.LocalizeText = _isPlayngMiniGame? Localization.EscMenuBar_StopLevelBtnLabel : Localization.EscMenuBar_ExitBtnLabel;
		}
		
		private function SurenderBtn(e:Event):void
		{	
			e.stopPropagation();
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN_CLOSE, WindowIndex));
			FSCommands.Send(FSCommands.ESCMENU_VOTE_FOR_SURRENDER);
		}
		
		private function OptionsBtn(e:Event):void
		{
			e.stopPropagation();
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN, EWindows.WINDOW_OPTIONSBAR));
		}
		
		private function RunToTheCity(e:Event):void
		{	
			e.stopPropagation();
			dispatchEvent(new ShowDialogEvent(Localization.MessageBox_Header, IsCurrentGameIsTraining||IsSpectatorModeOn? exitToLoobyFromTrainingDialogText : exitToLoobyDialogText, OnRunToLobby, null));
		}
		
		public function OnRunToLobby():void
		{
			FSCommands.Send(FSCommands.ESCMENU_RETURN_TO_LOBBY);
		}
		
		private function SkipTutorialBtn(e:Event):void
		{
			e.stopPropagation();
			dispatchEvent(new ShowDialogEvent(Localization.MessageBox_Header, Localization.MessageBox_ExitSkipTutorial, OnSkipTutorial, null));
		}
		
		public function OnSkipTutorial():void
		{
			FSCommands.Send(FSCommands.ESCMENU_SKIP_TUTORIAL);
		}	
		
		public function ExitBtnClick(e:Event):void
		{	
			e.stopPropagation();
			
			if (_isPlayngMiniGame) 
			{
				FSCommands.Send(FSCommands.ESCMENU_ABORTLEVEL)
				dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN_CLOSE,WindowIndex));
				return;
			}
			
			dispatchEvent(new ShowDialogEvent(Localization.MessageBox_Header, IsCurrentGameIsTraining||IsSpectatorModeOn? exitTrainDialogText: exitDialogText, OnExitBtnOk, null));
		} 
		
		public function OnExitBtnOk():void
		{
			FSCommands.Send(FSCommands.ESCMENU_EXITGAME);
		}
		
		private function CloseEscMenu(e:Event):void
		{	
			e.stopPropagation();
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN_CLOSE,WindowIndex));
		}
		
		public function set ShowMenu(show:Boolean):void 
		{
			this.visible = show;
			this.parent.setChildIndex(this, this.parent.numChildren - 1);
		}
		
		override protected function BaseBarObjectResize(e:Event=null):void
		{	
			super.BaseBarObjectResize();

			this.x = stage.stageWidth / 2;
			this.y = stage.stageHeight/ 2;
			this.x = Math.floor(this.x);
			this.y = Math.floor(this.y);
		}
		
		override protected function GetThisWindowToTheTop(e:MouseEvent):void 
		{
			
		}
		
		override public function AnimationClosing():void 
		{
			super.AnimationClosing();
			FSCommands.Send(FSCommands.ESCMENU_DISABLEHOTKEYS, FSCommands.DISABLE);
		}
		
		
		override public function ShowCinematicDialog():void
		{
			// remains unaffected by dialog
		}
		
		override public function HideCinematicDialog():void
		{
			// remains unaffected by dialog
		}
	}
	
}