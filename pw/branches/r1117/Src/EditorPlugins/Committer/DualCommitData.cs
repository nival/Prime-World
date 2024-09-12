using System.Collections.Generic;
using System.ComponentModel;
using EditorLib;
using libdb.Diagnostics;

namespace EditorPlugins.Committer
{
  internal class DualCommitData
  {
  	private readonly IEditorWinApplication application;
		private BackgroundWorker getInfoWorker = null;

		public delegate void OperationFinishHandler( bool success );
		public event OperationFinishHandler GetInfoFinished = null;	

		public Dictionary<string, AssetInfo> Assets { get; private set; }

		public DualCommitData( IEditorWinApplication _app )
    {
      Assets = null;
    	application = _app;
    }

    public void StartGetInfo()
    {
      getInfoWorker = new BackgroundWorker();
      getInfoWorker.WorkerSupportsCancellation = true;
      getInfoWorker.DoWork += GetInfoDoWork;
      getInfoWorker.RunWorkerCompleted += GetInfoWorkCompleted;
      getInfoWorker.RunWorkerAsync();
    }

    private void GetInfoDoWork( object sender, DoWorkEventArgs e )
    {
      DualCommitDataCollater collater = new DualCommitDataCollater();

			collater.FindDataChanges( application );
			if ( getInfoWorker.CancellationPending )
      {
        e.Cancel = true;
        return;
      }

			collater.FindSourceChanges( application );
			if ( getInfoWorker.CancellationPending )
      {
        e.Cancel = true;
        return;
      }

			Dictionary<string, AssetInfo> result = collater.Process( getInfoWorker );

      if ( null == result )
        e.Cancel = true;
      else 
        e.Result = result;
    }

    private void GetInfoWorkCompleted( object sender, RunWorkerCompletedEventArgs e )
    {
      bool success = !e.Cancelled && e.Error == null;

      if ( success )
        Assets = e.Result as Dictionary<string, AssetInfo>;
      else
      {
        if ( e.Error != null )
          Log.TraceError( "Error getting SVN Info: {0}", e.Error.ToString() );
      }

      RaiseGetInfoFinished(success);
    }

  	private void RaiseGetInfoFinished(bool _success)
  	{
  		if ( GetInfoFinished != null )
  			GetInfoFinished( _success );
  	}

  	public void Halt()
    {
      if ( getInfoWorker != null && getInfoWorker.IsBusy )
        getInfoWorker.CancelAsync();
    }
  }
}
