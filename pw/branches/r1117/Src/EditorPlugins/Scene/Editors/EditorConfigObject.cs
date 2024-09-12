using EditorLib.Settings;
using System.Collections.Generic;
using EditorPlugins.Editors;

namespace EditorPlugins.Scene.Editors
{
  [ConfigObject( true )]
  public class EditorConfigObject : SimpleConfigObject
	{
		public readonly List<ToolBoxItemData> toolBoxItems = new List<ToolBoxItemData>();
		public bool terrainIndependentSnapping = false;
    public float DefaultPitch = -1.0f;
    public float DefaultRod = 21.0f;
    public float DefaultRoll = 0;
    public float DefaultYaw = -0.1f;
	}
}
