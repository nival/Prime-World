package MainScreen
{
	import flash.display.Bitmap;
	import flash.display.MovieClip;
	import flash.events.Event;
	import BaseClasses.BaseResizableObject;
	
	public class DecorLine extends BaseResizableObject
	{
		public static var DECOR_LINE_HEIGHT:Number = 11;
		
		public function DecorLine()
		{
			DECOR_LINE_HEIGHT = this.height;
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			super.BaseBarObjectResize(e);
			
			DECOR_LINE_HEIGHT = this.height;
			this.x = 0;
			this.y = stage.stageHeight-this.height;
		}
		
	}
}