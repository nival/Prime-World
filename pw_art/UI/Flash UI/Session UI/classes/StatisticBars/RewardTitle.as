package StatisticBars 
{
	import flash.display.MovieClip;
	import flash.text.TextField;

	public class RewardTitle extends MovieClip
	{
		public var headerText:TextField;
		
		public function SetText(title:String):void
		{
			if (headerText == null)
				return;
			
			headerText.text = title;
		}
	}

}