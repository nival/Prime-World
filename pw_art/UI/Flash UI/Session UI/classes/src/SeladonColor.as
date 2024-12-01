package src
{
	import flash.display.DisplayObject;
	import flash.filters.ColorMatrixFilter;

	public class SeladonColor
	{

		private static var seladon_arr:Array = [0.43,0.56,0,0,-59,0.43,0.62,0.1,0.04,-49,0.5,0.54,0.51,0,-77,0,0,0,1,-117];

		private static var seladonCMF:ColorMatrixFilter = new ColorMatrixFilter(seladon_arr);

		public static function seladon(target:DisplayObject):void
		{
			target.filters=[seladonCMF];
		}
		public static function saturate(target:DisplayObject):void{
			target.filters=[];
		}
	}
}