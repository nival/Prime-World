package Controllers
{
	import flash.utils.Dictionary;
	import Interfaces.IMateInfoContainer;
	import BaseClasses.MateInfoBase;
	import Utils.SortMatesUtils;
	
	public class MateInfoController 
	{
		private var mateContainer:IMateInfoContainer;
		
		private var mates_arr:Array = [];
		public  var SpectatorMode:Boolean = false;
		public var OurHeroId:int = -1;
		
		private var partyIds:Dictionary = new Dictionary();
		
		public function MateInfoController(_mateContainer:IMateInfoContainer) 
		{
			mateContainer = _mateContainer;
			//mateContainer.getNewMateInfo();
		}
		
		public function GetMatesCount():uint
		{
			return mates_arr.length;
		}
		
		public function GetMateInfoByIdx(idx:int):int
		{
			if(idx < 0 || idx >= GetMatesCount())
				return -1;
			
			return mates_arr[idx].id;
		}
		
		public function GenerateMateInfo(ID:int, partyId:int):MateInfoBase
		{
			for (var index:int =0; index<mates_arr.length; index++)
			{
				var id:int = mates_arr[index].id;
				
				if (id == ID)
				{
					trace("member was generated earlier, don't use this func")
					return null;
				}
			}
			
			var mateInfo:MateInfoBase = mateContainer.getNewMateInfo();
			
			if (mateInfo == null)
			{
				trace ("cannot create MateInfo");
				return null;
			}
			
			mates_arr.push(mateInfo);
			mateInfo.id = ID;
			mateInfo.SpectatorMode = SpectatorMode;
			partyIds[mateInfo] = partyId;
			
			ArrangeItems();
			
			return mateInfo;
		}
		
		private function ArrangeItems():void 
		{
			mates_arr = SortMatesUtils.SortMates(OurHeroId, mates_arr, partyIds)
			
			var startPos:Array = mateContainer.GetStartPositions();
			
			for (var i:int = 0; i < mates_arr.length; i++) 
			{
				mates_arr[i].x = startPos[i];
			}
			
			for (var j:int = 0; j < mates_arr.length-1; j++) 
			{
				mateContainer.ShowChain(j, partyIds[mates_arr[j]] == partyIds[mates_arr[j + 1]] && partyIds[mates_arr[j]] != 0);
			}
		}
		
		public function GetMateInfo(ID:int):MateInfoBase
		{
			for (var index:int =0; index<mates_arr.length; index++)
			{
				var id:int = mates_arr[index].id;
				
				if (id == ID)
					return mates_arr[index];
			}
			
			trace("member wasn't generated earlier, generate it before")
			return null;
		}
		
		public function ResetToStartState():void
		{
			mates_arr = [];
			partyIds = new Dictionary();
			mateContainer.ResetMateState();
			mateContainer.HideChains();
		}
		
		
		public function DoesHeroExist(_id:int):Boolean
		{
			for (var index:int =0; index<mates_arr.length; index++)
				if (_id == mates_arr[index].id)
					return true;
		
			return false;
		}
		
		public function ResetMateSelection():void
		{
			mateContainer.ResetMateSelection();
		}
	}
}