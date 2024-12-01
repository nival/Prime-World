package Controllers
{
	import BaseClasses.MateInfoBase;
	import flash.utils.Dictionary;
	import StatisticBars.StatisticContainer;
	import StatisticBars.StatisticsBarPlayers;
	import Utils.SortMatesUtils;
	public class StatisticMateInfoController 
	{
		private var mateContainer:StatisticContainer;
		private var mates_arr:Array = [];
	
		public var OurHeroId:int = -1;
		private var partyIds:Dictionary = new Dictionary();
		
		
		public function StatisticMateInfoController(_mateContainer:StatisticContainer) 
		{
			mateContainer = _mateContainer;
			//mateContainer.getNewMateInfo();
		}
		
		public function GenerateNewMateInfo(id:int, partyId:int):StatisticsBarPlayers
		{
			var mate:StatisticsBarPlayers =  mateContainer.getNewMateInfo();
			mate.id = id;
			mates_arr.push(mate);
			
			partyIds[mate] = partyId;
			
			ArrangeMates();
			
			return mate;
		}
		
		private function ArrangeMates():void 
		{
			mates_arr = SortMatesUtils.SortMates(OurHeroId, mates_arr, partyIds);
			mateContainer.HideChains();
			var posY:int = 0;
			
			for (var i:int = 0; i < mates_arr.length; i++) 
			{
				mates_arr[i].y = posY;
				posY += mateContainer.OneElementHeight;
			}
			
			for (var j:int = 0; j < mates_arr.length-1; j++) 
			{
				var show:Boolean = partyIds[mates_arr[j]] == partyIds[mates_arr[j + 1]] && partyIds[mates_arr[j]] != 0;
				
				mateContainer.ShowChain(j,show);
			}
		}
		
		
		public function GetMateInfo(ID:int):StatisticsBarPlayers
		{
			for (var index:int =0; index<mates_arr.length; index++)
			{
				var id:int = mates_arr[index].id;
				
				if (id == ID)
					return mates_arr[index];
			}
			
			trace("their is no mate by id "+ID)
			return null;
		}
		
		public function ResetMates():void
		{
			mates_arr = [];
			mateContainer.ResetMateState();
			mateContainer.HideChains();
			partyIds = new Dictionary();
		}
		
		public function DoesHeroExist(_id:int):Boolean
		{
			for (var index:int =0; index<mates_arr.length; index++)
				if (_id == mates_arr[index].id)
					return true;
		
			return false;
		}
	
		
		public function IsEmpty():Boolean 
		{
			return mates_arr.length == 0;
		}
		
		public function ResetOurHero():void 
		{
			for each (var item:StatisticsBarPlayers in mates_arr) 
			{
				item.SetSelected(false);
			}
		}
	}
}