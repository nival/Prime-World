// Automatically generated file, don't change it manually!
using System;
using System.Collections.Generic;
using System.ComponentModel;

using libdb;
using libdb.DB;
using libdb.IO;
using libdb.UndoRedo;
using libdb.Diagnostics;
using libdb.Animated;

namespace DBTypes
{
public enum Attenuation
{
	Linear = 0,
	Normal = 1,
	Slow = 2,
	Fast = 3,
	None = 4,
};

public enum BlendFactor
{
	ONE = 0,
	SRCALPHA = 1,
	INVSRCALPHA = 2,
};

public enum BlendMode
{
	Off = 0,
	LerpByAlpha = 1,
	PremultipliedLerp = 2,
	AddColor = 3,
	AddColorMulAlpha = 4,
	MulColor = 5,
	MulInvColor = 6,
};

public enum BooleanPin
{
	None = 0,
	Present = 1,
};

public enum BoolPin
{
	FALSE = 0,
	TRUE = 1,
};

public enum CachingPin
{
	Ordinary = 0,
	Fill = 1,
	Use = 2,
	Use2 = 3,
	Use3 = 4,
};

public enum ColorCorrectPin
{
	OFF = 0,
	ON = 1,
	NO_GAMMA = 2,
	DESATURATE_ONLY = 3,
};

public enum CompareFunction
{
	Never = 0,
	Less = 1,
	Equal = 2,
	LessOrEqual = 3,
	Greater = 4,
	NotEqual = 5,
	GreaterOrEqual = 6,
	Always = 7,
};

public enum CullingMode
{
	NONE = 0,
	CW = 1,
};

public enum DebugPin
{
	SimpleShading = 0,
	ShowNormals = 1,
	ShowMipMaps = 2,
};

public enum DecalModePin
{
	Standard = 0,
	DualDepth = 1,
	ZDecode = 2,
};

public enum DiffuseAlphaMixPin
{
	AlphaMixTex1 = 0,
	AlphaMixAddSmooth = 1,
	AlphaMixMul = 2,
};

public enum DiffuseColorMixPin
{
	ColorMixAdd = 0,
	ColorMixAddWithAlpha = 1,
	ColorMixLerp = 2,
	ColorMixMul = 3,
};

public enum DiffuseMapCountPin
{
	NoDiffuseMap = 0,
	BaseDiffuseMap = 1,
	BothDiffuseMaps = 2,
};

public enum DistortionPin
{
	DistortNone = 0,
	DistortMap = 1,
	DistortNoise = 2,
};

public enum EEmissivePin
{
	EmissiveOff = 0,
	EmissiveFromAlpha = 1,
	EmissiveFromSpecular = 2,
};

public enum ELightEnvironment
{
	Day = 0,
	Night = 1,
};

public enum EPixelFormat
{
	RGBA = 0,
	DXT1 = 1,
	DXT5 = 2,
	L8 = 3,
};

[NoCode]
public enum EPower2
{
	_4 = 0,
	_8 = 1,
	_16 = 2,
	_32 = 3,
	_64 = 4,
	_128 = 5,
	_256 = 6,
	_512 = 7,
	_1024 = 8,
	_2048 = 9,
	_4096 = 10,
};

public enum EUIImageDrawMode
{
	Normal = 0,
	Center = 1,
	Stretch = 2,
	Tile = 3,
	StretchedTile = 4,
};

public enum FillMode
{
	POINT = 0,
	WIREFRAME = 1,
	SOLID = 2,
};

public enum FlashBlendModePin
{
	_NORMAL = 0,
	LAYER = 1,
	MULTIPLY = 2,
	SCREEN = 3,
	LIGHTEN = 4,
	DARKEN = 5,
	_DIFFERENCE = 6,
	ADD = 7,
	SUBTRACT = 8,
	INVERT = 9,
	ALPHA = 10,
	ERASE = 11,
	OVERLAY = 12,
	HARDLIGHT = 13,
	SHADER = 14,
	COPY_BACKGRUOND = 15,
};

public enum LightingPin
{
	LightingSH = 0,
	LightingInstancedSH = 1,
	LightingBaked = 2,
	LightingDynamic = 3,
	LightingDynamic1Point = 4,
	LightingDynamic2Point = 5,
	LightingDynamic3Point = 6,
	LightingDynamic4Point = 7,
};

public enum LightModePin
{
	Diffuse = 0,
	DiffuseOpacity = 1,
	DiffuseSpecular = 2,
	DiffuseSpecularOpacity = 3,
	DiffuseEmissive = 4,
	DiffuseSpecularEmissive = 5,
	DiffuseSpecularToEmissive = 6,
};

public enum MADPin
{
	NoMAD = 0,
	MADEnabled = 1,
};

public enum MagFilterType
{
	Point = 0,
	Linear = 1,
};

public enum MaskingTypePin
{
	NoMasking = 0,
	Masking = 1,
	InvertMasking = 2,
};

[Flags]
public enum MaterialFlags
{
	None = 0,
	ShadowCaster = 1,
	ShadowReceiver = 2,
	ReflectInWater = 4,
};

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

public enum MipFilterType
{
	None = 0,
	Point = 1,
	Linear = 2,
};

public enum OnOffState
{
	Off = 0,
	On = 1,
};

public enum OpacityAndEmissiveModePin
{
	Simple = 0,
	AdditiveOpacity = 1,
	BlendOpacity = 2,
	Emissive = 3,
};

public enum OpacityPin
{
	Opaque = 0,
	AlphaOpacity = 1,
	ColorOpacity = 2,
};

public enum OrientTypePin
{
	NoneType = 0,
	AxisType = 1,
	SpeedType = 2,
	PlaneType = 3,
};

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
};

public enum PaintMaterialModePin
{
	Empty = 0,
	InWork = 1,
	Final = 2,
};

[Flags]
public enum PointLightFlags
{
	None = 0,
	Day = 1,
	Night = 2,
};

public enum ReflectivityPin
{
	ReflectivityOff = 0,
	ReflectivitySimple = 1,
	ReflectivityFromNormalMap = 2,
	ReflectivityFromSpecularMap = 3,
};

public enum RenderModePin
{
	RenderNormal = 0,
	RenderToShadow = 1,
	RenderShapeOnly = 2,
};

public enum ShaderQualityPin
{
	Best = 0,
	Fast = 1,
};

public enum ShadowBlendMode
{
	LerpByAlpha = 0,
	MulColor = 1,
};

public enum ShadowMode
{
	PCF = 0,
	SAESM = 1,
	AnisoESM = 2,
};

public enum TerrainUVSetPin
{
	Global = 0,
	Local = 1,
};

public enum TextureAddressType
{
	Wrap = 0,
	Clamp = 1,
	Mirror = 2,
	Border = 3,
};

public enum TextureColorizePin
{
	NoColor = 0,
	AddColoredAlpha = 1,
	MulColorByAlpha = 2,
	ColorForEveryChanel = 3,
	TestColor = 4,
};

public enum TextureCountPin
{
	Count1 = 0,
	Count2 = 1,
	Count3 = 2,
	Count4 = 3,
};

public enum WarFogType
{
	SingleLayer = 0,
	DualLayer = 1,
};

