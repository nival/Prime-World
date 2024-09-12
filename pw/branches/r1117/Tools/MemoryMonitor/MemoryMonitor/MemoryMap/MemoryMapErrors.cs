using System;
using System.Collections.Generic;
using System.Text;
using MemoryMonitor.EventLog;

namespace MemoryMonitor.Memory
{
  internal class AllocationOverlapException : Exception
  {
    // EventAlloc attempted to allocate memory that is already allocated
  }

  internal class AllocationIntegrityException : Exception
  {
    // EventAlloc was passed to a node that does not need it
  }

  internal class DeallocationMissException : Exception
  {
    // EventFree without matching EventAlloc
  }
}