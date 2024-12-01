package Test 
{
	import Components.PWCombobox;
	import flash.display.MovieClip;
	import flash.events.Event;
	
	import flash.display.Shape
	import flash.display.MovieClip;
	import Components.ScrollBar;
	
	public class MaskTest extends MovieClip
	{
		private var scrollBar:ScrollBar
		public var scrollableItem:ScrollableItem;
		public var combo:PWCombobox;
		
		public function MaskTest() 
		{
			this.addEventListener(Event.ADDED_TO_STAGE, OnAdded);
		}
		
		private function OnAdded(e:Event):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, OnAdded);
			
			var normalMovie:MovieClip = new MovieClip();
			this.addChild(normalMovie);
			var scaledMovie:MovieClip = new MovieClip();
			this.addChild(scaledMovie);
			scaledMovie.x = 160;

			var normalBack:Shape = new Shape();
			normalBack.graphics.beginFill(0xFF0000);
			normalBack.graphics.drawRect(0, 0, 150, 150);
			normalMovie.addChild(normalBack);

			var normalWithMask:Shape = new Shape();
			normalWithMask.graphics.beginFill(0x00FF00);
			normalWithMask.graphics.drawRect(0, 0, 150, 150);
			normalMovie.addChild(normalWithMask);

			var normalMask:Shape = new Shape();
			normalMask.graphics.beginFill(0x0000FF);
			normalMask.graphics.drawRect(25, 25, 100, 100);
			normalMovie.addChild(normalMask);

			normalWithMask.mask = normalMask;

			var scaledBack:Shape = new Shape();
			scaledBack.graphics.beginFill(0xFF0000);
			scaledBack.graphics.drawRect(0, 0, 150, 150);
			scaledMovie.addChild(scaledBack);

			var scaledWithMask:Shape = new Shape();
			scaledWithMask.graphics.beginFill(0x00FF00);
			scaledWithMask.graphics.drawRect(0, 0, 150, 150);
			scaledMovie.addChild(scaledWithMask);

			var scaledMask:Shape = new Shape();
			scaledMask.graphics.beginFill(0x0000FF);
			scaledMask.graphics.drawRect(25, 25, 100, 100);
			scaledMovie.addChild(scaledMask);

			scaledWithMask.mask = scaledMask;

			scaledMovie.scaleX = 0.6;
			scaledMovie.scaleY = 0.3;

			scrollBar = new ScrollBar(scrollableItem);
			this.addChild(scrollBar);
		}
	}

}