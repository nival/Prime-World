package Datas
{
	public class PlayerStatisticData
	{
		
		public var PlayerName:String;
		public var ClassName:String;
		public var HeroIcon:String;
		public var IsAnimatedAvatar:Boolean;
		public var LeagueIndex:int;
		public var LeaguePlace:int;
		public var DamageType:int;
		public var Level:int;
		public var UltimateCooldown:Number;
		public var Fraction:int;
		public var OriginalFraction:int;
		public var HeroId:int;
		public var Kills:int;
		public var Deaths:int;
		public var Assists:int;
		public var Score:int;
		public var CurrentHealth:int;
		public var MaximumHealth:int;
		public var CurrentMana:int;
		public var MaximumMana:int;
		public var isVisible:Boolean;
		public var TimeToRessurect:int;
		public var TitleIcon:String;
		public var TitleName:String;
		public var TitleTooltipID:int;
		public var Channeling:Number;
		public var Gender:Boolean = false;
		public var LastVisibleLevel:int = 1;
		public var IsFriend:Boolean;
		private var heroExploits:Array=[];
		private var heroResultNames:Array=[];
		private var heroResultIcons:Array=[];
		private var heroResultCounts:Array=[];
		private var isFirstWinAwards:Array = [];
		private var heroExploitsTooltipID:Array = [];
		private var awards:Array = [];
		private var premiumAwards:Array = [];		
		
		public var IsHeroLeft:Boolean = false;
		public var IsBot:Boolean;
		public var IsIgnoring:Boolean;
		public var ShowRedBack: Boolean = false;
		public var Force:int;
		public var HeroNameColor:uint;
		public var IsPending:Boolean;
		public var HeroRankIcon:String;
		public var HeroRankTooltip:String;
		public var HeroRaiting:Number = 0;
		public var RaitingDelta:Number = 0;
		public var IsPremium:Boolean;
		public var Prime:int; // прайм, который есть сейчас в герое
		public var CurrentPrime:int;//прайм, который отображался перед последним исчезновением героя.
		public var HealthRegen:Number;
		public var ManaRegen:Number;
		public var IsOurHero:Boolean;
		public var LeaveType:int;
		public var IsEnemyTeam:Boolean;
		public var PartyID:int = 0;
		public var GuildName:String;
		public var PlayerShortName:String;
		public var ownLeaguePlace:int;
		public var leaguePlaces:Array = [];
		
		public var playerFlagPath:String;
		public var playerFlagTooltip:String;
		
		public var IsNeedToShowInStatistics = false;
		
		public var ChatMuted:Boolean = false;
		
		public var CustomEnergy:Boolean = false;
		public var CustomEnergyName:String;
		public var CustomEnergyColor:uint;		
		
		public var newLeaguePlace:int;
		public var leaguePlaceChange:int;
		
		public function get HeroExploits():Array
		{
			return heroExploits;
		}
		
		public function AddHeroExploit(exploit:String):void
		{
			heroExploits.push(exploit);
		}
		
		public function AddHeroExploitTooltipID(tooltipID:int):void
		{
			heroExploitsTooltipID.push(tooltipID);
		}
		
		public function get HeroExploitsTooltips():Array
		{
			return heroExploitsTooltipID;
		}
		
		public function AddHeroResult(result:String, count:int, icon:String):void
		{
			heroResultIcons.push(icon)
			heroResultNames.push(result)
			heroResultCounts.push(count)
		}
		
		public function get ResultIcons():Array
		{
			return heroResultIcons;
		}
		
		public function get ResultNames():Array
		{
			return heroResultNames;
		}
		
		public function get ResultCounts():Array
		{
			return heroResultCounts;
		}
		
		public function AddAwards(awardID:int,awardIcon:String, count:int, isFirstWinAward:Boolean):void
		{
			var newAward:AwardData = new AwardData();
			newAward.Id = awardID;
			newAward.Count = count;
			newAward.IsFirstWin = isFirstWinAward;
			newAward.Icon = awardIcon;
			awards.push(newAward)
		}
		
		public function get Awards():Array
		{
			return awards;
		}
	
		public function set Awards(value:Array):void
		{
			awards = value;
		}
	
		public function set PremiumAwards(value:Array):void
		{
			premiumAwards=value;
		}
		
		public function get PremiumAwards():Array
		{
			return premiumAwards;
		}
		
		public function AddPremiumAwards(awardID:int, awardIcon:String, count:int):void
		{
			var newAward:AwardData = new AwardData();
			newAward.Id = awardID;
			newAward.Count = count;
			newAward.Icon = awardIcon;
			premiumAwards.push(newAward)
		}
		
	}
	
	
}