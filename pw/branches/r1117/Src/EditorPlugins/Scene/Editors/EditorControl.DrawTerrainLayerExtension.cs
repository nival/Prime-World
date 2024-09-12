using System;
using System.Collections.Generic;
using EditorLib;
using EditorNative;
using EditorNative.Terrain;
using EditorNative.Terrain.Layers;
using EditorPlugins.Scene.Editors.Drawing;
using EditorPlugins.Scene.Editors.Drawing.TerrainLayers;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;
using DBTypes;
using System.Windows.Forms;
using EditorPlugins.Scene;
using EditorLib.IO;
using System.Drawing;
using System.IO;
using EditorPlugins.Importer.Texture;

namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
		private sealed class DrawTerrainLayerExtension
			: IEditorControlDrawingExtension,
			  ITerrainLayersBrushSettingsController,
			  ITerrainLayersProvider
		{
			#region Private members.

			private readonly TerrainBrush brush = new TerrainBrush();
			private readonly DBTypes.Terrain resource;
			private readonly EditorTerrain terrain;
      private readonly SceneControl sceneControl = null;
      private int brushSize = 1;
      private RootFileSystem fileSystem;
      private List<Bitmap> textures = new List<Bitmap>();

			private int selectedLayerIndex;

			#endregion

			#region Initialization.

      internal DrawTerrainLayerExtension( DBTypes.Terrain resource, EditorTerrain terrain, SceneControl sceneControl, RootFileSystem fileSystem )
			{
				this.resource = resource;
				this.terrain = terrain;
        this.sceneControl = sceneControl;
        this.fileSystem = fileSystem;
			}

			#endregion

			#region Internal methods.

			internal void OnLayersChanged()
			{
				if ( LayersChanged != null )
				{
					LayersChanged();
				}
			}

			#endregion

			#region IEditorControlDrawingExtension Members

			public string ExtensionName
			{
				get { return "Layers"; }
			}

			bool IEditorControlDrawingExtension.CanBeginDrawing
			{
				get { return selectedLayerIndex >= 0; }
			}

			IDrawingController IEditorControlDrawingExtension.BeginDrawing()
			{
				return new TerrainLayersDrawingController(
					resource,
					brush,
					this,
					selectedLayerIndex
					);
			}

			public void OnActivated()
            {
            }

			public void OnDeactivated()
			{
			}

      private void OnTimerTick( object sender, EventArgs e )
      {
      }

			#endregion

			#region ITerrainLayersBrushSettingsController Members

			int ITerrainLayersBrushSettingsController.SelectedLayer
			{
				set 
        { 
          selectedLayerIndex = value; 
        }
			}

			int ITerrainLayersBrushSettingsController.BrushSize
			{
				set 
        {
          brushSize = value;
          brush.Size = value; 
        }
			}

			LayerView[] ITerrainLayersBrushSettingsController.Layers
			{
				get
				{
					var result = new List<LayerView>()
					{
						new LayerView( terrain.HolesLayer, "Holes layer", terrain.GetLayerColor(0), null ),
						new LayerView( terrain.LocalLayer, "Local layer", terrain.GetLayerColor(1), null )
					};

					var layers = terrain.GlobalLayers;
          if ( layers.Length != textures.Count )
          {
            textures.Clear();
            for ( int i = 0; i < layers.Length; ++i )
            {
              PFTerrainTypeInfo info = DataBase.Get<PFTerrainTypeInfo>( layers[i].TerrainTypeInfoId ).Get();

							if(info != null)
							{
								DBPtr<TextureBase> texture = info.pDBMaterial.Get().N_DiffuseMap.texture;

								Stream ddsFile = fileSystem.OpenFile( ( (Texture)texture.Get() ).textureFileName );
								if ( ddsFile != null )
								{
									Bitmap ddsBitmap = DdsImage.Load( ddsFile );
									if ( ddsBitmap != null )
									{
										textures.Add( ddsBitmap );
										continue;
									}
								}	
							}

              textures.Add( null );
            }            
          }

					for ( int i = 0; i < layers.Length; ++i )
					{
						if ( DataBase.IsExists( layers[i].TerrainTypeInfoId ) )
						{
              int startIdx = layers[i].TerrainTypeInfoId.Name.LastIndexOf( "/" );
              if ( startIdx == -1 )
              {
                startIdx = 0;
              }
              else
              {
                startIdx += 1;
              }

              int endIdx = layers[i].TerrainTypeInfoId.Name.IndexOf( "." );
              if ( endIdx == -1 )
              {
                endIdx = layers[i].TerrainTypeInfoId.Name.Length;
              }

              string name = layers[i].TerrainTypeInfoId.Name.Substring( startIdx, endIdx - startIdx );
              result.Add( new LayerView( layers[i], string.Format( "{0} ( global layer {1} )", name, i ), terrain.GetLayerColor( 2 + i ), textures[i] ) );
						}
					}

					return result.ToArray();
				}
			}

			int ITerrainLayersBrushSettingsController.DisplayLayerColors
			{
				set { terrain.LayerDisplayMode = value; }
			}

			public event Operation LayersChanged;

			#endregion

			#region ITerrainLayersProvider Members

			EditorNative.Terrain.Layers.TerrainLayer[] ITerrainLayersProvider.Layers
			{
				get { return Array.ConvertAll( ((ITerrainLayersBrushSettingsController)this).Layers, layerData => layerData.Layer ); }
			}

			#endregion
		}
	}
}
