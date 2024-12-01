package ReportWindow
{
	import BaseClasses.BaseDragObject;
	import BaseClasses.BaseResizableObject;
	import BaseClasses.TooltipSender;
	import Events.PrepareReportWindowEvent;
	import Components.ButtonStandart;
	import Components.PWCombobox;
	import Components.ScrollBar;
	import Enums.EWindows;
	import Events.PWComponentValueEvent;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.FocusEvent;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.text.TextField;
	import flash.utils.Dictionary;
	
	public class ReportWindow extends BaseDragObject
	{
		
		public var header_txt:TextField;
		public var hintChoose_txt:TextField;
		public var count_txt:TextField;
		public var hint_txt:TextField;
		public var nickname_txt:TextField;
		public var input_hint_txt:TextField;
		public var input_txt:TextField;
		
		public var report_btn:ButtonStandart;
		public var cancel_btn:ButtonStandart;
		
		public var combobox:PWCombobox;
		
		public var scroll:ScrollBar;
		public var ReportedUsers:Array;
		public var TT_Sender:TooltipSender;
		public var reportCountIcon:MovieClip;
		public var inputHit:MovieClip;
		
		private var DictID:Dictionary = new Dictionary;
		private var _currentReportItem:int;
		private var _currentReportCount:int = 0;
		private var _maxReportCount:int = 5;
		private var _heroID:int;
		private var _focusIN:Boolean;
		private var isInitialised:Boolean = false;
		private var _inputString:String = "";
		private var _maxInputChars:int = 119;
		private var isOnInput:Boolean
		private var isLocalisationFilled:Boolean;
		
		public function ReportWindow()
		{
			header_mc.mouseEnabled = true;
			header_txt.mouseEnabled = true;
			input_txt.mouseEnabled = true;
			input_hint_txt.mouseEnabled = false;
			
			report_btn.addEventListener("Up", OnReportUp);
			cancel_btn.addEventListener("Up", closeThisFunction);
			
			input_txt.addEventListener(TextEvent.TEXT_INPUT, OnInputText);
			input_txt.addEventListener(KeyboardEvent.KEY_DOWN, OnKeyDown);
			
			inputHit.addEventListener(MouseEvent.CLICK, OnInputClick);
			inputHit.addEventListener(MouseEvent.MOUSE_OVER, OverInput);
			inputHit.addEventListener(MouseEvent.MOUSE_OUT, OutInput);
			
			input_txt.addEventListener(MouseEvent.CLICK, OnInputClick);
			input_txt.addEventListener(MouseEvent.MOUSE_OVER, OverInput);
			input_txt.addEventListener(MouseEvent.MOUSE_OUT, OutInput);
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
			
			combobox.addEventListener(PWComponentValueEvent.CHANGE, OnComboChange);
			count_txt.text = _currentReportCount + "/" + _maxReportCount;
			TT_Sender.TooltipText = Localization.ReportWindow_CounterTooltip;
			//	scroll.SetScrollableContent(input_txt, false);
			
			UpdateReportWindow();
		}
		
		private function OnKeyDown(e:KeyboardEvent):void
		{
			if (e.keyCode == 8)
				_inputString = _inputString.substr(0, _inputString.length - 1);
		}
		
		private function OnInputClick(e:MouseEvent):void
		{
			stage.focus = input_txt;
			
			input_hint_txt.visible = false;
		}
		
		private function OutInput(e:MouseEvent):void
		{
			isOnInput = false;
		}
		
		private function OverInput(e:MouseEvent):void
		{
			isOnInput = true;
		}
		
		private function OnStageClick(e:MouseEvent):void
		{
			if (isOnInput)
				return;
			
			if (stage.focus == input_txt)
				stage.focus = null;
			
			if (input_txt.text == "")
				input_hint_txt.visible = true;
		}
		
		private function OnInputText(e:TextEvent):void
		{
			e.preventDefault();
			
			UpdateReportInput();
			
			if (input_txt.text.length > _maxInputChars)
				return;
			
			_inputString += e.text;
			
			UpdateReportInput();
		
		}
		
		private function UpdateReportInput():void
		{
			input_txt.text = _inputString;
		}
		
		override public function AddedToStage(e:Event):void
		{
			super.AddedToStage(e);
			scroll.visible = false;
			stage.addEventListener(MouseEvent.CLICK, OnStageClick);
			this.x = (stage.stageWidth - this.width) / 2;
			this.y = (stage.stageHeight - this.height) / 2;
			input_txt.text = "";
		}
		
		public function TrySetHeroReportParams(id:int, name:String):Boolean
		{
			if (!isInitialised)
				return false;
			
			count_txt.text = _currentReportCount + "/" + _maxReportCount;
			
			TT_Sender.width = reportCountIcon.width + count_txt.textWidth;
			
			input_txt.text = "";
			_inputString = "";
			
			if (stage.focus == input_txt)
			{
				stage.focus = null;
				if (input_txt.text == "")
					input_hint_txt.visible = true;
			}
			
			FSCommands.Send(FSCommands.REPORT_WINDOW_OPENED, FSCommands.ENABLE);
			UpdateReportWindow();
			nickname_txt.text = name;
			_heroID = id;
			
			return true;
		}
		
		private function UpdateReportWindow():void
		{
			if (_currentReportCount == 0 || combobox.SelectedIndex==0)
				report_btn.disable();
			else
				report_btn.enable();
		}
		
		private function OnComboChange(e:PWComponentValueEvent):void
		{
			e.stopPropagation();
			_currentReportItem = DictID[e.componentValue];
			UpdateReportWindow();
		}
		
		public function SetReportCounters(currentReportCount:int, maxReportCount:int):void
		{
			_currentReportCount = currentReportCount;
			_maxReportCount = maxReportCount;
			count_txt.text = currentReportCount + "/" + maxReportCount;
			UpdateReportWindow();
		}
		
		public function AddReportComboboxItem(reportItemID:int, reportItemString:String):void
		{
			isInitialised = true;
			
			if(combobox.GetRows().length==0)
				combobox.AddComboBoxRow(Localization.ReportWindow_DefaultText);
				
			var comboIndex:int = combobox.AddComboBoxRow(reportItemString);
			
			if (comboIndex == -1)
				return;
			
			DictID[comboIndex] = reportItemID;
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void
		{
			super.BaseBarObjectResize(e);
			this.x = (stage.stageWidth - this.width) / 2;
			this.y = (stage.stageHeight - this.height) / 2;
		}
		
		private function FillLocalization(e:Event):void
		{
			header_txt.text = Localization.ReportWindow_Header;
			hintChoose_txt.text = Localization.ReportWindow_ReportChioceTExt;
			hint_txt.text = Localization.ReportWindow_HintTExt;
			cancel_btn.LocalizeText = Localization.ReportWindow_CancelButton;
			report_btn.LocalizeText = Localization.ReportWindow_ReportButton;
			input_hint_txt.text = Localization.ReportWindow_HintEmptyText;
			TT_Sender.TooltipText = Localization.ReportWindow_CounterTooltip;
			
			var rows:Array = combobox.GetRows();
			
			if (rows.length == 0)
				return;	
				
			rows[0].Text = Localization.ReportWindow_DefaultText;
			
		}
		
		private function OnReportUp(e:Event):void
		{
			
			for (var i:int = 0; i < ReportedUsers.length; i++)
			{
				if (ReportedUsers[i] == _heroID)
					return;
			}
			
			ReportedUsers.push(_heroID);
			_currentReportCount--;
			if (input_txt.text == "")
				input_txt.text = "None";
			FSCommands.Send(FSCommands.REPORT_WINDOW_SEND_REPORT, _heroID.toString() + ' ' + _currentReportItem.toString() + ' ' + input_txt.text);
			FSCommands.Send(FSCommands.IGNORE_USER, _heroID.toString());
			
			closeThisFunction(e);
		}
		
		public function IsInFocus():Boolean
		{
			return (stage.focus == this || stage.focus == input_txt);
		}
		
		public function OnEnterPressed():void
		{
		
		}
	}

}