using EditorLib.Settings;
using EditorLib.Menu;
using EditorLib;

namespace EditorPlugins.Scene
{
  [ConfigObject( false, "SceneSettingsConfig" )]
  public sealed class SceneSettingsConfig : SimpleConfigObject
  {
    public bool usePostFX = true;
		public bool drawCollisionSelection = true;
  }

	public class CollisionSelectionCommand : IEditorCommand
	{
		private SceneSettingsConfig config;

		public CollisionSelectionCommand( IEditorWinApplication _application )
		{
			config = _application.Application.Settings.Get<SceneSettingsConfig>();
		}

		public override void Execute( IEditorWinApplication _application )
		{
			config.drawCollisionSelection = !config.drawCollisionSelection;
		}

		public override string Name { get { return "CollisionSelection"; } }

		public override bool IsChecked
		{
			get { return config.drawCollisionSelection; }
		}
	}

  public class PostFXCommand : IEditorCommand
  {
    private SceneSettingsConfig config;

    public PostFXCommand( IEditorWinApplication _application )
    {
      config = _application.Application.Settings.Get<SceneSettingsConfig>();
    }

    public override void Execute( IEditorWinApplication _application )
    {
      config.usePostFX = !config.usePostFX;
    }

    public override string Name { get { return "PostFX"; } }

    public override bool IsChecked
    {
      get { return config.usePostFX; }
    }
  }
}