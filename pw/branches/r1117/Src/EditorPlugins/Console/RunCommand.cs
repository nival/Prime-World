using System;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Plugin;
using libdb.Diagnostics;

namespace EditorPlugins.Console
{
  [CommandName( "run", "", "execute specified script" )]
  public class RunCommand : IConsoleCommand
  {
    public int Execute( IEditorCommonApplication application, string[] parameters )
    {
      if ( parameters.Length <= 0 )
        return 0;

      string[] arguments;
      if ( parameters.Length == 1 )
        arguments = new string[] { };
      else
      {
        arguments = new string[parameters.Length - 1];
        for ( int i = 0; i < parameters.Length - 1; ++i )
          arguments[i] = parameters[i + 1];
      }

      if (!application.Scripts.LoadScript(parameters[0], arguments))
        return 1;

      try
      {
        while ( application.Scripts.StepWithException() )
        {
        }
      }
      catch ( Exception e )
      {
        Log.TraceError( "Exception {0}. {1}", e, e.Message );
        return 1;
      }

      return 0;
    }
  }
}
