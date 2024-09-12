/*
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System.Collections;
using EditorLib;
using EditorLib.Operations;
using EditorPlugins.Importer.Texture;
using libdb.DB;

public class CreateGlobalAtlas
{
  private IEditorCommonApplication application;

  private bool Work( IOperationContext context )
  {
    bool result = GlobalAtlas.Process( application, context );
    if ( result )
      DataBase.Store();
    return result;
  }

  public IEnumerable Main( IEditorCommonApplication app )
  {
    this.application = app;
    this.application.OperationExecutor.Start( Work );

    yield return true;
  }
}
