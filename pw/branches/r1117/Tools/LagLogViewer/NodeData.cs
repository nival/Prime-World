using System;
using System.Collections.Generic;
using NPlot.Windows;
using System.Drawing;
using System.Globalization;
using System.IO;

namespace TrackVis
{
  public class OnOffItem
  {
    public float on = -1;
    public float off = -1;
  }

  public class Event
  {
    public float time;
    public string info = string.Empty;

    public Event( float t, string s ) { time = t; info = s; }
  }

  public class NodeData
  {
    public Point nodeLocation = new Point( 200, 200 );
    public string nodeId;

    public TrackBunchDesc[] connections = null;

    public Dictionary<string, TrackDesc> tracks = new Dictionary<string, TrackDesc>();
    public double ySize = -1;
    public Dictionary<string, List<OnOffItem>> flags = new Dictionary<string, List<OnOffItem>>();
    public Dictionary<string, List<Event>> events = new Dictionary<string, List<Event>>();
    public PlotSurface2D control = new PlotSurface2D();

    public void ReadFromFile( StreamReader sr, Dataset data )
    {
      string line;
      // Data
      while ( ( line = sr.ReadLine() ) != null )
      {
        if ( line.Length == 0 )
          continue;

        string[] parts = line.Split( ',' );

        if ( parts.Length < 3 )
          continue;

        float time;
        float.TryParse( parts[0], NumberStyles.Any, NumberFormatInfo.InvariantInfo, out time );
        time /= 1000.0f;

        if ( parts[2] == "on" )
        {
          data.GetFlagColor( parts[1] );
          StoreLocalFlagOn( time, parts[1] );
          continue;
        }
        else if ( parts[2] == "off" )
        {
          data.GetFlagColor( parts[1] );
          StoreLocalFlagOff( time, parts[1] );
          continue;
        }
        else if ( parts[2] == "E" || parts[2] == "!" || parts[2] == "event" )
        {
          StoreLocalEvent( time, parts[1], parts.Length < 4 ? string.Empty : parts[3] );
          continue;
        }

        float value;
        float.TryParse( parts[2], NumberStyles.Any, NumberFormatInfo.InvariantInfo, out value );

        if ( time > data.Length )
          data.Length = time;

        TrackDesc track = null;
        if ( tracks.ContainsKey( parts[1] ) )
          track = tracks[parts[1]];
        else
        {
          track = new TrackDesc();
          tracks[parts[1]] = track;
        }

        track.times.Add( time );
        track.data.Add( value );
      }
    }

    private void StoreLocalEvent( float time, string p, string desc )
    {
      if ( !events.ContainsKey( p ) )
        events[p] = new List<Event>();

      events[p].Add( new Event( time, desc ) );
    }

    private void StoreLocalFlagOn( float time, string flagName )
    {
      if ( !flags.ContainsKey( flagName ) )
      {
        flags[flagName] = new List<OnOffItem>();
        OnOffItem item = new OnOffItem();
        item.on = time;
        item.off = -1;
        flags[flagName].Add( item );
        return;
      }

      List<OnOffItem> flagTrack = flags[flagName];

      OnOffItem end = new OnOffItem();
      end.on = time;
      end.off = -1;
      flagTrack.Add( end );
    }

    private void StoreLocalFlagOff( float time, string flagName )
    {
      if ( !flags.ContainsKey( flagName ) )
      {
        flags[flagName] = new List<OnOffItem>();
        OnOffItem item = new OnOffItem();
        item.on = -1;
        item.off = time;
        flags[flagName].Add( item );
        return;
      }

      List<OnOffItem> flagTrack = flags[flagName];

      OnOffItem end = flagTrack[flagTrack.Count - 1];
      end.off = time;
    }

    private int TestFlagItem( OnOffItem item, float time )
    {
      if ( item.off > 0 && item.off < time )
        return 1;
      if ( item.on > time )
        return -1;
      return 0;
    }

    public bool IsFlagOn( string flag, float time )
    {
      if ( !flags.ContainsKey( flag ) )
        return false;
      List<OnOffItem> track = flags[flag];
      if ( null == track || track.Count == 0 )
        return false;

      int max = track.Count - 1;
      int min = 0;
      if ( TestFlagItem( track[min], time ) == 0 || TestFlagItem( track[max], time ) == 0 )
        return true;
      if ( TestFlagItem( track[min], time ) < 0 || TestFlagItem( track[max], time ) > 0 )
        return false;

      while ( max - min > 1 )
      {
        int i = ( max + min ) / 2;

        int res = TestFlagItem( track[i], time );
        if ( 0 == res )
          return true;
        if ( res > 0 )
          min = i;
        else
          max = i;
      }

      return false;
    }
  }
}