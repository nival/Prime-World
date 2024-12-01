package Effects
{
	import Controllers.SoundController;
	import fl.transitions.Tween;
	import fl.motion.easing.Linear;
	import fl.transitions.TweenEvent;
	import flash.display.MovieClip;
	import flash.events.TimerEvent;
	import flash.geom.ColorTransform;
	import flash.events.Event;
	import flash.utils.Timer;

	public class AttentionEffect extends MovieClip
	{
		// NOTE: должны совпадать с актуальным кол-вом кадров в клипах, составляющих эффект
		// если еще немного дописать, можно получать кол-во кадров напрямую из клипов
		private static const BIRTH_FRAMES:uint = 15;
		private static const PING_FRAMES:uint = 20;
		
		private var _free:Boolean = true;
		
		private var _timer:Timer = null;
		private var _fader:Tween = null;
		
		public function AttentionEffect()
		{
			mouseEnabled = false;
			mouseChildren = false;
			
			scaleX = 1.5;
			scaleY = 1.5;
				
			visible = false;
			
			stop();
		}
		
		public function StartFade():void
		{
			//_fader.start();
		}
		
		private function CleanupLifeTimeController():void
		{
			if (_timer != null)
				_timer.stop();
			if (_fader != null)
				_fader.stop();
				
			_timer = null;
			_fader = null;
		}
		
		private function StartLifeTimeController(lifeTime:Number):void
		{
			var birthTime:Number = Number(BIRTH_FRAMES) / stage.frameRate;
			var pingTime:Number = Number(PING_FRAMES) / stage.frameRate;
			
			var pingCount:Number = Math.ceil((lifeTime - birthTime) / pingTime);
			
			if (pingCount < 1)
				pingCount = 1;
			
			var effectiveFadeTime = pingTime * pingCount;
			var effectiveLifeTime = birthTime + effectiveFadeTime;
			
			_timer = new Timer(effectiveLifeTime * 1000.0, 1);
			_timer.addEventListener(TimerEvent.TIMER_COMPLETE, OnTimerComplete);
			_timer.start();
			
			_fader = new Tween(this, 'alpha', Linear.easeNone, 1, 0, effectiveFadeTime, true);
			_fader.start();
		}
		
		private function Stop():void
		{	
			_free = true;
			
			visible = false;
			gotoAndStop(1);
			
			CleanupLifeTimeController();
		}
		
		public function Play(lifeTime:Number = 5.0):void
		{
			_free = false;
			
			alpha = 1;
			visible = true;
			gotoAndPlay(1);
			
			SoundController.PlaySound(SoundController.MINIMAP_ALERT);
			
			StartLifeTimeController(lifeTime);
		}
		
		public function get Available():Boolean
		{
			return _free;
		}
		
		public function set Color(value:uint):void
		{
			var r:Number = ((value >> 16) & 0xFF);
			var g:Number = ((value >>  8) & 0xFF);
			var b:Number = ((value >>  0) & 0xFF);
			
			r /= 255.0;
			g /= 255.0;
			b /= 255.0;

			var ct:ColorTransform = transform.colorTransform;
			
			ct.redMultiplier = r;
			ct.greenMultiplier = g;
			ct.blueMultiplier = b;
			
			transform.colorTransform = ct;
		}
		
		private function OnTimerComplete(e:TimerEvent):void
		{
			Stop();
		}
	}
}