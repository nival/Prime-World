package Utils 
{
	import flash.utils.Dictionary;
	import Interfaces.IMate;

	public class SortMatesUtils 
	{
		static private var OurHeroId:int;
		static private var partyIds:Dictionary;
		static private var mates_arr:Array;
		public static function SortMates(ourHeroId:int, mates:Array, ids:Dictionary):Array
		{
			SortMatesUtils.partyIds = ids;
			SortMatesUtils.OurHeroId = ourHeroId;
			SortMatesUtils.mates_arr = mates;
			
			return mates_arr.sort(SortFunction);
		}
		
		static private function SortFunction(a:IMate, b:IMate):int 
		{
			var ourPartyId:int = 0;
			
			if (OurHeroId != -1) 
			{
				if (a.id == OurHeroId) 
					return -1;
				
				if (b.id == OurHeroId) 
					return 1;
				
				for each (var item:IMate in mates_arr) 
				{
					if (item.id == OurHeroId && partyIds[item]!=null)
					{
						ourPartyId = partyIds[item];
						break;
					}
				}
			}
			
			if (ourPartyId != 0 ) 
			{
				if ( partyIds[a] == ourPartyId && partyIds[b]!=ourPartyId) 
				{
					return -1;
				}
				
				if ( partyIds[b] == ourPartyId && partyIds[a]!=ourPartyId) 
				{
					return 1;
				}
			}
			
			if (partyIds[a] > partyIds[b])
			{
				return -1;
			}
			
			if (partyIds[a] < partyIds[b])
			{
				return 1;
			}
			
			return 0;
		}
		
	}

}