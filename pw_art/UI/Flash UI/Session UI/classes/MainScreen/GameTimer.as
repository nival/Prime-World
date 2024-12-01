package MainScreen 
{
	import Components.FormatedTimer;
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Rectangle;
	
	public class GameTimer extends MovieClip 
	{	
		// TODO: ?
		public var __exportedProperties:Array = ['TimerTooltip'];
		
		public var timer_mc:FormatedTimer;
		
		private var timer_collider:Shape;
		
		public function GameTimer() 
		{
			super();
			
			timer_mc.mouseEnabled = false;
			
			timer_collider = new Shape();
			
			timer_collider.graphics.beginFill(0x000000, 0);
			timer_collider.graphics.drawRect(0, 0, Math.ceil(timer_mc.width), Math.ceil(timer_mc.height));
			timer_collider.graphics.endFill();
			
			addChild(timer_collider);
			
			timer_collider.x = timer_mc.x;
			timer_collider.y = timer_mc.y;
			
			function onAddedToStage(e:Event):void
			{
				timer_collider.addEventListener(MouseEvent.MOUSE_OVER, OnTimerOver);
				timer_collider.addEventListener(MouseEvent.MOUSE_OUT, OnTimerOut);
			}
			
			function onRemovedFromStage(e:Event):void
			{
				timer_collider.removeEventListener(MouseEvent.MOUSE_OVER, OnTimerOver);
				timer_collider.removeEventListener(MouseEvent.MOUSE_OUT, OnTimerOut);
			}
			
			addEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
			addEventListener(Event.REMOVED_FROM_STAGE, onRemovedFromStage);
			
			TimerTooltip = Localization.Tooltip_MinimapTimer;
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, OnLocalizationComplete);
		}
		
		private function OnLocalizationComplete(e:Event):void
		{
			TimerTooltip = Localization.Tooltip_MinimapTimer;
		}
		
		private function OnTimerOver(e:MouseEvent):void
		{
			timer_mc.onOver();
		}
		
		private function OnTimerOut(e:MouseEvent):void
		{
			timer_mc.onOut();
		}
		
		public function set TimerTooltip(value:String):void
		{
			timer_mc.Tooltip = value;
		}
		
		public function get TimerTooltip():String
		{
			return timer_mc.Tooltip;
		}
		
		public function set GameTime(value:int):void
		{
			timer_mc.Time = value;
		}
	}
}
