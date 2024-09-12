using System;
using EditorNative;
using EditorNative.Terrain;
using EditorNative.Terrain.Layers;
using libdb.DB;

namespace EditorPlugins.Scene.Editors.Drawing.TerrainLayers
{
	internal sealed class TerrainLayersDrawingController : IDrawingController
	{
		#region Private members.

		private readonly DBTypes.Terrain terrain;
		private readonly TerrainBrush brush;
		private readonly ITerrainLayersProvider provider;
		private readonly int layerIndex;

		#endregion

		#region Initialization.

		internal TerrainLayersDrawingController(
			DBTypes.Terrain terrain,
			TerrainBrush brush,
			ITerrainLayersProvider provider,
			int layerIndex
			)
		{
			this.terrain = terrain;
			this.brush = brush;
			this.provider = provider;
			this.layerIndex = layerIndex;
		}

		#endregion

		#region IDrawingController Members

		void IDrawingController.Draw( PickResult pickResult )
		{
      float relativeX = pickResult.TerrainIntersection.X / (TerrainUtils.PatchSize * terrain.elemXCount);
      float relativeY = pickResult.TerrainIntersection.Y / (TerrainUtils.PatchSize * terrain.elemYCount);

			int sizeX = terrain.elemXCount * TerrainUtils.TexelsInPatch;
			int sizeY = terrain.elemYCount * TerrainUtils.TexelsInPatch;

			int rowCentral = (int)Math.Floor( relativeY * sizeX );
			int columnCentral = (int)Math.Floor( relativeX * sizeY );

			for ( int row = 0; row < brush.Height; ++row )
			{
				for ( int column = 0; column < brush.Height; ++column )
				{
					if ( brush[row, column]  )
					{
						int currentRow = rowCentral + row - brush.Height / 2;
						int currentColumn = columnCentral + column - brush.Width / 2;

						if ( currentRow >= 0 && currentColumn >= 0 && currentRow < sizeY && currentColumn < sizeX )
						{
							AddOperation( currentRow, currentColumn );
						}
					}
				}
			}

		}

		void IDrawingController.Erase( PickResult pickResult )
		{
			// Ignore.
		}

		#endregion

		#region Private helper methods.

		private void AddOperation( int currentRow, int currentColumn )
		{
			var layers = provider.Layers;

			LayerValueChangeData[] layersData = new LayerValueChangeData[layers.Length];
			for ( int i = 0; i < layers.Length; ++i )
			{
				layersData[i] = CalculateLayerData( currentRow, currentColumn, layers, i );
			}

			if (!ReferenceEquals( layersData, null ) && Array.Exists( layersData, data => data.PrevValue != data.NewValue ))
			{
				DataBase.UndoRedoManager.AddOperation(
					new DrawOperation(
						terrain,
						provider,
						currentRow,
						currentColumn,
						layersData
						)
					);
			}
		}

		private LayerValueChangeData CalculateLayerData( int currentRow, int currentColumn, TerrainLayer[] layers, int i )
		{
			byte value;
			byte defaultValue = layers[i][currentRow, currentColumn];
			if ( layerIndex == 0 )
			{
				// Редактируем дырки.
				value = i == 0 ? byte.MinValue : defaultValue;
			}
			else
			{
				// Редактируем маски.
				if ( i == 0 )
				{
					// Значения для дырок.
					value = byte.MaxValue;
				}
				else
				{
					// Значения для масок.
					value = i == layerIndex ? byte.MaxValue : byte.MinValue;
				}
			}

			return new LayerValueChangeData(
				i,
				defaultValue,
				value
				);
		}

		#endregion
	}
}
