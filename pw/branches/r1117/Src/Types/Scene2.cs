//#include "Scene.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using Render.DBRender;
using Render.DBRenderResources;
using Scene.DBSceneBase;
using Sound.DBSound;

namespace Scene.DBScene
{
  public enum EOrientType
  {
    None,
    Axis,
    Speed,
    Plane
  };

  [IndexField( "name" )]
  [UseTypeName( "SOTRACK" )]
  public class SceneObjectTrack : DBResource
  {
    public AnimatedPlacement placement;
    public AnimatedFloat opacity = new AnimatedFloat( 1.0f );
    public string name;
  }

  [UseTypeName( "SOTRACKS" )]
  public class SceneObjectTracks : DBResource
  {
    public List<DBPtr<SceneObjectTrack>> animatedTracks = new List<DBPtr<SceneObjectTrack>>();
  }

  [TypeId(0x9E647A80)]
  public class TimeController : DBResource
  {
    public float speed            = 1.0f;
    public float startDelay       = 0.0f;
    public float firstCycleOffset = 0.0f;
    public float firstCycleOffsetDelta = 0.0f;
    public float cycleLength = 0.0f;
    public int   cycleCount       = 1;
    public float fadein           = 0.0f;
    public float fadeout          = 0.0f;
  }


  [TypeId(0x9E6433C1)]
  [UseTypeName("SCEV")]
  public class SCEvent : DBResource
  {
  }

  [TypeId(0x9E6433C2)]
  public class AnimationSCEvent : SCEvent
  {
    [Description("Type of event")]
    public EAnimEventType type = EAnimEventType.NodeParam;
    [Description("Name of animation sequence or marker")]
    [AnimationScEventSelector]
    public string name = string.Empty;
    [Description("Animation parameter [0..1]")]
    public float animParam = 0.0f;
    [Description( "Probability in per cent[0..100]" )]
    public float probability = 100.0f;
  }

  [TypeId(0x9E6433C3)]
  public class GroundHitSCEvent : SCEvent
  {
    [Description("Event will be triggered when height of the component above ground reach this value")]
    public float heightAboveGround = 0.0f;
  }

  [TypeId(0xA06A4B80)]
  public class NamedSCEvent : SCEvent
  {
    [Description("Event name")]
    public string name = string.Empty;
  }

  public enum EEnableDisableOrder
  {
    EnableThenDisable = 0,
    DisableThenEnable,
  }

  [TypeId(0x9E64AA80)]
  [UseTypeName("EDEV")]
  public class EnableDisableSCEvents : DBResource
  {
    [Description("Order of component enabling/disabling. When component is enabled-then-disabled, it will be disabled on start.")]
    public EEnableDisableOrder order = EEnableDisableOrder.EnableThenDisable;
    [Description("Forces component to reinit on enable & deinit on disable")]
    public bool restartComponent = true;
    [Description("List of enable events")]
    public List<DBPtr<SCEvent>> enableEvents = new List<DBPtr<SCEvent>>();
    [Description("List of disable events")]
    public List<DBPtr<SCEvent>> disableEvents = new List<DBPtr<SCEvent>>();
  }

  [TypeId(0x9D759480)]
  [UseTypeName("EDEV")]
  public class EnableDisableSkinEvents : DBResource
  {
    [Description("Order of component enabling/disabling. When component is enabled-then-disabled, it will be disabled on start.")]
    public EEnableDisableOrder order = EEnableDisableOrder.EnableThenDisable;
    [Description("List of enable events")]
    public List<DBPtr<SCEvent>> enableEvents = new List<DBPtr<SCEvent>>();
    [Description("List of disable events")]
    public List<DBPtr<SCEvent>> disableEvents = new List<DBPtr<SCEvent>>();
  }

  [TypeId(0x8D5A3B40)]
  public class DBAnimKey : DBResource
  {
    public string name = String.Empty;
  }

  [TypeId(0x8D5A3AC0)]
  public class DBAttachAnimKey : DBAnimKey
  {
    public DBPtr<DBSceneComponent> component;
  }

  [TypeId( 0x146AAB40 )]
  [UseTypeName("LOLS")]
  public class LocatorList : DBResource
  {
    [Description( "List of locators" )]
    public List<Locator> locators;
  }

  public enum ESCOrientation
  {
    Default = 0,
    Camera,
    CameraFixedZ
  }

  [Flags]
  public enum EGroupFlags
  {
    None           = 0,
    Recolorable    = (1 << 2),
    // Want to add something here? Check SceneComponent::InternalGroupFlags which uses part of bit range.
  }

