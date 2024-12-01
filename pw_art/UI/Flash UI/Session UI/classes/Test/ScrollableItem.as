package Test 
{
	import Interfaces.IScrollableObject;
	import flash.display.MovieClip;
	public class ScrollableItem extends MovieClip implements IScrollableObject
	{
		
		public function get ScrollableHight():Number 
		{
			return this.height;
		}
		
		public function get StepSize():Number 
		{
			return 5;
		}
		
		public function get ActualHeight():Number 
		{
			return 80;
		}
		
		public function get TopMargin():Number 
		{
			return 0;
		}
		
		public function get BottomMargin():Number 
		{
			return 0;
		}		
	}

}