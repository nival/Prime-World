package  Events
{
	import flash.events.Event;
	
	public class DetailedStatisticMateEvent extends Event
	{
		public static const EVENT_TYPE:String = 'DetailedStatMateEvent';
		
		public var id:int = -1;		
		
		public function DetailedStatisticMateEvent(_id:int, boobles:Boolean = true) 
		{
			super(EVENT_TYPE, boobles);
			id = _id;
			
		}
	}
}
