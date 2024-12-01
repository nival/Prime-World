package Chat 
{
	import BaseClasses.BaseIconLoader;
	import Datas.ChatMessage;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.events.MouseEvent;
	import fl.motion.easing.Linear;
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.text.TextLineMetrics;
	import flash.utils.Timer;
	import Events.MouseRightEvents;
	import Events.ChatBarPlayerSelectEvent;
	import Events.ChatBarChannelSelectEvent;
	import Events.ChatBarShowPlayerContextMenuEvent;
	
	public class ChatMessageView extends MovieClip 
	{
		private const ELLIPSIS:String = " [...]";
		
		private const FadeDelay:Number = 30000;
		private const FadeTime:Number = 50;
		
		private const STATE_REGULAR:int = 0;
		private const STATE_OVER_PLAYER:int = 1;
		private const STATE_OVER_CHANNEL:int = 2;
		
		private var chatMessage:ChatMessage = null;
		
		private var playerMouseCatcher:ChatBarMouseCatcher = new ChatBarMouseCatcher();
		private var channelMouseCatcher:ChatBarMouseCatcher = new ChatBarMouseCatcher();
		
		private var text:String;
		private var textOverPlayer:String;
		private var textOverChannel:String;
		
		private var lineHeight:Number;
		
		private var fadeOutTween:Tween;
		private var fadeOutTimer:Timer;
		
		private var state:int = STATE_REGULAR;
		
		public var icon:BaseIconLoader;
		public var label:TextField;
		public var enemyBg:MovieClip;
		public var allyBg:MovieClip;
		
		public function ChatMessageView() 
		{
			super();
			
			visible = false;
			
			icon.mouseEnabled = false;
			
			label.mouseEnabled = false;
			label.multiline = true;
			label.wordWrap = true;
			label.autoSize = TextFieldAutoSize.LEFT;
			
			addChildAt(playerMouseCatcher, 0);
			addChildAt(channelMouseCatcher, 0);
			
			lineHeight = label.textHeight;
			
			fadeOutTween = new Tween(this, "alpha", Linear.easeNone, 1, 0, FadeTime);
			fadeOutTween.stop();
			
			fadeOutTimer = new Timer(FadeDelay, 1);
			fadeOutTimer.reset();
			
			function onAddedToStage(e:Event):void
			{
				removeEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
				
				playerMouseCatcher.addEventListener(MouseEvent.CLICK, OnPlayerClick);
				playerMouseCatcher.addEventListener(MouseEvent.MOUSE_OUT, OnCatcherMouseOut);
				playerMouseCatcher.addEventListener(MouseEvent.MOUSE_OVER, OnPlayerMouseOver);
				playerMouseCatcher.addEventListener(MouseRightEvents.RIGHT_CLICK, OnPlayerRightClick);
				
				channelMouseCatcher.addEventListener(MouseEvent.CLICK, OnChannelClick);
				channelMouseCatcher.addEventListener(MouseEvent.MOUSE_OUT, OnCatcherMouseOut);
				channelMouseCatcher.addEventListener(MouseEvent.MOUSE_OVER, OnChannelMouseOver);
				
				fadeOutTween.addEventListener(TweenEvent.MOTION_FINISH, OnFadeOutFinished);
				
				fadeOutTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnTimer);
			}
			
			{
				addEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
			}
			
			// NOTE: нестандартное расширение
			// PF-91545
			{
				var dynamicTextField:Object = label;
				
				dynamicTextField.userInput = true;
			}
		}
		
		public function SetMessage(message:ChatMessage):void
		{
			chatMessage = message;
			
			if (chatMessage == null)
				return;
			
			var channelName:String = "";
			var playerName:String = "";
			var overChannelNameView:String = "";	
			var overPlayerNameView:String = "";
			var textAddition:String = ": ";
			
			if (chatMessage.ChannelData.ShowPlayerName)
			{
				if (chatMessage.ChannelData.ChannelName != null && chatMessage.ChannelData.ChannelName != "")
				{
					playerName = "[" + chatMessage.PlayerName  + "]";
					overPlayerNameView = "[" + chatMessage.PlayerName + "]";
					
					label.text = playerName;
				
					playerMouseCatcher.SetSize(label.textWidth, label.textHeight);
				}
			}
			
			if (chatMessage.ChannelData.ShowChannelName)
			{
				if (chatMessage.ChannelData.ChannelName != null && chatMessage.ChannelData.ChannelName != "")
				{
					channelName = "[" + chatMessage.ChannelData.ChannelName + "]";
					overChannelNameView = "[" + chatMessage.ChannelData.ChannelName + "]";
					
					label.text = channelName;
					
					channelMouseCatcher.SetSize(label.textWidth, label.textHeight);
				}
			}
							
			if (channelName == "" && playerName == "")
				textAddition = "";
			
			text = channelName + playerName + textAddition + chatMessage.Message;
			textOverPlayer = channelName + overPlayerNameView + textAddition + chatMessage.Message;
			textOverChannel = overChannelNameView + playerName + textAddition + chatMessage.Message;
			
			if (chatMessage.Icon != null)
			{
				icon.visible = true;
				icon.SetIcon(chatMessage.Icon);
				if (chatMessage.IsEnemy)
				{
					enemyBg.visible = true;
					allyBg.visible = false;
				}
				else
				{
					enemyBg.visible = false;
					allyBg.visible = true;
				}
			}
			else
			{
				icon.visible = false;
				enemyBg.visible = false;
				allyBg.visible = false;
			}
			
			OnShow();
			UpdateView();
		}
		
		public function Show():void
		{
			if (chatMessage == null)
				return;
				
			OnShow();
			UpdateView();
		}
		
		public function ForceHide():void
		{
			visible = false;
		}
		
		public function FadeOut():void
		{
			fadeOutTimer.start();
		}
		
		public function LayoutSelf():void
		{
			if (chatMessage == null)
				visible = false;
			
			if (visible == false)
				return;
			
			var cx:Number = label.x;
			var cy:Number = label.y;
			
			if (chatMessage.ChannelData.ShowChannelName)
			{
				channelMouseCatcher.visible = true;
				channelMouseCatcher.x = cx;
				channelMouseCatcher.y = cy;
				
				cx += channelMouseCatcher.width;
			}
			else
			{
				channelMouseCatcher.visible = false;
			}
			
			if (chatMessage.ChannelData.ShowPlayerName)
			{
				playerMouseCatcher.visible = true;
				playerMouseCatcher.x = cx;
				playerMouseCatcher.y = cy;
			}
			else
			{
				playerMouseCatcher.visible = false;
			}
		}
		
		private function OnCatcherMouseOut(e:Event):void
		{
			state = STATE_REGULAR;
			UpdateView();
		}
		
		private function OnPlayerClick(e:Event):void
		{
			if (chatMessage == null)
				return;
				
			dispatchEvent(new ChatBarPlayerSelectEvent(chatMessage.PlayerName));
		}
		
		private function OnPlayerRightClick(e:Event):void
		{
			if (chatMessage == null)
				return;
				
			dispatchEvent(new ChatBarShowPlayerContextMenuEvent(chatMessage.PlayerId, chatMessage.PlayerName));
		}
		
		private function OnPlayerMouseOver(e:Event):void
		{
			state = STATE_OVER_PLAYER;
			UpdateView();
		}
		
		private function OnChannelClick(e:Event):void
		{
			if (chatMessage == null)
				return;
			
			dispatchEvent(new ChatBarChannelSelectEvent(chatMessage.ChannelData.ChannelId));
		}
		
		private function OnChannelMouseOver(e:Event):void
		{
			state = STATE_OVER_CHANNEL;
			UpdateView();
		}
		
		private function OnTimer(e:Event):void
		{
			fadeOutTween.start();
		}
		
		private function OnFadeOutFinished(e:Event):void
		{
			ForceHide();
		}
		
		private function UpdateView():void
		{
			var textToShow:String;
			
			switch (state)
			{
				case STATE_REGULAR:
					textToShow = text;
					break;
				case STATE_OVER_PLAYER:
					textToShow = textOverPlayer;
					break;
				case STATE_OVER_CHANNEL:
					textToShow = textOverChannel;
					break;
			}
			
			DoUpdateView(textToShow);
		}
		
		private function DoUpdateView(text:String):void
		{
			label.text = text;
			label.textColor = chatMessage.ChannelData.ChannelColor;
			
			label.height = Math.ceil(Math.max(icon.height, label.textHeight));
			
			var heightLimit:Number = GetHeightLimit();
			
			if (heightLimit > 0)
			{
				if (this.height > heightLimit)
				{
					if (text.length > 1000)
					{
						text = text.substr(0, Math.floor(text.length * 0.9));
					}
					else if (text.length > 500)
					{
						text = text.substr(0, text.length - 50);
					}
					else
					{
						text = text.substr(0, text.length - 10);
					}
					
					DoUpdateView(text + ELLIPSIS);
				}
			}
		}
		
		private function OnShow():void
		{
			fadeOutTimer.reset();
			fadeOutTween.stop();
			
			visible = true;
			alpha = 1;
		}
		
		private function GetHeightLimit():Number
		{
			if (parent is ChatOutputTextBox)
				return (parent as ChatOutputTextBox).MessageViewHeightLimit;
			return 0;
		}
		
		public function get Message():ChatMessage
		{
			return chatMessage;
		}
	}
}