[DBVersion(0)]
public class BakedLighting : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BakedLighting __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _dynObjLightingGridResX;
	private UndoRedo<int> _dynObjLightingGridResY;
	private UndoRedo<float> _renderedEnvironmentEffect;
	private UndoRedo<float> _renderedEnvironmentRange;

	[Category( "Dynamic objects baked lighting" )]
	[Description( "X resolution of spherical harmonics grid" )]
	public int dynObjLightingGridResX { get { return _dynObjLightingGridResX.Get(); } set { _dynObjLightingGridResX.Set( value ); } }

	[Category( "Dynamic objects baked lighting" )]
	[Description( "Y resolution of spherical harmonics grid" )]
	public int dynObjLightingGridResY { get { return _dynObjLightingGridResY.Get(); } set { _dynObjLightingGridResY.Set( value ); } }

	[Category( "Dynamic objects baked lighting" )]
	[Description( "This value controls the effect of secondary lighting comes from environment (e.g. ground, trees, buildings, etc)" )]
	public float renderedEnvironmentEffect { get { return _renderedEnvironmentEffect.Get(); } set { _renderedEnvironmentEffect.Set( value ); } }

	[Category( "Dynamic objects baked lighting" )]
	[Description( "The range in which environment affects the lighting" )]
	public float renderedEnvironmentRange { get { return _renderedEnvironmentRange.Get(); } set { _renderedEnvironmentRange.Set( value ); } }

	[DstFile("shgrid")]
	public string dynObjBakedLighting { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "shgrid"
	); } }
	[DstFile("vtxcolor")]
	public string vertexColorsFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  GetOwner().DBId
			, "vtxcolor"
	); } }
	private void Initialize( DBResource owner )
	{
		_dynObjLightingGridResX = new UndoRedo<int>( owner, 5 );
		_dynObjLightingGridResY = new UndoRedo<int>( owner, 5 );
		_renderedEnvironmentEffect = new UndoRedo<float>( owner, 0.5f );
		_renderedEnvironmentRange = new UndoRedo<float>( owner, 10.0f );
		_dynObjLightingGridResX.Changed += FireChangedEvent;
		_dynObjLightingGridResY.Changed += FireChangedEvent;
		_renderedEnvironmentEffect.Changed += FireChangedEvent;
		_renderedEnvironmentRange.Changed += FireChangedEvent;
	}

	public BakedLighting()
	{
		Initialize( GetOwner() );
	}

	public BakedLighting( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BakedLighting( DBResource owner, BakedLighting source )
		: this(owner, source, true){}

	protected BakedLighting( DBResource owner, BakedLighting source, bool fireEvent )
	{
		_dynObjLightingGridResX = new UndoRedo<int>( owner, source.dynObjLightingGridResX );
		_dynObjLightingGridResY = new UndoRedo<int>( owner, source.dynObjLightingGridResY );
		_renderedEnvironmentEffect = new UndoRedo<float>( owner, source.renderedEnvironmentEffect );
		_renderedEnvironmentRange = new UndoRedo<float>( owner, source.renderedEnvironmentRange );
		_dynObjLightingGridResX.Changed += FireChangedEvent;
		_dynObjLightingGridResY.Changed += FireChangedEvent;
		_renderedEnvironmentEffect.Changed += FireChangedEvent;
		_renderedEnvironmentRange.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BakedLighting source = _source as BakedLighting;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BakedLighting" );
		dynObjLightingGridResX = source.dynObjLightingGridResX;
		dynObjLightingGridResY = source.dynObjLightingGridResY;
		renderedEnvironmentEffect = source.renderedEnvironmentEffect;
		renderedEnvironmentRange = source.renderedEnvironmentRange;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BakedLighting newParent = _newParent as BakedLighting;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_dynObjLightingGridResX.SetParent( newParent == null ? null : newParent._dynObjLightingGridResX );
		_dynObjLightingGridResY.SetParent( newParent == null ? null : newParent._dynObjLightingGridResY );
		_renderedEnvironmentEffect.SetParent( newParent == null ? null : newParent._renderedEnvironmentEffect );
		_renderedEnvironmentRange.SetParent( newParent == null ? null : newParent._renderedEnvironmentRange );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_dynObjLightingGridResX.Reset();
		_dynObjLightingGridResY.Reset();
		_renderedEnvironmentEffect.Reset();
		_renderedEnvironmentRange.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_dynObjLightingGridResX.IsDerivedFromParent()
			&& _dynObjLightingGridResY.IsDerivedFromParent()
			&& _renderedEnvironmentEffect.IsDerivedFromParent()
			&& _renderedEnvironmentRange.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "dynObjLightingGridResX" )
			_dynObjLightingGridResX.Reset();
		else if ( fieldName == "dynObjLightingGridResY" )
			_dynObjLightingGridResY.Reset();
		else if ( fieldName == "renderedEnvironmentEffect" )
			_renderedEnvironmentEffect.Reset();
		else if ( fieldName == "renderedEnvironmentRange" )
			_renderedEnvironmentRange.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "dynObjLightingGridResX" )
			return _dynObjLightingGridResX.IsDerivedFromParent();
		if ( fieldName == "dynObjLightingGridResY" )
			return _dynObjLightingGridResY.IsDerivedFromParent();
		if ( fieldName == "renderedEnvironmentEffect" )
			return _renderedEnvironmentEffect.IsDerivedFromParent();
		if ( fieldName == "renderedEnvironmentRange" )
			return _renderedEnvironmentRange.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class Direction : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Direction __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _Yaw;
	private UndoRedo<float> _Pitch;

	public float Yaw { get { return _Yaw.Get(); } set { _Yaw.Set( value ); } }

	public float Pitch { get { return _Pitch.Get(); } set { _Pitch.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_Yaw = new UndoRedo<float>( owner, 0.0f );
		_Pitch = new UndoRedo<float>( owner, 0.0f );
		_Yaw.Changed += FireChangedEvent;
		_Pitch.Changed += FireChangedEvent;
	}

	public Direction()
	{
		Initialize( GetOwner() );
	}

	public Direction( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Direction( DBResource owner, Direction source )
		: this(owner, source, true){}

	protected Direction( DBResource owner, Direction source, bool fireEvent )
	{
		_Yaw = new UndoRedo<float>( owner, source.Yaw );
		_Pitch = new UndoRedo<float>( owner, source.Pitch );
		_Yaw.Changed += FireChangedEvent;
		_Pitch.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Direction source = _source as Direction;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Direction" );
		Yaw = source.Yaw;
		Pitch = source.Pitch;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Direction newParent = _newParent as Direction;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Yaw.SetParent( newParent == null ? null : newParent._Yaw );
		_Pitch.SetParent( newParent == null ? null : newParent._Pitch );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Yaw.Reset();
		_Pitch.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Yaw.IsDerivedFromParent()
			&& _Pitch.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Yaw" )
			_Yaw.Reset();
		else if ( fieldName == "Pitch" )
			_Pitch.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Yaw" )
			return _Yaw.IsDerivedFromParent();
		if ( fieldName == "Pitch" )
			return _Pitch.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class MaterialParameterDescriptor : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MaterialParameterDescriptor __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private UndoRedo<int> _presentDefineIndex;
	private UndoRedoList<int> _presentValues;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public int presentDefineIndex { get { return _presentDefineIndex.Get(); } set { _presentDefineIndex.Set( value ); } }

	public libdb.IChangeableList<int> presentValues { get { return _presentValues; } set { _presentValues.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_presentDefineIndex = new UndoRedo<int>( owner, 0 );
		_presentValues = new UndoRedoList<int>( owner );
		_name.Changed += FireChangedEvent;
		_presentDefineIndex.Changed += FireChangedEvent;
		_presentValues.Changed += FireChangedEvent;
	}

	public MaterialParameterDescriptor()
	{
		Initialize( GetOwner() );
	}

	public MaterialParameterDescriptor( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MaterialParameterDescriptor( DBResource owner, MaterialParameterDescriptor source )
		: this(owner, source, true){}

	protected MaterialParameterDescriptor( DBResource owner, MaterialParameterDescriptor source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_presentDefineIndex = new UndoRedo<int>( owner, source.presentDefineIndex );
		_presentValues = new UndoRedoList<int>( owner );
		_presentValues.Assign( source.presentValues );
		_name.Changed += FireChangedEvent;
		_presentDefineIndex.Changed += FireChangedEvent;
		_presentValues.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MaterialParameterDescriptor source = _source as MaterialParameterDescriptor;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MaterialParameterDescriptor" );
		name = source.name;
		presentDefineIndex = source.presentDefineIndex;
		presentValues = source.presentValues;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MaterialParameterDescriptor newParent = _newParent as MaterialParameterDescriptor;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_presentDefineIndex.SetParent( newParent == null ? null : newParent._presentDefineIndex );
		_presentValues.SetParent( newParent == null ? null : newParent._presentValues );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_presentDefineIndex.Reset();
		_presentValues.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _presentDefineIndex.IsDerivedFromParent()
			&& _presentValues.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "presentDefineIndex" )
			_presentDefineIndex.Reset();
		else if ( fieldName == "presentValues" )
			_presentValues.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "presentDefineIndex" )
			return _presentDefineIndex.IsDerivedFromParent();
		if ( fieldName == "presentValues" )
			return _presentValues.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class PointLightInfo : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PointLightInfo __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<Attenuation> _attenuation;
	private Vec3 _location;
	private UndoRedo<float> _range;
	private HDRColor _diffuse;
	private UndoRedo<float> _diffuseIntensity;
	private UndoRedo<PointLightFlags> _flags;

	public Attenuation attenuation { get { return _attenuation.Get(); } set { _attenuation.Set( value ); } }

	public Vec3 location { get { return _location; } set { _location.Assign( value ); } }

	public float range { get { return _range.Get(); } set { _range.Set( value ); } }

	public HDRColor diffuse { get { return _diffuse; } set { _diffuse.Assign( value ); } }

	public float diffuseIntensity { get { return _diffuseIntensity.Get(); } set { _diffuseIntensity.Set( value ); } }

	public PointLightFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_attenuation = new UndoRedo<Attenuation>( owner, Attenuation.None );
		_location = new Vec3( owner );
		_range = new UndoRedo<float>( owner, 0.0f );
		HDRColor __diffuse = new HDRColor(); // Construct default object for diffuse
		__diffuse.R = 1.0f;
		__diffuse.G = 1.0f;
		__diffuse.B = 1.0f;
		_diffuse = new HDRColor( owner, __diffuse );
		_diffuseIntensity = new UndoRedo<float>( owner, 1.0f );
		_flags = new UndoRedo<PointLightFlags>( owner, PointLightFlags.Day );
		_attenuation.Changed += FireChangedEvent;
		_location.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_diffuse.Changed += FireChangedEvent;
		_diffuseIntensity.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
	}

	public PointLightInfo()
	{
		Initialize( GetOwner() );
	}

	public PointLightInfo( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PointLightInfo( DBResource owner, PointLightInfo source )
		: this(owner, source, true){}

	protected PointLightInfo( DBResource owner, PointLightInfo source, bool fireEvent )
	{
		_attenuation = new UndoRedo<Attenuation>( owner, source.attenuation );
		_location = new Vec3( owner, source.location );
		_range = new UndoRedo<float>( owner, source.range );
		_diffuse = new HDRColor( owner, source.diffuse );
		_diffuseIntensity = new UndoRedo<float>( owner, source.diffuseIntensity );
		_flags = new UndoRedo<PointLightFlags>( owner, source.flags );
		_attenuation.Changed += FireChangedEvent;
		_location.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_diffuse.Changed += FireChangedEvent;
		_diffuseIntensity.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PointLightInfo source = _source as PointLightInfo;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PointLightInfo" );
		attenuation = source.attenuation;
		location = source.location;
		range = source.range;
		diffuse = source.diffuse;
		diffuseIntensity = source.diffuseIntensity;
		flags = source.flags;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PointLightInfo newParent = _newParent as PointLightInfo;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_attenuation.SetParent( newParent == null ? null : newParent._attenuation );
		_location.SetParent( newParent == null ? null : newParent._location );
		_range.SetParent( newParent == null ? null : newParent._range );
		_diffuse.SetParent( newParent == null ? null : newParent._diffuse );
		_diffuseIntensity.SetParent( newParent == null ? null : newParent._diffuseIntensity );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_attenuation.Reset();
		_location.Reset();
		_range.Reset();
		_diffuse.Reset();
		_diffuseIntensity.Reset();
		_flags.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_attenuation.IsDerivedFromParent()
			&& _location.IsDerivedFromParent()
			&& _range.IsDerivedFromParent()
			&& _diffuse.IsDerivedFromParent()
			&& _diffuseIntensity.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "attenuation" )
			_attenuation.Reset();
		else if ( fieldName == "location" )
			_location.Reset();
		else if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "diffuse" )
			_diffuse.Reset();
		else if ( fieldName == "diffuseIntensity" )
			_diffuseIntensity.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "attenuation" )
			return _attenuation.IsDerivedFromParent();
		if ( fieldName == "location" )
			return _location.IsDerivedFromParent();
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "diffuse" )
			return _diffuse.IsDerivedFromParent();
		if ( fieldName == "diffuseIntensity" )
			return _diffuseIntensity.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[StateType]
public class RenderState : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RenderState __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<BlendMode> _blendMode;
	private UndoRedo<OnOffState> _alphaTest;
	private UndoRedo<int> _alphaTestRef;
	private UndoRedo<OnOffState> _culling;

	public BlendMode blendMode { get { return _blendMode.Get(); } set { _blendMode.Set( value ); } }

	public OnOffState alphaTest { get { return _alphaTest.Get(); } set { _alphaTest.Set( value ); } }

	[IntMinMax(0, 255)]
	public int alphaTestRef { get { return _alphaTestRef.Get(); } set { _alphaTestRef.Set( value ); } }

	public OnOffState culling { get { return _culling.Get(); } set { _culling.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_blendMode = new UndoRedo<BlendMode>( owner, BlendMode.Off );
		_alphaTest = new UndoRedo<OnOffState>( owner, OnOffState.Off );
		_alphaTestRef = new UndoRedo<int>( owner, 127 );
		_culling = new UndoRedo<OnOffState>( owner, OnOffState.On );
		_blendMode.Changed += FireChangedEvent;
		_alphaTest.Changed += FireChangedEvent;
		_alphaTestRef.Changed += FireChangedEvent;
		_culling.Changed += FireChangedEvent;
	}

	public RenderState()
	{
		Initialize( GetOwner() );
	}

	public RenderState( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RenderState( DBResource owner, RenderState source )
		: this(owner, source, true){}

	protected RenderState( DBResource owner, RenderState source, bool fireEvent )
	{
		_blendMode = new UndoRedo<BlendMode>( owner, source.blendMode );
		_alphaTest = new UndoRedo<OnOffState>( owner, source.alphaTest );
		_alphaTestRef = new UndoRedo<int>( owner, source.alphaTestRef );
		_culling = new UndoRedo<OnOffState>( owner, source.culling );
		_blendMode.Changed += FireChangedEvent;
		_alphaTest.Changed += FireChangedEvent;
		_alphaTestRef.Changed += FireChangedEvent;
		_culling.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RenderState source = _source as RenderState;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RenderState" );
		blendMode = source.blendMode;
		alphaTest = source.alphaTest;
		alphaTestRef = source.alphaTestRef;
		culling = source.culling;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RenderState newParent = _newParent as RenderState;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_blendMode.SetParent( newParent == null ? null : newParent._blendMode );
		_alphaTest.SetParent( newParent == null ? null : newParent._alphaTest );
		_alphaTestRef.SetParent( newParent == null ? null : newParent._alphaTestRef );
		_culling.SetParent( newParent == null ? null : newParent._culling );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_blendMode.Reset();
		_alphaTest.Reset();
		_alphaTestRef.Reset();
		_culling.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_blendMode.IsDerivedFromParent()
			&& _alphaTest.IsDerivedFromParent()
			&& _alphaTestRef.IsDerivedFromParent()
			&& _culling.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "blendMode" )
			_blendMode.Reset();
		else if ( fieldName == "alphaTest" )
			_alphaTest.Reset();
		else if ( fieldName == "alphaTestRef" )
			_alphaTestRef.Reset();
		else if ( fieldName == "culling" )
			_culling.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "blendMode" )
			return _blendMode.IsDerivedFromParent();
		if ( fieldName == "alphaTest" )
			return _alphaTest.IsDerivedFromParent();
		if ( fieldName == "alphaTestRef" )
			return _alphaTestRef.IsDerivedFromParent();
		if ( fieldName == "culling" )
			return _culling.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[NeedEqualOperator]
public class SamplerState : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SamplerState __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<MinFilterType> _minFilter;
	private UndoRedo<MagFilterType> _magFilter;
	private UndoRedo<MipFilterType> _mipFilter;
	private UndoRedo<TextureAddressType> _addressU;
	private UndoRedo<TextureAddressType> _addressV;
	private UndoRedo<TextureAddressType> _addressW;

	public MinFilterType minFilter { get { return _minFilter.Get(); } set { _minFilter.Set( value ); } }

	public MagFilterType magFilter { get { return _magFilter.Get(); } set { _magFilter.Set( value ); } }

	public MipFilterType mipFilter { get { return _mipFilter.Get(); } set { _mipFilter.Set( value ); } }

	public TextureAddressType addressU { get { return _addressU.Get(); } set { _addressU.Set( value ); } }

	public TextureAddressType addressV { get { return _addressV.Get(); } set { _addressV.Set( value ); } }

	public TextureAddressType addressW { get { return _addressW.Get(); } set { _addressW.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minFilter = new UndoRedo<MinFilterType>( owner, MinFilterType.Linear );
		_magFilter = new UndoRedo<MagFilterType>( owner, MagFilterType.Linear );
		_mipFilter = new UndoRedo<MipFilterType>( owner, MipFilterType.Linear );
		_addressU = new UndoRedo<TextureAddressType>( owner, TextureAddressType.Wrap );
		_addressV = new UndoRedo<TextureAddressType>( owner, TextureAddressType.Wrap );
		_addressW = new UndoRedo<TextureAddressType>( owner, TextureAddressType.Wrap );
		_minFilter.Changed += FireChangedEvent;
		_magFilter.Changed += FireChangedEvent;
		_mipFilter.Changed += FireChangedEvent;
		_addressU.Changed += FireChangedEvent;
		_addressV.Changed += FireChangedEvent;
		_addressW.Changed += FireChangedEvent;
	}

	public SamplerState()
	{
		Initialize( GetOwner() );
	}

	public SamplerState( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SamplerState( DBResource owner, SamplerState source )
		: this(owner, source, true){}

	protected SamplerState( DBResource owner, SamplerState source, bool fireEvent )
	{
		_minFilter = new UndoRedo<MinFilterType>( owner, source.minFilter );
		_magFilter = new UndoRedo<MagFilterType>( owner, source.magFilter );
		_mipFilter = new UndoRedo<MipFilterType>( owner, source.mipFilter );
		_addressU = new UndoRedo<TextureAddressType>( owner, source.addressU );
		_addressV = new UndoRedo<TextureAddressType>( owner, source.addressV );
		_addressW = new UndoRedo<TextureAddressType>( owner, source.addressW );
		_minFilter.Changed += FireChangedEvent;
		_magFilter.Changed += FireChangedEvent;
		_mipFilter.Changed += FireChangedEvent;
		_addressU.Changed += FireChangedEvent;
		_addressV.Changed += FireChangedEvent;
		_addressW.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SamplerState source = _source as SamplerState;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SamplerState" );
		minFilter = source.minFilter;
		magFilter = source.magFilter;
		mipFilter = source.mipFilter;
		addressU = source.addressU;
		addressV = source.addressV;
		addressW = source.addressW;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SamplerState newParent = _newParent as SamplerState;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minFilter.SetParent( newParent == null ? null : newParent._minFilter );
		_magFilter.SetParent( newParent == null ? null : newParent._magFilter );
		_mipFilter.SetParent( newParent == null ? null : newParent._mipFilter );
		_addressU.SetParent( newParent == null ? null : newParent._addressU );
		_addressV.SetParent( newParent == null ? null : newParent._addressV );
		_addressW.SetParent( newParent == null ? null : newParent._addressW );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minFilter.Reset();
		_magFilter.Reset();
		_mipFilter.Reset();
		_addressU.Reset();
		_addressV.Reset();
		_addressW.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minFilter.IsDerivedFromParent()
			&& _magFilter.IsDerivedFromParent()
			&& _mipFilter.IsDerivedFromParent()
			&& _addressU.IsDerivedFromParent()
			&& _addressV.IsDerivedFromParent()
			&& _addressW.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minFilter" )
			_minFilter.Reset();
		else if ( fieldName == "magFilter" )
			_magFilter.Reset();
		else if ( fieldName == "mipFilter" )
			_mipFilter.Reset();
		else if ( fieldName == "addressU" )
			_addressU.Reset();
		else if ( fieldName == "addressV" )
			_addressV.Reset();
		else if ( fieldName == "addressW" )
			_addressW.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minFilter" )
			return _minFilter.IsDerivedFromParent();
		if ( fieldName == "magFilter" )
			return _magFilter.IsDerivedFromParent();
		if ( fieldName == "mipFilter" )
			return _mipFilter.IsDerivedFromParent();
		if ( fieldName == "addressU" )
			return _addressU.IsDerivedFromParent();
		if ( fieldName == "addressV" )
			return _addressV.IsDerivedFromParent();
		if ( fieldName == "addressW" )
			return _addressW.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class SamplerCube : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SamplerCube __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private SamplerState _samplerState;
	private UndoRedoDBPtr<CubeMap> _texture;

	public SamplerState samplerState { get { return _samplerState; } set { _samplerState.Assign( value ); } }

	public DBPtr<CubeMap> texture { get { return _texture.Get(); } set { _texture.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_samplerState = new SamplerState( owner );
		_texture = new UndoRedoDBPtr<CubeMap>( owner );
		_samplerState.Changed += FireChangedEvent;
		_texture.Changed += FireChangedEvent;
	}

	public SamplerCube()
	{
		Initialize( GetOwner() );
	}

	public SamplerCube( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SamplerCube( DBResource owner, SamplerCube source )
		: this(owner, source, true){}

	protected SamplerCube( DBResource owner, SamplerCube source, bool fireEvent )
	{
		_samplerState = new SamplerState( owner, source.samplerState );
		_texture = new UndoRedoDBPtr<CubeMap>( owner, source.texture );
		_samplerState.Changed += FireChangedEvent;
		_texture.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SamplerCube source = _source as SamplerCube;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SamplerCube" );
		samplerState = source.samplerState;
		texture = source.texture;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SamplerCube newParent = _newParent as SamplerCube;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_samplerState.SetParent( newParent == null ? null : newParent._samplerState );
		_texture.SetParent( newParent == null ? null : newParent._texture );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_samplerState.Reset();
		_texture.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_samplerState.IsDerivedFromParent()
			&& _texture.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "samplerState" )
			_samplerState.Reset();
		else if ( fieldName == "texture" )
			_texture.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "samplerState" )
			return _samplerState.IsDerivedFromParent();
		if ( fieldName == "texture" )
			return _texture.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class SamplerEx : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SamplerEx __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private SamplerState _samplerState;
	private UndoRedoDBPtr<TextureBase> _texture;
	private HDRColor _Multiplier;
	private HDRColor _Add;

	public SamplerState samplerState { get { return _samplerState; } set { _samplerState.Assign( value ); } }

	public DBPtr<TextureBase> texture { get { return _texture.Get(); } set { _texture.Set( value ); } }

	public HDRColor Multiplier { get { return _Multiplier; } set { _Multiplier.Assign( value ); } }

	public HDRColor Add { get { return _Add; } set { _Add.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_samplerState = new SamplerState( owner );
		_texture = new UndoRedoDBPtr<TextureBase>( owner );
		HDRColor __Multiplier = new HDRColor(); // Construct default object for Multiplier
		__Multiplier.R = 1.0f;
		__Multiplier.G = 1.0f;
		__Multiplier.B = 1.0f;
		_Multiplier = new HDRColor( owner, __Multiplier );
		HDRColor __Add = new HDRColor(); // Construct default object for Add
		__Add.A = 0.0f;
		_Add = new HDRColor( owner, __Add );
		_samplerState.Changed += FireChangedEvent;
		_texture.Changed += FireChangedEvent;
		_Multiplier.Changed += FireChangedEvent;
		_Add.Changed += FireChangedEvent;
	}

	public SamplerEx()
	{
		Initialize( GetOwner() );
	}

	public SamplerEx( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SamplerEx( DBResource owner, SamplerEx source )
		: this(owner, source, true){}

	protected SamplerEx( DBResource owner, SamplerEx source, bool fireEvent )
	{
		_samplerState = new SamplerState( owner, source.samplerState );
		_texture = new UndoRedoDBPtr<TextureBase>( owner, source.texture );
		_Multiplier = new HDRColor( owner, source.Multiplier );
		_Add = new HDRColor( owner, source.Add );
		_samplerState.Changed += FireChangedEvent;
		_texture.Changed += FireChangedEvent;
		_Multiplier.Changed += FireChangedEvent;
		_Add.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SamplerEx source = _source as SamplerEx;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SamplerEx" );
		samplerState = source.samplerState;
		texture = source.texture;
		Multiplier = source.Multiplier;
		Add = source.Add;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SamplerEx newParent = _newParent as SamplerEx;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_samplerState.SetParent( newParent == null ? null : newParent._samplerState );
		_texture.SetParent( newParent == null ? null : newParent._texture );
		_Multiplier.SetParent( newParent == null ? null : newParent._Multiplier );
		_Add.SetParent( newParent == null ? null : newParent._Add );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_samplerState.Reset();
		_texture.Reset();
		_Multiplier.Reset();
		_Add.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_samplerState.IsDerivedFromParent()
			&& _texture.IsDerivedFromParent()
			&& _Multiplier.IsDerivedFromParent()
			&& _Add.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "samplerState" )
			_samplerState.Reset();
		else if ( fieldName == "texture" )
			_texture.Reset();
		else if ( fieldName == "Multiplier" )
			_Multiplier.Reset();
		else if ( fieldName == "Add" )
			_Add.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "samplerState" )
			return _samplerState.IsDerivedFromParent();
		if ( fieldName == "texture" )
			return _texture.IsDerivedFromParent();
		if ( fieldName == "Multiplier" )
			return _Multiplier.IsDerivedFromParent();
		if ( fieldName == "Add" )
			return _Add.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class Sampler : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Sampler __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private SamplerState _samplerState;
	private UndoRedoDBPtr<TextureBase> _texture;

	public SamplerState samplerState { get { return _samplerState; } set { _samplerState.Assign( value ); } }

	public DBPtr<TextureBase> texture { get { return _texture.Get(); } set { _texture.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_samplerState = new SamplerState( owner );
		_texture = new UndoRedoDBPtr<TextureBase>( owner );
		_samplerState.Changed += FireChangedEvent;
		_texture.Changed += FireChangedEvent;
	}

	public Sampler()
	{
		Initialize( GetOwner() );
	}

	public Sampler( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Sampler( DBResource owner, Sampler source )
		: this(owner, source, true){}

	protected Sampler( DBResource owner, Sampler source, bool fireEvent )
	{
		_samplerState = new SamplerState( owner, source.samplerState );
		_texture = new UndoRedoDBPtr<TextureBase>( owner, source.texture );
		_samplerState.Changed += FireChangedEvent;
		_texture.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Sampler source = _source as Sampler;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Sampler" );
		samplerState = source.samplerState;
		texture = source.texture;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Sampler newParent = _newParent as Sampler;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_samplerState.SetParent( newParent == null ? null : newParent._samplerState );
		_texture.SetParent( newParent == null ? null : newParent._texture );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_samplerState.Reset();
		_texture.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_samplerState.IsDerivedFromParent()
			&& _texture.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "samplerState" )
			_samplerState.Reset();
		else if ( fieldName == "texture" )
			_texture.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "samplerState" )
			return _samplerState.IsDerivedFromParent();
		if ( fieldName == "texture" )
			return _texture.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class ShaderDefineDescriptor : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ShaderDefineDescriptor __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _name;
	private UndoRedo<int> _minValue;
	private UndoRedo<int> _maxValue;
	private UndoRedo<bool> _CanChangedInEditor;
	private UndoRedoList<string> _definesValuesDescriptions;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public int minValue { get { return _minValue.Get(); } set { _minValue.Set( value ); } }

	public int maxValue { get { return _maxValue.Get(); } set { _maxValue.Set( value ); } }

	public bool CanChangedInEditor { get { return _CanChangedInEditor.Get(); } set { _CanChangedInEditor.Set( value ); } }

	public libdb.IChangeableList<string> definesValuesDescriptions { get { return _definesValuesDescriptions; } set { _definesValuesDescriptions.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new UndoRedo<string>( owner, string.Empty );
		_minValue = new UndoRedo<int>( owner, 0 );
		_maxValue = new UndoRedo<int>( owner, 0 );
		_CanChangedInEditor = new UndoRedo<bool>( owner, false );
		_definesValuesDescriptions = new UndoRedoList<string>( owner );
		_name.Changed += FireChangedEvent;
		_minValue.Changed += FireChangedEvent;
		_maxValue.Changed += FireChangedEvent;
		_CanChangedInEditor.Changed += FireChangedEvent;
		_definesValuesDescriptions.Changed += FireChangedEvent;
	}

	public ShaderDefineDescriptor()
	{
		Initialize( GetOwner() );
	}

	public ShaderDefineDescriptor( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ShaderDefineDescriptor( DBResource owner, ShaderDefineDescriptor source )
		: this(owner, source, true){}

	protected ShaderDefineDescriptor( DBResource owner, ShaderDefineDescriptor source, bool fireEvent )
	{
		_name = new UndoRedo<string>( owner, source.name );
		_minValue = new UndoRedo<int>( owner, source.minValue );
		_maxValue = new UndoRedo<int>( owner, source.maxValue );
		_CanChangedInEditor = new UndoRedo<bool>( owner, source.CanChangedInEditor );
		_definesValuesDescriptions = new UndoRedoList<string>( owner );
		_definesValuesDescriptions.Assign( source.definesValuesDescriptions );
		_name.Changed += FireChangedEvent;
		_minValue.Changed += FireChangedEvent;
		_maxValue.Changed += FireChangedEvent;
		_CanChangedInEditor.Changed += FireChangedEvent;
		_definesValuesDescriptions.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ShaderDefineDescriptor source = _source as ShaderDefineDescriptor;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ShaderDefineDescriptor" );
		name = source.name;
		minValue = source.minValue;
		maxValue = source.maxValue;
		CanChangedInEditor = source.CanChangedInEditor;
		definesValuesDescriptions = source.definesValuesDescriptions;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ShaderDefineDescriptor newParent = _newParent as ShaderDefineDescriptor;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_minValue.SetParent( newParent == null ? null : newParent._minValue );
		_maxValue.SetParent( newParent == null ? null : newParent._maxValue );
		_CanChangedInEditor.SetParent( newParent == null ? null : newParent._CanChangedInEditor );
		_definesValuesDescriptions.SetParent( newParent == null ? null : newParent._definesValuesDescriptions );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_minValue.Reset();
		_maxValue.Reset();
		_CanChangedInEditor.Reset();
		_definesValuesDescriptions.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _minValue.IsDerivedFromParent()
			&& _maxValue.IsDerivedFromParent()
			&& _CanChangedInEditor.IsDerivedFromParent()
			&& _definesValuesDescriptions.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "minValue" )
			_minValue.Reset();
		else if ( fieldName == "maxValue" )
			_maxValue.Reset();
		else if ( fieldName == "CanChangedInEditor" )
			_CanChangedInEditor.Reset();
		else if ( fieldName == "definesValuesDescriptions" )
			_definesValuesDescriptions.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "minValue" )
			return _minValue.IsDerivedFromParent();
		if ( fieldName == "maxValue" )
			return _maxValue.IsDerivedFromParent();
		if ( fieldName == "CanChangedInEditor" )
			return _CanChangedInEditor.IsDerivedFromParent();
		if ( fieldName == "definesValuesDescriptions" )
			return _definesValuesDescriptions.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class ShaderDefinesDescriptorsTable : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ShaderDefinesDescriptorsTable __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<ShaderDefineDescriptor> _definesDescriptors;

	public libdb.IChangeableList<ShaderDefineDescriptor> definesDescriptors { get { return _definesDescriptors; } set { _definesDescriptors.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_definesDescriptors = new UndoRedoAssignableList<ShaderDefineDescriptor>( owner );
		_definesDescriptors.Changed += FireChangedEvent;
	}

	public ShaderDefinesDescriptorsTable()
	{
		Initialize( GetOwner() );
	}

	public ShaderDefinesDescriptorsTable( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ShaderDefinesDescriptorsTable( DBResource owner, ShaderDefinesDescriptorsTable source )
		: this(owner, source, true){}

	protected ShaderDefinesDescriptorsTable( DBResource owner, ShaderDefinesDescriptorsTable source, bool fireEvent )
	{
		_definesDescriptors = new UndoRedoAssignableList<ShaderDefineDescriptor>( owner );
		_definesDescriptors.Assign( source.definesDescriptors );
		_definesDescriptors.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ShaderDefinesDescriptorsTable source = _source as ShaderDefinesDescriptorsTable;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ShaderDefinesDescriptorsTable" );
		definesDescriptors = source.definesDescriptors;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ShaderDefinesDescriptorsTable newParent = _newParent as ShaderDefinesDescriptorsTable;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_definesDescriptors.SetParent( newParent == null ? null : newParent._definesDescriptors );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_definesDescriptors.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_definesDescriptors.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "definesDescriptors" )
			_definesDescriptors.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "definesDescriptors" )
			return _definesDescriptors.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[BaseMaterialType]
[DBVersion(1)]
[IndexField("caption")]
[NonTerminal]
[TypeId]
public class Material : DBResource
{
	private UndoRedoDBPtr<Material> ___parent;
	[HideInOutliner]
	public new DBPtr<Material> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _SubPriority;
	private UndoRedo<string> _caption;
	private UndoRedo<bool> _ignoreRenderState;

	[Description( "The less the sooner" )]
	[IntMinMax(-16, 16)]
	public int SubPriority { get { return _SubPriority.Get(); } set { _SubPriority.Set( value ); } }

	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	[Description( "Не выставлять прописанный RenderState" )]
	public bool ignoreRenderState { get { return _ignoreRenderState.Get(); } set { _ignoreRenderState.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Material>(owner);
		_SubPriority = new UndoRedo<int>( owner, 0 );
		_caption = new UndoRedo<string>( owner, string.Empty );
		_ignoreRenderState = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_SubPriority.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_ignoreRenderState.Changed += FireChangedEvent;
	}

	public Material()
	{
		Initialize( this );
	}
	private void AssignSelf( Material source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Material" );
		SubPriority = source.SubPriority;
		caption = source.caption;
		ignoreRenderState = source.ignoreRenderState;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Material source = _source as Material;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Material" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Material newParent = rawParent == null ? null : rawParent.Get<Material>();
		if ( newParent == null && _newParent is Material )
			newParent = _newParent as Material;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_SubPriority.SetParent( newParent == null ? null : newParent._SubPriority );
		_caption.SetParent( newParent == null ? null : newParent._caption );
		_ignoreRenderState.SetParent( newParent == null ? null : newParent._ignoreRenderState );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_SubPriority.Reset();
		_caption.Reset();
		_ignoreRenderState.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_SubPriority.IsDerivedFromParent()
			&& _caption.IsDerivedFromParent()
			&& _ignoreRenderState.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "SubPriority" )
			_SubPriority.Reset();
		else if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "ignoreRenderState" )
			_ignoreRenderState.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "SubPriority" )
			return _SubPriority.IsDerivedFromParent();
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		if ( fieldName == "ignoreRenderState" )
			return _ignoreRenderState.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[MaterialFunc("CommonMaterialFunc.inl")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B7A5B80)]
[UseTypeName("MTRL")]
public class AOEMaterial : Material
{
	private UndoRedoDBPtr<AOEMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<AOEMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private Sampler _DiffuseMap;
	private HDRColor _primaryColor;
	private HDRColor _secondaryColor;
	private UndoRedo<float> _aspectRatio;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0)]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Category( "Modificator" )]
	public HDRColor primaryColor { get { return _primaryColor; } set { _primaryColor.Assign( value ); } }

	[Category( "Modificator" )]
	public HDRColor secondaryColor { get { return _secondaryColor; } set { _secondaryColor.Assign( value ); } }

	public float aspectRatio { get { return _aspectRatio.Get(); } set { _aspectRatio.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AOEMaterial>(owner);
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.alphaTest = OnOffState.On;
		__renderState.alphaTestRef = 0;
		_renderState = new RenderState( owner, __renderState );
		Sampler __DiffuseMap = new Sampler(); // Construct default object for DiffuseMap
		__DiffuseMap.samplerState.addressU = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressV = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressW = TextureAddressType.Clamp;
		_DiffuseMap = new Sampler( owner, __DiffuseMap );
		HDRColor __primaryColor = new HDRColor(); // Construct default object for primaryColor
		__primaryColor.R = 1.0f;
		__primaryColor.G = 1.0f;
		__primaryColor.B = 1.0f;
		_primaryColor = new HDRColor( owner, __primaryColor );
		HDRColor __secondaryColor = new HDRColor(); // Construct default object for secondaryColor
		__secondaryColor.R = 1.0f;
		__secondaryColor.G = 1.0f;
		__secondaryColor.B = 1.0f;
		_secondaryColor = new HDRColor( owner, __secondaryColor );
		_aspectRatio = new UndoRedo<float>( owner, 2.0f );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_primaryColor.Changed += FireChangedEvent;
		_secondaryColor.Changed += FireChangedEvent;
		_aspectRatio.Changed += FireChangedEvent;
	}

	public AOEMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( AOEMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AOEMaterial" );
		renderState = source.renderState;
		DiffuseMap = source.DiffuseMap;
		primaryColor = source.primaryColor;
		secondaryColor = source.secondaryColor;
		aspectRatio = source.aspectRatio;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AOEMaterial source = _source as AOEMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AOEMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AOEMaterial newParent = rawParent == null ? null : rawParent.Get<AOEMaterial>();
		if ( newParent == null && _newParent is AOEMaterial )
			newParent = _newParent as AOEMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_primaryColor.SetParent( newParent == null ? null : newParent._primaryColor );
		_secondaryColor.SetParent( newParent == null ? null : newParent._secondaryColor );
		_aspectRatio.SetParent( newParent == null ? null : newParent._aspectRatio );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_DiffuseMap.Reset();
		_primaryColor.Reset();
		_secondaryColor.Reset();
		_aspectRatio.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _primaryColor.IsDerivedFromParent()
			&& _secondaryColor.IsDerivedFromParent()
			&& _aspectRatio.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "primaryColor" )
			_primaryColor.Reset();
		else if ( fieldName == "secondaryColor" )
			_secondaryColor.Reset();
		else if ( fieldName == "aspectRatio" )
			_aspectRatio.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "primaryColor" )
			return _primaryColor.IsDerivedFromParent();
		if ( fieldName == "secondaryColor" )
			return _secondaryColor.IsDerivedFromParent();
		if ( fieldName == "aspectRatio" )
			return _aspectRatio.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[DBVersion(0)]
[NonTerminal]
public class BaseUIMaterial : Material
{
	private UndoRedoDBPtr<BaseUIMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<BaseUIMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EUIImageDrawMode> _horizontalDrawMode;
	private UndoRedo<EUIImageDrawMode> _verticalDrawMode;
	private IntPoint _textureShift;
	private IntPoint _imageSize;
	private IntPoint _imageTileShift;
	private IntPoint _imageTileSize;
	private UndoRedo<BooleanPin> _UseAutosize;

	public EUIImageDrawMode horizontalDrawMode { get { return _horizontalDrawMode.Get(); } set { _horizontalDrawMode.Set( value ); } }

	public EUIImageDrawMode verticalDrawMode { get { return _verticalDrawMode.Get(); } set { _verticalDrawMode.Set( value ); } }

	public IntPoint textureShift { get { return _textureShift; } set { _textureShift.Assign( value ); } }

	public IntPoint imageSize { get { return _imageSize; } set { _imageSize.Assign( value ); } }

	public IntPoint imageTileShift { get { return _imageTileShift; } set { _imageTileShift.Assign( value ); } }

	public IntPoint imageTileSize { get { return _imageTileSize; } set { _imageTileSize.Assign( value ); } }

	public BooleanPin UseAutosize { get { return _UseAutosize.Get(); } set { _UseAutosize.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BaseUIMaterial>(owner);
		_horizontalDrawMode = new UndoRedo<EUIImageDrawMode>( owner, EUIImageDrawMode.Stretch );
		_verticalDrawMode = new UndoRedo<EUIImageDrawMode>( owner, EUIImageDrawMode.Stretch );
		_textureShift = new IntPoint( owner );
		_imageSize = new IntPoint( owner );
		_imageTileShift = new IntPoint( owner );
		_imageTileSize = new IntPoint( owner );
		_UseAutosize = new UndoRedo<BooleanPin>( owner, BooleanPin.Present );
		___parent.Changed += FireChangedEvent;
		_horizontalDrawMode.Changed += FireChangedEvent;
		_verticalDrawMode.Changed += FireChangedEvent;
		_textureShift.Changed += FireChangedEvent;
		_imageSize.Changed += FireChangedEvent;
		_imageTileShift.Changed += FireChangedEvent;
		_imageTileSize.Changed += FireChangedEvent;
		_UseAutosize.Changed += FireChangedEvent;
	}

	public BaseUIMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( BaseUIMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BaseUIMaterial" );
		horizontalDrawMode = source.horizontalDrawMode;
		verticalDrawMode = source.verticalDrawMode;
		textureShift = source.textureShift;
		imageSize = source.imageSize;
		imageTileShift = source.imageTileShift;
		imageTileSize = source.imageTileSize;
		UseAutosize = source.UseAutosize;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BaseUIMaterial source = _source as BaseUIMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BaseUIMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BaseUIMaterial newParent = rawParent == null ? null : rawParent.Get<BaseUIMaterial>();
		if ( newParent == null && _newParent is BaseUIMaterial )
			newParent = _newParent as BaseUIMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_horizontalDrawMode.SetParent( newParent == null ? null : newParent._horizontalDrawMode );
		_verticalDrawMode.SetParent( newParent == null ? null : newParent._verticalDrawMode );
		_textureShift.SetParent( newParent == null ? null : newParent._textureShift );
		_imageSize.SetParent( newParent == null ? null : newParent._imageSize );
		_imageTileShift.SetParent( newParent == null ? null : newParent._imageTileShift );
		_imageTileSize.SetParent( newParent == null ? null : newParent._imageTileSize );
		_UseAutosize.SetParent( newParent == null ? null : newParent._UseAutosize );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_horizontalDrawMode.Reset();
		_verticalDrawMode.Reset();
		_textureShift.Reset();
		_imageSize.Reset();
		_imageTileShift.Reset();
		_imageTileSize.Reset();
		_UseAutosize.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_horizontalDrawMode.IsDerivedFromParent()
			&& _verticalDrawMode.IsDerivedFromParent()
			&& _textureShift.IsDerivedFromParent()
			&& _imageSize.IsDerivedFromParent()
			&& _imageTileShift.IsDerivedFromParent()
			&& _imageTileSize.IsDerivedFromParent()
			&& _UseAutosize.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "horizontalDrawMode" )
			_horizontalDrawMode.Reset();
		else if ( fieldName == "verticalDrawMode" )
			_verticalDrawMode.Reset();
		else if ( fieldName == "textureShift" )
			_textureShift.Reset();
		else if ( fieldName == "imageSize" )
			_imageSize.Reset();
		else if ( fieldName == "imageTileShift" )
			_imageTileShift.Reset();
		else if ( fieldName == "imageTileSize" )
			_imageTileSize.Reset();
		else if ( fieldName == "UseAutosize" )
			_UseAutosize.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "horizontalDrawMode" )
			return _horizontalDrawMode.IsDerivedFromParent();
		if ( fieldName == "verticalDrawMode" )
			return _verticalDrawMode.IsDerivedFromParent();
		if ( fieldName == "textureShift" )
			return _textureShift.IsDerivedFromParent();
		if ( fieldName == "imageSize" )
			return _imageSize.IsDerivedFromParent();
		if ( fieldName == "imageTileShift" )
			return _imageTileShift.IsDerivedFromParent();
		if ( fieldName == "imageTileSize" )
			return _imageTileSize.IsDerivedFromParent();
		if ( fieldName == "UseAutosize" )
			return _UseAutosize.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(3)]
[MaterialFunc("BasicFXMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)", "ModifyUVOffset(float u, float v)")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9E5872A2)]
[UseTypeName("MTRL")]
public class BasicFXMaterial : Material
{
	private UndoRedoDBPtr<BasicFXMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<BasicFXMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private Sampler _DiffuseMap;
	private AnimatedHDRColor _DiffuseMul;
	private AnimatedHDRColor _DiffuseAdd;
	private UndoRedo<BooleanPin> _SkeletalMeshPinValue;
	private UndoRedo<OpacityAndEmissiveModePin> _OpacityAndEmissiveModePinValue;
	private UndoRedo<BooleanPin> _MultiplyVertexColorPinValue;
	private UndoRedo<DistortionPin> _DistortionPinValue;
	private UndoRedo<float> _emissive;
	private UndoRedo<float> _distortion;
	private AnimatedFloat _opacity;
	private AnimatedFloat _uOffset;
	private AnimatedFloat _vOffset;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0, "DiffuseMap", true)]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Category( "Diffuse" )]
	public AnimatedHDRColor DiffuseMul { get { return _DiffuseMul; } set { _DiffuseMul.Assign( value ); } }

	[Category( "Diffuse" )]
	public AnimatedHDRColor DiffuseAdd { get { return _DiffuseAdd; } set { _DiffuseAdd.Assign( value ); } }

	[Category( "Pins" )]
	[Pin2("SkeletalMeshPin")]
	[ReadOnly( true )]
	public BooleanPin SkeletalMeshPinValue { get { return _SkeletalMeshPinValue.Get(); } set { _SkeletalMeshPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue { get { return _OpacityAndEmissiveModePinValue.Get(); } set { _OpacityAndEmissiveModePinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2("MultiplyVertexColorPin")]
	[ReadOnly( true )]
	public BooleanPin MultiplyVertexColorPinValue { get { return _MultiplyVertexColorPinValue.Get(); } set { _MultiplyVertexColorPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public DistortionPin DistortionPinValue { get { return _DistortionPinValue.Get(); } set { _DistortionPinValue.Set( value ); } }

	public float emissive { get { return _emissive.Get(); } set { _emissive.Set( value ); } }

	public float distortion { get { return _distortion.Get(); } set { _distortion.Set( value ); } }

	public AnimatedFloat opacity { get { return _opacity; } set { _opacity.Assign( value ); } }

	public AnimatedFloat uOffset { get { return _uOffset; } set { _uOffset.Assign( value ); } }

	public AnimatedFloat vOffset { get { return _vOffset; } set { _vOffset.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BasicFXMaterial>(owner);
		_renderState = new RenderState( owner );
		_DiffuseMap = new Sampler( owner );
		_DiffuseMul = new AnimatedHDRColor( owner, 1.0f, 1.0f, 1.0f, 1.0f );
		_DiffuseAdd = new AnimatedHDRColor( owner, 0.0f, 0.0f, 0.0f, 0.0f );
		_SkeletalMeshPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_OpacityAndEmissiveModePinValue = new UndoRedo<OpacityAndEmissiveModePin>( owner, OpacityAndEmissiveModePin.Simple );
		_MultiplyVertexColorPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_DistortionPinValue = new UndoRedo<DistortionPin>( owner, DistortionPin.DistortNone );
		_emissive = new UndoRedo<float>( owner, 0.0f );
		_distortion = new UndoRedo<float>( owner, 1.0f );
		_opacity = new AnimatedFloat( owner, 1.0f );
		_uOffset = new AnimatedFloat( owner );
		_vOffset = new AnimatedFloat( owner );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_DiffuseMul.Changed += FireChangedEvent;
		_DiffuseAdd.Changed += FireChangedEvent;
		_SkeletalMeshPinValue.Changed += FireChangedEvent;
		_OpacityAndEmissiveModePinValue.Changed += FireChangedEvent;
		_MultiplyVertexColorPinValue.Changed += FireChangedEvent;
		_DistortionPinValue.Changed += FireChangedEvent;
		_emissive.Changed += FireChangedEvent;
		_distortion.Changed += FireChangedEvent;
		_opacity.Changed += FireChangedEvent;
		_uOffset.Changed += FireChangedEvent;
		_vOffset.Changed += FireChangedEvent;
	}

	public BasicFXMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( BasicFXMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BasicFXMaterial" );
		renderState = source.renderState;
		DiffuseMap = source.DiffuseMap;
		DiffuseMul = source.DiffuseMul;
		DiffuseAdd = source.DiffuseAdd;
		SkeletalMeshPinValue = source.SkeletalMeshPinValue;
		OpacityAndEmissiveModePinValue = source.OpacityAndEmissiveModePinValue;
		MultiplyVertexColorPinValue = source.MultiplyVertexColorPinValue;
		DistortionPinValue = source.DistortionPinValue;
		emissive = source.emissive;
		distortion = source.distortion;
		opacity = source.opacity;
		uOffset = source.uOffset;
		vOffset = source.vOffset;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BasicFXMaterial source = _source as BasicFXMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BasicFXMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BasicFXMaterial newParent = rawParent == null ? null : rawParent.Get<BasicFXMaterial>();
		if ( newParent == null && _newParent is BasicFXMaterial )
			newParent = _newParent as BasicFXMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_DiffuseMul.SetParent( newParent == null ? null : newParent._DiffuseMul );
		_DiffuseAdd.SetParent( newParent == null ? null : newParent._DiffuseAdd );
		_SkeletalMeshPinValue.SetParent( newParent == null ? null : newParent._SkeletalMeshPinValue );
		_OpacityAndEmissiveModePinValue.SetParent( newParent == null ? null : newParent._OpacityAndEmissiveModePinValue );
		_MultiplyVertexColorPinValue.SetParent( newParent == null ? null : newParent._MultiplyVertexColorPinValue );
		_DistortionPinValue.SetParent( newParent == null ? null : newParent._DistortionPinValue );
		_emissive.SetParent( newParent == null ? null : newParent._emissive );
		_distortion.SetParent( newParent == null ? null : newParent._distortion );
		_opacity.SetParent( newParent == null ? null : newParent._opacity );
		_uOffset.SetParent( newParent == null ? null : newParent._uOffset );
		_vOffset.SetParent( newParent == null ? null : newParent._vOffset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_DiffuseMap.Reset();
		_DiffuseMul.Reset();
		_DiffuseAdd.Reset();
		_SkeletalMeshPinValue.Reset();
		_OpacityAndEmissiveModePinValue.Reset();
		_MultiplyVertexColorPinValue.Reset();
		_DistortionPinValue.Reset();
		_emissive.Reset();
		_distortion.Reset();
		_opacity.Reset();
		_uOffset.Reset();
		_vOffset.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _DiffuseMul.IsDerivedFromParent()
			&& _DiffuseAdd.IsDerivedFromParent()
			&& _SkeletalMeshPinValue.IsDerivedFromParent()
			&& _OpacityAndEmissiveModePinValue.IsDerivedFromParent()
			&& _MultiplyVertexColorPinValue.IsDerivedFromParent()
			&& _DistortionPinValue.IsDerivedFromParent()
			&& _emissive.IsDerivedFromParent()
			&& _distortion.IsDerivedFromParent()
			&& _opacity.IsDerivedFromParent()
			&& _uOffset.IsDerivedFromParent()
			&& _vOffset.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "DiffuseMul" )
			_DiffuseMul.Reset();
		else if ( fieldName == "DiffuseAdd" )
			_DiffuseAdd.Reset();
		else if ( fieldName == "SkeletalMeshPinValue" )
			_SkeletalMeshPinValue.Reset();
		else if ( fieldName == "OpacityAndEmissiveModePinValue" )
			_OpacityAndEmissiveModePinValue.Reset();
		else if ( fieldName == "MultiplyVertexColorPinValue" )
			_MultiplyVertexColorPinValue.Reset();
		else if ( fieldName == "DistortionPinValue" )
			_DistortionPinValue.Reset();
		else if ( fieldName == "emissive" )
			_emissive.Reset();
		else if ( fieldName == "distortion" )
			_distortion.Reset();
		else if ( fieldName == "opacity" )
			_opacity.Reset();
		else if ( fieldName == "uOffset" )
			_uOffset.Reset();
		else if ( fieldName == "vOffset" )
			_vOffset.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "DiffuseMul" )
			return _DiffuseMul.IsDerivedFromParent();
		if ( fieldName == "DiffuseAdd" )
			return _DiffuseAdd.IsDerivedFromParent();
		if ( fieldName == "SkeletalMeshPinValue" )
			return _SkeletalMeshPinValue.IsDerivedFromParent();
		if ( fieldName == "OpacityAndEmissiveModePinValue" )
			return _OpacityAndEmissiveModePinValue.IsDerivedFromParent();
		if ( fieldName == "MultiplyVertexColorPinValue" )
			return _MultiplyVertexColorPinValue.IsDerivedFromParent();
		if ( fieldName == "DistortionPinValue" )
			return _DistortionPinValue.IsDerivedFromParent();
		if ( fieldName == "emissive" )
			return _emissive.IsDerivedFromParent();
		if ( fieldName == "distortion" )
			return _distortion.IsDerivedFromParent();
		if ( fieldName == "opacity" )
			return _opacity.IsDerivedFromParent();
		if ( fieldName == "uOffset" )
			return _uOffset.IsDerivedFromParent();
		if ( fieldName == "vOffset" )
			return _vOffset.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialFunc("EaselPaintMaterial.inl", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9963DB80)]
[UseTypeName("MTRL")]
public class BasicMaskMaterial : Material
{
	private UndoRedoDBPtr<BasicMaskMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<BasicMaskMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private Sampler _Diffuse;
	private Sampler _Mask;

	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0)]
	public Sampler Diffuse { get { return _Diffuse; } set { _Diffuse.Assign( value ); } }

	[Category( "Mask" )]
	[Sampler(3)]
	public Sampler Mask { get { return _Mask; } set { _Mask.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BasicMaskMaterial>(owner);
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.alphaTest = OnOffState.On;
		__renderState.alphaTestRef = 1;
		_renderState = new RenderState( owner, __renderState );
		_Diffuse = new Sampler( owner );
		_Mask = new Sampler( owner );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_Diffuse.Changed += FireChangedEvent;
		_Mask.Changed += FireChangedEvent;
	}

	public BasicMaskMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( BasicMaskMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BasicMaskMaterial" );
		renderState = source.renderState;
		Diffuse = source.Diffuse;
		Mask = source.Mask;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BasicMaskMaterial source = _source as BasicMaskMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BasicMaskMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BasicMaskMaterial newParent = rawParent == null ? null : rawParent.Get<BasicMaskMaterial>();
		if ( newParent == null && _newParent is BasicMaskMaterial )
			newParent = _newParent as BasicMaskMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_Diffuse.SetParent( newParent == null ? null : newParent._Diffuse );
		_Mask.SetParent( newParent == null ? null : newParent._Mask );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_Diffuse.Reset();
		_Mask.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _Diffuse.IsDerivedFromParent()
			&& _Mask.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "Diffuse" )
			_Diffuse.Reset();
		else if ( fieldName == "Mask" )
			_Mask.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "Diffuse" )
			return _Diffuse.IsDerivedFromParent();
		if ( fieldName == "Mask" )
			return _Mask.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(677)]
[MaterialFunc("BasicMaterialWithBatch.inl", "ModifyEmissive(float power)", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)", "SetBlendModeOverride(bool state)")]
[MaterialFunc("SpecialTransparency.inl", "SetSpecialTransparency(bool on)")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9E5872A4)]
[UseTypeName("MTRL")]
public class BasicMaterial : Material
{
	private UndoRedoDBPtr<BasicMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<BasicMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private UndoRedo<MaterialFlags> _renderFlags;
	private HDRColor _diffuseColor;
	private UndoRedo<float> _lightingIntencity;
	private Sampler _DiffuseMap;
	private Sampler _NormalMap;
	private SamplerEx _SpecularMap;
	private SamplerCube _ReflectionMap;
	private UndoRedo<ReflectivityPin> _ReflectivityPinValue;
	private HDRColor _outputMul;
	private HDRColor _outputAdd;
	private UndoRedo<EEmissivePin> _EmissivePinValue;
	private UndoRedo<LightingPin> _LightingPinValue;
	private UndoRedo<float> _emissive;
	private UndoRedo<float> _reflectivity;
	private UndoRedo<float> _specularPower;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "States" )]
	[NoCode]
	public MaterialFlags renderFlags { get { return _renderFlags.Get(); } set { _renderFlags.Set( value ); } }

	[Category( "Lighting" )]
	public HDRColor diffuseColor { get { return _diffuseColor; } set { _diffuseColor.Assign( value ); } }

	[Category( "Lighting" )]
	public float lightingIntencity { get { return _lightingIntencity.Get(); } set { _lightingIntencity.Set( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0, "DiffuseMap", true)]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Category( "Normal" )]
	[Sampler(1, true)]
	public Sampler NormalMap { get { return _NormalMap; } set { _NormalMap.Assign( value ); } }

	[Category( "Specular" )]
	[Sampler(2, true)]
	public SamplerEx SpecularMap { get { return _SpecularMap; } set { _SpecularMap.Assign( value ); } }

	[Category( "Reflection" )]
	[Sampler(3, true)]
	public SamplerCube ReflectionMap { get { return _ReflectionMap; } set { _ReflectionMap.Assign( value ); } }

	[Category( "Reflection" )]
	[Pin2]
	public ReflectivityPin ReflectivityPinValue { get { return _ReflectivityPinValue.Get(); } set { _ReflectivityPinValue.Set( value ); } }

	[Category( "Modificator" )]
	public HDRColor outputMul { get { return _outputMul; } set { _outputMul.Assign( value ); } }

	[Category( "Modificator" )]
	public HDRColor outputAdd { get { return _outputAdd; } set { _outputAdd.Assign( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public EEmissivePin EmissivePinValue { get { return _EmissivePinValue.Get(); } set { _EmissivePinValue.Set( value ); } }

	[Category( "Pins" )]
	[HideEnumValues("LightingDynamic1Point", "LightingDynamic2Point", "LightingDynamic3Point", "LightingDynamic4Point")]
	[Pin2("LightingPin")]
	public LightingPin LightingPinValue { get { return _LightingPinValue.Get(); } set { _LightingPinValue.Set( value ); } }

	public float emissive { get { return _emissive.Get(); } set { _emissive.Set( value ); } }

	public float reflectivity { get { return _reflectivity.Get(); } set { _reflectivity.Set( value ); } }

	public float specularPower { get { return _specularPower.Get(); } set { _specularPower.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BasicMaterial>(owner);
		_renderState = new RenderState( owner );
		_renderFlags = new UndoRedo<MaterialFlags>( owner, MaterialFlags.ShadowReceiver );
		HDRColor __diffuseColor = new HDRColor(); // Construct default object for diffuseColor
		__diffuseColor.R = 1.0f;
		__diffuseColor.G = 1.0f;
		__diffuseColor.B = 1.0f;
		_diffuseColor = new HDRColor( owner, __diffuseColor );
		_lightingIntencity = new UndoRedo<float>( owner, 1.0f );
		_DiffuseMap = new Sampler( owner );
		_NormalMap = new Sampler( owner );
		SamplerEx __SpecularMap = new SamplerEx(); // Construct default object for SpecularMap
		__SpecularMap.Multiplier.R = 1.0f;
		__SpecularMap.Multiplier.G = 1.0f;
		__SpecularMap.Multiplier.B = 1.0f;
		__SpecularMap.Add.A = 0.0f;
		_SpecularMap = new SamplerEx( owner, __SpecularMap );
		_ReflectionMap = new SamplerCube( owner );
		_ReflectivityPinValue = new UndoRedo<ReflectivityPin>( owner, ReflectivityPin.ReflectivityOff );
		HDRColor __outputMul = new HDRColor(); // Construct default object for outputMul
		__outputMul.R = 1.0f;
		__outputMul.G = 1.0f;
		__outputMul.B = 1.0f;
		_outputMul = new HDRColor( owner, __outputMul );
		HDRColor __outputAdd = new HDRColor(); // Construct default object for outputAdd
		__outputAdd.A = 0.0f;
		_outputAdd = new HDRColor( owner, __outputAdd );
		_EmissivePinValue = new UndoRedo<EEmissivePin>( owner, EEmissivePin.EmissiveOff );
		_LightingPinValue = new UndoRedo<LightingPin>( owner, LightingPin.LightingSH );
		_emissive = new UndoRedo<float>( owner, 0.0f );
		_reflectivity = new UndoRedo<float>( owner, 1.0f );
		_specularPower = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_renderFlags.Changed += FireChangedEvent;
		_diffuseColor.Changed += FireChangedEvent;
		_lightingIntencity.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_NormalMap.Changed += FireChangedEvent;
		_SpecularMap.Changed += FireChangedEvent;
		_ReflectionMap.Changed += FireChangedEvent;
		_ReflectivityPinValue.Changed += FireChangedEvent;
		_outputMul.Changed += FireChangedEvent;
		_outputAdd.Changed += FireChangedEvent;
		_EmissivePinValue.Changed += FireChangedEvent;
		_LightingPinValue.Changed += FireChangedEvent;
		_emissive.Changed += FireChangedEvent;
		_reflectivity.Changed += FireChangedEvent;
		_specularPower.Changed += FireChangedEvent;
	}

	public BasicMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( BasicMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BasicMaterial" );
		renderState = source.renderState;
		renderFlags = source.renderFlags;
		diffuseColor = source.diffuseColor;
		lightingIntencity = source.lightingIntencity;
		DiffuseMap = source.DiffuseMap;
		NormalMap = source.NormalMap;
		SpecularMap = source.SpecularMap;
		ReflectionMap = source.ReflectionMap;
		ReflectivityPinValue = source.ReflectivityPinValue;
		outputMul = source.outputMul;
		outputAdd = source.outputAdd;
		EmissivePinValue = source.EmissivePinValue;
		LightingPinValue = source.LightingPinValue;
		emissive = source.emissive;
		reflectivity = source.reflectivity;
		specularPower = source.specularPower;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BasicMaterial source = _source as BasicMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BasicMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BasicMaterial newParent = rawParent == null ? null : rawParent.Get<BasicMaterial>();
		if ( newParent == null && _newParent is BasicMaterial )
			newParent = _newParent as BasicMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_renderFlags.SetParent( newParent == null ? null : newParent._renderFlags );
		_diffuseColor.SetParent( newParent == null ? null : newParent._diffuseColor );
		_lightingIntencity.SetParent( newParent == null ? null : newParent._lightingIntencity );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_NormalMap.SetParent( newParent == null ? null : newParent._NormalMap );
		_SpecularMap.SetParent( newParent == null ? null : newParent._SpecularMap );
		_ReflectionMap.SetParent( newParent == null ? null : newParent._ReflectionMap );
		_ReflectivityPinValue.SetParent( newParent == null ? null : newParent._ReflectivityPinValue );
		_outputMul.SetParent( newParent == null ? null : newParent._outputMul );
		_outputAdd.SetParent( newParent == null ? null : newParent._outputAdd );
		_EmissivePinValue.SetParent( newParent == null ? null : newParent._EmissivePinValue );
		_LightingPinValue.SetParent( newParent == null ? null : newParent._LightingPinValue );
		_emissive.SetParent( newParent == null ? null : newParent._emissive );
		_reflectivity.SetParent( newParent == null ? null : newParent._reflectivity );
		_specularPower.SetParent( newParent == null ? null : newParent._specularPower );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_renderFlags.Reset();
		_diffuseColor.Reset();
		_lightingIntencity.Reset();
		_DiffuseMap.Reset();
		_NormalMap.Reset();
		_SpecularMap.Reset();
		_ReflectionMap.Reset();
		_ReflectivityPinValue.Reset();
		_outputMul.Reset();
		_outputAdd.Reset();
		_EmissivePinValue.Reset();
		_LightingPinValue.Reset();
		_emissive.Reset();
		_reflectivity.Reset();
		_specularPower.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _renderFlags.IsDerivedFromParent()
			&& _diffuseColor.IsDerivedFromParent()
			&& _lightingIntencity.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _NormalMap.IsDerivedFromParent()
			&& _SpecularMap.IsDerivedFromParent()
			&& _ReflectionMap.IsDerivedFromParent()
			&& _ReflectivityPinValue.IsDerivedFromParent()
			&& _outputMul.IsDerivedFromParent()
			&& _outputAdd.IsDerivedFromParent()
			&& _EmissivePinValue.IsDerivedFromParent()
			&& _LightingPinValue.IsDerivedFromParent()
			&& _emissive.IsDerivedFromParent()
			&& _reflectivity.IsDerivedFromParent()
			&& _specularPower.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "renderFlags" )
			_renderFlags.Reset();
		else if ( fieldName == "diffuseColor" )
			_diffuseColor.Reset();
		else if ( fieldName == "lightingIntencity" )
			_lightingIntencity.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "NormalMap" )
			_NormalMap.Reset();
		else if ( fieldName == "SpecularMap" )
			_SpecularMap.Reset();
		else if ( fieldName == "ReflectionMap" )
			_ReflectionMap.Reset();
		else if ( fieldName == "ReflectivityPinValue" )
			_ReflectivityPinValue.Reset();
		else if ( fieldName == "outputMul" )
			_outputMul.Reset();
		else if ( fieldName == "outputAdd" )
			_outputAdd.Reset();
		else if ( fieldName == "EmissivePinValue" )
			_EmissivePinValue.Reset();
		else if ( fieldName == "LightingPinValue" )
			_LightingPinValue.Reset();
		else if ( fieldName == "emissive" )
			_emissive.Reset();
		else if ( fieldName == "reflectivity" )
			_reflectivity.Reset();
		else if ( fieldName == "specularPower" )
			_specularPower.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "renderFlags" )
			return _renderFlags.IsDerivedFromParent();
		if ( fieldName == "diffuseColor" )
			return _diffuseColor.IsDerivedFromParent();
		if ( fieldName == "lightingIntencity" )
			return _lightingIntencity.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "NormalMap" )
			return _NormalMap.IsDerivedFromParent();
		if ( fieldName == "SpecularMap" )
			return _SpecularMap.IsDerivedFromParent();
		if ( fieldName == "ReflectionMap" )
			return _ReflectionMap.IsDerivedFromParent();
		if ( fieldName == "ReflectivityPinValue" )
			return _ReflectivityPinValue.IsDerivedFromParent();
		if ( fieldName == "outputMul" )
			return _outputMul.IsDerivedFromParent();
		if ( fieldName == "outputAdd" )
			return _outputAdd.IsDerivedFromParent();
		if ( fieldName == "EmissivePinValue" )
			return _EmissivePinValue.IsDerivedFromParent();
		if ( fieldName == "LightingPinValue" )
			return _LightingPinValue.IsDerivedFromParent();
		if ( fieldName == "emissive" )
			return _emissive.IsDerivedFromParent();
		if ( fieldName == "reflectivity" )
			return _reflectivity.IsDerivedFromParent();
		if ( fieldName == "specularPower" )
			return _specularPower.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("CUBE")]
public class CubeMap : DBResource
{
	private UndoRedoDBPtr<CubeMap> ___parent;
	[HideInOutliner]
	public new DBPtr<CubeMap> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SrcFile _srcFileName_0;
	private SrcFile _srcFileName_1;
	private SrcFile _srcFileName_2;
	private SrcFile _srcFileName_3;
	private SrcFile _srcFileName_4;
	private SrcFile _srcFileName_5;
	private UndoRedo<EPixelFormat> _pixelFormat;
	private UndoRedo<EPower2> _size;

	[Description( "+X Image source" )]
	[SrcFile("Image files", "*.tga")]
	public SrcFile srcFileName_0 { get { return _srcFileName_0; } set { _srcFileName_0.Assign( value ); } }

	[Description( "-X Image source" )]
	[SrcFile("Image files", "*.tga")]
	public SrcFile srcFileName_1 { get { return _srcFileName_1; } set { _srcFileName_1.Assign( value ); } }

	[Description( "+Y Image source" )]
	[SrcFile("Image files", "*.tga")]
	public SrcFile srcFileName_2 { get { return _srcFileName_2; } set { _srcFileName_2.Assign( value ); } }

	[Description( "-Y Image source" )]
	[SrcFile("Image files", "*.tga")]
	public SrcFile srcFileName_3 { get { return _srcFileName_3; } set { _srcFileName_3.Assign( value ); } }

	[Description( "+Z Image source" )]
	[SrcFile("Image files", "*.tga")]
	public SrcFile srcFileName_4 { get { return _srcFileName_4; } set { _srcFileName_4.Assign( value ); } }

	[Description( "-Z Image source" )]
	[SrcFile("Image files", "*.tga")]
	public SrcFile srcFileName_5 { get { return _srcFileName_5; } set { _srcFileName_5.Assign( value ); } }

	[NoCode]
	public EPixelFormat pixelFormat { get { return _pixelFormat.Get(); } set { _pixelFormat.Set( value ); } }

	[NoCode]
	public EPower2 size { get { return _size.Get(); } set { _size.Set( value ); } }

	[DstFile("dds")]
	public string textureFileName { get {
		return libdb.DB.GeneratedCodeUtilities.GenerateRelativePath(
			  DBId
			, "dds"
	); } }
	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CubeMap>(owner);
		_srcFileName_0 = new SrcFile( owner, new SrcFile() );
		_srcFileName_1 = new SrcFile( owner, new SrcFile() );
		_srcFileName_2 = new SrcFile( owner, new SrcFile() );
		_srcFileName_3 = new SrcFile( owner, new SrcFile() );
		_srcFileName_4 = new SrcFile( owner, new SrcFile() );
		_srcFileName_5 = new SrcFile( owner, new SrcFile() );
		_pixelFormat = new UndoRedo<EPixelFormat>( owner, EPixelFormat.DXT1 );
		_size = new UndoRedo<EPower2>( owner, EPower2._256 );
		___parent.Changed += FireChangedEvent;
		_srcFileName_0.Changed += FireChangedEvent;
		_srcFileName_1.Changed += FireChangedEvent;
		_srcFileName_2.Changed += FireChangedEvent;
		_srcFileName_3.Changed += FireChangedEvent;
		_srcFileName_4.Changed += FireChangedEvent;
		_srcFileName_5.Changed += FireChangedEvent;
		_pixelFormat.Changed += FireChangedEvent;
		_size.Changed += FireChangedEvent;
	}

	public CubeMap()
	{
		Initialize( this );
	}
	private void AssignSelf( CubeMap source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CubeMap" );
		srcFileName_0 = source.srcFileName_0;
		srcFileName_1 = source.srcFileName_1;
		srcFileName_2 = source.srcFileName_2;
		srcFileName_3 = source.srcFileName_3;
		srcFileName_4 = source.srcFileName_4;
		srcFileName_5 = source.srcFileName_5;
		pixelFormat = source.pixelFormat;
		size = source.size;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CubeMap source = _source as CubeMap;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CubeMap" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CubeMap newParent = rawParent == null ? null : rawParent.Get<CubeMap>();
		if ( newParent == null && _newParent is CubeMap )
			newParent = _newParent as CubeMap;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_srcFileName_0.SetParent( newParent == null ? null : newParent._srcFileName_0 );
		_srcFileName_1.SetParent( newParent == null ? null : newParent._srcFileName_1 );
		_srcFileName_2.SetParent( newParent == null ? null : newParent._srcFileName_2 );
		_srcFileName_3.SetParent( newParent == null ? null : newParent._srcFileName_3 );
		_srcFileName_4.SetParent( newParent == null ? null : newParent._srcFileName_4 );
		_srcFileName_5.SetParent( newParent == null ? null : newParent._srcFileName_5 );
		_pixelFormat.SetParent( newParent == null ? null : newParent._pixelFormat );
		_size.SetParent( newParent == null ? null : newParent._size );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_srcFileName_0.Reset();
		_srcFileName_1.Reset();
		_srcFileName_2.Reset();
		_srcFileName_3.Reset();
		_srcFileName_4.Reset();
		_srcFileName_5.Reset();
		_pixelFormat.Reset();
		_size.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_srcFileName_0.IsDerivedFromParent()
			&& _srcFileName_1.IsDerivedFromParent()
			&& _srcFileName_2.IsDerivedFromParent()
			&& _srcFileName_3.IsDerivedFromParent()
			&& _srcFileName_4.IsDerivedFromParent()
			&& _srcFileName_5.IsDerivedFromParent()
			&& _pixelFormat.IsDerivedFromParent()
			&& _size.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "srcFileName_0" )
			_srcFileName_0.Reset();
		else if ( fieldName == "srcFileName_1" )
			_srcFileName_1.Reset();
		else if ( fieldName == "srcFileName_2" )
			_srcFileName_2.Reset();
		else if ( fieldName == "srcFileName_3" )
			_srcFileName_3.Reset();
		else if ( fieldName == "srcFileName_4" )
			_srcFileName_4.Reset();
		else if ( fieldName == "srcFileName_5" )
			_srcFileName_5.Reset();
		else if ( fieldName == "pixelFormat" )
			_pixelFormat.Reset();
		else if ( fieldName == "size" )
			_size.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "srcFileName_0" )
			return _srcFileName_0.IsDerivedFromParent();
		if ( fieldName == "srcFileName_1" )
			return _srcFileName_1.IsDerivedFromParent();
		if ( fieldName == "srcFileName_2" )
			return _srcFileName_2.IsDerivedFromParent();
		if ( fieldName == "srcFileName_3" )
			return _srcFileName_3.IsDerivedFromParent();
		if ( fieldName == "srcFileName_4" )
			return _srcFileName_4.IsDerivedFromParent();
		if ( fieldName == "srcFileName_5" )
			return _srcFileName_5.IsDerivedFromParent();
		if ( fieldName == "pixelFormat" )
			return _pixelFormat.IsDerivedFromParent();
		if ( fieldName == "size" )
			return _size.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x4A55D341)]
[UseTypeName("MTRL")]
public class DebugMaterial : Material
{
	private UndoRedoDBPtr<DebugMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<DebugMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<BooleanPin> _DarkMapPinValue;
	private UndoRedo<BooleanPin> _SkeletalMeshPinValue;
	private UndoRedo<DebugPin> _DebugPinValue;

	[Pin2]
	public BooleanPin DarkMapPinValue { get { return _DarkMapPinValue.Get(); } set { _DarkMapPinValue.Set( value ); } }

	[Pin2("SkeletalMeshPin")]
	public BooleanPin SkeletalMeshPinValue { get { return _SkeletalMeshPinValue.Get(); } set { _SkeletalMeshPinValue.Set( value ); } }

	[Pin2]
	public DebugPin DebugPinValue { get { return _DebugPinValue.Get(); } set { _DebugPinValue.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DebugMaterial>(owner);
		_DarkMapPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_SkeletalMeshPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_DebugPinValue = new UndoRedo<DebugPin>( owner, DebugPin.SimpleShading );
		___parent.Changed += FireChangedEvent;
		_DarkMapPinValue.Changed += FireChangedEvent;
		_SkeletalMeshPinValue.Changed += FireChangedEvent;
		_DebugPinValue.Changed += FireChangedEvent;
	}

	public DebugMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( DebugMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DebugMaterial" );
		DarkMapPinValue = source.DarkMapPinValue;
		SkeletalMeshPinValue = source.SkeletalMeshPinValue;
		DebugPinValue = source.DebugPinValue;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DebugMaterial source = _source as DebugMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DebugMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DebugMaterial newParent = rawParent == null ? null : rawParent.Get<DebugMaterial>();
		if ( newParent == null && _newParent is DebugMaterial )
			newParent = _newParent as DebugMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_DarkMapPinValue.SetParent( newParent == null ? null : newParent._DarkMapPinValue );
		_SkeletalMeshPinValue.SetParent( newParent == null ? null : newParent._SkeletalMeshPinValue );
		_DebugPinValue.SetParent( newParent == null ? null : newParent._DebugPinValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_DarkMapPinValue.Reset();
		_SkeletalMeshPinValue.Reset();
		_DebugPinValue.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_DarkMapPinValue.IsDerivedFromParent()
			&& _SkeletalMeshPinValue.IsDerivedFromParent()
			&& _DebugPinValue.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "DarkMapPinValue" )
			_DarkMapPinValue.Reset();
		else if ( fieldName == "SkeletalMeshPinValue" )
			_SkeletalMeshPinValue.Reset();
		else if ( fieldName == "DebugPinValue" )
			_DebugPinValue.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "DarkMapPinValue" )
			return _DarkMapPinValue.IsDerivedFromParent();
		if ( fieldName == "SkeletalMeshPinValue" )
			return _SkeletalMeshPinValue.IsDerivedFromParent();
		if ( fieldName == "DebugPinValue" )
			return _DebugPinValue.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(6)]
[MaterialFunc("BasicMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B625AC0)]
[UseTypeName("MTRL")]
public class DecalMaterial : Material
{
	private UndoRedoDBPtr<DecalMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<DecalMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private Sampler _DiffuseMap;
	private AnimatedHDRColor _DiffuseMul;
	private AnimatedHDRColor _DiffuseAdd;
	private UndoRedo<float> _radius;
	private UndoRedo<BooleanPin> _AccessibilityPinValue;
	private UndoRedo<OpacityAndEmissiveModePin> _OpacityAndEmissiveModePinValue;
	private UndoRedo<BooleanPin> _DistortionPinValue;
	private UndoRedo<BooleanPin> _DecalPlanePinValue;
	private UndoRedo<float> _distortion;
	private UndoRedo<bool> _putOnWater;
	private AnimatedFloat _opacity;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0)]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Category( "Diffuse" )]
	public AnimatedHDRColor DiffuseMul { get { return _DiffuseMul; } set { _DiffuseMul.Assign( value ); } }

	[Category( "Diffuse" )]
	public AnimatedHDRColor DiffuseAdd { get { return _DiffuseAdd; } set { _DiffuseAdd.Assign( value ); } }

	[Description( "Decal radius, in meters" )]
	public float radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	[Category( "Pins" )]
	[Description( "Set this pin to see the object shell and manipulate it. Usually switched off after object placement." )]
	[Pin2]
	public BooleanPin AccessibilityPinValue { get { return _AccessibilityPinValue.Get(); } set { _AccessibilityPinValue.Set( value ); } }

	[Category( "Pins" )]
	[HideEnumValues("Emissive")]
	[Pin2]
	public OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue { get { return _OpacityAndEmissiveModePinValue.Get(); } set { _OpacityAndEmissiveModePinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public BooleanPin DistortionPinValue { get { return _DistortionPinValue.Get(); } set { _DistortionPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public BooleanPin DecalPlanePinValue { get { return _DecalPlanePinValue.Get(); } set { _DecalPlanePinValue.Set( value ); } }

	public float distortion { get { return _distortion.Get(); } set { _distortion.Set( value ); } }

	[NonSignificantField]
	public bool putOnWater { get { return _putOnWater.Get(); } set { _putOnWater.Set( value ); } }

	[NonSignificantField]
	public AnimatedFloat opacity { get { return _opacity; } set { _opacity.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DecalMaterial>(owner);
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.alphaTest = OnOffState.On;
		__renderState.alphaTestRef = 0;
		_renderState = new RenderState( owner, __renderState );
		Sampler __DiffuseMap = new Sampler(); // Construct default object for DiffuseMap
		__DiffuseMap.samplerState.addressU = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressV = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressW = TextureAddressType.Clamp;
		_DiffuseMap = new Sampler( owner, __DiffuseMap );
		_DiffuseMul = new AnimatedHDRColor( owner, 1.0f, 1.0f, 1.0f, 1.0f );
		_DiffuseAdd = new AnimatedHDRColor( owner, 0.0f, 0.0f, 0.0f, 0.0f );
		_radius = new UndoRedo<float>( owner, 5.0f );
		_AccessibilityPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.Present );
		_OpacityAndEmissiveModePinValue = new UndoRedo<OpacityAndEmissiveModePin>( owner, OpacityAndEmissiveModePin.Simple );
		_DistortionPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_DecalPlanePinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.Present );
		_distortion = new UndoRedo<float>( owner, 1.0f );
		_putOnWater = new UndoRedo<bool>( owner, true );
		_opacity = new AnimatedFloat( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_DiffuseMul.Changed += FireChangedEvent;
		_DiffuseAdd.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_AccessibilityPinValue.Changed += FireChangedEvent;
		_OpacityAndEmissiveModePinValue.Changed += FireChangedEvent;
		_DistortionPinValue.Changed += FireChangedEvent;
		_DecalPlanePinValue.Changed += FireChangedEvent;
		_distortion.Changed += FireChangedEvent;
		_putOnWater.Changed += FireChangedEvent;
		_opacity.Changed += FireChangedEvent;
	}

	public DecalMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( DecalMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DecalMaterial" );
		renderState = source.renderState;
		DiffuseMap = source.DiffuseMap;
		DiffuseMul = source.DiffuseMul;
		DiffuseAdd = source.DiffuseAdd;
		radius = source.radius;
		AccessibilityPinValue = source.AccessibilityPinValue;
		OpacityAndEmissiveModePinValue = source.OpacityAndEmissiveModePinValue;
		DistortionPinValue = source.DistortionPinValue;
		DecalPlanePinValue = source.DecalPlanePinValue;
		distortion = source.distortion;
		putOnWater = source.putOnWater;
		opacity = source.opacity;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DecalMaterial source = _source as DecalMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DecalMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DecalMaterial newParent = rawParent == null ? null : rawParent.Get<DecalMaterial>();
		if ( newParent == null && _newParent is DecalMaterial )
			newParent = _newParent as DecalMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_DiffuseMul.SetParent( newParent == null ? null : newParent._DiffuseMul );
		_DiffuseAdd.SetParent( newParent == null ? null : newParent._DiffuseAdd );
		_radius.SetParent( newParent == null ? null : newParent._radius );
		_AccessibilityPinValue.SetParent( newParent == null ? null : newParent._AccessibilityPinValue );
		_OpacityAndEmissiveModePinValue.SetParent( newParent == null ? null : newParent._OpacityAndEmissiveModePinValue );
		_DistortionPinValue.SetParent( newParent == null ? null : newParent._DistortionPinValue );
		_DecalPlanePinValue.SetParent( newParent == null ? null : newParent._DecalPlanePinValue );
		_distortion.SetParent( newParent == null ? null : newParent._distortion );
		_putOnWater.SetParent( newParent == null ? null : newParent._putOnWater );
		_opacity.SetParent( newParent == null ? null : newParent._opacity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_DiffuseMap.Reset();
		_DiffuseMul.Reset();
		_DiffuseAdd.Reset();
		_radius.Reset();
		_AccessibilityPinValue.Reset();
		_OpacityAndEmissiveModePinValue.Reset();
		_DistortionPinValue.Reset();
		_DecalPlanePinValue.Reset();
		_distortion.Reset();
		_putOnWater.Reset();
		_opacity.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _DiffuseMul.IsDerivedFromParent()
			&& _DiffuseAdd.IsDerivedFromParent()
			&& _radius.IsDerivedFromParent()
			&& _AccessibilityPinValue.IsDerivedFromParent()
			&& _OpacityAndEmissiveModePinValue.IsDerivedFromParent()
			&& _DistortionPinValue.IsDerivedFromParent()
			&& _DecalPlanePinValue.IsDerivedFromParent()
			&& _distortion.IsDerivedFromParent()
			&& _putOnWater.IsDerivedFromParent()
			&& _opacity.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "DiffuseMul" )
			_DiffuseMul.Reset();
		else if ( fieldName == "DiffuseAdd" )
			_DiffuseAdd.Reset();
		else if ( fieldName == "radius" )
			_radius.Reset();
		else if ( fieldName == "AccessibilityPinValue" )
			_AccessibilityPinValue.Reset();
		else if ( fieldName == "OpacityAndEmissiveModePinValue" )
			_OpacityAndEmissiveModePinValue.Reset();
		else if ( fieldName == "DistortionPinValue" )
			_DistortionPinValue.Reset();
		else if ( fieldName == "DecalPlanePinValue" )
			_DecalPlanePinValue.Reset();
		else if ( fieldName == "distortion" )
			_distortion.Reset();
		else if ( fieldName == "putOnWater" )
			_putOnWater.Reset();
		else if ( fieldName == "opacity" )
			_opacity.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "DiffuseMul" )
			return _DiffuseMul.IsDerivedFromParent();
		if ( fieldName == "DiffuseAdd" )
			return _DiffuseAdd.IsDerivedFromParent();
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
		if ( fieldName == "AccessibilityPinValue" )
			return _AccessibilityPinValue.IsDerivedFromParent();
		if ( fieldName == "OpacityAndEmissiveModePinValue" )
			return _OpacityAndEmissiveModePinValue.IsDerivedFromParent();
		if ( fieldName == "DistortionPinValue" )
			return _DistortionPinValue.IsDerivedFromParent();
		if ( fieldName == "DecalPlanePinValue" )
			return _DecalPlanePinValue.IsDerivedFromParent();
		if ( fieldName == "distortion" )
			return _distortion.IsDerivedFromParent();
		if ( fieldName == "putOnWater" )
			return _putOnWater.IsDerivedFromParent();
		if ( fieldName == "opacity" )
			return _opacity.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialFunc("BasicMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x37B47B00)]
[UseTypeName("MTRL")]
public class DecalTerrainMaterial : Material
{
	private UndoRedoDBPtr<DecalTerrainMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<DecalTerrainMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private Sampler _DiffuseMap;
	private Sampler _MaskMap;
	private AnimatedHDRColor _DiffuseMul;
	private AnimatedHDRColor _DiffuseAdd;
	private UndoRedo<float> _radius;
	private UndoRedo<BooleanPin> _AccessibilityPinValue;
	private UndoRedo<OpacityAndEmissiveModePin> _OpacityAndEmissiveModePinValue;
	private UndoRedo<BooleanPin> _DistortionPinValue;
	private UndoRedo<BooleanPin> _DecalPlanePinValue;
	private UndoRedo<float> _distortion;
	private UndoRedo<bool> _putOnWater;
	private AnimatedFloat _opacity;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0)]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Category( "Diffuse" )]
	[Sampler(1)]
	public Sampler MaskMap { get { return _MaskMap; } set { _MaskMap.Assign( value ); } }

	[Category( "Diffuse" )]
	public AnimatedHDRColor DiffuseMul { get { return _DiffuseMul; } set { _DiffuseMul.Assign( value ); } }

	[Category( "Diffuse" )]
	public AnimatedHDRColor DiffuseAdd { get { return _DiffuseAdd; } set { _DiffuseAdd.Assign( value ); } }

	[Description( "Decal radius, in meters" )]
	public float radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	[Category( "Pins" )]
	[Description( "Set this pin to see the object shell and manipulate it. Usually switched off after object placement." )]
	[Pin2]
	public BooleanPin AccessibilityPinValue { get { return _AccessibilityPinValue.Get(); } set { _AccessibilityPinValue.Set( value ); } }

	[Category( "Pins" )]
	[HideEnumValues("Emissive")]
	[Pin2]
	public OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue { get { return _OpacityAndEmissiveModePinValue.Get(); } set { _OpacityAndEmissiveModePinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public BooleanPin DistortionPinValue { get { return _DistortionPinValue.Get(); } set { _DistortionPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public BooleanPin DecalPlanePinValue { get { return _DecalPlanePinValue.Get(); } set { _DecalPlanePinValue.Set( value ); } }

	public float distortion { get { return _distortion.Get(); } set { _distortion.Set( value ); } }

	[NonSignificantField]
	public bool putOnWater { get { return _putOnWater.Get(); } set { _putOnWater.Set( value ); } }

	[NonSignificantField]
	public AnimatedFloat opacity { get { return _opacity; } set { _opacity.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DecalTerrainMaterial>(owner);
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.alphaTest = OnOffState.On;
		__renderState.alphaTestRef = 0;
		_renderState = new RenderState( owner, __renderState );
		Sampler __DiffuseMap = new Sampler(); // Construct default object for DiffuseMap
		__DiffuseMap.samplerState.addressU = TextureAddressType.Border;
		__DiffuseMap.samplerState.addressV = TextureAddressType.Border;
		__DiffuseMap.samplerState.addressW = TextureAddressType.Border;
		_DiffuseMap = new Sampler( owner, __DiffuseMap );
		Sampler __MaskMap = new Sampler(); // Construct default object for MaskMap
		__MaskMap.samplerState.addressU = TextureAddressType.Border;
		__MaskMap.samplerState.addressV = TextureAddressType.Border;
		__MaskMap.samplerState.addressW = TextureAddressType.Border;
		_MaskMap = new Sampler( owner, __MaskMap );
		_DiffuseMul = new AnimatedHDRColor( owner, 1.0f, 1.0f, 1.0f, 1.0f );
		_DiffuseAdd = new AnimatedHDRColor( owner, 0.0f, 0.0f, 0.0f, 0.0f );
		_radius = new UndoRedo<float>( owner, 5.0f );
		_AccessibilityPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.Present );
		_OpacityAndEmissiveModePinValue = new UndoRedo<OpacityAndEmissiveModePin>( owner, OpacityAndEmissiveModePin.Simple );
		_DistortionPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_DecalPlanePinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.Present );
		_distortion = new UndoRedo<float>( owner, 1.0f );
		_putOnWater = new UndoRedo<bool>( owner, true );
		_opacity = new AnimatedFloat( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_MaskMap.Changed += FireChangedEvent;
		_DiffuseMul.Changed += FireChangedEvent;
		_DiffuseAdd.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_AccessibilityPinValue.Changed += FireChangedEvent;
		_OpacityAndEmissiveModePinValue.Changed += FireChangedEvent;
		_DistortionPinValue.Changed += FireChangedEvent;
		_DecalPlanePinValue.Changed += FireChangedEvent;
		_distortion.Changed += FireChangedEvent;
		_putOnWater.Changed += FireChangedEvent;
		_opacity.Changed += FireChangedEvent;
	}

	public DecalTerrainMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( DecalTerrainMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DecalTerrainMaterial" );
		renderState = source.renderState;
		DiffuseMap = source.DiffuseMap;
		MaskMap = source.MaskMap;
		DiffuseMul = source.DiffuseMul;
		DiffuseAdd = source.DiffuseAdd;
		radius = source.radius;
		AccessibilityPinValue = source.AccessibilityPinValue;
		OpacityAndEmissiveModePinValue = source.OpacityAndEmissiveModePinValue;
		DistortionPinValue = source.DistortionPinValue;
		DecalPlanePinValue = source.DecalPlanePinValue;
		distortion = source.distortion;
		putOnWater = source.putOnWater;
		opacity = source.opacity;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DecalTerrainMaterial source = _source as DecalTerrainMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DecalTerrainMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DecalTerrainMaterial newParent = rawParent == null ? null : rawParent.Get<DecalTerrainMaterial>();
		if ( newParent == null && _newParent is DecalTerrainMaterial )
			newParent = _newParent as DecalTerrainMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_MaskMap.SetParent( newParent == null ? null : newParent._MaskMap );
		_DiffuseMul.SetParent( newParent == null ? null : newParent._DiffuseMul );
		_DiffuseAdd.SetParent( newParent == null ? null : newParent._DiffuseAdd );
		_radius.SetParent( newParent == null ? null : newParent._radius );
		_AccessibilityPinValue.SetParent( newParent == null ? null : newParent._AccessibilityPinValue );
		_OpacityAndEmissiveModePinValue.SetParent( newParent == null ? null : newParent._OpacityAndEmissiveModePinValue );
		_DistortionPinValue.SetParent( newParent == null ? null : newParent._DistortionPinValue );
		_DecalPlanePinValue.SetParent( newParent == null ? null : newParent._DecalPlanePinValue );
		_distortion.SetParent( newParent == null ? null : newParent._distortion );
		_putOnWater.SetParent( newParent == null ? null : newParent._putOnWater );
		_opacity.SetParent( newParent == null ? null : newParent._opacity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_DiffuseMap.Reset();
		_MaskMap.Reset();
		_DiffuseMul.Reset();
		_DiffuseAdd.Reset();
		_radius.Reset();
		_AccessibilityPinValue.Reset();
		_OpacityAndEmissiveModePinValue.Reset();
		_DistortionPinValue.Reset();
		_DecalPlanePinValue.Reset();
		_distortion.Reset();
		_putOnWater.Reset();
		_opacity.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _MaskMap.IsDerivedFromParent()
			&& _DiffuseMul.IsDerivedFromParent()
			&& _DiffuseAdd.IsDerivedFromParent()
			&& _radius.IsDerivedFromParent()
			&& _AccessibilityPinValue.IsDerivedFromParent()
			&& _OpacityAndEmissiveModePinValue.IsDerivedFromParent()
			&& _DistortionPinValue.IsDerivedFromParent()
			&& _DecalPlanePinValue.IsDerivedFromParent()
			&& _distortion.IsDerivedFromParent()
			&& _putOnWater.IsDerivedFromParent()
			&& _opacity.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "MaskMap" )
			_MaskMap.Reset();
		else if ( fieldName == "DiffuseMul" )
			_DiffuseMul.Reset();
		else if ( fieldName == "DiffuseAdd" )
			_DiffuseAdd.Reset();
		else if ( fieldName == "radius" )
			_radius.Reset();
		else if ( fieldName == "AccessibilityPinValue" )
			_AccessibilityPinValue.Reset();
		else if ( fieldName == "OpacityAndEmissiveModePinValue" )
			_OpacityAndEmissiveModePinValue.Reset();
		else if ( fieldName == "DistortionPinValue" )
			_DistortionPinValue.Reset();
		else if ( fieldName == "DecalPlanePinValue" )
			_DecalPlanePinValue.Reset();
		else if ( fieldName == "distortion" )
			_distortion.Reset();
		else if ( fieldName == "putOnWater" )
			_putOnWater.Reset();
		else if ( fieldName == "opacity" )
			_opacity.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "MaskMap" )
			return _MaskMap.IsDerivedFromParent();
		if ( fieldName == "DiffuseMul" )
			return _DiffuseMul.IsDerivedFromParent();
		if ( fieldName == "DiffuseAdd" )
			return _DiffuseAdd.IsDerivedFromParent();
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
		if ( fieldName == "AccessibilityPinValue" )
			return _AccessibilityPinValue.IsDerivedFromParent();
		if ( fieldName == "OpacityAndEmissiveModePinValue" )
			return _OpacityAndEmissiveModePinValue.IsDerivedFromParent();
		if ( fieldName == "DistortionPinValue" )
			return _DistortionPinValue.IsDerivedFromParent();
		if ( fieldName == "DecalPlanePinValue" )
			return _DecalPlanePinValue.IsDerivedFromParent();
		if ( fieldName == "distortion" )
			return _distortion.IsDerivedFromParent();
		if ( fieldName == "putOnWater" )
			return _putOnWater.IsDerivedFromParent();
		if ( fieldName == "opacity" )
			return _opacity.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(3)]
[MaterialFunc("DropMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)", "ModifyReflectionColor(const Render::HDRColor& _color0, const Render::HDRColor& _color1, const Render::HDRColor& _color2, const Render::HDRColor& _color3)")]
[MaterialGroup("BaseMaterial")]
[TypeId(0xC8667D00)]
[UseTypeName("MTRL")]
public class DropMaterial : Material
{
	private UndoRedoDBPtr<DropMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<DropMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private UndoRedo<MaterialFlags> _renderFlags;
	private HDRColor _diffuseColor;
	private UndoRedo<float> _lightingIntencity;
	private UndoRedo<float> _ambientIntensity;
	private HDRColor _additionalAmbient;
	private Sampler _DiffuseMap;
	private Sampler _NormalMap;
	private UndoRedo<BooleanPin> _NormalMapPinValue;
	private SamplerEx _SpecularMap;
	private UndoRedo<BooleanPin> _SpecularMapPinValue;
	private SamplerCube _ReflectionMap;
	private UndoRedo<ReflectivityPin> _ReflectivityPinValue;
	private UndoRedo<TextureColorizePin> _colorizeReflectionMap;
	private HDRColor _reflectionMapColor0;
	private HDRColor _reflectionMapColor1;
	private HDRColor _reflectionMapColor2;
	private HDRColor _reflectionMapColor3;
	private HDRColor _outputMul;
	private HDRColor _outputAdd;
	private UndoRedo<BooleanPin> _SkeletalMeshPinValue;
	private UndoRedo<LightModePin> _LightModePinValue;
	private UndoRedo<float> _emissive;
	private AnimatedFloat _opacity;
	private UndoRedo<float> _reflectivityLerp;
	private UndoRedo<float> _reflectivityAdd;
	private UndoRedo<float> _reflectivityMul;
	private UndoRedo<float> _specularPower;
	private AnimatedFloat _uOffset1;
	private AnimatedFloat _vOffset1;
	private AnimatedFloat _uOffset2;
	private AnimatedFloat _vOffset2;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "States" )]
	[NoCode]
	public MaterialFlags renderFlags { get { return _renderFlags.Get(); } set { _renderFlags.Set( value ); } }

	[Category( "Lighting" )]
	public HDRColor diffuseColor { get { return _diffuseColor; } set { _diffuseColor.Assign( value ); } }

	[Category( "Lighting" )]
	public float lightingIntencity { get { return _lightingIntencity.Get(); } set { _lightingIntencity.Set( value ); } }

	[Category( "Lighting" )]
	public float ambientIntensity { get { return _ambientIntensity.Get(); } set { _ambientIntensity.Set( value ); } }

	[Category( "Lighting" )]
	public HDRColor additionalAmbient { get { return _additionalAmbient; } set { _additionalAmbient.Assign( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0, "DiffuseMap", true)]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Category( "Normal" )]
	[Sampler(1, true)]
	public Sampler NormalMap { get { return _NormalMap; } set { _NormalMap.Assign( value ); } }

	[Category( "Normal" )]
	[Pin2]
	public BooleanPin NormalMapPinValue { get { return _NormalMapPinValue.Get(); } set { _NormalMapPinValue.Set( value ); } }

	[Category( "Specular" )]
	[Sampler(2, true)]
	public SamplerEx SpecularMap { get { return _SpecularMap; } set { _SpecularMap.Assign( value ); } }

	[Category( "Specular" )]
	[Pin2]
	public BooleanPin SpecularMapPinValue { get { return _SpecularMapPinValue.Get(); } set { _SpecularMapPinValue.Set( value ); } }

	[Category( "Reflection" )]
	[Sampler(3, true)]
	public SamplerCube ReflectionMap { get { return _ReflectionMap; } set { _ReflectionMap.Assign( value ); } }

	[Category( "Reflection" )]
	[Pin2]
	public ReflectivityPin ReflectivityPinValue { get { return _ReflectivityPinValue.Get(); } set { _ReflectivityPinValue.Set( value ); } }

	[Category( "Reflection" )]
	[Pin2]
	public TextureColorizePin colorizeReflectionMap { get { return _colorizeReflectionMap.Get(); } set { _colorizeReflectionMap.Set( value ); } }

	[Category( "Reflection" )]
	public HDRColor reflectionMapColor0 { get { return _reflectionMapColor0; } set { _reflectionMapColor0.Assign( value ); } }

	[Category( "Reflection" )]
	public HDRColor reflectionMapColor1 { get { return _reflectionMapColor1; } set { _reflectionMapColor1.Assign( value ); } }

	[Category( "Reflection" )]
	public HDRColor reflectionMapColor2 { get { return _reflectionMapColor2; } set { _reflectionMapColor2.Assign( value ); } }

	[Category( "Reflection" )]
	public HDRColor reflectionMapColor3 { get { return _reflectionMapColor3; } set { _reflectionMapColor3.Assign( value ); } }

	[Category( "Modificator" )]
	public HDRColor outputMul { get { return _outputMul; } set { _outputMul.Assign( value ); } }

	[Category( "Modificator" )]
	public HDRColor outputAdd { get { return _outputAdd; } set { _outputAdd.Assign( value ); } }

	[Category( "Pins" )]
	[Pin2("SkeletalMeshPin")]
	public BooleanPin SkeletalMeshPinValue { get { return _SkeletalMeshPinValue.Get(); } set { _SkeletalMeshPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public LightModePin LightModePinValue { get { return _LightModePinValue.Get(); } set { _LightModePinValue.Set( value ); } }

	public float emissive { get { return _emissive.Get(); } set { _emissive.Set( value ); } }

	public AnimatedFloat opacity { get { return _opacity; } set { _opacity.Assign( value ); } }

	[FloatMinMax(0, 1)]
	public float reflectivityLerp { get { return _reflectivityLerp.Get(); } set { _reflectivityLerp.Set( value ); } }

	public float reflectivityAdd { get { return _reflectivityAdd.Get(); } set { _reflectivityAdd.Set( value ); } }

	public float reflectivityMul { get { return _reflectivityMul.Get(); } set { _reflectivityMul.Set( value ); } }

	public float specularPower { get { return _specularPower.Get(); } set { _specularPower.Set( value ); } }

	public AnimatedFloat uOffset1 { get { return _uOffset1; } set { _uOffset1.Assign( value ); } }

	public AnimatedFloat vOffset1 { get { return _vOffset1; } set { _vOffset1.Assign( value ); } }

	public AnimatedFloat uOffset2 { get { return _uOffset2; } set { _uOffset2.Assign( value ); } }

	public AnimatedFloat vOffset2 { get { return _vOffset2; } set { _vOffset2.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DropMaterial>(owner);
		_renderState = new RenderState( owner );
		_renderFlags = new UndoRedo<MaterialFlags>( owner, MaterialFlags.ShadowReceiver );
		HDRColor __diffuseColor = new HDRColor(); // Construct default object for diffuseColor
		__diffuseColor.R = 1.0f;
		__diffuseColor.G = 1.0f;
		__diffuseColor.B = 1.0f;
		_diffuseColor = new HDRColor( owner, __diffuseColor );
		_lightingIntencity = new UndoRedo<float>( owner, 1.0f );
		_ambientIntensity = new UndoRedo<float>( owner, 1.0f );
		_additionalAmbient = new HDRColor( owner );
		_DiffuseMap = new Sampler( owner );
		_NormalMap = new Sampler( owner );
		_NormalMapPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		SamplerEx __SpecularMap = new SamplerEx(); // Construct default object for SpecularMap
		__SpecularMap.Multiplier.R = 1.0f;
		__SpecularMap.Multiplier.G = 1.0f;
		__SpecularMap.Multiplier.B = 1.0f;
		__SpecularMap.Add.A = 0.0f;
		_SpecularMap = new SamplerEx( owner, __SpecularMap );
		_SpecularMapPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_ReflectionMap = new SamplerCube( owner );
		_ReflectivityPinValue = new UndoRedo<ReflectivityPin>( owner, ReflectivityPin.ReflectivityOff );
		_colorizeReflectionMap = new UndoRedo<TextureColorizePin>( owner, TextureColorizePin.NoColor );
		HDRColor __reflectionMapColor0 = new HDRColor(); // Construct default object for reflectionMapColor0
		__reflectionMapColor0.R = 1.0f;
		__reflectionMapColor0.G = 1.0f;
		__reflectionMapColor0.B = 1.0f;
		_reflectionMapColor0 = new HDRColor( owner, __reflectionMapColor0 );
		HDRColor __reflectionMapColor1 = new HDRColor(); // Construct default object for reflectionMapColor1
		__reflectionMapColor1.R = 1.0f;
		__reflectionMapColor1.G = 1.0f;
		__reflectionMapColor1.B = 1.0f;
		_reflectionMapColor1 = new HDRColor( owner, __reflectionMapColor1 );
		HDRColor __reflectionMapColor2 = new HDRColor(); // Construct default object for reflectionMapColor2
		__reflectionMapColor2.R = 1.0f;
		__reflectionMapColor2.G = 1.0f;
		__reflectionMapColor2.B = 1.0f;
		_reflectionMapColor2 = new HDRColor( owner, __reflectionMapColor2 );
		HDRColor __reflectionMapColor3 = new HDRColor(); // Construct default object for reflectionMapColor3
		__reflectionMapColor3.R = 1.0f;
		__reflectionMapColor3.G = 1.0f;
		__reflectionMapColor3.B = 1.0f;
		_reflectionMapColor3 = new HDRColor( owner, __reflectionMapColor3 );
		HDRColor __outputMul = new HDRColor(); // Construct default object for outputMul
		__outputMul.R = 1.0f;
		__outputMul.G = 1.0f;
		__outputMul.B = 1.0f;
		_outputMul = new HDRColor( owner, __outputMul );
		HDRColor __outputAdd = new HDRColor(); // Construct default object for outputAdd
		__outputAdd.A = 0.0f;
		_outputAdd = new HDRColor( owner, __outputAdd );
		_SkeletalMeshPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_LightModePinValue = new UndoRedo<LightModePin>( owner, LightModePin.Diffuse );
		_emissive = new UndoRedo<float>( owner, 0.0f );
		_opacity = new AnimatedFloat( owner, 1.0f );
		_reflectivityLerp = new UndoRedo<float>( owner, 0.0f );
		_reflectivityAdd = new UndoRedo<float>( owner, 0.0f );
		_reflectivityMul = new UndoRedo<float>( owner, 0.0f );
		_specularPower = new UndoRedo<float>( owner, 10.0f );
		_uOffset1 = new AnimatedFloat( owner );
		_vOffset1 = new AnimatedFloat( owner );
		_uOffset2 = new AnimatedFloat( owner );
		_vOffset2 = new AnimatedFloat( owner );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_renderFlags.Changed += FireChangedEvent;
		_diffuseColor.Changed += FireChangedEvent;
		_lightingIntencity.Changed += FireChangedEvent;
		_ambientIntensity.Changed += FireChangedEvent;
		_additionalAmbient.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_NormalMap.Changed += FireChangedEvent;
		_NormalMapPinValue.Changed += FireChangedEvent;
		_SpecularMap.Changed += FireChangedEvent;
		_SpecularMapPinValue.Changed += FireChangedEvent;
		_ReflectionMap.Changed += FireChangedEvent;
		_ReflectivityPinValue.Changed += FireChangedEvent;
		_colorizeReflectionMap.Changed += FireChangedEvent;
		_reflectionMapColor0.Changed += FireChangedEvent;
		_reflectionMapColor1.Changed += FireChangedEvent;
		_reflectionMapColor2.Changed += FireChangedEvent;
		_reflectionMapColor3.Changed += FireChangedEvent;
		_outputMul.Changed += FireChangedEvent;
		_outputAdd.Changed += FireChangedEvent;
		_SkeletalMeshPinValue.Changed += FireChangedEvent;
		_LightModePinValue.Changed += FireChangedEvent;
		_emissive.Changed += FireChangedEvent;
		_opacity.Changed += FireChangedEvent;
		_reflectivityLerp.Changed += FireChangedEvent;
		_reflectivityAdd.Changed += FireChangedEvent;
		_reflectivityMul.Changed += FireChangedEvent;
		_specularPower.Changed += FireChangedEvent;
		_uOffset1.Changed += FireChangedEvent;
		_vOffset1.Changed += FireChangedEvent;
		_uOffset2.Changed += FireChangedEvent;
		_vOffset2.Changed += FireChangedEvent;
	}

	public DropMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( DropMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DropMaterial" );
		renderState = source.renderState;
		renderFlags = source.renderFlags;
		diffuseColor = source.diffuseColor;
		lightingIntencity = source.lightingIntencity;
		ambientIntensity = source.ambientIntensity;
		additionalAmbient = source.additionalAmbient;
		DiffuseMap = source.DiffuseMap;
		NormalMap = source.NormalMap;
		NormalMapPinValue = source.NormalMapPinValue;
		SpecularMap = source.SpecularMap;
		SpecularMapPinValue = source.SpecularMapPinValue;
		ReflectionMap = source.ReflectionMap;
		ReflectivityPinValue = source.ReflectivityPinValue;
		colorizeReflectionMap = source.colorizeReflectionMap;
		reflectionMapColor0 = source.reflectionMapColor0;
		reflectionMapColor1 = source.reflectionMapColor1;
		reflectionMapColor2 = source.reflectionMapColor2;
		reflectionMapColor3 = source.reflectionMapColor3;
		outputMul = source.outputMul;
		outputAdd = source.outputAdd;
		SkeletalMeshPinValue = source.SkeletalMeshPinValue;
		LightModePinValue = source.LightModePinValue;
		emissive = source.emissive;
		opacity = source.opacity;
		reflectivityLerp = source.reflectivityLerp;
		reflectivityAdd = source.reflectivityAdd;
		reflectivityMul = source.reflectivityMul;
		specularPower = source.specularPower;
		uOffset1 = source.uOffset1;
		vOffset1 = source.vOffset1;
		uOffset2 = source.uOffset2;
		vOffset2 = source.vOffset2;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DropMaterial source = _source as DropMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DropMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DropMaterial newParent = rawParent == null ? null : rawParent.Get<DropMaterial>();
		if ( newParent == null && _newParent is DropMaterial )
			newParent = _newParent as DropMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_renderFlags.SetParent( newParent == null ? null : newParent._renderFlags );
		_diffuseColor.SetParent( newParent == null ? null : newParent._diffuseColor );
		_lightingIntencity.SetParent( newParent == null ? null : newParent._lightingIntencity );
		_ambientIntensity.SetParent( newParent == null ? null : newParent._ambientIntensity );
		_additionalAmbient.SetParent( newParent == null ? null : newParent._additionalAmbient );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_NormalMap.SetParent( newParent == null ? null : newParent._NormalMap );
		_NormalMapPinValue.SetParent( newParent == null ? null : newParent._NormalMapPinValue );
		_SpecularMap.SetParent( newParent == null ? null : newParent._SpecularMap );
		_SpecularMapPinValue.SetParent( newParent == null ? null : newParent._SpecularMapPinValue );
		_ReflectionMap.SetParent( newParent == null ? null : newParent._ReflectionMap );
		_ReflectivityPinValue.SetParent( newParent == null ? null : newParent._ReflectivityPinValue );
		_colorizeReflectionMap.SetParent( newParent == null ? null : newParent._colorizeReflectionMap );
		_reflectionMapColor0.SetParent( newParent == null ? null : newParent._reflectionMapColor0 );
		_reflectionMapColor1.SetParent( newParent == null ? null : newParent._reflectionMapColor1 );
		_reflectionMapColor2.SetParent( newParent == null ? null : newParent._reflectionMapColor2 );
		_reflectionMapColor3.SetParent( newParent == null ? null : newParent._reflectionMapColor3 );
		_outputMul.SetParent( newParent == null ? null : newParent._outputMul );
		_outputAdd.SetParent( newParent == null ? null : newParent._outputAdd );
		_SkeletalMeshPinValue.SetParent( newParent == null ? null : newParent._SkeletalMeshPinValue );
		_LightModePinValue.SetParent( newParent == null ? null : newParent._LightModePinValue );
		_emissive.SetParent( newParent == null ? null : newParent._emissive );
		_opacity.SetParent( newParent == null ? null : newParent._opacity );
		_reflectivityLerp.SetParent( newParent == null ? null : newParent._reflectivityLerp );
		_reflectivityAdd.SetParent( newParent == null ? null : newParent._reflectivityAdd );
		_reflectivityMul.SetParent( newParent == null ? null : newParent._reflectivityMul );
		_specularPower.SetParent( newParent == null ? null : newParent._specularPower );
		_uOffset1.SetParent( newParent == null ? null : newParent._uOffset1 );
		_vOffset1.SetParent( newParent == null ? null : newParent._vOffset1 );
		_uOffset2.SetParent( newParent == null ? null : newParent._uOffset2 );
		_vOffset2.SetParent( newParent == null ? null : newParent._vOffset2 );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_renderFlags.Reset();
		_diffuseColor.Reset();
		_lightingIntencity.Reset();
		_ambientIntensity.Reset();
		_additionalAmbient.Reset();
		_DiffuseMap.Reset();
		_NormalMap.Reset();
		_NormalMapPinValue.Reset();
		_SpecularMap.Reset();
		_SpecularMapPinValue.Reset();
		_ReflectionMap.Reset();
		_ReflectivityPinValue.Reset();
		_colorizeReflectionMap.Reset();
		_reflectionMapColor0.Reset();
		_reflectionMapColor1.Reset();
		_reflectionMapColor2.Reset();
		_reflectionMapColor3.Reset();
		_outputMul.Reset();
		_outputAdd.Reset();
		_SkeletalMeshPinValue.Reset();
		_LightModePinValue.Reset();
		_emissive.Reset();
		_opacity.Reset();
		_reflectivityLerp.Reset();
		_reflectivityAdd.Reset();
		_reflectivityMul.Reset();
		_specularPower.Reset();
		_uOffset1.Reset();
		_vOffset1.Reset();
		_uOffset2.Reset();
		_vOffset2.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _renderFlags.IsDerivedFromParent()
			&& _diffuseColor.IsDerivedFromParent()
			&& _lightingIntencity.IsDerivedFromParent()
			&& _ambientIntensity.IsDerivedFromParent()
			&& _additionalAmbient.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _NormalMap.IsDerivedFromParent()
			&& _NormalMapPinValue.IsDerivedFromParent()
			&& _SpecularMap.IsDerivedFromParent()
			&& _SpecularMapPinValue.IsDerivedFromParent()
			&& _ReflectionMap.IsDerivedFromParent()
			&& _ReflectivityPinValue.IsDerivedFromParent()
			&& _colorizeReflectionMap.IsDerivedFromParent()
			&& _reflectionMapColor0.IsDerivedFromParent()
			&& _reflectionMapColor1.IsDerivedFromParent()
			&& _reflectionMapColor2.IsDerivedFromParent()
			&& _reflectionMapColor3.IsDerivedFromParent()
			&& _outputMul.IsDerivedFromParent()
			&& _outputAdd.IsDerivedFromParent()
			&& _SkeletalMeshPinValue.IsDerivedFromParent()
			&& _LightModePinValue.IsDerivedFromParent()
			&& _emissive.IsDerivedFromParent()
			&& _opacity.IsDerivedFromParent()
			&& _reflectivityLerp.IsDerivedFromParent()
			&& _reflectivityAdd.IsDerivedFromParent()
			&& _reflectivityMul.IsDerivedFromParent()
			&& _specularPower.IsDerivedFromParent()
			&& _uOffset1.IsDerivedFromParent()
			&& _vOffset1.IsDerivedFromParent()
			&& _uOffset2.IsDerivedFromParent()
			&& _vOffset2.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "renderFlags" )
			_renderFlags.Reset();
		else if ( fieldName == "diffuseColor" )
			_diffuseColor.Reset();
		else if ( fieldName == "lightingIntencity" )
			_lightingIntencity.Reset();
		else if ( fieldName == "ambientIntensity" )
			_ambientIntensity.Reset();
		else if ( fieldName == "additionalAmbient" )
			_additionalAmbient.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "NormalMap" )
			_NormalMap.Reset();
		else if ( fieldName == "NormalMapPinValue" )
			_NormalMapPinValue.Reset();
		else if ( fieldName == "SpecularMap" )
			_SpecularMap.Reset();
		else if ( fieldName == "SpecularMapPinValue" )
			_SpecularMapPinValue.Reset();
		else if ( fieldName == "ReflectionMap" )
			_ReflectionMap.Reset();
		else if ( fieldName == "ReflectivityPinValue" )
			_ReflectivityPinValue.Reset();
		else if ( fieldName == "colorizeReflectionMap" )
			_colorizeReflectionMap.Reset();
		else if ( fieldName == "reflectionMapColor0" )
			_reflectionMapColor0.Reset();
		else if ( fieldName == "reflectionMapColor1" )
			_reflectionMapColor1.Reset();
		else if ( fieldName == "reflectionMapColor2" )
			_reflectionMapColor2.Reset();
		else if ( fieldName == "reflectionMapColor3" )
			_reflectionMapColor3.Reset();
		else if ( fieldName == "outputMul" )
			_outputMul.Reset();
		else if ( fieldName == "outputAdd" )
			_outputAdd.Reset();
		else if ( fieldName == "SkeletalMeshPinValue" )
			_SkeletalMeshPinValue.Reset();
		else if ( fieldName == "LightModePinValue" )
			_LightModePinValue.Reset();
		else if ( fieldName == "emissive" )
			_emissive.Reset();
		else if ( fieldName == "opacity" )
			_opacity.Reset();
		else if ( fieldName == "reflectivityLerp" )
			_reflectivityLerp.Reset();
		else if ( fieldName == "reflectivityAdd" )
			_reflectivityAdd.Reset();
		else if ( fieldName == "reflectivityMul" )
			_reflectivityMul.Reset();
		else if ( fieldName == "specularPower" )
			_specularPower.Reset();
		else if ( fieldName == "uOffset1" )
			_uOffset1.Reset();
		else if ( fieldName == "vOffset1" )
			_vOffset1.Reset();
		else if ( fieldName == "uOffset2" )
			_uOffset2.Reset();
		else if ( fieldName == "vOffset2" )
			_vOffset2.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "renderFlags" )
			return _renderFlags.IsDerivedFromParent();
		if ( fieldName == "diffuseColor" )
			return _diffuseColor.IsDerivedFromParent();
		if ( fieldName == "lightingIntencity" )
			return _lightingIntencity.IsDerivedFromParent();
		if ( fieldName == "ambientIntensity" )
			return _ambientIntensity.IsDerivedFromParent();
		if ( fieldName == "additionalAmbient" )
			return _additionalAmbient.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "NormalMap" )
			return _NormalMap.IsDerivedFromParent();
		if ( fieldName == "NormalMapPinValue" )
			return _NormalMapPinValue.IsDerivedFromParent();
		if ( fieldName == "SpecularMap" )
			return _SpecularMap.IsDerivedFromParent();
		if ( fieldName == "SpecularMapPinValue" )
			return _SpecularMapPinValue.IsDerivedFromParent();
		if ( fieldName == "ReflectionMap" )
			return _ReflectionMap.IsDerivedFromParent();
		if ( fieldName == "ReflectivityPinValue" )
			return _ReflectivityPinValue.IsDerivedFromParent();
		if ( fieldName == "colorizeReflectionMap" )
			return _colorizeReflectionMap.IsDerivedFromParent();
		if ( fieldName == "reflectionMapColor0" )
			return _reflectionMapColor0.IsDerivedFromParent();
		if ( fieldName == "reflectionMapColor1" )
			return _reflectionMapColor1.IsDerivedFromParent();
		if ( fieldName == "reflectionMapColor2" )
			return _reflectionMapColor2.IsDerivedFromParent();
		if ( fieldName == "reflectionMapColor3" )
			return _reflectionMapColor3.IsDerivedFromParent();
		if ( fieldName == "outputMul" )
			return _outputMul.IsDerivedFromParent();
		if ( fieldName == "outputAdd" )
			return _outputAdd.IsDerivedFromParent();
		if ( fieldName == "SkeletalMeshPinValue" )
			return _SkeletalMeshPinValue.IsDerivedFromParent();
		if ( fieldName == "LightModePinValue" )
			return _LightModePinValue.IsDerivedFromParent();
		if ( fieldName == "emissive" )
			return _emissive.IsDerivedFromParent();
		if ( fieldName == "opacity" )
			return _opacity.IsDerivedFromParent();
		if ( fieldName == "reflectivityLerp" )
			return _reflectivityLerp.IsDerivedFromParent();
		if ( fieldName == "reflectivityAdd" )
			return _reflectivityAdd.IsDerivedFromParent();
		if ( fieldName == "reflectivityMul" )
			return _reflectivityMul.IsDerivedFromParent();
		if ( fieldName == "specularPower" )
			return _specularPower.IsDerivedFromParent();
		if ( fieldName == "uOffset1" )
			return _uOffset1.IsDerivedFromParent();
		if ( fieldName == "vOffset1" )
			return _vOffset1.IsDerivedFromParent();
		if ( fieldName == "uOffset2" )
			return _uOffset2.IsDerivedFromParent();
		if ( fieldName == "vOffset2" )
			return _vOffset2.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x1056F3C0)]
[UseTypeName("MTRL")]
public class GrassMaterial : Material
{
	private UndoRedoDBPtr<GrassMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<GrassMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private SamplerEx _FrozenDiffuseMap;
	private SamplerEx _NormalDiffuseMap;
	private SamplerEx _BurnedDiffuseMap;
	private UndoRedo<BooleanPin> _ShadowReciverPinValue;
	private Vec2 _bladeSize;
	private UndoRedo<float> _elasticity;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Frozen" )]
	[Sampler(0)]
	public SamplerEx FrozenDiffuseMap { get { return _FrozenDiffuseMap; } set { _FrozenDiffuseMap.Assign( value ); } }

	[Category( "Normal" )]
	[Sampler(1)]
	public SamplerEx NormalDiffuseMap { get { return _NormalDiffuseMap; } set { _NormalDiffuseMap.Assign( value ); } }

	[Category( "Burned" )]
	[Sampler(2)]
	public SamplerEx BurnedDiffuseMap { get { return _BurnedDiffuseMap; } set { _BurnedDiffuseMap.Assign( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public BooleanPin ShadowReciverPinValue { get { return _ShadowReciverPinValue.Get(); } set { _ShadowReciverPinValue.Set( value ); } }

	[Category( "Blade" )]
	public Vec2 bladeSize { get { return _bladeSize; } set { _bladeSize.Assign( value ); } }

	[Category( "Animation" )]
	public float elasticity { get { return _elasticity.Get(); } set { _elasticity.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GrassMaterial>(owner);
		_renderState = new RenderState( owner );
		SamplerEx __FrozenDiffuseMap = new SamplerEx(); // Construct default object for FrozenDiffuseMap
		__FrozenDiffuseMap.Multiplier.R = 1.0f;
		__FrozenDiffuseMap.Multiplier.G = 1.0f;
		__FrozenDiffuseMap.Multiplier.B = 1.0f;
		__FrozenDiffuseMap.Add.A = 0.0f;
		_FrozenDiffuseMap = new SamplerEx( owner, __FrozenDiffuseMap );
		SamplerEx __NormalDiffuseMap = new SamplerEx(); // Construct default object for NormalDiffuseMap
		__NormalDiffuseMap.Multiplier.R = 1.0f;
		__NormalDiffuseMap.Multiplier.G = 1.0f;
		__NormalDiffuseMap.Multiplier.B = 1.0f;
		__NormalDiffuseMap.Add.A = 0.0f;
		_NormalDiffuseMap = new SamplerEx( owner, __NormalDiffuseMap );
		SamplerEx __BurnedDiffuseMap = new SamplerEx(); // Construct default object for BurnedDiffuseMap
		__BurnedDiffuseMap.Multiplier.R = 1.0f;
		__BurnedDiffuseMap.Multiplier.G = 1.0f;
		__BurnedDiffuseMap.Multiplier.B = 1.0f;
		__BurnedDiffuseMap.Add.A = 0.0f;
		_BurnedDiffuseMap = new SamplerEx( owner, __BurnedDiffuseMap );
		_ShadowReciverPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.Present );
		Vec2 __bladeSize = new Vec2(); // Construct default object for bladeSize
		__bladeSize.x = 0.75f;
		__bladeSize.y = 0.75f;
		_bladeSize = new Vec2( owner, __bladeSize );
		_elasticity = new UndoRedo<float>( owner, 0.75f );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_FrozenDiffuseMap.Changed += FireChangedEvent;
		_NormalDiffuseMap.Changed += FireChangedEvent;
		_BurnedDiffuseMap.Changed += FireChangedEvent;
		_ShadowReciverPinValue.Changed += FireChangedEvent;
		_bladeSize.Changed += FireChangedEvent;
		_elasticity.Changed += FireChangedEvent;
	}

	public GrassMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( GrassMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GrassMaterial" );
		renderState = source.renderState;
		FrozenDiffuseMap = source.FrozenDiffuseMap;
		NormalDiffuseMap = source.NormalDiffuseMap;
		BurnedDiffuseMap = source.BurnedDiffuseMap;
		ShadowReciverPinValue = source.ShadowReciverPinValue;
		bladeSize = source.bladeSize;
		elasticity = source.elasticity;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GrassMaterial source = _source as GrassMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GrassMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GrassMaterial newParent = rawParent == null ? null : rawParent.Get<GrassMaterial>();
		if ( newParent == null && _newParent is GrassMaterial )
			newParent = _newParent as GrassMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_FrozenDiffuseMap.SetParent( newParent == null ? null : newParent._FrozenDiffuseMap );
		_NormalDiffuseMap.SetParent( newParent == null ? null : newParent._NormalDiffuseMap );
		_BurnedDiffuseMap.SetParent( newParent == null ? null : newParent._BurnedDiffuseMap );
		_ShadowReciverPinValue.SetParent( newParent == null ? null : newParent._ShadowReciverPinValue );
		_bladeSize.SetParent( newParent == null ? null : newParent._bladeSize );
		_elasticity.SetParent( newParent == null ? null : newParent._elasticity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_FrozenDiffuseMap.Reset();
		_NormalDiffuseMap.Reset();
		_BurnedDiffuseMap.Reset();
		_ShadowReciverPinValue.Reset();
		_bladeSize.Reset();
		_elasticity.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _FrozenDiffuseMap.IsDerivedFromParent()
			&& _NormalDiffuseMap.IsDerivedFromParent()
			&& _BurnedDiffuseMap.IsDerivedFromParent()
			&& _ShadowReciverPinValue.IsDerivedFromParent()
			&& _bladeSize.IsDerivedFromParent()
			&& _elasticity.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "FrozenDiffuseMap" )
			_FrozenDiffuseMap.Reset();
		else if ( fieldName == "NormalDiffuseMap" )
			_NormalDiffuseMap.Reset();
		else if ( fieldName == "BurnedDiffuseMap" )
			_BurnedDiffuseMap.Reset();
		else if ( fieldName == "ShadowReciverPinValue" )
			_ShadowReciverPinValue.Reset();
		else if ( fieldName == "bladeSize" )
			_bladeSize.Reset();
		else if ( fieldName == "elasticity" )
			_elasticity.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "FrozenDiffuseMap" )
			return _FrozenDiffuseMap.IsDerivedFromParent();
		if ( fieldName == "NormalDiffuseMap" )
			return _NormalDiffuseMap.IsDerivedFromParent();
		if ( fieldName == "BurnedDiffuseMap" )
			return _BurnedDiffuseMap.IsDerivedFromParent();
		if ( fieldName == "ShadowReciverPinValue" )
			return _ShadowReciverPinValue.IsDerivedFromParent();
		if ( fieldName == "bladeSize" )
			return _bladeSize.IsDerivedFromParent();
		if ( fieldName == "elasticity" )
			return _elasticity.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialFunc("HeightfogMaterial.inl", "ModifyOpacity(float opacity)")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B629340)]
[UseTypeName("MTRL")]
public class HeightfogMaterial : Material
{
	private UndoRedoDBPtr<HeightfogMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<HeightfogMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private Sampler _noiseMap;
	private UndoRedo<float> _noiseR1;
	private UndoRedo<float> _noiseR2;
	private UndoRedo<float> _noiseR3;
	private UndoRedo<float> _speed;
	private UndoRedo<float> _tiling;
	private HDRColor _color1;
	private HDRColor _color2;
	private UndoRedo<float> _roughnessScale;
	private UndoRedo<float> _halfFadeDistance;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Noise Internals" )]
	[Sampler(0)]
	public Sampler noiseMap { get { return _noiseMap; } set { _noiseMap.Assign( value ); } }

	[Category( "Noise Internals" )]
	[Description( "[internal use]" )]
	public float noiseR1 { get { return _noiseR1.Get(); } set { _noiseR1.Set( value ); } }

	[Category( "Noise Internals" )]
	[Description( "[internal use]" )]
	public float noiseR2 { get { return _noiseR2.Get(); } set { _noiseR2.Set( value ); } }

	[Category( "Noise Internals" )]
	[Description( "[internal use]" )]
	public float noiseR3 { get { return _noiseR3.Get(); } set { _noiseR3.Set( value ); } }

	[Description( "Animation speed" )]
	public float speed { get { return _speed.Get(); } set { _speed.Set( value ); } }

	[Description( "Noise texture mapping scale, in meters" )]
	public float tiling { get { return _tiling.Get(); } set { _tiling.Set( value ); } }

	[Description( "Fog color 1" )]
	public HDRColor color1 { get { return _color1; } set { _color1.Assign( value ); } }

	[Description( "Fog color 1" )]
	public HDRColor color2 { get { return _color2; } set { _color2.Assign( value ); } }

	[Description( "Roughness of the fog surface, in meters" )]
	public float roughnessScale { get { return _roughnessScale.Get(); } set { _roughnessScale.Set( value ); } }

	[Description( "Distance at which fog is twice denser, in meters" )]
	public float halfFadeDistance { get { return _halfFadeDistance.Get(); } set { _halfFadeDistance.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeightfogMaterial>(owner);
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.alphaTest = OnOffState.On;
		__renderState.alphaTestRef = 0;
		__renderState.culling = OnOffState.Off;
		_renderState = new RenderState( owner, __renderState );
		_noiseMap = new Sampler( owner );
		_noiseR1 = new UndoRedo<float>( owner, 1.0f );
		_noiseR2 = new UndoRedo<float>( owner, 0.3f );
		_noiseR3 = new UndoRedo<float>( owner, 0.3f );
		_speed = new UndoRedo<float>( owner, 2.5f );
		_tiling = new UndoRedo<float>( owner, 10.0f );
		HDRColor __color1 = new HDRColor(); // Construct default object for color1
		__color1.R = 0.8f;
		__color1.G = 1.0f;
		__color1.B = 0.8f;
		_color1 = new HDRColor( owner, __color1 );
		HDRColor __color2 = new HDRColor(); // Construct default object for color2
		__color2.R = 0.8f;
		__color2.G = 0.8f;
		__color2.B = 1.0f;
		_color2 = new HDRColor( owner, __color2 );
		_roughnessScale = new UndoRedo<float>( owner, 2.0f );
		_halfFadeDistance = new UndoRedo<float>( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_noiseMap.Changed += FireChangedEvent;
		_noiseR1.Changed += FireChangedEvent;
		_noiseR2.Changed += FireChangedEvent;
		_noiseR3.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_tiling.Changed += FireChangedEvent;
		_color1.Changed += FireChangedEvent;
		_color2.Changed += FireChangedEvent;
		_roughnessScale.Changed += FireChangedEvent;
		_halfFadeDistance.Changed += FireChangedEvent;
	}

	public HeightfogMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( HeightfogMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeightfogMaterial" );
		renderState = source.renderState;
		noiseMap = source.noiseMap;
		noiseR1 = source.noiseR1;
		noiseR2 = source.noiseR2;
		noiseR3 = source.noiseR3;
		speed = source.speed;
		tiling = source.tiling;
		color1 = source.color1;
		color2 = source.color2;
		roughnessScale = source.roughnessScale;
		halfFadeDistance = source.halfFadeDistance;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeightfogMaterial source = _source as HeightfogMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeightfogMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeightfogMaterial newParent = rawParent == null ? null : rawParent.Get<HeightfogMaterial>();
		if ( newParent == null && _newParent is HeightfogMaterial )
			newParent = _newParent as HeightfogMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_noiseMap.SetParent( newParent == null ? null : newParent._noiseMap );
		_noiseR1.SetParent( newParent == null ? null : newParent._noiseR1 );
		_noiseR2.SetParent( newParent == null ? null : newParent._noiseR2 );
		_noiseR3.SetParent( newParent == null ? null : newParent._noiseR3 );
		_speed.SetParent( newParent == null ? null : newParent._speed );
		_tiling.SetParent( newParent == null ? null : newParent._tiling );
		_color1.SetParent( newParent == null ? null : newParent._color1 );
		_color2.SetParent( newParent == null ? null : newParent._color2 );
		_roughnessScale.SetParent( newParent == null ? null : newParent._roughnessScale );
		_halfFadeDistance.SetParent( newParent == null ? null : newParent._halfFadeDistance );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_noiseMap.Reset();
		_noiseR1.Reset();
		_noiseR2.Reset();
		_noiseR3.Reset();
		_speed.Reset();
		_tiling.Reset();
		_color1.Reset();
		_color2.Reset();
		_roughnessScale.Reset();
		_halfFadeDistance.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _noiseMap.IsDerivedFromParent()
			&& _noiseR1.IsDerivedFromParent()
			&& _noiseR2.IsDerivedFromParent()
			&& _noiseR3.IsDerivedFromParent()
			&& _speed.IsDerivedFromParent()
			&& _tiling.IsDerivedFromParent()
			&& _color1.IsDerivedFromParent()
			&& _color2.IsDerivedFromParent()
			&& _roughnessScale.IsDerivedFromParent()
			&& _halfFadeDistance.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "noiseMap" )
			_noiseMap.Reset();
		else if ( fieldName == "noiseR1" )
			_noiseR1.Reset();
		else if ( fieldName == "noiseR2" )
			_noiseR2.Reset();
		else if ( fieldName == "noiseR3" )
			_noiseR3.Reset();
		else if ( fieldName == "speed" )
			_speed.Reset();
		else if ( fieldName == "tiling" )
			_tiling.Reset();
		else if ( fieldName == "color1" )
			_color1.Reset();
		else if ( fieldName == "color2" )
			_color2.Reset();
		else if ( fieldName == "roughnessScale" )
			_roughnessScale.Reset();
		else if ( fieldName == "halfFadeDistance" )
			_halfFadeDistance.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "noiseMap" )
			return _noiseMap.IsDerivedFromParent();
		if ( fieldName == "noiseR1" )
			return _noiseR1.IsDerivedFromParent();
		if ( fieldName == "noiseR2" )
			return _noiseR2.IsDerivedFromParent();
		if ( fieldName == "noiseR3" )
			return _noiseR3.IsDerivedFromParent();
		if ( fieldName == "speed" )
			return _speed.IsDerivedFromParent();
		if ( fieldName == "tiling" )
			return _tiling.IsDerivedFromParent();
		if ( fieldName == "color1" )
			return _color1.IsDerivedFromParent();
		if ( fieldName == "color2" )
			return _color2.IsDerivedFromParent();
		if ( fieldName == "roughnessScale" )
			return _roughnessScale.IsDerivedFromParent();
		if ( fieldName == "halfFadeDistance" )
			return _halfFadeDistance.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(4)]
[UseTypeName("LTEN")]
public class LightEnvironment : DBResource
{
	private UndoRedoDBPtr<LightEnvironment> ___parent;
	[HideInOutliner]
	public new DBPtr<LightEnvironment> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private Direction _Light1Direction;
	private Direction _Light2Direction;
	private HDRColor _AmbientColor;
	private HDRColor _Light1DiffuseColor;
	private HDRColor _Light2DiffuseColor;
	private UndoRedoDBPtr<CubeMap> _environmentCubeMap;
	private UndoRedoDBPtr<CubeMap> _lightingCubeMap;
	private HDRColor _minBakedColor;
	private HDRColor _maxBakedColor;
	private UndoRedoList<float> _lightingCubeMapSHCoeffs;
	private UndoRedo<float> _WaterOscillationSpeedFactor;
	private HDRColor _WaterReflColor0;
	private HDRColor _WaterReflColor1;
	private UndoRedo<int> _fullSizeX;
	private UndoRedo<int> _fullSizeY;
	private UndoRedo<int> _fullSizeSAX;
	private UndoRedo<int> _fullSizeSAY;
	private UndoRedo<ShadowMode> _shadowMode;
	private UndoRedo<float> _powerOfESM;
	private UndoRedo<float> _depthBias;
	private UndoRedo<float> _biasSlope;
	private HDRColor _shadowColor;
	private Direction _shadowDirection;
	private UndoRedo<ShadowBlendMode> _shadowBlendMode;
	private UndoRedo<float> _shadowLength;
	private UndoRedo<float> _shadowFar;
	private UndoRedo<float> _shadowFarRange;
	private UndoRedo<WarFogType> _warFogType;
	private Color _warFogColor;
	private Color _warFogColor2;
	private HDRColor _warFogColorForObjects;
	private UndoRedo<float> _warFogObstacleVisibility;
	private UndoRedo<bool> _warFogUseHeightsDelta;
	private UndoRedo<float> _warFogMaxHeightsDelta;
	private UndoRedo<float> _warFogMiniMapAlphaScale;

	[Category( "Light" )]
	public Direction Light1Direction { get { return _Light1Direction; } set { _Light1Direction.Assign( value ); } }

	[Category( "Light" )]
	public Direction Light2Direction { get { return _Light2Direction; } set { _Light2Direction.Assign( value ); } }

	[Category( "Light" )]
	public HDRColor AmbientColor { get { return _AmbientColor; } set { _AmbientColor.Assign( value ); } }

	[Category( "Light" )]
	public HDRColor Light1DiffuseColor { get { return _Light1DiffuseColor; } set { _Light1DiffuseColor.Assign( value ); } }

	[Category( "Light" )]
	public HDRColor Light2DiffuseColor { get { return _Light2DiffuseColor; } set { _Light2DiffuseColor.Assign( value ); } }

	[Category( "Light" )]
	public DBPtr<CubeMap> environmentCubeMap { get { return _environmentCubeMap.Get(); } set { _environmentCubeMap.Set( value ); } }

	[Category( "Light" )]
	public DBPtr<CubeMap> lightingCubeMap { get { return _lightingCubeMap.Get(); } set { _lightingCubeMap.Set( value ); } }

	[Category( "Light" )]
	public HDRColor minBakedColor { get { return _minBakedColor; } set { _minBakedColor.Assign( value ); } }

	[Category( "Light" )]
	public HDRColor maxBakedColor { get { return _maxBakedColor; } set { _maxBakedColor.Assign( value ); } }

	public libdb.IChangeableList<float> lightingCubeMapSHCoeffs { get { return _lightingCubeMapSHCoeffs; } set { _lightingCubeMapSHCoeffs.Assign( value ); } }

	[Category( "Water" )]
	public float WaterOscillationSpeedFactor { get { return _WaterOscillationSpeedFactor.Get(); } set { _WaterOscillationSpeedFactor.Set( value ); } }

	[Category( "Water" )]
	public HDRColor WaterReflColor0 { get { return _WaterReflColor0; } set { _WaterReflColor0.Assign( value ); } }

	[Category( "Water" )]
	public HDRColor WaterReflColor1 { get { return _WaterReflColor1; } set { _WaterReflColor1.Assign( value ); } }

	public int fullSizeX { get { return _fullSizeX.Get(); } set { _fullSizeX.Set( value ); } }

	public int fullSizeY { get { return _fullSizeY.Get(); } set { _fullSizeY.Set( value ); } }

	public int fullSizeSAX { get { return _fullSizeSAX.Get(); } set { _fullSizeSAX.Set( value ); } }

	public int fullSizeSAY { get { return _fullSizeSAY.Get(); } set { _fullSizeSAY.Set( value ); } }

	public ShadowMode shadowMode { get { return _shadowMode.Get(); } set { _shadowMode.Set( value ); } }

	public float powerOfESM { get { return _powerOfESM.Get(); } set { _powerOfESM.Set( value ); } }

	[Description( "Offset to the z-values of the shadows-texture, that helps ensure that shadow is rendered properly" )]
	public float depthBias { get { return _depthBias.Get(); } set { _depthBias.Set( value ); } }

	[Description( "Coefficient multiplying the slope value that is added to bias" )]
	public float biasSlope { get { return _biasSlope.Get(); } set { _biasSlope.Set( value ); } }

	public HDRColor shadowColor { get { return _shadowColor; } set { _shadowColor.Assign( value ); } }

	public Direction shadowDirection { get { return _shadowDirection; } set { _shadowDirection.Assign( value ); } }

	public ShadowBlendMode shadowBlendMode { get { return _shadowBlendMode.Get(); } set { _shadowBlendMode.Set( value ); } }

	public float shadowLength { get { return _shadowLength.Get(); } set { _shadowLength.Set( value ); } }

	public float shadowFar { get { return _shadowFar.Get(); } set { _shadowFar.Set( value ); } }

	public float shadowFarRange { get { return _shadowFarRange.Get(); } set { _shadowFarRange.Set( value ); } }

	[Category( "WarFog" )]
	public WarFogType warFogType { get { return _warFogType.Get(); } set { _warFogType.Set( value ); } }

	public Color warFogColor { get { return _warFogColor; } set { _warFogColor.Assign( value ); } }

	public Color warFogColor2 { get { return _warFogColor2; } set { _warFogColor2.Assign( value ); } }

	public HDRColor warFogColorForObjects { get { return _warFogColorForObjects; } set { _warFogColorForObjects.Assign( value ); } }

	[Category( "WarFog" )]
	[Description( "visibility deep in meters. it describes how deep we see forest, stones etc" )]
	public float warFogObstacleVisibility { get { return _warFogObstacleVisibility.Get(); } set { _warFogObstacleVisibility.Set( value ); } }

	[Category( "WarFog" )]
	[Description( "Defines whether to use terrain heights delta for visibility tests." )]
	public bool warFogUseHeightsDelta { get { return _warFogUseHeightsDelta.Get(); } set { _warFogUseHeightsDelta.Set( value ); } }

	[Category( "WarFog" )]
	[Description( "Defines the maximum terrain heights delta which passes visibility test (meters)." )]
	public float warFogMaxHeightsDelta { get { return _warFogMaxHeightsDelta.Get(); } set { _warFogMaxHeightsDelta.Set( value ); } }

	[Description( "Scales WarFog alpha while rendering MiniMap. Greater value means darker minimap." )]
	public float warFogMiniMapAlphaScale { get { return _warFogMiniMapAlphaScale.Get(); } set { _warFogMiniMapAlphaScale.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LightEnvironment>(owner);
		Direction __Light1Direction = new Direction(); // Construct default object for Light1Direction
		__Light1Direction.Yaw = 45.0f;
		__Light1Direction.Pitch = -60.0f;
		_Light1Direction = new Direction( owner, __Light1Direction );
		Direction __Light2Direction = new Direction(); // Construct default object for Light2Direction
		__Light2Direction.Yaw = -45.0f;
		__Light2Direction.Pitch = 60.0f;
		_Light2Direction = new Direction( owner, __Light2Direction );
		HDRColor __AmbientColor = new HDRColor(); // Construct default object for AmbientColor
		__AmbientColor.R = 0.5f;
		__AmbientColor.G = 0.5f;
		__AmbientColor.B = 0.5f;
		_AmbientColor = new HDRColor( owner, __AmbientColor );
		HDRColor __Light1DiffuseColor = new HDRColor(); // Construct default object for Light1DiffuseColor
		__Light1DiffuseColor.R = 1.0f;
		__Light1DiffuseColor.G = 1.0f;
		__Light1DiffuseColor.B = 1.0f;
		_Light1DiffuseColor = new HDRColor( owner, __Light1DiffuseColor );
		HDRColor __Light2DiffuseColor = new HDRColor(); // Construct default object for Light2DiffuseColor
		__Light2DiffuseColor.R = 0.3f;
		__Light2DiffuseColor.G = 0.3f;
		__Light2DiffuseColor.B = 0.3f;
		__Light2DiffuseColor.A = 0.3f;
		_Light2DiffuseColor = new HDRColor( owner, __Light2DiffuseColor );
		_environmentCubeMap = new UndoRedoDBPtr<CubeMap>( owner );
		_lightingCubeMap = new UndoRedoDBPtr<CubeMap>( owner );
		HDRColor __minBakedColor = new HDRColor(); // Construct default object for minBakedColor
		__minBakedColor.A = 0.0f;
		_minBakedColor = new HDRColor( owner, __minBakedColor );
		HDRColor __maxBakedColor = new HDRColor(); // Construct default object for maxBakedColor
		__maxBakedColor.R = 255.0f;
		__maxBakedColor.G = 255.0f;
		__maxBakedColor.B = 255.0f;
		__maxBakedColor.A = 0.0f;
		_maxBakedColor = new HDRColor( owner, __maxBakedColor );
		_lightingCubeMapSHCoeffs = new UndoRedoList<float>( owner );
		_WaterOscillationSpeedFactor = new UndoRedo<float>( owner, 1.0f );
		HDRColor __WaterReflColor0 = new HDRColor(); // Construct default object for WaterReflColor0
		__WaterReflColor0.R = 0.1f;
		__WaterReflColor0.G = 0.5f;
		__WaterReflColor0.B = 0.6f;
		__WaterReflColor0.A = 0.0f;
		_WaterReflColor0 = new HDRColor( owner, __WaterReflColor0 );
		HDRColor __WaterReflColor1 = new HDRColor(); // Construct default object for WaterReflColor1
		__WaterReflColor1.G = 0.4f;
		__WaterReflColor1.B = 0.7f;
		__WaterReflColor1.A = 0.0f;
		_WaterReflColor1 = new HDRColor( owner, __WaterReflColor1 );
		_fullSizeX = new UndoRedo<int>( owner, 2048 );
		_fullSizeY = new UndoRedo<int>( owner, 2048 );
		_fullSizeSAX = new UndoRedo<int>( owner, 1024 );
		_fullSizeSAY = new UndoRedo<int>( owner, 1024 );
		_shadowMode = new UndoRedo<ShadowMode>( owner, ShadowMode.PCF );
		_powerOfESM = new UndoRedo<float>( owner, 80.0f );
		_depthBias = new UndoRedo<float>( owner, 0.0001f );
		_biasSlope = new UndoRedo<float>( owner, 4.0f );
		HDRColor __shadowColor = new HDRColor(); // Construct default object for shadowColor
		__shadowColor.B = 0.1f;
		__shadowColor.A = 0.25f;
		_shadowColor = new HDRColor( owner, __shadowColor );
		Direction __shadowDirection = new Direction(); // Construct default object for shadowDirection
		__shadowDirection.Yaw = 45.0f;
		__shadowDirection.Pitch = -60.0f;
		_shadowDirection = new Direction( owner, __shadowDirection );
		_shadowBlendMode = new UndoRedo<ShadowBlendMode>( owner, ShadowBlendMode.LerpByAlpha );
		_shadowLength = new UndoRedo<float>( owner, 20.0f );
		_shadowFar = new UndoRedo<float>( owner, 60.0f );
		_shadowFarRange = new UndoRedo<float>( owner, 10.0f );
		_warFogType = new UndoRedo<WarFogType>( owner, WarFogType.SingleLayer );
		Color __warFogColor = new Color(); // Construct default object for warFogColor
		__warFogColor.R = 20;
		__warFogColor.G = 26;
		__warFogColor.B = 31;
		__warFogColor.A = 165;
		_warFogColor = new Color( owner, __warFogColor );
		Color __warFogColor2 = new Color(); // Construct default object for warFogColor2
		__warFogColor2.R = 20;
		__warFogColor2.G = 26;
		__warFogColor2.B = 31;
		_warFogColor2 = new Color( owner, __warFogColor2 );
		HDRColor __warFogColorForObjects = new HDRColor(); // Construct default object for warFogColorForObjects
		__warFogColorForObjects.R = 0.08f;
		__warFogColorForObjects.G = 0.1f;
		__warFogColorForObjects.B = 0.12f;
		__warFogColorForObjects.A = 0.35f;
		_warFogColorForObjects = new HDRColor( owner, __warFogColorForObjects );
		_warFogObstacleVisibility = new UndoRedo<float>( owner, 6.0f );
		_warFogUseHeightsDelta = new UndoRedo<bool>( owner, true );
		_warFogMaxHeightsDelta = new UndoRedo<float>( owner, 3.0f );
		_warFogMiniMapAlphaScale = new UndoRedo<float>( owner, 1.5f );
		___parent.Changed += FireChangedEvent;
		_Light1Direction.Changed += FireChangedEvent;
		_Light2Direction.Changed += FireChangedEvent;
		_AmbientColor.Changed += FireChangedEvent;
		_Light1DiffuseColor.Changed += FireChangedEvent;
		_Light2DiffuseColor.Changed += FireChangedEvent;
		_environmentCubeMap.Changed += FireChangedEvent;
		_lightingCubeMap.Changed += FireChangedEvent;
		_minBakedColor.Changed += FireChangedEvent;
		_maxBakedColor.Changed += FireChangedEvent;
		_lightingCubeMapSHCoeffs.Changed += FireChangedEvent;
		_WaterOscillationSpeedFactor.Changed += FireChangedEvent;
		_WaterReflColor0.Changed += FireChangedEvent;
		_WaterReflColor1.Changed += FireChangedEvent;
		_fullSizeX.Changed += FireChangedEvent;
		_fullSizeY.Changed += FireChangedEvent;
		_fullSizeSAX.Changed += FireChangedEvent;
		_fullSizeSAY.Changed += FireChangedEvent;
		_shadowMode.Changed += FireChangedEvent;
		_powerOfESM.Changed += FireChangedEvent;
		_depthBias.Changed += FireChangedEvent;
		_biasSlope.Changed += FireChangedEvent;
		_shadowColor.Changed += FireChangedEvent;
		_shadowDirection.Changed += FireChangedEvent;
		_shadowBlendMode.Changed += FireChangedEvent;
		_shadowLength.Changed += FireChangedEvent;
		_shadowFar.Changed += FireChangedEvent;
		_shadowFarRange.Changed += FireChangedEvent;
		_warFogType.Changed += FireChangedEvent;
		_warFogColor.Changed += FireChangedEvent;
		_warFogColor2.Changed += FireChangedEvent;
		_warFogColorForObjects.Changed += FireChangedEvent;
		_warFogObstacleVisibility.Changed += FireChangedEvent;
		_warFogUseHeightsDelta.Changed += FireChangedEvent;
		_warFogMaxHeightsDelta.Changed += FireChangedEvent;
		_warFogMiniMapAlphaScale.Changed += FireChangedEvent;
	}

	public LightEnvironment()
	{
		Initialize( this );
	}
	private void AssignSelf( LightEnvironment source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LightEnvironment" );
		Light1Direction = source.Light1Direction;
		Light2Direction = source.Light2Direction;
		AmbientColor = source.AmbientColor;
		Light1DiffuseColor = source.Light1DiffuseColor;
		Light2DiffuseColor = source.Light2DiffuseColor;
		environmentCubeMap = source.environmentCubeMap;
		lightingCubeMap = source.lightingCubeMap;
		minBakedColor = source.minBakedColor;
		maxBakedColor = source.maxBakedColor;
		lightingCubeMapSHCoeffs = source.lightingCubeMapSHCoeffs;
		WaterOscillationSpeedFactor = source.WaterOscillationSpeedFactor;
		WaterReflColor0 = source.WaterReflColor0;
		WaterReflColor1 = source.WaterReflColor1;
		fullSizeX = source.fullSizeX;
		fullSizeY = source.fullSizeY;
		fullSizeSAX = source.fullSizeSAX;
		fullSizeSAY = source.fullSizeSAY;
		shadowMode = source.shadowMode;
		powerOfESM = source.powerOfESM;
		depthBias = source.depthBias;
		biasSlope = source.biasSlope;
		shadowColor = source.shadowColor;
		shadowDirection = source.shadowDirection;
		shadowBlendMode = source.shadowBlendMode;
		shadowLength = source.shadowLength;
		shadowFar = source.shadowFar;
		shadowFarRange = source.shadowFarRange;
		warFogType = source.warFogType;
		warFogColor = source.warFogColor;
		warFogColor2 = source.warFogColor2;
		warFogColorForObjects = source.warFogColorForObjects;
		warFogObstacleVisibility = source.warFogObstacleVisibility;
		warFogUseHeightsDelta = source.warFogUseHeightsDelta;
		warFogMaxHeightsDelta = source.warFogMaxHeightsDelta;
		warFogMiniMapAlphaScale = source.warFogMiniMapAlphaScale;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LightEnvironment source = _source as LightEnvironment;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LightEnvironment" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LightEnvironment newParent = rawParent == null ? null : rawParent.Get<LightEnvironment>();
		if ( newParent == null && _newParent is LightEnvironment )
			newParent = _newParent as LightEnvironment;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_Light1Direction.SetParent( newParent == null ? null : newParent._Light1Direction );
		_Light2Direction.SetParent( newParent == null ? null : newParent._Light2Direction );
		_AmbientColor.SetParent( newParent == null ? null : newParent._AmbientColor );
		_Light1DiffuseColor.SetParent( newParent == null ? null : newParent._Light1DiffuseColor );
		_Light2DiffuseColor.SetParent( newParent == null ? null : newParent._Light2DiffuseColor );
		_environmentCubeMap.SetParent( newParent == null ? null : newParent._environmentCubeMap );
		_lightingCubeMap.SetParent( newParent == null ? null : newParent._lightingCubeMap );
		_minBakedColor.SetParent( newParent == null ? null : newParent._minBakedColor );
		_maxBakedColor.SetParent( newParent == null ? null : newParent._maxBakedColor );
		_lightingCubeMapSHCoeffs.SetParent( newParent == null ? null : newParent._lightingCubeMapSHCoeffs );
		_WaterOscillationSpeedFactor.SetParent( newParent == null ? null : newParent._WaterOscillationSpeedFactor );
		_WaterReflColor0.SetParent( newParent == null ? null : newParent._WaterReflColor0 );
		_WaterReflColor1.SetParent( newParent == null ? null : newParent._WaterReflColor1 );
		_fullSizeX.SetParent( newParent == null ? null : newParent._fullSizeX );
		_fullSizeY.SetParent( newParent == null ? null : newParent._fullSizeY );
		_fullSizeSAX.SetParent( newParent == null ? null : newParent._fullSizeSAX );
		_fullSizeSAY.SetParent( newParent == null ? null : newParent._fullSizeSAY );
		_shadowMode.SetParent( newParent == null ? null : newParent._shadowMode );
		_powerOfESM.SetParent( newParent == null ? null : newParent._powerOfESM );
		_depthBias.SetParent( newParent == null ? null : newParent._depthBias );
		_biasSlope.SetParent( newParent == null ? null : newParent._biasSlope );
		_shadowColor.SetParent( newParent == null ? null : newParent._shadowColor );
		_shadowDirection.SetParent( newParent == null ? null : newParent._shadowDirection );
		_shadowBlendMode.SetParent( newParent == null ? null : newParent._shadowBlendMode );
		_shadowLength.SetParent( newParent == null ? null : newParent._shadowLength );
		_shadowFar.SetParent( newParent == null ? null : newParent._shadowFar );
		_shadowFarRange.SetParent( newParent == null ? null : newParent._shadowFarRange );
		_warFogType.SetParent( newParent == null ? null : newParent._warFogType );
		_warFogColor.SetParent( newParent == null ? null : newParent._warFogColor );
		_warFogColor2.SetParent( newParent == null ? null : newParent._warFogColor2 );
		_warFogColorForObjects.SetParent( newParent == null ? null : newParent._warFogColorForObjects );
		_warFogObstacleVisibility.SetParent( newParent == null ? null : newParent._warFogObstacleVisibility );
		_warFogUseHeightsDelta.SetParent( newParent == null ? null : newParent._warFogUseHeightsDelta );
		_warFogMaxHeightsDelta.SetParent( newParent == null ? null : newParent._warFogMaxHeightsDelta );
		_warFogMiniMapAlphaScale.SetParent( newParent == null ? null : newParent._warFogMiniMapAlphaScale );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_Light1Direction.Reset();
		_Light2Direction.Reset();
		_AmbientColor.Reset();
		_Light1DiffuseColor.Reset();
		_Light2DiffuseColor.Reset();
		_environmentCubeMap.Reset();
		_lightingCubeMap.Reset();
		_minBakedColor.Reset();
		_maxBakedColor.Reset();
		_lightingCubeMapSHCoeffs.Reset();
		_WaterOscillationSpeedFactor.Reset();
		_WaterReflColor0.Reset();
		_WaterReflColor1.Reset();
		_fullSizeX.Reset();
		_fullSizeY.Reset();
		_fullSizeSAX.Reset();
		_fullSizeSAY.Reset();
		_shadowMode.Reset();
		_powerOfESM.Reset();
		_depthBias.Reset();
		_biasSlope.Reset();
		_shadowColor.Reset();
		_shadowDirection.Reset();
		_shadowBlendMode.Reset();
		_shadowLength.Reset();
		_shadowFar.Reset();
		_shadowFarRange.Reset();
		_warFogType.Reset();
		_warFogColor.Reset();
		_warFogColor2.Reset();
		_warFogColorForObjects.Reset();
		_warFogObstacleVisibility.Reset();
		_warFogUseHeightsDelta.Reset();
		_warFogMaxHeightsDelta.Reset();
		_warFogMiniMapAlphaScale.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_Light1Direction.IsDerivedFromParent()
			&& _Light2Direction.IsDerivedFromParent()
			&& _AmbientColor.IsDerivedFromParent()
			&& _Light1DiffuseColor.IsDerivedFromParent()
			&& _Light2DiffuseColor.IsDerivedFromParent()
			&& _environmentCubeMap.IsDerivedFromParent()
			&& _lightingCubeMap.IsDerivedFromParent()
			&& _minBakedColor.IsDerivedFromParent()
			&& _maxBakedColor.IsDerivedFromParent()
			&& _lightingCubeMapSHCoeffs.IsDerivedFromParent()
			&& _WaterOscillationSpeedFactor.IsDerivedFromParent()
			&& _WaterReflColor0.IsDerivedFromParent()
			&& _WaterReflColor1.IsDerivedFromParent()
			&& _fullSizeX.IsDerivedFromParent()
			&& _fullSizeY.IsDerivedFromParent()
			&& _fullSizeSAX.IsDerivedFromParent()
			&& _fullSizeSAY.IsDerivedFromParent()
			&& _shadowMode.IsDerivedFromParent()
			&& _powerOfESM.IsDerivedFromParent()
			&& _depthBias.IsDerivedFromParent()
			&& _biasSlope.IsDerivedFromParent()
			&& _shadowColor.IsDerivedFromParent()
			&& _shadowDirection.IsDerivedFromParent()
			&& _shadowBlendMode.IsDerivedFromParent()
			&& _shadowLength.IsDerivedFromParent()
			&& _shadowFar.IsDerivedFromParent()
			&& _shadowFarRange.IsDerivedFromParent()
			&& _warFogType.IsDerivedFromParent()
			&& _warFogColor.IsDerivedFromParent()
			&& _warFogColor2.IsDerivedFromParent()
			&& _warFogColorForObjects.IsDerivedFromParent()
			&& _warFogObstacleVisibility.IsDerivedFromParent()
			&& _warFogUseHeightsDelta.IsDerivedFromParent()
			&& _warFogMaxHeightsDelta.IsDerivedFromParent()
			&& _warFogMiniMapAlphaScale.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "Light1Direction" )
			_Light1Direction.Reset();
		else if ( fieldName == "Light2Direction" )
			_Light2Direction.Reset();
		else if ( fieldName == "AmbientColor" )
			_AmbientColor.Reset();
		else if ( fieldName == "Light1DiffuseColor" )
			_Light1DiffuseColor.Reset();
		else if ( fieldName == "Light2DiffuseColor" )
			_Light2DiffuseColor.Reset();
		else if ( fieldName == "environmentCubeMap" )
			_environmentCubeMap.Reset();
		else if ( fieldName == "lightingCubeMap" )
			_lightingCubeMap.Reset();
		else if ( fieldName == "minBakedColor" )
			_minBakedColor.Reset();
		else if ( fieldName == "maxBakedColor" )
			_maxBakedColor.Reset();
		else if ( fieldName == "lightingCubeMapSHCoeffs" )
			_lightingCubeMapSHCoeffs.Reset();
		else if ( fieldName == "WaterOscillationSpeedFactor" )
			_WaterOscillationSpeedFactor.Reset();
		else if ( fieldName == "WaterReflColor0" )
			_WaterReflColor0.Reset();
		else if ( fieldName == "WaterReflColor1" )
			_WaterReflColor1.Reset();
		else if ( fieldName == "fullSizeX" )
			_fullSizeX.Reset();
		else if ( fieldName == "fullSizeY" )
			_fullSizeY.Reset();
		else if ( fieldName == "fullSizeSAX" )
			_fullSizeSAX.Reset();
		else if ( fieldName == "fullSizeSAY" )
			_fullSizeSAY.Reset();
		else if ( fieldName == "shadowMode" )
			_shadowMode.Reset();
		else if ( fieldName == "powerOfESM" )
			_powerOfESM.Reset();
		else if ( fieldName == "depthBias" )
			_depthBias.Reset();
		else if ( fieldName == "biasSlope" )
			_biasSlope.Reset();
		else if ( fieldName == "shadowColor" )
			_shadowColor.Reset();
		else if ( fieldName == "shadowDirection" )
			_shadowDirection.Reset();
		else if ( fieldName == "shadowBlendMode" )
			_shadowBlendMode.Reset();
		else if ( fieldName == "shadowLength" )
			_shadowLength.Reset();
		else if ( fieldName == "shadowFar" )
			_shadowFar.Reset();
		else if ( fieldName == "shadowFarRange" )
			_shadowFarRange.Reset();
		else if ( fieldName == "warFogType" )
			_warFogType.Reset();
		else if ( fieldName == "warFogColor" )
			_warFogColor.Reset();
		else if ( fieldName == "warFogColor2" )
			_warFogColor2.Reset();
		else if ( fieldName == "warFogColorForObjects" )
			_warFogColorForObjects.Reset();
		else if ( fieldName == "warFogObstacleVisibility" )
			_warFogObstacleVisibility.Reset();
		else if ( fieldName == "warFogUseHeightsDelta" )
			_warFogUseHeightsDelta.Reset();
		else if ( fieldName == "warFogMaxHeightsDelta" )
			_warFogMaxHeightsDelta.Reset();
		else if ( fieldName == "warFogMiniMapAlphaScale" )
			_warFogMiniMapAlphaScale.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "Light1Direction" )
			return _Light1Direction.IsDerivedFromParent();
		if ( fieldName == "Light2Direction" )
			return _Light2Direction.IsDerivedFromParent();
		if ( fieldName == "AmbientColor" )
			return _AmbientColor.IsDerivedFromParent();
		if ( fieldName == "Light1DiffuseColor" )
			return _Light1DiffuseColor.IsDerivedFromParent();
		if ( fieldName == "Light2DiffuseColor" )
			return _Light2DiffuseColor.IsDerivedFromParent();
		if ( fieldName == "environmentCubeMap" )
			return _environmentCubeMap.IsDerivedFromParent();
		if ( fieldName == "lightingCubeMap" )
			return _lightingCubeMap.IsDerivedFromParent();
		if ( fieldName == "minBakedColor" )
			return _minBakedColor.IsDerivedFromParent();
		if ( fieldName == "maxBakedColor" )
			return _maxBakedColor.IsDerivedFromParent();
		if ( fieldName == "lightingCubeMapSHCoeffs" )
			return _lightingCubeMapSHCoeffs.IsDerivedFromParent();
		if ( fieldName == "WaterOscillationSpeedFactor" )
			return _WaterOscillationSpeedFactor.IsDerivedFromParent();
		if ( fieldName == "WaterReflColor0" )
			return _WaterReflColor0.IsDerivedFromParent();
		if ( fieldName == "WaterReflColor1" )
			return _WaterReflColor1.IsDerivedFromParent();
		if ( fieldName == "fullSizeX" )
			return _fullSizeX.IsDerivedFromParent();
		if ( fieldName == "fullSizeY" )
			return _fullSizeY.IsDerivedFromParent();
		if ( fieldName == "fullSizeSAX" )
			return _fullSizeSAX.IsDerivedFromParent();
		if ( fieldName == "fullSizeSAY" )
			return _fullSizeSAY.IsDerivedFromParent();
		if ( fieldName == "shadowMode" )
			return _shadowMode.IsDerivedFromParent();
		if ( fieldName == "powerOfESM" )
			return _powerOfESM.IsDerivedFromParent();
		if ( fieldName == "depthBias" )
			return _depthBias.IsDerivedFromParent();
		if ( fieldName == "biasSlope" )
			return _biasSlope.IsDerivedFromParent();
		if ( fieldName == "shadowColor" )
			return _shadowColor.IsDerivedFromParent();
		if ( fieldName == "shadowDirection" )
			return _shadowDirection.IsDerivedFromParent();
		if ( fieldName == "shadowBlendMode" )
			return _shadowBlendMode.IsDerivedFromParent();
		if ( fieldName == "shadowLength" )
			return _shadowLength.IsDerivedFromParent();
		if ( fieldName == "shadowFar" )
			return _shadowFar.IsDerivedFromParent();
		if ( fieldName == "shadowFarRange" )
			return _shadowFarRange.IsDerivedFromParent();
		if ( fieldName == "warFogType" )
			return _warFogType.IsDerivedFromParent();
		if ( fieldName == "warFogColor" )
			return _warFogColor.IsDerivedFromParent();
		if ( fieldName == "warFogColor2" )
			return _warFogColor2.IsDerivedFromParent();
		if ( fieldName == "warFogColorForObjects" )
			return _warFogColorForObjects.IsDerivedFromParent();
		if ( fieldName == "warFogObstacleVisibility" )
			return _warFogObstacleVisibility.IsDerivedFromParent();
		if ( fieldName == "warFogUseHeightsDelta" )
			return _warFogUseHeightsDelta.IsDerivedFromParent();
		if ( fieldName == "warFogMaxHeightsDelta" )
			return _warFogMaxHeightsDelta.IsDerivedFromParent();
		if ( fieldName == "warFogMiniMapAlphaScale" )
			return _warFogMiniMapAlphaScale.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B61E442)]
[UseTypeName("MTRL")]
public class LightningMaterial : Material
{
	private UndoRedoDBPtr<LightningMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<LightningMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private Sampler _DiffuseMap;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0)]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LightningMaterial>(owner);
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.alphaTest = OnOffState.On;
		__renderState.alphaTestRef = 0;
		__renderState.culling = OnOffState.Off;
		_renderState = new RenderState( owner, __renderState );
		_DiffuseMap = new Sampler( owner );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
	}

	public LightningMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( LightningMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LightningMaterial" );
		renderState = source.renderState;
		DiffuseMap = source.DiffuseMap;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LightningMaterial source = _source as LightningMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LightningMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LightningMaterial newParent = rawParent == null ? null : rawParent.Get<LightningMaterial>();
		if ( newParent == null && _newParent is LightningMaterial )
			newParent = _newParent as LightningMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_DiffuseMap.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x49547341)]
[UseTypeName("MTRL")]
public class AIGeometryMaterialType : Material
{
	private UndoRedoDBPtr<AIGeometryMaterialType> ___parent;
	[HideInOutliner]
	public new DBPtr<AIGeometryMaterialType> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AIGeometryMaterialType>(owner);
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.AddColor;
		_renderState = new RenderState( owner, __renderState );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
	}

	public AIGeometryMaterialType()
	{
		Initialize( this );
	}
	private void AssignSelf( AIGeometryMaterialType source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AIGeometryMaterialType" );
		renderState = source.renderState;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AIGeometryMaterialType source = _source as AIGeometryMaterialType;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AIGeometryMaterialType" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AIGeometryMaterialType newParent = rawParent == null ? null : rawParent.Get<AIGeometryMaterialType>();
		if ( newParent == null && _newParent is AIGeometryMaterialType )
			newParent = _newParent as AIGeometryMaterialType;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B641440)]
[UseTypeName("MTRL")]
public class NatureMapMaterial : Material
{
	private UndoRedoDBPtr<NatureMapMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<NatureMapMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<NatureMapMaterial>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public NatureMapMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( NatureMapMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for NatureMapMaterial" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		NatureMapMaterial source = _source as NatureMapMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NatureMapMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		NatureMapMaterial newParent = rawParent == null ? null : rawParent.Get<NatureMapMaterial>();
		if ( newParent == null && _newParent is NatureMapMaterial )
			newParent = _newParent as NatureMapMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[MaterialFunc("EaselPaintMaterial.inl", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode)")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9963ED00)]
[UseTypeName("MTRL")]
public class PaintMaterial : Material
{
	private UndoRedoDBPtr<PaintMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<PaintMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<PackedMasksNumberPin> _masksNumber;
	private UndoRedo<PaintMaterialModePin> _paintMode;
	private RenderState _renderState;
	private Sampler _Draft;
	private Sampler _Background;
	private Sampler _BaseBackground;
	private Sampler _Complete;
	private Sampler _Mask;

	[Pin2("PackedMasksNumberPin")]
	public PackedMasksNumberPin masksNumber { get { return _masksNumber.Get(); } set { _masksNumber.Set( value ); } }

	[Pin2("PaintMaterialModePin")]
	public PaintMaterialModePin paintMode { get { return _paintMode.Get(); } set { _paintMode.Set( value ); } }

	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Sampler(0)]
	public Sampler Draft { get { return _Draft; } set { _Draft.Assign( value ); } }

	[Sampler(1)]
	public Sampler Background { get { return _Background; } set { _Background.Assign( value ); } }

	[Sampler(2)]
	public Sampler BaseBackground { get { return _BaseBackground; } set { _BaseBackground.Assign( value ); } }

	[Sampler(3)]
	public Sampler Complete { get { return _Complete; } set { _Complete.Assign( value ); } }

	[Sampler(4)]
	public Sampler Mask { get { return _Mask; } set { _Mask.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PaintMaterial>(owner);
		_masksNumber = new UndoRedo<PackedMasksNumberPin>( owner, PackedMasksNumberPin.PackedMasks1 );
		_paintMode = new UndoRedo<PaintMaterialModePin>( owner, PaintMaterialModePin.InWork );
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.alphaTest = OnOffState.On;
		__renderState.alphaTestRef = 1;
		_renderState = new RenderState( owner, __renderState );
		Sampler __Draft = new Sampler(); // Construct default object for Draft
		__Draft.samplerState.addressU = TextureAddressType.Clamp;
		__Draft.samplerState.addressV = TextureAddressType.Clamp;
		__Draft.samplerState.addressW = TextureAddressType.Clamp;
		_Draft = new Sampler( owner, __Draft );
		Sampler __Background = new Sampler(); // Construct default object for Background
		__Background.samplerState.addressU = TextureAddressType.Clamp;
		__Background.samplerState.addressV = TextureAddressType.Clamp;
		__Background.samplerState.addressW = TextureAddressType.Clamp;
		_Background = new Sampler( owner, __Background );
		Sampler __BaseBackground = new Sampler(); // Construct default object for BaseBackground
		__BaseBackground.samplerState.addressU = TextureAddressType.Clamp;
		__BaseBackground.samplerState.addressV = TextureAddressType.Clamp;
		__BaseBackground.samplerState.addressW = TextureAddressType.Clamp;
		_BaseBackground = new Sampler( owner, __BaseBackground );
		Sampler __Complete = new Sampler(); // Construct default object for Complete
		__Complete.samplerState.addressU = TextureAddressType.Clamp;
		__Complete.samplerState.addressV = TextureAddressType.Clamp;
		__Complete.samplerState.addressW = TextureAddressType.Clamp;
		_Complete = new Sampler( owner, __Complete );
		Sampler __Mask = new Sampler(); // Construct default object for Mask
		__Mask.samplerState.addressU = TextureAddressType.Clamp;
		__Mask.samplerState.addressV = TextureAddressType.Clamp;
		__Mask.samplerState.addressW = TextureAddressType.Clamp;
		_Mask = new Sampler( owner, __Mask );
		___parent.Changed += FireChangedEvent;
		_masksNumber.Changed += FireChangedEvent;
		_paintMode.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_Draft.Changed += FireChangedEvent;
		_Background.Changed += FireChangedEvent;
		_BaseBackground.Changed += FireChangedEvent;
		_Complete.Changed += FireChangedEvent;
		_Mask.Changed += FireChangedEvent;
	}

	public PaintMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( PaintMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PaintMaterial" );
		masksNumber = source.masksNumber;
		paintMode = source.paintMode;
		renderState = source.renderState;
		Draft = source.Draft;
		Background = source.Background;
		BaseBackground = source.BaseBackground;
		Complete = source.Complete;
		Mask = source.Mask;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PaintMaterial source = _source as PaintMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PaintMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PaintMaterial newParent = rawParent == null ? null : rawParent.Get<PaintMaterial>();
		if ( newParent == null && _newParent is PaintMaterial )
			newParent = _newParent as PaintMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_masksNumber.SetParent( newParent == null ? null : newParent._masksNumber );
		_paintMode.SetParent( newParent == null ? null : newParent._paintMode );
		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_Draft.SetParent( newParent == null ? null : newParent._Draft );
		_Background.SetParent( newParent == null ? null : newParent._Background );
		_BaseBackground.SetParent( newParent == null ? null : newParent._BaseBackground );
		_Complete.SetParent( newParent == null ? null : newParent._Complete );
		_Mask.SetParent( newParent == null ? null : newParent._Mask );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_masksNumber.Reset();
		_paintMode.Reset();
		_renderState.Reset();
		_Draft.Reset();
		_Background.Reset();
		_BaseBackground.Reset();
		_Complete.Reset();
		_Mask.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_masksNumber.IsDerivedFromParent()
			&& _paintMode.IsDerivedFromParent()
			&& _renderState.IsDerivedFromParent()
			&& _Draft.IsDerivedFromParent()
			&& _Background.IsDerivedFromParent()
			&& _BaseBackground.IsDerivedFromParent()
			&& _Complete.IsDerivedFromParent()
			&& _Mask.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "masksNumber" )
			_masksNumber.Reset();
		else if ( fieldName == "paintMode" )
			_paintMode.Reset();
		else if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "Draft" )
			_Draft.Reset();
		else if ( fieldName == "Background" )
			_Background.Reset();
		else if ( fieldName == "BaseBackground" )
			_BaseBackground.Reset();
		else if ( fieldName == "Complete" )
			_Complete.Reset();
		else if ( fieldName == "Mask" )
			_Mask.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "masksNumber" )
			return _masksNumber.IsDerivedFromParent();
		if ( fieldName == "paintMode" )
			return _paintMode.IsDerivedFromParent();
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "Draft" )
			return _Draft.IsDerivedFromParent();
		if ( fieldName == "Background" )
			return _Background.IsDerivedFromParent();
		if ( fieldName == "BaseBackground" )
			return _BaseBackground.IsDerivedFromParent();
		if ( fieldName == "Complete" )
			return _Complete.IsDerivedFromParent();
		if ( fieldName == "Mask" )
			return _Mask.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(7)]
[MaterialFunc("ParticleFXMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyOpacity(float opacity)", "ModifyBlendMode(NDb::BlendMode blendMode, bool isSetDefaultBlendMode), CorrectRS(const RenderState &_src), GetRSandSamplersRep(PBYTE _pRep) const")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x49547342)]
[UseTypeName("MTRL")]
public class ParticleFXMaterial : Material
{
	private UndoRedoDBPtr<ParticleFXMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<ParticleFXMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private SamplerEx _DiffuseMap;
	private UndoRedo<OpacityAndEmissiveModePin> _OpacityAndEmissiveModePinValue;
	private UndoRedo<BooleanPin> _DistortionPinValue;
	private UndoRedo<float> _opacity;
	private UndoRedo<float> _distortion;
	private Vec2 _uvSpeed;
	private UndoRedo<float> _scale;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Diffuse Map" )]
	[Sampler(0, "DiffuseMap", true)]
	public SamplerEx DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Category( "Opacity" )]
	[HideEnumValues("Emissive")]
	[Pin2("OpacityModePin")]
	public OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue { get { return _OpacityAndEmissiveModePinValue.Get(); } set { _OpacityAndEmissiveModePinValue.Set( value ); } }

	[Category( "Distortion" )]
	[Pin2]
	public BooleanPin DistortionPinValue { get { return _DistortionPinValue.Get(); } set { _DistortionPinValue.Set( value ); } }

	public float opacity { get { return _opacity.Get(); } set { _opacity.Set( value ); } }

	public float distortion { get { return _distortion.Get(); } set { _distortion.Set( value ); } }

	public Vec2 uvSpeed { get { return _uvSpeed; } set { _uvSpeed.Assign( value ); } }

	[Browsable( false )]
	[HideInOutliner]
	public float scale { get { return _scale.Get(); } set { _scale.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ParticleFXMaterial>(owner);
		_renderState = new RenderState( owner );
		SamplerEx __DiffuseMap = new SamplerEx(); // Construct default object for DiffuseMap
		__DiffuseMap.Multiplier.R = 1.0f;
		__DiffuseMap.Multiplier.G = 1.0f;
		__DiffuseMap.Multiplier.B = 1.0f;
		__DiffuseMap.Add.A = 0.0f;
		_DiffuseMap = new SamplerEx( owner, __DiffuseMap );
		_OpacityAndEmissiveModePinValue = new UndoRedo<OpacityAndEmissiveModePin>( owner, OpacityAndEmissiveModePin.Simple );
		_DistortionPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_opacity = new UndoRedo<float>( owner, 1.0f );
		_distortion = new UndoRedo<float>( owner, 1.0f );
		_uvSpeed = new Vec2( owner );
		_scale = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_OpacityAndEmissiveModePinValue.Changed += FireChangedEvent;
		_DistortionPinValue.Changed += FireChangedEvent;
		_opacity.Changed += FireChangedEvent;
		_distortion.Changed += FireChangedEvent;
		_uvSpeed.Changed += FireChangedEvent;
		_scale.Changed += FireChangedEvent;
	}

	public ParticleFXMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( ParticleFXMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ParticleFXMaterial" );
		renderState = source.renderState;
		DiffuseMap = source.DiffuseMap;
		OpacityAndEmissiveModePinValue = source.OpacityAndEmissiveModePinValue;
		DistortionPinValue = source.DistortionPinValue;
		opacity = source.opacity;
		distortion = source.distortion;
		uvSpeed = source.uvSpeed;
		scale = source.scale;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ParticleFXMaterial source = _source as ParticleFXMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ParticleFXMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ParticleFXMaterial newParent = rawParent == null ? null : rawParent.Get<ParticleFXMaterial>();
		if ( newParent == null && _newParent is ParticleFXMaterial )
			newParent = _newParent as ParticleFXMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_OpacityAndEmissiveModePinValue.SetParent( newParent == null ? null : newParent._OpacityAndEmissiveModePinValue );
		_DistortionPinValue.SetParent( newParent == null ? null : newParent._DistortionPinValue );
		_opacity.SetParent( newParent == null ? null : newParent._opacity );
		_distortion.SetParent( newParent == null ? null : newParent._distortion );
		_uvSpeed.SetParent( newParent == null ? null : newParent._uvSpeed );
		_scale.SetParent( newParent == null ? null : newParent._scale );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_DiffuseMap.Reset();
		_OpacityAndEmissiveModePinValue.Reset();
		_DistortionPinValue.Reset();
		_opacity.Reset();
		_distortion.Reset();
		_uvSpeed.Reset();
		_scale.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _OpacityAndEmissiveModePinValue.IsDerivedFromParent()
			&& _DistortionPinValue.IsDerivedFromParent()
			&& _opacity.IsDerivedFromParent()
			&& _distortion.IsDerivedFromParent()
			&& _uvSpeed.IsDerivedFromParent()
			&& _scale.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "OpacityAndEmissiveModePinValue" )
			_OpacityAndEmissiveModePinValue.Reset();
		else if ( fieldName == "DistortionPinValue" )
			_DistortionPinValue.Reset();
		else if ( fieldName == "opacity" )
			_opacity.Reset();
		else if ( fieldName == "distortion" )
			_distortion.Reset();
		else if ( fieldName == "uvSpeed" )
			_uvSpeed.Reset();
		else if ( fieldName == "scale" )
			_scale.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "OpacityAndEmissiveModePinValue" )
			return _OpacityAndEmissiveModePinValue.IsDerivedFromParent();
		if ( fieldName == "DistortionPinValue" )
			return _DistortionPinValue.IsDerivedFromParent();
		if ( fieldName == "opacity" )
			return _opacity.IsDerivedFromParent();
		if ( fieldName == "distortion" )
			return _distortion.IsDerivedFromParent();
		if ( fieldName == "uvSpeed" )
			return _uvSpeed.IsDerivedFromParent();
		if ( fieldName == "scale" )
			return _scale.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(14)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B759340)]
[UseTypeName("MTRL")]
public class RoadMaterial : Material
{
	private UndoRedoDBPtr<RoadMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<RoadMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private Sampler _RoadMap;
	private Sampler _BorderMap;

	[Category( "States" )]
	[ReadOnly( true )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Sampler(0, "RoadMap", true)]
	public Sampler RoadMap { get { return _RoadMap; } set { _RoadMap.Assign( value ); } }

	[Sampler(1, "BorderMap", true)]
	public Sampler BorderMap { get { return _BorderMap; } set { _BorderMap.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RoadMaterial>(owner);
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		_renderState = new RenderState( owner, __renderState );
		_RoadMap = new Sampler( owner );
		_BorderMap = new Sampler( owner );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_RoadMap.Changed += FireChangedEvent;
		_BorderMap.Changed += FireChangedEvent;
	}

	public RoadMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( RoadMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RoadMaterial" );
		renderState = source.renderState;
		RoadMap = source.RoadMap;
		BorderMap = source.BorderMap;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RoadMaterial source = _source as RoadMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RoadMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RoadMaterial newParent = rawParent == null ? null : rawParent.Get<RoadMaterial>();
		if ( newParent == null && _newParent is RoadMaterial )
			newParent = _newParent as RoadMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_RoadMap.SetParent( newParent == null ? null : newParent._RoadMap );
		_BorderMap.SetParent( newParent == null ? null : newParent._BorderMap );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_RoadMap.Reset();
		_BorderMap.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _RoadMap.IsDerivedFromParent()
			&& _BorderMap.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "RoadMap" )
			_RoadMap.Reset();
		else if ( fieldName == "BorderMap" )
			_BorderMap.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "RoadMap" )
			return _RoadMap.IsDerivedFromParent();
		if ( fieldName == "BorderMap" )
			return _BorderMap.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(4)]
[MaterialFunc("WaterMaterial.inl")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B78C340)]
[UseTypeName("MTRL")]
public class SilhouetteMaterial : Material
{
	private UndoRedoDBPtr<SilhouetteMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<SilhouetteMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private UndoRedo<MaterialFlags> _renderFlags;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "States" )]
	[NoCode]
	public MaterialFlags renderFlags { get { return _renderFlags.Get(); } set { _renderFlags.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SilhouetteMaterial>(owner);
		_renderState = new RenderState( owner );
		_renderFlags = new UndoRedo<MaterialFlags>( owner, MaterialFlags.None );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_renderFlags.Changed += FireChangedEvent;
	}

	public SilhouetteMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( SilhouetteMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SilhouetteMaterial" );
		renderState = source.renderState;
		renderFlags = source.renderFlags;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SilhouetteMaterial source = _source as SilhouetteMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SilhouetteMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SilhouetteMaterial newParent = rawParent == null ? null : rawParent.Get<SilhouetteMaterial>();
		if ( newParent == null && _newParent is SilhouetteMaterial )
			newParent = _newParent as SilhouetteMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_renderFlags.SetParent( newParent == null ? null : newParent._renderFlags );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_renderFlags.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _renderFlags.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "renderFlags" )
			_renderFlags.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "renderFlags" )
			return _renderFlags.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialFunc("SkyMaterial.inl")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3D84CC00)]
