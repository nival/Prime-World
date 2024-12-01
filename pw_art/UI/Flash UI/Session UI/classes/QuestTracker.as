package  
{
	
	import BaseClasses.BaseResizableObject;
	import Events.QTItemAnimationEnded;
	import fl.accessibility.TileListAccImpl;
	import fl.motion.easing.Quintic;
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.text.TextField;
	import flash.text.TextFieldAutoSize;
	import Components.Frame;
	import flash.events.Event;
	import flash.utils.Timer;
	
	import fl.transitions.Tween;
	import fl.transitions.TweenEvent;
	import fl.transitions.easing.Strong;
		
	public class QuestTracker extends BaseResizableObject 
	{
		public var qtFrame_cmp:MovieClip;

		private var topMargins:int = 12;//отступ сверху из-за рамки.
		private var leftMargin:int = 0;//отступ слева из-за рамки.
		private var bottomMargin:int = 12;//задел рамки из-за закругленности.
		//private var frameBorder:int = 12;
		
		private var qtFrameHeightTween:Tween;//твин для рамки.
		private var frameHeight:Number = -1;//кастомноанимируемый параметр высоты рамки, поскольку ее высота задается отдельным методом.
		private var time = 15;//время анимации
		
		private var qtRemoved:QTItem;//удаляемый элемент квеста.
		private var removedID:int = -1;//ID удаляемого элемента квеста.
			
		private var quests:Array = new Array();
		private var removingQuests:Array = new Array();
		private var backAlphaFadeTime:Number = 100;
		private var fadeTimeOutDuration:Number = 2000;
		//private var qtFrameAlphaTween:Tween;
		private var timeOutTimer:Timer;
		
		public function QuestTracker()
		{
			this.visible = false;
			this.mouseEnabled = false;
			this.mouseChildren = false;
			
			frameHeight = qtFrame_cmp.height;
			qtFrame_cmp.mouseEnabled = false;
			qtFrameHeightTween = new Tween(qtFrame_cmp, 'height', Strong.easeInOut, qtFrame_cmp.height, qtFrame_cmp.height, time);
			qtFrameHeightTween.addEventListener(TweenEvent.MOTION_FINISH,OnFrameHeightChangeFinish)
			qtFrameHeightTween.stop();
			
		//	qtFrameAlphaTween = new Tween(qtFrame_cmp, "alpha", Strong.easeOut, 1, 0, backAlphaFadeTime);
			qtFrameHeightTween.stop();
			
			timeOutTimer = new Timer(fadeTimeOutDuration, 1);
			timeOutTimer.stop();
			timeOutTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnTimerEnded);
			
			this.addEventListener("OnFadeFinish", OnFadeOutFinish);
			this.addEventListener(MouseEvent.MOUSE_OVER, OnMouseOver);
			this.addEventListener(MouseEvent.MOUSE_OUT, OnMouseOut);
			
			this.addEventListener(QTItemAnimationEnded.EVENT_TYPE, OnAnimationEnded);
		}		
		
		private function OnTimerEnded(e:TimerEvent):void 
		{
			
		}
		
		private function OnMouseOut(e:MouseEvent):void 
		{
			timeOutTimer.start();
		}
		
		private function OnMouseOver(e:MouseEvent):void 
		{
			//qtFrameAlphaTween.stop();
			timeOutTimer.stop();
			qtFrame_cmp.alpha = 1;
		}
		
		private function OnFadeOutFinish(e:Event):void 
		{
			RescaleBackHeight(false);
		}
		
		private function OnFrameHeightChangeFinish(e:TweenEvent):void 
		{
			for each (var item:QTItem in quests) 
			{
				item.FadeIn();
			}
			
			for each (var removingItem:QTItem in removingQuests) 
			{
				if (removingItem.alpha == 0)
				{
					this.removeChild(removingItem);
					removingItem == null;
				}
			}
			
			removingQuests = new Array();
			
			this.visible = quests.length != 0;
		}
		
		private function ResetBackFadeOut():void
		{
		//	qtFrameAlphaTween.stop();
			timeOutTimer.stop();
			qtFrame_cmp.alpha = 1;
		}
		
		public function AddQuest(questId:int, primary:Boolean, text:String, totalGoals:int):void 
		{
			if (GetQuestItemIndexById(questId) != -1)
				return;
			
			this.visible = true;
			
			ResetBackFadeOut();
			timeOutTimer.start();
			
			var questItem:QTItem = new QTItem();
			questItem.ID = questId;
			questItem.SetQuest(primary, text, totalGoals);
			questItem.x = leftMargin;
			
			var position:int = GetNewElementStackPosition(primary);
			
			SetAndSortElementsYPosition(questItem, position);
			
			quests.splice(position, 0, questItem);
			addChild(questItem);
			
			RescaleBackHeight(true);
			questItem.AddAnim();
		//	questItem.FadeIn();
		}
		
		private function GetNewFrameHeight():Number
		{
			var totalHeight:Number = 0;

			if (quests.length == 0)
			{
				totalHeight = 20 + 2 // минимум: двойной радиус закругления + еще чуть-чуть, иначе появляются артефакты
			}
			else
			{
				for (var i:int = 0; i < quests.length; i++) 
				{
					totalHeight += quests[i].ItemHeight
	 			}
				
				totalHeight += topMargins
				totalHeight += bottomMargin
			}

			return int(Math.ceil(totalHeight));
		}
		
		private function SetAndSortElementsYPosition(questItem:QTItem, stackPosition:int):void
		{
			if (stackPosition == 0 && quests.length==0)
			{
				questItem.YPos = topMargins;
				return;
			}
			
			if (stackPosition == quests.length)
			{
				questItem.YPos = quests[quests.length - 1].YPos + quests[quests.length - 1].ItemHeight;
				return;
			}
			
			questItem.YPos = quests[stackPosition].YPos;
			
			for (var i:int = stackPosition; i < quests.length; i++) 
			{
				quests[i].MoveYPos(quests[i].YPos + questItem.ItemHeight);
			}
		}
		
		private function GetNewElementStackPosition(primary:Boolean):int
		{
			if (primary)
			{
				for (var i:int = 0; i < quests.length; i++) 
				{
					if (!quests[i].Primary && primary)
					{
						return i;
					}
				}
			}
			
			return quests.length;
		}
		
		public function UpdateQuest(questId:int, complitedGoals:int):void 
		{
			var index:int = GetQuestItemIndexById(questId);
			
			if (index == -1) return;
			
			quests[index].UpdateQuest(complitedGoals)
		}
		
		public function UpdateQuestText( questId:int, text:String )
		{
			var index:int = GetQuestItemIndexById(questId);
			
			if (index == -1) return;
			
			var oldH : int = quests[index].ItemHeight;
			quests[index].UpdateQuestText(text);
			var newH : int = quests[index].ItemHeight;

			var deltaH = newH - oldH

			if (Math.abs(deltaH) < 2) return;

			for (var i:int = index + 1; i < quests.length; i++) 
			{
				quests[i].MoveYPos(quests[i].YPos + deltaH);
			}

			RescaleBackHeight(true);
		}
		
		public function RemoveQuest(questId:int):void 
		{
			var index:int = GetQuestItemIndexById(questId);
			
			if (index == -1) return;
			quests[index].StartAnim();
			ResetBackFadeOut();
		}
		
		private function OnAnimationEnded(e:QTItemAnimationEnded):void 			
		{
			var index = GetQuestItemIndexById(e.Item.ID);
			if (index == -1) return;
			
			quests[index].RemoveAnimation();
			quests[index].FadeOut();
			
			for (var i:int = index + 1; i < quests.length; i++)
			{
				quests[i].MoveYPos(quests[i].YPos - quests[index].ItemHeight);
			}
			removingQuests.push(quests[index]);
			quests.splice(index,1);
			
			RescaleBackHeight(false);
		}
		
		private function RescaleBackHeight(_add:Boolean):void
		{
			//если добавляем квест, и анимация еще не доиграла, то раздвигаем рамку быстрее
			//если убираем, то играем как обычно, потому, что текст не вылазит и всегда перерыт рамкой.
			if(_add && qtFrameHeightTween.isPlaying)
			{
				qtFrameHeightTween.duration = time/3;
			}
			else
			{
				qtFrameHeightTween.duration = time;
			}
			qtFrameHeightTween.stop();
			qtFrameHeightTween.begin = qtFrame_cmp.height;
			qtFrameHeightTween.finish = GetNewFrameHeight();
			qtFrameHeightTween.start();
		}
		
		private function GetQuestItemIndexById(questId:int):int 
		{
			for (var i:int = 0; i < quests.length; i++) 
			{
				if (quests[i].ID == questId)
				{
					return i;
				}
			}
			
			return -1;
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			this.x = stage.stageWidth - this.width;
			this.y = startYPosition * stage.stageHeight/initialStage.y;
		}
		
		override public function get isNeedToShowBackAfterCinematic():Boolean
		{
			return quests.length != 0;
		}
		
		
	}
}
