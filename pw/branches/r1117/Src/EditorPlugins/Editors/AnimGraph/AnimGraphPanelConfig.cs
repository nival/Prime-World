using EditorLib.Settings;

namespace EditorPlugins.Editors.AnimGraph
{
	[ConfigObject( true )]
	public class AnimGraphPanelConfig : SimpleConfigObject
	{
		public bool MeasureInFrames = true;

    public bool SustainLooped = false;
    public float SustainLength = 0.0f;

		public bool SmartSelectionEnabled;
	}
}