[UseTypeName("MTRL")]
public class SkyMaterial : Material
{
	private UndoRedoDBPtr<SkyMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<SkyMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private UndoRedo<MaterialFlags> _renderFlags;
	private Sampler _DiffuseMap;
	private HDRColor _outputMul;
	private HDRColor _outputAdd;
	private AnimatedFloat _uOffset1;
	private AnimatedFloat _vOffset1;
	private AnimatedFloat _uOffset2;
	private AnimatedFloat _vOffset2;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "States" )]
	[NoCode]
	public MaterialFlags renderFlags { get { return _renderFlags.Get(); } set { _renderFlags.Set( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0, "DiffuseMap", true)]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Category( "Modificator" )]
	public HDRColor outputMul { get { return _outputMul; } set { _outputMul.Assign( value ); } }

	[Category( "Modificator" )]
	public HDRColor outputAdd { get { return _outputAdd; } set { _outputAdd.Assign( value ); } }

	public AnimatedFloat uOffset1 { get { return _uOffset1; } set { _uOffset1.Assign( value ); } }

	public AnimatedFloat vOffset1 { get { return _vOffset1; } set { _vOffset1.Assign( value ); } }

	public AnimatedFloat uOffset2 { get { return _uOffset2; } set { _uOffset2.Assign( value ); } }

	public AnimatedFloat vOffset2 { get { return _vOffset2; } set { _vOffset2.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SkyMaterial>(owner);
		_renderState = new RenderState( owner );
		_renderFlags = new UndoRedo<MaterialFlags>( owner, MaterialFlags.ReflectInWater );
		_DiffuseMap = new Sampler( owner );
		HDRColor __outputMul = new HDRColor(); // Construct default object for outputMul
		__outputMul.R = 1.0f;
		__outputMul.G = 1.0f;
		__outputMul.B = 1.0f;
		_outputMul = new HDRColor( owner, __outputMul );
		HDRColor __outputAdd = new HDRColor(); // Construct default object for outputAdd
		__outputAdd.A = 0.0f;
		_outputAdd = new HDRColor( owner, __outputAdd );
		_uOffset1 = new AnimatedFloat( owner );
		_vOffset1 = new AnimatedFloat( owner );
		_uOffset2 = new AnimatedFloat( owner );
		_vOffset2 = new AnimatedFloat( owner );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_renderFlags.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_outputMul.Changed += FireChangedEvent;
		_outputAdd.Changed += FireChangedEvent;
		_uOffset1.Changed += FireChangedEvent;
		_vOffset1.Changed += FireChangedEvent;
		_uOffset2.Changed += FireChangedEvent;
		_vOffset2.Changed += FireChangedEvent;
	}

	public SkyMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( SkyMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SkyMaterial" );
		renderState = source.renderState;
		renderFlags = source.renderFlags;
		DiffuseMap = source.DiffuseMap;
		outputMul = source.outputMul;
		outputAdd = source.outputAdd;
		uOffset1 = source.uOffset1;
		vOffset1 = source.vOffset1;
		uOffset2 = source.uOffset2;
		vOffset2 = source.vOffset2;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SkyMaterial source = _source as SkyMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SkyMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SkyMaterial newParent = rawParent == null ? null : rawParent.Get<SkyMaterial>();
		if ( newParent == null && _newParent is SkyMaterial )
			newParent = _newParent as SkyMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_renderFlags.SetParent( newParent == null ? null : newParent._renderFlags );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_outputMul.SetParent( newParent == null ? null : newParent._outputMul );
		_outputAdd.SetParent( newParent == null ? null : newParent._outputAdd );
		_uOffset1.SetParent( newParent == null ? null : newParent._uOffset1 );
		_vOffset1.SetParent( newParent == null ? null : newParent._vOffset1 );
		_uOffset2.SetParent( newParent == null ? null : newParent._uOffset2 );
		_vOffset2.SetParent( newParent == null ? null : newParent._vOffset2 );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_renderFlags.Reset();
		_DiffuseMap.Reset();
		_outputMul.Reset();
		_outputAdd.Reset();
		_uOffset1.Reset();
		_vOffset1.Reset();
		_uOffset2.Reset();
		_vOffset2.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _renderFlags.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _outputMul.IsDerivedFromParent()
			&& _outputAdd.IsDerivedFromParent()
			&& _uOffset1.IsDerivedFromParent()
			&& _vOffset1.IsDerivedFromParent()
			&& _uOffset2.IsDerivedFromParent()
			&& _vOffset2.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "renderFlags" )
			_renderFlags.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "outputMul" )
			_outputMul.Reset();
		else if ( fieldName == "outputAdd" )
			_outputAdd.Reset();
		else if ( fieldName == "uOffset1" )
			_uOffset1.Reset();
		else if ( fieldName == "vOffset1" )
			_vOffset1.Reset();
		else if ( fieldName == "uOffset2" )
			_uOffset2.Reset();
		else if ( fieldName == "vOffset2" )
			_vOffset2.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "renderFlags" )
			return _renderFlags.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "outputMul" )
			return _outputMul.IsDerivedFromParent();
		if ( fieldName == "outputAdd" )
			return _outputAdd.IsDerivedFromParent();
		if ( fieldName == "uOffset1" )
			return _uOffset1.IsDerivedFromParent();
		if ( fieldName == "vOffset1" )
			return _vOffset1.IsDerivedFromParent();
		if ( fieldName == "uOffset2" )
			return _uOffset2.IsDerivedFromParent();
		if ( fieldName == "vOffset2" )
			return _vOffset2.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialFunc("CommonMaterialFunc.inl")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B5C8C00)]
