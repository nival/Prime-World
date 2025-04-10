package 
{
	import flash.display.MovieClip;
	
	/**
	 * ...
	 * @author 
	 */
	public class roundBarAnim extends MovieClip 
	{
		public var charge_mc:MovieClip;
		public var roundBar_mc:MovieClip;
		
		
		public function roundBarAnimPosition (animPos:Number):void 
		{
			roundBar_mc.gotoAndStop(animPos);
		}
		
		public function chargePosition(chargePos:Number):void 
		{
			charge_mc.gotoAndPlay(chargePos*3);
		}
	}
}