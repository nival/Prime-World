using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using System.IO;
using Zzima;
using MSUtil;
using LogQuery = MSUtil.LogQueryClassClass;
using EventLogInputFormat = MSUtil.COMEventLogInputContextClassClass;
using LogRecordSet = MSUtil.ILogRecordset;
using CodeEngine.Framework.QueryBuilder;
using CodeEngine.Framework.QueryBuilder.Enums;
using System.Threading;
using System.Diagnostics;
using System.ServiceModel;
using log4net;
using log4net.Config;

namespace DockSample
{
  [ServiceBehavior( ConcurrencyMode = ConcurrencyMode.Reentrant, InstanceContextMode = InstanceContextMode.Single )]
  public partial class DummyDoc : DockContent, IFromClientToServerMessages
  {
    int defaultTop = 100;
    const int maxBytesWithoutVirtualMode = 200000000;
    //const int maxBytesWithoutVirtualMode = 1000;
    const string outputFile = "PWLogResultGrid.tsv";
    List<string> levels = new List<string> { "any", "d: debug", "m: message", "w: warning", "e: error", "a: assert", "c: critical" };

    List<PWLogRecord> resultSet = null;
    string currentQuery;
    BackgroundWorker backgroundWorker = new BackgroundWorker();
    bool nowQuerying = false;
    //private static readonly ILog log = LogManager.GetLogger( typeof( DummyDoc ) );
    public DummyDoc()
    {
      //BasicConfigurator.Configure();
      InitializeComponent();
      chkEnableTime.Checked = false;
      //cmbThreadOperator.DataSource = Enum.GetValues(typeof(Comparison));
      cmbThreadOperator.DataSource = new List<Comparison> { Comparison.Equals, Comparison.NotEquals };
      cmbChannelOperator.DataSource = new List<Comparison> { Comparison.Equals, Comparison.NotEquals, Comparison.Like, Comparison.NotLike };
      //cmbLevelOperator.DataSource = Enum.GetValues(typeof(Comparison));
      cmbMessageOperator.DataSource = new List<Comparison> { Comparison.Equals, Comparison.NotEquals, Comparison.Like, Comparison.NotLike };

      cmbLogLevel.DataSource = levels;
      cmbLogLevel.SelectedItem = "any";

      backgroundWorker.WorkerReportsProgress = true;
      backgroundWorker.WorkerSupportsCancellation = true;
      backgroundWorker.ProgressChanged += new ProgressChangedEventHandler( bwAsync_ProgressChanged );
      backgroundWorker.RunWorkerCompleted += new RunWorkerCompletedEventHandler( bwAsync_RunWorkerCompleted );
      txtTopRecords.Text = defaultTop.ToString();
      backgroundWorker.DoWork += new DoWorkEventHandler( bwAsync_DoWork );

      //wcf service for ipc
      clientGuid = Guid.NewGuid();
      serverHost = new ServiceHost( this );
      serverHost.AddServiceEndpoint( ( typeof( IFromClientToServerMessages ) ), new NetNamedPipeBinding(), "net.pipe://localhost/Server" + clientGuid.ToString() );
      serverHost.Open();
    }
    private void NotifyPluginToCancel()
    {
      using ( ChannelFactory<IFromServerToClientMessages> factory = new ChannelFactory<IFromServerToClientMessages>( new NetNamedPipeBinding(), new EndpointAddress( "net.pipe://localhost/Client" + clientGuid.ToString() ) ) )
      {
        IFromServerToClientMessages serverToClientChannel = factory.CreateChannel();
        try
        {
          serverToClientChannel.NotifyNeedToCancel( true );
        }
        catch ( Exception ex )
        {
          MessageBox.Show( ex.ToString() );
        }
        finally
        {
          CloseChannel( (ICommunicationObject)serverToClientChannel );
        }
      }
    }

