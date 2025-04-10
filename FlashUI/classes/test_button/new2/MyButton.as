package new2{
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	
	public class MyButton extends MovieClip {
		
		public function MyButton() 
		{
			stop();
			addEventListener(MouseEvent.MOUSE_OVER,OnMouseOver);
			addEventListener(MouseEvent.MOUSE_DOWN,OnMouseDown);
			addEventListener(MouseEvent.MOUSE_OUT,OnMouseOut);
			addEventListener(MouseEvent.MOUSE_UP,OnMouseUp);
			
		}
		
		protected function OnMouseOver(evt:MouseEvent):void
		{
			gotoAndStop(2);
		}
		
		protected function OnMouseDown(evt:MouseEvent) :void
		{
			gotoAndStop(3);
		}
		
		protected function OnMouseOut(evt:MouseEvent) :void
		{
			gotoAndStop(1);
		}
		
		protected function OnMouseUp(evt:MouseEvent):void
		{
			gotoAndStop(1);
		}
	}
	
}
