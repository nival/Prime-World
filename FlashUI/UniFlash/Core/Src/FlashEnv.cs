namespace Flash
{
  public static class FlashEnv
  {
    /// <summary>
    /// Paths
    /// </summary>
    public const string FONTS_PATH = "Fonts/";
    public const string FONTSTORAGE_CACHE_PATH = "FlashUI/fontStorage.bin";
    public const string PATH_TO_XML_TREES = "../../FlashUI/";
    public const string PATH_TO_FLASH_FRAMEWORK = "Components/FlashFramework/";
    public const string CACHE_DIR_NAME = "SwfCache";

    /// <summary>
    /// Atlasing
    /// </summary>
    public const bool CACHE_ENABLED = true;
    public const string ATLAS_CACHE_NAME = "atlascache";
    public const string ATLAS_RECT_CACHE_NAME = "atlasdata.atlas";
    public const string NODE_NAME = "rect";
    public const string ID_NAME = "id";
    public const string RESOURCES_PATH_NAME = "p";
    public const string WIDTH_NAME = "tw";
    public const string HEIGHT_NAME = "th";
    public const string X_NAME = "x";
    public const string Y_NAME = "y";
    public const string W_NAME = "w";
    public const string H_NAME = "h";

    public const string ATLAS_DATA_POSTFIX = "data";
    public const string ATLASES_FOLDER = "Atlases/";
    public const string UI_ICONS_ATLAS = "icons";

    /// <summary>
    /// Bitmap ScaleGrid
    /// </summary>
    public const bool CLIPPED_SCALE_GRID_ENABLED = true;

    /// <summary>
    /// Shape vertex type
    /// </summary>
    public const int FILL_BITMAP = 0;
    public const int LINE_BITMAP = 1;
    public const int FILL_RADIAL_GRADIENT = 2;
    public const int LINE_RADIAL_GRADIENT = 3;
    public const int SOLID = 4;
    public const int LINE_LINEAR_GRADIENT = 5;
    public const int FILL_LINEAR_GRADIENT = 6;

    /// <summary>
    /// Shape Generation
    /// </summary>
    public const int SEGMENTS_PER_CURVE = 7;
    public const float FLASH_GRADIENT_RES_IN_PIX = 1636.4F;
    public const float VERTEX_ADJ_BIAS = 0.00001F;

    /// <summary>
    /// Textures
    /// </summary>
    public const string GRADIENT_NAME = "<gradient>";
    public const bool ADJUST_TEXTURES_TO_FONT_SIZE = true;

    /// <summary>
    /// Networking
    /// </summary>
    public const int MAX_WWW_REQUEST_COUNT = 5;

    public const bool USE_ARIAL_KERNING = true;
  }
}