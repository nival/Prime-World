package Datas 
{
	import fl.motion.Color;
	public class Channel 
	{
		public static const NormalChannel:int = 0;
		public static const PrivateChannel:int = 1;
		public static const SystemChannel:int = 2;
		public var ChannelType:int = 0;
		
		private var comboBoxIndex:int = -1;
		private var playerCanWriteInTo:Boolean;
		private var _channelId:int;
		private var _channelName:String;
		private var _channelColor:uint;
		private var _showChannelName:Boolean;
		private var _showPlayerName:Boolean;
	
		public function get ChannelId():int 
		{
			return _channelId;
		}
		
		public function set ChannelId(value:int):void 
		{
			_channelId = value;
		}
		
		public function get ChannelName():String 
		{
			return _channelName;
		}
		
		public function set ChannelName(value:String):void 
		{
			_channelName = value;
		}
		
		public function get ChannelColor():uint 
		{
			return _channelColor;
		}
		
		public function set ChannelColor(value:uint):void 
		{
			_channelColor = value;
		}
		
		public function get ShowChannelName():Boolean 
		{
			return _showChannelName;
		}
		
		public function set ShowChannelName(value:Boolean):void 
		{
			_showChannelName = value;
		}
		
		public function get ShowPlayerName():Boolean 
		{
			return _showPlayerName;
		}
		
		public function set ShowPlayerName(value:Boolean):void 
		{
			_showPlayerName = value;
		}
		
		public function get PlayerCanWriteInTo():Boolean 
		{
			return playerCanWriteInTo;
		}
		
		public function set PlayerCanWriteInTo(value:Boolean):void 
		{
			playerCanWriteInTo = value;
		}
		
		public function get ComboBoxIndex():int 
		{
			return comboBoxIndex;
		}
		
		public function set ComboBoxIndex(value:int):void 
		{
			comboBoxIndex = value;
		}
		
	}

}