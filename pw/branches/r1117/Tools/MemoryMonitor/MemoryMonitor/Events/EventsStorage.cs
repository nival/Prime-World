using System.Collections.Generic;
using System;

namespace MemoryMonitor.Events
{
  # region Auxiliary Data

  internal struct TimeRange
  {
    public static readonly TimeRange Empty = new TimeRange( ulong.MinValue, ulong.MinValue );

    public ulong start;
    public ulong end;

    public TimeRange( ulong start, ulong end ) { this.start = start; this.end = end; }
    public ulong EvaluateTime( float u ) { return start + ( ulong )( u * ( end - start ) ); }
    public float EvaluateParameter( ulong value )
    {
      if( value < start || end == start ) return 0;
      else return ( float )( value - start ) / ( float )( end - start );
    }
  };

  internal delegate void TimeSetEvent( ulong time );

  # endregion

  internal sealed class EventsStorage
  {
    # region Fields

    private SortedList<ulong, List<Event>> allEvents = new SortedList<ulong, List<Event>>();

    private TimeRange interval = new TimeRange( ulong.MaxValue, ulong.MinValue );

    public ulong StartTime { get { return interval.start; } }
    public ulong EndTime { get { return interval.end; } }

    private const ulong EventsQuant = 2000;
    private ulong currentEventCounter = 0;
    private ulong eventQuants = 0;

    //private SortedDictionary<SelectRequestData, IDictionary<ulong, ICollection<Event>>> selectCache = new SortedDictionary<SelectRequestData, IDictionary<ulong, ICollection<Event>>>();
    private SortedList<ulong, ICollection<ICollection<Event>>> quantCache = new SortedList<ulong, ICollection<ICollection<Event>>>();

    # endregion

    public void Reset()
    {
      allEvents.Clear();
      interval.start = ulong.MaxValue;
      interval.end = ulong.MinValue;
      currentEventCounter = 0;
      eventQuants = 0;
      quantCache.Clear();
    }

    # region C# VisibleEvents

    internal event TimeSetEvent StartTimeChangeHandlers;
    internal event TimeSetEvent EndTimeChangeHandlers;

    # endregion

    # region Cache

    private class SelectRequestData : IComparable
    {
      private readonly ulong t1;
      private readonly ulong t2;
      private readonly ICollection<Event> filter;

      public SelectRequestData( ulong t1, ulong t2, ICollection<Event> filter )
      {
        this.t1 = t1;
        this.t2 = t2;
        this.filter = filter;
      }

      public override int GetHashCode()
      {
        int hash = t1.GetHashCode() ^ t2.GetHashCode();
        if( null != filter )
          foreach( Event e in filter )
            hash ^= e.GetHashCode();

        return hash;
      }

      public int CompareTo( object obj )
      {
        SelectRequestData temp = obj as SelectRequestData;
        if ( null == temp ) return -1;
        if ( Equals( temp ) )
          return 0;
        return temp.t1 > t1 ? -1 : 1;
      }

      public override bool Equals( object obj )
      {
        if ( !(obj is SelectRequestData) )
          return false;

        SelectRequestData temp = obj as SelectRequestData;
        return t1 == temp.t1 && t2 == temp.t2 && UnorderedEqual<Event>( filter, temp.filter );
      }
      
      private static bool UnorderedEqual<T>( ICollection<T> a, ICollection<T> b )
      {
        if ( a == null && b == null )
          return true;

        if ( a == null )
          return false;

        if ( b == null )
          return false;

        if ( a.Count != b.Count )
          return false;
        
        Dictionary<T, int> d = new Dictionary<T, int>();
        foreach ( T item in a )
        {
          int c;
          if ( d.TryGetValue( item, out c ) )
            d[item] = c + 1;
          else
            d.Add( item, 1 );
        }

        foreach ( T item in b )
        {
          int c;
          if ( d.TryGetValue( item, out c ) )
          {
            if ( c == 0 )
              return false;
            else
              d[item] = c - 1;
          }
          else
            return false;
        }

        foreach ( int v in d.Values )
        {
          if ( v != 0 )
            return false;
        }

        return true;
      }
    };

    #endregion

    # region VisibleEvents managment

