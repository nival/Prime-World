package Datas
{
	public class ErrorMessagesData
	{
		private var message:String;
		private var playSound:Boolean;
		private var lifeTime:Number;
		private var _id:int;
		
		public function set ID(value:int):void
		{
			_id=value;
		}
		
		public function get ID():int
		{
			return _id;
		}
		
		public function set Message(value:String):void
		{
			message=value;
		}
		
		public function get Message():String
		{
			return message;
		}
	
		public function set PlaySound(value:Boolean):void
		{
			playSound=value;
		}
		
		public function get PlaySound():Boolean
		{
			return playSound;
		}
		
		public function set LifeTimes(value:Number):void
		{
			lifeTime = value;
		}
		
		public function get LifeTimes():Number
		{
			return lifeTime;
		}
		
	}
	
}