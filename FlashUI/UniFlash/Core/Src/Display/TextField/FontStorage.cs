using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using Flash.Utils;
using NivalCLI;
using UnityEngine;
using UnityEngine.Assertions;

using Resources = ResourcesManager.Resources;

namespace Flash
{
  [Serializable]
  public class FontStorage : ISerializable, IFontStorage
  {
    /// <summary>
    /// Using for OSX AA compensation. 
    /// Even after "defaults write CoreGraphics CGFontDisableAntialiasing YES" fonts drawn with anti aliasing
    /// </summary>
    public const int OSX_AA_PIXEL_OFFSET = 2;

    public const int DEFAULT_TEX_SIZE = 1024;
    public const int GLYPH_MARGIN = 4;
    private const char DOT = '.';
    private static bool LoadedFromCache = false;
    public const string DEFAULT_FONT_TEX_NAME = "__FONT_TEXTURE";
    private const string FONT_STORAGE_GONAME = "__FLASH_FONT_STORAGE";
    private const string DEFAULT_FONT_NAME = "DejaVu LGC Sans";
    private const string CACHE_FILENAME = "FlashUI/fontStorage.bin";
    public const TextureFormat TEXTURE_FORMAT = TextureFormat.ARGB32;

    public static Action FontsDataWasReseted;
    public static Action FontTextureWasReseted;
    private static GameObject _mainFontStorageObject;
    private static bool _init;
    private static FontStorageDebugViewer _debug;
    private static bool _isTextureWasBroken = false;
    private static bool _deviceObtainedSubscribed = false;
    private static List<FontStorage> _globalStorage = new List<FontStorage>();
    private static Texture2D _charTex;
    private static LayoutSolver _mainTexSolver;
    private static readonly Dictionary<Texture2D, LayoutSolver> _charDatabase = new Dictionary<Texture2D, LayoutSolver>();
    private static byte _id = 1;

    private static readonly Font _defaultFont = Resources.Load( FlashEnv.FONTS_PATH + DEFAULT_FONT_NAME ) as Font;
    public static Font DefaultFont
    {
      get
      {
        return _defaultFont;
      }
    }

    /// <summary>
    /// Names of file(not fonts names from Font.name) for loading like "MyFolder/FontName"
    /// Using for make links by fontid between TextFields and FontStorage after binary serialization
    /// </summary>
    private static Dictionary<int, string> _loadedFontsNames = new Dictionary<int, string>();
    public static Dictionary<int, string> LoadedFontsNames
    {
      get { return _loadedFontsNames; }
      set { _loadedFontsNames = value; }
    }

    private static Dictionary<int, Font> _fontsMap = new Dictionary<int, Font>();
    public static Dictionary<int, Font> FontsMap
    {
      get { return _fontsMap; }
    }

    public static bool TryLoadFontToMap( int fontId, string fontName )
    {
      if ( _fontsMap.ContainsKey( fontId ) )
        return false;

      Font font = Resources.Load( FlashEnv.FONTS_PATH + fontName ) as Font;

      if ( font == null )
      {
        NivalCLI.CLI.Warning( "Font {0} is not found, use default font.", fontName );
        font = DefaultFont;
      }
      _fontsMap.Add( fontId, font );
      _loadedFontsNames.Add( fontId, fontName );
      CLI.Debug( "Font '{0}' loaded to map for id={1}", font.name, fontId );
      return true;
    }

    private static Dictionary<Font,FontDataTTF> _ttfDataMap = new Dictionary<Font, FontDataTTF>();
    private static readonly List<char> _formatSymbols = new List<char> { ' ', '\n', '\t', '\r' };
    public static List<char> FormatSymbols
    {
      get { return _formatSymbols; }
    }

    private Font _font;
    private FontDataTTF _ttfData;
    private int _size;
    private FontStyle _style;
    private Dictionary<object, IFontMetrics> _charSet = new Dictionary<object, IFontMetrics>();
    private readonly Dictionary<UInt32, int> _pixKern = new Dictionary<uint, int>();
    private int _baseLine;
    public int BaseLine
    {
      get { return _baseLine; }
    }

