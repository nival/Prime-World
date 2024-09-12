using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using NPlot.Windows;
using System.Collections;
using System.IO;
using System.Globalization;

namespace TrackVis
{
  public partial class TrackVisForm : Form
  {
    private class FilterItem
    {
      public string Name = string.Empty;
      public string Value = string.Empty;
      public override string ToString() { return Name; }
      public FilterItem( string _name, string _value )
      {
        Name = _name;
        Value = _value;
      }
    }

    private float BrowseStart = 0.0f;
    private float BrowseLength = 1000.0f;
    private int ZoomLevel = 0;
    private string filterFrom = string.Empty;
    private string filterTo = string.Empty;

    private List<PlotSurface2D> allPlotControls = new List<PlotSurface2D>();

    private Dataset data = new Dataset();

    public TrackVisForm()
    {
      InitializeComponent();
      connGraphVis.Dataset = data;
      this.MouseWheel += new MouseEventHandler( ScrollablePanel_MouseWheel );
    }

    private void openToolStripMenuItem_Click( object sender, EventArgs e )
    {
      DialogResult result = openFileDialog.ShowDialog();
      if ( result != DialogResult.OK )
        return;

      RemoveAllTracks();
      data.ReadFiles( openFileDialog.FileNames );
      CreateTrackControls();

      FillFilterCombos();

      hScrollBrowse.Maximum = (int)data.Length;
      hScrollBrowse.LargeChange = (int)BrowseLength;
      hScrollBrowse.Enabled = true;

      connGraphVis.Dataset = data;

      foreach ( string trackName in data.trackTypes.Keys )
      {
        comboSelectLeftGraph.Items.Add( trackName );
      }
      if ( comboSelectLeftGraph.Items.Count > 0 )
        comboSelectLeftGraph.SelectedIndex = 0;

    }

    private void CreateTrackControls()
    {
      tracksPanel.SuspendLayout();
      int y = 0;

      foreach ( NodeData node in data.nodes )
      {
        if ( filterFrom != string.Empty && node.nodeId != filterFrom )
          continue;

        if ( filterTo != string.Empty && node.nodeId != filterTo )
          continue;

        node.control = new PlotSurface2D();
        node.control.Title = "Local data: " + node.nodeId;

        foreach ( var eventSet in node.events )
        {
          TrackTypeDesc desc = data.GetEventDesc( eventSet.Key );
          if ( !desc.IsOn )
            continue;

          foreach ( Event item in eventSet.Value )
          {
            node.control.Add( new NPlot.VerticalLine( item.time, desc.Color ) );
          }
        }

        y += CreateSinglePlotControl( y, node.control, node.tracks );

        if ( node.ySize >= 0 )
          node.control.YAxis1.WorldMax = node.ySize;
        else
          node.ySize = node.control.YAxis1.WorldMax;
      }

      foreach ( var item in data.eventTypes )
        AddToLegendEvents( item.Value );

      foreach ( TrackBunchDesc track in data.tracks )
      {
        if ( filterFrom != string.Empty && track.nodeFrom != filterFrom )
          continue;

        if ( filterTo != string.Empty && track.nodeTo != filterTo )
          continue;

        track.control = new PlotSurface2D();
        track.control.Title = "From " + track.nodeFrom.ToString() + " to " + track.nodeTo.ToString();

        y += CreateSinglePlotControl( y, track.control, track.tracks );

        if ( track.ySize >= 0 )
          track.control.YAxis1.WorldMax = track.ySize;
        else
          track.ySize = track.control.YAxis1.WorldMax;
      }
      tracksPanel.ResumeLayout();
      UpdateTrackBrowseParams();
    }

