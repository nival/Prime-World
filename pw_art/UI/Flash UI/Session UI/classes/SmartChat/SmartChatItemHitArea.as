package classes.SmartChat
{
	import flash.display.Shape;
	import flash.display.Sprite;
	
	public class SmartChatItemHitArea extends Sprite
	{
		private var _targetItem:SmartChatItem;
		private var collider:Shape;
		
		public function SmartChatItemHitArea(item:SmartChatItem)
		{
			_targetItem = item;
			
			collider = new Shape();
			
			collider.graphics.beginFill(0x000000, 0); // transparent black
			collider.graphics.drawRect(0, 0, 10, 10);
			collider.graphics.endFill();
			
			addChild(collider);
			
			mouseChildren = false;
		}
		
		public function get targetItem():SmartChatItem
		{
			return _targetItem;
		}
	}	
}