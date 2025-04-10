package 
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	

	public class ProduceCash extends MovieClip
	{
		public	var	silver_txt:TextField;
		
		public function CashInit(frame:Number, cost:int):void
		{
			this.gotoAndStop(frame);
			silver_txt.text = cost.toString();
		}
	}
	
}