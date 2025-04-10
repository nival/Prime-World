package  {
	
	import flash.display.MovieClip;
	import flash.events.Event;
	
	
	public class PWCombobox extends MovieClip 
	{		
		public function PWCombobox() 
		{
			chatCombo_btn.addEventListener('OPEN', itemOpen);
			rowContainer.visible = false;
			frame.visible = false;
			rowMask.visible = false;
			
			setSize(this.width, this.height)
		}
		public function setSize(_w:Number, _h:Number)
		{
			chatCombo_btn.setSize(_w, _h);
			
			rowContainer.y = _h+12;
			rowContainer.row_btn.setSize(_w - 6, rowContainer.row_btn.height);
			
			frame.y = _h;
			frame.setSize(_w, rowContainer.height+24);
			
			rowMask.y = rowContainer.y;
			rowMask.width = rowContainer.width;
			rowMask.height = rowContainer.height;
			
			this.scaleX = 1;
			this.scaleY = 1;

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
