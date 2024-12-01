package Components
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import src.ButtonTooltipEvent;
	import flash.geom.Point;
	import flash.events.MouseEvent;
	
	public class FormatedTimer extends MovieClip
	{
		private var isTwoDigital:Boolean;
		public var clock:TextField;
		public var coolDownMask_mc:MovieClip;
		public var clockRightText:TextField;
		public var clockLeftText:TextField;
		private var timerTooltip:String = '';
		private var globalPoint:Point;
		
		private var startPosition:Number;
		private var epselon:Number = 2;
		
		public function FormatedTimer()
		{
			clock.autoSize = TextFieldAutoSize.CENTER;
			if (clockLeftText != null) {
				clockLeftText.mouseEnabled = false;
				clockLeftText.autoSize = TextFieldAutoSize.RIGHT;
			}
			if (clockRightText != null) {
				clockRightText.mouseEnabled = false;
				clockRightText.autoSize = TextFieldAutoSize.LEFT;
			}
			clock.mouseEnabled = false;
			clock.x = Math.round(clock.x);	
			
			startPosition = this.x;
		}
		
		public function onOver():void
		{
			if (timerTooltip.length == 0) return;
			globalPoint = this.localToGlobal(new Point());
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, this, globalPoint.x, globalPoint.y, timerTooltip));
		}
		
		public function onOut():void
		{
			if (timerTooltip.length == 0) return;
			
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
		}
		
		
		public function set Tooltip(value:String):void 
		{
			timerTooltip = value;
		}
		
		public function get Tooltip():String
		{
			return timerTooltip;
		}
		
		public function set TwoDigitalTimerFormat(_isTwoDigital:Boolean):void
		{
			isTwoDigital = _isTwoDigital;
		}
		
		public function set Time(value:Number):void
		{
			if (value <= 0) return;
			
			if (value < 1&&isTwoDigital)
			{
				DotedTime = value;
				return;
			}
			
			var timeLeft:int = Math.round(value-0.5);
			
			var hour:int = Math.floor(timeLeft/3600);
			var secInHour:int = hour * 3600;
			var min:int = Math.floor((timeLeft-secInHour)/60);
			var sec:int = timeLeft - min * 60-secInHour;
			
			
			isTwoDigital? FormatAsTwoDigital(hour, min, sec) : FormatAsFourDigital(hour, min, sec);
		}
		
		public function set DotedTime(time:Number):void 
		{
			if (value >= 1) return;
			var value:Number = Math.round(time * 10) / 10;
			
			clock.text = value.toString();
		}
		
		private function FormatAsTwoDigital(hour:int, min:int, sec:int):void
		{
			if (hour > 0)
			{
				clock.text = hour.toString() + "ч";
				return;
			}
			if (min > 0)
			{
				clock.text = min.toString() + "м";
				return;
			}
			
			clock.text = sec.toString();
		}
		
		private function FormatAsFourDigital(hour:int, min:int, sec:int):void
		{
			if (clockLeftText == null || clockRightText == null) return;
			
			var hours:String = hour.toString();
			var minutes:String = min.toString();
			var seconds:String = sec.toString();
			
			if (hour > 0)
			{
				if (hours.length == 1) 
				{
					hours = " " + hours;
					this.x = startPosition - Math.round(clock.textWidth / 2)-epselon;
				}
				else
				{
					this.x = startPosition;
				}
				
				if (minutes.length == 1) 
				{
					minutes = "0" + minutes;
				}
				
				clockRightText.text = minutes;
				clockLeftText.text = hours;
				
				clockRightText.x = Math.round(clock.textWidth) + clock.x;
				clockLeftText.x = clock.x - Math.round(clockLeftText.textWidth);
				
				return;
			} 
			
			if (minutes.length == 1) 
			{
				minutes = " " + minutes; 
				this.x = startPosition - Math.round(clock.textWidth / 2)-epselon;
			}
			else
			{
				this.x = startPosition;
			}
			if (seconds.length == 1) 
			{
				seconds = "0" + seconds;
			}
			
			clockLeftText.text = minutes;
			clockRightText.text = seconds;
				
			clockRightText.x = Math.round(clock.textWidth) + clock.x;
			clockLeftText.x = clock.x - Math.round(clockLeftText.textWidth);
			
		}
	}


}