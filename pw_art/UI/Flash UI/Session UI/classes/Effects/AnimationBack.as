package Effects
{
	
	import flash.display.MovieClip;
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import fl.transitions.easing.Strong;
	
	public class AnimationBack extends MovieClip 
	{
		private var backTween:Tween;
		
		public function AnimationBack() 
		{
			this.visible = false;
			backTween = new Tween(this, 'alpha', Strong.easeOut, 0, 1, 20);
			backTween.addEventListener(TweenEvent.MOTION_FINISH, backTweenFinish);
			backTween.stop();
		}
		public function onOver():void
		{
			this.visible = true;
			backTween.stop();
			backTween.continueTo(1, 15);
			backTween.start();
		}
		public function onOut():void
		{
			backTween.stop();
			backTween.continueTo(0, 20);
			backTween.start();
		}
		public function backTweenFinish (e:TweenEvent):void
		{
			if(e.target.finish == 0)
			{
				this.visible = false;
			}
		}
	}
}
