package Controllers 
{
	public class StatBarHelper 
	{
		private var barWidth:int;
		private var levelsTable:Array;
		private var currentExp:int;
		private var earnedExp:int;
		private var premiumExp:int;
		private var currentLevel:int = 0;
		private var isTheirAnithingToShow:Boolean;
		
		public function StatBarHelper(barWidth:int)
		{
			this.barWidth = barWidth;
		}
		
		public function SetStatBarData(levelsTable:Array,prevExp:int,earnedExp:int, premiumExp:int):void
		{
			this.premiumExp = premiumExp;
			this.earnedExp = earnedExp;
			this.levelsTable = levelsTable;
			
			for (var i:int = 1; i < levelsTable.length; i++) 
			{
				if (levelsTable[i]> prevExp && prevExp >= levelsTable[i-1])
				{
					currentLevel = i;
					currentExp = prevExp - levelsTable[i-1];
					break;
				}
			}
			
			if (prevExp >= levelsTable[levelsTable.length - 1]) 
			{
				currentLevel = levelsTable.length - 1;
				currentExp = GetLevelRange(levelsTable.length - 1);
			}
		}
		
		public function GetLevelRange(level:int):int
		{
			if (level<0||level>=levelsTable.length) return 0;
			
			return levelsTable[level] - levelsTable[level - 1];
		}
		
		public function GetCurrentLevel():int
		{
			return currentLevel;
		}
		
		public function IsWillBeLevelUp():Boolean
		{
			var range:int = GetLevelRange(currentLevel);
			
			return (currentExp + earnedExp + premiumExp >= range)&&range!=0 && currentLevel != (levelsTable.length - 1);
		}
		
		public function IsTheirAnithingToShow():Boolean
		{
			return isTheirAnithingToShow;
		}
		
		public function GetWidthKoeff():Number
		{
			return barWidth / GetLevelRange(currentLevel);
		}
		
		public function GetCurrentExp():Number
		{
			return currentExp;
		}
		
		public function GetEarnedExp():Number
		{
			var range:int = GetLevelRange(currentLevel)
			
			return (currentExp + earnedExp >= range? range-currentExp :earnedExp);
		}
		
		public function GetPremiumExp():Number
		{
			var range:int = GetLevelRange(currentLevel)
			
			return (currentExp + earnedExp+premiumExp >= range? range-currentExp-GetEarnedExp():premiumExp);
		}
		
		public function GetEmpty():Number 
		{
			var emptyRange:Number = GetLevelRange(currentLevel) - currentExp - earnedExp - premiumExp;
			return emptyRange < 0? 0:emptyRange;
		}
		
		public function RefillData():void
		{
			var range:int = GetLevelRange(currentLevel);
			
			isTheirAnithingToShow = (currentExp + earnedExp + premiumExp >= range)&&range!=0 && currentLevel != (levelsTable.length - 1);
			
			if (currentExp + earnedExp + premiumExp >= range)
			{
				currentLevel++;
				
			}
			
			if (currentLevel == levelsTable.length)
					currentLevel = levelsTable.length - 1;	
			
				
			range = range - currentExp;
			
			currentExp = 0;
			if (range > earnedExp)
			{
				earnedExp = 0;
				range = range - earnedExp;
			}
			else
			{
				earnedExp = earnedExp - range;
				range = 0;
			}
			
			if (range > 0) 
			{
				if (range > premiumExp)
				{
					premiumExp = 0;
					range = range - premiumExp;
				}
				else
				{
					premiumExp = premiumExp - range;
					range = 0;
				}
			}
		}
		

	}

}