  [TypeId(0x9E656380)]
  [FactoryBase("Create", "NScene::SceneComponent", "NScene::HierarchyCreator &creator", "const AttachedSceneComponent* pAttached", "const Placement& transform", ReturnType = "CObj<NScene::SceneComponent>", Define = "!VISUAL_CUTTED")]
  public class DBSceneComponentBase : DBSceneResource
  {
  }

  [TypeId(0x8D5A1240)]
  [UseTypeName("PRXY")]
	[IndexField( "caption" )]
  [FactoryImpl("Create", "NScene::SceneComponent", "SceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class DBSceneComponent : DBSceneComponentBase
  {
    [Description( "List of locators" )]
    public DBPtr<LocatorList> locatorList;

    [Description("Automatic orientation of the component ('Default' means straight application of attachFlags)")]
    public ESCOrientation orientation = ESCOrientation.Default;

    [Description("Flags allowing to mark component as belonging to some game specific group")]
    public EGroupFlags groupFlags = EGroupFlags.None;

    [NoCode]
		public string caption = string.Empty;
  }

  public class SkinPart : SkinPartBase
  {
    [Description("Events for enabling and disabling this skin")]
    public DBPtr<EnableDisableSkinEvents> events;
  }

  [UseTypeName( "ANSC" )]
  [TypeId(0x8D5A1241)]
	[DBVersion( 1 )]
  [FactoryImpl("Create", "NScene::AnimatedSceneComponent", "AnimatedSceneComponent.h", CreateFunction = "NScene::CreateAnimatedSceneComponent")]
  public class DBAnimatedSceneComponent : DBSceneComponent
  {
    // Data of AnimatedSplitSceneComponent
    [Description("Additional animation graph")]
    public DBPtr<AnimGraphCreator> additionalGraph;
    // Data of AnimatedSplitSceneComponent
    [Description("Name of bone to split animations")]
    public string splitBoneName = string.Empty;
    // Data of AnimatedSplitSceneComponent

    [SrcFile("Maya files", "*.mb")]
    [DstFileArg(0)]
    public string srcFileName = string.Empty;

    [NoCode]
    [DstFile("mayaSkel")]
    public string mayaFileName = string.Empty;

    [DstFile("skel")]
    public string skeletonFileName = string.Empty;

    [NoCode]
    [DstFileArg(1)]
    public string selection = string.Empty;

    public List<SkinPart> skins = new List<SkinPart>();
    public List<Animation> animations = new List<Animation>();
    public List<FaceFX> faceFXAnims = new List<FaceFX>();
    
    //animation graph
    public DBPtr<AnimGraphCreator> animGraph;

    public AABB aabb = new AABB(666.0f, -666.0f, 666.0f, -666.0f, 666.0f, -666.0f); // Init to invalid BBox

    public List<AnimFaceFXKey> anims = new List<AnimFaceFXKey>();
    public List<int> skinOn = new List<int>();
    public List<DBPtr<DBAnimKey>> keys = new List<DBPtr<DBAnimKey>>();
  }

  [UseTypeName( "STSC" )]
  [TypeId(0x8D5A1242)]
  [FactoryImpl("Create", "NScene::StaticSceneComponent", "SceneObjectCreation.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class DBStaticSceneComponent : DBSceneComponent
  {
		[SrcFile( "Maya files", "*.mb" )]
		[DstFileArg( 0 )]
		public string srcFileName = string.Empty;

		[NoCode]
		[DstFile( "mayaStat" )]
		public string mayaFileName = string.Empty;

		[DstFile( "stat" )]
		public string geometryFileName = string.Empty;

		[NoCode]
		[DstFileArg( 1 )]
		public string selection = string.Empty;

		[ReadOnly( true )]
		public AABB aabb = new AABB();

		[NoCode]
		public int uvSetCount = 1;

    [Description("List of materials")]
    public List<DBPtr<Material>> materialsReferences = new List<DBPtr<Material>>();
  }

  [UseTypeName("WAIN")]
  [TypeId(0x3B622C41)]
  public class DBWaterInfo : DBResource // can be shared between several DBWaterSceneComponents
  {
    [Description("Ripples texture tiling. Increase to make ripples smaller in size.")]
    public float tiling = 2.0f;
    [Description("Shininess controls reflections. Decrease to make more reflective, even from above.")]
    public float shininess = 4.0f;
    [Description("Increase to make ripples (waves) harder.")]
    public float ripples = 1.0f;
    [Description("Increase to make ripples (waves) higher. Most obvious at border.")]
    public float ripplesHeight = 0.1f;
    [Description("Controls 'fog'. Distance at which bottom color is faded twice, in meters.")]
    public float distance = 5.0f;
    [Description("=NOT USED YET=")]
    public float refraction = 1.05f;
    [Description("Water depth for gradient texture mapping, in meters.")]
    public float depth = 10.0f;
    [Description("Water depth for reflections to appear, in meters.")]
    public float depthReflect = 0.0f;
    [Description("Speed and direction of river current (texture scrolling).")]
    public Vec2 speed = new Vec2(0.0f, 0.0f);
    [Description("Caustics texture tiling. Increase to make ripples smaller in size.")]
    public float causticsTiling = 2.0f;
    [Description("Caustics texture intensity multiplier.")]
    public float causticsIntensity = 1.0f;

    public DBPtr<Texture> gradientMap;
    public DBPtr<Texture> causticsMap;
  }

  [UseTypeName("WASC")]
  [TypeId(0x3B622C40)]
  [FactoryImpl("Create", "NScene::WaterSceneComponent", "WaterSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class DBWaterSceneComponent : DBStaticSceneComponent
  {
		[FieldCategory( "Water Settings" )]
		public DBPtr<DBWaterInfo> water;

    [FieldCategory("Water Settings")]
    [ReadOnly( true )]
    public float waterLevel = 0.0f; // automatically calculated based on AABB
  }

  [UseTypeName("PRSC")]
  [TypeId(0x8D5A1243)]
	[DBVersion( 1 )]
  [FactoryImpl("Create", "NScene::ParticleSceneComponent", "ParticleSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class DBParticleSceneComponent : DBSceneComponent
  {
    [Description("Particle to camera offset")]
    public float camoffset = 0.0f;
    [Description("Is Oriented?")]
    public EOrientType orient = EOrientType.None;
    [Description("Particle pivot")]
    public Vec2 pivot;
    [Description("Do we need particles be attached to it's source or leaved at birth place?")]
    public bool leaveParticlesWhereStarted = false;
		[Description( "FadeOut time for dying particles with leaveParticlesWhereStarted = true" )]
		public float deathFadeOutTime = 0.5f;

    public DBPtr<ParticleFXMaterial> material;
    [NoCode]
    [SrcFile("Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff", "PFX_Textures")]
    public List<string> textures = new List<string>();
    [NoCode]
    [SrcFile("Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff", "PFX_Textures")]
    public List<string> normaltextures = new List<string>();
    [NoCode]
    [SrcFile("Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff", "PFX_Textures")]
    public List<string> speculartextures = new List<string>();
    public List<UVPair> uvPairs = new List<UVPair>();

    public AABB aabb = new AABB(666.0f, -666.0f, 666.0f, -666.0f, 666.0f, -666.0f); // Init to invalid BBox

    [NoCode]
    [DstFile("mayaPart")]
    public string mayaFileName;
    [DstFile("part")]
    public string fxFileName;
    [NoCode]
    public float compression = 2.0f;
    [NoCode]
    [DstFileArg(1)]
    public string selection = string.Empty;
    [SrcFile("Maya files", "*.mb")]
    [DstFileArg(0)]
    public string srcFileName;
  }

  public enum Sound3DSimultType
  {
    Melee,
    Range,
    CreepDeath,
    Infinite // @IgorKaa: keep it last
  }

  [UseTypeName("SNSC")]
  [TypeId(0x4D5B9BC0)]
  [FactoryImpl("Create", "NScene::SoundSceneComponent", "SoundSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class DBSoundSceneComponent : DBSceneComponent
  {
    [Description("Sound event description")]
    public DBFMODEventDesc desc;

    [Description("Sound will playing in this time interval")]
    public float timeInterval = 0.0f;
  }

  public enum EAnimEventType
  {
      NodeEnter,
      NodeLeave,
      NodeParam,
      Marker
  }

  [UseTypeName("TRSC")]
  [TypeId(0x3B6184C0)]
  [FactoryImpl("Create", "NScene::TraceSceneComponent", "TraceSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class DBTraceSceneComponent : DBSceneComponent
  {
    [Description("TraceMaterial to use")]
    public DBPtr<TraceMaterial> material;
    [Description("The first locator name")]
    public string locator1Name = string.Empty;
    [Description("The second locator name")]
    public string locator2Name = string.Empty;

    [Description("Maximal trace length allowed, in meters")]
    [FieldCategory("Effect Parameters")]
    public float maxLength = 1.0f;

    [Description("When to start generating trace, in mps")]
    [FieldCategory("Effect Parameters")]
    public float speedStart = 10.0f;

    [Description("When to stop generating trace, in mps")]
    [FieldCategory("Effect Parameters")]
    public float speedStop = 2.0f;

    [Description("Color of trace near the blade")]
    [FieldCategory("Effect Parameters")]
    public HDRColor colorFirst = new HDRColor(1.0f, 1.0f, 0.0f, 1.0f);

    [Description("Color of trace to fade into")]
    [FieldCategory("Effect Parameters")]
    public HDRColor colorLast = new HDRColor(0.0f, 0.0f, 1.0f, 1.0f);

    [Description("Delay for color interpolation, in 0..1")]
    [FieldCategory("Effect Parameters")]
    public float offsetColor = 0.0f;

    [Description("Delay for transparency interpolation, in 0..1")]
    [FieldCategory("Effect Parameters")]
    public float offsetAlpha = 0.0f;

    [Description("Fadeout speed, in mps")]
    [FieldCategory("Effect Parameters")]
    public float fadeoutSpeed = 10.0f;

    [Description("Coefficient of trace skewness, in 0..1")]
    [FieldCategory("Effect Parameters")]
    public float skewness = 0.5f;
  }

	public enum ELightningAnimType
	{
		None,
		Sequential,
		Randomized
	}

	public class DBLightningFXParams
	{
		[Description("Total number of subtextures in texture atlas.")]
		public int animAtlasSize = 1;

		[Description("Zero-based index of the first subtexture used in animation.")]
		public int animFirstFrame = 0;

    [Description("Zero-based index of the last subtexture used in animation.")]
		public int animLastFrame = 0;

		[Description("Texture animation speed, in frames per second.")]
		public float animSpeed = 0.0f;

		[Description("Texture animation type.")]
		public ELightningAnimType animType = ELightningAnimType.None;

    [Description("Opacity fadeout distance at the beginning")]
    public float opacityDistance1 = 0.0f;

    [Description("Opacity fadeout distance at the end")]
    public float opacityDistance2 = 0.0f;

		[Description("Color to modulate the texture.")]
		public HDRColor color = new HDRColor(1, 1, 1, 1);

		[Description("Thickness of the lightning geometry.")]
		public float radius = 0.25f;

		[Description("Texture scroll speed, in meters per second.")]
		public float scrollSpeed = 0.0f;

		[Description("Texture mapping length along the lightning, in meters.")]
		public float tiling = 5.0f;
	}

  [UseTypeName("LGSC")]
  [TypeId(0x3B61E441)]
  [FactoryImpl("Create", "NScene::LightningSceneComponent", "LightningSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
  public class DBLightningSceneComponent : DBSceneComponent
  {
    [Description("LightningMaterial to use")]
    public DBPtr<LightningMaterial> material;
    [Description("The first locator name")]
    public string fromLocator = string.Empty;
    [Description("The second locator name")]
    public string toLocator = string.Empty;
		[Description("FX Parameters")]
		public DBLightningFXParams fxParams;
	}

  public class AnimatedPlacement
	{
		public AnimatedVec3 pos;
		public AnimatedQuat rot;
		public AnimatedScale scale = new AnimatedScale( 1.0f, 1.0f, 1.0f );
	}

  [Flags]
  public enum EAttachFlags
  {
    None                = 0,
    UseParentScale      = 1,
    UseParentRotation   = 1 << 1,
    UseParentTime       = 1 << 2,
    UseAGSpeedCoeff     = 1 << 3,
    StayInWorld         = 1 << 4,
    CancelOffsetScaling = 1 << 5,
  }

  [Flags]
  public enum EStandAloneEffectFlags
  {
    None = 0,
    UseParentScale = 1,
    UseParentRotation = 1 << 1,
  }

  [IndexField("component")]
	public class AttachedSceneComponent
  {
    public DBPtr<DBSceneComponent> component;

    [LocatorNameSelector]
    public string locatorName;
    
    public DBPtr<TimeController> timeController;
		
    public AnimatedPlacement placement;

    public EAttachFlags attachFlags = EAttachFlags.UseParentScale | EAttachFlags.UseParentRotation | EAttachFlags.UseParentTime | EAttachFlags.UseAGSpeedCoeff;
    
    public string id = string.Empty;
    
    [Description("Events for enabling and disabling this scene component")]
    public DBPtr<EnableDisableSCEvents> events;
  }

  [UseTypeName("SOBJ")]
  public class DBSceneObject : DBSceneResource
  {
    public DBPtr<SceneObjectTracks> tracksList;
    public DBPtr<CollisionGeometry> collisionGeometry;
    [Description("Do not accept effect attaches to non-default locators")]
    public bool ignoreAttachesToNonDefaultLocators = false;
  };

  [NonTerminal]
  public class DBSceneResource : DBResource
  {
    public List<AttachedSceneComponent> attached;
  }

  [UseTypeName("ANPL")]
  [TypeId(0xA071B300)]
  public class AnimatedPlacementResource : DBResource
  {
    public AnimatedPlacement placement;
  }
}



