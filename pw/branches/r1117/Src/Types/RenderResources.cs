//#include "Materials.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using Render.DBRender;

namespace Render.DBRenderResources
{
	public class AABB
	{
    public AABB() {}
    public AABB(float minX_, float maxX_, float minY_, float maxY_, float minZ_, float maxZ_)
    {
      minX = minX_;
      maxX = maxX_;
      minY = minY_;
      maxY = maxY_;
      minZ = minZ_;
      maxZ = maxZ_;
    }

    ///
		public float minX;
		public float maxX;
		///
		public float minY;
		public float maxY;
		///
		public float minZ;
		public float maxZ;
	}

	public enum TextureType
	{
		Color = 0,
		Normal,
	}

	public enum MipLevel
	{
		AutoGenerate = 0,
		NoMips,
		//CustomMips,
	}

	public class TextureSize
	{
		public int width = 0;
		public int height = 0;
	}

	//need importer
	[UseTypeName( "TXTR" )]
  [FactoryImpl("Load", "Render::Texture2D", "TextureManager.h", CreateFunction = "(Render::Texture *)Render::LoadTexture2D")]
  [FactoryImpl("LoadInPool", "Render::Texture2D", "TextureManager.h", CreateFunction = "(Render::Texture *)Render::LoadTexture2DIntoPool")]
  [IndexField( "srcFileName" )]
  public class Texture : TextureBase
	{
		[DstFileArg( 0 )]
		[SrcFile( "Image files", "*.tga;*.bmp;*.png;*.gif;*.tiff" )]
		public string srcFileName = string.Empty;

		[ReadOnly( true )]
		[DstFileArg( 1 )]
		[NoCode]
		public string generatedFileName = string.Empty;

		[DstFile( "dds" )]
		public string textureFileName = string.Empty;

		[NoCode]
		public MipLevel mipLevelUsage = MipLevel.AutoGenerate;

		[NoCode]
		[IntMinMax(0, 13)]
		public int mipLevels = 0;

		[NoCode]
		[IntMinMax(0,12)]
		public int startMipLevel = 0;

		[NoCode]
		[Description( "Sharpen passes for each mip level. Up to 10 passes for up to 10 mip levels, starting from 1-st mip. Example: 1 0 2 0 : Sharpen 1-st mip 1 time; 2-nd not sharpen; 3-rd sharpen 2 times" )]
		public string mipSharpenPasses = "";

		[NoCode]
		[ReadOnly( true )]
		public TextureSize size;

		[NoCode]
		public TextureType textureType = TextureType.Color;

		[NoCode]
		public EPixelFormat pixelFormat = EPixelFormat.DXT1;
	}

	//need importer
	[TypeId( 0x9E5573C0 )]
	[UseTypeName( "STAT" )]
  [IndexField("geometryFileName")]
	public class StaticMesh : DBResource
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

		[NoCode]
		public int uvSetCount = 1;

		public List<DBPtr<Material>> materialsReferences = new List<DBPtr<Material>>();

		[ReadOnly( true )]
		public AABB aabb = new AABB();
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  public enum EAnGrTransactionKind
  {
    Uniform, 
    Parabolic3,
    RecParabolic3,
    Sine,
    RecSine,
    Spline,
    RecSpline,
  }

  public enum EAnGrTransactionUpdate
  {
    PoseToPose,
    AnimToPose,
    PoseToAnim,
    AnimToAnim,
  }

	public enum EAnGrNodeType
	{
		Normal,
		Dispatcher,
		SubNode
	}

	
  public class AnGrFlTransaction
  {
    [Description("Type of float transaction update")]
    [ReadOnly( true )]
    public EAnGrTransactionUpdate blending = EAnGrTransactionUpdate.PoseToAnim;

    [Description("Kind of transaction")]
    [ReadOnly( true )]
    public EAnGrTransactionKind kind = EAnGrTransactionKind.Uniform;

    [Description("Parameter 1")]
    [ReadOnly( true )]
    public AnGrFormula parA;

    [Description("Parameter 2")]
    [ReadOnly( true )]
    public AnGrFormula parB;

    [Description("Start parameter of interval")]
    [ReadOnly( true )]
    public AnGrFormula fromMin;

    [Description("Stop parameter of interval")]
    [ReadOnly( true )]
    public AnGrFormula fromMax;

    [Description("Destination virtPar of target node")]
    [ReadOnly( true )]
    public AnGrFormula toParam;

    [Description( "Transaction speed in seconds" )]
    [ReadOnly( true )]
    public float duration = 0.3f;

