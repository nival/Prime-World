package EscMenu
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	public class TestInputText extends MovieClip
	{
		public var inputTXT:TextField;
		public var apply:MovieClip;
		
		public function TestInputText()
		{
		//	this.addEventListener(Event.ADDED_TO_STAGE, AddedToStage);
		//	function AddedToStage(e:Event):void{
		//		apply.addEventListener(MouseEvent.CLICK, Apply);
		//		apply.mouseChildren = false;
		//	}
		}
		
		private function Apply(e:MouseEvent):void
		{
			FSCommands.Send("PreferenceComponentsLoadPreset", inputTXT.text);
		}
	}
	
}