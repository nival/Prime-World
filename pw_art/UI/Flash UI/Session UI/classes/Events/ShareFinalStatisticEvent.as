package classes.Events 
{
	import flash.events.Event;

	public class ShareFinalStatisticEvent extends Event 
	{
		public static const EVENT_TYPE:String = 'ShareFinalStatisticEvent';
		
		public function ShareFinalStatisticEvent() 
		{ 
			super(EVENT_TYPE, true);
		} 
		
	}

}