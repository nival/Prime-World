package ActionBar
{

	import Events.ToggleButtonClickedEvent;
	import Interfaces.IShowImpulseTalent;
	import Controllers.SoundController;
	import flash.display.DisplayObjectContainer;
	import flash.display.MovieClip;
	import flash.display.DisplayObject;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import fl.transitions.TweenEvent;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.utils.Timer;
	import BaseClasses.BaseResizableObject;
	import Components.*;
	import Datas.ErrorMessagesData;
	import BaseClasses.BaseShortCut;
	import MainScreen.DecorLine;
	import Enums.ActionBarSlotState;
	import Enums.EActionBarDesiredPositions;
	import TalentBar.Talent;
	
	import flash.utils.getDefinitionByName;
	import flash.display.Bitmap;
	
	public class ActionBar extends MovieClip implements IShowImpulseTalent
	{
		private var time:Number;
		private var myTweenBarUp:Tween;
		private var myTweenBarUp2:Tween;
		private var myTweenBarDown:Tween;
		private var myTweenBarDown2:Tween;

		private var buffArr:Array;
		private var actionButtons:Array;
		private var death:Boolean = false;
		
		public var grafic01:MovieClip;
		public var grafic02:MovieClip;
			
		// Bars
		public var healthBar_mc:Bar;
		public var manaBar_mc:Bar;
		public var channelBar:Bar;
		
		/// Menu buttons
		public var talents_btn:RulerButton;
		public var char_btn:RulerButton;
		public var inventory_btn:RulerButton;
		public var statistics_btn:RulerButton;
		public var esc_btn:RulerButton;
		
		public var naftaGold_mc:NaftaButton;
		public var BarButtonsArray:Array;
		
		private var hideBuffsForTutorial:Boolean = false;
		
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
		public var buff15:Buf;
		public var buff16:Buf;
		public var buff17:Buf;
		public var buff18:Buf;
		public var buff19:Buf;
		public var buff20:Buf;
		public var buff21:Buf;
		public var buff22:Buf;
		
		public var btn1:ActionButton;
		public var btn2:ActionButton;
		public var btn3:ActionButton;
		public var btn4:ActionButton;
		public var btn5:ActionButton;
		public var btn6:ActionButton;
		public var btn7:ActionButton;
		public var btn8:ActionButton;
		public var btn9:ActionButton;
		public var btn10:ActionButton;
		public var portalBtn:ActionButtonPortal;
		
		public var errorMessageText:TextField;
		public var impulsTalent_mc:ImpulsTalent;
		public var lockBtn:ButtonRound;
		
		
		private var epselon:Number=0.001;
		
		private const START_POSITION:int = 0;
		private const FIRST_LINE_POSITION:int = 1;
		private const SECOND_LINE_POSITION:int = 2;
		
		private var currentChanelingLevel:int = START_POSITION;
		
		private var errorMessages:Array = [];

		private var lastPermanentErrorMessage:ErrorMessagesData = null;
		private var errorMessageTimer:Timer;
		private var nowShowingErrorMessage:ErrorMessagesData = null;
		private var isInMiniGame:Boolean =false;
		private var buyToIndex:int = -1;
		
		private var lockActionBar:Boolean;
		private var blockActionBar:Boolean;
		private var tempUnlockActionBar:Boolean;
		
		public function ActionBar()
		{
			this.stop();
			
			//lockBtn.visible = false;
			errorMessageText.visible = false;
			errorMessageText.mouseEnabled = false;
			
		//	impulsTalent_mc.visible = false;
			impulsTalent_mc.stop();
			
			this.mouseEnabled = false;
			lockBtn.AutoCheck = false;
			
			channelBar.visible = false;
		
			buffArr = [buff1,buff2,buff3,buff4,buff5,buff6,buff7,buff8,buff9,buff10,buff11,
			   buff12,buff13,buff14,buff15,buff16,buff17,buff18,buff19,buff20,buff21,buff22];

			actionButtons = [btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8, btn9, btn10];
			
			BarButtonsArray = [talents_btn,char_btn,inventory_btn,null,null,statistics_btn,esc_btn]
			
			for (var k:int = 0; k < BarButtonsArray.length; k++)
			{
				if (BarButtonsArray[k]!=null)
					BarButtonsArray[k].ButtonIndex = k;
			}
			
			for (var i:int; i<actionButtons.length; i++)
			{
				actionButtons[i].ActionBarIndex = i;
				actionButtons[i].actionBar = this;
			}
			
			talents_btn.AddNaftaShiningAnimation();
			
			buffArr.forEach(Hide);

			function Hide(element:*)
			{
				element.visible = false;
			}
			
			addEventListener(Event.ADDED_TO_STAGE, ThisAddedToStage);
			
			lockBtn.addEventListener(ToggleButtonClickedEvent.EVENT_TYPE, OnLockUp);
			
			FillButtonTooltips();
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);				
			
			manaBar_mc.hideOnZeroMax = false;
		}
		
		
		private function OnLockUp(e:ToggleButtonClickedEvent):void
		{
			e.stopPropagation();
			if (tempUnlockActionBar) return;
			
			if (e.Checked)
			{
				lockBtn.SwitchOn();
			}
			else
			{
				lockBtn.SwitchOff();
			}
			
			
			FSCommands.Send(FSCommands.ActionBarLock, int(e.Checked).toString());
		}
		
		private function FillLocalization(e:Event):void
		{
			FillButtonTooltips();
		}
		
		public function ThisAddedToStage(e:Event):void
		{
			var gapForChannelingBar:Number = healthBar_mc.y- (buff1.y + buff1.BuffHeight);
			
			var firstPos:Number = healthBar_mc.y - gapForChannelingBar-channelBar.BarHeight;
			var secondPos:Number = buff1.y - gapForChannelingBar-channelBar.BarHeight;
			var thirdPos:Number = buff12.y - gapForChannelingBar-channelBar.BarHeight;

			firstPos = Math.round(firstPos - 0.5);
			secondPos = Math.round(secondPos - 0.5);
			thirdPos = Math.round(thirdPos - 0.5);
			
			myTweenBarUp = new Tween(channelBar,"y",Strong.easeOut,firstPos,secondPos,6,false);
			myTweenBarUp.stop();
			myTweenBarUp2 = new Tween(channelBar,"y",Strong.easeOut,secondPos,thirdPos,5,false);
			myTweenBarUp2.stop();

			
			myTweenBarDown = new Tween(channelBar,"y",Strong.easeOut,secondPos,firstPos,5,false);
			myTweenBarDown.stop();
			myTweenBarDown2 = new Tween(channelBar,"y",Strong.easeOut,thirdPos,secondPos,5,false);
			myTweenBarDown2.stop();
			
			channelBar.y = firstPos;
			//activate button Portal
			//btn11.Shortcut.State = ActionBarSlotState.ACTIVE;
		}
		
		public function set EnemyHealthbarPresentation(value:Boolean):void
		{
			if (value)
				healthBar_mc.barColor = Bar.HEALTHBAR_COLOR_ENEMY;
			else
				healthBar_mc.barColor = Bar.HEALTHBAR_COLOR_ALLY;
		}
		
		public function set ManaBarColor(value:uint):void
		{
			manaBar_mc.barColor = value;
		}
		
		public function set ManaBarShowRegeneration(value:Boolean):void
		{
			manaBar_mc.ShowRegenerationText = value;
		}

		public function UseSlot(slot:int):void
		{
			actionButtons[slot].Shortcut.Press();
		}
		
		public function RemoveShortcut(shortcut:BaseShortCut)
		{
			RemoveObjectFromSlot(GetActionButtonIndex(shortcut));
		}
		
		public function SetReservedPosition(index:int):void
		{
			if (index<0||index>=actionButtons.length) return;

			actionButtons[index].isReserved = true;
		}

		public function AddShortcut(shortcut:BaseShortCut)
		{
			
			if (buyToIndex != -1)
			{
				if(!actionButtons[i].isFreeSlot)
					actionButtons[buyToIndex].Shortcut.RemoveFromActionbar();
					
				actionButtons[buyToIndex].Shortcut = shortcut;
				actionButtons[buyToIndex].Shortcut.EnableDeathMask(death);
				ResetByeToIndex();
				return;
			}
			
			if (shortcut.DesirableIndex == EActionBarDesiredPositions.NOT_NEEDED_IN_ACTIONBAR)
				return;
			
			if (shortcut.DesirableIndex==EActionBarDesiredPositions.INTO_ANY_POSITION/*||shortcut.DesirableIndex == EActionBarDesiredPositions.NOT_NEEDED_IN_ACTIONBAR*/)
			{
				for (var i:int; i<actionButtons.length; i++)
				{
					if (actionButtons[i].isFreeSlot&&!actionButtons[i].isReserved)
					{
						actionButtons[i].Shortcut = shortcut;
						actionButtons[i].Shortcut.EnableDeathMask(death);
						break;
					}
				}		
				return;
			}
			
			if (shortcut.DesirableIndex<0|| shortcut.DesirableIndex>=actionButtons.length) return;
			
			if (actionButtons[shortcut.DesirableIndex].isFreeSlot)
				{
					actionButtons[shortcut.DesirableIndex].Shortcut = shortcut;
					actionButtons[shortcut.DesirableIndex].Shortcut.EnableDeathMask(death);
				}
		}
		
		
		private function RemoveObjectFromSlot(index:int):void 
		{
			if (index < 0 || index >= actionButtons.length) return;
			
			actionButtons[index].Shortcut = new BaseShortCut();
			actionButtons[index].State = ActionBarSlotState.DISABLED;
			actionButtons[index].isFreeSlot = true;
			actionButtons[index].isReserved = false;
		}
		
		public function GetActionButtonIndex(shortcut:BaseShortCut):int
		{
			for (var i:int; i<actionButtons.length; i++)
			{
				if (actionButtons[i].Shortcut == shortcut)
					return i;
			}
			
			return -1;
		}
		
		public function BuyItemInSlot(index:int):void
		{
			if (index < 0 || index >= actionButtons.length) return;
			
			buyToIndex = index;
		}
		
		public function get BuyToIndex():int
		{
			return buyToIndex;
		}
		
		public function ResetByeToIndex():void
		{
			if (buyToIndex == -1) return;
			
			buyToIndex = -1;
		}
		
		public function placeShortCutIntoIndex(index:int,shortCut:BaseShortCut):void 
		{ 	
			ResetByeToIndex();
			var i:int = GetActionButtonIndex(shortCut);
			var actButton:ActionButton = actionButtons[index];
			var currentShortCut:BaseShortCut;
			
			if (i<0||i>=actionButtons.length)
			{
				currentShortCut = actButton.Shortcut;
				currentShortCut.RemoveFromActionbar();
				
				actButton.Shortcut = shortCut;
				actButton.Shortcut.EnableDeathMask(death);
				actButton.Shortcut.showTooltip();
				return;
			}
				
			if (actButton.isFreeSlot) 
			{
				currentShortCut = actionButtons[i].Shortcut;
								
				var count:int = actionButtons[i].count; 
				actionButtons[i].Shortcut.RemoveFromActionbar();
				
				actionButtons[index].Shortcut = currentShortCut;
				actionButtons[index].count = count;
				actionButtons[index].Shortcut.showTooltip();
			}
			else 
			{	
				var movingCount:int = actionButtons[i].count;
				var movingState:int = actionButtons[i].State

				actionButtons[i].Shortcut = actButton.Shortcut;
				actionButtons[i].count = actButton.count;
				actionButtons[i].State = actButton.State;
				actionButtons[i].Shortcut.hideTooltip();
				
				actionButtons[index].Shortcut = shortCut;
				actionButtons[index].count = movingCount;
				actionButtons[index].State = movingState;
				actionButtons[index].Shortcut.showTooltip();
			}	
		}
		

		public function actionBarDisable(_death:Boolean):void
		{
			if (death != _death)
			{
				for (var i:int = 0; i<actionButtons.length; i++)
				{
					actionButtons[i].Shortcut.EnableDeathMask(_death);
				}
				
				portalBtn.EnableDeathMask(_death);
				death = _death;
			}
		}

		public function set Prime(_prame:int):void
		{
			naftaGold_mc.Prime = _prame;
		}
		
		public function set Gold(_gold:int):void
		{
			naftaGold_mc.GoldCount = _gold;
		}
		
		public function setGlobalCooldown(cooldown:Number,maxCooldownValue:Number):void 
		{
			for (var i:int = 0; i < actionButtons.length; i++ )
				actionButtons[i].GlobalCoolDown(cooldown, maxCooldownValue);
				
			portalBtn.GlobalCoolDown(cooldown, maxCooldownValue);
		}
		
		public function ShowCentral(show:Boolean):void
		{	
			var i:int = 0;
			
			isInMiniGame = !show;
		
			grafic01.visible = show;
			grafic02.visible = show;
					
			healthBar_mc.showInActionBar = show;
			manaBar_mc.showInActionBar = show;
			healthBar_mc.visible =  show;
			manaBar_mc.visible =  show;
			lockBtn.visible = show;
			
			if(!show)
				channelBar.visible = show;
				
			UpdateBuffsVisibility();
			
			for (i = 0; i < actionButtons.length; i++)
			{
				actionButtons[i].visible = show;
			}
			portalBtn.visible = show;
			
		}
	
		public function GetActionBarItem(index:int):MovieClip
		{
			if (index<0||index>=actionButtons.length) return null;
			
			return actionButtons[index];
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
			
			if (index < 11)
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
		
		public function ShowBuffsForTutorial(show:Boolean)
		{
			hideBuffsForTutorial = !show;
			
			UpdateBuffsVisibility();
		}
		
		private function UpdateBuffsVisibility():void 
		{
			for (var i:int = 0; i < buffArr.length; i++)
			{
				buffArr[i].Hide(hideBuffsForTutorial || isInMiniGame);
			}
		}
		
		public function ResetActionBar():void
		{
			for (var i:int = 0; i < actionButtons.length; i++)
			{
				RemoveObjectFromSlot(i);
			}
		}
		
		
		public function set ChannelingProgress(chaneling:Number):void
		{
			if (channelBar == null)
				return;
			
			if (isInMiniGame) return;
			
			if (chaneling<epselon||chaneling>=1-epselon)
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
			myTweenBarDown.stop();
			myTweenBarDown2.stop();
			
			if (value == FIRST_LINE_POSITION)
			{			
				myTweenBarUp2.stop()
				myTweenBarUp.start();
			}
			
			if (value == SECOND_LINE_POSITION)
			{			
				myTweenBarUp.stop()
				myTweenBarUp2.start();
			}
		}
		
		private function AnimateUpChaneling(value:int):void
		{
			myTweenBarUp.stop();
			myTweenBarUp2.stop();
			
			if (value == FIRST_LINE_POSITION)
			{			
				myTweenBarDown.stop()
				myTweenBarDown2.start();
			}
			
			if (value == START_POSITION)
			{			
				myTweenBarDown2.stop()
				myTweenBarDown.start();
			}
		}		
		
		public function SetErrorMessage(errorID:int, msg:String, playSound:Boolean, lifeTime:Number):void
		{
			for (var i:int = 0; i < errorMessages.length; i++)
			{
				if (errorMessages[i].ID == errorID)
				{
					errorMessages[i].Message = msg;
					errorMessages[i].PlaySound = playSound;
					errorMessages[i].LifeTimes = lifeTime;
					return;
				}
			}

			var errorMessage:ErrorMessagesData = new ErrorMessagesData();
			
			errorMessage.ID = errorID;
			errorMessage.LifeTimes = lifeTime;
			errorMessage.Message = msg;
			errorMessage.PlaySound = playSound;
			
			errorMessages.push(errorMessage);
		}
		
		public function ShowErrorMessage(errorID:int, show:Boolean):void
		{
			var errorMessage:ErrorMessagesData = null;
			
			for (var i:int = 0; i < errorMessages.length; i++ )
			{
				if (errorMessages[i].ID == errorID)
				{
					errorMessage = errorMessages[i];
				}
			}
			
			if (errorMessage == null) return;
				
			SetErrorMessageText(errorMessage,show);
		}
		
		public function ShowErrorEvent(mes:String, playSound:Boolean, lifeTime:Number):void
		{
			var errorMessage:ErrorMessagesData = new ErrorMessagesData();
			errorMessage.Message = mes;
			errorMessage.PlaySound = playSound;
			errorMessage.LifeTimes = lifeTime;
			
			SetErrorMessageText(errorMessage,true);
		}
		
		private function StartPlaingNafta():void 
		{
			naftaGold_mc.StartPlaingNafta();
			talents_btn.ShowNaftaShiningAnimation(true);
		}
		
		private function StopPlaingNafta():void 
		{
			naftaGold_mc.StopPlaingNafta();
			talents_btn.ShowNaftaShiningAnimation(false);
		}
		
		/* INTERFACE Interfaces.IShowImpulseTalent */

		public function AddImpulseTalent(talent:Talent, topLevel:int, minLevel:int):void
		{
			impulsTalent_mc.AddImpulseTalent(talent, topLevel, minLevel);
		}
		
		public function RemoveImpulseTalent(talent:Talent):void
		{
			impulsTalent_mc.RemoveImpulseTalent(talent);
		}

		public function ShowImpulseTalent():void
		{
			impulsTalent_mc.ShowImpulseTalent();

			if (impulsTalent_mc.ShowNaftaShining())
				StartPlaingNafta();
			else
				StopPlaingNafta();
		}
		
		public function ShowTutorialActionBarItemHighlight(slot:int, show:Boolean):void 
		{
			if (slot<0||slot>=actionButtons.length)
				return;
			if (show)
				actionButtons[slot].ShowTutorialHighlight();
			else
				actionButtons[slot].HideTutorialHighlight();
		}
		
		public function BlockActionBar(lock:Boolean):void 
		{
			blockActionBar = lock;
			
			UpdateActionBarLock();
		}
			
		
		public function LockActionBar(lock:Boolean):void 
		{
			lockActionBar = lock;
			
			if (!lock)
				lockBtn.SwitchOff();
			else
				lockBtn.SwitchOn();
			
			UpdateActionBarLock();
		}
		
		
		public function TempUnlockActionBar(unlock:Boolean):void 
		{
			tempUnlockActionBar = unlock;
			
			if (unlock)
			{
				lockBtn.SwitchOff();
			}
			else
			{
				if (lockActionBar)
					lockBtn.SwitchOn();
			}
			UpdateActionBarLock();
		}
		
		public function SetBindToSlot(index:int, bind:String):void 
		{
			var curIndex:int = index-1;
			
			if (curIndex == -1) 
				curIndex = 9;

			if (curIndex<0||curIndex>=actionButtons.length)	
				return;
				
				
			actionButtons[curIndex].SetBindKey(bind);
		}
						
				
		private function SetErrorMessageText(errorMessage:ErrorMessagesData,show:Boolean):void
		{
			if (errorMessage.PlaySound&&(show||errorMessage.LifeTimes > epselon))
				SoundController.PlaySound(SoundController.ERROR_SOUND);
				
			if (errorMessage.LifeTimes > epselon)
			{
				if (errorMessageTimer!=null)
					errorMessageTimer.stop();
			
				errorMessageText.visible = true;
				errorMessageText.text = errorMessage.Message;
				nowShowingErrorMessage = errorMessage;
			
				errorMessageTimer = new Timer(errorMessage.LifeTimes*1000, 1);
				errorMessageTimer.addEventListener(TimerEvent.TIMER_COMPLETE, ChangeToLastPermanentErrorMessage);
				errorMessageTimer.start();
				return;
			}
						
			if (show)
			{
				lastPermanentErrorMessage = errorMessage;
				errorMessageText.text = errorMessage.Message;
				nowShowingErrorMessage = lastPermanentErrorMessage;
				errorMessageText.visible = true;
				
				if (errorMessageTimer!=null)
					errorMessageTimer.stop();
				return;
			}
			
			if (nowShowingErrorMessage == lastPermanentErrorMessage)
			{
				errorMessageText.visible = false;
				nowShowingErrorMessage = null;
			}
			
			lastPermanentErrorMessage = null;
			
		}
		
		private function ChangeToLastPermanentErrorMessage(e:TimerEvent):void
		{
			nowShowingErrorMessage = lastPermanentErrorMessage;
			
			if (lastPermanentErrorMessage == null) 
			{
				errorMessageText.visible = false;
				return;
			}
			
			errorMessageText.text = lastPermanentErrorMessage.Message;
			
			if (lastPermanentErrorMessage.PlaySound)
				SoundController.PlaySound(SoundController.ERROR_SOUND);
		}
		
		private function FillButtonTooltips():void
		{	
			lockBtn.Tooltip = Localization.Tooltip_LockActionBarBtnUp;
			lockBtn.TogledTooltip = Localization.Tooltip_LockActionBarBtnDown;
			
			talents_btn.Tooltip = Localization.Tooltip_ActionBarTalentWindowOn;
			talents_btn.TogledTooltip = Localization.Tooltip_ActionBarTalentWindowOff;
			
			char_btn.Tooltip = Localization.Tooltip_ActionBarCharStatWindowOn;
			char_btn.TogledTooltip = Localization.Tooltip_ActionBarCharStatWindowOff;
			
			inventory_btn.Tooltip = Localization.Tooltip_ActionBarInventoryWindowOn;
			inventory_btn.TogledTooltip = Localization.Tooltip_ActionBarInventoryWindowOff;
			
			statistics_btn.Tooltip = Localization.Tooltip_ActionBarStatisticBarWindowOn;
			statistics_btn.TogledTooltip = Localization.Tooltip_ActionBarStatisticBarWindowOff;
			
			esc_btn.Tooltip = Localization.Tooltip_ActionBarEscMenuWindowOn;
			esc_btn.TogledTooltip = Localization.Tooltip_ActionBarEscMenuWindowOff;
		}
		
		private function UpdateActionBarLock():void 
		{
			for each (var button:ActionButton in actionButtons) 
			{
				button.BlockActionBar(blockActionBar || (lockActionBar && !tempUnlockActionBar));
			}
		}
	} 
}