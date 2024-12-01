package classes.SmartChat
{
	import flash.events.Event;
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.geom.Point;
	import flash.utils.Dictionary;
	
	public class SmartChatGroup extends MovieClip
	{
		private var _id:uint = 0;
		private var _cancel:SmartChatItem = null;
		private var _hitAreas:Vector.<SmartChatItemHitArea> = new Vector.<SmartChatItemHitArea>();
		
		public function SmartChatGroup(id:uint)
		{
			super();
			
			_id = id;
			
			mouseEnabled = false;
			mouseChildren = false;
		}
		
		public function get id():uint
		{
			return _id;
		}
		
		public function AddCategory(id:uint, key:String, name:String):SmartChatItem
		{
			var item:SmartChatItem = new SmartChatCategoryItem();
			
			item.id = id;
			item.key_txt.text = key;
			item.label_txt.text = name;
			
			addChild(item);
			
			return item;
		}
		
		public function AddMessage(id:uint, key:String, text:String):SmartChatItem
		{
			var item:SmartChatItem = new SmartChatMessageItem();
			
			item.id = id;
			item.key_txt.text = key;
			item.label_txt.text = text;
			
			addChild(item);
			
			return item;
		}
		
		public function AddCancel(id:uint, key:String, text:String):SmartChatItem
		{
			if (_cancel != null)
				return _cancel;
				
			var item:SmartChatItem = new SmartChatCancelItem();
		
			item.id = id;
			item.key_txt.text = key;
			item.label_txt.text = text;
			
			addChild(item);
			
			_cancel = item;
			
			return item;
		}
		
		public function UpdateLayout(spacing:int)
		{
			var y:int = 0;
			
			for (var i:uint = 0, count:uint = numChildren; i < count; ++i)
			{
				var child:DisplayObject = getChildAt(i);
				
				if (!(child is SmartChatItem))
					continue;
				
				child.x = 0;
				child.y = y;
				
				y += child.height;
				y += spacing;
			}
		}
		
		public function CreateItemHitAreas():void
		{
			for (var i:uint = 0, count:uint = numChildren; i < count; ++i)
			{
				var child:DisplayObject = getChildAt(i);
				
				if (!(child is SmartChatItem))
					continue;
				
				var item:SmartChatItem = (child as SmartChatItem);
				var itemHitArea:SmartChatItemHitArea = new SmartChatItemHitArea(item);
				
				_hitAreas.push(itemHitArea);
			}
		}
		
		public function AdjustItemHitAreas(dx:Number, dy:Number, viewWidth:Number):void
		{
			for each (var itemHitArea:SmartChatItemHitArea in _hitAreas)
			{
				var item:SmartChatItem = itemHitArea.targetItem;
				
				var p:Point = new Point(0, 0);
				
				p = item.localToGlobal(p);
				p = parent.globalToLocal(p);
				
				itemHitArea.x = dx;
				itemHitArea.y = p.y - dy;
				itemHitArea.width = viewWidth - dx * 2;
				itemHitArea.height = item.textHeight + dy * 2;
			}
		}
		
		public function AddItemHitAreas():void
		{
			if (parent == null)
				return;
			
			for each (var itemHitArea:SmartChatItemHitArea in _hitAreas)
			{				
				parent.addChild(itemHitArea);
			}
		}
		
		public function RemoveItemHitAreas():void
		{
			for each (var itemHitArea:SmartChatItemHitArea in _hitAreas)
			{
				if (itemHitArea.parent != null)
					itemHitArea.parent.removeChild(itemHitArea);
			}
		}
	}

}