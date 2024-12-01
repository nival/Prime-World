
package  {
	
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.display.Shape;
	
	public class Main extends MovieClip 
	{
		public function Main() 
		{
			var tooltip:ToolTip = new ToolTip(this);
			addChild(tooltip);
			tooltip.tooltip = 'это тестовый тултип. Он отображает текст'
			tooltip.target = new Shape();
			
			tooltip.scaleX = 1;
			tooltip.scaleY = 1;
			tooltip.ShowTooltip();
			
		}
	}
	
}
