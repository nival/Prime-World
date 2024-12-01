package InventoryBar
{
	
	import Controllers.SoundController;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import BaseClasses.BaseBarButton;
	import Enums.ActionBarSlotState;
	import DragAndDrop.DnDController;
	import Enums.EErrorMessageType;
	import Events.ErrorEvent;
	import DragAndDrop.InvenroryDragOBject;
	
	
	public class InventoryButton extends BaseBarButton 
	{
		private var tooltipOn:Boolean = false;
		private var _index:int = -1;
		public var invNonBound_mc:MovieClip;
		
		private var _inventoryBar:InventoriesBar;
		
		public function InventoryButton()
		{
			super();
			invNonBound_mc.visible = false;
		}
		
		public function set InventoryBar(value:InventoriesBar):void
		{
			_inventoryBar = value;
		}
		
		public function set InventoryIndex(value:int):void
		{
			_index = value;
		}
		
		public function get InventoryIndex():int
		{
			return _index;
		}
		

		public function Press():void
		{
			if (State == ActionBarSlotState.NOT_ENOUGHT_MANA)
			{
				dispatchEvent(new ErrorEvent(EErrorMessageType.ERRORMESSAGETYPE_NOTENOUGHMANAFORABILITY));
				return;
			}
			
			if (cooldown>0)
			{
				dispatchEvent(new ErrorEvent(EErrorMessageType.ERRORMESSAGETYPE_ABILITYONCOOLDOWN));
				return;
			}
			
			if (State == ActionBarSlotState.DISABLED) return;
			
			FSCommands.Send(FSCommands.INVENTORYITEM_CLICK, InventoryIndex.toString());
			SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
		}
		
		override protected function onRightClick(e:Event):void 
		{
			e.stopPropagation();
			Press();
		}
		
		override protected function onUp(e:MouseEvent):void
		{
			super.onUp(e);
			
			if (DnDController.isDragging) 
			{
				DragEndedOverThis();
				return;
			}
			Press();
		}
				
		override protected function onOver(e:MouseEvent):void
		{
			super.onOver(e);
			if (super.iconPath == null || super.iconPath.length == 0) return;
			FSCommands.Send(FSCommands.INVENTORYITEM_TOOLTIP, '1 ' + InventoryIndex.toString());
			tooltipOn = true;
		}
		
		override protected function onOut(e:MouseEvent):void
		{
			super.onOut(e);
		
			if (super.iconPath == null || super.iconPath.length == 0) return;
			FSCommands.Send(FSCommands.INVENTORYITEM_TOOLTIP, '0 ' + InventoryIndex.toString());
			tooltipOn = false;
		}
		
		override protected function DragEndedOverThis():void 
		{
			if (DnDController.DraggingObject.CanDragIntoInventoryBar)
			{	
				DnDController.DraggingObject.DragIntoInventoryBarSlot(InventoryIndex, _inventoryBar);
			}
			
			DnDController.EndDrag();
		}
		
		override protected function StartDragThis():void 
		{
			DnDController.StartDrag(new InvenroryDragOBject(this)); 
		}
		
		override public function set iconPath( _path : String ):void
		{
			
			super.iconPath = _path;
			
			isFreeSlot = false;
			
			if (_path == null || _path.length == 0)
			{	
				downState();
				
				State = ActionBarSlotState.DISABLED;
			
				if (tooltipOn) FSCommands.Send(FSCommands.INVENTORYITEM_TOOLTIP, '0 ' + InventoryIndex.toString());
			
				//remove shortcut
				if (Shortcut != null)
				{
					Shortcut.RemoveFromActionbar();
				}
				
				count = 0;
				CooldownAfterChanging(0, 0);
				isActiveGlobalCooldown = false;
				isFreeSlot = true;
			}
			
		}
		
		public function CooldownAfterChanging(_cooldown:Number,_maxCooldown:Number):void
		{
			if (_cooldown <= 0)
			{
					cooldown = 0;
					coolDown_mc.gotoAndStop(1);
					coolDown_mc.visible = false;
					return;
			}
			
			Cooldown(_cooldown,_maxCooldown);
		}
	
		public override function GlobalCoolDown (_cooldown:Number,maxCooldownValue:Number):void
		{
			if (count>0)
				super.GlobalCoolDown(_cooldown,maxCooldownValue);
		}
		
		public override function set count(value:int):void
		{
			super.count = value;
			
			if (Shortcut != null)
				Shortcut.count = value;
		}
		
		public function RemoveFromInventoryBar():void 
		{
			FSCommands.Send(FSCommands.DROP_ITEM_OUTSIDE, InventoryIndex.toString());			
		}
		
		override public function get width():Number 
		{
			return toggleButton_mc.width;
		}
		
		override public function get height():Number 
		{
			return toggleButton_mc.height;
		}
	}
	
}
