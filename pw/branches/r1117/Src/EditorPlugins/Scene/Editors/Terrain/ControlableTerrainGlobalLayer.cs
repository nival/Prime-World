using System;
using EditorLib;
using EditorNative.Terrain.Layers;

namespace EditorPlugins.Scene.Editors.Terrain
{
	internal sealed class ControlableTerrainGlobalLayer : TerrainGlobalLayer, IController<DBTypes.TerrainLayer>
	{
		private readonly DBTypes.TerrainLayer resourcePart;

		internal ControlableTerrainGlobalLayer( DBTypes.TerrainLayer resourcePart )
			: base( resourcePart.pTerrainType.DBId )
		{
			this.resourcePart = resourcePart;
			resourcePart.pTerrainType_Changed += OnTerrainTypeChanged;
		}

		public void Unsubscribe()
		{
			resourcePart.pTerrainType_Changed -= OnTerrainTypeChanged;
		}

		public DBTypes.TerrainLayer Resource
		{
			get { return resourcePart; }
		}

		internal event Operation TerrainTypeChanged;

		private void OnTerrainTypeChanged( object sender, EventArgs e )
		{
			TerrainTypeInfoId = resourcePart.pTerrainType.DBId;
			if ( TerrainTypeChanged != null )
			{
				TerrainTypeChanged();
			}
		}
	}
}
