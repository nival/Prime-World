package Components
{

	import flash.display.Sprite;
	import flash.display.BitmapData;
	import flash.geom.Rectangle;
	import flash.utils.getDefinitionByName;
	
	import src.ScaleBitmap;
	import flash.display.Bitmap;

	public class Frame extends Sprite
	{
		private var frame_bm:BitmapData;
		private var className:String;
		private var image:Class;
		
		private var Width:Number = 100;
		private var Height:Number = 100;
		
		private var scaleRectangle:Rectangle;

		private var myScaleBitmap:ScaleBitmap;
		
		public function Frame()
		{			
			super();
			setRectangle(10,10,80,80);//def
			Image = 'frame_png';
			configUI();
		}
		public function setRectangle(X:Number, Y:Number, Width:Number, Height:Number):void
		{
			scaleRectangle = new Rectangle(X,Y,Width,Height);
			return;
		}
		protected function configUI():void
		{
			var r:Number = rotation;
			rotation = 0;
			var w:Number = super.width;
			var h:Number = super.height;
			super.scaleX = super.scaleY = 1;
			rotation = r;
			setSize(w,h);
		}

		public function setSize(_width:Number, _height:Number):void
		{
			myScaleBitmap.setSize(_width, _height);
			Width = _width;
			Height = _height;
		}
		public function set Image(className:String)
		{	
			image = getDefinitionByName(className) as Class;
			
  			frame_bm = new image;
			myScaleBitmap = new ScaleBitmap(frame_bm);
			myScaleBitmap.scale9Grid = scaleRectangle;
			
			//08.06.12 TODO почему на тестах выдает ошибку, если компонент создается кодом а не вручную.
			if(numChildren > 0)
			{
				removeChildAt(0);
			}
			addChild(myScaleBitmap);
			setSize(Width, Height)
		}
	}
}