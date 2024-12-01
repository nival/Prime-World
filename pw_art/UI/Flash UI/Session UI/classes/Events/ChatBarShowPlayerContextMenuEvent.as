package Events 
{
	import flash.events.Event;
	public class ChatBarShowPlayerContextMenuEvent extends Event
	{
		public static const EVENT_TYPE:String = 'ChatBarShowPlayerContextMenuEvent';
		
		public var HeroId:int;
		public var Name:String;
		
		public function ChatBarShowPlayerContextMenuEvent(heroId:int, name:String, bubbles:Boolean = true) 
		{
			super(EVENT_TYPE, bubbles);
			
			HeroId = heroId;
			Name = name;
		}
		
	}

}