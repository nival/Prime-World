package  {
	
	import flash.display.MovieClip;
	import flash.display.Bitmap;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	
	
	public class PWComboBoxButton extends PWFrame 
	{
		private var opened:Boolean = false;
		
		public function PWComboBoxButton() 
		{
			this.stop();
			arrow_mc.stop();
			addEventListener(MouseEvent.MOUSE_OVER, onOver);
			addEventListener(MouseEvent.MOUSE_OUT, onOut);
			addEventListener(MouseEvent.MOUSE_DOWN, onDown);
			addEventListener(MouseEvent.MOUSE_UP, onUp);
		}
		override public function configure():void
		{
			image = getChildAt(0) as Bitmap;			
			setScaleBitmap(image);
		}
		override public function reSize()
		{
			arrow_mc.y = ((Height/2) - (arrow_mc.height/2));
			arrow_mc.x = (Width - 6);
			txt.y = (Height - txt.height)/2;
			txt.width = Width-35;
		}
		private function onOver(e:MouseEvent):void
		{
			//this.gotoAndStop(2);
			arrow_mc.gotoAndStop(2);
		}
		private function onOut(e:MouseEvent):void
		{
			//this.gotoAndStop(1);
			arrow_mc.gotoAndStop(1);
		}
		private function onDown(e:MouseEvent):void
		{
			//this.gotoAndStop(3);
			arrow_mc.gotoAndStop(3);
		}
		private function onUp(e:MouseEvent):void
		{
			//this.gotoAndStop(2);
			arrow_mc.gotoAndStop(2);
			if(!opened)
			{
			}
			else
			{
			}
			opened = !opened;
			dispatchEvent(new Event('OPEN', true));
		}
	}
}
