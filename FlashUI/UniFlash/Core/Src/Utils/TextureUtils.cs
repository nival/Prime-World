using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Xml;
using Flash.Utils.Atlasses;
using SwfDotNet.IO;
using UnityEngine;
using Application = UnityEngine.Application;
using Resources = ResourcesManager.Resources;

namespace Flash.Utils
{
  public static class TextureUtils
  {
    public const string TEXTURE_CLONE_POSTFIX = "_FLASH_TEXTURE_CLONE";
    private const int GRADIENT_RESOLUTION = 256;

    private static string PathToCache { get { return "/Resources/FlashUI"; } }

    private static string GetRelativeAtlasPath( string assetName )
    {
      return "FlashUI/" + assetName;
    }

    private static string GetRelativeAtlasDataPath( string assetName )
    {
      return "FlashUI/"  + assetName + ".atlas";
    }

    private static string GetAtlasPath( string assetName )
    {
      return Application.dataPath + PathToCache + "/" + assetName + ".png";
    }

    private static string GetAtlasDataPath( string assetName )
    {
      return Application.dataPath + PathToCache + "/" + assetName + ".atlas.bytes";
    }

    public struct TextureDesc
    {
      public int originalWidth;
      public int originalHeight;

      TextureDesc( int _originalWidth, int _originalHeight )
      {
        originalWidth = _originalWidth;
        originalHeight = _originalHeight;
      }
    }

    private static Dictionary<string, TextureDesc> _npot2pot = new Dictionary<string, TextureDesc>();

    /// <summary>
    /// Get readable flag from texture, setted in import.
    /// Strange implementation, but in unity 3.5.5 no other way to check it.
    /// </summary>
    /// <param name="tex"></param>
    /// <returns></returns>
    public static bool IsReadable( Texture2D tex )
    {
      bool catched = false;
      try
      {
        tex.Apply( false, false );
      }
      catch ( Exception )
      {
        catched = true;
      }
      return !catched;
    }

    /// <summary>
    /// Is texture has power of two size
    /// </summary>
    /// <param name="texture"></param>
    /// <returns></returns>
    public static bool isPOT( Texture texture )
    {
      return ( Mathf.Log( texture.width, 2 ) % 1 == 0 ) && ( Mathf.Log( texture.height, 2 ) % 1 == 0 );
    }

    public static void ExtendToPowerOfTwo( Texture2D source, string _name, ref int originalWidth, ref int originalHeight )
    {
      TextureDesc textureDesc;

      if ( _npot2pot.TryGetValue( _name + TEXTURE_CLONE_POSTFIX, out textureDesc ) )
      {
        originalWidth = textureDesc.originalWidth;
        originalHeight = textureDesc.originalHeight;
        return;
      }

      // pow
      int newWidth = 1;
      int newHeight = 1;
      textureDesc.originalWidth = source.width;
      textureDesc.originalHeight = source.height;

      GetNextPowOfTwo( source.width, source.height, ref newWidth, ref newHeight );

      // if tex was is pow of two
      if ( newWidth == textureDesc.originalWidth && newHeight == textureDesc.originalHeight )
      {
        return;
      }

      if ( source.format != TextureFormat.ARGB32 && source.format != TextureFormat.RGBA32 )
      {
        if (source.format == TextureFormat.RGB24)
        {
          Debug.LogWarningFormat("JPEG texture source for '{0}'", source.name);
        }
        else
        {
          Debug.LogErrorFormat("Wrong texture format for '{0}': {1}", source.name, source.format);
        }
      }

      // ��� ������������� �� ������ ������ ������ ������ ��� ���� ����� ������� �������� ��
      // ��������� ������� ������ ������ Read / Write Enable = false
      source.GetPixels();

      /*
      if ( copy )
      {
        texture = new Texture2D( source.width, source.height, TextureFormat.ARGB32, false );
        texture.name = source.name + TEXTURE_CLONE_POSTFIX;
        texture.SetPixels( source.GetPixels() );
      }
      else
      {
        texture = source;
      }
      /**/

      _npot2pot.Add( _name + TEXTURE_CLONE_POSTFIX, textureDesc );

      Color[] pixels = source.GetPixels();
      source.Reinitialize( newWidth, newHeight );

      // Clear
      Color[] clear = new Color[newWidth * newHeight];
      source.SetPixels( clear );
      source.SetPixels( 0, newHeight - textureDesc.originalHeight, textureDesc.originalWidth, textureDesc.originalHeight, pixels );

      source.Apply( false, true );
    }
    public static Texture2D Resample( Texture2D source, int width, int height )
    {
      TextureFormat format = source.format;
      if (format != TextureFormat.ARGB32 || format != TextureFormat.RGBA32)
      {
        format = TextureFormat.RGBA32;
      }
      Texture2D result = new Texture2D( width, height, format, false );
      for ( int i = 0; i < height; i++ )
      {
        for ( int j = 0; j < width; j++ )
        {
          result.SetPixel( i, j, source.GetPixelBilinear( ( i + 0.25F ) / width, ( j + 0.25F ) / height ) );
        }
      }
      result.Apply();

      return result;
    }
    public static void GetNextPowOfTwo( int width, int height, ref int powOf2Width, ref int powOf2Height )
    {
      // pow
      int oldWidth = width;
      int oldHeight = height;

      int i = 0;
      do
      {
        powOf2Width = 1 << i;
        i++;
      } while ( powOf2Width < oldWidth );

      i = 0;
      do
      {
        powOf2Height = 1 << i;
        i++;
      } while ( powOf2Height < oldHeight );
    }

