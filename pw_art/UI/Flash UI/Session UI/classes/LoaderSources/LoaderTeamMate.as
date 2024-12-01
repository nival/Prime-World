package LoaderSources
{
	import BaseClasses.BaseIconLoader;
	import Components.FlagFormater;
	import Components.HeroClassIcon;
	import Components.PremiumShields;
	import Controllers.TextFieldFormater;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.display.Bitmap;
	import BaseClasses.MateInfoBase;
	import Components.Bar;
	import src.ButtonTooltipEvent;
	import Utils.AnimatedPortraitsUtils;
	
	public class LoaderTeamMate extends MateInfoBase
	{
		public var loadingBar_mc:Bar;
		public var heroName_txt:TextField;
		public var lensFlare:MovieClip;
		public var raitingBar:LoaderHeroRaitingBar;
		
		//public var chainlock:MovieClip;
		
		private var _percent:Number = 0;
		private var isPlayerLeftGame:Boolean = false;
		private var maxBarValue:Number = 100;
		
		private var nameText:TextFieldFormater;
		//public var loaderFlag:FlagFormater;
		
		public var premiumIcon_mc:PremiumShields;
		public var guildAbbr_mc:LoaderGuildAbbr;
		
		public var classIcon:HeroClassIcon
		
		public var animatedIcoContainer:MovieClip;
		
		public function LoaderTeamMate()
		{
			loadingBar_mc.setMaxBar(maxBarValue);
			loadingBar_mc.setValue(0);
			this.visible = false;
			lensFlare.visible = false;
			levelRoundFrame.visible = false;
			level_txt.visible = false;
			flag.visible = false;
			redBack.visible = false;
					
			guildAbbr_mc.frame.x = (this.width - guildAbbr_mc.width) / 2;
			removeChild(blueGlow_mc);
			nameText = new TextFieldFormater(heroName_txt);
		}
		override protected function AddedToStage(e:Event):void 
		{
			super.AddedToStage(e);
			this.setChildIndex(flag, numChildren - 1);
		}
		override public function get heroName():String 
		{
			return nameText.Text;
		}
		
		override public function set heroName(value:String):void 
		{
			if (value == null || value == "") return;
			nameText.Text = value;
		}
		
		override public function SetHeroNameColor(color:uint):void 
		{
			heroName_txt.textColor = color;
			redBack.visible = (heroName_txt.textColor == 0xff0000);
		}
		
		/*override public function SetHeroGuildColor(color:uint):void 
		{
			guildAbbr_mc.abbr_txt.textColor = color;
		}*/
		
		public function SetFlag(flagIcon:String, flagTooltipPath:String)
		{
			if (flag != null && (flagIcon != null || flagIcon!=""))
			{
				flag.Icon = flagIcon;
				flag.TooltipText = flagTooltipPath
			}
			flag.visible = flagIcon != null && flagIcon != "";
		}
		
		override public function get level():int 
		{
			return -1;
		}
	
		public function set LoadingProgressBar(persent:Number)
		{
			if (persent < 0)
				persent = 0;
				
			_percent = persent;
			
			loadingBar_mc.setValue(persent);
		}
		
		public function get LoadingProgressBar():Number
		{
			if (isPlayerLeftGame)
				return maxBarValue;
				
			return _percent;
		}
		
		public function PlayerDisconnected(isLeftGame:Boolean)
		{
			isPlayerLeftGame = isLeftGame;
			
			if(isLeftGame)
				SetLeaverIcon();
			else
				RemoveLeaverIcon()
				
			SetGreyMask(isLeftGame);
		}
		
		public function GetMateWidth():Number
		{
			return roundFrame.width+2;
		}
		
		public function SetHeroLevel(value:int):void 
		{
			level_txt.visible = true;
			lensFlare.visible = true;
			levelRoundFrame.visible = true;
			level_txt.text = value.toString();
		}
		
		public function SetHeroRaiting(raiting:int, deltaWin:Number, deltaLose:Number,rankIcon:String, rankTooltip:String):void 
		{
			
			if (raitingBar == null ) return;
			raitingBar.SetHeroRaiting(isItOurHero, raiting, deltaWin, deltaLose, rankIcon, rankTooltip);
		}
		
		public function SetPremium(hasPremium:Boolean, originalFraction:int, heroName:String):void 
		{
			premiumIcon_mc.SetPremium(hasPremium, originalFraction, heroName);
			premiumIcon_mc.visible = false;
		}
		
		override protected function ShowContextMenu(e:MouseEvent):void 
		{
			
		}
		
		override public function setHeroInfoIcon(path:String, isAnimatedAvatar:Boolean):void 
		{
			var classObject:Object = AnimatedPortraitsUtils.FindClassObject(path, isAnimatedAvatar);
			
			// нашли подходящий анимированный портрет - грузим анимацию
			if (classObject != null)
			{
				AnimatedPortraitsUtils.ClearContainer(animatedIcoContainer);
								
				heroIco_mc.visible = false;
				animatedIcoContainer.visible = true;
				
				var iconClass:Class = classObject as Class;
				var animatedIcon:MovieClip = new iconClass();
				animatedIcoContainer.addChild(animatedIcon);
				
				// размер иконки 166, размер места под иконку 108
				// 108 / 166 == 0.63
				animatedIcon.scaleX = 0.65;
				animatedIcon.scaleY = 0.65;
			}
			else
			{
				heroIco_mc.visible = true;
				animatedIcoContainer.visible = false;
				super.setHeroInfoIcon(path, false);
			}
		}
	}
}