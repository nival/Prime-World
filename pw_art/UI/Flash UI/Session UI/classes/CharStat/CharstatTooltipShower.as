package CharStat
{
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.text.TextField;
	import flash.events.MouseEvent;
	
	public class CharstatTooltipShower extends Sprite
	{
		private var index:int;
		private var isBaseStat:Boolean;		
		
		private var baseTooltipCommand:String = FSCommands.CHARSTAT_BASE_TOOLTIP;
		private var derivativeTooltipCommand:String = FSCommands.CHARSTAT_DERIVATIVE_TOOLTIP;
		
		public function CharstatTooltipShower(baseStat:Boolean,_index:int)
		{
			index = _index;
 
			var shape:Shape = new Shape();
			
			shape.graphics.beginFill(0x0000CC);
			shape.graphics.drawRect(0, 0, 3, 3);
			shape.graphics.endFill();
			shape.alpha = 0;	
			
			addChild(shape);
			
			isBaseStat = baseStat;
			
			this.addEventListener(MouseEvent.MOUSE_OVER, ShowTooltip);
			this.addEventListener(MouseEvent.MOUSE_OUT, HideTooltip);
		}
		
		
		private function ShowTooltip(e:MouseEvent):void
		{
			var fsname:String = isBaseStat? baseTooltipCommand:derivativeTooltipCommand;
			FSCommands.Send(fsname, FSCommands.TOOLTIP_SHOW + index);
		}
		
		private function HideTooltip(e:MouseEvent):void
		{
			var fsname:String = isBaseStat? baseTooltipCommand:derivativeTooltipCommand;
			FSCommands.Send(fsname, FSCommands.TOOLTIP_HIDE + index);
		}
		
		
		public function SetTooltipPositionAndSize(statName:TextField,statField:TextField,statAddition:TextField=null):void
		{
			var addition:Number = 0;
			if (statAddition != null) addition = statAddition.textWidth;
			
			var gapBetweenNameAndStatField:Number = statField.x - statName.textWidth - statName.x;
			
			this.x = statName.x;
			this.y = statName.y;
			this.width = statName.textWidth+statField.textWidth +gapBetweenNameAndStatField + addition; 
			this.height =  statField.height;
		}
		
		public function ChangeCharStatTooltipCommands(isSelection:Boolean):void
		{
			baseTooltipCommand = isSelection? FSCommands.SELECTION_CHARSTAT_BASE_TOOLTIP : FSCommands.CHARSTAT_BASE_TOOLTIP;
			derivativeTooltipCommand = isSelection? FSCommands.SELECTION_CHARSTAT_DERIVATIVE_TOOLTIP:FSCommands.CHARSTAT_DERIVATIVE_TOOLTIP;
			
		}
	}
}