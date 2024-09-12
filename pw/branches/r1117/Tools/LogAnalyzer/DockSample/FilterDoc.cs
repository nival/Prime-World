using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using CodeEngine.Framework.QueryBuilder;
using CodeEngine.Framework.QueryBuilder.Enums;
using System.IO;
using System.Diagnostics;
using System.Linq.Expressions;
using System.Reflection;

namespace DockSample
{
  public partial class FilterDoc : DockContent
  {
    int defaultTop = 100;
    List<string> levels = new List<string> { "any", "d:", "m:", "w:", "e:", "a:", "c:" };
    BackgroundWorker backWorker = new BackgroundWorker();
    List<PWLogRecord> resultSet = null;
    private string currentFile;
    private string currentLine;
    Stopwatch sw;
    long approximateLinesQuant;
    int averageLineLength = 75; //средний размер строки = 75
    int quantIntervalToUpdateProgress = 50000;
    Predicate<PWLogRecord> predicate;
    bool trivialPredicate;
    int? setTop;

    public FilterDoc()
    {
      InitializeComponent();
      chkEnableTime.Checked = false;
      //cmbThreadOperator.DataSource = Enum.GetValues(typeof(Comparison));
      cmbThreadOperator.DataSource = new List<Comparison> { Comparison.Equals, Comparison.NotEquals };
      cmbChannelOperator.DataSource = new List<Comparison> { Comparison.Contains, Comparison.NotContains };
      cmbMessageOperator.DataSource = new List<Comparison> { Comparison.Contains, Comparison.NotContains };
      //cmbLevelOperator.DataSource = Enum.GetValues(typeof(Comparison));
      //cmbMessageOperator.DataSource = new List<Comparison> { Comparison.Equals, Comparison.NotEquals, Comparison.Like, Comparison.NotLike, Comparison.In };
      cmbLogLevel.DataSource = levels;
      cmbLogLevel.SelectedItem = "any";
      txtTopRecords.Text = defaultTop.ToString();

      backWorker.WorkerReportsProgress = true;
      backWorker.WorkerSupportsCancellation = true;
      backWorker.ProgressChanged += new ProgressChangedEventHandler( bwAsync_ProgressChanged );
      backWorker.RunWorkerCompleted += new RunWorkerCompletedEventHandler( bwAsync_RunWorkerCompleted );
      backWorker.DoWork += new DoWorkEventHandler( bwAsync_DoWork );
    }

