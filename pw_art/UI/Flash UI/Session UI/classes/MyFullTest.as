package  
{
	import Controllers.SoundController;
	import Datas.InvItemDatas;
	import Datas.ShopItemData;
	import Enums.EWindows;
	import Events.FsCommandEvent;
	import fl.controls.Button;
	import flash.display.Sprite;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.text.engine.*;
	import flash.utils.Timer;
	public class MyFullTest extends Sprite
	{
		
		private var _interface:MainInterface;
		private var _main:Main;
		private var buttons:Array = new Array();
		private var _shopItemsCount:int = 0;
		private var _iconsPath:String = 'art/ico/talents/';
		private var _icons:Array = [];
		private var _prime: int;
		private var _inventorySlotsNumber:int = Math.random() * 19;
		private var _shopDatas:Array = new Array();
		private var _inventoryDatas:Array = new Array();
		private	var	_names_arr:Array = new Array();
		private var _guildNames_arr:Array = new Array();
		
		public function MyFullTest(mainInterface:MainInterface, main:Main) 
		{
			_main = main;
			_interface = mainInterface;
			
			_names_arr = ['[Ginas]_Fragnomore', 'patrik2', 'даркДрагон3', 'Warband4', 'Панамка5', 'Greck6', 'Lenin7', 'Тор8', 'папай маряк9', 'Linda10', "newMan11"];
			_guildNames_arr = ['[Abb]', '[WWW]', '[eeeee]', '[12345]', '[12345]', '[12345]', '[12345]', '[12345]', '[12345]', '[12345]', '[12345]', '[12345]', '[12345]', '[12345]'];
			FSCommands.testing = true;
			FSCommands.MyEventDispatcher.addEventListener(FsCommandEvent.EVENT_TYPE, OnFsCommand);
			
			
			//Set error messages
			for (var i:int = 0; i < 10; i++) 
			{
				_interface.SetErrorMessage(i, "Ашыпка №" + i, true, 2);
			}
			
			//set Icons
			_icons = ["01.png", "02.png", "03.png", "04.png", "05.png", "06.png", "07.png", "08.png", "09.png", "10.png", "11.png", "12.png", "13.png", "14.png", "14.png", "15.png", "16.png", "27.png", "30.png", "48.png", "72.png", "74.png"];
			
			GenerateButton("VersionTest", VersionTest);
			GenerateButton("Error MessageTest", ErrorMessageTest);
			GenerateButton("-----------", Empty);
			GenerateButton("Inventory", InventoryFillTest);
			GenerateButton("Shop Open", OpenShopTest);
			GenerateButton("Shop Fill", FillShopTest);
			GenerateButton("-----------", Empty);
			GenerateButton("Shop States", StateShopTest);
			GenerateButton("МАНИ!", AddGoldTest);
			GenerateButton("Пожаловаться", ReportWindowTest);
			GenerateButton("GuildNames", TestGuildNames);
			
 			_shopItemsCount = _icons.length;
			
			for (var j:int = 0; j < _shopItemsCount; j++ )
			{
				var shopDataItem:ShopItemData = new ShopItemData();
				shopDataItem.IconPath = _iconsPath + _icons[j];
				shopDataItem.ItemShopPrice =  int(Math.random() * 450);
				shopDataItem.ShopID = j;
				_shopDatas.push(shopDataItem);
			}
			
			Localization.LocalizationComplete();
		}
		
		private function TestGuildNames():void 
		{
			
		}
		
		private function ReportWindowTest(event:MouseEvent):void 
		{
			_interface.ShowHideWindow(EWindows.WINDOW_REPORT);
		}
		
		private function OnFsCommand(e:FsCommandEvent):void 
		{
			trace("from my tests, опа - " + e.CommandName + " " + e.Args );
			
			if (e.CommandName == FSCommands.SHOPITEM_CLICK)
			OnShopItemBuy(e.Args);
			
			if (e.CommandName == FSCommands.SHOPITEM_TOOLTIP)
			OnShopItemData(e.Args);
			
			if (e.CommandName == FSCommands.INVENTORYITEM_CLICK)
			OnInventoryClick(e.Args);
			
			if (e.CommandName == FSCommands.REPORT_WINDOW_SEND_REPORT)
			OnReportSend();
		}
		
		private function OnReportSend():void 
		{
			trace("Report sent");
		}
		
		private function AddGoldTest(event:MouseEvent):void 
		{
			_prime += 2000;
			UpdateShopItems();
			UpdatePrime(_prime, 0);
		}
		
		private function InventoryFillTest(event:MouseEvent):void 
		{
			_prime = Math.random() * 5000;
						
			UpdatePrime(_prime, 0);
			
			for (var i:int = 0; i < _inventorySlotsNumber; i++) 
			{
				var invDataItem:InvItemDatas = new InvItemDatas();
				var shopData:ShopItemData = _shopDatas[i];
				
				invDataItem.ItemStackCount = 1;
				invDataItem.InvID = shopData.ShopID;
				_inventoryDatas.push(invDataItem);
				
				_interface.SetInventoryItemIcon(invDataItem.InvID, shopData.IconPath);
				_interface.SetInventoryItemState(invDataItem.InvID, 1, 0, 0, 0);
				
			}
			
			_interface.ShowHideWindow(EWindows.WINDOW_INVENTORYBAR);
		}
		
		
		private function Empty(event:MouseEvent):void 
		{
			return;
		}
		
		
		
		private function OnInventoryClick(args:String):void 
		{
			var num:Number = args.indexOf(" ");
			var index:int = int(args.substr(num + 1));
			var invData: InvItemDatas = _inventoryDatas[index];
			
			if (invData.ItemStackCount > 1)
			{
				invData.ItemStackCount--;
				_interface.SetInventoryItemState(index, invData.ItemStackCount, 0, 0, 0);
			}
			
			else
			{
				_interface.SetInventoryItemIcon(index, "");
				invData.InvID = -1;
				invData.ItemStackCount = 0;
			}
			SoundController.PlaySound(SoundController.BUTTON_PRESS_SMALL);
		}
		
		
		private function OnShopItemData(args:String):void ///-- Tooltip
		{
			var num:Number = args.indexOf(" ");
			var index:int = int(args.substr(num + 1));
			var shopData:ShopItemData = _shopDatas[index];
			trace ("ItemPrice", shopData.ItemShopPrice);
		}
		
		
		private function OnShopItemBuy(args:String):void 
		{
			var index:int = int(args);
			var shopData:ShopItemData = _shopDatas[index];
			var isBought:Boolean = false;
			
			for (var i:int = 0; i < _inventoryDatas.length; i++) 
			{
				var invData:InvItemDatas = _inventoryDatas[i];
				
				if (invData.InvID == shopData.ShopID && invData.ItemStackCount<5)
				{
					invData.ItemStackCount++;
					_interface.SetInventoryItemState(i, invData.ItemStackCount, 0, 0, 0);
					isBought = true;
					break;
				}
			}
			
			if (!isBought)
				{
					var freeSlotFound:Boolean = false;
					for (var j:int = 0; j < _inventoryDatas.length; j++) 
					{
						var invData2:InvItemDatas = _inventoryDatas[j];
						if (invData2.InvID == -1)
						{
							invData2.InvID= shopData.ShopID;
							invData2.ItemStackCount = 1;
							freeSlotFound = true;
							_interface.SetInventoryItemIcon(j, shopData.IconPath);
							_interface.SetInventoryItemState(j, invData2.ItemStackCount, 0, 0, 0);
							break;
						}
					}
					
					if (!freeSlotFound)
					{
						var invDataItem:InvItemDatas = new InvItemDatas();
						invDataItem.InvID = shopData.ShopID;
						invDataItem.ItemStackCount = 1;
						_interface.SetInventoryItemIcon(_inventoryDatas.length, shopData.IconPath);
						_interface.SetInventoryItemState(_inventoryDatas.length, invDataItem.ItemStackCount, 0, 0, 0);
						_inventoryDatas.push(invDataItem);
					}
				}
				
			_prime-= shopData.ItemShopPrice;
			UpdatePrime(_prime, 0);
			UpdateShopItems();
		}
		
		
		private function OpenShopTest(event:MouseEvent):void 
		{
			_interface.ShowShop(true);
		}
		
		private function UpdateShopItems():void 
		{
			for (var i:int = 0; i < _shopItemsCount; i++) 
			{
				var shopData:ShopItemData = _shopDatas[i];
				
				if (_prime < shopData.ItemShopPrice)
				{
					_interface.SetShopItemState(i, 1);
				}
				
				if (_prime <= 100) _main.inventoriesBar_mc.prime_txt.textColor = 0xff0000;
			}
		}
		
		private function FillShopTest(event:MouseEvent):void 
		{
			_interface.SetShopItemsCount(_shopItemsCount);
			
			for (var i:int = 0; i < _shopItemsCount; i++) 
			{
				var shopData:ShopItemData = _shopDatas[i];
				
				_interface.SetShopItemIcon(i, shopData.IconPath);
			}
			UpdateShopItems();
		}
		
		
		private function UpdatePrime(prime:int, gold:int):void
		{
			_interface.SetHeroDevelopmentParams(prime, gold);
		}
		
		private function StateShopTest(event:MouseEvent):void 
		{
			for (var j:int = 0; j < _shopItemsCount; j++) 
			{
				_interface.SetShopItemState(j, Math.random() * 2);
			}
		}
		
		
		private function ErrorMessageTest(event:MouseEvent):void 
		{
			var myTimer:Timer = new Timer (1000, 11);
			myTimer.addEventListener(TimerEvent.TIMER, onTimerEvent);
			myTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnTimerComplete);
			myTimer.start();
			var tick:int = 0;
			
			function OnTimerComplete(e:TimerEvent):void 
			{
				_interface.ShowErrorMessage(tick, false);
			}
			function onTimerEvent(e:TimerEvent):void 
			{
				_interface.ShowErrorMessage(tick, true);
				tick++;
			}
		}
			
			
		private function GenerateButton(label:String, testFunction:Function):void 
		{
			var newButton:Button = new Button();
			newButton.label = label;
			
			AddButton (newButton, buttons.length == 0? null:buttons[buttons.length - 1]);
			function AddButton (newButt:Button, oldButt:Button): void
			{
				if (oldButt == null)
				{
					newButt.y = 200;
					newButt.x = 100;
				}
				
				else
				{
					newButt.y = oldButt.y + 30;
					newButt.x = oldButt.x;
				}
				
				if (newButt.y >= 700)
				{
					newButt.x = newButt.x + 100;
					newButt.y = 200;
				}
				
				buttons.push(newButt);
				newButton.width = 200;
				_main.addChild(newButt);
				
			}
			
			newButton.addEventListener(MouseEvent.CLICK, testFunction);
		}
		
		private function VersionTest(event:MouseEvent):void 
		{
			_interface.SetClientVersion("ver.testEugene.0.0.0.1");
			trace("Адмирал Ясенхуй приветствует вас!");
		}
	}

}