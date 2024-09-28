package  {
	
	import flash.display.SimpleButton;
	import flash.events.MouseEvent;
	import flash.system.fscommand;
	
	public class button_core extends SimpleButton 
	{
				
		public function button_core() 
		{
			addEventListener(flash.events.MouseEvent.CLICK, OnButtonClick);
		}
		
		private function OnButtonClick():void
		{
			fscommand("ZZ_Boost","Inspiration");
		}
	}
	
}