[UseTypeName("MTRL")]
public class TerrainAOEMaterial : Material
{
	private UndoRedoDBPtr<TerrainAOEMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<TerrainAOEMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private Sampler _DiffuseMap;
	private Vec2 _uvScale;
	private Vec2 _uvOffset;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0)]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	public Vec2 uvScale { get { return _uvScale; } set { _uvScale.Assign( value ); } }

	public Vec2 uvOffset { get { return _uvOffset; } set { _uvOffset.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TerrainAOEMaterial>(owner);
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.alphaTest = OnOffState.On;
		__renderState.alphaTestRef = 0;
		_renderState = new RenderState( owner, __renderState );
		Sampler __DiffuseMap = new Sampler(); // Construct default object for DiffuseMap
		__DiffuseMap.samplerState.addressU = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressV = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressW = TextureAddressType.Clamp;
		_DiffuseMap = new Sampler( owner, __DiffuseMap );
		Vec2 __uvScale = new Vec2(); // Construct default object for uvScale
		__uvScale.x = 1.0f;
		__uvScale.y = 1.0f;
		_uvScale = new Vec2( owner, __uvScale );
		_uvOffset = new Vec2( owner );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_uvScale.Changed += FireChangedEvent;
		_uvOffset.Changed += FireChangedEvent;
	}

	public TerrainAOEMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( TerrainAOEMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TerrainAOEMaterial" );
		renderState = source.renderState;
		DiffuseMap = source.DiffuseMap;
		uvScale = source.uvScale;
		uvOffset = source.uvOffset;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TerrainAOEMaterial source = _source as TerrainAOEMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TerrainAOEMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TerrainAOEMaterial newParent = rawParent == null ? null : rawParent.Get<TerrainAOEMaterial>();
		if ( newParent == null && _newParent is TerrainAOEMaterial )
			newParent = _newParent as TerrainAOEMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_uvScale.SetParent( newParent == null ? null : newParent._uvScale );
		_uvOffset.SetParent( newParent == null ? null : newParent._uvOffset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_DiffuseMap.Reset();
		_uvScale.Reset();
		_uvOffset.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _uvScale.IsDerivedFromParent()
			&& _uvOffset.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "uvScale" )
			_uvScale.Reset();
		else if ( fieldName == "uvOffset" )
			_uvOffset.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "uvScale" )
			return _uvScale.IsDerivedFromParent();
		if ( fieldName == "uvOffset" )
			return _uvOffset.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B61E340)]
