using System.IO;
using System.Collections.Generic;

namespace MemoryMonitor
{
  namespace Events
  {
    internal class EventsBuilder
    {
      public enum Events
      {
        Message,
        Allocation,
        Freed,
      }

      private static ulong eventsCounter = ulong.MinValue;
      internal static KeyValuePair<ulong, Event> Build( BinaryReader reader, int blockSize )
      {
        long initialPosition = reader.BaseStream.Position;
        Event e = null;

        Events type = (Events)reader.ReadInt32();
        ulong time = (ulong)reader.ReadUInt32();

        // for test purpose (to improve loading speed while testing)
        //if ( eventsCounter < 100000 )
        {
          switch ( type )
          {
            case Events.Allocation:
              {
                ulong address = (ulong)reader.ReadUInt32();
                ulong size = (ulong)reader.ReadUInt32();
                e = new Allocation( ++eventsCounter, address, size );
              }
              break;

            case Events.Freed:
              {
                ulong address = (ulong)reader.ReadUInt32();
                e = new Freed( ++eventsCounter, address );
              }
              break;
          }
        }

        reader.BaseStream.Position = initialPosition + (long)blockSize;
        return new KeyValuePair<ulong, Event>( time, e );
      }
    }    
  }
}