    private void btnExecuteQuery_Click( object sender, EventArgs e )
    {
      dgvResult.DataSource = null;
      if ( backgroundWorker.IsBusy )
      {
        TurnQueryButtons( false );
        lblStatus.Text = "Canceling...";
        NotifyPluginToCancel();
        nowQuerying = false;
        backgroundWorker.CancelAsync();
        ( (MainForm)ParentForm ).UnlockPluginAtMain();
      }
      else
      {
        bool pluginIsAccessible = ((MainForm)ParentForm).LockPluginAtMain();
        nowQuerying = true;
        if ( ! pluginIsAccessible )
        {
          MessageBox.Show( "QueryEngine is busy with other file" );
          return;
        }
        
        currentQuery = txtCurrentQuery.Text;
        btnApplyFilter.Text = "Cancel";
        btnExecuteQuery.Text = "Cancel";
        lblStatus.Text = "";
        progressBar.Visible = true;
        // Kickoff the worker thread to begin it's DoWork function.
        backgroundWorker.RunWorkerAsync();
      }
    }
    //Stopwatch sw;
    private void bwAsync_DoWork( object sender, DoWorkEventArgs e )
    {
      BackgroundWorker bwAsync = sender as BackgroundWorker;
      PWLogPlugin inputFormat = null;
      bwAsync.ReportProgress( 0 );
      //COMTSVOutputContextClassClass outputFormat = null;
      resultSet = new List<PWLogRecord>();
      try
      {
        LogQuery logQuery = new LogQuery();
        inputFormat = new PWLogPlugin( clientGuid );
        //sw = Stopwatch.StartNew();

        //воткнуть в currentQuery output
        currentQuery = currentQuery.ReplaceFirst( "FROM", "into " + outputFile + " FROM" );
        logQuery.ExecuteBatch( currentQuery, inputFormat, null );
        //MessageBox.Show(sw.Elapsed.ToString() + " millisec");
        if ( bwAsync.CancellationPending )
        {
          inputFormat.CloseInput( false );
          // Set the e.Cancel flag so that the WorkerCompleted event
          // knows that the process was canceled.
          e.Cancel = true;
          return;
        }
        ////считываем из tsv файла
        PrepareDataForGrid();
      }
      finally
      {
        //MessageBox.Show( "Time" + sw.Elapsed );
        if ( inputFormat != null )
          inputFormat.CloseInput( true );
        nowQuerying = false;
        ( (MainForm)ParentForm ).UnlockPluginAtMain();
      }
    }
    private void ShowDataInGrid()
    {
      dgvResult.DataSource = resultSet;
      dgvResult.Columns[4].Width = 800;
      lblStatus.Text = "Completed";
    }
    private void PrepareDataForGrid()
    {
      if ( File.Exists( outputFile ) )
      {
        FileInfo fInfo = new FileInfo( outputFile );
        if ( fInfo.Length <= maxBytesWithoutVirtualMode )
        {
          bool firstLine = true;
          FileStream fOut = new FileStream( outputFile, FileMode.Open );
          StreamReader r = new StreamReader( fOut, System.Text.Encoding.ASCII );
          string line = "start";
          string[] input;
          PWLogRecord pwLine;
          do
          {
            if ( firstLine ) //TODO сделать норм output без хидеров
            {
              firstLine = false;
              r.ReadLine();
              continue;
            }
            line = r.ReadLine();
            if ( line == null )
              break;
            if ( line == "\t\t\t\t" )
              continue;
            if ( line == "" )
              continue;
            input = line.Split( '\t' );
            if ( input.Length == 5 )
            {
              pwLine = new PWLogRecord( input[0], input[1], input[2], input[3], input[4] );
              resultSet.Add( pwLine );
            }
          } while ( line != null );
          r.Close();
          fOut.Close();
        }
        else//в виртуальном режиме
        {
          throw new Exception( "Результат запроса сохранен в файле " + outputFile );
        }
        //File.Delete(outputFile);
      }
      //else
      //{
      //    throw new Exception("Отсутствует файл с результатом запроса " + outputFile);
      //}
      backgroundWorker.ReportProgress( 100 );
    }

    private void bwAsync_ProgressChanged( object sender, ProgressChangedEventArgs e )
    {
      progressBar.Value = e.ProgressPercentage;
    }
    private void bwAsync_RunWorkerCompleted( object sender, RunWorkerCompletedEventArgs e )
    {
      // The background process is complete. We need to inspect 
      // our response to see if an error occured, a cancel was 
      // requested or if we completed succesfully.
      // Check to see if an error occured in the 
      // background process.
      if ( e.Error != null )
      {
        int hresult = System.Runtime.InteropServices.Marshal.GetHRForException( e.Error );
        //log.DebugFormat("hresult : {0}, e.Error : {1}", hresult.ToString(), e.Error.ToString());
        if ( hresult == -2147221164 )
        {
          lblStatus.Text = ( String.Format( "Проверьте правильность установки LogParser 2.2\n{0}\n\n{1}",
         "http://www.microsoft.com/download/en/details.aspx?displaylang=en&id=24659", e.Error.Message.ToString() ) );
        }
        else if ( hresult == -2147023281 ) //error parsing query)
        {
          lblStatus.Text = "Error parsing query";
        }
        else
        {
          lblStatus.Text = e.Error.Message.ToString();
        }
      }
      else
      {
        // Check to see if the background process was cancelled.
        if ( e.Cancelled )
        {
          lblStatus.Text = "Cancelled";
        }
        else
        {
          ShowDataInGrid();
        }
      }
      progressBar.Visible = false;
      btnApplyFilter.Text = "Apply Filter";
      btnExecuteQuery.Text = "Execute Query";
      TurnQueryButtons( true );
    }