    #region Caching FontStorages
    /// Simply structured variables for serialization process help
    private List<Metrics> _serializationMetrics;
    private string _serializationFontName = string.Empty;
    void ISerializable.GetObjectData( SerializationInfo info, StreamingContext context )
    {
      _serializationMetrics = new List<Metrics>( _charSet.Count );
      foreach ( var p in _charSet )
        if ( p.Key is char )
        {
          var metric = p.Value as Metrics;
          _serializationMetrics.Add( metric );
          metric.Char = (char)p.Key;
        }
      SerializeHelpers.Pack( info, "_mainTexSolver", _mainTexSolver );
      SerializeHelpers.Pack( info, "_metrics", _serializationMetrics );
      SerializeHelpers.Pack( info, "_size", _size );
      SerializeHelpers.Pack( info, "_style", _style );
      SerializeHelpers.Pack( info, "_fontName", _font.name );
      SerializeHelpers.Pack( info, "_baseLine", _baseLine );
    }
    public FontStorage( SerializationInfo info, StreamingContext context )
    {
      SerializeHelpers.Unpack( info, "_mainTexSolver", out _mainTexSolver );
      SerializeHelpers.Unpack( info, "_metrics", out _serializationMetrics );
      SerializeHelpers.Unpack( info, "_baseLine", out _baseLine );
      SerializeHelpers.Unpack( info, "_size", out _size );
      SerializeHelpers.Unpack( info, "_style", out _style );
      SerializeHelpers.Unpack( info, "_fontName", out _serializationFontName );
    }

    [OnDeserialized]
    internal void OnDeserialized( StreamingContext context )
    {
      if ( string.IsNullOrEmpty( _serializationFontName )
        || string.Equals( _serializationFontName, DEFAULT_FONT_NAME ) )
        _font = DefaultFont;
      else
      {
        _font = Resources.Load( FlashEnv.FONTS_PATH + _serializationFontName ) as Font;
        if ( _font == null )
        {
          NivalCLI.CLI.DataAssert( "Unable to load font with name {0}. Default will be used.",
            _serializationFontName );
          _font = DefaultFont;
        }
      }

      foreach ( var m in _serializationMetrics )
        if ( !_charSet.ContainsKey( m.Char ) )
        {
          _charSet.Add( m.Char, m );
          m.Tex = _charTex;
        }
        else
          NivalCLI.CLI.Warning(
            "Duplicated char '{0}' defined twice in binary cache.", m.Char );

      if ( !_charDatabase.ContainsKey( _charTex ) )
        _charDatabase.Add( _charTex, _mainTexSolver );
      else
        _charDatabase[_charTex] = _mainTexSolver;
      InitStorage( _font, _size, _style, _charSet );
    }

    public static bool TryLoadFromCache( string path )
    {
      CLI.Info( "Loading cached FontStorage..." );
      var timeStart = Time.realtimeSinceStartup;
      var mem = GC.GetTotalMemory( false );
      _charTex = Resources.Load( path, typeof( Texture2D ) ) as Texture2D;
      if ( _charTex == null )
      {
        CLI.Info( "Loading cached FontStorage...Failed. Atlas not found." );
        return false;
      }

      var textAsset = Resources.Load( path, typeof( TextAsset ) ) as TextAsset;
      if ( textAsset != null )
      {
        LoadedFromCache = true;
        //_charTex = new Texture2D( atlas.width, atlas.height );
        //_charTex.SetPixels( atlas.GetPixels() );
        _globalStorage =
          (List<FontStorage>)
          new BinaryFormatter().Deserialize( new MemoryStream( textAsset.bytes ) );
        if ( _globalStorage != null )
        {
          CLI.Info( "Loading cached FontStorage...Ok, time: {0}sec, mem: {1}bytes",
            Time.realtimeSinceStartup - timeStart, GC.GetTotalMemory( false ) - mem );
          return true;
        }
      }
      LoadedFromCache = false;
      _charTex = null;
      CLI.Info( "Loading cached FontStorage...Failed. Bin data not loaded." );
      return false;
    }

