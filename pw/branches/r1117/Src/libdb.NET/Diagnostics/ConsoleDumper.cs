using System;
using System.Collections.Generic;
using System.Text;
using libdb.Diagnostics;

namespace libdb.Diagnostics
{
	public class ConsoleDumper : IDumper
	{
		public void Trace( Log.Level level, TimeSpan time, int threadId, string fileName, int lineNumber, string message )
		{
			switch ( level )
			{
			case Log.Level.Error:
				Console.Write( "Error: " );
				Console.WriteLine( message );
				Console.Error.WriteLine( message );
				break;
			case Log.Level.Warning:
				Console.Write( "Warning: " );
				Console.WriteLine( message );
				break;
			case Log.Level.Information:
				Console.WriteLine( message );
				break;
			}
		}
	}
}
