using System.Collections.Generic;
using libdb.DB;
using libdb.UndoRedo;
using Render.DBRender;
using Render.DBRenderResources;
using System.ComponentModel;
using Foundation.DBSystem;
using Scene.DBScene;
using Terrain.DBTerrain;
using PF_Core.DBEffect;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_GameLogic.DBPFEffect
{
  [TypeId(0x9E67B282)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "NGameX::PFPlayAnimEffect", "PFPlayAnimEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class PlayAnimationEffect : EffectBase
  {
    [Description("Name of animation graph node to play")]
    public string animGraphNode;

    [Description("Time of reaching specified marker")]
    public float markerReachTime = 0.0f;

    [Description("Marker name")]
    public string marker;

    [Description("Should animation return to some node when effect is dropped")]
    public bool goToOtherNodeOnStop = false;

    [Description("Return anim graph node name")]
    public string returnAnimGraphNode;
  }

  [TypeId(0xA06CEC00)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "NGameX::PriestessSignEffect", "PFPriestessSignEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class PriestessSignEffect : BasicEffectStandalone
  {
    [Description("Effect of dead hero soul appearing")]
    public DBPtr<BasicEffectStandalone> soulEffect;

    [Description("Name of locator for soul sphere destination")]
    public string destinationLocator = string.Empty;

    [Description("Time delay from soul effect start to fly-in start")]
    public float flyInDelay = 0.0f;

    [Description("Trajectory of priestess flying in on dead hero body, curve from (0, 1, 1) to (0, 0, 0)")]
    public DBPtr<AnimatedPlacementResource> flyInPath;

    [Description("Name of animation of priestess flying in on dead hero body (only pose change, no real translation)")]
    public string flyInAnim = string.Empty;

    [Description("Name of animation of priestess flying out with dead hero soul")]
    public string flyOutAnim = string.Empty;
  }

  public enum EAuraType
  {
    Ally,
    Enemy,
  }

  [TypeId(0x9E71DC80)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "NGameX::PFAuraEffect", "PFAuraEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class AuraEffect : EffectBase
  {
    [Description("Тип ауры: дружественная или враждебная")]
    public EAuraType type = EAuraType.Enemy;
  }

  public enum EEffectSwitchLogic
  {
    FactionVisibility,
    SenderFaction,
  }

  [TypeId(0x9E71EC00)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "NGameX::PFEffectSwitcher", "PFEffectSwitcher.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class EffectSwitcher : EffectBase
  {
    [Description("Логика переключения между эффектами")]
    public EEffectSwitchLogic logic = EEffectSwitchLogic.FactionVisibility;

    [Description("FactionVisibility: Эффект для случая, когда фрацкия смотрящего равна фракции юнита, на которого наложен EffectSwitcher")]
    public DBPtr<EffectBase> effectOnVisible;

    [Description("FactionVisibility: Эффект для случая, когда фрацкия смотрящего отличается от фракции юнита, на которого наложен EffectSwitcher")]
    public DBPtr<EffectBase> effectOnInvisible;

    public bool isVisibleUnderWarfog = false;
  }

  public enum EUnitSceneObjectModifyMode
  {
    Append,
    ReplaceStatic,
    ReplaceAnimated,
  }

  public enum ESceneObjectVisibilityMode
  {
    AsObject,
    AsBuilding,
  }

  [TypeId(0x9E720B00)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "NGameX::PFUnitSceneObjectModify", "PFUnitSceneObjectModify.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class UnitSceneObjectModify : EffectBase
  {
    [Description("Механизм влияния на оригинальный Scene Object")]
    public EUnitSceneObjectModifyMode mode = EUnitSceneObjectModifyMode.Append;

    [Description("Модель видимости под туманов войны. AsObject - под туманом войны объект не видим, AsBuilding - виден")]
    public ESceneObjectVisibilityMode visibilityMode = ESceneObjectVisibilityMode.AsObject;

    [Description("Scene Object")]
    [EnumArray(typeof(ENatureType))]
    public List<DBPtr<DBSceneObject>> sceneObjects;
  }

  [TypeId(0xB753AC0)]
  [DBVersion(0)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "NGameX::PFEffectRandom", "PFEffectRandom.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class RandomEffect : EffectBase
  {
    [Description("Список эффектов для случайного выбора")]
    public List<DBPtr<EffectBase>> effects = new List<DBPtr<EffectBase>>();
  }

  [TypeId(0xB732380)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "NGameX::InvisibilityEffect", "PFInvisibilityEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class InvisibilityEffect : ScaleColorEffect
  {
  }

  public enum EMinimapEffects
  {
    EggCarrier,
    MarkerAlly,
    MarkerHostile,
    Chat,
  }

  [TypeId(0xE78B94C0)]
  [UseTypeName("EFFT")]
  [FactoryImpl( "Retrieve", "NGameX::PFMinimapEffect", "PFMinimapEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>" )]
  public class MinimapEffect : EffectBase
  {
    public EMinimapEffects effect = EMinimapEffects.EggCarrier;
  }

}
