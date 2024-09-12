using EditorNative.Terrain.Layers;

namespace EditorPlugins.Scene.Editors.Drawing.TerrainLayers
{
	internal interface ITerrainLayersProvider
	{
		TerrainLayer[] Layers { get; }
	}
}
