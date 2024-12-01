package MainScreen 
{
	import Enums.EFraction;
	import flash.display.Loader;
	import flash.display.Shape;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.net.URLRequest;
	import flash.text.TextField;
	import flash.utils.getDefinitionByName;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import fl.transitions.TweenEvent;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import Components.WFrame;
	import Components.Frame;
	import Components.ButtonSquare;
	import Components.ButtonStandart;
	import flash.events.Event;
	import BaseClasses.BaseDragObject;
	import Events.WindowVisibleControllerEvent;
	import Events.DetailedStatisticMateEvent;
	import Effects.AnimationBack;

	public class EndGameScreen extends BaseDragObject
	{
		public var header_txt:TextField;
		
		public var screen_mc:MovieClip;
		private var screenTween:Tween;
		private var showFinalStatistic:Function;
		public var frameSmall1_mc:Frame;
		public var buttonClose:ButtonStandart;
	
		private var showEndScreenDelay:int = 4000;
		private var icoLoader:Loader;
		public function EndGameScreen() 
		{
			
			icoLoader = new Loader();
			screen_mc.addChild(icoLoader);
			
			this.visible = false;
			
			screenTween = new Tween(screen_mc, 'alpha', Strong.easeOut, 0, 1, 15);
			screenTween.stop();
			
			buttonClose.addEventListener(MouseEvent.MOUSE_UP, CloseEndScreen);
		}
		
		private function CloseEndScreen(e:MouseEvent):void 
		{
			this.visible = false;
			
			if (showFinalStatistic != null)
				showFinalStatistic.call();
		}

		override protected function closeThisFunction(e:Event):void 
		{
			this.visible = false;
			
			if (showFinalStatistic != null)
				showFinalStatistic.call();
		}
		
		public function ShowEndScreen(screen:String, isVictory:Boolean,_showFinalStatistic:Function):void
		{
			showFinalStatistic = _showFinalStatistic;
			
			buttonClose.LocalizeText = isVictory? Localization.VictoryScreen_VictoryText:Localization.EndGameScreens_CloseBtnLabel;
			header_txt.text = isVictory? Localization.VictoryScreen_VictoryText : Localization.DefeatScreen_DefeatText;
			
			var myURLRequest:URLRequest = new URLRequest(screen);
			icoLoader.unload();
			icoLoader.load(myURLRequest);

			var timer:Timer = new Timer(showEndScreenDelay, 1);
			timer.addEventListener(TimerEvent.TIMER_COMPLETE, OnComplete);
			timer.start();
		}
		
		private function OnComplete(e:TimerEvent):void 
		{
			this.visible = true;
			screenTween.start();
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);

			this.x = stage.stageWidth/ 2;
			this.y = stage.stageHeight / 2;
			this.x = Math.floor(this.x);
			this.y = Math.floor(this.y);
		}
		
		override protected function GetThisWindowToTheTop(e:MouseEvent):void 
		{
			
		}
	}
}
