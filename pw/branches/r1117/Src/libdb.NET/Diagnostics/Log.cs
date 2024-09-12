using System;
using System.Collections.Generic;
using libdb.Diagnostics;
using System.Threading;
using System.Diagnostics;

namespace libdb.Diagnostics
{
	public static class Log
	{
		public enum Level
		{
			Error,
			Warning,
			Information,

			Assert,
			Debug,
		}

		private static readonly DateTime startTime = DateTime.Now;
    private static readonly object lockObject = new object();
		private static volatile List<IDumper> dumpers = new List<IDumper>();

		public static void AttachDumper( IDumper dumper )
		{
      lock( lockObject )
			{
				dumpers.Add( dumper );
			}
		}

    public static bool DetachDumper( IDumper dumper )
    {
      bool result = false;

      lock( lockObject )
      {
        result = dumpers.Remove( dumper );
      }

      return result;
    }

		[DebuggerNonUserCode, DebuggerHidden]
		private static void Trace( Log.Level level, string message )
		{
			string fileName = string.Empty;
			int lineNumber = -1;

			StackTrace stack = new StackTrace( 1, true );
			if ( stack.FrameCount > 0 )
			{
				StackFrame frame = stack.GetFrame( 1 );
				fileName = frame.GetFileName();
				lineNumber = frame.GetFileLineNumber();
			}

      Trace( fileName, lineNumber, level, message );
		}

    [DebuggerNonUserCode, DebuggerHidden]
    public static void Trace( string fileName, int lineNumber, Log.Level level, string message )
    {
      TimeSpan time = DateTime.Now - startTime;
      int threadId = Thread.CurrentThread.ManagedThreadId;
      lock( lockObject )
      {
        foreach ( IDumper dumper in dumpers )
          dumper.Trace( level, time, threadId, fileName, lineNumber, message );
      }
    }

		[DebuggerNonUserCode, DebuggerHidden]
		public static bool Assert( bool expresssion )
		{
			if ( expresssion )
				return false;

			Trace( Level.Assert, string.Empty );
			return true;
		}

		[DebuggerNonUserCode, DebuggerHidden]
		public static bool Assert( bool expresssion, string message )
		{
			if ( expresssion )
				return false;

			Trace( Level.Assert, message );
			return true;
		}

		[DebuggerNonUserCode, DebuggerHidden]
		public static bool Assert( bool expresssion, string format, params object[] args )
		{
			if ( expresssion )
				return false;

			Trace( Level.Assert, string.Format( format, args ) );
			return true;
		}

		[DebuggerNonUserCode, DebuggerHidden]
		public static bool AlwaysAssert( string message )
		{
			Trace( Level.Assert, message );
			return true;
		}

		[DebuggerNonUserCode, DebuggerHidden]
		public static bool AlwaysAssert( string format, params object[] args )
		{
			Trace( Level.Assert, string.Format( format, args ) );
			return true;
		}

		public static void TraceError( string message )
		{
			Trace( Level.Error, message );
		}

		public static void TraceError( string format, params object[] args )
		{
			Trace( Level.Error, string.Format( format, args ) );
		}

		public static void TraceWarning( string message )
		{
			Trace( Level.Warning, message );
		}

		public static void TraceWarning( string format, params object[] args )
		{
			Trace( Level.Warning, string.Format( format, args ) );
		}

		public static void TraceMessage( string message )
		{
			Trace( Level.Information, message );
		}

		public static void TraceMessage( string format, params object[] args )
		{
			Trace( Level.Information, string.Format( format, args ) );
		}

		public static void TraceDebug( string message )
		{
#if DEBUG
			Trace( Level.Debug, message );
#endif
		}

		public static void TraceDebug( string format, params object[] args )
		{
#if DEBUG
			Trace( Level.Debug, string.Format( format, args ) );
#endif
		}

//    public static void TraceMessage( string message )
//    {
//#if TRACE
//      Trace( Level.Message, message );
//#endif
//    }

//    public static void TraceMessage( string format, params object[] args )
//    {
//#if TRACE
//      Trace( Level.Message, string.Format( format, args ) );
//#endif
//    }
	}
}
