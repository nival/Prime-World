using EditorLib.Settings;

namespace EditorPlugins.Scene.Editors
{
  [ConfigObject( true )]
  public class AdvMapEditorConfig : SimpleConfigObject
  {
    public bool lockObjectsMode;
    public bool splineSelectionMode;
  }

}
