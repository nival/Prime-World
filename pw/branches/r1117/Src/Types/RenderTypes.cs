//#include "Render.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;

namespace Render.DBRender
{
	public enum CompareFunction
	{
		Never,
		Less,
		Equal,
		LessOrEqual,
		Greater,
		NotEqual,
		GreaterOrEqual,
		Always,
	}

	public enum BlendFactor
	{
		//ZERO,
		ONE,
		//SRCCOLOR,
		//INVSRCCOLOR,
		SRCALPHA,
		INVSRCALPHA,
		//DESTALPHA,
		//INVDESTALPHA,
		//DESTCOLOR,
		//INVDESTCOLOR,
		//SRCALPHASAT,
		//BOTHSRCALPHA,
		//BOTHINVSRCALPHA,
		//BLENDFACTOR,
		//INVBLENDFACTOR,
	}

	public enum FillMode
	{
		POINT,
		WIREFRAME,
		SOLID,
	}

	public enum CullingMode
	{
		NONE,
		CW,
		//CCW,
	}

  public enum OnOffState
  {
    Off = 0,
    On = 1,
  }

  public enum BlendMode
  {
    Off = 0,
    LerpByAlpha,
    PremultipliedLerp,
    AddColor,
    AddColorMulAlpha,
    MulColor,
    MulInvColor,
  }

  public enum ShadowBlendMode
  {
    LerpByAlpha,
    MulColor,
  }

  public enum WarFogType
  {
    SingleLayer,
    DualLayer,
  }

  [StateType]
  public class RenderState
  {
    public BlendMode  blendMode = BlendMode.Off;
    
    public OnOffState alphaTest = OnOffState.Off;

    [IntMinMax(0, 255)]
    public int alphaTestRef = 127;

    public OnOffState culling = OnOffState.On;

    public RenderState() {}
    public RenderState(BlendMode blendMode, OnOffState alphaTest, int alphaTestRef, OnOffState culling)
		{
			this.blendMode    = blendMode;
      this.alphaTest    = alphaTest;
      this.alphaTestRef = alphaTestRef;
      this.culling      = culling;
		}
  }

	public enum MinFilterType
	{
		Point = 0,
		Linear = 1,
		Anisotropic1x = 2,
    Anisotropic2x = 3,
    Anisotropic3x = 4,
    Anisotropic4x = 5,
    Anisotropic5x = 6,
    Anisotropic6x = 7,
  };

  public enum MagFilterType
  {
    Point = 0,
    Linear = 1,
  };

  public enum MipFilterType
  {
    None = 0,
    Point = 1,
    Linear = 2,
  };
  
  public enum TextureAddressType
	{
		Wrap = 0,
		Clamp = 1,
    Mirror = 2,
		Border = 3,
	};

	[NeedEqualOperator]
	public class SamplerState
	{
		public MinFilterType minFilter = MinFilterType.Linear;
		public MagFilterType magFilter = MagFilterType.Linear;
		public MipFilterType mipFilter = MipFilterType.Linear;

		public TextureAddressType addressU = TextureAddressType.Wrap;
		public TextureAddressType addressV = TextureAddressType.Wrap;
		public TextureAddressType addressW = TextureAddressType.Wrap;

		public SamplerState() { }

		public SamplerState( TextureAddressType address )
		{
			addressU = addressV = addressW = address;
		}

    public SamplerState(TextureAddressType address, MipFilterType _mipFilter)
    {
      addressU = addressV = addressW = address;
      mipFilter = _mipFilter;
    }
  }

  [FactoryBase( "Load", "Render::Texture", ReturnType = "CObj<Render::Texture>", Define = "!VISUAL_CUTTED" )]
  [FactoryBase( "LoadInPool", "Render::Texture", new string[] { "bool canBeVisualDegrade", "void * texturePoolId" }, ReturnType = "CObj<Render::Texture>", Define = "!VISUAL_CUTTED" )]
  public class TextureBase : DBResource
  {
  }

  //need importer
  [UseTypeName( "CUBE" )]
  public class CubeMap : DBResource
  {
    //[Description( "First of 6 cube images. ( <name>_0.<ext> )" )]
    //[DstFileArg( 0 )]
    //[SrcFile( "Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff" )]
    //public string srcFileName = new SrcFile();

