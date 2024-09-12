using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace EditorLib.Operations
{
	public sealed class SingleThreadExecutor : Executor
	{
		private List<OperationHandler> operations = new List<OperationHandler>();
		private Thread executorThread = null;
    private bool stop = false;

		private void Do()
		{
			while ( !stop )
			{
				bool hasOperation = false;
				lock (operations)
				{
					hasOperation = operations.Count != 0;
				}

				if ( !hasOperation)
				{           
          Thread.Sleep( 10 ); 
				}
				else
				{
					OperationHandler operation = null;
					lock (operations)
					{
						operation = operations[0];
						operations.RemoveAt(0);
					}
					bool success = ProcessOperation(operation);
					bool finished = false;
					lock (operations)
					{
						if (!success)
							operations.Clear();
						finished = operations.Count == 0;
					}

					if (finished)
					{
						OnFinishAllOperation(success);
					}
				}
			}
		}

		public SingleThreadExecutor()
		{
			executorThread = new Thread( new ThreadStart( Do ) );
		  executorThread.IsBackground = true;
			executorThread.Start();
		}

		public override void Start( params Executor.OperationHandler[] _operations )
		{
			lock ( operations )
			{
				operations.AddRange( _operations );
			}
		}

		public void Stop()
		{
      stop = true;
      if ( !executorThread.Join( 30 * 1000 ) )
        executorThread.Abort();
			lock ( operations )
			{
				operations.Clear();
			}
			OnFinishAllOperation( false );
		}
	}
}