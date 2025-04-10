package  new2 {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
		
	public class ButtonUpgrade extends MovieClip 
	{
		
		public var tutorialItemHighlight:MovieClip;
		public var ico:MovieClip; 
		public var buttonUpgradeCoolDown_mc:MovieClip;
		
		
		public function ButtonUpgrade() 
		{
			tutorialItemHighlight.play();
			stop();
			addEventListener(MouseEvent.MOUSE_OVER, OnMouseOver);
			addEventListener(MouseEvent.MOUSE_DOWN, OnMouseDown);
			addEventListener(MouseEvent.MOUSE_UP, OnMouseOver);
			
			addEventListener(MouseEvent.MOUSE_OUT, OnMouseOut);
			addEventListener(Event.ENTER_FRAME,OnEnterFrame);
		}
		
		private function OnMouseOver(evt:MouseEvent):void
		{
			gotoAndStop(2);
		}
		
		private function OnMouseDown(evt:MouseEvent):void
		{
			gotoAndStop(3);
			buttonUpgradeCoolDown_mc.play();
			
		}
		
		private function OnMouseOut(evt:MouseEvent):void
		{
			gotoAndStop(1);
		}
		
		private function OnEnterFrame(evt:Event):void
		{
			trace("OnEnterFrame "+tutorialItemHighlight.currentFrame);
			if(tutorialItemHighlight.currentFrame==tutorialItemHighlight.totalFrames)
			{
				tutorialItemHighlight.gotoAndStop(1);
				
				removeEventListener(Event.ENTER_FRAME,OnEnterFrame);
				trace("removeEventListener "+tutorialItemHighlight.currentFrame);
			}
		}
	}
}
