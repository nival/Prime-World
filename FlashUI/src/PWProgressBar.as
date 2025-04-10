package  {
	
	import flash.display.MovieClip;
	import flash.display.Bitmap;
	import flash.display.Shape;
	
	
	public class PWProgressBar extends PWFrame
	{		
		public function PWProgressBar() 
		{
		}
		override public function configure():void
		{
			line_mc.gotoAndStop(100);

			image = getChildAt(0) as Bitmap;			
			setScaleBitmap(image);
				
			image = getChildAt(2) as Bitmap;			
			setScaleBitmap(image);
		}
		override public function reSize()
		{
			line_mc.width = Width-2;
			line_mc.height = Height-2;
		}
	}
}
