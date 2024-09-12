using System;
using System.Collections.Generic;
using NPlot.Windows;
using System.Drawing;
using System.Globalization;
using System.IO;

namespace TrackVis
{
  #region Data Structures

  public class TrackDesc
  {
    public List<float> times = new List<float>();
    public List<float> data = new List<float>();
  }

  public class TrackBunchDesc
  {
    public string nodeFrom = string.Empty;
    public string nodeTo = string.Empty;

    public double ySize = -1;

    public Dictionary<string, TrackDesc> tracks = new Dictionary<string, TrackDesc>();
    public PlotSurface2D control = new PlotSurface2D();
  }

  public class TrackTypeDesc
  {
    public Color Color = Color.Black;
    public bool IsOn = true;
    public LegendItemControl LegendItem = null;
    public TrackTypeDesc( Color _color, LegendItemControl _control ) { this.Color = _color; LegendItem = _control; }
  }

  #endregion

  public class Dataset
  {
    public List<NodeData> nodes = new List<NodeData>();
    public List<TrackBunchDesc> tracks = new List<TrackBunchDesc>();
    public Dictionary<string, int> nodeMap = new Dictionary<string, int>();
    public Dictionary<string, TrackTypeDesc> trackTypes = new Dictionary<string, TrackTypeDesc>();
    public Dictionary<string, Color> flagTypes = new Dictionary<string, Color>();
    public Dictionary<string, TrackTypeDesc> eventTypes = new Dictionary<string, TrackTypeDesc>();
    public float Length = 0.0f;
    public int NodeCount = 0;

    private NPlot.VerticalLine vSyncLine = new NPlot.VerticalLine( 0, Color.Black );
    public NPlot.VerticalLine SyncLine { get { return vSyncLine; } }
    public float CurrentTime
    {
      get { return (float)vSyncLine.AbscissaValue; }
      set
      {
        vSyncLine.AbscissaValue = ( value < 0 ) ? 0 : ( ( value > Length ) ? Length : value );
      }
    }


    public void ReadFiles( string[] fileNames )
    {
      Clear();
      foreach ( string fileName in fileNames )
        ReadFileData( fileName );

      RebuildNodes();
    }

    private bool ReadFileData( string fileName )
    {
      try
      {
        StreamReader sr = new StreamReader( fileName, System.Text.Encoding.Default );
        string line;

        // Header
        if ( ( line = sr.ReadLine() ) == null )
          return false;

        string[] parts = line.Split( ',' );

        if ( parts.Length > 1 && parts[0] == "Local" )
        {
          RegisterNodeId( parts[1] );
          NodeData node = nodes[nodeMap[parts[1]]];

          node.ReadFromFile( sr, this );
          return true;
        }
        else
        {
          return ReadNormalFileData( line, sr );
        }

      }
      catch ( Exception )
      {
        return false;
      }
    }

    private bool ReadNormalFileData( string title, StreamReader sr )
    {
      string line;
      // Data
      while ( ( line = sr.ReadLine() ) != null )
      {
        if ( line.Length == 0 )
          continue;

        string[] parts = line.Split( ',' );

        if ( parts.Length != 4 )
          continue;

        float time;
        float value;
        string nodeFrom = parts[1];
        string nodeTo = parts[2];
        float.TryParse( parts[0], NumberStyles.Any, NumberFormatInfo.InvariantInfo, out time );
        float.TryParse( parts[3], NumberStyles.Any, NumberFormatInfo.InvariantInfo, out value );

        if ( time > Length * 1000.0f )
          Length = time / 1000.0f;

        TrackDesc track = GetOrCreateTrack( title, nodeFrom, nodeTo );
        track.times.Add( time / 1000.0f );
        track.data.Add( value );
      }
      return true;
    }

