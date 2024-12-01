package Components 
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import Interfaces.IScrollableObject;
	import InventoryBar.InventoryButton;
	import ShopBar.ShopBarButton;
	
	public class ScrollableContent extends MovieClip implements IScrollableObject 
	{
		private var buttons:Array;
		private var posX:Number = 0;
		private var posY:Number = 0;
		private var xOffset:Number = 3;
		private var yOffset:Number = 3;
		private var columnsCount:int = 4;
		private var rawCount:int =5 ;
		private var actualHeight:Number;
		private var stepSize:Number = 0;
		private var scrollableHeight:Number;
		
		public function ScrollableContent(barButtons_arr:Array, _columnsCount:int, _rawCount:Number) 
		{
			buttons = barButtons_arr;
			columnsCount = _columnsCount;
			rawCount = int(_rawCount);
			addEventListener(Event.ADDED_TO_STAGE, AddedToStage);
		}
		
		public function AddShopButtons(neededCount:int):void //для магазина
		{
			var numberOfRaws:int;

			numberOfRaws = neededCount % 4 == 0? neededCount : (int(neededCount / 4) + 1);
			
			for (var i:int = 0; i < numberOfRaws*columnsCount; i++) 
			{
				var button:ShopBarButton = new ShopBarButton();
				this.addChild(button)
				button.x = posX;
				button.y = posY;
				
				buttons.push(button);
				
				posX += button.width + xOffset;
				
				if (posX >= columnsCount * (button.width + xOffset))
				{
					posX = 0;
					posY +=  button.height+yOffset
				}
			}
			
			scrollableHeight = posY - yOffset;
		}
		
		public function AddInventoryButtons(neededCount:int):void   //для инвентаря
		{
			var numberOfRaws:int;
			numberOfRaws = neededCount % 4 == 0? neededCount : (int(neededCount / 4) + 1);
			
			for (var i:int = 0; i < numberOfRaws*columnsCount; i++) 
			{
				var button:InventoryButton = new InventoryButton();
				this.addChild(button)
				button.x = posX;
				button.y = posY;
				buttons.push(button);
				posX += button.width + xOffset;
				
				if (posX >= columnsCount * (button.width + xOffset))
				{
					posX = 0;
					posY +=  button.height+yOffset
				}
			}
			
			scrollableHeight = posY - yOffset;
		}
		
		private function AddedToStage(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, AddedToStage);
			
			for (var i:int = 0; i < buttons.length; i++) 
			{
				addChild(buttons[i])
				buttons[i].x = posX;
				buttons[i].y = posY;
				
				posX += buttons[i].width + xOffset;
				
				if (posX >= columnsCount * (buttons[i].width + xOffset))
				{
					posX = 0;
					posY +=  buttons[i].height+yOffset
				}
			}
			
			stepSize = buttons[0].height + yOffset;
			
			actualHeight = stepSize * rawCount-yOffset;
			scrollableHeight = posY - yOffset;
		}
		
		public function get ScrollableHeight():Number 
		{
			return scrollableHeight;
		}
		
		public function get StepSize():Number 
		{
			return stepSize;
		}
		
		public function get ActualHeight():Number 
		{
			return actualHeight;
		}
		
		public function get TopMargin():Number 
		{
			return 0;
		}
		
		public function get BottomMargin():Number 
		{
			return 0;
		}
		
		override public function get width():Number 
		{
			return columnsCount*(buttons[0].width +xOffset) // пришлось так вычислять, потому что в инвентаре кнопки больше чем надо
		}
	}

}