    // Difference only on import operation. 
    // SrcFileName contains first of 6 sequential images in <name>_#.<ext> format starting from 0

    [SrcFile( "Image files", "*.tga" )]
    [Description( "+X Image source" )]
    public string srcFileName_0 = string.Empty;

    [SrcFile( "Image files", "*.tga" )]
    [Description( "-X Image source" )]
    public string srcFileName_1 = string.Empty;

    [SrcFile( "Image files", "*.tga" )]
    [Description( "+Y Image source" )]
    public string srcFileName_2 = string.Empty;

    [SrcFile( "Image files", "*.tga" )]
    [Description( "-Y Image source" )]
    public string srcFileName_3 = string.Empty;

    [SrcFile( "Image files", "*.tga" )]
    [Description( "+Z Image source" )]
    public string srcFileName_4 = string.Empty;

    [SrcFile( "Image files", "*.tga" )]
    [Description( "-Z Image source" )]
    public string srcFileName_5 = string.Empty;

    [NoCode]
    public EPixelFormat pixelFormat = EPixelFormat.DXT1;

    [NoCode]
    public EPower2 size = EPower2._256;

    [DstFile( "dds" )]
    public string textureFileName = string.Empty;
  }
  [Custom("Social")]
  public class Sampler
	{
		public SamplerState samplerState = new SamplerState();
		public DBPtr<TextureBase> texture;

		public Sampler() { }

		public Sampler(SamplerState samplerState)
		{
			this.samplerState = samplerState;
		}
	}

  public class SamplerCube
  {
    public SamplerState samplerState = new SamplerState();
    public DBPtr<CubeMap> texture;

    public SamplerCube() { }

    public SamplerCube(SamplerState samplerState)
    {
      this.samplerState = samplerState;
    }
  }

  public class SamplerEx
  {
    public SamplerState samplerState = new SamplerState();
    public DBPtr<TextureBase> texture;
    public HDRColor Multiplier = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
    public HDRColor Add        = new HDRColor(0.0f, 0.0f, 0.0f, 0.0f);

		public SamplerEx() { }

		public SamplerEx(SamplerState samplerState)
		{
			this.samplerState = samplerState;
		}

    public SamplerEx(SamplerState samplerState, HDRColor Multiplier, HDRColor Add)
		{
      this.samplerState = samplerState;
      this.Multiplier   = Multiplier;
			this.Add          = Add;
    }
  }

	public class Direction
	{
		public float Yaw = 0.0f;
		public float Pitch = 0.0f;

		public Direction() { }

		public Direction( float _Yaw, float _Pitch )
		{
			Yaw = _Yaw;
			Pitch = _Pitch;
		}
	}

	public enum Attenuation
	{
    Linear = 0,
    Normal,
    Slow,
    Fast,
    None,
	}

  [Flags]
  public enum PointLightFlags
  {
    None = 0,
    Day = (1 << 0),
    Night = (1 << 1),
  }

	public class PointLightInfo
	{
		public Attenuation attenuation = Attenuation.None;
		public Vec3 location = new Vec3( 0.0f, 0.0f, 0.0f );
		public float range = 0.0f;
		public HDRColor diffuse = new HDRColor( 1.0f, 1.0f, 1.0f, 1.0f );
    public float diffuseIntensity = 1.0f;
    public PointLightFlags flags = PointLightFlags.Day;
	}

  public enum ShadowMode
  {
    PCF = 0,
    SAESM,
    AnisoESM
  }

	[UseTypeName("LTEN")]
  [DBVersion(4)]
  public class LightEnvironment : DBResource
	{
		[FieldCategory("Light")]
		public Direction Light1Direction = new Direction( 45.0f, -60.0f );
    [FieldCategory("Light")]
    public Direction Light2Direction = new Direction( -45.0f, 60.0f );
    [FieldCategory("Light")]
		public HDRColor AmbientColor = new HDRColor( 0.5f, 0.5f, 0.5f, 1.0f );
		[FieldCategory("Light")]
		public HDRColor Light1DiffuseColor = new HDRColor( 1.0f, 1.0f, 1.0f, 1.0f );
    [FieldCategory("Light")]
    public HDRColor Light2DiffuseColor = new HDRColor( 0.3f, 0.3f, 0.3f, 0.3f );

