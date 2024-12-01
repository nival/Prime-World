package Events 
{
	import flash.events.Event;
	
	public class ToggleButtonClickedEvent extends Event
	{
		public static const EVENT_TYPE:String = "Up";
		public var Checked:Boolean = false;
		
		
		public function ToggleButtonClickedEvent(checked:Boolean) 
		{
			super(EVENT_TYPE, true);
			Checked = checked;
		}
		
	}

}