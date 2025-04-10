package
{
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.text.TextField;
	
	public class production extends MovieClip
	{
		public var bath_pnl:ProductionPnl;
		public var test_txt:TextField;
		public var initBathTimer:Number = 10;
		public var BonusFrameConst:int = 11;
		
		private var productionCycles:Array = new Array();
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
			for (var i:int = 0; i < productionCycles.length; i++) 
			{
				var item:ProductionData = productionCycles[i];
				
				item.IsWorking = false;
				item.IsActive = false;
				item.IsFaded = false;
				item.ProductionTimer = initBathTimer * i + initBathTimer;
			}
			
			bath_pnl.SetCyclesData(productionCycles);
			removeEventListener(Event.ENTER_FRAME, OnEnterFrame);
		}
		
		private function OnStartButtonClick(e:StartCycleEvent):void
		{
			for (var i:int = 0; i < productionCycles.length; i++) 
			{
				var item:ProductionData = productionCycles[i];
				
				item.IsWorking = true;
				item.ProductionTimer = initBathTimer * i + initBathTimer;
				item.MathTimer = initBathTimer * i + initBathTimer;
				item.ProductionProgress = 0;
				item.CurrentProgress = 0;
			}
			
			var productionData:ProductionData = productionCycles[e.Index];
			productionData.IsFaded = true;
			productionData.IsActive = true;
			bath_pnl.SetCyclesData(productionCycles);
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
			
			for each (var item:ProductionData in productionCycles)
			{
				
				if (!item.IsActive)
					{
						continue;
					}				
				item.ProductionTimer -= 1;
				if (item.ProductionTimer < 0) item.ProductionTimer = 0;
				item.CurrentProgress += 100 / item.MathTimer;
				item.ProductionProgress = Math.round(item.CurrentProgress);
				if (item.ProductionProgress > 100) item.ProductionProgress = 100;
			}			
			bath_pnl.SetCyclesData(productionCycles);
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
				var newProductionData:ProductionData = new ProductionData();
				
				newProductionData.Index = i;
				newProductionData.IsActive = false;
				newProductionData.IsWorking = false;
				newProductionData.IsFaded = false;
				newProductionData.TitleText = "Item " + i.toString();
				
				var ProductionPrice:ProductionCostResource = new ProductionCostResource();
				ProductionPrice.CostSilver = (i * 100 + 100);
				ProductionPrice.CostIcon = ProductionCostResource.gold;
				
				newProductionData.CycleCost = ProductionPrice;
				
				var ProductionBonusVar:ProductionBounusResource = new ProductionBounusResource();
				ProductionBonusVar.Bonus = i * 100;
				ProductionBonusVar.BounusIcon = ProductionBounusResource.wood
				
				newProductionData.ProductionBonus = ProductionBonusVar;
				
				productionCycles.push(newProductionData);
			}
			
			bath_pnl.SetCyclesData(productionCycles);
		}
	}
}