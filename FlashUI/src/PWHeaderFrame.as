package  {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	public class PWHeaderFrame extends PWFrame 
	{
		private var timer:Timer;
		private var chance:int = 2;
		
		public function PWHeaderFrame() 
		{
			headerFlash_mc.width = Width;
			headerLight_mc.width = headerFlash_mc.width;
			
			headerFlash_mc.stop();
			headerLight_mc.stop();
			
			timer = new Timer(10000, 1);
			timer.addEventListener(TimerEvent.TIMER, onTimer);
			timer.start();
			
			addEventListener(MouseEvent.MOUSE_DOWN, onDown);
		}
		private function onDown(e:MouseEvent):void
		{
			headerFlash_mc.gotoAndPlay(1);
		}
		private function onTimer(e:TimerEvent):void
		{
			chance = Math.floor(Math.random()*2);
			if(chance<1)
			{
				headerLight_mc.gotoAndPlay(1);
				timer.reset();
				timer.start();
			}
		}
	}
}
