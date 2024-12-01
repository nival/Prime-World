package BaseClasses
{
	import Components.HeroRankIconHolder;
	import Controllers.TextFieldFormater;
	import fl.motion.FunctionEase;
	import fl.transitions.easing.Strong;
	import fl.transitions.Tween;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.events.Event;
	import Enums.EMateInfoIcons;
	import flash.utils.Timer;
	import MainScreen.MateInfoIcons;
	import Components.HeroIco;
	import Components.RoundFrame;
	import StatisticBars.CurrentGameStatistics;
	import StatisticBars.ExploitIconLoader;
	import StatisticBars.Titles;
	
	public class BaseFinalStats extends MovieClip
	{
		public var humanLogo_mc:MovieClip;
		public var elfLogo_mc:MovieClip;
		public var roundFrame:RoundFrame;
		public var heroInfo_mc:HeroIco;
		public var playerName:TextField;
		public var heroName:TextField;
		public var level:TextField;
		public var leftHeaderText:TextField;
		public var mateInfoIcons:MateInfoIcons;
		public var titleHeroIcon:Titles;
		public var HeroTitleText:TextField;
		
		public var elitHero:HeroRankIconHolder;
		public var raiting_txt:TextField;
		public var league_place_txt:TextField;
		public var raitingVal_txt:TextField;
		
		private var playerNameFormater:TextFieldFormater;
		private var textAlphaTween:Tween;
		
		private var tweenDuration:Number = 1;
		
		protected var Exploits:Array=[];
		protected var duration:Number = 250;
		
		private var exploitsTimers:Array = new Array();
		
		protected var _ratingLayout:InlineTextLayout;
		
		public function BaseFinalStats()
		{
			_ratingLayout = new InlineTextLayout();			
			_ratingLayout.Add(raiting_txt);
			_ratingLayout.Add(league_place_txt);
			_ratingLayout.Add(raitingVal_txt);
			
			mateInfoIcons.visible = false;
			humanLogo_mc.visible = false;
			elfLogo_mc.visible = false;
			playerNameFormater = new TextFieldFormater(playerName);
			
			textAlphaTween = new Tween(HeroTitleText, "alpha", Strong.easeIn, 0, 1, tweenDuration, true);	
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
			
			function onAddedToStage(e:Event):void
			{
				removeEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
				
				_ratingLayout.Layout();
			}
			
			{
				addEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
			}
		}
		
		protected function FillLocalization(e:Event):void 
		{
			raiting_txt.text = Localization.CharStarBar_RaitingLabelText;
			if (league_place_txt != null)
				league_place_txt.text = Localization.CharStarBar_LeaguePlaceLabelText;
			
			if (_ratingLayout != null)
				_ratingLayout.Layout();
		}
		
		protected function SetShowingHeroParams(heroname:String, fraction:int, heroClass:String, path:String, isAnimatedAvatar:Boolean):void
		{
			playerNameFormater.Text = heroname;
			heroName.text = heroClass;
			setHeroInfoIcon(path, isAnimatedAvatar);
			HeroFraction = fraction;
		}
		
		protected function setHeroInfoIcon(path:String, isAnimatedAvatar:Boolean):void 
		{
			heroInfo_mc.SetIcon(path);
		}
		
		protected function SetHeroTitle(heroTitle:String, heroTitleIcon:String,tooltipID:int,animated:Boolean=true):void 
		{
			titleHeroIcon.visible = true;
			HeroTitleText.visible = true;
			titleHeroIcon.SetImage(heroTitleIcon, animated);
			titleHeroIcon.Tooltip = tooltipID;
		
			HeroTitleText.text = heroTitle;
			
			if (animated)
				textAlphaTween.start();			
			else
				HeroTitleText.alpha = 1;
		}
		
		
		protected function set ShowingHeroLevel(_level:int):void
		{
			level.text = _level.toString();
		}
		
	/*	public function SetFlag(path:String, tooltip:String):void
		
		{
			flag.visible = path.length != 0;
			flag.Icon = path;
			flag.TooltipText = tooltip;
		}
	*/	
		protected function set HeroFraction(fraction:int):void
		{
			if (fraction == CurrentGameStatistics.ELF_FACTION)
			{
				humanLogo_mc.visible = false;
				elfLogo_mc.visible = true;
			}
			if (fraction == CurrentGameStatistics.HUMAN_FACTION)
			{
				humanLogo_mc.visible = true;
				elfLogo_mc.visible = false;
			}
		}
		
		public function SetGender(isMale:Boolean):void
		{
			//mateInfoIcons.Icon = isMale? EMateInfoIcons.MALE:EMateInfoIcons.FEMALE;
		}
		
		protected function FillExploits(heroExploits:Array,heroExploitsTooltips:Array,callbackFunction:Function,animated:Boolean = true):void 
		{
			var callBack:Function =  null;
			
			for (var i:int = 0; i < Exploits.length; i++)
			{
				if ((i == Exploits.length - 1) || (i == heroExploits.length - 1)) 
				{
					callBack = callbackFunction;
				}
				
				AddHeroExploit(heroExploits[i],heroExploitsTooltips[i],i,callBack,animated);
			}
		}
		
		private function AddHeroExploit(path:String,tooltipID:int,numExpl:int,callbackFunction:Function, animated:Boolean):void
		{	
			if (animated) 
			{
				
			
			var myTimer:Timer = new Timer(duration * (numExpl+1), 1);
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, FillExploit);
			myTimer.start()
			
			exploitsTimers.push(myTimer);
			}
			else
			{
				FillExploit(null);
			}
			
			function FillExploit(e:TimerEvent):void 
			{
				Exploits[numExpl].SetImage(path,animated);
				Exploits[numExpl].Tooltip = tooltipID;
				
				if (callbackFunction!=null)
					callbackFunction.call();
			}
		}
		
		protected function ResetExploitsAndTitle():void
		{
			for each (var timer:Timer in exploitsTimers) 
			{
				timer.stop();
			}
			exploitsTimers = new Array();
			
			textAlphaTween.stop();
			titleHeroIcon.StopAnimation();
			HeroTitleText.visible = false;
			
			for each (var item:ExploitIconLoader in Exploits) 
			{
				item.StopAnimation();
			}
		}
		
		public function SetHeroRank(raiting:Number, delta:Number, rankIcon:String, rankTooltip:String, leagueIndex:int, newleaguePlace:int, leaguePlaceChange:int):void 
		{
			elitHero.visible = rankIcon.length!=0;
			elitHero.Icon = rankIcon;
			elitHero.TooltipText = rankTooltip;
			
			var i_rating:int = int(raiting);
			
			if (i_rating > 0)
			{
				raiting_txt.visible = true;
				raitingVal_txt.visible = true;
				raitingVal_txt.text = i_rating.toFixed(0);
				
				if (newleaguePlace != 0 && league_place_txt != null) {
					raitingVal_txt.text = newleaguePlace.toString();
					league_place_txt.visible = true;
					raiting_txt.visible = false;
				}
				else {
					if (league_place_txt != null)
						league_place_txt.visible = false;
				}
			}
			else
			{
				raiting_txt.visible = false;
				raitingVal_txt.visible = false;
				if (league_place_txt != null)
					league_place_txt.visible = false;
			}
			
			_ratingLayout.Layout();
		}
	}
}