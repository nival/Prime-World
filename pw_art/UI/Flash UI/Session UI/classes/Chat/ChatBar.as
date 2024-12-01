package Chat 
{
	import BaseClasses.BaseResizableObject;
	import Components.ButtonSquare;
	import Controllers.SoundController;
	import Datas.Channel;
	import Datas.ChatMessage;
	import Events.ChatBarChannelSelectEvent;
	import Events.ChatBarPlayerSelectEvent;
	import Events.PWComponentValueEvent;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.utils.Dictionary;
	import MainScreen.SetPlayerShortName;
	import Enums.EChatChannel;
	import LoaderSources.LoaderLocalization;
		
	public class ChatBar extends BaseResizableObject 
	{
		public var chatOutput_mc:ChatOutputTextBox;
		public var chatInput_mc:ChatInputTextBox;
		public var up_btn:ButtonSquare;
		public var down_btn:ButtonSquare;
		public var end_btn:ButtonSquare;
		
		private var _index:int;
		private var blink_mc:MovieClip;
		
		private var channels:Array = [];
		
		private var isBlinking:Boolean = false;
		private var friendsList:Array = new Array();
		private var privateChannelId:int=-1;
		private var ignoringPlayers:Array = new Array();
		private var disabledInput: Boolean = false;
		
		public var knownPlayers:Array = new Array();
		public var CantFindPlayer:String = "";
		
		private var _shortheroname:SetPlayerShortName;
		
		private var _playerIcons:Object = new Object();
		
		private var _useLoadingLocalisation:Boolean;
		
		private var ourPlayerId:int;
		private var ourHeroId:int;
		private var playerTeam:Object = new Object();
		private var heroTeam:Object = new Object();
		private var ourIdSetted:Boolean;
		private var delayedMessages:Array = new Array();
		
		public function ChatBar() 
		{
			_shortheroname = new SetPlayerShortName();
			
			blink_mc = new Blink();
			
			up_btn.addEventListener(MouseEvent.MOUSE_UP, ScrollOutputTextUp);
			down_btn.addEventListener(MouseEvent.MOUSE_UP, ScrollOutputTextDown);
			end_btn.addEventListener(MouseEvent.MOUSE_UP, ScrollOutputTextToTheEnd);
			
			if (chatInput_mc != null) {
				chatInput_mc.knownPlayers = knownPlayers;
				chatInput_mc.SendErrorMessageToChat = SendErrorMessageToChat;
			}
			
			end_btn.button_mc.addChild(blink_mc)
			
			blink_mc.stop();
			chatOutput_mc.addEventListener(ChatBarChannelSelectEvent.EVENT_TYPE, ChangeChannel);
			chatOutput_mc.addEventListener(ChatBarPlayerSelectEvent.EVENT_TYPE, ChangePlayer);
			chatInput_mc.addEventListener(ChatBarChannelSelectEvent.EVENT_TYPE, ChangeChannel);
			chatInput_mc.addEventListener(PWComponentValueEvent.CHANGE, InputChannelChangedFromCombo);
			
			chatOutput_mc.IgnoringPlayers = ignoringPlayers;
			ourIdSetted = false;
		}
		
		public function SetUseLoadingLocalisation():void 
		{
			chatOutput_mc.SetUseLoadingLocalisation();
			_useLoadingLocalisation = true;
		}
		
		public function SetPlayerIcon(playerId:int, path:String):void
		{
			if (playerId < 0)
				return;
				
			_playerIcons[playerId] = path;
		}
		
		public function AddChannel(channelID:int, channelName:String, channelColor:uint, showChannelName:Boolean, showPlayerName:Boolean, playerCanWriteInTo:Boolean, channelType:int):void 
		{
			var oldChannel:Channel = GetChannelByID(channelID)
			
			if (channelType == Channel.PrivateChannel)
				privateChannelId = channelID;
			
			if (oldChannel != null)
			{
				oldChannel.ChannelName = channelName;
				oldChannel.ChannelColor = channelColor;
				oldChannel.ShowChannelName = showChannelName;
				oldChannel.ShowPlayerName = showPlayerName;
				oldChannel.PlayerCanWriteInTo = playerCanWriteInTo;
				oldChannel.ChannelType = channelType;
				chatInput_mc.AddChannel(oldChannel);
				return;
			}
			
			var channel:Channel = new Channel();
			channel.ChannelId = channelID
			channel.ChannelName = channelName;
			channel.ChannelColor = channelColor;
			channel.ShowChannelName = showChannelName;
			channel.ShowPlayerName = showPlayerName;
			channel.PlayerCanWriteInTo = playerCanWriteInTo;
			channel.ChannelType = channelType;
			channels.push(channel);
			
			chatInput_mc.AddChannel(channel);
		}
		
		private static function ShouldDisplayMessageIcon(channelId:int, playerId:int):Boolean
		{
			if (playerId < 0)
				return false;
			
			switch (channelId)
			{
			case EChatChannel.MyTeam:
			case EChatChannel.BothTeams:
			case EChatChannel.SmartChat:
				return true;
			default:
				return false;
			}
		}
		
		private function IsPlayerIgnored(playerId:int):Boolean
		{
			if (playerId < 0)
				return false;
			if (ignoringPlayers.indexOf(playerId) < 0)
				return false;
			
			return true;
		}
		
		public function AddMessage(channelID:int, playerName:String, message:String, playerId:int = -1):void 
		{
			// NOTE: сообщения смарт-чата нельзя игнорить
			if (channelID != EChatChannel.SmartChat)
			{
				if (IsPlayerIgnored(playerId))
					return;
			}
			
			var channel:Channel = GetChannelByID(channelID);
			
			if (!IsWeKnowPlayer(playerName) && playerName.length != 0)
			{
				knownPlayers.push(playerName);
			}
			
			if (channel == null)
				return;
				
			if (ShouldDisplayMessageIcon(channelID, playerId))
			{
				if (ourIdSetted)
				{
					var isEnemy:Boolean;
					var isEnemySet:Boolean = false;
					if (_useLoadingLocalisation)
					{
						if (playerTeam.hasOwnProperty(playerId) && heroTeam.hasOwnProperty(ourHeroId))
						{
							isEnemy = playerTeam[playerId] != heroTeam[ourHeroId];
							isEnemySet = true;
						}
					}
					else
					{
						if (playerTeam.hasOwnProperty(playerId) && playerTeam.hasOwnProperty(ourPlayerId))
						{
							isEnemy = playerTeam[playerId] != playerTeam[ourPlayerId];
							isEnemySet = true;
						}
					}
					
					if (isEnemySet)
					{
						chatOutput_mc.AddMessage(channel, playerId, _shortheroname.SetPlayerName(playerName), message, _playerIcons[playerId], isEnemy);
					}
					else
					{
						chatOutput_mc.AddMessage(channel, playerId, _shortheroname.SetPlayerName(playerName), message, _playerIcons[playerId]);
					}
				}
				else
				{
					var newMessage:ChatMessage = new ChatMessage();
			
					newMessage.ChannelData = channel;
					newMessage.PlayerId = playerId;
					newMessage.PlayerName = _shortheroname.SetPlayerName(playerName);
					newMessage.Message = message;
					newMessage.Icon = _playerIcons[playerId];
					
					delayedMessages.push(newMessage);
				}
			}
			else
				chatOutput_mc.AddMessage(channel, playerId, _shortheroname.SetPlayerName(playerName), message);
			
			if (channel.ChannelType == Channel.PrivateChannel && playerName.length != 0)
			{
				chatInput_mc.AddPlayerToInputCombo(playerName);
			}
			
			if (!isBlinking&&chatOutput_mc.CurrentTextPosition!=0)
			{
				blink_mc.visible = true;
				blink_mc.play();
				isBlinking = true;
			}
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
		
		private function ChangePlayer(e:ChatBarPlayerSelectEvent):void 
		{
			chatInput_mc.SelectInputComboPlayer(e.Name);
			
			if (privateChannelId == -1) return;
			
			chatInput_mc.SetInputChannel(GetChannelByID(privateChannelId));
			
		}
		
		
		private function GetChannelByID(channelID:int):Channel
		{
			for (var i:int = 0; i < channels.length; i++)
			{
				if (channels[i].ChannelId == channelID)
				{
					return channels[i];
				}
			}
			
			return null;
		}
		
		private function ScrollOutputTextUp(e:MouseEvent):void 
		{
			chatOutput_mc.ScrollOneStringUp();
			ShowOutput();
		}
		
		private function ScrollOutputTextDown(e:MouseEvent):void 
		{
			chatOutput_mc.ScrollOneStringDown();
			
			ShowOutput();
			
			if (isBlinking&&chatOutput_mc.CurrentTextPosition==0)
			{
				blink_mc.visible = false;
				blink_mc.stop();
				isBlinking = false;
			}
		}
		
		private function ScrollOutputTextToTheEnd(e:MouseEvent):void 
		{
			chatOutput_mc.ScrollToTheEnd();
			ShowOutput();
			
			if (isBlinking&&chatOutput_mc.CurrentTextPosition==0)
			{
				blink_mc.visible = false;
				blink_mc.stop();
				isBlinking = false;
			}
		}
		
		private function ShowOutput():void 
		{
			if (chatInput_mc.visible) return;
			
			chatOutput_mc.ShowOutputBox();
			chatOutput_mc.StartOutputFaidOut();
		}
		
		public function SetDefaultChannel(channelID:int):void 
		{
			chatInput_mc.SetInputChannel(GetChannelByID(channelID));
		}
		
		public function DisableInput(value:Boolean):void
		{
			disabledInput = value;
		}
		
		public function EnterPressed():void 
		{
			if (disabledInput)
				return;
			
			if (chatInput_mc.visible && chatInput_mc.combo_player.AutoFillSelectin())
			{
				chatInput_mc.combo_player.EnterPressed();
				return;
			}
				
			FSCommands.Send(FSCommands.ACTIVATE_CHAT_INPUT, int(!chatInput_mc.visible).toString());
			
			SoundController.PlaySound(SoundController.CHAT_SOUND);
			
			if (chatInput_mc.visible)
			{
				chatInput_mc.EnterPressed();
				chatOutput_mc.StartOutputFaidOut();
				return;
			}
			
			chatInput_mc.StartInputText();
			chatOutput_mc.ShowOutputBox();
		}
		
		public function OpenChannel(channelID:int):void 
		{
			if (disabledInput)
				return;
				
			var channel:Channel = GetChannelByID(channelID)
				
			if (channel == null) return;
				
			if (!chatInput_mc.visible) 
			{
				FSCommands.Send(FSCommands.ACTIVATE_CHAT_INPUT, int(!chatInput_mc.visible).toString());
				SoundController.PlaySound(SoundController.CHAT_SOUND);
				
				chatInput_mc.StartInputText();
				chatOutput_mc.ShowOutputBox();
				
			}
			
			chatInput_mc.SetInputChannel(channel);
		}
		
		
		public function SendErrorMessageToChat():void
		{
			for each (var item:Channel in channels) 
			{
				if (item.ChannelType == Channel.SystemChannel)
				{
					AddMessage(item.ChannelId, "", CantFindPlayer);
					return;
				}
			}
		}
		
		public function EscPressed():void
		{
			FSCommands.Send(FSCommands.ACTIVATE_CHAT_INPUT, int(!chatInput_mc.visible).toString());
			chatInput_mc.EscPressed()
			chatOutput_mc.StartOutputFaidOut();
		}
		
		public function AddChannelShortCut(channel:int, shortcut:String):void 
		{
			chatInput_mc.AddChannelShortCut(channel, shortcut);
		}
		
		public function AddFriend(friendName:String):void 
		{
			for each (var item:String in friendsList) 
			{
				if (item == friendName)
				return;
			}
			
			if (!IsWeKnowPlayer(friendName))
				knownPlayers.push(friendName);
				
			friendsList.push(friendName);
			chatInput_mc.AddFriend(friendName);
		}
		
		public function AddIgnoringUser(playerId:int, playerName:String = ""):void
		{
			var index:int = ignoringPlayers.indexOf(playerId);
			
			if (index < 0)
			{
				ignoringPlayers.push(playerId);
				
				trace("Ignore " + playerId.toString());
				
				if (playerName != "")
				{
					var message = _useLoadingLocalisation ? LoaderLocalization.ChatMessage_Ignore : Localization.ChatMessage_Ignore;
					message = "<style:TT_Chat>" + message.replace('{0}', "<style:TT_Players_Name>" + playerName + "<style:TT_Chat>") + "<style:TT_Chat>";
					AddMessage(EChatChannel.Achievments, "", message);
				}
			}
		}
		
		public function RemoveIgnoringUser(playerId:int, playerName:String = ""):void
		{
			var index:int = ignoringPlayers.indexOf(playerId);
			
			if (index < 0)
				return;
			
			ignoringPlayers.splice(index, 1);
			
			trace("Forgive " + playerId.toString());
			
			if (playerName != "")
			{
				var message = _useLoadingLocalisation ? LoaderLocalization.ChatMessage_RemoveIgnore : Localization.ChatMessage_RemoveIgnore;
				message = "<style:TT_Chat>" + message.replace('{0}', "<style:TT_Players_Name>" + playerName + "<style:TT_Chat>") + "<style:TT_Chat>";
				AddMessage(EChatChannel.Achievments, "", message);
			}
		}
		
		public function ForcedHide():void 
		{
			if (chatInput_mc.visible)
				FSCommands.Send(FSCommands.ACTIVATE_CHAT_INPUT, int(!chatInput_mc.visible).toString());
				chatInput_mc.EscPressed();
				
			chatOutput_mc.ForceHide();
		}

		private function InputChannelChangedFromCombo(e:PWComponentValueEvent):void 
		{
			e.stopPropagation();
			
			for each (var item:Channel in channels) 
			{
				if (item.ComboBoxIndex == e.componentValue)
				{
					chatInput_mc.SetInputChannel(item);
					return;
				}
			}
		}
		
		private function ChangeChannel(e:ChatBarChannelSelectEvent):void 
		{
			e.stopPropagation();
			chatInput_mc.SetInputChannel(GetChannelByID(e.id));
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			this.x = 0;
			this.y = stage.stageHeight - (initialStage.y - startPozition.y) * scale;
		}
		
		public function SetPlayerHeroId(playerId:int, heroId:int, teamId:int):void
		{
			playerTeam[playerId] = teamId;
			heroTeam[heroId] = teamId;
		}
		
		public function SetOurHeroId(heroId:int):void
		{
			ourHeroId = heroId;
			ourIdSetted = true;
		}
		
		public function SetOurPlayerId(playerId:int):void
		{
			ourPlayerId = playerId;
			ourIdSetted = true;
			
			if (delayedMessages.length > 0)
			{
				for each(var message: ChatMessage in delayedMessages)
				{
					var isEnemy:Boolean;
					var isEnemySet:Boolean = false;
					if (_useLoadingLocalisation)
					{
						if (playerTeam.hasOwnProperty(message.PlayerId) && heroTeam.hasOwnProperty(ourHeroId))
						{
							isEnemy = playerTeam[message.PlayerId] != heroTeam[ourHeroId];
							isEnemySet = true;
						}
					}
					else
					{
						if (playerTeam.hasOwnProperty(message.PlayerId) && playerTeam.hasOwnProperty(ourPlayerId))
						{
							isEnemy = playerTeam[message.PlayerId] != playerTeam[ourPlayerId];
							isEnemySet = true;
						}
					}
					
					if (isEnemySet)
					{
						chatOutput_mc.AddMessage(message.ChannelData, message.PlayerId, message.PlayerName, message.Message, message.Icon, isEnemy);
					}
					else
					{
						chatOutput_mc.AddMessage(message.ChannelData, message.PlayerId, message.PlayerName, message.Message, message.Icon);
					}
				}
				delayedMessages.splice(0);
			}
		}
	}

}