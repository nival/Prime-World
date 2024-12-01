package Chat 
{
	import Components.Frame;
	import ContMenu.ContextItemIgnore;
	import ContMenu.ContextItemRemoveIgnore;
	import Datas.Channel;
	import Datas.ChatMessage;
	import Events.ChatBarShowPlayerContextMenuEvent;
	import Events.ContextMenuEvent;
	import fl.controls.TextArea;
	import fl.motion.Color;
	import fl.motion.easing.Linear;
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import flash.display.MovieClip;
	import flash.events.TextEvent;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.Timer;
	import LoaderSources.LoaderLocalization;
//	import flash.text.StyleSheet;
	
	public class ChatOutputTextBox extends MovieClip 
	{
		// NOTE: границы должны соответствовать положению маски
		private const marginTop:int = 3;
		private const marginBottom:int = 3;
		
		private var _mv:ChatMessageView = new _ChatMessageView();
		
		public var mv1:ChatMessageView;
		public var mv2:ChatMessageView;
		public var mv3:ChatMessageView;
		public var mv4:ChatMessageView;
		public var mv5:ChatMessageView;
		public var mv6:ChatMessageView;
		public var mv7:ChatMessageView;
		public var mv8:ChatMessageView;
		
		public var frame:Frame;
		public var IgnoringPlayers:Array;
		public var OurName:String;
		public var OurHeroId:int;
	//	private var sheet:StyleSheet = new StyleSheet();
		
		private var messages:Array = [];
		private var messageViews:Array = [];
		private var currentMessagePosition:int = 0;
		
		private var bottomOfOutputText:Number;
		private var backFadeTime:Number = 100;
		private var fadeOutTween:Tween;
		private var isOutputFaiding:Boolean = true;
		
		private var fadeTimer:Timer = new Timer(5000, 1);
		
		private var frameAlpha:Number = 1;//Это из-за того, что дизайнеры захотели изменить альфу фрэйма.
		private var _useLoadingLocalisation:Boolean;
		//я ее запоминаю и подстваляю где используется, для того, чтобы дизайнеры могли подстраивать альфу фрейма на стейдже.
		
		private var _contentHeight:Number = 0;
		private var _contentOffset:Number = 0;
		private var _contentViewHeight:Number = 0;
		
		protected var contextMenuList:Array = [];
		
		public function ChatOutputTextBox() 
		{	
			super();
			
			frame.visible = false;
			frameAlpha = frame.alpha;
			
			this.mouseEnabled = false;
			this.mouseChildren = false;
			
			messageViews = [mv1, mv2, mv3, mv4, mv5, mv6, mv7, mv8];
			
			for (var i:int = 0; i < messageViews.length; i++)
			{
				var channelMouseCatcher:ChatBarMouseCatcher=new ChatBarMouseCatcher();
				this.addChild(channelMouseCatcher)
				
				var playerMouseCatcher:ChatBarMouseCatcher=new ChatBarMouseCatcher();
				this.addChild(playerMouseCatcher)
			}
			
			bottomOfOutputText = Math.ceil(frame.y + frame.height) - marginBottom;
			
			fadeOutTween = new Tween(frame, "alpha", Linear.easeNone, frameAlpha, 0, backFadeTime);
			fadeOutTween.addEventListener(TweenEvent.MOTION_FINISH, OnTweenEnded);
			
			fadeTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnDelayTimerComplete);
			this.addEventListener(ChatBarShowPlayerContextMenuEvent.EVENT_TYPE, OnShowContextMenuClick);
			
			_contentHeight = 0;
			_contentOffset = 0;
			_contentViewHeight = Math.floor(this.ViewHeight);
		}
		
		private function OnShowContextMenuClick(e:ChatBarShowPlayerContextMenuEvent):void 
		{
			contextMenuList = new Array();
			
			var label:String;
			
			if (OurHeroId == e.HeroId)
				return;
				
			if (IgnoringPlayers.indexOf(e.HeroId) < 0)
			{
				label = _useLoadingLocalisation
					? LoaderLocalization.ContextMenu_Ignore
					: Localization.ContextMenu_Ignore;
				
				var ignore:ContextItemIgnore = new ContextItemIgnore(true, label, false, e.HeroId);
				ignore.IsNegativeItem = false;
				contextMenuList.push(ignore);
			}
			else
			{
				label = _useLoadingLocalisation
					? LoaderLocalization.ContextMenu_RemoveIgnore
					: Localization.ContextMenu_RemoveIgnore;
				
				var removeIgnore:ContextItemRemoveIgnore = new ContextItemRemoveIgnore(true, label, false, e.HeroId);
				removeIgnore.IsNegativeItem = false;
				contextMenuList.push(removeIgnore);
			}
			
			dispatchEvent(new ContextMenuEvent(contextMenuList));
		}
				
		public function StartOutputFaidOut():void //старт таймера на анимацию пропадания
		{
			fadeTimer.start();
			isOutputFaiding = true;
			
			this.mouseEnabled = false;
			this.mouseChildren = false;
			
			for each (var item:ChatMessageView in messageViews) 
			{	
				item.FadeOut();
			}
		}
		
				
		public function ForceHide():void 
		{
			frame.visible = false;
			
			this.mouseEnabled = false;
			this.mouseChildren = false;
			
			for each (var item:ChatMessageView in messageViews) 
			{	
				item.ForceHide();
			}
		}
		
		private function OnDelayTimerComplete(e:TimerEvent):void //старт анимации пропадания после таймера
		{
			fadeOutTween.start();
		}
		
		private function OnTweenEnded(e:TweenEvent):void //элемент пропал и стал невидимым.
		{
			frame.visible = false;
		}
		
		public function ShowOutputBox():void
		{
			fadeTimer.stop();
			fadeOutTween.stop();
			frame.visible = true;
			frame.alpha = frameAlpha;
			isOutputFaiding = false;
			this.mouseEnabled = true;
			this.mouseChildren = true;
			
			for each (var item:ChatMessageView in messageViews) 
			{
				item.Show();
			}
			
			LayoutMessageViews();
		}
		
		public function ScrollOneStringDown():void
		{
			if (currentMessagePosition == 0)
				return;
			
			if (_contentOffset <= 0)
				return;
			
			currentMessagePosition--;
			
			SetMessagesFromRegion(currentMessagePosition, currentMessagePosition + messageViews.length);
			
			var view:ChatMessageView = messageViews[0];
			
			_contentOffset -= Math.ceil(view.height);
		}
		
		public function ScrollOneStringUp():void
		{
			if (_contentOffset + _contentViewHeight >= _contentHeight)
				return;
				
			var view:ChatMessageView = messageViews[0];
			
			_contentOffset += Math.ceil(view.height);
			
			currentMessagePosition++;
			
			SetMessagesFromRegion(currentMessagePosition, currentMessagePosition + messageViews.length);
		}
		
		public function ScrollToTheEnd():void
		{
			if (currentMessagePosition == 0)
				return;
				
			currentMessagePosition = 0;
			
			_contentOffset = 0;
			
			SetMessagesFromRegion(currentMessagePosition, currentMessagePosition + messageViews.length);
		}
		
		private function DoAddMessage(message:ChatMessage):ChatMessageView
		{
			var result:ChatMessageView = _mv;
			
			messages.splice(0, 0, message);
			
			_mv.SetMessage(message);
			
			if (currentMessagePosition == 0)
			{
				var messageView:ChatMessageView = messageViews.pop();
				var messageViewIndex:int = messageView.parent.getChildIndex(messageView);
				
				removeChildAt(messageViewIndex);
				addChildAt(_mv, messageViewIndex);
				
				_mv.x = messageView.x;
				_mv.y = messageView.y;
				
				messageViews.splice(0, 0, _mv);
				
				if (isOutputFaiding)
					_mv.FadeOut();
					
				_mv = messageView;
					
				LayoutMessageViews();
			}
			else
			{
				currentMessagePosition++;
			}
			
			return result;
		}
		
		public function AddMessage(channel:Channel, playerId:int, playerName:String, message:String, iconPath:String = null, isEnemy:Boolean = false):void
		{
			var newMessage:ChatMessage = new ChatMessage();
			
			newMessage.ChannelData = channel;
			newMessage.PlayerId = playerId;
			newMessage.PlayerName = playerName;
			newMessage.Message = message;
			newMessage.Icon = iconPath;
			newMessage.IsEnemy = isEnemy;

			var newMessageView:ChatMessageView = DoAddMessage(newMessage);
			var newMessageViewHeight:Number = Math.ceil(newMessageView.height);
			
			_contentHeight += newMessageViewHeight;
			
			if (currentMessagePosition > 0)
				_contentOffset += newMessageViewHeight;
		}
		
		public function SetUseLoadingLocalisation():void 
		{
			_useLoadingLocalisation = true;
		}

		private function LayoutMessageViews():void 
		{
			var bottomTextPosition:Number = bottomOfOutputText;
			
			for (var i:int = 0; i < messageViews.length; i++)
			{		
				var messageView:ChatMessageView = messageViews[i];
				
				if (messageView == null) return;
				
				var viewY:Number = bottomTextPosition - messageView.height;
				
				messageView.y = viewY;
				messageView.visible = !(viewY < marginTop);
				messageView.LayoutSelf();
				
				bottomTextPosition = viewY;
			}
		}
		
		private function SetMessagesFromRegion(startIndex:int, finishIndex:int):void
		{
			var viewIndex:int =  0;
			
			for (var i:int = startIndex; i < finishIndex; i++)
			{		
				var messageView:ChatMessageView = messageViews[viewIndex];
	
				if (messageView == null) return;
			
				messageView.SetMessage(messages[i]);
				
				if (isOutputFaiding)
					messageView.FadeOut();
					
				viewIndex++;
			}
			
			LayoutMessageViews();
		}
		
		public function get CurrentTextPosition():int
		{
			return currentMessagePosition;
		}
		
		public function get ViewHeight():Number
		{
			return frame.height - marginTop - marginBottom;
		}
		
		public function get MessageViewHeightLimit():Number
		{
			return this.ViewHeight;
		}
	}

}