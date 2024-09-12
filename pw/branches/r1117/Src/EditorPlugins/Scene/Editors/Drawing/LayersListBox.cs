using System.Windows.Forms;

namespace EditorPlugins.Scene.Editors.Drawing
{
	internal sealed class LayersListBox : ListBox
	{
		internal LayersListBox()
		{
			Dock = DockStyle.Fill;
			DrawMode = DrawMode.OwnerDrawVariable;
		}

		internal ILayerView[] Layers
		{
			set
			{
				BeginUpdate();
				{
					Items.Clear();
					if ( !ReferenceEquals( value, null ) )
					{
						Items.AddRange( (object[])value );
					}
					if ( Items.Count > 0 )
					{
						SelectedIndex = 0;
					}
				}
				EndUpdate();
			}
		}

		protected override void OnMeasureItem( MeasureItemEventArgs e )
		{
			if ( e.Index >= 0 )
			{
				e.ItemHeight = ((ILayerView)Items[e.Index]).VerticalSize;
			}
		}

		protected override void OnDrawItem( DrawItemEventArgs e )
		{
			if ( e.Index >= 0 )
			{
				e.DrawBackground();
				e.DrawFocusRectangle();

				((ILayerView)Items[e.Index]).Draw( e.Graphics, e.Font, e.Bounds );
			}
		}
	}
}
