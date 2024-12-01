package Tutorial 
{
	import Components.ButtonRound;
	import flash.display.MovieClip;
	
	public class CooldownButtonRound  extends ButtonRound
	{
		public var coolDown_mc:MovieClip;
		
		public function CooldownButtonRound() 
		{
			super();
			coolDown_mc.mouseEnabled = false;
			coolDown_mc.mouseChildren = false;
		}
		
		public function startWaitingAnim():void 
		{
			coolDown_mc.visible = true;
			coolDown_mc.gotoAndPlay(2);
		}
		
		public function stopWaitingAnim():void 
		{
			coolDown_mc.gotoAndStop(1);
			coolDown_mc.visible = false;
		}
	}
}