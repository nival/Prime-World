package Effects 
{
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	
	public class TargetZoneEffect extends Sprite 
	{
		private static const COLOR:uint = 0xFFFFFFFF;
		private static const THICKNESS:uint = 2;
		
		private var _color:uint = COLOR;
		private var _thickness:uint = THICKNESS;
		private var _radius:Number = 0;
		private var _shape:Shape = new Shape();
		private var _dirty:Boolean = true;
		
		public function TargetZoneEffect() 
		{
			super();
			
			addChild(_shape);
			
			mouseEnabled = false;
			mouseChildren = false;
			
			visible = false;
		}
		
		public function set Color(value:uint):void
		{
			if (value == 0)
				value = COLOR;
			
			if (value == _color)
				return;
			
			_color = value;
			_dirty = true;
		}
		
		public function set Thickness(value:uint):void
		{
			if (value == 0)
				value = THICKNESS;
			
			if (value == _thickness)
				return;
			
			_thickness = value;
			_dirty = true;
		}
		
		public function set Radius(value:Number):void
		{
			if (value < 1)
				value = 1;
			
			if (Math.abs(_radius - value) < 0.05)
				return;
			
			_radius = value;
			_dirty = true;
		}
		
		public function Update():void
		{
			if (_dirty)
			{
				_dirty = false;
				
				DoUpdateShape();
			}
		}
		
		private function DoUpdateShape():void
		{
			var rgb:uint = _color & 0x00FFFFFF;
			var a:uint = (_color >> 24) & 0xFF;
			
			_shape.graphics.clear();
			
			// almost invisible (alpha < 5%)
			if (a < 12)
				return;
			
			_shape.graphics.lineStyle(_thickness, rgb, Number(a) / 255.0);
			_shape.graphics.drawCircle(0, 0, _radius);
		}
	}

}