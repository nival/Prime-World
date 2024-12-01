package Events
{
	import flash.events.Event;
	
	public class ShowDialogEvent extends Event 
	{
		public static const EVENT_TYPE:String = 'ShowDialogEvent';
		public var dialogHeader:String = "";
		public var dialogText:String = "";
		public var onYes:String;
		public var OnYesFunction:Function;
		public var OnNoFunction:Function;
		public var OkDialog:Boolean;
		
		public function ShowDialogEvent( _dialogHeader:String, _dialogText:String,_onYesFunction:Function,_onNoFunction:Function, okDialog:Boolean = false, bubbles:Boolean=true)
		{ 
			super(EVENT_TYPE, bubbles);
			dialogHeader = _dialogHeader;
			dialogText = _dialogText;
			OnYesFunction = _onYesFunction;
			OnNoFunction = _onNoFunction;
			OkDialog = okDialog;
		} 
	}
	
}