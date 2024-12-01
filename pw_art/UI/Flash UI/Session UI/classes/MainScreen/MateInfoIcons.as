package MainScreen
{
	import flash.display.MovieClip;
	import flash.utils.getDefinitionByName;
	import flash.display.Bitmap;
	public class MateInfoIcons extends MovieClip
	{
		private var iconName:String = "none";
		
		public function MateInfoIcons():void
		{
			this.stop();
			this.mouseEnabled = false;
		}
		
		public function set Icon(value:String):void
		{
			if(this.numChildren!=0)
				this.removeChildAt(0);
			
			if (value == "none")return;
			
			iconName = value;
			
			var image:Class = getDefinitionByName(iconName) as Class;
			this.addChild(new Bitmap(new image));
			
		}
		public function get Icon():String
		{
			return iconName;
		}		
	}
	
	
}