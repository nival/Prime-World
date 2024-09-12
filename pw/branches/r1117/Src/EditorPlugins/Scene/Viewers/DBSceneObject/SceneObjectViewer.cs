using EditorLib.Extensions;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;
using PF_EditorNative;

namespace EditorPlugins.Scene.Viewers.Effect
{
  [EditorAttribute( "SceneObject", true, "4004175c-8c50-4f48-a26c-802d1746f5a3" )]
  [ApplicableForDeriver]
  public sealed class SceneObjectViewer : SimpleViewer<DBTypes.DBSceneObject>
  {
    protected override EditorSceneObject CreateSceneObject( DBPtr<DBTypes.DBSceneObject> _resource )
    {
      return new EditorSceneObject( _resource.DBId );
    }

    protected override string GetTabText( DBPtr<DBTypes.DBSceneObject> _resource )
    {
      return Utility.GetResourceName( _resource.DBId );
    }

    protected override string ConfigSection
    {
      get { return "SceneObject"; }
    }

    protected override void OnActivateEditor()
    {
      base.OnActivateEditor();
    }

    protected override void OnDeactivateEditor()
    {
      base.OnDeactivateEditor();
    }
  }

  [EditorAttribute( "SceneComponent", true, "4004175c-8c50-4f48-a26c-802d1746f5a3" )]
  [ApplicableForDeriver]
  public sealed class SceneComponentViewer : SimpleViewer<DBTypes.DBSceneComponent>
  {
    protected override EditorSceneObject CreateSceneObject( DBPtr<DBTypes.DBSceneComponent> _resource )
    {
      return new EditorSceneObject( _resource.DBId );
    }

    protected override string GetTabText( DBPtr<DBTypes.DBSceneComponent> _resource )
    {
      return Utility.GetResourceName( _resource.DBId );
    }

    protected override string ConfigSection
    {
      get { return "SceneComponent"; }
    }

    protected override void OnActivateEditor()
    {
      base.OnActivateEditor();
    }

    protected override void OnDeactivateEditor()
    {
      base.OnDeactivateEditor();
    }
  }

  [EditorAttribute( "StaticMesh", true, "4004175c-8c50-4f48-a26c-802d1746f5a3" )]
  [ApplicableForDeriver]
  public sealed class StaticMeshViewer : SimpleViewer<DBTypes.StaticMesh>
  {
    protected override EditorSceneObject CreateSceneObject( DBPtr<DBTypes.StaticMesh> _resource )
    {
      return new EditorSceneObject( _resource.DBId );
    }

    protected override string GetTabText( DBPtr<DBTypes.StaticMesh> _resource )
    {
      return Utility.GetResourceName( _resource.DBId );
    }

    protected override string ConfigSection
    {
      get { return "StaticMesh"; }
    }

    protected override void OnActivateEditor()
    {
      base.OnActivateEditor();
    }

    protected override void OnDeactivateEditor()
    {
      base.OnDeactivateEditor();
    }
  }

  [EditorAttribute( "Effect", true, "4004175c-8c50-4f48-a26c-802d1746f5a3" )]
  [ApplicableForDeriver]
  public sealed class EffectViewer : SimpleViewer<DBTypes.BasicEffect>
  {
    protected override EditorSceneObject CreateSceneObject( DBPtr<DBTypes.BasicEffect> _resource )
    {
      EffectSceneObject so = new EffectSceneObject( _resource.DBId, _resource.Get().component.DBId );
      return so;
    }

    protected override string GetTabText( DBPtr<DBTypes.BasicEffect> _resource )
    {
      return Utility.GetResourceName( _resource.DBId );
    }

    protected override string ConfigSection
    {
      get { return "Effect"; }
    }

    protected override void OnActivateEditor()
    {
      base.OnActivateEditor();
    }

    protected override void OnDeactivateEditor()
    {
      base.OnDeactivateEditor();
    }
  }

  [EditorAttribute( "LightingEffect", true, "4004175c-8c50-4f48-a26c-802d1846f5a3" )]
  [ApplicableForDeriver]
  public sealed class LightingEffectViewer : SimpleViewer<DBTypes.LightningEffect>
  {
    protected override EditorSceneObject CreateSceneObject( DBPtr<DBTypes.LightningEffect> _resource )
    {
      EffectSceneObject so = new EffectSceneObject( _resource.DBId, _resource.Get().component.DBId );
      return so;
    }

    protected override string GetTabText( DBPtr<DBTypes.LightningEffect> _resource )
    {
      return Utility.GetResourceName( _resource.DBId );
    }

    protected override string ConfigSection
    {
      get { return "LightingEffect"; }
    }

    protected override void OnActivateEditor()
    {
      base.OnActivateEditor();
    }

    protected override void OnDeactivateEditor()
    {
      base.OnDeactivateEditor();
    }
  }

  [EditorAttribute( "AdvMapCreepSpawner", true, "4004175c-8c50-4f48-a26c-802d1746f5a3" )]
  [ApplicableForDeriver]
  public sealed class AdvMapCreepSpawnerViewer : SimpleViewer<DBTypes.AdvMapCreepSpawner>
  {
    protected override EditorSceneObject CreateSceneObject( DBPtr<DBTypes.AdvMapCreepSpawner> _resource )
    {
      return new EditorSceneObject( DBID.FromString( "Tech/Default/Bulb.SOBJ" ) );
    }

    protected override string GetTabText( DBPtr<DBTypes.AdvMapCreepSpawner> _resource )
    {
      return Utility.GetResourceName( _resource.DBId );
    }

    protected override string ConfigSection
    {
      get { return "AdvMapCreepSpawner"; }
    }

    protected override void OnActivateEditor()
    {
      base.OnActivateEditor();
    }

    protected override void OnDeactivateEditor()
    {
      base.OnDeactivateEditor();
    }
  }

  [EditorAttribute( "AdvMapNeutralCreepSpawner", true, "4004175c-8c50-4f48-a26c-802d1746f5a3" )]
  [ApplicableForDeriver]
  public sealed class AdvMapNeutralCreepSpawnerViewer : SimpleViewer<DBTypes.AdvMapNeutralCreepSpawner>
  {
    protected override EditorSceneObject CreateSceneObject( DBPtr<DBTypes.AdvMapNeutralCreepSpawner> _resource )
    {
      return new EditorSceneObject( DBID.FromString( "Tech/Default/Bulb.SOBJ" ) );
    }

    protected override string GetTabText( DBPtr<DBTypes.AdvMapNeutralCreepSpawner> _resource )
    {
      return Utility.GetResourceName( _resource.DBId );
    }

    protected override string ConfigSection
    {
      get { return "AdvMapNeutralCreepSpawner"; }
    }

    protected override void OnActivateEditor()
    {
      base.OnActivateEditor();
    }

    protected override void OnDeactivateEditor()
    {
      base.OnDeactivateEditor();
    }
  }
}
