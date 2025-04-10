package  {
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.EventDispatcher;
	import flash.events.Event;
	
	public class ToggleButton extends MovieClip
	{
		private var isToggled:Boolean = false;			
		private var hit_mc:MovieClip;
		private var hit_test:MovieClip;
		
		public function ToggleButton()
		{
			this.stop();
			if (hit_test == null)
				setTB(this);
			else
				setTB(hit_test);
		}
		
		private function setTB(hitTest_mc:MovieClip)
		{
			hitTest_mc.mouseChildren = false;
			hitTest_mc.buttonMode = true;
			hitTest_mc.addEventListener(MouseEvent.MOUSE_OVER, OnMouseOver);
			hitTest_mc.addEventListener(MouseEvent.MOUSE_OUT, OnMouseOut);
			hitTest_mc.addEventListener(MouseEvent.MOUSE_DOWN, OnMouseDown);
			hitTest_mc.addEventListener(MouseEvent.MOUSE_UP, OnMouseUp);
		}		
		
		protected function OnMouseOver(evt:MouseEvent):void
		{
			if(!isToggled)
				gotoAndStop(2);
			else
				gotoAndStop(6);
			
		}
		
		protected function OnMouseDown(evt:MouseEvent) :void
		{	
			if(!isToggled)
				gotoAndStop(3);
			else
				gotoAndStop(7);
		}
		
		protected function OnMouseOut(evt:MouseEvent) :void
		{
			if(!isToggled)
				gotoAndStop(1);
			else
				gotoAndStop(5);
		}
		
		protected function OnMouseUp(evt:MouseEvent):void
		{
			if(!isToggled)
			{
				gotoAndStop(6);
			}
			else
			{
				this.gotoAndStop(2);
			}
			
			isToggled=!isToggled;
			if (isToggled)
				trace ("ON");
			else 
				trace ("OFF");
		}
	}	
}
