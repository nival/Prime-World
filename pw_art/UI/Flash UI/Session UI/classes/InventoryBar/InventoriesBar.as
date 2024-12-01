package InventoryBar
{

	import Components.ScrollableContent;
	import Components.ScrollBar;
	import fl.events.ComponentEvent;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextField;
	import BaseClasses.BaseDragObject;
	import Components.ButtonRound;
	import BaseClasses.BaseShortCut;
	public class InventoriesBar extends BaseDragObject
	{
		private var prime:int;
		private var inventoriesBar_arr:Array;
		
		private var inventoriesButtonsIndexs:Array = new Array(); 
		
		//reference
	//	public var splitButton_mc:ButtonRound;
	//	public var sortButton_mc:ButtonRound;
		
		public var invItem1_mc:InventoryButton;
		public var invItem2_mc:InventoryButton;
		public var invItem3_mc:InventoryButton;
		public var invItem4_mc:InventoryButton;
		public var invItem5_mc:InventoryButton;
		public var invItem6_mc:InventoryButton;
		public var invItem7_mc:InventoryButton;
		public var invItem8_mc:InventoryButton;
		public var invItem9_mc:InventoryButton;
		public var invItem10_mc:InventoryButton;
		public var invItem11_mc:InventoryButton;
		public var invItem12_mc:InventoryButton;
		public var invItem13_mc:InventoryButton;
		public var invItem14_mc:InventoryButton;
		public var invItem15_mc:InventoryButton;
		public var invItem16_mc:InventoryButton;
		public var invItem17_mc:InventoryButton;
		public var invItem18_mc:InventoryButton;
		public var invItem19_mc:InventoryButton;
		public var invItem20_mc:InventoryButton;
		public var invItem21_mc:InventoryButton;
		public var invItem22_mc:InventoryButton;
		public var invItem23_mc:InventoryButton;
		public var invItem24_mc:InventoryButton;
		public var invItem25_mc:InventoryButton;
		public var invItem26_mc:InventoryButton;
		public var invItem27_mc:InventoryButton;
		public var invItem28_mc:InventoryButton;
		public var invItem29_mc:InventoryButton;
		public var invItem30_mc:InventoryButton;
		public var invItem31_mc:InventoryButton;
		public var invItem32_mc:InventoryButton;
		public var scrollBar:ScrollBar;
		public var prime_txt:TextField;
		public var header_txt:TextField;
		public var primeLabel_txt:TextField;
		
		public var __exportedProperties : Array = ['SortButtonTooltip', 'SplitButtonTooltip'];
		
		private var buyToIndex:int = -1;
		private var inventoryScrollableContent:ScrollableContent;
		
		private var columnsCount:int = 4;
		public function InventoriesBar()
		{
			inventoriesBar_arr = [invItem1_mc,invItem2_mc,invItem3_mc,invItem4_mc,invItem5_mc,invItem6_mc,invItem7_mc,invItem8_mc,invItem9_mc,invItem10_mc,invItem11_mc,invItem12_mc,invItem13_mc,invItem14_mc,invItem15_mc,invItem16_mc,invItem17_mc,invItem18_mc,invItem19_mc,invItem20_mc,invItem21_mc,invItem22_mc,invItem23_mc,invItem24_mc,invItem25_mc,invItem26_mc,invItem27_mc,invItem28_mc,invItem29_mc,invItem30_mc,invItem31_mc,invItem32_mc];
			
			for (var i:int = 0; i < inventoriesBar_arr.length; i++)
			{
				inventoriesBar_arr[i].InventoryIndex = i;
				inventoriesBar_arr[i].InventoryBar = this;
				inventoriesButtonsIndexs.push(i);
			}
			
			prime_txt.autoSize = TextFieldAutoSize.LEFT;
			prime_txt.mouseEnabled = false;
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
		}
		
		override public function AddedToStage(e:Event):void 
		{
			super.AddedToStage(e);
			
			var startX:Number = invItem1_mc.x;
			var startY:Number = invItem1_mc.y;
			
			inventoryScrollableContent = new ScrollableContent(inventoriesBar_arr, columnsCount, inventoriesBar_arr.length / columnsCount);
			
			this.addChild(inventoryScrollableContent);
			inventoryScrollableContent.x = startX;
			inventoryScrollableContent.y = startY;
			
			scrollBar.SetScrollableContent(inventoryScrollableContent,false);
			scrollBar.RecalcContentHeight();
		}
		
		private function FillLocalization(e:Event):void
		{
			header_txt.text = Localization.InventoryBar_HeaderText;
			primeLabel_txt.text = Localization.InventoryBar_PrimeCountLabel;
		}
		
		public function GetInventoryItem(index:int):InventoryButton
		{
			if(index>=0 && index<=inventoriesBar_arr.length)
				return inventoriesBar_arr[inventoriesButtonsIndexs[index]];
			return null;
		}
		
		public function GetInventoryItemBySlot(index:int):InventoryButton
		{
			for ( var i:int; i < inventoriesBar_arr.length; i++ )
			{
				var but:InventoryButton = inventoriesBar_arr[i] as InventoryButton;
				if ( but == null )
					continue;
					
				if ( but.InventoryIndex == index )
					return but;
			}
			return null;
		}
		
		public function SetInventoryItemIcon(index:int, path:String):void
		{
			if (index < 0) return;
			
			if (index >= inventoriesBar_arr.length)
			{
				var previousLength:int = inventoriesBar_arr.length;
				inventoryScrollableContent.AddInventoryButtons(index - (inventoriesBar_arr.length-1));
				
				for (var i:int = previousLength; i < inventoriesBar_arr.length; i++) 
				{
					inventoriesBar_arr[i].InventoryIndex = i;
					inventoriesBar_arr[i].InventoryBar = this;
					inventoriesButtonsIndexs.push(i);
				}
				
				scrollBar.RecalcContentHeight();
			}
			
			
			var buyTo:int = buyToIndex;
			var switchingIndex:int = -1;
			var switchingIndexIsChosen:Boolean = false;
			buyToIndex = -1;
				
			if (buyTo == index||path == "")
			{
				inventoriesBar_arr[inventoriesButtonsIndexs[index]].iconPath = path;
				return;
			}
			
			if (buyTo == -1)
			{
				switchingIndex = FindFirstFreeSlot();
				
				SwitchAndSetIconToRightPosition(switchingIndex, index, path);
				return;
			}
			
			if (buyTo != -1 && !inventoriesBar_arr[inventoriesButtonsIndexs[buyTo]].isFreeSlot)
			{
				switchingIndex = FindFirstFreeSlot();
				SwitchAndSetIconToRightPosition(switchingIndex, index, path);
				return;
			}
			
			if (inventoriesBar_arr[inventoriesButtonsIndexs[buyTo]].isFreeSlot && buyTo != -1)
			{
				switchingIndex = buyTo;
				SwitchAndSetIconToRightPosition(switchingIndex, index, path);
				return;
			}	
		}
		
		public function ResetBuyToIndex():void
		{
			buyToIndex = -1;
		}
		
		private function SwitchAndSetIconToRightPosition(switchIndex:int, indexFromLogic:int,path:String):void
		{
			SwitchButtons(inventoriesButtonsIndexs[switchIndex], inventoriesButtonsIndexs[indexFromLogic]);
			for (var i:int = 0; i<inventoriesBar_arr.length; i++)
			{
				inventoriesButtonsIndexs[inventoriesBar_arr[i].InventoryIndex] = i;
			}
			inventoriesBar_arr[inventoriesButtonsIndexs[indexFromLogic]].iconPath = path;
		}
		
		
		private function FindFirstFreeSlot():int
		{
			var index:int = -1;
			
			for (var i:int = 0; i < inventoriesBar_arr.length; i++ )
			{
				if (inventoriesBar_arr[i].isFreeSlot)
				{
					index = inventoriesBar_arr[i].InventoryIndex;
					break
				}
			}			
			return index;
		}
		
		public function SetInventoryItemState(index, count, state, cooldown,maxCooldownValue:Number):void
		{
			if (index<0 || index>inventoriesBar_arr.length) return;
			
			var button:InventoryButton = inventoriesBar_arr[inventoriesButtonsIndexs[index]];
			button.count = count;
			button.State = state;
			button.Cooldown(cooldown,maxCooldownValue);
			
			if (button.Shortcut != null)
			{
				button.Shortcut.Cooldown(cooldown,maxCooldownValue);
				button.Shortcut.State = state;
				button.Shortcut.count = count;
			}
		}

		public function set Prime(_prime:int):void
		{
			if (_prime == prime)
			{
				return;
			}

			prime = _prime;
			prime_txt.text = prime.toString();
		}
		
		public function setGlobalCooldown(cooldown:Number,maxCooldownValue:Number):void {
			for (var i:int = 0; i < inventoriesBar_arr.length; i++)
			{	
				inventoriesBar_arr[i].GlobalCoolDown(cooldown,maxCooldownValue);
			}
		}
		
		public function ResetInventory():void
		{
			for (var i:int = 0; i < inventoriesBar_arr.length; i++)
			{	
				inventoriesBar_arr[i].iconPath = "";
			}
		}
		
		public function PlaceInventoryButtonIntoIndex(newIndex:int, inventoryButton:InventoryButton):void
		{
			var oldIndex:int = 0;
			for (var index:int = 0; index < inventoriesBar_arr.length; index++)
			{
				if (inventoriesBar_arr[inventoriesButtonsIndexs[index]] == inventoryButton)
				{
					oldIndex = index;
					break;
				}
			}
			
			SwitchButtons(inventoriesButtonsIndexs[oldIndex], inventoriesButtonsIndexs[newIndex]);

			for (var i:int = 0; i<inventoriesBar_arr.length; i++)
			{
				inventoriesButtonsIndexs[inventoriesBar_arr[i].InventoryIndex] = i;
			}
		}
		
		private function SwitchButtons(draggedButtonIndex:int,notDraggedButtonIndex:int):void
		{			
			var shortCut:BaseShortCut = inventoriesBar_arr[draggedButtonIndex].Shortcut;
			var icon:String = inventoriesBar_arr[draggedButtonIndex].iconPath;
			var state:int = inventoriesBar_arr[draggedButtonIndex].State;
			var logicalIndex:int = inventoriesBar_arr[draggedButtonIndex].InventoryIndex;
			var count:int = inventoriesBar_arr[draggedButtonIndex].count;
			var isFreeSlot:Boolean = inventoriesBar_arr[draggedButtonIndex].isFreeSlot;
			var cooldown:Number = inventoriesBar_arr[draggedButtonIndex].CooldownValue;
			var maxCooldownValue:Number = inventoriesBar_arr[draggedButtonIndex].MaxCooldownValue;
			
			
			inventoriesBar_arr[draggedButtonIndex].isFreeSlot = inventoriesBar_arr[notDraggedButtonIndex].isFreeSlot;
			inventoriesBar_arr[draggedButtonIndex].State = inventoriesBar_arr[notDraggedButtonIndex].State
			inventoriesBar_arr[draggedButtonIndex].Shortcut = inventoriesBar_arr[notDraggedButtonIndex].Shortcut;
			
			if (inventoriesBar_arr[draggedButtonIndex].Shortcut != null )
				inventoriesBar_arr[draggedButtonIndex].Shortcut.InventoryButtonItem = inventoriesBar_arr[draggedButtonIndex];
				
			inventoriesBar_arr[draggedButtonIndex].InventoryIndex = inventoriesBar_arr[notDraggedButtonIndex].InventoryIndex;
			inventoriesBar_arr[draggedButtonIndex].count = inventoriesBar_arr[notDraggedButtonIndex].count;
			inventoriesBar_arr[draggedButtonIndex].iconPath = inventoriesBar_arr[notDraggedButtonIndex].iconPath;
			inventoriesBar_arr[draggedButtonIndex].CooldownAfterChanging(inventoriesBar_arr[notDraggedButtonIndex].CooldownValue, inventoriesBar_arr[notDraggedButtonIndex].MaxCooldownValue);
		
			
			inventoriesBar_arr[notDraggedButtonIndex].isFreeSlot = isFreeSlot;
			inventoriesBar_arr[notDraggedButtonIndex].State = state;
			inventoriesBar_arr[notDraggedButtonIndex].Shortcut = shortCut;
			
			if (inventoriesBar_arr[notDraggedButtonIndex].Shortcut != null )
				inventoriesBar_arr[notDraggedButtonIndex].Shortcut.InventoryButtonItem = inventoriesBar_arr[notDraggedButtonIndex];
				
			inventoriesBar_arr[notDraggedButtonIndex].InventoryIndex = logicalIndex;
			inventoriesBar_arr[notDraggedButtonIndex].count = count;
			inventoriesBar_arr[notDraggedButtonIndex].iconPath = icon;
			inventoriesBar_arr[notDraggedButtonIndex].CooldownAfterChanging(cooldown,maxCooldownValue);
		}
		
		public function BuyToIndex(index:int):void
		{
			buyToIndex = index;
		}
		
		public function ShowTutorialShopBarItemHighlight(slot:int, show:Boolean):void 
		{
			if (slot<0 || slot>inventoriesBar_arr.length) return;
			
			var button:InventoryButton = inventoriesBar_arr[inventoriesButtonsIndexs[slot]];
			
			if(show)
				button.ShowTutorialHighlight();
			else
				button.HideTutorialHighlight();
		}
	}
}