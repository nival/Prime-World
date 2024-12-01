package MainScreen
{
	import Controllers.TextFieldFormater;
	import Events.ContextMenuEvent;
	import Events.WindowVisibleControllerEvent;
	import flash.display.MovieClip;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import Strokes.LevelStroke;

	import BaseClasses.MateInfoBase;
	import Components.Bar;
	import Events.MouseRightEvents;
	import Enums.EWindows;
	
	import Utils.AnimatedPortraitsUtils;
	
	public class MateInfo extends MateInfoBase
	{
		//reference
		
		public var nameText:TextField;
		public var healthBar_mc:Bar;
		public var manaBar_mc:Bar;
		
		private var onFocus:Boolean = false;
		
		private var formatedName:TextFieldFormater;
		
		public var animatedIcoContainer:MovieClip;

		public function MateInfo()
		{
			this.doubleClickEnabled = true;
			this.buttonMode = true;
			
			this.visible = false;
			
			formatedName = new TextFieldFormater(nameText);
			nameText.mouseEnabled = false;
			
			manaBar_mc.mouseEnabled = false;
			healthBar_mc.mouseEnabled = false;
			roundFrame.mouseEnabled = false;
			roundFrame.mouseChildren = false;			
			
			Init();
		}
		
		override protected function onDown(e:MouseEvent):void
		{	
			FSCommands.Send(FSCommands.HERO_CLICK, _id.toString());
			onFocus = true;
		}

		override protected function onUp(e:MouseEvent = null):void
		{
			if (onFocus) 
			{ 
				FSCommands.Send(FSCommands.HERO_LOSTFOCUS); 
				onFocus = false
			}
		}
		
		override protected function onDoubleClick(e:MouseEvent):void
		{	
			FSCommands.Send(FSCommands.HERO_DOUBLECLICK,_id.toString());
		}

		override public function set heroName(name:String):void
		{
			super.heroName = name;
			formatedName.Text = name;
		}

		override public function get heroName():String
		{
			return super.heroName;
		}
			
		protected function get healthBar():Bar
		{
			return healthBar_mc;
		}
		
		protected function get manaBar():Bar
		{
			return manaBar_mc;
		}
		
		override public function SetHeroParams(curHealth:int,maxHealth:int,curMana:int,maxMana:int,healthRegen:Number=0,manaRegen:Number=0,animate:Boolean = true):void
		{
			if (healthBar != null)
			{
				healthBar.setMaxBar(maxHealth, animate);
				healthBar.setValue(curHealth,healthRegen, animate);
			}

			if (manaBar != null)
			{
				manaBar.setMaxBar(maxMana, animate);
				manaBar.setValue(curMana, manaRegen, animate);
			}
		}
		
		override public function SetHeroNameColor(color:uint):void 
		{
			nameText.textColor = color;			
		} 
		
		override public function SetRedBackVisibility(isVisible:Boolean):void
		{
			redBack.visible = isVisible;
		}
		
		override public function SetGreyMask(setMask:Boolean):void
		{	
			super.SetGreyMask(setMask);
			if (isVisible == false) onUp();
		}
		
		override public function ShowTutorialLevelHighlight(show:Boolean):void 
		{
			if (show)
			{
				if (tutorialLevelHighlight != null) return;
			
				tutorialLevelHighlight = new LevelStroke();
				tutorialLevelHighlight.x = roundFrame.x - 4;
				tutorialLevelHighlight.y = roundFrame.y - 2;
				this.addChild(tutorialLevelHighlight);
			}
			else
			{
				if (tutorialLevelHighlight!=null)
					this.removeChild(tutorialLevelHighlight);
			}
		}
		
		override public function set ManaBarColor(value:uint):void
		{
			manaBar.barColor = value;
		}
		
		override public function set ManaBarShowRegeneration(value:Boolean):void
		{
			manaBar.ShowRegenerationText = value;
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
				
				// размер иконки 166, размер места под иконку 72
				// 72 / 166 == 0.43
				animatedIcon.scaleX = 0.43;
				animatedIcon.scaleY = 0.43;
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