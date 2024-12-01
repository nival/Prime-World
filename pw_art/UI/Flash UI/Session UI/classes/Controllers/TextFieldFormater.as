package Controllers
{
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.text.TextField;
	import src.ButtonTooltipEvent;
	
	public class TextFieldFormater
	{
		private var textField:TextField;
		private var textFieldFull:String = "";
		
		private var isNeedTooltipShow:Boolean = false;
		private var textFieldWidth:Number;
		private var isOver:Boolean;
		
		public function TextFieldFormater(_textField:TextField)
		{
			textField = _textField;
			textFieldWidth = textField.width;
			textField.mouseEnabled = true;
			textField.addEventListener(MouseEvent.ROLL_OVER, OnTextFieldOver);
			textField.addEventListener(MouseEvent.ROLL_OUT, OnTextFieldOut);
			textField.addEventListener(MouseEvent.MOUSE_MOVE, OnTextFieldMove);
		}
		
		public function RecalcTextWidth(newTextWidth:Number):void 
		{
			textFieldWidth = newTextWidth;
			Text = textFieldFull;
		}
		
		private function OnTextFieldMove(e:MouseEvent):void 
		{
			
			if (isNeedTooltipShow&&isOver)
			{
				var point:Point = new Point(textField.mouseX, textField.mouseY);
				textField.dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
				textField.dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, textField, textField.localToGlobal(point).x, textField.localToGlobal(point).y, textFieldFull));
			}
		}
		
		private function OnTextFieldOut(e:MouseEvent):void 
		{
			isOver = false;
			
			if (isNeedTooltipShow)
				textField.dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_OUT));
		}
		
		private function OnTextFieldOver(e:MouseEvent):void
		{
			isOver = true;
			var point:Point = new Point(textField.mouseX, textField.mouseY);
		
			if (isNeedTooltipShow)
				textField.dispatchEvent(new ButtonTooltipEvent(ButtonTooltipEvent.ACTION_TYPE_IN, textField, textField.localToGlobal(point).x, textField.localToGlobal(point).y, textFieldFull));
		}
		
		public function get Text():String		
		{
			return isNeedTooltipShow? textFieldFull:textField.text;
		}
		
		public function set Text(value:String):void
		{
			textFieldFull = value;
			
			textField.text = value;
			if (textField.textWidth <= textFieldWidth)
			{
				isNeedTooltipShow = false;
				return;
			}
			
			isNeedTooltipShow = true;
				
			var length:int = textFieldFull.length;
			
			for (var i:int = 0; i < length; i++)
			{
				var currentText:String = textField.text.substring(0, textField.text.length - 1);
				
				textField.text = currentText+"...";
				
				if (textField.textWidth <= textFieldWidth)
				{
					break;
				}
				else
				{
					textField.text = currentText;
				}
			}
		}
		
		public function SetFormatedNumber(value:int):void
		{
			textFieldFull = value.toString();
			textField.text = textFieldFull;
			
			if (value < 100000) 
			{
				isNeedTooltipShow = false
				return;
			}
				
			isNeedTooltipShow = true;
			
			textField.text = int(value / 1000).toString() + Localization.StatisticsThousendsIndificator;
		}
	}

}