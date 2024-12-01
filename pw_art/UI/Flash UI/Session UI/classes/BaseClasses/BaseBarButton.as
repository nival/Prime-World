package BaseClasses
{
	import fl.transitions.easing.Strong;
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import flash.display.Sprite;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.MovieClip;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.utils.Timer;
	import Strokes.SquadStroke;
	
	import flash.net.URLRequest;
	import src.BlueColor;
	import flash.geom.Point;
	
	import Interfaces.IActionButton;
	import Interfaces.IDragSlotHightLight;
	import ActionBar.ActionBarToggle;
	import Enums.ActionBarSlotState;
	import Effects.DragOverEffect;
	import DragAndDrop.DnDController;
	import Events.MouseRightEvents;
	import Components.FormatedTimer;
	 
	public class BaseBarButton extends MovieClip implements IActionButton, IDragSlotHightLight
	{
		public var type:String;
		public var toggleButton_mc:ActionBarToggle;
		public var activSpetial_mc:MovieClip;
		public var enableState_mc:MovieClip;
		public var path:String;
		
		protected var _shortcut:BaseShortCut;
		
		protected var _iconPath:String = "";
			
		protected var cooldown:Number = 0;
		protected var maxCooldownValue:Number = 0;
		
		private var freeSlot:Boolean = true;
		protected var isActiveGlobalCooldown:Boolean = false;
		private var state:int = ActionBarSlotState.DISABLED;
		private var _count:int = -1;
		private var disable:Loader;
		private var isAnimationPlayedOnce:Boolean = false;
		
		public var itemCount_txt:TextField;
		public var coolDown_mc:FormatedTimer;
		public var coolDownEndFlash:MovieClip;
		
		private var isBlueFilterEnabled:Boolean = false;
			
		private var isDragEffectShowing:Boolean = false;
		
		protected var downPosition:Point = new Point( -10,-10);
		protected var isDown:Boolean = false;
		private var dragRadius:Number = 6;
		
		private var timerToDrug:Timer = new Timer(150,1);
		private var isTimerEnded:Boolean = false;
		
		private var tutorialHighLight:SquadStroke;
		public function BaseBarButton()
		{	 
			path = toggleButton_mc.ico_mc.path;
			type = toggleButton_mc.ico_mc.type;
							
			this.buttonMode = true;
			this.doubleClickEnabled = true;
			this.mouseChildren = false;
			
			//BlueColor.onBlue(notMana);
			itemCount_txt.visible = false;
			itemCount_txt.mouseEnabled = false;
			
			enableState_mc.stop();
			enableState_mc.visible = false;
			
			coolDown_mc.stop();
			coolDown_mc.coolDownMask_mc.stop();
			coolDown_mc.mouseEnabled = false;
			coolDown_mc.coolDownMask_mc.mouseEnabled = false;
			coolDown_mc.visible = false;
			coolDown_mc.TwoDigitalTimerFormat = true;

			activSpetial_mc.stop();
			activSpetial_mc.visible = false;
			
			coolDownEndFlash.stop();
			coolDownEndFlash.visible = false;
			
			this.addEventListener(MouseEvent.MOUSE_UP, onUp);
			this.addEventListener(MouseEvent.MOUSE_OVER, onOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, onOut);
			this.addEventListener(MouseEvent.DOUBLE_CLICK, onUp);
			this.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
			this.addEventListener(MouseEvent.MOUSE_MOVE,MouseMoveOverThis)
			this.addEventListener(MouseRightEvents.RIGHT_CLICK, onRightClick);
			
			disableState();
			timerToDrug.stop();
			timerToDrug.addEventListener(TimerEvent.TIMER_COMPLETE, OnTimerToDrugEnd);
		}
		
		public function get isFreeSlot():Boolean
		{
			return freeSlot; 
		}
		
		public function set isFreeSlot(value:Boolean):void
		{
			freeSlot = value; 
		}
		
		protected function onRightClick(e:Event):void 
		{
		}
		
		protected function onDown(e:MouseEvent):void
		{
			if (state == ActionBarSlotState.CHOSEN) return;

			toggleButton_mc.onDown();
			if (isFreeSlot) return;
			
			timerToDrug.stop();
			timerToDrug.start();
			isTimerEnded = false;
			isDown = true;
			downPosition.x = this.mouseX;
			downPosition.y = this.mouseY;
			
		}
		
		protected function onUp(e:MouseEvent):void
		{
			if (state == ActionBarSlotState.CHOSEN) return;
			
			toggleButton_mc.onUp();
			
			timerToDrug.stop();
			isDown = false;
			downPosition.x = -10;
			downPosition.y = -10;
		}
		
		protected function DragEndedOverThis():void
		{
		}
		
		private function OnTimerToDrugEnd(e:TimerEvent):void 
		{
			isTimerEnded = true;
		}
		
		private function MouseMoveOverThis(e:MouseEvent):void 
		{
			if (DnDController.isDragging||downPosition.x==-10||downPosition.y==-10) return;
			
			if (isFreeSlot)	return;
				
			var curRadius:Number = Math.sqrt(Math.abs(this.mouseX - downPosition.x) * Math.abs(this.mouseX - downPosition.x) + Math.abs(this.mouseY - downPosition.y) * Math.abs(this.mouseY - downPosition.y));
			
			if (isDown && curRadius >= dragRadius && isTimerEnded)
				StartDragThis();
		}
		
		protected function StartDragThis():void
		{
			
		}
		
		protected function onOver(e:MouseEvent):void
		{
			if (state == ActionBarSlotState.CHOSEN) return;
			
			toggleButton_mc.onOver();
		
			DnDController.HightLightingObject = this;
		}
		
		protected function onOut(e:MouseEvent):void
		{
			if (state == ActionBarSlotState.CHOSEN) return;
			
			toggleButton_mc.onOut();
		
			DnDController.ResetHightLightingObject();
			
			
			downPosition.x = -10;
			downPosition.y = -10;
			
			if (isDown && !DnDController.isDragging)
			{
				timerToDrug.stop();
				StartDragThis();
			}
			
			isDown = false;
		}
		
		public function set Shortcut(value:BaseShortCut):void
		{
			_shortcut = value;
			if (_shortcut) _shortcut.count = count;
		}
		
		public function get Shortcut():BaseShortCut
		{
			return _shortcut;
		}
		
		protected function normalState():void
		{
			if (isBlueFilterEnabled)
			{
				BlueColor.unBlue(toggleButton_mc.ico_mc);
				isBlueFilterEnabled = false;
			}
				
			activSpetial_mc.gotoAndStop(1);
			activSpetial_mc.visible = false;

			toggleButton_mc.enable();
			toggleButton_mc.ico_mc.enable();
			toggleButton_mc.ico_mc.visible = true;
			toggleButton_mc.ico_mc.ico = _iconPath;
			
			toggleButton_mc.up();
			toggleButton_mc.ico_mc.alpha = 1;
		}
		
		public function get iconPath():String
		{
			return _iconPath;
		}
		
		public function set iconPath( _path : String ):void
		{
			
			_iconPath = _path;
			
			if (_iconPath.length == 0)
			{
				toggleButton_mc.ico_mc.ico = _iconPath;
				return;
			}
			var myURLRequest:URLRequest = new URLRequest(_path);
			
			toggleButton_mc.ico_mc.ico = _path;
		}
		
		private function coolDownState(newCooldown:Number,maxCooldown:Number):void
		{
			if (newCooldown < 0.001)
				newCooldown = 0;
				
			if (newCooldown == 0)
			{ 
				cooldown = 0;
				coolDown_mc.gotoAndStop(1);
				coolDown_mc.visible = false;
				
				if (!isAnimationPlayedOnce)
				{
					coolDownEndFlash.visible = true;
					coolDownEndFlash.gotoAndPlay(1);
				}
					
				isAnimationPlayedOnce = true;	
				return;
			}
			
			isAnimationPlayedOnce = false;
			
			cooldown = newCooldown;
			maxCooldownValue = maxCooldown;
			
			var framesCount:Number = coolDown_mc.coolDownMask_mc.totalFrames;
		
			var percentProgress:Number = newCooldown/maxCooldown;
			var frameNumber:Number = (1-percentProgress) * framesCount;
			var actualFrame:Number = Math.ceil(frameNumber);
			
			var cooldownToShow:int;
			
			coolDown_mc.Time = newCooldown;
		
			coolDown_mc.clock.visible = newCooldown > 0;
			coolDown_mc.coolDownMask_mc.gotoAndStop(actualFrame);
			
			coolDown_mc.visible = true;
		}
		
		public function DontShowCoolDownEndAnimation():void
		{
			isAnimationPlayedOnce = true;
		}
		
		public function Cooldown(_cooldown:Number, maxCooldown:Number):void
		{
			if (isActiveGlobalCooldown)
				return;
				
			coolDownState(_cooldown,maxCooldown);
			return;
		}
		
		public function get CooldownValue():Number 
		{
			return cooldown;
		}
		
		public function get MaxCooldownValue():Number
		{
			return maxCooldownValue;
		}
		
		public function GlobalCoolDown(_cooldown:Number,maxCooldownValue:Number):void
		{ 
			if ( _cooldown > cooldown)
				isActiveGlobalCooldown = true;
				
			if (isActiveGlobalCooldown)
				coolDownState(_cooldown, maxCooldownValue);
				
			if (_cooldown < 0.001)
				isActiveGlobalCooldown = false;
		}
		
		public function get State():int
		{
			return state;
		}
			
		public function set State(_state:int):void
		{
			if(state == _state)
			{
				return;
			}
			
			if (state == ActionBarSlotState.DISABLED && _state == ActionBarSlotState.ACTIVE && cooldown==0)
			{
				enableState_mc.visible = true;
				enableState_mc.gotoAndPlay(1);
			}
			
			state = _state;
			
			switch (_state)
			{
				case ActionBarSlotState.ACTIVE :
					{
						normalState();
						break;

					};
				case ActionBarSlotState.ACTIVE_SPECIAL :
					{
						activeSpetialState();
						break;

					};
				case ActionBarSlotState.ACTIVETED_SPECIAL:
					{
						activetedSpetialState();
						break;

					};
				case ActionBarSlotState.NOT_ENOUGHT_MANA :
				case ActionBarSlotState.NOT_ENOUGH_LIFE :
					{
						notManaState();
						break;

					};
				case ActionBarSlotState.DISABLED :
					{
						disableState();
						break;

					};
				case ActionBarSlotState.CHOSEN :
					{
						activeSpetialState();
						downState();
						
						break;

					};
				default :
					{
				}
			}
		}
		
		public function set count(value:int):void
		{				
			_count = value;
			itemCount_txt.visible  = _count > 1;
			if (_count > 1)
			{
				itemCount_txt.text = _count.toString();
			}
		}
		
		public function get count():int 
		{
			return _count;	
		}
	
		
		private function activeSpetialState():void
		{
			normalState();
//			toggleButton_mc.disable();
			activSpetial_mc.visible = true;
			activSpetial_mc.gotoAndPlay(2);
		}

		private function activetedSpetialState():void
		{
			normalState();
		}

		private function notManaState():void
		{
			normalState();
			toggleButton_mc.disable(false);
			BlueColor.onBlue(toggleButton_mc.ico_mc);
			isBlueFilterEnabled = true;
		}
		
		protected function disableState():void
		{
			normalState();
			toggleButton_mc.disable();
			toggleButton_mc.ico_mc.visible = true;
			toggleButton_mc.ico_mc.disable();
		}
		
		protected function downState():void
		{
			toggleButton_mc.down();
			toggleButton_mc.ico_mc.alpha = 0.5;
		}
		
		public function ShowDraggingBorder(show:Boolean,draggerEffect:DragOverEffect):void 
		{	
			if(show)
			{
				this.addChild(draggerEffect);
				this.setChildIndex(draggerEffect, this.numChildren - 2);
				draggerEffect.Show();
				isDragEffectShowing = true;
				return
			}
			
			if (!isDragEffectShowing) return;
			
			draggerEffect.Hide();
			this.removeChild(draggerEffect);
			isDragEffectShowing = false;
		}
		
		public function ShowTutorialHighlight():void
		{
			if (tutorialHighLight != null)
				return;
				
			tutorialHighLight = new SquadStroke();
			this.addChildAt(tutorialHighLight, this.numChildren - 1);	
			tutorialHighLight.setSize(toggleButton_mc.width, toggleButton_mc.height);
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