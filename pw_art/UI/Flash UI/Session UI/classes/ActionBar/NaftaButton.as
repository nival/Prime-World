package ActionBar
{
	import fl.transitions.TweenEvent;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.Timer;
	import TalentBar.Talent;

	import src.TextFieldFormat;
	import src.WButton;
	import flash.display.MovieClip;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;

	import Events.WindowVisibleControllerEvent;
	import Enums.EWindows;
	public class NaftaButton extends MovieClip
	{
		public var __exportedProperties:Array = ["Tooltip"];
		private var moneyFull:Boolean = false;
		
		private var prime:int;
		private var gold:int;
		
		private var backPrimeNormalWidth:Number;
		private var backGoldNormalWidth:Number;
		
		private var originalNaftaBackX:Number;
		private var originalGoldBackX:Number;
		
		private var originalNaftaBackCenter:Number;
		
		private var NaftaHeightTween:Tween;
		
		private const BACK_OUT_SIZE:int = 5;
		
		//reference in stage
		public var tooltipOrigin_mc:MovieClip;//fake movie clip for tooltip
		
		public var naftaSpark_mc:MovieClip;
		public var naftaFull_mc:MovieClip;
		public var naftaGlow_mc:MovieClip;
		public var infoBackN:MovieClip;
		public var infoBackG:MovieClip;
		public var gold_txt:TextField;
		public var nafta_mc:MovieClip;
		public var nafta_txt:TextField;
		public var flashGold_mc:MovieClip;
		public var flashGoldFull_mc:MovieClip;
		public var moneyFull_mc:MovieClip;
		
		public var canBuy:Boolean = false;
		public var mask_mc:MovieClip;
		public var plug_mc:MovieClip;
		public var bottle_mc:MovieClip;
		
		private var needPrime:int = 50;

		public function NaftaButton()
		{
			naftaSpark_mc.visible = false;
			naftaSpark_mc.stop();
			naftaFull_mc.visible = false;
			naftaFull_mc.stop();
			naftaGlow_mc.visible = false;
			naftaGlow_mc.stop();
			moneyFull_mc.visible = false;
			plug_mc.stop();


			bottle_mc.naftaButton_mc.addEventListener(MouseEvent.MOUSE_OVER, onOver);
			bottle_mc.stop();
			
			NaftaHeightTween = new Tween(mask_mc, "scaleY", Strong.easeOut, 0, 1, 30, false);
			NaftaHeightTween.stop();
			
			infoBackN.mouseEnabled = false;
			nafta_txt.mouseEnabled = false;
			infoBackG.mouseEnabled = false;
			gold_txt.mouseEnabled = false;
			naftaGlow_mc.mouseChildren = false;
			naftaGlow_mc.mouseEnabled = false;
			nafta_mc.mouseEnabled = false;
			nafta_mc.mouseChildren = false;

			nafta_txt.autoSize = TextFieldAutoSize.CENTER;
			gold_txt.autoSize = TextFieldAutoSize.CENTER;

			backPrimeNormalWidth = infoBackN.width;
			backGoldNormalWidth = infoBackG.width;

			originalNaftaBackX = nafta_txt.x;
			originalGoldBackX = gold_txt.x;
			originalNaftaBackCenter = infoBackN.x + infoBackN.width / 2;
			
			nafta_txt.multiline = true;
			gold_txt.multiline = true;
			
			nafta_txt.text = '0';
			gold_txt.text = '0';
			
			//infoBackN.x = nafta_txt.x + (nafta_txt.width - backPrimeNormalWidth) / 2;
			//infoBackG.x = gold_txt.x + (gold_txt.width - backGoldNormalWidth) / 2;

			flashGoldFull_mc.blendMode = "overlay";
			flashGold_mc.blendMode = "overlay";
			
			bottle_mc.addEventListener("Up", NaftaBtnClick);		
			
			bottle_mc.naftaButton_mc.TargetObject = tooltipOrigin_mc;
			
			Tooltip = Localization.Tooltip_NaftaBtn;
			if (Localization.CompleteEventDispatcher!=null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
			
			//прячем весь голд в Навтабатн
			gold_txt.visible = false;
			infoBackG.visible = false;
			flashGold_mc.visible = false;
			flashGoldFull_mc.visible = false;
			moneyFull_mc.visible = false;
			
			bottle_mc.bottleLight.mouseEnabled = false;
			
		}
		
		private function FillLocalization(e:Event):void
		{
			Tooltip = Localization.Tooltip_NaftaBtn;
		}

		public function set Tooltip(value:String):void
		{
			bottle_mc.naftaButton_mc.Tooltip = value;
		}
		
		public function get Tooltip():String
		{
			return bottle_mc.naftaButton_mc.Tooltip;
		}
		
		private function NaftaBtnClick(e:Event):void
		{
			e.stopPropagation();
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN_CLOSE,EWindows.WINDOW_TALENTSBAR));
		}
		
		private function getFull():void
		{
			naftaSpark_mc.visible = true;
			naftaSpark_mc.play();
			naftaGlow_mc.visible = true;
			naftaFull_mc.visible = true;
			naftaFull_mc.play();

		//	nafta_mc.height = 36;

		}

		private function getMoneyFull():void
		{
			//moneyFull_mc.visible = true;
			moneyFull = true;
		}

		private function getMoney():void
		{
			//moneyFull_mc.visible = false;
			moneyFull = false;
		}

		private function getNormal():void
		{
			naftaSpark_mc.visible = false;
			naftaSpark_mc.stop();
			naftaGlow_mc.visible = false;
			naftaFull_mc.visible = false;
			naftaFull_mc.stop();
		}

		private function onOver(e:MouseEvent):void
		{
//			if (! moneyFull)
//			{
//				flashGold_mc.play();
//			}
//			if (moneyFull)
//			{
//				flashGoldFull_mc.play();
//			}
		}
		
		public function set Prime(_prime:int):void
		{
			if(_prime == prime)
			{
				return;
			}
			prime = _prime;
			nafta_txt.text = prime.toString();
			
			if(nafta_txt.width + BACK_OUT_SIZE >  backPrimeNormalWidth)
			{
				infoBackN.width = nafta_txt.width + BACK_OUT_SIZE;
				infoBackN.x = originalNaftaBackCenter - infoBackN.width / 2;
			
			}
		}
		
		
		public function set GoldCount(_gold:int):void
		{
			if(_gold == gold)
			{
				return;
			}
			gold = _gold;
			gold_txt.text = gold.toString();
			
			if(gold_txt.width + BACK_OUT_SIZE > backGoldNormalWidth)
			{
				infoBackG.width = gold_txt.width + BACK_OUT_SIZE;
				infoBackG.x = originalGoldBackX - (infoBackG.width - backGoldNormalWidth) / 2;
			}
		}
		
		public function StartPlaingNafta():void
		{
			if (canBuy) return;
			
			canBuy = true;
			
			NaftaHeightTween.stop();
			NaftaHeightTween.continueTo(1, 30);
			NaftaHeightTween.start();
			
			naftaSpark_mc.visible = true;
			naftaSpark_mc.play();
			naftaGlow_mc.visible = true;
			naftaGlow_mc.play();
			plug_mc.play();
			bottle_mc.play();
			
			bottle_mc.bottleLight.play();
			bottle_mc.bottleLight.visible = true;
		}
		
		public function StopPlaingNafta():void
		{		
			canBuy = false;
			
			NaftaHeightTween.stop();		
			NaftaHeightTween.continueTo(0, 30);
			NaftaHeightTween.start();
			
			naftaSpark_mc.visible = false;
			naftaSpark_mc.gotoAndStop(1);
			naftaGlow_mc.visible = false;
			naftaGlow_mc.gotoAndStop(1);
			plug_mc.gotoAndStop(1);
			bottle_mc.gotoAndStop(1);
			
			bottle_mc.bottleLight.gotoAndStop(1);
			bottle_mc.bottleLight.visible = false;
		}
	}
}