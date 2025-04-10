package 
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author 
	 */
	public class RoundBarControl extends MovieClip 
	{
		public var markerAnim: MovieClip;
		public var heroPanelRound_bar: MovieClip;
		
		public function SetBarPosition(barPos:Number):void 
		{
			heroPanelRound_bar.gotoAndStop(barPos);
		}
		
		public function SetMarkerPosition(markPos:Number):void 
		{
			markerAnim.gotoAndStop(markPos);
		}
	}
	
}