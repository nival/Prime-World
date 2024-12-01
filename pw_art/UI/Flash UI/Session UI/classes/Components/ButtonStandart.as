package Components
{

	import Controllers.SoundController;
	import flash.display.MovieClip;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.geom.Rectangle;
	import flash.text.TextFieldAutoSize;

	import src.ScaleBitmap;
	import flash.text.TextField;
	import src.WButton;
	import src.Desaturate;
	import flash.events.Event;
	
	public class ButtonStandart extends MovieClip
	{
		private var isLocalized:Boolean = false;
		private var originalWidth:Number;
		private var originalHeight:Number;
		//reference
		public var label_txt:TextField;
		public var button_mc:WButton;

		public function ButtonStandart()
		{
			label_txt.height = label_txt.height-2;
			label_txt.mouseEnabled = false;
			label_txt.autoSize = TextFieldAutoSize.CENTER;
			
			var xOffset:int = 10;
			var yOffset:int = 7;
			
			var rec:Rectangle = new Rectangle(xOffset, yOffset, Math.max(0, int(button_mc.width - xOffset * 2)), Math.max(0, int(button_mc.height - yOffset * 2)));
			
			button_mc.ConvertBitmapToScaleBitmap(rec);
			
			configUI();
			
			button_mc.addEventListener("Up", OnUp);
		}
		
		private function OnUp(e:Event):void 
		{
			SoundController.PlaySound(SoundController.BUTTON_PRESS_BIG);
		}

		private function configUI():void
		{
			var r:Number = rotation;
			rotation = 0;
			originalWidth = super.width;
			originalHeight = super.height;
			super.scaleX = super.scaleY = 1;
			setSize(originalWidth,originalHeight);
			rotation = r;
		}
		
		private function setSize(_width:Number, _height:Number):void
		{
			button_mc.SetScaleBitmapSizes(_width, _height);
			
			label_txt.x = (button_mc.UpVisObj.width - label_txt.width)/2;
			label_txt.y = (button_mc.UpVisObj.height - (label_txt.height-2))/2;
		}
		
		public function set LocalizeText(value:String):void 
		{		
			label_txt.text = value;
			isLocalized = true;
		}
		
		public function set labelColor(_color:uint)
		{
			label_txt.textColor = _color;
		}

		public function get labelColor():uint
		{
			return label_txt.textColor;
		}
		public function set labelText(_text:String)
		{
			if (isLocalized) return;
			label_txt.text = _text;
		}
		public function get labelText():String
		{
			return label_txt.text;
		}

		public function disable():void
		{
			mouseChildren = false;
				
			button_mc.UpVisObj.visible = false;
			button_mc.OverVisObj.visible = false;
			button_mc.DownVisObj.visible = false;
			button_mc.DisableVisObj.visible = true;
			
			Desaturate.desaturate(button_mc);
		}

		public function enable():void
		{
			mouseChildren = true;
			button_mc.UpVisObj.visible = true;
			button_mc.OverVisObj.visible = false;
			button_mc.DownVisObj.visible = false;
			button_mc.DisableVisObj.visible = false;
			Desaturate.saturate(button_mc);
		}
		
		public function set EnableButton(value:Boolean):void
		{
			if (value)
				enable()
			else
				disable()
		}
		
		public function GetHeight():Number
		{
			return originalHeight;
		}
		
		public function GetWidth():Number 
		{
			return originalWidth
		}
	}
}