using System;
using System.Drawing;

namespace EditorPlugins.LayoutEditor.Background
{
	internal abstract class BackgroundTexture : IBackground
	{
		private readonly Image texture = null;

		public BackgroundTexture( Image image ) { texture = image; }

		private bool ClampCoordinates( ref int minSrc, ref int maxSrc, ref int minDest, ref int maxDest, int minParent, int maxParent )
		{
			if ( minParent > maxDest || maxParent < minDest )
				return false;

			int minSrc2 = minSrc;
			if ( minParent > minDest )
				minSrc2 = minSrc + ( maxSrc - minSrc ) * ( minParent - minDest ) / ( maxDest - minDest );

			int maxSrc2 = maxSrc;
			if ( maxParent < maxDest )
				maxSrc2 = maxSrc - ( maxSrc - minSrc ) * ( maxDest - maxParent ) / ( maxDest - minDest );

			minDest = Math.Max( minDest, minParent );
			maxDest = Math.Min( maxDest, maxParent );
			minSrc = minSrc2;
			maxSrc = maxSrc2;

			return true;
		}

		private bool ClampRect( ref Rectangle src, ref Rectangle dest, Rectangle parent )
		{
			int leftSrc = src.Left;
			int rightSrc = src.Right;
			int leftDest = dest.Left;
			int rightDest = dest.Right;
			if ( !ClampCoordinates( ref leftSrc, ref rightSrc, ref leftDest, ref rightDest, parent.Left, parent.Right ) )
				return false;

			int topSrc = src.Top;
			int bottomSrc = src.Bottom;
			int topDest = dest.Top;
			int bottomDest = dest.Bottom;
			if ( !ClampCoordinates( ref topSrc, ref bottomSrc, ref topDest, ref bottomDest, parent.Top, parent.Bottom ) )
				return false;

			src = new Rectangle( leftSrc, topSrc, rightSrc - leftSrc, bottomSrc - topSrc );
			dest = new Rectangle( leftDest, topDest, rightDest - leftDest, bottomDest - topDest );

			return true;
		}

		protected void DrawRect( Graphics graphics, Rectangle src, Rectangle dest, Rectangle parent )
		{
			Rectangle _src = src;
			Rectangle _dest = dest;
			if ( ClampRect( ref _src, ref _dest, parent ) )
				graphics.DrawImage( texture, _dest, _src, GraphicsUnit.Pixel );
		}

		protected int Width { get { return texture.Width; } }
		protected int Height { get { return texture.Height; } }

		public abstract void Draw( Graphics graphics, Rectangle control, Rectangle parent, bool isClipped );
	}
}
