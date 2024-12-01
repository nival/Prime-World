package StatisticBars
{
	
	import Datas.PlayerStatisticData;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	//import flash.utils.getDefinitionByName;
	
	import Components.ButtonStandart;
	import BaseClasses.BaseDragObject;
	import Events.WindowVisibleControllerEvent;
	import Events.DetailedStatisticMateEvent;
	
	public class StatisticsBar extends BaseDragObject
	{
		public var allStats_mc:CurrentGameStatistics;
		public var buttonStatClose:ButtonStandart;
		public var header_txt:TextField;
		
		public function StatisticsBar()
		{	
			addEventListener(Event.ADDED_TO_STAGE, AddedToStage);
			addEventListener(DetailedStatisticMateEvent.EVENT_TYPE, StopEvent);
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);

		}
		
		private function FillLocalization(e:Event):void
		{
			header_txt.text = Localization.StatisticBar_HeaderText;
			buttonStatClose.LocalizeText = Localization.StatisticBar_CloseBtnLabel;
		}		
		private function StopEvent(e:DetailedStatisticMateEvent):void
		{
			e.stopPropagation();
		}
		
		public function get CurrentGameStatistic():CurrentGameStatistics
		{	
			return allStats_mc;
		}
		
		override public function AddedToStage(e:Event):void
		{	
			super.AddedToStage(e);
			buttonStatClose.addEventListener(MouseEvent.CLICK, CloseButtonClick);
			
			this.x = (stage.stageWidth - this.width) / 2;
			this.y = (stage.stageHeight - this.height) / 2;
			startPozition.x = this.x;
			startPozition.y = this.y;
		}
		
		public function SetPveBacks( winImage:String, normal:String,  looseImage:String):void 
		{
			allStats_mc.SetPveBacks(winImage, normal, looseImage)

		}
		
		private function UpdatePveBack():void 
		{
			
		}
		
		private function CloseButtonClick(e:MouseEvent):void
		{
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN_CLOSE,WindowIndex));
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			if (!wasDragged)
			{
				this.x = (stage.stageWidth - this.width) / 2;
				this.y = (stage.stageHeight - this.height) / 2;
				this.x = Math.floor(this.x);
				this.y = Math.floor(this.y);
			}
		}
	}
}
