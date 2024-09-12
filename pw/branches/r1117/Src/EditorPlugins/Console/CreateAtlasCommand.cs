using EditorLib;
using EditorLib.Plugin;
using libdb.DB;
using System.Collections.Generic;
using EditorLib.IO;
using System;
using EditorPlugins.Importer.Texture;
using libdb.Diagnostics;

namespace EditorPlugins.Console
{
  [CommandName( "createAtlas", "ca", "Create global atlas for all particles." )]
  public sealed class CreateAtlasCommand : IConsoleCommand
  {
    public int Execute( IEditorCommonApplication application, string[] parameters )
    {
      if ( !GlobalAtlas.Process( application, null ) )
      {
        Log.TraceError( "Error create atlas" );
      }
      else
      {
        Log.TraceMessage( "Atlas created" );
      }
      DataBase.Store();
      return 0;
    }
  }
}
