using System;
using System.Collections.Generic;
using System.Text;

namespace FixSln.Diagnostics
{
	public sealed class ConsoleDumper : IDumper
	{
		public void Trace( Log.Level level, TimeSpan time, int threadId, string fileName, int lineNumber, string message )
		{
			if ( level == Log.Level.Error || level == Log.Level.Assert )
				Console.Write( "ERROR: " );
			else if ( level == Log.Level.Warning )
				Console.Write( "WARNING: " );

			Console.WriteLine( message );
		}
	}
}
