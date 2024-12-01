package DragAndDrop
{
	import InventoryBar.InventoryButton;
	import ActionBar.ActionBar;
	import InventoryBar.InventoriesBar;
	import InventoryBar.InventoryItemShortcut;
	
	public class InvenroryDragOBject extends Object implements IDragObject {
		
		private var inventoryItem:InventoryButton = null;
		
		public function InvenroryDragOBject(_inventoryItem:InventoryButton) 
		{
			inventoryItem = _inventoryItem;
		}
		
		public function DragIntoActionBarSlot(index:int, actionBar:ActionBar):void 
		{
			if (inventoryItem.Shortcut != null) 
				actionBar.placeShortCutIntoIndex(index, inventoryItem.Shortcut) 
			else 
				actionBar.placeShortCutIntoIndex(index, new InventoryItemShortcut(inventoryItem,actionBar));
		}
		
		
		public function DragIntoInventoryBarSlot(index:int, inventoryBar:InventoriesBar):void
		{
			inventoryBar.PlaceInventoryButtonIntoIndex(index, inventoryItem);
		}
		
		public function get CanDragIntoActionBar():Boolean 
		{
			return true;
		}
		
		public function get CanDragIntoInventoryBar():Boolean
		{
			return true;
		}
		
		public function get icon():String 
		{
			return inventoryItem != null? inventoryItem.iconPath : "";
		}
		
		public function DragOutSide():void
		{
			inventoryItem.RemoveFromInventoryBar();
		}
			
		public function get CanDragOutside():Boolean {
			return true;
		}
	}	
}