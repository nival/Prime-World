package MainScreen
{
	import fl.transitions.easing.Strong;
	import fl.transitions.Tween;
	import flash.display.MovieClip;
	import flash.events.Event;

	import BaseClasses.MateInfoBase;
	import BaseClasses.BaseResizableObject;
	import Interfaces.IMateInfoContainer;
	
	public class TeamInfoFriendly extends TeamInfoBase
	{
		private var tweenTime:int = 1;
		
		override public function AddedToStage(e:Event):void 
		{
			teamMates = [teamMate1_mc, teamMate2_mc, teamMate3_mc, teamMate4_mc, teamMate5_mc];
			super.AddedToStage(e);
		}
		
		override protected function BaseBarObjectResize(e:Event=null):void
		{	
			super.BaseBarObjectResize();
			this.x = startXPosition * scale;
			this.y = 0;
			this.x = Math.floor(this.x);
			this.y = Math.floor(this.y);
		}
		
		
		override public function ShowFinalAnimation():void 
		{
			var tween:Tween = new Tween(this, "y", Strong.easeOut, y, -height, tweenTime,true);
			tween.start();
		}
	}
}