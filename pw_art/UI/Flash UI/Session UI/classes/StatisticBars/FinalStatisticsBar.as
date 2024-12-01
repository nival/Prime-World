package StatisticBars
{
	import classes.Events.ShareFinalStatisticEvent;
	import Components.ButtonToggle;
	import Datas.PlayerStatisticData;
	import Effects.AnimationBack;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import src.ButtonTooltipEvent;
	import src.WButton;
	
	import BaseClasses.BaseDragObject;
	import Components.ButtonStandart;
	import Events.DetailedStatisticMateEvent;
	import Events.ShowDialogEvent;
	
	public class FinalStatisticsBar extends BaseDragObject
	{
		private const PERSONAL_STATS_INDEX:int = 0;
		private const BATTLE_STATS_INDEX:int = 1;
		private const DETAILED_STATS_INDEX:int = 2;
		
		public var header_txt:TextField;
		public var allStats_mc:MovieClip;
		
		//public var buttonStatClose:ButtonStandart;
		public var personalStat:PersonalGameStatistic;
		public var batleStatistic:CurrentGameStatistics;
		public var nextStat:ButtonStandart;
		public var closeStats:ButtonStandart;
		public var detailedStat:DetailGameStatistic;
		public var share_btn:ButtonToggle;
		public var playSameTeam:PlaySameTeamControl;
		
		public var Victory:Boolean = false;
		
		private var Stats:Array = [];
		private var ButtonStates:Array = [];
		private var players:Array = [];
		private var currentStatsIndex:int = 0;
		
		private var ourHeroID:int;
		private var isPersonalDataFilled:Boolean;
		private var isDetailedStatWasFilled:Boolean;
		private var isSpectatorMode:Boolean;
		
		public function FinalStatisticsBar()
		{	
			this.stop();
			
			personalStat = new PersonalGameStatistic();
			detailedStat = new DetailGameStatistic();
			
			nextStat.addEventListener(MouseEvent.CLICK, ShowNextStat);
			share_btn.addEventListener(MouseEvent.CLICK, onShareClick);
			closeStats.addEventListener(MouseEvent.CLICK, closeThisFunction);
			
			addEventListener(Event.ADDED_TO_STAGE, AddedToStage);	
			addEventListener(DetailedStatisticMateEvent.EVENT_TYPE, FillPlayerDetailedStatistics);
		
			FillLocalization();
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, OnLocalizationComplete);
		}
		
		private function OnLocalizationComplete(e:Event):void
		{
			FillLocalization();
		}
		
		private function UpdateHeaderText()
		{
			// PF-87050
			header_txt.text = Victory ? Localization.VictoryScreen_VictoryText : Localization.DefeatScreen_DefeatText;
		}
		
		private function FillLocalization()
		{
			closeStats.LocalizeText = Localization.FinalStatisticBar_CloseBtnLabel;
			nextStat.LocalizeText = Localization.FinalStatisticBar_OpenStatisticBtnLabel;
			share_btn.Tooltip = Localization.ShareButtonTooltip;
			
			ButtonStates[PERSONAL_STATS_INDEX] = Localization.FinalStatisticBar_OpenStatisticBtnLabel;
			ButtonStates[BATTLE_STATS_INDEX] = Localization.FinalStatisticBar_OpenDetailedStatisticBtnLabel;
			ButtonStates[DETAILED_STATS_INDEX] = Localization.PersonalStatisticBar_AwardsHeaderText;
			
			UpdateHeaderText();
		}
		
		override public function AddedToStage(e:Event):void
		{	
			super.AddedToStage(e);
			
			UpdateHeaderText();
			
			this.x = stage.stageWidth  / 2;
			this.y = stage.stageHeight / 2;
			
			startPozition.x = this.x;
			startPozition.y = this.y;
			
			personalStat.x = batleStatistic.x = detailedStat.x = allStats_mc.x;
			personalStat.y = batleStatistic.y = detailedStat.y = allStats_mc.y;
			
			this.addChild(personalStat);
			this.addChild(batleStatistic);
			this.addChild(detailedStat);
			
			this.setChildIndex(detailedStat, this.getChildIndex(allStats_mc));
			
			Stats[PERSONAL_STATS_INDEX] = personalStat;
			Stats[BATTLE_STATS_INDEX] = batleStatistic;
			Stats[DETAILED_STATS_INDEX] = detailedStat;
			
			ShowStat(PERSONAL_STATS_INDEX);
			
			share_btn.visible = !isSpectatorMode;
			
			var player:PlayerStatisticData = GetPlayerByID(ourHeroID);
			
			if (player == null) return;
			
			isPersonalDataFilled = true;
			
			personalStat.FillPersonalData(player);
			
			detailedStat.ResetTeamMate();
			
			if (player.Fraction == CurrentGameStatistics.ELF_FACTION)
				detailedStat.SortElfTeamAsOurTeam();
			
			var elfFactionCount:int = 0;
			var humanFactionCount:int = 0;
			
			for each (var plr:PlayerStatisticData in players)
			{
				// TODO: почему OriginalFraction ?
				if (plr.OriginalFraction == CurrentGameStatistics.ELF_FACTION)
					elfFactionCount++;
				else
					humanFactionCount++;
				
				detailedStat.SetHeroIdentity(plr);
			}
			
			detailedStat.SetFacrionsBack(humanFactionCount, elfFactionCount);
		}		
		
		public function SetOurHero(heroID:int, fraction:int):void 
		{
			ourHeroID = heroID
			detailedStat.SetOurHero(heroID, fraction);
		}
		
		public function set Players(value:Array):void
		{
			players = value;
		}
		
		private function ShowNextStat(e:MouseEvent =null):void
		{
			if (Stats.length < 1) return;
			
			var nextStatsIndex:int = (currentStatsIndex + 1) % Stats.length;
			
			ShowStat(nextStatsIndex);
		}
		
		private function ShowStat(index:int):void
		{
			if (index == DETAILED_STATS_INDEX)
			{
				if (!isDetailedStatWasFilled)
				{
					isDetailedStatWasFilled = true;
					
					detailedStat.FillPlayerDetaledStatistic(GetPlayerByID(ourHeroID));
				}
			}
			
			for (var i:int = 0, count:int = Stats.length; i < count; ++i)
			{
				if (i == index)
				{
					Stats[i].visible = true;
					
					nextStat.LocalizeText = ButtonStates[i];
				}
				else
				{
					Stats[i].visible = false;
				}
			}
			
			currentStatsIndex = index;
		}
		
		override protected function closeThisFunction(e:Event):void 
		{
			FSCommands.Send(FSCommands.ESCMENU_RETURN_TO_LOBBY);
		}
		
		private function onShareClick(e:MouseEvent):void 
		{
			e.stopPropagation();
			dispatchEvent(new ShowDialogEvent(Localization.ShareMessageBoxHeader, Localization.ShareMessageBoxText, OnBtnOk, null));
		}
		
		public function OnBtnOk():void
		{
			dispatchEvent(new ShareFinalStatisticEvent());
		}
		
		public function set BatleStat(stat:CurrentGameStatistics):void
		{
			batleStatistic = stat;
			
			batleStatistic.SwitchPlayersToFinalStatistic();			
		}
		
		private function GetPlayerByID(heroID:int):PlayerStatisticData
		{
			for (var i:int = 0; i < players.length; i++)
			{
				if (players[i].HeroId == heroID)
				{
					return players[i];
				}
			}
			return null;
		}
		
		private function FillPlayerDetailedStatistics(e:DetailedStatisticMateEvent):void
		{
			e.stopPropagation();
			
			var player:PlayerStatisticData = GetPlayerByID(e.id);
			
			if (player == null) return;
			
			if (currentStatsIndex == BATTLE_STATS_INDEX)
			{
				ShowStat(DETAILED_STATS_INDEX);
			}
			
			isDetailedStatWasFilled = true;
			
			detailedStat.FillPlayerDetaledStatistic(player);
		}
		
		public function FinishAwarding(index:int):void 
		{
			personalStat.FinishAwarding(players[index]);
		}
		
		public function SetSpectatorMode():void 
		{
			isSpectatorMode = true;
			if (share_btn!=null)
				share_btn.visible = false;
			if (playSameTeam != null)
				playSameTeam.visible = false;
		}
		
		override protected function GetThisWindowToTheTop(e:MouseEvent):void 
		{
			
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			this.x = stage.stageWidth  / 2;
			this.y = stage.stageHeight / 2;
		}
		
		public function RemoveAwardsIcons():void
		{
			personalStat.RemoveAwardsIcons();
		}
		
		public function IsOurHero(heroID:int):Boolean
		{
			return (ourHeroID == heroID);
		}
	}
}
