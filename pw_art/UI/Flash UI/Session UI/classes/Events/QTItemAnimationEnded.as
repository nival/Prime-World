package Events 
{
	import flash.events.Event;

	public class QTItemAnimationEnded extends Event
	{
		public static const EVENT_TYPE:String = 'QTItemAnimationEnded';
		public var Item:QTItem;
		
		public function QTItemAnimationEnded(_item:QTItem) 
		{
			super(EVENT_TYPE, true);
			Item = _item;
		}
		
	}

}