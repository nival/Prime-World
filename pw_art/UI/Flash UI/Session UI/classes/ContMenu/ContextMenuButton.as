package ContMenu 
{
	import BaseClasses.BaseContextItem;
	import Events.WindowVisibleControllerEvent;
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import src.WButton;
	public class ContextMenuButton extends BaseContextMenuButton
	{
		private var contextItem:BaseContextItem;
		public var IsNegative:Boolean;
		public var IsUsing:Boolean;
		
		public function AddContextButtonHandler(contItem:BaseContextItem)
		{
			contextItem = contItem;
			label.text = contextItem.Name;
			IsNegative = contextItem.IsNegativeItem;
			contItem.ForseDispatcher = this;
			IsUsing = true;
		}
		
		override protected function ButtonPressed(e:Event):void 
		{
			e.stopPropagation();
			
			if (contextItem == null) return;
			
			contextItem.Press();
			
			if (contextItem.WindowNeededToBeOpen != -1)
				dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN, contextItem.WindowNeededToBeOpen));
			
			parent.visible = false;
		}
		
		public function get ContextItem():BaseContextItem 
		{
			return contextItem;
		}
	
	}

}