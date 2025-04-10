package  {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	
	public class TextToggleButton extends ToggleButton
	{
		public var tbText:TextField;
		
		public function TextToggleButton()
		{
			tbText.multiline = false;
			tbText.autoSize = TextFieldAutoSize.CENTER;
		}
		
		public function SetText(txt:String):void
		{
			tbText.text= txt;
		}
	}
}
