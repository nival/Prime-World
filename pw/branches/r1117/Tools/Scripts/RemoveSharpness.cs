/*
#about Removes sharpness settings from textures. Fix size showed in texture viewer
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib.IO;
using EditorLib.Operations;
using libdb.DB;
using EditorLib;
using EditorLib.Extensions;

public class RemoveSharpness
{
  private IEditorCommonApplication application;

  private bool Work( IOperationContext context )
  {
    context.Start( true, true );
    context.Progress( "Searching for textures..." );
    List<DBID> dbids = null;
    ObjectsSelector.CollectObjects( application, "/", typeof( Texture ), true, false, out dbids );
    for ( int i = 0; i < dbids.Count; ++i )
    {
      context.Progress( dbids.ToString(), ( i * 100 ) / dbids.Count );
      DBPtr<Texture> ptr = DataBase.Get<Texture>( dbids[i] );
      if ( ptr == null )
        continue;
      Texture texture = ptr.Get();
      if ( texture == null )
        continue;

      if ( string.IsNullOrEmpty( texture.mipSharpenPasses.Trim() ) )
        continue;

      texture.mipSharpenPasses = string.Empty;
      IImporter importer = application.Extensions.CreateImporter( dbids[i], application, true );
      this.application.OperationExecutor.Start( importer.Import );
    }

    return true;
  }

  public IEnumerable Main( EditorLib.IEditorCommonApplication application )
  {
    this.application = application;
    this.application.OperationExecutor.Start( Work );

    yield return true;
  }
}