[UseTypeName("MTRL")]
public class TerrainElementDebugMaterial : Material
{
	private UndoRedoDBPtr<TerrainElementDebugMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<TerrainElementDebugMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TerrainElementDebugMaterial>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public TerrainElementDebugMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( TerrainElementDebugMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TerrainElementDebugMaterial" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TerrainElementDebugMaterial source = _source as TerrainElementDebugMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TerrainElementDebugMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TerrainElementDebugMaterial newParent = rawParent == null ? null : rawParent.Get<TerrainElementDebugMaterial>();
		if ( newParent == null && _newParent is TerrainElementDebugMaterial )
			newParent = _newParent as TerrainElementDebugMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B5BDAC1)]
[UseTypeName("MTRL")]
public class TerrainElementMaterial : Material
{
	private UndoRedoDBPtr<TerrainElementMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<TerrainElementMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<TerrainUVSetPin> _TerrainUVSetPinValue;
	private UndoRedo<TextureCountPin> _TextureCountPinValue;

	[Pin2("TerrainUVSetPin")]
	public TerrainUVSetPin TerrainUVSetPinValue { get { return _TerrainUVSetPinValue.Get(); } set { _TerrainUVSetPinValue.Set( value ); } }

	[Pin2("TextureCountPin")]
	public TextureCountPin TextureCountPinValue { get { return _TextureCountPinValue.Get(); } set { _TextureCountPinValue.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TerrainElementMaterial>(owner);
		_TerrainUVSetPinValue = new UndoRedo<TerrainUVSetPin>( owner, TerrainUVSetPin.Global );
		_TextureCountPinValue = new UndoRedo<TextureCountPin>( owner, TextureCountPin.Count1 );
		___parent.Changed += FireChangedEvent;
		_TerrainUVSetPinValue.Changed += FireChangedEvent;
		_TextureCountPinValue.Changed += FireChangedEvent;
	}

	public TerrainElementMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( TerrainElementMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TerrainElementMaterial" );
		TerrainUVSetPinValue = source.TerrainUVSetPinValue;
		TextureCountPinValue = source.TextureCountPinValue;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TerrainElementMaterial source = _source as TerrainElementMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TerrainElementMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TerrainElementMaterial newParent = rawParent == null ? null : rawParent.Get<TerrainElementMaterial>();
		if ( newParent == null && _newParent is TerrainElementMaterial )
			newParent = _newParent as TerrainElementMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_TerrainUVSetPinValue.SetParent( newParent == null ? null : newParent._TerrainUVSetPinValue );
		_TextureCountPinValue.SetParent( newParent == null ? null : newParent._TextureCountPinValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_TerrainUVSetPinValue.Reset();
		_TextureCountPinValue.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_TerrainUVSetPinValue.IsDerivedFromParent()
			&& _TextureCountPinValue.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "TerrainUVSetPinValue" )
			_TerrainUVSetPinValue.Reset();
		else if ( fieldName == "TextureCountPinValue" )
			_TextureCountPinValue.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "TerrainUVSetPinValue" )
			return _TerrainUVSetPinValue.IsDerivedFromParent();
		if ( fieldName == "TextureCountPinValue" )
			return _TextureCountPinValue.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9354BD01)]
