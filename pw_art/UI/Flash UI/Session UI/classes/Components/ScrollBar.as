package Components
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.Shape;
	import flash.geom.Rectangle;
	import src.Desaturate;
	
	import src.WButton;
	import BaseClasses.BaseScrollButton;
	import Interfaces.IScrollableObject;
	
	public class ScrollBar extends MovieClip
	{
		public var scrollUp_btn:WButton;
		public var drag_btn:BaseScrollButton;
		public var scrollDown_btn:WButton;
		public var backFrame_cmp:MovieClip;
		
		private var dragRectangle:Rectangle
		private var scrollableContent:IScrollableObject
		private var maskHeight:Number;
		
		private var dragStep:Number;
		private var dragSize:Number;
		private var dragStart:Number;
		
		private var scrollStep:Number;
		private var scrollableHeight:Number;
		private var scrollableVisibleHeight:Number = 0;
		
		private var startYPosition:Number;				
		public var Enabled:Boolean;
		
		public function ScrollBar()
		{
			this.stop();
			scrollUp_btn.addEventListener(MouseEvent.MOUSE_DOWN, ScrollContentUp);
			scrollUp_btn.addEventListener(MouseEvent.MOUSE_UP, ScrollButtonUp);
			scrollUp_btn.addEventListener(MouseEvent.MOUSE_OUT, ScrollButtonUp);
			
			scrollDown_btn.addEventListener(MouseEvent.MOUSE_DOWN, ScrollContentDown);
			scrollDown_btn.addEventListener(MouseEvent.MOUSE_UP, ScrollButtonUp);
			scrollDown_btn.addEventListener(MouseEvent.MOUSE_OUT, ScrollButtonUp);
			
			drag_btn.addEventListener(MouseEvent.MOUSE_DOWN, DragContent);
			drag_btn.addEventListener(MouseEvent.MOUSE_UP, StopDragContent);
			
			this.addEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
			configUI();
		}
		
		protected function configUI():void
		{
			var r:Number = rotation;
			rotation = 0;
			var w:Number = super.width;
			var h:Number = super.height;
			super.scaleX = super.scaleY = 1;
			
			setSize(w,h);
			rotation = r;
		}
		
		public function setSize(_width:Number, _height:Number)
		{
			backFrame_cmp.setSize( _width, _height);
			scrollUp_btn.y = 1;
			drag_btn.y = scrollUp_btn.y + scrollUp_btn.height;
			scrollDown_btn.y = backFrame_cmp.height - 2;
			
			dragSize = backFrame_cmp.height - scrollUp_btn.y - scrollUp_btn.height - scrollDown_btn.height - 2;
			dragStart = scrollUp_btn.y + scrollUp_btn.height;
			dragRectangle = new Rectangle(backFrame_cmp.x + 1, scrollUp_btn.y + scrollUp_btn.height, 0, dragSize - drag_btn.height);
		}

		public function SetScrollableContent(_scrollableContent:IScrollableObject,isNeedToMove:Boolean=true,isNeedMask:Boolean=true):void
		{
			scrollableContent = _scrollableContent;
			
			if (scrollableContent == null) 
			{
				EnableScrollBar(false)
				return;
			}
			
			EnableScrollBar(scrollableContent.ActualHeight <  scrollableContent.ScrollableHeight);
			if (isNeedToMove)
			{
				var moveOffset:Number = isNeedToMove? this.width : 0;
				this.x = scrollableContent.x + scrollableContent.width - moveOffset - 3;
				this.y = scrollableContent.y;
				setSize(21, scrollableContent.ActualHeight)//ширина скролла всегда одна
			}
						
			startYPosition = scrollableContent.y;
			scrollableVisibleHeight = scrollableContent.ActualHeight;
			
			if (isNeedMask)
			{
				var mask:Shape = new Shape();
				mask.graphics.beginFill(0xFF0000);
				mask.graphics.drawRect(scrollableContent.x- this.x, scrollableContent.TopMargin, scrollableContent.width, scrollableContent.ActualHeight-scrollableContent.BottomMargin);
				this.addChild(mask);
		
				scrollableContent.mask = mask;
			}
			scrollStep = scrollableContent.StepSize;
			
			var dragcontent:MovieClip = _scrollableContent as MovieClip;
			dragcontent.addEventListener(MouseEvent.MOUSE_WHEEL,OnMaskMouseWheeel);
			this.addEventListener(MouseEvent.MOUSE_WHEEL,OnMaskMouseWheeel);
		}
		
		private function EnableScrollBar(enable:Boolean):void
		{
			Enabled = enable;
			
			if (enable) 
			{
				Desaturate.saturate(backFrame_cmp);
				Desaturate.saturate(scrollUp_btn);
				Desaturate.saturate(scrollDown_btn);
			}
			else 
			{
				Desaturate.desaturate(backFrame_cmp);
				Desaturate.desaturate(scrollUp_btn);
				Desaturate.desaturate(scrollDown_btn);
			}
			
			drag_btn.visible = enable;
			scrollUp_btn.Enable = enable;
			scrollDown_btn.Enable = enable;	
		}
		
		private function OnAddedToStage(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, OnAddedToStage);
			stage.addEventListener(MouseEvent.MOUSE_UP, StopDragContent);
			RecalcContentHeight();
		}
		
		private function OnMaskMouseWheeel(e:MouseEvent):void 
		{	
			if (e.delta > 0)
				ScrollUp(null)
			
			if (e.delta < 0)
				ScrollDown(null);
		}
		
		public function RecalcContentHeight(moveToBegin:Boolean = false):void
		{
			if (scrollableContent == null ) return;
		
			if (moveToBegin)
			{
				scrollableContent.y = startYPosition;
			}
			
			scrollableHeight = scrollableContent.ScrollableHeight;
		
			var proportion:Number = dragSize / scrollableHeight;
			drag_btn.setSize(drag_btn.width, proportion * scrollableVisibleHeight);
			
			dragStep = proportion * scrollStep;
			dragRectangle.height = dragSize - drag_btn.height;
			
			EnableScrollBar(scrollableContent.ActualHeight < scrollableContent.ScrollableHeight);
		}
				
		public function ScrollUp(e:Event):void
		{
			if (scrollableContent == null || !Enabled) return;
			
			if (drag_btn.y - dragStep <= dragStart)
			{
				drag_btn.y = dragStart;
				scrollableContent.y = startYPosition;
				return;
			}
			
			drag_btn.y -= dragStep;
			scrollableContent.y += scrollStep;
			CorrectPosition();
		}
				
		public function ScrollDown(e:Event):void
		{
			if (scrollableContent == null || !Enabled) return;
			if (drag_btn.y +drag_btn.height +dragStep >= dragStart + dragSize) 
			{
				drag_btn.y = dragStart + dragSize - drag_btn.height;
				scrollableContent.y = startYPosition+scrollableVisibleHeight-scrollableHeight - 2;
				return;
			}
			
			drag_btn.y += dragStep;
			scrollableContent.y -= scrollStep;
			CorrectPosition();
		}
		
		private function ScrollContentUp(e:MouseEvent):void
		{
			this.addEventListener(Event.ENTER_FRAME, ScrollUp);
		}
		
		private function ScrollContentDown(e:MouseEvent):void
		{
			this.addEventListener(Event.ENTER_FRAME, ScrollDown);
		}

		private function ScrollButtonUp(e:Event):void
		{
			this.removeEventListener(Event.ENTER_FRAME, ScrollUp);
			this.removeEventListener(Event.ENTER_FRAME, ScrollDown);
		}
		
		private function DragContent(e:MouseEvent):void
		{		
			drag_btn.startDrag(false, dragRectangle);
			stage.addEventListener(MouseEvent.MOUSE_MOVE, MoveScrollableObject);
		}		
		private function StopDragContent(e:MouseEvent):void
		{
			drag_btn.stopDrag();
			stage.removeEventListener(MouseEvent.MOUSE_MOVE, MoveScrollableObject);
			CorrectPosition();
		}
		
		private function MoveScrollableObject(e:MouseEvent):void
		{	
			if (scrollableContent == null  ) return;
			scrollableContent.y = startYPosition - (drag_btn.y - dragStart) * (scrollableHeight / dragSize);
		}
		
		private function CorrectPosition():void
		{
			if (scrollableContent == null ) return;
			
			scrollableContent.y = startYPosition - scrollStep * ((startYPosition-scrollableContent.y) / scrollStep);
			
			drag_btn.y = (startYPosition - scrollableContent.y) * (dragSize / scrollableHeight) + dragStart;
		}
		
		public function ResetToStartPosition():void
		{
			if (scrollableContent == null ) return;
			scrollableContent.y = startYPosition;
			drag_btn.y = dragStart;
			this.visible = false;
		}		
		public function ScrollToTheTop():void 
		{
			if (scrollableContent == null ) return;
			scrollableContent.y = startYPosition;
			drag_btn.y = (startYPosition - scrollableContent.y) * (dragSize / scrollableHeight) +dragStart;
		}
	}
}