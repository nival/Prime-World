package Events 
{
	import flash.events.Event;
	public class ChatBarPlayerSelectEvent extends Event
	{
		public static const EVENT_TYPE:String = 'ChatBarPlayerSelectEvent';
		
		public var Name:String = "";		
		
		public function ChatBarPlayerSelectEvent(_id:String, boobles:Boolean = true) 
		{
			super(EVENT_TYPE, boobles);
			Name = _id;
			
		}
	}

}