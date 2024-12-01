package Components 
{
	import BaseClasses.TooltipSender;
	import BaseClasses.BaseIconLoader;
	import flash.display.MovieClip;
	
	public class HeroRankIconHolder extends TooltipSender
	{
		public var eliteHero_mc:BaseIconLoader;
		
		public var back2:MovieClip;
		public var back3:MovieClip;
		public var back4:MovieClip;
		
		public function HeroRankIconHolder()
		{
			back2.visible = false;
			back3.visible = false;
			back4.visible = false;
		}
		
		
		public function set Icon(value:String) 
		{
			eliteHero_mc.SetIcon(value);
		}
		
		public function setLeagueIndex(leagueIndex:int):void
		{
			back2.visible = false;
			back3.visible = false;
			back4.visible = false;
			
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
					back2.visible = true;
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
					back3.visible = true;
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
					back4.visible = true;
					break;
					
				// легенда
				case 7:
				case 11:
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
					back4.visible = true;
					break;
			}
		}
	}

}