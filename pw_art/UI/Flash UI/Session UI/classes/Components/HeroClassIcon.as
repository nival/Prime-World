package Components 
{
	import BaseClasses.BaseIconLoader;
	import flash.display.MovieClip;
	public class HeroClassIcon extends MovieClip
	{
		public var sign:BaseIconLoader;
		
		public function HeroClassIcon() 
		{
			this.visible = false;
		}
		
		public function SetClassIcon(classIcon:String):void 
		{
			sign.SetIcon(classIcon);
			visible = true;
		}
		
	}

}