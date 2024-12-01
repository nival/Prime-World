package  
{
	import classes.QuestAnimation;
	import Events.QTItemAnimationEnded;
	import fl.transitions.TweenEvent;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	import flash.events.Event;
	
	public class QTItem extends MovieClip 
	{
		public var main_txt:TextField;
		public var label_txt:TextField;
		public var counter_txt:TextField;
		public var qtButton_mc:MovieClip;
		
		public var ID:int = -1;
		
		private var tweenAlpha:Tween;
		private var tweenYPos:Tween;
		private var timeAlpha:int = 10;
		private var time:int = 15;
		
		private var topMargin:int = 4;
		private var bottomMargin:int = 4;

		private var yPos:Number;
		private var btnTweenAlpha:Tween;
		private var tweenShapeHeight:Tween;
		
		private var alphaDuration:Number = 20;
		
		public var current_txt:TextField;
		
		private var _primary:Boolean;
		private var _totalGoals:int = 0;
		private var _currentGoals:int = 0;
		private var _maxCount:int = 0;
		
		public var removeAnim: MovieClip = new MovieClip;
		public var addAnim: MovieClip = new MovieClip;
		
		private var removeTimer:Timer;
		private var removeQuestDuration:Number = 3200;
		
		public function QTItem() 
		{
			counter_txt.autoSize = TextFieldAutoSize.RIGHT;
			
			removeAnim.gotoAndStop(0);
			
			addAnim.gotoAndStop(0);
			
			label_txt.y = topMargin;
			main_txt.y = topMargin;
			
			main_txt.autoSize = TextFieldAutoSize.RIGHT;
			label_txt.autoSize = TextFieldAutoSize.RIGHT;
			
			
			label_txt.mouseEnabled = false;
			counter_txt.mouseEnabled = false;
			
			removeTimer = new Timer(removeQuestDuration, 1);
		//	removeTimer.addEventListener(TimerEvent.TIMER, RemoveTimerIsStarted);
			removeTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnRemoveTimerEnded);
			removeTimer.stop();
			
			tweenAlpha = new Tween(this, 'alpha', Strong.easeOut, 0, 1, timeAlpha);
			tweenAlpha.stop();
			tweenYPos = new Tween(this, 'y', Strong.easeInOut, this.y, this.y, time);
			tweenYPos.stop();
			
			tweenShapeHeight = new Tween(removeAnim, 'height', Strong.easeOut, removeAnim.height, this.height, removeAnim.totalFrames);
			tweenShapeHeight.stop();
			tweenShapeHeight.addEventListener(TweenEvent.MOTION_FINISH, OnShapeAnimFinished);
			
		//	this.addEventListener(MouseEvent.MOUSE_OVER, OnOver);
		//	this.addEventListener(MouseEvent.MOUSE_OUT, OnOut);
			this.addEventListener(MouseEvent.CLICK, OnClick);
			addEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
			
			btnTweenAlpha = new Tween(qtButton_mc, 'alpha', Strong.easeOut, 0, 1, alphaDuration);
			btnTweenAlpha.stop();
			
			alpha = 0;
		}
		
		private function onAddedToStage(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, onAddedToStage);
			removeAnim.gotoAndStop(0);
		}
		
		private function OnShapeAnimFinished(e:TweenEvent):void 
		{
			tweenShapeHeight.stop();
		}
		
		private function OnClick(e:MouseEvent):void 
		{
			FSCommands.Send(FSCommands.QUEST_CLICKED,ID.toString())
		}
		
		private function OnOut(e:MouseEvent):void 
		{
			btnTweenAlpha.stop();
			btnTweenAlpha.continueTo(0, alphaDuration * qtButton_mc.alpha);
			btnTweenAlpha.start();
		}
		
		private function OnOver(e:MouseEvent):void 
		{
			btnTweenAlpha.stop();
			btnTweenAlpha.continueTo(1, alphaDuration * (1 - qtButton_mc.alpha));
			btnTweenAlpha.start();
		}
		
		private function QuestCounter(curentCount:int, maxCount:int):void
		{
			counter_txt.visible = maxCount>0;
			
			counter_txt.text = curentCount + "/" + maxCount;
			
			counter_txt.x = 0;
			counter_txt.y = 0;
			
			if(maxCount>0)
			{
				_maxCount = maxCount;
				counter_txt.x = current_txt.x + current_txt.width - counter_txt.width;
				counter_txt.y = current_txt.y + current_txt.textHeight;
			}
		}
		public function FadeIn():void
		{
			if (alpha == 1)
				return;	
				
			tweenAlpha.begin = 0;
			tweenAlpha.finish = 1;
			tweenAlpha.start();
		}
		public function FadeOut():void
		{
			tweenAlpha.begin = 1;
			tweenAlpha.finish = 0;
			tweenAlpha.start();
		}
				
		public function MoveYPos(newPos:Number):void
		{
			yPos = newPos;
			
			tweenYPos.stop();
			tweenYPos.begin = this.y;
			tweenYPos.finish = newPos;
			tweenYPos.start();
		}
		
		public function SetQuest(primary:Boolean, text:String, totalGoals:int):void
		{
			_primary = primary;
			_totalGoals = totalGoals;
			main_txt.text = "";
			label_txt.text = "";
			current_txt = primary ? main_txt : label_txt;
			
			current_txt.text = text;
			
			QuestCounter(_currentGoals, totalGoals);
			
			var totalHeight = current_txt.y + current_txt.textHeight + bottomMargin
			if (totalGoals > 0)
				totalHeight += counter_txt.textHeight
			
			qtButton_mc.height = totalHeight;
			
			removeAnim.y = current_txt.y + current_txt.height - removeAnim.height;
			addAnim.y = current_txt.y + current_txt.height - removeAnim.height;
		}
		
		public function UpdateQuest(complitedGoals:int):void 
		{
			_currentGoals = complitedGoals;
			QuestCounter(complitedGoals, _totalGoals);
		}
		
		public function UpdateQuestText(text:String):void 
		{
			SetQuest( _primary, text, _totalGoals );
		}
		
		public function get Primary():Boolean
		{
			return _primary;
		}
		
		public function set YPos(pos:Number):void  //используем это из-за того, что у нас при добавлении/удалении элемента может идти твин.
		{
			yPos = pos;
			y = pos
		}
		public function get YPos():Number
		{
			return yPos;
		}
		
		public function get ItemHeight():Number
		{
			return int(Math.ceil(qtButton_mc.height));
		}
		
		public function AddAnim():void
		{
			addAnim.gotoAndPlay(1);
		}
		
		public function StartAnim():void
		{
			removeTimer.start();
			removeAnim.gotoAndPlay(1);
		}
		
		public function RemoveAnimation():void
		{
			removeAnim.gotoAndStop(0);
		}
		
		private function OnRemoveTimerEnded(e:Event):void 
		{
			dispatchEvent(new QTItemAnimationEnded(this));
		}
		
	}
}
