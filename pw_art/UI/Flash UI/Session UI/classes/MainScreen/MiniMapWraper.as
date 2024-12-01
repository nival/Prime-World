package MainScreen
{
	
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	import BaseClasses.BaseResizableObject;
	
	public class MiniMapWraper extends BaseResizableObject
	{
		public var miniMapAnim_mc:Minimap;
		
		public function MiniMapWraper()
		{
		
		}
		
		public function set MiniGameOn(_minigameOn:Boolean):void 
		{				
			this.mouseChildren = !_minigameOn;
			this.mouseEnabled = !_minigameOn;
			
		}
		
		override protected function BaseBarObjectResize(e:Event=null):void
			{	
				super.BaseBarObjectResize();
				this.x = stage.stageWidth
				this.y = (stage.stageHeight - DecorLine.DECOR_LINE_HEIGHT);
				this.x = Math.floor(this.x);
				this.y = Math.floor(this.y);
			}	
			
		public function AddSignal(X:Number, Y:Number, color:uint, lifeTime:Number):void
		{
			miniMapAnim_mc.AddSignal(X, Y, color, lifeTime);
		}
		
		public function SetTargetZoneColor(value:uint):void
		{
			miniMapAnim_mc.TargetZoneColor = value;
		}
		
		public function SetTargetZoneThickness(value:uint):void
		{
			miniMapAnim_mc.TargetZoneThickness = value;
		}
		
		public function ShowTargetZone(X:Number, Y:Number, radius:Number):void
		{
			miniMapAnim_mc.ShowTargetZone(X, Y, radius);
		}
		
		public function HideTargetZone():void
		{
			miniMapAnim_mc.HideTargetZone();
		}
		
		public function set GameTime(value:int):void
		{
			miniMapAnim_mc.GameTime = value;
		}
		
		public function set GameTimerVisible(value:Boolean):void
		{
			miniMapAnim_mc.timer_mc.visible = value;
		}
		
		public function set HeroIsDead(isDead:Boolean):void
		{
			miniMapAnim_mc.HeroIsDead = isDead;
		}
		
		public function DisablePingButton() : void
		{
			miniMapAnim_mc.DisablePingButton();
		}

		public function set CameraBtnStatus(isLocked:Boolean):void
		{
			miniMapAnim_mc.CameraBtnStatus = isLocked;
		}

	}
}