package MainScreen 
{
	import Components.PWFrame;
	import Enums.EBubbleViewType;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.geom.Point;
	import flash.text.TextField;
	import Components.Frame;
	import Components.ButtonStandart;
	import flash.text.TextFieldAutoSize;
	public class BubbleControl extends MovieClip
	{
		public var mouse_mc:MovieClip;
		public var toolTip_txt:TextField;
		public var tooltipFrameLeft_mc:PWFrame;
		public var tooltipFrameRight_mc:PWFrame;
		public var tooltipFrameUpRight_mc:PWFrame;
		public var tooltipFrameUpLeft_mc:PWFrame;
		public var next_btn:ButtonStandart;
		private var control:MovieClip;
		private var text:String;
		
		
		private var xLeftOffset:Number;
		private var xRightOffset:Number;
		private var bottomArrowOffset:Number;
		private var topArrowOffset:Number;
		
		private var topNoArrowOffset:Number;
		private var debthIndex:int = -1;
		private var currentControlX:Number;
		private var currentControlY:Number;
		private var frameWidth:Number;
		private var frameHeight:Number;
		private var xOffset:Number;
		private var yOffset:Number;
		private var visibleControl:MovieClip;
		private var bubbleViewType:String;
		
		private var nextBtnOffset:Number = 10;
		
		private var positionXOffset:Number = 25;
		private var bubbleIndex:int;
		
		public function BubbleControl(_control:MovieClip, _text:String, _bubbleViewType:String, _bubbleIndex:int, _xOffset:Number = 0, _yOffset:Number = 0)
		{
			bubbleIndex = _bubbleIndex;
			bubbleViewType = _bubbleViewType;
		//	visibleControl = _visibleControl;
			
			this.mouseEnabled = false;
			tooltipFrameLeft_mc.mouseEnabled = tooltipFrameLeft_mc.mouseChildren =false;
			tooltipFrameRight_mc.mouseEnabled = tooltipFrameRight_mc.mouseChildren  = false;
			tooltipFrameUpRight_mc.mouseEnabled = tooltipFrameUpRight_mc.mouseChildren = false;
			tooltipFrameUpLeft_mc.mouseEnabled = tooltipFrameUpLeft_mc.mouseChildren = false;
			toolTip_txt.mouseEnabled = false;
			mouse_mc.mouseEnabled = false;
			
			tooltipFrameLeft_mc:PWFrame;

			yOffset = _yOffset;
			xOffset = _xOffset;
			
			text = _text;
			visible = false;
			control = _control;
			addEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
		}
		
		private function OnLocalizationComplete(e:Event):void 
		{
			next_btn.LocalizeText = Localization.BubbleNextButton;
		}
		
		private function OnAddedToStage(e:Event):void 
		{
			Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, OnLocalizationComplete);
			removeEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
			next_btn.addEventListener("Up", OnNextBtnClick);
			next_btn.LocalizeText = Localization.BubbleNextButton;
			toolTip_txt.autoSize = TextFieldAutoSize.LEFT;
			
			xLeftOffset =  toolTip_txt.x;
			xRightOffset = tooltipFrameLeft_mc.width - (toolTip_txt.x + toolTip_txt.width);
			bottomArrowOffset = tooltipFrameLeft_mc.height - (toolTip_txt.y + toolTip_txt.height);
			topArrowOffset = toolTip_txt.y - tooltipFrameUpLeft_mc.y;
			topNoArrowOffset = toolTip_txt.y;
			
			tooltipFrameUpRight_mc.y = tooltipFrameUpLeft_mc.y = 0;
			mouse_mc.visible = bubbleViewType == EBubbleViewType.LeftClickElement || bubbleViewType == EBubbleViewType.RightClickElement;
			next_btn.visible = bubbleViewType == EBubbleViewType.NextButtonElement;
			
			mouse_mc.gotoAndStop(bubbleViewType == EBubbleViewType.RightClickElement? 2 : 1);
			
			SetDebthPosition();
			SetSize();
			control.addEventListener(Event.ENTER_FRAME, OnEnterFrame);
		
		}
		
		private function OnNextBtnClick(e:Event):void 
		{
			FSCommands.Send(FSCommands.BubbleNextButtonClick, bubbleIndex.toString());
		}
		
		public function Destroy():void 
		{
			control.removeEventListener(Event.ENTER_FRAME, OnEnterFrame);
		}
		
		private function SetSize():void 
		{
			toolTip_txt.text = text;
			toolTip_txt.text = text;
			
			frameWidth = toolTip_txt.textWidth + xLeftOffset + xRightOffset;

			var addition:Number = 0;
			
			if (mouse_mc.visible) 
			{
				addition = mouse_mc.height;
			}
			
			if (next_btn.visible)
			{
				addition = nextBtnOffset + next_btn.GetHeight();
			}
			
			frameHeight = toolTip_txt.textHeight + topNoArrowOffset + bottomArrowOffset + addition;

			tooltipFrameLeft_mc.setSize(frameWidth, frameHeight);
			tooltipFrameRight_mc.setSize(frameWidth, frameHeight);
			tooltipFrameUpRight_mc.setSize(frameWidth, frameHeight);
			tooltipFrameUpLeft_mc.setSize(frameWidth, frameHeight);
		}
		
		private function OnEnterFrame(e:Event):void 
		{
			visible = IsControlVisible(visibleControl==null? control:visibleControl);
			SetDebthPosition();
			
			var globalX:Number = control.localToGlobal(new Point(0,0)).x;
			var globalY:Number = control.localToGlobal(new Point(0, 0)).y;
			
			if (currentControlX == globalX && currentControlY == globalY) return;
			
			tooltipFrameLeft_mc.visible = globalX + frameWidth<=stage.stageWidth && globalY - this.height >= 0;
			tooltipFrameRight_mc.visible = globalX + frameWidth>stage.stageWidth && globalY - this.height >= 0;
			
			tooltipFrameUpLeft_mc.visible = globalX + frameWidth<=stage.stageWidth && globalY - this.height < 0;
			tooltipFrameUpRight_mc.visible = globalX + frameWidth>stage.stageWidth && globalY - this.height < 0;
			
			var textWidthDifferenceOffset:Number = (toolTip_txt.width - toolTip_txt.textWidth)/2;
			
			toolTip_txt.x = xLeftOffset - textWidthDifferenceOffset;
			toolTip_txt.y = globalY - frameHeight >= 0? topNoArrowOffset : topArrowOffset;
			
			mouse_mc.x = toolTip_txt.x +(toolTip_txt.width + toolTip_txt.textWidth)/2 - mouse_mc.width;
			mouse_mc.y = toolTip_txt.y + toolTip_txt.textHeight;
			
			next_btn.x =  toolTip_txt.x +(toolTip_txt.width - next_btn.GetWidth())/ 2;
			next_btn.y = toolTip_txt.y + toolTip_txt.textHeight + nextBtnOffset;
			
			this.x = (globalX+frameWidth > stage.stageWidth? (globalX - frameWidth+control.width+positionXOffset) : globalX-positionXOffset)+xOffset;
			this.y = (globalY - frameHeight >= 0? globalY - frameHeight+topNoArrowOffset : globalY + control.height-topNoArrowOffset) + yOffset;
			
			if (this.x + frameWidth > stage.stageWidth)
				this.x = stage.stageWidth - frameWidth+xRightOffset/2;
			
			if (this.x < 0)
				x = 0;
				
			currentControlX = globalX;
			currentControlY = globalY;
		}
			
		private function SetDebthPosition():void 
		{	
			var index:int = GetControlParentIndex(control);
			if (debthIndex == index) return;
			
			debthIndex = index;
			this.parent.setChildIndex(this,debthIndex==this.parent.numChildren-1? debthIndex : debthIndex+1);
		}
		
		private function GetControlParentIndex(control:MovieClip):int 
		{
			if (control == null) return -1;
			
			if (control.parent == root)
				return control.parent.getChildIndex(control);
			
			return GetControlParentIndex(control.parent as MovieClip);
		}
		
		private function IsControlVisible(control:MovieClip):Boolean
		{
			if (control == null) return true;
			
			if (!control.visible||control.alpha==0) return false;
			
			return IsControlVisible(control.parent as MovieClip);
		}
		

	}

}