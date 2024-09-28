namespace MemoryMonitor
{
  namespace Events
  {
    public class Event
    {
      private readonly string message = string.Empty;
      private readonly ulong id = ulong.MinValue;
      private readonly byte[] data = null;
      
      public string Message { get { return message; } }
      public byte[] Data { get { return data; } }
      public ulong Id { get { return id; } }

      public Event( ulong id, string message )
      {
        this.id = id;
        this.message = message;
      }

      public Event( ulong id, string message, byte[] data )
        : this( id, message )
      {
        this.data = data;
      }
    };

    public class Allocation : Event
    {
      private readonly ulong address;
      private readonly ulong size;

      public ulong Address { get { return address; } }
      public ulong Size { get { return size; } }

      public Allocation( ulong id, ulong address, ulong size )
        : this( id, address, size, string.Empty )
      {
      }

      public Allocation( ulong id, ulong address, ulong size, string message )
        : this( id, address, size, message, null )
      {
      }

      public Allocation( ulong id, ulong address, ulong size, string message, byte[] data )
        : base( id, message, data )
      {
        this.address = address;
        this.size = size;
      }
    };

    public class Freed : Event
    {
      private readonly ulong address;      
      public ulong Address { get { return address; } }

      public Freed( ulong id, ulong address )
        : this( id, address, string.Empty )
      {
      }

      public Freed( ulong time, ulong address, string message )
        : this( time, address, message, null )
      {
      }

      public Freed( ulong id, ulong address, string message, byte[] data )
        : base( id, message, data )
      {
        this.address = address;
      }
    };
  }
}
