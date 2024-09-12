using System;

namespace EditorLib.Operations
{
	public abstract partial class Executor
	{
		private ExecutorOperationContext context = null;

		public Executor()
		{
			context = new ExecutorOperationContext();
			context.StartOperationEvent += new ExecutorOperationContext.StartOperationEventHandler( OnStartOperationEvent );
			context.ProgressOperationEvent += new ExecutorOperationContext.ProgressOperationEventHandler( OnProgressOperationEvent );
		}

		private void OnStartOperationEvent( bool knownDuration, bool blockInterface )
		{
			if ( StartOperationEvent != null )
				StartOperationEvent( knownDuration, blockInterface );
		}

		private void OnProgressOperationEvent( string message, int progress )
		{
			if ( ProgressOperationEvent != null )
				ProgressOperationEvent( message, progress );
		}

		protected void OnFinishAllOperation( bool success )
		{
			if ( FinishAllOperationEvent != null )
				FinishAllOperationEvent( success );
		}

		protected bool ProcessOperation( OperationHandler operation )
		{
			context.Reset();
			bool success = operation( context );
			if ( context.IsStartCalled )
			{
				if ( FinishOperationEvent != null )
					FinishOperationEvent( success );
			}

			return success;
		}

		public delegate bool OperationHandler( IOperationContext context );
		public abstract void Start( params OperationHandler[] operations );

		public delegate void StartOperationEventHandler( bool knownDuration, bool blockInterface );
		public event StartOperationEventHandler StartOperationEvent = null;
		
		public delegate void ProgressOperationEventHandler( string messagge, int progress );
		public event ProgressOperationEventHandler ProgressOperationEvent = null;
		
		public delegate void FinishOperationEventHandler( bool success );
		public event FinishOperationEventHandler FinishOperationEvent = null;

		public event FinishOperationEventHandler FinishAllOperationEvent = null;
	}
}
