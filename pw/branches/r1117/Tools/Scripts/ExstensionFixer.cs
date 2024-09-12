/*
#about Чиним расширения
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using EditorLib;
using EditorLib.IO;
using EditorLib.Operations;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace Scripts
{
	class ExstensionFixer
	{
    private IEditorCommonApplication application;

    public IEnumerable Main( IEditorCommonApplication _application )
    {
      application = _application;
      application.OperationExecutor.Start( Work );

      yield return true;
    }

    private bool Work( IOperationContext context )
    {
      context.Start( false, true );
      context.Progress( "Analyzing resources" );
      Log.TraceMessage( "Analyzing resources" );


      if( !( application.FileSystem.WriteFileSystem is SVNFileSystem ) )
      {
        Log.TraceError( "WriteFileSystem should be SVNFileSystem type to proceed exstensions fixer. Exiting." );
        return true;
      }

      ( application.FileSystem.WriteFileSystem as SVNFileSystem ).InitNonGuiMode( "brownie", "gbhj;rb-k.,k." );

      var resources = new Dictionary<Type, List<DBID>>();

      ObjectsSelector.CollectObjects( application, "/", new []{typeof(DBResource)}, true, true, out resources );

      int cnt = 0;

      foreach( var type in resources.Keys )
      {
        foreach( var r in resources[type] )
        {
          DBID newdbid;

          if( r.IsInlined || !DBID.TryCreateDBID( FileUtils.GetParentFolderPath( r.FileName ),
                             Path.GetFileNameWithoutExtension( r.FileName ), type, out newdbid ) )
            continue;

          if( newdbid == r )
            continue;

          cnt++;

          Log.TraceMessage( "Renaming {0} to {1}", r, newdbid );
          DataBase.Rename( newdbid, r );
        }
      }

      context.Progress( "Storing data to file system" );
      Log.TraceMessage( "Storing data to file system" );
      DataBase.Store();

      context.Progress( string.Format("Extensions fixed for {0} resources", cnt ));
      Log.TraceMessage( "Extensions fixed for {0} resources", cnt );

      return true;
    }
	}
}
