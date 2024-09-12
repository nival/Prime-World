/*
#about Удаляем все неиспользуемые Texture в папке GFX_Textures
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using EditorLib.Operations;
using libdb.DB;
using libdb.Diagnostics;

namespace Scripts
{
  public class DeleteUnusedTextures
  {
    private IEditorCommonApplication application;

    public IEnumerable Main( EditorLib.IEditorCommonApplication application )
    {
      this.application = application;
      this.application.OperationExecutor.Start( Work );

      yield return true;
    }

    private bool Work( IOperationContext context )
    {
      int filesDeleted = 0;

      context.Start( true, true );
      context.Progress( "Searching for textures..." );
      Log.TraceMessage( "Searching for textures..." );

      List<DBID> dbids = null;
      ObjectsSelector.CollectObjects( application, "/GFX_Textures/", typeof( Texture ), true, false, out dbids );

      for ( int i = 0; i < dbids.Count; ++i )
      {
        context.Progress( dbids.ToString(), ( i * 100 ) / dbids.Count );

        DBPtr<Texture> ptr = DataBase.Get<Texture>( dbids[i] );
        if ( DBID.IsNullOrEmpty( ptr.DBId ) || ptr.DBId.IsInlined )
          continue;

        var backLinks = ptr.GetBackLinks();

        //We don't have links to this Texture
        if ( backLinks.Count == 0 )
        {
          Texture texture = ptr.Get();
          if ( texture == null )
            continue;

          DataBase.Delete( ptr.DBId );
          var message = string.Format( "File {0} Texture '{1}' deleted", ptr.DBId.FileName, texture.textureFileName );
          context.Progress( message );
          Log.TraceMessage( message );
          ++filesDeleted;
        }
      }

      if(filesDeleted > 0)
        DataBase.Store();

      Log.TraceMessage( "Textures: {0}; Unused Textures: {1}", dbids.Count, filesDeleted );

      return true;
    }
  }
}
