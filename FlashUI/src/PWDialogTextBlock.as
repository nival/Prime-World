package  
{
	
	import flash.display.MovieClip;
	
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	
	import flash.text.TextFieldAutoSize;
	
	public class PWDialogTextBlock extends MovieClip 
	{		
	
	public var frame_cmp:PWFrame;
	
	private var TweenAlpha:Tween;
	private var TweenY:Tween;
	
	private var posY:int;
	
	private var time:int = 15;
	
	private const STARTLINE:int = 620;
	private const FRAMEROUND:int = 10;
	
		public function PWDialogTextBlock() 
		{
			TweenAlpha = new Tween(this, 'alpha', Strong.easeOut, 0, 1, time);
			TweenAlpha.stop();
			TweenY = new Tween(this, 'y', Strong.easeOut, this.y, this.y, time);
			TweenY.stop();
		}
		public function set Message(_txt:String):void
		{
			message_txt.text = _txt;
		}
		public function get START():int
		{
			return frame_cmp.y;
		}
		public function get END():int
		{
			return frame_cmp.y + frame_cmp.height - FRAMEROUND;
		}
		public function set Y(_pos:int):void
		{
			posY = _pos;
		}
		public function get Y():int
		{
			return posY;
		}
		public function Show()
		{
			posY = STARTLINE - this.END;

			TweenY.stop();
			TweenY.begin = this.y;
			TweenY.finish = posY;
			TweenY.start();
			TweenAlpha.start();
		}
	}
}
