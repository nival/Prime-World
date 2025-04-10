package  {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	
	
	public class PWDialogUI extends MovieClip 
	{
		public var hero_01:MovieClip;
		public var hero_02:MovieClip;
		public var buttonsPanelFrame_cmp:MovieClip;
		
		private const STARTLINE:int = 620;
		
		public function PWDialogUI() 
		{			
			hero_01.y = STARTLINE;
			hero_01.posY = y;
			hero_02.y = hero_01.y + hero_01.END - hero_02.START;
			
			stage.addEventListener(MouseEvent.CLICK, onClick);
		}
		
		private function onClick(e:MouseEvent):void
		{
			hero_01.Show();
		}
	}
}
