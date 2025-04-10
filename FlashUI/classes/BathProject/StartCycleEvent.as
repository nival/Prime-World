package  
{
	import flash.events.Event;
	
	public class StartCycleEvent extends Event 
	{
		public static const Type:String = "StartCycleEvent";
		
		public var Index:int;
		
		public function StartCycleEvent(index:int, bubbles:Boolean=true) 
		{ 
			super(Type, bubbles);
			Index = index;
		}		
	}
	
}