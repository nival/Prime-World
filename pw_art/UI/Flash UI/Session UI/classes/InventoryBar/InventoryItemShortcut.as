package InventoryBar
{
	import ActionBar.ActionBarShortcut;
	import ActionBar.ActionBar;
	import Enums.ActionBarSlotState;
	import Interfaces.IActionButton;
	import BaseClasses.BaseShortCut;
	
	public class InventoryItemShortcut extends ActionBarShortcut
	{
		private var item:InventoryButton;
		private var tooltipOn:Boolean = false;
		
		public function InventoryItemShortcut(_item:InventoryButton,actionBar:ActionBar)
		{	
			super(actionBar);
			item = _item;
			State = item.State;
		}

		override public function Press():void 
		{			
			super.Press();
			item.Press();
		}
		
		override public function set InventoryButtonItem(_item:InventoryButton):void
		{
			item = _item;
		}
		
		override public function showTooltip():void
		{
			tooltipOn = true;
			FSCommands.Send(FSCommands.INVENTORYITEMSHORTCUT_TOOLTIP,'1 '+ item.InventoryIndex.toString());
		}
		
		override public function hideTooltip():void
		{
			tooltipOn = false;
			FSCommands.Send(FSCommands.INVENTORYITEMSHORTCUT_TOOLTIP, '0 ' + item.InventoryIndex.toString());
		}

		override public function set actionButton(button:IActionButton)
		{
			super.actionButton = button;

			item.Shortcut = this;
			
			if (_actionButton!=null)
				_actionButton.iconPath = item.iconPath;
		}
		
		override public function get icon():String 
		{
			return item.iconPath;
		}
		
		override public function RemoveFromActionbar():void 
		{ 	
			if (tooltipOn) hideTooltip();
			actionBar.RemoveShortcut(this);
			item.Shortcut = null;
		}
		
		override public function set count(value:int):void 
		{			
			if (_actionButton!=null)
				_actionButton.count = value;
		}
	}
}