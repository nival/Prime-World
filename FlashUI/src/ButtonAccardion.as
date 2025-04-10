package  {
	
	import flash.display.MovieClip;
	
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import fl.transitions.TweenEvent;
	
	
	public class ButtonAccardion extends PWButton
	{
		
		private var tweenAccordionB:Tween;
		private var time:int = 10;
		public var frame_mc:PWFrame;
		
		private var Open:Boolean = false;
				
		private var frameHeight:int = 28;
		private var frameHeightArea:int = 28;
		
		public function ButtonAccardion() 
		{			
			tweenAccordionB = new Tween(this, 'frameHeightArea', Strong.easeInOut, frameHeight, frameHeight, time);
			tweenAccordionB.addEventListener(TweenEvent.MOTION_CHANGE, onChange);
			tweenAccordionB.stop();
		}
		public function setArea(Height:int):void
		{			
			if(!Open)
			{
				tweenAccordionB.stop();
				tweenAccordionB.continueTo(Height + frameHeight, time);
			}
			else
			{
				tweenAccordionB.stop();
				tweenAccordionB.continueTo(frameHeight, time);
			}
			Open =!Open;
		}
		private function onChange(e:TweenEvent):void
		{
			frame_mc.setSize(frame_mc.width, Math.round(e.position));
		}
	}
}