    public static bool CacheSwfAtlas( TextAsset swfAsset )
    {
      MemoryStream stream = new MemoryStream( swfAsset.bytes );
      SwfReader reader = new SwfReader( stream );
      Swf swf = reader.ReadSwf();

      UniSwf uniSwf = new UniSwf( swf, swfAsset.name, false, false );
      return CacheSwfAtlas( uniSwf, swfAsset.name );
    }

    public static bool CacheSwfAtlas( UniSwf uniSwf, string assetName )
    {
      string atlasFile = GetAtlasPath( assetName );
      string atlasDataFile = GetAtlasDataPath( assetName );

      try
      {
        AtlasData atlas = GenerateTextureAtlas( uniSwf.TextureResources );
        CacheTexture( atlasFile, atlas.Atlas );
        CacheRectData( atlasDataFile, atlas.Rects, uniSwf.TextureResources );

        //foreach ( Texture2D texture2D in uniSwf.TextureResources )
        //  Texture2D.DestroyImmediate( texture2D );
      }
      catch ( Exception e )
      {
        if ( File.Exists( atlasFile ) )
          File.Delete( atlasFile );

        if ( File.Exists( atlasDataFile ) )
          File.Delete( atlasDataFile );

        Debug.LogError( String.Format( "Caching {0} failed {1}.\n{2}", assetName, e.Message, e.StackTrace ) );
        return false;
      }
      finally
      {
#if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
#endif        
      }

      Debug.Log( String.Format( "Caching {0} complited.", assetName ) );
      return true;
    }

    public static AtlasData LoadAtlas( string assetName )
    {
      string atlasFile = GetRelativeAtlasPath( assetName );
      string atlasDataFile = GetRelativeAtlasDataPath( assetName );

      Texture2D atlas = Resources.Load( atlasFile, typeof( Texture2D ) ) as Texture2D;
      TextAsset atlasData = Resources.Load( atlasDataFile, typeof( TextAsset ) ) as TextAsset;

      if ( atlas != null )
      {
        if ( atlasData != null )
        {
          Dictionary<int, Rect> atlasRects = new Dictionary<int, Rect>();
          Dictionary<int, Vector2> atlasSizes = new Dictionary<int, Vector2>();
          ReadRectData( atlasData, atlasRects, atlasSizes );

          NivalCLI.CLI.Debug( "Atlas cache has found for \"{0}\"!", assetName );
          return new AtlasData( atlas, atlasRects, atlasSizes );
        }
      }

      return null;
    }

    public static void DeleteCache()
    {
      string cacheDir = Application.dataPath + PathToCache;
      foreach ( string file in Directory.GetFiles( cacheDir ) )
      {

        if ( file.EndsWith( ".png", StringComparison.InvariantCultureIgnoreCase ) ||
             file.EndsWith( ".png.meta", StringComparison.InvariantCultureIgnoreCase ) ||
             file.EndsWith( ".atlas.bytes", StringComparison.InvariantCultureIgnoreCase ) ||
             file.EndsWith( ".atlas.bytes.meta", StringComparison.InvariantCultureIgnoreCase ) ||
             file.EndsWith( ".bin.bytes", StringComparison.InvariantCultureIgnoreCase ) || //��� ������ �������� ������ ��������� ������, �.�. ��������� � �� ����
             file.EndsWith( ".bin.bytes.meta", StringComparison.InvariantCultureIgnoreCase ) )
        {
          // PF-102150 ������ 10 ������� ������� ����, ���� �� ���-�� �����, ����� ����������
          for (int i = 0; i < 10; i++)
          {
            try
            {
              if (File.Exists(file))
              {
                File.Delete(file);
              }
              break;
            }
            catch (IOException)
            {
              Thread.Sleep(1000);
            }
            catch (Exception ex)
            {
              Debug.LogError(ex.Message);
              break;
            }
          }
        }
      }

#if UNITY_EDITOR
      UnityEditor.AssetDatabase.Refresh();
#endif
        
    }

