using System.Diagnostics;

namespace LocKit
{
  public class DebugTraceListener : TraceListener
  {
    public override void Write( string message )
    {
      Debugger.Log( 0, string.Empty, message );
    }

    public override void WriteLine( string message )
    {
      Debugger.Log( 0, string.Empty, message );
      Debugger.Log( 0, string.Empty, "\n" );
    }

    public override void Write( string message, string category )
    {
      Debugger.Log( 0, category, message );
    }

    public override void WriteLine( string message, string category )
    {
      Debugger.Log( 0, category, message );
      Debugger.Log( 0, category, "\n" );
    }

    [DebuggerNonUserCode, DebuggerHidden]
    public override void TraceEvent( TraceEventCache eventCache, string source, TraceEventType eventType, int id )
    {
      TraceEvent( eventCache, source, eventType, id, string.Empty );
    }

    [DebuggerNonUserCode, DebuggerHidden]
    public override void TraceEvent( TraceEventCache eventCache, string source, TraceEventType eventType, int id, string format, params object[] args )
    {
      TraceEvent( eventCache, source, eventType, id, string.Format( format, args ) );
    }

    [DebuggerNonUserCode, DebuggerHidden]
    public override void TraceEvent( TraceEventCache eventCache, string source, TraceEventType eventType, int id, string message )
    {
      string fileNameAndLine = string.Empty;

      StackTrace stack = new StackTrace( 3, true );
      if ( stack.FrameCount > 0 )
      {
        StackFrame frame = stack.GetFrame( 0 );
        fileNameAndLine = frame.GetFileName() + "(" + frame.GetFileLineNumber().ToString() + ")";
        Debugger.Log( 0, fileNameAndLine, fileNameAndLine );
        Debugger.Log( 0, fileNameAndLine, ": " );
      }

      if ( ( eventType | TraceEventType.Critical ) == TraceEventType.Critical )
      {
        Debugger.Log( 0, fileNameAndLine, TraceEventType.Critical.ToString() );
        Debugger.Log( 0, fileNameAndLine, ": " );
      }
      else if ( ( eventType | TraceEventType.Error ) == TraceEventType.Error )
      {
        Debugger.Log( 0, fileNameAndLine, TraceEventType.Error.ToString() );
        Debugger.Log( 0, fileNameAndLine, ": " );
      }
      else if ( ( eventType | TraceEventType.Warning ) == TraceEventType.Warning )
      {
        Debugger.Log( 0, fileNameAndLine, TraceEventType.Warning.ToString() );
        Debugger.Log( 0, fileNameAndLine, ": " );
      }

      Debugger.Log( 0, fileNameAndLine, message );
      Debugger.Log( 0, fileNameAndLine, "\n" );
    }
  }
}