    private string GetQueryFromFilter( string filePath )
    {
      SelectQueryBuilder query = new SelectQueryBuilder();
      query.SelectFromTable( filePath );
      query.SelectAllColumns();
      if ( !String.IsNullOrEmpty( txtTopRecords.Text ) )
      {
        int top = 0;
        Int32.TryParse( txtTopRecords.Text, out top );
        if ( top > 0 )
          query.TopRecords = top;
      }

      if ( txtThreadId.Text.Length > 0 )
        query.AddWhere( "Thread", (Comparison)cmbThreadOperator.SelectedItem, txtThreadId.Text );
      if ( chkEnableTime.Checked )
      {
        query.AddWhere( "Time", Comparison.GreaterOrEquals, String.Format( "{0}:{1}:{2}.000", dateFrom.Value.Hour.IntTo2Signs(), dateFrom.Value.Minute.IntTo2Signs(), dateFrom.Value.Second.IntTo2Signs() ) );
        query.AddWhere( "Time", Comparison.LessOrEquals, String.Format( "{0}:{1}:{2}.999", dateTo.Value.Hour.IntTo2Signs(), dateTo.Value.Minute.IntTo2Signs(), dateTo.Value.Second.IntTo2Signs() ) );
      }
      if ( txtChannel.Text.Length > 0 )
      {
        if ( (Comparison)cmbChannelOperator.SelectedItem == Comparison.Like || (Comparison)cmbChannelOperator.SelectedItem == Comparison.NotLike )
        {
          if ( txtChannel.Text.Contains( "%" ) )
            query.AddWhere( "Channel", (Comparison)cmbChannelOperator.SelectedItem, txtChannel.Text.ToUpper() );
          else
            query.AddWhere( "Channel", (Comparison)cmbChannelOperator.SelectedItem, string.Format( "%{0}%", txtChannel.Text.ToUpper() ) );
        }
        else
          query.AddWhere( "Channel", (Comparison)cmbChannelOperator.SelectedItem, txtChannel.Text.ToUpper() );
      }
      if ( cmbLogLevel.SelectedItem.ToString() != "any" )
      {
        //MessageBox.Show(cmbLogLevel.SelectedItem + " index: " + levels.IndexOf(cmbLogLevel.SelectedItem.ToString(), 0, levels.Count));
        int minimalLevel = levels.IndexOf( cmbLogLevel.SelectedItem.ToString(), 0, levels.Count );
        string[] toComparison = new string[levels.Count - minimalLevel];
        for ( int i = minimalLevel; i < levels.Count; i++ )
        {
          toComparison[( levels.Count - 1 ) - i] = levels[i].Substring( 0, 2 );
        }
        query.AddWhere( "Level", Comparison.In, toComparison );
        //query.AddWhere("Level", Comparison.Equals, cmbLogLevel.SelectedItem);
        //vels.
      }
      if ( txtMessage.Text.Length > 0 )
      {
        if ( (Comparison)cmbMessageOperator.SelectedItem == Comparison.Like || (Comparison)cmbMessageOperator.SelectedItem == Comparison.NotLike )
        {
          if (txtMessage.Text.Contains( "%" ) )
            query.AddWhere( "Message", (Comparison)cmbMessageOperator.SelectedItem, txtMessage.Text.ToUpper() );
          else
            query.AddWhere( "Message", (Comparison)cmbMessageOperator.SelectedItem, string.Format( "%{0}%", txtMessage.Text.ToUpper() ) );
        }
        else
          query.AddWhere( "Message", (Comparison)cmbMessageOperator.SelectedItem, txtMessage.Text.ToUpper() );
      }

      return query.BuildQuery();
    }

    private string currentFile = string.Empty;
    public string FileName
    {
      get { return currentFile; }
      set
      {
        //if (value != string.Empty)
        //{
        //    Stream s = new FileStream(value, FileMode.Open);
        //    FileInfo efInfo = new FileInfo(value);
        //    string fext = efInfo.Extension.ToUpper();
        //    if (fext.Equals(".RTF"))
        //        richTextBox1.LoadFile(s, RichTextBoxStreamType.RichText);
        //    else
        //        richTextBox1.LoadFile(s, RichTextBoxStreamType.PlainText);
        //    s.Close();
        //}
        currentFile = value;
        this.ToolTipText = value;
        lblCurrentFile.Text = value;
      }
    }

    protected override string GetPersistString()
    {
      // Add extra information into the persist string for this document
      // so that it is available when deserialized.
      return GetType().ToString() + "," + FileName + "," + Text;
    }

