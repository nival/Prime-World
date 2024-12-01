package MainScreen
{
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	import BaseClasses.BaseResizableObject;
	
	public class HeroInfo extends BaseResizableObject 
	{
		public var heroInfoAnim_mc:HeroMateInfo;
		
		public function HeroInfo() {
			
		}
		
		public function set MiniGameOn(_minigameOn:Boolean):void 
		{	
			this.mouseEnabled = !_minigameOn;
			this.mouseChildren = !_minigameOn;
		}
		
		override protected function BaseBarObjectResize(e:Event=null):void
			{	
				super.BaseBarObjectResize();
				this.x = 0;
				this.y = (stage.stageHeight - DecorLine.DECOR_LINE_HEIGHT);
				this.y = Math.floor(this.y);
			}
	}
	
}
