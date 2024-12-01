package StatisticBars
{
	
	import classes.Datas.ExperienceData;
	import Controllers.StatBarHelper;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	public class StatBar extends MovieClip 
	{
		private const BARWIDTH:int = 715;
		//reference
		public var greenLine_mc:StatLine;
		public var blueLine_mc:StatLine;
		public var orangeLine_mc:StatLine;
		public var emptyLine_mc:StatLine;
		
		public var statBarSoftMask_mc:MovieClip;
		
		public var levelUpGlow_mc:MovieClip;
		
		public var currentMasteryLevel:TextField;
		public var nextMasteryLevel:TextField;
		public var float_mc:FloatStat;

		private var statBarHelper:StatBarHelper;
		
		public function StatBar() 
		{	
			statBarHelper = new StatBarHelper(BARWIDTH);
			
			levelUpGlow_mc.visible = false;
			//levelUpGlow_mc.statBarSoftMask_mc.stop();//TODO вернуть когда подправят мягкую маску
			levelUpGlow_mc.stop();
			
			greenLine_mc.Color = 0x0CF400;
			blueLine_mc.Color = 0x0087BD;
			orangeLine_mc.Color = 0xFFA619;
			emptyLine_mc.Alpha = 0;
			
			currentMasteryLevel.visible = false;
			nextMasteryLevel.visible = false;
			blueLine_mc.addEventListener('wTweenFinish', EarnedExpMoveFinished);
			orangeLine_mc.addEventListener('wTweenFinish', PremiumExpMoveFinished);

			float_mc.addEventListener("floatLevelUp", floatLevelUp);

		//	orangeLine_mc.addEventListener(MouseEvent.MOUSE_UP, orangeClick);
			
		//	float_mc.addEventListener(MouseEvent.MOUSE_UP, orangeClick);
			
			SetStartPosition();
			
			emptyLine_mc.Width(BARWIDTH, false);
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
		}
		
		private function FillLocalization(e:Event):void 
		{
			greenLine_mc.ToolTipText = Localization.Tooltip_StatBarPrevExperience;
			blueLine_mc.ToolTipText = Localization.Tooltip_StatBarEarnedExperience;
			orangeLine_mc.ToolTipText = Localization.Tooltip_StatBarEarnedByCourageExperience;
			emptyLine_mc.ToolTipText = Localization.Tooltip_StatBarLeftExperience;
		}

		private function xpossFinish(e:Event):void
		{
		/*	e.stopPropagation();
			float_mc.removeEventListener('xposTweenFinish', xpossFinish);
			
			SetStartPosition();
			orangeLine_mc.Width((curentExpWidth+earnedExpWidth+earnedByCourageWidth)-BARWIDTH,false);
			float_mc.X(0,false);
			float_mc.X((curentExpWidth+earnedExpWidth+earnedByCourageWidth)-BARWIDTH);*/
		}
		
		public function SetStatisticExperienceBar(prevExp:int, earnedExp:int, premiumExp:int, _levelsTabel:Array):void 
		{
			currentMasteryLevel.visible = true;
			nextMasteryLevel.visible = true;
			
			statBarHelper.SetStatBarData(_levelsTabel, prevExp, earnedExp, premiumExp);
			
			currentMasteryLevel.text = (statBarHelper.GetCurrentLevel()).toString();
			nextMasteryLevel.text = (statBarHelper.GetCurrentLevel()+1).toString();
			
			SetExperience();
		}
		
		private function SetExperience():void
		{
			SetStartPosition();
			
		//	trace(statBarHelper.GetLevelRange(statBarHelper.GetCurrentLevel()) +" cur "+statBarHelper.GetCurrentExp()+" earn "+statBarHelper.GetEarnedExp()+" prem "+statBarHelper.GetPremiumExp());
			
			var koef:Number = statBarHelper.GetWidthKoeff();
			var curExpWidth:int = Math.round(koef * statBarHelper.GetCurrentExp());
			var earnedExpWidth:int =  Math.round(koef * statBarHelper.GetEarnedExp());
			var premiumExpWidth:int =  Math.round(koef * statBarHelper.GetPremiumExp());
			
			greenLine_mc.Text = statBarHelper.GetCurrentExp().toString();//пишем текст для зеленой
			blueLine_mc.Text = statBarHelper.GetEarnedExp().toString();
			orangeLine_mc.Text = statBarHelper.GetPremiumExp().toString();
			emptyLine_mc.Text = statBarHelper.GetEmpty().toString();
			
			greenLine_mc.Width(curExpWidth, false);//по сценарию выставляем для начала зеленую без анимации
			
			if (earnedExpWidth == 0 && premiumExpWidth == 0) 
			{
				float_mc.x = greenLine_mc.x+greenLine_mc.BarWidth;
			}
			
			if (earnedExpWidth != 0)
			{
				AnimateEarnedExperience();
				return;
			}
			
			if (premiumExpWidth != 0)
				AnimatePremiumExperience();
		}
		
		private function AnimateEarnedExperience():void
		{
			var koef:Number = statBarHelper.GetWidthKoeff();
			var curExpWidth:int = Math.round(koef * statBarHelper.GetCurrentExp());
			var earnedExpWidth:int =  Math.round(koef * statBarHelper.GetEarnedExp());
			var premiumExpWidth:int =  Math.round(koef * statBarHelper.GetPremiumExp());
			
			blueLine_mc.X(curExpWidth, false);//соответственно синию ставим по длине зеленой	
			blueLine_mc.Width(earnedExpWidth);
			
			float_mc.IsLevelUpWillBe(statBarHelper.IsWillBeLevelUp());
			float_mc.Text = (statBarHelper.GetCurrentExp() + statBarHelper.GetEarnedExp()+statBarHelper.GetPremiumExp()).toString();//пишем число в поплавок
			float_mc.x = blueLine_mc.x;
			float_mc.X(curExpWidth + earnedExpWidth);//анимируем поплавок
		}
		
		private function AnimatePremiumExperience():void 
		{
			var koef:Number = statBarHelper.GetWidthKoeff();
			var curExpWidth:int = Math.round(koef * statBarHelper.GetCurrentExp());
			var earnedExpWidth:int =  Math.round(koef * statBarHelper.GetEarnedExp());
			var premiumExpWidth:int =  Math.round(koef * statBarHelper.GetPremiumExp());
			
			orangeLine_mc.x = curExpWidth + earnedExpWidth;
			orangeLine_mc.Width(premiumExpWidth)
			
			float_mc.IsLevelUpWillBe(statBarHelper.IsWillBeLevelUp());
			float_mc.x = orangeLine_mc.x
			float_mc.Text = (statBarHelper.GetCurrentExp() + statBarHelper.GetEarnedExp()+statBarHelper.GetPremiumExp()).toString();//пишем число в поплавок
			float_mc.X(curExpWidth + earnedExpWidth+premiumExpWidth);//анимируем поплавок
		}
		
		
		private function PremiumExpMoveFinished(e:Event):void 
		{
			RefreshExperienceData();
		}
		
		private function EarnedExpMoveFinished(e:Event):void
		{
			e.stopPropagation();
			
			if (statBarHelper.GetPremiumExp() != 0)
			{
				AnimatePremiumExperience();
				return;
			}
			
			RefreshExperienceData();
		}
		
		private function RefreshExperienceData():void 
		{
			statBarHelper.RefillData();
			
			currentMasteryLevel.text = (statBarHelper.GetCurrentLevel()).toString();
			nextMasteryLevel.text = (statBarHelper.GetCurrentLevel() + 1).toString();
			
			if (statBarHelper.IsTheirAnithingToShow())
			{
				SetExperience();
				return;
			}
			
			emptyLine_mc.X(greenLine_mc.BarWidth + blueLine_mc.BarWidth + orangeLine_mc.BarWidth,false);
			emptyLine_mc.Width(BARWIDTH - (greenLine_mc.BarWidth + blueLine_mc.BarWidth + orangeLine_mc.BarWidth),false);
			
			greenLine_mc.ShowText();
			blueLine_mc.ShowText();
			orangeLine_mc.ShowText();
			emptyLine_mc.ShowText();
		}
		
		
		private function SetStartPosition():void
		{
			float_mc.X(0, false);
			greenLine_mc.X(0, false);
			blueLine_mc.X(0, false);
			orangeLine_mc.X(0, false);
			greenLine_mc.Width(0, false);
			blueLine_mc.Width(0, false);
			orangeLine_mc.Width(0, false);
		}
		
		/*private function orangeClick(e:MouseEvent):void
		{
			if (float_mc.x == orangeLine_mc.x + orangeLine_mc.BarWidth) return;
			
			if(BARWIDTH > curentExpWidth+earnedExpWidth+earnedByCourageWidth)
			{
				float_mc.X(curentExpWidth+earnedExpWidth+earnedByCourageWidth);
			}
			else
			{
				float_mc.X(BARWIDTH);
				float_mc.addEventListener('xposTweenFinish', xpossFinish);
			}
			float_mc.Text = (currentExpRange + earnedExpRange +earnedByCourageRange).toString();
		}*/
		private function floatLevelUp(e:Event):void
		{
			if (statBarHelper.IsWillBeLevelUp())
			{
				levelUpGlow_mc.visible = true;
				//levelUpGlow_mc.statBarSoftMask_mc.gotoAndPlay(1);//TODO вернуть когда поддержат мягкую маску
				levelUpGlow_mc.gotoAndPlay(1);
			}

		}
	}
}
