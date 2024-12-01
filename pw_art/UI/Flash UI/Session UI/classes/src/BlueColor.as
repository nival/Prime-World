package src
{
	import flash.display.DisplayObject;
	import flash.filters.ColorMatrixFilter;

	public class BlueColor
	{

		private static var blue_arr:Array = [
		0.3,0.6,0.1,0.0,0.0,
		0.3,0.6,0.1,0.0,0.0,
		0.8,0.8,0.8,0.2,0.0,
		0.0,0.0,0.0,1.0,0.0
		];

		private static var blueCMF:ColorMatrixFilter = new ColorMatrixFilter(blue_arr);

		public static function onBlue(target:DisplayObject):void
		{
			target.filters=[blueCMF];
		}
		public static function unBlue(target:DisplayObject):void
		{
			target.filters=[];
		}
	}
}