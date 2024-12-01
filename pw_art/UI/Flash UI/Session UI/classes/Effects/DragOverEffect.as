package Effects
{
	
	import flash.display.MovieClip;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import fl.transitions.TweenEvent;
	
	
	public class DragOverEffect extends MovieClip 
	{
		private var tweenAlpha:Tween;
		private var time:int = 10;
		
		public function DragOverEffect() 
		{
			this.stop();
			tweenAlpha = new Tween(this, 'alpha', Strong.easeOut, 0, 1, time);
			tweenAlpha.addEventListener(TweenEvent.MOTION_FINISH, tweenAlphaFinish);
			tweenAlpha.stop();
			
			this.mouseEnabled = false;
			this.visible = false;
		}
		public function Show():void
		{
			this.visible = true;
			this.play();
			tweenAlpha.stop();
			tweenAlpha.continueTo(1, time);
		}
		public function Hide():void
		{
			this.gotoAndStop(1);
			tweenAlpha.stop();
			tweenAlpha.continueTo(0, time);
		}
		private function tweenAlphaFinish(e:TweenEvent):void
		{
			if(e.target.finish == 0)
			{
				this.visible = false;
			}
		}
	}
}
