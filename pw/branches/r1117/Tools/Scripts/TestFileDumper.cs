/*
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System.Collections;
using System.Threading;
using EditorLib;
using EditorLib.Operations;
using libdb.Diagnostics;

namespace Scripts
{
  public class TestFileDumper
  {
    private IEditorCommonApplication application;

    public IEnumerable Main( IEditorCommonApplication _application )
    {
      application = _application;
      application.OperationExecutor.Start( Work );

      yield return true;
    }

    private bool Work( IOperationContext _context )
    {
      Log.AttachDumper( new EditorLib.OutputPanel.OutputFileDumper( "TestFileDumper.log" ) );

      _context.Start( true, true );
      _context.Progress( "Starting operation..." );

      Log.TraceMessage( "Starting operation..." );

      for( int i = 0; i < 100; ++i )
      {
        if(i % 4 == 0)
        {
          Log.TraceError( "TraceError" );  
        }
        else if( i % 3 == 0 )
        {
          Log.TraceWarning( "TraceWarning" );
        }
        else
        {
          Log.TraceMessage( "TraceMessage" );
        }

        Thread.Sleep( 500 );
      }

      Log.TraceMessage( "Operation completed" );

      _context.Progress( "Operation completed" );

      return true;
    }
  }
}
