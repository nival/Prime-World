package ContMenu 
{
	import ActionBar.ActionBarToggle;
	import BaseClasses.BaseContextItem;
	import BaseClasses.BaseResizableObject;
	import Components.Frame;
	import flash.display.MovieClip;
	import flash.display.DisplayObjectContainer;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.utils.Timer;
	import src.WButton;
	
	public class ContextMenu extends BaseResizableObject
	{
		public var frame:Frame;
		public var menu_btn:ContextMenuButton;
		public var arrow_btn:WButton;
		public var negativeList:BaseContextMenuButton;
		public var subject:MovieClip;
		
		private var startBtnPosition:Point = new Point();		
		private var contextButtons:Array = new Array();
		
		private var bottomOffset:Number;
		private var isMouseOut:Boolean = true;
		private var currentItems:Array = new Array();
		private var isNegativShowing:Boolean;
		private var showNegativeTimer:Timer = new Timer(1000,1)
		private var isOverNegativ:Boolean;
		override public function AddedToStage(e:Event):void 
		{
			super.AddedToStage(e);
			
			startBtnPosition.x = menu_btn.x;
			startBtnPosition.y = menu_btn.y;
			negativeList.x = menu_btn.x;
			contextButtons.push(menu_btn);
			
			
			visible =  false;
			bottomOffset = frame.height - (arrow_btn.y + arrow_btn.height);
			arrow_btn.visible = false;
			this.addEventListener(MouseEvent.ROLL_OUT, onMouseOut)
			this.addEventListener(MouseEvent.ROLL_OVER, onMouseOver)
			negativeList.visible = false;
			negativeList.addEventListener("Up", OnNegativListClick);
			
			negativeList.backBtn.addEventListener(MouseEvent.MOUSE_OVER, OnNegativListOver);
			negativeList.backBtn.addEventListener(MouseEvent.MOUSE_OUT, OnNegativListOut);
			showNegativeTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnTimerEnd);
			
			this.addEventListener(Event.ENTER_FRAME, OnEnterFrame);
		}
		
		private function OnEnterFrame(e:Event)
		{
			if ( !subject )
				return;
				
			if ( !subject.visible )
			{
				this.visible = false;
				return
			}
				
			if ( subject.stage == null )
			{
				this.visible = false;
				return;
			}
			
			var p:DisplayObjectContainer = subject.parent;
			
			while( !( p is Stage ) )
			{
				if ( !p.visible )
				{
					this.visible = false;
					return;
				}
				p = p.parent;
			}
		}
		
		private function OnTimerEnd(e:TimerEvent):void 
		{	
			if (isNegativShowing) return;
			
			ShowFullList();
		}
		
		private function OnNegativListOut(e:MouseEvent):void 
		{
			isOverNegativ = false;
			showNegativeTimer.stop();
		}
		
		private function OnNegativListOver(e:MouseEvent):void 
		{
			isOverNegativ = true;
			showNegativeTimer.start();
		}

		private function OnNegativListClick(e:Event):void 
		{
			e.stopPropagation();
			ShowFullList();
		}
		
		private function ShowFullList():void 
		{
			isNegativShowing = !isNegativShowing;
			showNegativeTimer.stop();
			
			for (var i:int = 0; i < contextButtons.length; i++) 
			{
				if (contextButtons[i].IsNegative && contextButtons[i].IsUsing)
					contextButtons[i].visible = isNegativShowing;
			}
			
			if (!isNegativShowing && isOverNegativ)
			{
				showNegativeTimer.start();
			}
			
			
			RecalcBackSize();
		}
		
		private function onMouseOver(e:MouseEvent):void 
		{
			isMouseOut = false;
		}
		
		private function onMouseOut(e:MouseEvent):void 
		{
			isMouseOut = true;
		}
		
		public function ShowMenu(items:Array):void 
		{
			currentItems = items;
			
			isNegativShowing = false;
			
			visible = true;
			negativeList.visible = false;
			
			for each(var item:ContextMenuButton in contextButtons)
			{
				item.visible = false;
				item.IsUsing = false;
			}
			
			for (var i:int = 0; i < items.length; i++)
			{
				if (i < contextButtons.length)
				{
					if (contextButtons[i] != null)
					{
						contextButtons[i].AddContextButtonHandler(items[i]);
						contextButtons[i].visible = !contextButtons[i].IsNegative;
						
						continue;
					}
				}
				
				var contextBtn:ContextMenuButton = new ContextMenuButton();
				contextBtn.AddContextButtonHandler(items[i])
				contextBtn.x = startBtnPosition.x;
				contextBtn.visible = !contextBtn.IsNegative;
				addChild(contextBtn);
				contextButtons.push(contextBtn);
			}
			
			ArrangeButtons();
			RecalcBackSize();
			
			this.x = stage.mouseX;
			this.y = stage.mouseY;
			
			if (this.x + frame.width > stage.stageWidth)
				this.x -= frame.width;
			
			if (this.y + frame.height > stage.stageHeight)
				this.y -= frame.height; 
		}
		
		private function ArrangeButtons():void
		{
			negativeList.visible = false;
			negativeList.y = startBtnPosition.y;
			
			var posY:Number = startBtnPosition.y;
			var negative:Array = new Array();
			var positive:Array = new Array();
			for (var i:int = 0; i < contextButtons.length ; i++) 
			{
				if (!contextButtons[i].IsUsing) continue;
				
				if (contextButtons[i].IsNegative )
					negative.push(contextButtons[i]);
				else
					positive.push(contextButtons[i]);
			}
			
			for (var k:int = 0; k < positive.length ; k++) 
			{
				positive[k].y = posY;
				posY += positive[k].GetHeight();
			}
				
			if (negative.length == 0)
				return;
				
			negativeList.y = posY;
			negativeList.visible = true;
			posY += negativeList.GetHeight();
			
			for (var j:int = 0; j < negative.length; j++) 
			{
				negative[j].y = posY;
				posY += menu_btn.GetHeight();
			}
			
		}
		
		private function RecalcBackSize():void
		{	
			var bottomElemenY : Number = 0;
			var hasNegativeVisibleItems : Boolean = false;
			
			for each (var button:ContextMenuButton in contextButtons) 
			{
				if (!button.visible) continue;
				
				bottomElemenY = Math.max( button.y + button.GetHeight(),  bottomElemenY );
			
				if (button.IsNegative)
					hasNegativeVisibleItems = true;
			}
					
			if (negativeList.visible && !hasNegativeVisibleItems)
				bottomElemenY = Math.max( negativeList.y +negativeList.GetHeight(),  bottomElemenY );
					
			frame.setSize(frame.width, bottomElemenY + bottomOffset);
		}
		
		
		public function get MouseIsOut():Boolean 
		{
			return isMouseOut;
		}
		
		override public function set visible(value:Boolean) : void
		{
			super.visible = value;
			if ( !value )
				subject = null;
		}
	}

}