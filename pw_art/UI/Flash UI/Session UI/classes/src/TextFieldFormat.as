package src
{
	import flash.text.TextField;
	import flash.text.TextFormat;

	public class TextFieldFormat
	{

		static public function Format(target:TextField, size:uint=15,color:uint = 0xffffff,font:String = "New Times Roman")
		{
			target.selectable = false;
			var format:TextFormat = new TextFormat();
			format.font = font;
			format.color = 0xFFFFFF;
			format.size = size;
			target.defaultTextFormat = format;
		}
	}
}