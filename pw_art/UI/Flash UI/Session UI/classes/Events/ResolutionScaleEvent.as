package Events 
{
	import flash.events.Event;

	public class ResolutionScaleEvent extends Event 
	{
		public static const EVENT_TYPE:String = 'ResolutionScaleEvent';
		
		public var ResolutionKoeff:Number=0;
		
		public function ResolutionScaleEvent(koef:Number) 
		{ 
			super(EVENT_TYPE, false);
			ResolutionKoeff = koef;
		} 
		
	}
	
}