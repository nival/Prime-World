package EscMenu 
{
	import flash.events.FocusEvent;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.text.TextField;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.ui.Keyboard;
	
	public class ShortcutItem extends MovieClip
	{
		public var text:TextField;
		public var value:TextField;
		public var valueFrame:MovieClip;
		
		private var isCapture:Boolean;
		private var currentValue:String;
		private var formatedValue:String;
		
		private var isShift:Boolean
		private var isControl:Boolean
		private var isAlt:Boolean
		
		private var defaultValue:String;
		
		private var container:ShortcutsContainer;
		
		public function ShortcutItem()
		{
			isCapture = false;
			
			value.addEventListener(MouseEvent.CLICK, OnValueFocusIn);
			value.addEventListener(KeyboardEvent.KEY_DOWN, OnValueKeyDown);
			value.addEventListener(KeyboardEvent.KEY_UP, OnValueKey);
		}
		
		public function SetName(name:String):void
		{
			text.text = name;		
		}
		
		public function SetBind(key:String):void
		{
			value.text = key;
			currentValue = key;		
			defaultValue = key;
		}
		
		public function SetContainer(shortcutsContainer:ShortcutsContainer):void
		{
			container = shortcutsContainer;
		}
		
		public function ResetToDefault():void
		{
			value.text = defaultValue;
			currentValue = defaultValue;
			ClearFocus();
		}
		
		public function IsChanged():Boolean
		{
			return defaultValue != currentValue;
		}
		
		public function ClearFocus():void
		{
			isCapture = false;
			isShift = false;
			isControl = false;
			value.text = currentValue;
			if (stage.focus == value)
			{
				stage.focus = null;
			}
		}
		
		public function GetRebindString():String
		{
			return formatedValue;
		}
		
		private function OnValueFocusIn(e:MouseEvent):void 
		{
			if (isCapture)
			{
				ClearFocus();
			}
			else
			{
				if (container)
				{
					container.ClearFocus();
				}
				
				e.type
				isCapture = true;
				isShift = false;
				isControl = false;
				value.text = "|";
				stage.focus = value;
			}
			
			e.stopPropagation();
		}
		
		private function OnValueKeyDown(event:KeyboardEvent):void 
		{
			if (event.keyCode == Keyboard.SHIFT)
			{
				isShift = true;
			}
			if (event.keyCode == Keyboard.CONTROL)
			{
				isControl = true;
			}		
			
			value.text = "";
			event.preventDefault();
		}
		
		private function OnValueKey(event:KeyboardEvent):void 
		{
			if (isCapture)
			{		
				value.text = "";
				
				if ((event.keyCode >= 0x30 && event.keyCode <= 0x39) ||
					(event.keyCode >= 0x41 && event.keyCode <= 0x5A))
				{
					value.text = String.fromCharCode(event.charCode);
				}
				else if (event.keyCode >= Keyboard.NUMPAD_0 && event.keyCode <= Keyboard.NUMPAD_9)
				{
					value.text = "NUM_" + (event.keyCode - Keyboard.NUMPAD_0);
				}
				else if (event.keyCode >= Keyboard.F1 && event.keyCode <= Keyboard.F15)
				{
					value.text = "F" + (event.keyCode - Keyboard.F1 + 1);
				}
				else
				{
					switch (event.keyCode)
					{
						case Keyboard.CONTROL:
							value.text = "CTRL";
							break;
						
						case Keyboard.ENTER:
							value.text = "ENTER";
							break;
						
						case Keyboard.SHIFT:
							value.text = "SHIFT";
							break;
						
						case Keyboard.SPACE:
							value.text = "SPACE";
							break;
						
						case Keyboard.TAB:
							value.text = "TAB";
							break;
						
						case Keyboard.UP:
							value.text = "UP";
							break;
						
						case Keyboard.DOWN:
							value.text = "DOWN";
							break;
						
						case Keyboard.LEFT:
							value.text = "LEFT";
							break;
						
						case Keyboard.RIGHT:
							value.text = "RIGHT";
							break;
							
						case 0x12:
							value.text = "ALT";
							break;
							
						case 0xBB:
							value.text = "=";
							break;
							
						case 0xBD:
							value.text = "-";
							break;
							
						case 0xDB:
							value.text = "[";
							break;
							
						case 0xDD:
							value.text = "]";
							break;
					}
				}
				
				if (value.text != "")
				{
					formatedValue = "'" + value.text + "'";
					
					if (isShift && event.keyCode != Keyboard.SHIFT)
					{
						formatedValue = "'SHIFT' + '" + value.text + "'";
						value.text = "SHIFT+" + value.text;						
					}
					if (isControl && event.keyCode != Keyboard.CONTROL && isShift == false)
					{
						formatedValue = "'CTRL' + '" + value.text + "'";
						value.text = "CTRL+" + value.text;						
					}
					
					currentValue = value.text;
				}
				else
				{
					value.text = currentValue;
				}
				
				ClearFocus();
			}
			
			if (event.keyCode == Keyboard.SHIFT)
			{
				isShift = false;
			}
			if (event.keyCode == Keyboard.CONTROL)
			{
				isControl = false;
			}
		}
	}
}