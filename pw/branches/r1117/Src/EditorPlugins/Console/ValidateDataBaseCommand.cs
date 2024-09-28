using EditorLib;
using EditorLib.Plugin;
using libdb.DB;

namespace EditorPlugins.Console
{
  [CommandName( "validate", "", "Validate database for broken links, backlinks, missing files etc..." )]
  class ValidateDateBaseCommand : IConsoleCommand
  {
    [CommandArgument( "dry-run", "", "Only diagnose problems, do not repair them" )]
    public bool dryRun = false;


    public int Execute( IEditorCommonApplication application, string[] parameters )
    {
      string[] scripts = { "..\\Tools\\Scripts\\ValidateBackLinks.cs",  "..\\Tools\\Scripts\\ExstensionFixer.cs", "..\\Tools\\Scripts\\RemoveUnusedFiles.cs" };

      foreach ( var script in scripts )
      {
        var run = new RunCommand();
        var result = run.Execute( application, new[] { script } );
        if ( result != 0 )
          return result;
      }

      if ( !dryRun )
        DataBase.Store();
      return 0;
    }
  }
}