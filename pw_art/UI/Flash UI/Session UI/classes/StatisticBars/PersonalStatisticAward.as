package StatisticBars
{
	import fl.transitions.easing.Strong;
	import fl.transitions.Tween;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.utils.Timer;
	
	import BaseClasses.BaseIconLoader;
	
	public class PersonalStatisticAward extends Titles
	{
		public var sumHeroAward:TextField;
		public var ID:int;
		public var PALight_mc:MovieClip;
		
		public function set Count(count:int):void
		{
			PALight_mc.visible = false;
			sumHeroAward.mouseEnabled = false;
			sumHeroAward.text = count.toString();
			sumHeroAward.visible = count > 1;
		}
		
		override protected function OnOut(e:MouseEvent):void 
		{
			FSCommands.Send(FSCommands.AWARD_TOOLTIP, FSCommands.TOOLTIP_HIDE+ID);
		}
		
		override protected function OnOver(e:MouseEvent):void 
		{
			FSCommands.Send(FSCommands.AWARD_TOOLTIP, FSCommands.TOOLTIP_SHOW+ID);
		}
		
		public function set IsPremium(value:Boolean):void 
		{
			PALight_mc.visible = value;
		}
	}
}