[UseTypeName("MTRL")]
public class TerrainHeightBuilderMaterial : Material
{
	private UndoRedoDBPtr<TerrainHeightBuilderMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<TerrainHeightBuilderMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TerrainHeightBuilderMaterial>(owner);
		_renderState = new RenderState( owner );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
	}

	public TerrainHeightBuilderMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( TerrainHeightBuilderMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TerrainHeightBuilderMaterial" );
		renderState = source.renderState;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TerrainHeightBuilderMaterial source = _source as TerrainHeightBuilderMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TerrainHeightBuilderMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TerrainHeightBuilderMaterial newParent = rawParent == null ? null : rawParent.Get<TerrainHeightBuilderMaterial>();
		if ( newParent == null && _newParent is TerrainHeightBuilderMaterial )
			newParent = _newParent as TerrainHeightBuilderMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[MaterialFunc("TerrainMaterialFunc.inl")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x49547344)]
[UseTypeName("MTRL")]
public class TerrainMaterial : Material
{
	private UndoRedoDBPtr<TerrainMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<TerrainMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private FloatRect _grassRect;
	private SamplerEx _A_DiffuseMap;
	private SamplerEx _N_DiffuseMap;
	private SamplerEx _B_DiffuseMap;
	private SamplerEx _FrozenNormalMap;
	private SamplerEx _NormalNormalMap;
	private SamplerEx _BurnedNormalMap;
	private SamplerEx _FrozenSpecularMap;
	private SamplerEx _NormalSpecularMap;
	private SamplerEx _BurnedSpecularMap;
	private SamplerEx _DarkMap;
	private UndoRedo<BooleanPin> _NormalMapPinValue;
	private UndoRedo<BooleanPin> _ShadowReciverPinValue;
	private UndoRedo<BooleanPin> _ShadowCasterPinValue;
	private UndoRedo<BooleanPin> _SpecularMapPinValue;
	private UndoRedo<BooleanPin> _EnvMapPinValue;
	private UndoRedo<BooleanPin> _DarkMapPinValue;
	private UndoRedo<TerrainUVSetPin> _TerrainUVSetPinValue;

	[Description( "UV координаты (можно подсмотреть в Maya) участка геометрии, который не нуждается в сшивке вершин" )]
	public FloatRect grassRect { get { return _grassRect; } set { _grassRect.Assign( value ); } }

	[Category( "Frozen" )]
	[Sampler(0, "DiffuseMapFrozen", true)]
	public SamplerEx A_DiffuseMap { get { return _A_DiffuseMap; } set { _A_DiffuseMap.Assign( value ); } }

	[Category( "Normal" )]
	[Sampler(1, "DiffuseMap", true)]
	public SamplerEx N_DiffuseMap { get { return _N_DiffuseMap; } set { _N_DiffuseMap.Assign( value ); } }

	[Category( "Burned" )]
	[Sampler(2, "DiffuseMapBurned", true)]
	public SamplerEx B_DiffuseMap { get { return _B_DiffuseMap; } set { _B_DiffuseMap.Assign( value ); } }

	[Category( "Frozen" )]
	[Sampler(3, true)]
	public SamplerEx FrozenNormalMap { get { return _FrozenNormalMap; } set { _FrozenNormalMap.Assign( value ); } }

	[Category( "Normal" )]
	[Sampler(4, true)]
	public SamplerEx NormalNormalMap { get { return _NormalNormalMap; } set { _NormalNormalMap.Assign( value ); } }

	[Category( "Burned" )]
	[Sampler(5, true)]
	public SamplerEx BurnedNormalMap { get { return _BurnedNormalMap; } set { _BurnedNormalMap.Assign( value ); } }

	[Category( "Frozen" )]
	[Sampler(6, true)]
	public SamplerEx FrozenSpecularMap { get { return _FrozenSpecularMap; } set { _FrozenSpecularMap.Assign( value ); } }

	[Category( "Normal" )]
	[Sampler(7, true)]
	public SamplerEx NormalSpecularMap { get { return _NormalSpecularMap; } set { _NormalSpecularMap.Assign( value ); } }

	[Category( "Burned" )]
	[Sampler(8, true)]
	public SamplerEx BurnedSpecularMap { get { return _BurnedSpecularMap; } set { _BurnedSpecularMap.Assign( value ); } }

