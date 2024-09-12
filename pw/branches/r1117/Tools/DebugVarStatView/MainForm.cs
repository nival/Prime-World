using System;
using System.Windows.Forms;
using System.Drawing;

using Npgsql;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using System.Globalization;
using NPlot;

namespace foo_csw1
{
  public partial class MainForm : Form
  {
    private class DebugVarInfo
    {
      public readonly string login = string.Empty;
      public readonly int session = -1;
      public readonly int game = -1;
      public readonly int step = -1;
      public readonly string name = string.Empty;
      public readonly float value = 0.0f;
      public readonly DateTime time = DateTime.MinValue;

      public DebugVarInfo()
      {
      }

      public DebugVarInfo( DbDataReader reader )
      {
        login = (string)reader[0];
        session = (int)reader[1];
        game = (int)reader[2];
        step = (int)reader[3];
        name = (string)reader[4];
        string _value = (string)reader[5];
        bool oldFormat = _value.IndexOf( ':' ) >= 0;
        if ( oldFormat )
        {
          _value = _value.Substring( 0, _value.IndexOf( ':' ) ).Trim();
          value = 1000.0f * float.Parse( _value, new NumberFormatInfo() { NumberDecimalSeparator = "." } );
        }
        else
          value = float.Parse( _value, new NumberFormatInfo() { NumberDecimalSeparator = "." } );

        time = (DateTime)reader[6];
      }
    }

    private class ValuesCollection<T>
    {
      private List<T> keys = new List<T>();
      private List<double> values = new List<double>();

      public void Add( T key, double value )
      {
        keys.Add( key );
        values.Add( value );
      }

      public void Normalize()
      {
        if ( values.Count == 0 )
          return;

        double min = values[0];
        double max = values[0];
        for ( int i = 1; i < values.Count; ++i )
        {
          min = Math.Min( min, values[i] );
          max = Math.Max( max, values[i] );
        }
        double k = ( min == max ) ? 1.0 : 1.0 / ( max - min );
        for ( int i = 0; i < values.Count; ++i )
          values[i] = ( values[i] - min ) * k;
      }

      public bool Empty { get { return values.Count == 0; } }

      public T KeyMin { get { return keys.Count > 0 ? keys[0] : default( T ); } }
      public T KeyMax { get { return keys.Count > 0 ? keys[keys.Count - 1] : default( T ); } }
      public double LastValue { get { return values.Count > 0 ? values[values.Count - 1] : 0.0; } }

      public List<T> Keys { get { return keys; } }
      public List<double> Values { get { return values; } }
    }

    #region HorizontalDrag

    public class HorizontalDrag : NPlot.Windows.PlotSurface2D.Interactions.Interaction
    {
      public override bool DoMouseDown( MouseEventArgs e, Control ctr )
      {
        NPlot.PlotSurface2D ps = ( (NPlot.Windows.PlotSurface2D)ctr ).Inner;

        if ( e.X > ps.PlotAreaBoundingBoxCache.Left && e.X < ( ps.PlotAreaBoundingBoxCache.Right ) &&
            e.Y > ps.PlotAreaBoundingBoxCache.Top && e.Y < ps.PlotAreaBoundingBoxCache.Bottom )
        {
          dragInitiated_ = true;

          lastPoint_ = startPoint_ = new Point( e.X, e.Y );
        }

        return false;
      }

      private void MoveAxis( PointF delta, Axis axis, PhysicalAxis physical )
      {
        if ( axis == null || physical == null )
          return;

        PointF pMin = physical.PhysicalMin;
        PointF pMax = physical.PhysicalMax;

        PointF physicalWorldMin = pMin;
        PointF physicalWorldMax = pMax;
        physicalWorldMin.X -= delta.X;
        physicalWorldMax.X -= delta.X;
        physicalWorldMin.Y -= delta.Y;
        physicalWorldMax.Y -= delta.Y;
        double newWorldMin = axis.PhysicalToWorld( physicalWorldMin, pMin, pMax, false );
        double newWorldMax = axis.PhysicalToWorld( physicalWorldMax, pMin, pMax, false );
        axis.WorldMin = newWorldMin;
        axis.WorldMax = newWorldMax;
      }

