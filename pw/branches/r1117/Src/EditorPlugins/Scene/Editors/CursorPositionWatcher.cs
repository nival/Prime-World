using System;
using EditorPlugins.Scene;
using EditorNative.Terrain;

namespace EditorPlugins.Scene.Editors
{
	internal sealed class CursorPositionWatcher
	{
		private readonly float initialTileX;
		private readonly float initialTileY;
		private readonly SceneControl sceneControl;
		private bool tileChanged;

		internal CursorPositionWatcher( SceneControl sceneControl )
		{
			this.sceneControl = sceneControl;
			GetTile( sceneControl, out this.initialTileX, out this.initialTileY );
		}

		internal bool TileChanged
		{
			get
			{
				if ( !tileChanged )
				{
					float tileX, tileY;
					GetTile( sceneControl, out tileX, out tileY );

					tileChanged =
						Math.Abs( tileX - initialTileX ) >= TerrainUtils.CursorGranularity ||
						Math.Abs( tileY - initialTileY ) >= TerrainUtils.CursorGranularity;
				}
				return tileChanged;
			}
		}

		private static void GetTile( SceneControl sceneControl, out float tileX, out float tileY )
		{
			var terrainIntersection = sceneControl.Pick().TerrainIntersection;
			tileX = TerrainUtils.NearestGranularity( terrainIntersection.X );
			tileY = TerrainUtils.NearestGranularity( terrainIntersection.Y );
		}
	}
}
