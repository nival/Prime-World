using System;

namespace libdb.Diagnostics
{
	public interface IDumper
	{
		void Trace( Log.Level level, TimeSpan time, int threadId, string fileName, int lineNumber, string message );
	}
}
