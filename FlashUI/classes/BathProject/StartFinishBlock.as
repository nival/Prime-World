package 
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	

	public class StartFinishBlock extends MovieClip 
	{
		public	var	start_btn: TextButton;
		public	var	finish_btn: TextButton;
		public var CycleIndex:int;

		public function StartFinishBlock()
		{
			finish_btn.visible = false;
			start_btn.addEventListener(MouseEvent.CLICK, OnStartClick);
		}
		
		private function OnStartClick(e:MouseEvent):void 
		{
			dispatchEvent(new StartCycleEvent(CycleIndex));
			
		}
		
		public function SetState(isWorking:Boolean, isActive:Boolean):void 
		{
			start_btn.visible = !isWorking;
			finish_btn.visible = false;
		}
	}
	
}