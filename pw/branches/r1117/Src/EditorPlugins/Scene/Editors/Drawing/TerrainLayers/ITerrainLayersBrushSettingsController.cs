using EditorLib;

namespace EditorPlugins.Scene.Editors.Drawing.TerrainLayers
{
	internal interface ITerrainLayersBrushSettingsController
	{
		int SelectedLayer { set; }
		int BrushSize { set; }

		int DisplayLayerColors { set; }

		LayerView[] Layers { get; }

		event Operation LayersChanged;
	}
}
