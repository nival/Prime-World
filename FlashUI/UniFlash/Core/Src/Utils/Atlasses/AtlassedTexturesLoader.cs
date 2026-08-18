using System.Collections.Generic;
using UnityEngine;
using Resources = ResourcesManager.Resources;

namespace Flash.Utils.Atlasses
{
  public static class AtlassedTexturesLoader
  {
    /// <summary>
    /// Cached atlas represented by 2 file: teture and XML data.
    /// XML data file name calculates as: %TEXTURE_NAME_WO_EXTENSION% + ATLAS_DATA_POSTFIX
    /// </summary>
    private static Dictionary<string,AtlassedTexture> _atlassedCache = new Dictionary<string, AtlassedTexture>();
    private static List<string> _loadedAtlasses = new List<string>();

    /// <summary>
    /// Reads atlas and caching containing textures to AtlassesTexture cache.
    /// </summary>
    /// <param name="path"></param>
    public static void LoadAtlas( string atlasName )
    {
      string path = FlashEnv.ATLASES_FOLDER + atlasName;
      if ( _loadedAtlasses.Contains( path ) )
      {
        Debug.LogWarning( string.Format( "Trying to load atlas '{0}' second time. Ignored.", path ) );
        return;
      }
      _loadedAtlasses.Add( path );

      Texture2D atlasTexture = Resources.Load( path ) as Texture2D;
      if ( atlasTexture == null )
      {
        Debug.LogWarning( string.Format( "Can't load atlas at '{0}'. File not found or has invalid format.", path ) );
        return;
      }
      string dataPath = path + FlashEnv.ATLAS_DATA_POSTFIX;
      TextAsset atlasData = Resources.Load( dataPath ) as TextAsset;
      if ( atlasData == null )
      {
        Debug.LogWarning( string.Format( "Can't load atlas data at '{0}'. File not found or has invalid format.", dataPath ) );
        return;
      }
      Dictionary<int, Rect> rects = new Dictionary<int, Rect>();
      Dictionary<int, Vector2> sizes = new Dictionary<int, Vector2>();
      List<string> paths = new List<string>();
      TextureUtils.ReadRectData( atlasData, rects, sizes, paths );

      for ( int i = 0; i < paths.Count; i++ )
      {
        if ( _atlassedCache.ContainsKey( paths[i] ) )
          Debug.LogWarning( "Asset '{0}' atlassed many times. First loaded copy will be used." );
        else
          _atlassedCache.Add( paths[i], new AtlassedTexture( paths[i], rects[i], sizes[i], atlasTexture ) );
      }

      Debug.Log( string.Format( "Readed {0} textures from atlas {1}.", paths.Count, path ) );
      //CLI.Debug( "Readed {0} textures from atlas {1}.", paths.Count, path );
    }

    /// <summary>
    /// Loads AtlassedTexture from early readed atlasses
    /// </summary>
    /// <param name="path">Texture path from Assets/Resources/</param>
    /// <param name="atlassed"></param>
    /// <returns></returns>
    public static bool TryToLoad( string path, out AtlassedTexture atlassed )
    {
      atlassed = null;
      if ( _atlassedCache.ContainsKey( path ) )
      {
        atlassed = _atlassedCache[path];
        return true;
      }
      return false;
    }
  }
}
