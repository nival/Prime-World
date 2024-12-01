package Strokes 
{
	import Strokes.Stroke;
	
	public class HeroOvertipStroke extends Stroke 
	{
		
		public function HeroOvertipStroke() 
		{
			
		}
		
		//время анимации
		override protected function get tutorialTweenDuration():Number
		{
			return 10;
		}
	}

}