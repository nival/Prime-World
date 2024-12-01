package ContMenu 
{
	import BaseClasses.BaseContextItem;
	import Enums.EWindows;
	
	public class ContextItemTalants extends BaseContextItem
	{
		public function ContextItemTalants(_isHero:Boolean,_name:String,isOurHero:Boolean=false,_heroID:int=-1) 
		{
			super(_isHero, _name, isOurHero, _heroID);
		}
		
		override protected function SetNeededWindow():void 
		{
			windowNeededToOpen = isItOurHero? EWindows.WINDOW_TALENTSBAR:EWindows.WINDOW_SELECTIONTALANTBAR;
		}
		
		override public function Press():void 
		{
			if (isItOurHero) return;
			FSCommands.Send(FSCommands.OPEN_TALANTS_FORUNIT, int(true) + " " + heroID);
		}
		
	}

}