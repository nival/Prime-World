package MainScreen 
{
	import BaseClasses.BaseDragObject;
	import BaseClasses.BaseIconLoader;
	import BaseClasses.BaseResizableObject;
	import Components.ButtonStandart;
	import Components.ButtonToggle;
	import Components.FrameChat;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.Timer;
	import TalantBarSelection.SelectionTalent;

	public class QuestHint extends BaseDragObject
	{
		private var _currentHintId:String;
		
		public var buttonHintClose:ButtonStandart
		public var hintText:TextField;
		public var hintImage_mc:BaseIconLoader
		public var header_txt:TextField;
		public var separator_mc:MovieClip;
		
		private var hintBackHeight:Number;
		private var hintBackStartY:Number;
		private var textStartY:Number;
		private var startTextSize:Number;
		private var startButtonYPos:Number;
		private var textDownOffset:Number;
		private var textTopOffset:Number;
		private var startTextYPos:Number;
		private var startButtonDownOffset:Number;
		private var separatorDownOffset:Number;
		private var timer:Timer;
		
		private const duration:Number = 300;
		
		public function QuestHint() 
		{
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
			
			buttonHintClose.addEventListener("Up", OnCloseHintPress)
			closeButton_mc.addEventListener("Up", OnClose);
			timer = new Timer(duration,1);
			timer.addEventListener(TimerEvent.TIMER_COMPLETE, OnTimerComplete);
			timer.stop();
		}
		
		private function OnTimerComplete(e:TimerEvent):void 
		{
			closeButton_mc.enable();
			buttonHintClose.EnableButton = true;
		}
		
		private function OnCloseHintPress(e:Event):void 
		{
			OnClose(e);
			closeThisFunction(e);
		}
		
		private function OnClose(e:Event):void 
		{
			FSCommands.Send(FSCommands.EXITHINTDIALOG, _currentHintId);
		}
		
		private function FillLocalization(e:Event):void 
		{
			buttonHintClose.LocalizeText = Localization.QuestHint_DefaultText;
		}
		
		override public function AddedToStage(e:Event):void 
		{
			super.AddedToStage(e);
			SetInToCenter();
			startTextSize = hintText.textHeight;
			textTopOffset = hintText.y - (hintImage_mc.y + hintImage_mc.GetInitialHeight());
			textDownOffset = buttonHintClose.y - hintText.textHeight - hintText.y;
			startButtonYPos = buttonHintClose.y;
			startTextYPos = hintText.y;
			startButtonDownOffset = this.height - buttonHintClose.y;
			
			separatorDownOffset = wframe_mc.height - separator_mc.y;
			
		}
		
		private function SetInToCenter():void 
		{
			this.x = (stage.stageWidth - width) / 2;
			this.y = (stage.stageHeight - height)/ 2;
			this.x = Math.floor(this.x);
			this.y = Math.floor(this.y);
		}
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			SetInToCenter();
		}
		
		public function SetQuestHint(id:String, title:String, hintTxt:String, picture:String) : void
		{
			
			closeButton_mc.disable();
			buttonHintClose.EnableButton = false;
			timer.stop();
			timer.start();
			_currentHintId = id;
			hintText.text = hintTxt;
			header_txt.text = title;
			hintImage_mc.SetIcon(picture);
			
			if (hintText.textHeight >= startTextSize)
			{
				hintText.y = startTextYPos;
				if (hintText.numLines <= 7) 
				{
					hintText.autoSize = TextFieldAutoSize.CENTER;
					buttonHintClose.y = hintText.y + hintText.textHeight + textDownOffset;	
				}
				else 
				{
					hintText.autoSize = TextFieldAutoSize.NONE;
					buttonHintClose.y = hintText.y + hintText.height + textDownOffset;
				}
			}
			else
			{
				hintText.y = (startTextYPos - textTopOffset) + (startButtonYPos - startTextYPos + textTopOffset - (separatorDownOffset - startButtonDownOffset)) / 2 - 
							hintText.textHeight / 2;
				buttonHintClose.y = startButtonYPos;
			}
			
			wframe_mc.height = startButtonDownOffset + buttonHintClose.y;
			separator_mc.y = wframe_mc.height - separatorDownOffset;
			
			SetInToCenter();
		}
		
		public function OnEscPressed():void
		{
			OnCloseHintPress(null);
		}
		
	}

}