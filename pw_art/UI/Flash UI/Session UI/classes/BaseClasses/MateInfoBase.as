package BaseClasses
{

	import Components.FlagFormater;
	import ContMenu.*;
	import Datas.LeaverIconData;
	import Datas.PlayerStatisticData;
	import Events.ContextMenuEvent;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import flash.text.TextFieldAutoSize;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.utils.getDefinitionByName;
	import flash.display.Bitmap;
	import flash.display.BlendMode;
	import Interfaces.IMate;
	import Strokes.HeroStroke;
	import Strokes.SquadStroke;
	import Strokes.LevelStroke;
	import Strokes.Stroke;
	
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import fl.transitions.TweenEvent;

	import Components.FormatedTimer;
	import Events.DetailedStatisticMateEvent;
	import Enums.EMateInfoIcons;
	import MainScreen.MateInfoIcons;
	import Components.RoundFrame;
	import Components.HeroIco;
	import Events.MouseRightEvents;
	
	public class MateInfoBase extends MovieClip implements IMate
	{

		private var _isBusy:Boolean = false;
		private var _sorted:Boolean = false;
		protected var _id:int = -1;
		protected var _level:int = -1;

		private var sec:Number;
		private var min:Number;
		protected var isVisible:Boolean = true;
		private var isDeathTimeShowing:Boolean = false;
		
		private var _isHeroLeft:Boolean = false;
		
		//reference
		public var deathTime:FormatedTimer;
		public var leaverIco_mc:MovieClip;
		public var roundFrame:RoundFrame;
		public var levelRoundFrame:RoundFrame;
		
		public var male:MovieClip;
		public var female:MovieClip;
		
		public var male_mc:MovieClip;
		public var favoritIco1_mc:MovieClip;
		public var favoritIco2_mc:MovieClip;
		public var favoritIco3_mc:MovieClip;
		public var favoritIco4_mc:MovieClip;

		public var ultimatecd:MovieClip;
		public var cooldown_glow:MovieClip;
		
		public var female_mc:MovieClip;
		public var coupleIco1_mc:MovieClip;
		public var coupleIco2_mc:MovieClip;
		public var coupleIco3_mc:MovieClip;
		public var coupleIco4_mc:MovieClip;
		
		public var heroIco_mc:HeroIco;
		public var level_txt:TextField;
		
		public var disconnectIco_mc:MovieClip;
		public var newGamer_mc:MovieClip;
		
		public var deathMask_mc:MovieClip;
		public var selfShadow_mc:MovieClip;
		public var levelHighLight:MovieClip;
		
		public var blueGlow_mc:MovieClip;
		private var blueGlowTween:Tween;
		protected var selectionEffect:MovieClip;
		protected var onOverEffect:MovieClip;
		
		private var iconName:String="none";
		private var positionX:Number=0;
		private var positionY:Number=0;
		
		private var isMateInFinalStatistic:Boolean = false;
		public var mouseCatcher:MovieClip;
		
		private var _isItOurHero:Boolean = false;
		public var isHeroIgnored:Boolean;
		public var IsBot:Boolean;
		public var SpectatorMode:Boolean = false;
		
		private var leavBitm:Bitmap;
		private var _heroName:String;
		private var _heroFullName:String;
		private var _isSelected:Boolean;
		private var tutorialHighlight:HeroStroke;
		protected var tutorialLevelHighlight:Stroke;
		private var isFriend:Boolean;
		private var isPending:Boolean;
		protected var contMenuAddToFriend:ContextItemAddFriend
		
		private var LeaveIcons:Array = new Array();
		private var _currentIconIndex:int = -1;
		public var flag: FlagFormater;
		public var redBack:MovieClip;
		
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
		
		public function MateInfoBase()
		{
		//	this.mouseChildren = false;
			if (levelHighLight != null)
			{
				levelHighLight.mouseEnabled = false;
			}
		
			if (male != null)
				male.visible = false;
			
			if (female != null)
				female.visible = false;
			
			if (mouseCatcher != null) 
			{
				mouseCatcher.alpha = 0;
				mouseCatcher.buttonMode = true;
				mouseCatcher.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
				mouseCatcher.addEventListener(MouseEvent.MOUSE_OVER, onOver);
				mouseCatcher.addEventListener(MouseEvent.MOUSE_UP, onUp);
				mouseCatcher.addEventListener(MouseEvent.MOUSE_OUT, onOut);
				mouseCatcher.addEventListener(MouseEvent.DOUBLE_CLICK, onDoubleClick);
				mouseCatcher.addEventListener(MouseRightEvents.RIGHT_CLICK, ShowContextMenu);
			}
			else 
			{
				this.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
				this.addEventListener(MouseEvent.MOUSE_OVER, onOver);
				this.addEventListener(MouseEvent.MOUSE_UP, onUp);
				this.addEventListener(MouseEvent.MOUSE_OUT, onOut);
				this.addEventListener(MouseEvent.DOUBLE_CLICK, onDoubleClick);
				this.addEventListener(MouseRightEvents.RIGHT_CLICK, ShowContextMenu);
			}
	
			onOverEffect = new OverEffect();
			onOverEffect.x = 1;
			onOverEffect.y = 1;
			onOverEffect.stop();
			onOverEffect.width = roundFrame.width - 2;
			onOverEffect.height = roundFrame.height - 2;
			onOverEffect.blendMode = BlendMode.ADD;
			
			selectionEffect = new SelectionEffect();
			selectionEffect.x = 1;
			selectionEffect.y = 1;
			selectionEffect.stop();
			selectionEffect.width = roundFrame.width - 2;
			selectionEffect.height = roundFrame.height - 2;
			selectionEffect.blendMode = BlendMode.ADD;
			
			selectionEffect.mouseEnabled = false;
			selectionEffect.mouseChildren = false;
			onOverEffect.mouseEnabled = false;
			onOverEffect.mouseChildren = false;
			
			if (blueGlow_mc != null )
			{
				blueGlow_mc.visible = false;
				blueGlowTween = new Tween(blueGlow_mc, 'alpha', Strong.easeInOut,0, 1, 15, false);
				blueGlowTween.addEventListener(TweenEvent.MOTION_FINISH, GlowFinish);
				blueGlowTween.stop();
			}
			addEventListener(Event.ADDED_TO_STAGE, AddedToStage);
			
			if (heroIco_mc != null) {
				heroIco_mc.mouseEnabled = false;
				heroIco_mc.mouseChildren = false;
			}
			
			if (redBack != null)
				 redBack.visible = false;
			
			if (border1 != null) {
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
			}
		}
		
		protected function GetContextMenuList():Array 
		{
			var contextMenuList:Array = new Array();
			contextMenuList.push(new ContextItemCharstat(id != -1, Localization.ContextMenu_Character, isMateInFinalStatistic?false: isItOurHero, id));
			if (id != -1) 
				contextMenuList.push(new ContextItemTalants(true, Localization.ContextMenu_Talents, isMateInFinalStatistic? false: isItOurHero, id));
				
			if (!isItOurHero && id != -1 && heroName != "" && !IsBot)
			{
				if (SpectatorMode)
				{
					trace("ContextItemSwitchToSpectate " + id.toString());
					if(!isMateInFinalStatistic)
						contextMenuList.push(new ContextItemSwitchToSpectate(true, Localization.ContextMenu_StartSpectate, isItOurHero, id));
				}
				else
				{
					if (isHeroIgnored)
					{
						contextMenuList.push(new ContextItemRemoveIgnore(true, Localization.ContextMenu_RemoveIgnore, isItOurHero, id));
					}
					else
					{
						contextMenuList.push(new ContextItemIgnore(true, Localization.ContextMenu_Ignore, isItOurHero, id));
					}
					
					if (!isFriend && !isPending)
					{
						contMenuAddToFriend = new ContextItemAddFriend(true, Localization.ContextMenu_AddFriend, isItOurHero, id)
						contextMenuList.push(contMenuAddToFriend);
					}
					
					if (!isItOurHero)
					{
						contextMenuList.push(new ContextItemReportWindow(true, Localization.ContextMenu_Complain, heroFullName, isItOurHero, id));
					}
				}
			}
/*			
			trace("Fill context menu");
			
			
			for each (var item: BaseContextItem in contextMenuList)
			{
				trace("type = ", item, ", negative = ", item.IsNegativeItem, ", name = ", item.Name);
			}
*/			
			return contextMenuList;
		}
		
		protected function AddedToStage(e:Event):void
		{
			removeEventListener(Event.ADDED_TO_STAGE, AddedToStage);
			addChild(onOverEffect);
			addChild(selectionEffect);
			
			onOverEffect.mouseEnabled = false;
			onOverEffect.mouseChildren = false;
			
			selectionEffect.mouseEnabled = false;
			selectionEffect.mouseChildren = false;
			
			
			this.setChildIndex(selectionEffect, this.getChildIndex(roundFrame) -1);
			this.setChildIndex(onOverEffect, this.getChildIndex(roundFrame) - 1);
			if (mouseCatcher!=null)
				this.setChildIndex(mouseCatcher, this.numChildren - 1);
			Init();
		}
		
		protected function Init():void
		{	
			if (deathMask_mc != null)
			{
				deathMask_mc.stop();
				deathMask_mc.visible = false;
				deathMask_mc.mouseEnabled = false;
				deathMask_mc.mouseChildren = false;
			}
			if(selfShadow_mc != null)
			{
				selfShadow_mc.stop();
				selfShadow_mc.mouseEnabled = false;
				selfShadow_mc.mouseChildren = false;
				selfShadow_mc.visible = false;
			}
			
			if (deathTime != null) deathTime.visible = false;
			if (leaverIco_mc != null) 
			{
				var leaveIcon:LeaverIconData = new LeaverIconData();
				leaveIcon.IconName = "leaver";
				leaveIcon.IconHeight = leaverIco_mc.height;
				leaveIcon.IconWidth = leaverIco_mc.width;
				leaveIcon.IconDepth = this.getChildIndex(leaverIco_mc);
				leaveIcon.IconPosition.x = leaverIco_mc.x;
				leaveIcon.IconPosition.y = leaverIco_mc.y;
				
				LeaveIcons[LeaverIconData.LeaverIcon] = leaveIcon;
				
				this.removeChild(leaverIco_mc);
				leaverIco_mc = null;
			}
			
			if (disconnectIco_mc != null) 
			{
				var disconnect:LeaverIconData = new LeaverIconData();
				disconnect.IconName = "disconnectIco";
				disconnect.IconHeight = disconnectIco_mc.height;
				disconnect.IconWidth = disconnectIco_mc.width;
				disconnect.IconDepth = this.getChildIndex(disconnectIco_mc);
				disconnect.IconPosition.x = disconnectIco_mc.x;
				disconnect.IconPosition.y = disconnectIco_mc.y;
				
				LeaveIcons[LeaverIconData.DisconnectIcon] = disconnect;
				
				this.removeChild(disconnectIco_mc);
				disconnectIco_mc = null;
			}
			if (newGamer_mc != null) 
				newGamer_mc.visible = false;
			
			level = 1;
			level_txt.autoSize = TextFieldAutoSize.CENTER;
		}		
		
		protected function onOver(e:MouseEvent):void
		{
			if (onOverEffect == null) return;
			
			onOverEffect.gotoAndPlay('over')
			onOverEffect.visible = true;
		}
		
		protected function onDown(e:MouseEvent):void
		{
			dispatchEvent(new DetailedStatisticMateEvent(id));
		}
		
		protected function onUp(e:MouseEvent = null):void
		{
			
		}
		
		protected function onOut(e:MouseEvent):void
		{
			onUp(e);
			if (onOverEffect == null) return;
			onOverEffect.gotoAndPlay('out');
			onOverEffect.visible = true;
		}
		
		protected function onDoubleClick(e:MouseEvent):void
		{
			
		}
		
		protected function StartGlow():void
		{
			if (blueGlowTween == null ) return;
			
			blueGlow_mc.visible = true;
			blueGlowTween.stop();
			blueGlowTween.continueTo(1, 15);
			blueGlowTween.start();
		}
		private function GlowFinish(e:TweenEvent):void
		{
			if(e.target.finish == 0)
			{
				blueGlow_mc.visible = false;
				return;
			}
			blueGlowTween.continueTo(0, 15);
			blueGlowTween.start();
		}

		public function get isBusy():Boolean
		{
			return _isBusy;
		}

		public function set isBusy(busy:Boolean):void
		{
			_isBusy = busy;
		}
		
		public function setHeroInfoBorder(leagueIndex:int):void 
		{
			// leagueIndex - flash data index (не league index (id)) !
			
			if (border1 == null)
				return;
				
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
			
			
			// leagueIndex == 2 || 3 - нет рамок (деревянная и каменная лиги)
			
			// 1 клас
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
			
			// 2 летний
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
			
			// 3 осен
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
			
			// 4 зим
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
			
			// 5 вес
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
			
			// 6 лет
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
			
			// 7 осен
			else if ( leagueIndex == 28 ) {
				border61.visible = true;
			}
			else if ( leagueIndex == 29 ) {
				border62.visible = true;
			}
			else if ( leagueIndex == 30 ) {
				border63.visible = true;
			}
			else if ( leagueIndex == 31 ) {
				border64.visible = true;
			}
			
			// 8 зим
			else if ( leagueIndex == 32 ) {
				border71.visible = true;
			}
			else if ( leagueIndex == 33 ) {
				border72.visible = true;
			}
			else if ( leagueIndex == 34 ) {
				border73.visible = true;
			}
			else if ( leagueIndex == 35 ) {
				border74.visible = true;
			}
			
			// 9 вес
			else if ( leagueIndex == 36 ) {
				border81.visible = true;
			}
			else if ( leagueIndex == 37 ) {
				border82.visible = true;
			}
			else if ( leagueIndex == 38 ) {
				border83.visible = true;
			}
			else if ( leagueIndex == 39 ) {
				border84.visible = true;
			}
			
			// 10 лет
			else if ( leagueIndex == 40 ) {
				border81.visible = true;
			}
			else if ( leagueIndex == 41 ) {
				border82.visible = true;
			}
			else if ( leagueIndex == 42 ) {
				border83.visible = true;
			}
			else if ( leagueIndex == 43 ) {
				border84.visible = true;
			}
		}

		public function setHeroInfoIcon(path:String, isAnimatedAvatar:Boolean):void
		{
			heroIco_mc.SetIcon(path);
		}

		public function set id(id:int):void
		{
			_id = id;
		}
		
		public function get id():int
		{
			return _id;
		}

		public function get level():int
		{
			return _level;
		}

		public function set heroName(name:String):void
		{
			_heroName = name;
		}

		public function get heroName():String
		{
			return _heroName;
		}
		
		
		public function set heroFullName(name:String):void
		{
			_heroFullName = name;
		}

		public function get heroFullName():String
		{
			return _heroFullName;
		}

		public function SetHeroNameColor(color:uint):void 
		{
		} 
		
		public function SetRedBackVisibility(isVisible:Boolean):void
		{
		}
		
		public function set level(value:int):void
		{
			if(_level == value)
			{
				return;
			}
			
			_level = value;
			level_txt.text = _level.toString();
			StartGlow();
		}

		public function set ultcd(value:Number):void
		{
			if (ultimatecd == null)
				return;

			
			var setFrame:int = 1 + int((1.0 - value) * 29.0);

			if (ultimatecd.currentFrame == setFrame || setFrame == 2 /*какой-то баг со вторым кадром, хз че за фигня*/ )
				return;
				
			if (value < 0.0){
				ultimatecd.gotoAndStop(1);
				cooldown_glow.visible = false;
			}else{
				cooldown_glow.visible = false;
				ultimatecd.gotoAndStop(setFrame);
				if (ultimatecd.currentFrame == 30){
					cooldown_glow.visible = true;
					StartGlow();
				}
			}
		
		}
		
		public function get isItOurHero():Boolean 
		{
			return _isItOurHero;
		}
		
		public function set isItOurHero(value:Boolean):void 
		{
			_isItOurHero = value;
		}
		
		public function SetDeathTimeOut(timeLeft:int):void
		{
			if (_isHeroLeft) return;
			
			if (isMateInFinalStatistic) return;
			
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

		public function SetGreyMask(setMask:Boolean):void
		{	
			if (isMateInFinalStatistic) return;
			
			if (deathMask_mc == null) return;
			
			if (isVisible == !setMask) return;
			
			isVisible = !setMask;
			
			deathMask_mc.visible = setMask;
			if (deathMask_mc.visible) 
				deathMask_mc.gotoAndPlay(1);
		}
		
		public function SetViewInFinalStatistic():void
		{
			isMateInFinalStatistic = true;
			
			if (deathMask_mc == null) return;
		
			deathMask_mc.visible = _isHeroLeft;
			deathTime.visible = false;
			deathTime.Time = 0;
		}
		
		public function SetSelected(isSelect:Boolean):void
		{
			_isSelected = isSelect;
			if(isSelect)
			{
				selectionEffect.gotoAndPlay(1);
				selectionEffect.visible = true;
				return;
			}
			else
			{
				selectionEffect.gotoAndStop(1);
			}
		}
		
		public function IsSelected():Boolean
		{
			return _isSelected;
		}
		
		public function SetGender(isMale:Boolean):void
		{
			if (male!=null)
				male.visible = isMale ? true:false;
				
			if (female != null)
				female.visible = isMale ? false:true;
			
			
		//	mateInfoIcons.Icon = isMale? EMateInfoIcons.MALE:EMateInfoIcons.FEMALE
		}
		//TODO Начал было делать, но понял что это на долго... надо будет привести всё к этому виду
		public function SetHero(playerData:PlayerStatisticData, FullName:Boolean = true):void
		{
			trace("SetHero");
			setHeroInfoBorder(playerData.LeagueIndex);
			setHeroInfoIcon(playerData.HeroIcon, playerData.IsAnimatedAvatar);
			heroName = FullName ? playerData.PlayerName : playerData.PlayerShortName;
			heroFullName = playerData.PlayerName;
			SetHeroNameColor(playerData.HeroNameColor);
			SetRedBackVisibility(playerData.ShowRedBack);			
			
			if(flag!=null)
			{
				flag.visible = playerData.playerFlagPath.length != 0 && playerData.playerFlagPath != null;
				flag.Icon = playerData.playerFlagPath;
				flag.TooltipText = playerData.playerFlagTooltip;
			}
			
			id = playerData.HeroId;
			SetGender(playerData.Gender);
			IsBot = playerData.IsBot;
			isItOurHero = playerData.IsOurHero;
			if (playerData.IsHeroLeft)
				OnPlayerLeft( playerData.LeaveType );
			isHeroIgnored = playerData.IsIgnoring;
		}
		
		public function ResetGender():void
		{
			if (male!=null)
				male.visible = false;
				
			if (female != null)
				female.visible = false;
			
			//mateInfoIcons.Icon = EMateInfoIcons.NONE;
		}
		
		protected function SetLeaverIcon(iconIndex:int = LeaverIconData.LeaverIcon):void
		{	
			if (_currentIconIndex == iconIndex)
				return;
			
			_currentIconIndex = iconIndex;
				
			var leaveIcon:LeaverIconData = LeaveIcons[iconIndex];
			var image:Class = getDefinitionByName(leaveIcon.IconName) as Class;
			
			if (leavBitm != null) 
				RemoveLeaverIcon();
			
			leavBitm = new Bitmap(new image)
			this.addChildAt(leavBitm, leaveIcon.IconDepth);
			
			leavBitm.x = leaveIcon.IconPosition.x;
			leavBitm.y = leaveIcon.IconPosition.y;
			leavBitm.width = leaveIcon.IconWidth;
			leavBitm.height = leaveIcon.IconHeight;
		}
		
		protected function RemoveLeaverIcon():void 
		{
			if (leavBitm != null)
			{
				this.removeChild(leavBitm);
				leavBitm = null;
			}
			_currentIconIndex = -1;
		}
		
		
		public function OnPlayerLeft(iconIndex:int):void
		{
			SetLeaverIcon(iconIndex)
		
			SetGreyMask(true);
			
			if (deathTime != null) deathTime.visible = false;
			
			_isHeroLeft = true;
		}
		
		public function OnPlayerReturn():void 
		{
			RemoveLeaverIcon();
			_isHeroLeft = false;
		}
		
		public function SetFriendshipRelation(areFriends:Boolean,_isPending:Boolean):void 
		{
			isFriend = areFriends;
			isPending = _isPending;
		}
		
		
		public function SetHeroParams(curHealth:int,maxHealth:int,curMana:int,maxMana:int,healthRegen:Number=0,manaRegen:Number=0,animate:Boolean = true):void
		{
			
		}
		
		public function ShowTutorialHighlight(show:Boolean):void 
		{
			if (show)
			{
				if (tutorialHighlight != null) return;
			
				tutorialHighlight = new HeroStroke();
				tutorialHighlight.width = roundFrame.width;
				tutorialHighlight.height = roundFrame.height;
				this.addChild(tutorialHighlight);
			}
			else
			{
				if (tutorialHighlight!=null)
					this.removeChild(tutorialHighlight);
			}
		}
		
		public function ShowTutorialLevelHighlight(show:Boolean):void 
		{
			
		}
		
		protected function ShowContextMenu(e:MouseEvent):void
		{
			dispatchEvent(new ContextMenuEvent(GetContextMenuList()));
			
		}
		
		public function set ManaBarColor(value:uint):void
		{
			
		}
		
		public function set ManaBarShowRegeneration(value:Boolean):void
		{
			
		}		
		
	}
}