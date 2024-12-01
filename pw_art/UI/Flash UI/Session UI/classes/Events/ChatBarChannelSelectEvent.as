package Events 
{
	import flash.events.Event;
	public class ChatBarChannelSelectEvent extends Event
	{
		public static const EVENT_TYPE:String = 'ChatBarChannelSelect';
		
		public var id:int = -1;		
		
		public function ChatBarChannelSelectEvent(_id:int, boobles:Boolean = true) 
		{
			super(EVENT_TYPE, boobles);
			id = _id;
			
		}
	}

}