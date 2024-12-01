package Components
{
	import flash.events.Event;
	
	public class PWSliderEvent extends Event
	{
		public static const CHANGE:String = 'Change';
		public var SliderValue:int = 0;
		
		public function PWSliderEvent(eventType:String, _value:int, bubles:Boolean = true) 
		{
			SliderValue = _value;
			super(eventType, bubles);
		}
	}
}
