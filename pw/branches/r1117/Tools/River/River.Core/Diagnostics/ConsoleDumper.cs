using System;

namespace River.Core.Diagnostics
{
	public class ConsoleDumper : IDumper
	{
		private readonly bool showInfo = true;
		private readonly bool showWarn = true;

		public ConsoleDumper( bool showInfo, bool showWarn )
		{
			this.showInfo = showInfo;
			this.showWarn = showWarn;
		}

		public void Trace( Log.Level level, TimeSpan time, int threadId, string fileName, int lineNumber, string message )
		{
			if ( level == Log.Level.Error || ( level == Log.Level.Warning && showWarn ) || (level == Log.Level.Information && showInfo ) )
				Console.WriteLine( message );
		}
	}
}