    private void bwAsync_DoWork( object sender, DoWorkEventArgs e )
    {
      BackgroundWorker bwAsync = sender as BackgroundWorker;
      bwAsync.ReportProgress( 0 );
      sw = Stopwatch.StartNew();
      resultSet = new List<PWLogRecord>();
      PWLogRecord lr = new PWLogRecord();
      int fieldCount = 5;
      int linesSelected = 0;
      try
      {
        if ( File.Exists( currentFile ) )
        {
          StreamReader file = null;
          try
          {
            file = new StreamReader( currentFile );
            int countLines = 0;
            FileInfo fInfo = new FileInfo( currentFile );
            approximateLinesQuant = fInfo.Length / averageLineLength;
            while ( ( currentLine = file.ReadLine() ) != null )
            {
              if ( currentLine == "" )
                continue;
              lr.Clear();
              for ( int i = 0; i < fieldCount; i++ )
              {
                object val = GetValue( i );
                if ( i == 0 ) if ( val != null ) lr.Thread = val.ToString();
                if ( i == 1 ) if ( val != null ) lr.Time = val.ToString();
                if ( i == 2 ) if ( val != null ) lr.Channel = val.ToString();
                if ( i == 3 ) if ( val != null ) lr.Level = val.ToString();
                if ( i == 4 ) if ( val != null ) lr.Message = val.ToString();
              }
              if ( ! trivialPredicate )
              {
                if ( predicate( lr ) )
                {
                  resultSet.Add( new PWLogRecord { Thread = lr.Thread, Time = lr.Time, Channel = lr.Channel, Level = lr.Level, Message = lr.Message } );
                  linesSelected++;
                }
              }
              else
              {
                resultSet.Add( new PWLogRecord { Thread = lr.Thread, Time = lr.Time, Channel = lr.Channel, Level = lr.Level, Message = lr.Message } );
                linesSelected++;
              }
              if ( setTop <= linesSelected )
                break;
              countLines++;
              if ( ( countLines % quantIntervalToUpdateProgress ) == 0 )
                bwAsync.ReportProgress( GetCurrentPercentage( countLines ) );
            }
          }
          finally
          {
            if ( file != null )
              file.Close();
          }
        }
        else
          MessageBox.Show( "Файл не найден" );


        //sw = Stopwatch.StartNew();
        //воткнуть в currentQuery output
        //currentQuery = currentQuery.ReplaceFirst( "FROM", "into " + outputFile + " FROM" );
        //MessageBox.Show(sw.Elapsed.ToString() + " millisec");
        if ( bwAsync.CancellationPending )
        {
          ///inputFormat.CloseInput( false );
          // Set the e.Cancel flag so that the WorkerCompleted event
          // knows that the process was canceled.
          e.Cancel = true;
          return;
        }
        ////считываем из tsv файла
        ///PrepareDataForGrid();
      }
      finally
      {
        //MessageBox.Show( "Time" + sw.Elapsed );
        ///if ( inputFormat != null )
        ///  inputFormat.CloseInput( true );
      }
    }
    public int GetCurrentPercentage( long currentLine )
    {
      int result = (int)( ( (double)currentLine / approximateLinesQuant ) * 100 );
      return result > 90 ? 90 : result;
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
        //if ( hresult == -2147023281 ) //error parsing query)
        //{
        //  lblStatus.Text = "Error parsing query";
        //}
        //else
        //{
        //  lblStatus.Text = e.Error.Message.ToString();
        //}
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
      TurnQueryButtons( true );
    }
    private void ShowDataInGrid()
    {
      dgvResult.DataSource = resultSet;
      dgvResult.Columns[4].Width = 800;
      lblStatus.Text = "Completed " + sw.ElapsedMilliseconds.ToString();
    }
    private void TurnQueryButtons( bool action )
    {
      if ( action )
      {
        btnApplyFilter.Enabled = true;
      }
      else
      {
        btnApplyFilter.Enabled = false;
      }
    }