    public static void CacheFontStorage( string path )
    {
      var filenameWoExtension = string.Format( "{0}{1}{2}{1}{3}", Application.dataPath,
        Path.DirectorySeparatorChar, "Resources", path );
      string filePath = filenameWoExtension + ".bytes";
      using ( FileStream outStream = new FileStream( filePath, FileMode.Create, FileAccess.Write ) )
      {
        BinaryFormatter formatter = new BinaryFormatter();

        formatter.Serialize( outStream, _globalStorage );
        outStream.Close();
      }

      if ( _charTex != null )
      {
        byte[] bytes = _charTex.EncodeToPNG();
        File.WriteAllBytes( filenameWoExtension + ".png", bytes );
      }
    }
    #endregion

    public static IFontStorage GetStorage( Font font, int size, FontStyle style )
    {
      #if SDFFONT
        return GetSDFStorage(font, size, style);
      #else
        return GetNativeStorage(font, size, style);
      #endif
    }

    private static IFontStorage GetNativeStorage(Font font, int size, FontStyle style)
    {
      foreach ( FontStorage fontStorage in _globalStorage )
      {
        if ( fontStorage._font == font && fontStorage._size == size && fontStorage._style == style )
          return fontStorage;
      }

      return new FontStorage( font, size, style );
    }

    private static IFontStorage GetSDFStorage(Font font, int size, FontStyle style)
    {
      var fontManager = SDFFonts.FontManager.Instance;
      Assert.IsTrue(fontManager != null);
      return fontManager.GetFontStorage(font.name, style, size);
    }

    private static void CreateMainGameObject()
    {
      if ( _mainFontStorageObject == null )
      {
        _mainFontStorageObject = new GameObject( FONT_STORAGE_GONAME );
        UnityEngine.Object.DontDestroyOnLoad( _mainFontStorageObject );
        if ( Application.isEditor )
          _debug = _mainFontStorageObject.AddComponent<FontStorageDebugViewer>();

        Font.textureRebuilt += OnFontTextureRebuilt;
      }
    }

    private static void InitGlobalFontSystem()
    {
      CreateMainGameObject();
      if ( !LoadedFromCache )
      {
        InitGlobalCharTexture();
        // Push Arial
        GetStorage( DefaultFont, 14, FontStyle.Normal );
      }
      //Handling after lost device fonts rerender
      if ( !_deviceObtainedSubscribed )
      {
        UniFlashPlayer.DeviceObtained += ResetGlobalFontSystem;
        _deviceObtainedSubscribed = true;
      }
    }

    private static void ResetGlobalFontSystem()
    {
      if ( _isTextureWasBroken )
      {
        CLI.Info( "ResetGlobalFontSystem, font texture was broken" );
        if ( !TryLoadFromCache( FlashEnv.FONTSTORAGE_CACHE_PATH ) )
        {
          LoadedFromCache = false;
          InitGlobalFontSystem();
        }
        _isTextureWasBroken = false;
        if ( FontTextureWasReseted != null )
          FontTextureWasReseted();
        if ( FontsDataWasReseted != null )
          FontsDataWasReseted();
      }
    }

    private static void InitGlobalCharTexture()
    {
      if ( _charDatabase.Count > 1 )
      {
        CLI.Warning( "FONT TEXTURE ASSERT : You use more than ONE font texture" );
      }

      if ( !Mathf.IsPowerOfTwo( DEFAULT_TEX_SIZE ) )
        throw new Exception( "Wrong texture size : non power of two" );

      if ( _charTex == null )
      {
        // texture
        _charTex = new Texture2D( DEFAULT_TEX_SIZE, DEFAULT_TEX_SIZE,
                                  TEXTURE_FORMAT, false );
        _charTex.name = DEFAULT_FONT_TEX_NAME;
        _charTex.filterMode = FilterMode.Point;
        _charTex.wrapMode = TextureWrapMode.Repeat;
        UnityEngine.Object.DontDestroyOnLoad( _charTex );
        if ( _debug != null )
          _debug._textures.Add( _charTex );

        // solver
        _mainTexSolver = new LayoutSolver();
        _charDatabase.Add( _charTex, _mainTexSolver );
      }

      Color[] pixels = new Color[DEFAULT_TEX_SIZE * DEFAULT_TEX_SIZE];
      for ( int i = 0; i < pixels.Length; ++i )
      {
        pixels[i].r = 0;
        pixels[i].g = 0;
        pixels[i].b = 0;
        pixels[i].a = 0;
      }
      _charTex.SetPixels( pixels );
      _charDatabase[_charTex].Clear();
    }

