package ContMenu 
{
	import BaseClasses.BaseContextItem;
	
	public class ContextItemAddFriend extends BaseContextItem
	{
		public function ContextItemAddFriend(_isHero:Boolean,_name:String,isOurHero:Boolean=false,_heroID:int=-1) 
		{
			super(_isHero, _name, isOurHero, _heroID);
			IsNegativeItem = true;
		}
		
		override public function Press():void
		{
			FSCommands.Send(FSCommands.ADD_TO_FRIENDS, heroID.toString());
		}
	}

}