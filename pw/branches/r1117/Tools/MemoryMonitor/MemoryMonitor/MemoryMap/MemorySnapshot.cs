using System;
using System.Collections.Generic;
using System.Text;

namespace MemoryMonitor.Memory
{
    public class Snapshot
    {
      private Node root = null;
      private UInt32 time = 0;
      public UInt32 Time { get { return time; } }
      private long filePos = 0;
      public long FilePosition { get { return filePos; } }
      private int events = 0;
      public int EventsSincePrevious { get { return events; } }

      public Snapshot( Node src, UInt32 _time, long _filePos, int eventsSincePrev )
      {
        time = _time;
        filePos = _filePos;
        root = src.Clone();
        events = eventsSincePrev;
      }

      public Node Restore()
      {
        return root.Clone();
      }
    }
}
