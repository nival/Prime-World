package Events 
{
	import flash.events.Event;

	public class PrepareReportWindowEvent extends Event
	{
		public static const CONTEXT_REPORT:String = "PrepareReportWindow";
		public var playerName:String = "";
		public var heroID:int;
		
		public function PrepareReportWindowEvent(_playerName:String, _heroID:int) 
		{
			super(CONTEXT_REPORT, true);
			playerName = _playerName;
			heroID = _heroID;
		}
		
	}

}