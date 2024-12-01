package Components
{
	import flash.display.DisplayObject;
	import flash.events.MouseEvent;
	import src.WButton;
	import src.ButtonTooltipEvent;
	import flash.geom.Point;
	import flash.display.MovieClip;
	
	public class TooltipButton extends WButton
	{
		private var globalPoint:Point;
		private var tooltip:String = '';
		private var targetObject:DisplayObject = null;
		
		public var coolDown_mc:MovieClip;
		
		override protected function OnOut(e:MouseEvent):void 
		{
			super.OnOut(e);
			if (tooltip.length == 0) return;
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
		}
		
		override protected function OnOver(e:MouseEvent):void 
		{
			super.OnOver(e);
			globalPoint = TargetObject.localToGlobal(new Point());
			if (tooltip.length == 0) return;
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, TargetObject, globalPoint.x, globalPoint.y, tooltip));
		}
		
		public function set Tooltip(_tooltip:String)
		{
			tooltip = _tooltip;
		}
		public function get Tooltip():String
		{
			return tooltip;
		}
		
		public function set TargetObject(value:DisplayObject):void
		{
			targetObject = value;
		}
		
		public function get TargetObject():DisplayObject
		{
			if (targetObject != null)
				return targetObject;
			
			if (UpVisObj != null)
				return UpVisObj;
			
			return this;
		}
	}
}