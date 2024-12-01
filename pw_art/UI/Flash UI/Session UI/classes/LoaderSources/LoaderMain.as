package LoaderSources
{
	import BaseClasses.BaseIconLoader;
	import BaseClasses.TooltipSender;
	import Chat.ChatBar;
	import Components.ButtonStandart;
	import Components.Frame;
	import ContMenu.ContextMenu;
	import Controllers.SoundController;
	import Events.ContextMenuEvent;
	import Events.MouseRightEvents;
	import flash.display.MovieClip;
	import flash.display.StageScaleMode;
	import flash.display.StageAlign;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import MainScreen.ToolTip;
	import src.ButtonTooltipEvent;

	public class LoaderMain extends MovieClip
	{
		public var AvMight:TeamForceWrapper;
		public var team_pnl:LeftTeamHolder;
		public var enemyTeam_pnl:RightTeamHolder;
		public var loadingBar:LoadingBar;
		public var font1:TextField;
		public var font2:TextField;
		public var font3:TextField;
		public var backGround:BaseIconLoader;
		public var logo:BaseIconLoader;
		public var chatBar:ChatBar;
		public var tooltip:ToolTip;
		public var modificator:ModificatorWrapper;
		public var contextMenu_pnl:ContextMenu;
		private var _mainInterface:LoaderInterface;
		public var statusText:TextField;
		public var exitBtn:ButtonStandart;
		public var statusFrame:Frame;
		public var flag1:BaseIconLoader;
		public var flag2:BaseIconLoader;
		public var advice:GoodAdvice;

		private var exitXOffset:Number;
		private var exitYOffset:Number;
		private var initialStage:Point = new Point(1280,1024);

		private var statusFrameOffsetX:Number;
		private var statusFrameOffsetY:Number;

		private var statusFrameStartWidth:Number;
		private var statusFrameStartHeight:Number;

		private var flag1TooltipSender:TooltipSender;
		private var flag2TooltipSender:TooltipSender;
		
		private var _preferencesInterFace:LoaderPreferences;
		
		public function LoaderMain()
		{
			stop();
			var This:LoaderMain = this;

			this.addEventListener(Event.ADDED_TO_STAGE, Added);

			function Added(e:Event)
			{
				This.stop();

				exitXOffset = initialStage.x - exitBtn.x;
				exitYOffset = initialStage.y - exitBtn.y;

				var scale:Number = 1.0000;
				stage.scaleMode = StageScaleMode.NO_SCALE;
				stage.align = StageAlign.TOP_LEFT;
				stage.quality = "low";
				_mainInterface = new LoaderInterface(This);
				stage.addEventListener(Event.RESIZE, ResizeStage);

				tooltip.mainContainer = This;

				stage.addEventListener(ContextMenuEvent.EVENT_TYPE, ShowContextMenu);
				stage.addEventListener(MouseEvent.MOUSE_DOWN, actionMouseDown);

				stage.addEventListener(ButtonTooltipEvent.EVENT_TYPE, tooltip.tooltipHandler);
				stage.addEventListener(MouseRightEvents.MOUSE_RIGHT_DOWN, actionMouseDown);
				SoundController.Init();
				SetLoadingState(false);
				
				_preferencesInterFace = new LoaderPreferences(This);

				exitBtn.addEventListener("Up", OnExitClick);
				if (LoaderLocalization.CompleteEventDispatcher != null)
				{
					LoaderLocalization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, OnFillLocalization);
				}

				statusFrameStartWidth = statusFrame.width;
				statusFrameStartHeight = statusFrame.height;

				statusFrameOffsetX = statusText.x - statusFrame.x;
				statusFrameOffsetY = statusText.y - statusFrame.y;

				statusFrame.visible = statusText.visible = false;

				flag1.visible = flag2.visible = false;

				flag1TooltipSender = new TooltipSender(flag1);
				flag2TooltipSender = new TooltipSender(flag2);

				statusText.autoSize = TextFieldAutoSize.CENTER;

				flag1.addEventListener(Event.COMPLETE,OnFlagLoaded);
				flag2.addEventListener(Event.COMPLETE, OnFlagLoaded);

				chatBar.SetUseLoadingLocalisation();
				//chatBar.chatInput_mc.chatOutput_cb.visible = false;
				//chatBar.chatInput_mc.chatOutput_cbText.visible = false;
			}
		}
		
		public function get PreferencesInterface():LoaderPreferences
		{
			return _preferencesInterFace;
		}

		private function OnFlagLoaded(e:Event)
		{
			UpdateLocalisationPositions();
		}

		private function OnExitClick(e:Event):void
		{
			FSCommands.Send(FSCommands.ExitLoadingScreen);
		}

		private function ShowContextMenu(e:ContextMenuEvent):void
		{
			SoundController.PlaySound(SoundController.UI_OPEN_SMALL);
			contextMenu_pnl.ShowMenu(e.items);
			setChildIndex(contextMenu_pnl, numChildren - 1);
		}

		private function actionMouseDown(e:Event):void
		{
			if (contextMenu_pnl.visible && contextMenu_pnl.MouseIsOut)
			{
				SoundController.PlaySound(SoundController.UI_CLOSE);
				contextMenu_pnl.visible = false;
			}
		}

		public function get LocalizationResources():Class
		{
			return LoaderLocalization;
		}

		public function OnFillLocalization(e:Event):void
		{
			enemyTeam_pnl.BotName = LoaderLocalization.BotName;
			team_pnl.BotName = LoaderLocalization.BotName;
			chatBar.chatInput_mc.FillLocalization(LoaderLocalization.ChatInputComboBox_EnterName, LoaderLocalization.RestrictedChatSymbols, LoaderLocalization.Tooltip_PreferenceMenu_ReceiveRegularChatMessages);
			chatBar.chatInput_mc.chatOutput_cbText.text = LoaderLocalization.PreferenceMenu_ReceiveRegularChatMessages;
			chatBar.CantFindPlayer = LoaderLocalization.ChatBar_CantFindPlayer;
			exitBtn.LocalizeText = LoaderLocalization.ExitButtonText;
		}

		public function SetMapBack(back:String, logoIcon:String):void
		{
			backGround.SetIcon(back);
			logo.SetIcon(logoIcon);
			ResizeStage(null);
		}

		public function AddModeDescription(image:String, id:int):void
		{
			modificator.AddModeDescription(image, id);
		}

		public function SetLoadingStatusText(statText:String):void
		{
			statusFrame.visible = statusText.visible = statText.length != 0;
			statusText.text = statText;

			var statWidth:Number = statusText.width + 2 * statusFrameOffsetX;
			var statHeight:Number = statusText.height + 2 * statusFrameOffsetY;

			statusFrame.setSize((statWidth>statusFrameStartWidth? statWidth:statusFrameStartWidth),(statHeight>statusFrameStartHeight?statHeight:statusFrameStartHeight  ));
			ResizeStage(null);
		}

		public function SetLoadingState(preLoading:Boolean):void
		{
			team_pnl.visible = ! preLoading;
			enemyTeam_pnl.visible = ! preLoading;
			chatBar.visible = ! preLoading;
			modificator.visible = ! preLoading;
			loadingBar.visible = ! preLoading;
			statusText.visible = preLoading;
			statusFrame.visible = preLoading;
			exitBtn.visible = preLoading;
		}

		public function SetLocales(leftImage:String, leftTooltip:String, rightImage:String, rightTooltip:String ):void
		{
			flag1.visible = flag2.visible = leftImage.length != 0 && rightImage.length != 0;
			flag1.SetIcon(leftImage);
			flag2.SetIcon(rightImage);
			flag1TooltipSender.TooltipText = leftTooltip;
			flag2TooltipSender.TooltipText = rightTooltip;
			UpdateLocalisationPositions();
		}

		public function get LoaderWindowInterface():LoaderInterface
		{
			return _mainInterface;
		}

		private function ResizeStage(e:Event):void
		{
			backGround.x = (stage.stageWidth - backGround.width) / 2;
			backGround.y = (stage.stageHeight - backGround.height) / 2;
			logo.x = (stage.stageWidth - logo.width) / 2;
			logo.y = (stage.stageHeight - logo.height) / 2;
			statusText.x = (stage.stageWidth - statusText.width) / 2;
			exitBtn.x = stage.stageWidth - exitXOffset;
			exitBtn.y = stage.stageHeight - exitYOffset;
			statusText.y = (2 / 3) * stage.stageHeight;
			statusFrame.y = statusText.y - statusFrameOffsetY;
			statusFrame.x = (stage.stageWidth - statusFrame.width) / 2;

			AvMight.x = (stage.stageWidth - AvMight.width) / 2;
			UpdateLocalisationPositions();
		}

		public function UpdateLocalisationPositions():void
		{
			flag1.x = team_pnl.GetVisibleWidth();
			flag2.x = stage.stageWidth - enemyTeam_pnl.GetVisibleWidth() - flag2.width;
		}

	}
}