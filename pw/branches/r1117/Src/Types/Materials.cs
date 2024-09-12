//#include "Render.cs"
//#include "RenderTypes.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;

namespace Render.DBRender
{
  [Flags]
  [NoCSCode]
  public enum MaterialOldFlags
  {
    None = 0,
    RequireAlphaBlending = 1,
    CastsShadows = 2,
  }

  [Flags]
  public enum MaterialFlags
  {
    None = 0,
    ShadowCaster = (1 << 0),
    ShadowReceiver = (1 << 1),
    ReflectInWater = (1 << 2),
  }

  [NoCSCode]
  public enum MaterialPriority
  {
    None = -1,
    MeshesOpaque,
    MeshesOpaqueLate,
    MeshesSilhouette,
    TerrainLayer0,
    TerrainLayer1,
    Roads,
    TerrainObjects,
    TerrainDominationDecals,
    TerrainDecals,
    WaterDecals,
    TransparentSpecial,
    Transparent,
    Distortion,
    Heightfog,
    Sky,
    Count,
  }

  // Pins specifications

  public enum BooleanPin
  {
    None = 0,
    Present = 1,
  }

  public enum TerrainUVSetPin
  {
    Global = 0,
    Local = 1,
  }

  public enum TextureCountPin
  {
    Count1 = 0,
    Count2 = 1,
    Count3 = 2,
    Count4 = 3,
  }

  public enum DebugPin
  {
    SimpleShading = 0,
    ShowNormals = 1,
    ShowMipMaps = 2,
  }

  public enum MADPin
  {
    NoMAD = 0,
    MADEnabled = 1,
  }

  public enum OpacityPin
  {
    Opaque = 0,
    AlphaOpacity = 1,
    ColorOpacity = 2,
  }

  public enum OrientTypePin
  {
    NoneType = 0,
    AxisType = 1,
    SpeedType = 2,
    PlaneType = 3,
  }

  public enum DiffuseMapCountPin
  {
    NoDiffuseMap = 0,
    BaseDiffuseMap = 1,
    BothDiffuseMaps = 2,
  }

  public enum DiffuseColorMixPin
  {
    ColorMixAdd = 0,
    ColorMixAddWithAlpha = 1,
    ColorMixLerp = 2,
    ColorMixMul = 3,
  }

  public enum DiffuseAlphaMixPin
  {
    AlphaMixTex1 = 0,
    AlphaMixAddSmooth = 1,
    AlphaMixMul = 2,
  }

  public enum OpacityAndEmissiveModePin
  {
    Simple = 0,
    AdditiveOpacity = 1,
    BlendOpacity = 2,
    Emissive = 3,
  }

  public enum EEmissivePin
  {
    EmissiveOff = 0,
    EmissiveFromAlpha = 1,
    EmissiveFromSpecular = 2,
  }

  public enum LightModePin
  {
    Diffuse = 0,
    DiffuseOpacity = 1,
    DiffuseSpecular = 2,
    DiffuseSpecularOpacity = 3,
    DiffuseEmissive = 4,
    DiffuseSpecularEmissive = 5,
    DiffuseSpecularToEmissive = 6,
  }

  public enum ReflectivityPin
  {
    ReflectivityOff = 0,
    ReflectivitySimple = 1,
    ReflectivityFromNormalMap = 2,
    ReflectivityFromSpecularMap = 3,
  }

  public enum LightingPin
  {
    LightingSH = 0,
    LightingInstancedSH = 1,
    LightingBaked = 2,
    LightingDynamic = 3,   // LightingDynamic*** should be last memders of this enum
    LightingDynamic1Point = 4,
    LightingDynamic2Point = 5,
    LightingDynamic3Point = 6,
    LightingDynamic4Point = 7,
  }

  public enum DistortionPin
  {
    DistortNone = 0,
    DistortMap = 1,
    DistortNoise = 2,
  }

  public enum PackedMasksNumberPin
  {
    PackedMasks1 = 0,
    PackedMasks2 = 1,
    PackedMasks3 = 2,
    PackedMasks4 = 3,
    PackedMasks5 = 4,
    PackedMasks6 = 5,
    PackedMasks7 = 6,
    PackedMasks8 = 7,
    PackedMasks9 = 8,
    PackedMasks10 = 9,
    PackedMasks11 = 10,
    PackedMasks12 = 11,
    PackedMasks13 = 12,
    PackedMasks14 = 13,
    PackedMasks15 = 14,
    PackedMasks16 = 15,
    PackedMasks17 = 16,
    PackedMasks18 = 17,
    PackedMasks19 = 18,
    PackedMasks20 = 19,
  }

  public enum TextureColorizePin
  {
    NoColor = 0,
    AddColoredAlpha = 1,
    MulColorByAlpha = 2,
    ColorForEveryChanel = 3,
    TestColor = 4,

  }

  public enum RenderModePin
  {
    RenderNormal = 0,
    RenderToShadow = 1,
    RenderShapeOnly = 2,
    //RenderReprojection1
  }

  public enum CachingPin
  {
    Ordinary = 0,
    Fill = 1,
    Use,
    Use2,
    Use3
  }

  public enum ShaderQualityPin
  {
    Best = 0,
    Fast = 1,
  }

  public enum BoolPin
  {
    FALSE = 0,
    TRUE = 1,
  }

  public enum ColorCorrectPin
  {
    OFF = 0,
    ON = 1,
    NO_GAMMA,
    DESATURATE_ONLY
  }

  public enum DecalModePin
  {
    Standard,
    DualDepth,
    ZDecode
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Materials declaration
  [TypeId]
  [NonTerminal]
  [BaseMaterialType]
  [IndexField("caption")]
  [DBVersion(1)]
  public class Material : DBResource
  {
    [Description("The less the sooner")]
    [IntMinMax(-16, 16)]
    public int SubPriority = 0;

    public string caption;

    [NoCSCode]
    public MaterialFlags renderFlags = MaterialFlags.ShadowReceiver;

