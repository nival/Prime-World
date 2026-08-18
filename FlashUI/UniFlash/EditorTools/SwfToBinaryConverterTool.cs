using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using Flash;
using Flash.Utils;
using SwfDotNet.IO;
using UnityEditor;
using UnityEngine;
using UnityEngine.UI;

public class SwfToBinaryConverterTool : Editor
{
  private const string SWF_PATH = "Resources/FlashUI";
  private const string SWF_FOLDER = "FlashUI";

  [MenuItem( "Lobby Editors/Flash/Export UniSwf" )]
  public static void DoExportUniSwf()
  {
    TextureUtils.DeleteCache();

    foreach ( string relativePath in FindSwfTextAssets() )
    {
      TextAsset bytesAsset = GetResource( relativePath );

      if ( bytesAsset != null )
        ExportSwfAsset( bytesAsset );
    }

    Debug.Log( "UniSwf export done" );
  }

  [MenuItem( "Lobby Editors/Flash/Export FontStorages" )]
  public static void DoExportFontStorages()
  {
    ExportFontStorages( FlashEnv.FONTSTORAGE_CACHE_PATH );
  }

  [MenuItem( "Lobby Editors/Flash/Run internal test" )]
  public static void DoRunInternalTest()
  {
    string bytesPath = "Assets/Resources/FlashUI/main.bytes";

    TextAsset bytesAsset = GetResource( bytesPath );

    ExportSwfAsset( bytesAsset );
    ImportSwfAsset( bytesAsset );

    Debug.Log( "UniSwf export done" );
  }

  [MenuItem( "Lobby Editors/Flash/Clear Binary Cache" )]
  public static void ClearBinaryCache()
  {
    TextureUtils.DeleteCache();
    Debug.Log( "Binary Cache Cleared" );
  }

  public static void ExportFontStorages( string path )
  {
    Debug.Log( "FontStorages export..." );
    var startTime = Time.realtimeSinceStartup;
    var chars =
    @"АаБбВвГгДдЕеЁёЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЪъЫыЬьЭэЮюЯяABCDEFGHIKLMNOPQRSTVXYZabcdefghiklmnopqrstvxyz1234567890~!@#$%^&*()_+!№;%:?*()_+./|\'""";
    List<IFontStorage> storages = new List<IFontStorage>( 11 );
    storages.Add( FontStorage.GetStorage( FontStorage.DefaultFont, 32, FontStyle.Normal ) );
    for ( int i = 10; i <= 20; i++ )
      storages.Add( FontStorage.GetStorage( FontStorage.DefaultFont, i, FontStyle.Normal ) );

    foreach ( var fontStorage in storages )
      fontStorage.SetString( chars );
    FontStorage.CacheFontStorage( path );

    Debug.Log( "FontStorages export...Ok " + ( Time.realtimeSinceStartup - startTime ) );
  }

  private static TextAsset GetResource( string relativeAssetPath )
  {
    TextAsset asset = AssetDatabase.LoadAssetAtPath( relativeAssetPath, typeof( TextAsset ) ) as TextAsset;

    if ( asset == null )
    {
      Debug.LogError( "Unable to load asset at path:" + relativeAssetPath );
      return null;
    }

    return asset;
  }

  public static void ExportAsset( string assetPath )
  {
    TextAsset bytesAsset = GetResource( assetPath );

    ExportSwfAsset( bytesAsset );
  }

  //public static void ExportSwfAsset( FontStorage storage )
  //{

  //}

  public static void ExportSwfAsset( TextAsset textAsset )
  {
    if ( textAsset == null )
    {
      Debug.LogError( "ExportSwfAsset: Can't export empty SWF asset" );
      return;
    }

    SwfReader reader = new SwfReader( new MemoryStream( textAsset.bytes ) );
    Swf swf = reader.ReadSwf();
    UniSwf uniSwf = new UniSwf( swf, textAsset.name, true, true );

    if ( !Directory.Exists( ExportPath ) )
      Directory.CreateDirectory( ExportPath );

    TextureUtils.CacheSwfAtlas( uniSwf, textAsset.name );

    string filePath = TranslateAssetPath( textAsset );

    using ( FileStream outStream = new FileStream( filePath, FileMode.Create, FileAccess.Write ) )
    {
      BinaryFormatter formatter = new BinaryFormatter();

      formatter.Serialize( outStream, uniSwf );
      outStream.Close();
    }
  }

