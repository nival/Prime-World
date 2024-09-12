using libdb;
using libdb.DB;
using libdb.UndoRedo;
using EditorLib;
using EditorNative.Terrain.Layers;

namespace EditorPlugins.Scene.Editors.Drawing.TerrainLayers
{
	internal sealed class DrawOperation : IUndoRedoOperation
	{
		private readonly DBTypes.Terrain terrain;
		private readonly ITerrainLayersProvider provider;
		private readonly int currentRow;
		private readonly int currentColumn;
		private readonly LayerValueChangeData[] layersData;

		internal DrawOperation( DBTypes.Terrain terrain, ITerrainLayersProvider provider, int currentRow, int currentColumn, LayerValueChangeData[] layersData )
		{
			this.terrain = terrain;
			this.provider = provider;
			this.currentRow = currentRow;
			this.currentColumn = currentColumn;
			this.layersData = layersData;
		}

    #region Private helper methods.

    private void SetLayersValues( Function<byte, LayerValueChangeData> getValueToSet )
    {
      if ( !ReferenceEquals( layersData, null ) )
      {
        var layers = provider.Layers;
        for ( int i = 0; i < layers.Length; ++i )
        {
          layers[i][currentRow, currentColumn] = getValueToSet( layersData[i] );
        }
      }
    }

    #endregion

		public void Undo()
		{
			SetLayersValues( layerData => layerData.PrevValue );
		}

		public void Redo()
		{
			SetLayersValues( layerData => layerData.NewValue );
		}

		public string DefaultCaption { get { return "Draw terrain layer"; } }

		public DBResource GetOwner() { return terrain; }
	}
}