    [NoCSCode]
    public const MaterialOldFlags flags = MaterialOldFlags.None;

    [NoCSCode]
    public const MaterialPriority priority = MaterialPriority.MeshesOpaque;

    [NoCSCode]
    public const bool bShadowCastSupport = false;

    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public BoolPin DoDepthOutValue = BoolPin.TRUE;

    [Description( "Не выставлять прописанный RenderState" )]
    public bool ignoreRenderState = false;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x9E5872A4)]
  [MaterialFunc( "BasicMaterialWithBatch.inl", "ModifyEmissive(float power)", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)", "SetBlendModeOverride(bool state)" )]
  [MaterialFunc("SpecialTransparency.inl", "SetSpecialTransparency(bool on)")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(677)]
  public class BasicMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);

    [NoCSCode]
    public int isBlendModeOverrided = 0;

    [FieldCategory("States")]
    [NoCode]
    public new MaterialFlags renderFlags = MaterialFlags.ShadowReceiver;

    [FieldCategory("States")]
    [NoCode]
    public new const bool bShadowCastSupport = true;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Lighting")]
    public HDRColor diffuseColor = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Lighting")]
    public float lightingIntencity = 1.0f;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Diffuse")]
    [Sampler(0, "DiffuseMap", true)]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Wrap));

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Normal")]
    [Sampler(1, true)]
    public Sampler NormalMap = new Sampler(new SamplerState(TextureAddressType.Wrap));

    [FieldCategory("Normal")]
    [Pin2]
    [NoCSCode]
    public BooleanPin NormalMapPinValue = BooleanPin.None; // auto-calculated

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Specular")]
    [Sampler(2, true)]
    public SamplerEx SpecularMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap), new HDRColor(1, 1, 1, 1), new HDRColor(0, 0, 0, 0));

    [FieldCategory("Specular")]
    [Pin2]
    [NoCSCode]
    public BooleanPin SpecularMapPinValue = BooleanPin.None; // auto-calculated

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Reflection")]
    [Sampler(3, true)]
    public SamplerCube ReflectionMap = new SamplerCube(new SamplerState(TextureAddressType.Wrap));

    [FieldCategory("Reflection")]
    [Pin2]
    public ReflectivityPin ReflectivityPinValue = ReflectivityPin.ReflectivityOff;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Modificator")]
    public HDRColor outputMul = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Modificator")]
    public HDRColor outputAdd = new HDRColor(0.0f, 0.0f, 0.0f, 0.0f);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Pins")]
    [Pin2("SkeletalMeshPin")]
    [NoCSCode]
    public BooleanPin SkeletalMeshPinValue;

    [FieldCategory("Pins")]
    [Pin2]
    public EEmissivePin EmissivePinValue = EEmissivePin.EmissiveOff;

    [FieldCategory("Pins")]
    [Pin2]
    [NoCSCode]
    public BooleanPin OpacityPinValue = BooleanPin.None;

    [FieldCategory("Pins")]
    [Pin2]
    [NoCSCode]
    public BooleanPin SpecularPinValue = BooleanPin.None;

    [FieldCategory("Pins")]
    [HideEnumValues("LightingDynamic1Point", "LightingDynamic2Point", "LightingDynamic3Point", "LightingDynamic4Point")]
    [Pin2("LightingPin")]
    public LightingPin LightingPinValue = LightingPin.LightingSH;

    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public RenderModePin RenderModeValue = RenderModePin.RenderNormal;

    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public BooleanPin InstancingValue = BooleanPin.None;

    public float emissive = 0.0f;

    [NoCSCode]
    public float opacity = 1.0f;

    public float reflectivity = 1.0f;

    public float specularPower = 0.0f;

    [NoCSCode]
    public bool specialTransparency = false;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x9E5872A2)]
  [MaterialFunc("BasicFXMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)", "ModifyUVOffset(float u, float v)")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(3)]
  public class BasicFXMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);

    [FieldCategory("Diffuse")]
    [Sampler(0, "DiffuseMap", true)]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Wrap));

    [FieldCategory("Diffuse")]
    public AnimatedHDRColor DiffuseMul = new AnimatedHDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Diffuse")]
    public AnimatedHDRColor DiffuseAdd = new AnimatedHDRColor(0.0f, 0.0f, 0.0f, 0.0f);

    [FieldCategory("Pins")]
    [Pin2("SkeletalMeshPin")]
    [ReadOnly(true)]
    public BooleanPin SkeletalMeshPinValue;

    [FieldCategory("Pins")]
    [Pin2]
    public OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue = OpacityAndEmissiveModePin.Simple;

    [FieldCategory("Pins")]
    [Pin2("MultiplyVertexColorPin")]
    [ReadOnly(true)]
    public BooleanPin MultiplyVertexColorPinValue = BooleanPin.None;

    [FieldCategory("Pins")]
    [Pin2]
    public DistortionPin DistortionPinValue = DistortionPin.DistortNone;

    public float emissive = 0.0f;
    public float distortion = 1.0f;

    [NoCSCode]
    public float masterOpacity = 1.0f;

    [NoCSCode]
    public int isBlendModeOverrided = 0;

    public AnimatedFloat opacity = new AnimatedFloat(1.0f);

    public AnimatedFloat uOffset;
    public AnimatedFloat vOffset;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x49547342)]
  [MaterialFunc("ParticleFXMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode), CorrectRS(const RenderState &_src), GetRSandSamplersRep(PBYTE _pRep) const")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(7)]
  public class ParticleFXMaterial : Material
  {
    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public BoolPin NewParticlesValue = BoolPin.FALSE;

    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);

    [FieldCategory("Diffuse Map")]
    [Sampler(0, "DiffuseMap", true)]
    public SamplerEx DiffuseMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap), new HDRColor(1, 1, 1, 1), new HDRColor(0, 0, 0, 0));

    [FieldCategory("Opacity")]
    [HideEnumValues("Emissive")]
    [Pin2("OpacityModePin")]
    public OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue = OpacityAndEmissiveModePin.Simple;

    [FieldCategory("OrientType")]
    [NoCSCode]
    [Pin2("OrientTypePin")]
    public OrientTypePin OrientTypePinValue = OrientTypePin.NoneType;

    [FieldCategory("Distortion")]
    [Pin2]
    public BooleanPin DistortionPinValue = BooleanPin.None;

    public float opacity = 1.0f;
    public float distortion = 1.0f;
    public Vec2 uvSpeed;

    [NoCSCode]
    public new const MaterialPriority priority = MaterialPriority.Transparent;

    [NoCSCode]
    public int isBlendModeOverrided = 0;

    [Browsable(false), HideInOutliner]
    public float scale = 0.0f;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x3B5BDAC1)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(1)]
  public class TerrainElementMaterial : Material
  {
    [Pin2("TerrainUVSetPin")]
    public TerrainUVSetPin TerrainUVSetPinValue;
    [Pin2("TextureCountPin")]
    public TextureCountPin TextureCountPinValue;
    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public RenderModePin RenderModeValue = RenderModePin.RenderNormal;

    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public CachingPin CachingPinValue = CachingPin.Ordinary;
  }

  [TypeId(0x3B61E340)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(1)]
  public class TerrainElementDebugMaterial : Material
  {
  }

  [TypeId(0x3B641440)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(1)]
  public class NatureMapMaterial : Material
  {
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x3B5C8C00)]
  [MaterialFunc("CommonMaterialFunc.inl")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class TerrainAOEMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.On, 0, OnOffState.On);

    [FieldCategory("Diffuse")]
    [Sampler(0)]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Clamp));

    public Vec2 uvScale = new Vec2(1.0f, 1.0f);
    public Vec2 uvOffset;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId(0x3B61AC40)]
  [MaterialFunc("CommonMaterialFunc.inl")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class TraceMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.On, 0, OnOffState.Off);

    [FieldCategory("Diffuse")]
    [Sampler(0, "DiffuseMap")]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Wrap));

    [FieldCategory("Pins")]
    [Pin2("TraceTexturePin")]
    [NoCSCode]
    public BooleanPin TraceTexturePinValue = BooleanPin.None;

    public float uScale = 1.0f;
    public float vScale = 1.0f;
    public AnimatedFloat uOffset;
    public AnimatedFloat vOffset;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId(0x3B61E442)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class LightningMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.On, 0, OnOffState.Off);

    [FieldCategory("Diffuse")]
    [Sampler(0)]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Wrap));
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId(0x3B625AC0)]
  [MaterialFunc("BasicMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(6)]
  public class DecalMaterial : Material
  {
    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public DecalModePin DecalModeValue = DecalModePin.Standard;

    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public BooleanPin InstancingValue = BooleanPin.None;

    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.On, 0, OnOffState.On);

    //[FieldCategory("States")]
    //[HideEnumValues("ShadowCaster", "ReflectInWater")]
    //[NoCSCode]
    //[NoCode]
    //public new MaterialFlags renderFlags = MaterialFlags.None;

    [FieldCategory("Diffuse")]
    [Sampler(0)]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Clamp));

    [FieldCategory("Diffuse")]
    public AnimatedHDRColor DiffuseMul = new AnimatedHDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Diffuse")]
    public AnimatedHDRColor DiffuseAdd = new AnimatedHDRColor(0.0f, 0.0f, 0.0f, 0.0f);

    [Description("Decal radius, in meters")]
    public float radius = 5.0f;

    [Description("Set this pin to see the object shell and manipulate it. Usually switched off after object placement.")]
    [FieldCategory("Pins")]
    [Pin2]
    public BooleanPin AccessibilityPinValue = BooleanPin.Present;

    [FieldCategory("Pins")]
    [HideEnumValues("Emissive")]
    [Pin2]
    public OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue = OpacityAndEmissiveModePin.Simple;

    [FieldCategory("Pins")]
    [Pin2]
    public BooleanPin DistortionPinValue = BooleanPin.None;

    [FieldCategory("Pins")]
    [Pin2]
    public BooleanPin DecalPlanePinValue = BooleanPin.Present;

    public float distortion = 1.0f;
    [NonSignificantField]
    public bool putOnWater = true;

    [NoCSCode]
    public new const MaterialPriority priority = MaterialPriority.WaterDecals;

    [NoCSCode]
    public int isBlendModeOverrided = 0;

    [NoCSCode]
    [NonSignificantField]
    public float masterOpacity = 1.0f;

    [NonSignificantField]
    public AnimatedFloat opacity = new AnimatedFloat(1.0f);
  }

  [TypeId( 0x37B47B00 )]
  [MaterialFunc( "BasicMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)" )]
  [UseTypeName( "MTRL" )]
  [MaterialGroup( "BaseMaterial" )]
  [DBVersion( 0 )]
  public class DecalTerrainMaterial : Material
  {
    [Pin2( Pin2.Runtime )]
    [NoCSCode]
    [NoCode]
    public DecalModePin DecalModeValue = DecalModePin.Standard;

    [Pin2( Pin2.Runtime )]
    [NoCSCode]
    [NoCode]
    public BooleanPin InstancingValue = BooleanPin.None;

    [FieldCategory( "States" )]
    public RenderState renderState = new RenderState( BlendMode.LerpByAlpha, OnOffState.On, 0, OnOffState.On );

    //[FieldCategory("States")]
    //[HideEnumValues("ShadowCaster", "ReflectInWater")]
    //[NoCSCode]
    //[NoCode]
    //public new MaterialFlags renderFlags = MaterialFlags.None;

    [FieldCategory( "Diffuse" )]
    [Sampler( 0 )]
    public Sampler DiffuseMap = new Sampler( new SamplerState( TextureAddressType.Border ) );

    [FieldCategory( "Diffuse" )]
    [Sampler( 1 )]
    public Sampler MaskMap = new Sampler( new SamplerState( TextureAddressType.Border ) );

    [FieldCategory( "Diffuse" )]
    public AnimatedHDRColor DiffuseMul = new AnimatedHDRColor( 1.0f, 1.0f, 1.0f, 1.0f );

    [FieldCategory( "Diffuse" )]
    public AnimatedHDRColor DiffuseAdd = new AnimatedHDRColor( 0.0f, 0.0f, 0.0f, 0.0f );

    [Description( "Decal radius, in meters" )]
    public float radius = 5.0f;

    [Description( "Set this pin to see the object shell and manipulate it. Usually switched off after object placement." )]
    [FieldCategory( "Pins" )]
    [Pin2]
    public BooleanPin AccessibilityPinValue = BooleanPin.Present;

    [FieldCategory( "Pins" )]
    [HideEnumValues( "Emissive" )]
    [Pin2]
    public OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue = OpacityAndEmissiveModePin.Simple;

    [FieldCategory( "Pins" )]
    [Pin2]
    public BooleanPin DistortionPinValue = BooleanPin.None;

    [FieldCategory( "Pins" )]
    [Pin2]
    public BooleanPin DecalPlanePinValue = BooleanPin.Present;

    public float distortion = 1.0f;
    [NonSignificantField]
    public bool putOnWater = true;

    [NoCSCode]
    public new const MaterialPriority priority = MaterialPriority.TerrainDominationDecals;

    [NoCSCode]
    public int isBlendModeOverrided = 0;

    [NoCSCode]
    [NonSignificantField]
    public float masterOpacity = 1.0f;

    [NonSignificantField]
    public AnimatedFloat opacity = new AnimatedFloat( 1.0f );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId(0x3B629340)]
  [MaterialFunc("HeightfogMaterial.inl", "ModifyOpacity(float opacity)")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class HeightfogMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.On, 0, OnOffState.Off);

    [FieldCategory("Noise Internals")]
    [Sampler(0)]
    public Sampler noiseMap = new Sampler(new SamplerState(TextureAddressType.Wrap));
    [FieldCategory("Noise Internals")]
    [Description("[internal use]")]
    public float noiseR1 = 1.0f;
    [FieldCategory("Noise Internals")]
    [Description("[internal use]")]
    public float noiseR2 = 0.3f;
    [FieldCategory("Noise Internals")]
    [Description("[internal use]")]
    public float noiseR3 = 0.3f;

    [Description("Animation speed")]
    public float speed = 2.5f;

    [Description("Noise texture mapping scale, in meters")]
    public float tiling = 10.0f;

    [Description("Fog color 1")]
    public HDRColor color1 = new HDRColor(0.8f, 1.0f, 0.8f, 1.0f);

    [Description("Fog color 1")]
    public HDRColor color2 = new HDRColor(0.8f, 0.8f, 1.0f, 1.0f);

    [Description("Roughness of the fog surface, in meters")]
    public float roughnessScale = 2.0f;

    [Description("Distance at which fog is twice denser, in meters")]
    public float halfFadeDistance = 1.0f;

    [NoCSCode]
    public new const MaterialPriority priority = MaterialPriority.Heightfog;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x4A55D341)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class DebugMaterial : Material
  {
    [Pin2]
    public BooleanPin DarkMapPinValue;
    [Pin2("SkeletalMeshPin")]
    public BooleanPin SkeletalMeshPinValue;
    [Pin2]
    public DebugPin DebugPinValue;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x49547341)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class AIGeometryMaterialType : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.AddColor, OnOffState.Off, 127, OnOffState.On);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x49547344)]
  [MaterialFunc("TerrainMaterialFunc.inl")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(1)]
  public class TerrainMaterial : Material
  {
    [Description("UV координаты (можно подсмотреть в Maya) участка геометрии, который не нуждается в сшивке вершин")]
    public FloatRect grassRect;

    [FieldCategory("Frozen")]
    [Sampler(0, "DiffuseMapFrozen", true)]
    public SamplerEx A_DiffuseMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap));
    [FieldCategory("Normal")]
    [Sampler(1, "DiffuseMap", true)]
    public SamplerEx N_DiffuseMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap));
    [FieldCategory("Burned")]
    [Sampler(2, "DiffuseMapBurned", true)]
    public SamplerEx B_DiffuseMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap));

    [FieldCategory("Frozen")]
    [Sampler(3, true)]
    public SamplerEx FrozenNormalMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap), new HDRColor(2, 2, 2, 0), new HDRColor(-1, -1, -1, 0));
    [FieldCategory("Normal")]
    [Sampler(4, true)]
    public SamplerEx NormalNormalMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap), new HDRColor(2, 2, 2, 0), new HDRColor(-1, -1, -1, 0));
    [FieldCategory("Burned")]
    [Sampler(5, true)]
    public SamplerEx BurnedNormalMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap), new HDRColor(2, 2, 2, 0), new HDRColor(-1, -1, -1, 0));

    [FieldCategory("Frozen")]
    [Sampler(6, true)]
    public SamplerEx FrozenSpecularMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap), new HDRColor(1, 1, 1, 1), new HDRColor(0, 0, 0, 0));
    [FieldCategory("Normal")]
    [Sampler(7, true)]
    public SamplerEx NormalSpecularMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap), new HDRColor(1, 1, 1, 1), new HDRColor(0, 0, 0, 0));
    [FieldCategory("Burned")]
    [Sampler(8, true)]
    public SamplerEx BurnedSpecularMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap), new HDRColor(1, 1, 1, 1), new HDRColor(0, 0, 0, 0));

    [FieldCategory("Dark Map")]
    [Sampler(9, true)]
    public SamplerEx DarkMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap), new HDRColor(1, 1, 1, 1), new HDRColor(0, 0, 0, 0));

    [FieldCategory("Pins")]
    [Pin2]
    public BooleanPin NormalMapPinValue;
    [FieldCategory("Pins")]
    [Pin2]
    public BooleanPin ShadowReciverPinValue = BooleanPin.Present;
    [FieldCategory("Pins")]
    [Pin2("ShadowCasterPin")]
    public BooleanPin ShadowCasterPinValue = BooleanPin.Present;
    [FieldCategory("Pins")]
    [Pin2]
    public BooleanPin SpecularMapPinValue;
    [FieldCategory("Pins")]
    [Pin2]
    public BooleanPin EnvMapPinValue;
    [FieldCategory("Pins")]
    [Pin2]
    public BooleanPin DarkMapPinValue;
    [FieldCategory("Pins")]
    [Pin2]
    public TerrainUVSetPin TerrainUVSetPinValue;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  /*  
    [TypeId(0x50547340)]
    public class DefaultMaterial : Material
    {
      [Sampler( 0, "DiffuseMap" )]
      public Sampler DiffuseMap = new Sampler( 0, new SamplerState(TextureFilterType.Linear, TextureAddressType.Wrap ), new HDRColor( 1, 1, 1, 1 ), new HDRColor( 0, 0, 0, 0 ) );
      [Pin2( "DiffuseMapPin" )]
      public DiffuseMapPin DiffuseMapPin = DiffuseMapPin.DiffuseMapPresent;

      [Sampler( 1 )]
      public Sampler NormalMap = new Sampler( 1, new SamplerState(TextureFilterType.Linear, TextureAddressType.Wrap ), new HDRColor( 2, 2, 2, 0 ), new HDRColor( -1, -1, -1, 0 ) );
      [Pin2]
      public NormalMapPin NormalMapPin = NormalMapPin.NoNormalMap;

      public Vec2 someValue = new Vec2( 10.0f, 10.0f );

      public AlphaState alphaState = new AlphaState( true, 0, CompareFunction.Greater );
      public BlendState blendState = new BlendState( true, BlendFactor.ONE, BlendFactor.INVSRCALPHA );
      public DepthState depathState = new DepthState( true, false, CompareFunction.Always );

      [NoCSCode]
      public new const MaterialOldFlags flags = MaterialOldFlags.RequireAlphaBlending | MaterialOldFlags.CastsShadows;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
    [TypeId(0x50547342)]
    //[MaterialFunc( "DefaultMaterial2.inl", "TestFunction()", "TestFunction( int value )" )]
    public class DefaultMaterial2 : Material
    {
      public BlendState default_BlendState = new BlendState(true, BlendFactor.ONE, BlendFactor.ONE);

      [Sampler(0, "DiffuseMap")]
      public Sampler DiffuseMap = new Sampler( 0, new SamplerState(TextureFilterType.Linear, TextureAddressType.Wrap ), new HDRColor( 1, 1, 1, 1 ), new HDRColor( 0, 0, 0, 0 ) );
      [Pin2]
      public DiffuseMapPin DiffuseMapPin = DiffuseMapPin.DiffuseMapPresent;

      [Sampler( 1 )]
      public Sampler NormalMap = new Sampler( 1, new SamplerState(TextureFilterType.Linear, TextureAddressType.Wrap ), new HDRColor( 2, 2, 2, 0 ), new HDRColor( -1, -1, -1, 0 ) );
      [Pin2]
      public NormalMapPin NormalMapPin = NormalMapPin.NoNormalMap;
    }
  */

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId(0x1056F3C0)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class GrassMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);

    [FieldCategory("Frozen")]
    [Sampler(0)]
    public SamplerEx FrozenDiffuseMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap));
    [FieldCategory("Normal")]
    [Sampler(1)]
    public SamplerEx NormalDiffuseMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap));
    [FieldCategory("Burned")]
    [Sampler(2)]
    public SamplerEx BurnedDiffuseMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap));

    [FieldCategory("Pins")]
    [Pin2]
    public BooleanPin ShadowReciverPinValue = BooleanPin.Present;

    [FieldCategory("Blade")]
    public Vec2 bladeSize = new Vec2(0.75f, 0.75f);

    [FieldCategory("Animation")]
    public float elasticity = 0.75f;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId(0x9354BD01)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class TerrainHeightBuilderMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId(0x9E5574C0)]
  [MaterialFunc("WaterMaterial.inl")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(3)]
  public class WaterMaterial : Material
  {
    [FieldCategory("Pins")]
    [Pin2("CausticsTexturePin")]
    [NoCSCode]
    public BooleanPin CausticsTexturePinValue = BooleanPin.None;

    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public ShaderQualityPin ShaderQualityValue = ShaderQualityPin.Best;
  }

  [TypeId(0x3B686340)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(1)]
  public class WaterDummyMaterial : Material
  {
    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public BoolPin DualDepthPinValue = BoolPin.TRUE;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x9963DB80)]
  [MaterialFunc("EaselPaintMaterial.inl", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class BasicMaskMaterial : Material
  {
    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.On, 1, OnOffState.On);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Diffuse")]
    [Sampler(0)]
    public Sampler Diffuse = new Sampler(new SamplerState(TextureAddressType.Wrap));

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Mask")]
    [Sampler(3)]
    public Sampler Mask = new Sampler(new SamplerState(TextureAddressType.Wrap));

    [NoCSCode]
    public float opacity = 1.0f;

    [NoCSCode]
    public int isBlendModeOverrided = 0;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  public enum PaintMaterialModePin
  {
    Empty = 0,
    InWork = 1,
    Final = 2,
  }

  [TypeId(0x9963ED00)]
  [MaterialFunc("EaselPaintMaterial.inl", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(1)]
  public class PaintMaterial : Material
  {
    [Pin2("PackedMasksNumberPin")]
    public PackedMasksNumberPin masksNumber = PackedMasksNumberPin.PackedMasks1;

    [Pin2("PaintMaterialModePin")]
    public PaintMaterialModePin paintMode = PaintMaterialModePin.InWork;

    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.On, 1, OnOffState.On);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [Sampler(0)]
    public Sampler Draft = new Sampler(new SamplerState(TextureAddressType.Clamp));

    [Sampler(1)]
    public Sampler Background = new Sampler(new SamplerState(TextureAddressType.Clamp));

    [Sampler(2)]
    public Sampler BaseBackground = new Sampler(new SamplerState(TextureAddressType.Clamp));

    [Sampler(3)]
    public Sampler Complete = new Sampler(new SamplerState(TextureAddressType.Clamp));

    [Sampler(4)]
    public Sampler Mask = new Sampler(new SamplerState(TextureAddressType.Clamp));

    [NoCSCode]
    public float opacity = 1.0f;

    [NoCSCode]
    public int isBlendModeOverrided = 0;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [NonTerminal]
  [DBVersion(0)]
  [Custom("Social")]
  public class BaseUIMaterial : Material
  {
    public EUIImageDrawMode horizontalDrawMode = EUIImageDrawMode.Stretch;
    public EUIImageDrawMode verticalDrawMode = EUIImageDrawMode.Stretch;

    public IntPoint textureShift = new IntPoint();
    public IntPoint imageSize = new IntPoint();
    public IntPoint imageTileShift = new IntPoint();
    public IntPoint imageTileSize = new IntPoint();

    public BooleanPin UseAutosize = BooleanPin.Present;
  }

  public enum EUIImageDrawMode
  {
    Normal,
    Center,
    Stretch,
    Tile,
    StretchedTile,
  }

  public enum MaskingTypePin
  {
    NoMasking = 0,
    Masking = 1,
    InvertMasking = 2
  }

  [TypeId(0x9D656300)]
  [MaterialFunc("UIBaseMaterial.inl",
    "ModifyCoefs(const float coef3, const float coef4)",
    "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)",
    "ModifyStripesConstants(const float start, const float step1, const float step2, const float blendFactor1)",
    "ModifyStripesColor(const Render::HDRColor &color1, const Render::HDRColor &color2)")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  [Custom("Social")]
  public class UIBaseMaterial : BaseUIMaterial
  {
    [Sampler(0, "DiffuseMap")]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));
    [Sampler(1, "MaskMap")]
    public Sampler MaskMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    public HDRColor color1 = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
    public HDRColor color2 = new HDRColor(0.0f, 0.0f, 0.0f, 1.0f);

    public float coef1 = 0.0f;
    public float coef2 = 0.0f;

    [NoCSCode]
    public float coef3 = 0.0f;
    [NoCSCode]
    public float coef4 = 0.0f;
    [NoCSCode]
    public float stripesStart = 0.0f;
    [NoCSCode]
    public float stripesStep1 = 100.0f;
    [NoCSCode]
    public float stripesStep2 = 1000.0f;
    [NoCSCode]
    public float stripesBlendFactor1 = 0.0f;

    [Pin2("UseDiffuse")]
    public BooleanPin UseDiffuse = BooleanPin.None;

    [Pin2("Masking")]
    public MaskingTypePin Masking = MaskingTypePin.NoMasking;

    [Pin2("Gradient")]
    public BooleanPin Gradient = BooleanPin.None;

    [Pin2("Colorized")]
    public BooleanPin Colorized = BooleanPin.None;

    [Pin2("Stripes")]
    public BooleanPin Stripes = BooleanPin.None;

    public HDRColor colorStripe100 = new HDRColor(0.0f, 0.0f, 0.0f, 1.0f);
    public HDRColor colorStripe1000 = new HDRColor(1.0f, 0.68f, 0.19f, 1.0f);

    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.Off, 127, OnOffState.Off);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId(0x9D661300)]
  [UseTypeName("MTRL")]
  [MaterialFunc("UIGlassMaterial.inl")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class UIGlassMaterial : BaseUIMaterial
  {
    [Sampler(0, "BackgroundMap")]
    public Sampler BackgroundMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Sampler(1, "DiffuseMap")]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Sampler(2, "OverlayMap")]
    public Sampler OverlayMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Sampler(3, "ScreenMap")]
    public Sampler ScreenMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    public float OverlayOpacity = 1.0f;
    public float ScreenOpacity = 1.0f;

    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.Off, 127, OnOffState.Off);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId(0x9D6ABB80)]
  [UseTypeName("MTRL")]
  [MaterialFunc("UIButtonMaterial.inl")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class UIButtonMaterial : BaseUIMaterial
  {
    [Sampler(0, "BackgroundMap")]
    public Sampler BackgroundMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Sampler(1, "DiffuseMap")]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Sampler(2, "WaitForActivation")]
    public Sampler WaitForActMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Sampler(3, "LackOfMana")]
    public Sampler LackOfManaMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Sampler(4, "Pressed")]
    public Sampler PressedMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Sampler(5, "Highlight")]
    public Sampler HighlightMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Sampler(6, "ScreenMap")]
    public Sampler ScreenMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Pin2("WaitForActivationPin")]
    public BooleanPin WaitForActivationPin = BooleanPin.None;

    [Pin2("LackOfManaPin")]
    public BooleanPin LackOfManaPin = BooleanPin.None;

    [Pin2("PressedPin")]
    public BooleanPin PressedPin = BooleanPin.None;

    [Pin2("HighlightPin")]
    public BooleanPin HighlightPin = BooleanPin.None;

    [Pin2("DisablePin")]
    public BooleanPin DisablePin = BooleanPin.None;

    [Pin2("PassivePin")]
    public BooleanPin PassivePin = BooleanPin.None;

    [Pin2("UseDiffusePin")]
    public BooleanPin UseDiffusePin = BooleanPin.Present;

    public float ScreenOpacity = 1.0f;

    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.Off, 127, OnOffState.Off);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId(0x9D65A480)]
  [MaterialFunc("UIFontMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class UIFontMaterial : Material
  {
    [Sampler(0, "DiffuseMap")]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Pin2("UseDiffuse")]
    public BooleanPin UseDiffuse = BooleanPin.None;

    [Pin2("DrawContour")]
    public BooleanPin DrawContour = BooleanPin.None;

    public HDRColor PrimaryColor = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
    public HDRColor SecondaryColor = new HDRColor(0.0f, 0.0f, 0.0f, 1.0f);

    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.Off, 127, OnOffState.Off);
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  public enum FlashBlendModePin
  {
    _NORMAL, // in SWF Normal = 0 or 1. NORMAL - conflicts with HLSL semantic, thus _NORMAL

    LAYER,
    MULTIPLY,
    SCREEN,
    LIGHTEN,
    DARKEN,
    _DIFFERENCE,
    ADD,
    SUBTRACT,
    INVERT,
    ALPHA,
    ERASE,
    OVERLAY,
    HARDLIGHT,

    SHADER,
    COPY_BACKGRUOND
  }

  [TypeId(0x9D657440)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class UIFlashMaterial : Material
  {
    [Sampler(0, "DiffuseMap")]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    [Sampler(1, "DiffuseMap2")]
    public Sampler DiffuseMap2 = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Point));

    //    [Pin2("DebugMode")]
    //    public BooleanPin DebugMode = BooleanPin.None;

    [Pin2("UseDiffuse")]
    public BooleanPin UseDiffuse = BooleanPin.None;

    [Pin2("UseDiffuse2")]
    public BooleanPin UseDiffuse2 = BooleanPin.None;

    [Pin2("MorphShapes")]
    public BooleanPin MorphShapes = BooleanPin.None;

    [Pin2("ShaderForLines")]
    public BooleanPin ShaderForLines = BooleanPin.None;

    [Pin2("UseColorFilter")]
    public BooleanPin UseColorFilter = BooleanPin.None;

    [Pin2("Scale9Grid")]
    public BooleanPin Scale9Grid = BooleanPin.None;

    [Pin2("Scale9GridBitmap")]
    public BooleanPin Scale9GridBitmap = BooleanPin.None;

    [Pin2("FlashBlendModePin")]
    public FlashBlendModePin FlashBlendMode = FlashBlendModePin._NORMAL;

    public HDRColor CXFormMul = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
    public HDRColor CXFormAdd = new HDRColor(0.0f, 0.0f, 0.0f, 0.0f);
  }

  [TypeId(0x9D66EBC0)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [MaterialFunc("TestTownMaterial.inl")]
  [DBVersion(0)]
  public class TestTownMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState RenderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);

    [Sampler(0, "DiffuseMap")]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Clamp, MipFilterType.Linear));

    [Pin2("UseDiffuse")]
    public BooleanPin UseDiffuse = BooleanPin.None;

    [FieldCategory("Modificator")]
    public HDRColor outputMul = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Modificator")]
    public HDRColor outputAdd = new HDRColor(0.0f, 0.0f, 0.0f, 0.0f);
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  // наглый плагиат с Base material с единственным различием - шейдер
  [TypeId(0xC8667D00)]
  [MaterialFunc("DropMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)"
    , "ModifyReflectionColor(const Render::HDRColor& _color0, const Render::HDRColor& _color1, const Render::HDRColor& _color2, const Render::HDRColor& _color3)")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(3)]
  public class DropMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);

    [FieldCategory("States")]
    [NoCode]
    public new MaterialFlags renderFlags = MaterialFlags.ShadowReceiver;

    [FieldCategory("States")]
    [NoCode]
    public new const bool bShadowCastSupport = true;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Lighting")]
    public HDRColor diffuseColor = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Lighting")]
    public float lightingIntencity = 1.0f;

    [FieldCategory("Lighting")]
    public float ambientIntensity = 1.0f;

    [FieldCategory("Lighting")]
    public HDRColor additionalAmbient = new HDRColor(0.0f, 0.0f, 0.0f, 1.0f);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Diffuse")]
    [Sampler(0, "DiffuseMap", true)]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Wrap));

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Normal")]
    [Sampler(1, true)]
    public Sampler NormalMap = new Sampler(new SamplerState(TextureAddressType.Wrap));

    [FieldCategory("Normal")]
    [Pin2]
    public BooleanPin NormalMapPinValue = BooleanPin.None;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Specular")]
    [Sampler(2, true)]
    public SamplerEx SpecularMap = new SamplerEx(new SamplerState(TextureAddressType.Wrap), new HDRColor(1, 1, 1, 1), new HDRColor(0, 0, 0, 0));

    [FieldCategory("Specular")]
    [Pin2]
    public BooleanPin SpecularMapPinValue = BooleanPin.None;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Reflection")]
    [Sampler(3, true)]
    public SamplerCube ReflectionMap = new SamplerCube(new SamplerState(TextureAddressType.Wrap));

    [FieldCategory("Reflection")]
    [Pin2]
    public ReflectivityPin ReflectivityPinValue = ReflectivityPin.ReflectivityOff;

    [FieldCategory("Reflection")]
    [Pin2]
    public TextureColorizePin colorizeReflectionMap = TextureColorizePin.NoColor;

    [FieldCategory("Reflection")]
    public HDRColor reflectionMapColor0 = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Reflection")]
    public HDRColor reflectionMapColor1 = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Reflection")]
    public HDRColor reflectionMapColor2 = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Reflection")]
    public HDRColor reflectionMapColor3 = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Modificator")]
    public HDRColor outputMul = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Modificator")]
    public HDRColor outputAdd = new HDRColor(0.0f, 0.0f, 0.0f, 0.0f);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Pins")]
    [Pin2("SkeletalMeshPin")]
    public BooleanPin SkeletalMeshPinValue;

    [FieldCategory("Pins")]
    [Pin2]
    public LightModePin LightModePinValue = LightModePin.Diffuse;

    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public RenderModePin RenderModeValue = RenderModePin.RenderNormal;

    [NoCSCode]
    public int isBlendModeOverrided = 0;

    public float emissive = 0.0f;
    //public float opacity = 1.0f;
    // new
    public AnimatedFloat opacity = new AnimatedFloat(1.0f);
    //

    [FloatMinMax(0.0f, 1.0f)]
    public float reflectivityLerp = 0.0f;
    public float reflectivityAdd = 0.0f;
    public float reflectivityMul = 0.0f;

    public float specularPower = 10.0f;

    //public Vec2 uvSpeed;

    // new ....
    public AnimatedFloat uOffset1;
    public AnimatedFloat vOffset1;
    public AnimatedFloat uOffset2;
    public AnimatedFloat vOffset2;
    //
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x3D84CC00)]
  [MaterialFunc("SkyMaterial.inl")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class SkyMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);

    [FieldCategory("States")]
    [NoCode]
    public new MaterialFlags renderFlags = MaterialFlags.ReflectInWater;

    [NoCSCode]
    public new const MaterialPriority priority = MaterialPriority.Sky;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Diffuse")]
    [Sampler(0, "DiffuseMap", true)]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Wrap));

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Modificator")]
    public HDRColor outputMul = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Modificator")]
    public HDRColor outputAdd = new HDRColor(0.0f, 0.0f, 0.0f, 0.0f);

    //public Vec2 uvSpeed;

    // new ....
    public AnimatedFloat uOffset1;
    public AnimatedFloat vOffset1;
    public AnimatedFloat uOffset2;
    public AnimatedFloat vOffset2;
    //
  }

  [TypeId(0xA06B4B80)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  public class WaterMapMaterial : Material
  {
  }

  [TypeId(0x3B759340)]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(14)]
  public class RoadMaterial : Material
  {
    [FieldCategory("States")]
    [ReadOnly(true)]
    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.Off, 127, OnOffState.On);

    [Sampler(0, "RoadMap", true)]
    public Sampler RoadMap = new Sampler(new SamplerState(TextureAddressType.Wrap));

    [Sampler(1, "BorderMap", true)]
    public Sampler BorderMap = new Sampler(new SamplerState(TextureAddressType.Wrap));

    [FieldCategory("Pins")]
    [Pin2("TextureFitPinValue")]
    [NoCSCode]
    public BooleanPin TextureFitPinValue = BooleanPin.None;

    [FieldCategory("Pins")]
    [Pin2("DebugPinValue")]
    [NoCSCode]
    public BooleanPin DebugPinValue = BooleanPin.None;

    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public CachingPin CachingPinValue = CachingPin.Ordinary;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x3B78C340)]
  [MaterialFunc("WaterMaterial.inl")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(4)]
  public class SilhouetteMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);

    [FieldCategory("States")]
    [NoCode]
    public new MaterialFlags renderFlags = MaterialFlags.None;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [FieldCategory("Pins")]
    [Pin2("SkeletalMeshPin")]
    [NoCSCode]
    public BooleanPin SkeletalMeshPinValue;
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x3B7A5B80)]
  [MaterialFunc("CommonMaterialFunc.inl")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(2)]
  public class AOEMaterial : Material
  {
    [FieldCategory("States")]
    public RenderState renderState = new RenderState(BlendMode.LerpByAlpha, OnOffState.On, 0, OnOffState.On);

    [FieldCategory("Diffuse")]
    [Sampler(0)]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Clamp));

    [FieldCategory("Modificator")]
    public HDRColor primaryColor = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    [FieldCategory("Modificator")]
    public HDRColor secondaryColor = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);

    public float aspectRatio = 2.0f;

    [FieldCategory("Pins")]
    [Pin2("CustomizedGeometryPin")]
    [NoCSCode]
    public BooleanPin CustomizedGeometryPinValue;
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x3D82C581)]
  [MaterialFunc("ShadowMaterialFunc.inl")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(0)]
  [NoCSCode]
  public class ShadowMaterial : Material
  {
    public RenderState renderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [Sampler(0, "DiffuseMap", true)]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Wrap));
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [Pin2("SkeletalMeshPin")]
    [NoCSCode]
    public BooleanPin SkeletalMeshPinValue;

    //[FieldCategory("Pins")]
    //[Pin2]
    //[NoCSCode]
    //public BooleanPin OpacityPinValue = BooleanPin.None;

    [Pin2(Pin2.Runtime)]
    [NoCSCode]
    [NoCode]
    public BooleanPin InstancingValue = BooleanPin.None;

    //[NoCSCode]
    //public float opacity = 1.0f;
  }


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

  [TypeId(0x3D85DD40)]
  //[MaterialFunc("FullScreenMaterial.inl")]
  [UseTypeName("MTRL")]
  [MaterialGroup("BaseMaterial")]
  [DBVersion(2)]
  [NoCSCode]
  public class FullScreenMaterial : Material
  {
    public RenderState renderState = new RenderState(BlendMode.Off, OnOffState.Off, 127, OnOffState.On);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [Sampler(0, "DepthMap")]
    public Sampler DepthMap = new Sampler(new SamplerState(TextureAddressType.Clamp));
    [Sampler(1, "DiffuseMap")]
    public Sampler DiffuseMap = new Sampler(new SamplerState(TextureAddressType.Clamp));
    [Sampler(2, "BloomMap")]
    public Sampler BloomMap = new Sampler(new SamplerState(TextureAddressType.Clamp));
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    [Pin2("SharpPin")]
    [NoCSCode]
    public BooleanPin SharpPinValue;

    [Pin2("BloomPin")]
    [NoCSCode]
    public BooleanPin BloomPinValue;

    [Pin2("WarFogPin")]
    [NoCSCode]
    public BooleanPin WarFogPinValue;

    [Pin2("R2VBPin")]
    [NoCSCode]
    public BooleanPin R2VBPinValue;

    [Pin2("ColorCorrectPin")]
    [NoCSCode]
    public ColorCorrectPin ColorCorrectPinValue;
  }
}
