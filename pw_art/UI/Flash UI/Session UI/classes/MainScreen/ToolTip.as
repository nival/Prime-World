package MainScreen
{

	import flash.display.DisplayObjectContainer;
	import flash.display.Sprite;
	import flash.display.DisplayObject;
	import flash.display.Stage;
	import flash.geom.Point;
	import flash.text.TextField;
	import flash.events.Event;
	import flash.text.TextFieldAutoSize;
	import src.ButtonTooltipEvent;
	import Components.Frame;
	
	public class ToolTip extends Sprite
	{
		public var tooltip:String = '';
		private var objectTooltipX:Number;
		private var objectTooltipY:Number;
		
		public var mainContainer:DisplayObjectContainer;
		private var target:DisplayObject;
		
		private const BOTTOM_OFFSET:int = 20; //отступ снизу для тултипа
		private const OTHERS_OFFSET:int = 5;  //отступ со всех остальных сторон	
		
		//references
		public var frameTooltip:Frame;
		public var toolTip_txt:TextField;

		public function ToolTip()
		{
			//main = _main;
			this.visible = false;
			this.mouseEnabled = false;
			this.mouseChildren = false;

			//TODO из-за нашей "великолепной" сборки, не могу просто создать обычный объект из класса и вставить его сюда а просто вытаскиваю его из библиотеки,
			//потому что он доступен отовсюду."
			
			this.mouseEnabled = false;
		
			toolTip_txt.autoSize = TextFieldAutoSize.LEFT;
			frameTooltip.Image = 'frameTooltip_png';
			frameTooltip.setSize(25,25);
	
			
		}
		public function tooltipHandler(e:ButtonTooltipEvent):void
		{
			
			tooltip = e.tooltip;
			
			if (e.x != -1 && e.y != -1)
			{
				objectTooltipX = e.x;
				objectTooltipY = e.y;
			}
			
			target = e.targetObject;
			
			switch (e.action)
			{
				case ButtonTooltipEvent.ACTION_TYPE_IN :
					{
						ShowTooltip();
						break;
					};

				case ButtonTooltipEvent.ACTION_TYPE_OUT :
					{
						HideTooltip();
						break;
					};
				default :
					trace('bad ButtonTooltipEvent');
			}
		}

		private function ShowTooltip():void
		{
			if (tooltip == '') return;
		
			if (tooltip == toolTip_txt.text)
			{
				PositionTooltip();
				this.visible = true;
				return;
			}
			
			toolTip_txt.text = tooltip;

		
			if (toolTip_txt.width < 25)
			{
				//если текст по ширине меньше чем 25(поскольку мы не можем сделать рамку меньше, мы должны его просто выровнить по центру)
				frameTooltip.setSize(25,toolTip_txt.height+8);

				toolTip_txt.x = (frameTooltip.width - toolTip_txt.width)/2;
				toolTip_txt.y = (frameTooltip.height - toolTip_txt.height)/2;

			}
			
			if (toolTip_txt.height < 25)
			{
				frameTooltip.setSize(toolTip_txt.width+8,25);

				toolTip_txt.x = (frameTooltip.width - toolTip_txt.width)/2;
				toolTip_txt.y = (frameTooltip.height - toolTip_txt.height)/2;
			}
			else
			{
				//8 - потому что 5 отступ + 5-2 это скидка на толщину рамки
				frameTooltip.setSize(toolTip_txt.width+8,toolTip_txt.height+8);
			}
			
			PositionTooltip();
						
			this.visible = true;
			
		}
		
		private function CalcNewPoistion():Point
		{
			var pos:Point = new Point(objectTooltipX - OTHERS_OFFSET, objectTooltipY - OTHERS_OFFSET);
			var screenSize:Point = new Point(mainContainer.stage.stageWidth - OTHERS_OFFSET * 2, 
				mainContainer.stage.stageHeight - OTHERS_OFFSET - BOTTOM_OFFSET);
				
			var res:Point = new Point();
			
			//desired whole width
			var wholeWidth:int = pos.x + this.width;
			
			//try to position on top
			if (pos.y - this.height >= 0)
			{
				res.y = pos.y - this.height;
				
				//calculate x offset
				var xDelta:int = (wholeWidth > screenSize.x)? wholeWidth - screenSize.x : 0;
				
				res.x = pos.x - xDelta;
			}
			else
			{
				//position on the same y level
				res.y = pos.y + 1;
				
				if (wholeWidth + target.width < screenSize.x)
				{
					//we can place tooltip on the right side
					res.x = pos.x + target.width +1;
				}
				else  
				{
					//place on the left side
					res.x = pos.x - this.width -1;
				}
			}
			
			pos.x = Math.max(pos.x, 0);
			pos.y = Math.max(pos.y, 0);
			res.x += OTHERS_OFFSET;
			res.y += OTHERS_OFFSET;
			
			return res;
		}
		
		private function PositionTooltip():void
		{
			var newPos:Point = CalcNewPoistion();
			this.x = newPos.x;
			this.y = newPos.y;
			
			mainContainer.setChildIndex(this,mainContainer.numChildren - 1);
		}			

		private function HideTooltip():void
		{
			this.visible = false;
		}
	}
}