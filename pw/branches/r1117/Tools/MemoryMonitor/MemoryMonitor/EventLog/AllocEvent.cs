using System;
using System.Collections.Generic;
using System.Text;

namespace MemoryMonitor.EventLog
{

  public abstract class Event
  {
    public static int CallStackLength = 8;

    public UInt32 Time = 0;
    public UInt32 Address = 0;

    public UInt32[] CallStack = null;

    public Event( UInt32 time, UInt32 address ) { Time = time; Address = address; }
    public Event( UInt32 time, UInt32 address, UInt32[] callStack ) { Time = time; Address = address; CallStack = callStack; }
  }

  public class EventAlloc : Event
  {
    public uint Size = 0;

    public EventAlloc( UInt32 time, UInt32 address, UInt32 size ) : base( time, address ) { Size = size; }
    public EventAlloc( UInt32 time, UInt32 address, UInt32 size, UInt32[] callStack ) : base( time, address, callStack ) { Size = size; }

    public override string ToString()
    {
      return string.Format( "{0}: {1} bytes at {2:X8}", this.Time, this.Size, this.Address ); ;
    }
  }

  public class EventFree : Event
  {
    public EventFree( UInt32 time, UInt32 address ) : base( time, address ) { }
    public EventFree( UInt32 time, UInt32 address, UInt32[] callStack ) : base( time, address, callStack ) { }
  }
}
