package StatisticBars
{
	import Components.FlagFormater;
	import Components.HeroRankIconHolder;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import flash.events.Event;
	
	import Controllers.MateInfoController;
	import Components.ScrollBar;
	import BaseClasses.MateInfoBase;
	import BaseClasses.BaseFinalStats;
	import Datas.PlayerStatisticData;
	import Components.Bar;
	import Components.Frame;
	
	import Utils.AnimatedPortraitsUtils;
	
	public class DetailGameStatistic extends BaseFinalStats
	{
		public var bar:Bar;
		public var frameSmall1_mc:Frame;
	
		public var Results:DetailStatResults;
		
		public var HeroExploit1:ExploitIconLoader;
		public var HeroExploit2:ExploitIconLoader;
		public var HeroExploit3:ExploitIconLoader;
		
		public var teamInfoFrendly_mc:StatisticTeamInfoFriendly;
		public var teamInfoEnemy_mc:StatisticTeamInfoEnemy;
		public var teamA_mc:MovieClip;
		public var teamB_mc:MovieClip;
		public var rightHeaderText:TextField;
		
		private var HumanTeamController:MateInfoController;
		private var ElfTeamController:MateInfoController;
		private var ourHeroID:int;		
		
		public var selfShadow_mc:MovieClip;
	//	private var exploitScroll:ScrollBar;
		private var resultsScroll:ScrollBar;
		
		public var flag:FlagFormater;
		
		public var animatedIcoContainer:MovieClip;
		
		public function DetailGameStatistic()
		{	
			HumanTeamController = new MateInfoController(teamInfoFrendly_mc);
			ElfTeamController = new MateInfoController(teamInfoEnemy_mc);
			Exploits = [HeroExploit1, HeroExploit2, HeroExploit3];
			teamA_mc.stop();
			teamB_mc.stop();
		//	exploitScroll = new ScrollBar(Achivments);
		//	this.addChild(exploitScroll);
			
		//	resultsScroll = new ScrollBar(Results);
		//	this.addChild(resultsScroll);
		}
		
		override protected function FillLocalization(e:Event):void
		{
			super.FillLocalization(e);
			leftHeaderText.text = Localization.DetailedStatisticBar_AchivmentsHeaderText;
			rightHeaderText.text = Localization.DetailedStatisticBar_ResultsHeaderText;
		}
		
		public function SetOurHero(heroID:int, fraction:int):void 
		{
			HumanTeamController.OurHeroId = fraction == CurrentGameStatistics.HUMAN_FACTION?heroID: -1;
			ElfTeamController.OurHeroId = fraction == CurrentGameStatistics.ELF_FACTION?heroID: -1;
		}
		
		public function SetHeroIdentity(playerData:PlayerStatisticData):void
		{	
			if (!playerData.IsNeedToShowInStatistics)
				return;
			
			var mateInfo:MateInfoBase = MateInfoStat(playerData.HeroId, playerData.Fraction,playerData.PartyID);
			
			if (mateInfo == null) return;
			
			mateInfo.mouseEnabled = true;
			mateInfo.setHeroInfoIcon(playerData.HeroIcon, playerData.IsAnimatedAvatar);
			mateInfo.SetGender(playerData.Gender);
			mateInfo.level = playerData.Level;
			mateInfo.SetHero(playerData)
			if (playerData.IsHeroLeft)
				mateInfo.OnPlayerLeft(playerData.LeaveType);
		}
		
		public function SortElfTeamAsOurTeam():void
		{
			teamInfoEnemy_mc.SetThisAsOurFraction();
		}
		
		private function MateInfoStat(heroID:int,fraction:int,partyId:int):MateInfoBase
		{
			if (fraction == CurrentGameStatistics.HUMAN_FACTION)
			{
				return HumanTeamController.GenerateMateInfo(heroID,partyId);
			} 
			
			if (fraction == CurrentGameStatistics.ELF_FACTION)
			{
				return ElfTeamController.GenerateMateInfo(heroID,partyId);
			}	
			return null;
		}
		
		private function GetMateInfo(id:int):MateInfoBase
		{
			if (ElfTeamController.DoesHeroExist(id))
				return ElfTeamController.GetMateInfo(id);
			
			if (HumanTeamController.DoesHeroExist(id))
				return HumanTeamController.GetMateInfo(id);
			
			return null;
		}
			
		public function ResetTeamMate():void
		{
			teamInfoFrendly_mc.ResetMateState();
			teamInfoEnemy_mc.ResetMateState();
			teamInfoFrendly_mc.HideChains();
			teamInfoEnemy_mc.HideChains();
		}
		
		private function AddHeroResult(resultIcon:String,resultCount:int,resultName:String):void
		{	
			Results.AddResult(resultIcon, resultCount, resultName);
			
			if (Results.ScrollableHeight <= Results.ActualHeight) return;
			
			if (resultsScroll == null)
			{
				resultsScroll = new ScrollBar();
				resultsScroll.SetScrollableContent(Results);
				addChild(resultsScroll);
			}
			
			resultsScroll.RecalcContentHeight();
		}
		
		public function FillPlayerDetaledStatistic(playerData:PlayerStatisticData):void
		{
			if (playerData == null) return;
			
			teamInfoFrendly_mc.ResetMateSelection();
			teamInfoEnemy_mc.ResetMateSelection();
		
			var mateInfo:MateInfoBase = GetMateInfo(playerData.HeroId);
			
			if (mateInfo == null) return;
			Results.ResetToStartState();
			ResetExploitsAndTitle()
			
			mateInfo.SetSelected(true);
						
			SetShowingHeroParams(playerData.PlayerName, playerData.OriginalFraction, playerData.ClassName, playerData.HeroIcon, playerData.IsAnimatedAvatar);
			ShowingHeroLevel = playerData.Level;
			
			flag.visible = playerData.playerFlagPath.length != 0;
			flag.Icon = playerData.playerFlagPath;
			flag.TooltipText = playerData.playerFlagTooltip;
			
		//	SetFlag(playerData.playerFlagPath, playerData.playerFlagTooltip);
			HeroFraction = playerData.OriginalFraction;
			if (playerData.TitleIcon!=null&&playerData.TitleName!=null)
				SetHeroTitle(playerData.TitleName, playerData.TitleIcon, playerData.TitleTooltipID,false);
				
			SetGender(playerData.Gender);
			
			FillExploits(playerData.HeroExploits,playerData.HeroExploitsTooltips,null,false);
			SetHeroRank(playerData.HeroRaiting, playerData.RaitingDelta, playerData.HeroRankIcon, playerData.HeroRankTooltip, playerData.LeagueIndex, playerData.newLeaguePlace, playerData.leaguePlaceChange);
			for (var i:int = 0; i < playerData.ResultNames.length; i++)
			{
				AddHeroResult(playerData.ResultIcons[i], playerData.ResultCounts[i], playerData.ResultNames[i]);
			}	
			
			
			if (resultsScroll != null)
			{
				//resultsScroll.ResetToStartPosition();
				resultsScroll.RecalcContentHeight(true);
			}
		}
		
		public function SetFacrionsBack(humanFactionCount:int, elfFactionCount:int):void 
		{
			teamA_mc.gotoAndStop(humanFactionCount == 0? 2 : 1);
			teamB_mc.gotoAndStop(elfFactionCount == 0? 1: 2);
		}
		
		override protected function setHeroInfoIcon(path:String, isAnimatedAvatar:Boolean):void 
		{
			var classObject:Object = AnimatedPortraitsUtils.FindClassObject(path, isAnimatedAvatar);
			
			// нашли подходящий анимированный портрет - грузим анимацию
			if (classObject != null)
			{
				AnimatedPortraitsUtils.ClearContainer(animatedIcoContainer);
								
				heroInfo_mc.visible = false;
				animatedIcoContainer.visible = true;
				
				var iconClass:Class = classObject as Class;
				var animatedIcon:MovieClip = new iconClass();
				animatedIcoContainer.addChild(animatedIcon);
				
				// размер иконки 166, размер места под иконку 105
				// 105 / 166 == 0.63
				animatedIcon.scaleX = 0.63;
				animatedIcon.scaleY = 0.63;
			}
			else
			{
				heroInfo_mc.visible = true;
				animatedIcoContainer.visible = false;
				super.setHeroInfoIcon(path, false);
			}
		}
	}
}