    private static void PutChar( Texture2D tempBuffer, Metrics metrics, bool setId )
    {
      LayoutSolver solver = _charDatabase[_charTex];
      int x = -1;
      int y = -1;
      if ( !solver.TryPutChar( tempBuffer, ref x, ref y, metrics ) )
        throw new PlaceCharacterException( "Can't find appropriate place for character" );


      Color[] colors = tempBuffer.GetPixels();
      if ( setId )
        for ( int i = 0; i < colors.Length; ++i )
        {
          colors[i].r = 1;
          colors[i].g = 1;
          colors[i].b = 1;
        }
      _id++;
      _charTex.SetPixels( x, y, tempBuffer.width, tempBuffer.height, colors );
      _charTex.Apply();

      metrics.Rect = new Rect( x, y, tempBuffer.width, tempBuffer.height );
      metrics.Tex = _charTex;
    }

    private void InitStorage( Font font, int size, FontStyle style, Dictionary<object, IFontMetrics> charSet )
    {
      // Font
      _font = font;
      if ( _font == null )
      {
        CLI.Warning( "Font is null, use Default font." );
        _font = DefaultFont;
      }
      if ( !_ttfDataMap.ContainsKey( _font ) )
      {
        string path = FlashEnv.FONTS_PATH + _font.name;
        TextAsset fontTextAsset = (TextAsset)Resources.Load( path, typeof( TextAsset ) );
        if ( fontTextAsset )
        {
          BinaryReader fontReader = new BinaryReader( new MemoryStream( fontTextAsset.bytes ) );
          _ttfData = new FontDataTTF( _font.name );
          _ttfData.ReadData( fontReader );
          fontReader.Close();
        }
        else
          CLI.Warning( "Cant find Font TextAsset '{0}'", path );

        _ttfDataMap.Add( _font, _ttfData );
      }
      else
      {
        _ttfData = _ttfDataMap[_font];
      }

      // ������ ������������ ����������� �������
      if ( FlashEnv.USE_ARIAL_KERNING )
        _ttfData = _ttfDataMap[_defaultFont];

      _size = size;
      _style = style;
      _globalStorage.Add( this );
      if ( charSet == null )
        ClearCharSet();
      else
        _charSet = charSet;

      if ( !LoadedFromCache )
      {
        _baseLine = GetBaseLine();
        FontStorage.FontTextureWasReseted += ClearCharSet;
      }
    }

    private FontStorage( Font font, int size, FontStyle style )
    {
      InitStorage( font, size, style, null );
    }

    private void ClearCharSet()
    {
      _charSet.Clear();
    }

    private static void OnFontTextureRebuilt(Font changedFont)
    {
      foreach (var storage in _globalStorage)
        if (storage._font == changedFont)
          storage._charSet.Clear();
      _isTextureWasBroken = true;
    }
    private int GetBaseLine()
    {
      if ( !_charSet.ContainsKey( DOT ) )
        SetChar( DOT );
      return _charSet[DOT].Floor;
    }

    public void TryGetMetric( char prev, char character, ref IFontMetrics metric )
    {
      _charSet.TryGetValue( character, out metric );

      //TODO: REFACTOR: Bad architecture here
      // Kern
      if ( _ttfData != null )
      {
        UInt32 pair = MathUtils.ConcatShort( prev, character );
        int kern;
        if ( !_pixKern.ContainsKey( pair ) )
        {
          float val = _ttfData.GetKern( prev, character ) * _size;
          kern = Mathf.RoundToInt( val );

          _pixKern.Add( pair, kern );
        }
        else
        {
          kern = _pixKern[pair];
        }

        if ( metric != null && kern != 0 )
          metric = (metric as Metrics).SetKert( kern );
      }
    }

    public void TryGetMetric( Texture2D character, ref IFontMetrics metric )
    {
      _charSet.TryGetValue( character, out metric );
    }

    public void SetString( string characters )
    {
      foreach ( char character in characters )
      {
        SetChar( character );
      }
    }

