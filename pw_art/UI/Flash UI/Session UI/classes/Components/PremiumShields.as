package Components 
{
	import BaseClasses.TooltipSender;
	import flash.display.MovieClip;
	import Enums.EFraction;
	import flash.events.Event;
	import LoaderSources.LoaderLocalization;
	public class PremiumShields extends TooltipSender
	{
		private var _playerName:String;
		private var localisationText:String = "";
		public function PremiumShields()
		{
			stop();
			visible = false;
			localisationText = LoaderLocalization.PremiumAccountTooltip;
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
				
			if (LoaderLocalization.CompleteEventDispatcher != null)
				LoaderLocalization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLoadingScreenLocalization);
		}
		
		private function FillLoadingScreenLocalization(e:Event):void 
		{
			localisationText = LoaderLocalization.PremiumAccountTooltip;
			SetTooltip(localisationText, _playerName);
		}
		
		private function FillLocalization(e:Event):void 
		{
			localisationText = Localization.PremiumAccountTooltip;
			SetTooltip(localisationText, _playerName);
		}
		
		
		public function SetPremium(isPremium:Boolean, fraction:int,playerName:String):void
		{
			_playerName = playerName;
			//visible = isPremium&&(fraction==EFraction.HUMAN_FACTION||fraction == EFraction.ELF_FACTION);
			gotoAndStop(fraction == EFraction.HUMAN_FACTION?1:2);
			
			SetTooltip(localisationText, playerName);
		}
		
		private function SetTooltip(tooltip:String,playerName:String):void 
		{
			if ( tooltip.indexOf("{0}") == -1)
				return;
			
			var tooltipText:String = tooltip.replace('{0}', playerName);	
			TooltipText = tooltipText;
			
			SetTooltip(tooltipText, playerName);
		}
	}

}