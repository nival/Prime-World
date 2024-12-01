package Datas 
{
	public class ChannelShortcut 
	{	
		private var channelID:int = -1;
		private var shortcut:String = "";
		
		public function get ChannelID():int 
		{
			return channelID;
		}
		
		public function set ChannelID(value:int):void 
		{
			channelID = value;
		}
		
		public function get Shortcut():String 
		{
			return shortcut;
		}
		
		public function set Shortcut(value:String):void 
		{
			shortcut = value;
		}
		
	}

}