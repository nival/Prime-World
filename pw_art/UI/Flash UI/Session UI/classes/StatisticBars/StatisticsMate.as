package StatisticBars 
{
	import BaseClasses.MateInfoBase;
	import flash.display.MovieClip;
	import Utils.AnimatedPortraitsUtils;
	
	public class StatisticsMate extends MateInfoBase 
	{
		public var animatedIcoContainer:MovieClip;
		
		public var frame2:MovieClip;
		public var frame3:MovieClip;
		public var frame4:MovieClip;
		public var frame5:MovieClip;
		public var frame5_s2:MovieClip;
		
		public function StatisticsMate() 
		{
			if (frame2 != null) {
				frame2.visible = false;
				frame3.visible = false;
				frame4.visible = false;
				frame5.visible = false;	
				frame5_s2.visible = false;	
			}
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
		
		override public function setHeroInfoBorder(leagueIndex:int):void 
		{
			super.setHeroInfoBorder(leagueIndex);
			
			if (frame2 == null) 
				return;
				
			frame2.visible = false;
			frame3.visible = false;
			frame4.visible = false;
			frame5.visible = false;		
			frame5_s2.visible = false;
			
			switch (leagueIndex) {
				// бронза
				case 4:
				case 8:
				case 12:
				case 16:
				case 20:
				case 24:
				case 28:
				case 32:
				case 36:
				case 40:
				case 44:
				case 48:
				case 52:
				case 56:
				case 60:
				case 64:
				case 68:
					frame2.visible = true;
					break;
					
				// серебро
				case 5:
				case 9:
				case 13:
				case 17:
				case 21:
				case 25:
				case 29:
				case 33:
				case 37:
				case 41:
				case 45:
				case 49:
				case 53:
				case 57:
				case 61:
				case 65:
				case 69:
					frame3.visible = true;
					break;
					
				// золото
				case 6:
				case 10:
				case 14:
				case 18:
				case 22:
				case 26:
				case 30:
				case 34:
				case 38:
				case 42:
				case 46:
				case 50:
				case 54:
				case 58:
				case 62:
				case 66:
				case 70:
					frame4.visible = true;
					break;
					
				// легенда (кроме 2 сезона)
				case 7:
				//case 11:
				case 15:
				case 19:
				case 23:
				case 27:
				case 31:
				case 35:
				case 39:
				case 43:
				case 47:
				case 51:
				case 55:
				case 59:
				case 63:
				case 67:
				case 71:
					frame5.visible = true;
					break;
					
				// легенда (2 сезона)
				case 11:
					frame5_s2.visible = true;
					break;
			}
		}
	}
}