    // TODO ������ ������ ����������
    public static void GenerateGradient( UniFillStyle fillStyle, UniSwf uniSwf )
    {
      int heigth = 1;

      if ( uniSwf.AtlasIsNotCached() )
      {
        Texture2D gradient = new Texture2D( GRADIENT_RESOLUTION, heigth, TextureFormat.ARGB32, false );
        gradient.name = FlashEnv.GRADIENT_NAME;

        for ( int i = 0; i < fillStyle.GradientRecords.Count - 1; ++i )
        {
          UniGradientRecord rec0 = fillStyle.GradientRecords[i];
          UniGradientRecord rec1 = fillStyle.GradientRecords[i + 1];

          for ( int pix = rec0.ratio; pix <= rec1.ratio; ++pix )
          {
            float t = (float)( pix - rec0.ratio ) / ( rec1.ratio - rec0.ratio );
            gradient.SetPixel( pix, 0, Color.Lerp( rec0.color, rec1.color, t ) );
          }

          // before first
          if ( i == 0 && rec0.ratio != 0 )
          {
            for ( int pix = 0; pix <= rec0.ratio; ++pix )
            {
              gradient.SetPixel( pix, 0, rec0.color );
            }
          }

          // after last
          if ( i == fillStyle.GradientRecords.Count - 2 && rec1.ratio != 255 )
          {
            for ( int pix = rec1.ratio; pix <= 255; ++pix )
            {
              gradient.SetPixel( pix, 0, rec1.color );
            }
          }
        }

        // square gradient
        for ( int i = 0; i < heigth; ++i )
        {
          gradient.SetPixels( 0, i, GRADIENT_RESOLUTION, 1, gradient.GetPixels( 0, 0, GRADIENT_RESOLUTION, 1 ) );
        }

        gradient.wrapMode = TextureWrapMode.Clamp;
        gradient.Apply();

        //GameObject g = new GameObject("tex", typeof(GUITexture));
        //g.GetComponent<GUITexture>().texture = gradient;

        uniSwf.TextureResources.Add( gradient );
        fillStyle.GradientID = uniSwf.TextureResources.Count - 1;
      }
      else
      {
        uniSwf.TextureResources.Add( null );
        fillStyle.GradientID = uniSwf.TextureResources.Count - 1;
      }
    }

    /// <summary>
    /// Packs textures to bit POT atlas texture with locking gradient area
    /// for FlashFramework needs
    /// </summary>
    /// <param name="resources">Input textures</param>
    /// <returns>AtlasData for created atlas</returns>
    public static AtlasData GenerateTextureAtlas( List<Texture2D> resources )
    {
      return GenerateTextureAtlas( resources, true );
    }

    /// <summary>
    /// Packs textures to bit POT atlas texture
    /// </summary>
    /// <param name="resources">Input textures</param>
    /// <param name="lockGradient">using for FlashFramework gradiends packing</param>
    /// <returns>AtlasData for created atlas</returns>
    public static AtlasData GenerateTextureAtlas( List<Texture2D> resources, bool lockGradient )
    {
      NivalCLI.Profiler.Start("GenerateTextureAtlas");
      Texture2D[] textures = resources.ToArray();

      Texture2D atlas = new Texture2D( 1, 1, TextureFormat.ARGB32, false );
      Rect[] rect = PackTextures( atlas, textures, lockGradient );
      atlas.filterMode = FilterMode.Bilinear;
      atlas.wrapMode = TextureWrapMode.Clamp;

      Dictionary<int, Rect> rects = new Dictionary<int, Rect>();
      Dictionary<int, Vector2> sizes = new Dictionary<int, Vector2>();

      for ( int i = 0; i < textures.Length; ++i )
      {
        rects.Add( i, rect[i] );
        sizes.Add( i, new Vector2( textures[i].width, textures[i].height ) );
      }

      var aData =  new AtlasData( atlas, rects, sizes );
      NivalCLI.Profiler.Stop("GenerateTextureAtlas");
      return aData;
    }

