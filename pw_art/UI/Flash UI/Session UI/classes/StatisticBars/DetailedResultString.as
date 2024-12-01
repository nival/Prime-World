package StatisticBars
{
	import Controllers.TextFieldFormater;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	
	import BaseClasses.BaseIconLoader;
	
	public class DetailedResultString extends MovieClip
	{
		public var resultCount:TextField;
		public var resultName:TextField;
		private var icon:BaseIconLoader;
		
		private var resultFormatedCount:TextFieldFormater

		public function DetailedResultString()
		{
			resultFormatedCount = new TextFieldFormater(resultCount);
			resultCount.autoSize = TextFieldAutoSize.CENTER;
			icon = new BaseIconLoader();
			icon.ico_ld.name = 'DetailedIcoLoader';
			
			this.addChild(icon);
			var index1:int = this.getChildIndex(icon);
			var index2:int = this.getChildIndex(resultCount);
			if (index1 > index2)
				swapChildrenAt(index1, index2);
		}
		
		public function SetResultData(path:String,_resultName:String, count:int):void
		{
			icon.SetIcon(path);
			resultName.text = _resultName;
			resultFormatedCount.SetFormatedNumber(count);
		}
		
	}
}