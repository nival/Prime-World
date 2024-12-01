package Strokes 
{
	import ActionBar.ActionBar;
	import fl.transitions.easing.Strong;
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import flash.events.Event;
	import Components.PWFrame;
	public class Stroke  extends PWFrame
	{
		var tweenStrokeAlpha:Tween

		public function Stroke()
		{
			this.mouseEnabled = false;
			this.addEventListener(Event.ADDED_TO_STAGE,OnAddedToStage)
		}
		
		private function OnAddedToStage(e:Event):void 
		{
			trace("onAdded");
			removeEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
			tweenStrokeAlpha = new Tween(this, 'alpha', Strong.easeInOut, 0, 1, tutorialTweenDuration);
			tweenStrokeAlpha.addEventListener(TweenEvent.MOTION_FINISH, onTweenFinish);
			tweenStrokeAlpha.start();
		}
		
		private function onTweenFinish(e:TweenEvent):void 
		{
			e.target.yoyo();
		}
		
		//время анимации
		protected function get tutorialTweenDuration():Number
		{
			return 20;
		}
	}
}

