package Components{
	
	import Enums.EAltarDamageType;
	import flash.display.MovieClip;
	import flash.text.TextField;
	import Enums.EFraction;
	public class Dragonval extends MovieClip 
	{
		private var curRedDamage:int = 0 ;
		private var curBlueDamage:int = 0;
		public var adornCritical_mc:MovieClip;//анимация критического состояния адорнийцев
		public var doctCritical_mc:MovieClip;//анимация критического состояния доктов
		
		public var adornMedium_mc:MovieClip;//анимация, "внимание" адрнийцев
		public var doctMedium_mc:MovieClip;//анимация "внимание" доктов.
		
		public var adornNormal_mc:MovieClip;//анимация нормального состояния адорнийцев
		public var doctNormal_mc:MovieClip;//анимация доктовского состояния доктов
		
		public var redLine_mc:MovieClip;//линия бара адорнийцев
		public var blueLine_mc:MovieClip;//линия бара доктов
		
		public var adorn_txt:TextField;//текстфилд адорнийцев
		public var doct_txt:TextField;//текстфилд доктов
 		
		public function Dragonval()
		{
			this.visible = false;
			this.mouseEnabled = false;
			this.mouseChildren = false;
			adornCritical_mc.stop();
			adornCritical_mc.visible = false;//нужно запускать когда осталось 30%
			
			doctCritical_mc.stop();
			doctCritical_mc.visible = false; 
			
			adornMedium_mc.stop();
			adornMedium_mc.visible = false;//нужно запускать когда осталось 60%
			
			doctMedium_mc.stop();
			doctMedium_mc.visible = false;
			
			adornNormal_mc.stop();
			adornNormal_mc.visible = false;//нужно запускать когда осталось 90%
			
			doctNormal_mc.stop();
			doctNormal_mc.visible = false;
			
			redLine_mc.stop();
			blueLine_mc.stop();
		}
				
		public function SetCTEAltarStatus(fraction:int, curHealth:int, maxHealth:int, damageType:int):void 
		{
			var altarHealth:MovieClip = fraction == EFraction.ELF_FACTION? redLine_mc: blueLine_mc;
			var altarText:TextField = fraction == EFraction.ELF_FACTION? adorn_txt : doct_txt;
			
			altarText.text = curHealth.toString();
			
			var frameNumber:int = int((1-curHealth/maxHealth) * altarHealth.totalFrames);
			altarHealth.gotoAndStop(altarHealth.totalFrames - frameNumber);
			
			SetDamageAnimation(fraction,damageType);
		}
		
		private function SetDamageAnimation(fraction:int,damageType:int):void 
		{
			var lowDamage:MovieClip = fraction == EFraction.ELF_FACTION? adornNormal_mc: doctNormal_mc;
			var mediumDamage:MovieClip = fraction == EFraction.ELF_FACTION? adornMedium_mc: doctMedium_mc;
			var criticalDamage:MovieClip = fraction == EFraction.ELF_FACTION? adornCritical_mc: doctCritical_mc;
			
			lowDamage.visible = damageType == EAltarDamageType.LowDamage || damageType == EAltarDamageType.MediumDamage || damageType == EAltarDamageType.CriticalDamage ;
			mediumDamage.visible = damageType == EAltarDamageType.MediumDamage || damageType == EAltarDamageType.CriticalDamage ;
			criticalDamage.visible = damageType == EAltarDamageType.CriticalDamage;
			
			
			var curDamage:int = fraction == EFraction.ELF_FACTION? curRedDamage: curBlueDamage;
			
			var isNoPreviousDamage:Boolean = curDamage == 0;
			
			var isDamageChanged:Boolean = curDamage != damageType;
			
			if (fraction == EFraction.ELF_FACTION)
				curRedDamage = damageType;
			else
				curBlueDamage = damageType;
			
			if (!isDamageChanged) return;

			
			switch (damageType) 
			{
				case EAltarDamageType.LowDamage:
					if (isNoPreviousDamage) 
						lowDamage.gotoAndPlay(1);
					else
						lowDamage.play();
						
					criticalDamage.gotoAndStop(1);
					mediumDamage.gotoAndStop(1);
					break;
				case EAltarDamageType.MediumDamage:
					lowDamage.play();
					mediumDamage.gotoAndPlay(lowDamage.currentFrame);
					criticalDamage.gotoAndStop(1);
					break;
				case EAltarDamageType.CriticalDamage:
					lowDamage.play();
					mediumDamage.play();
					criticalDamage.gotoAndPlay(mediumDamage.currentFrame);
					break;
			}
		}
	}
}