  private static void ImportSwfAsset( TextAsset textAsset )
  {
    string resourcePath = TranslateAssetPath( textAsset );

    FileStream stream = new FileStream( resourcePath, FileMode.Open, FileAccess.Read );
    BinaryFormatter formatter = new BinaryFormatter();

    UniSwf uniSwf = (UniSwf)formatter.Deserialize( stream );
    uniSwf.DeserializeCompleted();


    Debug.Log( "Deserialization done" );
  }

  private static string ExportPath
  {
    get { return Application.dataPath + "/" + SWF_PATH; }
  }

  public static string GetBinCachePath( string assetName )
  {
    return ExportPath + "/" + assetName + ".bin.bytes";
  }

  private static string TranslateAssetPath( TextAsset textAsset )
  {
    return GetBinCachePath( textAsset.name );
  }

  private static IEnumerable<string> FindSwfTextAssets()
  {
    List<string> assets = new List<string>();
    string pathPrefix = Application.dataPath + "/";

    foreach ( string item in Directory.GetFiles( pathPrefix + SWF_PATH ) )
    {
      if ( item.EndsWith( ".bin.bytes", StringComparison.InvariantCultureIgnoreCase ) )
        continue;

      if ( item.EndsWith( ".atlas.bytes", StringComparison.InvariantCultureIgnoreCase ) )
        continue;

      if ( item.EndsWith( ".png", StringComparison.InvariantCultureIgnoreCase ) )
        continue;

      if ( !item.EndsWith( ".bytes", StringComparison.InvariantCultureIgnoreCase ) )
        continue;

      string finalPath = "Assets/" + item.Replace( pathPrefix, "" ).Replace( "\\", "/" );

      assets.Add( finalPath );
    }

    return assets.ToArray();
  }

  [MenuItem( "Lobby Editors/Flash/Generate atlases" )]
  public static void CreateAtlases()
  {
    TextureUtils.DeleteCache();

    foreach ( string swfEntry in FindSwfTextAssets() )
    {
      CreateForAsset( swfEntry );
    }

    GC.Collect();
    Debug.Log( "Finished generating atlases, now please restart Unity (before it crashes on texture reimport)" );
  }

  [MenuItem( "Lobby Editors/Flash/Generate atlas for..." )]
  public static void CreateAtlasFor()
  {
    string path = EditorUtility.OpenFilePanel( "Select *.bytes file", "Assets/Resources/FlashUI", "bytes" );
    if ( path.Length != 0 )
    {
      TextureUtils.DeleteCache();

      string finalPath = "Assets" + path.Replace( Application.dataPath, "" ).Replace( "\\", "/" );

      if ( !CreateForAsset( finalPath ) )
      {
        Debug.LogError( "Atlas generation error" );
        return;
      }

      string name = Path.GetFileNameWithoutExtension( path );

      GameObject g = new GameObject( "__ATLAS: " + name, typeof( RawImage ) );

      g.GetComponent<RawImage>().texture = Resources.Load( SWF_FOLDER + "/" + name, typeof( Texture2D ) ) as Texture2D;
      g.SetActive(false);

      GC.Collect();
      Debug.Log( "Atlas generated for: " + finalPath );
    }
    else
    {
      Debug.Log( "Atlas generation was cancelled" );
    }

  }

  private static bool CreateForAsset( string path )
  {
    Debug.Log( "Processing flash asset " + path );

    TextAsset swfAsset = AssetDatabase.LoadAssetAtPath( path, typeof( TextAsset ) ) as TextAsset;

    if ( swfAsset == null )
    {
      Debug.LogError( "Unable to load asset " + path + " (not a fatal error -- proceeding to next asset)" );
      return false;
    }

    //GC.Collect();
    return TextureUtils.CacheSwfAtlas( swfAsset );
  }
}