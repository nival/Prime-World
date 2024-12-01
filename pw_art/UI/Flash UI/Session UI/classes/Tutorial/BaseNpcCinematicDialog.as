package Tutorial 
{
	import BaseClasses.BaseResizableObject;
	import fl.transitions.easing.Strong;
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import flash.display.MovieClip;
	import flash.events.Event;

	public class BaseNpcCinematicDialog extends BaseResizableObject
	{
		public var NPCLine_mc:MovieClip;
		private var duration:int = 25;
		private var isShowing:Boolean;
		
		protected var fadeTween:Tween;
		protected var alphaTween:Tween;
		protected var startDialogYPosition:Number = 0;
		protected var endDialogYPosition:Number = 0;
		
		public function BaseNpcCinematicDialog()
		{
			this.visible = false;
			
			fadeTween = new Tween(this,"y",Strong.easeInOut,0,this.height,duration);
			alphaTween = new Tween(this, "alpha", Strong.easeIn, 0, 1, duration);
			fadeTween.stop();
			alphaTween.stop();
			fadeTween.addEventListener(TweenEvent.MOTION_FINISH, FadeFinished);
		}
		
		private function FadeFinished(e:TweenEvent):void 
		{
			this.visible = this.y != startDialogYPosition;
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			this.x = 0;
			if (scale>1)
				NPCLine_mc.width = stage.stageWidth * scale;
			else
				NPCLine_mc.width = stage.stageWidth / scale;
				
			this.y = isShowing? endDialogYPosition: startDialogYPosition;
		}

		override public function ShowCinematicDialog():void 
		{
			this.visible = true;
			isShowing = true;
			fadeTween.stop();
			alphaTween.stop();
			fadeTween.begin = this.y;
			fadeTween.finish = endDialogYPosition;
			alphaTween.begin = this.alpha;
			alphaTween.finish = 1;
			
			fadeTween.start();
			alphaTween.start();
		}
		
		override public function HideCinematicDialog():void 
		{
			this.visible = true;
			isShowing = false;
			fadeTween.stop();
			alphaTween.stop();
			
			fadeTween.begin = this.y;
			fadeTween.finish = startDialogYPosition;
			
			alphaTween.begin = 1;
			alphaTween.finish = 0;
			
			fadeTween.start();
			alphaTween.start();
		}
		
	}

}