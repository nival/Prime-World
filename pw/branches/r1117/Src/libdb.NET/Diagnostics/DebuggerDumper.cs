using System;
using libdb.Diagnostics;
using System.Diagnostics;

namespace libdb.Diagnostics
{
	public sealed class DebuggerDumper : IDumper
	{
		private bool ignoreAssets = false;

		public DebuggerDumper( bool _ignoreAsserts )
		{
			ignoreAssets = _ignoreAsserts;
		}

    [DebuggerNonUserCode, DebuggerHidden]
		public void Trace( Log.Level level, TimeSpan time, int threadId, string fileName, int lineNumber, string message )
		{
			string fileNameAndLine = string.Empty;
			if ( !string.IsNullOrEmpty( fileName ) )
			{
				if ( lineNumber <= 0 )
					fileNameAndLine = string.Format( "{0}", fileName );
				else
					fileNameAndLine = string.Format( "{0}({1})", fileName, lineNumber );
			}

			switch ( level )
			{
			case Log.Level.Error:
			case Log.Level.Warning:
			case Log.Level.Information:
        Debugger.Log( 0, fileNameAndLine, string.Format( "{0}: {1}\n", level, message ) );
				break;
			case Log.Level.Debug:
        Debugger.Log( 0, fileNameAndLine, message );
        Debugger.Log( 0, fileNameAndLine, "\n" );
				break;
			case Log.Level.Assert:
        Debugger.Log( 0, fileNameAndLine, message );
        Debugger.Log( 0, fileNameAndLine, "\n" );
        if ( Debugger.IsAttached && !ignoreAssets )
					Debugger.Break();
				break;
			}
		}
	}
}
