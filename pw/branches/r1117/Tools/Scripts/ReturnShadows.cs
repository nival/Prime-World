/*
#about Script for returning shadows (run "ReturnShadows.cs", run game, do not commit)
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
using libdb.IO;

public class ReturnShadows
{
  private IEditorCommonApplication application;

  private bool NeedUpdateMaterial( Material material )
  {
    return material != null && material.GetType() == typeof( BasicMaterial );
  }

  private bool NeedUpdateAnimated( DBAnimatedSceneComponent c )
  {
    foreach ( var skin in c.skins )
    {
      foreach( var material in skin.materialsReferences )
        if ( NeedUpdateMaterial( material.Get() ) )
          return true;
    }

    return false;
  }

  private bool NeedUpdateStatic( DBStaticSceneComponent c )
  {
    foreach ( var material in c.materialsReferences )
      if ( NeedUpdateMaterial( material.Get() ) )
        return true;

    return true;
  }

  private void UpdateMaterial( Material material, bool enableReciever )
  {
    if ( material == null )
      return;
    else if ( material.GetType() == typeof( BasicMaterial ) )
    {
      BasicMaterial basicMaterial = material as BasicMaterial;
      basicMaterial.renderFlags |= MaterialFlags.ShadowCaster;
      if ( enableReciever )
        basicMaterial.renderFlags |= MaterialFlags.ShadowReceiver;
    }
    //else if ( material.GetType() == typeof( InstancingMaterial ) )
    //{
    //  InstancingMaterial instancingMaterial = material as InstancingMaterial;
    //  instancingMaterial.renderFlags |= MaterialFlags.ShadowCaster;
    //  if ( enableReciever ) 
    //    instancingMaterial.renderFlags |= MaterialFlags.ShadowReceiver;
    //}
  }

  private void ProcessFolder( IOperationContext context, string folder, bool enableReciever )
  {
    context.Progress( string.Format( "Process \"{0}\"...", FileUtils.FixFolderName( folder ) ) );
    List<DBID> dbids = null;
    ObjectsSelector.CollectObjects( application, FileUtils.FixFolderName( folder ), typeof( DBSceneComponent ), true, true, out dbids );
    foreach ( DBID dbid in dbids )
    {
      DBSceneComponent sceneComponent = DataBase.Get<DBSceneComponent>( dbid ).Get();
      if ( sceneComponent == null )
        continue;

      if ( sceneComponent.GetType() == typeof( DBAnimatedSceneComponent ) )
      {
        DBAnimatedSceneComponent component = sceneComponent as DBAnimatedSceneComponent;
        if ( NeedUpdateAnimated( component ) )
        {
          //component.groupFlags |= EGroupFlags.CastShadow | EGroupFlags.ReflectInWater;
          foreach ( var skin in component.skins )
          {
            foreach ( var material in skin.materialsReferences )
              UpdateMaterial( material.Get(), enableReciever );
          }
        }
      }
      else if ( sceneComponent.GetType() == typeof( DBStaticSceneComponent ) )
      {
        DBStaticSceneComponent component = sceneComponent as DBStaticSceneComponent;
        if ( NeedUpdateStatic( component ) )
        {
          //component.groupFlags |= EGroupFlags.CastShadow | EGroupFlags.ReflectInWater;
          foreach ( var material in component.materialsReferences )
            UpdateMaterial( material.Get(), enableReciever );
        }
      }
    }
  }

  private bool Work( IOperationContext context )
  {
    context.Start( false, true );
    ProcessFolder( context, @"/Buildings/", true );
    ProcessFolder( context, @"/Creeps/", false );
    ProcessFolder( context, @"/Heroes/", false );
    ProcessFolder( context, @"/Terrain/Islands/", true );
    ProcessFolder( context, @"/Terrain/Minor/", true );
    ProcessFolder( context, @"/Terrain/RockyMountain/", true );
    ProcessFolder( context, @"/Terrain/Signs/", true );
    ProcessFolder( context, @"/Terrain/Totems/", true );
    ProcessFolder( context, @"/Terrain/Trees/", true );

    return true;
  }

  public IEnumerable Main( EditorLib.IEditorCommonApplication application )
  {
    this.application = application;
    this.application.OperationExecutor.Start( Work );

    yield return true;
  }
}