    private TrackDesc GetOrCreateTrack( string title, string nodeFrom, string nodeTo )
    {
      TrackBunchDesc bunch = null;
      TrackDesc track = null;
      foreach ( TrackBunchDesc item in tracks )
      {
        if ( item.nodeFrom == nodeFrom && item.nodeTo == nodeTo )
        {
          bunch = item;
          break;
        }
      }
      if ( null == bunch )
      {
        bunch = new TrackBunchDesc();
        bunch.nodeFrom = nodeFrom;
        bunch.nodeTo = nodeTo;
        RegisterNodeId( nodeFrom );
        RegisterNodeId( nodeTo );
        tracks.Add( bunch );
      }
      if ( bunch.tracks.ContainsKey( title ) )
      {
        track = bunch.tracks[title];
      }
      else
      {
        track = new TrackDesc();
        bunch.tracks[title] = track;
      }
      return track;
    }

    private void RegisterNodeId( string nodeId )
    {
      if ( !nodeMap.ContainsKey( nodeId ) )
      {
        nodeMap[nodeId] = nodeMap.Count;

        NodeCount = nodeMap.Count;
        NodeData newData = new NodeData();
        newData.nodeId = nodeId;
        nodes.Add( newData );
      }
    }

    private void RebuildNodes()
    {
      foreach ( NodeData node in nodes )
        node.connections = new TrackBunchDesc[NodeCount];

      foreach ( TrackBunchDesc item in tracks )
        SetLineData( nodeMap[item.nodeFrom], nodeMap[item.nodeTo], item );
    }

    private void SetLineData( int nodeFrom, int nodeTo, TrackBunchDesc bunch )
    {
      if ( nodeFrom < 0 || nodeFrom >= NodeCount || nodeTo < 0 || nodeTo >= nodes.Count || nodeFrom == nodeTo )
        return;

      nodes[nodeFrom].connections[nodeTo] = bunch;
      if ( bunch == null )
        return;

      nodes[nodeFrom].nodeId = bunch.nodeFrom;
    }

    public void Clear()
    {
      nodes.Clear();
      tracks.Clear();
      nodeMap.Clear();
      trackTypes.Clear();
      flagTypes.Clear();
      eventTypes.Clear();
      Length = 0;
      NodeCount = 0;
      CurrentTime = 0;
    }

    public TrackTypeDesc GetTrackVisDesc( string p )
    {
      if ( trackTypes.ContainsKey( p ) )
        return trackTypes[p];

      Color result = GetColorByIndex( trackTypes.Count );
      TrackTypeDesc newDesc = new TrackTypeDesc( result, new LegendItemControl( p, result ) );
      trackTypes[p] = newDesc;
      return trackTypes[p];
    }

    public Color GetFlagColor( string p )
    {
      if ( !flagTypes.ContainsKey( p ) )
        flagTypes[p] = GetColorByIndex( flagTypes.Count );

      return flagTypes[p];
    }

    public TrackTypeDesc GetEventDesc( string p )
    {
      if ( eventTypes.ContainsKey( p ) )
        return eventTypes[p];

      Color result = GetColorByIndex( eventTypes.Count );
      TrackTypeDesc newDesc = new TrackTypeDesc( result, new LegendItemControl( p, result ) );
      eventTypes[p] = newDesc;

      return eventTypes[p];
    }

    private Color GetColorByIndex( int i )
    {
      Color result = Color.Black;
      switch ( i )
      {
        case 0: result = Color.Red; break;
        case 1: result = Color.Green; break;
        case 2: result = Color.Blue; break;
        case 3: result = Color.Magenta; break;
        case 4: result = Color.Brown; break;
        case 5: result = Color.Gray; break;
        case 6: result = Color.Cyan; break;
        case 7: result = Color.DarkGray; break;
        case 8: result = Color.DarkGreen; break;
        case 9: result = Color.LightCoral; break;
        case 10: result = Color.DarkRed; break;
        case 12: result = Color.LightSeaGreen; break;
        case 13: result = Color.Lime; break;
        case 14: result = Color.LightPink; break;
        case 15: result = Color.DarkOrange; break;
      }
      return result;
    }
  }

}