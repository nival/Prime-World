using System.Drawing;
using Northwoods.Go;

namespace EditorPlugins.Editors.AnimGraph
{
	public class GoNodeExtended : GoBasicNode
	{
		public Font ownerFont;

		public override void Paint( Graphics g, GoView view )
		{
      Node node = UserObject as Node;
      if ( node != null && node.Name != Text )
        Text = node.Name;

			base.Paint( g, view );
			PaintIcons( g );
		}

		private void PaintIcons( Graphics g )
		{
      Node node = (UserObject as Node);
			int playingIndex = node.Context.Controller.GetCurTargetNode();

			if ( node is RandomNode )
				g.DrawImage( EditorPluginResources.AnimComplex, Left - 3, Top - 3, 16, 16 );
			if ( node.Looped )
				g.DrawImage( EditorPluginResources.AnimLooped, Right - 16 + 3, Top - 3, 16, 16 );
			if (playingIndex == node.AnGrNodeIndex )
				g.DrawImage( EditorPluginResources.AnimPlayed, Left + ( Right - Left ) / 2 - 8, Top - 3, 16, 16 );
			if ( node.PlayIndex > 0 )
			{
				g.DrawImage( EditorPluginResources.AnimIndex, Right - 16, Bottom - 16, 16, 16 );
				Brush b = new SolidBrush( System.Drawing.Color.Black );
				StringFormat f = new StringFormat {LineAlignment = StringAlignment.Center, Alignment = StringAlignment.Center};
				g.DrawString( node.PlayIndex.ToString(), ownerFont, b, new RectangleF( Right - 16, Bottom - 16, 16, 16 ), f );
			}
		}
	}
}
