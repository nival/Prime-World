package  {
	
	import flash.display.MovieClip;
	
	
	public class HeroFrame extends MovieClip 
	{
		
		
		public function HeroFrame()
		{
			glow_mc.stop();
		}
		public function heroGlow():void
		{
			glow_mc.play();
		}
	}
}
