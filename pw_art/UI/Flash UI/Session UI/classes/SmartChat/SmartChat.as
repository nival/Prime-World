package classes.SmartChat
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	
	import BaseClasses.BaseResizableObject;
	
	public class SmartChat extends BaseResizableObject
	{
		private static const marginTop:int = 12;
		private static const marginBottom:int = 12;
		private static const marginLeft:int = 10;
		private static const marginRight:int = 15;
		private static const spacing:int = 4;
		
		private static const itemMarginX:int = 5; // выделение: отступы по горизонтали, от краев фрейма внутрь
		private static const itemMarginY:int = 3; // выделение: отступы по вертикали, от краев итема наружу
		
		private var _groups:Vector.<SmartChatGroup>;
		
		private var _rootGroup:SmartChatGroup;
		private var _currentGroup:SmartChatGroup;
		
		private var _stack:Vector.<SmartChatGroup> = new Vector.<SmartChatGroup>();
		
		public var frame:MovieClip;
		public var selection:MovieClip;
		
		public function SmartChat()
		{
			super();
			
			visible = false;
			
			selection.visible = false;
			selection.mouseEnabled = false;
			
			function onAddedToStage(e:Event):void
			{
				addEventListener(MouseEvent.MOUSE_OVER, OnMouseOver);
				addEventListener(MouseEvent.MOUSE_OUT, OnMouseOut);
				addEventListener(MouseEvent.CLICK, OnMouseClick);
			}
			
			function onRemovedFromStage(e:Event):void
			{
				removeEventListener(MouseEvent.MOUSE_OVER, OnMouseOver);
				removeEventListener(MouseEvent.MOUSE_OUT, OnMouseOut);
				removeEventListener(MouseEvent.CLICK, OnMouseClick);
			}
			
			addEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
			addEventListener(Event.REMOVED_FROM_STAGE, onRemovedFromStage);
		}
		
		public function Show()
		{
			if (visible)
				return;
				
			if (_rootGroup == null)
				return;
				
			FSCommands.Send(FSCommands.SMART_CHAT_ACTIVATE);
				
			ShowGroup(_rootGroup);
				
			visible = true;
			
			root.dispatchEvent(new Event(SmartChatEvent.ACTIVATED));
		}
		
		public function Hide()
		{
			if (!visible)
				return;
				
			visible = false;
			
			ShowGroup(null);
			
			FSCommands.Send(FSCommands.SMART_CHAT_DEACTIVATE);
			
			root.dispatchEvent(new Event(SmartChatEvent.DEACTIVATED));
		}
		
		public function Toggle()
		{
			if (visible)
				Hide();
			else
				Show();
		}
				
		public function ShowCategory(id:uint)
		{
			if (!visible)
				return;
				
			var group:SmartChatGroup = GetGroup(id);
			
			if (group == null)
				return;
			
			ShowGroup(group);
		}
		
		public function BeginUpdate()
		{
			Hide();
			
			_rootGroup = new SmartChatGroup(0);
			_currentGroup = null;
			
			_groups = new Vector.<SmartChatGroup>();
			_groups.push(_rootGroup);
			
			_stack = new Vector.<SmartChatGroup>();
			_stack.push(_rootGroup);
		}
		
		public function EndUpdate()
		{
			if (_stack == null)
				return;
				
			if (_stack.length > 0)
			{
				PopGroup();
				
				if (_stack.length > 0)
					trace("SmartChat: Review update code! Group stack must be empty after update.");
			}
			else
			{
				trace("SmartChat: Review update code! Group stack is already empty.");
			}
			
			_stack = null;
		}
		
		public function BeginCategory(id:uint, key:String, name:String)
		{
			if (_stack == null)
				return;
			
			// TODO: ?
			if (GetGroup(id) != null)
				trace("SmartChat: Category #" + id + " already exists");
			
			var top:SmartChatGroup = GetTopGroup();
			
			if (top == null)
				return;
				
			var group:SmartChatGroup = new SmartChatGroup(id);
			
			_groups.push(group);
			_stack.push(group);
			
			top.AddCategory(id, key, name);
		}
		
		public function EndCategory()
		{
			if (_stack == null)
				return;
				
			if (_stack.length > 1)
			{
				PopGroup();
			}
		}
		
		public function AddMessage(id: uint, key:String, text:String)
		{
			if (_stack == null)
				return;
				
			var top:SmartChatGroup = GetTopGroup();
			
			if (top == null)
				return;
				
			top.AddMessage(id, key, text);
		}
		
		public function AddCancel(id: uint, key:String)
		{
			if (_stack == null)
				return;
				
			var top:SmartChatGroup = GetTopGroup();
			
			if (top == null)
				return;
				
			top.AddCancel(id, key, GetCancelItemText(top));
		}
		
		private function GetTopGroup():SmartChatGroup
		{
			if (_stack == null)
				return null;
			if (_stack.length == 0)
				return null;
				
			return _stack[_stack.length - 1];
		}
		
		private function GetGroup(id:uint):SmartChatGroup
		{
			for each (var group:SmartChatGroup in _groups)
			{
				if (group.id == id)
					return group;
			}
			
			return null;
		}
		
		private function PopGroup():void
		{
			var group:SmartChatGroup = _stack.pop();
			
			group.UpdateLayout(spacing);
			group.CreateItemHitAreas();
		}
		
		private function ShowGroup(group:SmartChatGroup)
		{
			if (_currentGroup == group)
				return;
			
			selection.visible = false;
			
			if (_currentGroup != null)
			{
				_currentGroup.RemoveItemHitAreas();
				
				removeChild(_currentGroup);
			}
			
			_currentGroup = group;
			
			if (_currentGroup != null)
			{
				addChild(_currentGroup);
				
				var viewWidth:Number = _currentGroup.width + marginLeft + marginRight;
				var viewHeight:Number = _currentGroup.height + marginTop + marginBottom;
				
				frame.y = -viewHeight;
				frame.width = viewWidth;
				frame.height = viewHeight;
				
				_currentGroup.x = frame.x + marginLeft;
				_currentGroup.y = frame.y + marginTop;
				
				_currentGroup.AddItemHitAreas();
				_currentGroup.AdjustItemHitAreas(itemMarginX, itemMarginY, viewWidth);
				
				FSCommands.Send(FSCommands.SMART_CHAT_ACTIVATE_CATEGORY, _currentGroup.id.toString());
			}
		}
		
		private function GetCancelItemText(group:SmartChatGroup):String
		{
			// PF-94564
			return Localization.SmartChat_Cancel;
		}
		
		private function OnMouseOver(e:MouseEvent):void
		{
			if (e.target is SmartChatItemHitArea)
			{
				e.stopPropagation();
				
				if (_currentGroup == null)
					return;
				
				var itemHitArea:SmartChatItemHitArea = (e.target as SmartChatItemHitArea);
				
				selection.x = itemHitArea.x;
				selection.y = itemHitArea.y;
				selection.width = itemHitArea.width;
				selection.height = itemHitArea.height;
				selection.visible = true;
			}
		}
		
		private function OnMouseOut(e:MouseEvent):void
		{
			if (e.target is SmartChatItemHitArea)
			{
				e.stopPropagation();
				
				selection.visible = false;
			}
		}
		
		private function OnMouseClick(e:MouseEvent):void
		{
			if (e.target is SmartChatItemHitArea)
			{
				e.stopPropagation();
				
				var itemHitArea:SmartChatItemHitArea = (e.target as SmartChatItemHitArea);
				var item:SmartChatItem = itemHitArea.targetItem;
				
				FSCommands.Send(FSCommands.SMART_CHAT_ITEM_CLICK, item.id.toString());
			}
		}
	}
}
