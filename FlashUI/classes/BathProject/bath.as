package
{
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.text.TextField;
	
	public class bath extends MovieClip
	{
		public var bath_pnl:BathPnl;
		public var test_txt:TextField;
		public var initBathTimer:Number = 10;
		public var BonusFrameConst:int = 11;
		
		private var bathCycles:Array = new Array();
		private var curFrame:int = 0;
		//////////
		public function bath():void
		{
			addEventListener(Event.ADDED_TO_STAGE, init);
			addEventListener(StartCycleEvent.Type, OnStartButtonClick)
			addEventListener(CancelCycleEvent.Type, OnCancelButtonClick)
		}
		
		private function OnCancelButtonClick(e:CancelCycleEvent):void
		{
			for (var i:int = 0; i < bathCycles.length; i++) 
			{
				var item:BathData = bathCycles[i];
				
				item.IsWorking = false;
				item.IsActive = false;
				item.IsFaded = false;
				item.BathTimer = initBathTimer * i + initBathTimer;
			}
			
			bath_pnl.SetCyclesData(bathCycles);
			removeEventListener(Event.ENTER_FRAME, OnEnterFrame);
		}
		
		private function OnStartButtonClick(e:StartCycleEvent):void
		{
			for (var i:int = 0; i < bathCycles.length; i++) 
			{
				var item:BathData = bathCycles[i];
				
				item.IsWorking = true;
				item.BathTimer = initBathTimer * i + initBathTimer;
				item.MathTimer = initBathTimer * i + initBathTimer;
				item.BathProgress = 0;
				item.CurrentProgress = 0;
			}
			
			var bathData:BathData = bathCycles[e.Index];
			bathData.IsFaded = true;
			bathData.IsActive = true;
			bath_pnl.SetCyclesData(bathCycles);
			addEventListener(Event.ENTER_FRAME, OnEnterFrame);
		}
		
		private function OnEnterFrame(e:Event):void
		{
			curFrame++;
			
			if (curFrame != 24)
			{
				return;
			}
			curFrame = 0;
			
			for each (var item:BathData in bathCycles)
			{
				
				if (!item.IsActive)
					{
						continue;
					}				
				item.BathTimer -= 1;
				if (item.BathTimer < 0) item.BathTimer = 0;
				item.CurrentProgress += 100 / item.MathTimer;
				item.BathProgress = Math.round(item.CurrentProgress);
				if (item.BathProgress > 100) item.BathProgress = 100;
			}			
			bath_pnl.SetCyclesData(bathCycles);
		}
		
		private function init(e:Event = null):void
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			FillBath();
		}
		
		private function FillBath():void
		{
			
			for (var i:int = 0; i < 4; i++)
			{
				var newBathData:BathData = new BathData();
				
				newBathData.Index = i;
				newBathData.IsActive = false;
				newBathData.IsWorking = false;
				newBathData.IsFaded = false;
				newBathData.TitleText = "Item " + i.toString();
				
				var BathPrice:BathCostResource = new BathCostResource();
				BathPrice.CostSilver = (i * 100 + 100);
				BathPrice.CostIcon = BathCostResource.gold;
				
				newBathData.CycleCost = BathPrice;
				
				var BathBonusVar:BathBounusResource = new BathBounusResource();
				BathBonusVar.Bonus = i * 100;
				BathBonusVar.BounusIcon = BathBounusResource.wood
				
				newBathData.BathBonus = BathBonusVar;
				
				bathCycles.push(newBathData);
			}
			
			bath_pnl.SetCyclesData(bathCycles);
		}
	}
}