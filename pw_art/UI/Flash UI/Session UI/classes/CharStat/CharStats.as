package CharStat
{
	import BaseClasses.BaseIconLoader;
	import BaseClasses.TooltipSender;
	import Components.FlagFormater;
	import Components.FormatedTimer;
	import Components.HeroRankIconHolder;
	import Components.PremiumShields;
	import Controllers.TextFieldFormater;
	import Datas.PlayerStatisticData;
	import flash.display.Bitmap;
	import flash.display.DisplayObject;
	import flash.display.DisplayObjectContainer;
	import flash.display.Graphics;
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.events.Event;
	import BaseClasses.BaseDragObject;
	import flash.text.TextFieldAutoSize;
	import Utils.ColorUtils;
	
	import Components.RoundFrame;
	import MainScreen.MateInfoIcons;
	import Enums.EStat;
	import Enums.EDamageType;
	import StatisticBars.CurrentGameStatistics;
	import Enums.EDerivativeStat;
	import Enums.EMateInfoIcons;
	import Enums.EFraction;
	import Components.HeroIco;
	
	import Utils.AnimatedPortraitsUtils;
	
	public class CharStats extends BaseDragObject 
	{
		//reference
		public var humanLogo_mc:MovieClip;
		public var elfLogo_mc:MovieClip;
		public var starHealth_mc:TooltipSender;
		public var starEnergy_mc:TooltipSender;
		public var starStrength_mc:TooltipSender;
		public var starIntelligence_mc:TooltipSender;
		public var starAgility_mc:TooltipSender;
		public var starDexterity_mc:TooltipSender;
		public var starFortitude_mc:TooltipSender;
		public var starWill_mc:TooltipSender;
		
		public var levelLable:TextField;
		private var humanLogo:DisplayObject;
		private var elfLogo:DisplayObject;
		
		private var starHealth:DisplayObject;
		private var starEnergy:DisplayObject;
		private var starStrength:DisplayObject;
		private var starIntelligence:DisplayObject;
		private var starAgility:DisplayObject;
		private var starDexterity:DisplayObject;
		private var starFortitude:DisplayObject;
		private var starWill:DisplayObject;
		private var magicalDmgIco:DisplayObject;
		private var physicalDmgIco:DisplayObject;
		
		public var magicalDmgIco_mc:MovieClip;
		public var physicalDmgIco_mc:MovieClip;
		
		public var roundFrame:RoundFrame;
		public var heroInfo_mc:HeroIco;
		public var playerName:TextField;
		public var heroName:TextField;
		public var level:TextField;
		public var life:TextField;
		public var lifeAdd:TextField;
		public var energy:TextField;
		public var energyAdd:TextField;
		public var strength:TextField;
		
		public var intellect:TextField;
		
		public var attackSpeed:TextField;
		
		public var dexterity:TextField;
		
		public var stamina:TextField;
		
		public var will:TextField;
		
		public var moveSpeed:TextField;
		public var damageMin:TextField;
		public var damageMax:TextField;
		public var atackpersecond:TextField;
		public var critChanse:TextField;
		public var critMiss:TextField;
		public var bodyDefense:TextField;
		public var spiritDefense:TextField;
		public var mateInfoIcons:MateInfoIcons;
		
		public var lifeName:TextField;
		public var energyName:TextField;
		public var strengthName:TextField;
		public var intellectName:TextField;
		public var attackSpeedName:TextField;
		public var dexterityName:TextField;
		public var staminaName:TextField;
		public var willName:TextField;
		public var moveSpeedName:TextField;
		public var damageName:TextField;
		public var atackpersecondName:TextField;
		public var critChanseName:TextField;
		public var critMissName:TextField;
		public var bodyDefenseName:TextField;
		public var spiritDefenseName:TextField;
		public var header_txt:TextField;
		public var deathMask_mc:MovieClip;
		public var selfShadow_mc:MovieClip;
		public var deathTime:FormatedTimer;
		
		public var raiting_txt:TextField;
		public var league_place_txt:TextField;
		public var raitingVal_txt:TextField;
		public var elitHero:HeroRankIconHolder;
		
		private var tooltipField:Sprite;
		
		//vars
		private var baseStatTextFieldsNames:Array = new Array();
		private var baseStatTextFields:Array = new Array();
		private var baseStatAddTextFields:Array = new Array();
		private var baseStatTooltipFields:Array = new Array();
		private var derivativeStatTooltipFields:Array = new Array();

		private var isVisible:Boolean = true;
		private var isDeathTimeShowing:Boolean;
		
		private var stars:Array = new Array();
		
		private var playerNameFormater:TextFieldFormater;
		private var headerFormater:TextFieldFormater;
		private var defaultColor:uint;
		public	var flag:FlagFormater;
		
		public var premiumIcon_mc:PremiumShields;
		
		public var isSelectionCharStats:Boolean = false;
		public var redBack:MovieClip;
		
		private var defaultEnergyNameText:String = null;
		
		public var animatedIcoContainer:MovieClip;
		
		public var border1:MovieClip;
		public var border2:MovieClip;
		public var border3:MovieClip;
		public var border4:MovieClip;
		public var border11:MovieClip;
		public var border12:MovieClip;
		public var border13:MovieClip;
		public var border14:MovieClip;
		public var border21:MovieClip;
		public var border22:MovieClip;
		public var border23:MovieClip;
		public var border24:MovieClip;
		public var border31:MovieClip;
		public var border32:MovieClip;
		public var border33:MovieClip;
		public var border34:MovieClip;
		public var border41:MovieClip;
		public var border42:MovieClip;
		public var border43:MovieClip;
		public var border44:MovieClip;
		public var border51:MovieClip;
		public var border52:MovieClip;
		public var border53:MovieClip;
		public var border54:MovieClip;
		public var border61:MovieClip;
		public var border62:MovieClip;
		public var border63:MovieClip;
		public var border64:MovieClip;
		public var border71:MovieClip;
		public var border72:MovieClip;
		public var border73:MovieClip;
		public var border74:MovieClip;
		public var border81:MovieClip;
		public var border82:MovieClip;
		public var border83:MovieClip;
		public var border84:MovieClip;
		
		public var level2:MovieClip;
		public var level3:MovieClip;
		public var level4:MovieClip;
		public var level5:MovieClip;
		public var level5_s2:MovieClip;
		
		public function CharStats() 
		{
			defaultEnergyNameText = energyName.text;
			
			defaultColor = damageMin.textColor;
			mateInfoIcons.visible =  false;
			// constructor code
			damageMax.autoSize = TextFieldAutoSize.LEFT;
			damageMin.autoSize = TextFieldAutoSize.LEFT;
			
			elitHero.visible = false;
			flag.visible = false;
			
			playerNameFormater = new TextFieldFormater(playerName);
			headerFormater = new TextFieldFormater(header_txt);
			magicalDmgIco = ConvertFromMovieToBitmap(magicalDmgIco_mc)
			physicalDmgIco = ConvertFromMovieToBitmap(physicalDmgIco_mc)
			humanLogo = ConvertFromMovieToBitmap(humanLogo_mc);
			elfLogo = ConvertFromMovieToBitmap(elfLogo_mc);
			
			magicalDmgIco_mc = null;
			physicalDmgIco_mc = null;
			humanLogo_mc = null;
			elfLogo_mc = null;
		
			baseStatTextFields.length = 30;
			baseStatAddTextFields.length = 30;
			baseStatTooltipFields.length = 30;
			stars.length = 30;
			derivativeStatTooltipFields.length = 13;
			
			baseStatTextFields[EStat.STAT_ATTACKSPEED] = attackSpeed;
			baseStatTextFieldsNames[EStat.STAT_ATTACKSPEED] = attackSpeedName;
			stars[EStat.STAT_ATTACKSPEED] = starAgility_mc;
			
			baseStatTextFields[EStat.STAT_STRENGTH] = strength;
			baseStatTextFieldsNames[EStat.STAT_STRENGTH] = strengthName;
			stars[EStat.STAT_STRENGTH] = starStrength_mc;
			
			baseStatTextFields[EStat.STAT_INTELLECT] = intellect;
			baseStatTextFieldsNames[EStat.STAT_INTELLECT] = intellectName;
			stars[EStat.STAT_INTELLECT] = starIntelligence_mc;
			
			baseStatTextFields[EStat.STAT_DEXTERITY] = dexterity;
			baseStatTextFieldsNames[EStat.STAT_DEXTERITY] = dexterityName;
			stars[EStat.STAT_DEXTERITY] = starDexterity_mc;
			
			baseStatTextFields[EStat.STAT_STAMINA] = stamina;
			baseStatTextFieldsNames[EStat.STAT_STAMINA] = staminaName;
			stars[EStat.STAT_STAMINA] = starFortitude_mc;
			
			baseStatTextFields[EStat.STAT_WILL] = will;
			baseStatTextFieldsNames[EStat.STAT_WILL] = willName;
			stars[EStat.STAT_WILL] = starWill_mc;
			
			baseStatTextFields[EStat.STAT_MOVESPEED] = moveSpeed;
			baseStatTextFieldsNames[EStat.STAT_MOVESPEED] = moveSpeedName;
			
			baseStatTextFields[EStat.STAT_LIFE] = life;
			baseStatAddTextFields[EStat.STAT_LIFE] = lifeAdd;
			baseStatTextFieldsNames[EStat.STAT_LIFE] = lifeName;
			stars[EStat.STAT_LIFE] = starHealth_mc;
			
			baseStatTextFields[EStat.STAT_ENERGY] = energy;
			baseStatAddTextFields[EStat.STAT_ENERGY] = energyAdd;
			baseStatTextFieldsNames[EStat.STAT_ENERGY] = energyName;
			stars[EStat.STAT_ENERGY] = starEnergy_mc;
			
			for (var k:int = 0; k < baseStatTextFieldsNames.length; k++) 
			{
				if (baseStatTextFieldsNames[k] != null)
					baseStatTextFieldsNames[k].autoSize = TextFieldAutoSize.RIGHT;
			}
			
			for (var i:int = 0; i < baseStatTextFields.length; i++)
			{
				if (baseStatTextFields[i] != null)
					baseStatTooltipFields[i] = MakeTooltipShower(true,i); 
			}
			
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_DAMAGEMAX] = MakeTooltipShower(false,EDerivativeStat.DERIVATIVESTAT_DAMAGEMAX); 
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_ATTACKSPERSECOND] = MakeTooltipShower(false,EDerivativeStat.DERIVATIVESTAT_ATTACKSPERSECOND); 
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_CRITCHANCE] = MakeTooltipShower(false, EDerivativeStat.DERIVATIVESTAT_CRITCHANCE);
			
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_PENETRATIONTOTAL] = MakeTooltipShower(false, EDerivativeStat.DERIVATIVESTAT_PENETRATIONTOTAL);
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_SPIRITDEFENCE] = MakeTooltipShower(false, EDerivativeStat.DERIVATIVESTAT_SPIRITDEFENCE);
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_BODYDEFENCE] = MakeTooltipShower(false,EDerivativeStat.DERIVATIVESTAT_BODYDEFENCE);
	
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);

			var j:int = 0
			
			for (j = 0; j < baseStatTextFields.length; j++) 
			{
				SetBaseStat(j, 0, 0,false);
			}
			for (j = 0; j < EDerivativeStat.LENGTH_OF_DERIVALTIVESTAT; j++) 
			{
				SetDerivativeStat(j, 0);
			}
			SetHeroParams(1, 0, 0, 0, 0);
			
			if (deathMask_mc != null)
			{
				deathMask_mc.stop();
				deathMask_mc.visible = false;
				deathMask_mc.mouseEnabled = false;
				deathMask_mc.mouseChildren = false;
			}
			deathTime.visible = false;
			redBack.visible = false;
			
			//if (border1 != null) {
				border1.visible = false;
				border2.visible = false;
				border3.visible = false;
				border4.visible = false;
				border11.visible = false;
				border12.visible = false;
				border13.visible = false;
				border14.visible = false;
				border21.visible = false;
				border22.visible = false;
				border23.visible = false;
				border24.visible = false;			//}
				border31.visible = false;
				border32.visible = false;
				border33.visible = false;
				border34.visible = false;
				border41.visible = false;
				border42.visible = false;
				border43.visible = false;
				border44.visible = false;
				border51.visible = false;
				border52.visible = false;
				border53.visible = false;
				border54.visible = false;
				border61.visible = false;
				border62.visible = false;
				border63.visible = false;
				border64.visible = false;
				border71.visible = false;
				border72.visible = false;
				border73.visible = false;
				border74.visible = false;
				border81.visible = false;
				border82.visible = false;
				border83.visible = false;
				border84.visible = false;
				
			
			//if (level2 != null) {
				level2.visible = false;
				level3.visible = false;
				level4.visible = false;
				level5.visible = false;
				level5_s2.visible = false;
			//}
		}
		
		public function SetGreyMask(setMask:Boolean):void
		{	
			if (deathMask_mc == null) return;
			
			if (isVisible == !setMask) 
			{
				return;
			}
			
			isVisible = !setMask;
			
			deathMask_mc.visible = setMask;
			if (deathMask_mc.visible) 
				deathMask_mc.gotoAndPlay(1);
		}
		
		
		private function SetStartValue(textArray:Array):void
		{
			for each(var textField:TextField in textArray)
			{
				if (textField != null)
					textField.text = "0";
			}
		}
		
		private function FillLocalization(e:Event):void
		{
			defaultEnergyNameText = Localization.CharStarBar_EnergyText;
			
			headerFormater.Text = Localization.CharStatBar_HeaderText;
			lifeName.text = Localization.CharStarBar_LifeText;
			energyName.text = Localization.CharStarBar_EnergyText;
			strengthName.text = Localization.CharStarBar_StrengthText;
			intellectName.text = Localization.CharStarBar_IntellectText;
			attackSpeedName.text = Localization.CharStarBar_AttackSpeedText;
			dexterityName.text = Localization.CharStarBar_DexterityText;
			staminaName.text = Localization.CharStarBar_StaminaText;
			willName.text = Localization.CharStarBar_WillText;
			moveSpeedName.text = Localization.CharStarBar_MoveSpeedText;
			damageName.text = Localization.CharStarBar_DamageText;
			atackpersecondName.text = Localization.CharStarBar_AttackPerSecondText;
			critChanseName.text = Localization.CharStarBar_CritChanseText;
			critMissName.text = Localization.CharStarBar_CritMissText;
			bodyDefenseName.text = Localization.CharStarBar_BodyDefenceText;
			spiritDefenseName.text = Localization.CharStarBar_SpiritDefenceText;
			raiting_txt.text = Localization.CharStarBar_RaitingLabelText;
			league_place_txt.text = Localization.CharStarBar_LeaguePlaceLabelText;
			
			for (var i:int = 0; i < stars.length; i++) 
			{
				if (stars[i] != null)
				{
					stars[i].TooltipText = Localization.CharStatBar_ThisIsImportantStat;
					// чит, для правильного отображения позиции в игре
					stars[i].x = baseStatTextFieldsNames[i].x +baseStatTextFieldsNames[i].width - baseStatTextFieldsNames[i].textWidth - stars[i].width - 3; 
				}
			}
		}
		
		private function ConvertFromMovieToBitmap(dispObject:MovieClip):DisplayObject
		{
			var bitm:DisplayObject = dispObject.getChildAt(0) as DisplayObject;
			
			this.addChildAt(bitm, this.getChildIndex(dispObject));
			bitm.x = dispObject.x;
			bitm.y = dispObject.y;
			bitm.visible = false;
			this.removeChild(dispObject);
				
			return bitm;
		}
		
		private function MakeTooltipShower(baseStat:Boolean,index:int):Sprite
		{
			tooltipField = new CharstatTooltipShower(baseStat,index);
			this.addChild(tooltipField);			
			return tooltipField;
		}
		
		public function SetHeroIdentity(playerData:PlayerStatisticData):void
		{
			if (isSelectionCharStats)
				headerFormater.Text = playerData.PlayerName;
				
			playerNameFormater.Text = playerData.PlayerName;
			//playerName.text = playerData.PlayerName;
			playerName.textColor = playerData.HeroNameColor;
			redBack.visible = playerData.ShowRedBack;
			heroName.text = playerData.ClassName;
			setHeroInfoBorder(playerData.LeagueIndex);
			setHeroInfoIcon(playerData.HeroIcon, playerData.IsAnimatedAvatar);			
			level.text = playerData.LastVisibleLevel.toString();
		//	mateInfoIcons.visible = true;
		//	mateInfoIcons.Icon = playerData.Gender? EMateInfoIcons.MALE:EMateInfoIcons.FEMALE;;
			ShowingFraction = playerData.OriginalFraction;
			
			premiumIcon_mc.SetPremium(playerData.IsPremium, playerData.OriginalFraction,playerData.PlayerName);
			
			elitHero.visible = playerData.HeroRankIcon.length!=0;
			elitHero.Icon = playerData.HeroRankIcon;
			elitHero.TooltipText = playerData.HeroRankTooltip;
			
			if (playerData.playerFlagPath.length != 0 || playerData.HeroId != -1)
			flag.visible = true;
			else flag.visible = false;
			
			flag.Icon = playerData.playerFlagPath;
			flag.TooltipText = playerData.playerFlagTooltip;
			
			raiting_txt.visible = playerData.HeroRaiting != 0;
			raitingVal_txt.visible = int(playerData.HeroRaiting) != 0;
			raitingVal_txt.text = int(playerData.HeroRaiting).toString();
			
			league_place_txt.visible = false;
			if (playerData.ownLeaguePlace > 0) { 
				raiting_txt.visible = false;
				league_place_txt.visible = true;
				raitingVal_txt.visible = true;
				raitingVal_txt.text = playerData.ownLeaguePlace.toString();
			}
								
			if (playerData.CustomEnergy)
				energyName.text = playerData.CustomEnergyName + ":";
			else
				energyName.text = defaultEnergyNameText;
		}
		
		public function SetCreapIdentity(iconPath:String, creapName:String, fraction:int, damageType:int):void
		{
			headerFormater.Text = creapName;
			playerNameFormater.Text = creapName;
			playerName.textColor = 0xffffff;
//			playerName.text = creapName;
			heroName.text = "";
			heroInfo_mc.SetIcon(iconPath);
			
			flag.visible = false;
	
			
			elitHero.visible =  false;
			raitingVal_txt.visible = false;
			raiting_txt.visible = false;
			premiumIcon_mc.visible = false;
			
		//	mateInfoIcons.visible = false;
			ShowingFraction = fraction;
		}
		
		private function set ShowingFraction(fraction:int):void
		{
			if (fraction == EFraction.ELF_FACTION)
			{
				humanLogo.visible = false;
				elfLogo.visible = true;
			}
			if (fraction == EFraction.HUMAN_FACTION)
			{
				humanLogo.visible = true;
				elfLogo.visible = false;
			}
			if (fraction == EFraction.NEUTRAL||fraction == EFraction.NO_FRACTION)
			{
				humanLogo.visible = false;
				elfLogo.visible = false;
			}
		}
		
		public function set ShowingDamageType(damageType:int):void
		{
			switch (damageType) 
			{
				case EDamageType.DAMAGETYPE_ENERGY: 
				{ 
					magicalDmgIco.visible = true;
					physicalDmgIco.visible = false;
					break; 
				}
				case EDamageType.DAMAGETYPE_MATERIAL: 
				{ 
					physicalDmgIco.visible = true;
					magicalDmgIco.visible = false;
					break; 
				}
			}
		}
		
		public function SetHeroParams(lev:int, curHealth:int, maxHealth:int, curMana:int, maxMana:int):void
		{
			level.text = lev.toString();
			
			life.text = curHealth.toString() + " /";
			lifeAdd.text = " "+maxHealth.toString();
			lifeAdd.x = life.x + life.textWidth;
			
			energy.text = curMana.toString() + " /";
			energyAdd.text = " "+maxMana.toString();
			energyAdd.x = energy.x + energy.textWidth;
		}
		
		public function SetDerivativeStat(valueType:int, value:int)
		{
			if (value < 0) 
				value = 0;
			
			switch (valueType){
				case EDerivativeStat.DERIVATIVESTAT_DAMAGEMIN: 
				{
					damageMin.text = value.toString();
					break; 
				}
				case EDerivativeStat.DERIVATIVESTAT_DAMAGEMAX:
				{ 
					damageMax.text = " - "+value.toString() + " ";
					damageMax.x = damageMin.x + damageMin.textWidth;
					magicalDmgIco.x = damageMax.x  + damageMax.textWidth;
					physicalDmgIco.x = damageMax.x  + damageMax.textWidth;
					derivativeStatTooltipFields[valueType].SetTooltipPositionAndSize(damageName,damageMin, damageMax);
					
					break; 
				}
				case EDerivativeStat.DERIVATIVESTAT_ATTACKSPERSECOND:
				{ 
					var atackPerSec:Number = value / 100;
					atackpersecond.text = atackPerSec.toString();
					
					derivativeStatTooltipFields[valueType].SetTooltipPositionAndSize(atackpersecondName,atackpersecond);
					break; 
				}
				case EDerivativeStat.DERIVATIVESTAT_CRITCHANCE:
				{
					critChanse.text = value.toString() + "%";
					derivativeStatTooltipFields[valueType].SetTooltipPositionAndSize(critChanseName,critChanse);
					break;
				}		
				case EDerivativeStat.DERIVATIVESTAT_BODYDEFENCE:
				{
					bodyDefense.text = value.toString() + "%";
					derivativeStatTooltipFields[valueType].SetTooltipPositionAndSize(bodyDefenseName,bodyDefense);
					break;
				}
				case EDerivativeStat.DERIVATIVESTAT_SPIRITDEFENCE:
				{
					spiritDefense.text = value.toString() + "%";
					derivativeStatTooltipFields[valueType].SetTooltipPositionAndSize(spiritDefenseName,spiritDefense);
					break;
				}
				case EDerivativeStat.DERIVATIVESTAT_PENETRATIONTOTAL:
				{
					critMiss.text = value.toString() + "%";
					derivativeStatTooltipFields[valueType].SetTooltipPositionAndSize(critMissName,critMiss);
					break;
				}
			}
		}
		
		public function SetBaseStat(valueType:int, value:int, addition:int, isImportant:Boolean):void
		{
			if (stars[valueType] != null)
			{
				stars[valueType].visible = isImportant;
			}
				
			if (value < 0) 
				value = 0;
			
			var baseStatText:TextField = baseStatTextFields[valueType];
			if (baseStatText == null) return;
			
			if (valueType == EStat.STAT_LIFE||valueType == EStat.STAT_ENERGY)
			{	
				baseStatAddTextFields[valueType].textColor = ColorUtils.GetColorBySighn(addition,defaultColor);
				baseStatTooltipFields[valueType].SetTooltipPositionAndSize(baseStatTextFieldsNames[valueType],baseStatTextFields[valueType],baseStatAddTextFields[valueType]);
				return
			}
			
			if (valueType != EStat.STAT_LIFE && valueType != EStat.STAT_ENERGY) 
				SetAddition(baseStatText, value, addition);
			
			baseStatTooltipFields[valueType].SetTooltipPositionAndSize(baseStatTextFieldsNames[valueType],baseStatTextFields[valueType],baseStatAddTextFields[valueType]);
		}
		
		private function SetAddition(tf:TextField, value:int, addition:int):void
		{
			if (tf == null) return;
			
			var statValue:int = value + addition;
			
			if (statValue < 0) statValue = 0;
			
			tf.text = statValue.toString();

			tf.textColor = ColorUtils.GetColorBySighn(addition,defaultColor);
		}
		public function ChangeSelectionCharStatTooltipCommands(isSelection:Boolean):void
		{
			for (var i:int = 0; i < baseStatTextFields.length; i++)
			{
				if (baseStatTextFields[i] != null)
					baseStatTooltipFields[i].ChangeCharStatTooltipCommands(isSelection);
			}
			
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_DAMAGEMAX].ChangeCharStatTooltipCommands(isSelection);
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_ATTACKSPERSECOND].ChangeCharStatTooltipCommands(isSelection);
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_CRITCHANCE].ChangeCharStatTooltipCommands(isSelection);
			
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_PENETRATIONTOTAL].ChangeCharStatTooltipCommands(isSelection);
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_SPIRITDEFENCE].ChangeCharStatTooltipCommands(isSelection);
			derivativeStatTooltipFields[EDerivativeStat.DERIVATIVESTAT_BODYDEFENCE].ChangeCharStatTooltipCommands(isSelection);
		}
		
		public function SetDeathTimeOut(timeLeft:int):void
		{
			if (deathTime == null) return;
			
			deathTime.visible = timeLeft > 0;
			deathTime.Time = timeLeft;
			
			if (isDeathTimeShowing == timeLeft > 0) return;
			
			if (timeLeft > 0)
			{
				selfShadow_mc.visible = true;
				selfShadow_mc.gotoAndPlay('death');
			}
			else 
			{
				selfShadow_mc.visible = true;
				selfShadow_mc.gotoAndPlay("life");
			}

			isDeathTimeShowing = timeLeft > 0;
		}
		
		private function setHeroInfoIcon(path:String, isAnimatedAvatar:Boolean):void 
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
				heroInfo_mc.SetIcon(path);
			}
		}
		
		private function setHeroInfoBorder(leagueIndex:int):void 
		{			
			elitHero.setLeagueIndex(leagueIndex);
			
			// BORDER
			
			border1.visible = false;
			border2.visible = false;
			border3.visible = false;
			border4.visible = false;
			border11.visible = false;
			border12.visible = false;
			border13.visible = false;
			border14.visible = false;
			border21.visible = false;
			border22.visible = false;
			border23.visible = false;
			border24.visible = false;
			border31.visible = false;
			border32.visible = false;
			border33.visible = false;
			border34.visible = false;
			border41.visible = false;
			border42.visible = false;
			border43.visible = false;
			border44.visible = false;
			border51.visible = false;
			border52.visible = false;
			border53.visible = false;
			border54.visible = false;
			border61.visible = false;
			border62.visible = false;
			border63.visible = false;
			border64.visible = false;
			border71.visible = false;
			border72.visible = false;
			border73.visible = false;
			border74.visible = false;
			border81.visible = false;
			border82.visible = false;
			border83.visible = false;
			border84.visible = false;
			
			// 1
			if ( leagueIndex == 4 ) {
				border1.visible = true;
			}
			else if ( leagueIndex == 5 ) {
				border2.visible = true;
			}
			else if ( leagueIndex == 6 ) {
				border3.visible = true;
			}
			else if ( leagueIndex == 7 ) {
				border4.visible = true;
			}
			
			// 2
			else if ( leagueIndex == 8 ) {
				border11.visible = true;
			}	
			else if ( leagueIndex == 9 ) {
				border12.visible = true;
			}	
			else if ( leagueIndex == 10 ) {
				border13.visible = true;
			}	
			else if ( leagueIndex == 11 ) {
				border14.visible = true;
			}	
			
			// 3
			else if ( leagueIndex == 12 ) {
				border21.visible = true;
			}
			else if ( leagueIndex == 13 ) {
				border22.visible = true;
			}
			else if ( leagueIndex == 14 ) {
				border23.visible = true;
			}
			else if ( leagueIndex == 15 ) {
				border24.visible = true;
			}			
			
			// 4
			else if ( leagueIndex == 16 ) {
				border31.visible = true;
			}
			else if ( leagueIndex == 17 ) {
				border32.visible = true;
			}
			else if ( leagueIndex == 18 ) {
				border33.visible = true;
			}
			else if ( leagueIndex == 19 ) {
				border34.visible = true;
			}
			
			// 5
			else if ( leagueIndex == 20 ) {
				border41.visible = true;
			}
			else if ( leagueIndex == 21 ) {
				border42.visible = true;
			}
			else if ( leagueIndex == 22 ) {
				border43.visible = true;
			}
			else if ( leagueIndex == 23 ) {
				border44.visible = true;
			}
			
			// 6
			else if ( leagueIndex == 24 ) {
				border51.visible = true;
			}
			else if ( leagueIndex == 25 ) {
				border52.visible = true;
			}
			else if ( leagueIndex == 26 ) {
				border53.visible = true;
			}
			else if ( leagueIndex == 27 ) {
				border54.visible = true;
			}
			
			// 7
			else if ( leagueIndex == 28 ) {
				border51.visible = true;
			}
			else if ( leagueIndex == 29 ) {
				border52.visible = true;
			}
			else if ( leagueIndex == 30 ) {
				border53.visible = true;
			}
			else if ( leagueIndex == 31 ) {
				border54.visible = true;
			}
			
			// 8
			else if ( leagueIndex == 32 ) {
				border51.visible = true;
			}
			else if ( leagueIndex == 33 ) {
				border52.visible = true;
			}
			else if ( leagueIndex == 34 ) {
				border53.visible = true;
			}
			else if ( leagueIndex == 35 ) {
				border54.visible = true;
			}
			
			// 9
			else if ( leagueIndex == 36 ) {
				border51.visible = true;
			}
			else if ( leagueIndex == 37 ) {
				border52.visible = true;
			}
			else if ( leagueIndex == 38 ) {
				border53.visible = true;
			}
			else if ( leagueIndex == 39 ) {
				border54.visible = true;
			}
			
			// 10
			else if ( leagueIndex == 40 ) {
				border61.visible = true;
			}
			else if ( leagueIndex == 41 ) {
				border62.visible = true;
			}
			else if ( leagueIndex == 42 ) {
				border63.visible = true;
			}
			else if ( leagueIndex == 43 ) {
				border64.visible = true;
			}
			
			// 11
			else if ( leagueIndex == 44 ) {
				border61.visible = true;
			}
			else if ( leagueIndex == 45 ) {
				border62.visible = true;
			}
			else if ( leagueIndex == 46 ) {
				border63.visible = true;
			}
			else if ( leagueIndex == 47 ) {
				border64.visible = true;
			}
			
			// 12
			else if ( leagueIndex == 48 ) {
				border71.visible = true;
			}
			else if ( leagueIndex == 49 ) {
				border72.visible = true;
			}
			else if ( leagueIndex == 50 ) {
				border73.visible = true;
			}
			else if ( leagueIndex == 51 ) {
				border74.visible = true;
			}
			
			// 13
			else if ( leagueIndex == 52 ) {
				border71.visible = true;
			}
			else if ( leagueIndex == 53 ) {
				border72.visible = true;
			}
			else if ( leagueIndex == 54 ) {
				border73.visible = true;
			}
			else if ( leagueIndex == 55 ) {
				border74.visible = true;
			}
			
			// 14
			else if ( leagueIndex == 56 ) {
				border81.visible = true;
			}
			else if ( leagueIndex == 57 ) {
				border82.visible = true;
			}
			else if ( leagueIndex == 58 ) {
				border83.visible = true;
			}
			else if ( leagueIndex == 59 ) {
				border84.visible = true;
			}
			
			// 15
			else if ( leagueIndex == 60 ) {
				border81.visible = true;
			}
			else if ( leagueIndex == 61 ) {
				border82.visible = true;
			}
			else if ( leagueIndex == 62 ) {
				border83.visible = true;
			}
			else if ( leagueIndex == 63 ) {
				border84.visible = true;
			}
			
			// 16
			else if ( leagueIndex == 64 ) {
				border81.visible = true;
			}
			else if ( leagueIndex == 65 ) {
				border82.visible = true;
			}
			else if ( leagueIndex == 66 ) {
				border83.visible = true;
			}
			else if ( leagueIndex == 67 ) {
				border84.visible = true;
			}
			
			// 17
			else if ( leagueIndex == 68 ) {
				border81.visible = true;
			}
			else if ( leagueIndex == 69 ) {
				border82.visible = true;
			}
			else if ( leagueIndex == 70 ) {
				border83.visible = true;
			}
			else if ( leagueIndex == 71 ) {
				border84.visible = true;
			}
			
			// LEVEL
				
			level2.visible = false;
			level3.visible = false;
			level4.visible = false;
			level5.visible = false;			
			level5_s2.visible = false;
			
			switch (leagueIndex) {
				// бронза
				case 4:
				case 8:
				case 12:
				case 16:
				case 20:
				case 24:
				case 28:
				case 32:
				case 36:
				case 40:
				case 44:
				case 48:
				case 52:
				case 56:
				case 60:
				case 64:
				case 68:
					level2.visible = true;
					break;
					
				// серебро
				case 5:
				case 9:
				case 13:
				case 17:
				case 21:
				case 25:
				case 29:
				case 33:
				case 37:
				case 41:
				case 45:
				case 49:
				case 53:
				case 57:
				case 61:
				case 65:
				case 69:
					level3.visible = true;
					break;
					
				// золото
				case 6:
				case 10:
				case 14:
				case 18:
				case 22:
				case 26:
				case 30:
				case 34:
				case 38:
				case 42:
				case 46:
				case 50:
				case 54:
				case 58:
				case 62:
				case 66:
				case 70:
					level4.visible = true;
					break;
					
				// легенда (кроме 2 сезона)
				case 7:
				//case 11:
				case 15:
				case 19:
				case 23:
				case 27:
				case 31:
				case 35:
				case 39:
				case 43:
				case 47:
				case 51:
				case 55:
				case 59:
				case 63:
				case 67:
				case 71:
					level5.visible = true;
					break;
					
				// легенда (2 сезона)
				case 11:
					level5_s2.visible = true;
					break;
			}
		}
	}
}
