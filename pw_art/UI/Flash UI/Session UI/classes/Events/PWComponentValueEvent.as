package Events
{
	import flash.events.Event;
	
	public class PWComponentValueEvent extends Event
	{
		public static const CHANGE:String = 'Change';
		public var componentValue:int = 0;
		public var ControlName:String = "";
		
		
		public function PWComponentValueEvent(eventType:String, _value:int, controlName:String, bubles:Boolean = true) 
		{
			componentValue = _value;
			ControlName = controlName;
			super(eventType, bubles);
		}
	}
}