    [FieldCategory("Light")]
    public DBPtr<CubeMap> environmentCubeMap;

    [FieldCategory("Light")]
    public DBPtr<CubeMap> lightingCubeMap;

    [FieldCategory("Light")]
    public HDRColor minBakedColor = new HDRColor(0.0f, 0.0f, 0.0f, 0.0f);

    [FieldCategory("Light")]
    // 255 means "255 times brighter than 1" when it comes to dynamic range compression
    public HDRColor maxBakedColor = new HDRColor(255.0f, 255.0f, 255.0f, 0.0f); 

    public List<float> lightingCubeMapSHCoeffs = new List<float>();

    [FieldCategory("Water")]
    public float WaterOscillationSpeedFactor = 1.0f;

    [FieldCategory("Water")]
    public HDRColor WaterReflColor0 = new HDRColor(0.1f, 0.5f, 0.6f, 0.0f);

    [FieldCategory("Water")]
    public HDRColor WaterReflColor1 = new HDRColor(0.0f, 0.4f, 0.7f, 0.0f);
		
		public int fullSizeX = 2048;
		public int fullSizeY = 2048;
    public int fullSizeSAX = 1024;
    public int fullSizeSAY = 1024;
    public ShadowMode shadowMode = ShadowMode.PCF;
    public float powerOfESM = 80.0f;
    [Description("Offset to the z-values of the shadows-texture, that helps ensure that shadow is rendered properly")]
    public float depthBias = 1.0e-4f;
    [Description("Coefficient multiplying the slope value that is added to bias")]
    public float biasSlope = 4.0f;
    public HDRColor shadowColor = new HDRColor(0.0f, 0.0f, 0.1f, 0.25f);
    public Direction shadowDirection = new Direction(45.0f, -60.0f);
    public ShadowBlendMode shadowBlendMode = ShadowBlendMode.LerpByAlpha;
    public float shadowLength = 20.0f;
    public float shadowFar = 60.0f;
    public float shadowFarRange = 10.0f;

    [FieldCategory("WarFog")]
    public WarFogType warFogType = WarFogType.SingleLayer;
    public Color warFogColor = new Color(20, 26, 31, 165);
    public Color warFogColor2 = new Color(20, 26, 31, 255);
    public HDRColor warFogColorForObjects = new HDRColor(0.08f, 0.1f, 0.12f, 0.35f);
    
    [FieldCategory( "WarFog" )]
    [Description( "visibility deep in meters. it describes how deep we see forest, stones etc" )]
    public float warFogObstacleVisibility = 6;

    [FieldCategory("WarFog")]
    [Description("Defines whether to use terrain heights delta for visibility tests.")]
    public bool warFogUseHeightsDelta = true;

    [FieldCategory("WarFog")]
    [Description("Defines the maximum terrain heights delta which passes visibility test (meters).")]
    public float warFogMaxHeightsDelta = 3.0f;
    [Description("Scales WarFog alpha while rendering MiniMap. Greater value means darker minimap.")]
    public float warFogMiniMapAlphaScale = 1.5f;
	}

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [DBVersion(0)]
  public class BakedLighting
  {
    [FieldCategory("Dynamic objects baked lighting")]
    [Description("X resolution of spherical harmonics grid")]
    public int dynObjLightingGridResX = 5;

    [FieldCategory("Dynamic objects baked lighting")]
    [Description("Y resolution of spherical harmonics grid")]
    public int dynObjLightingGridResY = 5;

    [FieldCategory("Dynamic objects baked lighting")]
    [Description("This value controls the effect of secondary lighting comes from environment (e.g. ground, trees, buildings, etc)")]
    public float renderedEnvironmentEffect = 0.5f;

    [FieldCategory("Dynamic objects baked lighting")]
    [Description("The range in which environment affects the lighting")]
    public float renderedEnvironmentRange = 10.0f;

    [DstFile( "shgrid" )]
    public string dynObjBakedLighting = string.Empty;

    [DstFile("vtxcolor")]
    public string vertexColorsFileName = string.Empty;
  }                                
}
