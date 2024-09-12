using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using PF_GameLogic.DBUnit;
using Render.DBRenderResources;
using Render.DBRender;
using PF_GameLogic.DBAbility;

namespace PF_GameLogic.DBStats
{
  public enum EMinimapIcons
  {
    Default,
    MainBuildingA,
    MainBuildingB,
    ShopA,
    ShopB,
    ShopN,
    QuarterA,
    QuarterB,
    TowerA,
    TowerB,
    NeutralsWeak,
    NeutralsStrong,
    NeutralsBoss,
    Minigame,
    FountainA,
    FountainB,
    Flagpole,
    AltarA,
    AltarB,
    Egg,
    AlchemistCircle,
    Glyph,
    BridgePassable,
    BridgeImpassable,
    PushButton,
    None
  }

  [UseTypeName("MMAPIMG")]
  public class MinimapImages : DBResource
  {
    [Description("First (A) faction minimap image")]
    public DBPtr<TextureBase> firstMap;

    [Description("Second (B) faction minimap image")]
    public DBPtr<TextureBase> secondMap;

    [Description("Neutral minimap image")]
    public DBPtr<TextureBase> neutralMap;

    [Description("Center offset of the minimap (in meters)")]
    public Vec2 centerOffset = new Vec2(0.0f, 0.0f);

    [Description("Scale factor of the minimap (1.0 = no scale)")]
    public float scaleFactor = 1.0f;
  }

  [UseTypeName("MMAP")]
  [DBVersion(7)]
  public class DBMinimap : DBResource
  {
    [FieldCategory("Fade")]
    [Description("Normal opacity")]
    [FloatMinMax(0.0f, 1.0f)]
    public float normalOpacity = 1.0f;

    [FieldCategory("Fade")]
    [Description("Minigame opacity")]
    [FloatMinMax(0.0f, 1.0f)]
    public float minigameOpacity = 0.2f;

    [FieldCategory("Fade")]
    [Description("Transition time")]
    [FloatMin(0.0f)]
    public float transitionVelocity = 1.0f;

    [Description("Время жизни сигнала (пинга), в секундах")]
    [FloatMinMax(1.0f, 600.0f)]
    public float signalLifeTime = 5.0f;

    [Description("Цвет сигнала (пинга) по умолчанию")]
    public Color signalDefaultColor = new Color(0xFF, 0xFC, 0xC2, 0xFF);

    [Description("Color for enemy unit without icon")]
    public Color enemyColor;
    [Description("Color for ally unit without icon")]
    public Color allyColor;
    [Description("Color for neutral unit without icon")]
    public Color neutralColor;

    [Description("Enemy hero frame")]
    public DBPtr<Texture> enemyHeroFrame;

    [Description("Ally hero frame")]
    public DBPtr<Texture> allyHeroFrame;

    [Description("Local hero frame")]
    public DBPtr<Texture> localHeroFrame;

    [Description("List of standard minimap icons")]
    [EnumArray(typeof(EMinimapIcons))]
    public List<DBPtr<Texture>> icons = new List<DBPtr<Texture>>();

    [Description("Target zone line color")]
    public Color targetZoneColor = new Color(0xFF, 0xFF, 0xFF, 0xFF);

    [Description("Target zone line thickness")]
    public int targetZoneLineThickness = 2;
  }

}