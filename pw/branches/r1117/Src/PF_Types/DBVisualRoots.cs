//#include "DBUnit.cs"
//#include "DBStats.cs"
//#include "DBCameraSettings.cs"

using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_Core.DBEffect;
using PF_GameLogic.DBAnimations;
using PF_GameLogic.DBGameLogic;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBUnit;

namespace PF_GameLogic.DBVisualRoots
{
  [UseTypeName( "ROOT" )]
  public class SessionUIRoot : DBResource
  {
    public DBPtr<UnitCategories>       unitCategories;
    public DBPtr<UnitCategoriesParams> unitCategoriesParams;
  }

  public enum EAnimSetID
  {
    Creep,
    Hero,
    Priestess,
    SittingPriestess,
    Critter,
  }

  public class AnimSets
  {
    [EnumArray( typeof( EAnimSetID ) )]
    public List<DBPtr<AnimSet>> sets;
  }

  public enum EAuraEffectType
  {
    Ally,
    Enemy,
    Mixed,
  }

  public class AuraEffects
  {
    [Description( "Минимальная интенсивность ауры" )]
    public float minimalEffectIntencity = 0.5f;

    [Description( "Количество аур, на котором достигается интенсивность 1" )]
    public int maximalAuraCount = 3;

    [Description( "Эффекты для трех различных типов аур" )]
    [EnumArray( typeof( EAuraEffectType ) )]
    public List<DBPtr<BasicEffectAttached>> auraEffects;
  }

  public enum EWinLose
  {
    Win,
    Lose
  }

  public class WinLoseEffect
  {
    [Description("Время движения камеры к зданию (сек)")]
    public float cameraMovementTime = 3;

    [Description("Позиция камеры относительно здания. Можно использовать поле anchor для горизонтального смещения")]
    public Scene.DBSceneBase.ViewCamera cameraPos;

    [Description("Задержка перед стартом эффекта (сек)")]
    public float effectDelay = 3;

    [Description("Сам эффект")]
    public DBPtr<PF_Core.DBEffect.BasicEffectStandalone> effect;
  }

  public class EffectWithDelay
  {
    [Description("Задержка перед запуском")]
    public float deltaTime;

    [Description("Описание эффекта")]
    public DBPtr<EffectBase> effect;
  }

  public enum EFemaleMaleAssistEffectSate
  {
    HeroToMiddle,
    MiddleToHero,
    SingleAtMidle,
    StartFlash,
    Destroy
  }

  public class FemaleMaleAssistEffect
  {
    [Description("Минимальная дистанция между героями для срабатывании эффекта")]
    public float minDistanceBetweenHeroes = 23;

    [Description("Высота, относительно террейна, на которую будет смещён центр эффекта")]
    public float middlePosHeight = 4;

    [Description("Воспроизводимые эффекты и относительная задержка перед из стартом")]
    [EnumArray(typeof(EFemaleMaleAssistEffectSate))]
    public List<EffectWithDelay> effectsWithDelay;
  }

  [UseTypeName( "ROOT" )]
  [DBVersion( 1 )]
  public class SessionVisualRoot : DBResource
  {
    public DBPtr<EmoteSettings> emoteSettings;
    public DBPtr<TeamsColoringScheme> teamColoringScheme;
    public DBPtr<EffectsPool> effects;

    [EnumArray( typeof( EAuraEffectType ) )]
    public List<DBPtr<BasicEffectAttached>> selfAuraEffects;

    public AnimSets animSets;

    public AuraEffects auraEffects;

    public DBPtr<UIEventsCustom> uiEvents;

    public List<DBPtr<AdventureCameraSettings>> cameras;

    [Description("Эффекты и перемещения камеры после победы/поражения")]
    [EnumArray( typeof( EWinLose ) )]
    public List<WinLoseEffect> winLoseEffects;

    [Description("Эффект при совместных гетеросексуальных убийствах и разрушениях")]
    public FemaleMaleAssistEffect femaleMaleAssistEffect;

    [Description("Ширина таргетзоны типа Стена")]
    public float wallTargetZoneWidth = 1.0f;
  }

  [UseTypeName( "ROOT" )]
  public class SessionAudioRoot : DBResource
  {
  }
}