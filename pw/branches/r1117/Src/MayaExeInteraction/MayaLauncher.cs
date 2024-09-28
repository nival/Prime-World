using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using libdb.IO;
using libdb.Diagnostics;

namespace Tools.MayaExeInteraction
{
  class MayaLauncher : IMayaLauncher
  {
    #region WinApi

    private const int SW_HIDE = 0;
    private const int SW_SHOW = 5;
  	private const int SW_FORCEMINIMIZE = 11;

    [DllImport( "user32.dll" )]
    static extern bool ShowWindow( IntPtr hWnd, int nCmdShow );

    [DllImport( "user32.dll" )]
    static extern IntPtr FindWindow( string lpClassName, string lpWindowName );

    #endregion

		#region Fields

		private const string COMMAND_START = "[RM_START_COMMAND]";
    private const string MEL_STRING_BEGIN = "mel:";
    private const string ERROR_STRING_BEGIN = "Error: ";
    private const string WARNING_STRING_BEGIN = "Warning: ";
    private const string COMMAND_END = "[RM_END_COMMAND]";

		private bool isErrorOccured = false;
    private bool commandStarted = false;
    private readonly AutoResetEvent commandProcessed = new AutoResetEvent( false );

    private Process process = null;
		private readonly string pathToMaya;
		private readonly string mayaPluginDirectory;

    private readonly string[] outputFilter = new[]
    {
      @"File read",
      @"Result: ",
      @"clip -paste  -sc 1 -s",
      @"mentalray",
      @"mental ray",
      @"You will need to rewind and play to see ypur particles",
      @"No cache file found for this object",
			@"Cannot find procedure ""fitRange""",
			@"An execution error occured in the expression expression"
    };

		#endregion

		public MayaLauncher( string _pathToMaya, string _mayaPluginDirectory)
    {
			pathToMaya = _pathToMaya;
      mayaPluginDirectory = _mayaPluginDirectory;
    }

		public bool ExecuteCommand( MayaCommand _command )
		{
			try
			{
				if ( !File.Exists( _command.Script ) )
				{
					TraceError( string.Format( "Maya export script \"{0}\" is not exist.", _command.Script ) );
					return false;
				}

				if ( process == null || process.HasExited )
				{
					bool success = StartMaya();

					if ( !success )
					{
						TraceError( "Maya process not started." );
						return false;
					}
				}

				HideMayaWindow();//окошко майки иногад все равно появляется, при каждой команде скрываем его снова

				if ( !SendCommand( _command ) )
					return false;

			}
			catch ( Exception err )
			{
				TraceError( string.Format( "Exception: {0}", err ) );
				return false;
			}

			if( _command is MayaImportCommand)
			{
				MayaImportCommand importCommand = (MayaImportCommand) _command;

				//проверяем создался ли файл
				if ( !string.IsNullOrEmpty( importCommand.OutFile ) && !File.Exists( importCommand.OutFile ) )
				{
					TraceError( string.Format( "Output file \"{0}\" not created", importCommand.OutFile ) );
					return false;
				}				
			}

			return true;
		}

  	public void Terminate()
		{
			if ( process != null && !process.HasExited )
			{
				process.StandardInput.WriteLine( "quit -f" );//ставим команду в очередь

				process.CancelErrorRead();
				process.CancelOutputRead();

				if ( !process.WaitForExit( 100 ) )//ждем когда майка завершится
					process.Kill();
			}
		}

    private bool StartMaya()
    {
      try
      {
        process = new Process();

        process.StartInfo = new ProcessStartInfo
        {
          FileName = string.IsNullOrEmpty(pathToMaya) ? @"maya.exe" : pathToMaya ,
          Arguments = "-prompt -noAutoloadPlugins",
          RedirectStandardInput = true,
          RedirectStandardOutput = true,
          RedirectStandardError = true,
          UseShellExecute = false,
          WindowStyle = ProcessWindowStyle.Hidden, 
          CreateNoWindow = true //скрываем консольное окошко
        };

        process.OutputDataReceived += OnOutputDataReceived;
        process.ErrorDataReceived += OnErrorDataReceived;
        
        process.Start();
        
				////ждем пока процесс создаст окно (10 сек)
				//for( int i = 0; i < 100; ++i  )
				//{
				//  Thread.Sleep( 100 );  

				//  if(HideMayaWindow()) 
				//    break;
				//}

        process.BeginOutputReadLine();
        process.BeginErrorReadLine();

				return Initialize( mayaPluginDirectory );
      }
      catch( Win32Exception err )
      {
        TraceError( string.Format( "Exception: {0}", err ) );
        process = null;
      }

      TraceError( "Can't start Maya process" );
      return false;
    }

