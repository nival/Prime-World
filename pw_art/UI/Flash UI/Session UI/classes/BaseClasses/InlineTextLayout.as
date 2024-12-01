package BaseClasses 
{
	import flash.display.DisplayObject;
	import flash.geom.Point;
	import flash.text.TextField;
	
	// TODO: управление способом выравнивания ?
	internal class InlineTextLayout
	{
		private var _elements:Array = new Array();
		private var _spacing:Number = 2;
		
		private var _min:Point = null;
		private var _max:Point = null;
		
		private var _guide:DisplayObject;
		
		public function InlineTextLayout(guide:DisplayObject = null)
		{
			_guide = guide;
		}
		
		public function Add(e:TextField):void
		{
			if (e == null)
				return;
				
			if (_elements.indexOf(e) >= 0)
				return;
				
			_elements.push(e);
			
			var x1:Number = e.x;
			var x2:Number = e.x + e.width;
			var y1:Number = e.y;
			var y2:Number = e.y + e.height;
			
			if (_elements.length == 1)
			{
				_min = new Point(x1, y1);
				_max = new Point(x2, y2);
			}
			
			if (_min.x > x1) _min.x = x1;
			if (_min.x > x2) _min.x = x2;
			if (_min.y > y1) _min.y = y1;
			if (_min.y > y2) _min.y = y2;
			
			if (_max.x < x1) _max.x = x1;
			if (_max.x < x2) _max.x = x2;
			if (_max.y < y1) _max.y = y1;
			if (_max.y < y2) _max.y = y2;
		}
		
		public function Layout():void
		{
			if (_elements.length == 0)
				return;
				
			var _textWidth:Number = _spacing * (_elements.length - 1);
			var _textHeight:Number = 0;				
			var _count:int = 0;
			
			var e:TextField;
			
			for each (e in _elements)
			{
				if (!e.visible)
					continue;
					
				e.width = Math.ceil(e.textWidth);
				e.height = Math.ceil(e.textHeight);
				
				_textWidth = _textWidth + e.width;
				_textHeight = Math.max(_textHeight, e.height);
				
				_count++;
			}
			
			if (_count == 0)
				return;
				
			var _area_x:Number = (_min.x);
			var _area_y:Number = (_min.y);
			var _area_w:Number = (_max.x - _min.x);
			var _area_h:Number = (_max.y - _min.y);
			
			if (_guide != null)
			{
				_area_x = 0;
				_area_w = _guide.width;
			}
			
			var _x:Number = _area_x + 0.5 * (_area_w - _textWidth);
			var _y:Number = _area_y + 0.5 * (_area_h - _textHeight) + _textHeight;
			
			for each (e in _elements)
			{
				if (!e.visible)
					continue;
				
				e.x = _x;
				e.y = _y - e.height;
				
				_x += e.width;
				_x += _spacing;
			}
		}
		
		public function set Spacing(value:Number):void
		{
			if (_spacing == value)
				return;
				
			_spacing = value;
			
			Layout();
		}
	}
}