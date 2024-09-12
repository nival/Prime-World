using System;
using libdb.Diagnostics;

namespace EditorLib.Operations
{
	public abstract partial class Executor
	{
		internal sealed class ExecutorOperationContext: IOperationContext
		{
			private int lastProgress = 0;
			private bool knownDuration = false;
			private bool startCalled = false;

			public delegate void StartOperationEventHandler( bool knownDuration, bool blockInterface );
			public event StartOperationEventHandler StartOperationEvent = null;

			public delegate void ProgressOperationEventHandler( string message, int progress );
			public event ProgressOperationEventHandler ProgressOperationEvent = null;

			public void Reset() { startCalled = false; knownDuration = false; lastProgress = 0; }
			public bool IsStartCalled { get { return startCalled; } }

			#region IOperationContext Members

			public void Start( bool _knownDuration, bool _blockInterface )
			{
				startCalled = true;
				lastProgress = 0;
				knownDuration = _knownDuration;
				if ( StartOperationEvent != null )
					StartOperationEvent( _knownDuration, _blockInterface );
			}

			public void Progress( string _message )
			{
				if ( ProgressOperationEvent != null )
					ProgressOperationEvent( _message, lastProgress );
			}

			public void Progress( string _message, int _progress )
			{
				if ( knownDuration )
					lastProgress = _progress;
				else
					Log.TraceWarning( "Operation without known duration cannot update its progress" );

				Progress( _message );
			}

			#endregion
		}
	}
}
