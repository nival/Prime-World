package EscMenu 
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.events.Event;
	
	import Interfaces.IScrollableObject;
	
	public class ShortcutsContainer extends MovieClip implements IScrollableObject
	{
		private var startHeight:Number = 536;
		private var verticalSpace:int = 28;
		private var verticalSpaceHeaderAfter:int = 45;
		private var verticalSpaceHeaderPrev:int = 20;
		private var scrollableHight:Number = 0;
		private var back:Shape;
		private var isInit:Boolean = false;
		
		private var commandNames:Object = new Object();			
		private var itemsMap:Object = new Object();
		
		private var headerActionBar:ShortcutsHeader;
		private var headerGameAction:ShortcutsHeader;
		private var headerSmartChar:ShortcutsHeader;
		private var headerWindows:ShortcutsHeader;
		private var headerCamera:ShortcutsHeader;
		
		public function ShortcutsContainer() 
		{
			startHeight = this.height;
			back = this.getChildAt(0) as Shape;
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, OnLocalizationComplete);
			
			FillLocalization();
		}
		
		private function OnLocalizationComplete(e:Event):void 
		{
			FillLocalization();
			
			if (isInit)
			{
				for (var command:String in itemsMap)
				{
					(itemsMap[command] as ShortcutItem).SetName(commandNames[command]);
				}
			}
		}
		
		private function FillLocalization():void
		{
			commandNames["cmd_action_bar_slot1"] = Localization.ShortcutsMenu_ActionBarSlot1;
			commandNames["cmd_action_bar_slot2"] = Localization.ShortcutsMenu_ActionBarSlot2;
			commandNames["cmd_action_bar_slot3"] = Localization.ShortcutsMenu_ActionBarSlot3;
			commandNames["cmd_action_bar_slot4"] = Localization.ShortcutsMenu_ActionBarSlot4;
			commandNames["cmd_action_bar_slot5"] = Localization.ShortcutsMenu_ActionBarSlot5;
			commandNames["cmd_action_bar_slot6"] = Localization.ShortcutsMenu_ActionBarSlot6;
			commandNames["cmd_action_bar_slot7"] = Localization.ShortcutsMenu_ActionBarSlot7;
			commandNames["cmd_action_bar_slot8"] = Localization.ShortcutsMenu_ActionBarSlot8;
			commandNames["cmd_action_bar_slot9"] = Localization.ShortcutsMenu_ActionBarSlot9;
			commandNames["cmd_action_bar_slot10"] = Localization.ShortcutsMenu_ActionBarSlot10;
			commandNames["self_cast_on"] = Localization.ShortcutsMenu_SelfCast;
			commandNames["cmd_portal"] = Localization.ShortcutsMenu_Portal;
			commandNames["actionbar_lock_off"] = Localization.ShortcutsMenu_ActionBarLockOff;
			
			commandNames["cmd_move"] = Localization.ShortcutsMenu_Move;
			commandNames["cmd_attack"] = Localization.ShortcutsMenu_Attack;
			commandNames["cmd_hold"] = Localization.ShortcutsMenu_Hold;
			commandNames["cs_toggle_healthbars"] = Localization.ShortcutsMenu_ToggleHealthbars;
			
			commandNames["cmd_smart_chat"] = Localization.ShortcutsMenu_OpenSmartChat;
			commandNames["cmd_smart_chat_1"] = Localization.ShortcutsMenu_SmartChat1;
			commandNames["cmd_smart_chat_2"] = Localization.ShortcutsMenu_SmartChat2;
			commandNames["cmd_smart_chat_3"] = Localization.ShortcutsMenu_SmartChat3;
			commandNames["cmd_smart_chat_4"] = Localization.ShortcutsMenu_SmartChat4;
			commandNames["cmd_smart_chat_5"] = Localization.ShortcutsMenu_SmartChat5;
			commandNames["cmd_smart_chat_6"] = Localization.ShortcutsMenu_SmartChat6;
			commandNames["cmd_smart_chat_7"] = Localization.ShortcutsMenu_SmartChat7;
			
			commandNames["chat_open_close"] = Localization.ShortcutsMenu_OpenChat;
			commandNames["chat_open_global"] = Localization.ShortcutsMenu_OpenGlobalChat;
			commandNames["chat_open_team"] = Localization.ShortcutsMenu_OpenTeamChat;
			commandNames["show_statistics"] = Localization.ShortcutsMenu_ShowStatistics;
			commandNames["show_charstat"] = Localization.ShortcutsMenu_ShowCharStats;
			commandNames["show_inventory"] = Localization.ShortcutsMenu_ShowInventory;
			commandNames["show_talents"] = Localization.ShortcutsMenu_ShowTalents;
			
			commandNames["camera_switch_attach_mode_down"] = Localization.ShortcutsMenu_HeroCenter;
			commandNames["camera_forward 1"] = Localization.ShortcutsMenu_CameraUp;
			commandNames["camera_forward -1"] = Localization.ShortcutsMenu_CameraDown;
			commandNames["camera_strafe 1"] = Localization.ShortcutsMenu_CameraRight;
			commandNames["camera_strafe -1"] = Localization.ShortcutsMenu_CameraLeft;
			commandNames["camera_rotate 1"] = Localization.ShortcutsMenu_CameraRotateRight;
			commandNames["camera_rotate -1"] = Localization.ShortcutsMenu_CameraRotateLeft;
			
			if (headerActionBar != null)
			{
				headerActionBar.title.text = Localization.ShortcutsMenu_ActionBarHeader;
			}
			if (headerGameAction != null)
			{
				headerGameAction.title.text = Localization.ShortcutsMenu_GameActionHeader;
			}
			if (headerSmartChar != null)
			{
				headerSmartChar.title.text = Localization.ShortcutsMenu_SmartCharHeader;
			}
			if (headerWindows != null)
			{
				headerWindows.title.text = Localization.ShortcutsMenu_WindowsHeader;
			}
			if (headerCamera != null)
			{
				headerCamera.title.text = Localization.ShortcutsMenu_CameraHeader;
			}
		}
		
		public function Init():void
		{
			if (!isInit)
			{
				isInit = true;
				
				headerActionBar = new ShortcutsHeader();
				headerActionBar.title.text = Localization.ShortcutsMenu_ActionBarHeader;
				headerActionBar.x = 0;
				headerActionBar.y = scrollableHight;			
				addChild(headerActionBar);
				scrollableHight = headerActionBar.y + verticalSpaceHeaderAfter;
				
				CreateBindItem("cmd_action_bar_slot1");
				CreateBindItem("cmd_action_bar_slot2");
				CreateBindItem("cmd_action_bar_slot3");
				CreateBindItem("cmd_action_bar_slot4");
				CreateBindItem("cmd_action_bar_slot5");
				CreateBindItem("cmd_action_bar_slot6");
				CreateBindItem("cmd_action_bar_slot7");
				CreateBindItem("cmd_action_bar_slot8");
				CreateBindItem("cmd_action_bar_slot9");
				CreateBindItem("cmd_action_bar_slot10");
				CreateBindItem("self_cast_on");
				CreateBindItem("cmd_portal");
				CreateBindItem("actionbar_lock_off");
				
				scrollableHight += verticalSpaceHeaderPrev;
				
				headerSmartChar = new ShortcutsHeader();
				headerSmartChar.title.text = Localization.ShortcutsMenu_SmartCharHeader;
				headerSmartChar.x = 0;
				headerSmartChar.y = scrollableHight;			
				addChild(headerSmartChar);
				scrollableHight = headerSmartChar.y + verticalSpaceHeaderAfter;
				
				CreateBindItem("cmd_smart_chat");
				CreateBindItem("cmd_smart_chat_1");
				CreateBindItem("cmd_smart_chat_2");
				CreateBindItem("cmd_smart_chat_3");
				CreateBindItem("cmd_smart_chat_4");
				CreateBindItem("cmd_smart_chat_5");
				CreateBindItem("cmd_smart_chat_6");
				CreateBindItem("cmd_smart_chat_7");
				
				scrollableHight += verticalSpaceHeaderPrev;
				
				headerGameAction = new ShortcutsHeader();
				headerGameAction.title.text = Localization.ShortcutsMenu_GameActionHeader;
				headerGameAction.x = 0;
				headerGameAction.y = scrollableHight;			
				addChild(headerGameAction);
				scrollableHight = headerGameAction.y + verticalSpaceHeaderAfter;
				
				CreateBindItem("cmd_move");
				CreateBindItem("cmd_attack");
				CreateBindItem("cmd_hold");
				CreateBindItem("cs_toggle_healthbars");
				
				scrollableHight += verticalSpaceHeaderPrev;
				
				headerWindows = new ShortcutsHeader();
				headerWindows.title.text = Localization.ShortcutsMenu_WindowsHeader;
				headerWindows.x = 0;
				headerWindows.y = scrollableHight;			
				addChild(headerWindows);
				scrollableHight = headerWindows.y + verticalSpaceHeaderAfter;
				
				CreateBindItem("chat_open_close");
				CreateBindItem("chat_open_global");
				CreateBindItem("chat_open_team");
				CreateBindItem("show_statistics");
				CreateBindItem("show_charstat");
				CreateBindItem("show_inventory");
				CreateBindItem("show_talents");
				
				scrollableHight += verticalSpaceHeaderPrev;
				
				headerCamera = new ShortcutsHeader();
				headerCamera.title.text = Localization.ShortcutsMenu_CameraHeader;
				headerCamera.x = 0;
				headerCamera.y = scrollableHight;			
				addChild(headerCamera);
				scrollableHight = headerCamera.y + verticalSpaceHeaderAfter;
				
				CreateBindItem("camera_switch_attach_mode_down");
				CreateBindItem("camera_forward 1");
				CreateBindItem("camera_forward -1");
				CreateBindItem("camera_strafe -1");
				CreateBindItem("camera_strafe 1");
				CreateBindItem("camera_rotate -1");
				CreateBindItem("camera_rotate 1");
			}
		}
		
		private function CreateBindItem(commandName:String)
		{
			var shortcutItem:ShortcutItem = new ShortcutItem();
			shortcutItem.SetName(commandNames[commandName]);
			shortcutItem.SetBind("");
			shortcutItem.SetContainer(this);
					
			shortcutItem.x = 0;
			shortcutItem.y = scrollableHight;
			
			addChild(shortcutItem);
			itemsMap[commandName] = shortcutItem;
			
			scrollableHight = shortcutItem.y + verticalSpace;
			
			if (back != null)
			{
				scrollableHight < startHeight ? back.height = startHeight : back.height = scrollableHight;
			}
		}
		
		public function FillItem(commandName:String, commandValue:String)
		{
			if (itemsMap.hasOwnProperty(commandName))
			{
				var shortcutItem:ShortcutItem = itemsMap[commandName];
				shortcutItem.SetBind(commandValue);
			}
		}		
		
		public function ResetToDefault():void
		{
			for (var command:String in itemsMap)
			{
				(itemsMap[command] as ShortcutItem).ResetToDefault();
			}
		}
		
		public function ClearFocus():void
		{
			for (var command:String in itemsMap)
			{
				(itemsMap[command] as ShortcutItem).ClearFocus();
			}
		}
		
		public function IsChanged():Boolean
		{
			for (var command:String in itemsMap)
			{
				if ((itemsMap[command] as ShortcutItem).IsChanged())
				{
					return true;
				}
			}
			
			return false;
		}
		
		public function SendRebinds():void
		{
			for (var command:String in itemsMap)
			{
				var item:ShortcutItem = (itemsMap[command] as ShortcutItem);
				if (item.IsChanged())
				{
					var isSmartChat:Boolean = false;
					if (command.search("cmd_smart_chat") != -1)
					{
						isSmartChat = true;
					}
					else
					{
						FSCommands.Send(FSCommands.PREFERENCE_SHORTCUT_REBIND, "bindsection adventure_screen");
					}
					
					FSCommands.Send(FSCommands.PREFERENCE_SHORTCUT_REBIND, "rebind " + command + " " + item.GetRebindString());
					
					if (command == "actionbar_lock_off")
					{
						FSCommands.Send(FSCommands.PREFERENCE_SHORTCUT_REBIND, "rebind !actionbar_lock_on " + item.GetRebindString());
					}
					if (command == "self_cast_on")
					{
						FSCommands.Send(FSCommands.PREFERENCE_SHORTCUT_REBIND, "rebind !self_cast_off " + item.GetRebindString());
					}
					if (command == "show_statistics")
					{
						FSCommands.Send(FSCommands.PREFERENCE_SHORTCUT_REBIND, "rebind !hide_statistics " + item.GetRebindString());
					}
					if (command == "camera_switch_attach_mode_down")
					{
						FSCommands.Send(FSCommands.PREFERENCE_SHORTCUT_REBIND, "rebind !camera_switch_attach_mode_up " + item.GetRebindString());
					}
					
					if (!isSmartChat)
					{
						FSCommands.Send(FSCommands.PREFERENCE_SHORTCUT_REBIND, "bindsection");
					}
				}
			}
		}
		
		public function get TopMargin():Number 
		{
			return 0;
		}
		
		public function get BottomMargin():Number 
		{
			return 0;
		}
		
		public function get ScrollableHeight():Number
		{
			return scrollableHight;
		}
		
		public function get StepSize():Number
		{
			return verticalSpace;
		}
		
		public function get ActualHeight():Number
		{
			return startHeight;
		}		
	}
}