package Tutorial 
{
	import flash.display.MovieClip;
	import BaseClasses.BaseIconLoader;
	public class CinematicDialogPortrait extends MovieClip
	{
		public var icon:BaseIconLoader;
		public var flshFX_mc:MovieClip;
		private var _currentIcon:String = "";
		
		public function set Icon(value:String):void
		{
			if (_currentIcon != value) 
			{
				flshFX_mc.gotoAndPlay(2);
			}
			
			_currentIcon = value;
			
			icon.SetIcon("");
			icon.SetIcon(value);
		}
	}

}