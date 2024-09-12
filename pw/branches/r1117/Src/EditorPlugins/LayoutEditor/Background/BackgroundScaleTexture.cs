using System;
using System.Drawing;

namespace EditorPlugins.LayoutEditor.Background
{
	internal sealed class BackgroundScaleTexture: BackgroundTexture
	{
		public BackgroundScaleTexture( Image image ) : base( image ) { }

		public override void Draw( Graphics graphics, Rectangle control, Rectangle parent, bool isClipped )
		{
			Rectangle image = new Rectangle( 0, 0, Math.Min( Width, control.Width ), Math.Min( Height, control.Height ) );
			//DrawRect(graphics, image, control, parent);
			DrawRect(graphics, new Rectangle(0, 0, Width, Height), new Rectangle(control.X, control.Y, control.Width, control.Height), parent);
		}
	}
}
