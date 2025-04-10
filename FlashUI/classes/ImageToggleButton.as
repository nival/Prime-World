package 
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import ImgLoader;
	
	public class ImageToggleButton extends ToggleButton
	{
	//	private var label_txt:TextField;
		public var ico:ImgLoader ;
		private var iconName:String ;
		
		public function SetImg(path:String):void
		{
			trace("ico "+ico);
			
			ico.SetImage(path);
		}
	}	
}