    private int CreateSinglePlotControl( int y, PlotSurface2D control, Dictionary<string, TrackDesc> tracks )
    {
      bool emptyControl = true;
      foreach ( string trackName in tracks.Keys )
      {
        TrackDesc item = tracks[trackName];
        TrackTypeDesc desc = data.GetTrackVisDesc( trackName );
        if ( !desc.IsOn )
          continue;

        AddToLegend( desc );

        emptyControl = false;
        NPlot.LinePlot lp = new NPlot.LinePlot( item.data, item.times );
        lp.Color = desc.Color;
        control.Add( lp );
      }

      if ( emptyControl )
      {
        NPlot.LinePlot lp = new NPlot.LinePlot();
        control.Add( lp );
      }

      control.XAxis1.WorldMin = BrowseStart;
      control.XAxis1.WorldMax = BrowseStart + BrowseLength;
      control.YAxis1.TickTextNextToAxis = false;
      control.YAxis1.WorldMin = 0;
      control.Top = y;
      control.Left = 0;
      control.Width = tracksPanel.Width - 20;
      control.Height = 250;

      control.Padding = 2;

      control.Add( data.SyncLine );
      control.MouseUp += new MouseEventHandler( TrackGraph_MouseUp );
      control.MouseWheel += new MouseEventHandler( ScrollablePanel_MouseWheel );

      tracksPanel.Controls.Add( control );

      allPlotControls.Add( control );

      return control.Height;
    }

    private void AddToLegend( TrackTypeDesc desc )
    {
      if ( flowLegend.Controls.Contains( desc.LegendItem ) )
        return;

      flowLegend.Controls.Add( desc.LegendItem );
      desc.LegendItem.MouseClick += new MouseEventHandler( LegendItem_MouseClick );
    }

    private void AddToLegendEvents( TrackTypeDesc desc )
    {
      if ( flowLegendEvents.Controls.Contains( desc.LegendItem ) )
        return;

      flowLegendEvents.Controls.Add( desc.LegendItem );
      desc.LegendItem.MouseClick += new MouseEventHandler( LegendEventItem_MouseClick );
    }

    private void RemoveAllTracks()
    {
      RemoveAllTrackControls();
      data.Clear();
      BrowseStart = 0.0f;
      BrowseLength = 1000.0f;
      ZoomLevel = 0;
      comboFrom.Items.Clear();
      comboTo.Items.Clear();
      comboSelectLeftGraph.Items.Clear();
      hScrollBrowse.Enabled = false;
      flowLegend.Controls.Clear();
      flowLegendEvents.Controls.Clear();
    }

    private void RemoveAllTrackControls()
    {
      tracksPanel.Controls.Clear();

      allPlotControls.Clear();

      foreach ( TrackBunchDesc item in data.tracks )
        item.control = null;

      foreach ( NodeData node in data.nodes )
        node.control = null;
    }

    private void FillFilterCombos()
    {
      comboFrom.Items.Add( new FilterItem( "From All", string.Empty ) );
      comboFrom.SelectedIndex = 0;
      comboTo.Items.Add( new FilterItem( "To All", string.Empty ) );
      comboTo.SelectedIndex = 0;
      foreach( string item in data.nodeMap.Keys )
      {
        comboFrom.Items.Add( new FilterItem( "From "+ item.ToString(), item ) );
        comboTo.Items.Add( new FilterItem( "To " + item.ToString(), item ) );
      }
    }

    #region Event handlers

    private void exitToolStripMenuItem_Click( object sender, EventArgs e )
    {
      Close();
    }

    private void buttonPlay_Click( object sender, EventArgs e )
    {
      if ( timerRefreshProgress.Enabled )
      {
        timerRefreshProgress.Stop();
        connGraphVis.Playing = false;
        buttonPlay.Text = "Play";
      }
      else
      {
        timerRefreshProgress.Start();
        connGraphVis.Playing = true;
        buttonPlay.Text = "Pause";
      }
    }

    private void timerRefreshProgress_Tick( object sender, EventArgs e )
    {
      if ( !connGraphVis.Playing )
      {
        data.CurrentTime = 0;
        timerRefreshProgress.Stop();
        buttonPlay.Text = "Play";
      }
      RefreshTimes();
    }

