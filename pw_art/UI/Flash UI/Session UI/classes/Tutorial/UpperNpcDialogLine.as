package Tutorial 
{
	import fl.transitions.Tween;
	import flash.events.Event;
	public class UpperNpcDialogLine extends BaseNpcCinematicDialog
	{
		public function UpperNpcDialogLine() 
		{
			startDialogYPosition = -this.height;
			endDialogYPosition = 0;
			this.y = startDialogYPosition;
			super();
		}
		
		override protected function BaseBarObjectResize(e:Event = null):void 
		{
			startDialogYPosition = -this.height;
			super.BaseBarObjectResize(e);
		}
	}
}