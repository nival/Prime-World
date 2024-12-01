package Datas 
{
	public class ChatMessage 
	{
		
		private var channel:Channel;
		private var playerId:int;
		private var playerName:String;
		private var message:String;
		private var icon:String;
		private var isEnemy:Boolean;
		
		public function get ChannelData():Channel 
		{
			return channel;
		}
		
		public function set ChannelData(value:Channel):void 
		{
			channel = value;
		}
		
		public function get PlayerId():int
		{
			return playerId;
		}
		
		public function set PlayerId(value:int):void
		{
			playerId = value;
		}
		
		public function get PlayerName():String 
		{
			return playerName;
		}
		
		public function set PlayerName(value:String):void 
		{
			playerName = value;
		}
		
		public function get Message():String 
		{
			return message;
		}
		
		public function set Message(value:String):void 
		{
			message = value;
		}
		
		public function get Icon():String
		{
			return icon;
		}
		
		public function set Icon(value:String):void
		{
			icon = value;
		}
		
		public function get IsEnemy():Boolean
		{
			return isEnemy;
		}
		
		public function set IsEnemy(value:Boolean):void
		{
			isEnemy = value;
		}
	}

}