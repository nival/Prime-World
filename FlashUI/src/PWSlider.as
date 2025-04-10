package  {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.geom.Rectangle;
	
	public class PWSlider extends MovieClip 
	{
		var rectangle:Rectangle;
		
		public function PWSlider() 
		{
			getChildAt(1).alpha = 0;
			rectangle = new Rectangle(0,0,back.width,0);
			
			slider_btn.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
			slider_btn.addEventListener(MouseEvent.MOUSE_UP, onUp);
			slider_btn.addEventListener(MouseEvent.MOUSE_OUT, onUp);
			back.body_mc.width = 1;
		}
		private function onDown(e:MouseEvent):void
		{
			slider_btn.startDrag(false, rectangle);
			slider_btn.addEventListener(MouseEvent.MOUSE_MOVE, onMove);
		}
		private function onUp(e:MouseEvent):void
		{
			slider_btn.stopDrag();
			slider_btn.removeEventListener(MouseEvent.MOUSE_MOVE, onMove);
			back.body_mc.width = slider_btn.x;
		}
		private function onMove(e:MouseEvent):void
		{
			back.body_mc.width = slider_btn.x;
		}
	}
}
