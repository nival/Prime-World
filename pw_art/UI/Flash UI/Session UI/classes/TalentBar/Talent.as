package TalentBar
{
	import Controllers.SoundController;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.display.MovieClip;
	import flash.events.TimerEvent;
	import flash.utils.Timer;

	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import fl.transitions.easing.Strong;
	import fl.transitions.easing.None
	
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.display.DisplayObject;
	
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;

	import src.SeladonColor;
	import src.Desaturate;

	import fl.transitions.TweenEvent;
	import flash.display.Bitmap;

	import Enums.ActionBarSlotState;
	import Enums.TalentUIState;
	import Components.FormatedTimer;
	import Events.MouseRightEvents;
	import BaseClasses.BaseShortCut;
	import DragAndDrop.DnDController;
	import Enums.EErrorMessageType;
	import Events.ErrorEvent;
	import DragAndDrop.TallentDragOBject;
	import flash.utils.getDefinitionByName;
	import Strokes.*;
	import flash.filters.ColorMatrixFilter;
	
	public class Talent extends MovieClip
	{
		private var TweenOverX:Tween;
		private var TweenOverY:Tween;
		private var TweenOutX:Tween;
		private var TweenOutY:Tween;

		private var TweenDownX:Tween;
		private var TweenDownY:Tween;
		private var TweenUpX:Tween;
		private var TweenUpY:Tween;

		public var path:String;
		public var altPath:String;
		public const type:String = 'talent';
		
		private var _talantState:int = ActionBarSlotState.ACTIVE;
		
		public var _index:int;
				
		private const SIZE:Number = 70;

		private var configPath:String = 'art/general/';
		private var onDown:Boolean;
		private var dragable:Boolean;
		
		public var icoState:int=TalentUIState.NOTENOUGH_DEV_POINTS;
		//unTour;
		public var column:int=0;
		public var raw:int=0;
		
		private var _shortcut:BaseShortCut;
		private var cooldown:Number = 0;
		
		private var ico_ld:Loader;
		
		private var icoFilter:ColorMatrixFilter;
		private var color_arr:Array;
		public var brightness:Number;
		private var tweenBrightness:Tween;
		
		private var _isActive:Boolean = false;
		private var disabled:Boolean = false;
		
		private var canBuyGlow_mc:CanBuyGlowEffect = null;
		
		private var isAddEffect:Boolean = true;
		
		private var canBuyIcoTweenX:Tween;
		private var canBuyIcoTweenY:Tween;
		
		//referense
		public var icoCont_mc:MovieClip;
		public var lock_bm:Shape;
		public var nafta_mc:MovieClip;
		public var clock_mc:FormatedTimer;
		public var IsClassTalent:Boolean;
		public var price:int;
		public var UpgradeLevel:int = 0;
		public var IsAlternativStateActivated:Boolean = false;
		private var nafta:DisplayObject;
		private var downPosition:Point = new Point( -10, -10);
		private var desiredIndex:int = -1;
		private var heroIsDead:Boolean;
		
		private var activeTalent_png:Bitmap;
		private var maxUpgradeLevel:int = 3;
		
		private var currentUpgradeLevelPos:Number = SIZE/2;
		private var upgradeLevels:Array = [];
		private var dragRadius:Number = 6;
		
		private var timerToDrug:Timer = new Timer(150,1);
		private var isTimerEnded:Boolean = false;
		private var tutorialHighLight:SquadStroke;
		
		public function Talent()
		{
			lock_bm = icoCont_mc.getChildAt(0) as Shape;
			lock_bm.visible = false;
			nafta_mc.visible = false;

			ico_ld = new Loader;
			icoCont_mc.addChild(ico_ld);
			icoCont_mc.setChildIndex(ico_ld, 0);
			ico_ld.contentLoaderInfo.addEventListener(Event.INIT, icoInit);

			this.addEventListener(MouseEvent.MOUSE_OVER,onOver);
			this.addEventListener(MouseEvent.MOUSE_OUT,onOut);
			this.addEventListener(MouseEvent.MOUSE_DOWN,OnDown);
			this.addEventListener(MouseEvent.MOUSE_UP, onUp);
			this.addEventListener(MouseRightEvents.MOUSE_RIGHT_UP, onUp);
			this.addEventListener(MouseRightEvents.MOUSE_RIGHT_DOWN,OnDown);
			this.addEventListener(MouseEvent.DOUBLE_CLICK, onUp);
			this.addEventListener(MouseEvent.MOUSE_MOVE, MouseMoveOverThis);
			this.mouseChildren = false;
			this.buttonMode = true;
			this.doubleClickEnabled = true;

			TweenOverX = new Tween(icoCont_mc,"scaleX",Strong.easeOut,1,1.1,5,false);
			TweenOverY = new Tween(icoCont_mc,"scaleY",Strong.easeOut,1,1.1,5,false);

			TweenOutX = new Tween(icoCont_mc,"scaleX",Strong.easeOut,1.1,1,5,false);
			TweenOutY = new Tween(icoCont_mc,"scaleY",Strong.easeOut,1.1,1,5,false);

			TweenUpX = new Tween(icoCont_mc,"scaleX",Strong.easeOut,0.9,1,7,false);
			TweenUpY = new Tween(icoCont_mc,"scaleY",Strong.easeOut,0.9,1,7,false);
			TweenDownX = new Tween(icoCont_mc,"scaleX",Strong.easeOut,1,0.9,7,false);
			TweenDownY = new Tween(icoCont_mc,"scaleY",Strong.easeOut,1,0.9,7,false);

			var naftaPosition:Point = new Point(nafta_mc.x, nafta_mc.y);
			
			nafta = ConvertFromMovieToBitmap(nafta_mc);
			nafta.x = naftaPosition.x;
			nafta.y = naftaPosition.y;
			clock_mc.TwoDigitalTimerFormat = true;
			clock_mc.visible = false;
			clock_mc.mouseEnabled = false;
			clock_mc.mouseChildren = false;
			nafta_mc = null;	
			
			TweenDownX.stop();
			TweenDownY.stop();
			TweenUpX.stop();
			TweenUpY.stop();
			lock_bm.visible = false;
			dragable = true;
			nafta.visible = false;
			
			//сделал анимацию иконки твинами потому что если сделать на стедже, то при запуске ее, визибл объекта nafta становится true, поскольку он не movieClip
			//Именно этого контейнера, потому что ico_ld центрируется в нем, если вешать на ico_ld то анимация будет от левого верхнего угла
			//canBuyIcoTweenX = new Tween(icoCont_mc, 'scaleX', Strong.easeOut, 1,1.1,20);
			//canBuyIcoTweenY = new Tween(icoCont_mc, 'scaleY', Strong.easeOut, 1,1.1,20);
			//canBuyIcoTweenX.addEventListener(TweenEvent.MOTION_FINISH, canbuyTweenFinihsh);
			//canBuyIcoTweenX.stop();
			//canBuyIcoTweenY.stop();
			brightness = 0;
			
			tweenBrightness = new Tween(this, 'brightness', None.easeNone, 0,0.4,15);
			tweenBrightness.addEventListener(TweenEvent.MOTION_CHANGE, tweenBrightnessChange);
			tweenBrightness.addEventListener(TweenEvent.MOTION_FINISH, tweenBrightnessFinish);
			tweenBrightness.stop();
			
			color_arr = [1,0,0,0,0,brightness,1,0,0,0,0,0,1,0,0,0,0,0,1,0];
			icoFilter = new ColorMatrixFilter(color_arr);
			
			timerToDrug.stop();
			timerToDrug.addEventListener(TimerEvent.TIMER_COMPLETE, OnTimerToDrugEnd);
		}
		
		private function ConvertFromMovieToBitmap(dispObject:MovieClip):DisplayObject
		{
			var bitm:DisplayObject = dispObject.getChildAt(0) as DisplayObject;
			
			this.addChildAt(bitm, this.getChildIndex(dispObject));
			this.removeChild(dispObject);
				
			return bitm;
		}

		public function set DesiredIndex(value:int):void
		{
			desiredIndex = value;
		}
		
		public function get DesiredIndex():int
		{
			return desiredIndex;
		}
		
		public function set IsActive(value:Boolean):void
		{
			_isActive = value;
			
			if(_isActive && activeTalent_png==null)
			{
				activeTalent_png = new Bitmap(new ActiveTalent_png());
				activeTalent_png.x = (SIZE - activeTalent_png.width) / 2;
				activeTalent_png.y = (SIZE - activeTalent_png.height) / 2;
				addChild(activeTalent_png);
			}
			
			if (activeTalent_png!=null)
				activeTalent_png.visible = _isActive;
		}
		public function get IsActive()
		{
			return _isActive;
		}
		
		public function set shortcut(value:BaseShortCut):void
		{
			_shortcut = value;
		}
		
		public function get shortcut():BaseShortCut
		{
			return _shortcut;
		}
		
		public function set TalantIndex(index:int):void
		{
			_index = index;
		}
		public function get TalantIndex():int
		{
			return _index;
		}
		
		public function set TalantState(value:int):void
		{
			_talantState = value;
		}
		
		public function get TalantState():int
		{
			return _talantState;
		}
		
		public function Press():void
		{	
			if (cooldown > 0)
			{
				dispatchEvent(new ErrorEvent(EErrorMessageType.ERRORMESSAGETYPE_ABILITYONCOOLDOWN));
				return;
			}
			
			if (icoState == TalentUIState.NOTENOUGH_PRIME)
			{
				dispatchEvent(new ErrorEvent(EErrorMessageType.ERRORMESSAGETYPE_NOTENOUGHPRIMETOBUY));
				return;
			}
			
			if (icoState == TalentUIState.BOUGHT)
			{
				if (TalantState == ActionBarSlotState.NOT_ENOUGHT_MANA)
				{
					dispatchEvent(new ErrorEvent(EErrorMessageType.ERRORMESSAGETYPE_NOTENOUGHMANAFORABILITY));
					return;
				}
				else if (TalantState == ActionBarSlotState.NOT_ENOUGH_LIFE)
				{
					dispatchEvent(new ErrorEvent(EErrorMessageType.ERRORMESSAGETYPE_NOTENOUGHLIFEFORABILITY));
					return;
				}
			}
			
			if (icoState == TalentUIState.BOUGHT && TalantState == ActionBarSlotState.DISABLED) 
			{
				return;
			}
			
			if(icoState == TalentUIState.CANBUY)
			{
				FSCommands.Send(FSCommands.TALENT_CLICK, column.toString() + ' ' + raw.toString());
				return;
			}
			
			if (icoState == TalentUIState.BOUGHT && !heroIsDead)
			{
				FSCommands.Send(FSCommands.TALENT_CLICK, column.toString() + ' ' + raw.toString());
				SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
			}
		
			
		}
		
		public function Cooldown(value:Number,maxCooldownValue:Number):void 
		{
			if (icoState != TalentUIState.BOUGHT) return;
			
			cooldown = value;
			
			clock_mc.Time = value;
			clock_mc.visible = value>0;
			
			if (shortcut != null)
				shortcut.Cooldown(value,maxCooldownValue);
				
			if(!disabled&&value>0)
				Desaturate.desaturate(ico_ld);
			
			if(value<=0)
				Desaturate.saturate(ico_ld);
		}
		
		private function onOver(e:MouseEvent):void
		{
			if (disabled) return;
			
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
			
			FSCommands.Send(FSCommands.TALENT_TOOLTIP,'1'+' '+column.toString()+ ' '+ raw.toString());
		}
		private function onOut(e:MouseEvent):void
		{	
			downPosition.x = -10;
			downPosition.y = -10;
			TweenUpX.stop();
			TweenUpY.stop();
			TweenDownX.stop();
			TweenDownY.stop();
			TweenOverX.stop();
			TweenOverY.stop();
			TweenOutX.start();
			TweenOutY.start();
			
			FSCommands.Send(FSCommands.TALENT_TOOLTIP, '0' + ' ' + column.toString() + ' ' + raw.toString());
			
			if (onDown && icoState == TalentUIState.BOUGHT && _isActive && !DnDController.isDragging)
			{
				StartDragThis();
				timerToDrug.stop();
			} 
			
			onDown = false;
		}
		private function OnDown(e:MouseEvent):void
		{
			if (disabled) return;
			
			timerToDrug.stop();
			timerToDrug.start();
			isTimerEnded = false;
			
			onDown = true;
			TweenUpX.stop();
			TweenUpY.stop();
			TweenDownX.start();
			TweenDownY.start();
				
			if (icoState == TalentUIState.BOUGHT&&_isActive)
			{
				downPosition.x = this.mouseX;
				downPosition.y = this.mouseY;
			}
		}
		private function onUp(e:Event):void
		{
			if (disabled) return;
			
			if (!onDown) return;
			
			onDown = false;
			
			timerToDrug.stop();
			TweenDownX.stop();
			TweenDownY.stop();
			TweenOverX.start();
			TweenOverY.start();
		
			if (!DnDController.isDragging) Press();

			downPosition.x = -10;
			downPosition.y = -10;
		}
		
				
		private function OnTimerToDrugEnd(e:TimerEvent):void 
		{
			isTimerEnded = true;
		}
		
		private function MouseMoveOverThis(e:MouseEvent):void
		{
			if (DnDController.isDragging||downPosition.x==-10||downPosition.y==-10) return;
			if (icoState != TalentUIState.BOUGHT||!_isActive)return;

			var curRadius:Number = Math.sqrt(Math.abs(this.mouseX - downPosition.x) * Math.abs(this.mouseX - downPosition.x) + Math.abs(this.mouseY - downPosition.y) * Math.abs(this.mouseY - downPosition.y));
			if (onDown && curRadius >= dragRadius && isTimerEnded)
				StartDragThis();
		}
		
		private function StartDragThis():void
		{
			DnDController.StartDrag(new TallentDragOBject(this));
		}
		
		private function ResetState():void
		{
			SeladonColor.saturate(ico_ld);
			lock_bm.visible = false;
			dragable = false;
			nafta.visible = false;
			
			if (upgradeLevels.length == 0) return;
			
			for each (var item:Bitmap in upgradeLevels) 
			{
				SeladonColor.saturate(item);
			}
		}
		
		public function setLock():void
		{
			ResetState();
			SeladonColor.seladon(ico_ld);
			lock_bm.visible = true;
			
			if (upgradeLevels.length == 0) return;
			
			for each (var item:Bitmap in upgradeLevels) 
			{
				SeladonColor.seladon(item);
			}
		}

		public function setNoNafta():void
		{
			ResetState();
			SeladonColor.seladon(ico_ld);
			nafta.visible = true;
			
			if (upgradeLevels.length == 0) return;
			
			for each (var item:Bitmap in upgradeLevels) 
			{
				SeladonColor.seladon(item);
			}
			
		}
		
		public function setNafta():void
		{
			ResetState();
			dragable = true;
		}

		public function setCanBuy():void
		{
			ResetState();
		}
		
		public function setEnable():void
		{
			ResetState();
			dragable = true;
		}
		
		public function setOnTur():void
		{
			ResetState();
			SeladonColor.seladon(ico_ld);
			//по просьбе художников
			dragable = true;
			
			if (upgradeLevels.length == 0) return;
			
			for each (var item:Bitmap in upgradeLevels) 
			{
				SeladonColor.seladon(item);
			}
		}
		
		public function set icon(_path:String):void
		{
			path = _path;

			if (path.length == 0)
			{
				ico_ld.unload();
				return;
			}

			var myURLRequest:URLRequest = new URLRequest(_path);

			ico_ld.unload();
			
			ico_ld.load(myURLRequest);
		}

		public function get icon():String
		{
			return path;
		}
		
		
		public function set altIcon(_path:String):void
		{
			altPath = _path;
		}
		
		public function get altIcon():String
		{
			return altPath;
		}
		
		private function icoInit(e:Event):void
		{
			ico_ld.x = - ico_ld.width / 2;
			ico_ld.y = - ico_ld.height / 2;
			e.target.content.smoothing = true;
		}
		
		public function ApplyCanBuyEffect():void
		{
			if (canBuyGlow_mc != null)
				return;
			
			canBuyGlow_mc = new CanBuyGlowEffect();
			canBuyGlow_mc.x = SIZE / 2;
			canBuyGlow_mc.y = SIZE / 2;
			canBuyGlow_mc.mouseEnabled = false;
			canBuyGlow_mc.mouseChildren = false;
			this.addChildAt(canBuyGlow_mc, 0);
			//canBuyIcoTweenX.start();
			//canBuyIcoTweenY.start();
			tweenBrightness.start();
			//по просьбе дизайнеров дисатурирую талант который не купили, но купить можно
			//Desaturate.desaturate(ico_ld);
		}
		
		public function RemoveCanBuyEffect():void
		{ 
			if (canBuyGlow_mc == null) return;
			
			this.removeChild(canBuyGlow_mc);
			canBuyGlow_mc = null;
			
			//canBuyIcoTweenX.stop();
			//canBuyIcoTweenY.stop();
			//canBuyIcoTweenX.rewind();
			//canBuyIcoTweenY.rewind();
			//ico_ld.scaleX = 1;
			//ico_ld.scaleY = 1;
			tweenBrightness.stop();
			tweenBrightness.rewind();
			//Desaturate.saturate(ico_ld);
			//ico_ld.transform.colorTransform = set_brightness(0);
			icoCont_mc.filters = [];
		}
		
		public function HeroIsDead(isHeroDead:Boolean):void 
		{
			heroIsDead = isHeroDead;
		}
		
		public function SetUpgradeLevel(upgradeLevel:int):void 
		{
			UpgradeLevel = upgradeLevel;
			
			var image:Class = getDefinitionByName("upgradeLevelIcon") as Class;
			
			if (upgradeLevel < 0 ||upgradeLevel > maxUpgradeLevel ) return;
			
			for (var j:int = 0; j < upgradeLevels.length; j++) 
			{
				icoCont_mc.removeChild(upgradeLevels[j]);
			}
			currentUpgradeLevelPos = SIZE / 2;
			upgradeLevels = new Array();
			
			for (var i:int = 0; i < upgradeLevel; i++) 
			{
				var bitm:Bitmap = new Bitmap(new image)
				icoCont_mc.addChild(bitm);
				bitm.x = currentUpgradeLevelPos - bitm.width;
				bitm.y = -SIZE/2;
				upgradeLevels.push(bitm);
				currentUpgradeLevelPos = bitm.x;
			}
		}
		
//		private function canbuyTweenFinihsh(e:TweenEvent):void
//		{
//			if(e.target.finish == 1.1)
//			{
//				canBuyIcoTweenX.continueTo(1,10);
//				canBuyIcoTweenX.func = Strong.easeIn;
//				canBuyIcoTweenY.continueTo(1,10);
//				canBuyIcoTweenY.func = Strong.easeIn;
//				canBuyIcoTweenX.start();
//				canBuyIcoTweenY.start();
//			}
//			else
//			{
//				canBuyIcoTweenX.continueTo(1.1,20);
//				canBuyIcoTweenX.func = Strong.easeOut;
//				canBuyIcoTweenY.continueTo(1.1,20);
//				canBuyIcoTweenY.func = Strong.easeOut;
//				canBuyIcoTweenX.start();
//				canBuyIcoTweenY.start();
//			}
//		}
		function tweenBrightnessChange(e:TweenEvent):void
		{
			color_arr = [0.6,0.46,0.46,0,-71,0.38,0.34,0.36,0.21,-48,0.57,0.54,0.44,brightness,-73,0,0,0,1,0]
			//color_arr = [0.34,0.44,0,0,0,brightness,0.61,0.23,0.06,0,0.31,0.29,0.3,0,0,0,0,0,1,0];
			icoFilter.matrix = color_arr;
			icoCont_mc.filters = [icoFilter];
		}
		function tweenBrightnessFinish(e:TweenEvent):void
		{
			tweenBrightness.yoyo();
		}
		
		public function ShowTutorialHighlight():void
		{
			if (tutorialHighLight != null)
				return;
			
			tutorialHighLight = new SquadStroke();
			
			this.addChildAt(tutorialHighLight, this.numChildren - 1);
			tutorialHighLight.setSize(SIZE, SIZE);
			
			
			tutorialHighLight.x = (SIZE - tutorialHighLight.width) / 2;
			tutorialHighLight.y = (SIZE - tutorialHighLight.height) / 2;

		}

		
		public function HideTutorialHighlight():void
		{
			if (tutorialHighLight == null)
				return;
				
			this.removeChild(tutorialHighLight);	
			tutorialHighLight = null;
		}
	}
}