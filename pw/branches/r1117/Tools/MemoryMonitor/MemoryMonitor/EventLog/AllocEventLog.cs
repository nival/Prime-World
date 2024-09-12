using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace MemoryMonitor.EventLog
{
  public class AllocEventLog
  {
    private FileStream file = null;
    private BinaryReader reader = null;

    private UInt32 eventTypeAlloc = 0;
    private UInt32 eventTypeFree = 0;

    private long firstEventPos = 0;

    public AllocEventLog( string fileName )
    {
      if ( string.IsNullOrEmpty( fileName ) )
        return;

      file = new FileStream( fileName, FileMode.Open, FileAccess.Read, FileShare.ReadWrite );
      reader = new BinaryReader( file );
    }

    public string FileName { get { return ( null != file ) ? file.Name : string.Empty; } }
    public bool IsOpen { get { return file != null && file.CanRead; } }

    public long Length { get { return ( file == null ) ? 0 : file.Length; } }

    private void Rewind( long pos ) { file.Position = pos; }
    public void Rewind() { Rewind( 0 ); }

    public delegate void EventAllocHandler( EventAlloc e, long filePos );
    public delegate void EventFreeHandler( EventFree e, long filePos );

    public event EventAllocHandler EventAllocation;
    public event EventFreeHandler EventDeallocation;

    public long ReadEventsToTime( long startPos, UInt32 time )
    {
      if ( !CheckReadHeaderAndRewind( startPos ) )
        return 0;

      long filePos = 0;
      int entryNo = 0;
      while ( true )
      {
        filePos = file.Position;
        ++entryNo;

        try
        {
          UInt32 eventSize = reader.ReadUInt16();

          UInt32 eventType = reader.ReadUInt32();

          if ( 0 == eventSize )
          {
            if ( 0 == eventType )
              break;

            string eventName = ReadCString();

            //Trace.WriteLine( entryNo.ToString() + ": introducing " + eventType + " - " + eventName );

            if ( eventName == "MemAllocEvent" )
              eventTypeAlloc = eventType;
            else if ( eventName == "MemFreeEvent" )
              eventTypeFree = eventType;

            continue;
          }

          UInt32 eventTime = eventType;

          eventType = reader.ReadUInt32();

          //Trace.WriteLine( entryNo.ToString() + ": time " + eventTime.ToString() + " event " + eventType.ToString() );
          if ( /*time > 0 &&*/ eventTime > time )
            break;

          if ( eventType != eventTypeAlloc && eventType != eventTypeFree )
          {
            file.Seek( eventSize, SeekOrigin.Current );
            continue;
          }

          // Call stack
          UInt32[] callStack = new UInt32[Event.CallStackLength];
          for ( int i = 0; i < Event.CallStackLength; ++i )   
            callStack[i] = reader.ReadUInt32();

          UInt32 eventAddress = reader.ReadUInt32();

          if ( eventType == eventTypeAlloc )
          {
            UInt32 eventAllocLen = reader.ReadUInt32();

            if ( null != EventAllocation )
              EventAllocation( new EventAlloc( eventTime, eventAddress, eventAllocLen, callStack ), filePos );
          }
          else
          {
            if ( null != EventDeallocation )
              EventDeallocation( new EventFree( eventTime, eventAddress, callStack ), filePos );
          }

        }
        catch
        {
          break;
        }
        
      }

      return filePos;
    }

    private bool CheckReadHeaderAndRewind( long startPos )
    {
      if ( startPos == 0 )
      {
        if ( firstEventPos == 0 ) // header not read yet
        {
          try
          {
            firstEventPos = reader.ReadUInt16();

            UInt32 fileVersion = reader.ReadUInt32();

            Event.CallStackLength = (int)reader.ReadUInt32();
          }
          catch
          {
            return false;
          }
        }
        else
          Rewind( firstEventPos );
      }
      else
        Rewind( startPos );

      return true;
    }

    public long ReadEvents( long startPos, int eventsToRead )
    {
      if ( !CheckReadHeaderAndRewind( startPos ) )
        return 0;

      long filePos = 0;
      int eventsLeft = eventsToRead;
      while ( true )
      {
        filePos = file.Position;

        try
        {
          UInt32 eventSize = reader.ReadUInt16();

          UInt32 eventType = reader.ReadUInt32();

          if ( 0 == eventSize )
          {
            if ( 0 == eventType )
              break;

            string eventName = ReadCString();

            //Trace.WriteLine( entryNo.ToString() + ": introducing " + eventType + " - " + eventName );

            if ( eventName == "MemAllocEvent" )
              eventTypeAlloc = eventType;
            else if ( eventName == "MemFreeEvent" )
              eventTypeFree = eventType;

            continue;
          }

          UInt32 eventTime = eventType;

          eventType = reader.ReadUInt32();

          //Trace.WriteLine( entryNo.ToString() + ": time " + eventTime.ToString() + " event " + eventType.ToString() );

          if ( eventType != eventTypeAlloc && eventType != eventTypeFree )
          {
            file.Seek( eventSize, SeekOrigin.Current );
            continue;
          }

          // Call stack
          UInt32[] callStack = new UInt32[Event.CallStackLength];
          for ( int i = 0; i < Event.CallStackLength; ++i )
            callStack[i] = reader.ReadUInt32();

          UInt32 eventAddress = reader.ReadUInt32();

          if ( eventType == eventTypeAlloc )
          {
            UInt32 eventAllocLen = reader.ReadUInt32();

            if ( null != EventAllocation )
              EventAllocation( new EventAlloc( eventTime, eventAddress, eventAllocLen, callStack ), filePos );
          }
          else
          {
            if ( null != EventDeallocation )
              EventDeallocation( new EventFree( eventTime, eventAddress, callStack ), filePos );
          }

          --eventsLeft;
          if ( 0 == eventsLeft )
          {
            filePos = file.Position;
            break;
          }
        }
        catch
        {
          break;
        }

      }

      return filePos;
    }

    private string ReadCString()
    {
      string result = string.Empty;
      while ( true )
      {
        byte c = reader.ReadByte();
        if ( c > 0 )
          result = result + (char)c;
        else
          break;
      }

      return result;
    }
  }
}
