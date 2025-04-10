package  
{
	import flash.text.TextField;
	public class TextButton extends MyButton 
	{
		
		public var txt:TextField;
		
		public function TextButton() 
		{
			
		}
		
		public function set Text(value:String):void
		{
			txt.text = value;
		}
		
		public function get Text():String
		{
			return txt.text;
		}
	}
}