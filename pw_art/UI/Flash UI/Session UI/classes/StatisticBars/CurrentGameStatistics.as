package StatisticBars
{
	
	import BaseClasses.BaseIconLoader;
	import Components.ScrollBar;
	import Datas.PlayerStatisticData;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	import Components.FormatedTimer;
	import Components.Frame;
	import Controllers.StatisticMateInfoController;
	
	public class CurrentGameStatistics extends MovieClip
	{	
		public static const HUMAN_FACTION:int = 1;
		public static const ELF_FACTION:int = 2;

		public var pointsElfs:TextField;
		public var pointsHumans:TextField;
		public var primeHumans:TextField;
		public var primeElfs:TextField;	
		
		public var frameSmall1_mc:Frame;
		public var frameSmall2_mc:Frame;
		public var frameTop_mc:Frame;
		public var percentHuman:TextField;
		public var percentElf:TextField;
		public var clock:FormatedTimer;
	//	public var clockNumber:TextField;
		public var TerrainDominate_mc:TerrainDominate;
		
		public var StatisticsHuman_mc:StatisticContainer;
		public var StatisticsElf_mc:StatisticContainer;
		
		public var doctScrollBar:ScrollBar;
		public var adornScrollBar:ScrollBar;
		
		public var humanPrime:CurrentStatisticIcons;
		public var elfPrime:CurrentStatisticIcons;
		public var humKills:CurrentStatisticIcons;
		public var elfKills:CurrentStatisticIcons;
		public var doctEmptyBack:BaseIconLoader;
		public var adornEmptyBack:BaseIconLoader;
		
		private var HumanTeamController:StatisticMateInfoController;
		private var ElfTeamController:StatisticMateInfoController;
		
		public var __exportedProperties : Array = ['MightTooltip','ScytheTooltip','FistTooltip','CupTooltip',];
		
		private var humanTextColor:uint = 0x3F91FD;
		private var elfTextColor:uint = 0xCD2500;
		private var humanKillsTextColor:uint = 0x3F91FD;
		private var elfKillsTextColor:uint = 0xCD2500;
		private var thousend:String;
		
		private var _winImage:String;
		private var _normalBack:String;
		private var _looseImage:String;
		
		private const NormalState:String = "Normal";
		private const WinState:String = "Win";
		private const LooseState:String = "Loose";
		
		private var currentState:String;
		private var ourId:int;
		public function CurrentGameStatistics()
		{
			currentState = NormalState;
			HumanTextColor = humanTextColor;
			ElfTextColor = elfTextColor;

			HumanKillsTextColor = humanKillsTextColor;
			ElfKillsTextColor = elfKillsTextColor;
			HumanTeamController = new StatisticMateInfoController(StatisticsHuman_mc);
			ElfTeamController = new StatisticMateInfoController(StatisticsElf_mc);
			
			MightTooltip = Localization.Tooltip_StatisticBarKillsIcon;
			ScytheTooltip = Localization.Tooltip_StatisticBarDeathsIcon;
			FistTooltip = Localization.Tooltip_StatisticBarAssistIcon;
			CupTooltip = Localization.Tooltip_StatisticBarScoreIcon;
			PrimeTooltip = Localization.Tooltip_StatisticBarPrimeIcon;
			PartyMarkerTooltip = Localization.Tooltip_FinalStatisticBar_PartyMarker;
			MuteTooltip = Localization.Tooltip_FinalStatisticBar_Mute;
			
			elfPrime.Tooltip = humanPrime.Tooltip = Localization.Tooltip_StatisticBarTeamPrimeIcon;
			elfKills.Tooltip = humKills.Tooltip = Localization.Tooltip_StatisticBarTeamKillsIcon;
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
		}
		
		private function FillLocalization(e:Event):void
		{
			MightTooltip = Localization.Tooltip_StatisticBarKillsIcon;
			ScytheTooltip = Localization.Tooltip_StatisticBarDeathsIcon;
			FistTooltip = Localization.Tooltip_StatisticBarAssistIcon;
			CupTooltip = Localization.Tooltip_StatisticBarScoreIcon;
			PrimeTooltip = Localization.Tooltip_StatisticBarPrimeIcon;
			PartyMarkerTooltip = Localization.Tooltip_FinalStatisticBar_PartyMarker;
			MuteTooltip = Localization.Tooltip_FinalStatisticBar_Mute;
			thousend = Localization.StatisticsThousendsIndificator;
			
			elfPrime.Tooltip = humanPrime.Tooltip = Localization.Tooltip_StatisticBarTeamPrimeIcon;
			elfKills.Tooltip = humKills.Tooltip = Localization.Tooltip_StatisticBarTeamKillsIcon;
		}
		
		public function set HumanTextColor(value:uint):void
		{
			humanTextColor = value;
			StatisticsHuman_mc.TextColors = humanTextColor
		}
		
		public function get HumanTextColor():uint
		{
			return humanTextColor;
		}
		
		public function set ElfTextColor(value:uint):void
		{
			elfTextColor = value;
			StatisticsElf_mc.TextColors = elfTextColor;
		}
		
		public function get ElfTextColor():uint
		{
			return elfTextColor;
		}
		
		public function set HumanKillsTextColor(value:uint):void
		{
			humanKillsTextColor = value;
			pointsHumans.textColor = humanKillsTextColor;
		}
		
		public function get HumanKillsTextColor():uint
		{
			return humanKillsTextColor;
		}
		
		public function set ElfKillsTextColor(value:uint):void
		{
			elfKillsTextColor = value;
			pointsElfs.textColor = elfKillsTextColor;
		}
		
		public function get ElfKillsTextColor():uint
		{
			return elfKillsTextColor;
		}
		
		
		public function set MightTooltip(value:String):void
		{
			StatisticsHuman_mc.MightTooltip = value;
			StatisticsElf_mc.MightTooltip = value;
		}
		
		public function get MightTooltip():String
		{
			return StatisticsHuman_mc.MightTooltip;
		}
		
		public function set ScytheTooltip(value:String):void
		{
			StatisticsHuman_mc.ScytheTooltip = value
			StatisticsElf_mc.ScytheTooltip = value
		}
		
		public function get ScytheTooltip():String
		{
			return StatisticsHuman_mc.ScytheTooltip;
		}
		
		public function set FistTooltip(value:String):void
		{
			StatisticsHuman_mc.FistTooltip = value;
			StatisticsElf_mc.FistTooltip = value;
		}
		
		public function get FistTooltip():String
		{
			return StatisticsHuman_mc.FistTooltip;
		}
		
		public function set CupTooltip(value:String):void
		{
			StatisticsHuman_mc.CupTooltip  = value;
			StatisticsElf_mc.CupTooltip  = value;
		}
		
		public function get CupTooltip():String
		{
			return StatisticsHuman_mc.CupTooltip;
		}		
		
		public function set PrimeTooltip(value:String):void
		{
			StatisticsHuman_mc.PrimeTooltip  = value;
			StatisticsElf_mc.PrimeTooltip  = value;
		}
		
		public function get PrimeTooltip():String
		{
			return StatisticsHuman_mc.PrimeTooltip;
		}		
		
		public function set PartyMarkerTooltip(value:String):void
		{
			StatisticsHuman_mc.PartyMarkerTooltip = value;
			StatisticsElf_mc.PartyMarkerTooltip = value;
		}
		
		public function set MuteTooltip(value:String):void
		{
			StatisticsHuman_mc.MuteTooltip = value;
			StatisticsElf_mc.MuteTooltip = value;
		}
		
		public function SetGameProgress(humanTerrain:Number, elfTerrain:Number, gameTime:int):void
		{
			TerrainDominate_mc.DwarfenTerrain = humanTerrain;
			TerrainDominate_mc.ElfenTerrain = elfTerrain;
		 
			var humTerr:Number = Math.round(100 * humanTerrain-0.5);
			var elfTerr:Number = Math.round(100 * elfTerrain-0.5);
			percentHuman.text = humTerr.toString()+"%";
			percentElf.text = elfTerr.toString()+"%";
			
			clock.Time = gameTime;
		}
					
		public function SetOurHero(heroID:int, fraction:int):void
		{
			HumanTeamController.OurHeroId = fraction == CurrentGameStatistics.HUMAN_FACTION? heroID: -1;
			ElfTeamController.OurHeroId = fraction == CurrentGameStatistics.ELF_FACTION? heroID: -1;
		}

		private function GetNewMateInfoStat(heroID:int,fraction:int,partyId:int):StatisticsBarPlayers
		{
			if (fraction == CurrentGameStatistics.HUMAN_FACTION)
			{
				return HumanTeamController.GenerateNewMateInfo(heroID,partyId);
			} 
			
			if (fraction == CurrentGameStatistics.ELF_FACTION)
			{
				return ElfTeamController.GenerateNewMateInfo(heroID,partyId);
			}	
			return null;
		}
		
		public function SetHeroIdentity(playerData:PlayerStatisticData):void
		{	
			var mateInfo:StatisticsBarPlayers =  GetMateInfoById(playerData.HeroId);  
			
			if (mateInfo == null)
				mateInfo = GetNewMateInfoStat(playerData.HeroId, playerData.Fraction,playerData.PartyID);
				
			if (mateInfo == null) return;
			
			mateInfo.SetPlayerData(playerData);

			doctEmptyBack.visible = HumanTeamController.IsEmpty();
			adornEmptyBack.visible = ElfTeamController.IsEmpty();
		}
		
		public function SetHeroStatus(heroID:int,visibleLevel:int, isVisible:Boolean, leftGame:Boolean, timeToRessurect:int):void
		{
			var mateInfo:StatisticsBarPlayers = GetMateInfoById(heroID);
			
			if (mateInfo == null) return;
			
			var isRessurecting:Boolean = timeToRessurect > 0;
			
			mateInfo.SetGreyMask(isRessurecting||!isVisible);
					
			mateInfo.SetDeathTimeOut(timeToRessurect);
						
			mateInfo.level = visibleLevel; 
		}
		
		public function SetHeroAgreedToPlaySameTeam(heroID:int, agreed:Boolean):void
		{
			var mateInfo:StatisticsBarPlayers = GetMateInfoById(heroID);
			
			if (mateInfo == null) return;
			
			mateInfo.party_mc.visible = agreed;
		}
		
		private function GetMateInfoById(id:int):StatisticsBarPlayers
		{
			if (HumanTeamController.DoesHeroExist(id))
				return HumanTeamController.GetMateInfo(id);
			
			if (ElfTeamController.DoesHeroExist(id))
				return ElfTeamController.GetMateInfo(id);
				
			return null;
		}
		
		public function SetHeroGameProgress(playerData:PlayerStatisticData ):void
		{
			var mateInfo:StatisticsBarPlayers = GetMateInfoById(playerData.HeroId);
			
			if (mateInfo == null) return;
			
			mateInfo.SetHeroGameProgress(playerData);
			
			SetTeamCountKills();
			SetTeamCountPrime();
			UpdateTeamCounterVisibility();
		}
		
		private function SetTeamCountPrime():void 
		{
			var humanPrime:int = StatisticsHuman_mc.GetTeamPrimeCount()
			var elfPrime:int = StatisticsElf_mc.GetTeamPrimeCount();
			
			primeHumans.text = GetPrimeCount(humanPrime);
			primeElfs.text = GetPrimeCount(elfPrime);
		}
		
		private function GetPrimeCount(prime:int):String 
		{
			if(prime<1000)
			{
				return prime.toString()
			}
			
			var result:int = int(prime / 100);
			
			return (result / 10)+thousend;
		}
		
		private function SetTeamCountKills():void
		{
			pointsHumans.text = StatisticsHuman_mc.GetTeamKillsCount().toString();
			pointsElfs.text = StatisticsElf_mc.GetTeamKillsCount().toString();
		}
		
		private function UpdateTeamCounterVisibility() : void
		{
			primeHumans.visible = humanPrime.visible = pointsHumans.visible = humKills.visible = percentHuman.visible = !HumanTeamController.IsEmpty();
			primeElfs.visible = elfPrime.visible = pointsElfs.visible = elfKills.visible = percentElf.visible = !ElfTeamController.IsEmpty();
		}
		
		public function ResetMates():void 
		{
			HumanTeamController.ResetMates();
			ElfTeamController.ResetMates();
		}
		
		public function OnHeroLeft(heroID:int,leaveType:int)
		{
			var mateInfo:StatisticsBarPlayers = GetMateInfoById(heroID);
			
			if (mateInfo == null) return;
			
			mateInfo.OnHeroLeft(leaveType);
		}
		
		public function SetFriendshipRelation(heroID:int, areFriends:Boolean,isPending:Boolean):void 
		{
			var mateInfo:StatisticsBarPlayers = GetMateInfoById(heroID);
			
			if (mateInfo == null) return;
			
			mateInfo.SetFriendshipRelation(areFriends,isPending);
		}
		
		public function SwitchPlayersToFinalStatistic():void 
		{
			StatisticsHuman_mc.SwitchPlayersToFinalStatistic();
			StatisticsElf_mc.SwitchPlayersToFinalStatistic();
			SetTeamCountPrime();
		}
		
		public function OnHeroReturn(id:int):void 
		{
			var mateInfo:StatisticsBarPlayers = GetMateInfoById(id);
			
			if (mateInfo == null) return;
			
			mateInfo.OnHeroReturn();
		}
			
		
		public function SetIgnoreStatus(id:int, ignore:Boolean):void 
		{
			var mateInfo:StatisticsBarPlayers = GetMateInfoById(id);
			
			if (mateInfo == null) return;
			
			mateInfo.HeroIgnored = ignore;
		}
		
		public function SetPveBacks(winImage:String, normal:String, looseImage:String):void 
		{
			_winImage = winImage;
			_normalBack = normal;
			_looseImage = looseImage;
			UpdatePveBack();
		}
		
		public function SetGameEnded(isVictory:Boolean):void 
		{
			currentState = isVictory? WinState:LooseState;
			
			UpdatePveBack();
		}
		
		public function SwitchToSpectatorMode():void 
		{
			StatisticsHuman_mc.SwitchToSpectetorMode();
			StatisticsElf_mc.SwitchToSpectetorMode();
		}
		
		private function UpdatePveBack():void 
		{
			switch (currentState) 
			{
				case NormalState:
				doctEmptyBack.SetIcon(_normalBack);
				adornEmptyBack.SetIcon(_normalBack);
				break;
				case WinState:
				doctEmptyBack.SetIcon(_winImage);
				adornEmptyBack.SetIcon(_winImage);
				break;
				case LooseState:
				doctEmptyBack.SetIcon(_looseImage);
				adornEmptyBack.SetIcon(_looseImage);
				break;
			}
		}
	}
	
}
