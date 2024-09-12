using System;
using System.Drawing;

namespace EditorPlugins.LayoutEditor.Background
{
	public interface IBackground
	{
		/// <summary>
		/// Draw texture on specified Graphics
		/// </summary>
		/// <param name="graphics">Graphics where texture will be drawen</param>
		/// <param name="control">Texture's contol rectangle in graphics space</param>
		/// <param name="parent">Contol's parent rectangle in graphics space (need to clip bounds)</param>
		void Draw( Graphics graphics, Rectangle control, Rectangle parent, bool isClipped );
	}
}