		private bool Initialize( string _pluginsDirectory )
		{
			Log.Assert(process != null && !process.HasExited, "You try initialize maya before its starts");

			var command = new MayaCommand();
			command.Name = "H6_exportInit";
			command.Script = Path.GetFullPath( @"..\Tools\MayaScripts\H6_exportInit.mel" );
			command.Parameters.Add( "pluginsDirectory", FileUtils.FixFileName(_pluginsDirectory) );

			return ExecuteCommand( command );
		}

		private bool HideMayaWindow()
    {
			try
			{
				if ( process == null || process.HasExited || process.MainModule == null )
					return false;

				IntPtr hwnd = FindWindow( null, process.MainModule.FileName );

				if ( hwnd != IntPtr.Zero )
				{
					ShowWindow( hwnd, SW_FORCEMINIMIZE );
					return true;
				}
			}
			catch
			{
				return false;
			}

			return false;
    }

		private bool SendCommand( MayaCommand _command )
		{
			//в этой команде ошибки еще не было
			isErrorOccured = false;

			StringBuilder sb = new StringBuilder();
			sb.AppendFormat( "print \"{0}\\n\";", COMMAND_START );
			sb.AppendFormat( "source \"{0}\";\n", FileUtils.FixFileName( Path.GetFullPath( _command.Script ) ) );
			sb.AppendFormat( "{0};\n", _command );
			sb.AppendFormat( "print \"{0}\\n\";", COMMAND_END );

			process.StandardInput.WriteLine( sb.ToString() );

			//ждем завершения команды
			WaitCommandProcessing();

			return !isErrorOccured;
		}

		private void WaitCommandProcessing()
		{
			//тут мы дождемся ответа от майки и распарсим standartOutput, см. OnOutputDataReceived
			while ( !commandProcessed.WaitOne( 100, false ) )
			{
				if ( process == null || process.HasExited )
				{
					TraceError( string.Format( "Maya Process has been closed internally" ) );
				}
			}
		}

		private void OnErrorDataReceived( object _sender, DataReceivedEventArgs _args )
		{
			if ( string.IsNullOrEmpty( _args.Data ) )
				return;

			TraceError( "error out: " + _args.Data.Trim() );
		}

		private void OnOutputDataReceived( object _sender, DataReceivedEventArgs _args )
		{
			ParseOutputData( _args.Data );
		}

    private void ParseOutputData( string _data )
    {
      if( string.IsNullOrEmpty( _data ) )
        return;
           
      string str = _data.Trim();

      //достигли конца команды
      if( str.Contains( COMMAND_END ) )
      {
        commandProcessed.Set();
        commandStarted = false;
        return;
      }

      //Обрабатываем строки типа "mel: mel: [RM_END_COMMAND]"
      while( str.StartsWith( MEL_STRING_BEGIN ) )
      {
        str = str.Substring( MEL_STRING_BEGIN.Length ).Trim();
      }

    	if(str.Length == 0)
    		return;

    	//начало команды
      if( str.StartsWith( COMMAND_START ) )
      {
        commandStarted = true;  
        return;
      }

    	if(!commandStarted)
    		return;

			//фильтрация вывода
			if ( FilterOutput(str) )
				return;

      //вывод результатов команды
      if( str.StartsWith( ERROR_STRING_BEGIN ) )
      {
        TraceError( str.Substring( ERROR_STRING_BEGIN.Length ) );
      }
      else if( str.StartsWith( WARNING_STRING_BEGIN ) )
      {
        TraceWarning( str.Substring( WARNING_STRING_BEGIN.Length ) );
      }
      else
      {
        TraceMessage( str );
      }
    }

		private bool FilterOutput(string _text)
		{
			foreach ( string filter in outputFilter )
			{
				if ( _text.ToLower().Contains( filter.ToLower() ) )
				{
					return true;
				}
			}

			return false;
		}

		#region Trace messages

		private void TraceMessage( string _text )
		{
			Log.TraceMessage( "Maya: {0}", _text );
		}

		private void TraceWarning( string _text )
		{
			Log.TraceWarning( "Maya: {0}", _text );
		}

		private void TraceError( string _text )
		{
			//error to warning
			if(_text.Contains("not found on MAYA_PLUG_IN_PATH"))
			{
				Log.TraceWarning( "Maya: {0}", _text );
			}
			else
			{
				Log.TraceError("Maya: {0}", _text);
				isErrorOccured = true;
			}	
		}

		#endregion
  }
}
