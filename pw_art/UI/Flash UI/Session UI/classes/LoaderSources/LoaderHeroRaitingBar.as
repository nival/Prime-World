package LoaderSources 
{
	import BaseClasses.BaseIconLoader;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.text.TextField;
	import src.ButtonTooltipEvent;
	public class LoaderHeroRaitingBar extends MovieClip
	{
		public var raitingBack:MovieClip;
		public var raiting_txt:TextField;
		public var eliteHero_mc:BaseIconLoader;
		
		private var tooltipText:String;
		
		private var ourPlayerTooltipTemplate:String;
		private var teamMateTooltipTemplate:String;
		
		public function LoaderHeroRaitingBar()
		{
			this.visible = false;
			
			addEventListener(MouseEvent.MOUSE_OVER, OnRaitingOver);
			addEventListener(MouseEvent.MOUSE_OUT, OnRaitingOut);
			
			ourPlayerTooltipTemplate = LoaderLocalization.OurPlayerRaitingTooltip;
			teamMateTooltipTemplate = LoaderLocalization.TeamMateRaitingTooltip;
			raiting_txt.mouseEnabled = false;
			
			if (LoaderLocalization.CompleteEventDispatcher != null)
					LoaderLocalization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, OnFillLocalization);
		}
		
		private function OnFillLocalization(e:Event):void 
		{
			ourPlayerTooltipTemplate = LoaderLocalization.OurPlayerRaitingTooltip;
			teamMateTooltipTemplate = LoaderLocalization.TeamMateRaitingTooltip;
		}
		
		public function SetHeroRaiting(isItOurHero:Boolean,raiting:int, deltaWin:Number, deltaLose:Number, rankIcon:String, rankTooltip:String):void 
		{
			this.visible = true;
			
			raiting_txt.text = raiting.toString();
			
			eliteHero_mc.SetIcon(rankIcon);
			
			tooltipText = rankTooltip + (isItOurHero? ourPlayerTooltipTemplate : teamMateTooltipTemplate);
			tooltipText = tooltipText.replace('{0}', ((Math.abs(int(deltaWin*10)))/10).toString());
			tooltipText = tooltipText.replace('{1}', ((Math.abs(int(deltaLose*10)))/10).toString());
		}
	
		private function OnRaitingOver(e:MouseEvent):void 
		{
			var globalPoint:Point = this.localToGlobal(new Point());
			if (tooltipText.length == 0) return;
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, this, globalPoint.x, globalPoint.y, tooltipText));
		}
		
		private function OnRaitingOut(e:MouseEvent):void 
		{
			if (tooltipText.length == 0) return;
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
		}
	}

}