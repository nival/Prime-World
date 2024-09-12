using EditorNative;
using EditorPlugins.Scene.Presets;
using libdb.DB;

namespace EditorPlugins.Scene.Viewers
{
  [IndexField( "Preset" )]
  public class SceneInfo
  {
    private SimpleEditorScene scene = null;

  	public ScenePreset Preset { get; set; }

  	public SimpleEditorScene.SimpleCamera Camera
    {
      get { return scene.GetCamera(); }
      set { scene.SetCamera( value ); }
    }

    public void Init( SimpleEditorScene _scene )
    {
      scene = _scene;
    }
  }

}