package MainScreen
{
	import flash.display.MovieClip;
	import flash.events.Event;
	
	import BaseClasses.BaseResizableObject;
	public class heroInfoTopWraper extends BaseResizableObject
	{
		public var heroInfoAnim_mc:MateInfo;
		
		public function heroInfoTopWraper()
		{
			this.mouseEnabled = false;
			heroInfoAnim_mc.mouseEnabled = false;
		}
		
		override protected function BaseBarObjectResize(e:Event=null):void
			{	
				super.BaseBarObjectResize();
				this.x = 0;
				this.y = 0;
				this.y = Math.floor(this.y);
			}
	}
}