    private void btnApplyFilter_Click( object sender, EventArgs e )
    {
      dgvResult.DataSource = null;
      if ( backWorker.IsBusy )
      {
        TurnQueryButtons( false );
        lblStatus.Text = "Canceling...";
        backWorker.CancelAsync();
      }
      else
      {
        trivialPredicate = string.IsNullOrEmpty( txtThreadId.Text ) && string.IsNullOrEmpty( txtMessage.Text ) && string.IsNullOrEmpty( txtChannel.Text ) && !chkEnableTime.Checked && cmbLogLevel.SelectedItem.ToString() == "any"; 
        if (! trivialPredicate )
          predicate = GetPredicateFromFilter();
        btnApplyFilter.Text = "Cancel";
        //btnExecuteQuery.Text = "Cancel";
        lblStatus.Text = "";
        progressBar.Visible = true;
        setTop = GetTopLinesValue( txtTopRecords.Text );
        // Kickoff the worker thread to begin it's DoWork function.
        backWorker.RunWorkerAsync();
      }
    }
    private int? GetTopLinesValue( string input )
    {
      int result = 0;
      bool succeed = Int32.TryParse(input, out result);
      int? r = succeed ? result : (int?)null;
      if ( r <= 0 )
        r = null; 
      return r;
    }
    private Predicate<PWLogRecord> GetPredicateFromFilter()
    {
      Expression<Func<PWLogRecord, bool>> exprLambda = null;
      Expression thread = null;
      Expression message = null;
      Expression time = null;
      Expression channel = null;
      Expression level = null;

      ParameterExpression pw = Expression.Parameter( typeof( PWLogRecord ), "input" );
      if ( ! string.IsNullOrEmpty( txtThreadId.Text ) )
      {
        Expression threadLeft = Expression.Property( pw, "Thread" );
        Expression threadRight = Expression.Constant( txtThreadId.Text, typeof( string ) );
        Comparison threadCmp = (Comparison)cmbThreadOperator.SelectedItem;
        thread = threadCmp.ComparisonToExpression( threadLeft, threadRight );
      }
      if ( chkEnableTime.Checked )
      {
        string dateFromValue = string.Format( "{0}:{1}:{2}.000", dateFrom.Value.Hour.IntTo2Signs(), dateFrom.Value.Minute.IntTo2Signs(), dateFrom.Value.Second.IntTo2Signs() );
        string dateToValue = string.Format( "{0}:{1}:{2}.000", dateTo.Value.Hour.IntTo2Signs(), dateTo.Value.Minute.IntTo2Signs(), dateTo.Value.Second.IntTo2Signs() );
        Expression toLeft = Expression.Constant( dateToValue, typeof( string ) );
        Expression toRight = Expression.Property( pw, "Time" );
        Expression fromLeft = Expression.Constant( dateFromValue, typeof( string ) );
        Expression fromRight = Expression.Property( pw, "Time" );
        Expression minusOne = Expression.Constant( -1, typeof( Int32 ) );//для сравнения в string.Compare
        Type[] paramTypes = new Type[2];
        paramTypes[0] = paramTypes[1] = typeof( string );
        MethodInfo compareMethod = typeof( string ).GetMethod( "Compare", paramTypes );
        Expression firstComp = Expression.Call( compareMethod, fromLeft, fromRight );
        Expression secondComp = Expression.Call( compareMethod, toLeft, toRight );
        Expression lConj = Expression.Equal( firstComp, minusOne );
        Expression rConj = Expression.NotEqual( secondComp, minusOne );
        time = Expression.AndAlso( lConj, rConj );
      }
      if ( !string.IsNullOrEmpty( txtChannel.Text ) )
      {
        Expression channelLeft = Expression.Property( pw, "Channel" );
        Expression channelRight = Expression.Constant( txtChannel.Text.ToUpper(), typeof( string ) );
        Comparison channelCmp = (Comparison)cmbChannelOperator.SelectedItem;
        channel = channelCmp.ComparisonToExpression( channelLeft, channelRight );
      }
      if ( cmbLogLevel.SelectedItem.ToString() != "any" )
      {
        int minimalLevel = levels.IndexOf( cmbLogLevel.SelectedItem.ToString(), 0, levels.Count );
        string[] levelsList = new string[levels.Count - minimalLevel];
        for ( int i = minimalLevel; i < levels.Count; i++ )
        {
          levelsList[( levels.Count - 1 ) - i] = levels[i].Substring( 0, 2 );
        }
        Expression levelLeft = Expression.Property( pw, "Level" );
        for ( int i = 0; i < levelsList.Length; i++ )
        {
          if ( level == null )
          {
            level = Expression.Equal( levelLeft, Expression.Constant( levelsList[i], typeof( string ) ) );
          }
          else
          {
            Expression levelRight = Expression.Equal( levelLeft, Expression.Constant( levelsList[i], typeof( string ) ) );
            level = Expression.OrElse( level, levelRight );
          }
        }
      }
      if ( !string.IsNullOrEmpty( txtMessage.Text ) )
      {
        Expression messageLeft = Expression.Property( pw, "Message" );
        Expression messageRight = Expression.Constant( txtMessage.Text.ToUpper(), typeof( string ) );
        Comparison messageCmp = (Comparison)cmbMessageOperator.SelectedItem;
        message = messageCmp.ComparisonToExpression( messageLeft, messageRight );
      }

      Expression predicateBody = null;
      predicateBody = predicateBody.AddConjuncts( new List<Expression> { thread, message, time, channel, level } );
      exprLambda = Expression.Lambda<Func<PWLogRecord, bool>>( predicateBody, pw );
      Func<PWLogRecord, bool> func = exprLambda.Compile();
      Predicate<PWLogRecord> predicate = new Predicate<PWLogRecord>( func );
      return predicate;
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
      cmbThreadOperator.SelectedIndex = 0;
      //cmbLevelOperator.SelectedIndex = 0;
      cmbChannelOperator.SelectedIndex = 0;
      txtTopRecords.Text = defaultTop.ToString();
    }

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