	[Category( "Dark Map" )]
	[Sampler(9, true)]
	public SamplerEx DarkMap { get { return _DarkMap; } set { _DarkMap.Assign( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public BooleanPin NormalMapPinValue { get { return _NormalMapPinValue.Get(); } set { _NormalMapPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public BooleanPin ShadowReciverPinValue { get { return _ShadowReciverPinValue.Get(); } set { _ShadowReciverPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2("ShadowCasterPin")]
	public BooleanPin ShadowCasterPinValue { get { return _ShadowCasterPinValue.Get(); } set { _ShadowCasterPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public BooleanPin SpecularMapPinValue { get { return _SpecularMapPinValue.Get(); } set { _SpecularMapPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public BooleanPin EnvMapPinValue { get { return _EnvMapPinValue.Get(); } set { _EnvMapPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public BooleanPin DarkMapPinValue { get { return _DarkMapPinValue.Get(); } set { _DarkMapPinValue.Set( value ); } }

	[Category( "Pins" )]
	[Pin2]
	public TerrainUVSetPin TerrainUVSetPinValue { get { return _TerrainUVSetPinValue.Get(); } set { _TerrainUVSetPinValue.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TerrainMaterial>(owner);
		_grassRect = new FloatRect( owner );
		SamplerEx __A_DiffuseMap = new SamplerEx(); // Construct default object for A_DiffuseMap
		__A_DiffuseMap.Multiplier.R = 1.0f;
		__A_DiffuseMap.Multiplier.G = 1.0f;
		__A_DiffuseMap.Multiplier.B = 1.0f;
		__A_DiffuseMap.Add.A = 0.0f;
		_A_DiffuseMap = new SamplerEx( owner, __A_DiffuseMap );
		SamplerEx __N_DiffuseMap = new SamplerEx(); // Construct default object for N_DiffuseMap
		__N_DiffuseMap.Multiplier.R = 1.0f;
		__N_DiffuseMap.Multiplier.G = 1.0f;
		__N_DiffuseMap.Multiplier.B = 1.0f;
		__N_DiffuseMap.Add.A = 0.0f;
		_N_DiffuseMap = new SamplerEx( owner, __N_DiffuseMap );
		SamplerEx __B_DiffuseMap = new SamplerEx(); // Construct default object for B_DiffuseMap
		__B_DiffuseMap.Multiplier.R = 1.0f;
		__B_DiffuseMap.Multiplier.G = 1.0f;
		__B_DiffuseMap.Multiplier.B = 1.0f;
		__B_DiffuseMap.Add.A = 0.0f;
		_B_DiffuseMap = new SamplerEx( owner, __B_DiffuseMap );
		SamplerEx __FrozenNormalMap = new SamplerEx(); // Construct default object for FrozenNormalMap
		__FrozenNormalMap.Multiplier.R = 2.0f;
		__FrozenNormalMap.Multiplier.G = 2.0f;
		__FrozenNormalMap.Multiplier.B = 2.0f;
		__FrozenNormalMap.Multiplier.A = 0.0f;
		__FrozenNormalMap.Add.R = -1.0f;
		__FrozenNormalMap.Add.G = -1.0f;
		__FrozenNormalMap.Add.B = -1.0f;
		__FrozenNormalMap.Add.A = 0.0f;
		_FrozenNormalMap = new SamplerEx( owner, __FrozenNormalMap );
		SamplerEx __NormalNormalMap = new SamplerEx(); // Construct default object for NormalNormalMap
		__NormalNormalMap.Multiplier.R = 2.0f;
		__NormalNormalMap.Multiplier.G = 2.0f;
		__NormalNormalMap.Multiplier.B = 2.0f;
		__NormalNormalMap.Multiplier.A = 0.0f;
		__NormalNormalMap.Add.R = -1.0f;
		__NormalNormalMap.Add.G = -1.0f;
		__NormalNormalMap.Add.B = -1.0f;
		__NormalNormalMap.Add.A = 0.0f;
		_NormalNormalMap = new SamplerEx( owner, __NormalNormalMap );
		SamplerEx __BurnedNormalMap = new SamplerEx(); // Construct default object for BurnedNormalMap
		__BurnedNormalMap.Multiplier.R = 2.0f;
		__BurnedNormalMap.Multiplier.G = 2.0f;
		__BurnedNormalMap.Multiplier.B = 2.0f;
		__BurnedNormalMap.Multiplier.A = 0.0f;
		__BurnedNormalMap.Add.R = -1.0f;
		__BurnedNormalMap.Add.G = -1.0f;
		__BurnedNormalMap.Add.B = -1.0f;
		__BurnedNormalMap.Add.A = 0.0f;
		_BurnedNormalMap = new SamplerEx( owner, __BurnedNormalMap );
		SamplerEx __FrozenSpecularMap = new SamplerEx(); // Construct default object for FrozenSpecularMap
		__FrozenSpecularMap.Multiplier.R = 1.0f;
		__FrozenSpecularMap.Multiplier.G = 1.0f;
		__FrozenSpecularMap.Multiplier.B = 1.0f;
		__FrozenSpecularMap.Add.A = 0.0f;
		_FrozenSpecularMap = new SamplerEx( owner, __FrozenSpecularMap );
		SamplerEx __NormalSpecularMap = new SamplerEx(); // Construct default object for NormalSpecularMap
		__NormalSpecularMap.Multiplier.R = 1.0f;
		__NormalSpecularMap.Multiplier.G = 1.0f;
		__NormalSpecularMap.Multiplier.B = 1.0f;
		__NormalSpecularMap.Add.A = 0.0f;
		_NormalSpecularMap = new SamplerEx( owner, __NormalSpecularMap );
		SamplerEx __BurnedSpecularMap = new SamplerEx(); // Construct default object for BurnedSpecularMap
		__BurnedSpecularMap.Multiplier.R = 1.0f;
		__BurnedSpecularMap.Multiplier.G = 1.0f;
		__BurnedSpecularMap.Multiplier.B = 1.0f;
		__BurnedSpecularMap.Add.A = 0.0f;
		_BurnedSpecularMap = new SamplerEx( owner, __BurnedSpecularMap );
		SamplerEx __DarkMap = new SamplerEx(); // Construct default object for DarkMap
		__DarkMap.Multiplier.R = 1.0f;
		__DarkMap.Multiplier.G = 1.0f;
		__DarkMap.Multiplier.B = 1.0f;
		__DarkMap.Add.A = 0.0f;
		_DarkMap = new SamplerEx( owner, __DarkMap );
		_NormalMapPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_ShadowReciverPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.Present );
		_ShadowCasterPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.Present );
		_SpecularMapPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_EnvMapPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_DarkMapPinValue = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_TerrainUVSetPinValue = new UndoRedo<TerrainUVSetPin>( owner, TerrainUVSetPin.Global );
		___parent.Changed += FireChangedEvent;
		_grassRect.Changed += FireChangedEvent;
		_A_DiffuseMap.Changed += FireChangedEvent;
		_N_DiffuseMap.Changed += FireChangedEvent;
		_B_DiffuseMap.Changed += FireChangedEvent;
		_FrozenNormalMap.Changed += FireChangedEvent;
		_NormalNormalMap.Changed += FireChangedEvent;
		_BurnedNormalMap.Changed += FireChangedEvent;
		_FrozenSpecularMap.Changed += FireChangedEvent;
		_NormalSpecularMap.Changed += FireChangedEvent;
		_BurnedSpecularMap.Changed += FireChangedEvent;
		_DarkMap.Changed += FireChangedEvent;
		_NormalMapPinValue.Changed += FireChangedEvent;
		_ShadowReciverPinValue.Changed += FireChangedEvent;
		_ShadowCasterPinValue.Changed += FireChangedEvent;
		_SpecularMapPinValue.Changed += FireChangedEvent;
		_EnvMapPinValue.Changed += FireChangedEvent;
		_DarkMapPinValue.Changed += FireChangedEvent;
		_TerrainUVSetPinValue.Changed += FireChangedEvent;
	}

	public TerrainMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( TerrainMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TerrainMaterial" );
		grassRect = source.grassRect;
		A_DiffuseMap = source.A_DiffuseMap;
		N_DiffuseMap = source.N_DiffuseMap;
		B_DiffuseMap = source.B_DiffuseMap;
		FrozenNormalMap = source.FrozenNormalMap;
		NormalNormalMap = source.NormalNormalMap;
		BurnedNormalMap = source.BurnedNormalMap;
		FrozenSpecularMap = source.FrozenSpecularMap;
		NormalSpecularMap = source.NormalSpecularMap;
		BurnedSpecularMap = source.BurnedSpecularMap;
		DarkMap = source.DarkMap;
		NormalMapPinValue = source.NormalMapPinValue;
		ShadowReciverPinValue = source.ShadowReciverPinValue;
		ShadowCasterPinValue = source.ShadowCasterPinValue;
		SpecularMapPinValue = source.SpecularMapPinValue;
		EnvMapPinValue = source.EnvMapPinValue;
		DarkMapPinValue = source.DarkMapPinValue;
		TerrainUVSetPinValue = source.TerrainUVSetPinValue;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TerrainMaterial source = _source as TerrainMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TerrainMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TerrainMaterial newParent = rawParent == null ? null : rawParent.Get<TerrainMaterial>();
		if ( newParent == null && _newParent is TerrainMaterial )
			newParent = _newParent as TerrainMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_grassRect.SetParent( newParent == null ? null : newParent._grassRect );
		_A_DiffuseMap.SetParent( newParent == null ? null : newParent._A_DiffuseMap );
		_N_DiffuseMap.SetParent( newParent == null ? null : newParent._N_DiffuseMap );
		_B_DiffuseMap.SetParent( newParent == null ? null : newParent._B_DiffuseMap );
		_FrozenNormalMap.SetParent( newParent == null ? null : newParent._FrozenNormalMap );
		_NormalNormalMap.SetParent( newParent == null ? null : newParent._NormalNormalMap );
		_BurnedNormalMap.SetParent( newParent == null ? null : newParent._BurnedNormalMap );
		_FrozenSpecularMap.SetParent( newParent == null ? null : newParent._FrozenSpecularMap );
		_NormalSpecularMap.SetParent( newParent == null ? null : newParent._NormalSpecularMap );
		_BurnedSpecularMap.SetParent( newParent == null ? null : newParent._BurnedSpecularMap );
		_DarkMap.SetParent( newParent == null ? null : newParent._DarkMap );
		_NormalMapPinValue.SetParent( newParent == null ? null : newParent._NormalMapPinValue );
		_ShadowReciverPinValue.SetParent( newParent == null ? null : newParent._ShadowReciverPinValue );
		_ShadowCasterPinValue.SetParent( newParent == null ? null : newParent._ShadowCasterPinValue );
		_SpecularMapPinValue.SetParent( newParent == null ? null : newParent._SpecularMapPinValue );
		_EnvMapPinValue.SetParent( newParent == null ? null : newParent._EnvMapPinValue );
		_DarkMapPinValue.SetParent( newParent == null ? null : newParent._DarkMapPinValue );
		_TerrainUVSetPinValue.SetParent( newParent == null ? null : newParent._TerrainUVSetPinValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_grassRect.Reset();
		_A_DiffuseMap.Reset();
		_N_DiffuseMap.Reset();
		_B_DiffuseMap.Reset();
		_FrozenNormalMap.Reset();
		_NormalNormalMap.Reset();
		_BurnedNormalMap.Reset();
		_FrozenSpecularMap.Reset();
		_NormalSpecularMap.Reset();
		_BurnedSpecularMap.Reset();
		_DarkMap.Reset();
		_NormalMapPinValue.Reset();
		_ShadowReciverPinValue.Reset();
		_ShadowCasterPinValue.Reset();
		_SpecularMapPinValue.Reset();
		_EnvMapPinValue.Reset();
		_DarkMapPinValue.Reset();
		_TerrainUVSetPinValue.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_grassRect.IsDerivedFromParent()
			&& _A_DiffuseMap.IsDerivedFromParent()
			&& _N_DiffuseMap.IsDerivedFromParent()
			&& _B_DiffuseMap.IsDerivedFromParent()
			&& _FrozenNormalMap.IsDerivedFromParent()
			&& _NormalNormalMap.IsDerivedFromParent()
			&& _BurnedNormalMap.IsDerivedFromParent()
			&& _FrozenSpecularMap.IsDerivedFromParent()
			&& _NormalSpecularMap.IsDerivedFromParent()
			&& _BurnedSpecularMap.IsDerivedFromParent()
			&& _DarkMap.IsDerivedFromParent()
			&& _NormalMapPinValue.IsDerivedFromParent()
			&& _ShadowReciverPinValue.IsDerivedFromParent()
			&& _ShadowCasterPinValue.IsDerivedFromParent()
			&& _SpecularMapPinValue.IsDerivedFromParent()
			&& _EnvMapPinValue.IsDerivedFromParent()
			&& _DarkMapPinValue.IsDerivedFromParent()
			&& _TerrainUVSetPinValue.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "grassRect" )
			_grassRect.Reset();
		else if ( fieldName == "A_DiffuseMap" )
			_A_DiffuseMap.Reset();
		else if ( fieldName == "N_DiffuseMap" )
			_N_DiffuseMap.Reset();
		else if ( fieldName == "B_DiffuseMap" )
			_B_DiffuseMap.Reset();
		else if ( fieldName == "FrozenNormalMap" )
			_FrozenNormalMap.Reset();
		else if ( fieldName == "NormalNormalMap" )
			_NormalNormalMap.Reset();
		else if ( fieldName == "BurnedNormalMap" )
			_BurnedNormalMap.Reset();
		else if ( fieldName == "FrozenSpecularMap" )
			_FrozenSpecularMap.Reset();
		else if ( fieldName == "NormalSpecularMap" )
			_NormalSpecularMap.Reset();
		else if ( fieldName == "BurnedSpecularMap" )
			_BurnedSpecularMap.Reset();
		else if ( fieldName == "DarkMap" )
			_DarkMap.Reset();
		else if ( fieldName == "NormalMapPinValue" )
			_NormalMapPinValue.Reset();
		else if ( fieldName == "ShadowReciverPinValue" )
			_ShadowReciverPinValue.Reset();
		else if ( fieldName == "ShadowCasterPinValue" )
			_ShadowCasterPinValue.Reset();
		else if ( fieldName == "SpecularMapPinValue" )
			_SpecularMapPinValue.Reset();
		else if ( fieldName == "EnvMapPinValue" )
			_EnvMapPinValue.Reset();
		else if ( fieldName == "DarkMapPinValue" )
			_DarkMapPinValue.Reset();
		else if ( fieldName == "TerrainUVSetPinValue" )
			_TerrainUVSetPinValue.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "grassRect" )
			return _grassRect.IsDerivedFromParent();
		if ( fieldName == "A_DiffuseMap" )
			return _A_DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "N_DiffuseMap" )
			return _N_DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "B_DiffuseMap" )
			return _B_DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "FrozenNormalMap" )
			return _FrozenNormalMap.IsDerivedFromParent();
		if ( fieldName == "NormalNormalMap" )
			return _NormalNormalMap.IsDerivedFromParent();
		if ( fieldName == "BurnedNormalMap" )
			return _BurnedNormalMap.IsDerivedFromParent();
		if ( fieldName == "FrozenSpecularMap" )
			return _FrozenSpecularMap.IsDerivedFromParent();
		if ( fieldName == "NormalSpecularMap" )
			return _NormalSpecularMap.IsDerivedFromParent();
		if ( fieldName == "BurnedSpecularMap" )
			return _BurnedSpecularMap.IsDerivedFromParent();
		if ( fieldName == "DarkMap" )
			return _DarkMap.IsDerivedFromParent();
		if ( fieldName == "NormalMapPinValue" )
			return _NormalMapPinValue.IsDerivedFromParent();
		if ( fieldName == "ShadowReciverPinValue" )
			return _ShadowReciverPinValue.IsDerivedFromParent();
		if ( fieldName == "ShadowCasterPinValue" )
			return _ShadowCasterPinValue.IsDerivedFromParent();
		if ( fieldName == "SpecularMapPinValue" )
			return _SpecularMapPinValue.IsDerivedFromParent();
		if ( fieldName == "EnvMapPinValue" )
			return _EnvMapPinValue.IsDerivedFromParent();
		if ( fieldName == "DarkMapPinValue" )
			return _DarkMapPinValue.IsDerivedFromParent();
		if ( fieldName == "TerrainUVSetPinValue" )
			return _TerrainUVSetPinValue.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialFunc("TestTownMaterial.inl")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9D66EBC0)]
[UseTypeName("MTRL")]
public class TestTownMaterial : Material
{
	private UndoRedoDBPtr<TestTownMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<TestTownMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _RenderState;
	private Sampler _DiffuseMap;
	private UndoRedo<BooleanPin> _UseDiffuse;
	private HDRColor _outputMul;
	private HDRColor _outputAdd;

	[Category( "States" )]
	public RenderState RenderState { get { return _RenderState; } set { _RenderState.Assign( value ); } }

	[Sampler(0, "DiffuseMap")]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Pin2("UseDiffuse")]
	public BooleanPin UseDiffuse { get { return _UseDiffuse.Get(); } set { _UseDiffuse.Set( value ); } }

	[Category( "Modificator" )]
	public HDRColor outputMul { get { return _outputMul; } set { _outputMul.Assign( value ); } }

	[Category( "Modificator" )]
	public HDRColor outputAdd { get { return _outputAdd; } set { _outputAdd.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TestTownMaterial>(owner);
		_RenderState = new RenderState( owner );
		Sampler __DiffuseMap = new Sampler(); // Construct default object for DiffuseMap
		__DiffuseMap.samplerState.addressU = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressV = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressW = TextureAddressType.Clamp;
		_DiffuseMap = new Sampler( owner, __DiffuseMap );
		_UseDiffuse = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		HDRColor __outputMul = new HDRColor(); // Construct default object for outputMul
		__outputMul.R = 1.0f;
		__outputMul.G = 1.0f;
		__outputMul.B = 1.0f;
		_outputMul = new HDRColor( owner, __outputMul );
		HDRColor __outputAdd = new HDRColor(); // Construct default object for outputAdd
		__outputAdd.A = 0.0f;
		_outputAdd = new HDRColor( owner, __outputAdd );
		___parent.Changed += FireChangedEvent;
		_RenderState.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_UseDiffuse.Changed += FireChangedEvent;
		_outputMul.Changed += FireChangedEvent;
		_outputAdd.Changed += FireChangedEvent;
	}

	public TestTownMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( TestTownMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TestTownMaterial" );
		RenderState = source.RenderState;
		DiffuseMap = source.DiffuseMap;
		UseDiffuse = source.UseDiffuse;
		outputMul = source.outputMul;
		outputAdd = source.outputAdd;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TestTownMaterial source = _source as TestTownMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TestTownMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TestTownMaterial newParent = rawParent == null ? null : rawParent.Get<TestTownMaterial>();
		if ( newParent == null && _newParent is TestTownMaterial )
			newParent = _newParent as TestTownMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_RenderState.SetParent( newParent == null ? null : newParent._RenderState );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_UseDiffuse.SetParent( newParent == null ? null : newParent._UseDiffuse );
		_outputMul.SetParent( newParent == null ? null : newParent._outputMul );
		_outputAdd.SetParent( newParent == null ? null : newParent._outputAdd );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_RenderState.Reset();
		_DiffuseMap.Reset();
		_UseDiffuse.Reset();
		_outputMul.Reset();
		_outputAdd.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_RenderState.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _UseDiffuse.IsDerivedFromParent()
			&& _outputMul.IsDerivedFromParent()
			&& _outputAdd.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "RenderState" )
			_RenderState.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "UseDiffuse" )
			_UseDiffuse.Reset();
		else if ( fieldName == "outputMul" )
			_outputMul.Reset();
		else if ( fieldName == "outputAdd" )
			_outputAdd.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "RenderState" )
			return _RenderState.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "UseDiffuse" )
			return _UseDiffuse.IsDerivedFromParent();
		if ( fieldName == "outputMul" )
			return _outputMul.IsDerivedFromParent();
		if ( fieldName == "outputAdd" )
			return _outputAdd.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Load", "Render::Texture", ReturnType = "CObj<Render::Texture>", Define = "!VISUAL_CUTTED")]
[FactoryBase("LoadInPool", "Render::Texture", "bool canBeVisualDegrade", "void * texturePoolId", ReturnType = "CObj<Render::Texture>", Define = "!VISUAL_CUTTED")]
public class TextureBase : DBResource
{
	private UndoRedoDBPtr<TextureBase> ___parent;
	[HideInOutliner]
	public new DBPtr<TextureBase> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TextureBase>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public TextureBase()
	{
		Initialize( this );
	}
	private void AssignSelf( TextureBase source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TextureBase" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TextureBase source = _source as TextureBase;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TextureBase" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TextureBase newParent = rawParent == null ? null : rawParent.Get<TextureBase>();
		if ( newParent == null && _newParent is TextureBase )
			newParent = _newParent as TextureBase;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialFunc("CommonMaterialFunc.inl")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B61AC40)]
[UseTypeName("MTRL")]
public class TraceMaterial : Material
{
	private UndoRedoDBPtr<TraceMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<TraceMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private RenderState _renderState;
	private Sampler _DiffuseMap;
	private UndoRedo<float> _uScale;
	private UndoRedo<float> _vScale;
	private AnimatedFloat _uOffset;
	private AnimatedFloat _vOffset;

	[Category( "States" )]
	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	[Category( "Diffuse" )]
	[Sampler(0, "DiffuseMap")]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	public float uScale { get { return _uScale.Get(); } set { _uScale.Set( value ); } }

	public float vScale { get { return _vScale.Get(); } set { _vScale.Set( value ); } }

	public AnimatedFloat uOffset { get { return _uOffset; } set { _uOffset.Assign( value ); } }

	public AnimatedFloat vOffset { get { return _vOffset; } set { _vOffset.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TraceMaterial>(owner);
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.alphaTest = OnOffState.On;
		__renderState.alphaTestRef = 0;
		__renderState.culling = OnOffState.Off;
		_renderState = new RenderState( owner, __renderState );
		_DiffuseMap = new Sampler( owner );
		_uScale = new UndoRedo<float>( owner, 1.0f );
		_vScale = new UndoRedo<float>( owner, 1.0f );
		_uOffset = new AnimatedFloat( owner );
		_vOffset = new AnimatedFloat( owner );
		___parent.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_uScale.Changed += FireChangedEvent;
		_vScale.Changed += FireChangedEvent;
		_uOffset.Changed += FireChangedEvent;
		_vOffset.Changed += FireChangedEvent;
	}

	public TraceMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( TraceMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TraceMaterial" );
		renderState = source.renderState;
		DiffuseMap = source.DiffuseMap;
		uScale = source.uScale;
		vScale = source.vScale;
		uOffset = source.uOffset;
		vOffset = source.vOffset;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TraceMaterial source = _source as TraceMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TraceMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TraceMaterial newParent = rawParent == null ? null : rawParent.Get<TraceMaterial>();
		if ( newParent == null && _newParent is TraceMaterial )
			newParent = _newParent as TraceMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_uScale.SetParent( newParent == null ? null : newParent._uScale );
		_vScale.SetParent( newParent == null ? null : newParent._vScale );
		_uOffset.SetParent( newParent == null ? null : newParent._uOffset );
		_vOffset.SetParent( newParent == null ? null : newParent._vOffset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_renderState.Reset();
		_DiffuseMap.Reset();
		_uScale.Reset();
		_vScale.Reset();
		_uOffset.Reset();
		_vOffset.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_renderState.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _uScale.IsDerivedFromParent()
			&& _vScale.IsDerivedFromParent()
			&& _uOffset.IsDerivedFromParent()
			&& _vOffset.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "renderState" )
			_renderState.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "uScale" )
			_uScale.Reset();
		else if ( fieldName == "vScale" )
			_vScale.Reset();
		else if ( fieldName == "uOffset" )
			_uOffset.Reset();
		else if ( fieldName == "vOffset" )
			_vOffset.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "uScale" )
			return _uScale.IsDerivedFromParent();
		if ( fieldName == "vScale" )
			return _vScale.IsDerivedFromParent();
		if ( fieldName == "uOffset" )
			return _uOffset.IsDerivedFromParent();
		if ( fieldName == "vOffset" )
			return _vOffset.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[DBVersion(0)]
[MaterialFunc("UIBaseMaterial.inl", "ModifyCoefs(const float coef3, const float coef4)", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)", "ModifyStripesConstants(const float start, const float step1, const float step2, const float blendFactor1)", "ModifyStripesColor(const Render::HDRColor &color1, const Render::HDRColor &color2)")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9D656300)]
[UseTypeName("MTRL")]
public class UIBaseMaterial : BaseUIMaterial
{
	private UndoRedoDBPtr<UIBaseMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<UIBaseMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private Sampler _DiffuseMap;
	private Sampler _MaskMap;
	private HDRColor _color1;
	private HDRColor _color2;
	private UndoRedo<float> _coef1;
	private UndoRedo<float> _coef2;
	private UndoRedo<BooleanPin> _UseDiffuse;
	private UndoRedo<MaskingTypePin> _Masking;
	private UndoRedo<BooleanPin> _Gradient;
	private UndoRedo<BooleanPin> _Colorized;
	private UndoRedo<BooleanPin> _Stripes;
	private HDRColor _colorStripe100;
	private HDRColor _colorStripe1000;
	private RenderState _renderState;

	[Sampler(0, "DiffuseMap")]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Sampler(1, "MaskMap")]
	public Sampler MaskMap { get { return _MaskMap; } set { _MaskMap.Assign( value ); } }

	public HDRColor color1 { get { return _color1; } set { _color1.Assign( value ); } }

	public HDRColor color2 { get { return _color2; } set { _color2.Assign( value ); } }

	public float coef1 { get { return _coef1.Get(); } set { _coef1.Set( value ); } }

	public float coef2 { get { return _coef2.Get(); } set { _coef2.Set( value ); } }

	[Pin2("UseDiffuse")]
	public BooleanPin UseDiffuse { get { return _UseDiffuse.Get(); } set { _UseDiffuse.Set( value ); } }

	[Pin2("Masking")]
	public MaskingTypePin Masking { get { return _Masking.Get(); } set { _Masking.Set( value ); } }

	[Pin2("Gradient")]
	public BooleanPin Gradient { get { return _Gradient.Get(); } set { _Gradient.Set( value ); } }

	[Pin2("Colorized")]
	public BooleanPin Colorized { get { return _Colorized.Get(); } set { _Colorized.Set( value ); } }

	[Pin2("Stripes")]
	public BooleanPin Stripes { get { return _Stripes.Get(); } set { _Stripes.Set( value ); } }

	public HDRColor colorStripe100 { get { return _colorStripe100; } set { _colorStripe100.Assign( value ); } }

	public HDRColor colorStripe1000 { get { return _colorStripe1000; } set { _colorStripe1000.Assign( value ); } }

	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIBaseMaterial>(owner);
		Sampler __DiffuseMap = new Sampler(); // Construct default object for DiffuseMap
		__DiffuseMap.samplerState.mipFilter = MipFilterType.Point;
		__DiffuseMap.samplerState.addressU = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressV = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressW = TextureAddressType.Clamp;
		_DiffuseMap = new Sampler( owner, __DiffuseMap );
		Sampler __MaskMap = new Sampler(); // Construct default object for MaskMap
		__MaskMap.samplerState.mipFilter = MipFilterType.Point;
		__MaskMap.samplerState.addressU = TextureAddressType.Clamp;
		__MaskMap.samplerState.addressV = TextureAddressType.Clamp;
		__MaskMap.samplerState.addressW = TextureAddressType.Clamp;
		_MaskMap = new Sampler( owner, __MaskMap );
		HDRColor __color1 = new HDRColor(); // Construct default object for color1
		__color1.R = 1.0f;
		__color1.G = 1.0f;
		__color1.B = 1.0f;
		_color1 = new HDRColor( owner, __color1 );
		_color2 = new HDRColor( owner );
		_coef1 = new UndoRedo<float>( owner, 0.0f );
		_coef2 = new UndoRedo<float>( owner, 0.0f );
		_UseDiffuse = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_Masking = new UndoRedo<MaskingTypePin>( owner, MaskingTypePin.NoMasking );
		_Gradient = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_Colorized = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_Stripes = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_colorStripe100 = new HDRColor( owner );
		HDRColor __colorStripe1000 = new HDRColor(); // Construct default object for colorStripe1000
		__colorStripe1000.R = 1.0f;
		__colorStripe1000.G = 0.68f;
		__colorStripe1000.B = 0.19f;
		_colorStripe1000 = new HDRColor( owner, __colorStripe1000 );
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.culling = OnOffState.Off;
		_renderState = new RenderState( owner, __renderState );
		___parent.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_MaskMap.Changed += FireChangedEvent;
		_color1.Changed += FireChangedEvent;
		_color2.Changed += FireChangedEvent;
		_coef1.Changed += FireChangedEvent;
		_coef2.Changed += FireChangedEvent;
		_UseDiffuse.Changed += FireChangedEvent;
		_Masking.Changed += FireChangedEvent;
		_Gradient.Changed += FireChangedEvent;
		_Colorized.Changed += FireChangedEvent;
		_Stripes.Changed += FireChangedEvent;
		_colorStripe100.Changed += FireChangedEvent;
		_colorStripe1000.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
	}

	public UIBaseMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( UIBaseMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIBaseMaterial" );
		DiffuseMap = source.DiffuseMap;
		MaskMap = source.MaskMap;
		color1 = source.color1;
		color2 = source.color2;
		coef1 = source.coef1;
		coef2 = source.coef2;
		UseDiffuse = source.UseDiffuse;
		Masking = source.Masking;
		Gradient = source.Gradient;
		Colorized = source.Colorized;
		Stripes = source.Stripes;
		colorStripe100 = source.colorStripe100;
		colorStripe1000 = source.colorStripe1000;
		renderState = source.renderState;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIBaseMaterial source = _source as UIBaseMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIBaseMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIBaseMaterial newParent = rawParent == null ? null : rawParent.Get<UIBaseMaterial>();
		if ( newParent == null && _newParent is UIBaseMaterial )
			newParent = _newParent as UIBaseMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_MaskMap.SetParent( newParent == null ? null : newParent._MaskMap );
		_color1.SetParent( newParent == null ? null : newParent._color1 );
		_color2.SetParent( newParent == null ? null : newParent._color2 );
		_coef1.SetParent( newParent == null ? null : newParent._coef1 );
		_coef2.SetParent( newParent == null ? null : newParent._coef2 );
		_UseDiffuse.SetParent( newParent == null ? null : newParent._UseDiffuse );
		_Masking.SetParent( newParent == null ? null : newParent._Masking );
		_Gradient.SetParent( newParent == null ? null : newParent._Gradient );
		_Colorized.SetParent( newParent == null ? null : newParent._Colorized );
		_Stripes.SetParent( newParent == null ? null : newParent._Stripes );
		_colorStripe100.SetParent( newParent == null ? null : newParent._colorStripe100 );
		_colorStripe1000.SetParent( newParent == null ? null : newParent._colorStripe1000 );
		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_DiffuseMap.Reset();
		_MaskMap.Reset();
		_color1.Reset();
		_color2.Reset();
		_coef1.Reset();
		_coef2.Reset();
		_UseDiffuse.Reset();
		_Masking.Reset();
		_Gradient.Reset();
		_Colorized.Reset();
		_Stripes.Reset();
		_colorStripe100.Reset();
		_colorStripe1000.Reset();
		_renderState.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_DiffuseMap.IsDerivedFromParent()
			&& _MaskMap.IsDerivedFromParent()
			&& _color1.IsDerivedFromParent()
			&& _color2.IsDerivedFromParent()
			&& _coef1.IsDerivedFromParent()
			&& _coef2.IsDerivedFromParent()
			&& _UseDiffuse.IsDerivedFromParent()
			&& _Masking.IsDerivedFromParent()
			&& _Gradient.IsDerivedFromParent()
			&& _Colorized.IsDerivedFromParent()
			&& _Stripes.IsDerivedFromParent()
			&& _colorStripe100.IsDerivedFromParent()
			&& _colorStripe1000.IsDerivedFromParent()
			&& _renderState.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "MaskMap" )
			_MaskMap.Reset();
		else if ( fieldName == "color1" )
			_color1.Reset();
		else if ( fieldName == "color2" )
			_color2.Reset();
		else if ( fieldName == "coef1" )
			_coef1.Reset();
		else if ( fieldName == "coef2" )
			_coef2.Reset();
		else if ( fieldName == "UseDiffuse" )
			_UseDiffuse.Reset();
		else if ( fieldName == "Masking" )
			_Masking.Reset();
		else if ( fieldName == "Gradient" )
			_Gradient.Reset();
		else if ( fieldName == "Colorized" )
			_Colorized.Reset();
		else if ( fieldName == "Stripes" )
			_Stripes.Reset();
		else if ( fieldName == "colorStripe100" )
			_colorStripe100.Reset();
		else if ( fieldName == "colorStripe1000" )
			_colorStripe1000.Reset();
		else if ( fieldName == "renderState" )
			_renderState.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "MaskMap" )
			return _MaskMap.IsDerivedFromParent();
		if ( fieldName == "color1" )
			return _color1.IsDerivedFromParent();
		if ( fieldName == "color2" )
			return _color2.IsDerivedFromParent();
		if ( fieldName == "coef1" )
			return _coef1.IsDerivedFromParent();
		if ( fieldName == "coef2" )
			return _coef2.IsDerivedFromParent();
		if ( fieldName == "UseDiffuse" )
			return _UseDiffuse.IsDerivedFromParent();
		if ( fieldName == "Masking" )
			return _Masking.IsDerivedFromParent();
		if ( fieldName == "Gradient" )
			return _Gradient.IsDerivedFromParent();
		if ( fieldName == "Colorized" )
			return _Colorized.IsDerivedFromParent();
		if ( fieldName == "Stripes" )
			return _Stripes.IsDerivedFromParent();
		if ( fieldName == "colorStripe100" )
			return _colorStripe100.IsDerivedFromParent();
		if ( fieldName == "colorStripe1000" )
			return _colorStripe1000.IsDerivedFromParent();
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialFunc("UIButtonMaterial.inl")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9D6ABB80)]
[UseTypeName("MTRL")]
public class UIButtonMaterial : BaseUIMaterial
{
	private UndoRedoDBPtr<UIButtonMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<UIButtonMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private Sampler _BackgroundMap;
	private Sampler _DiffuseMap;
	private Sampler _WaitForActMap;
	private Sampler _LackOfManaMap;
	private Sampler _PressedMap;
	private Sampler _HighlightMap;
	private Sampler _ScreenMap;
	private UndoRedo<BooleanPin> _WaitForActivationPin;
	private UndoRedo<BooleanPin> _LackOfManaPin;
	private UndoRedo<BooleanPin> _PressedPin;
	private UndoRedo<BooleanPin> _HighlightPin;
	private UndoRedo<BooleanPin> _DisablePin;
	private UndoRedo<BooleanPin> _PassivePin;
	private UndoRedo<BooleanPin> _UseDiffusePin;
	private UndoRedo<float> _ScreenOpacity;
	private RenderState _renderState;

	[Sampler(0, "BackgroundMap")]
	public Sampler BackgroundMap { get { return _BackgroundMap; } set { _BackgroundMap.Assign( value ); } }

	[Sampler(1, "DiffuseMap")]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Sampler(2, "WaitForActivation")]
	public Sampler WaitForActMap { get { return _WaitForActMap; } set { _WaitForActMap.Assign( value ); } }

	[Sampler(3, "LackOfMana")]
	public Sampler LackOfManaMap { get { return _LackOfManaMap; } set { _LackOfManaMap.Assign( value ); } }

	[Sampler(4, "Pressed")]
	public Sampler PressedMap { get { return _PressedMap; } set { _PressedMap.Assign( value ); } }

	[Sampler(5, "Highlight")]
	public Sampler HighlightMap { get { return _HighlightMap; } set { _HighlightMap.Assign( value ); } }

	[Sampler(6, "ScreenMap")]
	public Sampler ScreenMap { get { return _ScreenMap; } set { _ScreenMap.Assign( value ); } }

	[Pin2("WaitForActivationPin")]
	public BooleanPin WaitForActivationPin { get { return _WaitForActivationPin.Get(); } set { _WaitForActivationPin.Set( value ); } }

	[Pin2("LackOfManaPin")]
	public BooleanPin LackOfManaPin { get { return _LackOfManaPin.Get(); } set { _LackOfManaPin.Set( value ); } }

	[Pin2("PressedPin")]
	public BooleanPin PressedPin { get { return _PressedPin.Get(); } set { _PressedPin.Set( value ); } }

	[Pin2("HighlightPin")]
	public BooleanPin HighlightPin { get { return _HighlightPin.Get(); } set { _HighlightPin.Set( value ); } }

	[Pin2("DisablePin")]
	public BooleanPin DisablePin { get { return _DisablePin.Get(); } set { _DisablePin.Set( value ); } }

	[Pin2("PassivePin")]
	public BooleanPin PassivePin { get { return _PassivePin.Get(); } set { _PassivePin.Set( value ); } }

	[Pin2("UseDiffusePin")]
	public BooleanPin UseDiffusePin { get { return _UseDiffusePin.Get(); } set { _UseDiffusePin.Set( value ); } }

	public float ScreenOpacity { get { return _ScreenOpacity.Get(); } set { _ScreenOpacity.Set( value ); } }

	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIButtonMaterial>(owner);
		Sampler __BackgroundMap = new Sampler(); // Construct default object for BackgroundMap
		__BackgroundMap.samplerState.mipFilter = MipFilterType.Point;
		__BackgroundMap.samplerState.addressU = TextureAddressType.Clamp;
		__BackgroundMap.samplerState.addressV = TextureAddressType.Clamp;
		__BackgroundMap.samplerState.addressW = TextureAddressType.Clamp;
		_BackgroundMap = new Sampler( owner, __BackgroundMap );
		Sampler __DiffuseMap = new Sampler(); // Construct default object for DiffuseMap
		__DiffuseMap.samplerState.mipFilter = MipFilterType.Point;
		__DiffuseMap.samplerState.addressU = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressV = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressW = TextureAddressType.Clamp;
		_DiffuseMap = new Sampler( owner, __DiffuseMap );
		Sampler __WaitForActMap = new Sampler(); // Construct default object for WaitForActMap
		__WaitForActMap.samplerState.mipFilter = MipFilterType.Point;
		__WaitForActMap.samplerState.addressU = TextureAddressType.Clamp;
		__WaitForActMap.samplerState.addressV = TextureAddressType.Clamp;
		__WaitForActMap.samplerState.addressW = TextureAddressType.Clamp;
		_WaitForActMap = new Sampler( owner, __WaitForActMap );
		Sampler __LackOfManaMap = new Sampler(); // Construct default object for LackOfManaMap
		__LackOfManaMap.samplerState.mipFilter = MipFilterType.Point;
		__LackOfManaMap.samplerState.addressU = TextureAddressType.Clamp;
		__LackOfManaMap.samplerState.addressV = TextureAddressType.Clamp;
		__LackOfManaMap.samplerState.addressW = TextureAddressType.Clamp;
		_LackOfManaMap = new Sampler( owner, __LackOfManaMap );
		Sampler __PressedMap = new Sampler(); // Construct default object for PressedMap
		__PressedMap.samplerState.mipFilter = MipFilterType.Point;
		__PressedMap.samplerState.addressU = TextureAddressType.Clamp;
		__PressedMap.samplerState.addressV = TextureAddressType.Clamp;
		__PressedMap.samplerState.addressW = TextureAddressType.Clamp;
		_PressedMap = new Sampler( owner, __PressedMap );
		Sampler __HighlightMap = new Sampler(); // Construct default object for HighlightMap
		__HighlightMap.samplerState.mipFilter = MipFilterType.Point;
		__HighlightMap.samplerState.addressU = TextureAddressType.Clamp;
		__HighlightMap.samplerState.addressV = TextureAddressType.Clamp;
		__HighlightMap.samplerState.addressW = TextureAddressType.Clamp;
		_HighlightMap = new Sampler( owner, __HighlightMap );
		Sampler __ScreenMap = new Sampler(); // Construct default object for ScreenMap
		__ScreenMap.samplerState.mipFilter = MipFilterType.Point;
		__ScreenMap.samplerState.addressU = TextureAddressType.Clamp;
		__ScreenMap.samplerState.addressV = TextureAddressType.Clamp;
		__ScreenMap.samplerState.addressW = TextureAddressType.Clamp;
		_ScreenMap = new Sampler( owner, __ScreenMap );
		_WaitForActivationPin = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_LackOfManaPin = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_PressedPin = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_HighlightPin = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_DisablePin = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_PassivePin = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_UseDiffusePin = new UndoRedo<BooleanPin>( owner, BooleanPin.Present );
		_ScreenOpacity = new UndoRedo<float>( owner, 1.0f );
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.culling = OnOffState.Off;
		_renderState = new RenderState( owner, __renderState );
		___parent.Changed += FireChangedEvent;
		_BackgroundMap.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_WaitForActMap.Changed += FireChangedEvent;
		_LackOfManaMap.Changed += FireChangedEvent;
		_PressedMap.Changed += FireChangedEvent;
		_HighlightMap.Changed += FireChangedEvent;
		_ScreenMap.Changed += FireChangedEvent;
		_WaitForActivationPin.Changed += FireChangedEvent;
		_LackOfManaPin.Changed += FireChangedEvent;
		_PressedPin.Changed += FireChangedEvent;
		_HighlightPin.Changed += FireChangedEvent;
		_DisablePin.Changed += FireChangedEvent;
		_PassivePin.Changed += FireChangedEvent;
		_UseDiffusePin.Changed += FireChangedEvent;
		_ScreenOpacity.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
	}

	public UIButtonMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( UIButtonMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIButtonMaterial" );
		BackgroundMap = source.BackgroundMap;
		DiffuseMap = source.DiffuseMap;
		WaitForActMap = source.WaitForActMap;
		LackOfManaMap = source.LackOfManaMap;
		PressedMap = source.PressedMap;
		HighlightMap = source.HighlightMap;
		ScreenMap = source.ScreenMap;
		WaitForActivationPin = source.WaitForActivationPin;
		LackOfManaPin = source.LackOfManaPin;
		PressedPin = source.PressedPin;
		HighlightPin = source.HighlightPin;
		DisablePin = source.DisablePin;
		PassivePin = source.PassivePin;
		UseDiffusePin = source.UseDiffusePin;
		ScreenOpacity = source.ScreenOpacity;
		renderState = source.renderState;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIButtonMaterial source = _source as UIButtonMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIButtonMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIButtonMaterial newParent = rawParent == null ? null : rawParent.Get<UIButtonMaterial>();
		if ( newParent == null && _newParent is UIButtonMaterial )
			newParent = _newParent as UIButtonMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_BackgroundMap.SetParent( newParent == null ? null : newParent._BackgroundMap );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_WaitForActMap.SetParent( newParent == null ? null : newParent._WaitForActMap );
		_LackOfManaMap.SetParent( newParent == null ? null : newParent._LackOfManaMap );
		_PressedMap.SetParent( newParent == null ? null : newParent._PressedMap );
		_HighlightMap.SetParent( newParent == null ? null : newParent._HighlightMap );
		_ScreenMap.SetParent( newParent == null ? null : newParent._ScreenMap );
		_WaitForActivationPin.SetParent( newParent == null ? null : newParent._WaitForActivationPin );
		_LackOfManaPin.SetParent( newParent == null ? null : newParent._LackOfManaPin );
		_PressedPin.SetParent( newParent == null ? null : newParent._PressedPin );
		_HighlightPin.SetParent( newParent == null ? null : newParent._HighlightPin );
		_DisablePin.SetParent( newParent == null ? null : newParent._DisablePin );
		_PassivePin.SetParent( newParent == null ? null : newParent._PassivePin );
		_UseDiffusePin.SetParent( newParent == null ? null : newParent._UseDiffusePin );
		_ScreenOpacity.SetParent( newParent == null ? null : newParent._ScreenOpacity );
		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_BackgroundMap.Reset();
		_DiffuseMap.Reset();
		_WaitForActMap.Reset();
		_LackOfManaMap.Reset();
		_PressedMap.Reset();
		_HighlightMap.Reset();
		_ScreenMap.Reset();
		_WaitForActivationPin.Reset();
		_LackOfManaPin.Reset();
		_PressedPin.Reset();
		_HighlightPin.Reset();
		_DisablePin.Reset();
		_PassivePin.Reset();
		_UseDiffusePin.Reset();
		_ScreenOpacity.Reset();
		_renderState.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_BackgroundMap.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _WaitForActMap.IsDerivedFromParent()
			&& _LackOfManaMap.IsDerivedFromParent()
			&& _PressedMap.IsDerivedFromParent()
			&& _HighlightMap.IsDerivedFromParent()
			&& _ScreenMap.IsDerivedFromParent()
			&& _WaitForActivationPin.IsDerivedFromParent()
			&& _LackOfManaPin.IsDerivedFromParent()
			&& _PressedPin.IsDerivedFromParent()
			&& _HighlightPin.IsDerivedFromParent()
			&& _DisablePin.IsDerivedFromParent()
			&& _PassivePin.IsDerivedFromParent()
			&& _UseDiffusePin.IsDerivedFromParent()
			&& _ScreenOpacity.IsDerivedFromParent()
			&& _renderState.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "BackgroundMap" )
			_BackgroundMap.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "WaitForActMap" )
			_WaitForActMap.Reset();
		else if ( fieldName == "LackOfManaMap" )
			_LackOfManaMap.Reset();
		else if ( fieldName == "PressedMap" )
			_PressedMap.Reset();
		else if ( fieldName == "HighlightMap" )
			_HighlightMap.Reset();
		else if ( fieldName == "ScreenMap" )
			_ScreenMap.Reset();
		else if ( fieldName == "WaitForActivationPin" )
			_WaitForActivationPin.Reset();
		else if ( fieldName == "LackOfManaPin" )
			_LackOfManaPin.Reset();
		else if ( fieldName == "PressedPin" )
			_PressedPin.Reset();
		else if ( fieldName == "HighlightPin" )
			_HighlightPin.Reset();
		else if ( fieldName == "DisablePin" )
			_DisablePin.Reset();
		else if ( fieldName == "PassivePin" )
			_PassivePin.Reset();
		else if ( fieldName == "UseDiffusePin" )
			_UseDiffusePin.Reset();
		else if ( fieldName == "ScreenOpacity" )
			_ScreenOpacity.Reset();
		else if ( fieldName == "renderState" )
			_renderState.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "BackgroundMap" )
			return _BackgroundMap.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "WaitForActMap" )
			return _WaitForActMap.IsDerivedFromParent();
		if ( fieldName == "LackOfManaMap" )
			return _LackOfManaMap.IsDerivedFromParent();
		if ( fieldName == "PressedMap" )
			return _PressedMap.IsDerivedFromParent();
		if ( fieldName == "HighlightMap" )
			return _HighlightMap.IsDerivedFromParent();
		if ( fieldName == "ScreenMap" )
			return _ScreenMap.IsDerivedFromParent();
		if ( fieldName == "WaitForActivationPin" )
			return _WaitForActivationPin.IsDerivedFromParent();
		if ( fieldName == "LackOfManaPin" )
			return _LackOfManaPin.IsDerivedFromParent();
		if ( fieldName == "PressedPin" )
			return _PressedPin.IsDerivedFromParent();
		if ( fieldName == "HighlightPin" )
			return _HighlightPin.IsDerivedFromParent();
		if ( fieldName == "DisablePin" )
			return _DisablePin.IsDerivedFromParent();
		if ( fieldName == "PassivePin" )
			return _PassivePin.IsDerivedFromParent();
		if ( fieldName == "UseDiffusePin" )
			return _UseDiffusePin.IsDerivedFromParent();
		if ( fieldName == "ScreenOpacity" )
			return _ScreenOpacity.IsDerivedFromParent();
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9D657440)]
[UseTypeName("MTRL")]
public class UIFlashMaterial : Material
{
	private UndoRedoDBPtr<UIFlashMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<UIFlashMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private Sampler _DiffuseMap;
	private Sampler _DiffuseMap2;
	private UndoRedo<BooleanPin> _UseDiffuse;
	private UndoRedo<BooleanPin> _UseDiffuse2;
	private UndoRedo<BooleanPin> _MorphShapes;
	private UndoRedo<BooleanPin> _ShaderForLines;
	private UndoRedo<BooleanPin> _UseColorFilter;
	private UndoRedo<BooleanPin> _Scale9Grid;
	private UndoRedo<BooleanPin> _Scale9GridBitmap;
	private UndoRedo<FlashBlendModePin> _FlashBlendMode;
	private HDRColor _CXFormMul;
	private HDRColor _CXFormAdd;

