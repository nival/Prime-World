using System;
using System.Drawing;

namespace EditorPlugins.LayoutEditor.Background
{
	internal sealed class BackgroundGrid : IBackground
	{
		private readonly Color[] colors = new Color[2] { Color.LightGray, Color.White };
		private readonly int gridSize = 8;

		public void Draw( Graphics graphics, Rectangle control, Rectangle parent, bool isClipped )
		{
			Point topLeft = new Point( Math.Max( control.Left, parent.Left ), Math.Max( control.Top, parent.Top ) );
			Point bottomRight = new Point( Math.Min( control.Right, parent.Right ), Math.Min( control.Bottom, parent.Bottom ) );
			Rectangle dest = new Rectangle( topLeft.X, topLeft.Y, bottomRight.X - topLeft.X - 1, bottomRight.Y - topLeft.Y - 1 );

			Brush[] brushes = new Brush[2] { new SolidBrush( colors[0] ), new SolidBrush( colors[1] ) };
			int rowBrush = 0;
			Rectangle draw = new Rectangle( dest.Left, dest.Left, gridSize, gridSize );
			while ( draw.Y < dest.Bottom )
			{
				draw.X = dest.Left;
				draw.Width = gridSize;
				int colBrush = rowBrush;
				if ( draw.Y + gridSize > dest.Bottom )
					draw.Height = dest.Bottom - draw.Y + 1;
				while ( draw.X < dest.Right )
				{
					if ( draw.X + gridSize > dest.Right )
						draw.Width = dest.Right - draw.X + 1;
					graphics.FillRectangle( brushes[colBrush], draw );
					draw.X += gridSize;
					colBrush = 1 - colBrush;
				}
				rowBrush = 1 - rowBrush;
				draw.Y += gridSize;
			}
		}
	}
}
