package StatisticBars
{
	import BaseClasses.BaseIconLoader;
	import classes.Datas.ExperienceData;
	import Components.FlagFormater;
	import Components.HeroRankIconHolder;
	import Components.PremiumShields;
	import Datas.AwardData;
	import Enums.EFraction;
	import fl.transitions.easing.Strong;
	import fl.transitions.Tween;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.utils.Timer;
	import src.ButtonTooltipEvent;
	import Utils.ColorUtils;
	
	import BaseClasses.BaseFinalStats;
	import Components.ScrollBar;
	import Datas.PlayerStatisticData;
	import Components.Frame;
	
	import Utils.AnimatedPortraitsUtils;
	
	public class PersonalGameStatistic extends BaseFinalStats
	{
		public var frameSmall1_mc:Frame;

		public var waitForRewardText:TextField;
		
		public var HeroExploit1:ExploitIconLoader;
		public var HeroExploit2:ExploitIconLoader;
		public var HeroExploit3:ExploitIconLoader;
		public var HeroExploit4:ExploitIconLoader;
		public var HeroExploit5:ExploitIconLoader;
		public var HeroExploit6:ExploitIconLoader;
		
		private var ourPlayerData:PlayerStatisticData = new PlayerStatisticData();
		
		public var Awards:AwardIcons;
		public var selfShadow_mc:MovieClip;
		public var firstWin_mc:BaseIconLoader;
		
		public var raitingValDelta:TextField;
		
		private var awardScrollBar:ScrollBar;
		
		public var statBar_comp:StatBar;
		
		
		private var isFinishAwarding:Boolean;
		private var isPersonalDataFilled:Boolean;
		private var isExploitsFillingEnded:Boolean;
		private var isAwardsIsFilled:Boolean;
		
		private var experienceData:ExperienceData =  new ExperienceData();
		private var defaultColor:uint;
		private var firstWinTooltip:String;
		
		public var flag:FlagFormater;

		public var premiumIcon_mc:PremiumShields;
		
		public var animatedIcoContainer:MovieClip;
		
		public function PersonalGameStatistic()
		{
			super();
			
			_ratingLayout.Add(raitingValDelta);
			
			defaultColor = raitingValDelta.textColor;
			raitingValDelta.visible = false;
			firstWin_mc.visible = false;
			firstWin_mc.addEventListener(MouseEvent.MOUSE_OVER, OnFirstWinOver);
			firstWin_mc.addEventListener(MouseEvent.MOUSE_OUT, OnFirstWinOut);
			Exploits = [HeroExploit1, HeroExploit2, HeroExploit3, HeroExploit4, HeroExploit5, HeroExploit6];
		}
		
		override protected function FillLocalization(e:Event):void
		{
			super.FillLocalization(e);
			leftHeaderText.text = Localization.PersonalStatisticBar_AchivmentsHeaderText;
		//	rightHeaderText.text = Localization.PersonalStatisticBar_AwardsHeaderText;
			waitForRewardText.text = Localization.PersonalStatisticBar_AwardsWaiting;
		}
		
		private function FillAwards():void 
		{	
			if (ourPlayerData == null||!isFinishAwarding||isAwardsIsFilled) return;
			
			var awards:Array = ourPlayerData.Awards;
			var premiumAwards:Array = ourPlayerData.PremiumAwards;
			
			if (awards.length == 0 && premiumAwards.length == 0) return;
			
			isAwardsIsFilled = true;
			
			if (premiumAwards.length == 0) 
			{
				FillSimpleAwards(awards);
				return
			}
			
			Awards.SetTitle(Localization.PersonalStatisticBar_PremiumAwardsHeaderText);
			
			for (var i:int = 0; i <premiumAwards.length ; i++) 
			{
				if (i == premiumAwards.length-1)
					AddHeroAward(premiumAwards[i],i,FillSimpleAwards,awards);	
				else
					AddHeroAward(premiumAwards[i],i);	
			}
		}
		
		private function FillSimpleAwards(awards:Array):void
		{
			Awards.SetTitle(Localization.PersonalStatisticBar_AwardsHeaderText);
			
			for (var i:int = 0; i < awards.length; i++)
			{
				AddHeroAward(awards[i],i);
			}
		}
		
		
		private function AddHeroAward(award:AwardData,numAward:int,func:Function=null, funcParams:Array=null):void
		{
			if (func != null)
			{
				var funcTimer:Timer = new Timer(duration * (numAward+1), 1);
				funcTimer.addEventListener(TimerEvent.TIMER_COMPLETE, CallFunction);
				funcTimer.start()
			}
			
			if (numAward == 0)
			{
				FillAward(null);
				return;
			}
		
			var myTimer:Timer = new Timer(duration * numAward, 1);
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, FillAward);
			myTimer.start()
			
			function CallFunction(e:TimerEvent):void
			{
				func.call(this, funcParams);
			}
		
			function FillAward(e:TimerEvent):void 
			{
				Awards.AddAward(award);

				if (Awards.ScrollableHeight <= Awards.ActualHeight) return;
				
				if (awardScrollBar == null)
				{
					awardScrollBar = new ScrollBar();
					awardScrollBar.SetScrollableContent(Awards);
					addChild(awardScrollBar);
				}
				
				awardScrollBar.RecalcContentHeight();
			}
		}
		
		public function FillPersonalData(personalData:PlayerStatisticData):void
		{
			ourPlayerData = personalData;
			
			SetHeroRank(personalData.HeroRaiting, personalData.RaitingDelta, personalData.HeroRankIcon, personalData.HeroRankTooltip, personalData.LeagueIndex, personalData.newLeaguePlace, personalData.leaguePlaceChange);
			
			SetShowingHeroParams(personalData.PlayerName, personalData.OriginalFraction, personalData.ClassName, personalData.HeroIcon, personalData.IsAnimatedAvatar);
			
			premiumIcon_mc.SetPremium(personalData.IsPremium, personalData.OriginalFraction,personalData.PlayerName);
			
			ShowingHeroLevel = personalData.Level;
			
			flag.visible = ourPlayerData.playerFlagPath.length != 0;
			flag.Icon = ourPlayerData.playerFlagPath;
			flag.TooltipText = ourPlayerData.playerFlagTooltip;
			
			//SetFlag(ourPlayerData.playerFlagPath, ourPlayerData.playerFlagTooltip);
			
			if (personalData.TitleName!=null&&personalData.TitleIcon!=null)
				SetHeroTitle(personalData.TitleName, personalData.TitleIcon, personalData.TitleTooltipID);
			
			SetGender(personalData.Gender);
			
			FillAwards();
			
			FillExploits(personalData.HeroExploits,personalData.HeroExploitsTooltips,OnExploitsFillingEnded);
			
			if(experienceData.IsFilled)
				statBar_comp.SetStatisticExperienceBar(experienceData.PreviousLevel, experienceData.NextLevel, experienceData.PremiumExperience, experienceData.ExpTable);
				
			isPersonalDataFilled = true;
		}
		
		private function OnExploitsFillingEnded():void
		{
			if (!isAwardsIsFilled) FillAwards();
			isExploitsFillingEnded = true;
		}
		
		public function FinishAwarding(player:PlayerStatisticData):void
		{
			waitForRewardText.visible = false;
			isFinishAwarding = true;
			
			if (player == null) return;
			ourPlayerData = player;

			if (isExploitsFillingEnded)
				FillAwards();
		}
		
		public function SetStatisticExperienceBar(prevLevel:int, nextLevel:int,premiumExp:int, levelsTabel:Array):void 
		{
			experienceData.PreviousLevel = prevLevel;
			experienceData.NextLevel = nextLevel;
			experienceData.ExpTable = levelsTabel;
			experienceData.IsFilled = true;
			experienceData.PremiumExperience = premiumExp;
			
			if (!isPersonalDataFilled) return
			
			statBar_comp.SetStatisticExperienceBar(prevLevel, nextLevel, premiumExp, levelsTabel);
		}
		
		override public function SetHeroRank(raiting:Number, delta:Number, rankIcon:String, rankTooltip:String, leagueIndex:int, newleaguePlace:int, leaguePlaceChange:int):void 
		{
			super.SetHeroRank(raiting, delta, rankIcon, rankTooltip, leagueIndex, newleaguePlace, leaguePlaceChange);
			
			var i_rating:int = int(raiting);
			var i_delta:int = int(delta);
			
			if (i_rating > 0 &&
				i_delta != 0)
			{
				raitingValDelta.visible = true;
				raitingValDelta.text = "(" + ((i_delta < 0) ? "-" : "+") + Math.abs(delta).toFixed(1) + ")";
				raitingValDelta.textColor = ColorUtils.GetColorBySighn(delta, defaultColor);
				
				if (newleaguePlace != 0) {
					raitingValDelta.text = "(" + ((leaguePlaceChange < 0) ? "-" : "+") + Math.abs(leaguePlaceChange).toString() + ")";
					raitingValDelta.textColor = ColorUtils.GetColorBySighn(leaguePlaceChange, defaultColor);
				}
			}
			else
			{
				raitingValDelta.visible = false;
			}
			
			_ratingLayout.Layout();
		}
		
		// FirstWinTooltip
		public function SetFirstWin(iconPath:String, tooltip:String):void 
		{
			firstWin_mc.visible = iconPath.length != 0;
			firstWin_mc.SetIcon(iconPath);
			firstWinTooltip = tooltip;
		}
		
		private function OnFirstWinOver(e:MouseEvent):void 
		{
			var globalPoint:Point = firstWin_mc.localToGlobal(new Point());
			if (firstWinTooltip.length == 0) return;
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, this, globalPoint.x, globalPoint.y, firstWinTooltip));
		}
		
		private function OnFirstWinOut(e:MouseEvent):void 
		{
			if (firstWinTooltip.length == 0) return;
			dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
		}
		
		public function RemoveAwardsIcons():void
		{
			isAwardsIsFilled = false;
			isFinishAwarding = false;
			
			this.Awards.RemoveIcons();
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