package ContMenu 
{
	import BaseClasses.BaseContextItem;
	import Enums.EWindows;
	
	public class ContextItemCharstat extends BaseContextItem
	{
		public function ContextItemCharstat(_isHero:Boolean,_name:String,isOurHero:Boolean=false,_heroID:int=-1) 
		{
			super(_isHero,_name,isOurHero,_heroID);
		}
		
		override protected function SetNeededWindow():void 
		{
			windowNeededToOpen = isItOurHero? EWindows.WINDOW_CHARSTATBAR:EWindows.WINDOW_SELECTIONCHARSTAT;
		}
		
		override public function Press():void 
		{
			if (isItOurHero) return;
			
			FSCommands.Send(FSCommands.FILL_CHARSTAT_FORUNIT, int(isHero) + " " + heroID);
		}
	}
}