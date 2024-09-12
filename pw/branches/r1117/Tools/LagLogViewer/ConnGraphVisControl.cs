using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TrackVis
{
  public partial class ConnGraphVisControl : UserControl
  {
    public ConnGraphVisControl()
    {
      InitializeComponent();
    }

    private Dataset data = null;
    public Dataset Dataset { get { return data; } set { data = value; RepositionNodes(); } }

    public string SelectedTrack = string.Empty;
    public bool SwapLineHalves = false;

    private float timeStep = 0.1f;

    private bool playing = false;
    public bool Playing
    {
      get { return playing; }
      set 
      {
        if ( playing != value )
        {
          playing = value;
          if ( playing )
            timerAnim.Start();
          else
            timerAnim.Stop();
        }
      }
    }

    private Pen linePen = new Pen( Color.Blue, 3 );
    private Pen labelPen = new Pen( Color.Black );
    private Brush labelBrush = new SolidBrush( Color.Black );
    private Brush labelBgBrush = new SolidBrush( Color.White );
    private SolidBrush labelStatsBrush = new SolidBrush( Color.Black );

    private void RepositionNodes()
    {
      if ( null == data || data.NodeCount < 2 )
        return;

      float xc = this.Width / 2;
      float yc = this.Height / 2;
      float r = Math.Min( xc, yc );
      if ( r > 100 )
        r -= 30;

      float step = (float)Math.PI * 2 / data.NodeCount;
      for ( int i = 0; i < data.NodeCount; ++i )
      {
        data.nodes[i].nodeLocation.X = (int)( xc + r * Math.Sin( i * step ) );
        data.nodes[i].nodeLocation.Y = (int)( yc + r * Math.Cos( i * step ) );
      }
    }

    protected override void OnPaint( PaintEventArgs e )
    {
      base.OnPaint( e );
      Graphics g = e.Graphics;
      for( int i = 0; i < data.nodes.Count; ++i )
      {
        NodeData node = data.nodes[i];
        for ( int j = 0; j < node.connections.Length; ++j )
        {
          TrackBunchDesc bunch = node.connections[j];
          if ( null == bunch )
            continue;
          if ( bunch.tracks.ContainsKey( SelectedTrack ) )
            DrawConnectionHalf( g, bunch.tracks[SelectedTrack], node, data.nodes[j] );
        }
      }

      for ( int i = 0; i < data.NodeCount; ++i )
      {
        NodeData node = data.nodes[i];

        PaintNodeFrame( g, node );
      }

      PaintLegend( g );
    }

    private void PaintLegend( Graphics g )
    {
      Rectangle rect = new Rectangle();

      rect.Width = 60;
      rect.Height = this.FontHeight * ( data.flagTypes.Count + 1 ) + 4;
      rect.X = this.Width - rect.Width;
      rect.Y = this.Height - rect.Height;

      g.FillRectangle( labelBgBrush, rect );
      g.DrawRectangle( labelPen, rect );
      g.DrawString( "Flags:", this.Font, labelBrush, rect.X + 2, rect.Y + 2 );

      int y = rect.Y + 2 + this.FontHeight;
      foreach ( var item in data.flagTypes )
      {
        labelStatsBrush.Color = item.Value;
        g.FillRectangle( labelStatsBrush, rect.X + 2, y + 1, this.FontHeight - 2, this.FontHeight - 2 );
        g.DrawString( item.Key, this.Font, labelBrush, rect.X + 2 + this.FontHeight, y );

        y += this.FontHeight;
      }
    }

    private void PaintNodeFrame( Graphics g, NodeData node )
    {
      SizeF labelSize = g.MeasureString( node.nodeId, this.Font );
      labelSize.Height += this.FontHeight * node.tracks.Count;
      if ( labelSize.Width < 50 )
        labelSize.Width = 50;

      PointF labelPt = new PointF();
      labelPt.X = node.nodeLocation.X - labelSize.Width / 2;
      labelPt.Y = node.nodeLocation.Y - labelSize.Height / 2;
      g.FillRectangle( labelBgBrush, labelPt.X - 2, labelPt.Y - 2, labelSize.Width + 4, labelSize.Height + 4 );
      g.DrawRectangle( labelPen, labelPt.X - 2, labelPt.Y - 2, labelSize.Width + 4, labelSize.Height + 4 );
      g.DrawString( node.nodeId, this.Font, labelBrush, labelPt );

      float y = labelPt.Y + this.FontHeight;
      foreach ( var item in node.tracks )
      {
        TrackTypeDesc desc = data.GetTrackVisDesc( item.Key );
        labelStatsBrush.Color = desc.Color;
        g.DrawString( GetTrackValue( item.Value ).ToString( "F0" ), this.Font, labelStatsBrush, labelPt.X, y );
        y += this.FontHeight;
      }

      y = labelPt.Y + this.FontHeight - 5;
      foreach ( var item in data.flagTypes )
      {
        y += 5;
        if ( !node.IsFlagOn( item.Key, data.CurrentTime ) )
          continue;

        labelStatsBrush.Color = item.Value;
        g.FillRectangle( labelStatsBrush, labelPt.X + labelSize.Width - 2, y, 4, 4 );
      }
    }

    private void DrawConnectionHalf( Graphics g, TrackDesc trackDesc, NodeData fromNode, NodeData toNode )
    {
      float xm = ( fromNode.nodeLocation.X + toNode.nodeLocation.X ) / 2;
      float ym = ( fromNode.nodeLocation.Y + toNode.nodeLocation.Y ) / 2;
      float x0 = fromNode.nodeLocation.X;
      float y0 = fromNode.nodeLocation.Y;


      float trackValue = GetTrackValue( trackDesc );
      linePen.Color = GetColorByValue( trackValue );
      if ( SwapLineHalves )
      {
        x0 = toNode.nodeLocation.X;
        y0 = toNode.nodeLocation.Y;
      }
      g.DrawLine( linePen, x0, y0, xm, ym );

      string label = trackValue.ToString( "F0" );
      SizeF labelSize = g.MeasureString( label, this.Font );
      PointF labelPt = new PointF();
      labelPt.X = ( x0 * 0.7f + xm * 0.3f ) - labelSize.Width / 2;
      labelPt.Y = ( y0 * 0.7f + ym * 0.3f ) - labelSize.Height / 2;
      g.FillRectangle( labelBgBrush, labelPt.X - 2, labelPt.Y - 2, labelSize.Width + 4, labelSize.Height + 4 );
      g.DrawString( label, this.Font, labelBrush, labelPt );
    }

    private float GetTrackValue( TrackDesc trackDesc )
    {
      float trackValue = trackDesc.data[0];
      for ( int i = 0; i < trackDesc.times.Count; ++i )
      {
        if ( trackDesc.times[i] > data.CurrentTime )
          break;
        trackValue = trackDesc.data[i];
      }
      return trackValue;
    }

    protected override void OnResize( EventArgs e )
    {
      base.OnResize( e );
      RepositionNodes();
    }

    private Color GetColorByValue( float value )
    {
      Color stage0 = Color.Green;
      Color stage1 = Color.Yellow;
      Color stage2 = Color.Red;
      float splitFactor = 1000;
      int r, g, b;
      float scaledValue = ( value < 0 ) ? 0 : value;
      scaledValue /= 100;
      splitFactor /= 100;
      scaledValue = 1 - 1 / ( scaledValue + 1 );
      splitFactor = 1 - 1 / ( splitFactor + 1 );
      if ( scaledValue > splitFactor )
      {
        scaledValue = ( scaledValue - splitFactor ) / ( 1 - splitFactor );
        
        r = (byte)( stage2.R * scaledValue + stage1.R * ( 1 - scaledValue ) );
        g = (byte)( stage2.G * scaledValue + stage1.G * ( 1 - scaledValue ) );
        b = (byte)( stage2.B * scaledValue + stage1.B * ( 1 - scaledValue ) );
      }
      else
      {
        scaledValue /= splitFactor;

        r = (byte)( stage1.R * scaledValue + stage0.R * ( 1 - scaledValue ) );
        g = (byte)( stage1.G * scaledValue + stage0.G * ( 1 - scaledValue ) );
        b = (byte)( stage1.B * scaledValue + stage0.B * ( 1 - scaledValue ) );
      }

      return Color.FromArgb( r, g, b );
    }

    private void timerAnim_Tick( object sender, EventArgs e )
    {
      data.CurrentTime += timeStep;
      if ( data.CurrentTime >= data.Length )
      {
        data.CurrentTime = data.Length;
        Playing = false;
      }

      Invalidate();
    }

  }
}
