package ActionBar 
{
	import BaseClasses.BaseResizableObject;
	import Components.ButtonRound;
	import flash.display.MovieClip;
	import flash.events.Event;
	import Interfaces.IShowImpulseTalent;
	import MainScreen.DecorLine;
	import TalentBar.Talent;
	
	public class ActionBarContainer extends BaseResizableObject
	{
		private var startProp:Number;
		public var actionBar_mc:ActionBar;
		public var hintMessage_mc:HintMessage;
		public var actionBarBack_mc:MovieClip;
		
		public function ActionBarContainer()
		{
			this.mouseEnabled = false;
			startProp =  actionBarBack_mc.height / this.height;
			actionBarBack_mc.mouseEnabled = false;
			actionBarBack_mc.mouseChildren = false;
		}
		
		public function SetHintline(text:String,type:String):void
		{
			hintMessage_mc.SetText(text, type);
			
			hintMessage_mc.x = positionOnCenter * actionBarBack_mc.width - hintMessage_mc.GetHintMessageCenterOffset();
		}
		
		
		override protected function BaseBarObjectResize(e:Event=null):void
		{	
			super.BaseBarObjectResize();
			this.x = stage.stageWidth / 2 - positionOnCenter * this.width;
			this.y = (stage.stageHeight - this.height * startProp - DecorLine.DECOR_LINE_HEIGHT);
			this.x = Math.floor(this.x);
			this.y = Math.floor(this.y);
		}
		
		override public function ShowFinalAnimation():void 
		{
			actionBar_mc.play();
			actionBar_mc.addFrameScript(actionBar_mc.totalFrames-1, StopPlay);
		}
		
		private function StopPlay():void
		{
			actionBar_mc.stop();
			actionBar_mc.visible = false;
		} 
	}

}