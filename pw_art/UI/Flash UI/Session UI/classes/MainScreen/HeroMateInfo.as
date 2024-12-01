package MainScreen
{
	import classes.SmartChat.SmartChatEvent;
	import Components.ButtonRound;
	import classes.ContMenu.ContextItemFollow;
	import ContMenu.ContextItemCharstat;
	import ContMenu.ContextItemTalants;
	import Controllers.TextFieldFormater;
	import flash.display.MovieClip;
	import flash.display.Loader;
	import flash.net.URLRequest;
	import flash.events.MouseEvent;
	import flash.text.TextFieldAutoSize;
	import fl.motion.easing.Back;
	import flash.text.TextField;
	import Events.ContextMenuEvent;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import BaseClasses.MateInfoBase;
	import Utils.AnimatedPortraitsUtils;
	
	public class HeroMateInfo extends MateInfoBase
	{	
		private var _healthBar:Object = null;
		private var _manaBar:Object = null;
		private var _heroName:String;
		private var heroNameHolder:TextFieldFormater
		private var _isNPCShowing:Boolean;
		private var _heroIcon:String;
		private var _currentIcon:String;
		
		//reference
		public var name_txt:TextField;
		public var heroLevelBack:MovieClip;
		public var flshFX_mc:MovieClip;
		public var chatBtn:ButtonRound;
		
		private var ldr:Loader = new Loader();	
		private var mcExt:MovieClip;
		
		public var animatedIcoContainer:MovieClip;
		
		public function HeroMateInfo() 
		{	
			this.doubleClickEnabled = true;
			this.buttonMode = true;

			flshFX_mc.mouseEnabled = false;
			name_txt.autoSize = TextFieldAutoSize.LEFT;
			name_txt.mouseEnabled = false;
			
			heroNameHolder = new TextFieldFormater(name_txt);
			level = 1;
			selfShadow_mc.mouseEnabled = false;
			selfShadow_mc.mouseChildren = false;
			//художники просили чтоб на нижнем портрете овер был более прозрачным чем у маленьких портретов
			onOverEffect.alpha = 0.8;
			
			chatBtn.addEventListener("Up", SmartChatToggle);
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, OnLocalizationComplete);
				
			FillLocalization();
			
			function onAddedToStage(e:Event):void
			{
				root.addEventListener(SmartChatEvent.ACTIVATED, OnSmartChatActivated);
				root.addEventListener(SmartChatEvent.DEACTIVATED, OnSmartChatDeactivated);
			}
			
			function onRemovedFromStage(e:Event):void
			{
				root.removeEventListener(SmartChatEvent.ACTIVATED, OnSmartChatActivated);
				root.removeEventListener(SmartChatEvent.DEACTIVATED, OnSmartChatDeactivated);
			}
			
			addEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
			addEventListener(Event.REMOVED_FROM_STAGE, onRemovedFromStage);
		}
		
		private function OnLocalizationComplete(e:Event):void
		{
			FillLocalization();
		}
		
		private function FillLocalization():void
		{
			chatBtn.Tooltip = Localization.Tooltip_chatBtn;
			chatBtn.TogledTooltip = Localization.Tooltip_chatBtn;
		}
		
		private function SmartChatToggle(e:Event):void
		{
			e.stopPropagation();
			
			dispatchEvent(new Event(SmartChatEvent.TOGGLE));
		}
		
		private function OnSmartChatActivated(e:Event):void
		{
			chatBtn.SwitchOn();
		}
		
		private function OnSmartChatDeactivated(e:Event):void
		{
			chatBtn.SwitchOff();
		}
		
		override protected function Init():void 
		{
			if (selfShadow_mc == null)
				return;

			selfShadow_mc.stop();
		}
		
		override public function SetHeroParams(curHealth:int,maxHealth:int,curMana:int,maxMana:int,healthRegen:Number=0,manaRegen:Number=0,animate:Boolean = true): void
		{
			if (_healthBar == null || _manaBar==null)
				return;
				
			_healthBar.setMaxBar(maxHealth,animate);
			_healthBar.setValue(curHealth,healthRegen,animate);

			_manaBar.setMaxBar(maxMana,animate);
			_manaBar.setValue(curMana,manaRegen,animate);
						
		}
				
		public function set healthBar(value:Object):void
		{
			_healthBar = value;
		}
		
		public function set manaBar(value:Object):void
		{
			_manaBar = value;
		}
		
	  	override public function set heroName(name:String):void
		{
			_heroName = name;
			
			if (_isNPCShowing) return;
			
			heroNameHolder.Text = _heroName;
			//name_txt.text = _heroName;
		}
		
		override public function SetHeroNameColor(color:uint):void 
		{
			name_txt.textColor = color;
		} 
		
		override public function SetRedBackVisibility(isVisible:Boolean):void
		{
			redBack.visible = isVisible;
		}
				
		override public function setHeroInfoIcon(path:String, isAnimatedAvatar:Boolean):void 
		{
			_heroIcon = path;
			
			if (_isNPCShowing) return;
			
			_currentIcon = path;
			
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
				
				// размер иконки 166, размер места под иконку 176
				// 176 / 166 == 1,06
				animatedIcon.scaleX = 1.06;
				animatedIcon.scaleY = 1.06;
			}
			else
			{
				heroIco_mc.visible = true;
				animatedIcoContainer.visible = false;
				super.setHeroInfoIcon(path, false);
			}
		}
		
	    override protected function onDown(e:MouseEvent):void
		{
			FSCommands.Send(FSCommands.HERO_CLICK, _id.toString());
		}

		override protected function onUp(e:MouseEvent = null):void
		{
			FSCommands.Send(FSCommands.HERO_LOSTFOCUS);
		}

		override protected function onDoubleClick(e:MouseEvent):void
		{
			FSCommands.Send(FSCommands.HERO_DOUBLECLICK, _id.toString());
			e.stopPropagation();
		}
		
		override protected function ShowContextMenu(e:MouseEvent):void 
		{
			if (!_isNPCShowing)
				super.ShowContextMenu(e);
		}
		
		public function ShowNPC(iconPath:String, name:String):void
		{
			if (iconPath != _currentIcon)
				flshFX_mc.gotoAndPlay(2);
			
			_currentIcon = iconPath;
			_isNPCShowing = true;
			heroNameHolder.Text = name;
			
			super.setHeroInfoIcon(iconPath, false);
			heroLevelBack.visible = false;
			level_txt.visible = false;
		}
		
		public function HideNPC():void
		{
			_isNPCShowing = false;
			
			if (_currentIcon!=_heroIcon)
				flshFX_mc.gotoAndPlay(2);
				
			heroNameHolder.Text = _heroName;
			_currentIcon = _heroIcon;
			super.setHeroInfoIcon(_heroIcon, false);
			heroLevelBack.visible = true;
			level_txt.visible = true;
		}
		
		override protected function StartGlow():void 
		{
			if (_isNPCShowing) return;
			
			super.StartGlow();
		}
	}
}