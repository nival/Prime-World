using EditorNative.Terrain.Layers;

namespace EditorPlugins.Scene.Editors.Drawing.TerrainLayers
{
	internal struct LayerValueChangeData
	{
		internal readonly int LayerIndex;
		internal readonly byte PrevValue;
		internal readonly byte NewValue;

		internal LayerValueChangeData( int layerIndex, byte prevValue, byte newValue )
		{
			LayerIndex = layerIndex;
			PrevValue = prevValue;
			NewValue = newValue;
		}
	}
}
