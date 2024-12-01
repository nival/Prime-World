package Announcements
{

	import Controllers.TextFieldFormater;
	import fl.controls.List;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import fl.transitions.TweenEvent;
	import BaseClasses.BaseResizableObject;
	
	import Components.FormatedTimer;
	import Enums.EFraction;
	
	public class Announcement extends BaseResizableObject
	{
		public var topText:TextField;
		public var achivmentText:TextField;
		public var portraitLeft_mc:AnnouncementPortrait;
		public var portraitRight_mc:AnnouncementPortrait;
		public var nameLeft_txt:TextField;
		public var nameRight_txt:TextField;
		public var leftNameBack:MovieClip;
		public var rightNameBack:MovieClip;
		
		private var leftFormatedName:TextFieldFormater;
		private var rightFormatedName:TextFieldFormater;
		
		public var announcementTimer:FormatedTimer;
		
		private var delayTimer:Timer;
		private var alphaDecreaseTween:Tween;
		
		private var currentLefPortraitData:AnnouncementPotraitData;
		private var currentRightPortraitData:AnnouncementPotraitData;
		
		private var announcementDatas:Array = [];
		
		private var isGameClosing:Boolean = false;
		private var isAnnouncementIsShowing:Boolean = false;
		private var isCripTimerShowing:Boolean = false;
		
		
		private var leftPortraitIsFilled:Boolean;
		private var rightPortraitIsFilled:Boolean;
		
		private var leftCreepIcon:String;
		private var rightCreepIcon:String;
		private var creepSpawnAnnouncementText:String;
		
		public function Announcement()
		{
			this.visible = false;
			announcementTimer.visible = false;
			achivmentText.visible = false;
			topText.visible = false;
			
			delayTimer = new Timer(2000,1);
			delayTimer.addEventListener(TimerEvent.TIMER_COMPLETE,timerComplete);
			delayTimer.stop();
			
			alphaDecreaseTween = new Tween(this,"alpha",Strong.easeOut,1,0,30,false);
			alphaDecreaseTween.addEventListener(TweenEvent.MOTION_FINISH,tweenComplete);
			alphaDecreaseTween.stop();
			this.mouseEnabled =  false;
			this.mouseChildren = false;
			leftFormatedName = new TextFieldFormater(nameLeft_txt);
			rightFormatedName = new TextFieldFormater(nameRight_txt);
			
		}
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			this.x = stage.stageWidth / 2;
			curPosition.x = this.x;
		}
		
		public function StartAnouncement(_time:Number = 2000):void
		{
			delayTimer.delay = _time;
			delayTimer.start();
			this.visible = true;
			isAnnouncementIsShowing = true;
		}
		
		public function CloseAtTheEndOfTheGame():void
		{
			isGameClosing = true;
			if (this.visible == false) return;
			
			alphaDecreaseTween.start();
		}
		
		private function timerComplete(e:TimerEvent):void
		{
			delayTimer.reset();
			alphaDecreaseTween.start();
		}
		private function tweenComplete(e:TweenEvent):void
		{
			alphaDecreaseTween.rewind();
			this.visible = false;
			
			isAnnouncementIsShowing = false;
			isCripTimerShowing = false;
			
			if (isGameClosing) return;
			
			ShowNextAnnouncement();
		}
		
		public function SetAnnouncementPart(right:Boolean, portraitIcon:String, level:int, name:String,fraction:int):void
		{
			if (right)
				SetRightPortraitData(portraitIcon, level, name, fraction)
			else
				SetLeftPortraitData(portraitIcon, level, name, fraction);
		}
		
		private function SetLeftPortraitData(icon:String, level:int, name:String, fraction:int):void
		{
			currentLefPortraitData = new AnnouncementPotraitData();
			currentLefPortraitData.Icon = icon;
			currentLefPortraitData.Level = level;
			currentLefPortraitData.HeroName = name;
			currentLefPortraitData.Fraction = fraction;
			leftPortraitIsFilled = true;
		}
		
		
		private function SetRightPortraitData(icon:String, level:int, name:String, fraction:int):void
		{
			currentRightPortraitData = new AnnouncementPotraitData();
			currentRightPortraitData.Icon = icon;
			currentRightPortraitData.Level = level;
			currentRightPortraitData.HeroName = name;
			currentRightPortraitData.Fraction = fraction;
			rightPortraitIsFilled = true;
		}
		
		public function SetAnouncementData(announcementText:String, lifeTime:Number,priority:int):void
		{
			if (!leftPortraitIsFilled || !rightPortraitIsFilled)
			{
				leftPortraitIsFilled = false;
				rightPortraitIsFilled = false;
				return;
			}
			
			leftPortraitIsFilled = false;
			rightPortraitIsFilled = false;
			
			var newAnnouncement:AnnouncementData = new AnnouncementData();
			
			newAnnouncement.AnnouncementText = announcementText;
			newAnnouncement.Priority = priority;
			newAnnouncement.LeftPortrait = currentLefPortraitData;
			newAnnouncement.RightPortrait = currentRightPortraitData;
			newAnnouncement.LifeTime = lifeTime;
			
			for (var i:int = 0; i < announcementDatas.length; i++)
			{ 
				if (announcementDatas[i].Priority < newAnnouncement.Priority) 
				{
					announcementDatas.splice(i, 0, newAnnouncement);
					break;
				}
				if (i == announcementDatas.length - 1)
				{
					announcementDatas.push(newAnnouncement);
					break;
				}
			}
				
			if (announcementDatas.length == 0)
				announcementDatas.push(newAnnouncement);
				
			
			if (isAnnouncementIsShowing) return;
			
			ShowNextAnnouncement();
		}
		
		public function set TimeToCreepSpawn(value:int):void
		{
			if (leftCreepIcon == null || rightCreepIcon == null || creepSpawnAnnouncementText == null) return;
			
			if (isAnnouncementIsShowing) return;
			
			if (value <= 0 && isCripTimerShowing)
			{
				announcementTimer.Time = 0;
				alphaDecreaseTween.start();
				isCripTimerShowing = false;
				return;
			}
				
			if (value <= 0) return;
			
			this.visible = true;
			announcementTimer.visible = true;
			topText.visible = true;
			achivmentText.visible = false;
			nameLeft_txt.visible = false;
			nameRight_txt.visible = false;
			leftNameBack.visible = false;
			rightNameBack.visible = false;
			portraitRight_mc.level = 0;
			portraitLeft_mc.level = 0;
			portraitLeft_mc.FractionColor(EFraction.HUMAN_FACTION);
			portraitRight_mc.FractionColor(EFraction.ELF_FACTION);
			
			if (!isCripTimerShowing) 
			{
				portraitRight_mc.setHeroInfoIcon(rightCreepIcon, false);
				portraitLeft_mc.setHeroInfoIcon(leftCreepIcon, false);
			}
			topText.text = creepSpawnAnnouncementText;
			
			announcementTimer.Time = value;
			isCripTimerShowing = true;
			
		}
		
		private function ShowNextAnnouncement():void
		{
			if (announcementDatas.length == 0) return;
			
			if (isCripTimerShowing) 
			{
				alphaDecreaseTween.start();
				return;
			}
			
			announcementTimer.visible = false;
			topText.visible = false;
			
			var showingAnnouncement:AnnouncementData = announcementDatas.shift();
			ShowAnouncementText(showingAnnouncement.AnnouncementText);
			ShowLeftPortrait(showingAnnouncement.LeftPortrait);
			ShowRightPortrait(showingAnnouncement.RightPortrait);
			CorrectTextPosition();
			StartAnouncement(showingAnnouncement.LifeTime*1000);
		}
		
		private function CorrectTextPosition():void 
		{
			if (nameLeft_txt.textWidth < portraitLeft_mc.roundFrame.width) 
			{
				nameLeft_txt.autoSize = TextFieldAutoSize.CENTER;
				nameLeft_txt.x = leftNameBack.x + (leftNameBack.width - nameLeft_txt.width) / 2;
			}
			else
			{
				nameLeft_txt.autoSize = TextFieldAutoSize.LEFT;
				nameLeft_txt.x = portraitLeft_mc.x;
			}
			
			if (nameRight_txt.textWidth < portraitRight_mc.roundFrame.width)
			{	
				nameRight_txt.autoSize = TextFieldAutoSize.CENTER;
				nameRight_txt.x = rightNameBack.x + rightNameBack.width/2 - nameRight_txt.width/2;
			}
			else
			{
				nameRight_txt.autoSize = TextFieldAutoSize.RIGHT;
				nameRight_txt.x = portraitRight_mc.x + portraitRight_mc.roundFrame.width - nameRight_txt.width;
			}
		}
		
		private function ShowLeftPortrait(portraitData:AnnouncementPotraitData):void
		{
			portraitLeft_mc.setHeroInfoIcon(portraitData.Icon, false);
			portraitLeft_mc.level = portraitData.Level;
			portraitLeft_mc.FractionColor(portraitData.Fraction);
			
			nameLeft_txt.visible = portraitData.HeroName.length != 0;
			leftNameBack.visible = portraitData.HeroName.length != 0;
			leftFormatedName.Text = portraitData.HeroName;
		}
		
		
		private function ShowRightPortrait(portraitData:AnnouncementPotraitData):void
		{
			portraitRight_mc.setHeroInfoIcon(portraitData.Icon, false);
			portraitRight_mc.level = portraitData.Level;
			portraitRight_mc.FractionColor(portraitData.Fraction);

			nameRight_txt.visible = portraitData.HeroName.length != 0;
			rightNameBack.visible = portraitData.HeroName.length != 0;
			rightFormatedName.Text = portraitData.HeroName;
		}
		
		
		private function ShowAnouncementText(announcementText:String):void
		{
			achivmentText.visible = announcementText.length != 0;
			achivmentText.text = announcementText;
		}
		
		public function ShowSpawnCreepsAnnouncement(leftIcon:String, rightIcon:String, announcementText:String):void
		{
			leftCreepIcon = leftIcon;
			rightCreepIcon = rightIcon;
			creepSpawnAnnouncementText = announcementText;
		}
	}
}