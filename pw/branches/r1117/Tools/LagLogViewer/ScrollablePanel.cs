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
  public partial class ScrollablePanel : Panel
  {
    private Point rememberedLocation;

    public ScrollablePanel()
    {
      InitializeComponent();
    }

    protected override void OnScroll( ScrollEventArgs se )
    {
      base.OnScroll( se );
      rememberedLocation.X = this.DisplayRectangle.X;
      rememberedLocation.Y = this.DisplayRectangle.Y;
    }

    protected override Point ScrollToControl( Control activeControl )
    {
      return rememberedLocation;
    }

  }
}
