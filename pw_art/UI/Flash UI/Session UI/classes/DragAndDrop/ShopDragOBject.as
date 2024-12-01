package DragAndDrop{
	import ShopBar.ShopBarButton;
	import ActionBar.ActionBar;
	import InventoryBar.InventoriesBar;
	
	public class ShopDragOBject extends Object implements IDragObject {
		
		private var shopItem:ShopBarButton = null;
		
		public function ShopDragOBject(_shopItem:ShopBarButton) 
		{
			shopItem = _shopItem;
		}
		
		public function DragIntoActionBarSlot(index:int, actionBar:ActionBar):void 
		{
			actionBar.BuyItemInSlot(index);
			shopItem.BuyItem();
		}
		
		public function DragIntoInventoryBarSlot(index:int, inventoryBar:InventoriesBar):void
		{
			inventoryBar.BuyToIndex(index);
			shopItem.BuyItem();
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
			return shopItem != null? shopItem.iconPath : "";
		}
		
		public function DragOutSide():void
		{
		}
			
		public function get CanDragOutside():Boolean {
			return false;
		}
	}	
}