package MainScreen 
{
	import BaseClasses.BaseDragObject;
	import Components.ButtonStandart;
	import Components.WFrame;
	import Events.WindowVisibleControllerEvent;
	import flash.events.Event;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	public class MessageBox extends BaseDragObject
	{
		public var wFrame_mc:WFrame;
		public var header_txt:TextField;
		public var msgText_txt:TextField;
		public var msgYes_btn:ButtonStandart;
		public var msgNo_btn:ButtonStandart;
		public var msgOk_btn:ButtonStandart;
		
		private var onYesFunction:Function;
		private var onNoFunction:Function;
		public function MessageBox() 
		{
			msgYes_btn.addEventListener("Up", OnYesBtnClick);
			msgNo_btn.addEventListener("Up", OnNoBtnClick);
			msgOk_btn.addEventListener("Up", OnNoBtnClick);
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
				
				
			msgText_txt.autoSize = TextFieldAutoSize.CENTER;
			msgText_txt.y = - msgText_txt.height/2;
		}
		
		private function FillLocalization(e:Event):void 
		{
			msgNo_btn.LocalizeText = Localization.MessageBox_NoBtn;
			msgYes_btn.LocalizeText = Localization.MessageBox_YesBtn;
		}
		
		public function PrepareDialog( _dialogHeader : String, _dialogText:String,_onYesFunction:Function,_onNoFunction:Function, isOkDialog:Boolean):void
		{
			
			msgYes_btn.visible = !isOkDialog;
			msgNo_btn.visible =  !isOkDialog;
			msgOk_btn.visible =  isOkDialog;
			
			header_txt.text = _dialogHeader;
			msgText_txt.text = _dialogText;
			onYesFunction = _onYesFunction;
			onNoFunction = _onNoFunction;
			msgText_txt.y = - msgText_txt.height/2;
		}
			
		private function OnYesBtnClick(e:Event):void 
		{
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN_CLOSE, WindowIndex));
			if (onYesFunction == null) return;
			onYesFunction.call();
		}
		
		public function OnNoBtnClick(e:Event):void 
		{
			closeThisFunction(null);
		}
			
		override protected function closeThisFunction(e:Event):void 
		{
			super.closeThisFunction(e);
			if (onNoFunction == null) return;
			
			onNoFunction.call();
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			this.x = stage.stageWidth/ 2;
			this.y = stage.stageHeight/ 2;
		}
		
		override public function SetOnStartPosition():void 
		{
			
		}
		
		override public function ShowCinematicDialog():void
		{
			// remains unaffected by dialog
		}
	}

}