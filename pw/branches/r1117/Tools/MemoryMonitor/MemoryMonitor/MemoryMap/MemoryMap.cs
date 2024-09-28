using System;
using System.Collections.Generic;
using System.Text;
using MemoryMonitor.EventLog;
using System.Diagnostics;

namespace MemoryMonitor.Memory
{
  public partial class MemoryMap
  {
    private const UInt32 memTotal = 0x80000000;
    private Node mapRoot = new Node( 0, memTotal );

    public UInt32 MemoryUsed { get { return mapRoot.MemoryUsed; } }
    public UInt32 MemoryFree { get { return memTotal - MemoryUsed; } }

    private AllocEventLog eventProvider = null;
    public string ProviderName { get { return ( null == eventProvider ) ? string.Empty : eventProvider.FileName; } }
    private UInt32 currentTime = 0;
    public UInt32 CurrentTime { get { return currentTime; } }

    private long lastFilePos = 0;

    private const UInt32 snapshotTimeStep = 1000;
    private Dictionary<UInt32, Snapshot> snapshotHistory = new Dictionary<uint, Snapshot>();

    public delegate void StateChangeHandler();
    public event StateChangeHandler MemoryStateChangedEvent = null;

    private int eventsSinceSnapshot = 0;

    private void Clear( bool report )
    {
      mapRoot = new Node( 0, memTotal );
      lastFilePos = 0;
      currentTime = 0;

      if ( report && null != MemoryStateChangedEvent )
        MemoryStateChangedEvent();
    }

    public void SetEventProvider( AllocEventLog _eventProvider )
    {
      eventProvider = _eventProvider;
      eventProvider.EventAllocation += ProcessAlloc;
      eventProvider.EventDeallocation += ProcessFree;

      snapshotHistory.Clear();
      Clear( false );
    }

    public EventAlloc GetInfo( UInt32 address )
    {
      return mapRoot.GetInfo( address );
    }

    public UInt32 GetRangeInfo( UInt32 address, UInt32 length, List<EventAlloc> allocs )
    {
      allocs.Clear();

      return mapRoot.GetFastRegionInfo( address, length, allocs );
    }

    public UInt32 GetRangeFullInfo( UInt32 address, UInt32 length, List<EventAlloc> allocs )
    {
      allocs.Clear();

      return mapRoot.GetFullRegionInfo( address, length, allocs );
    }

    public void NavigateToTime( uint time )
    {
      long fp = ApplyNearestSnapshot( time );

      lastFilePos = eventProvider.ReadEventsToTime( fp, time );

      if ( null != MemoryStateChangedEvent )
        MemoryStateChangedEvent();
    }

    public void NavigateByTimeOffset( int offset )
    {
      uint targetTime = 1;

      if ( currentTime + offset > 0 )
        targetTime = (uint)( currentTime + offset );

      NavigateToTime( targetTime );
    }

    public void NavigateByEventOffset( int offset )
    {
      if ( offset == 0 )
        return;

      if ( offset > 0 )
      {
        lastFilePos = eventProvider.ReadEvents( lastFilePos, offset );
      }
      else
      {
        int eventsToRead = eventsSinceSnapshot + offset;
        Snapshot ss = FindNearestSnapshot( currentTime );
        long filePos = 0;
        if ( eventsToRead >= 0 )
        {
          if ( null == ss )
            Clear( false );
          else
          {
            currentTime = ss.Time;
            mapRoot = ss.Restore();
            filePos = ss.FilePosition;
          }
        }
        else
        {
          if ( null == ss )
            Clear( false );
          else
          {
            eventsToRead += ss.EventsSincePrevious;
            ss = FindNearestSnapshot( ss.Time - 1 );
            if ( null == ss )
              Clear( false );
            else
            {
              currentTime = ss.Time;
              mapRoot = ss.Restore();
              filePos = ss.FilePosition;
            }
          }
        }
        eventsSinceSnapshot = 0;
        if ( eventsToRead > 0 )
          lastFilePos = eventProvider.ReadEvents( filePos, eventsToRead );
      }
      if ( null != MemoryStateChangedEvent )
        MemoryStateChangedEvent();
    }

    public delegate void MemoryStateChangeAlloc( EventAlloc e );
    public delegate void MemoryStateChangeFree( EventFree e, UInt32 len );
    public event MemoryStateChangeAlloc OnAlloc = null;
    public event MemoryStateChangeFree OnFree = null;

    private void ProcessAlloc( EventAlloc e, long filePos )
    {
      try
      {
        ++eventsSinceSnapshot;
        currentTime = e.Time;
        lastFilePos = filePos;
        CheckAddSnapshot( e.Time, filePos );
        mapRoot.ProcessAlloc( e );
        if ( OnAlloc != null )
          OnAlloc( e );
      }
      catch
      {
        Trace.TraceWarning( string.Format( "{0}: bad alloc {1} at {2:X8}", e.Time, e.Size, e.Address ) );
        return;
      }
    }

    private void ProcessFree( EventFree e, long filePos )
    {
      try
      {
        ++eventsSinceSnapshot;
        currentTime = e.Time;
        lastFilePos = filePos;
        UInt32 freedMem = mapRoot.ProcessFree( e );
        if ( OnFree != null )
          OnFree( e, freedMem );
      }
      catch
      {
        Trace.TraceWarning( string.Format( "{0}: bad free at {1:X8}", e.Time, e.Address ) );
        return;
      }
    }

    private void CheckAddSnapshot( UInt32 timeRaw, long filePos )
    {
      UInt32 time = timeRaw / snapshotTimeStep * snapshotTimeStep;

      if ( time == 0 || time % snapshotTimeStep != 0 )
        return;

      if ( !snapshotHistory.ContainsKey( time ) )
        snapshotHistory[time] = new Snapshot( mapRoot, time, filePos, eventsSinceSnapshot );

      eventsSinceSnapshot = 0;
    }

    private long ApplyNearestSnapshot( UInt32 time )
    {
      eventsSinceSnapshot = 0;
      Snapshot ss = FindNearestSnapshot( time );

      if ( null == ss )
      {
        mapRoot = new Node( 0, memTotal );
        currentTime = 0;
        return 0;
      }

      mapRoot = ss.Restore();
      return ss.FilePosition;
    }

    private Snapshot FindNearestSnapshot( UInt32 time )
    {
      if ( time < snapshotTimeStep )
        return null;

      UInt32 timeLvl = time / snapshotTimeStep * snapshotTimeStep;

      while ( timeLvl > 0 )
      {
        if ( snapshotHistory.ContainsKey( timeLvl ) )
          return snapshotHistory[timeLvl];

        timeLvl -= snapshotTimeStep;
      }

      return null;
    }

  }

  public class Range
  {
    public UInt32 Address = 0;
    public UInt32 Length = 0;

    public Range( UInt32 a, UInt32 l ) { Address = a; Length = l; }
  }
}
