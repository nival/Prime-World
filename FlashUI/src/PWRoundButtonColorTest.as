package  
{
	
	import flash.display.MovieClip;
	import flash.geom.ColorTransform;
	import flash.utils.getDefinitionByName;
	import flash.display.BitmapData;
	import flash.display.Bitmap;
	
	public class PWRoundButtonColorTest extends PWButton
	{
		private var blank:int = 0xFFFFFF;
		private var blue:int = 0x13B4FF;
		private var red:int = 0xB80004;
		private var yellow:int = 0xffff00;
		private var green:int = 0x00FF33;
		
		private var color:int;
		private var colorTransform:ColorTransform;
		
		private var ico:Class;
		private var ico_bm:Bitmap;
		
		public function PWRoundButtonColorTest() 
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
		public function set Ico(_ico:String)
		{
			if (_ico == 'none')
			return;
			
			if(ico_bm)
			{
				ico_mc.removeChild(ico_bm);
			}
			
			ico = getDefinitionByName(_ico) as Class;
			var ico_bmd:BitmapData = new ico;
			ico_bm = new Bitmap(ico_bmd);
			ico_bm.x = (ico_mc.width - ico_bm.width)/2;
			ico_bm.y = (ico_mc.height - ico_bm.height)/2
			ico_mc.addChild(ico_bm);
		}
	}
}
