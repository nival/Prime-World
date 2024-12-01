package Announcements
{
	public class AnnouncementData
	{
		private var _leftPortrait:AnnouncementPotraitData;
		private var _rightPortrait:AnnouncementPotraitData;
		private var _announcementText:String;
		private var _priority:int;
		private var _lifeTime:Number;
		
		public function set Priority(value:int):void
		{
			_priority = value;
		}
		public function get Priority():int
		{
			return _priority;
		}
		public function set AnnouncementText(value:String):void
		{
			_announcementText = value;
		}
		
		public function get AnnouncementText():String
		{
			return _announcementText;
		}
		
		public function set LeftPortrait(value:AnnouncementPotraitData):void
		{
			_leftPortrait = value;
		}
		public function get LeftPortrait():AnnouncementPotraitData
		{
			return _leftPortrait;
		}
		
		public function set RightPortrait(value:AnnouncementPotraitData):void
		{
			_rightPortrait = value;
		}
		public function get RightPortrait():AnnouncementPotraitData
		{
			return _rightPortrait;
		}
		
		public function set LifeTime(value:Number):void
		{
			_lifeTime = value;
		}
			
		public function get LifeTime():Number
		{
			return _lifeTime;
		}
	}
}