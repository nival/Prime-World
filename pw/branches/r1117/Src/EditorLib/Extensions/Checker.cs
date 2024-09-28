using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;
using EditorLib.Operations;
using libdb.Diagnostics;

namespace EditorLib.Extensions
{
	public interface IChecker
	{
    bool CanFixErrors { get; }
    void Check( DBID id, IEditorCommonApplication application, bool fixErrors );
    bool CheckImmediate( DBID id, IEditorCommonApplication application, bool fixErrors );
	}

  public abstract class Checker<T> : IChecker where T : DBResource, new()
	{
		#region IChecker realization

    public void Check( DBID id, IEditorCommonApplication application, bool fixErrors )
		{
			// check type validation...
			this.application = application;
			try
			{
				resource = DataBase.Get<T>( id );
        ShouldFixErrors = fixErrors && CanFixErrors;
				application.OperationExecutor.Start( new Executor.OperationHandler[1] { Start } );
			}
			catch ( Exception e )
			{
				Log.TraceError( "Cannot execute checker \"{0}\" for DBID \"{3}\". Exception {1}: {2}", ToString(), e.ToString(), e.Message, id.Name );
			}
		}

    public bool CheckImmediate( DBID id, IEditorCommonApplication application, bool fixErrors )
    {
      // check type validation...
      this.application = application;
      try
      {
        resource = DataBase.Get<T>( id );
        ShouldFixErrors = fixErrors && CanFixErrors;
        return Process( resource, application );
      }
      catch ( Exception e )
      {
        Log.TraceError( "Cannot execute checker \"{0}\" for DBID \"{3}\". Exception {1}: {2}", ToString(), e.ToString(), e.Message, id.Name );
        return false;
      }
    }

		#endregion

		#region IChecker

		private DBPtr<T> resource;
		private IEditorCommonApplication application;
		private IOperationContext context;

		private bool Start( IOperationContext context )
		{
			this.context = context;

			context.Start( KnownDuration, true );
			return Process( resource, application );
		}

		protected void Progress( string message ) { context.Progress( message ); }
		protected void Progress( string message, int progress ) { context.Progress( message, progress ); }

		#endregion

    public abstract bool CanFixErrors { get; }

    protected bool ShouldFixErrors { get; private set; }

    protected abstract bool KnownDuration { get; }

		protected abstract bool Process( DBPtr<T> resource, IEditorCommonApplication application );
	}
}
