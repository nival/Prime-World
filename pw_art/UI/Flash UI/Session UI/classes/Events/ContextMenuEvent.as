package Events 
{
	import flash.events.Event;
	
	public class ContextMenuEvent extends Event 
	{
		public static const EVENT_TYPE:String = 'ContextMenuEvent';
		public var items:Array = new Array();
		
		public function ContextMenuEvent(_items:Array, bubbles:Boolean=true) 
		{ 
			super(EVENT_TYPE, bubbles);
			items = _items;
		} 
	}
	
}