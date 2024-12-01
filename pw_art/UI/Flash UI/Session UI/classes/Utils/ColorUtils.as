package Utils 
{
	public class ColorUtils 
	{
		public static function GetColorBySighn(value:Number,defaultColor:uint):uint
		{
			if (value < 0) return 0xFF0000;
			if (value > 0) return 0x66C62E;
			return defaultColor;
		}
				
	}

}