	[Sampler(0, "DiffuseMap")]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Sampler(1, "DiffuseMap2")]
	public Sampler DiffuseMap2 { get { return _DiffuseMap2; } set { _DiffuseMap2.Assign( value ); } }

	[Pin2("UseDiffuse")]
	public BooleanPin UseDiffuse { get { return _UseDiffuse.Get(); } set { _UseDiffuse.Set( value ); } }

	[Pin2("UseDiffuse2")]
	public BooleanPin UseDiffuse2 { get { return _UseDiffuse2.Get(); } set { _UseDiffuse2.Set( value ); } }

	[Pin2("MorphShapes")]
	public BooleanPin MorphShapes { get { return _MorphShapes.Get(); } set { _MorphShapes.Set( value ); } }

	[Pin2("ShaderForLines")]
	public BooleanPin ShaderForLines { get { return _ShaderForLines.Get(); } set { _ShaderForLines.Set( value ); } }

	[Pin2("UseColorFilter")]
	public BooleanPin UseColorFilter { get { return _UseColorFilter.Get(); } set { _UseColorFilter.Set( value ); } }

	[Pin2("Scale9Grid")]
	public BooleanPin Scale9Grid { get { return _Scale9Grid.Get(); } set { _Scale9Grid.Set( value ); } }

	[Pin2("Scale9GridBitmap")]
	public BooleanPin Scale9GridBitmap { get { return _Scale9GridBitmap.Get(); } set { _Scale9GridBitmap.Set( value ); } }

	[Pin2("FlashBlendModePin")]
	public FlashBlendModePin FlashBlendMode { get { return _FlashBlendMode.Get(); } set { _FlashBlendMode.Set( value ); } }

	public HDRColor CXFormMul { get { return _CXFormMul; } set { _CXFormMul.Assign( value ); } }

	public HDRColor CXFormAdd { get { return _CXFormAdd; } set { _CXFormAdd.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIFlashMaterial>(owner);
		Sampler __DiffuseMap = new Sampler(); // Construct default object for DiffuseMap
		__DiffuseMap.samplerState.mipFilter = MipFilterType.Point;
		__DiffuseMap.samplerState.addressU = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressV = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressW = TextureAddressType.Clamp;
		_DiffuseMap = new Sampler( owner, __DiffuseMap );
		Sampler __DiffuseMap2 = new Sampler(); // Construct default object for DiffuseMap2
		__DiffuseMap2.samplerState.mipFilter = MipFilterType.Point;
		__DiffuseMap2.samplerState.addressU = TextureAddressType.Clamp;
		__DiffuseMap2.samplerState.addressV = TextureAddressType.Clamp;
		__DiffuseMap2.samplerState.addressW = TextureAddressType.Clamp;
		_DiffuseMap2 = new Sampler( owner, __DiffuseMap2 );
		_UseDiffuse = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_UseDiffuse2 = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_MorphShapes = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_ShaderForLines = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_UseColorFilter = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_Scale9Grid = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_Scale9GridBitmap = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_FlashBlendMode = new UndoRedo<FlashBlendModePin>( owner, FlashBlendModePin._NORMAL );
		HDRColor __CXFormMul = new HDRColor(); // Construct default object for CXFormMul
		__CXFormMul.R = 1.0f;
		__CXFormMul.G = 1.0f;
		__CXFormMul.B = 1.0f;
		_CXFormMul = new HDRColor( owner, __CXFormMul );
		HDRColor __CXFormAdd = new HDRColor(); // Construct default object for CXFormAdd
		__CXFormAdd.A = 0.0f;
		_CXFormAdd = new HDRColor( owner, __CXFormAdd );
		___parent.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_DiffuseMap2.Changed += FireChangedEvent;
		_UseDiffuse.Changed += FireChangedEvent;
		_UseDiffuse2.Changed += FireChangedEvent;
		_MorphShapes.Changed += FireChangedEvent;
		_ShaderForLines.Changed += FireChangedEvent;
		_UseColorFilter.Changed += FireChangedEvent;
		_Scale9Grid.Changed += FireChangedEvent;
		_Scale9GridBitmap.Changed += FireChangedEvent;
		_FlashBlendMode.Changed += FireChangedEvent;
		_CXFormMul.Changed += FireChangedEvent;
		_CXFormAdd.Changed += FireChangedEvent;
	}

	public UIFlashMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( UIFlashMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIFlashMaterial" );
		DiffuseMap = source.DiffuseMap;
		DiffuseMap2 = source.DiffuseMap2;
		UseDiffuse = source.UseDiffuse;
		UseDiffuse2 = source.UseDiffuse2;
		MorphShapes = source.MorphShapes;
		ShaderForLines = source.ShaderForLines;
		UseColorFilter = source.UseColorFilter;
		Scale9Grid = source.Scale9Grid;
		Scale9GridBitmap = source.Scale9GridBitmap;
		FlashBlendMode = source.FlashBlendMode;
		CXFormMul = source.CXFormMul;
		CXFormAdd = source.CXFormAdd;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIFlashMaterial source = _source as UIFlashMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIFlashMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIFlashMaterial newParent = rawParent == null ? null : rawParent.Get<UIFlashMaterial>();
		if ( newParent == null && _newParent is UIFlashMaterial )
			newParent = _newParent as UIFlashMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_DiffuseMap2.SetParent( newParent == null ? null : newParent._DiffuseMap2 );
		_UseDiffuse.SetParent( newParent == null ? null : newParent._UseDiffuse );
		_UseDiffuse2.SetParent( newParent == null ? null : newParent._UseDiffuse2 );
		_MorphShapes.SetParent( newParent == null ? null : newParent._MorphShapes );
		_ShaderForLines.SetParent( newParent == null ? null : newParent._ShaderForLines );
		_UseColorFilter.SetParent( newParent == null ? null : newParent._UseColorFilter );
		_Scale9Grid.SetParent( newParent == null ? null : newParent._Scale9Grid );
		_Scale9GridBitmap.SetParent( newParent == null ? null : newParent._Scale9GridBitmap );
		_FlashBlendMode.SetParent( newParent == null ? null : newParent._FlashBlendMode );
		_CXFormMul.SetParent( newParent == null ? null : newParent._CXFormMul );
		_CXFormAdd.SetParent( newParent == null ? null : newParent._CXFormAdd );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_DiffuseMap.Reset();
		_DiffuseMap2.Reset();
		_UseDiffuse.Reset();
		_UseDiffuse2.Reset();
		_MorphShapes.Reset();
		_ShaderForLines.Reset();
		_UseColorFilter.Reset();
		_Scale9Grid.Reset();
		_Scale9GridBitmap.Reset();
		_FlashBlendMode.Reset();
		_CXFormMul.Reset();
		_CXFormAdd.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_DiffuseMap.IsDerivedFromParent()
			&& _DiffuseMap2.IsDerivedFromParent()
			&& _UseDiffuse.IsDerivedFromParent()
			&& _UseDiffuse2.IsDerivedFromParent()
			&& _MorphShapes.IsDerivedFromParent()
			&& _ShaderForLines.IsDerivedFromParent()
			&& _UseColorFilter.IsDerivedFromParent()
			&& _Scale9Grid.IsDerivedFromParent()
			&& _Scale9GridBitmap.IsDerivedFromParent()
			&& _FlashBlendMode.IsDerivedFromParent()
			&& _CXFormMul.IsDerivedFromParent()
			&& _CXFormAdd.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "DiffuseMap2" )
			_DiffuseMap2.Reset();
		else if ( fieldName == "UseDiffuse" )
			_UseDiffuse.Reset();
		else if ( fieldName == "UseDiffuse2" )
			_UseDiffuse2.Reset();
		else if ( fieldName == "MorphShapes" )
			_MorphShapes.Reset();
		else if ( fieldName == "ShaderForLines" )
			_ShaderForLines.Reset();
		else if ( fieldName == "UseColorFilter" )
			_UseColorFilter.Reset();
		else if ( fieldName == "Scale9Grid" )
			_Scale9Grid.Reset();
		else if ( fieldName == "Scale9GridBitmap" )
			_Scale9GridBitmap.Reset();
		else if ( fieldName == "FlashBlendMode" )
			_FlashBlendMode.Reset();
		else if ( fieldName == "CXFormMul" )
			_CXFormMul.Reset();
		else if ( fieldName == "CXFormAdd" )
			_CXFormAdd.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap2" )
			return _DiffuseMap2.IsDerivedFromParent();
		if ( fieldName == "UseDiffuse" )
			return _UseDiffuse.IsDerivedFromParent();
		if ( fieldName == "UseDiffuse2" )
			return _UseDiffuse2.IsDerivedFromParent();
		if ( fieldName == "MorphShapes" )
			return _MorphShapes.IsDerivedFromParent();
		if ( fieldName == "ShaderForLines" )
			return _ShaderForLines.IsDerivedFromParent();
		if ( fieldName == "UseColorFilter" )
			return _UseColorFilter.IsDerivedFromParent();
		if ( fieldName == "Scale9Grid" )
			return _Scale9Grid.IsDerivedFromParent();
		if ( fieldName == "Scale9GridBitmap" )
			return _Scale9GridBitmap.IsDerivedFromParent();
		if ( fieldName == "FlashBlendMode" )
			return _FlashBlendMode.IsDerivedFromParent();
		if ( fieldName == "CXFormMul" )
			return _CXFormMul.IsDerivedFromParent();
		if ( fieldName == "CXFormAdd" )
			return _CXFormAdd.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialFunc("UIFontMaterial.inl", "ModifyColor(const Render::HDRColor &mul, const Render::HDRColor &add)")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9D65A480)]
[UseTypeName("MTRL")]
public class UIFontMaterial : Material
{
	private UndoRedoDBPtr<UIFontMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<UIFontMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private Sampler _DiffuseMap;
	private UndoRedo<BooleanPin> _UseDiffuse;
	private UndoRedo<BooleanPin> _DrawContour;
	private HDRColor _PrimaryColor;
	private HDRColor _SecondaryColor;
	private RenderState _renderState;

	[Sampler(0, "DiffuseMap")]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Pin2("UseDiffuse")]
	public BooleanPin UseDiffuse { get { return _UseDiffuse.Get(); } set { _UseDiffuse.Set( value ); } }

	[Pin2("DrawContour")]
	public BooleanPin DrawContour { get { return _DrawContour.Get(); } set { _DrawContour.Set( value ); } }

	public HDRColor PrimaryColor { get { return _PrimaryColor; } set { _PrimaryColor.Assign( value ); } }

	public HDRColor SecondaryColor { get { return _SecondaryColor; } set { _SecondaryColor.Assign( value ); } }

	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIFontMaterial>(owner);
		Sampler __DiffuseMap = new Sampler(); // Construct default object for DiffuseMap
		__DiffuseMap.samplerState.mipFilter = MipFilterType.Point;
		__DiffuseMap.samplerState.addressU = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressV = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressW = TextureAddressType.Clamp;
		_DiffuseMap = new Sampler( owner, __DiffuseMap );
		_UseDiffuse = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		_DrawContour = new UndoRedo<BooleanPin>( owner, BooleanPin.None );
		HDRColor __PrimaryColor = new HDRColor(); // Construct default object for PrimaryColor
		__PrimaryColor.R = 1.0f;
		__PrimaryColor.G = 1.0f;
		__PrimaryColor.B = 1.0f;
		_PrimaryColor = new HDRColor( owner, __PrimaryColor );
		_SecondaryColor = new HDRColor( owner );
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.culling = OnOffState.Off;
		_renderState = new RenderState( owner, __renderState );
		___parent.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_UseDiffuse.Changed += FireChangedEvent;
		_DrawContour.Changed += FireChangedEvent;
		_PrimaryColor.Changed += FireChangedEvent;
		_SecondaryColor.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
	}

	public UIFontMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( UIFontMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIFontMaterial" );
		DiffuseMap = source.DiffuseMap;
		UseDiffuse = source.UseDiffuse;
		DrawContour = source.DrawContour;
		PrimaryColor = source.PrimaryColor;
		SecondaryColor = source.SecondaryColor;
		renderState = source.renderState;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIFontMaterial source = _source as UIFontMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIFontMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIFontMaterial newParent = rawParent == null ? null : rawParent.Get<UIFontMaterial>();
		if ( newParent == null && _newParent is UIFontMaterial )
			newParent = _newParent as UIFontMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_UseDiffuse.SetParent( newParent == null ? null : newParent._UseDiffuse );
		_DrawContour.SetParent( newParent == null ? null : newParent._DrawContour );
		_PrimaryColor.SetParent( newParent == null ? null : newParent._PrimaryColor );
		_SecondaryColor.SetParent( newParent == null ? null : newParent._SecondaryColor );
		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_DiffuseMap.Reset();
		_UseDiffuse.Reset();
		_DrawContour.Reset();
		_PrimaryColor.Reset();
		_SecondaryColor.Reset();
		_renderState.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_DiffuseMap.IsDerivedFromParent()
			&& _UseDiffuse.IsDerivedFromParent()
			&& _DrawContour.IsDerivedFromParent()
			&& _PrimaryColor.IsDerivedFromParent()
			&& _SecondaryColor.IsDerivedFromParent()
			&& _renderState.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "UseDiffuse" )
			_UseDiffuse.Reset();
		else if ( fieldName == "DrawContour" )
			_DrawContour.Reset();
		else if ( fieldName == "PrimaryColor" )
			_PrimaryColor.Reset();
		else if ( fieldName == "SecondaryColor" )
			_SecondaryColor.Reset();
		else if ( fieldName == "renderState" )
			_renderState.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "UseDiffuse" )
			return _UseDiffuse.IsDerivedFromParent();
		if ( fieldName == "DrawContour" )
			return _DrawContour.IsDerivedFromParent();
		if ( fieldName == "PrimaryColor" )
			return _PrimaryColor.IsDerivedFromParent();
		if ( fieldName == "SecondaryColor" )
			return _SecondaryColor.IsDerivedFromParent();
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialFunc("UIGlassMaterial.inl")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9D661300)]
[UseTypeName("MTRL")]
public class UIGlassMaterial : BaseUIMaterial
{
	private UndoRedoDBPtr<UIGlassMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<UIGlassMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private Sampler _BackgroundMap;
	private Sampler _DiffuseMap;
	private Sampler _OverlayMap;
	private Sampler _ScreenMap;
	private UndoRedo<float> _OverlayOpacity;
	private UndoRedo<float> _ScreenOpacity;
	private RenderState _renderState;

	[Sampler(0, "BackgroundMap")]
	public Sampler BackgroundMap { get { return _BackgroundMap; } set { _BackgroundMap.Assign( value ); } }

	[Sampler(1, "DiffuseMap")]
	public Sampler DiffuseMap { get { return _DiffuseMap; } set { _DiffuseMap.Assign( value ); } }

	[Sampler(2, "OverlayMap")]
	public Sampler OverlayMap { get { return _OverlayMap; } set { _OverlayMap.Assign( value ); } }

	[Sampler(3, "ScreenMap")]
	public Sampler ScreenMap { get { return _ScreenMap; } set { _ScreenMap.Assign( value ); } }

	public float OverlayOpacity { get { return _OverlayOpacity.Get(); } set { _OverlayOpacity.Set( value ); } }

	public float ScreenOpacity { get { return _ScreenOpacity.Get(); } set { _ScreenOpacity.Set( value ); } }

	public RenderState renderState { get { return _renderState; } set { _renderState.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIGlassMaterial>(owner);
		Sampler __BackgroundMap = new Sampler(); // Construct default object for BackgroundMap
		__BackgroundMap.samplerState.mipFilter = MipFilterType.Point;
		__BackgroundMap.samplerState.addressU = TextureAddressType.Clamp;
		__BackgroundMap.samplerState.addressV = TextureAddressType.Clamp;
		__BackgroundMap.samplerState.addressW = TextureAddressType.Clamp;
		_BackgroundMap = new Sampler( owner, __BackgroundMap );
		Sampler __DiffuseMap = new Sampler(); // Construct default object for DiffuseMap
		__DiffuseMap.samplerState.mipFilter = MipFilterType.Point;
		__DiffuseMap.samplerState.addressU = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressV = TextureAddressType.Clamp;
		__DiffuseMap.samplerState.addressW = TextureAddressType.Clamp;
		_DiffuseMap = new Sampler( owner, __DiffuseMap );
		Sampler __OverlayMap = new Sampler(); // Construct default object for OverlayMap
		__OverlayMap.samplerState.mipFilter = MipFilterType.Point;
		__OverlayMap.samplerState.addressU = TextureAddressType.Clamp;
		__OverlayMap.samplerState.addressV = TextureAddressType.Clamp;
		__OverlayMap.samplerState.addressW = TextureAddressType.Clamp;
		_OverlayMap = new Sampler( owner, __OverlayMap );
		Sampler __ScreenMap = new Sampler(); // Construct default object for ScreenMap
		__ScreenMap.samplerState.mipFilter = MipFilterType.Point;
		__ScreenMap.samplerState.addressU = TextureAddressType.Clamp;
		__ScreenMap.samplerState.addressV = TextureAddressType.Clamp;
		__ScreenMap.samplerState.addressW = TextureAddressType.Clamp;
		_ScreenMap = new Sampler( owner, __ScreenMap );
		_OverlayOpacity = new UndoRedo<float>( owner, 1.0f );
		_ScreenOpacity = new UndoRedo<float>( owner, 1.0f );
		RenderState __renderState = new RenderState(); // Construct default object for renderState
		__renderState.blendMode = BlendMode.LerpByAlpha;
		__renderState.culling = OnOffState.Off;
		_renderState = new RenderState( owner, __renderState );
		___parent.Changed += FireChangedEvent;
		_BackgroundMap.Changed += FireChangedEvent;
		_DiffuseMap.Changed += FireChangedEvent;
		_OverlayMap.Changed += FireChangedEvent;
		_ScreenMap.Changed += FireChangedEvent;
		_OverlayOpacity.Changed += FireChangedEvent;
		_ScreenOpacity.Changed += FireChangedEvent;
		_renderState.Changed += FireChangedEvent;
	}

	public UIGlassMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( UIGlassMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIGlassMaterial" );
		BackgroundMap = source.BackgroundMap;
		DiffuseMap = source.DiffuseMap;
		OverlayMap = source.OverlayMap;
		ScreenMap = source.ScreenMap;
		OverlayOpacity = source.OverlayOpacity;
		ScreenOpacity = source.ScreenOpacity;
		renderState = source.renderState;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIGlassMaterial source = _source as UIGlassMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIGlassMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIGlassMaterial newParent = rawParent == null ? null : rawParent.Get<UIGlassMaterial>();
		if ( newParent == null && _newParent is UIGlassMaterial )
			newParent = _newParent as UIGlassMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_BackgroundMap.SetParent( newParent == null ? null : newParent._BackgroundMap );
		_DiffuseMap.SetParent( newParent == null ? null : newParent._DiffuseMap );
		_OverlayMap.SetParent( newParent == null ? null : newParent._OverlayMap );
		_ScreenMap.SetParent( newParent == null ? null : newParent._ScreenMap );
		_OverlayOpacity.SetParent( newParent == null ? null : newParent._OverlayOpacity );
		_ScreenOpacity.SetParent( newParent == null ? null : newParent._ScreenOpacity );
		_renderState.SetParent( newParent == null ? null : newParent._renderState );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_BackgroundMap.Reset();
		_DiffuseMap.Reset();
		_OverlayMap.Reset();
		_ScreenMap.Reset();
		_OverlayOpacity.Reset();
		_ScreenOpacity.Reset();
		_renderState.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_BackgroundMap.IsDerivedFromParent()
			&& _DiffuseMap.IsDerivedFromParent()
			&& _OverlayMap.IsDerivedFromParent()
			&& _ScreenMap.IsDerivedFromParent()
			&& _OverlayOpacity.IsDerivedFromParent()
			&& _ScreenOpacity.IsDerivedFromParent()
			&& _renderState.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "BackgroundMap" )
			_BackgroundMap.Reset();
		else if ( fieldName == "DiffuseMap" )
			_DiffuseMap.Reset();
		else if ( fieldName == "OverlayMap" )
			_OverlayMap.Reset();
		else if ( fieldName == "ScreenMap" )
			_ScreenMap.Reset();
		else if ( fieldName == "OverlayOpacity" )
			_OverlayOpacity.Reset();
		else if ( fieldName == "ScreenOpacity" )
			_ScreenOpacity.Reset();
		else if ( fieldName == "renderState" )
			_renderState.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "BackgroundMap" )
			return _BackgroundMap.IsDerivedFromParent();
		if ( fieldName == "DiffuseMap" )
			return _DiffuseMap.IsDerivedFromParent();
		if ( fieldName == "OverlayMap" )
			return _OverlayMap.IsDerivedFromParent();
		if ( fieldName == "ScreenMap" )
			return _ScreenMap.IsDerivedFromParent();
		if ( fieldName == "OverlayOpacity" )
			return _OverlayOpacity.IsDerivedFromParent();
		if ( fieldName == "ScreenOpacity" )
			return _ScreenOpacity.IsDerivedFromParent();
		if ( fieldName == "renderState" )
			return _renderState.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[MaterialGroup("BaseMaterial")]
[TypeId(0x3B686340)]
[UseTypeName("MTRL")]
public class WaterDummyMaterial : Material
{
	private UndoRedoDBPtr<WaterDummyMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<WaterDummyMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WaterDummyMaterial>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public WaterDummyMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( WaterDummyMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WaterDummyMaterial" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WaterDummyMaterial source = _source as WaterDummyMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WaterDummyMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WaterDummyMaterial newParent = rawParent == null ? null : rawParent.Get<WaterDummyMaterial>();
		if ( newParent == null && _newParent is WaterDummyMaterial )
			newParent = _newParent as WaterDummyMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[MaterialGroup("BaseMaterial")]
[TypeId(0xA06B4B80)]
[UseTypeName("MTRL")]
public class WaterMapMaterial : Material
{
	private UndoRedoDBPtr<WaterMapMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<WaterMapMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WaterMapMaterial>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public WaterMapMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( WaterMapMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WaterMapMaterial" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WaterMapMaterial source = _source as WaterMapMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WaterMapMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WaterMapMaterial newParent = rawParent == null ? null : rawParent.Get<WaterMapMaterial>();
		if ( newParent == null && _newParent is WaterMapMaterial )
			newParent = _newParent as WaterMapMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(3)]
[MaterialFunc("WaterMaterial.inl")]
[MaterialGroup("BaseMaterial")]
[TypeId(0x9E5574C0)]
[UseTypeName("MTRL")]
public class WaterMaterial : Material
{
	private UndoRedoDBPtr<WaterMaterial> ___parent;
	[HideInOutliner]
	public new DBPtr<WaterMaterial> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WaterMaterial>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public WaterMaterial()
	{
		Initialize( this );
	}
	private void AssignSelf( WaterMaterial source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WaterMaterial" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WaterMaterial source = _source as WaterMaterial;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WaterMaterial" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WaterMaterial newParent = rawParent == null ? null : rawParent.Get<WaterMaterial>();
		if ( newParent == null && _newParent is WaterMaterial )
			newParent = _newParent as WaterMaterial;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
