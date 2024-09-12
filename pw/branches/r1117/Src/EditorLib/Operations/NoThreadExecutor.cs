using System;

namespace EditorLib.Operations
{
	public sealed class NoThreadExecutor : Executor
	{
		public override void Start( params Executor.OperationHandler[] operations )
		{
			foreach ( OperationHandler operation in operations )
			{
				if ( !ProcessOperation( operation ) )
					return;
			}
		}
	}
}
