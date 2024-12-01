package MainScreen 
{
	import flash.display.MovieClip;
	
	public class DayNight extends MovieClip 
	{
		private const EPSILON:Number = 0.001;
		
		public var dayNightIcon_mc:MovieClip;
		public var progress_mc:MovieClip;
		public var timer_mc:GameTimer;
		
		private var _night:Boolean = false;
		private var _fraction:Number = 0;
		
		public function DayNight() 
		{
			super();
			
			dayNightIcon_mc.stop();
			progress_mc.stop();
			
			ApplyState();
			ApplyStateFraction();
		}
		
		public function set Night(value:Boolean):void
		{
			if (_night == value)
				return;
			
			_night = value;
			
			ApplyState();
		}
		
		public function set StateFraction(value:Number):void
		{
			var safeValue:Number = Math.min(Math.max(value, 0), 1);
			
			if (Math.abs(_fraction - safeValue) < EPSILON)
				return;
			
			_fraction = safeValue;
			
			ApplyStateFraction();
		}
		
		public function set GameTime(value:int):void
		{
			timer_mc.GameTime = value;
		}
		
		private function ApplyState():void
		{
			if (_night)
				dayNightIcon_mc.gotoAndStop(1);
			else
				dayNightIcon_mc.gotoAndStop(2);
		}
		
		private function ApplyStateFraction():void
		{
			// технически, есть 1 фейковый кадр
			var frame:Number = _fraction * (progress_mc.totalFrames + 1);
			
			if (frame < 1)
			{
				progress_mc.visible = false;
				progress_mc.gotoAndStop(1);
			}
			else
			{
				progress_mc.visible = true;
				progress_mc.gotoAndStop(Math.max(Math.ceil(frame - 1), 1));
			}
		}
	}
}