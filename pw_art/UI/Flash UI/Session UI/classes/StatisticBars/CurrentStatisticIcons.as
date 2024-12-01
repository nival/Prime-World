package StatisticBars
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import src.ButtonTooltipEvent;
	
	public class CurrentStatisticIcons extends MovieClip
	{
		private var tooltip:String;
		public function CurrentStatisticIcons()
		{
			this.addEventListener(MouseEvent.MOUSE_OVER, onOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, onOut);
		}
		
		private function onOver(e:MouseEvent):void
		{
			var point:Point = this.localToGlobal(new Point());
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, this, point.x,point.y, tooltip));	
		}
		private function onOut(e:MouseEvent):void
		{
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));	
		}
		
		public function set Tooltip(value:String):void
		{
			tooltip = value;
		}
		
		public function get Tooltip():String
		{
			return tooltip;
		}
	}
}