using EditorLib;
using EditorLib.Plugin;

namespace PF_EditorC
{
  [CommandName( "script", "", "Just execute script like code" )]
  public partial class ScriptCommand : IConsoleCommand
  {
    public int Execute( IEditorCommonApplication application, string[] parameters )
    {
      var script = Main( application, parameters ).GetEnumerator();
      while ( !script.MoveNext() ) ;
      return 0;
    }
  }
}
