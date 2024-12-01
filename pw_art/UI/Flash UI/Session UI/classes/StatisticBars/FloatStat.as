package StatisticBars
{
	
	import flash.display.MovieClip;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import fl.transitions.easing.None;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.events.Event;
	import fl.transitions.TweenEvent;
	import flash.utils.Timer;
	
	
	public class FloatStat extends MovieClip 
	{
		//reference 
		public var allPoint_txt:TextField;
		public var floatFlash_mc:MovieClip;
		public var levelUpSpark_mc:MovieClip;
		
		private var time = 40;
		private var xposFloatTween:Tween;
		
		private var xposTweenFinishEvent:Event;
		private var floatLevelUp:Event;
		
		private var levelUpSparkTimer:Timer;
		private var isNeedToLevelUp:Boolean;
		
		
		private var durationKoeff:int = 15;
		
		public function FloatStat() 
		{
			floatFlash_mc.stop();
			floatFlash_mc.visible = false;
			levelUpSpark_mc.stop();
			levelUpSpark_mc.visible = false;
			
			xposTweenFinishEvent = new Event('xposTweenFinish', true);
			floatLevelUp = new Event('floatLevelUp', true);
			xposFloatTween = new Tween(this, 'x', Strong.easeOut, 0, 0, time);
			xposFloatTween.addEventListener(TweenEvent.MOTION_FINISH, xposTweenFinish);
			xposFloatTween.addEventListener(TweenEvent.MOTION_CHANGE, xposTweenChange);
			xposFloatTween.stop();
			allPoint_txt.autoSize = TextFieldAutoSize.CENTER;
			
			levelUpSparkTimer = new Timer(1, 1);
			levelUpSparkTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnSparksTimerEnd);
			
		}
		
		private function OnSparksTimerEnd(e:TimerEvent):void 
		{
			if (!isNeedToLevelUp) return;
			
			levelUpSpark_mc.visible = true;
			levelUpSpark_mc.gotoAndPlay(1);
		}
		
		public function X(_x:Number, animate = true):void
		{
			if(animate)
			{
				xposFloatTween.func = Strong.easeOut;
				xposFloatTween.duration = Math.abs(this.x - _x)/durationKoeff;
				
				levelUpSparkTimer.delay = (Math.abs(this.x - _x) / durationKoeff) / 3;
				levelUpSparkTimer.start();
								
				xposFloatTween.stop();
				xposFloatTween.begin = this.x;
				xposFloatTween.finish = _x;
				xposFloatTween.start();
			}
			else
			{
				xposFloatTween.stop();
				this.x = _x;
			}
		}

		public function set Text(text:String):void
		{
			allPoint_txt.text = text;
		}
		private function xposTweenFinish(e:TweenEvent):void
		{
			dispatchEvent(xposTweenFinishEvent);
		}
		
		public function IsLevelUpWillBe(isLevelUp:Boolean):void
		{
			isNeedToLevelUp = isLevelUp;
		}
		
		private function xposTweenChange(e:TweenEvent):void
		{
			if(e.position > 710&&floatFlash_mc.visible ==false&&isNeedToLevelUp)
			{
				floatFlash_mc.visible = true;
				floatFlash_mc.gotoAndPlay(1);
				dispatchEvent(floatLevelUp);
			}
		}
	}
}