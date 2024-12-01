package  ActionBar
{
	import Controllers.SoundController;
	import Enums.TalentUIState;
	import flash.display.MovieClip;
	import flash.display.Bitmap;
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import fl.transitions.easing.Strong;
	import fl.transitions.easing.None
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import TalentBar.Talent;
	
	import flash.filters.ColorMatrixFilter;
	
	import flash.events.MouseEvent;
	
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	
	import Events.MouseRightEvents;
	import flash.utils.getDefinitionByName;
	
	public class ImpulsTalentIco extends MovieClip 
	{
		private var TweenOverX:Tween;
		private var TweenOverY:Tween;
		private var TweenOutX:Tween;
		private var TweenOutY:Tween;

		private var TweenDownX:Tween;
		private var TweenDownY:Tween;
		private var TweenUpX:Tween;
		private var TweenUpY:Tween;
		
		private var tweenBrightness:Tween;
		public var brightness:Number;
		
		
		
		private var onDown:Boolean;
		
		private var ico_ld:Loader;
		public var path:String;
		
		private var icoFilter:ColorMatrixFilter;
		private var color_arr:Array;
		
		private var _isActive:Boolean = false;
		private var disabled:Boolean = false;
		
		private var activeTalent_png:Bitmap;

		private var currentTalent:Talent;
		private var isOver:Boolean;
		private var waitingTalent:Talent;
		
		private var myTimer:Timer;
		private var timeOut:Timer;
		
		private var timeOutDuration:int=1500;
		private var canChangeTalents:Boolean;
		
		public var isShowing:Boolean;
		
		private var soundTimer:Timer = new Timer(200, 1);
		
		private var maxUpgradeLevel:int = 3;
		private var SIZE:Number = 70;
		private var currentUpgradeLevelPos:Number = SIZE/2;
		private var upgradeLevels:Array = [];
		private var loaderContainer:MovieClip
		
		private var showingTimeOutTimer:Timer;
		private var timeOutShowing:Number = 5;
		
		public function ImpulsTalentIco() 
		{
			loaderContainer = new MovieClip();
			addChild(loaderContainer);
			
			ico_ld = new Loader;
			loaderContainer.addChild(ico_ld);
			
			this.addEventListener(MouseEvent.MOUSE_OVER,onOver);
			this.addEventListener(MouseEvent.MOUSE_OUT,onOut);
			this.addEventListener(MouseEvent.MOUSE_DOWN,OnDown);
			this.addEventListener(MouseEvent.CLICK, onUp);
			this.addEventListener(MouseRightEvents.MOUSE_RIGHT_UP, onUp);
			this.addEventListener(MouseRightEvents.MOUSE_RIGHT_DOWN,OnDown);
			this.addEventListener(MouseEvent.DOUBLE_CLICK, onUp);
			
			this.mouseChildren = false;
			this.buttonMode = true;
			this.doubleClickEnabled = true;
			
			TweenOverX = new Tween(loaderContainer,"scaleX",Strong.easeOut,1,1.1,5,false);
			TweenOverY = new Tween(loaderContainer,"scaleY",Strong.easeOut,1,1.1,5,false);

			TweenOutX = new Tween(loaderContainer,"scaleX",Strong.easeOut,1.1,1,5,false);
			TweenOutY = new Tween(loaderContainer,"scaleY",Strong.easeOut,1.1,1,5,false);

			TweenUpX = new Tween(loaderContainer,"scaleX",Strong.easeOut,0.9,1,7,false);
			TweenUpY = new Tween(loaderContainer,"scaleY",Strong.easeOut,0.9,1,7,false);
			TweenDownX = new Tween(loaderContainer,"scaleX",Strong.easeOut,1,0.9,7,false);
			TweenDownY = new Tween(loaderContainer,"scaleY",Strong.easeOut,1,0.9,7,false);
			
			TweenDownX.stop();
			TweenDownY.stop();
			TweenUpX.stop();
			TweenUpY.stop();
			
			brightness = 0;
			
			tweenBrightness = new Tween(this, 'brightness', None.easeNone, 0,0.4,15);
			tweenBrightness.addEventListener(TweenEvent.MOTION_CHANGE, tweenBrightnessChange);
			tweenBrightness.addEventListener(TweenEvent.MOTION_FINISH, tweenBrightnessFinish);
			tweenBrightness.stop();
			
			color_arr = [1,0,0,0,0,brightness,1,0,0,0,0,0,1,0,0,0,0,0,1,0];
			icoFilter = new ColorMatrixFilter(color_arr);
			
			timeOut = new Timer(timeOutDuration, 1);
			timeOut.addEventListener(TimerEvent.TIMER_COMPLETE,timeOutEnd);
			
			myTimer = new Timer(200, 1);  // ГОВНО-КОД, но иначе никак=( средствами флеша проблему с поднятием уровней не решить...
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, EndTimer);
			
			soundTimer.addEventListener(TimerEvent.TIMER_COMPLETE, PlaySound)
					
			var image:Class = getDefinitionByName("upgradeLevelIcon") as Class;
			
			for (var i:int = 0; i < maxUpgradeLevel; i++) 
			{
				var bitm:Bitmap = new Bitmap(new image)
				loaderContainer.addChild(bitm);
				bitm.x = currentUpgradeLevelPos - bitm.width;
				bitm.y = -SIZE/2;
				upgradeLevels.push(bitm);
				currentUpgradeLevelPos = bitm.x;
				bitm.visible = false;
			}
		}
		

		private function timeOutEnd(e:TimerEvent):void 
		{
			isOver = false;
			
			if (waitingTalent != null)
			{
				ShowImpulseTalent(waitingTalent);
			}
		}
		
		private function EndTimer(e:TimerEvent):void 
		{
			canChangeTalents = false;
		}
		
		public function StartShowingImpulseTimer(talent:Talent):void
		{
			if(showingTimeOutTimer!=null)
				showingTimeOutTimer.stop();
				
			showingTimeOutTimer = new Timer(timeOutShowing, 1);
			showingTimeOutTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnTimerComplete);
			showingTimeOutTimer.start();
			
			function OnTimerComplete(e:TimerEvent):void 
			{
				ShowImpulseTalent(talent);
			}
		}
		
		
		private function ShowImpulseTalent(talent:Talent):void 
		{
			if (talent == null)
			{
				if (currentTalent!=null)
					FSCommands.Send(FSCommands.TALENT_TOOLTIP, '0' + ' ' + currentTalent.column.toString() + ' ' + currentTalent.raw.toString());

				currentTalent = null;
				waitingTalent = null;
				return;
			}
			
			if (isOver && currentTalent!=null && !canChangeTalents && currentTalent.icoState == TalentUIState.CANBUY)
			{
				waitingTalent = talent;
				return;
			}
			
			if (talent != null && currentTalent != talent && isShowing)
				soundTimer.start();
			
			mouseEnabled = true;
			currentTalent = talent;
			waitingTalent = null;
			icon = currentTalent.icon;
			
			for (var i:int = 0; i < upgradeLevels.length; i++) 
			{
				upgradeLevels[i].visible = (talent.UpgradeLevel - 1) >= i;
			}
			
			
			this.visible = true;
			
			if (isOver && currentTalent!=null)
				FSCommands.Send(FSCommands.TALENT_TOOLTIP, '1' + ' ' + currentTalent.column.toString() + ' ' + currentTalent.raw.toString());
		}
	
		private function PlaySound(e:TimerEvent):void 
		{
			if (currentTalent == null) return;
			
			SoundController.PlaySound(SoundController.NEW_LEVEL);
		}
		
		
		private function onOver(e:MouseEvent):void
		{
			if (disabled) return;
			
			isOver = true;
			
			timeOut.stop();
			
			if (! onDown)
			{
				TweenOutX.stop();
				TweenOutY.stop();
				TweenOverX.start();
				TweenOverY.start();
			}
			else
			{
				TweenUpX.stop();
				TweenUpY.stop();
				TweenDownX.start();
				TweenDownY.start();
			}
			
			if (currentTalent!=null && currentTalent.icoState == TalentUIState.CANBUY)
				FSCommands.Send(FSCommands.TALENT_TOOLTIP,'1'+' '+currentTalent.column.toString()+ ' '+ currentTalent.raw.toString());
		}
		
		private function onOut(e:MouseEvent):void
		{	
			if (disabled) return;
			
			isOver = false;
			timeOut.start();
			
			onDown = false;
			TweenUpX.stop();
			TweenUpY.stop();
			TweenDownX.stop();
			TweenDownY.stop();
			TweenOverX.stop();
			TweenOverY.stop();
			TweenOutX.start();
			TweenOutY.start();
			if (currentTalent!=null)
				FSCommands.Send(FSCommands.TALENT_TOOLTIP, '0' + ' ' + currentTalent.column.toString() + ' ' + currentTalent.raw.toString());
		}
		
		private function OnDown(e:MouseEvent):void
		{
			if (disabled||canChangeTalents) return;
			
			onDown = true;
			TweenUpX.stop();
			TweenUpY.stop();
			TweenDownX.start();
			TweenDownY.start();
		}
		private function onUp(e:Event):void
		{
			if (disabled) return;
			
			if (!onDown) return;
			
			TweenDownX.stop();
			TweenDownY.stop();
			TweenOverX.start();
			TweenOverY.start();
			
			tweenBrightness.stop();
			tweenBrightness.rewind();
			ico_ld.filters = [];
			
			for (var j:int = 0; j < upgradeLevels.length; j++) 
			{
				upgradeLevels[j].filters = [];
			}
			
			onDown = false;
			
			if (currentTalent != null && !canChangeTalents && currentTalent.icoState == TalentUIState.CANBUY)
			{
				FSCommands.Send(FSCommands.TALENT_CLICK, currentTalent.column.toString() + ' ' + currentTalent.raw.toString());
				mouseEnabled = false;
			}
			
			canChangeTalents = true;
			myTimer.start();
			
		}		
		public function set icon(_path:String):void
		{
			path = _path;

			if (path.length == 0)
			{
				ico_ld.unload();
				for (var k:int = 0; k < upgradeLevels.length; k++) 
				{
					this.removeChild(upgradeLevels[k]);
				}
				return;
			}

			var myURLRequest:URLRequest = new URLRequest(_path);

			ico_ld.unload();
			ico_ld.contentLoaderInfo.addEventListener(Event.INIT,icoInit);
			ico_ld.load(myURLRequest);
			
			tweenBrightness.start();
		}
		private function icoInit(e:Event):void
		{
			e.target.content.x = - e.target.content.width / 2;
			e.target.content.y = - e.target.content.height / 2;
			e.target.content.smoothing = true;
		}

		public function get icon():String
		{
			return path;
		}
		
		function tweenBrightnessChange(e:TweenEvent):void
		{
			color_arr = [0.6,0.46,0.46,0,-71,0.38,0.34,0.36,0.21,-48,0.57,0.54,0.44,brightness,-73,0,0,0,1,0]
			icoFilter.matrix = color_arr;
			ico_ld.filters = [icoFilter];
			
			for (var j:int = 0; j < upgradeLevels.length; j++) 
			{
				upgradeLevels[j].filters = [icoFilter];
			}
		}
		
		function tweenBrightnessFinish(e:TweenEvent):void
		{
			tweenBrightness.yoyo();
		}
		
		public function set IsActive(value:Boolean):void
		{
			_isActive = value;
			
			if(_isActive)
			{
				activeTalent_png = new Bitmap(new ActiveTalent_png());
				activeTalent_png.x =- activeTalent_png.width / 2;
				activeTalent_png.y =- activeTalent_png.height / 2;
				addChild(activeTalent_png);
			}
			
			if (!_isActive&&activeTalent_png!=null)
			{
				removeChild(activeTalent_png);
				activeTalent_png = null;
			}
		}
		public function get IsActive()
		{
			return _isActive;
		}
	}
}
