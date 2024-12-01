package Events
{
	import flash.events.Event;
	
	public class ErrorEvent extends Event
	{
		public static const SHOW_ERROR:String = 'ShowError';
	
		public var id:int = -1;		
		
		public function ErrorEvent(_id:int) 
		{
			super(SHOW_ERROR, true);
			id = _id;
		}
	}
}
