package ContMenu 
{
	import BaseClasses.BaseContextItem;
	
	public class ContextItemSwitchToSpectate extends BaseContextItem
	{
		public function ContextItemSwitchToSpectate(_isHero:Boolean,_name:String, isOurHero:Boolean, _heroID:int) 
		{
			super(_isHero, _name, isOurHero, _heroID);
		}
		
		override public function Press():void
		{
			if (heroID == -1) return;
			
			FSCommands.Send(FSCommands.START_SPECTATE, heroID.toString());
		}
		
	}

}