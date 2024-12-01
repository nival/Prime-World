package ActionBar
{
	import Controllers.TextFieldFormater;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;

	
	
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.display.MovieClip;
	
	import src.Desaturate;
	import BaseClasses.BaseBarButton;
	import BaseClasses.BaseShortCut;
	import DragAndDrop.DnDController;
	import DragAndDrop.ActionBarDragOBject;
	
	public class ActionButton extends BaseBarButton 
	{
		private var _actionBar:ActionBar;
		private var _index:int = -1;
		public var textNum:TextField;
		private var _isReserved:Boolean = false;
		private var _isActionBarLocked:Boolean;
		private var isBindSetted:Boolean;
	
		private var formatedBind:TextFieldFormater;
		
		public function ActionButton()
		{
			Shortcut = new BaseShortCut();
			Shortcut.actionButton = this;
			isFreeSlot = true;
			textNum.mouseEnabled = false;
			formatedBind = new TextFieldFormater(textNum);
		}
		
		public function set isReserved (value:Boolean):void
		{
			_isReserved = value;
		}
		
		public function get isReserved():Boolean
		{
			return _isReserved;
		}
		
		public function set ActionBarIndex(value:int):void
		{
			_index = value;
			
			value += 1;
			if (value == 10) 
				value = 0;
			if(!isBindSetted)
				textNum.text = value.toString();
		}
		
		public function get ActionBarIndex():int
		{
			return _index;
		}
		
		
		public function set actionBar(actBar:ActionBar):void
		{
			_actionBar = actBar;
		}
		override protected function onUp(e:MouseEvent):void 
		{	
			super.onUp(e);
		
			if (DnDController.isDragging) 
			{
				DragEndedOverThis();
				return;
			}
			
			Shortcut.Press();
		} 
		
		override protected function onOver(e:MouseEvent):void 
		{	
			super.onOver(e);
			Shortcut.showTooltip();
		}
		
		override protected function onOut(e:MouseEvent):void 
		{	
			super.onOut(e);
			
			Shortcut.hideTooltip();
		}
		
		override protected function onRightClick(e:Event):void
		{
			e.stopPropagation();
			Shortcut.Press();
		}
			
		override protected function StartDragThis():void 
		{
			if ( _isActionBarLocked) return;
			
			DnDController.StartDrag(new ActionBarDragOBject(Shortcut));
		}
		
		override protected function DragEndedOverThis():void 
		{ 	
			if (DnDController.DraggingObject.CanDragIntoActionBar && !_isActionBarLocked)
			{	
				DnDController.DraggingObject.DragIntoActionBarSlot(ActionBarIndex, _actionBar);
			}
			
			DnDController.EndDrag();
		}
		
		override public function set Shortcut(value:BaseShortCut):void 
		{	
			_shortcut = value;
			_shortcut.actionButton = this;
			
			if (_shortcut) _shortcut.count = count;
			isFreeSlot = false;
			isReserved = false;
		}
		
		override public function GlobalCoolDown(value:Number,maxCooldownValue:Number):void 
		{
			if (isFreeSlot) return;
			super.GlobalCoolDown(value,maxCooldownValue);
		}
		
		public function BlockActionBar(lock:Boolean):void 
		{
			_isActionBarLocked = lock;
		}
			
		public function SetBindKey(bindKey:String):void
		{
			isBindSetted = true;
			formatedBind.Text = bindKey;
		}
	}
} 