      private void ScaleAxis( Point startPoint, float delta, Axis axis, PhysicalAxis physical )
      {
        PointF pMin = physical.PhysicalMin;
        PointF pMax = physical.PhysicalMax;
        double physicalWorldLength = Math.Sqrt( ( pMax.X - pMin.X ) * ( pMax.X - pMin.X ) + ( pMax.Y - pMin.Y ) * ( pMax.Y - pMin.Y ) );

        float prop = 2.0f * (float)( physicalWorldLength * delta / sensitivity_ );

        float relativePosX = ( startPoint.X - pMin.X ) / ( pMax.X - pMin.X );
        if ( float.IsInfinity( relativePosX ) || float.IsNaN( relativePosX ) ) relativePosX = 0.0f;

        float relativePosY = ( startPoint.Y - pMin.Y ) / ( pMax.Y - pMin.Y );
        if ( float.IsInfinity( relativePosY ) || float.IsNaN( relativePosY ) ) relativePosY = 0.0f;

        PointF physicalWorldMin = pMin;
        PointF physicalWorldMax = pMax;

        physicalWorldMin.X += relativePosX * prop;
        physicalWorldMax.X -= ( 1 - relativePosX ) * prop;
        physicalWorldMin.Y -= relativePosY * prop;
        physicalWorldMax.Y += ( 1 - relativePosY ) * prop;

        double newWorldMin = axis.PhysicalToWorld( physicalWorldMin, pMin, pMax, false );
        double newWorldMax = axis.PhysicalToWorld( physicalWorldMax, pMin, pMax, false );
        axis.WorldMin = newWorldMin;
        axis.WorldMax = newWorldMax;
      }

      public override bool DoMouseMove( MouseEventArgs e, Control ctr, KeyEventArgs lastKeyEventArgs )
      {
        NPlot.PlotSurface2D ps = ( (NPlot.Windows.PlotSurface2D)ctr ).Inner;

        if ( dragInitiated_ )
        {
          if ( e.Button == MouseButtons.Left )
          {
            ( (NPlot.Windows.PlotSurface2D)ctr ).CacheAxes();
            PointF delta = new PointF( e.X - lastPoint_.X, e.Y - lastPoint_.Y );
            MoveAxis( delta, ps.XAxis1, ps.PhysicalXAxis1Cache );
            MoveAxis( delta, ps.XAxis2, ps.PhysicalXAxis2Cache );
            MoveAxis( delta, ps.YAxis1, ps.PhysicalYAxis1Cache );
            MoveAxis( delta, ps.YAxis2, ps.PhysicalYAxis2Cache );

            lastPoint_ = new Point( e.X, e.Y );
            return true;
          }
          else if ( e.Button == MouseButtons.Right )
          {
            ( (NPlot.Windows.PlotSurface2D)ctr ).CacheAxes();
            ScaleAxis( startPoint_, e.X - lastPoint_.X, ps.XAxis1, ps.PhysicalXAxis1Cache );
            ScaleAxis( startPoint_, -e.Y + lastPoint_.Y, ps.YAxis1, ps.PhysicalYAxis1Cache );

            lastPoint_ = new Point( e.X, e.Y );
            return true;
          }
        }

        return false;
      }

      public override bool DoMouseUp( MouseEventArgs e, Control ctr )
      {
        if ( ( e.Button == MouseButtons.Left ) && dragInitiated_ )
        {
          lastPoint_ = new Point( -1, -1 );
          startPoint_ = new Point( -1, -1 );
          dragInitiated_ = false;
        }
        return false;
      }

      private bool dragInitiated_ = false;
      private Point lastPoint_ = new Point( -1, -1 );
      private Point startPoint_ = new Point( -1, -1 );
      private float sensitivity_ = 200.0f;
    }

    #endregion

    List<DebugVarInfo>  records = new List<DebugVarInfo>();

    public MainForm()
    {
      InitializeComponent();
    }

