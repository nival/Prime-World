using System.IO;
using System.Collections;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.ServiceModel;

namespace Zzima
{
  public interface ILogParserInputContext
  {
    void OpenInput( string from );
    int GetFieldCount();
    string GetFieldName( int index );
    int GetFieldType( int index );
    bool ReadRecord();
    object GetValue( int index );
    void CloseInput( bool abort );
  }

  // TODO: Generate a unique GUID for your input format
  /// <summary>XMLInputFormat for LogParser</summary>
  [ServiceBehavior( ConcurrencyMode = ConcurrencyMode.Reentrant, InstanceContextMode = InstanceContextMode.Single )]
  [Guid( "4BA6A9EF-E469-4122-A3ED-D1404D97450B" )]
  public class PWLogPlugin : ILogParserInputContext, IFromServerToClientMessages
  {
    //static FileStream fLog = new FileStream("c:/PWLogPlugin.log", FileMode.Create);
    //static StreamWriter wLog = new StreamWriter(fLog);
    static long approximateLinesQuant;
    static int averageLineLength = 75; //средний размер = 75
    static int quantIntervalToUpdateProgress = 50000;

    //static string mask = @"\((?<thread>\d{1,10})\) (?<time>\d{2}:\d{2}:\d{2}.\d{3,6})(?<channel> \[[a-z0-9 ]+\])? (?<level>d:|m:|w:|e:|a:|c:)? (?<message>.*)";
    //static Regex regex = new Regex(mask, RegexOptions.IgnoreCase | RegexOptions.Compiled);
    static List<string> levels = new List<string> { "d:", "m:", "w:", "e:", "a:", "c:" };

    FileStream targetFile;
    StreamReader reader;
    string currentLine;
    
    //wcf service for ipc
    ServiceHost clientHost;
    Guid clientID;
    int currentProcent = 0;
    volatile bool needToCancel = false;

    public PWLogPlugin(Guid clientGuid)
    {
      clientID = clientGuid;
      clientHost = new ServiceHost( this );
      clientHost.AddServiceEndpoint( ( typeof( IFromServerToClientMessages ) ), new NetNamedPipeBinding(), "net.pipe://localhost/Client" + clientGuid.ToString() );
      clientHost.Open();
    }

    //public void AddLogRecord( string s )
    //{
    //  try
    //  {
    //    wLog.WriteLine( s + " At: " + DateTime.Now );
    //    wLog.Flush();
    //  }
    //  catch { }
    //}

    public int GetCurrentPercentage( long currentLine )
    {
      int result = (int)( ( (double)currentLine / approximateLinesQuant ) * 100 );
      return result > 90 ? 90 : result;
    }

    //ArrayList logFields;
    //#region LogField Class
    //private class LogField
    //{
    //    string fieldName;
    //    FieldType fieldType;

    //    public LogField ( string FieldName, FieldType FieldType )
    //    {
    //        fieldName = FieldName;
    //        fieldType = FieldType;
    //    }

    //    public string FieldName
    //    {
    //        get { return fieldName; }
    //        set { fieldName = value; }
    //    }

    //    public FieldType FieldType
    //    {
    //        get { return fieldType; }
    //        set { fieldType = value; }
    //    }
    //}
    //#endregion

    /// <summary>XMLInputFormat constructor</summary>
    //public PWLogPlugin ( )
    //{
    //    logFields = new ArrayList();

    //    logFields.Add(new LogField("Thread", FieldType.String));
    //    logFields.Add(new LogField("Time", FieldType.String));
    //    logFields.Add(new LogField("Channel", FieldType.String));
    //    logFields.Add(new LogField("Level", FieldType.String));
    //    logFields.Add(new LogField("Message", FieldType.String));
    //}

    /// <summary>InputFormat.FieldType Enumeration</summary>
    //private enum FieldType
    //{
    //    /// <summary>VT_I8</summary>
    //    Integer = 1,
    //    /// <summary>VT_R8</summary>
    //    Real = 2,
    //    /// <summary>VT_BSTR</summary>
    //    String = 3,
    //    /// <summary>VT_DATE or VT_I8 (UTC)</summary>
    //    Timestamp = 4
    //}

