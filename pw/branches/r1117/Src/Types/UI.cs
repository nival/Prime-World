//#include "Preferences.cs"
//#include "RenderResources.cs"
//#include "Sound.cs"
//#include "VotingForSurrender.cs"

using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using Render.DBRender;
using Render.DBRenderResources;
using Sound.DBSound;
using UI.DBPreferences;
using UI.DBVotingForSurrender;

namespace UI.DBUI
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI Texture : extends Texture to support bit-mask shapes
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  [UseTypeName("ITEX")]
  [FactoryImpl("Load", "Render::Texture2D", "../Render/TextureManager.h", CreateFunction = "(Render::Texture *)Render::LoadTexture2D")]
  [FactoryImpl("LoadInPool", "Render::Texture2D", "../Render/TextureManager.h", CreateFunction = "(Render::Texture *)Render::LoadTexture2DIntoPool")]
  public class UITexture : Texture
  {
    public bool importOnlyShape = false;
    public int shapeAlphaThreshold = 0;

    [DstFile("shp")]
    public string shapeFileName = string.Empty;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI FontStyle
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  [UseTypeName("IFNT")]
  [IndexField("styleName")]
  [DBVersion(1)]
  [Custom("Social")]
  public class UIFontStyle : DBResource
  {
    public string styleName;

    public bool drawContour;
    public HDRColor primaryColor = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
    public HDRColor secondaryColor = new HDRColor(0.0f, 0.0f, 0.0f, 1.0f);
    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.Off, 127, OnOffState.Off);

    [FileRef("*.ttf;*.pfb")]
    public string ttfFileName = string.Empty;
    [FieldCategory("Text")]
    public string fontFamily = string.Empty;

    public int fontSize = 0;
    public int lineGap = 0;

    [Description("Additional horizontal advance between letters ")]
    public float additionalAdvance = 0.0f;

    [Description("Relative size of white-space char; Used to tweak font render")]
    public float spaceScale = 1.0f;

    public bool bold = false;
    public bool italic = false;
    [NoCode, Custom("Social")]
    public bool disableImageScaling = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI Layout
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  public enum EUIElementHAlign
  {
    Left,
    Right,
    Center,
    FixedMargins,
    Proportional
  };

  public enum EUIElementVAlign
  {
    Top,
    Bottom,
    Center,
    FixedMargins,
    Proportional,
  };

  public enum EUIElementAspectRatio
  {
    DontCare,
    WidthBased,
    HeightBased
  };

  [NeedEqualOperator]
  [NeedAssignOperator]
  [IndexField("id")]
  public class UIRelatedLayout
  {
    public string id = string.Empty;
    public DBPtr<UILayout> layout;
  }

  [NeedEqualOperator]
  [NeedAssignOperator]
  [IndexField("id")]
  public class UIRelatedText
  {
    public string id = string.Empty;
    public TextRef relatedText = new TextRef();
    public string comment = string.Empty;
  }

  [NeedEqualOperator]
  [NeedAssignOperator]
  public class UICursors
  {
    public string normal = "ui_normal";
    public string dragging = "ui_dragging";
    public string dragable = "ui_dragable";
    public string focused = "ui_focused";
    public string disabled = "ui_disabled";
    public string pushing = "ui_pushing";
    public string pushable = "ui_pushable";
  }

  [NeedEqualOperator]
  [NeedAssignOperator]
  public class UICatchEvents
  {
    public bool mouseMove = true;
    public bool leftMouseDown = true;
    public bool rightMouseDown = true;
    public bool leftMouseUp = true;
    public bool rightMouseUp = true;
    public bool leftDoubleClick = true;
    public bool rightDoubleClick = true;
  }

  [NeedEqualOperator]
  [NeedAssignOperator]
  [HasStates]
  [IndexField("name")]
  public class UILayout : DBResource
  {
    public string name = string.Empty;
    public bool visible = true;
    public bool enabled = true;

    public FloatPoint location = new FloatPoint(0, 0);
    public FloatPoint size = new FloatPoint(1280, 1024);
    public EUIElementHAlign hAlign = EUIElementHAlign.Left;
    public EUIElementVAlign vAlign = EUIElementVAlign.Top;
    public EUIElementAspectRatio keepAspectRatio = EUIElementAspectRatio.DontCare;

    public string subclass = string.Empty;

    [FileRef("*.lua")]
    public string scriptFile = string.Empty;

    public UICursors cursors;

    public List<DBPtr<UILayout>> subLayouts;

    public bool draggable = false;

    public UICatchEvents defaultEventsCatch = new UICatchEvents();
    public bool transparent = false;
    public bool cursorTransparent = false;

    public bool needCrop = false;

    public List<UIRelatedLayout> relatedLayouts;

    public List<UIRelatedText> relatedTexts;

    public TextRef tooltipText = new TextRef();

    [Description("Sound event that will be started when window becomes visible")]
    public DBFMODEventDesc soundShow;

    [Description("Sound event that will be started when window becomes invisible")]
    public DBFMODEventDesc soundHide;

    [Description("Sound event that will be started on activation")]
    public DBFMODEventDesc soundActivate;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI Base
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  [ToolBoxItem("General", "Base", "Layout")]
  public class UIBaseLayout : UILayout
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI ImageLabel
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  public enum EImageLabelShapeType
  {
    Empty,
    SimpleBox,
    FromShapeStyle,
    FromBackgroundStyle,
    FromShapeOrBackgroundStyle,
    ByText,
  }

  public enum EUITextVAlign
  {
    Top,
    Center,
    Bottom
  };

  public enum EUITextHAlign
  {
    Right,
    Center,
    Left
  };

  [UseTypeName("IMGLBL")]
  [ToolBoxItem("General", "Image Label", "Layout")]
  public class UIImageLabelLayout : UILayout
  {
    public DBPtr<BaseUIMaterial> backgroundMaterial;

    [FieldCategory("Shape")]
    public EImageLabelShapeType shapeType = EImageLabelShapeType.FromShapeOrBackgroundStyle;

    [FieldCategory("Text")]
    public TextRef captionText = new TextRef();

    [FieldCategory("Text")]
    public string fontStyle = string.Empty;

    [Description("Words in text will wrap around right margin")]
    public bool wordWrap = true;

    [Description("Text will stretch to given width, if possible")]
    public bool stretchText = false;

    [Description("Disable text formating tags etc")]
    public bool rawTextMode = false;

    [FieldCategory("Text")]
    public EUITextVAlign textVAlign = EUITextVAlign.Center;
    [FieldCategory("Text")]
    public EUITextHAlign textHAlign = EUITextHAlign.Center;

    [FieldCategory("Text")]
    public FloatRect textMargins = new FloatRect();

    [FieldCategory("Text")]
    public float captionOpacity = 1.0f;
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI Common interactive control
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  public enum EUIControlMouseActions
  {
    Left,
    Right,
    Both
  };

  [UseTypeName("CTRL")]
  public class UICommonControl : UIImageLabelLayout
  {
    public EUIControlMouseActions mouseActions = EUIControlMouseActions.Left;

    [Description("Sound event that will be started on mouse over")]
    public DBFMODEventDesc soundHilite;

    [Description("Input bind identifier thaat will activate this control")]
    public string activationBind;

    //TODO: move active, hilited and disabled materials here
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI Button
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  public enum EUIButtonViewMode
  {
    ByMaterials,
    ByPins,
    ByPinsWithoutDisablePin
    //Some buttons have multiple visual 'Disabled' states: level is not enough OR no mana OR no gold etc
    //So let the external code setup disabled state manually
  };

  [UseTypeName("BTN")]
  [ToolBoxItem("Controls", "Button", "Button")]
  public class UIButtonLayout : UICommonControl
  {
    public DBPtr<BaseUIMaterial> highlightMaterial;
    public DBPtr<BaseUIMaterial> pushedMaterial;
    public DBPtr<BaseUIMaterial> disabledMaterial;
    public DBPtr<BaseUIMaterial> flashedMaterial;

    [Description("Use background material advanced pins or multiple materials")]
    public EUIButtonViewMode viewMode = EUIButtonViewMode.ByMaterials;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI CheckBox
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  [UseTypeName("CheckBox")]
  [ToolBoxItem("Controls", "Check Box", "Button")]
  public class UICheckBoxLayout : UICommonControl
  {
    [LuaProperty]
    public DBPtr<BaseUIMaterial> highlightMaterial;

    [LuaProperty]
    public DBPtr<BaseUIMaterial> checkedMaterial;

    [LuaProperty]
    public DBPtr<BaseUIMaterial> highlightCheckedMaterial;

    [LuaProperty]
    public DBPtr<BaseUIMaterial> disabledMaterial;

    [LuaProperty]
    public DBPtr<BaseUIMaterial> disabledCheckedMaterial;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI RadioButton and RadioPanel
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  [NeedEqualOperator]
  public class UIPageTabElement
  {
    public DBPtr<UIRadioButtonLayout> button;
    public DBPtr<UIImageLabelLayout> page;
  }

  [ToolBoxItem("Containers", "PageTabControl", "Layout")]
  public class UIPageTabControlLayout : UIImageLabelLayout
  {
    [Category("Layout")]
    public List<UIPageTabElement> tabs;
  }

  [ToolBoxItem("Containers", "Radio Panel", "Layout")]
  public class UIRadioPanelLayout : UIImageLabelLayout
  {
  }

  [ToolBoxItem("Controls", "Radio Button", "Button")]
  public class UIRadioButtonLayout : UICommonControl
  {
    [LuaProperty]
    public DBPtr<BaseUIMaterial> highlightMaterial;

    [LuaProperty]
    public DBPtr<BaseUIMaterial> selectedMaterial;

    [LuaProperty]
    public DBPtr<BaseUIMaterial> disabledMaterial;

    [LuaProperty]
    public DBPtr<BaseUIMaterial> disabledSelectedMaterial;

    [LuaProperty]
    public DBPtr<BaseUIMaterial> flashedMaterial;

    [LuaProperty]
    public int group = 0;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI EditBox
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  public enum EUITextEntryType
  {
    Free,
    Console,
    Numeric,
    Identifier,
    PlayerName,
  };

  [UseTypeName("EditBox")]
  [ToolBoxItem("Controls", "Edit Box", "Layout")]
  public class UIEditBoxLayout : UIImageLabelLayout
  {
    [LuaProperty]
    public DBPtr<BaseUIMaterial> disabledMaterial;

    [LuaProperty]
    public DBPtr<BaseUIMaterial> cursorMaterial;

    [FieldCategory("Text")]
    [LuaProperty]
    public int maxLength = 65535;

    [Category("Text")]
    [LuaProperty]
    public bool isPassword = false;

    [FieldCategory("Text")]
    [LuaProperty]
    public int maxLines = 1;

    [FieldCategory("Text")]
    [LuaProperty]
    public EUITextEntryType textEntryType = EUITextEntryType.Free;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI View
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  [UseTypeName("View")]
  [ToolBoxItem("General", "View", "View")]
  public class UIViewLayout : UILayout
  {
    [FieldCategory("View")]
    public string provider = string.Empty;

    [FieldCategory("View")]
    public string address = string.Empty;

    [FieldCategory("Image")]
    public int framesPerSecond = 15;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI ProgressBar
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  public enum EUIProgressBarType
  {
    HorizontalScalingBar,
    TextureMaskedProgress,
  };
  public enum EUIRotationType
  {
    CW,
    CCW,
  };

  [UseTypeName("Progress")]
  [ToolBoxItem("Indicators", "Progress Bar", "View")]
  public class UIProgressBarLayout : UIImageLabelLayout
  {
    public DBPtr<BaseUIMaterial> progressMaterial;

    public DBPtr<BaseUIMaterial> rotationEffectMaterial;

    [FieldCategory("Image")]
    public FloatPoint rotationEffectPivot = new FloatPoint(-1, -1);
    [FieldCategory("Image")]
    public EUIRotationType effectRotationType = EUIRotationType.CW;

    [FieldCategory("Image")]
    public EUIProgressBarType progressBarType = EUIProgressBarType.HorizontalScalingBar;

    [FieldCategory("Image")]
    public int maskGradientItems = 1;
  };

  [UseTypeName("HealthBar")]
  [ToolBoxItem("Indicators", "Health Bar", "View")]
  public class UIHealthBarLayout : UIImageLabelLayout
  {
    public DBPtr<BaseUIMaterial> healthMaterial;
    public DBPtr<BaseUIMaterial> shieldMaterial;

    public bool showShield = false;
    public bool showStripes = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI ScrollArea
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  [NeedEqualOperator]
  public class UIScrollLimits
  {
    public float inMin = 0.0f;
    public float inMax = 1.0f;
    public int outMin = 0;
    public int outMax = 0;
  }

  [ToolBoxItem("Containers", "Scroll Area", "Layout")]
  public class UIScrollAreaLayout : UILayout
  {
    [FieldCategory("Script")]
    public string handleMsgForXScroll = string.Empty;
    [FieldCategory("Script")]
    public string handleMsgForYScroll = string.Empty;

    [FieldCategory("Script")]
    public UIScrollLimits scrollXLimits;
    [FieldCategory("Script")]
    public UIScrollLimits scrollYLimits;

    [FieldCategory("Script")]
    public string spawnMsgOnLimitsChanged = string.Empty;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI ScrollList : extends ScrollArea
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  public enum EUIListItemsPlacingOrigin
  {
    LeftTop,
    RightTop,
    LeftBottom,
    RightBottom,
  }

  public enum EUIListItemsPlacingOrder
  {
    ByRows,
    ByColumns,
    ByRowsOfColumns,
    ByColumnsOfRows,
  }

  [ToolBoxItem("Containers", "Scroll List", "Layout")]
  public class UIScrollListLayout : UIScrollAreaLayout
  {
    [FieldCategory("List Items")]
    public EUIListItemsPlacingOrigin placingOrigin = EUIListItemsPlacingOrigin.LeftTop;
    [FieldCategory("List Items")]
    public EUIListItemsPlacingOrder placingOrder = EUIListItemsPlacingOrder.ByRows;
    [FieldCategory("List Items")]
    public FloatPoint minItemSize;
    [FieldCategory("List Items")]
    public FloatPoint maxItemSize;
    [FieldCategory("List Items")]
    public int maxItemsTotal = 0; // 0 = unlimited
    [FieldCategory("List Items")]
    public int maxStrideItems = 0; // 0 = auto by size

    public DBPtr<BaseUIMaterial> hilightMaterial;
    public DBPtr<BaseUIMaterial> preselectMaterial;
    public DBPtr<BaseUIMaterial> selectionMaterial;

    [FieldCategory("Script")]
    public string spawnMsgOnItemHighlighted = string.Empty;
    [FieldCategory("Script")]
    public string spawnMsgOnItemSelected = string.Empty;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI ScrollBar
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  public enum EUIScrollBarType
  {
    Vertical,
    Horizontal,
  }
  public enum EUIDiscreteType
  {
    None,
    Fixed, // uses discretePositionsCount field
    RelativeToItemsCount,
  }

  [ToolBoxItem("Controls", "Scroll Window", "Layout")]
  public class UIScrollableWindowLayout : UILayout
  {
    [Category("General")]
    public DBPtr<UIScrollAreaLayout> scrollArea = null;
    [Category("General")]
    public DBPtr<UIScrollBarLayout> scrollBar = null;
  }

  public enum EUIScrollBarElementStyle
  {
    Normal,
    Hilited,
    Pressed,
    Disabled
  }

  [ToolBoxItem("Controls", "Scroll Bar", "Layout")]
  public class UIScrollBarLayout : UILayout
  {
    public EUIScrollBarType scrollBarType = EUIScrollBarType.Vertical;
    public int discretePositionsCount = 0; // 0 = non-discrete
    public EUIDiscreteType discreteType = EUIDiscreteType.None;

    public string spawnMsgOnScrolled = string.Empty;

    public DBPtr<BaseUIMaterial> leverAreaMaterial;
    public DBPtr<BaseUIMaterial> leverAreaDisabledMaterial;

    [EnumArray(typeof(EUIScrollBarElementStyle))]
    public List<DBPtr<BaseUIMaterial>> leverMaterials = new List<DBPtr<BaseUIMaterial>>();

    [EnumArray(typeof(EUIScrollBarElementStyle))]
    public List<DBPtr<BaseUIMaterial>> firstButtonMaterials = new List<DBPtr<BaseUIMaterial>>();

    [EnumArray(typeof(EUIScrollBarElementStyle))]
    public List<DBPtr<BaseUIMaterial>> secondButtonMaterials = new List<DBPtr<BaseUIMaterial>>();

    public int leverSize = 0; // 0 = auto
    public int firstButtonSize = 0; // 0 = auto
    public int secondButtonSize = 0; // 0 = auto
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI Flash
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  [NeedEqualOperator]
  [IndexField("propertyName", true)]
  public class UIFlashProperties
  {
    public string propertyName = string.Empty;
    public TextRef propertyValue = new TextRef();
  }

  [ToolBoxItem("Controls", "Flash", "Layout")]
  public class UIFlashLayout : UILayout
  {
    [SwfFileRef("*.swf")]
    public string srcFileName = string.Empty;
    public bool useScissorTest = false;
    [Description("Use size from SWF file")]
    public bool useOwnSize = false;
    [Description("Triangulation pixel error")]
    public float triangulationError = 1.0f;
    [Description("Public properties of flash control")]
    [FixedList]
    public List<UIFlashProperties> properties = new List<UIFlashProperties>();
  }

  [ToolBoxItem("Controls", "Flash2", "Layout")]
  public class UIFlashLayout2 : UIFlashLayout
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // other UI Resources
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  public class UICursorBase : DBResource
  {
  }

  [UseTypeName("ICUR")]
  [DBVersion(0)]
  public class UICursor : UICursorBase
  {
    public DBPtr<Texture> texture;
    public int hotSpotX = 0;
    public int hotSpotY = 0;
  }

  [UseTypeName("ACUR")]
  [DBVersion(1)]
  public class UIAnimatedCursor : UICursorBase
  {
    [SrcFile("Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff")]
    [Description("»м€ файла первого кадра секвенции, должно содержать на конце номер (обычно 01 или вроде того).")]
    public string srcFileName = string.Empty;

    [DstFile("ani")]
    [Description("»м€ файла дл€ сымпортированного курсора, генерируетс€ автоматически.")]
    public string dstFileName = string.Empty;

    [IntMin(1)]
    [Description(" оличество кадров в секвенции, каждый кадр беретс€ из отдельного файла по пор€дку номеров.")]
    public int frameCount = 1;

    [IntMinMax(1, 60)]
    [Description("ѕримерна€ скорость проигрывани€ анимации в кадрах в секунду, от 1 до 60.")]
    public int fps = 10;

    [FloatMin(0.0f)]
    [Description("ѕримерна€ задержка (длительность первого кадра) перед зацикливанием последовательности.")]
    public float delay = 0.0f;

    [Description("X-координата хотспота, ноль - слева.")]
    public int hotSpotX = 0;

    [Description("Y-координата хотспота, ноль - сверху.")]
    public int hotSpotY = 0;
  }

  /////////////////////////
  // Overtips
  /////////////////////////

  public enum EUIOvertipBindPoint
  {
    None,
    Center,
    LeftTop,
    CenterTop,
    RightTop,
    LeftCenter,
    RightCenter,
    LeftBottom,
    CenterBottom,
    RightBottom
  }

  public class UIPlainOvertipDesc
  {
    public EUIOvertipBindPoint bindPoint = EUIOvertipBindPoint.Center;
    public DBPtr<UILayout> layout;
    public bool useDepth = false;
    public float depthBias = 0;
    public FloatPoint offset = new FloatPoint(0, 0);
  }

  public enum EUI3DOvertipMode
  {
    World,
    Billboard,
    AxisBillboard
  }

  public class UI3DOvertipDesc
  {
    public DBPtr<UILayout> layout;
    public EUI3DOvertipMode mode = EUI3DOvertipMode.World;
    public Vec2 worldSize = new Vec2(1.0f, 1.0f);
    public Vec2 align = new Vec2(0.5f, 0.5f);
    public float depthBias = 0;
  }

  public class UIObjectOvertips : DBResource
  {
    public List<UIPlainOvertipDesc> plain = new List<UIPlainOvertipDesc>();
    public List<UI3DOvertipDesc> threeDimensional = new List<UI3DOvertipDesc>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // UI Root
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //

  [IndexField("screenId")]
  public class UIScreenDesc
  {
    public string screenId = string.Empty;
    public DBPtr<UIBaseLayout> baseLayout;
    public string comment = string.Empty;
  }

  public class UICursorDesc
  {
    public string cursorId = string.Empty;
    public DBPtr<UICursorBase> cursor;
    public DBPtr<UICursorBase> cursorOverlay;
    public IntPoint cursorOverlayOffset = new IntPoint();
  }

  public class UIScriptDesc
  {
    public string scriptFile = string.Empty;
  }

  public class UISoundDesc
  {
  }

  // base class for custom content resources
  //TODO: kill as soon as possible
  public class UIContentResource : DBResource
  {
    public string contentId = string.Empty;
  }

  public class UIContentGroup
  {
    public string groupId = string.Empty;
    public List<DBPtr<UIContentResource>> resources;
    public string comment = string.Empty;
  }

  public class UIConstant
  {
    public string name = string.Empty;
    public string value = string.Empty;
    public string comment = string.Empty;
  }

  [IndexField("name")]
  [Custom("Social")]
  public class UIStyleAlias
  {
    public string name = string.Empty;
    public DBPtr<BaseUIMaterial> material;
  }

  [IndexField("id")]
  [Custom( "Social" )]
  public class UITextSubstitute
  {
    public string id = string.Empty;
    public TextRef captionText = new TextRef();
  }

  public class UIHealthStripes
  {
    public float stripe1Step = 100;
    public float stripe2Step = 1000;
    public HDRColor allyColor100 = new HDRColor(0.0f, 0.0f, 0.0f, 1.0f);
    public HDRColor enemyColor100 = new HDRColor(0.0f, 0.0f, 0.0f, 1.0f);
    public HDRColor allyColor1000 = new HDRColor(1.0f, 0.68f, 0.19f, 1.0f);
    public HDRColor enemyColor1000 = new HDRColor(1.0f, 0.68f, 0.19f, 1.0f);
  }

  [DBVersion(2)]

  public class UIRoot : DBResource
  {
    public List<UIScreenDesc> screens = new List<UIScreenDesc>();
    public List<UICursorDesc> cursors = new List<UICursorDesc>();
    public List<UIScriptDesc> scripts = new List<UIScriptDesc>();
    public List<UIContentGroup> contents = new List<UIContentGroup>();
    public List<UIConstant> consts = new List<UIConstant>();
    [Custom( "Social" )]
    public List<UITextSubstitute> substitutes = new List<UITextSubstitute>();
    [Custom( "Social" )]
    public List<UIStyleAlias> styleAliases = new List<UIStyleAlias>();
    [Custom( "Social" )]
    public List<DBPtr<UIFontStyle>> fontStyles = new List<DBPtr<UIFontStyle>>();
    public DBPtr<Preferences> preferences;
    public DBPtr<VotingForSurrender> votingForSurrender;
    public UIHealthStripes healthStripes;
  }
}

