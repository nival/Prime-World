package MainScreen 
{
	import BaseClasses.BaseResizableObject;
	import flash.events.Event;
	
	public class DayNightWrapper extends BaseResizableObject 
	{
		public var dayNightAnim_mc:DayNight;
		
		public function DayNightWrapper() 
		{
			super();
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void
		{	
			super.BaseBarObjectResize(e);
			
			// TODO: учитывать фактическое положение и размеры миникарты
			// NOTE: 280 - ширина миникарты, 24 - подвигает ближе к миникарте
			this.x = Math.floor(stage.stageWidth - 280 + 24);
			this.y = Math.floor(stage.stageHeight - DecorLine.DECOR_LINE_HEIGHT);
		}
		
		public function set GameTime(value:int):void
		{
			dayNightAnim_mc.GameTime = value;
		}
		
		public function set GameTimerVisible(value:Boolean):void
		{
			dayNightAnim_mc.timer_mc.visible = value;
		}
	}
}