    private static void CacheRectData( string fileName, Dictionary<int, Rect> data, List<Texture2D> textureResources )
    {
      CacheRectDataToFile( fileName, data, textureResources, null );
    }

    public static void CacheRectDataToFile( string fileName, Dictionary<int, Rect> data, List<Texture2D> textureResources, List<string> resourcesPaths )
    {
      XmlTextWriter xmlWriter = new XmlTextWriter( fileName, Encoding.UTF8 );
      try
      {
        xmlWriter.Formatting = Formatting.Indented;
        xmlWriter.WriteStartDocument();
        xmlWriter.WriteStartElement( "root" );
        foreach ( KeyValuePair<int, Rect> pair in data )
        {
          xmlWriter.WriteStartElement( FlashEnv.NODE_NAME );
          xmlWriter.WriteAttributeString( FlashEnv.ID_NAME, pair.Key.ToString() );
          if ( resourcesPaths != null )
            xmlWriter.WriteAttributeString( FlashEnv.RESOURCES_PATH_NAME, resourcesPaths[pair.Key] );
          xmlWriter.WriteAttributeString( FlashEnv.WIDTH_NAME, textureResources[pair.Key].width.ToString() );
          xmlWriter.WriteAttributeString( FlashEnv.HEIGHT_NAME, textureResources[pair.Key].height.ToString() );
          xmlWriter.WriteAttributeString( FlashEnv.X_NAME, pair.Value.x.ToString() );
          xmlWriter.WriteAttributeString( FlashEnv.Y_NAME, pair.Value.y.ToString() );
          xmlWriter.WriteAttributeString( FlashEnv.W_NAME, pair.Value.width.ToString() );
          xmlWriter.WriteAttributeString( FlashEnv.H_NAME, pair.Value.height.ToString() );
          xmlWriter.WriteEndElement();
        }
        xmlWriter.WriteEndElement();
        xmlWriter.WriteEndDocument();
      }
      finally
      {
        xmlWriter.Close();
      }
    }

    private static void ReadRectData( TextAsset atlasData, Dictionary<int, Rect> atlasRects, Dictionary<int, Vector2> atlasSizes )
    {
      ReadRectData( atlasData, atlasRects, atlasSizes, null );
    }

    public static void ReadRectData( TextAsset atlasData, Dictionary<int, Rect> atlasRects, Dictionary<int, Vector2> atlasSizes, List<string> resourcesPaths )
    {
      MemoryStream stream = new MemoryStream( atlasData.bytes );
      XmlTextReader xmlReader = new XmlTextReader( stream );

      try
      {
        while ( xmlReader.Read() )
        {
          if ( xmlReader.NodeType == XmlNodeType.Element )
          {
            if ( xmlReader.Name == FlashEnv.NODE_NAME )
            {
              int id = 0;
              int width = 0;
              int height = 0;
              float x = 0;
              float y = 0;
              float w = 0;
              float h = 0;
              //string resourcesPath;

              if ( xmlReader.MoveToAttribute( FlashEnv.ID_NAME ) )
                id = int.Parse( xmlReader.Value );
              if ( resourcesPaths != null && xmlReader.MoveToAttribute( FlashEnv.RESOURCES_PATH_NAME ) )
                resourcesPaths.Add( xmlReader.Value );
              xmlReader.MoveToAttribute( FlashEnv.WIDTH_NAME );
              width = int.Parse( xmlReader.Value );
              xmlReader.MoveToAttribute( FlashEnv.HEIGHT_NAME );
              height = int.Parse( xmlReader.Value );
              xmlReader.MoveToAttribute( FlashEnv.X_NAME );
              x = float.Parse( xmlReader.Value, CultureInfo.InvariantCulture );
              xmlReader.MoveToAttribute( FlashEnv.Y_NAME );
              y = float.Parse( xmlReader.Value, CultureInfo.InvariantCulture );
              xmlReader.MoveToAttribute( FlashEnv.W_NAME );
              w = float.Parse( xmlReader.Value, CultureInfo.InvariantCulture );
              xmlReader.MoveToAttribute( FlashEnv.H_NAME );
              h = float.Parse( xmlReader.Value, CultureInfo.InvariantCulture );

              atlasSizes.Add( id, new Vector2( width, height ) );
              atlasRects.Add( id, new Rect( x, y, w, h ) );
            }
          }
        }
      }
      finally
      {
        xmlReader.Close();
      }
    }
    public static void CacheTexture( string dir, string name, Texture2D texture )
    {
      CacheTexture( dir + "/" + name + ".png", texture );
    }
    public static void CacheTexture( string fileName, Texture2D texture )
    {
      byte[] bytes = texture.EncodeToPNG();
      FileStream stream = null;
      try
      {
        stream = new FileStream(fileName, FileMode.OpenOrCreate);
        stream.Write(bytes, 0, bytes.Length);
      }
      finally
      {
        if (stream != null)
        {
          stream.Close();
        }
      }
    }

