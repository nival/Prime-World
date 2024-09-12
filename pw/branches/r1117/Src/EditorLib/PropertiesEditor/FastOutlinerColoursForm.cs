using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace EditorLib.PropertiesEditor
{
  public partial class FastOutlinerColoursForm : Form
  {
    private PropertiesEditorConfig config;
    private List<Color> colours = new List<Color>();
    private SolidBrush brushText = null;
    private Font fontBold = null;

    public FastOutlinerColoursForm( IEditorWinApplication application )
    {
      InitializeComponent();

      config = application.Application.Settings.Get<PropertiesEditorConfig>();
      colours.AddRange( config.OutlinerColors );

      brushText = new SolidBrush( listBoxColours.ForeColor );
      fontBold = new Font( listBoxColours.Font, FontStyle.Bold );

      for ( int i = 0; i < colours.Count; ++i )
      {
        listBoxColours.Items.Add( "item" );
      }
    }

    private void buttonCancel_Click( object sender, EventArgs e )
    {
      Close();
    }

    private void buttonOk_Click( object sender, EventArgs e )
    {
      config.OutlinerColors = colours;
      Close();
    }

    private void listBoxColours_DrawItem( object sender, DrawItemEventArgs e )
    {
      e.DrawBackground();
      Graphics g = e.Graphics;
      SolidBrush brushBack = new SolidBrush( colours[e.Index] );
      g.FillRectangle( brushBack, e.Bounds );
      g.DrawString( string.Format( "Level {0}", e.Index ), e.Index == listBoxColours.SelectedIndex ? fontBold : e.Font, brushText, e.Bounds );
      e.DrawFocusRectangle();
    }

    private void buttonAdd_Click( object sender, EventArgs e )
    {
      colorDialog1.Color = Color.Transparent;
      if ( colorDialog1.ShowDialog() != DialogResult.OK )
        return;

      colours.Add( colorDialog1.Color );
      listBoxColours.Items.Add( "item" );
    }

    private void buttonEdit_Click( object sender, EventArgs e )
    {
      if ( listBoxColours.SelectedIndex < 0 || listBoxColours.SelectedIndex >= colours.Count )
        return;

      colorDialog1.Color = colours[listBoxColours.SelectedIndex];
      if ( colorDialog1.ShowDialog() != DialogResult.OK )
        return;

      colours[listBoxColours.SelectedIndex] = colorDialog1.Color;
      listBoxColours.Invalidate();
    }

    private void buttonRemove_Click( object sender, EventArgs e )
    {
      if ( listBoxColours.SelectedIndex < 0 || listBoxColours.SelectedIndex >= colours.Count )
        return;

      colours.RemoveAt( listBoxColours.SelectedIndex );
      listBoxColours.Items.RemoveAt( listBoxColours.Items.Count - 1 );
    }

    private void buttonUp_Click( object sender, EventArgs e )
    {
      if ( listBoxColours.SelectedIndex <= 0 || listBoxColours.SelectedIndex >= colours.Count )
        return;

      int i = listBoxColours.SelectedIndex;
      Color tmpColor = colours[i];
      colours[i] = colours[i - 1];
      colours[i - 1] = tmpColor;
      --listBoxColours.SelectedIndex;
    }

    private void buttonDown_Click( object sender, EventArgs e )
    {
      if ( listBoxColours.SelectedIndex < 0 || listBoxColours.SelectedIndex >= colours.Count - 1 )
        return;

      int i = listBoxColours.SelectedIndex;
      Color tmpColor = colours[i];
      colours[i] = colours[i + 1];
      colours[i + 1] = tmpColor;
      ++listBoxColours.SelectedIndex;
    }

    private void listBoxColours_SelectedIndexChanged( object sender, EventArgs e )
    {
      listBoxColours.Invalidate();
    }

    private void listBoxColours_DoubleClick( object sender, EventArgs e )
    {
      buttonEdit_Click( sender, e );
    }
  }
}
