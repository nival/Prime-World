package Events 
{
	import flash.events.Event;
	
	public class FsCommandEvent extends Event
	{
		public static const EVENT_TYPE:String = 'FsCommandEvent';
		
		public var Args:String;
		public var CommandName:String;
		
		public function FsCommandEvent(commandName:String, args:String) 
		{
			super(EVENT_TYPE, true);
			CommandName = commandName;
			Args = args;
		}
		
	}

}