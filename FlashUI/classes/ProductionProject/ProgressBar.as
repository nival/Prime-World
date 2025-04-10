package 
{
	import flash.display.MovieClip;
		
	
	public class  ProgressBar extends MovieClip
	{
		public	var line_mc: MovieClip;
		
		public function StopProgress(frame:Number):void
		{
			line_mc.gotoAndStop(frame);
		}
	}	
}