    /// <summary>Open a log file or resource</summary>
    /// <param name="from">Entity to open that specified in the FROM statement</param>
    public void OpenInput( string from )
    {
      //try
      //{
      //AddLogRecord(String.Format("OpenInput from: {0}", from));
      if ( from != "" )
      {
        targetFile = new FileStream( from, FileMode.Open );
        FileInfo fInfo = new FileInfo( from );
        approximateLinesQuant = fInfo.Length / averageLineLength;
        reader = new StreamReader( targetFile, System.Text.Encoding.UTF8 );
        //AddLogRecord("started at:" + DateTime.Now.ToUniversalTime());
      }
      //}
      //catch (Exception ex)
      //{
      //    AddLogRecord("in open input : " + ex.ToString());
      //}
      ReportProgress( 1 ); //сообщить что запустилось
    }

    /// <summary>Return the total number of fields that are exported to logparser</summary>
    /// <returns>Number of fields in entity</returns>
    public int GetFieldCount()
    {
      //AddLogRecord(String.Format("GetFieldCount count:{0}", logFields.Count));
      return 5;
    }

    /// <summary>Return the name of the field. Method is called as many times as specified by GetFieldCount.</summary>
    /// <param name="index">0 based index of the field name to return</param>
    /// <returns>Field name</returns>
    public string GetFieldName( int index )
    {
      switch ( index )
      {
      case 0:
        return "Thread";
      case 1:
        return "Time";
      case 2:
        return "Channel";
      case 3:
        return "Level";
      case 4:
        return "Message";
      default:
        return "Thread";
      }
    }

    /// <summary>Returns the type of the field. Method is called as many times as specified by GetFieldCount.</summary>
    /// <param name="index">0 based index of the field type to return</param>
    /// <returns>Field Type</returns>
    public int GetFieldType( int index )
    {
      //LogField logfield = (LogField)logFields[index];
      //AddLogRecord(String.Format("GetFieldType index:{0} fieldName:{1}", index, logfield.FieldType.ToString()));
      return 3;
    }
    long i = 0;
    /// <summary>Read a new record advancing the internal 'state' machine. This method is called until there are no more records to export.</summary>
    /// <returns>TRUE if record was read, FALSE if there are no more records to read</returns>
    public bool ReadRecord()
    {
      if ( needToCancel )
        return false;
      i++;
      if ((i % quantIntervalToUpdateProgress) == 0)
        ReportProgress(GetCurrentPercentage(i));

      //    return false;
      //return true;
      //try
      //{
      currentLine = reader.ReadLine();
      //    AddLogRecord(String.Format("ReadRecord read:{0}", currentLine));
      //}
      //catch (Exception ex)
      //{
      //    AddLogRecord("in read record : " + ex.ToString());
      //}
      if ( currentLine == null ) //return currentLine != null;
      {
        //AddLogRecord("finishedReadingAt:" + DateTime.Now.ToUniversalTime());
        ReportProgress( 100 ); //finished
        return false;
      }
      return true;
    }

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

        if ( currentLine == "" )
          failedString = true;

        for ( int i = threadStart; i < currentLine.Length; i++ )//первую скобку пропускаем
        {
          char current = currentLine[i];
          if ( current == ' ' && ! readingChannel )//пробел может быть в channel
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

    /// <summary>Close log file or resource</summary>
    /// <param name="abort">TRUE if execution is terminated by abnormal situation, such as Ctrl+C</param>
    public void CloseInput( bool abort )
    {
      if ( reader != null )
        reader.Close();
      if ( targetFile != null )
        targetFile.Close();
      //if (wLog != null) 
      //  wLog.Close();
      //if (fLog != null)
      //  fLog.Close();
      try
      {
        clientHost.Close();
      } catch { }

    }

    public void ReportProgress( int percentage )
    {
      if ( percentage <= currentProcent )
        return;
      using ( ChannelFactory<IFromClientToServerMessages> factory = new ChannelFactory<IFromClientToServerMessages>( new NetNamedPipeBinding(), new EndpointAddress( "net.pipe://localhost/Server" + clientID.ToString() ) ) )
      {
        IFromClientToServerMessages clientToServerChannel = factory.CreateChannel();
        try
        {
          clientToServerChannel.ReportProgress( percentage );
        }
        catch// ( Exception ex )
        {
          //MessageBox.Show( ex.ToString() );
        }
        finally
        {
          CloseChannel( (ICommunicationObject)clientToServerChannel );
        }
      }
    }
    private void CloseChannel( ICommunicationObject channel )
    {
      try
      {
        channel.Close();
      }
      catch// ( Exception ex )
      {
        //MessageBox.Show( ex.ToString() );
      }
      finally
      {
        channel.Abort();
      }
    }
    public void NotifyNeedToCancel( bool getFlag )
    {
      needToCancel = true;
    }
  }
}
