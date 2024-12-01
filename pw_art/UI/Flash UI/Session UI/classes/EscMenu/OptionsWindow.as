package EscMenu 
{
	import BaseClasses.BaseDragObject;
	import BaseClasses.BaseResizableObject;
	import BaseClasses.TooltipSender;
	import Interfaces.IPWComponents;
	import Components.ButtonStandart;
	import Components.PWCheckBox;
	import Components.PWCombobox;
	import Components.PWSlider;
	import Components.WFrame;
	import Effects.AnimationBack;
	import Events.PWComponentValueEvent;
	import Events.WindowVisibleControllerEvent;
	import fl.controls.Slider;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.utils.Dictionary;
	
	public class OptionsWindow extends BaseDragObject
	{
		public var title:TextField;
		
		//public var downClose_btn:ButtonStandart;
		public var wFrame_mc:WFrame;
		
		public var tab1:ButtonStandart;
		
		public var shortcutsTab:ShortcutsTab;		
		public var settingsTab:OptionsSettingsTab;
		
		private var checkBoxes:Array = [];
		private var comboBoxes:Array = [];
		private var sliders:Array = [];
		
		private var binded:Dictionary = new Dictionary();
	//	private var _index:int = -1;
		private var isApplyPressed:Boolean;
		
		private var _filterChatMessagesTooltip:TooltipSender;
		
		public function OptionsWindow() 
		{
			_filterChatMessagesTooltip = new TooltipSender(settingsTab.smartchat_cb);
			
		//	this.addEventListener(MouseEvent.MOUSE_OUT, OnOut);
		//	this.addEventListener(MouseEvent.MOUSE_OVER, OnOver);
			
			checkBoxes.push(settingsTab.windowed_tb, settingsTab.leftClick_tb, settingsTab.useBadwordsFilter, settingsTab.smartchat_cb);
			comboBoxes.push(settingsTab.resolution, settingsTab.graphic);
			sliders.push(settingsTab.sfx_mc, settingsTab.music_mc, settingsTab.voice_mc);
			
		//	closeButton_mc.addEventListener("Up", CloseThis);
			addEventListener(PWComponentValueEvent.CHANGE, ComponentValueChanged);
			
			settingsTab.apply_btn.addEventListener("Up", ApplyPreferences);
			settingsTab.cansel_btn.addEventListener("Up", CanselPreferences);
			//downClose_btn.addEventListener("Up", closeThisFunction);
			
			settingsTab.warning.visible = false;
			settingsTab.apply_btn.EnableButton = false;
			settingsTab.cansel_btn.EnableButton = false;
			
			settingsTab.common.visible = false;
			settingsTab.common_mc.visible = false;
			
			tab1.addEventListener("Up", Tab1Click);
			
			settingsTab.visible = true;
			shortcutsTab.visible = false;
			shortcutsTab.apply_btn.addEventListener("Up", ApplyShortCutClick);
			shortcutsTab.cancel_btn.addEventListener("Up", CancelShortCutClick);
			
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
		}
		
		private function ApplyShortCutClick(e:Event):void 
		{
			if (shortcutsTab.shortcutContainer.IsChanged())
			{
				shortcutsTab.shortcutContainer.SendRebinds();
				FSCommands.Send(FSCommands.PREFERENCE_SHORTCUTS_APPLY);
			}
			
			settingsTab.visible = true;
			shortcutsTab.visible = false;
			tab1.visible = true;
			title.text = Localization.PreferenceMenu_Header;
			shortcutsTab.shortcutContainer.ClearFocus();
		}
		
		private function CancelShortCutClick(e:Event):void 
		{
			shortcutsTab.shortcutContainer.ResetToDefault();
			
			settingsTab.visible = true;
			shortcutsTab.visible = false;
			tab1.visible = true;
			title.text = Localization.PreferenceMenu_Header;
			shortcutsTab.shortcutContainer.ClearFocus();
		}
		
		private function Tab1Click(e:Event):void 
		{
			title.text = Localization.ShortcutsMenu_Header;
			settingsTab.visible = false;
			tab1.visible = false;
			shortcutsTab.visible = true;
			shortcutsTab.Init();
			shortcutsTab.shortcutContainer.ClearFocus();
		}
		
		override public function AddedToStage(e:Event):void 
		{
			super.AddedToStage(e);		
			
			settingsTab.AddedToStage();
		}
/*
		private function OnOver(e:MouseEvent):void 
		{
			myBack_mc.onOver();
		}
		
		private function OnOut(e:MouseEvent):void 
		{
			myBack_mc.onOut();
		} */
		
		private function FillLocalization(e:Event):void 
		{
			if (settingsTab.visible)
			{
				title.text = Localization.PreferenceMenu_Header;
			}
			else
			{
				title.text = Localization.ShortcutsMenu_Header;
			}
			//downClose_btn.LocalizeText = Localization.PreferenceMenu_CloseBtn;
			
			tab1.LocalizeText = Localization.ShortcutsMenu_Header;
			
			settingsTab.Localize();
			
			_filterChatMessagesTooltip.TooltipText = Localization.Tooltip_PreferenceMenu_ReceiveRegularChatMessages;
		}
		
		private function ApplyPreferences(e:Event):void 
		{
		//	if (warning.visible)
		//		isApplyPressed = true;
			
	
			FSCommands.Send(FSCommands.PREFERENCE_COMPONENT_APPLY);
		}
		
		private function CanselPreferences(e:Event):void 
		{
			FSCommands.Send(FSCommands.PREFERENCE_COMPONENT_CANCEL);
		}
		
	/*	private function CloseThis(e:Event):void 
		{
			e.stopPropagation();
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN_CLOSE,_index));
		}
	*/	
		private function ComponentValueChanged(e:PWComponentValueEvent):void 
		{
			FSCommands.Send(FSCommands.PREFERENCE_COMPONENT_SET_VALUE, e.ControlName + " " + e.componentValue);
			
			if (e.ControlName == "smartchat_cb")
			{
				(this.parent as Main).chatBar.chatInput_mc.chatOutput_cb.Value = e.componentValue;
			}
		}
		
		public function AddCheckBoxControl(controlName:String):void 
		{
			for each (var item:PWCheckBox in checkBoxes)
			{
				if (item.name == controlName)
				{
					binded[controlName] = item;
					return;
				}
			}
		}
		
		public function AddSliderControl(controlName:String, maxCount:int):void 
		{
			for each (var item:PWSlider in sliders)
			{
				if (item.name == controlName)
				{
					binded[controlName] = item;
					item.SetSectionsCount(maxCount);
					return
				}
			}
		}
		
		public function AddComboBoxControl(controlName:String, comboboxValues:Array):void 
		{
			for each (var item:PWCombobox in comboBoxes)
			{
				if (item.name == controlName)
				{
					for (var i:int = 0; i < comboboxValues.length; i++) 
					{
						item.AddComboBoxRow(comboboxValues[i]);
					}
					
					binded[controlName] = item;
					return;
				}
			}
		}
		
		public function SetControlValue(controlName:String, value:int, active:Boolean):void 
		{
			if (binded[controlName] == null)
				return;
			
			var item:IPWComponents = binded[controlName];
			
			item.Value = value;
			item.Disable = !active;
						
			if (controlName == "smartchat_cb")
			{
				(this.parent as Main).chatBar.chatInput_mc.chatOutput_cb.Value = value;
			}
		}
		
		public function ActivateAbilityToChange(activate:Boolean):void 
		{
		//	if(!isApplyPressed)
				//warning.visible = activate;
				
			settingsTab.apply_btn.EnableButton = activate;
			settingsTab.cansel_btn.EnableButton = activate;
		}
	
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			this.x = (stage.stageWidth - this.wFrame_mc.width) / 2;
			this.y = (stage.stageHeight - this.wFrame_mc.height) / 2 - 15; 
		}
		/*
		public function set WindowIndex(value:int):void
		{
			_index = value;
		}
		public function get WindowIndex():int
		{
			return _index;
		}
		*/
	/*	public function set CloseButtonTooltip(value:String):void
		{
			closeButton_mc.Tooltip = value;
		}
		*/
		
		private function OnDownCloseClick(e:Event):void 
		{
			e.stopPropagation();			
			
			FSCommands.Send(FSCommands.PREFERENCE_COMPONENT_CANCEL);
			dispatchEvent(new WindowVisibleControllerEvent(WindowVisibleControllerEvent.OPEN_CLOSE,WindowIndex));
		}
		
		override protected function closeThisFunction(e:Event):void
		{
			CancelShortCutClick(e);
			
			super.closeThisFunction(e);
		}
		
		public function OnCloseByEsc():void
		{
			CancelShortCutClick(null);
		}
		
		override public function SetOnStartPosition():void 
		{
			
		}
		
		override public function ShowCinematicDialog():void
		{
			// remains unaffected by dialog
		}
		
		override public function HideCinematicDialog():void
		{
			// remains unaffected by dialog
		}
	}

}