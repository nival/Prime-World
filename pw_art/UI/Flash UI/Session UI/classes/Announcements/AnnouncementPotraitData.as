package Announcements
{
	public class AnnouncementPotraitData
	{
		private var _icon:String;
		private var _level:int;
		private var _fraction:int;
		private var _heroName:String;
		public var isFilled:Boolean;
		
		public function set Icon(value:String):void
		{
			_icon = value;
		}
		
		public function get Icon():String
		{
			return _icon;
		}
		
		public function set Level(value:int):void
		{
			_level = value;
		}
		
		public function get Level():int 
		{
			return _level;
		}
		
		public function set Fraction(value:int):void
		{
			_fraction = value;
		}
		
		public function get Fraction():int
		{
			return _fraction;
		}
		
		public function set HeroName(value:String):void
		{
			_heroName = value;
		}
		
		public function get HeroName():String
		{
			return _heroName;
		}		
	}
	
	
}