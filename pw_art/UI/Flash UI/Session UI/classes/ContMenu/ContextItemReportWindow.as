package ContMenu 
{
	import BaseClasses.BaseContextItem;
	import Enums.EWindows;
	import Events.PrepareReportWindowEvent;
	
	public class ContextItemReportWindow extends BaseContextItem
	{
		private var _playerName:String;
		
		public function ContextItemReportWindow(_isHero:Boolean, _name:String, playername:String, _isOurHero:Boolean=false, _heroID:int=-1 )
		{
			super (_isHero, _name, _isOurHero, _heroID);
			_playerName = playername;
			IsNegativeItem = true;
		}
		
		override protected function SetNeededWindow():void 
		{
		}
		
		override public function Press():void 
		{
			ForseDispatcher.dispatchEvent(new PrepareReportWindowEvent(_playerName, heroID));
		}
		
	}

}