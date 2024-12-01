package Events
{
	import flash.events.Event;
	
	public class WindowVisibleControllerEvent extends Event
	{
		public static const OPEN_CLOSE:String = 'WindoVisibleController';
		public static const OPEN:String = 'OpenWindow';
		public static const WINDOW_CHANGED:String = 'WindowChangedState';
		public static const WINDOW_MOVING:String = 'WindowMoving';
				
		public var id:int = -1;		
		
		public function WindowVisibleControllerEvent(eventType:String,_id:int, boobles:Boolean = true) 
		{
			super(eventType, boobles);
			id = _id;
			
		}
	}
}
