package LoaderSources
{
	import BaseClasses.MateInfoBase;
	import Datas.ForceColors;
	import Enums.EFraction;
	import MainScreen.SetPlayerShortName;
	import flash.display.MovieClip;
	import flash.text.TextField;

	public class LoaderInterface
	{
		private var main:LoaderMain;
		private var humanTeam:LeftTeamHolder;
		private var elfTeam:RightTeamHolder;
		private var avgForce:TeamForceWrapper;

		private var ourHeroId:int = -1;
		private var forceColors:Array = new Array();
		private var isINovice:Boolean;
		private var ourFraction:int;
		private var _shortheroname:SetPlayerShortName;

		public function LoaderInterface(_loader:LoaderMain)
		{
			main = _loader;
			_shortheroname = new SetPlayerShortName();
			humanTeam = main.team_pnl;
			elfTeam = main.enemyTeam_pnl;
			avgForce = main.AvMight;
			//var testInterface:LoaderInterfaceTest = new LoaderInterfaceTest(this, main);
		}

		public function SetOurHeroId(id:int,fraction:int, isMuted:Boolean = false):void
		{
			ourHeroId = id;
			ourFraction = fraction;

			if (fraction == EFraction.HUMAN_FACTION)
			{
				humanTeam.OurHeroID = ourHeroId;
			}
			else
			{
				elfTeam.SetElfTeamIsOur();
				elfTeam.OurHeroID = ourHeroId;
			}
			
			main.chatBar.SetOurHeroId(id);
		}


		public function SetPlayersFaction(leftFaction:int, rightFaction:int) :void
		{
			main.loadingBar.SetPlayersFaction(leftFaction, rightFaction);
		}

		public function SetHeroIdentity(heroID:int, fraction:int, heroName:String, iconPath:String, heroLevel:int, isMale:Boolean, classIcon:String,  partyId:int, playerFlagPath:String = "", playerFlagTooltip:String = "", isAnimatedAvatar:Boolean = false, leagueIndex:int = 0):void
		{
			var teamMate:LoaderTeamMate;

			if (fraction == EFraction.HUMAN_FACTION)
				teamMate = humanTeam.GenerateMateInfo(heroID, partyId);

			if (fraction == EFraction.ELF_FACTION)
				teamMate = elfTeam.GenerateMateInfo(heroID, partyId);

			if (teamMate == null) return;

			var nick:String = "";
			var guildName:String = "";

			if (heroName.substr(0, 1) != "[") guildName = "";

			else guildName = heroName.substr(0, heroName.indexOf("]") + 1);

			nick = _shortheroname.SetPlayerName(heroName);
			
			teamMate.setHeroInfoBorder(leagueIndex);
			teamMate.setHeroInfoIcon(iconPath, isAnimatedAvatar);
			teamMate.heroName = nick;
			teamMate.SetGender(isMale);
			teamMate.classIcon.SetClassIcon(classIcon);

			teamMate.SetFlag(playerFlagPath, playerFlagTooltip);

			teamMate.guildAbbr_mc.guildName = guildName;

			if (guildName != "")
			{
				teamMate.guildAbbr_mc.visible = true;
			}
			if (heroID == ourHeroId)
			{
				teamMate.SetSelected(true);
				teamMate.isItOurHero = true;
			}

			main.UpdateLocalisationPositions();
		}

		public function SetHeroPremium(heroId:int, hasPremium:Boolean, originalFraction:int):void
		{
			var teamMate:LoaderTeamMate = GetHeroById(heroId);

			if (teamMate == null) return;


			teamMate.SetPremium(hasPremium,originalFraction,teamMate.heroName);

		}

		public function SetHeroLevel(heroId:int,level:int):void
		{
			var teamMate:LoaderTeamMate = GetHeroById(heroId);

			if (teamMate == null) return;

			teamMate.SetHeroLevel(level);
		}

		public function SetHeroLoadProgress(heroId:int, loadProgress:Number, isLeftGame:Boolean):void
		{
			var teamMate:LoaderTeamMate = GetHeroById(heroId);

			if (teamMate == null) return;

			teamMate.LoadingProgressBar = loadProgress;

			teamMate.PlayerDisconnected(isLeftGame);


			var dwarfProgress:Number = humanTeam.PersentOfLoading / 1000;
			var elfProgress:Number = elfTeam.PersentOfLoading / 1000;

			main.loadingBar.SetLoadingBarParametres(dwarfProgress, elfProgress);
		}

		private function GetHeroById(heroId:int):LoaderTeamMate
		{
			if (humanTeam.DoesHeroExist(heroId))
				return humanTeam.GetHeroByID(heroId);

			if (elfTeam.DoesHeroExist(heroId))
				return elfTeam.GetHeroByID(heroId);

			return null;
		}

		public function EnterPressed():void
		{
			main.chatBar.EnterPressed();
		}

		public function AddChannel(channel:int, channelName:String, channelColor:uint, showChannelName:Boolean,showPlayerName:Boolean,playerCanWriteToChannel:Boolean,channelType:int=0):void
		{
			main.chatBar.AddChannel(channel, channelName, channelColor, showChannelName, showPlayerName, playerCanWriteToChannel,channelType);
		}

		public function AddMessage(channel:int, playerName:String, message:String):void
		{
			main.chatBar.AddMessage(channel, playerName, message);
		}

		public function AddMessageEx(channel:int, playerName:String, message:String, playerId:int):void
		{
			main.chatBar.AddMessage(channel, playerName,  message, playerId);
		}

		public function SetDefaultChannel(channelID:int):void
		{
			main.chatBar.SetDefaultChannel(channelID);
		}

		public function SetPlayerIcon(playerId:int, path:String):void
		{
			main.chatBar.SetPlayerIcon(playerId, path);
		}
		
		public function SetPlayerHeroId(playerId:int, heroId:int, teamId:int):void
		{
			main.chatBar.SetPlayerHeroId(playerId, heroId, teamId);
		}

		public function AddChannelShortCut(channel:int, shortcut:String):void
		{
			main.chatBar.AddChannelShortCut(channel, shortcut);
		};

		public function OnEscape():void
		{
			main.chatBar.chatInput_mc.EscPressed();
		}

		public function SetChatVisible(value:Boolean):void
		{
			main.chatBar.DisableInput(!value);
			main.chatBar.visible = value;
		}

		public function SetForceColors(forces:Array,colors:Array):void
		{
			if (forces.length != colors.length)
				return;

			for (var i:int = 0; i < forces.length; i++)
			{
				var forceColor:ForceColors = new ForceColors();
				forceColor.Force = forces[i];
				forceColor.Color = colors[i];
				forceColors.push(forceColor);
			}
		}

		public function SetHeroForce(id:int, force:int)
		{
			var hero:LoaderTeamMate = GetHeroById(id);

			if (hero == null)
				return;

			var color:uint = 0xffffff;

			for (var i:int = 0; i < forceColors.length; i++)
			{
				if (force >= forceColors[i].Force)
					color = forceColors[i].Color;
				else
					break;
			}

			hero.SetHeroNameColor(color);
			if (color == forceColors[forceColors.length-1].Color)
			{
				hero.redBack.visible = true;
			}

			if (hero.guildAbbr_mc.abbr_txt.text != "")
				hero.guildAbbr_mc.abbr_txt.textColor = color;
		}

		public function SetTeamForce(forceLeft:String="", forceRight:String=""):void
		{
			//avgForce = new TeamForceWrapper();
			if (forceLeft != "" && forceRight !="")
			{	
				avgForce.visible = true;
				avgForce.SetTeamForce(forceLeft, forceRight);
			}
			else 
				avgForce.visible = false;
		}


		public function SetHeroRaiting(id:int,raiting:int, deltaWin:Number,deltaLose:Number, isNovice:Boolean = true, rankIcon:String = "", rankTooltip:String=""):void
		{
			if (id == ourHeroId)
			{
				isINovice = isNovice;
				if(isINovice)
					RemoveAllRaitings();
			}

			if (isINovice)return;

			var hero:LoaderTeamMate = GetHeroById(id);

			if (hero == null) return;

			hero.SetHeroRaiting(raiting, deltaWin, deltaLose,rankIcon,rankTooltip);
		}

		private function RemoveAllRaitings():void
		{
			humanTeam.RemoveAllRaitings();
			elfTeam.RemoveAllRaitings();
		}

		public function SetMapBack(back:String, logo:String):void
		{
			main.SetMapBack(back, logo);
		}

		public function AddModeDescription(image:String, id:int) :void
		{
			main.AddModeDescription(image, id);
		}

		public function IgnoreUser(playerId:int):void
		{
			main.chatBar.AddIgnoringUser(playerId);
		}

		public function RemoveIgnore(playerId:int):void
		{
			main.chatBar.RemoveIgnoringUser(playerId);
		}

		public function SetLoadingStatusText( statusText:String):void
		{
			main.SetLoadingStatusText(statusText);
		}

		public function SetLoadingState(preLoading:Boolean):void
		{
			main.SetLoadingState(preLoading);
		}

		public function SetLocales(myTeamLocaleImage:String, myTeamTooltip:String, enemyTeamLocaleImage:String, enemyTooltip:String ):void
		{
			var leftImage:String = ourFraction == EFraction.HUMAN_FACTION? myTeamLocaleImage: enemyTeamLocaleImage;
			var rightImage:String = ourFraction == EFraction.ELF_FACTION? myTeamLocaleImage: enemyTeamLocaleImage;

			var leftTooltip:String = ourFraction == EFraction.HUMAN_FACTION? myTeamTooltip: enemyTooltip;
			var  rightTooltip:String = ourFraction == EFraction.ELF_FACTION? myTeamTooltip: enemyTooltip;

			main.SetLocales(leftImage, leftTooltip, rightImage, rightTooltip );
		}

		public function SetTip(tip:String):void
		{
			main.advice.SetAdvice(tip);
		}

		public function SwitchToSpectatorMode():void
		{
			main.chatBar.DisableInput(true);
		}

		public function OpenChanel(channelID:int):void
		{
			main.chatBar.OpenChannel(channelID);
		}
		
		public function SetChatOff(isChatOff:Boolean):void
		{
			main.chatBar.chatInput_mc.chatOutput_cb.Value = isChatOff ? 1 : 0;
		}
	}
}