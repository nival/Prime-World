package DragAndDrop
{
	import ActionBar.ActionBar;
	import InventoryBar.InventoriesBar
	public interface IDragObject {
		function DragIntoActionBarSlot(index:int, actionBar:ActionBar):void;
		function DragOutSide():void;
		function get CanDragOutside():Boolean;
		function get CanDragIntoActionBar():Boolean;
		function get icon():String;
		function DragIntoInventoryBarSlot(index:int, inventoryBar:InventoriesBar):void
		function get CanDragIntoInventoryBar():Boolean;
		}
	}