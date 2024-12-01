package Chat 
{
	import Components.Frame;
	import Components.InputCombobox;
	import Components.PWCombobox;
	import Components.PWCheckBox;
	import Datas.Channel;
	import Datas.ChannelShortcut;
	import Events.ChatBarChannelSelectEvent;
	import Events.PWComponentValueEvent;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;	
	import flash.utils.Dictionary;
	import src.ButtonTooltipEvent;
	import BaseClasses.TooltipSender;
	
	public class ChatInputTextBox extends MovieClip 
	{
		private const MAX_INPUT_CHARS:int = 512;
		
		private var channel:Channel;
		public var text_txt:TextField;
		public var frame:Frame;
		public var combo:PWCombobox;
		public var combo_player:InputCombobox;
		public var knownPlayers:Array;
		public var SendErrorMessageToChat:Function;
		
		private var inputedText:String = "";

		private var channelShortCuts:Array = new Array();
		private var channels:Array = new Array();
		private var players:Array = new Array;
		private var startTextPosition:Number;
		private var textOffset:Number;
		private var startTextWidth:Number;
		private var friendsList:Array = new Array();
		private var isToolTipShowing:Boolean;
		public var chatOutput_cb:PWCheckBox;
		public var chatOutput_cbText:TextField;
		
		private var _restrictedChatSymbols:String;
		private var _filterChatMessagesTooltip:TooltipSender;
		
		public function ChatInputTextBox() 
		{
			this.visible = false;
			combo.ShowScrollBar(false);
			combo_player.visible = false;
			combo_player.addEventListener(PWComponentValueEvent.CHANGE, ChangePlayer)
			
			text_txt.addEventListener(TextEvent.TEXT_INPUT, OnTextInput);
			text_txt.maxChars = MAX_INPUT_CHARS;
			
			startTextPosition = text_txt.x;
			textOffset = startTextPosition - (combo.x + combo.width);
			startTextWidth = text_txt.width;
			
			this.addEventListener(ButtonTooltipEvent.EVENT_TYPE, OnTooltipShowing);
			
			// NOTE: нестандартное расширение
			// PF-91545
			{
				var dynamicTextField:Object = text_txt;
				
				dynamicTextField.userInput = true;
			}
			
			chatOutput_cbText.x = chatOutput_cbText.x - chatOutput_cb.x;
			chatOutput_cbText.y = chatOutput_cbText.y - chatOutput_cb.y;
			chatOutput_cb.addChild(chatOutput_cbText);
			
			_filterChatMessagesTooltip = new TooltipSender(chatOutput_cb);
			chatOutput_cb.addEventListener(PWComponentValueEvent.CHANGE, ChangeChatOff)
		}
		
		private function OnTooltipShowing(e:ButtonTooltipEvent):void 
		{	
			isToolTipShowing = e.action == ButtonTooltipEvent.ACTION_TYPE_IN;
		}

		public function FillLocalization(value:String, restrictedChatSymbols:String, chatOffTooltip:String):void 
		{
			_restrictedChatSymbols = restrictedChatSymbols;
			combo_player.AddComboBoxRow(value);
			combo_player.AddAutoFillRow(value);
			
			_filterChatMessagesTooltip.TooltipText = chatOffTooltip;
		}
		
		public function ChangePlayer(e:PWComponentValueEvent):void 
		{
			if (e.ControlName == "combo_player")
			{
				e.stopPropagation();
				
				combo_player.SelectedIndex = e.componentValue;
			}
		}
		
		public function ChangeChatOff(e:PWComponentValueEvent):void 
		{
			if (e.ControlName == "chatOutput_cb")
			{
				e.stopPropagation();
				
				FSCommands.Send(FSCommands.PREFERENCE_COMPONENT_SET_VALUE, "smartchat_cb " + e.componentValue);
			}
		}
		
		public function SelectInputComboPlayer(name:String):void 
		{
			if (!IsPlayerInCombo(name))
			{
				combo_player.SelectedIndex = 0;
				combo_player.txt.text = name;
				return;
			}
			
			for (var i:int = 0; i < players.length; i++) 
			{
				if (players[i] == name)
				{
					combo_player.SelectedIndex = i;
					return;
				}
			}
			
			combo_player.SelectedIndex = 0;
		}
		
		private function OnTextInput(e:TextEvent):void 
		{
			if (e.text == "\n" || e.text == "\r" || (_restrictedChatSymbols.length != 0 && _restrictedChatSymbols.indexOf(e.text) != -1))
			{
				e.preventDefault();
				return;
			}
			
			var text:String = text_txt.text + e.text;
			
			if (text.charAt(0) != "/" || text.indexOf(" ") == -1)
				return;
				
			for each (var item:ChannelShortcut in channelShortCuts) 
			{
				if (item.Shortcut == text.slice(1, text.indexOf(" ")))
				{
					dispatchEvent(new ChatBarChannelSelectEvent(item.ChannelID));
					e.preventDefault();
					text_txt.text = "";
					stage.focus = text_txt;
					return;
				}
			}
		}
		
		public function SetInputChannel(_channel:Channel):void 
		{
			channel = _channel;
			stage.focus = text_txt;	
			combo.SelectedIndex = channel.ComboBoxIndex;
			text_txt.textColor = channel.ChannelColor;
			
			combo_player.visible = channel.ChannelType == Channel.PrivateChannel;
			text_txt.x = channel.ChannelType != Channel.PrivateChannel? startTextPosition : startTextPosition + combo_player.width + textOffset;
			text_txt.width = channel.ChannelType != Channel.PrivateChannel? startTextWidth : startTextWidth - combo_player.width
		}
		
		public function StartInputText():void
		{
			this.visible = true;
			text_txt.text = "";
			
			if (channel.ChannelType == Channel.PrivateChannel&&combo_player.txt.text == "")
				stage.focus = combo_player.txt;
			else
				stage.focus = text_txt;
		}
		
		private function IsWeKnowPlayer(name:String):Boolean
		{
			for each (var item:String in knownPlayers) 
			{
				if (item == name) 
					return true;
			}
			
			return false;
		}
		
		public function EnterPressed():void 
		{
			if (channel == null) return;
			
			if (isToolTipShowing)
			{
				dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
				isToolTipShowing = false;
			}
			
			
			if (channel.ChannelType == Channel.PrivateChannel && !IsWeKnowPlayer(combo_player.txt.text))
			{
				SendErrorMessageToChat.call();
				
				combo_player.txt.text = "";
				text_txt.text = "";
				combo.CloseDropList();
				combo_player.CloseDropList();
				this.visible = false;
				stage.focus = this.parent;
				return;
			}
			
			FSCommands.Send(FSCommands.CHATBAR_SENDMESSAGE, channel.ChannelId +" " + text_txt.text);
			
			if (channel.ChannelType == Channel.PrivateChannel && !IsPlayerInCombo(combo_player.txt.text))
			{
				AddPlayerToInputCombo(combo_player.txt.text);
			}
			
			text_txt.text = "";
			
			combo.CloseDropList();
			combo_player.CloseDropList();
			this.visible = false;
			stage.focus = this.parent;
		}
		
		
		public function EscPressed():void
		{
			if (isToolTipShowing)
			{
				dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
				isToolTipShowing = false;
			}
			
			text_txt.text = "";
			combo_player.txt.text = "";
			combo.CloseDropList();
			combo_player.CloseDropList();
			this.visible = false;
			stage.focus = this.parent;
		}
		
		public function AddChannel(channel:Channel):void 
		{
			if (channel != null && channel.PlayerCanWriteInTo)
			{
				channel.ComboBoxIndex = combo.AddComboBoxRow(channel.ChannelName);
				combo.SetRowTextColor(channel.ComboBoxIndex, channel.ChannelColor);
			}
			
			if (channel.ChannelType == Channel.PrivateChannel)
			{
				combo_player.ComboBoxColor(channel.ChannelColor);
			}
		}
		
		public function AddChannelShortCut(channel:int, shortcut:String):void 
		{
			var channelShortcut:ChannelShortcut = new ChannelShortcut();
			channelShortcut.ChannelID = channel;
			channelShortcut.Shortcut = shortcut;
			
			channelShortCuts.push(channelShortcut);
		}
		
		private function IsPlayerInCombo(name:String):Boolean
		{
			for each (var item:String in players) 
			{
				if (item == name) return true;
			}
			
			return false;
		}
		
		public function AddPlayerToInputCombo(playerName:String):void
		{
			if (!IsPlayerInCombo(playerName))
			{
				players.push(playerName);
				combo_player.AddComboBoxRow(playerName);
			}
		}
		
		public function AddFriend(friendName:String):void 
		{
			friendsList.push(friendName);
			combo_player.AddAutoFillRow(friendName);
		}
	}

}