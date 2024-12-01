package MainScreen
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import fl.transitions.easing.Strong;
	
	import flash.utils.setInterval;
	
	import flash.media.Sound;
	import BaseClasses.BaseResizableObject;
	import Controllers.DelayedAnimation;
	
	
	public class ImpulsShop extends BaseResizableObject
	{		
		private var TweenXOut:Tween;
		private var TweenYOut:Tween;
		
		private var feathersOutTween:Tween;
		
		private var tooltipOn:Boolean = false;
		
		//reference
		public var box_mc:MovieClip;
		public var feathers_mc:MovieClip;
			
		private const OPENING : String = "opening";
		private const LOOPING : String = "inLoop";
		private const HIDING  : String = "hiding";
		private const NOT_VISIBLE : String = "notvisible";
		
		private var currentState : String = NOT_VISIBLE;
		
		private var menuOpen_snd:Sound;
		private var DelayedAnim:DelayedAnimation = new DelayedAnimation(this);
		
		public function ImpulsShop()
		{	
			this.stop();
			this.mouseEnabled = false;
			feathers_mc.mouseEnabled = false;
			feathers_mc.mouseChildren = false;
			box_mc.boxBody_mc.ico_mc.mouseEnabled = false;
			
			TweenXOut = new Tween(box_mc.boxBody_mc.ico_mc.icoCont_sp,"scaleX",Strong.easeOut,1,0.9,7,false);
			TweenYOut = new Tween(box_mc.boxBody_mc.ico_mc.icoCont_sp,"scaleY",Strong.easeOut,1,0.9,7,false);
			TweenYOut.addEventListener(TweenEvent.MOTION_FINISH, TweenYOutFinish);
			
			feathersOutTween = new Tween(feathers_mc, 'alpha', Strong.easeOut, 1, 0, 20, false);
			feathersOutTween.stop();
			
			TweenXOut.stop();
			TweenYOut.stop();
			
			box_mc.closeButton_mc.addEventListener("Up",buttonClose);
			box_mc.boxBody_mc.ico_mc.addEventListener("Up",icoDown);
			box_mc.boxBody_mc.ico_mc.addEventListener(MouseEvent.MOUSE_OVER,icoOver);
			box_mc.boxBody_mc.ico_mc.addEventListener(MouseEvent.MOUSE_OUT,icoOut);
			
			box_mc.mouseEnabled = false;
			box_mc.boxBody_mc.mouseEnabled = false;
			box_mc.closeButton_mc.mouseEnabled = false;
			
			box_mc.boxBody_mc.ico_mc.disable = true;
			
			feathers_mc.stop();
			feathers_mc.impulsDusts_mc.stop();
			feathers_mc.visible = false;
			menuOpen_snd = new menu_open();
			this.visible = false;
		}
		
		public function StartAnimation(path:String):void
		{			
			this.gotoAndPlay(1);
			box_mc.gotoAndStop(1);
			box_mc.boxBody_mc.gotoAndStop(1);	
			
			
			currentState = OPENING;
			this.visible = true;
			
			box_mc.boxBody_mc.ico_mc.icons = path;
			box_mc.boxBody_mc.ico_mc.disable = false;
			box_mc.closeButton_mc.mouseEnabled = true;
			box_mc.mouseEnabled = true;
			this.gotoAndPlay(1);
			
			
			feathers_mc.visible = true;
			feathers_mc.play();
			feathers_mc.impulsDusts_mc.play();
				
			feathersOutTween.stop();
			feathersOutTween.rewind();
		}
		
		public function ShowImpulsBuff(path:String):void
		{	
			if (currentState == OPENING || currentState == LOOPING)
			{
				return;
			}
			
			if (currentState == HIDING)
			{
				DelayedAnim.setShowAnimation(StartAnimation, path);
				return;
			}
			
			StartAnimation(path);
		}
		
		override protected function BaseBarObjectResize(e:Event=null):void
		{	
			super.BaseBarObjectResize();
			
			this.x = (stage.stageWidth - this.width) / 2;
			this.x = Math.floor(this.x);
		}	

		public function HideImpulseBuff(wasBought:Boolean, fromKeyboard:Boolean)
		{
			if (currentState == HIDING || currentState == NOT_VISIBLE) 
			{
				return;
			}
			
			if (currentState==OPENING) 
			{
				DelayedAnim.setCloseAnimation(StartHideAnimation, wasBought, fromKeyboard);
				return;
			}
			
			StartHideAnimation(wasBought, fromKeyboard);
		
		}
		
		public function StartHideAnimation(wasBought:Boolean, fromKeyboard:Boolean):void
		{
			currentState = HIDING;
				
			if (wasBought)
			{
				if (fromKeyboard)
				{
					TweenXOut.start();
					TweenYOut.start();
				}
				else
				{
					StartBuyAnimation();
				}
			}
			else
			{
				StartCloseAnimation();
			}
				
			box_mc.boxBody_mc.ico_mc.disable = true;
			box_mc.closeButton_mc.mouseEnabled = false;
			box_mc.mouseEnabled = false;
		
			feathers_mc.impulsDusts_mc.gotoAndStop(2);
			feathers_mc.visible = false;
		
			feathersOutTween.stop();
			feathersOutTween.finish = 0;
			feathersOutTween.start();
		}
		
		public function OnAppearanceEnded():void
		{
			currentState = LOOPING;
			//box_mc.boxBody_mc.gotoAndPlay(2);
			box_mc.boxBody_mc.gotoAndStop(2);
			
			if (DelayedAnim.HasAnimation) 
				DelayedAnim.PlayAnimation();
		}
		
		public function AnimationFinished():void
		{
			currentState = NOT_VISIBLE;
			this.stop();
			this.visible = false;
			
			if (DelayedAnim.HasAnimation) 
				DelayedAnim.PlayAnimation();
		}
		
		public function ResetImpulsBuffIcon(path:String):void 
		{
			box_mc.boxBody_mc.ico_mc.icons = path;
			box_mc.boxBody_mc.ico_mc.disable = false;
			//анимация смены иконки
			box_mc.boxBody_mc.gotoAndPlay(2);
		}
		
		private function TweenYOutFinish(e:TweenEvent):void
		{
			TweenXOut.rewind();
			TweenYOut.rewind();

			StartBuyAnimation();
		}		
		
		private function buttonClose(e:Event):void
		{
			e.stopPropagation();
			FSCommands.Send(FSCommands.IMPULSBUFF_CLOSE);
			
			if (tooltipOn)
			{
				FSCommands.Send(FSCommands.IMPULSBUFF_TOOLTIP,'0')					
			};
			HideImpulseBuff(false, false);
			
		}
		private function icoOver(e:Event):void
		{
			FSCommands.Send(FSCommands.IMPULSBUFF_TOOLTIP, '1');
			tooltipOn = true;
		}
		private function icoOut(e:Event):void
		{
			tooltipOn = false;
			FSCommands.Send(FSCommands.IMPULSBUFF_TOOLTIP,'0');
		}
		private function icoDown(e:Event):void
		{
			e.stopPropagation();
			FSCommands.Send(FSCommands.IMPULSBUFF_BUY);
			
			if (tooltipOn)
				FSCommands.Send(FSCommands.IMPULSBUFF_TOOLTIP,'0');
		}
		
		private function StartCloseAnimation():void
		{
			gotoAndPlay("close");
		}
		
		private function StartBuyAnimation():void
		{
			menuOpen_snd.play();
			gotoAndPlay("buy");
		}
	}
};