    //[ReadOnly( true )]
    public List<AnGrMarker> markers;

  }

  [TypeId(0x14591F84)]
  [UseTypeName("AGFT")]
  public class AnGrFlMultiTransaction //: AnGrTransactionData
  {
    [Description("Target node")]
    [ReadOnly( true )]
    public string targetNode = "";

    [Description("Probability")]
    [ReadOnly( true )]
    public float probability = 0.0f;

    //transaction can have several start end interval in that case in split into several normal one
    public AnGrFlTransaction parameters;
  }

  public class AnGrMacronode
  {
    [Description("Name of the node")]
    [ReadOnly( true )]
    public string nodeName = "";

		[Description( "Type of this node" )]
		[ReadOnly( true )]
		public EAnGrNodeType nodeType = EAnGrNodeType.Normal;

    [Description("Default next node name (can be this node ==> node is looped)")]
    [ReadOnly( true )]
    public string nextNode = "";

    [Description("Speed of the surface for this node")]
    [ReadOnly( true )]
    public float surfSpeedX = 0.0f;

    [Description("Speed of the surface for this node")]
    [ReadOnly( true )]
    public float surfSpeedY = 0.0f;

    //if it contains more than one sequence node is actually macronode
    [Description( "Name of animation" )]
    [ReadOnly( true )]
    public string sequenceName = "";

    [Description( "Start VPar of animation" )]
    [ReadOnly( true )]
    public AnGrFormula startPar;

    [Description( "Stop VPar of animation" )]
    [ReadOnly( true )]
    public AnGrFormula stopPar;

    [Description( "Sequence speed" )]
    [ReadOnly( true )]
    public AnGrFormula speed;


    //transactions from this node. Really they are not "simple" - they are "float" but now all transactions are float transactions
    [ReadOnly( true )]
    public List<AnGrFlMultiTransaction> simpleTransactions;

    [Description("X-position of node")]
    [ReadOnly( true )]
    public int posX = -1;

    [Description("Y-position of node")]
    [ReadOnly( true )]
    public int posY = -1;

    //[ReadOnly( true )]
    public List<AnGrMarker> markers;
  }

  public class AnGrExternalParameter
  {
    [Description("Name of the external parameter")]
    public string paramName = "CHANGE_NAME!";

    [Description("Default value")]
    public float defaultValue = 0.0f;
  }

  public class AnGrExternalParameterCoeff
  {
    [Description("Name of the external parameter")]
    public string name = "";

    [Description("Default value")]
    public float value = 1.0f;
  }

  public class AnGrFormula
  {
    public float value = 0f;
    public List<AnGrExternalParameterCoeff> coeffs;
  }

  public enum EAnGrMarkerOwner
  {
    ANGRM_NODE,
    ANGRM_TRANSACTION,
  }

  public class AnGrMarker
  {
    [Description("Name of the marker")]
    public string name = "newmarker";

    [Description("Virtual parameter of the marker: in [0..1]")]
    public float virtPar = 0.0f;
  }

  [TypeId(0x145573F8)]
  [UseTypeName("ANGR")]
  [DBVersion(0)]
  public class AnimGraphCreator : DBResource
  {
    public string defaultNode = "idle";
    [ReadOnly( true )]
    public List<AnGrMacronode> macroNodes;
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	[UseTypeName( "SKEL" )]
	public class Skeleton : DBResource
	{
		[SrcFile( "Maya files", "*.mb" )]
		[DstFileArg( 0 )]
		public string srcFileName = string.Empty;

		[NoCode]
		[DstFile( "mayaSkel" )]
		public string mayaFileName = string.Empty;

		[DstFile( "skel" )]
		public string skeletonFileName = string.Empty;

		[NoCode]
		[DstFileArg( 1 )]
		public string selection = string.Empty;

		public List<SkinPartBase> skins = new List<SkinPartBase>();

		public List<Animation> animations = new List<Animation>();

    public DBPtr<AnimGraphCreator> animGraph;

    public DBPtr<AnimGraphCreator> additionalGraph;

		public List<FaceFX> faceFXAnims = new List<FaceFX>();
}

	public class FaceFX
	{
		[SrcFile( "Face FX Animation files", "*.fxa" )]
		[DstFileArg( 0 )]
		public string srcFileName = string.Empty;

		[DstFile( "fxa" )]
		public string fxaFileName = string.Empty;
}

  [IndexField( "selection" )]
	public class SkinPartBase
	{
		[SrcFile( "Maya files", "*.mb" )]
		[DstFileArg( 0 )]
		public string srcFileName = string.Empty;

