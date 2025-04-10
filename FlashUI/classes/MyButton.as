package 
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.EventDispatcher;
	import flash.events.Event;
	
	public class MyButton extends MovieClip 
	{
		public function MyButton()
		{
			this.stop();
			setButton(this);
		}
		
		private function setButton(hitTest_mc:MovieClip)
		{
			hitTest_mc.mouseChildren = false;
			hitTest_mc.buttonMode = true;
			hitTest_mc.addEventListener(MouseEvent.MOUSE_OVER, onOver);
			hitTest_mc.addEventListener(MouseEvent.MOUSE_OUT, onOut);
			hitTest_mc.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
			hitTest_mc.addEventListener(MouseEvent.MOUSE_UP, onUp);
		}		

		private function onOver(e:MouseEvent):void
		{
			this.gotoAndStop(2);
		}
		private function onOut(e:MouseEvent):void
		{
			this.gotoAndStop(1);
		}
		private function onDown(e:MouseEvent):void
		{
			this.gotoAndStop(3);
		}
		private function onUp(e:MouseEvent):void
		{
			this.gotoAndStop(2);
		}
	
	}
}