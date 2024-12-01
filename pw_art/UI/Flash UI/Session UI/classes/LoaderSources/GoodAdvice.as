package LoaderSources 
{
	import BaseClasses.BaseResizableObject;
	import Components.Frame;
	import Components.PWFrame;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	
	public class GoodAdvice extends BaseResizableObject 
	{
		public var txt:TextField;
		public var frame:PWFrame;
		
		//public var back:MovieClip;
		public var tipExclamation: MovieClip;
		
		private var  textOffset:Number = 15;
		public function GoodAdvice() 
		{
			visible = false;
			txt.autoSize = TextFieldAutoSize.LEFT;
		}
		
		public function SetAdvice(adviceText:String):void
		{
			visible = adviceText.length != 0;
			txt.text = adviceText;
			txt.x = frame.x + (frame.width - txt.width - tipExclamation.width) / 2;
			frame.setSize(txt.width + textOffset * 2 + tipExclamation.width, txt.height + textOffset * 2);
			txt.y = frame.y + (frame.height - txt.height) / 2;
			tipExclamation.y = (frame.height - tipExclamation.height) / 2;
			tipExclamation.x = frame.width - tipExclamation.width - textOffset;
			frame.x = txt.x - textOffset;
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			this.x = (stage.stageWidth - this.width) / 2;
			this.y = stage.stageHeight - frame.height * scale + textOffset / 2;
		}
	}
}