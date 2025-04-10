package  {
	
	import flash.display.MovieClip;
	import flash.display.Bitmap;
	import flash.display.Shape;
	
	public class PWScroll extends PWFrame 
	{		
		public function PWScroll() 
		{
		}
		override public function configure():void
		{
			image = getChildAt(0) as Bitmap;			
			setScaleBitmap(image);
		}
		override public function reSize()
		{
			up_btn.x = (Width-up_btn.width)/2;
			down_btn.x = (Width+down_btn.width)/2;
			down_btn.y = Height-1;
			sliderPath_mc.height = Height - sliderPath_mc.y - down_btn.height;
		}
	}
}
