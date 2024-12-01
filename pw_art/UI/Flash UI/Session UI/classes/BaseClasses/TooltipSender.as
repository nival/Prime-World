package BaseClasses 
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import src.ButtonTooltipEvent;
	public class TooltipSender extends MovieClip
	{
		private var tooltipShower:MovieClip;
		private var tooltipText:String = "";
		private var isOver:Boolean = false;
		private var mouseDowns:uint = 0;
		
		private var _visible:Boolean = false;
		
		public function TooltipSender(sender:MovieClip = null)
		{
			tooltipShower = (sender == null) ? this : sender;
			
			tooltipShower.addEventListener(MouseEvent.MOUSE_OVER, OnMouseOver);
			tooltipShower.addEventListener(MouseEvent.MOUSE_OUT, OnMouseOut);
			tooltipShower.addEventListener(MouseEvent.MOUSE_MOVE, OnMouseMove);
			tooltipShower.addEventListener(MouseEvent.MOUSE_DOWN, OnMouseDown);
			tooltipShower.addEventListener(MouseEvent.MOUSE_UP, OnMouseUp);
		}
		
		private function OnMouseMove(e:MouseEvent):void 
		{
			DoUpdate();
		}
		
		private function OnMouseOut(e:MouseEvent):void 
		{
			isOver = false;
			
			DoHide();
		}
		
		private function OnMouseOver(e:MouseEvent):void 
		{
			mouseDowns = 0;
			
			isOver = true;
			
			DoShow();
		}
		
		private function OnMouseDown(e:MouseEvent):void
		{
			++mouseDowns;
			
			if (mouseDowns == 1)
				DoHide();
		}
		
		private function OnMouseUp(e:MouseEvent):void
		{
			if (mouseDowns == 0)
				return;
			
			--mouseDowns;
			
			if (mouseDowns == 0)
				DoShow();
		}
		
		private function DoShow():void
		{
			if (tooltipText == "")
				return;
			if (!isOver)
				return;
			if (mouseDowns > 0)
				return;
				
			if (_visible == true)
				return;
				
			_visible = true;
			
			var point:Point;
			
			point = new Point(tooltipShower.mouseX, tooltipShower.mouseY);
			point = tooltipShower.localToGlobal(point);
			
			tooltipShower.dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, tooltipShower, point.x, point.y, tooltipText));
		}
		
		private function DoHide():void
		{
			if (_visible == false)
				return;
			
			_visible = false;
			
			tooltipShower.dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
		}
		
		private function DoUpdate():void
		{
			DoHide();
			DoShow();
		}
		
		public function get TooltipText():String 
		{
			return tooltipText;
		}
		
		public function set TooltipText(value:String):void 
		{
			tooltipText = value;
		}
		
	}

}