    public static int LowerBoundSearch<T>( IList<T> array, int index, int length, T value ) where T : IComparable<T>
    {
      int lo = index;
      int hi = index + length - 1;
      
      int lower = -1;

      while ( lo <= hi )
      {
        int i = lo + ( ( hi - lo ) >> 1 );
        int order = array[i].CompareTo( value );

        if ( order == 0 )
          return i;

        if ( order < 0 )
        {
          lower = lo;
          lo = i + 1;
        }
        else
        {
          hi = i - 1;
        }
      }

      return lower;
    }

    public static int LowerBoundSearch<T>( IList<T> array, int index, int length, T value, IComparer<T> comparer )
    {
      int lo = index;
      int hi = index + length - 1;

      int lower = -1;

      while ( lo <= hi )
      {
        int i = lo + ( ( hi - lo ) >> 1 );
        int order = comparer.Compare( array[i], value );

        if ( order == 0 )
          return i;

        if ( order < 0 )
        {
          lower = lo;
          lo = i + 1;
        }
        else
        {
          hi = i - 1;
        }
      }

      return lower;
    }

    //private static KeyValuePair<ulong, U> LowBoundSearch<U>( SortedList<ulong, U> array, ulong value )
    //{
    //  var keys = array.Keys;

    //  //return ~lo;

    //  return default( KeyValuePair<ulong, U> );
    //}

    public ICollection<ICollection<Event>> select( ulong t )
    {
      var quants = quantCache.Keys;

      int lowerIndex = LowerBoundSearch( quants, 0, quants.Count, t );
      ulong quant = lowerIndex >= 0 && lowerIndex < quants.Count ? quants[lowerIndex] : ulong.MaxValue;

      ICollection<ICollection<Event>> result = null;
      if( !quantCache.TryGetValue( quant, out result ) )
      {
        result = new List<ICollection<Event>>();
        foreach ( var pair in allEvents )
        {
          if ( pair.Key > t )
            break;

          result.Add( pair.Value );
        }
      }
      else
      {
        result = new List<ICollection<Event>>( result );

        var keys = allEvents.Keys;
        int i = LowerBoundSearch( keys, 0, keys.Count, quant ) + 1;

        for ( ; i < keys.Count; ++i )
        {
          ulong key = keys[i];

          if ( key > t )
            break;

          result.Add( allEvents[key] );
        }
      }

      return result;
    }

    public IDictionary<ulong, ICollection<Event>> select( ulong t1, ulong t2, ICollection<Event> filter )
    {
      IDictionary<ulong, ICollection<Event>> result = new SortedList<ulong, ICollection<Event>>( allEvents.Count );
      foreach ( var pair in allEvents )
      {
        if ( pair.Key < t1 )
          continue;
        if ( pair.Key > t2 )
          break;

        result.Add( pair.Key, pair.Value );
      }

      return result;
    }

    //public IDictionary<ulong, ICollection<Event>> select( TimeRange interval, ICollection<Event> filter )
    //{
    //  return select( interval.start, interval.end, filter );
    //}

    public void PushEvent( ulong t, Event e )
    {
      AddEventInternal( t, e );
      if ( StartTime > t )
        interval.start = t;
      else if ( EndTime < t )
        interval.end = t;
    }

    public void ForceTimeChangeEventsCall()
    {
      if ( null != StartTimeChangeHandlers )
        StartTimeChangeHandlers( interval.start );

      if ( null != EndTimeChangeHandlers )
        EndTimeChangeHandlers( interval.end );
    }

    public void AddEvent( ulong t, Event e )
    {
      AddEventInternal( t, e );
      UpdateTimeRange( t );      
    }

    private void AddEventInternal( ulong t, Event e )
    {
      List<Event> container = null;
      if ( !allEvents.TryGetValue( t, out container ) )
      {
        container = new List<Event>( new Event[1] { e } );
        allEvents.Add( t, container );
      }
      else
        allEvents[t].Add( e );

      if ( currentEventCounter++ >= EventsQuant )
      {
        currentEventCounter = 0;
        ++eventQuants;

        // calculate snapshot for range 0 .. t
        quantCache[t] = select( t );
      }

      // TODO: invalidate events blocksCache
    }

    private void UpdateTimeRange( ulong t )
    {
      if ( StartTime > t )
      {
        interval.start = t;
        if ( null != StartTimeChangeHandlers )
          StartTimeChangeHandlers( t );
      }
      else if ( EndTime < t )
      {
        interval.end = t;
        if ( null != EndTimeChangeHandlers )
          EndTimeChangeHandlers( t );
      }
    }

    # endregion
  }
}
