using EditorLib.Extensions;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;

namespace EditorPlugins.Scene.Viewers.Effect
{
  [EditorAttribute( "COLL", true, "4004175c-8c50-4f48-a26c-806d1746f5a3" )]
  [ApplicableForDeriver]
  public sealed class CollViewer : SimpleViewer<DBTypes.CollisionGeometry>
  {
    protected override EditorSceneObject CreateSceneObject( DBPtr<DBTypes.CollisionGeometry> _resource )
    {
      return new CollSceneObject( _resource.DBId );
    }

    protected override void OnChangeDBResource(DBID dbid)
    {
      if ( isActive )
      {
        mainSceneObject = CreateSceneObject( resource );
        base.OnChangeDBResource( dbid );
        RefreshScene();
      }
    }

    protected override string GetTabText( DBPtr<DBTypes.CollisionGeometry> _resource )
    {
      return "COLL";
    }

    protected override string ConfigSection
    {
      get { return "COLL"; }
    }
  }
}