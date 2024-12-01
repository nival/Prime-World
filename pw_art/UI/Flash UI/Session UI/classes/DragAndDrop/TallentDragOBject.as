package DragAndDrop
{
	import DragAndDrop.IDragObject;
	import ActionBar.ActionBar;
	import InventoryBar.InventoriesBar;
	import TalentBar.Talent;
	import TalentBar.TalentShortCut;
	public class TallentDragOBject extends Object implements IDragObject {
		
		private  var talent:Talent = null;
		
		public function TallentDragOBject(_talent:Talent) {
			
			talent = _talent;
			
			}
		
		public function DragIntoActionBarSlot(index:int, actionBar:ActionBar):void {
			if (talent.shortcut != null) actionBar.placeShortCutIntoIndex(index, talent.shortcut)
			else actionBar.placeShortCutIntoIndex(index, new TalentShortCut(talent,actionBar));
			}
		
		public function DragIntoInventoryBarSlot(index:int, inventoryBar:InventoriesBar):void
		{
			
		}
			
		public function get CanDragIntoActionBar():Boolean 
		{
			return true;
		}
		
		public function get CanDragIntoInventoryBar():Boolean
		{
			return false;
		}	
			
		
		public function get icon():String 
		{
			return talent != null? talent.icon : "";	
		}
		
		public function DragOutSide():void
		{	
			
		}
			
		public function get CanDragOutside():Boolean 
		{
			return false;
		}
	}	
}