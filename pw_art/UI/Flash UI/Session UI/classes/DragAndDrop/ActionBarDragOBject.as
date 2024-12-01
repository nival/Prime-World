package DragAndDrop
{
	import BaseClasses.BaseShortCut;
	import ActionBar.ActionBar;
	import InventoryBar.InventoriesBar;
	
	
	public class ActionBarDragOBject extends Object implements IDragObject {
		
		private  var shortCut:BaseShortCut = null;
		
		public function ActionBarDragOBject(_shortCut:BaseShortCut) 
		{
			shortCut = _shortCut;
		}
		
		public function DragIntoActionBarSlot(index:int, actionBar:ActionBar):void 
		{
			actionBar.placeShortCutIntoIndex(index, shortCut);
		}
			
		public function get CanDragIntoActionBar():Boolean 
		{
			return true;
		}
		
		public function DragIntoInventoryBarSlot(index:int, inventoryBar:InventoriesBar):void
		{
			
		}
		
		public function get CanDragIntoInventoryBar():Boolean 
		{
			return false;
		}
		
		public function get icon():String 
		{
			return shortCut != null? shortCut.icon : "";
		}
		
		public function DragOutSide():void
		{	
			shortCut.RemoveFromActionbar();
		}
			
		public function get CanDragOutside():Boolean 
		{
			return true;
		}
	}	
}