		[NoCode]
		[DstFile( "mayaSkin" )]
		public string mayaFileName = string.Empty;

		[DstFile( "skin" )]
		public string geometryFileName = string.Empty; // binary file represents several primitives [(VB, IB, VD) + (reindex)]

		[NoCode]
		[DstFileArg( 1 )]
		public string selection = string.Empty;

		[NoCode]
		public int uvSetCount = 1;

		[NoCode]
		public int jointsCountPerVertex = 4;

		public string skinPartName = string.Empty;

		public List<DBPtr<Material>> materialsReferences = new List<DBPtr<Material>>();
	}

	public class AnimKey
	{
		public float time = 0.0f;
		public string name = String.Empty;
	}

  [IndexField( "name" )]
	public class Animation
	{
		public string name;

		public List<AnimKey> animkeys;

		[SrcFile( "Maya files", "*.ma" )]
		[DstFileArg( 0 )]
		public string srcFileName = string.Empty;

		[NoCode]
		[DstFile( "mayaAnim" )]
		public string mayaFileName = string.Empty;

		[DstFile( "anim" )]
		public string animationFileName = string.Empty;

		[NoCode]
		public float compression = 0.0f;
	}

	// need importer (already done)
	[UseTypeName( "PART" )]
	public class ParticleFX : DBResource
	{
		[SrcFile( "Maya files", "*.mb" )]
		[DstFileArg( 0 )]
		public string srcFileName;

		[NoCode]
		[DstFile( "mayaPart" )]
		public string mayaFileName;

		[DstFile( "part" )]
		public string fxFileName;

		[NoCode]
		[DstFileArg( 1 )]
		public string selection = string.Empty;

		[NoCode]
		public float compression = 2.0f;
	};

	public class UVPair
	{
		public Vec2 uvTopLeft;
		public Vec2 uvBottomRight;
	}

	// need importer
	// 	public class ParticleFXInstance : DBResource
	// 	{
	// 		public DBPtr<ParticleFX> particle;
	// 
	// 		[NoCode]
	// 		public List<DBPtr<Texture>> textures = new List<DBPtr<Texture>>();
	// 
	// 		public DBPtr<MaterialType> material;
	// 
	// 		public List<UVPair> uvPairs = new List<UVPair>();
	// 
	// 		public bool worldSpace;
	// 	};

	public class OmniLight : DBResource
	{
		public HDRColor diffuseColor;
		public HDRColor specularColor;
		//[ FloatMinMax(0.001f, 10000 )]
		public float radius = 1;
	}

  [Flags]
  public enum EGeometryUsageFlags
  {
    None = 0,
    Lighting = 1,      // VertexFormat += Normals
    NormalMapping = 2, // VertexFormat += TBN
    VertexColors = 4   // VertexFormat += VertexColors
  }

  [TypeId(0xC867EC41)]
  public class TgaTextureName
  {
    [SrcFile("Image files", "*.tga")]
    public string name = string.Empty;
  }

  [TypeId(0xC867EC40)]
  public class PaintPackedMasks : DBResource
  {
    [NoCode]
    public List<TgaTextureName> masks;

    [NoCode]
    public EPower2 size = EPower2._256;

    [ReadOnly( true )]
    public List<DBPtr<Texture>> packedMasks;
  }

  public class FlatSplineControlPointDesc
  {
    public Vec2 location;
    public float width = 10f;
  }

  public class Spline3DControlPointDesc
  {
      public Vec3 rotation;
      public Vec3 position;
      public float tension = 0.0f;
  }

  public class FlatSplineDesc
  {
    public List<FlatSplineControlPointDesc> points;
    public bool HasWidth = false;
    public bool IsCircle = false;
    public bool AbsolutePosition = false;
  }

  public class FullScreenFXParams
  {
    // RGB levels
    public Vec3 InMin = new Vec3(0, 0, 0);
    public Vec3 InMax = new Vec3(255, 255, 255);
    public Vec3 OutMin = new Vec3(0, 0, 0);
    public Vec3 OutMax = new Vec3(255, 255, 255);
    public Vec3 Gamma = new Vec3(0, 0, 0);

    // color cast
    public HDRColor Color = new HDRColor(1.0f, 1.0f, 1.0f, 1.0f);
    public float ColorCastCoef = 0.0f;

    // sharp
    public float SharpPixelSize = 1.0f;
    public float SharpCoef = 0.0f;
  }
}
