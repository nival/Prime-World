package  
{
	import flash.events.Event;

	public class CancelCycleEvent extends Event 
	{
		public static const Type:String = "CancelCycleEvent";
		
		public var Index:int;
		
		public function CancelCycleEvent(cycleIndex:int) 
		{ 
			super(Type, true);
			Index = cycleIndex;
		} 
	}
	
}