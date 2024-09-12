using System.Drawing;
using EditorNative.Terrain.Layers;
using EditorPlugins.Importer.Texture;
using System.IO;
using EditorLib.IO;

namespace EditorPlugins.Scene.Editors.Drawing.TerrainLayers
{
	internal sealed class LayerView : ILayerView
	{
		private readonly TerrainLayer layer;
		private readonly string layerName;
		private readonly SolidBrush colorBrush;
    private Bitmap texture = null;

    internal LayerView( TerrainLayer layer, string layerName, Color color, Bitmap texture )
		{
			this.layer = layer;
			this.layerName = layerName;
			this.colorBrush = new SolidBrush(color);
      this.texture = texture;
		}

		internal TerrainLayer Layer
		{
			get { return layer; }
		}

		#region ILayerView Members

		int ILayerView.VerticalSize
		{
			get { return 128; }
		}

		void ILayerView.Draw( Graphics graphics, Font font, Rectangle bounds )
		{
			int offset = 4;
			int side = bounds.Height - 2 * offset;

      if ( texture == null )
      {
        graphics.FillRectangle( colorBrush, new System.Drawing.Rectangle( bounds.Left + offset, bounds.Top + offset, side, side ) );
      }
      else
      {
        graphics.DrawImage( texture, new System.Drawing.Rectangle( bounds.Left + offset, bounds.Top + offset, side, side ) );
        graphics.FillRectangle( colorBrush, new System.Drawing.Rectangle( bounds.Left + offset, bounds.Top + offset, side/4, side/4 ) );
      }

			graphics.DrawString(
				layerName,
				font,
				new SolidBrush(Color.FromKnownColor(KnownColor.WindowText)),
				new RectangleF(bounds.Left + bounds.Height, bounds.Top, bounds.Width - bounds.Height, bounds.Height),
				new StringFormat() { Alignment = StringAlignment.Center, LineAlignment = StringAlignment.Center }
				);
		}

		#endregion
	}
}
