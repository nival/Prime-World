#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;
// forward declarations for factories
namespace Render
{
	class Texture;
}; //namespace Render

namespace NDb
{
struct CubeMap;
struct TextureBase;

enum Attenuation
{
	ATTENUATION_LINEAR = 0,
	ATTENUATION_NORMAL = 1,
	ATTENUATION_SLOW = 2,
	ATTENUATION_FAST = 3,
	ATTENUATION_NONE = 4,
};

const char *EnumToString( const Attenuation value );
const Attenuation StringToEnum_Attenuation( const char* value );

template <>
struct KnownEnum< Attenuation >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const Attenuation value ) { return EnumToString( value ); }
	static const Attenuation ToEnum( const char* value ) { return StringToEnum_Attenuation( value ); }
	static const Attenuation ToEnum( const string& value ) { return StringToEnum_Attenuation( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum BlendFactor
{
	BLENDFACTOR_ONE = 0,
	BLENDFACTOR_SRCALPHA = 1,
	BLENDFACTOR_INVSRCALPHA = 2,
};

const char *EnumToString( const BlendFactor value );
const BlendFactor StringToEnum_BlendFactor( const char* value );

template <>
struct KnownEnum< BlendFactor >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const BlendFactor value ) { return EnumToString( value ); }
	static const BlendFactor ToEnum( const char* value ) { return StringToEnum_BlendFactor( value ); }
	static const BlendFactor ToEnum( const string& value ) { return StringToEnum_BlendFactor( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum BlendMode
{
	BLENDMODE_OFF = 0,
	BLENDMODE_LERPBYALPHA = 1,
	BLENDMODE_PREMULTIPLIEDLERP = 2,
	BLENDMODE_ADDCOLOR = 3,
	BLENDMODE_ADDCOLORMULALPHA = 4,
	BLENDMODE_MULCOLOR = 5,
	BLENDMODE_MULINVCOLOR = 6,
};

const char *EnumToString( const BlendMode value );
const BlendMode StringToEnum_BlendMode( const char* value );

template <>
struct KnownEnum< BlendMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const BlendMode value ) { return EnumToString( value ); }
	static const BlendMode ToEnum( const char* value ) { return StringToEnum_BlendMode( value ); }
	static const BlendMode ToEnum( const string& value ) { return StringToEnum_BlendMode( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum BooleanPin
{
	BOOLEANPIN_NONE = 0,
	BOOLEANPIN_PRESENT = 1,
};

const char *EnumToString( const BooleanPin value );
const BooleanPin StringToEnum_BooleanPin( const char* value );

template <>
struct KnownEnum< BooleanPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const BooleanPin value ) { return EnumToString( value ); }
	static const BooleanPin ToEnum( const char* value ) { return StringToEnum_BooleanPin( value ); }
	static const BooleanPin ToEnum( const string& value ) { return StringToEnum_BooleanPin( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum BoolPin
{
	BOOLPIN_FALSE = 0,
	BOOLPIN_TRUE = 1,
};

const char *EnumToString( const BoolPin value );
const BoolPin StringToEnum_BoolPin( const char* value );

template <>
struct KnownEnum< BoolPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const BoolPin value ) { return EnumToString( value ); }
	static const BoolPin ToEnum( const char* value ) { return StringToEnum_BoolPin( value ); }
	static const BoolPin ToEnum( const string& value ) { return StringToEnum_BoolPin( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum CachingPin
{
	CACHINGPIN_ORDINARY = 0,
	CACHINGPIN_FILL = 1,
	CACHINGPIN_USE = 2,
	CACHINGPIN_USE2 = 3,
	CACHINGPIN_USE3 = 4,
};

const char *EnumToString( const CachingPin value );
const CachingPin StringToEnum_CachingPin( const char* value );

template <>
struct KnownEnum< CachingPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const CachingPin value ) { return EnumToString( value ); }
	static const CachingPin ToEnum( const char* value ) { return StringToEnum_CachingPin( value ); }
	static const CachingPin ToEnum( const string& value ) { return StringToEnum_CachingPin( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum ColorCorrectPin
{
	COLORCORRECTPIN_OFF = 0,
	COLORCORRECTPIN_ON = 1,
	COLORCORRECTPIN_NO_GAMMA = 2,
	COLORCORRECTPIN_DESATURATE_ONLY = 3,
};

const char *EnumToString( const ColorCorrectPin value );
const ColorCorrectPin StringToEnum_ColorCorrectPin( const char* value );

template <>
struct KnownEnum< ColorCorrectPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const ColorCorrectPin value ) { return EnumToString( value ); }
	static const ColorCorrectPin ToEnum( const char* value ) { return StringToEnum_ColorCorrectPin( value ); }
	static const ColorCorrectPin ToEnum( const string& value ) { return StringToEnum_ColorCorrectPin( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum CompareFunction
{
	COMPAREFUNCTION_NEVER = 0,
	COMPAREFUNCTION_LESS = 1,
	COMPAREFUNCTION_EQUAL = 2,
	COMPAREFUNCTION_LESSOREQUAL = 3,
	COMPAREFUNCTION_GREATER = 4,
	COMPAREFUNCTION_NOTEQUAL = 5,
	COMPAREFUNCTION_GREATEROREQUAL = 6,
	COMPAREFUNCTION_ALWAYS = 7,
};

const char *EnumToString( const CompareFunction value );
const CompareFunction StringToEnum_CompareFunction( const char* value );

template <>
struct KnownEnum< CompareFunction >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const CompareFunction value ) { return EnumToString( value ); }
	static const CompareFunction ToEnum( const char* value ) { return StringToEnum_CompareFunction( value ); }
	static const CompareFunction ToEnum( const string& value ) { return StringToEnum_CompareFunction( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

enum CullingMode
{
	CULLINGMODE_NONE = 0,
	CULLINGMODE_CW = 1,
};

const char *EnumToString( const CullingMode value );
const CullingMode StringToEnum_CullingMode( const char* value );

template <>
struct KnownEnum< CullingMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const CullingMode value ) { return EnumToString( value ); }
	static const CullingMode ToEnum( const char* value ) { return StringToEnum_CullingMode( value ); }
	static const CullingMode ToEnum( const string& value ) { return StringToEnum_CullingMode( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum DebugPin
{
	DEBUGPIN_SIMPLESHADING = 0,
	DEBUGPIN_SHOWNORMALS = 1,
	DEBUGPIN_SHOWMIPMAPS = 2,
};

const char *EnumToString( const DebugPin value );
const DebugPin StringToEnum_DebugPin( const char* value );

template <>
struct KnownEnum< DebugPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const DebugPin value ) { return EnumToString( value ); }
	static const DebugPin ToEnum( const char* value ) { return StringToEnum_DebugPin( value ); }
	static const DebugPin ToEnum( const string& value ) { return StringToEnum_DebugPin( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum DecalModePin
{
	DECALMODEPIN_STANDARD = 0,
	DECALMODEPIN_DUALDEPTH = 1,
	DECALMODEPIN_ZDECODE = 2,
};

const char *EnumToString( const DecalModePin value );
const DecalModePin StringToEnum_DecalModePin( const char* value );

template <>
struct KnownEnum< DecalModePin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const DecalModePin value ) { return EnumToString( value ); }
	static const DecalModePin ToEnum( const char* value ) { return StringToEnum_DecalModePin( value ); }
	static const DecalModePin ToEnum( const string& value ) { return StringToEnum_DecalModePin( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum DiffuseAlphaMixPin
{
	DIFFUSEALPHAMIXPIN_ALPHAMIXTEX1 = 0,
	DIFFUSEALPHAMIXPIN_ALPHAMIXADDSMOOTH = 1,
	DIFFUSEALPHAMIXPIN_ALPHAMIXMUL = 2,
};

const char *EnumToString( const DiffuseAlphaMixPin value );
const DiffuseAlphaMixPin StringToEnum_DiffuseAlphaMixPin( const char* value );

template <>
struct KnownEnum< DiffuseAlphaMixPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const DiffuseAlphaMixPin value ) { return EnumToString( value ); }
	static const DiffuseAlphaMixPin ToEnum( const char* value ) { return StringToEnum_DiffuseAlphaMixPin( value ); }
	static const DiffuseAlphaMixPin ToEnum( const string& value ) { return StringToEnum_DiffuseAlphaMixPin( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum DiffuseColorMixPin
{
	DIFFUSECOLORMIXPIN_COLORMIXADD = 0,
	DIFFUSECOLORMIXPIN_COLORMIXADDWITHALPHA = 1,
	DIFFUSECOLORMIXPIN_COLORMIXLERP = 2,
	DIFFUSECOLORMIXPIN_COLORMIXMUL = 3,
};

const char *EnumToString( const DiffuseColorMixPin value );
const DiffuseColorMixPin StringToEnum_DiffuseColorMixPin( const char* value );

template <>
struct KnownEnum< DiffuseColorMixPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const DiffuseColorMixPin value ) { return EnumToString( value ); }
	static const DiffuseColorMixPin ToEnum( const char* value ) { return StringToEnum_DiffuseColorMixPin( value ); }
	static const DiffuseColorMixPin ToEnum( const string& value ) { return StringToEnum_DiffuseColorMixPin( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum DiffuseMapCountPin
{
	DIFFUSEMAPCOUNTPIN_NODIFFUSEMAP = 0,
	DIFFUSEMAPCOUNTPIN_BASEDIFFUSEMAP = 1,
	DIFFUSEMAPCOUNTPIN_BOTHDIFFUSEMAPS = 2,
};

const char *EnumToString( const DiffuseMapCountPin value );
const DiffuseMapCountPin StringToEnum_DiffuseMapCountPin( const char* value );

template <>
struct KnownEnum< DiffuseMapCountPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const DiffuseMapCountPin value ) { return EnumToString( value ); }
	static const DiffuseMapCountPin ToEnum( const char* value ) { return StringToEnum_DiffuseMapCountPin( value ); }
	static const DiffuseMapCountPin ToEnum( const string& value ) { return StringToEnum_DiffuseMapCountPin( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum DistortionPin
{
	DISTORTIONPIN_DISTORTNONE = 0,
	DISTORTIONPIN_DISTORTMAP = 1,
	DISTORTIONPIN_DISTORTNOISE = 2,
};

const char *EnumToString( const DistortionPin value );
const DistortionPin StringToEnum_DistortionPin( const char* value );

template <>
struct KnownEnum< DistortionPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const DistortionPin value ) { return EnumToString( value ); }
	static const DistortionPin ToEnum( const char* value ) { return StringToEnum_DistortionPin( value ); }
	static const DistortionPin ToEnum( const string& value ) { return StringToEnum_DistortionPin( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EEmissivePin
{
	EMISSIVEPIN_EMISSIVEOFF = 0,
	EMISSIVEPIN_EMISSIVEFROMALPHA = 1,
	EMISSIVEPIN_EMISSIVEFROMSPECULAR = 2,
};

const char *EnumToString( const EEmissivePin value );
const EEmissivePin StringToEnum_EEmissivePin( const char* value );

template <>
struct KnownEnum< EEmissivePin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EEmissivePin value ) { return EnumToString( value ); }
	static const EEmissivePin ToEnum( const char* value ) { return StringToEnum_EEmissivePin( value ); }
	static const EEmissivePin ToEnum( const string& value ) { return StringToEnum_EEmissivePin( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ELightEnvironment
{
	LIGHTENVIRONMENT_DAY = 0,
	LIGHTENVIRONMENT_NIGHT = 1,
};

const char *EnumToString( const ELightEnvironment value );
const ELightEnvironment StringToEnum_ELightEnvironment( const char* value );

template <>
struct KnownEnum< ELightEnvironment >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ELightEnvironment value ) { return EnumToString( value ); }
	static const ELightEnvironment ToEnum( const char* value ) { return StringToEnum_ELightEnvironment( value ); }
	static const ELightEnvironment ToEnum( const string& value ) { return StringToEnum_ELightEnvironment( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EPixelFormat
{
	PIXELFORMAT_RGBA = 0,
	PIXELFORMAT_DXT1 = 1,
	PIXELFORMAT_DXT5 = 2,
	PIXELFORMAT_L8 = 3,
};

const char *EnumToString( const EPixelFormat value );
const EPixelFormat StringToEnum_EPixelFormat( const char* value );

template <>
struct KnownEnum< EPixelFormat >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EPixelFormat value ) { return EnumToString( value ); }
	static const EPixelFormat ToEnum( const char* value ) { return StringToEnum_EPixelFormat( value ); }
	static const EPixelFormat ToEnum( const string& value ) { return StringToEnum_EPixelFormat( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EUIImageDrawMode
{
	UIIMAGEDRAWMODE_NORMAL = 0,
	UIIMAGEDRAWMODE_CENTER = 1,
	UIIMAGEDRAWMODE_STRETCH = 2,
	UIIMAGEDRAWMODE_TILE = 3,
	UIIMAGEDRAWMODE_STRETCHEDTILE = 4,
};

const char *EnumToString( const EUIImageDrawMode value );
const EUIImageDrawMode StringToEnum_EUIImageDrawMode( const char* value );

template <>
struct KnownEnum< EUIImageDrawMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const EUIImageDrawMode value ) { return EnumToString( value ); }
	static const EUIImageDrawMode ToEnum( const char* value ) { return StringToEnum_EUIImageDrawMode( value ); }
	static const EUIImageDrawMode ToEnum( const string& value ) { return StringToEnum_EUIImageDrawMode( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum FillMode
{
	FILLMODE_POINT = 0,
	FILLMODE_WIREFRAME = 1,
	FILLMODE_SOLID = 2,
};

const char *EnumToString( const FillMode value );
const FillMode StringToEnum_FillMode( const char* value );

template <>
struct KnownEnum< FillMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const FillMode value ) { return EnumToString( value ); }
	static const FillMode ToEnum( const char* value ) { return StringToEnum_FillMode( value ); }
	static const FillMode ToEnum( const string& value ) { return StringToEnum_FillMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum FlashBlendModePin
{
	FLASHBLENDMODEPIN__NORMAL = 0,
	FLASHBLENDMODEPIN_LAYER = 1,
	FLASHBLENDMODEPIN_MULTIPLY = 2,
	FLASHBLENDMODEPIN_SCREEN = 3,
	FLASHBLENDMODEPIN_LIGHTEN = 4,
	FLASHBLENDMODEPIN_DARKEN = 5,
	FLASHBLENDMODEPIN__DIFFERENCE = 6,
	FLASHBLENDMODEPIN_ADD = 7,
	FLASHBLENDMODEPIN_SUBTRACT = 8,
	FLASHBLENDMODEPIN_INVERT = 9,
	FLASHBLENDMODEPIN_ALPHA = 10,
	FLASHBLENDMODEPIN_ERASE = 11,
	FLASHBLENDMODEPIN_OVERLAY = 12,
	FLASHBLENDMODEPIN_HARDLIGHT = 13,
	FLASHBLENDMODEPIN_SHADER = 14,
	FLASHBLENDMODEPIN_COPY_BACKGRUOND = 15,
};

const char *EnumToString( const FlashBlendModePin value );
const FlashBlendModePin StringToEnum_FlashBlendModePin( const char* value );

template <>
struct KnownEnum< FlashBlendModePin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 16 };
	static const char *ToString( const FlashBlendModePin value ) { return EnumToString( value ); }
	static const FlashBlendModePin ToEnum( const char* value ) { return StringToEnum_FlashBlendModePin( value ); }
	static const FlashBlendModePin ToEnum( const string& value ) { return StringToEnum_FlashBlendModePin( value.c_str() ); }
	static const int SizeOf() { return 16; }
};

enum LightingPin
{
	LIGHTINGPIN_LIGHTINGSH = 0,
	LIGHTINGPIN_LIGHTINGINSTANCEDSH = 1,
	LIGHTINGPIN_LIGHTINGBAKED = 2,
	LIGHTINGPIN_LIGHTINGDYNAMIC = 3,
	LIGHTINGPIN_LIGHTINGDYNAMIC1POINT = 4,
	LIGHTINGPIN_LIGHTINGDYNAMIC2POINT = 5,
	LIGHTINGPIN_LIGHTINGDYNAMIC3POINT = 6,
	LIGHTINGPIN_LIGHTINGDYNAMIC4POINT = 7,
};

const char *EnumToString( const LightingPin value );
const LightingPin StringToEnum_LightingPin( const char* value );

template <>
struct KnownEnum< LightingPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const LightingPin value ) { return EnumToString( value ); }
	static const LightingPin ToEnum( const char* value ) { return StringToEnum_LightingPin( value ); }
	static const LightingPin ToEnum( const string& value ) { return StringToEnum_LightingPin( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

enum LightModePin
{
	LIGHTMODEPIN_DIFFUSE = 0,
	LIGHTMODEPIN_DIFFUSEOPACITY = 1,
	LIGHTMODEPIN_DIFFUSESPECULAR = 2,
	LIGHTMODEPIN_DIFFUSESPECULAROPACITY = 3,
	LIGHTMODEPIN_DIFFUSEEMISSIVE = 4,
	LIGHTMODEPIN_DIFFUSESPECULAREMISSIVE = 5,
	LIGHTMODEPIN_DIFFUSESPECULARTOEMISSIVE = 6,
};

const char *EnumToString( const LightModePin value );
const LightModePin StringToEnum_LightModePin( const char* value );

template <>
struct KnownEnum< LightModePin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const LightModePin value ) { return EnumToString( value ); }
	static const LightModePin ToEnum( const char* value ) { return StringToEnum_LightModePin( value ); }
	static const LightModePin ToEnum( const string& value ) { return StringToEnum_LightModePin( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum MADPin
{
	MADPIN_NOMAD = 0,
	MADPIN_MADENABLED = 1,
};

const char *EnumToString( const MADPin value );
const MADPin StringToEnum_MADPin( const char* value );

template <>
struct KnownEnum< MADPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const MADPin value ) { return EnumToString( value ); }
	static const MADPin ToEnum( const char* value ) { return StringToEnum_MADPin( value ); }
	static const MADPin ToEnum( const string& value ) { return StringToEnum_MADPin( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum MagFilterType
{
	MAGFILTERTYPE_POINT = 0,
	MAGFILTERTYPE_LINEAR = 1,
};

const char *EnumToString( const MagFilterType value );
const MagFilterType StringToEnum_MagFilterType( const char* value );

template <>
struct KnownEnum< MagFilterType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const MagFilterType value ) { return EnumToString( value ); }
	static const MagFilterType ToEnum( const char* value ) { return StringToEnum_MagFilterType( value ); }
	static const MagFilterType ToEnum( const string& value ) { return StringToEnum_MagFilterType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum MaskingTypePin
{
	MASKINGTYPEPIN_NOMASKING = 0,
	MASKINGTYPEPIN_MASKING = 1,
	MASKINGTYPEPIN_INVERTMASKING = 2,
};

const char *EnumToString( const MaskingTypePin value );
const MaskingTypePin StringToEnum_MaskingTypePin( const char* value );

template <>
struct KnownEnum< MaskingTypePin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const MaskingTypePin value ) { return EnumToString( value ); }
	static const MaskingTypePin ToEnum( const char* value ) { return StringToEnum_MaskingTypePin( value ); }
	static const MaskingTypePin ToEnum( const string& value ) { return StringToEnum_MaskingTypePin( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum MaterialFlags
{
	MATERIALFLAGS_NONE = 0,
	MATERIALFLAGS_SHADOWCASTER = 1,
	MATERIALFLAGS_SHADOWRECEIVER = 2,
	MATERIALFLAGS_REFLECTINWATER = 4,
};

const char *EnumToString( const MaterialFlags value );
const MaterialFlags StringToEnum_MaterialFlags( const char* value );

template <>
struct KnownEnum< MaterialFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const MaterialFlags value ) { return EnumToString( value ); }
	static const MaterialFlags ToEnum( const char* value ) { return StringToEnum_MaterialFlags( value ); }
	static const MaterialFlags ToEnum( const string& value ) { return StringToEnum_MaterialFlags( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum MaterialOldFlags
{
	MATERIALOLDFLAGS_NONE = 0,
	MATERIALOLDFLAGS_REQUIREALPHABLENDING = 1,
	MATERIALOLDFLAGS_CASTSSHADOWS = 2,
};

const char *EnumToString( const MaterialOldFlags value );
const MaterialOldFlags StringToEnum_MaterialOldFlags( const char* value );

template <>
struct KnownEnum< MaterialOldFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const MaterialOldFlags value ) { return EnumToString( value ); }
	static const MaterialOldFlags ToEnum( const char* value ) { return StringToEnum_MaterialOldFlags( value ); }
	static const MaterialOldFlags ToEnum( const string& value ) { return StringToEnum_MaterialOldFlags( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum MaterialPriority
{
	MATERIALPRIORITY_NONE = -1,
	MATERIALPRIORITY_MESHESOPAQUE = 0,
	MATERIALPRIORITY_MESHESOPAQUELATE = 1,
	MATERIALPRIORITY_MESHESSILHOUETTE = 2,
	MATERIALPRIORITY_TERRAINLAYER0 = 3,
	MATERIALPRIORITY_TERRAINLAYER1 = 4,
	MATERIALPRIORITY_ROADS = 5,
	MATERIALPRIORITY_TERRAINOBJECTS = 6,
	MATERIALPRIORITY_TERRAINDOMINATIONDECALS = 7,
	MATERIALPRIORITY_TERRAINDECALS = 8,
	MATERIALPRIORITY_WATERDECALS = 9,
	MATERIALPRIORITY_TRANSPARENTSPECIAL = 10,
	MATERIALPRIORITY_TRANSPARENT = 11,
	MATERIALPRIORITY_DISTORTION = 12,
	MATERIALPRIORITY_HEIGHTFOG = 13,
	MATERIALPRIORITY_SKY = 14,
	MATERIALPRIORITY_COUNT = 15,
};

const char *EnumToString( const MaterialPriority value );
const MaterialPriority StringToEnum_MaterialPriority( const char* value );

template <>
struct KnownEnum< MaterialPriority >
{
	enum { isKnown = 1 };
	enum { sizeOf = 17 };
	static const char *ToString( const MaterialPriority value ) { return EnumToString( value ); }
	static const MaterialPriority ToEnum( const char* value ) { return StringToEnum_MaterialPriority( value ); }
	static const MaterialPriority ToEnum( const string& value ) { return StringToEnum_MaterialPriority( value.c_str() ); }
	static const int SizeOf() { return 17; }
};

enum MinFilterType
{
	MINFILTERTYPE_POINT = 0,
	MINFILTERTYPE_LINEAR = 1,
	MINFILTERTYPE_ANISOTROPIC1X = 2,
	MINFILTERTYPE_ANISOTROPIC2X = 3,
	MINFILTERTYPE_ANISOTROPIC3X = 4,
	MINFILTERTYPE_ANISOTROPIC4X = 5,
	MINFILTERTYPE_ANISOTROPIC5X = 6,
	MINFILTERTYPE_ANISOTROPIC6X = 7,
};

const char *EnumToString( const MinFilterType value );
const MinFilterType StringToEnum_MinFilterType( const char* value );

template <>
struct KnownEnum< MinFilterType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const MinFilterType value ) { return EnumToString( value ); }
	static const MinFilterType ToEnum( const char* value ) { return StringToEnum_MinFilterType( value ); }
	static const MinFilterType ToEnum( const string& value ) { return StringToEnum_MinFilterType( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

enum MipFilterType
{
	MIPFILTERTYPE_NONE = 0,
	MIPFILTERTYPE_POINT = 1,
	MIPFILTERTYPE_LINEAR = 2,
};

const char *EnumToString( const MipFilterType value );
const MipFilterType StringToEnum_MipFilterType( const char* value );

template <>
struct KnownEnum< MipFilterType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const MipFilterType value ) { return EnumToString( value ); }
	static const MipFilterType ToEnum( const char* value ) { return StringToEnum_MipFilterType( value ); }
	static const MipFilterType ToEnum( const string& value ) { return StringToEnum_MipFilterType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum OnOffState
{
	ONOFFSTATE_OFF = 0,
	ONOFFSTATE_ON = 1,
};

const char *EnumToString( const OnOffState value );
const OnOffState StringToEnum_OnOffState( const char* value );

template <>
struct KnownEnum< OnOffState >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const OnOffState value ) { return EnumToString( value ); }
	static const OnOffState ToEnum( const char* value ) { return StringToEnum_OnOffState( value ); }
	static const OnOffState ToEnum( const string& value ) { return StringToEnum_OnOffState( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum OpacityAndEmissiveModePin
{
	OPACITYANDEMISSIVEMODEPIN_SIMPLE = 0,
	OPACITYANDEMISSIVEMODEPIN_ADDITIVEOPACITY = 1,
	OPACITYANDEMISSIVEMODEPIN_BLENDOPACITY = 2,
	OPACITYANDEMISSIVEMODEPIN_EMISSIVE = 3,
};

const char *EnumToString( const OpacityAndEmissiveModePin value );
const OpacityAndEmissiveModePin StringToEnum_OpacityAndEmissiveModePin( const char* value );

template <>
struct KnownEnum< OpacityAndEmissiveModePin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const OpacityAndEmissiveModePin value ) { return EnumToString( value ); }
	static const OpacityAndEmissiveModePin ToEnum( const char* value ) { return StringToEnum_OpacityAndEmissiveModePin( value ); }
	static const OpacityAndEmissiveModePin ToEnum( const string& value ) { return StringToEnum_OpacityAndEmissiveModePin( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum OpacityPin
{
	OPACITYPIN_OPAQUE = 0,
	OPACITYPIN_ALPHAOPACITY = 1,
	OPACITYPIN_COLOROPACITY = 2,
};

const char *EnumToString( const OpacityPin value );
const OpacityPin StringToEnum_OpacityPin( const char* value );

template <>
struct KnownEnum< OpacityPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const OpacityPin value ) { return EnumToString( value ); }
	static const OpacityPin ToEnum( const char* value ) { return StringToEnum_OpacityPin( value ); }
	static const OpacityPin ToEnum( const string& value ) { return StringToEnum_OpacityPin( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum OrientTypePin
{
	ORIENTTYPEPIN_NONETYPE = 0,
	ORIENTTYPEPIN_AXISTYPE = 1,
	ORIENTTYPEPIN_SPEEDTYPE = 2,
	ORIENTTYPEPIN_PLANETYPE = 3,
};

const char *EnumToString( const OrientTypePin value );
const OrientTypePin StringToEnum_OrientTypePin( const char* value );

template <>
struct KnownEnum< OrientTypePin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const OrientTypePin value ) { return EnumToString( value ); }
	static const OrientTypePin ToEnum( const char* value ) { return StringToEnum_OrientTypePin( value ); }
	static const OrientTypePin ToEnum( const string& value ) { return StringToEnum_OrientTypePin( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum PackedMasksNumberPin
{
	PACKEDMASKSNUMBERPIN_PACKEDMASKS1 = 0,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS2 = 1,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS3 = 2,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS4 = 3,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS5 = 4,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS6 = 5,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS7 = 6,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS8 = 7,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS9 = 8,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS10 = 9,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS11 = 10,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS12 = 11,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS13 = 12,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS14 = 13,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS15 = 14,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS16 = 15,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS17 = 16,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS18 = 17,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS19 = 18,
	PACKEDMASKSNUMBERPIN_PACKEDMASKS20 = 19,
};

const char *EnumToString( const PackedMasksNumberPin value );
const PackedMasksNumberPin StringToEnum_PackedMasksNumberPin( const char* value );

template <>
struct KnownEnum< PackedMasksNumberPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 20 };
	static const char *ToString( const PackedMasksNumberPin value ) { return EnumToString( value ); }
	static const PackedMasksNumberPin ToEnum( const char* value ) { return StringToEnum_PackedMasksNumberPin( value ); }
	static const PackedMasksNumberPin ToEnum( const string& value ) { return StringToEnum_PackedMasksNumberPin( value.c_str() ); }
	static const int SizeOf() { return 20; }
};

enum PaintMaterialModePin
{
	PAINTMATERIALMODEPIN_EMPTY = 0,
	PAINTMATERIALMODEPIN_INWORK = 1,
	PAINTMATERIALMODEPIN_FINAL = 2,
};

const char *EnumToString( const PaintMaterialModePin value );
const PaintMaterialModePin StringToEnum_PaintMaterialModePin( const char* value );

template <>
struct KnownEnum< PaintMaterialModePin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const PaintMaterialModePin value ) { return EnumToString( value ); }
	static const PaintMaterialModePin ToEnum( const char* value ) { return StringToEnum_PaintMaterialModePin( value ); }
	static const PaintMaterialModePin ToEnum( const string& value ) { return StringToEnum_PaintMaterialModePin( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum PointLightFlags
{
	POINTLIGHTFLAGS_NONE = 0,
	POINTLIGHTFLAGS_DAY = 1,
	POINTLIGHTFLAGS_NIGHT = 2,
};

const char *EnumToString( const PointLightFlags value );
const PointLightFlags StringToEnum_PointLightFlags( const char* value );

template <>
struct KnownEnum< PointLightFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const PointLightFlags value ) { return EnumToString( value ); }
	static const PointLightFlags ToEnum( const char* value ) { return StringToEnum_PointLightFlags( value ); }
	static const PointLightFlags ToEnum( const string& value ) { return StringToEnum_PointLightFlags( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ReflectivityPin
{
	REFLECTIVITYPIN_REFLECTIVITYOFF = 0,
	REFLECTIVITYPIN_REFLECTIVITYSIMPLE = 1,
	REFLECTIVITYPIN_REFLECTIVITYFROMNORMALMAP = 2,
	REFLECTIVITYPIN_REFLECTIVITYFROMSPECULARMAP = 3,
};

const char *EnumToString( const ReflectivityPin value );
const ReflectivityPin StringToEnum_ReflectivityPin( const char* value );

template <>
struct KnownEnum< ReflectivityPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const ReflectivityPin value ) { return EnumToString( value ); }
	static const ReflectivityPin ToEnum( const char* value ) { return StringToEnum_ReflectivityPin( value ); }
	static const ReflectivityPin ToEnum( const string& value ) { return StringToEnum_ReflectivityPin( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum RenderModePin
{
	RENDERMODEPIN_RENDERNORMAL = 0,
	RENDERMODEPIN_RENDERTOSHADOW = 1,
	RENDERMODEPIN_RENDERSHAPEONLY = 2,
};

const char *EnumToString( const RenderModePin value );
const RenderModePin StringToEnum_RenderModePin( const char* value );

template <>
struct KnownEnum< RenderModePin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const RenderModePin value ) { return EnumToString( value ); }
	static const RenderModePin ToEnum( const char* value ) { return StringToEnum_RenderModePin( value ); }
	static const RenderModePin ToEnum( const string& value ) { return StringToEnum_RenderModePin( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum ShaderQualityPin
{
	SHADERQUALITYPIN_BEST = 0,
	SHADERQUALITYPIN_FAST = 1,
};

const char *EnumToString( const ShaderQualityPin value );
const ShaderQualityPin StringToEnum_ShaderQualityPin( const char* value );

template <>
struct KnownEnum< ShaderQualityPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ShaderQualityPin value ) { return EnumToString( value ); }
	static const ShaderQualityPin ToEnum( const char* value ) { return StringToEnum_ShaderQualityPin( value ); }
	static const ShaderQualityPin ToEnum( const string& value ) { return StringToEnum_ShaderQualityPin( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum ShadowBlendMode
{
	SHADOWBLENDMODE_LERPBYALPHA = 0,
	SHADOWBLENDMODE_MULCOLOR = 1,
};

const char *EnumToString( const ShadowBlendMode value );
const ShadowBlendMode StringToEnum_ShadowBlendMode( const char* value );

template <>
struct KnownEnum< ShadowBlendMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const ShadowBlendMode value ) { return EnumToString( value ); }
	static const ShadowBlendMode ToEnum( const char* value ) { return StringToEnum_ShadowBlendMode( value ); }
	static const ShadowBlendMode ToEnum( const string& value ) { return StringToEnum_ShadowBlendMode( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum ShadowMode
{
	SHADOWMODE_PCF = 0,
	SHADOWMODE_SAESM = 1,
	SHADOWMODE_ANISOESM = 2,
};

const char *EnumToString( const ShadowMode value );
const ShadowMode StringToEnum_ShadowMode( const char* value );

template <>
struct KnownEnum< ShadowMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const ShadowMode value ) { return EnumToString( value ); }
	static const ShadowMode ToEnum( const char* value ) { return StringToEnum_ShadowMode( value ); }
	static const ShadowMode ToEnum( const string& value ) { return StringToEnum_ShadowMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum TerrainUVSetPin
{
	TERRAINUVSETPIN_GLOBAL = 0,
	TERRAINUVSETPIN_LOCAL = 1,
};

const char *EnumToString( const TerrainUVSetPin value );
const TerrainUVSetPin StringToEnum_TerrainUVSetPin( const char* value );

template <>
struct KnownEnum< TerrainUVSetPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const TerrainUVSetPin value ) { return EnumToString( value ); }
	static const TerrainUVSetPin ToEnum( const char* value ) { return StringToEnum_TerrainUVSetPin( value ); }
	static const TerrainUVSetPin ToEnum( const string& value ) { return StringToEnum_TerrainUVSetPin( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum TextureAddressType
{
	TEXTUREADDRESSTYPE_WRAP = 0,
	TEXTUREADDRESSTYPE_CLAMP = 1,
	TEXTUREADDRESSTYPE_MIRROR = 2,
	TEXTUREADDRESSTYPE_BORDER = 3,
};

const char *EnumToString( const TextureAddressType value );
const TextureAddressType StringToEnum_TextureAddressType( const char* value );

template <>
struct KnownEnum< TextureAddressType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const TextureAddressType value ) { return EnumToString( value ); }
	static const TextureAddressType ToEnum( const char* value ) { return StringToEnum_TextureAddressType( value ); }
	static const TextureAddressType ToEnum( const string& value ) { return StringToEnum_TextureAddressType( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum TextureColorizePin
{
	TEXTURECOLORIZEPIN_NOCOLOR = 0,
	TEXTURECOLORIZEPIN_ADDCOLOREDALPHA = 1,
	TEXTURECOLORIZEPIN_MULCOLORBYALPHA = 2,
	TEXTURECOLORIZEPIN_COLORFOREVERYCHANEL = 3,
	TEXTURECOLORIZEPIN_TESTCOLOR = 4,
};

const char *EnumToString( const TextureColorizePin value );
const TextureColorizePin StringToEnum_TextureColorizePin( const char* value );

template <>
struct KnownEnum< TextureColorizePin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 5 };
	static const char *ToString( const TextureColorizePin value ) { return EnumToString( value ); }
	static const TextureColorizePin ToEnum( const char* value ) { return StringToEnum_TextureColorizePin( value ); }
	static const TextureColorizePin ToEnum( const string& value ) { return StringToEnum_TextureColorizePin( value.c_str() ); }
	static const int SizeOf() { return 5; }
};

enum TextureCountPin
{
	TEXTURECOUNTPIN_COUNT1 = 0,
	TEXTURECOUNTPIN_COUNT2 = 1,
	TEXTURECOUNTPIN_COUNT3 = 2,
	TEXTURECOUNTPIN_COUNT4 = 3,
};

const char *EnumToString( const TextureCountPin value );
const TextureCountPin StringToEnum_TextureCountPin( const char* value );

template <>
struct KnownEnum< TextureCountPin >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const TextureCountPin value ) { return EnumToString( value ); }
	static const TextureCountPin ToEnum( const char* value ) { return StringToEnum_TextureCountPin( value ); }
	static const TextureCountPin ToEnum( const string& value ) { return StringToEnum_TextureCountPin( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum WarFogType
{
	WARFOGTYPE_SINGLELAYER = 0,
	WARFOGTYPE_DUALLAYER = 1,
};

const char *EnumToString( const WarFogType value );
const WarFogType StringToEnum_WarFogType( const char* value );

template <>
struct KnownEnum< WarFogType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const WarFogType value ) { return EnumToString( value ); }
	static const WarFogType ToEnum( const char* value ) { return StringToEnum_WarFogType( value ); }
	static const WarFogType ToEnum( const string& value ) { return StringToEnum_WarFogType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

struct BakedLighting
{
public:
	int dynObjLightingGridResX;
	int dynObjLightingGridResY;
	float renderedEnvironmentEffect;
	float renderedEnvironmentRange;
	string dynObjBakedLighting;
	string vertexColorsFileName;

	BakedLighting();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Direction
{
public:
	float Yaw;
	float Pitch;

	Direction();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct MaterialParameterDescriptor
{
public:
	string name;
	int presentDefineIndex;
	vector< int > presentValues;

	MaterialParameterDescriptor();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PointLightInfo
{
public:
	Attenuation attenuation;
	CVec3 location;
	float range;
	Render::HDRColor diffuse;
	float diffuseIntensity;
	PointLightFlags flags;

	PointLightInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct RenderState
{
public:
	BlendMode blendMode;
	OnOffState alphaTest;
	int alphaTestRef;
	OnOffState culling;

	RenderState();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SamplerState
{
public:
	MinFilterType minFilter;
	MagFilterType magFilter;
	MipFilterType mipFilter;
	TextureAddressType addressU;
	TextureAddressType addressV;
	TextureAddressType addressW;

	SamplerState();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const SamplerState &_samplerState ) const { return IsEqual( _samplerState ); }
	bool operator!=( const SamplerState &_samplerState ) const { return !IsEqual( _samplerState ); }
	bool IsEqual ( const SamplerState &_samplerState ) const;
};

struct SamplerCube
{
public:
	SamplerState samplerState;
	Ptr< CubeMap > texture;

	SamplerCube();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SamplerEx
{
public:
	SamplerState samplerState;
	Ptr< TextureBase > texture;
	Render::HDRColor Multiplier;
	Render::HDRColor Add;

	SamplerEx();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Sampler
{
public:
	SamplerState samplerState;
	Ptr< TextureBase > texture;

	Sampler();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ShaderDefineDescriptor
{
public:
	string name;
	int minValue;
	int maxValue;
	bool CanChangedInEditor;
	vector< string > definesValuesDescriptions;

	ShaderDefineDescriptor();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ShaderDefinesDescriptorsTable
{
public:
	vector< ShaderDefineDescriptor > definesDescriptors;

	ShaderDefinesDescriptorsTable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Material : public DbResource
{
public:
	virtual const DWORD GetObjectTypeID() const = 0;
	int SubPriority;
	string caption;
	MaterialFlags renderFlags;
	bool ignoreRenderState;
	enum { flags = 0, };
	enum { priority = 0, };

	Material();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Material& operator = ( const Material &_material ) { Assign( _material ); return *this; }
	Material( const Material &_material ) { Assign( _material ); }
	virtual void Assign( const Material &_material );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Material * pOther = dynamic_cast< const Material * > ( _pResource );
		if ( pOther ) Material::Assign( *pOther );
	}
};

struct AOEMaterial : public Material
{
	DBRESOURCE_METHODS( AOEMaterial );
public:
	enum { typeId = 0x3B7A5B80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AOEMaterial::typeId; }
	RenderState renderState;
	Sampler DiffuseMap;
	Render::HDRColor primaryColor;
	Render::HDRColor secondaryColor;
	float aspectRatio;
	BooleanPin CustomizedGeometryPinValue;
	enum { flags = 0, };
	enum { priority = 0, };

	AOEMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AOEMaterial& operator = ( const AOEMaterial &_aOEMaterial ) { Assign( _aOEMaterial ); return *this; }
	AOEMaterial( const AOEMaterial &_aOEMaterial ) { Assign( _aOEMaterial ); }
	virtual void Assign( const AOEMaterial &_aOEMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AOEMaterial * pOther = dynamic_cast< const AOEMaterial * > ( _pResource );
		if ( pOther ) AOEMaterial::Assign( *pOther );
	}
};

struct BaseUIMaterial : public Material
{
public:
	EUIImageDrawMode horizontalDrawMode;
	EUIImageDrawMode verticalDrawMode;
	CTPoint<int> textureShift;
	CTPoint<int> imageSize;
	CTPoint<int> imageTileShift;
	CTPoint<int> imageTileSize;
	BooleanPin UseAutosize;
	enum { flags = 0, };
	enum { priority = 0, };

	BaseUIMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BaseUIMaterial& operator = ( const BaseUIMaterial &_baseUIMaterial ) { Assign( _baseUIMaterial ); return *this; }
	BaseUIMaterial( const BaseUIMaterial &_baseUIMaterial ) { Assign( _baseUIMaterial ); }
	virtual void Assign( const BaseUIMaterial &_baseUIMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BaseUIMaterial * pOther = dynamic_cast< const BaseUIMaterial * > ( _pResource );
		if ( pOther ) BaseUIMaterial::Assign( *pOther );
	}
};

struct BasicFXMaterial : public Material
{
	DBRESOURCE_METHODS( BasicFXMaterial );
public:
	enum { typeId = 0x9E5872A2 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BasicFXMaterial::typeId; }
	RenderState renderState;
	Sampler DiffuseMap;
	Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> DiffuseMul;
	Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> DiffuseAdd;
	BooleanPin SkeletalMeshPinValue;
	OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue;
	BooleanPin MultiplyVertexColorPinValue;
	DistortionPin DistortionPinValue;
	float emissive;
	float distortion;
	float masterOpacity;
	int isBlendModeOverrided;
	Animated<float, NDb::AnimatedAlgorithms::Linear> opacity;
	Animated<float, NDb::AnimatedAlgorithms::Linear> uOffset;
	Animated<float, NDb::AnimatedAlgorithms::Linear> vOffset;
	enum { flags = 0, };
	enum { priority = 0, };

	BasicFXMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BasicFXMaterial& operator = ( const BasicFXMaterial &_basicFXMaterial ) { Assign( _basicFXMaterial ); return *this; }
	BasicFXMaterial( const BasicFXMaterial &_basicFXMaterial ) { Assign( _basicFXMaterial ); }
	virtual void Assign( const BasicFXMaterial &_basicFXMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BasicFXMaterial * pOther = dynamic_cast< const BasicFXMaterial * > ( _pResource );
		if ( pOther ) BasicFXMaterial::Assign( *pOther );
	}
};

struct BasicMaskMaterial : public Material
{
	DBRESOURCE_METHODS( BasicMaskMaterial );
public:
	enum { typeId = 0x9963DB80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BasicMaskMaterial::typeId; }
	RenderState renderState;
	Sampler Diffuse;
	Sampler Mask;
	float opacity;
	int isBlendModeOverrided;
	enum { flags = 0, };
	enum { priority = 0, };

	BasicMaskMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BasicMaskMaterial& operator = ( const BasicMaskMaterial &_basicMaskMaterial ) { Assign( _basicMaskMaterial ); return *this; }
	BasicMaskMaterial( const BasicMaskMaterial &_basicMaskMaterial ) { Assign( _basicMaskMaterial ); }
	virtual void Assign( const BasicMaskMaterial &_basicMaskMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BasicMaskMaterial * pOther = dynamic_cast< const BasicMaskMaterial * > ( _pResource );
		if ( pOther ) BasicMaskMaterial::Assign( *pOther );
	}
};

struct BasicMaterial : public Material
{
	DBRESOURCE_METHODS( BasicMaterial );
public:
	enum { typeId = 0x9E5872A4 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)BasicMaterial::typeId; }
	RenderState renderState;
	int isBlendModeOverrided;
	Render::HDRColor diffuseColor;
	float lightingIntencity;
	Sampler DiffuseMap;
	Sampler NormalMap;
	BooleanPin NormalMapPinValue;
	SamplerEx SpecularMap;
	BooleanPin SpecularMapPinValue;
	SamplerCube ReflectionMap;
	ReflectivityPin ReflectivityPinValue;
	Render::HDRColor outputMul;
	Render::HDRColor outputAdd;
	BooleanPin SkeletalMeshPinValue;
	EEmissivePin EmissivePinValue;
	BooleanPin OpacityPinValue;
	BooleanPin SpecularPinValue;
	LightingPin LightingPinValue;
	float emissive;
	float opacity;
	float reflectivity;
	float specularPower;
	bool specialTransparency;
	enum { flags = 0, };
	enum { priority = 0, };

	BasicMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	BasicMaterial& operator = ( const BasicMaterial &_basicMaterial ) { Assign( _basicMaterial ); return *this; }
	BasicMaterial( const BasicMaterial &_basicMaterial ) { Assign( _basicMaterial ); }
	virtual void Assign( const BasicMaterial &_basicMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const BasicMaterial * pOther = dynamic_cast< const BasicMaterial * > ( _pResource );
		if ( pOther ) BasicMaterial::Assign( *pOther );
	}
};

struct CubeMap : public DbResource
{
	DBRESOURCE_METHODS( CubeMap );
public:
	string srcFileName_0;
	string srcFileName_1;
	string srcFileName_2;
	string srcFileName_3;
	string srcFileName_4;
	string srcFileName_5;
	string textureFileName;

	CubeMap();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CubeMap& operator = ( const CubeMap &_cubeMap ) { Assign( _cubeMap ); return *this; }
	CubeMap( const CubeMap &_cubeMap ) { Assign( _cubeMap ); }
	virtual void Assign( const CubeMap &_cubeMap );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CubeMap * pOther = dynamic_cast< const CubeMap * > ( _pResource );
		if ( pOther ) CubeMap::Assign( *pOther );
	}
};

struct DebugMaterial : public Material
{
	DBRESOURCE_METHODS( DebugMaterial );
public:
	enum { typeId = 0x4A55D341 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DebugMaterial::typeId; }
	BooleanPin DarkMapPinValue;
	BooleanPin SkeletalMeshPinValue;
	DebugPin DebugPinValue;
	enum { flags = 0, };
	enum { priority = 0, };

	DebugMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DebugMaterial& operator = ( const DebugMaterial &_debugMaterial ) { Assign( _debugMaterial ); return *this; }
	DebugMaterial( const DebugMaterial &_debugMaterial ) { Assign( _debugMaterial ); }
	virtual void Assign( const DebugMaterial &_debugMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DebugMaterial * pOther = dynamic_cast< const DebugMaterial * > ( _pResource );
		if ( pOther ) DebugMaterial::Assign( *pOther );
	}
};

struct DecalMaterial : public Material
{
	DBRESOURCE_METHODS( DecalMaterial );
public:
	enum { typeId = 0x3B625AC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DecalMaterial::typeId; }
	RenderState renderState;
	Sampler DiffuseMap;
	Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> DiffuseMul;
	Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> DiffuseAdd;
	float radius;
	BooleanPin AccessibilityPinValue;
	OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue;
	BooleanPin DistortionPinValue;
	BooleanPin DecalPlanePinValue;
	float distortion;
	bool putOnWater;
	int isBlendModeOverrided;
	float masterOpacity;
	Animated<float, NDb::AnimatedAlgorithms::Linear> opacity;
	enum { priority = 9, };
	enum { flags = 0, };

	DecalMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DecalMaterial& operator = ( const DecalMaterial &_decalMaterial ) { Assign( _decalMaterial ); return *this; }
	DecalMaterial( const DecalMaterial &_decalMaterial ) { Assign( _decalMaterial ); }
	virtual void Assign( const DecalMaterial &_decalMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DecalMaterial * pOther = dynamic_cast< const DecalMaterial * > ( _pResource );
		if ( pOther ) DecalMaterial::Assign( *pOther );
	}
};

struct DecalTerrainMaterial : public Material
{
	DBRESOURCE_METHODS( DecalTerrainMaterial );
public:
	enum { typeId = 0x37B47B00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DecalTerrainMaterial::typeId; }
	RenderState renderState;
	Sampler DiffuseMap;
	Sampler MaskMap;
	Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> DiffuseMul;
	Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear> DiffuseAdd;
	float radius;
	BooleanPin AccessibilityPinValue;
	OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue;
	BooleanPin DistortionPinValue;
	BooleanPin DecalPlanePinValue;
	float distortion;
	bool putOnWater;
	int isBlendModeOverrided;
	float masterOpacity;
	Animated<float, NDb::AnimatedAlgorithms::Linear> opacity;
	enum { priority = 7, };
	enum { flags = 0, };

	DecalTerrainMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DecalTerrainMaterial& operator = ( const DecalTerrainMaterial &_decalTerrainMaterial ) { Assign( _decalTerrainMaterial ); return *this; }
	DecalTerrainMaterial( const DecalTerrainMaterial &_decalTerrainMaterial ) { Assign( _decalTerrainMaterial ); }
	virtual void Assign( const DecalTerrainMaterial &_decalTerrainMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DecalTerrainMaterial * pOther = dynamic_cast< const DecalTerrainMaterial * > ( _pResource );
		if ( pOther ) DecalTerrainMaterial::Assign( *pOther );
	}
};

struct DropMaterial : public Material
{
	DBRESOURCE_METHODS( DropMaterial );
public:
	enum { typeId = 0xC8667D00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DropMaterial::typeId; }
	RenderState renderState;
	Render::HDRColor diffuseColor;
	float lightingIntencity;
	float ambientIntensity;
	Render::HDRColor additionalAmbient;
	Sampler DiffuseMap;
	Sampler NormalMap;
	BooleanPin NormalMapPinValue;
	SamplerEx SpecularMap;
	BooleanPin SpecularMapPinValue;
	SamplerCube ReflectionMap;
	ReflectivityPin ReflectivityPinValue;
	TextureColorizePin colorizeReflectionMap;
	Render::HDRColor reflectionMapColor0;
	Render::HDRColor reflectionMapColor1;
	Render::HDRColor reflectionMapColor2;
	Render::HDRColor reflectionMapColor3;
	Render::HDRColor outputMul;
	Render::HDRColor outputAdd;
	BooleanPin SkeletalMeshPinValue;
	LightModePin LightModePinValue;
	int isBlendModeOverrided;
	float emissive;
	Animated<float, NDb::AnimatedAlgorithms::Linear> opacity;
	float reflectivityLerp;
	float reflectivityAdd;
	float reflectivityMul;
	float specularPower;
	Animated<float, NDb::AnimatedAlgorithms::Linear> uOffset1;
	Animated<float, NDb::AnimatedAlgorithms::Linear> vOffset1;
	Animated<float, NDb::AnimatedAlgorithms::Linear> uOffset2;
	Animated<float, NDb::AnimatedAlgorithms::Linear> vOffset2;
	enum { flags = 0, };
	enum { priority = 0, };

	DropMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DropMaterial& operator = ( const DropMaterial &_dropMaterial ) { Assign( _dropMaterial ); return *this; }
	DropMaterial( const DropMaterial &_dropMaterial ) { Assign( _dropMaterial ); }
	virtual void Assign( const DropMaterial &_dropMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DropMaterial * pOther = dynamic_cast< const DropMaterial * > ( _pResource );
		if ( pOther ) DropMaterial::Assign( *pOther );
	}
};

struct FullScreenMaterial : public Material
{
	DBRESOURCE_METHODS( FullScreenMaterial );
public:
	enum { typeId = 0x3D85DD40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)FullScreenMaterial::typeId; }
	RenderState renderState;
	Sampler DepthMap;
	Sampler DiffuseMap;
	Sampler BloomMap;
	BooleanPin SharpPinValue;
	BooleanPin BloomPinValue;
	BooleanPin WarFogPinValue;
	BooleanPin R2VBPinValue;
	ColorCorrectPin ColorCorrectPinValue;
	enum { flags = 0, };
	enum { priority = 0, };

	FullScreenMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FullScreenMaterial& operator = ( const FullScreenMaterial &_fullScreenMaterial ) { Assign( _fullScreenMaterial ); return *this; }
	FullScreenMaterial( const FullScreenMaterial &_fullScreenMaterial ) { Assign( _fullScreenMaterial ); }
	virtual void Assign( const FullScreenMaterial &_fullScreenMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FullScreenMaterial * pOther = dynamic_cast< const FullScreenMaterial * > ( _pResource );
		if ( pOther ) FullScreenMaterial::Assign( *pOther );
	}
};

struct GrassMaterial : public Material
{
	DBRESOURCE_METHODS( GrassMaterial );
public:
	enum { typeId = 0x1056F3C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)GrassMaterial::typeId; }
	RenderState renderState;
	SamplerEx FrozenDiffuseMap;
	SamplerEx NormalDiffuseMap;
	SamplerEx BurnedDiffuseMap;
	BooleanPin ShadowReciverPinValue;
	CVec2 bladeSize;
	float elasticity;
	enum { flags = 0, };
	enum { priority = 0, };

	GrassMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GrassMaterial& operator = ( const GrassMaterial &_grassMaterial ) { Assign( _grassMaterial ); return *this; }
	GrassMaterial( const GrassMaterial &_grassMaterial ) { Assign( _grassMaterial ); }
	virtual void Assign( const GrassMaterial &_grassMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GrassMaterial * pOther = dynamic_cast< const GrassMaterial * > ( _pResource );
		if ( pOther ) GrassMaterial::Assign( *pOther );
	}
};

struct HeightfogMaterial : public Material
{
	DBRESOURCE_METHODS( HeightfogMaterial );
public:
	enum { typeId = 0x3B629340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)HeightfogMaterial::typeId; }
	RenderState renderState;
	Sampler noiseMap;
	float noiseR1;
	float noiseR2;
	float noiseR3;
	float speed;
	float tiling;
	Render::HDRColor color1;
	Render::HDRColor color2;
	float roughnessScale;
	float halfFadeDistance;
	enum { priority = 13, };
	enum { flags = 0, };

	HeightfogMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeightfogMaterial& operator = ( const HeightfogMaterial &_heightfogMaterial ) { Assign( _heightfogMaterial ); return *this; }
	HeightfogMaterial( const HeightfogMaterial &_heightfogMaterial ) { Assign( _heightfogMaterial ); }
	virtual void Assign( const HeightfogMaterial &_heightfogMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeightfogMaterial * pOther = dynamic_cast< const HeightfogMaterial * > ( _pResource );
		if ( pOther ) HeightfogMaterial::Assign( *pOther );
	}
};

struct LightEnvironment : public DbResource
{
	DBRESOURCE_METHODS( LightEnvironment );
public:
	Direction Light1Direction;
	Direction Light2Direction;
	Render::HDRColor AmbientColor;
	Render::HDRColor Light1DiffuseColor;
	Render::HDRColor Light2DiffuseColor;
	Ptr< CubeMap > environmentCubeMap;
	Ptr< CubeMap > lightingCubeMap;
	Render::HDRColor minBakedColor;
	Render::HDRColor maxBakedColor;
	vector< float > lightingCubeMapSHCoeffs;
	float WaterOscillationSpeedFactor;
	Render::HDRColor WaterReflColor0;
	Render::HDRColor WaterReflColor1;
	int fullSizeX;
	int fullSizeY;
	int fullSizeSAX;
	int fullSizeSAY;
	ShadowMode shadowMode;
	float powerOfESM;
	float depthBias;
	float biasSlope;
	Render::HDRColor shadowColor;
	Direction shadowDirection;
	ShadowBlendMode shadowBlendMode;
	float shadowLength;
	float shadowFar;
	float shadowFarRange;
	WarFogType warFogType;
	Render::Color warFogColor;
	Render::Color warFogColor2;
	Render::HDRColor warFogColorForObjects;
	float warFogObstacleVisibility;
	bool warFogUseHeightsDelta;
	float warFogMaxHeightsDelta;
	float warFogMiniMapAlphaScale;

	LightEnvironment();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	LightEnvironment& operator = ( const LightEnvironment &_lightEnvironment ) { Assign( _lightEnvironment ); return *this; }
	LightEnvironment( const LightEnvironment &_lightEnvironment ) { Assign( _lightEnvironment ); }
	virtual void Assign( const LightEnvironment &_lightEnvironment );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const LightEnvironment * pOther = dynamic_cast< const LightEnvironment * > ( _pResource );
		if ( pOther ) LightEnvironment::Assign( *pOther );
	}
};

struct LightningMaterial : public Material
{
	DBRESOURCE_METHODS( LightningMaterial );
public:
	enum { typeId = 0x3B61E442 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)LightningMaterial::typeId; }
	RenderState renderState;
	Sampler DiffuseMap;
	enum { flags = 0, };
	enum { priority = 0, };

	LightningMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	LightningMaterial& operator = ( const LightningMaterial &_lightningMaterial ) { Assign( _lightningMaterial ); return *this; }
	LightningMaterial( const LightningMaterial &_lightningMaterial ) { Assign( _lightningMaterial ); }
	virtual void Assign( const LightningMaterial &_lightningMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const LightningMaterial * pOther = dynamic_cast< const LightningMaterial * > ( _pResource );
		if ( pOther ) LightningMaterial::Assign( *pOther );
	}
};

struct AIGeometryMaterialType : public Material
{
	DBRESOURCE_METHODS( AIGeometryMaterialType );
public:
	enum { typeId = 0x49547341 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AIGeometryMaterialType::typeId; }
	RenderState renderState;
	enum { flags = 0, };
	enum { priority = 0, };

	AIGeometryMaterialType();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AIGeometryMaterialType& operator = ( const AIGeometryMaterialType &_aIGeometryMaterialType ) { Assign( _aIGeometryMaterialType ); return *this; }
	AIGeometryMaterialType( const AIGeometryMaterialType &_aIGeometryMaterialType ) { Assign( _aIGeometryMaterialType ); }
	virtual void Assign( const AIGeometryMaterialType &_aIGeometryMaterialType );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AIGeometryMaterialType * pOther = dynamic_cast< const AIGeometryMaterialType * > ( _pResource );
		if ( pOther ) AIGeometryMaterialType::Assign( *pOther );
	}
};

struct NatureMapMaterial : public Material
{
	DBRESOURCE_METHODS( NatureMapMaterial );
public:
	enum { typeId = 0x3B641440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)NatureMapMaterial::typeId; }
	enum { flags = 0, };
	enum { priority = 0, };

	NatureMapMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	NatureMapMaterial& operator = ( const NatureMapMaterial &_natureMapMaterial ) { Assign( _natureMapMaterial ); return *this; }
	NatureMapMaterial( const NatureMapMaterial &_natureMapMaterial ) { Assign( _natureMapMaterial ); }
	virtual void Assign( const NatureMapMaterial &_natureMapMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const NatureMapMaterial * pOther = dynamic_cast< const NatureMapMaterial * > ( _pResource );
		if ( pOther ) NatureMapMaterial::Assign( *pOther );
	}
};

struct PaintMaterial : public Material
{
	DBRESOURCE_METHODS( PaintMaterial );
public:
	enum { typeId = 0x9963ED00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)PaintMaterial::typeId; }
	PackedMasksNumberPin masksNumber;
	PaintMaterialModePin paintMode;
	RenderState renderState;
	Sampler Draft;
	Sampler Background;
	Sampler BaseBackground;
	Sampler Complete;
	Sampler Mask;
	float opacity;
	int isBlendModeOverrided;
	enum { flags = 0, };
	enum { priority = 0, };

	PaintMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PaintMaterial& operator = ( const PaintMaterial &_paintMaterial ) { Assign( _paintMaterial ); return *this; }
	PaintMaterial( const PaintMaterial &_paintMaterial ) { Assign( _paintMaterial ); }
	virtual void Assign( const PaintMaterial &_paintMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PaintMaterial * pOther = dynamic_cast< const PaintMaterial * > ( _pResource );
		if ( pOther ) PaintMaterial::Assign( *pOther );
	}
};

struct ParticleFXMaterial : public Material
{
	DBRESOURCE_METHODS( ParticleFXMaterial );
public:
	enum { typeId = 0x49547342 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ParticleFXMaterial::typeId; }
	RenderState renderState;
	SamplerEx DiffuseMap;
	OpacityAndEmissiveModePin OpacityAndEmissiveModePinValue;
	OrientTypePin OrientTypePinValue;
	BooleanPin DistortionPinValue;
	float opacity;
	float distortion;
	CVec2 uvSpeed;
	int isBlendModeOverrided;
	float scale;
	enum { priority = 11, };
	enum { flags = 0, };

	ParticleFXMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ParticleFXMaterial& operator = ( const ParticleFXMaterial &_particleFXMaterial ) { Assign( _particleFXMaterial ); return *this; }
	ParticleFXMaterial( const ParticleFXMaterial &_particleFXMaterial ) { Assign( _particleFXMaterial ); }
	virtual void Assign( const ParticleFXMaterial &_particleFXMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ParticleFXMaterial * pOther = dynamic_cast< const ParticleFXMaterial * > ( _pResource );
		if ( pOther ) ParticleFXMaterial::Assign( *pOther );
	}
};

struct RoadMaterial : public Material
{
	DBRESOURCE_METHODS( RoadMaterial );
public:
	enum { typeId = 0x3B759340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)RoadMaterial::typeId; }
	RenderState renderState;
	Sampler RoadMap;
	Sampler BorderMap;
	BooleanPin TextureFitPinValue;
	BooleanPin DebugPinValue;
	enum { flags = 0, };
	enum { priority = 0, };

	RoadMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	RoadMaterial& operator = ( const RoadMaterial &_roadMaterial ) { Assign( _roadMaterial ); return *this; }
	RoadMaterial( const RoadMaterial &_roadMaterial ) { Assign( _roadMaterial ); }
	virtual void Assign( const RoadMaterial &_roadMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const RoadMaterial * pOther = dynamic_cast< const RoadMaterial * > ( _pResource );
		if ( pOther ) RoadMaterial::Assign( *pOther );
	}
};

struct ShadowMaterial : public Material
{
	DBRESOURCE_METHODS( ShadowMaterial );
public:
	enum { typeId = 0x3D82C581 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ShadowMaterial::typeId; }
	RenderState renderState;
	Sampler DiffuseMap;
	BooleanPin SkeletalMeshPinValue;
	enum { flags = 0, };
	enum { priority = 0, };

	ShadowMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ShadowMaterial& operator = ( const ShadowMaterial &_shadowMaterial ) { Assign( _shadowMaterial ); return *this; }
	ShadowMaterial( const ShadowMaterial &_shadowMaterial ) { Assign( _shadowMaterial ); }
	virtual void Assign( const ShadowMaterial &_shadowMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ShadowMaterial * pOther = dynamic_cast< const ShadowMaterial * > ( _pResource );
		if ( pOther ) ShadowMaterial::Assign( *pOther );
	}
};

struct SilhouetteMaterial : public Material
{
	DBRESOURCE_METHODS( SilhouetteMaterial );
public:
	enum { typeId = 0x3B78C340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SilhouetteMaterial::typeId; }
	RenderState renderState;
	BooleanPin SkeletalMeshPinValue;
	enum { flags = 0, };
	enum { priority = 0, };

	SilhouetteMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SilhouetteMaterial& operator = ( const SilhouetteMaterial &_silhouetteMaterial ) { Assign( _silhouetteMaterial ); return *this; }
	SilhouetteMaterial( const SilhouetteMaterial &_silhouetteMaterial ) { Assign( _silhouetteMaterial ); }
	virtual void Assign( const SilhouetteMaterial &_silhouetteMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SilhouetteMaterial * pOther = dynamic_cast< const SilhouetteMaterial * > ( _pResource );
		if ( pOther ) SilhouetteMaterial::Assign( *pOther );
	}
};

struct SkyMaterial : public Material
{
	DBRESOURCE_METHODS( SkyMaterial );
public:
	enum { typeId = 0x3D84CC00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)SkyMaterial::typeId; }
	RenderState renderState;
	Sampler DiffuseMap;
	Render::HDRColor outputMul;
	Render::HDRColor outputAdd;
	Animated<float, NDb::AnimatedAlgorithms::Linear> uOffset1;
	Animated<float, NDb::AnimatedAlgorithms::Linear> vOffset1;
	Animated<float, NDb::AnimatedAlgorithms::Linear> uOffset2;
	Animated<float, NDb::AnimatedAlgorithms::Linear> vOffset2;
	enum { priority = 14, };
	enum { flags = 0, };

	SkyMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SkyMaterial& operator = ( const SkyMaterial &_skyMaterial ) { Assign( _skyMaterial ); return *this; }
	SkyMaterial( const SkyMaterial &_skyMaterial ) { Assign( _skyMaterial ); }
	virtual void Assign( const SkyMaterial &_skyMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SkyMaterial * pOther = dynamic_cast< const SkyMaterial * > ( _pResource );
		if ( pOther ) SkyMaterial::Assign( *pOther );
	}
};

struct TerrainAOEMaterial : public Material
{
	DBRESOURCE_METHODS( TerrainAOEMaterial );
public:
	enum { typeId = 0x3B5C8C00 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TerrainAOEMaterial::typeId; }
	RenderState renderState;
	Sampler DiffuseMap;
	CVec2 uvScale;
	CVec2 uvOffset;
	enum { flags = 0, };
	enum { priority = 0, };

	TerrainAOEMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TerrainAOEMaterial& operator = ( const TerrainAOEMaterial &_terrainAOEMaterial ) { Assign( _terrainAOEMaterial ); return *this; }
	TerrainAOEMaterial( const TerrainAOEMaterial &_terrainAOEMaterial ) { Assign( _terrainAOEMaterial ); }
	virtual void Assign( const TerrainAOEMaterial &_terrainAOEMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TerrainAOEMaterial * pOther = dynamic_cast< const TerrainAOEMaterial * > ( _pResource );
		if ( pOther ) TerrainAOEMaterial::Assign( *pOther );
	}
};

struct TerrainElementDebugMaterial : public Material
{
	DBRESOURCE_METHODS( TerrainElementDebugMaterial );
public:
	enum { typeId = 0x3B61E340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TerrainElementDebugMaterial::typeId; }
	enum { flags = 0, };
	enum { priority = 0, };

	TerrainElementDebugMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TerrainElementDebugMaterial& operator = ( const TerrainElementDebugMaterial &_terrainElementDebugMaterial ) { Assign( _terrainElementDebugMaterial ); return *this; }
	TerrainElementDebugMaterial( const TerrainElementDebugMaterial &_terrainElementDebugMaterial ) { Assign( _terrainElementDebugMaterial ); }
	virtual void Assign( const TerrainElementDebugMaterial &_terrainElementDebugMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TerrainElementDebugMaterial * pOther = dynamic_cast< const TerrainElementDebugMaterial * > ( _pResource );
		if ( pOther ) TerrainElementDebugMaterial::Assign( *pOther );
	}
};

struct TerrainElementMaterial : public Material
{
	DBRESOURCE_METHODS( TerrainElementMaterial );
public:
	enum { typeId = 0x3B5BDAC1 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TerrainElementMaterial::typeId; }
	TerrainUVSetPin TerrainUVSetPinValue;
	TextureCountPin TextureCountPinValue;
	enum { flags = 0, };
	enum { priority = 0, };

	TerrainElementMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TerrainElementMaterial& operator = ( const TerrainElementMaterial &_terrainElementMaterial ) { Assign( _terrainElementMaterial ); return *this; }
	TerrainElementMaterial( const TerrainElementMaterial &_terrainElementMaterial ) { Assign( _terrainElementMaterial ); }
	virtual void Assign( const TerrainElementMaterial &_terrainElementMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TerrainElementMaterial * pOther = dynamic_cast< const TerrainElementMaterial * > ( _pResource );
		if ( pOther ) TerrainElementMaterial::Assign( *pOther );
	}
};

struct TerrainHeightBuilderMaterial : public Material
{
	DBRESOURCE_METHODS( TerrainHeightBuilderMaterial );
public:
	enum { typeId = 0x9354BD01 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TerrainHeightBuilderMaterial::typeId; }
	RenderState renderState;
	enum { flags = 0, };
	enum { priority = 0, };

	TerrainHeightBuilderMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TerrainHeightBuilderMaterial& operator = ( const TerrainHeightBuilderMaterial &_terrainHeightBuilderMaterial ) { Assign( _terrainHeightBuilderMaterial ); return *this; }
	TerrainHeightBuilderMaterial( const TerrainHeightBuilderMaterial &_terrainHeightBuilderMaterial ) { Assign( _terrainHeightBuilderMaterial ); }
	virtual void Assign( const TerrainHeightBuilderMaterial &_terrainHeightBuilderMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TerrainHeightBuilderMaterial * pOther = dynamic_cast< const TerrainHeightBuilderMaterial * > ( _pResource );
		if ( pOther ) TerrainHeightBuilderMaterial::Assign( *pOther );
	}
};

struct TerrainMaterial : public Material
{
	DBRESOURCE_METHODS( TerrainMaterial );
public:
	enum { typeId = 0x49547344 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TerrainMaterial::typeId; }
	CTRect<float> grassRect;
	SamplerEx A_DiffuseMap;
	SamplerEx N_DiffuseMap;
	SamplerEx B_DiffuseMap;
	SamplerEx FrozenNormalMap;
	SamplerEx NormalNormalMap;
	SamplerEx BurnedNormalMap;
	SamplerEx FrozenSpecularMap;
	SamplerEx NormalSpecularMap;
	SamplerEx BurnedSpecularMap;
	SamplerEx DarkMap;
	BooleanPin NormalMapPinValue;
	BooleanPin ShadowReciverPinValue;
	BooleanPin ShadowCasterPinValue;
	BooleanPin SpecularMapPinValue;
	BooleanPin EnvMapPinValue;
	BooleanPin DarkMapPinValue;
	TerrainUVSetPin TerrainUVSetPinValue;
	enum { flags = 0, };
	enum { priority = 0, };

	TerrainMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TerrainMaterial& operator = ( const TerrainMaterial &_terrainMaterial ) { Assign( _terrainMaterial ); return *this; }
	TerrainMaterial( const TerrainMaterial &_terrainMaterial ) { Assign( _terrainMaterial ); }
	virtual void Assign( const TerrainMaterial &_terrainMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TerrainMaterial * pOther = dynamic_cast< const TerrainMaterial * > ( _pResource );
		if ( pOther ) TerrainMaterial::Assign( *pOther );
	}
};

struct TestTownMaterial : public Material
{
	DBRESOURCE_METHODS( TestTownMaterial );
public:
	enum { typeId = 0x9D66EBC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TestTownMaterial::typeId; }
	RenderState RenderState;
	Sampler DiffuseMap;
	BooleanPin UseDiffuse;
	Render::HDRColor outputMul;
	Render::HDRColor outputAdd;
	enum { flags = 0, };
	enum { priority = 0, };

	TestTownMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TestTownMaterial& operator = ( const TestTownMaterial &_testTownMaterial ) { Assign( _testTownMaterial ); return *this; }
	TestTownMaterial( const TestTownMaterial &_testTownMaterial ) { Assign( _testTownMaterial ); }
	virtual void Assign( const TestTownMaterial &_testTownMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TestTownMaterial * pOther = dynamic_cast< const TestTownMaterial * > ( _pResource );
		if ( pOther ) TestTownMaterial::Assign( *pOther );
	}
};

struct TextureBase : public DbResource
{
	DBRESOURCE_METHODS( TextureBase );
public:

	TextureBase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TextureBase& operator = ( const TextureBase &_textureBase ) { Assign( _textureBase ); return *this; }
	TextureBase( const TextureBase &_textureBase ) { Assign( _textureBase ); }
	virtual void Assign( const TextureBase &_textureBase );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TextureBase * pOther = dynamic_cast< const TextureBase * > ( _pResource );
		if ( pOther ) TextureBase::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<Render::Texture> Load() const;
	virtual CObj<Render::Texture> LoadInPool( bool canBeVisualDegrade, void * texturePoolId ) const;
#endif // #ifndef VISUAL_CUTTED
};

struct TraceMaterial : public Material
{
	DBRESOURCE_METHODS( TraceMaterial );
public:
	enum { typeId = 0x3B61AC40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TraceMaterial::typeId; }
	RenderState renderState;
	Sampler DiffuseMap;
	BooleanPin TraceTexturePinValue;
	float uScale;
	float vScale;
	Animated<float, NDb::AnimatedAlgorithms::Linear> uOffset;
	Animated<float, NDb::AnimatedAlgorithms::Linear> vOffset;
	enum { flags = 0, };
	enum { priority = 0, };

	TraceMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	TraceMaterial& operator = ( const TraceMaterial &_traceMaterial ) { Assign( _traceMaterial ); return *this; }
	TraceMaterial( const TraceMaterial &_traceMaterial ) { Assign( _traceMaterial ); }
	virtual void Assign( const TraceMaterial &_traceMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const TraceMaterial * pOther = dynamic_cast< const TraceMaterial * > ( _pResource );
		if ( pOther ) TraceMaterial::Assign( *pOther );
	}
};

struct UIBaseMaterial : public BaseUIMaterial
{
	DBRESOURCE_METHODS( UIBaseMaterial );
public:
	enum { typeId = 0x9D656300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UIBaseMaterial::typeId; }
	Sampler DiffuseMap;
	Sampler MaskMap;
	Render::HDRColor color1;
	Render::HDRColor color2;
	float coef1;
	float coef2;
	float coef3;
	float coef4;
	float stripesStart;
	float stripesStep1;
	float stripesStep2;
	float stripesBlendFactor1;
	BooleanPin UseDiffuse;
	MaskingTypePin Masking;
	BooleanPin Gradient;
	BooleanPin Colorized;
	BooleanPin Stripes;
	Render::HDRColor colorStripe100;
	Render::HDRColor colorStripe1000;
	RenderState renderState;
	enum { flags = 0, };
	enum { priority = 0, };

	UIBaseMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIBaseMaterial& operator = ( const UIBaseMaterial &_uIBaseMaterial ) { Assign( _uIBaseMaterial ); return *this; }
	UIBaseMaterial( const UIBaseMaterial &_uIBaseMaterial ) { Assign( _uIBaseMaterial ); }
	virtual void Assign( const UIBaseMaterial &_uIBaseMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIBaseMaterial * pOther = dynamic_cast< const UIBaseMaterial * > ( _pResource );
		if ( pOther ) UIBaseMaterial::Assign( *pOther );
	}
};

struct UIButtonMaterial : public BaseUIMaterial
{
	DBRESOURCE_METHODS( UIButtonMaterial );
public:
	enum { typeId = 0x9D6ABB80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UIButtonMaterial::typeId; }
	Sampler BackgroundMap;
	Sampler DiffuseMap;
	Sampler WaitForActMap;
	Sampler LackOfManaMap;
	Sampler PressedMap;
	Sampler HighlightMap;
	Sampler ScreenMap;
	BooleanPin WaitForActivationPin;
	BooleanPin LackOfManaPin;
	BooleanPin PressedPin;
	BooleanPin HighlightPin;
	BooleanPin DisablePin;
	BooleanPin PassivePin;
	BooleanPin UseDiffusePin;
	float ScreenOpacity;
	RenderState renderState;
	enum { flags = 0, };
	enum { priority = 0, };

	UIButtonMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIButtonMaterial& operator = ( const UIButtonMaterial &_uIButtonMaterial ) { Assign( _uIButtonMaterial ); return *this; }
	UIButtonMaterial( const UIButtonMaterial &_uIButtonMaterial ) { Assign( _uIButtonMaterial ); }
	virtual void Assign( const UIButtonMaterial &_uIButtonMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIButtonMaterial * pOther = dynamic_cast< const UIButtonMaterial * > ( _pResource );
		if ( pOther ) UIButtonMaterial::Assign( *pOther );
	}
};

struct UIFlashMaterial : public Material
{
	DBRESOURCE_METHODS( UIFlashMaterial );
public:
	enum { typeId = 0x9D657440 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UIFlashMaterial::typeId; }
	Sampler DiffuseMap;
	Sampler DiffuseMap2;
	BooleanPin UseDiffuse;
	BooleanPin UseDiffuse2;
	BooleanPin MorphShapes;
	BooleanPin ShaderForLines;
	BooleanPin UseColorFilter;
	BooleanPin Scale9Grid;
	BooleanPin Scale9GridBitmap;
	FlashBlendModePin FlashBlendMode;
	Render::HDRColor CXFormMul;
	Render::HDRColor CXFormAdd;
	enum { flags = 0, };
	enum { priority = 0, };

	UIFlashMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIFlashMaterial& operator = ( const UIFlashMaterial &_uIFlashMaterial ) { Assign( _uIFlashMaterial ); return *this; }
	UIFlashMaterial( const UIFlashMaterial &_uIFlashMaterial ) { Assign( _uIFlashMaterial ); }
	virtual void Assign( const UIFlashMaterial &_uIFlashMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIFlashMaterial * pOther = dynamic_cast< const UIFlashMaterial * > ( _pResource );
		if ( pOther ) UIFlashMaterial::Assign( *pOther );
	}
};

struct UIFontMaterial : public Material
{
	DBRESOURCE_METHODS( UIFontMaterial );
public:
	enum { typeId = 0x9D65A480 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UIFontMaterial::typeId; }
	Sampler DiffuseMap;
	BooleanPin UseDiffuse;
	BooleanPin DrawContour;
	Render::HDRColor PrimaryColor;
	Render::HDRColor SecondaryColor;
	RenderState renderState;
	enum { flags = 0, };
	enum { priority = 0, };

	UIFontMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIFontMaterial& operator = ( const UIFontMaterial &_uIFontMaterial ) { Assign( _uIFontMaterial ); return *this; }
	UIFontMaterial( const UIFontMaterial &_uIFontMaterial ) { Assign( _uIFontMaterial ); }
	virtual void Assign( const UIFontMaterial &_uIFontMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIFontMaterial * pOther = dynamic_cast< const UIFontMaterial * > ( _pResource );
		if ( pOther ) UIFontMaterial::Assign( *pOther );
	}
};

struct UIGlassMaterial : public BaseUIMaterial
{
	DBRESOURCE_METHODS( UIGlassMaterial );
public:
	enum { typeId = 0x9D661300 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)UIGlassMaterial::typeId; }
	Sampler BackgroundMap;
	Sampler DiffuseMap;
	Sampler OverlayMap;
	Sampler ScreenMap;
	float OverlayOpacity;
	float ScreenOpacity;
	RenderState renderState;
	enum { flags = 0, };
	enum { priority = 0, };

	UIGlassMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	UIGlassMaterial& operator = ( const UIGlassMaterial &_uIGlassMaterial ) { Assign( _uIGlassMaterial ); return *this; }
	UIGlassMaterial( const UIGlassMaterial &_uIGlassMaterial ) { Assign( _uIGlassMaterial ); }
	virtual void Assign( const UIGlassMaterial &_uIGlassMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const UIGlassMaterial * pOther = dynamic_cast< const UIGlassMaterial * > ( _pResource );
		if ( pOther ) UIGlassMaterial::Assign( *pOther );
	}
};

struct WaterDummyMaterial : public Material
{
	DBRESOURCE_METHODS( WaterDummyMaterial );
public:
	enum { typeId = 0x3B686340 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)WaterDummyMaterial::typeId; }
	enum { flags = 0, };
	enum { priority = 0, };

	WaterDummyMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	WaterDummyMaterial& operator = ( const WaterDummyMaterial &_waterDummyMaterial ) { Assign( _waterDummyMaterial ); return *this; }
	WaterDummyMaterial( const WaterDummyMaterial &_waterDummyMaterial ) { Assign( _waterDummyMaterial ); }
	virtual void Assign( const WaterDummyMaterial &_waterDummyMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const WaterDummyMaterial * pOther = dynamic_cast< const WaterDummyMaterial * > ( _pResource );
		if ( pOther ) WaterDummyMaterial::Assign( *pOther );
	}
};

struct WaterMapMaterial : public Material
{
	DBRESOURCE_METHODS( WaterMapMaterial );
public:
	enum { typeId = 0xA06B4B80 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)WaterMapMaterial::typeId; }
	enum { flags = 0, };
	enum { priority = 0, };

	WaterMapMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	WaterMapMaterial& operator = ( const WaterMapMaterial &_waterMapMaterial ) { Assign( _waterMapMaterial ); return *this; }
	WaterMapMaterial( const WaterMapMaterial &_waterMapMaterial ) { Assign( _waterMapMaterial ); }
	virtual void Assign( const WaterMapMaterial &_waterMapMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const WaterMapMaterial * pOther = dynamic_cast< const WaterMapMaterial * > ( _pResource );
		if ( pOther ) WaterMapMaterial::Assign( *pOther );
	}
};

struct WaterMaterial : public Material
{
	DBRESOURCE_METHODS( WaterMaterial );
public:
	enum { typeId = 0x9E5574C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)WaterMaterial::typeId; }
	BooleanPin CausticsTexturePinValue;
	enum { flags = 0, };
	enum { priority = 0, };

	WaterMaterial();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	WaterMaterial& operator = ( const WaterMaterial &_waterMaterial ) { Assign( _waterMaterial ); return *this; }
	WaterMaterial( const WaterMaterial &_waterMaterial ) { Assign( _waterMaterial ); }
	virtual void Assign( const WaterMaterial &_waterMaterial );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const WaterMaterial * pOther = dynamic_cast< const WaterMaterial * > ( _pResource );
		if ( pOther ) WaterMaterial::Assign( *pOther );
	}
};

}; // namespace NDb
