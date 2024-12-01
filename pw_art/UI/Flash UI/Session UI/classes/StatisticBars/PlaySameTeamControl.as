package StatisticBars 
{
	import Components.ButtonStandart;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.utils.Timer;
	
	public class PlaySameTeamControl extends MovieClip 
	{
		public var party_lbl:TextField;
		public var party_btn:ButtonStandart;
		
		private var _available:Boolean = false;
		private var _agreed:Boolean = false;
		private var _timer:Timer;
		
		public function PlaySameTeamControl() 
		{
			super();
			
			party_btn.addEventListener("Up", OnButtonClick);
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, OnLocalizationComplete);
				
			UpdateButton();
		}
		
		public function Configure(available:Boolean, timeOut:int):void
		{
			if (_timer != null)
				_timer.stop();
			
			if (timeOut < 1)
			{
				available = false;
				timeOut = 0;
			}
			
			_available = available;
			_agreed = false;
			
			if (timeOut > 0)
			{
				_timer = new Timer(1000, timeOut);
				_timer.reset();
				_timer.addEventListener(TimerEvent.TIMER, OnTimer);
				_timer.addEventListener(TimerEvent.TIMER_COMPLETE, OnTimerComplete);
			}
			else
			{
				_timer = null;
			}
			
			UpdateButton();
		}
		
		public function StartCountdown():void
		{
			if (_timer != null)
				_timer.start();
			
			UpdateButton();
		}
		
		public function set Agreed(value:Boolean):void
		{
			if (_timer != null)
				_timer.stop();
				
			_agreed = value;
			_timer = null;
			
			UpdateButton();
			
			DispatchResult();
		}
		
		private function OnLocalizationComplete(e:Event):void
		{
			party_lbl.text = Localization.FinalStatisticBar_PartyLabel;
			
			UpdateButton();
		}
		
		private function UpdateButton():void
		{
			var timeLeft:int = this.TimeLeft;
			
			if (timeLeft > 0)
			{
				party_btn.EnableButton = _available;
				party_btn.labelText = Localization.FinalStatisticBar_PartyButtonYes + " (" + timeLeft + ")";
			}
			else
			{
				party_btn.EnableButton = false;
				
				if (_agreed)
					party_btn.labelText = Localization.FinalStatisticBar_PartyButtonYes;
				else
					party_btn.labelText = Localization.FinalStatisticBar_PartyButtonNo;
			}
		}
		
		private function get TimeLeft():int
		{
			if (_timer == null)
				return 0;
			if (_timer.running == false)
				return 0;
			
			return _timer.repeatCount - _timer.currentCount;
		}
		
		private function OnTimer(e:Event):void
		{
			UpdateButton();
		}
		
		private function OnTimerComplete(e:Event):void
		{
			Agreed = false;
		}
		
		private function OnButtonClick(e:Event):void
		{
			Agreed = true;
		}
				
		private function DispatchResult():void
		{
			if (_available == false)
				return;
			
			FSCommands.Send(FSCommands.PLAY_SAME_TEAM, (_agreed ? "1" : "0"));
		}
	}
}