package  
{
	import flash.display.MovieClip;
	
	public class ZZButton extends MovieClip 
	{
		private var buttonState:int = -1;

		private const STATE_ENABLED:int = 0;
		private const STATE_DISABLED:int = 1;
		private const STATE_PREVIEW:int = 2;
		
		private var movies:Array = new Array();
		
		private function ShowState(newState:int): void
		{
			if (buttonState != newState) 
			{
				if (buttonState != -1)
				{
					movies[buttonState].stop();
					movies[buttonState].visible = false;
				}
				
				buttonState = newState;
				movies[buttonState].visible = true;
				movies[buttonState].play();
			}
		}
		
		public function ZZButton()
		{
			var bt1 : Button_Main = new Button_Main();
			bt1.borderSymbol.mouseEnabled = false;
			movies.push( bt1 );
			addChild(movies[STATE_ENABLED]);
			movies[STATE_ENABLED].visible = false;
			
			var bt2 : Disable = new Disable();
			bt2.borderSymbol.mouseEnabled = false;
			movies.push( bt2 );
			addChild(movies[STATE_DISABLED]);
			movies[STATE_DISABLED].visible = false;
			
			var bt3 : ZZPreview = new ZZPreview();
			bt3.borderSymbol.mouseEnabled = false;
			movies.push( bt3 );
			addChild(movies[STATE_PREVIEW]);
			movies[STATE_PREVIEW].visible = false;
			
			for (var i:Number = 0; i < 3; i++) 
			{
				movies[i].x = 125;
				movies[i].y = 80;
			}
			
			EnableZZButton();
		}
		
		public function EnableZZButton(): void
		{
			trace("EnableZZButton");
			ShowState(STATE_ENABLED);
		}
		
		public function DisableZZButton(): void
		{
			trace("DisableZZButton");
			ShowState(STATE_DISABLED);
		}
		
		public function PreviewZZButton(): void
		{
			("PreviewZZButton");
			ShowState(STATE_PREVIEW);
		}
	}
	
}
