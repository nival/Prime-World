using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TrackVis
{
  public partial class LegendItemControl : UserControl
  {
    private Brush brush = null;
    private Pen crossPen = new Pen( Color.White, 2 );

    private bool crossedOut = false;
    public bool CrossedOut { get { return crossedOut; } set { crossedOut = value; Invalidate(); } }

    public new string Text { get { return label.Text; } }

    public LegendItemControl( string name, Color colour )
    {
      InitializeComponent();

      label.Text = name;
      brush = new SolidBrush( colour );
    }

    protected override void OnPaint( PaintEventArgs e )
    {
      base.OnPaint( e );
      e.Graphics.FillRectangle( brush, 2, 2, 16, 16 );
      if ( crossedOut )
      {
        e.Graphics.DrawLine( crossPen, 0, 0, 18, 18 );
        e.Graphics.DrawLine( crossPen, 18, 0, 0, 18 );
      }
    }
  }
}
