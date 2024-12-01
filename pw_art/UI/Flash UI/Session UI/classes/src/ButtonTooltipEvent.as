package  src
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	
	public class ButtonTooltipEvent extends Event
	{
		public static const EVENT_TYPE:String = 'buttonTooltipEvent';
		
		public static const ACTION_TYPE_IN:int = 0;
		public static const ACTION_TYPE_OUT:int = 1;
		
		public var x:int = 0;
		public var y:int = 0;
		
		public var tooltip: String = '';
		public var action:int = -1;
		
		public var targetObject:DisplayObject = null;
		
		public function ButtonTooltipEvent(_action:int, _targetObject:DisplayObject = null, _x:int=-1, _y:int=-1, _tooltip:String="", boobles:Boolean = true) 
		{
			super(EVENT_TYPE, boobles);
			
			x = _x;
			y= _y;
			tooltip = _tooltip;
			action = _action; 
			targetObject = _targetObject;
		}
	}
}