    private static Rect[] PackTextures( Texture2D atlas, Texture2D[] textures, bool lockGradient )
    {
      if ( textures == null || textures.Length == 0 || atlas == null )
        return null;

      // Sort textures
      Texture2D[] sortedTextures = new Texture2D[textures.Length];
      textures.CopyTo( sortedTextures, 0 );
      Array.Sort<Texture2D>( sortedTextures, new TextureComparer() );

      // Resize atlas
      int square = 0;
      foreach ( Texture2D sortedTexture in sortedTextures )
        square += sortedTexture.width * sortedTexture.height;

      Vector2[] pow2squares = new Vector2[] { new Vector2( 512, 512 ),
        new Vector2( 1024, 512 ), new Vector2( 1024, 1024 ), 
        new Vector2( 2048, 1024 ), new Vector2( 2048, 2048 ), 
        new Vector2( 4096, 2048 ), new Vector2( 4096, 4096 ) ,
        new Vector2( 4096*2, 4096 ), new Vector2( 4096*2, 4096*2 ),
        new Vector2( 4096*4, 4096*2 ), new Vector2( 4096*4, 4096*4)
      };
      int s = 0;
      Vector2 size = pow2squares[0];
      for ( int i = 0; i < pow2squares.Length; ++i )
      {
        if ( square < pow2squares[i].x * pow2squares[i].y )
        {
          s = i;
          size = pow2squares[s];
          break;
        }
      }
      if ( !atlas.Reinitialize( (int)size.x, (int)size.y ) )
      {
        Debug.LogError( "Atlas resize Error!" );
        return null;
      }

      // Try do pack
      Dictionary<Texture2D, Rect> tex2Rect = new Dictionary<Texture2D, Rect>( textures.Length );
      Rect[] rects = DoPack( atlas, sortedTextures, tex2Rect, lockGradient );
      while ( rects == null ) // fail
      {
        if ( s == pow2squares.Length - 1 )
        {
          Debug.LogError( "Packing Error ! Atlas size must be too big > : " + atlas.width + " " + atlas.height );
          return null;
        }

        // Get more size
        size = pow2squares[++s];

        if ( !atlas.Reinitialize( (int)size.x, (int)size.y ) )
        {
          Debug.LogError( "Atlas resize Error!" );
          return null;
        }

        rects = DoPack( atlas, sortedTextures, tex2Rect, lockGradient );
      }

      atlas.Apply();

      // Normalize rectangles
      for ( int i = 0; i < textures.Length; ++i )
      {
        rects[i] = tex2Rect[textures[i]];
        rects[i] = new Rect( rects[i].x / atlas.width, rects[i].y / atlas.height, rects[i].width / atlas.width, rects[i].height / atlas.height );
      }

      return rects;
    }
    private static Rect[] DoPack( Texture2D atlas, Texture2D[] sortedTextures, Dictionary<Texture2D, Rect> tex2Rect )
    {
      return DoPack( atlas, sortedTextures, tex2Rect, true );
    }

    private static Rect[] DoPack( Texture2D atlas, Texture2D[] sortedTextures, Dictionary<Texture2D, Rect> tex2Rect, bool lockGradient )
    {
      Rect[] rects = new Rect[sortedTextures.Length];
      tex2Rect.Clear();
      Node root = new Node( new Rect( 0, 0, atlas.width, atlas.height ) );
      Node gradientRoot = null;
      //Gradient area in left bottom corner of the atlas.
      //Using for FlashFramework gradient densely packing
      if ( lockGradient )
      {
        Rect gradientRect = new Rect( 0, 0, 256, 1024 );
        //Guarantees that gradient will be lockable in atlas
        if ( atlas.height < gradientRect.height )
          gradientRect = new Rect( 0, 0, 256, atlas.height );

        gradientRoot = new Node( gradientRect );

        if ( !root.Lock( gradientRoot.Rect ) )
          Debug.LogError( "Can't lock gradient area!" );
      }
      for ( int i = 0; i < sortedTextures.Length; ++i )
      {
        Node node = null;
        if ( sortedTextures[i].name != FlashEnv.GRADIENT_NAME )
          node = root.Insert( sortedTextures[i] );
        else
        {
          if ( lockGradient )
            node = gradientRoot.Insert( sortedTextures[i] );
        }

        if ( node != null )
        {
          atlas.SetPixels( (int)node.Rect.x, (int)node.Rect.y, (int)node.Rect.width, (int)node.Rect.height,
                          sortedTextures[i].GetPixels() );
          tex2Rect.Add( sortedTextures[i], node.Rect );
        }
        else
        {
          return null;
        }
      }

      return rects;
    }
  }

