package Components
{

	import flash.display.Sprite;
	import flash.display.BitmapData;
	import flash.geom.Rectangle;
	import flash.utils.getDefinitionByName;
	
	import src.ScaleBitmap;
	import flash.display.Bitmap;

	public class FrameChat extends Sprite
	{
		private var _framePng:BitmapData;
		private var image:Class;

		private var myScaleBitmap:ScaleBitmap;
		
		public function FrameChat()
		{			
			super();
			setFrame();
			configUI();
		}
		protected function configUI():void
		{
			var r:Number = rotation;
			rotation = 0;
			var w:Number = super.width;
			var h:Number = super.height;
			super.scaleX = super.scaleY = 1;
			setSize(w,h);
			rotation = r;
		}

		public function setSize(_width:Number, _height:Number):void
		{
			myScaleBitmap.setSize(_width, _height);
		}
		public function setFrame(tooltip:Boolean = false)
		{
					
			removeChildAt(0);
			if(!tooltip)
			{
				image = getDefinitionByName('frameChat_png') as Class;
  				_framePng = new image;
			}
			if(tooltip)
			{
				image = getDefinitionByName('frameTooltip_png') as Class;
				_framePng = new image;
			}

			myScaleBitmap = new ScaleBitmap(_framePng);
			myScaleBitmap.scale9Grid = new Rectangle(10,10,80,80);
			addChild(myScaleBitmap);
		}
	}
}