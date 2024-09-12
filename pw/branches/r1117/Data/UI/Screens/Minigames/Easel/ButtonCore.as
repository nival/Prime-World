package  {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.events.Event;
	import flash.system.fscommand;
	
	public class ButtonCore extends MovieClip 
	{
		private var pressed : Boolean;
		
		public function ButtonCore() 
		{
			pressed = false;
			stateDown.visible = false;
			stateOver.visible = false;
			stateNormal.visible = true;
			glowBorder.mouseEnabled = false;
			
			this.addEventListener(MouseEvent.ROLL_OVER, onMouseOver);
			this.addEventListener(MouseEvent.ROLL_OUT, onMouseOut);
			this.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			this.addEventListener(MouseEvent.MOUSE_UP, onMouseUp);
		}
		
		public function onMouseOver( e:Event ):void
		{
			if ( pressed )
				return;
			
			trace("MOver");
			stateNormal.visible = false;
			stateOver.visible = true;
			stateDown.visible = false;
			gotoAndStop(10);
		}
		
		public function onMouseOut( e:Event ):void
		{
			if ( pressed )
				return;

			trace("MOut");
			stateNormal.visible = true;
			stateOver.visible = false;
			stateDown.visible = false;
			play();
		}
		
		public function onMouseDown( e:Event ):void
		{
			trace("MDown");
			stateNormal.visible = false;
			stateDown.visible = true;
			stateOver.visible = false;
			pressed = true;
		}
		
		public function onMouseUp( e:Event ):void
		{
			fscommand("ZZ_Boost","Inspiration");
			
			trace("MUp");
			stateNormal.visible = true;
			stateDown.visible = false;
			stateOver.visible = false;
			pressed = false;
		}
	}
}