    //parser
    int threadStart = 1;
    int threadLen;
    int timeStart = -1;
    int timeLen;
    int channelStart = -1;
    int channelLen;
    int messageStart;

    bool readingThread;
    bool readingTime;
    bool tryReadingChannel;
    bool readingLevel;
    bool readingChannel;
    bool failedString;

    string thread;
    string time;
    string channel;
    string debugLevel;
    string message;

    //Stopwatch sw;
    /// <summary>Must return the value of the last record 'read'</summary>
    /// <param name="index">0 based index of the field value to read</param>
    /// <returns>Value of the field. Can also return null.</returns>
    public object GetValue( int index )
    {
      if ( index == 0 )
      {
        threadLen = 0;
        timeStart = 0;
        timeLen = 0;
        channelStart = 0;
        channelLen = 0;
        messageStart = 0;

        readingThread = true;
        readingTime = false;
        tryReadingChannel = false;
        readingChannel = false;
        readingLevel = false;
        failedString = false;

        thread = null;
        time = null;
        channel = null;
        debugLevel = null;
        message = null;

        for ( int i = threadStart; i < currentLine.Length; i++ )//первую скобку пропускаем
        {
          char current = currentLine[i];
          if ( current == ' ' && !readingChannel )//пробел может быть в channel
            continue;
          if ( readingThread )
          {
            if ( Char.IsDigit( current ) )
            {
              threadLen++;
            }
            else
            {
              readingThread = false;
              if ( current == ')' && threadLen > 0 )
              {
                readingTime = true;
                timeStart = i + 2;
                continue;
              }
              else
              {
                failedString = true;
                break;
              }
            }
          }
          else if ( readingTime )
          {
            if ( Char.IsDigit( current ) || current == ':' || current == '.' )
              timeLen++;
            else
            {
              readingTime = false;
              tryReadingChannel = true;
              if ( timeLen == 0 )
              {
                failedString = true;
                break;
              }
              //i++;//пропускаем пробел
            }
          }
          if ( tryReadingChannel )
          {
            if ( current == '[' )//то есть channel есть
            {
              channelStart = i;
              readingChannel = true;
              tryReadingChannel = false;
            }
            else//channel не определен 
            {
              tryReadingChannel = false;
              readingLevel = true;
            }
          }
          if ( readingChannel )
          {
            if ( current != ']' )
            {
              channelLen++;
            }
            else
            {
              channelLen++;
              readingChannel = false;
              readingLevel = true;
              continue;
            }
          }
          if ( readingLevel )
          {
            debugLevel = currentLine.Substring( i, 2 );
            if ( levels.Contains( debugLevel ) )
            {
              messageStart = i + 3;
              break;
            }
            else
            {
              failedString = true;//если level необязательный - отсюда message
              break;
            }
          }
        }

        if ( failedString )
        {
          message = currentLine;
        }
        else
        {
          thread = currentLine.Substring( threadStart, threadLen );
          time = currentLine.Substring( timeStart, timeLen );
          if ( channelLen > 0 )
            channel = currentLine.Substring( channelStart, channelLen );
          message = currentLine.Substring( messageStart, currentLine.Length - messageStart ).Trim();
        }

        //col = regex.Matches(currentLine);
      }
      if ( failedString )
      {
        if ( index == 4 )
          return currentLine;
        return null;
      }

      //LogField lf = (LogField)logFields[index];
      //AddLogRecord(String.Format("GetValue index:{0} lf.FieldName:{1}", index, lf.FieldName, col[0].Groups[index].Value));

      switch ( index )
      {
      case 0:
        return thread;
      case 1:
        return time;
      case 2:
        return channel.ToUpper();
      case 3:
        return debugLevel;
      case 4:
        return message.ToUpper();
      }
      return null;
    }
  }
}
