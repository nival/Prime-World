package 
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.events.Event;
	
	public class BathItem extends MovieClip
	{
		public	var	closeS_btn: MyButton;
		public	var	title: TextField;
		public	var	titleFrame: MovieClip;
		public	var	res_txt: TextField;
		public	var	clock_txt: TextField;
		public	var	produceIcon_mc: ProduceIcon;
		public	var	paLight_mc: MovieClip;
		public	var	bathProgress_bar: ProgressBar;
		public	var	cash: ProduceCash;
		public	var	startFinishBlock_mc: StartFinishBlock;
		public	var	paShields_mc: MovieClip;
		public	var	anim_mc: MovieClip;
		public	var	bathItemSize: MovieClip;
		public	var	glow: MovieClip;
		public	var	top_line: MovieClip;
		
		public	var	race:Number = 1;
		private var timeFormater:TimerFormater;
		private var currentCycle:BathData;
		
		public function BathItem():void 
		{
			addEventListener(Event.ADDED_TO_STAGE, itemInit);
		}
		
		private function itemInit(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, itemInit);
			timeFormater = new TimerFormater(clock_txt);
			// временный стоп клипов;
			paShields_mc.gotoAndStop(race);
			anim_mc.gotoAndStop(1);
			anim_mc.visible = false;
			paShields_mc.visible = false;
			paLight_mc.visible = false;
			glow.visible = true;
			
			closeS_btn.addEventListener(MouseEvent.MOUSE_DOWN, OnCancelClick);
		}
		
		private function OnCancelClick(e:MouseEvent):void 
		{
			if (currentCycle == null) return;
			
			dispatchEvent(new CancelCycleEvent(currentCycle.Index));
		}
		
		public function GetWidth():Number
		{
			return bathItemSize.width;
		}
		
		public	function	SetCycle(cycle:BathData): void
		{  
			currentCycle = cycle;
			
			 title.text = cycle.TitleText;;
			 produceIcon_mc.ProduceIconInit(cycle.BathBonus.BounusIcon);
			 res_txt.text = cycle.BathBonus.Bonus.toString();
			 bathProgress_bar.StopProgress(cycle.BathProgress);
			 cash.CashInit(cycle.CycleCost.CostIcon, cycle.CycleCost.CostSilver);
			 
			  timeFormater.SetTime(cycle.BathTimer);
			 
			 closeS_btn.visible = cycle.IsWorking && cycle.IsActive;
			 
			 startFinishBlock_mc.SetState(cycle.IsWorking, cycle.IsActive );
			 bathProgress_bar.visible = cycle.IsActive;
			 
			 
			 startFinishBlock_mc.CycleIndex = cycle.Index;
			 
			 if (cycle.IsActive)
				{
					glow.visible = false;
				}
			 else 
				{
					glow.visible = true;
				}
			 trace (cycle.IsFaded);
		}
	}
	
}