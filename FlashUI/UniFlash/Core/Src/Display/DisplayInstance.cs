using System;

namespace Flash
{
	public class DisplayInstance
	{
		public DisplayObject DisplayObject { get; set; }
		public Transform Transform { get; set; }

		public DisplayInstance( DisplayObject obj, Transform data )
		{
			DisplayObject = obj;
			Transform = data;
		}
	}
}
