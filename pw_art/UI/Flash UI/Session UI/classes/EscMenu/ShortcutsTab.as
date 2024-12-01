package EscMenu 
{
	import flash.display.MovieClip;
	import Components.ScrollBar;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import Components.ComboBoxRow;
	import flash.utils.Timer;
	import flash.events.TimerEvent;
	import Components.ButtonStandart;
	
	public class ShortcutsTab extends MovieClip
	{		
		public var shortcutContainer:ShortcutsContainer;
		
		public var apply_btn:ButtonStandart;
		public var cancel_btn:ButtonStandart;

		private var scroll_bar:ScrollBar;
		
		private var commandNames:Array = [];
		private var commandValues:Array = [];		
		private var isInit:Boolean = false;
		
		public function ShortcutsTab()
		{
			this.addEventListener(MouseEvent.CLICK, OnMouseClick);
		}
		
		public function Init():void
		{
			if (!isInit)
			{
				isInit = true;
				shortcutContainer.Init();
				
				if (shortcutContainer.ScrollableHeight > shortcutContainer.ActualHeight)
				{
					if (scroll_bar == null)
					{
						scroll_bar = new ScrollBar();
						scroll_bar.SetScrollableContent(shortcutContainer, true, false);
						addChild(scroll_bar);
					}			
					
					scroll_bar.RecalcContentHeight();				
				}
				
				for (var i:int = 0; i < commandNames.length; i++)
				{
					shortcutContainer.FillItem(commandNames[i], commandValues[i]);							
				}
			}			
		}
		
		public function FillBindSettings(bindString:String):void 
		{			
			var firstSpaceIndex:int = bindString.indexOf(" ");
			if (firstSpaceIndex == -1)
				return;
			
			var secondSpaceIndex:int = bindString.indexOf(" ", firstSpaceIndex + 1);
			if (secondSpaceIndex == -1)
				return;
			
			var command:String = bindString.slice(firstSpaceIndex + 1, secondSpaceIndex);
			
			bindString = bindString.slice(secondSpaceIndex + 1, bindString.length);
			
			if (bindString.indexOf("'") == -1)
				return;
				
			var number: int = int(bindString.slice(0, bindString.indexOf("'")));
			if (number != 0)
			{
				command = command + " " + number;
			}
			
			var bind:String = bindString.slice(bindString.indexOf("'") + 1, bindString.length);
			bindString = bindString.slice(bindString.indexOf("'") + 1, bindString.length);
			
			bind = bind.slice(0,bind.indexOf("'"))
			
			if (bindString.indexOf("+", 0) != -1 )
			{
				bindString = bindString.slice(bindString.indexOf("+"), bindString.length);
				bindString = bindString.slice(bindString.indexOf("'") + 1, bindString.length);
				bind = bind + "+" + bindString.slice(0, bindString.indexOf("'"));
			}
			
			if (isInit)
			{
				shortcutContainer.FillItem(command, bind);
			}
			else
			{
				if (commandNames.indexOf(command) == -1)
				{
					commandNames.push(command);
					commandValues.push(bind);
				}
			}
		}
		
		private function OnMouseClick(e:MouseEvent):void 
		{
			shortcutContainer.ClearFocus();
		}
	}
}