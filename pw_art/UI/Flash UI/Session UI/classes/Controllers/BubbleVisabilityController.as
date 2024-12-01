package classes.Controllers 
{
	import ActionBar.ImpulsTalentIco;
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.utils.Dictionary;
	import MainScreen.BubbleControl;
	public class BubbleVisabilityController 
	{
		private var bubbles:Dictionary = new Dictionary();
		private var mainWindow:Main;
		
		public function BubbleVisabilityController(_main:Main) 
		{
			mainWindow = _main
		}
		
		public function ShowBuble(control:MovieClip, show:Boolean, text:String,bubbleViewType:String, bubbleIndex:int, xOffset:Number=0, yOffset:Number=0):void 
		{
			if (control == null) return;

			if (!show && bubbles[control] != null)
			{
				mainWindow.removeChild(bubbles[control]);
				bubbles[control].Destroy();
				bubbles[control] = null;
				return;
			}
			
			if (bubbles[control]==null && show)
			{
				var bubble:BubbleControl = new BubbleControl(control,text,bubbleViewType,bubbleIndex, xOffset, yOffset);
				mainWindow.addChild(bubble);
				bubbles[control] = bubble;
			}
		}
		
		public function GetBubble(control:MovieClip):DisplayObject
		{
			if (control == null) return null;
			
			return bubbles[control];
		}
		
		
	}

}