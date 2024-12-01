package StatisticBars
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.geom.Point;
	import flash.text.TextField;
	
	import Interfaces.IScrollableObject;
	
	public class DetailStatResults extends MovieClip implements IScrollableObject
	{
		private var startPoint:Point = new Point(15, 15);
		private var startYPosition:int; 
		private var verticalGap:int = 30;
		private var results:Array = [];
		private var scrollableHight:Number;
		private var actualHeight:Number;
		private var back:Shape;
		
		public function DetailStatResults() 
		{
			startYPosition = startPoint.y;
			actualHeight = this.height;
			back = this.getChildAt(0) as Shape;
		}
		
		public function AddResult(resultIcon:String, resultCount:int, resultName:String):void
		{
			for (var i:int = 0; i < results.length; i++)
			{
				if (results[i].visible == false)
				{
					results[i].SetResultData(resultIcon, resultName, resultCount);
					results[i].visible = true;
					scrollableHight = results[i].y + results[i].height;
					return;
				}
			}
			
			var result:DetailedResultString = new DetailedResultString();
			result.SetResultData(resultIcon, resultName, resultCount);
			result.x = startPoint.x;
			result.y = startYPosition;
			this.addChild(result);
			startYPosition += verticalGap;
			
			scrollableHight = result.y + result.height;
			
			results.push(result);
			
			if (back != null)
			{
				scrollableHight < actualHeight ? back.height = actualHeight : back.height = scrollableHight;
			}
		}
		
		public function ResetToStartState():void
		{
			for (var i:int = 0; i < results.length; i++)
				results[i].visible = false;
		}
		
		/* INTERFACE Interfaces.IScrollableObject */
				
		public function get TopMargin():Number 
		{
			return 0;
		}
		
		public function get BottomMargin():Number 
		{
			return 0;
		}
		
		public function get ScrollableHeight():Number
		{
			return scrollableHight;
		}
		
		public function get StepSize():Number
		{
			return verticalGap;
		}
		
		public function get ActualHeight():Number
		{
			return actualHeight;
		}
	}
}