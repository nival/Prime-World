package MainScreen
{	
	import flash.events.Event;
	import BaseClasses.BaseResizableObject;
	
	public class NonClickable extends BaseResizableObject
	{
	
		override protected function BaseBarObjectResize(e:Event=null):void
		{	
			this.x = 0;
			this.y = 0;
			this.width = stage.stageWidth+5;
			this.height = stage.stageHeight+5;
		}
		
		override public function ShowCinematicDialog():void
		{
			// do nothing
		}
		
		override public function HideCinematicDialog():void
		{
			// do nothing
		}
	}
	
}