  internal class Node
  {
    private Node[] _childs;
    private Texture2D _texture;
    private bool _locked;
    private Rect _rect;
    public Rect Rect
    {
      get { return _rect; }
    }

    public Node() { }
    public Node( Rect rect )
    {
      _rect = rect;
    }
    public Node Insert( Texture2D texture )
    {
      if ( _childs != null )
      {
        Node node = _childs[0].Insert( texture );
        if ( node != null )
          return node;
        return _childs[1].Insert( texture );
      }
      else
      {
        if ( _texture != null || _locked )
          return null;

        if ( _rect.width < texture.width || _rect.height < texture.height )
          return null;

        if ( _rect.width == texture.width && _rect.height == texture.height )
        {
          _texture = texture;
          return this;
        }

        _childs = new Node[2];
        _childs[0] = new Node();
        _childs[1] = new Node();

        int dw = (int)_rect.width - texture.width;
        int dh = (int)_rect.height - texture.height;

        if ( dw > dh )// vert
        {
          _childs[0]._rect = new Rect( _rect.x, _rect.y, texture.width, _rect.height );
          _childs[1]._rect = new Rect( _rect.x + texture.width, _rect.y, _rect.width - texture.width, _rect.height );
        }
        else// horiz
        {
          _childs[0]._rect = new Rect( _rect.x, _rect.y, _rect.width, texture.height );
          _childs[1]._rect = new Rect( _rect.x, _rect.y + texture.height, _rect.width, _rect.height - texture.height );
        }

        return _childs[0].Insert( texture );
      }
    }
    public bool Lock( Rect lockRect )
    {
      if ( _childs != null )
      {
        if ( _childs[0].Lock( lockRect ) )
          return true;
        return _childs[1].Lock( lockRect );
      }
      else
      {
        if ( _texture != null || _locked )
          return false;

        if ( _rect.width < lockRect.width || _rect.height < lockRect.height )
          return false;

        if ( _rect.width == lockRect.width && _rect.height == lockRect.height )
        {
          _locked = true;
          return true;
        }

        _childs = new Node[2];
        _childs[0] = new Node();
        _childs[1] = new Node();

        int dw = (int)_rect.width - (int)lockRect.width;
        int dh = (int)_rect.height - (int)lockRect.height;

        if ( dw > dh )// vert
        {
          _childs[0]._rect = new Rect( _rect.x, _rect.y, lockRect.width, _rect.height );
          _childs[1]._rect = new Rect( _rect.x + lockRect.width, _rect.y, _rect.width - lockRect.width, _rect.height );
        }
        else// horiz
        {
          _childs[0]._rect = new Rect( _rect.x, _rect.y, _rect.width, lockRect.height );
          _childs[1]._rect = new Rect( _rect.x, _rect.y + lockRect.height, _rect.width, _rect.height - lockRect.height );
        }

        return _childs[0].Lock( lockRect );
      }
    }
    public override string ToString()
    {
      return "NODE : " + _texture.name + " " + _rect.ToString();
    }
  }

  internal class TextureComparer : IComparer<Texture2D>
  {
    public int Compare( Texture2D x, Texture2D y )
    {
      if ( x == y )
        return 0;

      if ( x == null )
        return 1;

      if ( y == null )
        return -1;

      // if gradient exist
      if ( x.name == FlashEnv.GRADIENT_NAME && y.name == FlashEnv.GRADIENT_NAME )
        return 0;
      if ( x.name == FlashEnv.GRADIENT_NAME )
        return 1;
      if ( y.name == FlashEnv.GRADIENT_NAME )
        return -1;

      return -( x.width * x.height - y.width * y.height );
    }
  }
}