    public void SetTexture( Texture2D texture )
    {
      SetChar( texture );
    }

    private void SetChar( object character )
    {
      if ( _mainFontStorageObject == null )
      {
        // Font was not inited and was not loaded from cache. 
        // Init system and font texture.
        InitGlobalFontSystem();
      }

      IFontMetrics existMetric;
      if ( !_charSet.TryGetValue( character, out existMetric ) )
      {
        Texture2D tempBuffer = null;
        bool resampled = false;
        Metrics metrics = new Metrics();
          bool setId = true;

          if ( character is char )
          {
            tempBuffer = RenderChar( (char)character, metrics );
          }
          else if ( character is Texture2D )
          {
            tempBuffer = (Texture2D)character;
            setId = false;

            if ( FlashEnv.ADJUST_TEXTURES_TO_FONT_SIZE )
            {
              if ( tempBuffer.height > _size )
              {
                float aspect = (float)tempBuffer.height / _size;
                tempBuffer = TextureUtils.Resample( tempBuffer, Mathf.CeilToInt( tempBuffer.width / aspect ), _size );
                resampled = true;
              }
            }
          }

          if ( tempBuffer == null )
          {
            metrics.Tex = _charTex;
          }
          else
          {
            PutChar( tempBuffer, metrics, setId );
            metrics.Recalculate();
          }

          if ( metrics.Tex == null )
            throw new Exception( "Textute in Metric can't be NULL" );

          _charSet.Add( character, metrics );

        if ( character is char || ( character is Texture2D && resampled ) )
          Texture2D.DestroyImmediate( tempBuffer );
      }
    }
    private Texture2D RenderChar( char character, Metrics metrics )
    {
      _font.RequestCharactersInTexture( character.ToString(), _size, _style );

      CharacterInfo ci;
      if ( !_font.GetCharacterInfo( character, out ci, _size, _style ) )
        return null;

      var atlas = _font.material.mainTexture as Texture2D;
      if ( atlas == null )
        return null;

      int aw = atlas.width, ah = atlas.height;
      float uMin = Mathf.Min( ci.uvBottomLeft.x, ci.uvTopRight.x );
      float uMax = Mathf.Max( ci.uvBottomLeft.x, ci.uvTopRight.x );
      float vMin = Mathf.Min( ci.uvBottomLeft.y, ci.uvTopRight.y );
      float vMax = Mathf.Max( ci.uvBottomLeft.y, ci.uvTopRight.y );
      int px = Mathf.Clamp( Mathf.RoundToInt( uMin * aw ), 0, aw - 1 );
      int py = Mathf.Clamp( Mathf.RoundToInt( vMin * ah ), 0, ah - 1 );
      int gw = Mathf.Clamp( Mathf.RoundToInt( (uMax - uMin) * aw ), 1, aw - px );
      int gh = Mathf.Clamp( Mathf.RoundToInt( (vMax - vMin) * ah ), 1, ah - py );

      if ( character == '2' ) --gw;

      Color[] region;
      try
      {
        region = atlas.GetPixels( px, py, gw, gh );
      }
      catch
      {
        // atlas not readable — blit via RenderTexture
        var rt = RenderTexture.GetTemporary( aw, ah, 0, RenderTextureFormat.ARGB32 );
        Graphics.Blit( atlas, rt );
        RenderTexture.active = rt;
        var readable = new Texture2D( aw, ah, TextureFormat.ARGB32, false );
        readable.ReadPixels( new Rect( 0, 0, aw, ah ), 0, 0 );
        readable.Apply();
        RenderTexture.active = null;
        RenderTexture.ReleaseTemporary( rt );
        region = readable.GetPixels( px, py, gw, gh );
        Texture2D.DestroyImmediate( readable );
      }

      var glyph = new Texture2D( gw, gh, TextureFormat.ARGB32, false );
      glyph.SetPixels( region );
      glyph.Apply();

      metrics.LineHeight = gh;
      metrics.Floor = Mathf.Max( 0, -ci.minY );

      return glyph;
    }

    public static void SaveFontTexture(string path)
    {
      File.WriteAllBytes(path + ".png", _charTex.EncodeToPNG());
    }
  }
}


