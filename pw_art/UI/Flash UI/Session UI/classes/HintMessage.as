package
{
	
	import BaseClasses.BaseResizableObject;
	import fl.transitions.TweenEvent;
	import flash.display.MovieClip;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import flash.events.Event;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import Components.Frame;
	import Enums.EBubbleViewType;
	
	public class HintMessage extends MovieClip
	{
		public var txt:TextField;
		public var showeffect_mc:MovieClip;
		public var frame_mc:Frame;
		public var	mouse_mc:MovieClip;
		
		private var tweenAlphaShow:Tween;
		private var time:int = 30;
		private var _showingText:String = "";

		private var Width:Number;
		private var Height:Number;
		private var isShowing:Boolean;
		private var _bubbleType: String;
		public function HintMessage()
		{
			this.alpha = 0;
			this.mouseChildren = false;
			this.mouseEnabled = false;
			mouse_mc.visible = false;
			
			Width = this.width;
			Height = this.height;
			
			txt.text = "";
			txt.autoSize = TextFieldAutoSize.CENTER;
			
			tweenAlphaShow = new Tween(this, 'alpha', Strong.easeOut, 0, 1, time);
			tweenAlphaShow.addEventListener(TweenEvent.MOTION_FINISH, OnShowEventFinish);
			tweenAlphaShow.stop();
			showeffect_mc.stop();
			
		}
		
		private function OnShowEventFinish(e:TweenEvent):void 
		{
			if (isShowing) return;
			
			if (_showingText != "")
				Show(_showingText);
			else
				txt.text = "";
		}
		
		public function Show(text:String):void
		{
			isShowing = true;
			
			txt.text = text;
			mouse_mc.visible = _bubbleType == EBubbleViewType.LeftClickElement || _bubbleType == EBubbleViewType.RightClickElement;
			
			mouse_mc.gotoAndStop(_bubbleType == EBubbleViewType.RightClickElement? 2 : 1);
			
			var textOffset:Number = _bubbleType == EBubbleViewType.NoElements?  0 : mouse_mc.width / 2;
			
			frame_mc.setSize(Math.round(txt.width + 20 + textOffset), Math.round(txt.height + 15));
			txt.x -= textOffset * 2;
			frame_mc.x = txt.x - 10;
			frame_mc.y = txt.y - 7;
			
			mouse_mc.x = frame_mc.x + frame_mc.width - mouse_mc.width;
			//mouse_mc.y = frame_mc.y - (frame_mc.height - mouse_mc.height);
			
			showeffect_mc.width = frame_mc.width;
			showeffect_mc.height = frame_mc.height;
			showeffect_mc.x = frame_mc.x;
			showeffect_mc.y = frame_mc.y;
					
			tweenAlphaShow.continueTo(1, time);
			showeffect_mc.gotoAndPlay(1);
		}
		
		private function Hide():void
		{
			isShowing = false;
			tweenAlphaShow.continueTo(0, time);
		}
		
		public function SetText(text:String,type:String):void 
		{
			_bubbleType = type;
			
			if (_showingText == text)
				return;
			
			_showingText = text;
			
			if (text == "" || (txt.text!=text && txt.text!=""))
			{
				Hide();
				return;
			}
			
			Show(text);
		}
		
		public function GetHintMessageCenterOffset():Number
		{
			var offset: Number = frame_mc.x + frame_mc.width / 2;
			
			return offset;
		}
	}
}
