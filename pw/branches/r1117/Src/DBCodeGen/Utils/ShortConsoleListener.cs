using System;
using System.Diagnostics;

namespace DBCodeGen.Utils
{
  public class ShortConsoleListener : TraceListener
  {
    public enum VerboseLevel
    {
      CriticalsOnly,
      CriticalsAndWarnings,
      All,
    }

    private readonly VerboseLevel level = VerboseLevel.CriticalsAndWarnings;

    public ShortConsoleListener( VerboseLevel _level )
    {
      level = _level;
    }

    public override void Write( string message )
    {
      if ( level == VerboseLevel.All )
        Console.Write( message );
    }

    public override void WriteLine( string message )
    {
      if ( level == VerboseLevel.All )
        Console.WriteLine( message );
    }

    public override void Write( string message, string category )
    {
      Write( category );
      Write( ": " );
      Write( message );
    }

    public override void WriteLine( string message, string category )
    {
      Write( category );
      Write( ": " );
      WriteLine( message );
    }

    public override void TraceEvent( TraceEventCache eventCache, string source, TraceEventType eventType, int id )
    {
      TraceEvent( eventCache, source, eventType, id, string.Empty );
    }

    public override void TraceEvent( TraceEventCache eventCache, string source, TraceEventType eventType, int id, string format, params object[] args )
    {
      TraceEvent( eventCache, source, eventType, id, string.Format( format, args ) );
    }

    public override void TraceEvent( TraceEventCache eventCache, string source, TraceEventType eventType, int id, string message )
    {
      if ( ( eventType | TraceEventType.Critical ) == TraceEventType.Critical )
      {
        Console.Error.Write( TraceEventType.Critical.ToString() );
        Console.Error.Write( ": " );
        Console.Error.WriteLine( message );
      }
      else if ( ( eventType | TraceEventType.Error ) == TraceEventType.Error )
      {
        Console.Error.Write( TraceEventType.Error.ToString() );
        Console.Error.Write( ": " );
        Console.Error.WriteLine( message );
      }
      else if ( ( eventType | TraceEventType.Warning ) == TraceEventType.Warning )
      {
        if ( level != VerboseLevel.All && level != VerboseLevel.CriticalsAndWarnings )
          return;

        Write( TraceEventType.Warning.ToString() );
        Write( ": " );
        WriteLine( message );
      }
      else if ( level != VerboseLevel.All )
        return;

    }
  }
}