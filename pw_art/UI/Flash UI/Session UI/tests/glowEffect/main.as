package
{
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;

	public class main extends MovieClip
	{
		private var isGlowAdded:Boolean = false;
		private var canBuyGlow_mc:CanBuyGlowEffect;
		
		public function main()
		{
			this.stop();
			
			this.addEventListener(Event.ADDED_TO_STAGE, OnAdded);
			
			function OnAdded(e:Event)
			{
				stage.addEventListener(MouseEvent.CLICK, ClickStage);
			}
			
		}
		
		
		
		private function ClickStage(e:MouseEvent):void
		{
			isGlowAdded? RemoveCanBuyEffect():ApplyCanBuyEffect();
			isGlowAdded = !isGlowAdded;
		}
		
		private function ApplyCanBuyEffect():void
		{
			if (canBuyGlow_mc != null)
				return;
			
			canBuyGlow_mc = new CanBuyGlowEffect();
			//this.addChildAt(canBuyGlow_mc, 0);
		}
		
		private function RemoveCanBuyEffect():void
		{ 
			if (canBuyGlow_mc == null) return;
			
			//this.removeChild(canBuyGlow_mc);
			canBuyGlow_mc = null;
		}
	}
}