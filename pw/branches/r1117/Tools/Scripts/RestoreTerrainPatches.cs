/*
#about Чтобы восстановить патчи: 1) Открыть карту 2) Перейти в режим редактирования патчей 3) Запустить скрипт 4) Сохранить карту
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
#ref EditorPlugins.dll
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using EditorPlugins.Importer.Texture;
using libdb;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using DBTypes;
using System.Windows.Forms;

public class RestoreTerrainPatches
{
  // Можно менять на другие патчи
  private const string PatchFile = "/Terrain/Elements/Plain.STAT";

  private float GetLength( float x, float y )
  {
    return (float)Math.Sqrt( x * x + y * y );
  }

  private TerrainElementInstance GetTerrainElementInstanceByCoord( float x, float y, AdvMap map )
  {
    foreach ( var te in map.terrain.Get().geometry.terrainElements )
    {
      if ( GetLength( x - te.position.x, y - te.position.y ) < Math.Sqrt( 20 ) / 2.0f )
      {
        return te;
      }
    }
    return null;
  }

  public IEnumerable Main(IEditorCommonApplication app, string[] parameters)
  {
    string mapFilePath;

    if ( parameters.Length == 0 )
    {
      //Called from editor UI
      var openFileDialog = new OpenFileDialog
      {
        InitialDirectory = Convert.ToString(Environment.SpecialFolder.Recent),
        Filter = @"Xdb (*.xdb)|*.xdb|All Files (*.*)|*.*",
        Title = @"Choose map for reseting terrain elements",
        FilterIndex = 1
      };

      if (openFileDialog.ShowDialog() == DialogResult.OK)
        mapFilePath = openFileDialog.FileName;
      else
        yield break;
    }
    else
      mapFilePath = parameters[0];

    var fullRootPath = Path.GetFullPath( app.FileSystem.RootPath );
    if ( mapFilePath.Contains( fullRootPath ) )
      mapFilePath = mapFilePath.Substring( fullRootPath.Length );

    var map = DataBase.Get<AdvMap>( DBID.FromFileName( mapFilePath, false ) );

    if ( map == null )
    {
      Log.TraceMessage( "Wrong map path: {0}", mapFilePath );
      yield break;
    }

    Log.TraceMessage( "Reset terrain element for map \"{0}\"...", mapFilePath );

    List<TerrainElementInstance> telist = new List<TerrainElementInstance>();
    var refte = map.Get().terrain.Get().geometry.terrainElements[0];

    for ( int x = 0; x < map.Get().terrain.Get().elemXCount; x++ )
    {
      for ( int y = 0; y < map.Get().terrain.Get().elemYCount; y++ )
      {
        float realx = x * 10.0f + 5.0f;
        float realy = y * 10.0f + 5.0f;
        var te = GetTerrainElementInstanceByCoord( realx, realy, map );
        if ( te == null )
        {
          TerrainElementInstance newte = new TerrainElementInstance( refte.GetOwner(), refte );
          newte.position.x = realx;
          newte.position.y = realy;
          newte.terrainObject = DataBase.Get<StaticMesh>( DBID.FromFileName( PatchFile, false ) );
          newte.material = newte.terrainObject.Get().materialsReferences[0];
          telist.Add( newte );
        }
      }
    }

    foreach( var te in telist )
    {
      map.Get().terrain.Get().geometry.terrainElements.Add( te );
    }

    Log.TraceMessage("Save results..");
    DataBase.Store();
    app.FileSystem.Store();

    yield return true;
  }
}