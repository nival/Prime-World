package BaseClasses
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.geom.Rectangle;
	
	import src.ScaleBitmap;
	import src.WButton;

	public class BaseScrollButton extends MovieClip
	{
		public var button_mc:WButton;
		
		
		
		public function BaseScrollButton()
		{
			var xOffset:int = 1;
			var yOffset:int = 2;
			
			var rec:Rectangle = new Rectangle(xOffset,yOffset,Math.max(0,int(button_mc.width)) - xOffset*2, Math.max(0,int(button_mc.height) - yOffset*2));
			
			button_mc.ConvertBitmapToScaleBitmap(rec);
		}

		public function setSize(_width:Number, _height:Number):void
		{
			button_mc.SetScaleBitmapSizes(_width, _height);
		}
		
		public function set Enable(value:Boolean):void
		{
			button_mc.Enable = value;
		}
	}
}