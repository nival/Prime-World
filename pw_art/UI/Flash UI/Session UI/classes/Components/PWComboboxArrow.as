package Components {
	
	import flash.display.MovieClip;
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import fl.transitions.easing.Strong;
	
	import flash.events.MouseEvent
	
	public class PWComboboxArrow extends MovieClip 
	{
		public var up_mc:MovieClip;
		public var over_mc:MovieClip;
		public var down_mc:MovieClip;
		public var disable_mc:MovieClip;
		private var	tweenOut:Tween;
		private var	tweenIn:Tween;
		
		private var isOver:Boolean =  false;
		public var onDown:Boolean =false;
		private var Time:Number = 10;

		public function PWComboboxArrow() 
		{
			over_mc.visible = false;
			down_mc.visible = false;
			disable_mc.visible = false;
			
			tweenIn = new Tween(this,"alpha",Strong.easeOut,0,1,Time,false);
			tweenIn.addEventListener(TweenEvent.MOTION_FINISH, tweenInFinish);
			tweenOut = new Tween(this,"alpha",Strong.easeOut,1,0,Time * 2,false);
			tweenOut.addEventListener(TweenEvent.MOTION_FINISH, tweenOutFinish);
			
			tweenIn.stop();
			tweenOut.stop();
			
			this.mouseChildren = false;
		}
		public function OnOver(e:MouseEvent):void
		{
			isOver = true;
			
			if (!onDown)
			{
				over_mc.visible = true;
				
				StartInAnimation(over_mc);
			}
			if(onDown)
			{
				OnDown(null);
			}
		}
		public function OnOut(e:MouseEvent):void
		{
			isOver = false;
			
			if (!onDown)
			{
				over_mc.visible = true;
				StartOutAnimation(over_mc)
			}
			else
			{
				over_mc.visible = false;
				StartInAnimation(over_mc)
				StartOutAnimation(down_mc);
			}
		}
		public function OnDown(e:MouseEvent):void
		{
			onDown = true;
			over_mc.visible = false;
			down_mc.visible = true;
			StartInAnimation(down_mc)
		}
		public function OnUp(e:MouseEvent):void
		{
			if (!onDown) return;
			
			onDown = false;
			
			over_mc.visible = true;
			down_mc.visible = false;
			StartOutAnimation(down_mc);
			StartInAnimation(over_mc)			
		}		
		private function tweenOutFinish(e:TweenEvent):void
		{
			e.target.obj.visible = false;
		}
		private function tweenInFinish(e:TweenEvent):void
		{
			if(e.target.obj == down_mc)
			{
				over_mc.visible = false;
			}
		}
		
		private function StartInAnimation(obj:Object):void
		{
			if (obj == null) return;
			
			tweenOut.obj = obj;
			tweenOut.stop();
			
			tweenIn.obj = obj;
			tweenIn.start();
		}
		
		private function StartOutAnimation(obj:Object):void
		{
			if (obj == null) return;
			
			tweenIn.obj = obj;
			tweenIn.stop();
			
			tweenOut.obj = obj;
			tweenOut.start();
		}
	}
}
