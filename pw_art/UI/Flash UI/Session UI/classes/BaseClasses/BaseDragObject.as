package BaseClasses
{
	
	import Components.ButtonToggle;
	import fl.transitions.TweenEvent;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import Components.WFrame;
	import Effects.AnimationBack;
	import Events.WindowVisibleControllerEvent;
	
	public class BaseDragObject extends BaseResizableObject 
	{
		public var header_mc:MovieClip;
		public var closeButton_mc:ButtonToggle;
		protected var wasDragged:Boolean = false;		
		//ref
		
		private var _index:int;
				
		public var windowWidth:Number;
		private var isSticked:Boolean;
		
		private var _closerWindow:BaseDragObject = null;
		public var windowHeight:Number;
		
		public var startDragPosition:int = -1;
		
		public var wframe_mc:WFrame;
		public var myBack_mc:AnimationBack;
		
		public function BaseDragObject() 
		{	
			if (header_mc!=null){
				header_mc.addEventListener(MouseEvent.MOUSE_DOWN,StartDragBaseBarObject);
				header_mc.addEventListener(MouseEvent.MOUSE_UP, StopDragBaseBarObject);
				header_mc.addEventListener(MouseEvent.MOUSE_OVER,OverAnimation);
				header_mc.addEventListener(MouseEvent.MOUSE_OUT, OutAnimation);
				header_mc.addEventListener(MouseEvent.MOUSE_MOVE, MoveOverHeaderAnimation);
			}
			
			if (closeButton_mc != null){
				closeButton_mc.addEventListener("Up", closeThisFunction);
				closeButton_mc.RemoveIntegratedSound();
			}
			this.addEventListener(MouseEvent.MOUSE_OVER,onOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, onOut);
			this.addEventListener(MouseEvent.MOUSE_DOWN, GetThisWindowToTheTop);
			
			windowWidth = myBack_mc.width;
			windowHeight = myBack_mc.height;
		}
		
		private function StopDragging():void
		{
			this.stopDrag();
			this.x = Math.floor(this.x)
			this.y = Math.floor(this.y)
			curPosition.x = this.x;
			curPosition.y = this.y;
			if(this.hasEventListener(MouseEvent.MOUSE_MOVE))
				this.removeEventListener(MouseEvent.MOUSE_MOVE, WindowMovening)
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			windowWidth = myBack_mc.width * scale;
			windowHeight = myBack_mc.height * scale;

			if (_closerWindow == null) return;
			
			var leftWindow:BaseDragObject;
			var rightWindow:BaseDragObject;
			
			if (_closerWindow.x < this.x)
			{
				leftWindow = _closerWindow;
				rightWindow = this;
			}
			else
			{
				leftWindow = this;
				rightWindow = _closerWindow;
			}
			
			if (rightWindow.x >= stage.stageWidth / 2)
			{
				leftWindow.x = rightWindow.x - leftWindow.windowWidth;
				curPosition.x = this.x;
				return;
			}
			
			rightWindow.x = leftWindow.x + leftWindow.windowWidth;
			curPosition.x = this.x;
		}
		
		private function StartDragBaseBarObject(e:MouseEvent):void
		{
			wasDragged = true;
			
			RestartStickDrag(isSticked);
			
			startDragPosition = this.mouseX;
			
		//	this.parent.setChildIndex(this, this.parent.numChildren - 1);
			this.addEventListener(MouseEvent.MOUSE_MOVE,WindowMovening)
			
			if(wframe_mc)
			wframe_mc.onDown();
		}
		
		private function StopDragBaseBarObject(e:MouseEvent):void
		{
			StopDragging();
			if(wframe_mc)
			wframe_mc.onUp();
		}
		private function OverAnimation(e:MouseEvent):void
		{
			if(wframe_mc)
			wframe_mc.onOver();
		}
		private function OutAnimation(e:MouseEvent):void
		{
			StopDragging();	
			if(wframe_mc)
			wframe_mc.onOut();
		}
		private function MoveOverHeaderAnimation(e:MouseEvent):void
		{
			if(wframe_mc)
			wframe_mc.onMove();
		}
		
		protected function closeThisFunction(e:Event):void
		{
			if (e!=null)
				e.stopPropagation();
				
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN_CLOSE,_index));
		}
		
		private function onOver(e:MouseEvent):void
		{
			if(myBack_mc!==null)
				myBack_mc.onOver();
		}
		private function onOut(e:MouseEvent):void
		{
			if(myBack_mc!==null)
				myBack_mc.onOut();
		}
		protected function GetThisWindowToTheTop(e:MouseEvent):void
		{
			this.parent.setChildIndex(this, this.parent.numChildren - 1);
		}
		
		public function set WindowIndex(value:int):void
		{
			_index = value;
		}
		public function get WindowIndex():int
		{
			return _index;
		}
		public function AnimationClosing():void
		{
			tweenThisAlpha.stop();		
			tweenThisAlpha.begin = this.alpha;
			tweenThisAlpha.continueTo(0, 20);
			tweenThisAlpha.addEventListener(TweenEvent.MOTION_STOP, OnAlphaTweenStoped);
		}
		
		private function OnAlphaTweenStoped(e:TweenEvent):void 
		{
			this.visible = false;
			this.alpha = 1;
		}
		public function get CloseButtonTooltip():String
		{
			return closeButton_mc.Tooltip;
		}
		
		public function set CloseButtonTooltip(value:String):void
		{
			closeButton_mc.Tooltip = value;
		}
		
		public function WindowMovening(e:MouseEvent):void
		{
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.WINDOW_MOVING, WindowIndex));
		}
		
		public function RestartStickDrag(isStick:Boolean):void
		{
			if (isStick)
			{
				this.stopDrag();
				this.startDrag(false, new Rectangle(this.x, -wframe_mc.height, 0, stage.stageHeight+wframe_mc.height));
			}
			else
			{
				this.stopDrag();
				this.startDrag();
			}
			
			isSticked = isStick;
		}
		
		public function set isWindowStick(value:Boolean):void
		{
			isSticked = value;
		}
		
		public function get isWindowStick():Boolean
		{
			return isSticked;
		}
		
		public function set StickWindow(window:BaseDragObject):void
		{
			if (window!=null)
				window.UnStickWindow();
				
			if (_closerWindow != null && window == null)
			{
				_closerWindow.UnStickWindow();
			}	
				
			_closerWindow = window;
			
			if (window == null) 
			{
				isWindowStick = false;
				return;
			}
			
			_closerWindow._closerWindow = this;
			_closerWindow.isWindowStick = true;		
		}
		
		public function UnStickWindow():void
		{
			if (_closerWindow!=null)
			{
				_closerWindow.isWindowStick = false;
				_closerWindow._closerWindow = null;
			}
			
			isWindowStick = false;
			_closerWindow = null;
		}
		
		public function SetOnStartPosition():void
		{ 
			var verticalCenter:Number = this.y + this.windowHeight / 2;
			var horizontalCenter:Number = this.x + this.windowWidth / 2;
			
			if (!isAddedToStage) return;
			
			if (verticalCenter<0||verticalCenter>stage.stageHeight||horizontalCenter<0||horizontalCenter>stage.stageWidth)
			{
				this.x = startPozition.x;
				this.y = startPozition.y;
				curPosition.x = this.x;
				curPosition.y = this.y;
			}
		}
	}
}