    private void RefreshTimes()
    {
      textBoxTimes.Text = data.CurrentTime.ToString( "F02" ) + " / " + data.Length.ToString( "F02" );
      if ( data.Length == 0 )
        hScrollBarPlay.Value = 0;
      else
        hScrollBarPlay.Value = (int)( data.CurrentTime / data.Length * hScrollBarPlay.Maximum );
    }

    private void hScrollBarPlay_Scroll( object sender, ScrollEventArgs e )
    {
      data.CurrentTime = data.Length * hScrollBarPlay.Value / hScrollBarPlay.Maximum;
      RefreshTimes();
      connGraphVis.Invalidate();
    }

    private void comboFrom_SelectedIndexChanged( object sender, EventArgs e )
    {
      FilterItem filter = comboFrom.SelectedItem as FilterItem;
      if ( null == filter || filterFrom == filter.Value )
        return;
      
      filterFrom = filter.Value;
      RemoveAllTrackControls();
      CreateTrackControls();
    }

    private void comboTo_SelectedIndexChanged( object sender, EventArgs e )
    {
      FilterItem filter = comboTo.SelectedItem as FilterItem;
      if ( null == filter || filterTo == filter.Value )
        return;

      filterTo = filter.Value;
      RemoveAllTrackControls();
      CreateTrackControls();
    }

    private void buttonZoomIn_Click( object sender, EventArgs e )
    {
      if ( ZoomLevel >= 10 ) 
        return;

      ++ZoomLevel;
      BrowseLength /= 2;
      hScrollBrowse.LargeChange = (int)BrowseLength;
      UpdateTrackBrowseParams();
    }

    private void buttonZoomOut_Click( object sender, EventArgs e )
    {
      if ( ZoomLevel <= -10 )
        return;

      --ZoomLevel;
      BrowseLength *= 2;
      hScrollBrowse.LargeChange = (int)BrowseLength;
      UpdateTrackBrowseParams();
    }

    private void hScrollBrowse_Scroll( object sender, ScrollEventArgs e )
    {
      BrowseStart = hScrollBrowse.Value;
      UpdateTrackBrowseParams();
    }

    private void UpdateTrackBrowseParams()
    {
      foreach ( PlotSurface2D control in allPlotControls )
      {
        control.XAxis1.WorldMin = BrowseStart;
        control.XAxis1.WorldMax = BrowseStart + BrowseLength;
        control.Invalidate();
      }
    }

    private void TrackVisForm_Resize( object sender, EventArgs e )
    {
      foreach ( PlotSurface2D control in allPlotControls )
        control.Width = tracksPanel.Width - 20;
    }

    private void comboSelectLeftGraph_SelectedIndexChanged( object sender, EventArgs e )
    {
      connGraphVis.SelectedTrack = comboSelectLeftGraph.SelectedItem.ToString();
      connGraphVis.Invalidate();
    }

    private void cbOppositeLines_CheckedChanged( object sender, EventArgs e )
    {
      connGraphVis.SwapLineHalves = cbOppositeLines.Checked;
      connGraphVis.Invalidate();
    }

    private void buttonVZoomIn_Click( object sender, EventArgs e )
    {
      foreach ( TrackBunchDesc track in data.tracks )
      {
        if ( null == track.control )
          continue;

        track.control.YAxis1.WorldMax /= 2;
        track.ySize = track.control.YAxis1.WorldMax;
        track.control.Invalidate();
      }

      foreach ( NodeData node in data.nodes )
      {
        if ( null == node.control )
          continue;

        node.control.YAxis1.WorldMax /= 2;
        node.ySize = node.control.YAxis1.WorldMax;
        node.control.Invalidate();
      }
    }

    private void buttonVZoomOut_Click( object sender, EventArgs e )
    {
      foreach ( TrackBunchDesc track in data.tracks )
      {
        if ( null == track.control )
          continue;

        track.control.YAxis1.WorldMax *= 2;
        track.ySize = track.control.YAxis1.WorldMax;
        track.control.Invalidate();
      }

      foreach ( NodeData node in data.nodes )
      {
        if ( null == node.control )
          continue;

        node.control.YAxis1.WorldMax *= 2;
        node.ySize = node.control.YAxis1.WorldMax;
        node.control.Invalidate();
      }
    }

