using System;
using System.IO;
using System.Runtime.InteropServices;
using libdb.Diagnostics;

namespace PF_EditorC
{
  class Program
  {
    [DllImport( "PW_GameLogic.dll" )]
    private static extern void TooSmartCompiler();

    static int Main( string[] args )
    {
      try
      {
        Log.AttachDumper( new DebuggerDumper( false ) );
        Log.AttachDumper( new ConsoleDumper() );

        string logFileName = string.Format( "{0}{1}-{2:yyyy.MM.dd-HH.mm.ss}-consoleEditor.log",
                                    EditorApplication.Editor.ApplicationName,
                                    EditorApplication.Editor.ApplicationVersion,
                                    DateTime.Now );

        Log.AttachDumper( new FileDumper( Path.Combine( @".\log\", logFileName ) ) );

        TooSmartCompiler(); // COMMON REASON OF CRASH HERE: you forgot to set working directory to <project>\Bin! Do this for projects PF_Game, PF_Editor for both Debug and Release configurations!

        EditorApplication.Editor.Initialize( null );

        int result = 0;
        if ( !EditorApplication.Editor.Commands.TryExecute( EditorApplication.Editor, args, out result ) )
          EditorApplication.Editor.Commands.ShowHelp();

        return result;
      }
      finally
      {
        EditorApplication.Editor.Terminate();
      }
    }
  }
}
