package DragAndDrop
{
	import Controllers.SoundController;
	import flash.display.MovieClip;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import Effects.DragOverEffect;
	import Interfaces.IDragSlotHightLight;
	import Components.icoDrag;
	
	public class DnDController extends Object {
		
		private static var isDrag:Boolean;
		private static var myTimer:Timer;
		
		private static var hightLightingObject:IDragSlotHightLight = null;
		private static var dragObject:IDragObject = null;
		private static var iconMov:icoDrag = null;
		private static var draggerEffect:DragOverEffect=new DragOverEffect();	
		
		public static function StartDrag(_dragObject:IDragObject):void
		{	
			
			if (hightLightingObject != null) hightLightingObject.ShowDraggingBorder(true,draggerEffect);
			isDrag = true;
			dragObject = _dragObject;
			if (iconMov == null) return;
			
			iconMov.setIco(_dragObject.icon);
			iconMov.visible = true;
			iconMov.startDrag(true);
			
			SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
		}
				
		public static function set HightLightingObject(value:IDragSlotHightLight):void
		{
			hightLightingObject = value;
			if (isDragging&&hightLightingObject!=null) hightLightingObject.ShowDraggingBorder(true,draggerEffect);
		}
		
		public static function ResetHightLightingObject():void
		{
			if (hightLightingObject != null) hightLightingObject.ShowDraggingBorder(false,draggerEffect);
			hightLightingObject = null;
		}
		
		
		public static function set iconObject(value:icoDrag):void 
		{	
			iconMov = value;
		}
			
		public static function EndDrag():void
		{	
			if(!(dragObject is ShopDragOBject))
				SoundController.PlaySound(SoundController.BUTTON_CANCEL_SMALL);
				
				
			isDrag = false;
			dragObject = null;
			if (iconMov == null) return;
			
			if (hightLightingObject != null) hightLightingObject.ShowDraggingBorder(false, draggerEffect);
			
			iconMov.stopDrag();
			iconMov.visible = false;
		}
		
		
		public static function get isDragging():Boolean 
		{
			return isDrag;
		}
			
		public static  function get DraggingObject():IDragObject 
		{
			return dragObject;
			
		}
	} 
}