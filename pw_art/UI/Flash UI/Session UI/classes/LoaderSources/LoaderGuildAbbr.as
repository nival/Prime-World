package LoaderSources 
{
	import Components.PWFrame;
	import Controllers.TextFieldFormater;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;

	public class LoaderGuildAbbr extends MovieClip
	{
		
		public var frame:MovieClip;
		public var abbr_txt:TextField;
		
		private var _textOffset:Number;
		private var _initialTextWidth:Number;
		private var _frameCenterPos:Number;
		private var _textInitialXPos:Number;
		private var nameText:TextFieldFormater;
		
		public function LoaderGuildAbbr()
		{
			abbr_txt.autoSize = TextFieldAutoSize.NONE;
			_textInitialXPos = abbr_txt.x;
			_textOffset = (frame.width - abbr_txt.width) / 2;
			_initialTextWidth = abbr_txt.textWidth;
			_frameCenterPos = frame.x + frame.width / 2;
			this.visible = false;
			nameText = new TextFieldFormater(abbr_txt);
		}
		
		public function get guildName():String 
		{
			return nameText.Text;
		}
		
		public function set guildName(value:String):void 
		{
			if (value == null || value == "") return;
			nameText.Text = value;
			frame.x = _frameCenterPos - frame.width / 2;
			if (this.visible = true)
			parent.setChildIndex(this, parent.numChildren - 1);
		}
	}
}