    private void LoadRecords( DateTime date )
    {
      records.Clear();

      using ( var conn = new NpgsqlConnection( "Server=tioserv;Port=5432;Database=pw_analysis;User ID=Ivn;Password=ivn" ) )
      {
        conn.Open();
        var cmd = new NpgsqlCommand { Connection = conn };
        cmd.CommandText = string.Format( @"
SELECT player.login, sessiontoplayer.gamesession, gamesession.idclient, event_debugvar.step, event_debugvar.name, event_debugvar.value, event_debugvar.eventtime
FROM event_debugvar
  JOIN sessiontoplayer ON sessiontoplayer.id = event_debugvar.sessiontoplayerid
  JOIN playercharacter ON playercharacter.id = sessiontoplayer.playercharacter
  JOIN player ON player.id = playercharacter.player
  JOIN gamesession ON gamesession.id = sessiontoplayer.gamesession
WHERE event_debugvar.eventtime >= '{0} 00:00:00' AND event_debugvar.eventtime < '{1} 00:00:00'
ORDER BY player.login ASC, sessiontoplayer.gamesession ASC, event_debugvar.eventtime ASC", date.ToString( "yyyy-MM-dd" ), ( date + TimeSpan.FromDays( 1.0 ) ).ToString( "yyyy-MM-dd" ) );
        var reader = cmd.ExecuteReader();
        while ( reader.Read() )
          records.Add( new DebugVarInfo( reader ) );
      }

      players.BeginUpdate();
      players.Items.Clear();
      DebugVarInfo lastItem = new DebugVarInfo();
      float maxDataBufferSize = 0.0f;
      bool hasEmptyBuffer = false;
      foreach ( var info in records )
      {
        if ( info.login != lastItem.login || info.session != lastItem.session )
        {
          if ( !string.IsNullOrEmpty( lastItem.login ) )
          {
            var item = players.Items.Add( lastItem.login );
            item.Tag = lastItem;
            item.SubItems.Add( string.Format( "{0} | {1}", lastItem.session, lastItem.game ) );
            if ( maxDataBufferSize > 5.0f )
              item.Font = new Font( item.Font, FontStyle.Bold );
            if ( hasEmptyBuffer )
              item.ForeColor = Color.Blue;
          }
          lastItem = info;
          maxDataBufferSize = 0.0f;
        }
        if ( info.name == "DataBufferSize" )
        {
          if ( info.value > maxDataBufferSize )
            maxDataBufferSize = info.value;
          hasEmptyBuffer = info.value < 0.0f;
        }
      }
      if ( !string.IsNullOrEmpty( lastItem.login ) )
      {
        var item = players.Items.Add( lastItem.login );
        item.Tag = lastItem;
        item.SubItems.Add( string.Format( "{0} | {1}", lastItem.session, lastItem.game ) );
        if ( maxDataBufferSize > 5.0f )
          item.Font = new Font( item.Font, FontStyle.Bold );
        if ( hasEmptyBuffer )
          item.ForeColor = Color.Blue;
      }
      players.EndUpdate();
    }

    private void AddSessionPlots( DebugVarInfo session, NPlot.Windows.PlotSurface2D graph, Color bufferColor, Color fpsColor, Color pingColor, System.Drawing.Drawing2D.DashStyle style )
    {
      ValuesCollection<DateTime> buffer = new ValuesCollection<DateTime>();
      ValuesCollection<DateTime> fps = new ValuesCollection<DateTime>();
      ValuesCollection<DateTime> ping = new ValuesCollection<DateTime>();
      ValuesCollection<DateTime> step = new ValuesCollection<DateTime>();
      DateTime startStepTime = DateTime.MinValue;
      foreach ( var info in records )
      {
        if ( info.login != session.login || info.session != session.session )
          continue;
        switch ( info.name )
        {
        case "DataBufferSize":
          buffer.Add( info.time, info.value );
          if ( step.Empty )
          {
            startStepTime = info.time;
            step.Add( info.time, 0.0 );
          }
          else if ( step.LastValue < info.step )
          {
            int wantedStep = (int)( ( info.time - startStepTime ).TotalMilliseconds / 100.0 );
            step.Add( info.time, info.step - wantedStep );
          }
          break;
        case "FPS":
          fps.Add( info.time, info.value * 10.0 );
          if ( step.Empty )
          {
            startStepTime = info.time;
            step.Add( info.time, 0.0 );
          }
          else if ( step.LastValue < info.step )
          {
            int wantedStep = (int)( ( info.time - startStepTime ).TotalMilliseconds / 100.0 );
            step.Add( info.time, info.step - wantedStep );
          }
          break;
        case "hybrid_ping_value":
          ping.Add( info.time, info.value );
          break;
        }
      }

      graph.Add( new LinePlot( buffer.Values, buffer.Keys ) { Pen = new Pen( bufferColor ) { DashStyle = style } } );
      graph.Add( new LinePlot( fps.Values, fps.Keys ) { Pen = new Pen( fpsColor ) { DashStyle = style } } );
      graph.Add( new LinePlot( ping.Values, ping.Keys ) { Pen = new Pen( pingColor ) { DashStyle = style } } );
      graph.Add( new LinePlot( step.Values, step.Keys ) { Pen = new Pen( Color.Magenta ) { DashStyle = style } } );
    }

    private void FindMinMax( DebugVarInfo session, DebugVarInfo session2, out DateTime min, out DateTime max )
    {
      min = default( DateTime );
      max = default( DateTime );
      bool assigned = false;
      foreach ( var info in records )
      {
        if ( info.login == session.login && info.session == session.session )
        {
          if ( !assigned || info.time < min )
            min = info.time;
          if ( !assigned || info.time > max )
            max = info.time;
        }
        if ( session2 != null && info.login == session2.login && info.session == session2.session )
        {
          if ( !assigned || info.time < min )
            min = info.time;
          if ( !assigned || info.time > max )
            max = info.time;
        }
      }
    }

    private void LoadGraph( DebugVarInfo session, DebugVarInfo session2 )
    {
      graph.Clear();

      DateTime min, max;
      FindMinMax( session, session2, out min, out max );
      graph.AddInteraction( new HorizontalDrag() );
      graph.XAxis1 = new DateTimeAxis( min, max );
      graph.YAxis1 = new LinearAxis( 0.0, 100.0 );
      graph.YAxis1.Hidden = false;

      graph.Add( new HorizontalLine( 100.0, new Pen( Color.Silver ) { DashStyle = System.Drawing.Drawing2D.DashStyle.Dash } ) );
      graph.Add( new HorizontalLine( 300.0, new Pen( Color.Silver ) { DashStyle = System.Drawing.Drawing2D.DashStyle.Dash } ) );
      graph.Add( new HorizontalLine( 500.0, new Pen( Color.Silver ) { DashStyle = System.Drawing.Drawing2D.DashStyle.Dash } ) );

      if ( session2 != null )
        AddSessionPlots( session2, graph, Color.FromArgb( 0, 0, 255 ), Color.FromArgb( 255, 0, 0 ), Color.FromArgb( 0, 192, 0 ), System.Drawing.Drawing2D.DashStyle.Dot );
      AddSessionPlots( session, graph, Color.FromArgb( 0, 0, 255 ), Color.FromArgb( 255, 0, 0 ), Color.FromArgb( 0, 192, 0 ), System.Drawing.Drawing2D.DashStyle.Solid );
      
      graph.Invalidate();
    }

    protected override void OnLoad( EventArgs e )
    {
      base.OnLoad( e );
      LoadRecords( rangeDate.Value.Date );
    }

    private void OnDateTimeValueChanged( object sender, EventArgs e )
    {
      LoadRecords( rangeDate.Value.Date );
    }

    private void OnSelectPlayer( object sender, EventArgs e )
    {
      if ( players.SelectedItems.Count < 1 || players.SelectedItems.Count > 2 )
        return;

      DebugVarInfo info = players.SelectedItems[0].Tag as DebugVarInfo;
      DebugVarInfo info2 = null;
      if ( players.SelectedItems.Count == 2 )
        info2 = players.SelectedItems[1].Tag as DebugVarInfo;
      LoadGraph( info, info2 );

      foreach ( ListViewItem item in players.Items )
      {
        if ( !item.Selected )
        {
          if ( ( item.Tag as DebugVarInfo ).session == info.session )
            item.BackColor = Color.PaleGoldenrod;
          else
            item.BackColor = players.BackColor;
        }
      }
    }

    [STAThread]
    static void Main()
    {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault( false );
      Application.Run( new MainForm() );
    }
  }
}
