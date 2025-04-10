package 
{
	import flash.display.MovieClip;
	import flash.text.TextField;
	
	/**
	 * ...
	 * @author 
	 */
	public class priceClass extends MovieClip 
	{
		public var icon:MovieClip;
		public var cost_txt:TextField;
		
		public function priceClass()
		{
			stop();
		}
		
		public function SetCost(resourceData:ResourceData):void 
		{
			icon.gotoAndStop(resourceData.ResourceType);
			cost_txt.text = resourceData.Cost.toString();
		}
	}
	
}