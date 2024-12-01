package BaseClasses 
{
	import flash.events.EventDispatcher;
	public class BaseContextItem 
	{
		private var name:String = "";
		protected var heroID:int = -1;
		protected var isHero:Boolean = false;
		protected var isItOurHero:Boolean;
		protected var windowNeededToOpen:int = -1;
		public var IsNegativeItem:Boolean = false;
		public var ForseDispatcher:EventDispatcher;
		
		public function BaseContextItem(_isHero:Boolean,_name:String,isOurHero:Boolean=false,_heroID:int=-1) 
		{
			name = _name;
			heroID =  _heroID;
			isHero = _isHero;
			isItOurHero = isOurHero;
			SetNeededWindow();
		}
		
		protected function SetNeededWindow():void 
		{
			
		}
		
		public function get Name():String 
		{
			return name;
		}
		
		public function Press():void 
		{
			
		}
		
		public function get WindowNeededToBeOpen():int
		{
			return windowNeededToOpen;
		}
		
	}

}