    private void buttonResetVZoom_Click( object sender, EventArgs e )
    {
      foreach ( TrackBunchDesc track in data.tracks )
      {
        if ( null == track.control )
          continue;

        track.control.YAxis1.WorldMax = 1000;
        track.ySize = track.control.YAxis1.WorldMax;
        track.control.Invalidate();
      }

      foreach ( NodeData node in data.nodes )
      {
        if ( null == node.control )
          continue;

        node.control.YAxis1.WorldMax = 1000;
        node.ySize = node.control.YAxis1.WorldMax;
        node.control.Invalidate();
      }
    }

    private void TrackGraph_MouseUp( object sender, MouseEventArgs e )
    {
      PlotSurface2D control = sender as PlotSurface2D;
      if ( null == control )
        return;

      if ( e.Button == MouseButtons.Left )
      {
        PointF click = new PointF( e.X, 0 );
        PointF xMin = new PointF( 2, 0 );
        PointF xMax = new PointF( control.Width - 2, 0 );
        data.CurrentTime = (float)control.XAxis1.PhysicalToWorld( click, xMin, xMax, true );
        RefreshTimes();

        foreach ( PlotSurface2D item in allPlotControls )
          item.Invalidate();
      }
      else if ( e.Button == MouseButtons.Right )
      {
        foreach ( NodeData node in data.nodes )
        {
          if ( node.control != control )
            continue;

          PointF click1 = new PointF( e.X - 2, 0 );
          PointF click2 = new PointF( e.X + 2, 0 );
          PointF xMin = new PointF( 2, 0 );
          PointF xMax = new PointF( control.Width - 2, 0 );
          float bound1 = (float)control.XAxis1.PhysicalToWorld( click1, xMin, xMax, true );
          float bound2 = (float)control.XAxis1.PhysicalToWorld( click2, xMin, xMax, true );

          List<string> lines = new List<string>();

          foreach ( var eventSet in node.events )
          {
            TrackTypeDesc typeDesc = data.GetEventDesc( eventSet.Key );
            if ( !typeDesc.IsOn )
              continue;

            foreach ( Event item in eventSet.Value )
            {
              if ( item.time < bound1 )
                continue;

              if ( item.time > bound2 )
                break;

              lines.Add( string.Format( "{0} ({1:f3}) {2}", eventSet.Key, item.time, item.info ) );
            }
          }

          textBoxEventsDesc.Lines = lines.ToArray();

          break;
        }
      }
    }

    private void ScrollablePanel_MouseWheel( object sender, MouseEventArgs e )
    {
      int value = tracksPanel.VerticalScroll.Value - e.Delta;
      value = ( value < tracksPanel.VerticalScroll.Minimum ) ? tracksPanel.VerticalScroll.Minimum
        : ( value > tracksPanel.VerticalScroll.Maximum ) ? tracksPanel.VerticalScroll.Maximum : value;
      tracksPanel.VerticalScroll.Value = value;
      tracksPanel.Invalidate();
    }

    private void LegendItem_MouseClick( object sender, MouseEventArgs e )
    {
      LegendItemControl control = sender as LegendItemControl;
      if ( null == control || e.Button != MouseButtons.Left )
        return;

      TrackTypeDesc desc = data.trackTypes[control.Text];
      desc.IsOn = !desc.IsOn;
      control.CrossedOut = !desc.IsOn;
      RemoveAllTrackControls();
      CreateTrackControls();
    }

    private void LegendEventItem_MouseClick( object sender, MouseEventArgs e )
    {
      LegendItemControl control = sender as LegendItemControl;
      if ( null == control || e.Button != MouseButtons.Left )
        return;

      TrackTypeDesc desc = data.eventTypes[control.Text];
      desc.IsOn = !desc.IsOn;
      control.CrossedOut = !desc.IsOn;
      RemoveAllTrackControls();
      CreateTrackControls();
    }

    #endregion
  }
}
