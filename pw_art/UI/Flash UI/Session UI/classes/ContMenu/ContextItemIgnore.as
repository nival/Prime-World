package ContMenu 
{
	import BaseClasses.BaseContextItem;

	public class ContextItemIgnore extends BaseContextItem
	{
		public function ContextItemIgnore(_isHero:Boolean, _name:String, isOurHero:Boolean = false, _heroID:int = -1) 
		{
			super(_isHero, _name, isOurHero, _heroID);
			
			IsNegativeItem = true;
		}
		
		override public function Press():void
		{
			if (isItOurHero)
				return;
			if (heroID < 0)
				return;
			
			FSCommands.Send(FSCommands.IGNORE_USER, heroID.toString());
		}
	}
}