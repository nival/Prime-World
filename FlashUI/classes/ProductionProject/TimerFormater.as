package  
{
	import flash.text.TextField;
	public class TimerFormater 
	{
		private var textField:TextField
		
		public function TimerFormater(_textField:TextField) 
		{
			textField = _textField;
		}
		
		public function SetTime(time:int):void 
		{
			var minutes:int = (int)(time / 60);
			var seconds:int = time - minutes * 60;
			
			textField.text = minutes+":"+seconds;
		}
		
	}

}