    private void menuItemCheckTest_Click( object sender, System.EventArgs e )
    {
      menuItemCheckTest.Checked = !menuItemCheckTest.Checked;
    }

    private void chkEnableTime_CheckedChanged( object sender, EventArgs e )
    {
      dateFrom.Enabled = dateTo.Enabled = chkEnableTime.Checked;
      ZeroDateTime();
    }
    private void ZeroDateTime()
    {
      dateFrom.Value = new DateTime( 2000, 01, 01, 00, 00, 00 );
      dateTo.Value = new DateTime( 2000, 01, 01, 23, 59, 59, 999 );
    }

    private void btnClearFilter_Click( object sender, EventArgs e )
    {
      txtThreadId.Text = "";
      dateFrom.Value = new DateTime( 2000, 01, 01, 00, 00, 00, 000 );
      dateTo.Value = new DateTime( 2000, 01, 01, 23, 59, 59, 999 );
      chkEnableTime.Checked = false;
      txtChannel.Text = "";
      cmbLogLevel.SelectedItem = "any";
      txtMessage.Text = "";
      txtCurrentQuery.Text = "";
      cmbThreadOperator.SelectedIndex = 0;
      //cmbLevelOperator.SelectedIndex = 0;
      cmbChannelOperator.SelectedIndex = 0;
      cmbMessageOperator.SelectedIndex = 0;
      txtTopRecords.Text = defaultTop.ToString();
    }

    private void TurnQueryButtons( bool action )
    {
      if ( action )
      {
        btnApplyFilter.Enabled = true;
        btnExecuteQuery.Enabled = true;
      }
      else
      {
        btnApplyFilter.Enabled = false;
        btnExecuteQuery.Enabled = false;
      }
    }

    private void btnApplyFilter_Click( object sender, EventArgs e )
    {
      //плагин на вход не терпит не-utf пробелов в пути к файлу
      txtCurrentQuery.Text = GetQueryFromFilter( currentFile.Replace( " ", "\\u0020" ) );
      btnExecuteQuery_Click( null, null );
    }

    private void btnSaveQuery_Click( object sender, EventArgs e )
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();

      saveFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
      saveFileDialog.FilterIndex = 2;
      saveFileDialog.RestoreDirectory = true;

      if ( saveFileDialog.ShowDialog() == DialogResult.OK )
      {
        try
        {
          File.WriteAllText( saveFileDialog.FileName, txtCurrentQuery.Text );
        }
        catch ( Exception ex )
        {
          MessageBox.Show( "Could not save file. Error : " + ex.Message );
        }
      }
    }

    private void btnLoadQuery_Click( object sender, EventArgs e )
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.InitialDirectory = Application.ExecutablePath;
      openFileDialog.Filter = "All files (*.*)|*.*|txt files (*.txt)|*.txt";
      openFileDialog.FilterIndex = 1;
      openFileDialog.RestoreDirectory = true;

      if ( openFileDialog.ShowDialog() == DialogResult.OK )
      {
        Stream queryStream = null;
        try
        {
          if ( ( queryStream = openFileDialog.OpenFile() ) != null )
          {
            using ( queryStream )
            {
              txtCurrentQuery.LoadFile( queryStream, RichTextBoxStreamType.PlainText );
            }
          }
        }
        catch ( Exception ex )
        {
          MessageBox.Show( "Could not read file. Error : " + ex.Message );
        }
      }
    }
    private void menuItemClose_Click( object sender, EventArgs e )
    {
      this.Close();
    }

    //ipc with wcf
    ServiceHost serverHost;
    Guid clientGuid;

    public void ReportProgress( int gotPercent )
    {
      backgroundWorker.ReportProgress( gotPercent );
    }

    private void CloseChannel( ICommunicationObject channel )
    {
      try
      {
        channel.Close();
      }
      catch ( Exception ex )
      {
        MessageBox.Show( ex.ToString() );
      }
      finally
      {
        channel.Abort();
      }
    }

    private void DummyDoc_FormClosing( object sender, FormClosingEventArgs e )
    {
      ( (MainForm)ParentForm ).UnlockPluginAtMain();
      if (nowQuerying)
      {
        NotifyPluginToCancel();
        backgroundWorker.CancelAsync();
        ( (MainForm)ParentForm ).UnlockPluginAtMain();
      //TurnQueryButtons( false );
      //lblStatus.Text = "Canceling...";
      //NotifyPluginToCancel();
      //nowQuerying = false;
      //backgroundWorker.CancelAsync();
      //( (MainForm)ParentForm ).UnlockPluginAtMain();
      }
      serverHost.Close();
    }
  }
}