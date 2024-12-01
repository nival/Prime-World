package ContMenu 
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.text.TextField;
	import src.WButton;
	public class BaseContextMenuButton extends MovieClip
	{
		public var label:TextField;
		public var backBtn:WButton;
		
		public function BaseContextMenuButton() 
		{
			label.mouseEnabled = false;
			backBtn.addEventListener("Up", ButtonPressed);
		}
		
		protected function ButtonPressed(e:Event):void 
		{
			
		}
		
		public function GetHeight():Number
		{
			return label.height;
		}
	}

}