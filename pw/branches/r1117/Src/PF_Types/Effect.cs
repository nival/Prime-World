
//#include "../Types/Terrain.cs"
//#include "../Types/Scene2.cs"
//#include "DBExecString.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using Render.DBRender;
using Render.DBRenderResources;
using Scene.DBScene;
using Terrain.DBTerrain;
using PF_GameLogic.DBAbility;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Core.DBEffect
{
  [UseTypeName("TXRC")]
  [FactoryImpl("Load", "PF_Core::RecolorableTexture", "RecolorableTexture.h", CreateFunction = "PF_Core::LoadRecolorableTexture")]
  [FactoryImpl("LoadInPool", "PF_Core::RecolorableTexture", "RecolorableTexture.h", CreateFunction = "PF_Core::LoadRecolorableTextureInPool")]
  [DBVersion(1)]
  public class TextureRecolorable : TextureBase
  {
    public DBPtr<Texture> main;
    public DBPtr<Texture> mask;

    [Description("Color that is applied by default (no recolor by default when A=0)")]
    public HDRColor baseRGB = new HDRColor(0.0f, 0.0f, 0.0f, 0.0f);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [UseTypeName("TXAN")]
  [FactoryImpl("Load", "PF_Core::AnimatedTexture", "AnimatedTexture.h", CreateFunction = "PF_Core::LoadAnimatedTexture")]
  [FactoryImpl("LoadInPool", "PF_Core::AnimatedTexture", "AnimatedTexture.h", CreateFunction = "PF_Core::LoadAnimatedTextureIntoPool")]
  public class TextureAnimated : Texture
  {
    public int animCount = 1;
    public float animSpeed = 10.0f;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  public enum EEffects
  {
    Empty = 0,
    LevelUp,
    ClickOnTerrain,
    OnDamageFragTeamA,
    OnDamageFragTeamB,
    OnBuildingDestructTeamA,
    OnBuildingDestructTeamB,
    ControlledHeroAura,

    // todo: below refactoring is required, seems to be duplication [3/18/2011 paul.smirnov]

    SelectionAuraSelf,
    SelectionAuraAlly,
    SelectionAuraHostile,

    PreSelectionAuraSelf,
    PreSelectionAuraAlly,
    PreSelectionAuraHostile,

    SelectionPickSelf,
    SelectionPickAlly,
    SelectionPickHostile,

    SelectionBuildingPickSelf,
    SelectionBuildingPickAlly,
    SelectionBuildingPickHostile,

    MarkerAlly,
    MarkerHostile,
    MarkerChat,

    DefaultEffect,
    GlowEffectA,
    GlowEffectB,

    RotateAnimationEffect,

    MinigameScrollGiven,

    TowerAttackEffectAlly,
    TowerAttackEffectEnemy,
  }

  public enum EEffectAttachType
  {
    General = 0,
    Above,
    Ground,
    Body,
    Death,
    Head,
  }

  public enum EEffectDeathType
  {
    Manual = 0,
    Anim,
    Time,
  }

  public enum EEffectEvent
  {
    Attack = 0,
    Death,
    Stop,
  }

  [Flags]
  public enum EEffectGroupFlags
  {
    None = 0,
    IgnoreColorModification = (1 << 20),
    IgnoreInvisibility = (1 << 21),
  }

	[TypeId(0xA06253C0)]
  [UseTypeName("EFFT")]
	[FactoryBase("Retrieve", "PF_Core::BasicEffect", "PF_Core::ObjectsPool &pool", ReturnType = "CObj<PF_Core::BasicEffect>", Define = "!VISUAL_CUTTED")]
  [HasStates]
	public class EffectBase : DBResource
  {
    public EEffectDeathType deathType = EEffectDeathType.Manual;
    public float lifeTime = 0.0f;

    [Description("Формула для активации эффекта; true = активировать; Если поле не задано, то считается что условие выполняется.")]
    public DBPtr<ConditionFormula> enableCondition;
	}

  [DBVersion(4)]
  [UseTypeName("EFPL")]
  public class EffectsPool : DBResource
  {
    [EnumArray(typeof(EEffects))]
    public List<DBPtr<EffectBase>> effectsList = new List<DBPtr<EffectBase>>();
  }

  [TypeId(0x2B823BC0)]
  [UseTypeName("EFFT")]
  public class EffectList : EffectBase
  {
    public List<DBPtr<EffectBase>> effects = new List<DBPtr<EffectBase>>();
  }

  [TypeId(0xA06253C1)]
  [UseTypeName("EFFT")]
  public class BasicEffect : EffectBase
  {
    public DBPtr<DBSceneComponent> component;
    public float fadeIn = 0;
    public float fadeOut = 0;
	}

  [TypeId(0xA06253C2)]
  [UseTypeName("EFFT")]
	[FactoryImpl( "Retrieve", "PF_Core::BasicEffectStandalone", "EffectsPool.h", CreateFunction = "PF_Core::CreateEffectFromPool<>" )]
  public class BasicEffectStandalone : BasicEffect
  {
    [Description("If true effective visibility is limited by visibleTime, otherwise it's limited only by visibility itself.")]
    public bool visibilityLimited = false;

    public float visibleTime = 0.0f;

    public bool isVisibleUnderWarfog = false;

    [DefaultValues( typeof( EEffectAttachType ) )]
    public string parentType = "General";
    public EStandAloneEffectFlags parentFlags = EStandAloneEffectFlags.None;
  }

  [TypeId(0xA06253C3)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "PF_Core::BasicEffectAttached", "EffectsPool.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class BasicEffectAttached : BasicEffect
  {
    [DefaultValues(typeof(EEffectAttachType))]
    public string attachType = "General";
    public EAttachFlags attachFlags = EAttachFlags.None;
    public EEffectGroupFlags groupFlags = EEffectGroupFlags.None;
  }

  public class EffectEventAction
  {
    [Description("Animation to play")]
    public string animation = string.Empty;
    [Description("Marker to synchronize with event")]
    public string marker = string.Empty;
  }

  [TypeId(0xA06CEBC0)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "PF_Core::ControlledStatusEffect", "EffectsPool.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class ControlledStatusEffect : BasicEffectAttached
  {
    [Description("Actions for events")]
    [EnumArray(typeof(EEffectEvent))]
    public List<EffectEventAction> eventActions = new List<EffectEventAction>();

    [Description("Standalone afterlife extension (starts upon DEATH event, scene components inherited)")]
    public DBPtr<BasicEffectStandalone> onDeathEffect;
  }

  [TypeId(0xA0629380)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "PF_Core::LightningEffect", "LightningEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class LightningEffect : EffectBase
  {
    [Description( "Associated scene component" )]
    public DBPtr<DBLightningSceneComponent> component;

    [Description("Lightning is visible iff at least one object attached to is visible?")]
    public bool controlledVisibility = false;
  }

  public enum EnableSCEffectMode
  {
    ComponentId,
    EventName,
  }
  
  [TypeId(0xA0626B00)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "PF_Core::EnableSCEffect", "EnableSCEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  [DBVersion(1)]
  public class EnableSCEffect : EffectBase
  {
    [Description("ComponentId or EventName used then effect start")]
    public string nameStart;
    [Description("ComponentId or EventName used then effect stop")]
    public string nameStop;

    public EnableSCEffectMode mode = EnableSCEffectMode.ComponentId;
    public bool enable = true;
  }

  [TypeId(0xA06253C4)]
  [UseTypeName("EFFT")]
  [DBVersion(3)]
  [FactoryImpl("Retrieve", "PF_Core::ScaleColorEffect", "ScaleColorEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class ScaleColorEffect : EffectBase
  {
    public float scale = 1.0f;
    public HDRColor colorMul = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
    public HDRColor colorAdd = new HDRColor(0.0f, 0.0f, 0.0f, 0.0f);
    public BlendMode blendMode = BlendMode.LerpByAlpha;
    public AnimatedFloat scaleIn = new AnimatedFloat(1.0f);
    public AnimatedFloat scaleOut = new AnimatedFloat(1.0f);
    public float fadeInTime = 1.0f;
    public float fadeOutTime = 1.0f;
    public bool fullRecolor = false;
  }

  [TypeId(0x9DAA1380)]
  [UseTypeName("EFFT")]
  [DBVersion(1)]
  [FactoryImpl("Retrieve", "PF_Core::ChangeMaterialEffect", "ChangeMaterialEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class ChangeMaterialEffect : EffectBase
  {
    public float fadeInTime = 1.0f;
    public float fadeOutTime = 1.0f;

    public List<DBPtr<Material>> materials = new List<DBPtr<Material>>();
  }

  [TypeId(0xA06B93C0)]
  [UseTypeName("EFFT")]
  [FactoryImpl("Retrieve", "PF_Core::GhostEffect", "GhostEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
  public class GhostEffect : EffectBase
  {
  }

  public enum EEffectSelectionPolicy
  {
    Random = 0,
    Sequential,
  }
	[UseTypeName( "ESEL" )]
  public class EffectSelector : DBResource
  {
    [Description("Effects to select from")]
    public List<DBPtr<BasicEffectStandalone>> effects = new List<DBPtr<BasicEffectStandalone>>();

    [Description("Method to select effect")]
    public EEffectSelectionPolicy selectionPolicy = EEffectSelectionPolicy.Random;
  }

  public enum EEffectGenPolicy
  {
    Start = 0,
    Death,
    Regular,
  }

  public enum EEffectAlignment
  {
    None = 0,
    Ground,
  }

  public class PositionRandomizer : DBResource
  {

  }

  public class RectangleRandomizer : PositionRandomizer
  {
    public Vec2 min = new Vec2(0.0f, 0.0f);
    public Vec2 max = new Vec2(0.0f, 0.0f);
  }

  public class CircleRandomizer : PositionRandomizer
  {
    public float radius = 0.0f;
  }

  [TypeId(0x9E6433C0)]
  [UseTypeName("EGSC")]
  [FactoryImpl("Create", "PF_Core::EffectGenSceneComponent", "EffectGenSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class EffectGenSceneComponent : DBSceneComponent
  {
    [Description("Effect to be created")]
    public DBPtr<EffectSelector> effect;
    
    [FieldCategory("Generation")]
    public EEffectGenPolicy generationPolicy = EEffectGenPolicy.Start;
    [FieldCategory("Generation")]
    public float minPeriod = 1.0f;
    [FieldCategory("Generation")]
    public float maxPeriod = 1.0f;

    [FieldCategory("Randomization")]
    public DBPtr<PositionRandomizer>  posRandomizer;
    [FieldCategory("Randomization")]
    public bool randomizeDirection = false;

    public EEffectAlignment alignment = EEffectAlignment.None;
    public float offset = 0.0f;
  }
	[UseTypeName( "TRAC" )]
  public class Trace : DBResource
  {
    public DBPtr<EffectSelector> waterTrace;

    [EnumArray(typeof(ENatureType))]
    public List<DBPtr<EffectSelector>> terrainTrace = new List<DBPtr<EffectSelector>>();
  };

  public class TraceInfo
  {
    [Description("Animation node name (traces will be generated when in this node)")]
    public string nodeName;
    [Description("Locator name (traces will be generated at this locator's position)")]
    public string locatorName;
    public DBPtr<Trace> traces;
  };

  [TypeId(0xA065B300)]
  [UseTypeName("TGSC")]
  [FactoryImpl("Create", "PF_Core::TraceGenSceneComponent", "TraceGenSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class TraceGenSceneComponent : DBSceneComponent
  {
    public DBPtr<Trace>  defaultTraces;
    public string defaultLocatorName;
    public List<TraceInfo> traceByAnim = new List<TraceInfo>();
  }

  [UseTypeName("PSCE")]
  [TypeId(0xA065DB40)]
  [FactoryImpl("Create", "PF_Core::ParticleSceneComponentWithEffect", "ParticleSceneComponentWithEffect.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class ParticleSceneComponentWithEffect : DBParticleSceneComponent
  {
    public DBPtr<BasicEffectStandalone> effect;
  }

  [UseTypeName("CSSC")]
  [TypeId(0xA0698AC0)]
  [FactoryImpl("Create", "PF_Core::CameraShakeSceneComponent", "CameraShakeSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class CameraShakeSceneComponent : DBSceneComponent
  {
    [Description("Animated camera displacement")]
    public DBPtr<AnimatedPlacementResource> displacement;

    [Description("Maximum distance between camera anchor and component for shake to be visible")]
    public float range = 10.0f;
  }

  [UseTypeName("PFXP")]
  [TypeId(0xA06C5B40)]
  [DBVersion(0)]
  public class PostFXParams : DBResource
  {
    [EnumArray(typeof(ENatureType))]
    public List<FullScreenFXParams> fullScreenFXParams = new List<FullScreenFXParams>();
    public float mipMapLodBias = 0.0f;
  }

  [DBVersion(0)]
  public class SpringParamDynamics
  {
    [Description("Множитель скорости изменения параметра")]
    public float speed = 1.0f;

    [Description("Максимальное отставание (-1 значит не ограничено)")]
    public float maxValue = -1.0f;
  }

  [TypeId(0xA071EBC0)]
  [DBVersion(0)]
  [UseTypeName("SPSC")]
  [FactoryImpl("Create", "PF_Core::SpringSceneComponent", "SpringSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class SpringSceneComponent : DBSceneComponent
  {
    [Description("Параметры динамики позиции")]
    public SpringParamDynamics posDynamics;

    [Description("Параметры динамики поворота")]
    public SpringParamDynamics rotDynamics;

    [Description("Параметры динамики масштаба")]
    public SpringParamDynamics scaleDynamics;
  }
}
