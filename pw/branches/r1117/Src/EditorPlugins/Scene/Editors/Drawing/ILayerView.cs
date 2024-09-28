using System.Drawing;

namespace EditorPlugins.Scene.Editors.Drawing
{
	internal interface ILayerView
	{
		int VerticalSize { get; }
		void Draw( Graphics graphics, Font font, Rectangle bounds );
	}
}
