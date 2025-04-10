package  
{
	
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
	
	public class PWRoundButtonColor extends MovieClip 
	{
		private var blank:int = 0xFFFFFF;
		private var blue:int = 0x13B4FF;
		private var red:int = 0xB80004;
		private var yellow:int = 0xffff00;
		private var green:int = 0x00FF33;
		
		
		private var color:int;
		private var colorTransform:ColorTransform;
		
		public function PWRoundButtonColor() 
		{
			colorTransform = back_mc.transform.colorTransform;
		}
		public function set Color(_color:String)
		{
			if(_color == 'blank')
			{
				color = blank;
			}
			if(_color == 'blue')
			{
				color = blue;
			}
			if(_color == 'red')
			{
				color = red;
			}
			if(_color == 'yellow')
			{
				color = yellow;
			}
			if(_color == 'green')
			{
				color = green;
			}
			colorTransform.redMultiplier = (color >> 16 & 255) / 255;
			colorTransform.greenMultiplier = (color >> 8 & 255) / 255;
			colorTransform.blueMultiplier = (color & 255) / 255;
			back_mc.transform.colorTransform = colorTransform;
			//trace(color)
		}
	}
}
