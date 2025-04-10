package  {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	
	
	public class PWComboboxNoResize extends MovieClip 
	{
		
		
		public function PWComboboxNoResize() {
			chatCombo_btn.addEventListener('OPEN', itemOpen);
			rowContainer.visible = false;
			frame.visible = false;
			rowMask.visible = false;
			rowMask.mouseEnabled = false;
			
			//setSize(this.width, this.height)
			
			//noSize add script
//			frame.y = chatCombo_btn.height;
//			rowContainer.y = frame.y+12;
			Text = '$Комбобокс';

		}
		public function set Text(t:String):void
		{
			chatCombo_btn.txt.text = t;
			return;
		}

		private function itemOpen(e:Event):void
		{
			e.stopPropagation();
			rowContainer.visible = !rowContainer.visible;
			frame.visible = !frame.visible;
			rowMask.visible = !rowMask.visible;
		}

	}
	
}
