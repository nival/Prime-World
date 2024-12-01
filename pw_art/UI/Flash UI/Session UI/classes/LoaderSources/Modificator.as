package LoaderSources 
{
	import flash.display.MovieClip;
	import BaseClasses.BaseIconLoader;
	import flash.events.MouseEvent;
	public class Modificator extends MovieClip
	{
		public var img:BaseIconLoader;
		private var _id:int;
		public function Modificator() 
		{			
			this.addEventListener(MouseEvent.MOUSE_OVER, OnMouseOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, OnMouseOut);
		}
		
		private function OnMouseOut(e:MouseEvent):void 
		{
			FSCommands.Send(FSCommands.ModeDescriptionTooltip,FSCommands.TOOLTIP_HIDE + _id);
		}
		
		private function OnMouseOver(e:MouseEvent):void 
		{
			FSCommands.Send(FSCommands.ModeDescriptionTooltip,FSCommands.TOOLTIP_SHOW + _id);
		}
		
		public function SetData(id:int,iconPath:String) 
		{
			img.SetIcon(iconPath);
			_id = id;
		}
		
	}

}