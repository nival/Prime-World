package MainScreen
{

	import Controllers.SoundController;
	import Controllers.TextFieldFormater;
	import flash.display.MovieClip;
	import flash.display.DisplayObject;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import fl.transitions.TweenEvent;
	import flash.text.TextFieldAutoSize;
	import flash.events.Event;
	import flash.text.TextField;
	
	import BaseClasses.BaseResizableObject;
	import Components.*;

	public class SelectionInfo extends BaseResizableObject
	{
		private var time:Number;
		private var myTweenBarUp:Tween;
		private var myTweenBarUp2:Tween;
		private var myTweenBarDown:Tween;
		private var myTweenBarDown2:Tween;

		private var buffArr:Array;
		
		//reference
		public var selectionInfoHero_mc:SelectionMateInfo;
		public var channelBar:Bar;
		public var healthBar_mc:Bar;
		public var manaBar_mc:Bar;
		
		public var name_txt:TextField;
		
		public var buff1:Buf;
		public var buff2:Buf;
		public var buff3:Buf;
		public var buff4:Buf;
		public var buff5:Buf;
		public var buff6:Buf;
		public var buff7:Buf;
		public var buff8:Buf;
		public var buff9:Buf;
		public var buff10:Buf;
		public var buff11:Buf;
		public var buff12:Buf;
		public var buff13:Buf;
		public var buff14:Buf;
		public var redBack:MovieClip;

		private const EPSILON:Number = 0.001;
		
		
		private const START_POSITION:int = 0;
		private const FIRST_LINE_POSITION:int = 1;
		private const SECOND_LINE_POSITION:int = 2;
		
		private var currentChanelingLevel:int = START_POSITION;
		
		private var isNewSelection:Boolean = true;
		
		private var nameText:TextFieldFormater;
		private var defaultColor;
		
		
		public function SelectionInfo()
		{
			this.visible = false;
			this.mouseEnabled = false;
			
			healthBar_mc.mouseEnabled = false;
			manaBar_mc.mouseEnabled = false;
			channelBar.mouseEnabled = false;	
			selectionInfoHero_mc.mouseEnabled = false;
			
			// constructor code
			channelBar.visible = false;

			buffArr = [buff1,buff2,buff3,buff4,buff5,buff6,buff7,buff8,buff9,buff10,buff11,buff12,buff13,buff14];
			buffArr.forEach(Hide);
			
			
			function Hide(element:*)
			{
				element.visible = false;
			}

			var gapForChannelingBar:Number = buff1.y-(manaBar_mc.y+manaBar_mc.BarHeight);
			
			var firstPos:Number = buff1.y;
			var secondPos:Number = buff1.y + buff1.BuffHeight + gapForChannelingBar;
			var thirdPos:Number = buff8.y + buff8.BuffHeight + gapForChannelingBar;

			firstPos = Math.round(firstPos - 0.5);
			secondPos = Math.round(secondPos - 0.5);
			thirdPos = Math.round(thirdPos - 0.5);
			
			myTweenBarUp =  new Tween(channelBar,"y",Strong.easeOut,secondPos,firstPos,5,false);
			myTweenBarUp.stop();

			myTweenBarUp2 = new Tween(channelBar,"y",Strong.easeOut,thirdPos,secondPos,5,false);
			myTweenBarUp2.stop();
			
			myTweenBarDown = new Tween(channelBar,"y",Strong.easeOut,firstPos,secondPos,5,false);
			myTweenBarDown.stop();
			myTweenBarDown2 =new Tween(channelBar,"y",Strong.easeOut,secondPos,thirdPos,5,false); 
			myTweenBarDown2.stop();
			
			channelBar.y = firstPos;
			
		//	this.name_txt.autoSize = TextFieldAutoSize.CENTER;
			name_txt.mouseEnabled = false;
			
			nameText = new TextFieldFormater(name_txt);
			
			defaultColor = name_txt.textColor;
			redBack.visible = false;
		}

		
		public function setParams(heroName:String,level:int,curHealth:int,maxHealth:int,curMana:int,maxMana:int,isEnemy:Boolean,channelingProgress:Number,healthRegen:Number,manaRegen:Number,leagueIndex:int):void
		{
			selectionInfoHero_mc.setHeroInfoBorder(leagueIndex);
			selectionInfoHero_mc.round_mc.visible = level != 0;
			selectionInfoHero_mc.level_txt.visible = level != 0;
			
			if (isEnemy)
				healthBar_mc.barColor = Bar.HEALTHBAR_COLOR_ENEMY;
			else
				healthBar_mc.barColor = Bar.HEALTHBAR_COLOR_ALLY;
				
			healthBar_mc.setMaxBar(maxHealth,!isNewSelection);
			healthBar_mc.setValue(curHealth, healthRegen, !isNewSelection);
			
			manaBar_mc.setMaxBar(maxMana,!isNewSelection);
			manaBar_mc.setValue(curMana, manaRegen, !isNewSelection);
			
			nameText.Text = heroName;
			
			selectionInfoHero_mc.level = level;
			selectionInfoHero_mc.heroName = heroName;
			
			ChannelingProgress = channelingProgress;
			
			isNewSelection = false;
		}
		
		private function set ChannelingProgress(chaneling:Number):void
		{
			if (chaneling<EPSILON||chaneling>=1-EPSILON)
			{
				channelBar.visible = false;
				return;
			}
			
			if (!channelBar.visible)
			{
				channelBar.visible = true;
				channelBar.setMaxBar(1000, false);
				channelBar.setValue(chaneling*1000,0, false);
				return;
			}
			channelBar.setValue(chaneling*1000);
		}
		
		public function SetIcon(path:String, isAnimatedAvatar:Boolean):void
		{	
			if (!this.visible && path == '')
				return;
			
			SoundController.PlaySound(SoundController.SELECTION);
			
			ChangeIcon(path, isAnimatedAvatar);
		}
		
		private function ChangeIcon(path:String, isAnimatedAvatar:Boolean):void
		{
			if (path == '')
			{
				this.visible = false;
				return;
			}
			
			this.visible = true;
			selectionInfoHero_mc.setHeroInfoIcon(path, isAnimatedAvatar);
			isNewSelection = true;
		}
		
		public function HideWithoutSound():void 
		{
			ChangeIcon("", false);
		}
		
		override protected function BaseBarObjectResize(e:Event=null):void
		{	
			super.BaseBarObjectResize();
			this.x = stage.stageWidth / 2;
			
			this.y = 0;
			this.x = Math.floor(this.x);
			this.y = Math.floor(this.y);
		}
			
		public function SetBuffIcon(isSelection:Boolean,path:String, index:int, isPositive:Boolean):void
		{
			if (buffArr[index] == null) return;		
			buffArr[index].SetBuffIcon(isSelection, path, index, isPositive);
			var index:int = -1;
			
			for (var i:int = 0; i < buffArr.length; i++)
			{
				if (!buffArr[i].visible)
					break;
				index = i;
			}
			
			if (index == -1)
			{
				AnimateChanelingTo(START_POSITION);
			
				return;
			}
			
			if (index < 7)
			{
				AnimateChanelingTo(FIRST_LINE_POSITION);
			
				return;
			}
			
			AnimateChanelingTo(SECOND_LINE_POSITION);
			
		}
		
		public function SetBuffStatus(index:int, cooldown:Number, count:int ):void
		{
			if (buffArr[index] == null) return;
			buffArr[index].SetBuffStatus(cooldown, count);
		}	
		
		
		private function AnimateChanelingTo(value:int):void
		{
			if (currentChanelingLevel == value) return;
		
			if (value > currentChanelingLevel)
			{
				AnimateDownChaneling(value)
			}
			else
			{
				AnimateUpChaneling(value)
			}
			currentChanelingLevel = value;
		}
		
		private function AnimateDownChaneling(value:int):void
		{
			myTweenBarUp.stop();
			myTweenBarUp2.stop();
			
			if (value == FIRST_LINE_POSITION)
			{			
				myTweenBarDown2.stop()
				myTweenBarDown.start();
			}
			
			if (value == SECOND_LINE_POSITION)
			{			
				myTweenBarDown.stop()
				myTweenBarDown2.start();
			}
		}
		
		private function AnimateUpChaneling(value:int):void
		{
			myTweenBarDown.stop();
			myTweenBarDown2.stop();
			
			if (value == FIRST_LINE_POSITION)
			{			
				myTweenBarUp.stop()
				myTweenBarUp2.start();
			}
			
			if (value == START_POSITION)
			{			
				myTweenBarUp2.stop()
				myTweenBarUp.start();
			}
		}		
		
		public function SetGender(isMale:Boolean):void
		{
			selectionInfoHero_mc.SetGender(isMale);
		}
		
		public function ResetGender():void
		{
			selectionInfoHero_mc.ResetGender();
		}
		
		public function SetFriendShipRelation(isFriend:Boolean,isPending:Boolean):void 
		{
			selectionInfoHero_mc.SetFriendshipRelation(isFriend,isPending);
		}
		
		public function IsBot(isBot:Boolean):void 
		{
			selectionInfoHero_mc.IsBot = isBot;
		}
		
		public function SetRedBackVisibility(isVisible:Boolean):void
		{
			redBack.visible = isVisible;
		}
		
		public function SetHeroNameColor(color:uint):void 
		{
			name_txt.textColor = color;			
		}
		
		public function ResetHeroNameColor():void
		{
			name_txt.textColor = defaultColor;
			redBack.visible = false;
		}

		
		public function set HeroId(value:int):void 
		{
			selectionInfoHero_mc.id = value;
		}
		
		public function set IsOurHeroSelected(value:Boolean):void 
		{
			selectionInfoHero_mc.isItOurHero = value;
		}
	}
}