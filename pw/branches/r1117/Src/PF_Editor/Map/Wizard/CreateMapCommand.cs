using System.Windows.Forms;
using EditorLib;
using EditorLib.Menu;
using EditorNative.Terrain;
using libdb.DB;
using libdb.Diagnostics;
using libdb.UndoRedo;
using PF_Editor.Properties;

namespace PF_Editor.Map.Wizard
{
  public class CreateMapCommand : IEditorCommand
  {
    public override void Execute( IEditorWinApplication application )
    {
      var dialog = new MapCreationDialog();
      
      if(dialog.ShowDialog() == DialogResult.OK)
      {
        using(var undoRedoTransaction = new UndoRedoTransaction("Create map"))
        {
            if (CreateMap(dialog.MapCreationInformation, application))
            undoRedoTransaction.Commit();
          else
            Log.TraceError( "Can't create map" );
        }
      }
    }

    public override string Name { get { return "Create Map..."; } }

    public override string TooltipText
    {
      get { return "Open Create Map dialog"; }
    }

    public override System.Drawing.Bitmap Image
    {
      get
      {
        return Resources.map;
      }
    }

    #region Private Helpers

    private bool CreateMap(MapCreationInfo info, IEditorWinApplication application)
    {
      if( info == null )
        return false;

      DBID advMapId;
      DBID terrainId;

      if(DBID.TryCreateDBID( info.Path, info.Name, typeof( DBTypes.AdvMap ), out advMapId ) &&
         DBID.TryCreateDBID( info.Path, info.Name, typeof( DBTypes.Terrain ), out terrainId ) )
      {

        DBTypes.AdvMap newMap = new DBTypes.AdvMap
                                {
                                  terrain = CreateTerrain( terrainId, info )
                                };

        DBTypes.AdvMap advMap = DataBase.Create( advMapId, newMap);

        if( DataBase.IsExists( info.LightEnvironmentId ) )
          advMap.lightEnvironment = DataBase.Get<DBTypes.LightEnvironment>( info.LightEnvironmentId );

        if (DataBase.IsExists(info.NightLightEnvironmentId))
          advMap.nightLightEnvironment = DataBase.Get<DBTypes.LightEnvironment>(info.NightLightEnvironmentId);

        application.Application.Extensions.EditorStoreMap(advMap.DBId, application);

        Log.TraceMessage("Map \"{0}\" created succesfully", info.Name);

        return true;
      }

      return false;
    }

    private DBPtr<DBTypes.Terrain> CreateTerrain( DBID terrainId, MapCreationInfo info )
    {
      DBPtr<DBTypes.Terrain> terrain = DataBase.Create( terrainId, new DBTypes.Terrain
                                                                   { 
                                                                     elemXCount = info.Width, 
                                                                     elemYCount = info.Height, 
                                                                     tilesPerElement = info.Resolution 
                                                                   });

      float rW = TerrainUtils.PatchSize * info.Width;
      float rH = TerrainUtils.PatchSize * info.Height;

      var nature = terrain.Get().natureMap;
      nature.editableNatureMap = info.EditableNatureMap;

      nature.baseA.x = 0.125f * rW;
      nature.baseA.y = 0.5f * rH;
      nature.baseB.x = 0.875f * rW;
      nature.baseB.y = 0.5f * rH;

      nature.attackSpaceRoads[0].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.125f * rW, y = 0.75f * rH } );
      nature.attackSpaceRoads[0].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.875f * rW, y = 0.75f * rH } );
      nature.attackSpaceRoads[1].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.250f * rW, y = 0.50f * rH } );
      nature.attackSpaceRoads[1].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.750f * rW, y = 0.50f * rH } );
      nature.attackSpaceRoads[2].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.125f * rW, y = 0.25f * rH } );
      nature.attackSpaceRoads[2].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.875f * rW, y = 0.25f * rH } );

      nature.logicRoads[0].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.125f * rW, y = 0.75f * rH } );
      nature.logicRoads[0].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.875f * rW, y = 0.75f * rH } );
      nature.logicRoads[1].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.250f * rW, y = 0.50f * rH } );
      nature.logicRoads[1].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.750f * rW, y = 0.50f * rH } );
      nature.logicRoads[2].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.125f * rW, y = 0.25f * rH } );
      nature.logicRoads[2].nodes.Add( new DBTypes.Vec2( nature.GetOwner() ) { x = 0.875f * rW, y = 0.25f * rH } );

      var geometry = terrain.Get().geometry;

      DBPtr<DBTypes.StaticMesh> mesh = DataBase.Get<DBTypes.StaticMesh>( info.InitialPatchTypeId );
      DBPtr<DBTypes.Material> mat = mesh.Get().materialsReferences[0];
      for( int x = 0; x < info.Width; ++x )
      {
        for( int y = 0; y < info.Height; ++y )
        {
          geometry.terrainElements.Add(
            new DBTypes.TerrainElementInstance( geometry.GetOwner() )
            {
              position = new DBTypes.Vec3( geometry.GetOwner() )
                         {
                           x = PatchCenter( x ),
                           y = PatchCenter( y )
                         },
              terrainObject = mesh,
              material = mat
            }
            );
        }
      }
      return terrain;
    }

    private static float PatchCenter( int x )
    {
      return x * TerrainUtils.PatchSize + TerrainUtils.PatchSize / 2;
    }

    #endregion

  }
}