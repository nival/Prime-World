using System;
using System.Drawing;

namespace EditorPlugins.LayoutEditor.Background
{
	internal sealed class BackgroundSolid : IBackground
	{
		private Color color;

		public BackgroundSolid()
		{
			color = Color.DarkGoldenrod;
		}

		public BackgroundSolid( Color color )
		{
			this.color = color;
		}

		public void Draw( Graphics graphics, Rectangle control, Rectangle parent, bool isClipped )
		{
			Point topLeft = new Point(control.Left,control.Top);
			Point bottomRight = new Point(control.Right, control.Bottom);
			if (isClipped)
			{
				topLeft = new Point(Math.Max(control.Left, parent.Left), Math.Max(control.Top, parent.Top));
				bottomRight = new Point(Math.Min(control.Right, parent.Right), Math.Min(control.Bottom, parent.Bottom));
			}
						
			Rectangle dest = new Rectangle( topLeft.X, topLeft.Y, bottomRight.X - topLeft.X, bottomRight.Y - topLeft.Y );

			graphics.FillRectangle( new SolidBrush( Color.FromArgb( 128, color ) ), dest );
			
			graphics.DrawRectangle( new Pen( Color.DarkGoldenrod, 1.0f ), dest );

		}
	}
}
