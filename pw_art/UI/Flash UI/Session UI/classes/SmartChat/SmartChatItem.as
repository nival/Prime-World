package classes.SmartChat
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	
	public class SmartChatItem extends MovieClip 
	{
		private var _id:uint = 0xFFFFFFFF;
		
		public var key_txt:TextField;
		public var label_txt:TextField;
		
		public function SmartChatItem() 
		{
			super();
			
			mouseEnabled = false;
			mouseChildren = false;
			
			label_txt.autoSize = TextFieldAutoSize.LEFT;
		}
		
		public function get textHeight():Number
		{
			return Math.ceil(Math.max(key_txt.textHeight, label_txt.textHeight));
		}
		
		public function set id(value:uint):void
		{
			_id = value;
		}
		
		public function get id():uint
		{
			return _id;
		}
	}
}