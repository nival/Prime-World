package src
{
	import flash.display.DisplayObject;
	import flash.filters.ColorMatrixFilter;

	public class Desaturate
	{
		private static var desaturate_arr:Array = [
		0.3, 0.6, 0.1, 0.0, 0.0,
		0.3, 0.6, 0.1, 0.0, 0.0,
		0.3, 0.6, 0.1, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0, 0.0
		];
		
		private static var saturate_arr:Array = [1,0,0,0,0,
												 0,1,0,0,0,
												 0,0,1,0,0,
												 0,0,0,1,0]

		private static var desaturateCMF:ColorMatrixFilter = new ColorMatrixFilter(desaturate_arr);
		private static var saturateCMF:ColorMatrixFilter = new ColorMatrixFilter(saturate_arr);

		public static function desaturate(target:DisplayObject):void
		{
			//TODO по хорошему нужно пушить этот фильтр к существующему массиву, чтобы не затереть существующие.
			//впринципе пока не актуально - на объект не накладывается больше 1 фильтра во всем UI, но все же так неправильно.
			target.filters=[desaturateCMF];
		}
		public static function saturate(target:DisplayObject):void
		{
			//TODO по хорошему нужно обойти циклом массив фильтров объекта, найти в нем desaturate_arr и удалить его, а то т.о. можно случайно потереть другой фильтр.
			target.filters=[saturateCMF];
		}
	}
}