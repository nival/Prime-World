package Chat 
{
	import fl.transitions.easing.Strong;
	import fl.transitions.Tween;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.MouseEvent;
	public class ChatBarMouseCatcher extends Sprite
	{
		private var alphaTween:Tween;
		private var shape:Shape
		private var duration:Number = 1;
		
		public function ChatBarMouseCatcher() 
		{			
			shape = new Shape();

			shape.graphics.beginFill(0x22616B);
			shape.graphics.drawRect(0, 0, 3, 3);
			shape.graphics.endFill();
			shape.alpha = 0.9;
			
			addChild(shape);	
			this.alpha = 0;
			this.addEventListener(MouseEvent.MOUSE_OVER, OnMouseOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, OnMouseOut);
			
			alphaTween = new Tween(this, "alpha", Strong.easeOut, 0, 1, duration, true);
			alphaTween.stop();
			this.alpha = 0;
		}	
		
		private function OnMouseOut(e:MouseEvent):void 
		{
			alphaTween.stop();
			alphaTween.position = this.alpha;
			alphaTween.finish = 0;
			alphaTween.start();
		}
		
		private function OnMouseOver(e:MouseEvent):void 
		{
			alphaTween.stop();
			alphaTween.position = this.alpha;
			alphaTween.finish = 1;
			alphaTween.start();
		}
			
		public function SetSize(_width:Number, _height:Number):void
		{
			this.width = _width;
			this.height = _height;
		}
		
	}

}