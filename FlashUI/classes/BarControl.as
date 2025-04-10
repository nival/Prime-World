package 
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author 
	 */
	public class BarControl extends MovieClip 
	{
		public var markerAnim: MovieClip;
		public var heroPanelRound_bar: roundBarAnim;
		
		public function SetBarPosition(barPos:Number):void 
		{
			heroPanelRound_bar.roundBarAnimPosition(barPos);
			heroPanelRound_bar.chargePosition(barPos);
			
		}
		
		public function SetMarkerPosition(markPos:Number):void 
		{
			markerAnim.gotoAndStop(markPos);
		}
	}
	
}