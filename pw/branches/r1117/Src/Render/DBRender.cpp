// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBRender.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_DBRESOURCE( Material );
REGISTER_DBRESOURCE( AOEMaterial );
BASIC_REGISTER_DBRESOURCE( BaseUIMaterial );
REGISTER_DBRESOURCE( BasicFXMaterial );
REGISTER_DBRESOURCE( BasicMaskMaterial );
REGISTER_DBRESOURCE( BasicMaterial );
REGISTER_DBRESOURCE( CubeMap );
REGISTER_DBRESOURCE( DebugMaterial );
REGISTER_DBRESOURCE( DecalMaterial );
REGISTER_DBRESOURCE( DecalTerrainMaterial );
REGISTER_DBRESOURCE( DropMaterial );
REGISTER_DBRESOURCE( FullScreenMaterial );
REGISTER_DBRESOURCE( GrassMaterial );
REGISTER_DBRESOURCE( HeightfogMaterial );
REGISTER_DBRESOURCE( LightEnvironment );
REGISTER_DBRESOURCE( LightningMaterial );
REGISTER_DBRESOURCE( AIGeometryMaterialType );
REGISTER_DBRESOURCE( NatureMapMaterial );
REGISTER_DBRESOURCE( PaintMaterial );
REGISTER_DBRESOURCE( ParticleFXMaterial );
REGISTER_DBRESOURCE( RoadMaterial );
REGISTER_DBRESOURCE( ShadowMaterial );
REGISTER_DBRESOURCE( SilhouetteMaterial );
REGISTER_DBRESOURCE( SkyMaterial );
REGISTER_DBRESOURCE( TerrainAOEMaterial );
REGISTER_DBRESOURCE( TerrainElementDebugMaterial );
REGISTER_DBRESOURCE( TerrainElementMaterial );
REGISTER_DBRESOURCE( TerrainHeightBuilderMaterial );
REGISTER_DBRESOURCE( TerrainMaterial );
REGISTER_DBRESOURCE( TestTownMaterial );
REGISTER_DBRESOURCE( TextureBase );
REGISTER_DBRESOURCE( TraceMaterial );
REGISTER_DBRESOURCE( UIBaseMaterial );
REGISTER_DBRESOURCE( UIButtonMaterial );
REGISTER_DBRESOURCE( UIFlashMaterial );
REGISTER_DBRESOURCE( UIFontMaterial );
REGISTER_DBRESOURCE( UIGlassMaterial );
REGISTER_DBRESOURCE( WaterDummyMaterial );
REGISTER_DBRESOURCE( WaterMapMaterial );
REGISTER_DBRESOURCE( WaterMaterial );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const Attenuation value )
{
	switch( value )
	{
		case ATTENUATION_LINEAR:
			return "Linear";
		case ATTENUATION_NORMAL:
			return "Normal";
		case ATTENUATION_SLOW:
			return "Slow";
		case ATTENUATION_FAST:
			return "Fast";
		case ATTENUATION_NONE:
			return "None";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum Attenuation", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Attenuation StringToEnum_Attenuation( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (Attenuation)(NStr::ToInt( value ));
	if ( strcmp( value, "Linear" ) == 0 || strcmp( value, "ATTENUATION_LINEAR" ) == 0 )
		return ATTENUATION_LINEAR;
	if ( strcmp( value, "Normal" ) == 0 || strcmp( value, "ATTENUATION_NORMAL" ) == 0 )
		return ATTENUATION_NORMAL;
	if ( strcmp( value, "Slow" ) == 0 || strcmp( value, "ATTENUATION_SLOW" ) == 0 )
		return ATTENUATION_SLOW;
	if ( strcmp( value, "Fast" ) == 0 || strcmp( value, "ATTENUATION_FAST" ) == 0 )
		return ATTENUATION_FAST;
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "ATTENUATION_NONE" ) == 0 )
		return ATTENUATION_NONE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum Attenuation", value ) );
	return ATTENUATION_LINEAR;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const BlendFactor value )
{
	switch( value )
	{
		case BLENDFACTOR_ONE:
			return "ONE";
		case BLENDFACTOR_SRCALPHA:
			return "SRCALPHA";
		case BLENDFACTOR_INVSRCALPHA:
			return "INVSRCALPHA";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum BlendFactor", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BlendFactor StringToEnum_BlendFactor( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (BlendFactor)(NStr::ToInt( value ));
	if ( strcmp( value, "ONE" ) == 0 || strcmp( value, "BLENDFACTOR_ONE" ) == 0 )
		return BLENDFACTOR_ONE;
	if ( strcmp( value, "SRCALPHA" ) == 0 || strcmp( value, "BLENDFACTOR_SRCALPHA" ) == 0 )
		return BLENDFACTOR_SRCALPHA;
	if ( strcmp( value, "INVSRCALPHA" ) == 0 || strcmp( value, "BLENDFACTOR_INVSRCALPHA" ) == 0 )
		return BLENDFACTOR_INVSRCALPHA;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum BlendFactor", value ) );
	return BLENDFACTOR_ONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const BlendMode value )
{
	switch( value )
	{
		case BLENDMODE_OFF:
			return "Off";
		case BLENDMODE_LERPBYALPHA:
			return "LerpByAlpha";
		case BLENDMODE_PREMULTIPLIEDLERP:
			return "PremultipliedLerp";
		case BLENDMODE_ADDCOLOR:
			return "AddColor";
		case BLENDMODE_ADDCOLORMULALPHA:
			return "AddColorMulAlpha";
		case BLENDMODE_MULCOLOR:
			return "MulColor";
		case BLENDMODE_MULINVCOLOR:
			return "MulInvColor";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum BlendMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BlendMode StringToEnum_BlendMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (BlendMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Off" ) == 0 || strcmp( value, "BLENDMODE_OFF" ) == 0 )
		return BLENDMODE_OFF;
	if ( strcmp( value, "LerpByAlpha" ) == 0 || strcmp( value, "BLENDMODE_LERPBYALPHA" ) == 0 )
		return BLENDMODE_LERPBYALPHA;
	if ( strcmp( value, "PremultipliedLerp" ) == 0 || strcmp( value, "BLENDMODE_PREMULTIPLIEDLERP" ) == 0 )
		return BLENDMODE_PREMULTIPLIEDLERP;
	if ( strcmp( value, "AddColor" ) == 0 || strcmp( value, "BLENDMODE_ADDCOLOR" ) == 0 )
		return BLENDMODE_ADDCOLOR;
	if ( strcmp( value, "AddColorMulAlpha" ) == 0 || strcmp( value, "BLENDMODE_ADDCOLORMULALPHA" ) == 0 )
		return BLENDMODE_ADDCOLORMULALPHA;
	if ( strcmp( value, "MulColor" ) == 0 || strcmp( value, "BLENDMODE_MULCOLOR" ) == 0 )
		return BLENDMODE_MULCOLOR;
	if ( strcmp( value, "MulInvColor" ) == 0 || strcmp( value, "BLENDMODE_MULINVCOLOR" ) == 0 )
		return BLENDMODE_MULINVCOLOR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum BlendMode", value ) );
	return BLENDMODE_OFF;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const BooleanPin value )
{
	switch( value )
	{
		case BOOLEANPIN_NONE:
			return "None";
		case BOOLEANPIN_PRESENT:
			return "Present";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum BooleanPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BooleanPin StringToEnum_BooleanPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (BooleanPin)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "BOOLEANPIN_NONE" ) == 0 )
		return BOOLEANPIN_NONE;
	if ( strcmp( value, "Present" ) == 0 || strcmp( value, "BOOLEANPIN_PRESENT" ) == 0 )
		return BOOLEANPIN_PRESENT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum BooleanPin", value ) );
	return BOOLEANPIN_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const BoolPin value )
{
	switch( value )
	{
		case BOOLPIN_FALSE:
			return "FALSE";
		case BOOLPIN_TRUE:
			return "TRUE";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum BoolPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const BoolPin StringToEnum_BoolPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (BoolPin)(NStr::ToInt( value ));
	if ( strcmp( value, "FALSE" ) == 0 || strcmp( value, "BOOLPIN_FALSE" ) == 0 )
		return BOOLPIN_FALSE;
	if ( strcmp( value, "TRUE" ) == 0 || strcmp( value, "BOOLPIN_TRUE" ) == 0 )
		return BOOLPIN_TRUE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum BoolPin", value ) );
	return BOOLPIN_FALSE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const CachingPin value )
{
	switch( value )
	{
		case CACHINGPIN_ORDINARY:
			return "Ordinary";
		case CACHINGPIN_FILL:
			return "Fill";
		case CACHINGPIN_USE:
			return "Use";
		case CACHINGPIN_USE2:
			return "Use2";
		case CACHINGPIN_USE3:
			return "Use3";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum CachingPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CachingPin StringToEnum_CachingPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (CachingPin)(NStr::ToInt( value ));
	if ( strcmp( value, "Ordinary" ) == 0 || strcmp( value, "CACHINGPIN_ORDINARY" ) == 0 )
		return CACHINGPIN_ORDINARY;
	if ( strcmp( value, "Fill" ) == 0 || strcmp( value, "CACHINGPIN_FILL" ) == 0 )
		return CACHINGPIN_FILL;
	if ( strcmp( value, "Use" ) == 0 || strcmp( value, "CACHINGPIN_USE" ) == 0 )
		return CACHINGPIN_USE;
	if ( strcmp( value, "Use2" ) == 0 || strcmp( value, "CACHINGPIN_USE2" ) == 0 )
		return CACHINGPIN_USE2;
	if ( strcmp( value, "Use3" ) == 0 || strcmp( value, "CACHINGPIN_USE3" ) == 0 )
		return CACHINGPIN_USE3;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum CachingPin", value ) );
	return CACHINGPIN_ORDINARY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ColorCorrectPin value )
{
	switch( value )
	{
		case COLORCORRECTPIN_OFF:
			return "OFF";
		case COLORCORRECTPIN_ON:
			return "ON";
		case COLORCORRECTPIN_NO_GAMMA:
			return "NO_GAMMA";
		case COLORCORRECTPIN_DESATURATE_ONLY:
			return "DESATURATE_ONLY";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ColorCorrectPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ColorCorrectPin StringToEnum_ColorCorrectPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ColorCorrectPin)(NStr::ToInt( value ));
	if ( strcmp( value, "OFF" ) == 0 || strcmp( value, "COLORCORRECTPIN_OFF" ) == 0 )
		return COLORCORRECTPIN_OFF;
	if ( strcmp( value, "ON" ) == 0 || strcmp( value, "COLORCORRECTPIN_ON" ) == 0 )
		return COLORCORRECTPIN_ON;
	if ( strcmp( value, "NO_GAMMA" ) == 0 || strcmp( value, "COLORCORRECTPIN_NO_GAMMA" ) == 0 )
		return COLORCORRECTPIN_NO_GAMMA;
	if ( strcmp( value, "DESATURATE_ONLY" ) == 0 || strcmp( value, "COLORCORRECTPIN_DESATURATE_ONLY" ) == 0 )
		return COLORCORRECTPIN_DESATURATE_ONLY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ColorCorrectPin", value ) );
	return COLORCORRECTPIN_OFF;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const CompareFunction value )
{
	switch( value )
	{
		case COMPAREFUNCTION_NEVER:
			return "Never";
		case COMPAREFUNCTION_LESS:
			return "Less";
		case COMPAREFUNCTION_EQUAL:
			return "Equal";
		case COMPAREFUNCTION_LESSOREQUAL:
			return "LessOrEqual";
		case COMPAREFUNCTION_GREATER:
			return "Greater";
		case COMPAREFUNCTION_NOTEQUAL:
			return "NotEqual";
		case COMPAREFUNCTION_GREATEROREQUAL:
			return "GreaterOrEqual";
		case COMPAREFUNCTION_ALWAYS:
			return "Always";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum CompareFunction", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CompareFunction StringToEnum_CompareFunction( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (CompareFunction)(NStr::ToInt( value ));
	if ( strcmp( value, "Never" ) == 0 || strcmp( value, "COMPAREFUNCTION_NEVER" ) == 0 )
		return COMPAREFUNCTION_NEVER;
	if ( strcmp( value, "Less" ) == 0 || strcmp( value, "COMPAREFUNCTION_LESS" ) == 0 )
		return COMPAREFUNCTION_LESS;
	if ( strcmp( value, "Equal" ) == 0 || strcmp( value, "COMPAREFUNCTION_EQUAL" ) == 0 )
		return COMPAREFUNCTION_EQUAL;
	if ( strcmp( value, "LessOrEqual" ) == 0 || strcmp( value, "COMPAREFUNCTION_LESSOREQUAL" ) == 0 )
		return COMPAREFUNCTION_LESSOREQUAL;
	if ( strcmp( value, "Greater" ) == 0 || strcmp( value, "COMPAREFUNCTION_GREATER" ) == 0 )
		return COMPAREFUNCTION_GREATER;
	if ( strcmp( value, "NotEqual" ) == 0 || strcmp( value, "COMPAREFUNCTION_NOTEQUAL" ) == 0 )
		return COMPAREFUNCTION_NOTEQUAL;
	if ( strcmp( value, "GreaterOrEqual" ) == 0 || strcmp( value, "COMPAREFUNCTION_GREATEROREQUAL" ) == 0 )
		return COMPAREFUNCTION_GREATEROREQUAL;
	if ( strcmp( value, "Always" ) == 0 || strcmp( value, "COMPAREFUNCTION_ALWAYS" ) == 0 )
		return COMPAREFUNCTION_ALWAYS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum CompareFunction", value ) );
	return COMPAREFUNCTION_NEVER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const CullingMode value )
{
	switch( value )
	{
		case CULLINGMODE_NONE:
			return "NONE";
		case CULLINGMODE_CW:
			return "CW";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum CullingMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CullingMode StringToEnum_CullingMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (CullingMode)(NStr::ToInt( value ));
	if ( strcmp( value, "NONE" ) == 0 || strcmp( value, "CULLINGMODE_NONE" ) == 0 )
		return CULLINGMODE_NONE;
	if ( strcmp( value, "CW" ) == 0 || strcmp( value, "CULLINGMODE_CW" ) == 0 )
		return CULLINGMODE_CW;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum CullingMode", value ) );
	return CULLINGMODE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const DebugPin value )
{
	switch( value )
	{
		case DEBUGPIN_SIMPLESHADING:
			return "SimpleShading";
		case DEBUGPIN_SHOWNORMALS:
			return "ShowNormals";
		case DEBUGPIN_SHOWMIPMAPS:
			return "ShowMipMaps";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum DebugPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DebugPin StringToEnum_DebugPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (DebugPin)(NStr::ToInt( value ));
	if ( strcmp( value, "SimpleShading" ) == 0 || strcmp( value, "DEBUGPIN_SIMPLESHADING" ) == 0 )
		return DEBUGPIN_SIMPLESHADING;
	if ( strcmp( value, "ShowNormals" ) == 0 || strcmp( value, "DEBUGPIN_SHOWNORMALS" ) == 0 )
		return DEBUGPIN_SHOWNORMALS;
	if ( strcmp( value, "ShowMipMaps" ) == 0 || strcmp( value, "DEBUGPIN_SHOWMIPMAPS" ) == 0 )
		return DEBUGPIN_SHOWMIPMAPS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum DebugPin", value ) );
	return DEBUGPIN_SIMPLESHADING;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const DecalModePin value )
{
	switch( value )
	{
		case DECALMODEPIN_STANDARD:
			return "Standard";
		case DECALMODEPIN_DUALDEPTH:
			return "DualDepth";
		case DECALMODEPIN_ZDECODE:
			return "ZDecode";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum DecalModePin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DecalModePin StringToEnum_DecalModePin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (DecalModePin)(NStr::ToInt( value ));
	if ( strcmp( value, "Standard" ) == 0 || strcmp( value, "DECALMODEPIN_STANDARD" ) == 0 )
		return DECALMODEPIN_STANDARD;
	if ( strcmp( value, "DualDepth" ) == 0 || strcmp( value, "DECALMODEPIN_DUALDEPTH" ) == 0 )
		return DECALMODEPIN_DUALDEPTH;
	if ( strcmp( value, "ZDecode" ) == 0 || strcmp( value, "DECALMODEPIN_ZDECODE" ) == 0 )
		return DECALMODEPIN_ZDECODE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum DecalModePin", value ) );
	return DECALMODEPIN_STANDARD;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const DiffuseAlphaMixPin value )
{
	switch( value )
	{
		case DIFFUSEALPHAMIXPIN_ALPHAMIXTEX1:
			return "AlphaMixTex1";
		case DIFFUSEALPHAMIXPIN_ALPHAMIXADDSMOOTH:
			return "AlphaMixAddSmooth";
		case DIFFUSEALPHAMIXPIN_ALPHAMIXMUL:
			return "AlphaMixMul";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum DiffuseAlphaMixPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DiffuseAlphaMixPin StringToEnum_DiffuseAlphaMixPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (DiffuseAlphaMixPin)(NStr::ToInt( value ));
	if ( strcmp( value, "AlphaMixTex1" ) == 0 || strcmp( value, "DIFFUSEALPHAMIXPIN_ALPHAMIXTEX1" ) == 0 )
		return DIFFUSEALPHAMIXPIN_ALPHAMIXTEX1;
	if ( strcmp( value, "AlphaMixAddSmooth" ) == 0 || strcmp( value, "DIFFUSEALPHAMIXPIN_ALPHAMIXADDSMOOTH" ) == 0 )
		return DIFFUSEALPHAMIXPIN_ALPHAMIXADDSMOOTH;
	if ( strcmp( value, "AlphaMixMul" ) == 0 || strcmp( value, "DIFFUSEALPHAMIXPIN_ALPHAMIXMUL" ) == 0 )
		return DIFFUSEALPHAMIXPIN_ALPHAMIXMUL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum DiffuseAlphaMixPin", value ) );
	return DIFFUSEALPHAMIXPIN_ALPHAMIXTEX1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const DiffuseColorMixPin value )
{
	switch( value )
	{
		case DIFFUSECOLORMIXPIN_COLORMIXADD:
			return "ColorMixAdd";
		case DIFFUSECOLORMIXPIN_COLORMIXADDWITHALPHA:
			return "ColorMixAddWithAlpha";
		case DIFFUSECOLORMIXPIN_COLORMIXLERP:
			return "ColorMixLerp";
		case DIFFUSECOLORMIXPIN_COLORMIXMUL:
			return "ColorMixMul";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum DiffuseColorMixPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DiffuseColorMixPin StringToEnum_DiffuseColorMixPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (DiffuseColorMixPin)(NStr::ToInt( value ));
	if ( strcmp( value, "ColorMixAdd" ) == 0 || strcmp( value, "DIFFUSECOLORMIXPIN_COLORMIXADD" ) == 0 )
		return DIFFUSECOLORMIXPIN_COLORMIXADD;
	if ( strcmp( value, "ColorMixAddWithAlpha" ) == 0 || strcmp( value, "DIFFUSECOLORMIXPIN_COLORMIXADDWITHALPHA" ) == 0 )
		return DIFFUSECOLORMIXPIN_COLORMIXADDWITHALPHA;
	if ( strcmp( value, "ColorMixLerp" ) == 0 || strcmp( value, "DIFFUSECOLORMIXPIN_COLORMIXLERP" ) == 0 )
		return DIFFUSECOLORMIXPIN_COLORMIXLERP;
	if ( strcmp( value, "ColorMixMul" ) == 0 || strcmp( value, "DIFFUSECOLORMIXPIN_COLORMIXMUL" ) == 0 )
		return DIFFUSECOLORMIXPIN_COLORMIXMUL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum DiffuseColorMixPin", value ) );
	return DIFFUSECOLORMIXPIN_COLORMIXADD;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const DiffuseMapCountPin value )
{
	switch( value )
	{
		case DIFFUSEMAPCOUNTPIN_NODIFFUSEMAP:
			return "NoDiffuseMap";
		case DIFFUSEMAPCOUNTPIN_BASEDIFFUSEMAP:
			return "BaseDiffuseMap";
		case DIFFUSEMAPCOUNTPIN_BOTHDIFFUSEMAPS:
			return "BothDiffuseMaps";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum DiffuseMapCountPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DiffuseMapCountPin StringToEnum_DiffuseMapCountPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (DiffuseMapCountPin)(NStr::ToInt( value ));
	if ( strcmp( value, "NoDiffuseMap" ) == 0 || strcmp( value, "DIFFUSEMAPCOUNTPIN_NODIFFUSEMAP" ) == 0 )
		return DIFFUSEMAPCOUNTPIN_NODIFFUSEMAP;
	if ( strcmp( value, "BaseDiffuseMap" ) == 0 || strcmp( value, "DIFFUSEMAPCOUNTPIN_BASEDIFFUSEMAP" ) == 0 )
		return DIFFUSEMAPCOUNTPIN_BASEDIFFUSEMAP;
	if ( strcmp( value, "BothDiffuseMaps" ) == 0 || strcmp( value, "DIFFUSEMAPCOUNTPIN_BOTHDIFFUSEMAPS" ) == 0 )
		return DIFFUSEMAPCOUNTPIN_BOTHDIFFUSEMAPS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum DiffuseMapCountPin", value ) );
	return DIFFUSEMAPCOUNTPIN_NODIFFUSEMAP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const DistortionPin value )
{
	switch( value )
	{
		case DISTORTIONPIN_DISTORTNONE:
			return "DistortNone";
		case DISTORTIONPIN_DISTORTMAP:
			return "DistortMap";
		case DISTORTIONPIN_DISTORTNOISE:
			return "DistortNoise";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum DistortionPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const DistortionPin StringToEnum_DistortionPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (DistortionPin)(NStr::ToInt( value ));
	if ( strcmp( value, "DistortNone" ) == 0 || strcmp( value, "DISTORTIONPIN_DISTORTNONE" ) == 0 )
		return DISTORTIONPIN_DISTORTNONE;
	if ( strcmp( value, "DistortMap" ) == 0 || strcmp( value, "DISTORTIONPIN_DISTORTMAP" ) == 0 )
		return DISTORTIONPIN_DISTORTMAP;
	if ( strcmp( value, "DistortNoise" ) == 0 || strcmp( value, "DISTORTIONPIN_DISTORTNOISE" ) == 0 )
		return DISTORTIONPIN_DISTORTNOISE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum DistortionPin", value ) );
	return DISTORTIONPIN_DISTORTNONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EEmissivePin value )
{
	switch( value )
	{
		case EMISSIVEPIN_EMISSIVEOFF:
			return "EmissiveOff";
		case EMISSIVEPIN_EMISSIVEFROMALPHA:
			return "EmissiveFromAlpha";
		case EMISSIVEPIN_EMISSIVEFROMSPECULAR:
			return "EmissiveFromSpecular";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EEmissivePin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EEmissivePin StringToEnum_EEmissivePin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EEmissivePin)(NStr::ToInt( value ));
	if ( strcmp( value, "EmissiveOff" ) == 0 || strcmp( value, "EMISSIVEPIN_EMISSIVEOFF" ) == 0 )
		return EMISSIVEPIN_EMISSIVEOFF;
	if ( strcmp( value, "EmissiveFromAlpha" ) == 0 || strcmp( value, "EMISSIVEPIN_EMISSIVEFROMALPHA" ) == 0 )
		return EMISSIVEPIN_EMISSIVEFROMALPHA;
	if ( strcmp( value, "EmissiveFromSpecular" ) == 0 || strcmp( value, "EMISSIVEPIN_EMISSIVEFROMSPECULAR" ) == 0 )
		return EMISSIVEPIN_EMISSIVEFROMSPECULAR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EEmissivePin", value ) );
	return EMISSIVEPIN_EMISSIVEOFF;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ELightEnvironment value )
{
	switch( value )
	{
		case LIGHTENVIRONMENT_DAY:
			return "Day";
		case LIGHTENVIRONMENT_NIGHT:
			return "Night";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ELightEnvironment", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ELightEnvironment StringToEnum_ELightEnvironment( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ELightEnvironment)(NStr::ToInt( value ));
	if ( strcmp( value, "Day" ) == 0 || strcmp( value, "LIGHTENVIRONMENT_DAY" ) == 0 )
		return LIGHTENVIRONMENT_DAY;
	if ( strcmp( value, "Night" ) == 0 || strcmp( value, "LIGHTENVIRONMENT_NIGHT" ) == 0 )
		return LIGHTENVIRONMENT_NIGHT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ELightEnvironment", value ) );
	return LIGHTENVIRONMENT_DAY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EPixelFormat value )
{
	switch( value )
	{
		case PIXELFORMAT_RGBA:
			return "RGBA";
		case PIXELFORMAT_DXT1:
			return "DXT1";
		case PIXELFORMAT_DXT5:
			return "DXT5";
		case PIXELFORMAT_L8:
			return "L8";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EPixelFormat", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EPixelFormat StringToEnum_EPixelFormat( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EPixelFormat)(NStr::ToInt( value ));
	if ( strcmp( value, "RGBA" ) == 0 || strcmp( value, "PIXELFORMAT_RGBA" ) == 0 )
		return PIXELFORMAT_RGBA;
	if ( strcmp( value, "DXT1" ) == 0 || strcmp( value, "PIXELFORMAT_DXT1" ) == 0 )
		return PIXELFORMAT_DXT1;
	if ( strcmp( value, "DXT5" ) == 0 || strcmp( value, "PIXELFORMAT_DXT5" ) == 0 )
		return PIXELFORMAT_DXT5;
	if ( strcmp( value, "L8" ) == 0 || strcmp( value, "PIXELFORMAT_L8" ) == 0 )
		return PIXELFORMAT_L8;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EPixelFormat", value ) );
	return PIXELFORMAT_RGBA;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EUIImageDrawMode value )
{
	switch( value )
	{
		case UIIMAGEDRAWMODE_NORMAL:
			return "Normal";
		case UIIMAGEDRAWMODE_CENTER:
			return "Center";
		case UIIMAGEDRAWMODE_STRETCH:
			return "Stretch";
		case UIIMAGEDRAWMODE_TILE:
			return "Tile";
		case UIIMAGEDRAWMODE_STRETCHEDTILE:
			return "StretchedTile";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EUIImageDrawMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EUIImageDrawMode StringToEnum_EUIImageDrawMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EUIImageDrawMode)(NStr::ToInt( value ));
	if ( strcmp( value, "Normal" ) == 0 || strcmp( value, "UIIMAGEDRAWMODE_NORMAL" ) == 0 )
		return UIIMAGEDRAWMODE_NORMAL;
	if ( strcmp( value, "Center" ) == 0 || strcmp( value, "UIIMAGEDRAWMODE_CENTER" ) == 0 )
		return UIIMAGEDRAWMODE_CENTER;
	if ( strcmp( value, "Stretch" ) == 0 || strcmp( value, "UIIMAGEDRAWMODE_STRETCH" ) == 0 )
		return UIIMAGEDRAWMODE_STRETCH;
	if ( strcmp( value, "Tile" ) == 0 || strcmp( value, "UIIMAGEDRAWMODE_TILE" ) == 0 )
		return UIIMAGEDRAWMODE_TILE;
	if ( strcmp( value, "StretchedTile" ) == 0 || strcmp( value, "UIIMAGEDRAWMODE_STRETCHEDTILE" ) == 0 )
		return UIIMAGEDRAWMODE_STRETCHEDTILE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EUIImageDrawMode", value ) );
	return UIIMAGEDRAWMODE_NORMAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const FillMode value )
{
	switch( value )
	{
		case FILLMODE_POINT:
			return "POINT";
		case FILLMODE_WIREFRAME:
			return "WIREFRAME";
		case FILLMODE_SOLID:
			return "SOLID";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum FillMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const FillMode StringToEnum_FillMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (FillMode)(NStr::ToInt( value ));
	if ( strcmp( value, "POINT" ) == 0 || strcmp( value, "FILLMODE_POINT" ) == 0 )
		return FILLMODE_POINT;
	if ( strcmp( value, "WIREFRAME" ) == 0 || strcmp( value, "FILLMODE_WIREFRAME" ) == 0 )
		return FILLMODE_WIREFRAME;
	if ( strcmp( value, "SOLID" ) == 0 || strcmp( value, "FILLMODE_SOLID" ) == 0 )
		return FILLMODE_SOLID;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum FillMode", value ) );
	return FILLMODE_POINT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const FlashBlendModePin value )
{
	switch( value )
	{
		case FLASHBLENDMODEPIN__NORMAL:
			return "_NORMAL";
		case FLASHBLENDMODEPIN_LAYER:
			return "LAYER";
		case FLASHBLENDMODEPIN_MULTIPLY:
			return "MULTIPLY";
		case FLASHBLENDMODEPIN_SCREEN:
			return "SCREEN";
		case FLASHBLENDMODEPIN_LIGHTEN:
			return "LIGHTEN";
		case FLASHBLENDMODEPIN_DARKEN:
			return "DARKEN";
		case FLASHBLENDMODEPIN__DIFFERENCE:
			return "_DIFFERENCE";
		case FLASHBLENDMODEPIN_ADD:
			return "ADD";
		case FLASHBLENDMODEPIN_SUBTRACT:
			return "SUBTRACT";
		case FLASHBLENDMODEPIN_INVERT:
			return "INVERT";
		case FLASHBLENDMODEPIN_ALPHA:
			return "ALPHA";
		case FLASHBLENDMODEPIN_ERASE:
			return "ERASE";
		case FLASHBLENDMODEPIN_OVERLAY:
			return "OVERLAY";
		case FLASHBLENDMODEPIN_HARDLIGHT:
			return "HARDLIGHT";
		case FLASHBLENDMODEPIN_SHADER:
			return "SHADER";
		case FLASHBLENDMODEPIN_COPY_BACKGRUOND:
			return "COPY_BACKGRUOND";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum FlashBlendModePin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const FlashBlendModePin StringToEnum_FlashBlendModePin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (FlashBlendModePin)(NStr::ToInt( value ));
	if ( strcmp( value, "_NORMAL" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN__NORMAL" ) == 0 )
		return FLASHBLENDMODEPIN__NORMAL;
	if ( strcmp( value, "LAYER" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_LAYER" ) == 0 )
		return FLASHBLENDMODEPIN_LAYER;
	if ( strcmp( value, "MULTIPLY" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_MULTIPLY" ) == 0 )
		return FLASHBLENDMODEPIN_MULTIPLY;
	if ( strcmp( value, "SCREEN" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_SCREEN" ) == 0 )
		return FLASHBLENDMODEPIN_SCREEN;
	if ( strcmp( value, "LIGHTEN" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_LIGHTEN" ) == 0 )
		return FLASHBLENDMODEPIN_LIGHTEN;
	if ( strcmp( value, "DARKEN" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_DARKEN" ) == 0 )
		return FLASHBLENDMODEPIN_DARKEN;
	if ( strcmp( value, "_DIFFERENCE" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN__DIFFERENCE" ) == 0 )
		return FLASHBLENDMODEPIN__DIFFERENCE;
	if ( strcmp( value, "ADD" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_ADD" ) == 0 )
		return FLASHBLENDMODEPIN_ADD;
	if ( strcmp( value, "SUBTRACT" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_SUBTRACT" ) == 0 )
		return FLASHBLENDMODEPIN_SUBTRACT;
	if ( strcmp( value, "INVERT" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_INVERT" ) == 0 )
		return FLASHBLENDMODEPIN_INVERT;
	if ( strcmp( value, "ALPHA" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_ALPHA" ) == 0 )
		return FLASHBLENDMODEPIN_ALPHA;
	if ( strcmp( value, "ERASE" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_ERASE" ) == 0 )
		return FLASHBLENDMODEPIN_ERASE;
	if ( strcmp( value, "OVERLAY" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_OVERLAY" ) == 0 )
		return FLASHBLENDMODEPIN_OVERLAY;
	if ( strcmp( value, "HARDLIGHT" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_HARDLIGHT" ) == 0 )
		return FLASHBLENDMODEPIN_HARDLIGHT;
	if ( strcmp( value, "SHADER" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_SHADER" ) == 0 )
		return FLASHBLENDMODEPIN_SHADER;
	if ( strcmp( value, "COPY_BACKGRUOND" ) == 0 || strcmp( value, "FLASHBLENDMODEPIN_COPY_BACKGRUOND" ) == 0 )
		return FLASHBLENDMODEPIN_COPY_BACKGRUOND;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum FlashBlendModePin", value ) );
	return FLASHBLENDMODEPIN__NORMAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const LightingPin value )
{
	switch( value )
	{
		case LIGHTINGPIN_LIGHTINGSH:
			return "LightingSH";
		case LIGHTINGPIN_LIGHTINGINSTANCEDSH:
			return "LightingInstancedSH";
		case LIGHTINGPIN_LIGHTINGBAKED:
			return "LightingBaked";
		case LIGHTINGPIN_LIGHTINGDYNAMIC:
			return "LightingDynamic";
		case LIGHTINGPIN_LIGHTINGDYNAMIC1POINT:
			return "LightingDynamic1Point";
		case LIGHTINGPIN_LIGHTINGDYNAMIC2POINT:
			return "LightingDynamic2Point";
		case LIGHTINGPIN_LIGHTINGDYNAMIC3POINT:
			return "LightingDynamic3Point";
		case LIGHTINGPIN_LIGHTINGDYNAMIC4POINT:
			return "LightingDynamic4Point";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum LightingPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const LightingPin StringToEnum_LightingPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (LightingPin)(NStr::ToInt( value ));
	if ( strcmp( value, "LightingSH" ) == 0 || strcmp( value, "LIGHTINGPIN_LIGHTINGSH" ) == 0 )
		return LIGHTINGPIN_LIGHTINGSH;
	if ( strcmp( value, "LightingInstancedSH" ) == 0 || strcmp( value, "LIGHTINGPIN_LIGHTINGINSTANCEDSH" ) == 0 )
		return LIGHTINGPIN_LIGHTINGINSTANCEDSH;
	if ( strcmp( value, "LightingBaked" ) == 0 || strcmp( value, "LIGHTINGPIN_LIGHTINGBAKED" ) == 0 )
		return LIGHTINGPIN_LIGHTINGBAKED;
	if ( strcmp( value, "LightingDynamic" ) == 0 || strcmp( value, "LIGHTINGPIN_LIGHTINGDYNAMIC" ) == 0 )
		return LIGHTINGPIN_LIGHTINGDYNAMIC;
	if ( strcmp( value, "LightingDynamic1Point" ) == 0 || strcmp( value, "LIGHTINGPIN_LIGHTINGDYNAMIC1POINT" ) == 0 )
		return LIGHTINGPIN_LIGHTINGDYNAMIC1POINT;
	if ( strcmp( value, "LightingDynamic2Point" ) == 0 || strcmp( value, "LIGHTINGPIN_LIGHTINGDYNAMIC2POINT" ) == 0 )
		return LIGHTINGPIN_LIGHTINGDYNAMIC2POINT;
	if ( strcmp( value, "LightingDynamic3Point" ) == 0 || strcmp( value, "LIGHTINGPIN_LIGHTINGDYNAMIC3POINT" ) == 0 )
		return LIGHTINGPIN_LIGHTINGDYNAMIC3POINT;
	if ( strcmp( value, "LightingDynamic4Point" ) == 0 || strcmp( value, "LIGHTINGPIN_LIGHTINGDYNAMIC4POINT" ) == 0 )
		return LIGHTINGPIN_LIGHTINGDYNAMIC4POINT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum LightingPin", value ) );
	return LIGHTINGPIN_LIGHTINGSH;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const LightModePin value )
{
	switch( value )
	{
		case LIGHTMODEPIN_DIFFUSE:
			return "Diffuse";
		case LIGHTMODEPIN_DIFFUSEOPACITY:
			return "DiffuseOpacity";
		case LIGHTMODEPIN_DIFFUSESPECULAR:
			return "DiffuseSpecular";
		case LIGHTMODEPIN_DIFFUSESPECULAROPACITY:
			return "DiffuseSpecularOpacity";
		case LIGHTMODEPIN_DIFFUSEEMISSIVE:
			return "DiffuseEmissive";
		case LIGHTMODEPIN_DIFFUSESPECULAREMISSIVE:
			return "DiffuseSpecularEmissive";
		case LIGHTMODEPIN_DIFFUSESPECULARTOEMISSIVE:
			return "DiffuseSpecularToEmissive";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum LightModePin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const LightModePin StringToEnum_LightModePin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (LightModePin)(NStr::ToInt( value ));
	if ( strcmp( value, "Diffuse" ) == 0 || strcmp( value, "LIGHTMODEPIN_DIFFUSE" ) == 0 )
		return LIGHTMODEPIN_DIFFUSE;
	if ( strcmp( value, "DiffuseOpacity" ) == 0 || strcmp( value, "LIGHTMODEPIN_DIFFUSEOPACITY" ) == 0 )
		return LIGHTMODEPIN_DIFFUSEOPACITY;
	if ( strcmp( value, "DiffuseSpecular" ) == 0 || strcmp( value, "LIGHTMODEPIN_DIFFUSESPECULAR" ) == 0 )
		return LIGHTMODEPIN_DIFFUSESPECULAR;
	if ( strcmp( value, "DiffuseSpecularOpacity" ) == 0 || strcmp( value, "LIGHTMODEPIN_DIFFUSESPECULAROPACITY" ) == 0 )
		return LIGHTMODEPIN_DIFFUSESPECULAROPACITY;
	if ( strcmp( value, "DiffuseEmissive" ) == 0 || strcmp( value, "LIGHTMODEPIN_DIFFUSEEMISSIVE" ) == 0 )
		return LIGHTMODEPIN_DIFFUSEEMISSIVE;
	if ( strcmp( value, "DiffuseSpecularEmissive" ) == 0 || strcmp( value, "LIGHTMODEPIN_DIFFUSESPECULAREMISSIVE" ) == 0 )
		return LIGHTMODEPIN_DIFFUSESPECULAREMISSIVE;
	if ( strcmp( value, "DiffuseSpecularToEmissive" ) == 0 || strcmp( value, "LIGHTMODEPIN_DIFFUSESPECULARTOEMISSIVE" ) == 0 )
		return LIGHTMODEPIN_DIFFUSESPECULARTOEMISSIVE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum LightModePin", value ) );
	return LIGHTMODEPIN_DIFFUSE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MADPin value )
{
	switch( value )
	{
		case MADPIN_NOMAD:
			return "NoMAD";
		case MADPIN_MADENABLED:
			return "MADEnabled";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum MADPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MADPin StringToEnum_MADPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MADPin)(NStr::ToInt( value ));
	if ( strcmp( value, "NoMAD" ) == 0 || strcmp( value, "MADPIN_NOMAD" ) == 0 )
		return MADPIN_NOMAD;
	if ( strcmp( value, "MADEnabled" ) == 0 || strcmp( value, "MADPIN_MADENABLED" ) == 0 )
		return MADPIN_MADENABLED;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MADPin", value ) );
	return MADPIN_NOMAD;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MagFilterType value )
{
	switch( value )
	{
		case MAGFILTERTYPE_POINT:
			return "Point";
		case MAGFILTERTYPE_LINEAR:
			return "Linear";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum MagFilterType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MagFilterType StringToEnum_MagFilterType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MagFilterType)(NStr::ToInt( value ));
	if ( strcmp( value, "Point" ) == 0 || strcmp( value, "MAGFILTERTYPE_POINT" ) == 0 )
		return MAGFILTERTYPE_POINT;
	if ( strcmp( value, "Linear" ) == 0 || strcmp( value, "MAGFILTERTYPE_LINEAR" ) == 0 )
		return MAGFILTERTYPE_LINEAR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MagFilterType", value ) );
	return MAGFILTERTYPE_POINT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MaskingTypePin value )
{
	switch( value )
	{
		case MASKINGTYPEPIN_NOMASKING:
			return "NoMasking";
		case MASKINGTYPEPIN_MASKING:
			return "Masking";
		case MASKINGTYPEPIN_INVERTMASKING:
			return "InvertMasking";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum MaskingTypePin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MaskingTypePin StringToEnum_MaskingTypePin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MaskingTypePin)(NStr::ToInt( value ));
	if ( strcmp( value, "NoMasking" ) == 0 || strcmp( value, "MASKINGTYPEPIN_NOMASKING" ) == 0 )
		return MASKINGTYPEPIN_NOMASKING;
	if ( strcmp( value, "Masking" ) == 0 || strcmp( value, "MASKINGTYPEPIN_MASKING" ) == 0 )
		return MASKINGTYPEPIN_MASKING;
	if ( strcmp( value, "InvertMasking" ) == 0 || strcmp( value, "MASKINGTYPEPIN_INVERTMASKING" ) == 0 )
		return MASKINGTYPEPIN_INVERTMASKING;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MaskingTypePin", value ) );
	return MASKINGTYPEPIN_NOMASKING;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MaterialFlags value )
{
	switch( value )
	{
		case MATERIALFLAGS_NONE:
			return "None";
		case MATERIALFLAGS_SHADOWCASTER:
			return "ShadowCaster";
		case MATERIALFLAGS_SHADOWRECEIVER:
			return "ShadowReceiver";
		case MATERIALFLAGS_REFLECTINWATER:
			return "ReflectInWater";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MaterialFlags StringToEnum_MaterialFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MaterialFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "MATERIALFLAGS_NONE" ) == 0 )
		return MATERIALFLAGS_NONE;
	if ( strcmp( value, "ShadowCaster" ) == 0 || strcmp( value, "MATERIALFLAGS_SHADOWCASTER" ) == 0 )
		return MATERIALFLAGS_SHADOWCASTER;
	if ( strcmp( value, "ShadowReceiver" ) == 0 || strcmp( value, "MATERIALFLAGS_SHADOWRECEIVER" ) == 0 )
		return MATERIALFLAGS_SHADOWRECEIVER;
	if ( strcmp( value, "ReflectInWater" ) == 0 || strcmp( value, "MATERIALFLAGS_REFLECTINWATER" ) == 0 )
		return MATERIALFLAGS_REFLECTINWATER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MaterialFlags", value ) );
	return MATERIALFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MaterialOldFlags value )
{
	switch( value )
	{
		case MATERIALOLDFLAGS_NONE:
			return "None";
		case MATERIALOLDFLAGS_REQUIREALPHABLENDING:
			return "RequireAlphaBlending";
		case MATERIALOLDFLAGS_CASTSSHADOWS:
			return "CastsShadows";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MaterialOldFlags StringToEnum_MaterialOldFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MaterialOldFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "MATERIALOLDFLAGS_NONE" ) == 0 )
		return MATERIALOLDFLAGS_NONE;
	if ( strcmp( value, "RequireAlphaBlending" ) == 0 || strcmp( value, "MATERIALOLDFLAGS_REQUIREALPHABLENDING" ) == 0 )
		return MATERIALOLDFLAGS_REQUIREALPHABLENDING;
	if ( strcmp( value, "CastsShadows" ) == 0 || strcmp( value, "MATERIALOLDFLAGS_CASTSSHADOWS" ) == 0 )
		return MATERIALOLDFLAGS_CASTSSHADOWS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MaterialOldFlags", value ) );
	return MATERIALOLDFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MaterialPriority value )
{
	switch( value )
	{
		case MATERIALPRIORITY_NONE:
			return "None";
		case MATERIALPRIORITY_MESHESOPAQUE:
			return "MeshesOpaque";
		case MATERIALPRIORITY_MESHESOPAQUELATE:
			return "MeshesOpaqueLate";
		case MATERIALPRIORITY_MESHESSILHOUETTE:
			return "MeshesSilhouette";
		case MATERIALPRIORITY_TERRAINLAYER0:
			return "TerrainLayer0";
		case MATERIALPRIORITY_TERRAINLAYER1:
			return "TerrainLayer1";
		case MATERIALPRIORITY_ROADS:
			return "Roads";
		case MATERIALPRIORITY_TERRAINOBJECTS:
			return "TerrainObjects";
		case MATERIALPRIORITY_TERRAINDOMINATIONDECALS:
			return "TerrainDominationDecals";
		case MATERIALPRIORITY_TERRAINDECALS:
			return "TerrainDecals";
		case MATERIALPRIORITY_WATERDECALS:
			return "WaterDecals";
		case MATERIALPRIORITY_TRANSPARENTSPECIAL:
			return "TransparentSpecial";
		case MATERIALPRIORITY_TRANSPARENT:
			return "Transparent";
		case MATERIALPRIORITY_DISTORTION:
			return "Distortion";
		case MATERIALPRIORITY_HEIGHTFOG:
			return "Heightfog";
		case MATERIALPRIORITY_SKY:
			return "Sky";
		case MATERIALPRIORITY_COUNT:
			return "Count";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum MaterialPriority", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MaterialPriority StringToEnum_MaterialPriority( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MaterialPriority)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "MATERIALPRIORITY_NONE" ) == 0 )
		return MATERIALPRIORITY_NONE;
	if ( strcmp( value, "MeshesOpaque" ) == 0 || strcmp( value, "MATERIALPRIORITY_MESHESOPAQUE" ) == 0 )
		return MATERIALPRIORITY_MESHESOPAQUE;
	if ( strcmp( value, "MeshesOpaqueLate" ) == 0 || strcmp( value, "MATERIALPRIORITY_MESHESOPAQUELATE" ) == 0 )
		return MATERIALPRIORITY_MESHESOPAQUELATE;
	if ( strcmp( value, "MeshesSilhouette" ) == 0 || strcmp( value, "MATERIALPRIORITY_MESHESSILHOUETTE" ) == 0 )
		return MATERIALPRIORITY_MESHESSILHOUETTE;
	if ( strcmp( value, "TerrainLayer0" ) == 0 || strcmp( value, "MATERIALPRIORITY_TERRAINLAYER0" ) == 0 )
		return MATERIALPRIORITY_TERRAINLAYER0;
	if ( strcmp( value, "TerrainLayer1" ) == 0 || strcmp( value, "MATERIALPRIORITY_TERRAINLAYER1" ) == 0 )
		return MATERIALPRIORITY_TERRAINLAYER1;
	if ( strcmp( value, "Roads" ) == 0 || strcmp( value, "MATERIALPRIORITY_ROADS" ) == 0 )
		return MATERIALPRIORITY_ROADS;
	if ( strcmp( value, "TerrainObjects" ) == 0 || strcmp( value, "MATERIALPRIORITY_TERRAINOBJECTS" ) == 0 )
		return MATERIALPRIORITY_TERRAINOBJECTS;
	if ( strcmp( value, "TerrainDominationDecals" ) == 0 || strcmp( value, "MATERIALPRIORITY_TERRAINDOMINATIONDECALS" ) == 0 )
		return MATERIALPRIORITY_TERRAINDOMINATIONDECALS;
	if ( strcmp( value, "TerrainDecals" ) == 0 || strcmp( value, "MATERIALPRIORITY_TERRAINDECALS" ) == 0 )
		return MATERIALPRIORITY_TERRAINDECALS;
	if ( strcmp( value, "WaterDecals" ) == 0 || strcmp( value, "MATERIALPRIORITY_WATERDECALS" ) == 0 )
		return MATERIALPRIORITY_WATERDECALS;
	if ( strcmp( value, "TransparentSpecial" ) == 0 || strcmp( value, "MATERIALPRIORITY_TRANSPARENTSPECIAL" ) == 0 )
		return MATERIALPRIORITY_TRANSPARENTSPECIAL;
	if ( strcmp( value, "Transparent" ) == 0 || strcmp( value, "MATERIALPRIORITY_TRANSPARENT" ) == 0 )
		return MATERIALPRIORITY_TRANSPARENT;
	if ( strcmp( value, "Distortion" ) == 0 || strcmp( value, "MATERIALPRIORITY_DISTORTION" ) == 0 )
		return MATERIALPRIORITY_DISTORTION;
	if ( strcmp( value, "Heightfog" ) == 0 || strcmp( value, "MATERIALPRIORITY_HEIGHTFOG" ) == 0 )
		return MATERIALPRIORITY_HEIGHTFOG;
	if ( strcmp( value, "Sky" ) == 0 || strcmp( value, "MATERIALPRIORITY_SKY" ) == 0 )
		return MATERIALPRIORITY_SKY;
	if ( strcmp( value, "Count" ) == 0 || strcmp( value, "MATERIALPRIORITY_COUNT" ) == 0 )
		return MATERIALPRIORITY_COUNT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MaterialPriority", value ) );
	return MATERIALPRIORITY_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MinFilterType value )
{
	switch( value )
	{
		case MINFILTERTYPE_POINT:
			return "Point";
		case MINFILTERTYPE_LINEAR:
			return "Linear";
		case MINFILTERTYPE_ANISOTROPIC1X:
			return "Anisotropic1x";
		case MINFILTERTYPE_ANISOTROPIC2X:
			return "Anisotropic2x";
		case MINFILTERTYPE_ANISOTROPIC3X:
			return "Anisotropic3x";
		case MINFILTERTYPE_ANISOTROPIC4X:
			return "Anisotropic4x";
		case MINFILTERTYPE_ANISOTROPIC5X:
			return "Anisotropic5x";
		case MINFILTERTYPE_ANISOTROPIC6X:
			return "Anisotropic6x";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum MinFilterType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MinFilterType StringToEnum_MinFilterType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MinFilterType)(NStr::ToInt( value ));
	if ( strcmp( value, "Point" ) == 0 || strcmp( value, "MINFILTERTYPE_POINT" ) == 0 )
		return MINFILTERTYPE_POINT;
	if ( strcmp( value, "Linear" ) == 0 || strcmp( value, "MINFILTERTYPE_LINEAR" ) == 0 )
		return MINFILTERTYPE_LINEAR;
	if ( strcmp( value, "Anisotropic1x" ) == 0 || strcmp( value, "MINFILTERTYPE_ANISOTROPIC1X" ) == 0 )
		return MINFILTERTYPE_ANISOTROPIC1X;
	if ( strcmp( value, "Anisotropic2x" ) == 0 || strcmp( value, "MINFILTERTYPE_ANISOTROPIC2X" ) == 0 )
		return MINFILTERTYPE_ANISOTROPIC2X;
	if ( strcmp( value, "Anisotropic3x" ) == 0 || strcmp( value, "MINFILTERTYPE_ANISOTROPIC3X" ) == 0 )
		return MINFILTERTYPE_ANISOTROPIC3X;
	if ( strcmp( value, "Anisotropic4x" ) == 0 || strcmp( value, "MINFILTERTYPE_ANISOTROPIC4X" ) == 0 )
		return MINFILTERTYPE_ANISOTROPIC4X;
	if ( strcmp( value, "Anisotropic5x" ) == 0 || strcmp( value, "MINFILTERTYPE_ANISOTROPIC5X" ) == 0 )
		return MINFILTERTYPE_ANISOTROPIC5X;
	if ( strcmp( value, "Anisotropic6x" ) == 0 || strcmp( value, "MINFILTERTYPE_ANISOTROPIC6X" ) == 0 )
		return MINFILTERTYPE_ANISOTROPIC6X;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MinFilterType", value ) );
	return MINFILTERTYPE_POINT;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MipFilterType value )
{
	switch( value )
	{
		case MIPFILTERTYPE_NONE:
			return "None";
		case MIPFILTERTYPE_POINT:
			return "Point";
		case MIPFILTERTYPE_LINEAR:
			return "Linear";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum MipFilterType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MipFilterType StringToEnum_MipFilterType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MipFilterType)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "MIPFILTERTYPE_NONE" ) == 0 )
		return MIPFILTERTYPE_NONE;
	if ( strcmp( value, "Point" ) == 0 || strcmp( value, "MIPFILTERTYPE_POINT" ) == 0 )
		return MIPFILTERTYPE_POINT;
	if ( strcmp( value, "Linear" ) == 0 || strcmp( value, "MIPFILTERTYPE_LINEAR" ) == 0 )
		return MIPFILTERTYPE_LINEAR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MipFilterType", value ) );
	return MIPFILTERTYPE_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const OnOffState value )
{
	switch( value )
	{
		case ONOFFSTATE_OFF:
			return "Off";
		case ONOFFSTATE_ON:
			return "On";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum OnOffState", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const OnOffState StringToEnum_OnOffState( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (OnOffState)(NStr::ToInt( value ));
	if ( strcmp( value, "Off" ) == 0 || strcmp( value, "ONOFFSTATE_OFF" ) == 0 )
		return ONOFFSTATE_OFF;
	if ( strcmp( value, "On" ) == 0 || strcmp( value, "ONOFFSTATE_ON" ) == 0 )
		return ONOFFSTATE_ON;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum OnOffState", value ) );
	return ONOFFSTATE_OFF;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const OpacityAndEmissiveModePin value )
{
	switch( value )
	{
		case OPACITYANDEMISSIVEMODEPIN_SIMPLE:
			return "Simple";
		case OPACITYANDEMISSIVEMODEPIN_ADDITIVEOPACITY:
			return "AdditiveOpacity";
		case OPACITYANDEMISSIVEMODEPIN_BLENDOPACITY:
			return "BlendOpacity";
		case OPACITYANDEMISSIVEMODEPIN_EMISSIVE:
			return "Emissive";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum OpacityAndEmissiveModePin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const OpacityAndEmissiveModePin StringToEnum_OpacityAndEmissiveModePin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (OpacityAndEmissiveModePin)(NStr::ToInt( value ));
	if ( strcmp( value, "Simple" ) == 0 || strcmp( value, "OPACITYANDEMISSIVEMODEPIN_SIMPLE" ) == 0 )
		return OPACITYANDEMISSIVEMODEPIN_SIMPLE;
	if ( strcmp( value, "AdditiveOpacity" ) == 0 || strcmp( value, "OPACITYANDEMISSIVEMODEPIN_ADDITIVEOPACITY" ) == 0 )
		return OPACITYANDEMISSIVEMODEPIN_ADDITIVEOPACITY;
	if ( strcmp( value, "BlendOpacity" ) == 0 || strcmp( value, "OPACITYANDEMISSIVEMODEPIN_BLENDOPACITY" ) == 0 )
		return OPACITYANDEMISSIVEMODEPIN_BLENDOPACITY;
	if ( strcmp( value, "Emissive" ) == 0 || strcmp( value, "OPACITYANDEMISSIVEMODEPIN_EMISSIVE" ) == 0 )
		return OPACITYANDEMISSIVEMODEPIN_EMISSIVE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum OpacityAndEmissiveModePin", value ) );
	return OPACITYANDEMISSIVEMODEPIN_SIMPLE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const OpacityPin value )
{
	switch( value )
	{
		case OPACITYPIN_OPAQUE:
			return "Opaque";
		case OPACITYPIN_ALPHAOPACITY:
			return "AlphaOpacity";
		case OPACITYPIN_COLOROPACITY:
			return "ColorOpacity";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum OpacityPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const OpacityPin StringToEnum_OpacityPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (OpacityPin)(NStr::ToInt( value ));
	if ( strcmp( value, "Opaque" ) == 0 || strcmp( value, "OPACITYPIN_OPAQUE" ) == 0 )
		return OPACITYPIN_OPAQUE;
	if ( strcmp( value, "AlphaOpacity" ) == 0 || strcmp( value, "OPACITYPIN_ALPHAOPACITY" ) == 0 )
		return OPACITYPIN_ALPHAOPACITY;
	if ( strcmp( value, "ColorOpacity" ) == 0 || strcmp( value, "OPACITYPIN_COLOROPACITY" ) == 0 )
		return OPACITYPIN_COLOROPACITY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum OpacityPin", value ) );
	return OPACITYPIN_OPAQUE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const OrientTypePin value )
{
	switch( value )
	{
		case ORIENTTYPEPIN_NONETYPE:
			return "NoneType";
		case ORIENTTYPEPIN_AXISTYPE:
			return "AxisType";
		case ORIENTTYPEPIN_SPEEDTYPE:
			return "SpeedType";
		case ORIENTTYPEPIN_PLANETYPE:
			return "PlaneType";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum OrientTypePin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const OrientTypePin StringToEnum_OrientTypePin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (OrientTypePin)(NStr::ToInt( value ));
	if ( strcmp( value, "NoneType" ) == 0 || strcmp( value, "ORIENTTYPEPIN_NONETYPE" ) == 0 )
		return ORIENTTYPEPIN_NONETYPE;
	if ( strcmp( value, "AxisType" ) == 0 || strcmp( value, "ORIENTTYPEPIN_AXISTYPE" ) == 0 )
		return ORIENTTYPEPIN_AXISTYPE;
	if ( strcmp( value, "SpeedType" ) == 0 || strcmp( value, "ORIENTTYPEPIN_SPEEDTYPE" ) == 0 )
		return ORIENTTYPEPIN_SPEEDTYPE;
	if ( strcmp( value, "PlaneType" ) == 0 || strcmp( value, "ORIENTTYPEPIN_PLANETYPE" ) == 0 )
		return ORIENTTYPEPIN_PLANETYPE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum OrientTypePin", value ) );
	return ORIENTTYPEPIN_NONETYPE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const PackedMasksNumberPin value )
{
	switch( value )
	{
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS1:
			return "PackedMasks1";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS2:
			return "PackedMasks2";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS3:
			return "PackedMasks3";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS4:
			return "PackedMasks4";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS5:
			return "PackedMasks5";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS6:
			return "PackedMasks6";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS7:
			return "PackedMasks7";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS8:
			return "PackedMasks8";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS9:
			return "PackedMasks9";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS10:
			return "PackedMasks10";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS11:
			return "PackedMasks11";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS12:
			return "PackedMasks12";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS13:
			return "PackedMasks13";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS14:
			return "PackedMasks14";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS15:
			return "PackedMasks15";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS16:
			return "PackedMasks16";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS17:
			return "PackedMasks17";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS18:
			return "PackedMasks18";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS19:
			return "PackedMasks19";
		case PACKEDMASKSNUMBERPIN_PACKEDMASKS20:
			return "PackedMasks20";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum PackedMasksNumberPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PackedMasksNumberPin StringToEnum_PackedMasksNumberPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (PackedMasksNumberPin)(NStr::ToInt( value ));
	if ( strcmp( value, "PackedMasks1" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS1" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS1;
	if ( strcmp( value, "PackedMasks2" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS2" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS2;
	if ( strcmp( value, "PackedMasks3" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS3" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS3;
	if ( strcmp( value, "PackedMasks4" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS4" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS4;
	if ( strcmp( value, "PackedMasks5" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS5" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS5;
	if ( strcmp( value, "PackedMasks6" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS6" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS6;
	if ( strcmp( value, "PackedMasks7" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS7" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS7;
	if ( strcmp( value, "PackedMasks8" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS8" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS8;
	if ( strcmp( value, "PackedMasks9" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS9" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS9;
	if ( strcmp( value, "PackedMasks10" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS10" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS10;
	if ( strcmp( value, "PackedMasks11" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS11" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS11;
	if ( strcmp( value, "PackedMasks12" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS12" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS12;
	if ( strcmp( value, "PackedMasks13" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS13" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS13;
	if ( strcmp( value, "PackedMasks14" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS14" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS14;
	if ( strcmp( value, "PackedMasks15" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS15" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS15;
	if ( strcmp( value, "PackedMasks16" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS16" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS16;
	if ( strcmp( value, "PackedMasks17" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS17" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS17;
	if ( strcmp( value, "PackedMasks18" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS18" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS18;
	if ( strcmp( value, "PackedMasks19" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS19" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS19;
	if ( strcmp( value, "PackedMasks20" ) == 0 || strcmp( value, "PACKEDMASKSNUMBERPIN_PACKEDMASKS20" ) == 0 )
		return PACKEDMASKSNUMBERPIN_PACKEDMASKS20;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum PackedMasksNumberPin", value ) );
	return PACKEDMASKSNUMBERPIN_PACKEDMASKS1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const PaintMaterialModePin value )
{
	switch( value )
	{
		case PAINTMATERIALMODEPIN_EMPTY:
			return "Empty";
		case PAINTMATERIALMODEPIN_INWORK:
			return "InWork";
		case PAINTMATERIALMODEPIN_FINAL:
			return "Final";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum PaintMaterialModePin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PaintMaterialModePin StringToEnum_PaintMaterialModePin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (PaintMaterialModePin)(NStr::ToInt( value ));
	if ( strcmp( value, "Empty" ) == 0 || strcmp( value, "PAINTMATERIALMODEPIN_EMPTY" ) == 0 )
		return PAINTMATERIALMODEPIN_EMPTY;
	if ( strcmp( value, "InWork" ) == 0 || strcmp( value, "PAINTMATERIALMODEPIN_INWORK" ) == 0 )
		return PAINTMATERIALMODEPIN_INWORK;
	if ( strcmp( value, "Final" ) == 0 || strcmp( value, "PAINTMATERIALMODEPIN_FINAL" ) == 0 )
		return PAINTMATERIALMODEPIN_FINAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum PaintMaterialModePin", value ) );
	return PAINTMATERIALMODEPIN_EMPTY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const PointLightFlags value )
{
	switch( value )
	{
		case POINTLIGHTFLAGS_NONE:
			return "None";
		case POINTLIGHTFLAGS_DAY:
			return "Day";
		case POINTLIGHTFLAGS_NIGHT:
			return "Night";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const PointLightFlags StringToEnum_PointLightFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (PointLightFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "POINTLIGHTFLAGS_NONE" ) == 0 )
		return POINTLIGHTFLAGS_NONE;
	if ( strcmp( value, "Day" ) == 0 || strcmp( value, "POINTLIGHTFLAGS_DAY" ) == 0 )
		return POINTLIGHTFLAGS_DAY;
	if ( strcmp( value, "Night" ) == 0 || strcmp( value, "POINTLIGHTFLAGS_NIGHT" ) == 0 )
		return POINTLIGHTFLAGS_NIGHT;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum PointLightFlags", value ) );
	return POINTLIGHTFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ReflectivityPin value )
{
	switch( value )
	{
		case REFLECTIVITYPIN_REFLECTIVITYOFF:
			return "ReflectivityOff";
		case REFLECTIVITYPIN_REFLECTIVITYSIMPLE:
			return "ReflectivitySimple";
		case REFLECTIVITYPIN_REFLECTIVITYFROMNORMALMAP:
			return "ReflectivityFromNormalMap";
		case REFLECTIVITYPIN_REFLECTIVITYFROMSPECULARMAP:
			return "ReflectivityFromSpecularMap";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ReflectivityPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ReflectivityPin StringToEnum_ReflectivityPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ReflectivityPin)(NStr::ToInt( value ));
	if ( strcmp( value, "ReflectivityOff" ) == 0 || strcmp( value, "REFLECTIVITYPIN_REFLECTIVITYOFF" ) == 0 )
		return REFLECTIVITYPIN_REFLECTIVITYOFF;
	if ( strcmp( value, "ReflectivitySimple" ) == 0 || strcmp( value, "REFLECTIVITYPIN_REFLECTIVITYSIMPLE" ) == 0 )
		return REFLECTIVITYPIN_REFLECTIVITYSIMPLE;
	if ( strcmp( value, "ReflectivityFromNormalMap" ) == 0 || strcmp( value, "REFLECTIVITYPIN_REFLECTIVITYFROMNORMALMAP" ) == 0 )
		return REFLECTIVITYPIN_REFLECTIVITYFROMNORMALMAP;
	if ( strcmp( value, "ReflectivityFromSpecularMap" ) == 0 || strcmp( value, "REFLECTIVITYPIN_REFLECTIVITYFROMSPECULARMAP" ) == 0 )
		return REFLECTIVITYPIN_REFLECTIVITYFROMSPECULARMAP;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ReflectivityPin", value ) );
	return REFLECTIVITYPIN_REFLECTIVITYOFF;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const RenderModePin value )
{
	switch( value )
	{
		case RENDERMODEPIN_RENDERNORMAL:
			return "RenderNormal";
		case RENDERMODEPIN_RENDERTOSHADOW:
			return "RenderToShadow";
		case RENDERMODEPIN_RENDERSHAPEONLY:
			return "RenderShapeOnly";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum RenderModePin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const RenderModePin StringToEnum_RenderModePin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (RenderModePin)(NStr::ToInt( value ));
	if ( strcmp( value, "RenderNormal" ) == 0 || strcmp( value, "RENDERMODEPIN_RENDERNORMAL" ) == 0 )
		return RENDERMODEPIN_RENDERNORMAL;
	if ( strcmp( value, "RenderToShadow" ) == 0 || strcmp( value, "RENDERMODEPIN_RENDERTOSHADOW" ) == 0 )
		return RENDERMODEPIN_RENDERTOSHADOW;
	if ( strcmp( value, "RenderShapeOnly" ) == 0 || strcmp( value, "RENDERMODEPIN_RENDERSHAPEONLY" ) == 0 )
		return RENDERMODEPIN_RENDERSHAPEONLY;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum RenderModePin", value ) );
	return RENDERMODEPIN_RENDERNORMAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ShaderQualityPin value )
{
	switch( value )
	{
		case SHADERQUALITYPIN_BEST:
			return "Best";
		case SHADERQUALITYPIN_FAST:
			return "Fast";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ShaderQualityPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ShaderQualityPin StringToEnum_ShaderQualityPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ShaderQualityPin)(NStr::ToInt( value ));
	if ( strcmp( value, "Best" ) == 0 || strcmp( value, "SHADERQUALITYPIN_BEST" ) == 0 )
		return SHADERQUALITYPIN_BEST;
	if ( strcmp( value, "Fast" ) == 0 || strcmp( value, "SHADERQUALITYPIN_FAST" ) == 0 )
		return SHADERQUALITYPIN_FAST;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ShaderQualityPin", value ) );
	return SHADERQUALITYPIN_BEST;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ShadowBlendMode value )
{
	switch( value )
	{
		case SHADOWBLENDMODE_LERPBYALPHA:
			return "LerpByAlpha";
		case SHADOWBLENDMODE_MULCOLOR:
			return "MulColor";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ShadowBlendMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ShadowBlendMode StringToEnum_ShadowBlendMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ShadowBlendMode)(NStr::ToInt( value ));
	if ( strcmp( value, "LerpByAlpha" ) == 0 || strcmp( value, "SHADOWBLENDMODE_LERPBYALPHA" ) == 0 )
		return SHADOWBLENDMODE_LERPBYALPHA;
	if ( strcmp( value, "MulColor" ) == 0 || strcmp( value, "SHADOWBLENDMODE_MULCOLOR" ) == 0 )
		return SHADOWBLENDMODE_MULCOLOR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ShadowBlendMode", value ) );
	return SHADOWBLENDMODE_LERPBYALPHA;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const ShadowMode value )
{
	switch( value )
	{
		case SHADOWMODE_PCF:
			return "PCF";
		case SHADOWMODE_SAESM:
			return "SAESM";
		case SHADOWMODE_ANISOESM:
			return "AnisoESM";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum ShadowMode", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const ShadowMode StringToEnum_ShadowMode( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (ShadowMode)(NStr::ToInt( value ));
	if ( strcmp( value, "PCF" ) == 0 || strcmp( value, "SHADOWMODE_PCF" ) == 0 )
		return SHADOWMODE_PCF;
	if ( strcmp( value, "SAESM" ) == 0 || strcmp( value, "SHADOWMODE_SAESM" ) == 0 )
		return SHADOWMODE_SAESM;
	if ( strcmp( value, "AnisoESM" ) == 0 || strcmp( value, "SHADOWMODE_ANISOESM" ) == 0 )
		return SHADOWMODE_ANISOESM;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum ShadowMode", value ) );
	return SHADOWMODE_PCF;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const TerrainUVSetPin value )
{
	switch( value )
	{
		case TERRAINUVSETPIN_GLOBAL:
			return "Global";
		case TERRAINUVSETPIN_LOCAL:
			return "Local";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum TerrainUVSetPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const TerrainUVSetPin StringToEnum_TerrainUVSetPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (TerrainUVSetPin)(NStr::ToInt( value ));
	if ( strcmp( value, "Global" ) == 0 || strcmp( value, "TERRAINUVSETPIN_GLOBAL" ) == 0 )
		return TERRAINUVSETPIN_GLOBAL;
	if ( strcmp( value, "Local" ) == 0 || strcmp( value, "TERRAINUVSETPIN_LOCAL" ) == 0 )
		return TERRAINUVSETPIN_LOCAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum TerrainUVSetPin", value ) );
	return TERRAINUVSETPIN_GLOBAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const TextureAddressType value )
{
	switch( value )
	{
		case TEXTUREADDRESSTYPE_WRAP:
			return "Wrap";
		case TEXTUREADDRESSTYPE_CLAMP:
			return "Clamp";
		case TEXTUREADDRESSTYPE_MIRROR:
			return "Mirror";
		case TEXTUREADDRESSTYPE_BORDER:
			return "Border";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum TextureAddressType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const TextureAddressType StringToEnum_TextureAddressType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (TextureAddressType)(NStr::ToInt( value ));
	if ( strcmp( value, "Wrap" ) == 0 || strcmp( value, "TEXTUREADDRESSTYPE_WRAP" ) == 0 )
		return TEXTUREADDRESSTYPE_WRAP;
	if ( strcmp( value, "Clamp" ) == 0 || strcmp( value, "TEXTUREADDRESSTYPE_CLAMP" ) == 0 )
		return TEXTUREADDRESSTYPE_CLAMP;
	if ( strcmp( value, "Mirror" ) == 0 || strcmp( value, "TEXTUREADDRESSTYPE_MIRROR" ) == 0 )
		return TEXTUREADDRESSTYPE_MIRROR;
	if ( strcmp( value, "Border" ) == 0 || strcmp( value, "TEXTUREADDRESSTYPE_BORDER" ) == 0 )
		return TEXTUREADDRESSTYPE_BORDER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum TextureAddressType", value ) );
	return TEXTUREADDRESSTYPE_WRAP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const TextureColorizePin value )
{
	switch( value )
	{
		case TEXTURECOLORIZEPIN_NOCOLOR:
			return "NoColor";
		case TEXTURECOLORIZEPIN_ADDCOLOREDALPHA:
			return "AddColoredAlpha";
		case TEXTURECOLORIZEPIN_MULCOLORBYALPHA:
			return "MulColorByAlpha";
		case TEXTURECOLORIZEPIN_COLORFOREVERYCHANEL:
			return "ColorForEveryChanel";
		case TEXTURECOLORIZEPIN_TESTCOLOR:
			return "TestColor";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum TextureColorizePin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const TextureColorizePin StringToEnum_TextureColorizePin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (TextureColorizePin)(NStr::ToInt( value ));
	if ( strcmp( value, "NoColor" ) == 0 || strcmp( value, "TEXTURECOLORIZEPIN_NOCOLOR" ) == 0 )
		return TEXTURECOLORIZEPIN_NOCOLOR;
	if ( strcmp( value, "AddColoredAlpha" ) == 0 || strcmp( value, "TEXTURECOLORIZEPIN_ADDCOLOREDALPHA" ) == 0 )
		return TEXTURECOLORIZEPIN_ADDCOLOREDALPHA;
	if ( strcmp( value, "MulColorByAlpha" ) == 0 || strcmp( value, "TEXTURECOLORIZEPIN_MULCOLORBYALPHA" ) == 0 )
		return TEXTURECOLORIZEPIN_MULCOLORBYALPHA;
	if ( strcmp( value, "ColorForEveryChanel" ) == 0 || strcmp( value, "TEXTURECOLORIZEPIN_COLORFOREVERYCHANEL" ) == 0 )
		return TEXTURECOLORIZEPIN_COLORFOREVERYCHANEL;
	if ( strcmp( value, "TestColor" ) == 0 || strcmp( value, "TEXTURECOLORIZEPIN_TESTCOLOR" ) == 0 )
		return TEXTURECOLORIZEPIN_TESTCOLOR;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum TextureColorizePin", value ) );
	return TEXTURECOLORIZEPIN_NOCOLOR;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const TextureCountPin value )
{
	switch( value )
	{
		case TEXTURECOUNTPIN_COUNT1:
			return "Count1";
		case TEXTURECOUNTPIN_COUNT2:
			return "Count2";
		case TEXTURECOUNTPIN_COUNT3:
			return "Count3";
		case TEXTURECOUNTPIN_COUNT4:
			return "Count4";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum TextureCountPin", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const TextureCountPin StringToEnum_TextureCountPin( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (TextureCountPin)(NStr::ToInt( value ));
	if ( strcmp( value, "Count1" ) == 0 || strcmp( value, "TEXTURECOUNTPIN_COUNT1" ) == 0 )
		return TEXTURECOUNTPIN_COUNT1;
	if ( strcmp( value, "Count2" ) == 0 || strcmp( value, "TEXTURECOUNTPIN_COUNT2" ) == 0 )
		return TEXTURECOUNTPIN_COUNT2;
	if ( strcmp( value, "Count3" ) == 0 || strcmp( value, "TEXTURECOUNTPIN_COUNT3" ) == 0 )
		return TEXTURECOUNTPIN_COUNT3;
	if ( strcmp( value, "Count4" ) == 0 || strcmp( value, "TEXTURECOUNTPIN_COUNT4" ) == 0 )
		return TEXTURECOUNTPIN_COUNT4;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum TextureCountPin", value ) );
	return TEXTURECOUNTPIN_COUNT1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const WarFogType value )
{
	switch( value )
	{
		case WARFOGTYPE_SINGLELAYER:
			return "SingleLayer";
		case WARFOGTYPE_DUALLAYER:
			return "DualLayer";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum WarFogType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const WarFogType StringToEnum_WarFogType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (WarFogType)(NStr::ToInt( value ));
	if ( strcmp( value, "SingleLayer" ) == 0 || strcmp( value, "WARFOGTYPE_SINGLELAYER" ) == 0 )
		return WARFOGTYPE_SINGLELAYER;
	if ( strcmp( value, "DualLayer" ) == 0 || strcmp( value, "WARFOGTYPE_DUALLAYER" ) == 0 )
		return WARFOGTYPE_DUALLAYER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum WarFogType", value ) );
	return WARFOGTYPE_SINGLELAYER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BakedLighting::BakedLighting() :
		dynObjLightingGridResX( 5 )
	, dynObjLightingGridResY( 5 )
	, renderedEnvironmentEffect( 0.5f )
	, renderedEnvironmentRange( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BakedLighting::operator&( IBinSaver &saver )
{
	saver.Add( 2, &dynObjLightingGridResX );
	saver.Add( 3, &dynObjLightingGridResY );
	saver.Add( 4, &renderedEnvironmentEffect );
	saver.Add( 5, &renderedEnvironmentRange );
	saver.Add( 6, &dynObjBakedLighting );
	saver.Add( 7, &vertexColorsFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BakedLighting::operator&( IXmlSaver &saver )
{
	saver.Add( "dynObjLightingGridResX", &dynObjLightingGridResX );
	saver.Add( "dynObjLightingGridResY", &dynObjLightingGridResY );
	saver.Add( "renderedEnvironmentEffect", &renderedEnvironmentEffect );
	saver.Add( "renderedEnvironmentRange", &renderedEnvironmentRange );
	saver.Add( "dynObjBakedLighting", &dynObjBakedLighting );
	saver.Add( "vertexColorsFileName", &vertexColorsFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Direction::Direction() :
		Yaw( 0.0f )
	, Pitch( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Direction::operator&( IBinSaver &saver )
{
	saver.Add( 2, &Yaw );
	saver.Add( 3, &Pitch );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Direction::operator&( IXmlSaver &saver )
{
	saver.Add( "Yaw", &Yaw );
	saver.Add( "Pitch", &Pitch );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MaterialParameterDescriptor::MaterialParameterDescriptor() :
		presentDefineIndex( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MaterialParameterDescriptor::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &presentDefineIndex );
	saver.Add( 4, &presentValues );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MaterialParameterDescriptor::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "presentDefineIndex", &presentDefineIndex );
	saver.Add( "presentValues", &presentValues );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointLightInfo::PointLightInfo() :
		attenuation( ATTENUATION_NONE )
	, range( 0.0f )
	, diffuseIntensity( 1.0f )
	, flags( POINTLIGHTFLAGS_DAY )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PointLightInfo::operator&( IBinSaver &saver )
{
	saver.Add( 2, &attenuation );
	saver.Add( 3, &location );
	saver.Add( 4, &range );
	saver.Add( 5, &diffuse );
	saver.Add( 6, &diffuseIntensity );
	saver.Add( 7, &flags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PointLightInfo::operator&( IXmlSaver &saver )
{
	saver.Add( "attenuation", &attenuation );
	saver.Add( "location", &location );
	saver.Add( "range", &range );
	saver.Add( "diffuse", &diffuse );
	saver.Add( "diffuseIntensity", &diffuseIntensity );
	saver.Add( "flags", &flags );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RenderState::RenderState() :
		blendMode( BLENDMODE_OFF )
	, alphaTest( ONOFFSTATE_OFF )
	, alphaTestRef( 127 )
	, culling( ONOFFSTATE_ON )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RenderState::operator&( IBinSaver &saver )
{
	saver.Add( 2, &blendMode );
	saver.Add( 3, &alphaTest );
	saver.Add( 4, &alphaTestRef );
	saver.Add( 5, &culling );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RenderState::operator&( IXmlSaver &saver )
{
	saver.Add( "blendMode", &blendMode );
	saver.Add( "alphaTest", &alphaTest );
	saver.Add( "alphaTestRef", &alphaTestRef );
	saver.Add( "culling", &culling );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SamplerState::SamplerState() :
		minFilter( MINFILTERTYPE_LINEAR )
	, magFilter( MAGFILTERTYPE_LINEAR )
	, mipFilter( MIPFILTERTYPE_LINEAR )
	, addressU( TEXTUREADDRESSTYPE_WRAP )
	, addressV( TEXTUREADDRESSTYPE_WRAP )
	, addressW( TEXTUREADDRESSTYPE_WRAP )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SamplerState::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minFilter );
	saver.Add( 3, &magFilter );
	saver.Add( 4, &mipFilter );
	saver.Add( 5, &addressU );
	saver.Add( 6, &addressV );
	saver.Add( 7, &addressW );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SamplerState::operator&( IXmlSaver &saver )
{
	saver.Add( "minFilter", &minFilter );
	saver.Add( "magFilter", &magFilter );
	saver.Add( "mipFilter", &mipFilter );
	saver.Add( "addressU", &addressU );
	saver.Add( "addressV", &addressV );
	saver.Add( "addressW", &addressW );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SamplerState::IsEqual( const SamplerState& _samplerState ) const
{
	return minFilter == _samplerState.minFilter
		&& magFilter == _samplerState.magFilter
		&& mipFilter == _samplerState.mipFilter
		&& addressU == _samplerState.addressU
		&& addressV == _samplerState.addressV
		&& addressW == _samplerState.addressW;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SamplerCube::SamplerCube()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SamplerCube::operator&( IBinSaver &saver )
{
	saver.Add( 2, &samplerState );
	saver.Add( 3, &texture );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SamplerCube::operator&( IXmlSaver &saver )
{
	saver.Add( "samplerState", &samplerState );
	saver.Add( "texture", &texture );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SamplerEx::SamplerEx()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SamplerEx::operator&( IBinSaver &saver )
{
	saver.Add( 2, &samplerState );
	saver.Add( 3, &texture );
	saver.Add( 4, &Multiplier );
	saver.Add( 5, &Add );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SamplerEx::operator&( IXmlSaver &saver )
{
	saver.Add( "samplerState", &samplerState );
	saver.Add( "texture", &texture );
	saver.Add( "Multiplier", &Multiplier );
	saver.Add( "Add", &Add );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sampler::Sampler()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Sampler::operator&( IBinSaver &saver )
{
	saver.Add( 2, &samplerState );
	saver.Add( 3, &texture );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Sampler::operator&( IXmlSaver &saver )
{
	saver.Add( "samplerState", &samplerState );
	saver.Add( "texture", &texture );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShaderDefineDescriptor::ShaderDefineDescriptor() :
		minValue( 0 )
	, maxValue( 0 )
	, CanChangedInEditor( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShaderDefineDescriptor::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &minValue );
	saver.Add( 4, &maxValue );
	saver.Add( 5, &CanChangedInEditor );
	saver.Add( 6, &definesValuesDescriptions );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShaderDefineDescriptor::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "minValue", &minValue );
	saver.Add( "maxValue", &maxValue );
	saver.Add( "CanChangedInEditor", &CanChangedInEditor );
	saver.Add( "definesValuesDescriptions", &definesValuesDescriptions );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShaderDefinesDescriptorsTable::ShaderDefinesDescriptorsTable()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShaderDefinesDescriptorsTable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &definesDescriptors );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShaderDefinesDescriptorsTable::operator&( IXmlSaver &saver )
{
	saver.Add( "definesDescriptors", &definesDescriptors );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Material::Material() :
		SubPriority( 0 )
	, renderFlags( MATERIALFLAGS_SHADOWRECEIVER )
	, ignoreRenderState( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Material::operator&( IBinSaver &saver )
{
	saver.Add( 2, &SubPriority );
	saver.Add( 3, &caption );
	saver.Add( 4, &renderFlags );
	saver.Add( 5, &ignoreRenderState );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Material::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Material* parentPtr = (Material*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Material::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "SubPriority", &SubPriority );
	saver.Add( "caption", &caption );
	saver.Add( "renderFlags", &renderFlags );
	saver.Add( "ignoreRenderState", &ignoreRenderState );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Material::Assign( const Material& _material )
{
	SubPriority = _material.SubPriority;
	caption = _material.caption;
	renderFlags = _material.renderFlags;
	ignoreRenderState = _material.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AOEMaterial::AOEMaterial() :
		aspectRatio( 2.0f )
	, CustomizedGeometryPinValue( BOOLEANPIN_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AOEMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &primaryColor );
	saver.Add( 5, &secondaryColor );
	saver.Add( 6, &aspectRatio );
	saver.Add( 7, &CustomizedGeometryPinValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AOEMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AOEMaterial* parentPtr = (AOEMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AOEMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "primaryColor", &primaryColor );
	saver.Add( "secondaryColor", &secondaryColor );
	saver.Add( "aspectRatio", &aspectRatio );
	saver.Add( "CustomizedGeometryPinValue", &CustomizedGeometryPinValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AOEMaterial::Assign( const AOEMaterial& _aOEMaterial )
{
	renderState.blendMode = _aOEMaterial.renderState.blendMode;
	renderState.alphaTest = _aOEMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _aOEMaterial.renderState.alphaTestRef;
	renderState.culling = _aOEMaterial.renderState.culling;
	DiffuseMap.samplerState.minFilter = _aOEMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _aOEMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _aOEMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _aOEMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _aOEMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _aOEMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _aOEMaterial.DiffuseMap.texture;
	primaryColor = _aOEMaterial.primaryColor;
	secondaryColor = _aOEMaterial.secondaryColor;
	aspectRatio = _aOEMaterial.aspectRatio;
	CustomizedGeometryPinValue = _aOEMaterial.CustomizedGeometryPinValue;
	SubPriority = _aOEMaterial.SubPriority;
	caption = _aOEMaterial.caption;
	renderFlags = _aOEMaterial.renderFlags;
	ignoreRenderState = _aOEMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseUIMaterial::BaseUIMaterial() :
		horizontalDrawMode( UIIMAGEDRAWMODE_STRETCH )
	, verticalDrawMode( UIIMAGEDRAWMODE_STRETCH )
	, UseAutosize( BOOLEANPIN_PRESENT )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseUIMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &horizontalDrawMode );
	saver.Add( 3, &verticalDrawMode );
	saver.Add( 4, &textureShift );
	saver.Add( 5, &imageSize );
	saver.Add( 6, &imageTileShift );
	saver.Add( 7, &imageTileSize );
	saver.Add( 8, &UseAutosize );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BaseUIMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BaseUIMaterial* parentPtr = (BaseUIMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseUIMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "horizontalDrawMode", &horizontalDrawMode );
	saver.Add( "verticalDrawMode", &verticalDrawMode );
	saver.Add( "textureShift", &textureShift );
	saver.Add( "imageSize", &imageSize );
	saver.Add( "imageTileShift", &imageTileShift );
	saver.Add( "imageTileSize", &imageTileSize );
	saver.Add( "UseAutosize", &UseAutosize );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseUIMaterial::Assign( const BaseUIMaterial& _baseUIMaterial )
{
	horizontalDrawMode = _baseUIMaterial.horizontalDrawMode;
	verticalDrawMode = _baseUIMaterial.verticalDrawMode;
	textureShift = _baseUIMaterial.textureShift;
	imageSize = _baseUIMaterial.imageSize;
	imageTileShift = _baseUIMaterial.imageTileShift;
	imageTileSize = _baseUIMaterial.imageTileSize;
	UseAutosize = _baseUIMaterial.UseAutosize;
	SubPriority = _baseUIMaterial.SubPriority;
	caption = _baseUIMaterial.caption;
	renderFlags = _baseUIMaterial.renderFlags;
	ignoreRenderState = _baseUIMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BasicFXMaterial::BasicFXMaterial() :
		SkeletalMeshPinValue( BOOLEANPIN_NONE )
	, OpacityAndEmissiveModePinValue( OPACITYANDEMISSIVEMODEPIN_SIMPLE )
	, MultiplyVertexColorPinValue( BOOLEANPIN_NONE )
	, DistortionPinValue( DISTORTIONPIN_DISTORTNONE )
	, emissive( 0.0f )
	, distortion( 1.0f )
	, masterOpacity( 1.0f )
	, isBlendModeOverrided( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicFXMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &DiffuseMul );
	saver.Add( 5, &DiffuseAdd );
	saver.Add( 6, &SkeletalMeshPinValue );
	saver.Add( 7, &OpacityAndEmissiveModePinValue );
	saver.Add( 8, &MultiplyVertexColorPinValue );
	saver.Add( 9, &DistortionPinValue );
	saver.Add( 10, &emissive );
	saver.Add( 11, &distortion );
	saver.Add( 12, &masterOpacity );
	saver.Add( 13, &isBlendModeOverrided );
	saver.Add( 14, &opacity );
	saver.Add( 15, &uOffset );
	saver.Add( 16, &vOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicFXMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BasicFXMaterial* parentPtr = (BasicFXMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicFXMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "DiffuseMul", &DiffuseMul );
	saver.Add( "DiffuseAdd", &DiffuseAdd );
	saver.Add( "SkeletalMeshPinValue", &SkeletalMeshPinValue );
	saver.Add( "OpacityAndEmissiveModePinValue", &OpacityAndEmissiveModePinValue );
	saver.Add( "MultiplyVertexColorPinValue", &MultiplyVertexColorPinValue );
	saver.Add( "DistortionPinValue", &DistortionPinValue );
	saver.Add( "emissive", &emissive );
	saver.Add( "distortion", &distortion );
	saver.Add( "masterOpacity", &masterOpacity );
	saver.Add( "isBlendModeOverrided", &isBlendModeOverrided );
	saver.Add( "opacity", &opacity );
	saver.Add( "uOffset", &uOffset );
	saver.Add( "vOffset", &vOffset );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicFXMaterial::Assign( const BasicFXMaterial& _basicFXMaterial )
{
	renderState.blendMode = _basicFXMaterial.renderState.blendMode;
	renderState.alphaTest = _basicFXMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _basicFXMaterial.renderState.alphaTestRef;
	renderState.culling = _basicFXMaterial.renderState.culling;
	DiffuseMap.samplerState.minFilter = _basicFXMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _basicFXMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _basicFXMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _basicFXMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _basicFXMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _basicFXMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _basicFXMaterial.DiffuseMap.texture;
	DiffuseMul = _basicFXMaterial.DiffuseMul;
	DiffuseAdd = _basicFXMaterial.DiffuseAdd;
	SkeletalMeshPinValue = _basicFXMaterial.SkeletalMeshPinValue;
	OpacityAndEmissiveModePinValue = _basicFXMaterial.OpacityAndEmissiveModePinValue;
	MultiplyVertexColorPinValue = _basicFXMaterial.MultiplyVertexColorPinValue;
	DistortionPinValue = _basicFXMaterial.DistortionPinValue;
	emissive = _basicFXMaterial.emissive;
	distortion = _basicFXMaterial.distortion;
	masterOpacity = _basicFXMaterial.masterOpacity;
	isBlendModeOverrided = _basicFXMaterial.isBlendModeOverrided;
	opacity = _basicFXMaterial.opacity;
	uOffset = _basicFXMaterial.uOffset;
	vOffset = _basicFXMaterial.vOffset;
	SubPriority = _basicFXMaterial.SubPriority;
	caption = _basicFXMaterial.caption;
	renderFlags = _basicFXMaterial.renderFlags;
	ignoreRenderState = _basicFXMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BasicMaskMaterial::BasicMaskMaterial() :
		opacity( 1.0f )
	, isBlendModeOverrided( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicMaskMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &Diffuse );
	saver.Add( 4, &Mask );
	saver.Add( 5, &opacity );
	saver.Add( 6, &isBlendModeOverrided );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicMaskMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BasicMaskMaterial* parentPtr = (BasicMaskMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicMaskMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "Diffuse", &Diffuse );
	saver.Add( "Mask", &Mask );
	saver.Add( "opacity", &opacity );
	saver.Add( "isBlendModeOverrided", &isBlendModeOverrided );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicMaskMaterial::Assign( const BasicMaskMaterial& _basicMaskMaterial )
{
	renderState.blendMode = _basicMaskMaterial.renderState.blendMode;
	renderState.alphaTest = _basicMaskMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _basicMaskMaterial.renderState.alphaTestRef;
	renderState.culling = _basicMaskMaterial.renderState.culling;
	Diffuse.samplerState.minFilter = _basicMaskMaterial.Diffuse.samplerState.minFilter;
	Diffuse.samplerState.magFilter = _basicMaskMaterial.Diffuse.samplerState.magFilter;
	Diffuse.samplerState.mipFilter = _basicMaskMaterial.Diffuse.samplerState.mipFilter;
	Diffuse.samplerState.addressU = _basicMaskMaterial.Diffuse.samplerState.addressU;
	Diffuse.samplerState.addressV = _basicMaskMaterial.Diffuse.samplerState.addressV;
	Diffuse.samplerState.addressW = _basicMaskMaterial.Diffuse.samplerState.addressW;
	Diffuse.texture = _basicMaskMaterial.Diffuse.texture;
	Mask.samplerState.minFilter = _basicMaskMaterial.Mask.samplerState.minFilter;
	Mask.samplerState.magFilter = _basicMaskMaterial.Mask.samplerState.magFilter;
	Mask.samplerState.mipFilter = _basicMaskMaterial.Mask.samplerState.mipFilter;
	Mask.samplerState.addressU = _basicMaskMaterial.Mask.samplerState.addressU;
	Mask.samplerState.addressV = _basicMaskMaterial.Mask.samplerState.addressV;
	Mask.samplerState.addressW = _basicMaskMaterial.Mask.samplerState.addressW;
	Mask.texture = _basicMaskMaterial.Mask.texture;
	opacity = _basicMaskMaterial.opacity;
	isBlendModeOverrided = _basicMaskMaterial.isBlendModeOverrided;
	SubPriority = _basicMaskMaterial.SubPriority;
	caption = _basicMaskMaterial.caption;
	renderFlags = _basicMaskMaterial.renderFlags;
	ignoreRenderState = _basicMaskMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BasicMaterial::BasicMaterial() :
		isBlendModeOverrided( 0 )
	, lightingIntencity( 1.0f )
	, NormalMapPinValue( BOOLEANPIN_NONE )
	, SpecularMapPinValue( BOOLEANPIN_NONE )
	, ReflectivityPinValue( REFLECTIVITYPIN_REFLECTIVITYOFF )
	, SkeletalMeshPinValue( BOOLEANPIN_NONE )
	, EmissivePinValue( EMISSIVEPIN_EMISSIVEOFF )
	, OpacityPinValue( BOOLEANPIN_NONE )
	, SpecularPinValue( BOOLEANPIN_NONE )
	, LightingPinValue( LIGHTINGPIN_LIGHTINGSH )
	, emissive( 0.0f )
	, opacity( 1.0f )
	, reflectivity( 1.0f )
	, specularPower( 0.0f )
	, specialTransparency( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &isBlendModeOverrided );
	saver.Add( 4, &diffuseColor );
	saver.Add( 5, &lightingIntencity );
	saver.Add( 6, &DiffuseMap );
	saver.Add( 7, &NormalMap );
	saver.Add( 8, &NormalMapPinValue );
	saver.Add( 9, &SpecularMap );
	saver.Add( 10, &SpecularMapPinValue );
	saver.Add( 11, &ReflectionMap );
	saver.Add( 12, &ReflectivityPinValue );
	saver.Add( 13, &outputMul );
	saver.Add( 14, &outputAdd );
	saver.Add( 15, &SkeletalMeshPinValue );
	saver.Add( 16, &EmissivePinValue );
	saver.Add( 17, &OpacityPinValue );
	saver.Add( 18, &SpecularPinValue );
	saver.Add( 19, &LightingPinValue );
	saver.Add( 20, &emissive );
	saver.Add( 21, &opacity );
	saver.Add( 22, &reflectivity );
	saver.Add( 23, &specularPower );
	saver.Add( 24, &specialTransparency );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int BasicMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			BasicMaterial* parentPtr = (BasicMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "isBlendModeOverrided", &isBlendModeOverrided );
	saver.Add( "diffuseColor", &diffuseColor );
	saver.Add( "lightingIntencity", &lightingIntencity );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "NormalMap", &NormalMap );
	saver.Add( "NormalMapPinValue", &NormalMapPinValue );
	saver.Add( "SpecularMap", &SpecularMap );
	saver.Add( "SpecularMapPinValue", &SpecularMapPinValue );
	saver.Add( "ReflectionMap", &ReflectionMap );
	saver.Add( "ReflectivityPinValue", &ReflectivityPinValue );
	saver.Add( "outputMul", &outputMul );
	saver.Add( "outputAdd", &outputAdd );
	saver.Add( "SkeletalMeshPinValue", &SkeletalMeshPinValue );
	saver.Add( "EmissivePinValue", &EmissivePinValue );
	saver.Add( "OpacityPinValue", &OpacityPinValue );
	saver.Add( "SpecularPinValue", &SpecularPinValue );
	saver.Add( "LightingPinValue", &LightingPinValue );
	saver.Add( "emissive", &emissive );
	saver.Add( "opacity", &opacity );
	saver.Add( "reflectivity", &reflectivity );
	saver.Add( "specularPower", &specularPower );
	saver.Add( "specialTransparency", &specialTransparency );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BasicMaterial::Assign( const BasicMaterial& _basicMaterial )
{
	renderState.blendMode = _basicMaterial.renderState.blendMode;
	renderState.alphaTest = _basicMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _basicMaterial.renderState.alphaTestRef;
	renderState.culling = _basicMaterial.renderState.culling;
	isBlendModeOverrided = _basicMaterial.isBlendModeOverrided;
	diffuseColor = _basicMaterial.diffuseColor;
	lightingIntencity = _basicMaterial.lightingIntencity;
	DiffuseMap.samplerState.minFilter = _basicMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _basicMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _basicMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _basicMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _basicMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _basicMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _basicMaterial.DiffuseMap.texture;
	NormalMap.samplerState.minFilter = _basicMaterial.NormalMap.samplerState.minFilter;
	NormalMap.samplerState.magFilter = _basicMaterial.NormalMap.samplerState.magFilter;
	NormalMap.samplerState.mipFilter = _basicMaterial.NormalMap.samplerState.mipFilter;
	NormalMap.samplerState.addressU = _basicMaterial.NormalMap.samplerState.addressU;
	NormalMap.samplerState.addressV = _basicMaterial.NormalMap.samplerState.addressV;
	NormalMap.samplerState.addressW = _basicMaterial.NormalMap.samplerState.addressW;
	NormalMap.texture = _basicMaterial.NormalMap.texture;
	NormalMapPinValue = _basicMaterial.NormalMapPinValue;
	SpecularMap.samplerState.minFilter = _basicMaterial.SpecularMap.samplerState.minFilter;
	SpecularMap.samplerState.magFilter = _basicMaterial.SpecularMap.samplerState.magFilter;
	SpecularMap.samplerState.mipFilter = _basicMaterial.SpecularMap.samplerState.mipFilter;
	SpecularMap.samplerState.addressU = _basicMaterial.SpecularMap.samplerState.addressU;
	SpecularMap.samplerState.addressV = _basicMaterial.SpecularMap.samplerState.addressV;
	SpecularMap.samplerState.addressW = _basicMaterial.SpecularMap.samplerState.addressW;
	SpecularMap.texture = _basicMaterial.SpecularMap.texture;
	SpecularMap.Multiplier = _basicMaterial.SpecularMap.Multiplier;
	SpecularMap.Add = _basicMaterial.SpecularMap.Add;
	SpecularMapPinValue = _basicMaterial.SpecularMapPinValue;
	ReflectionMap.samplerState.minFilter = _basicMaterial.ReflectionMap.samplerState.minFilter;
	ReflectionMap.samplerState.magFilter = _basicMaterial.ReflectionMap.samplerState.magFilter;
	ReflectionMap.samplerState.mipFilter = _basicMaterial.ReflectionMap.samplerState.mipFilter;
	ReflectionMap.samplerState.addressU = _basicMaterial.ReflectionMap.samplerState.addressU;
	ReflectionMap.samplerState.addressV = _basicMaterial.ReflectionMap.samplerState.addressV;
	ReflectionMap.samplerState.addressW = _basicMaterial.ReflectionMap.samplerState.addressW;
	ReflectionMap.texture = _basicMaterial.ReflectionMap.texture;
	ReflectivityPinValue = _basicMaterial.ReflectivityPinValue;
	outputMul = _basicMaterial.outputMul;
	outputAdd = _basicMaterial.outputAdd;
	SkeletalMeshPinValue = _basicMaterial.SkeletalMeshPinValue;
	EmissivePinValue = _basicMaterial.EmissivePinValue;
	OpacityPinValue = _basicMaterial.OpacityPinValue;
	SpecularPinValue = _basicMaterial.SpecularPinValue;
	LightingPinValue = _basicMaterial.LightingPinValue;
	emissive = _basicMaterial.emissive;
	opacity = _basicMaterial.opacity;
	reflectivity = _basicMaterial.reflectivity;
	specularPower = _basicMaterial.specularPower;
	specialTransparency = _basicMaterial.specialTransparency;
	SubPriority = _basicMaterial.SubPriority;
	caption = _basicMaterial.caption;
	renderFlags = _basicMaterial.renderFlags;
	ignoreRenderState = _basicMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CubeMap::CubeMap()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CubeMap::operator&( IBinSaver &saver )
{
	saver.Add( 2, &srcFileName_0 );
	saver.Add( 3, &srcFileName_1 );
	saver.Add( 4, &srcFileName_2 );
	saver.Add( 5, &srcFileName_3 );
	saver.Add( 6, &srcFileName_4 );
	saver.Add( 7, &srcFileName_5 );
	saver.Add( 8, &textureFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CubeMap::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			CubeMap* parentPtr = (CubeMap*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CubeMap::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "srcFileName_0", &srcFileName_0 );
	saver.Add( "srcFileName_1", &srcFileName_1 );
	saver.Add( "srcFileName_2", &srcFileName_2 );
	saver.Add( "srcFileName_3", &srcFileName_3 );
	saver.Add( "srcFileName_4", &srcFileName_4 );
	saver.Add( "srcFileName_5", &srcFileName_5 );
	saver.Add( "textureFileName", &textureFileName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CubeMap::Assign( const CubeMap& _cubeMap )
{
	srcFileName_0 = _cubeMap.srcFileName_0;
	srcFileName_1 = _cubeMap.srcFileName_1;
	srcFileName_2 = _cubeMap.srcFileName_2;
	srcFileName_3 = _cubeMap.srcFileName_3;
	srcFileName_4 = _cubeMap.srcFileName_4;
	srcFileName_5 = _cubeMap.srcFileName_5;
	textureFileName = _cubeMap.textureFileName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DebugMaterial::DebugMaterial() :
		DarkMapPinValue( BOOLEANPIN_NONE )
	, SkeletalMeshPinValue( BOOLEANPIN_NONE )
	, DebugPinValue( DEBUGPIN_SIMPLESHADING )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DebugMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &DarkMapPinValue );
	saver.Add( 3, &SkeletalMeshPinValue );
	saver.Add( 4, &DebugPinValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DebugMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DebugMaterial* parentPtr = (DebugMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DebugMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "DarkMapPinValue", &DarkMapPinValue );
	saver.Add( "SkeletalMeshPinValue", &SkeletalMeshPinValue );
	saver.Add( "DebugPinValue", &DebugPinValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DebugMaterial::Assign( const DebugMaterial& _debugMaterial )
{
	DarkMapPinValue = _debugMaterial.DarkMapPinValue;
	SkeletalMeshPinValue = _debugMaterial.SkeletalMeshPinValue;
	DebugPinValue = _debugMaterial.DebugPinValue;
	SubPriority = _debugMaterial.SubPriority;
	caption = _debugMaterial.caption;
	renderFlags = _debugMaterial.renderFlags;
	ignoreRenderState = _debugMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DecalMaterial::DecalMaterial() :
		radius( 5.0f )
	, AccessibilityPinValue( BOOLEANPIN_PRESENT )
	, OpacityAndEmissiveModePinValue( OPACITYANDEMISSIVEMODEPIN_SIMPLE )
	, DistortionPinValue( BOOLEANPIN_NONE )
	, DecalPlanePinValue( BOOLEANPIN_PRESENT )
	, distortion( 1.0f )
	, putOnWater( true )
	, isBlendModeOverrided( 0 )
	, masterOpacity( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DecalMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &DiffuseMul );
	saver.Add( 5, &DiffuseAdd );
	saver.Add( 6, &radius );
	saver.Add( 7, &AccessibilityPinValue );
	saver.Add( 8, &OpacityAndEmissiveModePinValue );
	saver.Add( 9, &DistortionPinValue );
	saver.Add( 10, &DecalPlanePinValue );
	saver.Add( 11, &distortion );
	saver.Add( 12, &putOnWater );
	saver.Add( 13, &isBlendModeOverrided );
	saver.Add( 14, &masterOpacity );
	saver.Add( 15, &opacity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DecalMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DecalMaterial* parentPtr = (DecalMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DecalMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "DiffuseMul", &DiffuseMul );
	saver.Add( "DiffuseAdd", &DiffuseAdd );
	saver.Add( "radius", &radius );
	saver.Add( "AccessibilityPinValue", &AccessibilityPinValue );
	saver.Add( "OpacityAndEmissiveModePinValue", &OpacityAndEmissiveModePinValue );
	saver.Add( "DistortionPinValue", &DistortionPinValue );
	saver.Add( "DecalPlanePinValue", &DecalPlanePinValue );
	saver.Add( "distortion", &distortion );
	saver.Add( "putOnWater", &putOnWater );
	saver.Add( "isBlendModeOverrided", &isBlendModeOverrided );
	saver.Add( "masterOpacity", &masterOpacity );
	saver.Add( "opacity", &opacity );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DecalMaterial::Assign( const DecalMaterial& _decalMaterial )
{
	renderState.blendMode = _decalMaterial.renderState.blendMode;
	renderState.alphaTest = _decalMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _decalMaterial.renderState.alphaTestRef;
	renderState.culling = _decalMaterial.renderState.culling;
	DiffuseMap.samplerState.minFilter = _decalMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _decalMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _decalMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _decalMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _decalMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _decalMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _decalMaterial.DiffuseMap.texture;
	DiffuseMul = _decalMaterial.DiffuseMul;
	DiffuseAdd = _decalMaterial.DiffuseAdd;
	radius = _decalMaterial.radius;
	AccessibilityPinValue = _decalMaterial.AccessibilityPinValue;
	OpacityAndEmissiveModePinValue = _decalMaterial.OpacityAndEmissiveModePinValue;
	DistortionPinValue = _decalMaterial.DistortionPinValue;
	DecalPlanePinValue = _decalMaterial.DecalPlanePinValue;
	distortion = _decalMaterial.distortion;
	putOnWater = _decalMaterial.putOnWater;
	isBlendModeOverrided = _decalMaterial.isBlendModeOverrided;
	masterOpacity = _decalMaterial.masterOpacity;
	opacity = _decalMaterial.opacity;
	SubPriority = _decalMaterial.SubPriority;
	caption = _decalMaterial.caption;
	renderFlags = _decalMaterial.renderFlags;
	ignoreRenderState = _decalMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DecalTerrainMaterial::DecalTerrainMaterial() :
		radius( 5.0f )
	, AccessibilityPinValue( BOOLEANPIN_PRESENT )
	, OpacityAndEmissiveModePinValue( OPACITYANDEMISSIVEMODEPIN_SIMPLE )
	, DistortionPinValue( BOOLEANPIN_NONE )
	, DecalPlanePinValue( BOOLEANPIN_PRESENT )
	, distortion( 1.0f )
	, putOnWater( true )
	, isBlendModeOverrided( 0 )
	, masterOpacity( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DecalTerrainMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &MaskMap );
	saver.Add( 5, &DiffuseMul );
	saver.Add( 6, &DiffuseAdd );
	saver.Add( 7, &radius );
	saver.Add( 8, &AccessibilityPinValue );
	saver.Add( 9, &OpacityAndEmissiveModePinValue );
	saver.Add( 10, &DistortionPinValue );
	saver.Add( 11, &DecalPlanePinValue );
	saver.Add( 12, &distortion );
	saver.Add( 13, &putOnWater );
	saver.Add( 14, &isBlendModeOverrided );
	saver.Add( 15, &masterOpacity );
	saver.Add( 16, &opacity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DecalTerrainMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DecalTerrainMaterial* parentPtr = (DecalTerrainMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DecalTerrainMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "MaskMap", &MaskMap );
	saver.Add( "DiffuseMul", &DiffuseMul );
	saver.Add( "DiffuseAdd", &DiffuseAdd );
	saver.Add( "radius", &radius );
	saver.Add( "AccessibilityPinValue", &AccessibilityPinValue );
	saver.Add( "OpacityAndEmissiveModePinValue", &OpacityAndEmissiveModePinValue );
	saver.Add( "DistortionPinValue", &DistortionPinValue );
	saver.Add( "DecalPlanePinValue", &DecalPlanePinValue );
	saver.Add( "distortion", &distortion );
	saver.Add( "putOnWater", &putOnWater );
	saver.Add( "isBlendModeOverrided", &isBlendModeOverrided );
	saver.Add( "masterOpacity", &masterOpacity );
	saver.Add( "opacity", &opacity );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DecalTerrainMaterial::Assign( const DecalTerrainMaterial& _decalTerrainMaterial )
{
	renderState.blendMode = _decalTerrainMaterial.renderState.blendMode;
	renderState.alphaTest = _decalTerrainMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _decalTerrainMaterial.renderState.alphaTestRef;
	renderState.culling = _decalTerrainMaterial.renderState.culling;
	DiffuseMap.samplerState.minFilter = _decalTerrainMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _decalTerrainMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _decalTerrainMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _decalTerrainMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _decalTerrainMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _decalTerrainMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _decalTerrainMaterial.DiffuseMap.texture;
	MaskMap.samplerState.minFilter = _decalTerrainMaterial.MaskMap.samplerState.minFilter;
	MaskMap.samplerState.magFilter = _decalTerrainMaterial.MaskMap.samplerState.magFilter;
	MaskMap.samplerState.mipFilter = _decalTerrainMaterial.MaskMap.samplerState.mipFilter;
	MaskMap.samplerState.addressU = _decalTerrainMaterial.MaskMap.samplerState.addressU;
	MaskMap.samplerState.addressV = _decalTerrainMaterial.MaskMap.samplerState.addressV;
	MaskMap.samplerState.addressW = _decalTerrainMaterial.MaskMap.samplerState.addressW;
	MaskMap.texture = _decalTerrainMaterial.MaskMap.texture;
	DiffuseMul = _decalTerrainMaterial.DiffuseMul;
	DiffuseAdd = _decalTerrainMaterial.DiffuseAdd;
	radius = _decalTerrainMaterial.radius;
	AccessibilityPinValue = _decalTerrainMaterial.AccessibilityPinValue;
	OpacityAndEmissiveModePinValue = _decalTerrainMaterial.OpacityAndEmissiveModePinValue;
	DistortionPinValue = _decalTerrainMaterial.DistortionPinValue;
	DecalPlanePinValue = _decalTerrainMaterial.DecalPlanePinValue;
	distortion = _decalTerrainMaterial.distortion;
	putOnWater = _decalTerrainMaterial.putOnWater;
	isBlendModeOverrided = _decalTerrainMaterial.isBlendModeOverrided;
	masterOpacity = _decalTerrainMaterial.masterOpacity;
	opacity = _decalTerrainMaterial.opacity;
	SubPriority = _decalTerrainMaterial.SubPriority;
	caption = _decalTerrainMaterial.caption;
	renderFlags = _decalTerrainMaterial.renderFlags;
	ignoreRenderState = _decalTerrainMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DropMaterial::DropMaterial() :
		lightingIntencity( 1.0f )
	, ambientIntensity( 1.0f )
	, NormalMapPinValue( BOOLEANPIN_NONE )
	, SpecularMapPinValue( BOOLEANPIN_NONE )
	, ReflectivityPinValue( REFLECTIVITYPIN_REFLECTIVITYOFF )
	, colorizeReflectionMap( TEXTURECOLORIZEPIN_NOCOLOR )
	, SkeletalMeshPinValue( BOOLEANPIN_NONE )
	, LightModePinValue( LIGHTMODEPIN_DIFFUSE )
	, isBlendModeOverrided( 0 )
	, emissive( 0.0f )
	, reflectivityLerp( 0.0f )
	, reflectivityAdd( 0.0f )
	, reflectivityMul( 0.0f )
	, specularPower( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DropMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &diffuseColor );
	saver.Add( 4, &lightingIntencity );
	saver.Add( 5, &ambientIntensity );
	saver.Add( 6, &additionalAmbient );
	saver.Add( 7, &DiffuseMap );
	saver.Add( 8, &NormalMap );
	saver.Add( 9, &NormalMapPinValue );
	saver.Add( 10, &SpecularMap );
	saver.Add( 11, &SpecularMapPinValue );
	saver.Add( 12, &ReflectionMap );
	saver.Add( 13, &ReflectivityPinValue );
	saver.Add( 14, &colorizeReflectionMap );
	saver.Add( 15, &reflectionMapColor0 );
	saver.Add( 16, &reflectionMapColor1 );
	saver.Add( 17, &reflectionMapColor2 );
	saver.Add( 18, &reflectionMapColor3 );
	saver.Add( 19, &outputMul );
	saver.Add( 20, &outputAdd );
	saver.Add( 21, &SkeletalMeshPinValue );
	saver.Add( 22, &LightModePinValue );
	saver.Add( 23, &isBlendModeOverrided );
	saver.Add( 24, &emissive );
	saver.Add( 25, &opacity );
	saver.Add( 26, &reflectivityLerp );
	saver.Add( 27, &reflectivityAdd );
	saver.Add( 28, &reflectivityMul );
	saver.Add( 29, &specularPower );
	saver.Add( 30, &uOffset1 );
	saver.Add( 31, &vOffset1 );
	saver.Add( 32, &uOffset2 );
	saver.Add( 33, &vOffset2 );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DropMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DropMaterial* parentPtr = (DropMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DropMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "diffuseColor", &diffuseColor );
	saver.Add( "lightingIntencity", &lightingIntencity );
	saver.Add( "ambientIntensity", &ambientIntensity );
	saver.Add( "additionalAmbient", &additionalAmbient );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "NormalMap", &NormalMap );
	saver.Add( "NormalMapPinValue", &NormalMapPinValue );
	saver.Add( "SpecularMap", &SpecularMap );
	saver.Add( "SpecularMapPinValue", &SpecularMapPinValue );
	saver.Add( "ReflectionMap", &ReflectionMap );
	saver.Add( "ReflectivityPinValue", &ReflectivityPinValue );
	saver.Add( "colorizeReflectionMap", &colorizeReflectionMap );
	saver.Add( "reflectionMapColor0", &reflectionMapColor0 );
	saver.Add( "reflectionMapColor1", &reflectionMapColor1 );
	saver.Add( "reflectionMapColor2", &reflectionMapColor2 );
	saver.Add( "reflectionMapColor3", &reflectionMapColor3 );
	saver.Add( "outputMul", &outputMul );
	saver.Add( "outputAdd", &outputAdd );
	saver.Add( "SkeletalMeshPinValue", &SkeletalMeshPinValue );
	saver.Add( "LightModePinValue", &LightModePinValue );
	saver.Add( "isBlendModeOverrided", &isBlendModeOverrided );
	saver.Add( "emissive", &emissive );
	saver.Add( "opacity", &opacity );
	saver.Add( "reflectivityLerp", &reflectivityLerp );
	saver.Add( "reflectivityAdd", &reflectivityAdd );
	saver.Add( "reflectivityMul", &reflectivityMul );
	saver.Add( "specularPower", &specularPower );
	saver.Add( "uOffset1", &uOffset1 );
	saver.Add( "vOffset1", &vOffset1 );
	saver.Add( "uOffset2", &uOffset2 );
	saver.Add( "vOffset2", &vOffset2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DropMaterial::Assign( const DropMaterial& _dropMaterial )
{
	renderState.blendMode = _dropMaterial.renderState.blendMode;
	renderState.alphaTest = _dropMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _dropMaterial.renderState.alphaTestRef;
	renderState.culling = _dropMaterial.renderState.culling;
	diffuseColor = _dropMaterial.diffuseColor;
	lightingIntencity = _dropMaterial.lightingIntencity;
	ambientIntensity = _dropMaterial.ambientIntensity;
	additionalAmbient = _dropMaterial.additionalAmbient;
	DiffuseMap.samplerState.minFilter = _dropMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _dropMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _dropMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _dropMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _dropMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _dropMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _dropMaterial.DiffuseMap.texture;
	NormalMap.samplerState.minFilter = _dropMaterial.NormalMap.samplerState.minFilter;
	NormalMap.samplerState.magFilter = _dropMaterial.NormalMap.samplerState.magFilter;
	NormalMap.samplerState.mipFilter = _dropMaterial.NormalMap.samplerState.mipFilter;
	NormalMap.samplerState.addressU = _dropMaterial.NormalMap.samplerState.addressU;
	NormalMap.samplerState.addressV = _dropMaterial.NormalMap.samplerState.addressV;
	NormalMap.samplerState.addressW = _dropMaterial.NormalMap.samplerState.addressW;
	NormalMap.texture = _dropMaterial.NormalMap.texture;
	NormalMapPinValue = _dropMaterial.NormalMapPinValue;
	SpecularMap.samplerState.minFilter = _dropMaterial.SpecularMap.samplerState.minFilter;
	SpecularMap.samplerState.magFilter = _dropMaterial.SpecularMap.samplerState.magFilter;
	SpecularMap.samplerState.mipFilter = _dropMaterial.SpecularMap.samplerState.mipFilter;
	SpecularMap.samplerState.addressU = _dropMaterial.SpecularMap.samplerState.addressU;
	SpecularMap.samplerState.addressV = _dropMaterial.SpecularMap.samplerState.addressV;
	SpecularMap.samplerState.addressW = _dropMaterial.SpecularMap.samplerState.addressW;
	SpecularMap.texture = _dropMaterial.SpecularMap.texture;
	SpecularMap.Multiplier = _dropMaterial.SpecularMap.Multiplier;
	SpecularMap.Add = _dropMaterial.SpecularMap.Add;
	SpecularMapPinValue = _dropMaterial.SpecularMapPinValue;
	ReflectionMap.samplerState.minFilter = _dropMaterial.ReflectionMap.samplerState.minFilter;
	ReflectionMap.samplerState.magFilter = _dropMaterial.ReflectionMap.samplerState.magFilter;
	ReflectionMap.samplerState.mipFilter = _dropMaterial.ReflectionMap.samplerState.mipFilter;
	ReflectionMap.samplerState.addressU = _dropMaterial.ReflectionMap.samplerState.addressU;
	ReflectionMap.samplerState.addressV = _dropMaterial.ReflectionMap.samplerState.addressV;
	ReflectionMap.samplerState.addressW = _dropMaterial.ReflectionMap.samplerState.addressW;
	ReflectionMap.texture = _dropMaterial.ReflectionMap.texture;
	ReflectivityPinValue = _dropMaterial.ReflectivityPinValue;
	colorizeReflectionMap = _dropMaterial.colorizeReflectionMap;
	reflectionMapColor0 = _dropMaterial.reflectionMapColor0;
	reflectionMapColor1 = _dropMaterial.reflectionMapColor1;
	reflectionMapColor2 = _dropMaterial.reflectionMapColor2;
	reflectionMapColor3 = _dropMaterial.reflectionMapColor3;
	outputMul = _dropMaterial.outputMul;
	outputAdd = _dropMaterial.outputAdd;
	SkeletalMeshPinValue = _dropMaterial.SkeletalMeshPinValue;
	LightModePinValue = _dropMaterial.LightModePinValue;
	isBlendModeOverrided = _dropMaterial.isBlendModeOverrided;
	emissive = _dropMaterial.emissive;
	opacity = _dropMaterial.opacity;
	reflectivityLerp = _dropMaterial.reflectivityLerp;
	reflectivityAdd = _dropMaterial.reflectivityAdd;
	reflectivityMul = _dropMaterial.reflectivityMul;
	specularPower = _dropMaterial.specularPower;
	uOffset1 = _dropMaterial.uOffset1;
	vOffset1 = _dropMaterial.vOffset1;
	uOffset2 = _dropMaterial.uOffset2;
	vOffset2 = _dropMaterial.vOffset2;
	SubPriority = _dropMaterial.SubPriority;
	caption = _dropMaterial.caption;
	renderFlags = _dropMaterial.renderFlags;
	ignoreRenderState = _dropMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FullScreenMaterial::FullScreenMaterial() :
		SharpPinValue( BOOLEANPIN_NONE )
	, BloomPinValue( BOOLEANPIN_NONE )
	, WarFogPinValue( BOOLEANPIN_NONE )
	, R2VBPinValue( BOOLEANPIN_NONE )
	, ColorCorrectPinValue( COLORCORRECTPIN_OFF )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FullScreenMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DepthMap );
	saver.Add( 4, &DiffuseMap );
	saver.Add( 5, &BloomMap );
	saver.Add( 6, &SharpPinValue );
	saver.Add( 7, &BloomPinValue );
	saver.Add( 8, &WarFogPinValue );
	saver.Add( 9, &R2VBPinValue );
	saver.Add( 10, &ColorCorrectPinValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FullScreenMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			FullScreenMaterial* parentPtr = (FullScreenMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FullScreenMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DepthMap", &DepthMap );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "BloomMap", &BloomMap );
	saver.Add( "SharpPinValue", &SharpPinValue );
	saver.Add( "BloomPinValue", &BloomPinValue );
	saver.Add( "WarFogPinValue", &WarFogPinValue );
	saver.Add( "R2VBPinValue", &R2VBPinValue );
	saver.Add( "ColorCorrectPinValue", &ColorCorrectPinValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FullScreenMaterial::Assign( const FullScreenMaterial& _fullScreenMaterial )
{
	renderState.blendMode = _fullScreenMaterial.renderState.blendMode;
	renderState.alphaTest = _fullScreenMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _fullScreenMaterial.renderState.alphaTestRef;
	renderState.culling = _fullScreenMaterial.renderState.culling;
	DepthMap.samplerState.minFilter = _fullScreenMaterial.DepthMap.samplerState.minFilter;
	DepthMap.samplerState.magFilter = _fullScreenMaterial.DepthMap.samplerState.magFilter;
	DepthMap.samplerState.mipFilter = _fullScreenMaterial.DepthMap.samplerState.mipFilter;
	DepthMap.samplerState.addressU = _fullScreenMaterial.DepthMap.samplerState.addressU;
	DepthMap.samplerState.addressV = _fullScreenMaterial.DepthMap.samplerState.addressV;
	DepthMap.samplerState.addressW = _fullScreenMaterial.DepthMap.samplerState.addressW;
	DepthMap.texture = _fullScreenMaterial.DepthMap.texture;
	DiffuseMap.samplerState.minFilter = _fullScreenMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _fullScreenMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _fullScreenMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _fullScreenMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _fullScreenMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _fullScreenMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _fullScreenMaterial.DiffuseMap.texture;
	BloomMap.samplerState.minFilter = _fullScreenMaterial.BloomMap.samplerState.minFilter;
	BloomMap.samplerState.magFilter = _fullScreenMaterial.BloomMap.samplerState.magFilter;
	BloomMap.samplerState.mipFilter = _fullScreenMaterial.BloomMap.samplerState.mipFilter;
	BloomMap.samplerState.addressU = _fullScreenMaterial.BloomMap.samplerState.addressU;
	BloomMap.samplerState.addressV = _fullScreenMaterial.BloomMap.samplerState.addressV;
	BloomMap.samplerState.addressW = _fullScreenMaterial.BloomMap.samplerState.addressW;
	BloomMap.texture = _fullScreenMaterial.BloomMap.texture;
	SharpPinValue = _fullScreenMaterial.SharpPinValue;
	BloomPinValue = _fullScreenMaterial.BloomPinValue;
	WarFogPinValue = _fullScreenMaterial.WarFogPinValue;
	R2VBPinValue = _fullScreenMaterial.R2VBPinValue;
	ColorCorrectPinValue = _fullScreenMaterial.ColorCorrectPinValue;
	SubPriority = _fullScreenMaterial.SubPriority;
	caption = _fullScreenMaterial.caption;
	renderFlags = _fullScreenMaterial.renderFlags;
	ignoreRenderState = _fullScreenMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GrassMaterial::GrassMaterial() :
		ShadowReciverPinValue( BOOLEANPIN_PRESENT )
	, elasticity( 0.75f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GrassMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &FrozenDiffuseMap );
	saver.Add( 4, &NormalDiffuseMap );
	saver.Add( 5, &BurnedDiffuseMap );
	saver.Add( 6, &ShadowReciverPinValue );
	saver.Add( 7, &bladeSize );
	saver.Add( 8, &elasticity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GrassMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			GrassMaterial* parentPtr = (GrassMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GrassMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "FrozenDiffuseMap", &FrozenDiffuseMap );
	saver.Add( "NormalDiffuseMap", &NormalDiffuseMap );
	saver.Add( "BurnedDiffuseMap", &BurnedDiffuseMap );
	saver.Add( "ShadowReciverPinValue", &ShadowReciverPinValue );
	saver.Add( "bladeSize", &bladeSize );
	saver.Add( "elasticity", &elasticity );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GrassMaterial::Assign( const GrassMaterial& _grassMaterial )
{
	renderState.blendMode = _grassMaterial.renderState.blendMode;
	renderState.alphaTest = _grassMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _grassMaterial.renderState.alphaTestRef;
	renderState.culling = _grassMaterial.renderState.culling;
	FrozenDiffuseMap.samplerState.minFilter = _grassMaterial.FrozenDiffuseMap.samplerState.minFilter;
	FrozenDiffuseMap.samplerState.magFilter = _grassMaterial.FrozenDiffuseMap.samplerState.magFilter;
	FrozenDiffuseMap.samplerState.mipFilter = _grassMaterial.FrozenDiffuseMap.samplerState.mipFilter;
	FrozenDiffuseMap.samplerState.addressU = _grassMaterial.FrozenDiffuseMap.samplerState.addressU;
	FrozenDiffuseMap.samplerState.addressV = _grassMaterial.FrozenDiffuseMap.samplerState.addressV;
	FrozenDiffuseMap.samplerState.addressW = _grassMaterial.FrozenDiffuseMap.samplerState.addressW;
	FrozenDiffuseMap.texture = _grassMaterial.FrozenDiffuseMap.texture;
	FrozenDiffuseMap.Multiplier = _grassMaterial.FrozenDiffuseMap.Multiplier;
	FrozenDiffuseMap.Add = _grassMaterial.FrozenDiffuseMap.Add;
	NormalDiffuseMap.samplerState.minFilter = _grassMaterial.NormalDiffuseMap.samplerState.minFilter;
	NormalDiffuseMap.samplerState.magFilter = _grassMaterial.NormalDiffuseMap.samplerState.magFilter;
	NormalDiffuseMap.samplerState.mipFilter = _grassMaterial.NormalDiffuseMap.samplerState.mipFilter;
	NormalDiffuseMap.samplerState.addressU = _grassMaterial.NormalDiffuseMap.samplerState.addressU;
	NormalDiffuseMap.samplerState.addressV = _grassMaterial.NormalDiffuseMap.samplerState.addressV;
	NormalDiffuseMap.samplerState.addressW = _grassMaterial.NormalDiffuseMap.samplerState.addressW;
	NormalDiffuseMap.texture = _grassMaterial.NormalDiffuseMap.texture;
	NormalDiffuseMap.Multiplier = _grassMaterial.NormalDiffuseMap.Multiplier;
	NormalDiffuseMap.Add = _grassMaterial.NormalDiffuseMap.Add;
	BurnedDiffuseMap.samplerState.minFilter = _grassMaterial.BurnedDiffuseMap.samplerState.minFilter;
	BurnedDiffuseMap.samplerState.magFilter = _grassMaterial.BurnedDiffuseMap.samplerState.magFilter;
	BurnedDiffuseMap.samplerState.mipFilter = _grassMaterial.BurnedDiffuseMap.samplerState.mipFilter;
	BurnedDiffuseMap.samplerState.addressU = _grassMaterial.BurnedDiffuseMap.samplerState.addressU;
	BurnedDiffuseMap.samplerState.addressV = _grassMaterial.BurnedDiffuseMap.samplerState.addressV;
	BurnedDiffuseMap.samplerState.addressW = _grassMaterial.BurnedDiffuseMap.samplerState.addressW;
	BurnedDiffuseMap.texture = _grassMaterial.BurnedDiffuseMap.texture;
	BurnedDiffuseMap.Multiplier = _grassMaterial.BurnedDiffuseMap.Multiplier;
	BurnedDiffuseMap.Add = _grassMaterial.BurnedDiffuseMap.Add;
	ShadowReciverPinValue = _grassMaterial.ShadowReciverPinValue;
	bladeSize = _grassMaterial.bladeSize;
	elasticity = _grassMaterial.elasticity;
	SubPriority = _grassMaterial.SubPriority;
	caption = _grassMaterial.caption;
	renderFlags = _grassMaterial.renderFlags;
	ignoreRenderState = _grassMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HeightfogMaterial::HeightfogMaterial() :
		noiseR1( 1.0f )
	, noiseR2( 0.3f )
	, noiseR3( 0.3f )
	, speed( 2.5f )
	, tiling( 10.0f )
	, roughnessScale( 2.0f )
	, halfFadeDistance( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeightfogMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &noiseMap );
	saver.Add( 4, &noiseR1 );
	saver.Add( 5, &noiseR2 );
	saver.Add( 6, &noiseR3 );
	saver.Add( 7, &speed );
	saver.Add( 8, &tiling );
	saver.Add( 9, &color1 );
	saver.Add( 10, &color2 );
	saver.Add( 11, &roughnessScale );
	saver.Add( 12, &halfFadeDistance );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int HeightfogMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			HeightfogMaterial* parentPtr = (HeightfogMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeightfogMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "noiseMap", &noiseMap );
	saver.Add( "noiseR1", &noiseR1 );
	saver.Add( "noiseR2", &noiseR2 );
	saver.Add( "noiseR3", &noiseR3 );
	saver.Add( "speed", &speed );
	saver.Add( "tiling", &tiling );
	saver.Add( "color1", &color1 );
	saver.Add( "color2", &color2 );
	saver.Add( "roughnessScale", &roughnessScale );
	saver.Add( "halfFadeDistance", &halfFadeDistance );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HeightfogMaterial::Assign( const HeightfogMaterial& _heightfogMaterial )
{
	renderState.blendMode = _heightfogMaterial.renderState.blendMode;
	renderState.alphaTest = _heightfogMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _heightfogMaterial.renderState.alphaTestRef;
	renderState.culling = _heightfogMaterial.renderState.culling;
	noiseMap.samplerState.minFilter = _heightfogMaterial.noiseMap.samplerState.minFilter;
	noiseMap.samplerState.magFilter = _heightfogMaterial.noiseMap.samplerState.magFilter;
	noiseMap.samplerState.mipFilter = _heightfogMaterial.noiseMap.samplerState.mipFilter;
	noiseMap.samplerState.addressU = _heightfogMaterial.noiseMap.samplerState.addressU;
	noiseMap.samplerState.addressV = _heightfogMaterial.noiseMap.samplerState.addressV;
	noiseMap.samplerState.addressW = _heightfogMaterial.noiseMap.samplerState.addressW;
	noiseMap.texture = _heightfogMaterial.noiseMap.texture;
	noiseR1 = _heightfogMaterial.noiseR1;
	noiseR2 = _heightfogMaterial.noiseR2;
	noiseR3 = _heightfogMaterial.noiseR3;
	speed = _heightfogMaterial.speed;
	tiling = _heightfogMaterial.tiling;
	color1 = _heightfogMaterial.color1;
	color2 = _heightfogMaterial.color2;
	roughnessScale = _heightfogMaterial.roughnessScale;
	halfFadeDistance = _heightfogMaterial.halfFadeDistance;
	SubPriority = _heightfogMaterial.SubPriority;
	caption = _heightfogMaterial.caption;
	renderFlags = _heightfogMaterial.renderFlags;
	ignoreRenderState = _heightfogMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LightEnvironment::LightEnvironment() :
		WaterOscillationSpeedFactor( 1.0f )
	, fullSizeX( 2048 )
	, fullSizeY( 2048 )
	, fullSizeSAX( 1024 )
	, fullSizeSAY( 1024 )
	, shadowMode( SHADOWMODE_PCF )
	, powerOfESM( 80.0f )
	, depthBias( 0.0001f )
	, biasSlope( 4.0f )
	, shadowBlendMode( SHADOWBLENDMODE_LERPBYALPHA )
	, shadowLength( 20.0f )
	, shadowFar( 60.0f )
	, shadowFarRange( 10.0f )
	, warFogType( WARFOGTYPE_SINGLELAYER )
	, warFogObstacleVisibility( 6.0f )
	, warFogUseHeightsDelta( true )
	, warFogMaxHeightsDelta( 3.0f )
	, warFogMiniMapAlphaScale( 1.5f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LightEnvironment::operator&( IBinSaver &saver )
{
	saver.Add( 2, &Light1Direction );
	saver.Add( 3, &Light2Direction );
	saver.Add( 4, &AmbientColor );
	saver.Add( 5, &Light1DiffuseColor );
	saver.Add( 6, &Light2DiffuseColor );
	saver.Add( 7, &environmentCubeMap );
	saver.Add( 8, &lightingCubeMap );
	saver.Add( 9, &minBakedColor );
	saver.Add( 10, &maxBakedColor );
	saver.Add( 11, &lightingCubeMapSHCoeffs );
	saver.Add( 12, &WaterOscillationSpeedFactor );
	saver.Add( 13, &WaterReflColor0 );
	saver.Add( 14, &WaterReflColor1 );
	saver.Add( 15, &fullSizeX );
	saver.Add( 16, &fullSizeY );
	saver.Add( 17, &fullSizeSAX );
	saver.Add( 18, &fullSizeSAY );
	saver.Add( 19, &shadowMode );
	saver.Add( 20, &powerOfESM );
	saver.Add( 21, &depthBias );
	saver.Add( 22, &biasSlope );
	saver.Add( 23, &shadowColor );
	saver.Add( 24, &shadowDirection );
	saver.Add( 25, &shadowBlendMode );
	saver.Add( 26, &shadowLength );
	saver.Add( 27, &shadowFar );
	saver.Add( 28, &shadowFarRange );
	saver.Add( 29, &warFogType );
	saver.Add( 30, &warFogColor );
	saver.Add( 31, &warFogColor2 );
	saver.Add( 32, &warFogColorForObjects );
	saver.Add( 33, &warFogObstacleVisibility );
	saver.Add( 34, &warFogUseHeightsDelta );
	saver.Add( 35, &warFogMaxHeightsDelta );
	saver.Add( 36, &warFogMiniMapAlphaScale );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LightEnvironment::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			LightEnvironment* parentPtr = (LightEnvironment*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LightEnvironment::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "Light1Direction", &Light1Direction );
	saver.Add( "Light2Direction", &Light2Direction );
	saver.Add( "AmbientColor", &AmbientColor );
	saver.Add( "Light1DiffuseColor", &Light1DiffuseColor );
	saver.Add( "Light2DiffuseColor", &Light2DiffuseColor );
	saver.Add( "environmentCubeMap", &environmentCubeMap );
	saver.Add( "lightingCubeMap", &lightingCubeMap );
	saver.Add( "minBakedColor", &minBakedColor );
	saver.Add( "maxBakedColor", &maxBakedColor );
	saver.Add( "lightingCubeMapSHCoeffs", &lightingCubeMapSHCoeffs );
	saver.Add( "WaterOscillationSpeedFactor", &WaterOscillationSpeedFactor );
	saver.Add( "WaterReflColor0", &WaterReflColor0 );
	saver.Add( "WaterReflColor1", &WaterReflColor1 );
	saver.Add( "fullSizeX", &fullSizeX );
	saver.Add( "fullSizeY", &fullSizeY );
	saver.Add( "fullSizeSAX", &fullSizeSAX );
	saver.Add( "fullSizeSAY", &fullSizeSAY );
	saver.Add( "shadowMode", &shadowMode );
	saver.Add( "powerOfESM", &powerOfESM );
	saver.Add( "depthBias", &depthBias );
	saver.Add( "biasSlope", &biasSlope );
	saver.Add( "shadowColor", &shadowColor );
	saver.Add( "shadowDirection", &shadowDirection );
	saver.Add( "shadowBlendMode", &shadowBlendMode );
	saver.Add( "shadowLength", &shadowLength );
	saver.Add( "shadowFar", &shadowFar );
	saver.Add( "shadowFarRange", &shadowFarRange );
	saver.Add( "warFogType", &warFogType );
	saver.Add( "warFogColor", &warFogColor );
	saver.Add( "warFogColor2", &warFogColor2 );
	saver.Add( "warFogColorForObjects", &warFogColorForObjects );
	saver.Add( "warFogObstacleVisibility", &warFogObstacleVisibility );
	saver.Add( "warFogUseHeightsDelta", &warFogUseHeightsDelta );
	saver.Add( "warFogMaxHeightsDelta", &warFogMaxHeightsDelta );
	saver.Add( "warFogMiniMapAlphaScale", &warFogMiniMapAlphaScale );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LightEnvironment::Assign( const LightEnvironment& _lightEnvironment )
{
	Light1Direction.Yaw = _lightEnvironment.Light1Direction.Yaw;
	Light1Direction.Pitch = _lightEnvironment.Light1Direction.Pitch;
	Light2Direction.Yaw = _lightEnvironment.Light2Direction.Yaw;
	Light2Direction.Pitch = _lightEnvironment.Light2Direction.Pitch;
	AmbientColor = _lightEnvironment.AmbientColor;
	Light1DiffuseColor = _lightEnvironment.Light1DiffuseColor;
	Light2DiffuseColor = _lightEnvironment.Light2DiffuseColor;
	environmentCubeMap = _lightEnvironment.environmentCubeMap;
	lightingCubeMap = _lightEnvironment.lightingCubeMap;
	minBakedColor = _lightEnvironment.minBakedColor;
	maxBakedColor = _lightEnvironment.maxBakedColor;
	lightingCubeMapSHCoeffs = _lightEnvironment.lightingCubeMapSHCoeffs;
	WaterOscillationSpeedFactor = _lightEnvironment.WaterOscillationSpeedFactor;
	WaterReflColor0 = _lightEnvironment.WaterReflColor0;
	WaterReflColor1 = _lightEnvironment.WaterReflColor1;
	fullSizeX = _lightEnvironment.fullSizeX;
	fullSizeY = _lightEnvironment.fullSizeY;
	fullSizeSAX = _lightEnvironment.fullSizeSAX;
	fullSizeSAY = _lightEnvironment.fullSizeSAY;
	shadowMode = _lightEnvironment.shadowMode;
	powerOfESM = _lightEnvironment.powerOfESM;
	depthBias = _lightEnvironment.depthBias;
	biasSlope = _lightEnvironment.biasSlope;
	shadowColor = _lightEnvironment.shadowColor;
	shadowDirection.Yaw = _lightEnvironment.shadowDirection.Yaw;
	shadowDirection.Pitch = _lightEnvironment.shadowDirection.Pitch;
	shadowBlendMode = _lightEnvironment.shadowBlendMode;
	shadowLength = _lightEnvironment.shadowLength;
	shadowFar = _lightEnvironment.shadowFar;
	shadowFarRange = _lightEnvironment.shadowFarRange;
	warFogType = _lightEnvironment.warFogType;
	warFogColor = _lightEnvironment.warFogColor;
	warFogColor2 = _lightEnvironment.warFogColor2;
	warFogColorForObjects = _lightEnvironment.warFogColorForObjects;
	warFogObstacleVisibility = _lightEnvironment.warFogObstacleVisibility;
	warFogUseHeightsDelta = _lightEnvironment.warFogUseHeightsDelta;
	warFogMaxHeightsDelta = _lightEnvironment.warFogMaxHeightsDelta;
	warFogMiniMapAlphaScale = _lightEnvironment.warFogMiniMapAlphaScale;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LightningMaterial::LightningMaterial()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LightningMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DiffuseMap );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LightningMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			LightningMaterial* parentPtr = (LightningMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LightningMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LightningMaterial::Assign( const LightningMaterial& _lightningMaterial )
{
	renderState.blendMode = _lightningMaterial.renderState.blendMode;
	renderState.alphaTest = _lightningMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _lightningMaterial.renderState.alphaTestRef;
	renderState.culling = _lightningMaterial.renderState.culling;
	DiffuseMap.samplerState.minFilter = _lightningMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _lightningMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _lightningMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _lightningMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _lightningMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _lightningMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _lightningMaterial.DiffuseMap.texture;
	SubPriority = _lightningMaterial.SubPriority;
	caption = _lightningMaterial.caption;
	renderFlags = _lightningMaterial.renderFlags;
	ignoreRenderState = _lightningMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AIGeometryMaterialType::AIGeometryMaterialType()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AIGeometryMaterialType::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AIGeometryMaterialType::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AIGeometryMaterialType* parentPtr = (AIGeometryMaterialType*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AIGeometryMaterialType::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AIGeometryMaterialType::Assign( const AIGeometryMaterialType& _aIGeometryMaterialType )
{
	renderState.blendMode = _aIGeometryMaterialType.renderState.blendMode;
	renderState.alphaTest = _aIGeometryMaterialType.renderState.alphaTest;
	renderState.alphaTestRef = _aIGeometryMaterialType.renderState.alphaTestRef;
	renderState.culling = _aIGeometryMaterialType.renderState.culling;
	SubPriority = _aIGeometryMaterialType.SubPriority;
	caption = _aIGeometryMaterialType.caption;
	renderFlags = _aIGeometryMaterialType.renderFlags;
	ignoreRenderState = _aIGeometryMaterialType.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NatureMapMaterial::NatureMapMaterial()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NatureMapMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NatureMapMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			NatureMapMaterial* parentPtr = (NatureMapMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NatureMapMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NatureMapMaterial::Assign( const NatureMapMaterial& _natureMapMaterial )
{
	SubPriority = _natureMapMaterial.SubPriority;
	caption = _natureMapMaterial.caption;
	renderFlags = _natureMapMaterial.renderFlags;
	ignoreRenderState = _natureMapMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PaintMaterial::PaintMaterial() :
		masksNumber( PACKEDMASKSNUMBERPIN_PACKEDMASKS1 )
	, paintMode( PAINTMATERIALMODEPIN_INWORK )
	, opacity( 1.0f )
	, isBlendModeOverrided( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PaintMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &masksNumber );
	saver.Add( 3, &paintMode );
	saver.Add( 4, &renderState );
	saver.Add( 5, &Draft );
	saver.Add( 6, &Background );
	saver.Add( 7, &BaseBackground );
	saver.Add( 8, &Complete );
	saver.Add( 9, &Mask );
	saver.Add( 10, &opacity );
	saver.Add( 11, &isBlendModeOverrided );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PaintMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PaintMaterial* parentPtr = (PaintMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PaintMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "masksNumber", &masksNumber );
	saver.Add( "paintMode", &paintMode );
	saver.Add( "renderState", &renderState );
	saver.Add( "Draft", &Draft );
	saver.Add( "Background", &Background );
	saver.Add( "BaseBackground", &BaseBackground );
	saver.Add( "Complete", &Complete );
	saver.Add( "Mask", &Mask );
	saver.Add( "opacity", &opacity );
	saver.Add( "isBlendModeOverrided", &isBlendModeOverrided );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PaintMaterial::Assign( const PaintMaterial& _paintMaterial )
{
	masksNumber = _paintMaterial.masksNumber;
	paintMode = _paintMaterial.paintMode;
	renderState.blendMode = _paintMaterial.renderState.blendMode;
	renderState.alphaTest = _paintMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _paintMaterial.renderState.alphaTestRef;
	renderState.culling = _paintMaterial.renderState.culling;
	Draft.samplerState.minFilter = _paintMaterial.Draft.samplerState.minFilter;
	Draft.samplerState.magFilter = _paintMaterial.Draft.samplerState.magFilter;
	Draft.samplerState.mipFilter = _paintMaterial.Draft.samplerState.mipFilter;
	Draft.samplerState.addressU = _paintMaterial.Draft.samplerState.addressU;
	Draft.samplerState.addressV = _paintMaterial.Draft.samplerState.addressV;
	Draft.samplerState.addressW = _paintMaterial.Draft.samplerState.addressW;
	Draft.texture = _paintMaterial.Draft.texture;
	Background.samplerState.minFilter = _paintMaterial.Background.samplerState.minFilter;
	Background.samplerState.magFilter = _paintMaterial.Background.samplerState.magFilter;
	Background.samplerState.mipFilter = _paintMaterial.Background.samplerState.mipFilter;
	Background.samplerState.addressU = _paintMaterial.Background.samplerState.addressU;
	Background.samplerState.addressV = _paintMaterial.Background.samplerState.addressV;
	Background.samplerState.addressW = _paintMaterial.Background.samplerState.addressW;
	Background.texture = _paintMaterial.Background.texture;
	BaseBackground.samplerState.minFilter = _paintMaterial.BaseBackground.samplerState.minFilter;
	BaseBackground.samplerState.magFilter = _paintMaterial.BaseBackground.samplerState.magFilter;
	BaseBackground.samplerState.mipFilter = _paintMaterial.BaseBackground.samplerState.mipFilter;
	BaseBackground.samplerState.addressU = _paintMaterial.BaseBackground.samplerState.addressU;
	BaseBackground.samplerState.addressV = _paintMaterial.BaseBackground.samplerState.addressV;
	BaseBackground.samplerState.addressW = _paintMaterial.BaseBackground.samplerState.addressW;
	BaseBackground.texture = _paintMaterial.BaseBackground.texture;
	Complete.samplerState.minFilter = _paintMaterial.Complete.samplerState.minFilter;
	Complete.samplerState.magFilter = _paintMaterial.Complete.samplerState.magFilter;
	Complete.samplerState.mipFilter = _paintMaterial.Complete.samplerState.mipFilter;
	Complete.samplerState.addressU = _paintMaterial.Complete.samplerState.addressU;
	Complete.samplerState.addressV = _paintMaterial.Complete.samplerState.addressV;
	Complete.samplerState.addressW = _paintMaterial.Complete.samplerState.addressW;
	Complete.texture = _paintMaterial.Complete.texture;
	Mask.samplerState.minFilter = _paintMaterial.Mask.samplerState.minFilter;
	Mask.samplerState.magFilter = _paintMaterial.Mask.samplerState.magFilter;
	Mask.samplerState.mipFilter = _paintMaterial.Mask.samplerState.mipFilter;
	Mask.samplerState.addressU = _paintMaterial.Mask.samplerState.addressU;
	Mask.samplerState.addressV = _paintMaterial.Mask.samplerState.addressV;
	Mask.samplerState.addressW = _paintMaterial.Mask.samplerState.addressW;
	Mask.texture = _paintMaterial.Mask.texture;
	opacity = _paintMaterial.opacity;
	isBlendModeOverrided = _paintMaterial.isBlendModeOverrided;
	SubPriority = _paintMaterial.SubPriority;
	caption = _paintMaterial.caption;
	renderFlags = _paintMaterial.renderFlags;
	ignoreRenderState = _paintMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParticleFXMaterial::ParticleFXMaterial() :
		OpacityAndEmissiveModePinValue( OPACITYANDEMISSIVEMODEPIN_SIMPLE )
	, OrientTypePinValue( ORIENTTYPEPIN_NONETYPE )
	, DistortionPinValue( BOOLEANPIN_NONE )
	, opacity( 1.0f )
	, distortion( 1.0f )
	, isBlendModeOverrided( 0 )
	, scale( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ParticleFXMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &OpacityAndEmissiveModePinValue );
	saver.Add( 5, &OrientTypePinValue );
	saver.Add( 6, &DistortionPinValue );
	saver.Add( 7, &opacity );
	saver.Add( 8, &distortion );
	saver.Add( 9, &uvSpeed );
	saver.Add( 10, &isBlendModeOverrided );
	saver.Add( 11, &scale );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ParticleFXMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ParticleFXMaterial* parentPtr = (ParticleFXMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFXMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "OpacityAndEmissiveModePinValue", &OpacityAndEmissiveModePinValue );
	saver.Add( "OrientTypePinValue", &OrientTypePinValue );
	saver.Add( "DistortionPinValue", &DistortionPinValue );
	saver.Add( "opacity", &opacity );
	saver.Add( "distortion", &distortion );
	saver.Add( "uvSpeed", &uvSpeed );
	saver.Add( "isBlendModeOverrided", &isBlendModeOverrided );
	saver.Add( "scale", &scale );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFXMaterial::Assign( const ParticleFXMaterial& _particleFXMaterial )
{
	renderState.blendMode = _particleFXMaterial.renderState.blendMode;
	renderState.alphaTest = _particleFXMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _particleFXMaterial.renderState.alphaTestRef;
	renderState.culling = _particleFXMaterial.renderState.culling;
	DiffuseMap.samplerState.minFilter = _particleFXMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _particleFXMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _particleFXMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _particleFXMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _particleFXMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _particleFXMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _particleFXMaterial.DiffuseMap.texture;
	DiffuseMap.Multiplier = _particleFXMaterial.DiffuseMap.Multiplier;
	DiffuseMap.Add = _particleFXMaterial.DiffuseMap.Add;
	OpacityAndEmissiveModePinValue = _particleFXMaterial.OpacityAndEmissiveModePinValue;
	OrientTypePinValue = _particleFXMaterial.OrientTypePinValue;
	DistortionPinValue = _particleFXMaterial.DistortionPinValue;
	opacity = _particleFXMaterial.opacity;
	distortion = _particleFXMaterial.distortion;
	uvSpeed = _particleFXMaterial.uvSpeed;
	isBlendModeOverrided = _particleFXMaterial.isBlendModeOverrided;
	scale = _particleFXMaterial.scale;
	SubPriority = _particleFXMaterial.SubPriority;
	caption = _particleFXMaterial.caption;
	renderFlags = _particleFXMaterial.renderFlags;
	ignoreRenderState = _particleFXMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RoadMaterial::RoadMaterial() :
		TextureFitPinValue( BOOLEANPIN_NONE )
	, DebugPinValue( BOOLEANPIN_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoadMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &RoadMap );
	saver.Add( 4, &BorderMap );
	saver.Add( 5, &TextureFitPinValue );
	saver.Add( 6, &DebugPinValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoadMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			RoadMaterial* parentPtr = (RoadMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoadMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "RoadMap", &RoadMap );
	saver.Add( "BorderMap", &BorderMap );
	saver.Add( "TextureFitPinValue", &TextureFitPinValue );
	saver.Add( "DebugPinValue", &DebugPinValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoadMaterial::Assign( const RoadMaterial& _roadMaterial )
{
	renderState.blendMode = _roadMaterial.renderState.blendMode;
	renderState.alphaTest = _roadMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _roadMaterial.renderState.alphaTestRef;
	renderState.culling = _roadMaterial.renderState.culling;
	RoadMap.samplerState.minFilter = _roadMaterial.RoadMap.samplerState.minFilter;
	RoadMap.samplerState.magFilter = _roadMaterial.RoadMap.samplerState.magFilter;
	RoadMap.samplerState.mipFilter = _roadMaterial.RoadMap.samplerState.mipFilter;
	RoadMap.samplerState.addressU = _roadMaterial.RoadMap.samplerState.addressU;
	RoadMap.samplerState.addressV = _roadMaterial.RoadMap.samplerState.addressV;
	RoadMap.samplerState.addressW = _roadMaterial.RoadMap.samplerState.addressW;
	RoadMap.texture = _roadMaterial.RoadMap.texture;
	BorderMap.samplerState.minFilter = _roadMaterial.BorderMap.samplerState.minFilter;
	BorderMap.samplerState.magFilter = _roadMaterial.BorderMap.samplerState.magFilter;
	BorderMap.samplerState.mipFilter = _roadMaterial.BorderMap.samplerState.mipFilter;
	BorderMap.samplerState.addressU = _roadMaterial.BorderMap.samplerState.addressU;
	BorderMap.samplerState.addressV = _roadMaterial.BorderMap.samplerState.addressV;
	BorderMap.samplerState.addressW = _roadMaterial.BorderMap.samplerState.addressW;
	BorderMap.texture = _roadMaterial.BorderMap.texture;
	TextureFitPinValue = _roadMaterial.TextureFitPinValue;
	DebugPinValue = _roadMaterial.DebugPinValue;
	SubPriority = _roadMaterial.SubPriority;
	caption = _roadMaterial.caption;
	renderFlags = _roadMaterial.renderFlags;
	ignoreRenderState = _roadMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShadowMaterial::ShadowMaterial() :
		SkeletalMeshPinValue( BOOLEANPIN_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShadowMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &SkeletalMeshPinValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShadowMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ShadowMaterial* parentPtr = (ShadowMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShadowMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "SkeletalMeshPinValue", &SkeletalMeshPinValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShadowMaterial::Assign( const ShadowMaterial& _shadowMaterial )
{
	renderState.blendMode = _shadowMaterial.renderState.blendMode;
	renderState.alphaTest = _shadowMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _shadowMaterial.renderState.alphaTestRef;
	renderState.culling = _shadowMaterial.renderState.culling;
	DiffuseMap.samplerState.minFilter = _shadowMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _shadowMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _shadowMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _shadowMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _shadowMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _shadowMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _shadowMaterial.DiffuseMap.texture;
	SkeletalMeshPinValue = _shadowMaterial.SkeletalMeshPinValue;
	SubPriority = _shadowMaterial.SubPriority;
	caption = _shadowMaterial.caption;
	renderFlags = _shadowMaterial.renderFlags;
	ignoreRenderState = _shadowMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SilhouetteMaterial::SilhouetteMaterial() :
		SkeletalMeshPinValue( BOOLEANPIN_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SilhouetteMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &SkeletalMeshPinValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SilhouetteMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SilhouetteMaterial* parentPtr = (SilhouetteMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SilhouetteMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "SkeletalMeshPinValue", &SkeletalMeshPinValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SilhouetteMaterial::Assign( const SilhouetteMaterial& _silhouetteMaterial )
{
	renderState.blendMode = _silhouetteMaterial.renderState.blendMode;
	renderState.alphaTest = _silhouetteMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _silhouetteMaterial.renderState.alphaTestRef;
	renderState.culling = _silhouetteMaterial.renderState.culling;
	SkeletalMeshPinValue = _silhouetteMaterial.SkeletalMeshPinValue;
	SubPriority = _silhouetteMaterial.SubPriority;
	caption = _silhouetteMaterial.caption;
	renderFlags = _silhouetteMaterial.renderFlags;
	ignoreRenderState = _silhouetteMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SkyMaterial::SkyMaterial()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SkyMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &outputMul );
	saver.Add( 5, &outputAdd );
	saver.Add( 6, &uOffset1 );
	saver.Add( 7, &vOffset1 );
	saver.Add( 8, &uOffset2 );
	saver.Add( 9, &vOffset2 );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SkyMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SkyMaterial* parentPtr = (SkyMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SkyMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "outputMul", &outputMul );
	saver.Add( "outputAdd", &outputAdd );
	saver.Add( "uOffset1", &uOffset1 );
	saver.Add( "vOffset1", &vOffset1 );
	saver.Add( "uOffset2", &uOffset2 );
	saver.Add( "vOffset2", &vOffset2 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SkyMaterial::Assign( const SkyMaterial& _skyMaterial )
{
	renderState.blendMode = _skyMaterial.renderState.blendMode;
	renderState.alphaTest = _skyMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _skyMaterial.renderState.alphaTestRef;
	renderState.culling = _skyMaterial.renderState.culling;
	DiffuseMap.samplerState.minFilter = _skyMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _skyMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _skyMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _skyMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _skyMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _skyMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _skyMaterial.DiffuseMap.texture;
	outputMul = _skyMaterial.outputMul;
	outputAdd = _skyMaterial.outputAdd;
	uOffset1 = _skyMaterial.uOffset1;
	vOffset1 = _skyMaterial.vOffset1;
	uOffset2 = _skyMaterial.uOffset2;
	vOffset2 = _skyMaterial.vOffset2;
	SubPriority = _skyMaterial.SubPriority;
	caption = _skyMaterial.caption;
	renderFlags = _skyMaterial.renderFlags;
	ignoreRenderState = _skyMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainAOEMaterial::TerrainAOEMaterial()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainAOEMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &uvScale );
	saver.Add( 5, &uvOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainAOEMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TerrainAOEMaterial* parentPtr = (TerrainAOEMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainAOEMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "uvScale", &uvScale );
	saver.Add( "uvOffset", &uvOffset );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainAOEMaterial::Assign( const TerrainAOEMaterial& _terrainAOEMaterial )
{
	renderState.blendMode = _terrainAOEMaterial.renderState.blendMode;
	renderState.alphaTest = _terrainAOEMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _terrainAOEMaterial.renderState.alphaTestRef;
	renderState.culling = _terrainAOEMaterial.renderState.culling;
	DiffuseMap.samplerState.minFilter = _terrainAOEMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _terrainAOEMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _terrainAOEMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _terrainAOEMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _terrainAOEMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _terrainAOEMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _terrainAOEMaterial.DiffuseMap.texture;
	uvScale = _terrainAOEMaterial.uvScale;
	uvOffset = _terrainAOEMaterial.uvOffset;
	SubPriority = _terrainAOEMaterial.SubPriority;
	caption = _terrainAOEMaterial.caption;
	renderFlags = _terrainAOEMaterial.renderFlags;
	ignoreRenderState = _terrainAOEMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainElementDebugMaterial::TerrainElementDebugMaterial()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainElementDebugMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainElementDebugMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TerrainElementDebugMaterial* parentPtr = (TerrainElementDebugMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainElementDebugMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainElementDebugMaterial::Assign( const TerrainElementDebugMaterial& _terrainElementDebugMaterial )
{
	SubPriority = _terrainElementDebugMaterial.SubPriority;
	caption = _terrainElementDebugMaterial.caption;
	renderFlags = _terrainElementDebugMaterial.renderFlags;
	ignoreRenderState = _terrainElementDebugMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainElementMaterial::TerrainElementMaterial() :
		TerrainUVSetPinValue( TERRAINUVSETPIN_GLOBAL )
	, TextureCountPinValue( TEXTURECOUNTPIN_COUNT1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainElementMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &TerrainUVSetPinValue );
	saver.Add( 3, &TextureCountPinValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainElementMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TerrainElementMaterial* parentPtr = (TerrainElementMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainElementMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "TerrainUVSetPinValue", &TerrainUVSetPinValue );
	saver.Add( "TextureCountPinValue", &TextureCountPinValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainElementMaterial::Assign( const TerrainElementMaterial& _terrainElementMaterial )
{
	TerrainUVSetPinValue = _terrainElementMaterial.TerrainUVSetPinValue;
	TextureCountPinValue = _terrainElementMaterial.TextureCountPinValue;
	SubPriority = _terrainElementMaterial.SubPriority;
	caption = _terrainElementMaterial.caption;
	renderFlags = _terrainElementMaterial.renderFlags;
	ignoreRenderState = _terrainElementMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainHeightBuilderMaterial::TerrainHeightBuilderMaterial()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainHeightBuilderMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainHeightBuilderMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TerrainHeightBuilderMaterial* parentPtr = (TerrainHeightBuilderMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainHeightBuilderMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainHeightBuilderMaterial::Assign( const TerrainHeightBuilderMaterial& _terrainHeightBuilderMaterial )
{
	renderState.blendMode = _terrainHeightBuilderMaterial.renderState.blendMode;
	renderState.alphaTest = _terrainHeightBuilderMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _terrainHeightBuilderMaterial.renderState.alphaTestRef;
	renderState.culling = _terrainHeightBuilderMaterial.renderState.culling;
	SubPriority = _terrainHeightBuilderMaterial.SubPriority;
	caption = _terrainHeightBuilderMaterial.caption;
	renderFlags = _terrainHeightBuilderMaterial.renderFlags;
	ignoreRenderState = _terrainHeightBuilderMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TerrainMaterial::TerrainMaterial() :
		NormalMapPinValue( BOOLEANPIN_NONE )
	, ShadowReciverPinValue( BOOLEANPIN_PRESENT )
	, ShadowCasterPinValue( BOOLEANPIN_PRESENT )
	, SpecularMapPinValue( BOOLEANPIN_NONE )
	, EnvMapPinValue( BOOLEANPIN_NONE )
	, DarkMapPinValue( BOOLEANPIN_NONE )
	, TerrainUVSetPinValue( TERRAINUVSETPIN_GLOBAL )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &grassRect );
	saver.Add( 3, &A_DiffuseMap );
	saver.Add( 4, &N_DiffuseMap );
	saver.Add( 5, &B_DiffuseMap );
	saver.Add( 6, &FrozenNormalMap );
	saver.Add( 7, &NormalNormalMap );
	saver.Add( 8, &BurnedNormalMap );
	saver.Add( 9, &FrozenSpecularMap );
	saver.Add( 10, &NormalSpecularMap );
	saver.Add( 11, &BurnedSpecularMap );
	saver.Add( 12, &DarkMap );
	saver.Add( 13, &NormalMapPinValue );
	saver.Add( 14, &ShadowReciverPinValue );
	saver.Add( 15, &ShadowCasterPinValue );
	saver.Add( 16, &SpecularMapPinValue );
	saver.Add( 17, &EnvMapPinValue );
	saver.Add( 18, &DarkMapPinValue );
	saver.Add( 19, &TerrainUVSetPinValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TerrainMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TerrainMaterial* parentPtr = (TerrainMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "grassRect", &grassRect );
	saver.Add( "A_DiffuseMap", &A_DiffuseMap );
	saver.Add( "N_DiffuseMap", &N_DiffuseMap );
	saver.Add( "B_DiffuseMap", &B_DiffuseMap );
	saver.Add( "FrozenNormalMap", &FrozenNormalMap );
	saver.Add( "NormalNormalMap", &NormalNormalMap );
	saver.Add( "BurnedNormalMap", &BurnedNormalMap );
	saver.Add( "FrozenSpecularMap", &FrozenSpecularMap );
	saver.Add( "NormalSpecularMap", &NormalSpecularMap );
	saver.Add( "BurnedSpecularMap", &BurnedSpecularMap );
	saver.Add( "DarkMap", &DarkMap );
	saver.Add( "NormalMapPinValue", &NormalMapPinValue );
	saver.Add( "ShadowReciverPinValue", &ShadowReciverPinValue );
	saver.Add( "ShadowCasterPinValue", &ShadowCasterPinValue );
	saver.Add( "SpecularMapPinValue", &SpecularMapPinValue );
	saver.Add( "EnvMapPinValue", &EnvMapPinValue );
	saver.Add( "DarkMapPinValue", &DarkMapPinValue );
	saver.Add( "TerrainUVSetPinValue", &TerrainUVSetPinValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TerrainMaterial::Assign( const TerrainMaterial& _terrainMaterial )
{
	grassRect = _terrainMaterial.grassRect;
	A_DiffuseMap.samplerState.minFilter = _terrainMaterial.A_DiffuseMap.samplerState.minFilter;
	A_DiffuseMap.samplerState.magFilter = _terrainMaterial.A_DiffuseMap.samplerState.magFilter;
	A_DiffuseMap.samplerState.mipFilter = _terrainMaterial.A_DiffuseMap.samplerState.mipFilter;
	A_DiffuseMap.samplerState.addressU = _terrainMaterial.A_DiffuseMap.samplerState.addressU;
	A_DiffuseMap.samplerState.addressV = _terrainMaterial.A_DiffuseMap.samplerState.addressV;
	A_DiffuseMap.samplerState.addressW = _terrainMaterial.A_DiffuseMap.samplerState.addressW;
	A_DiffuseMap.texture = _terrainMaterial.A_DiffuseMap.texture;
	A_DiffuseMap.Multiplier = _terrainMaterial.A_DiffuseMap.Multiplier;
	A_DiffuseMap.Add = _terrainMaterial.A_DiffuseMap.Add;
	N_DiffuseMap.samplerState.minFilter = _terrainMaterial.N_DiffuseMap.samplerState.minFilter;
	N_DiffuseMap.samplerState.magFilter = _terrainMaterial.N_DiffuseMap.samplerState.magFilter;
	N_DiffuseMap.samplerState.mipFilter = _terrainMaterial.N_DiffuseMap.samplerState.mipFilter;
	N_DiffuseMap.samplerState.addressU = _terrainMaterial.N_DiffuseMap.samplerState.addressU;
	N_DiffuseMap.samplerState.addressV = _terrainMaterial.N_DiffuseMap.samplerState.addressV;
	N_DiffuseMap.samplerState.addressW = _terrainMaterial.N_DiffuseMap.samplerState.addressW;
	N_DiffuseMap.texture = _terrainMaterial.N_DiffuseMap.texture;
	N_DiffuseMap.Multiplier = _terrainMaterial.N_DiffuseMap.Multiplier;
	N_DiffuseMap.Add = _terrainMaterial.N_DiffuseMap.Add;
	B_DiffuseMap.samplerState.minFilter = _terrainMaterial.B_DiffuseMap.samplerState.minFilter;
	B_DiffuseMap.samplerState.magFilter = _terrainMaterial.B_DiffuseMap.samplerState.magFilter;
	B_DiffuseMap.samplerState.mipFilter = _terrainMaterial.B_DiffuseMap.samplerState.mipFilter;
	B_DiffuseMap.samplerState.addressU = _terrainMaterial.B_DiffuseMap.samplerState.addressU;
	B_DiffuseMap.samplerState.addressV = _terrainMaterial.B_DiffuseMap.samplerState.addressV;
	B_DiffuseMap.samplerState.addressW = _terrainMaterial.B_DiffuseMap.samplerState.addressW;
	B_DiffuseMap.texture = _terrainMaterial.B_DiffuseMap.texture;
	B_DiffuseMap.Multiplier = _terrainMaterial.B_DiffuseMap.Multiplier;
	B_DiffuseMap.Add = _terrainMaterial.B_DiffuseMap.Add;
	FrozenNormalMap.samplerState.minFilter = _terrainMaterial.FrozenNormalMap.samplerState.minFilter;
	FrozenNormalMap.samplerState.magFilter = _terrainMaterial.FrozenNormalMap.samplerState.magFilter;
	FrozenNormalMap.samplerState.mipFilter = _terrainMaterial.FrozenNormalMap.samplerState.mipFilter;
	FrozenNormalMap.samplerState.addressU = _terrainMaterial.FrozenNormalMap.samplerState.addressU;
	FrozenNormalMap.samplerState.addressV = _terrainMaterial.FrozenNormalMap.samplerState.addressV;
	FrozenNormalMap.samplerState.addressW = _terrainMaterial.FrozenNormalMap.samplerState.addressW;
	FrozenNormalMap.texture = _terrainMaterial.FrozenNormalMap.texture;
	FrozenNormalMap.Multiplier = _terrainMaterial.FrozenNormalMap.Multiplier;
	FrozenNormalMap.Add = _terrainMaterial.FrozenNormalMap.Add;
	NormalNormalMap.samplerState.minFilter = _terrainMaterial.NormalNormalMap.samplerState.minFilter;
	NormalNormalMap.samplerState.magFilter = _terrainMaterial.NormalNormalMap.samplerState.magFilter;
	NormalNormalMap.samplerState.mipFilter = _terrainMaterial.NormalNormalMap.samplerState.mipFilter;
	NormalNormalMap.samplerState.addressU = _terrainMaterial.NormalNormalMap.samplerState.addressU;
	NormalNormalMap.samplerState.addressV = _terrainMaterial.NormalNormalMap.samplerState.addressV;
	NormalNormalMap.samplerState.addressW = _terrainMaterial.NormalNormalMap.samplerState.addressW;
	NormalNormalMap.texture = _terrainMaterial.NormalNormalMap.texture;
	NormalNormalMap.Multiplier = _terrainMaterial.NormalNormalMap.Multiplier;
	NormalNormalMap.Add = _terrainMaterial.NormalNormalMap.Add;
	BurnedNormalMap.samplerState.minFilter = _terrainMaterial.BurnedNormalMap.samplerState.minFilter;
	BurnedNormalMap.samplerState.magFilter = _terrainMaterial.BurnedNormalMap.samplerState.magFilter;
	BurnedNormalMap.samplerState.mipFilter = _terrainMaterial.BurnedNormalMap.samplerState.mipFilter;
	BurnedNormalMap.samplerState.addressU = _terrainMaterial.BurnedNormalMap.samplerState.addressU;
	BurnedNormalMap.samplerState.addressV = _terrainMaterial.BurnedNormalMap.samplerState.addressV;
	BurnedNormalMap.samplerState.addressW = _terrainMaterial.BurnedNormalMap.samplerState.addressW;
	BurnedNormalMap.texture = _terrainMaterial.BurnedNormalMap.texture;
	BurnedNormalMap.Multiplier = _terrainMaterial.BurnedNormalMap.Multiplier;
	BurnedNormalMap.Add = _terrainMaterial.BurnedNormalMap.Add;
	FrozenSpecularMap.samplerState.minFilter = _terrainMaterial.FrozenSpecularMap.samplerState.minFilter;
	FrozenSpecularMap.samplerState.magFilter = _terrainMaterial.FrozenSpecularMap.samplerState.magFilter;
	FrozenSpecularMap.samplerState.mipFilter = _terrainMaterial.FrozenSpecularMap.samplerState.mipFilter;
	FrozenSpecularMap.samplerState.addressU = _terrainMaterial.FrozenSpecularMap.samplerState.addressU;
	FrozenSpecularMap.samplerState.addressV = _terrainMaterial.FrozenSpecularMap.samplerState.addressV;
	FrozenSpecularMap.samplerState.addressW = _terrainMaterial.FrozenSpecularMap.samplerState.addressW;
	FrozenSpecularMap.texture = _terrainMaterial.FrozenSpecularMap.texture;
	FrozenSpecularMap.Multiplier = _terrainMaterial.FrozenSpecularMap.Multiplier;
	FrozenSpecularMap.Add = _terrainMaterial.FrozenSpecularMap.Add;
	NormalSpecularMap.samplerState.minFilter = _terrainMaterial.NormalSpecularMap.samplerState.minFilter;
	NormalSpecularMap.samplerState.magFilter = _terrainMaterial.NormalSpecularMap.samplerState.magFilter;
	NormalSpecularMap.samplerState.mipFilter = _terrainMaterial.NormalSpecularMap.samplerState.mipFilter;
	NormalSpecularMap.samplerState.addressU = _terrainMaterial.NormalSpecularMap.samplerState.addressU;
	NormalSpecularMap.samplerState.addressV = _terrainMaterial.NormalSpecularMap.samplerState.addressV;
	NormalSpecularMap.samplerState.addressW = _terrainMaterial.NormalSpecularMap.samplerState.addressW;
	NormalSpecularMap.texture = _terrainMaterial.NormalSpecularMap.texture;
	NormalSpecularMap.Multiplier = _terrainMaterial.NormalSpecularMap.Multiplier;
	NormalSpecularMap.Add = _terrainMaterial.NormalSpecularMap.Add;
	BurnedSpecularMap.samplerState.minFilter = _terrainMaterial.BurnedSpecularMap.samplerState.minFilter;
	BurnedSpecularMap.samplerState.magFilter = _terrainMaterial.BurnedSpecularMap.samplerState.magFilter;
	BurnedSpecularMap.samplerState.mipFilter = _terrainMaterial.BurnedSpecularMap.samplerState.mipFilter;
	BurnedSpecularMap.samplerState.addressU = _terrainMaterial.BurnedSpecularMap.samplerState.addressU;
	BurnedSpecularMap.samplerState.addressV = _terrainMaterial.BurnedSpecularMap.samplerState.addressV;
	BurnedSpecularMap.samplerState.addressW = _terrainMaterial.BurnedSpecularMap.samplerState.addressW;
	BurnedSpecularMap.texture = _terrainMaterial.BurnedSpecularMap.texture;
	BurnedSpecularMap.Multiplier = _terrainMaterial.BurnedSpecularMap.Multiplier;
	BurnedSpecularMap.Add = _terrainMaterial.BurnedSpecularMap.Add;
	DarkMap.samplerState.minFilter = _terrainMaterial.DarkMap.samplerState.minFilter;
	DarkMap.samplerState.magFilter = _terrainMaterial.DarkMap.samplerState.magFilter;
	DarkMap.samplerState.mipFilter = _terrainMaterial.DarkMap.samplerState.mipFilter;
	DarkMap.samplerState.addressU = _terrainMaterial.DarkMap.samplerState.addressU;
	DarkMap.samplerState.addressV = _terrainMaterial.DarkMap.samplerState.addressV;
	DarkMap.samplerState.addressW = _terrainMaterial.DarkMap.samplerState.addressW;
	DarkMap.texture = _terrainMaterial.DarkMap.texture;
	DarkMap.Multiplier = _terrainMaterial.DarkMap.Multiplier;
	DarkMap.Add = _terrainMaterial.DarkMap.Add;
	NormalMapPinValue = _terrainMaterial.NormalMapPinValue;
	ShadowReciverPinValue = _terrainMaterial.ShadowReciverPinValue;
	ShadowCasterPinValue = _terrainMaterial.ShadowCasterPinValue;
	SpecularMapPinValue = _terrainMaterial.SpecularMapPinValue;
	EnvMapPinValue = _terrainMaterial.EnvMapPinValue;
	DarkMapPinValue = _terrainMaterial.DarkMapPinValue;
	TerrainUVSetPinValue = _terrainMaterial.TerrainUVSetPinValue;
	SubPriority = _terrainMaterial.SubPriority;
	caption = _terrainMaterial.caption;
	renderFlags = _terrainMaterial.renderFlags;
	ignoreRenderState = _terrainMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TestTownMaterial::TestTownMaterial() :
		UseDiffuse( BOOLEANPIN_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestTownMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &RenderState );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &UseDiffuse );
	saver.Add( 5, &outputMul );
	saver.Add( 6, &outputAdd );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestTownMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TestTownMaterial* parentPtr = (TestTownMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestTownMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "RenderState", &RenderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "UseDiffuse", &UseDiffuse );
	saver.Add( "outputMul", &outputMul );
	saver.Add( "outputAdd", &outputAdd );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestTownMaterial::Assign( const TestTownMaterial& _testTownMaterial )
{
	RenderState.blendMode = _testTownMaterial.RenderState.blendMode;
	RenderState.alphaTest = _testTownMaterial.RenderState.alphaTest;
	RenderState.alphaTestRef = _testTownMaterial.RenderState.alphaTestRef;
	RenderState.culling = _testTownMaterial.RenderState.culling;
	DiffuseMap.samplerState.minFilter = _testTownMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _testTownMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _testTownMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _testTownMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _testTownMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _testTownMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _testTownMaterial.DiffuseMap.texture;
	UseDiffuse = _testTownMaterial.UseDiffuse;
	outputMul = _testTownMaterial.outputMul;
	outputAdd = _testTownMaterial.outputAdd;
	SubPriority = _testTownMaterial.SubPriority;
	caption = _testTownMaterial.caption;
	renderFlags = _testTownMaterial.renderFlags;
	ignoreRenderState = _testTownMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureBase::TextureBase()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TextureBase::operator&( IBinSaver &saver )
{

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TextureBase::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TextureBase* parentPtr = (TextureBase*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextureBase::SerializeSelf( IXmlSaver &saver )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TextureBase::Assign( const TextureBase& _textureBase )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<Render::Texture> TextureBase::Load() const
{
	return ( CObj<Render::Texture> )(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Render::Texture> TextureBase::LoadInPool( bool canBeVisualDegrade, void * texturePoolId ) const
{
	return ( CObj<Render::Texture> )(0);
}
#endif // #ifndef VISUAL_CUTTED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TraceMaterial::TraceMaterial() :
		TraceTexturePinValue( BOOLEANPIN_NONE )
	, uScale( 1.0f )
	, vScale( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TraceMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &renderState );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &TraceTexturePinValue );
	saver.Add( 5, &uScale );
	saver.Add( 6, &vScale );
	saver.Add( 7, &uOffset );
	saver.Add( 8, &vOffset );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TraceMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			TraceMaterial* parentPtr = (TraceMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TraceMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "renderState", &renderState );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "TraceTexturePinValue", &TraceTexturePinValue );
	saver.Add( "uScale", &uScale );
	saver.Add( "vScale", &vScale );
	saver.Add( "uOffset", &uOffset );
	saver.Add( "vOffset", &vOffset );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TraceMaterial::Assign( const TraceMaterial& _traceMaterial )
{
	renderState.blendMode = _traceMaterial.renderState.blendMode;
	renderState.alphaTest = _traceMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _traceMaterial.renderState.alphaTestRef;
	renderState.culling = _traceMaterial.renderState.culling;
	DiffuseMap.samplerState.minFilter = _traceMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _traceMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _traceMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _traceMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _traceMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _traceMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _traceMaterial.DiffuseMap.texture;
	TraceTexturePinValue = _traceMaterial.TraceTexturePinValue;
	uScale = _traceMaterial.uScale;
	vScale = _traceMaterial.vScale;
	uOffset = _traceMaterial.uOffset;
	vOffset = _traceMaterial.vOffset;
	SubPriority = _traceMaterial.SubPriority;
	caption = _traceMaterial.caption;
	renderFlags = _traceMaterial.renderFlags;
	ignoreRenderState = _traceMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIBaseMaterial::UIBaseMaterial() :
		coef1( 0.0f )
	, coef2( 0.0f )
	, coef3( 0.0f )
	, coef4( 0.0f )
	, stripesStart( 0.0f )
	, stripesStep1( 100.0f )
	, stripesStep2( 1000.0f )
	, stripesBlendFactor1( 0.0f )
	, UseDiffuse( BOOLEANPIN_NONE )
	, Masking( MASKINGTYPEPIN_NOMASKING )
	, Gradient( BOOLEANPIN_NONE )
	, Colorized( BOOLEANPIN_NONE )
	, Stripes( BOOLEANPIN_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIBaseMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseUIMaterial*)this );
	saver.Add( 2, &DiffuseMap );
	saver.Add( 3, &MaskMap );
	saver.Add( 4, &color1 );
	saver.Add( 5, &color2 );
	saver.Add( 6, &coef1 );
	saver.Add( 7, &coef2 );
	saver.Add( 8, &coef3 );
	saver.Add( 9, &coef4 );
	saver.Add( 10, &stripesStart );
	saver.Add( 11, &stripesStep1 );
	saver.Add( 12, &stripesStep2 );
	saver.Add( 13, &stripesBlendFactor1 );
	saver.Add( 14, &UseDiffuse );
	saver.Add( 15, &Masking );
	saver.Add( 16, &Gradient );
	saver.Add( 17, &Colorized );
	saver.Add( 18, &Stripes );
	saver.Add( 19, &colorStripe100 );
	saver.Add( 20, &colorStripe1000 );
	saver.Add( 21, &renderState );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIBaseMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIBaseMaterial* parentPtr = (UIBaseMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIBaseMaterial::SerializeSelf( IXmlSaver &saver )
{
	BaseUIMaterial::SerializeSelf( saver );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "MaskMap", &MaskMap );
	saver.Add( "color1", &color1 );
	saver.Add( "color2", &color2 );
	saver.Add( "coef1", &coef1 );
	saver.Add( "coef2", &coef2 );
	saver.Add( "coef3", &coef3 );
	saver.Add( "coef4", &coef4 );
	saver.Add( "stripesStart", &stripesStart );
	saver.Add( "stripesStep1", &stripesStep1 );
	saver.Add( "stripesStep2", &stripesStep2 );
	saver.Add( "stripesBlendFactor1", &stripesBlendFactor1 );
	saver.Add( "UseDiffuse", &UseDiffuse );
	saver.Add( "Masking", &Masking );
	saver.Add( "Gradient", &Gradient );
	saver.Add( "Colorized", &Colorized );
	saver.Add( "Stripes", &Stripes );
	saver.Add( "colorStripe100", &colorStripe100 );
	saver.Add( "colorStripe1000", &colorStripe1000 );
	saver.Add( "renderState", &renderState );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIBaseMaterial::Assign( const UIBaseMaterial& _uIBaseMaterial )
{
	DiffuseMap.samplerState.minFilter = _uIBaseMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _uIBaseMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _uIBaseMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _uIBaseMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _uIBaseMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _uIBaseMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _uIBaseMaterial.DiffuseMap.texture;
	MaskMap.samplerState.minFilter = _uIBaseMaterial.MaskMap.samplerState.minFilter;
	MaskMap.samplerState.magFilter = _uIBaseMaterial.MaskMap.samplerState.magFilter;
	MaskMap.samplerState.mipFilter = _uIBaseMaterial.MaskMap.samplerState.mipFilter;
	MaskMap.samplerState.addressU = _uIBaseMaterial.MaskMap.samplerState.addressU;
	MaskMap.samplerState.addressV = _uIBaseMaterial.MaskMap.samplerState.addressV;
	MaskMap.samplerState.addressW = _uIBaseMaterial.MaskMap.samplerState.addressW;
	MaskMap.texture = _uIBaseMaterial.MaskMap.texture;
	color1 = _uIBaseMaterial.color1;
	color2 = _uIBaseMaterial.color2;
	coef1 = _uIBaseMaterial.coef1;
	coef2 = _uIBaseMaterial.coef2;
	coef3 = _uIBaseMaterial.coef3;
	coef4 = _uIBaseMaterial.coef4;
	stripesStart = _uIBaseMaterial.stripesStart;
	stripesStep1 = _uIBaseMaterial.stripesStep1;
	stripesStep2 = _uIBaseMaterial.stripesStep2;
	stripesBlendFactor1 = _uIBaseMaterial.stripesBlendFactor1;
	UseDiffuse = _uIBaseMaterial.UseDiffuse;
	Masking = _uIBaseMaterial.Masking;
	Gradient = _uIBaseMaterial.Gradient;
	Colorized = _uIBaseMaterial.Colorized;
	Stripes = _uIBaseMaterial.Stripes;
	colorStripe100 = _uIBaseMaterial.colorStripe100;
	colorStripe1000 = _uIBaseMaterial.colorStripe1000;
	renderState.blendMode = _uIBaseMaterial.renderState.blendMode;
	renderState.alphaTest = _uIBaseMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _uIBaseMaterial.renderState.alphaTestRef;
	renderState.culling = _uIBaseMaterial.renderState.culling;
	horizontalDrawMode = _uIBaseMaterial.horizontalDrawMode;
	verticalDrawMode = _uIBaseMaterial.verticalDrawMode;
	textureShift = _uIBaseMaterial.textureShift;
	imageSize = _uIBaseMaterial.imageSize;
	imageTileShift = _uIBaseMaterial.imageTileShift;
	imageTileSize = _uIBaseMaterial.imageTileSize;
	UseAutosize = _uIBaseMaterial.UseAutosize;
	SubPriority = _uIBaseMaterial.SubPriority;
	caption = _uIBaseMaterial.caption;
	renderFlags = _uIBaseMaterial.renderFlags;
	ignoreRenderState = _uIBaseMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIButtonMaterial::UIButtonMaterial() :
		WaitForActivationPin( BOOLEANPIN_NONE )
	, LackOfManaPin( BOOLEANPIN_NONE )
	, PressedPin( BOOLEANPIN_NONE )
	, HighlightPin( BOOLEANPIN_NONE )
	, DisablePin( BOOLEANPIN_NONE )
	, PassivePin( BOOLEANPIN_NONE )
	, UseDiffusePin( BOOLEANPIN_PRESENT )
	, ScreenOpacity( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIButtonMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseUIMaterial*)this );
	saver.Add( 2, &BackgroundMap );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &WaitForActMap );
	saver.Add( 5, &LackOfManaMap );
	saver.Add( 6, &PressedMap );
	saver.Add( 7, &HighlightMap );
	saver.Add( 8, &ScreenMap );
	saver.Add( 9, &WaitForActivationPin );
	saver.Add( 10, &LackOfManaPin );
	saver.Add( 11, &PressedPin );
	saver.Add( 12, &HighlightPin );
	saver.Add( 13, &DisablePin );
	saver.Add( 14, &PassivePin );
	saver.Add( 15, &UseDiffusePin );
	saver.Add( 16, &ScreenOpacity );
	saver.Add( 17, &renderState );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIButtonMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIButtonMaterial* parentPtr = (UIButtonMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIButtonMaterial::SerializeSelf( IXmlSaver &saver )
{
	BaseUIMaterial::SerializeSelf( saver );
	saver.Add( "BackgroundMap", &BackgroundMap );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "WaitForActMap", &WaitForActMap );
	saver.Add( "LackOfManaMap", &LackOfManaMap );
	saver.Add( "PressedMap", &PressedMap );
	saver.Add( "HighlightMap", &HighlightMap );
	saver.Add( "ScreenMap", &ScreenMap );
	saver.Add( "WaitForActivationPin", &WaitForActivationPin );
	saver.Add( "LackOfManaPin", &LackOfManaPin );
	saver.Add( "PressedPin", &PressedPin );
	saver.Add( "HighlightPin", &HighlightPin );
	saver.Add( "DisablePin", &DisablePin );
	saver.Add( "PassivePin", &PassivePin );
	saver.Add( "UseDiffusePin", &UseDiffusePin );
	saver.Add( "ScreenOpacity", &ScreenOpacity );
	saver.Add( "renderState", &renderState );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIButtonMaterial::Assign( const UIButtonMaterial& _uIButtonMaterial )
{
	BackgroundMap.samplerState.minFilter = _uIButtonMaterial.BackgroundMap.samplerState.minFilter;
	BackgroundMap.samplerState.magFilter = _uIButtonMaterial.BackgroundMap.samplerState.magFilter;
	BackgroundMap.samplerState.mipFilter = _uIButtonMaterial.BackgroundMap.samplerState.mipFilter;
	BackgroundMap.samplerState.addressU = _uIButtonMaterial.BackgroundMap.samplerState.addressU;
	BackgroundMap.samplerState.addressV = _uIButtonMaterial.BackgroundMap.samplerState.addressV;
	BackgroundMap.samplerState.addressW = _uIButtonMaterial.BackgroundMap.samplerState.addressW;
	BackgroundMap.texture = _uIButtonMaterial.BackgroundMap.texture;
	DiffuseMap.samplerState.minFilter = _uIButtonMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _uIButtonMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _uIButtonMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _uIButtonMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _uIButtonMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _uIButtonMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _uIButtonMaterial.DiffuseMap.texture;
	WaitForActMap.samplerState.minFilter = _uIButtonMaterial.WaitForActMap.samplerState.minFilter;
	WaitForActMap.samplerState.magFilter = _uIButtonMaterial.WaitForActMap.samplerState.magFilter;
	WaitForActMap.samplerState.mipFilter = _uIButtonMaterial.WaitForActMap.samplerState.mipFilter;
	WaitForActMap.samplerState.addressU = _uIButtonMaterial.WaitForActMap.samplerState.addressU;
	WaitForActMap.samplerState.addressV = _uIButtonMaterial.WaitForActMap.samplerState.addressV;
	WaitForActMap.samplerState.addressW = _uIButtonMaterial.WaitForActMap.samplerState.addressW;
	WaitForActMap.texture = _uIButtonMaterial.WaitForActMap.texture;
	LackOfManaMap.samplerState.minFilter = _uIButtonMaterial.LackOfManaMap.samplerState.minFilter;
	LackOfManaMap.samplerState.magFilter = _uIButtonMaterial.LackOfManaMap.samplerState.magFilter;
	LackOfManaMap.samplerState.mipFilter = _uIButtonMaterial.LackOfManaMap.samplerState.mipFilter;
	LackOfManaMap.samplerState.addressU = _uIButtonMaterial.LackOfManaMap.samplerState.addressU;
	LackOfManaMap.samplerState.addressV = _uIButtonMaterial.LackOfManaMap.samplerState.addressV;
	LackOfManaMap.samplerState.addressW = _uIButtonMaterial.LackOfManaMap.samplerState.addressW;
	LackOfManaMap.texture = _uIButtonMaterial.LackOfManaMap.texture;
	PressedMap.samplerState.minFilter = _uIButtonMaterial.PressedMap.samplerState.minFilter;
	PressedMap.samplerState.magFilter = _uIButtonMaterial.PressedMap.samplerState.magFilter;
	PressedMap.samplerState.mipFilter = _uIButtonMaterial.PressedMap.samplerState.mipFilter;
	PressedMap.samplerState.addressU = _uIButtonMaterial.PressedMap.samplerState.addressU;
	PressedMap.samplerState.addressV = _uIButtonMaterial.PressedMap.samplerState.addressV;
	PressedMap.samplerState.addressW = _uIButtonMaterial.PressedMap.samplerState.addressW;
	PressedMap.texture = _uIButtonMaterial.PressedMap.texture;
	HighlightMap.samplerState.minFilter = _uIButtonMaterial.HighlightMap.samplerState.minFilter;
	HighlightMap.samplerState.magFilter = _uIButtonMaterial.HighlightMap.samplerState.magFilter;
	HighlightMap.samplerState.mipFilter = _uIButtonMaterial.HighlightMap.samplerState.mipFilter;
	HighlightMap.samplerState.addressU = _uIButtonMaterial.HighlightMap.samplerState.addressU;
	HighlightMap.samplerState.addressV = _uIButtonMaterial.HighlightMap.samplerState.addressV;
	HighlightMap.samplerState.addressW = _uIButtonMaterial.HighlightMap.samplerState.addressW;
	HighlightMap.texture = _uIButtonMaterial.HighlightMap.texture;
	ScreenMap.samplerState.minFilter = _uIButtonMaterial.ScreenMap.samplerState.minFilter;
	ScreenMap.samplerState.magFilter = _uIButtonMaterial.ScreenMap.samplerState.magFilter;
	ScreenMap.samplerState.mipFilter = _uIButtonMaterial.ScreenMap.samplerState.mipFilter;
	ScreenMap.samplerState.addressU = _uIButtonMaterial.ScreenMap.samplerState.addressU;
	ScreenMap.samplerState.addressV = _uIButtonMaterial.ScreenMap.samplerState.addressV;
	ScreenMap.samplerState.addressW = _uIButtonMaterial.ScreenMap.samplerState.addressW;
	ScreenMap.texture = _uIButtonMaterial.ScreenMap.texture;
	WaitForActivationPin = _uIButtonMaterial.WaitForActivationPin;
	LackOfManaPin = _uIButtonMaterial.LackOfManaPin;
	PressedPin = _uIButtonMaterial.PressedPin;
	HighlightPin = _uIButtonMaterial.HighlightPin;
	DisablePin = _uIButtonMaterial.DisablePin;
	PassivePin = _uIButtonMaterial.PassivePin;
	UseDiffusePin = _uIButtonMaterial.UseDiffusePin;
	ScreenOpacity = _uIButtonMaterial.ScreenOpacity;
	renderState.blendMode = _uIButtonMaterial.renderState.blendMode;
	renderState.alphaTest = _uIButtonMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _uIButtonMaterial.renderState.alphaTestRef;
	renderState.culling = _uIButtonMaterial.renderState.culling;
	horizontalDrawMode = _uIButtonMaterial.horizontalDrawMode;
	verticalDrawMode = _uIButtonMaterial.verticalDrawMode;
	textureShift = _uIButtonMaterial.textureShift;
	imageSize = _uIButtonMaterial.imageSize;
	imageTileShift = _uIButtonMaterial.imageTileShift;
	imageTileSize = _uIButtonMaterial.imageTileSize;
	UseAutosize = _uIButtonMaterial.UseAutosize;
	SubPriority = _uIButtonMaterial.SubPriority;
	caption = _uIButtonMaterial.caption;
	renderFlags = _uIButtonMaterial.renderFlags;
	ignoreRenderState = _uIButtonMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIFlashMaterial::UIFlashMaterial() :
		UseDiffuse( BOOLEANPIN_NONE )
	, UseDiffuse2( BOOLEANPIN_NONE )
	, MorphShapes( BOOLEANPIN_NONE )
	, ShaderForLines( BOOLEANPIN_NONE )
	, UseColorFilter( BOOLEANPIN_NONE )
	, Scale9Grid( BOOLEANPIN_NONE )
	, Scale9GridBitmap( BOOLEANPIN_NONE )
	, FlashBlendMode( FLASHBLENDMODEPIN__NORMAL )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFlashMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &DiffuseMap );
	saver.Add( 3, &DiffuseMap2 );
	saver.Add( 4, &UseDiffuse );
	saver.Add( 5, &UseDiffuse2 );
	saver.Add( 6, &MorphShapes );
	saver.Add( 7, &ShaderForLines );
	saver.Add( 8, &UseColorFilter );
	saver.Add( 9, &Scale9Grid );
	saver.Add( 10, &Scale9GridBitmap );
	saver.Add( 11, &FlashBlendMode );
	saver.Add( 12, &CXFormMul );
	saver.Add( 13, &CXFormAdd );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFlashMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIFlashMaterial* parentPtr = (UIFlashMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlashMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "DiffuseMap2", &DiffuseMap2 );
	saver.Add( "UseDiffuse", &UseDiffuse );
	saver.Add( "UseDiffuse2", &UseDiffuse2 );
	saver.Add( "MorphShapes", &MorphShapes );
	saver.Add( "ShaderForLines", &ShaderForLines );
	saver.Add( "UseColorFilter", &UseColorFilter );
	saver.Add( "Scale9Grid", &Scale9Grid );
	saver.Add( "Scale9GridBitmap", &Scale9GridBitmap );
	saver.Add( "FlashBlendMode", &FlashBlendMode );
	saver.Add( "CXFormMul", &CXFormMul );
	saver.Add( "CXFormAdd", &CXFormAdd );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFlashMaterial::Assign( const UIFlashMaterial& _uIFlashMaterial )
{
	DiffuseMap.samplerState.minFilter = _uIFlashMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _uIFlashMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _uIFlashMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _uIFlashMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _uIFlashMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _uIFlashMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _uIFlashMaterial.DiffuseMap.texture;
	DiffuseMap2.samplerState.minFilter = _uIFlashMaterial.DiffuseMap2.samplerState.minFilter;
	DiffuseMap2.samplerState.magFilter = _uIFlashMaterial.DiffuseMap2.samplerState.magFilter;
	DiffuseMap2.samplerState.mipFilter = _uIFlashMaterial.DiffuseMap2.samplerState.mipFilter;
	DiffuseMap2.samplerState.addressU = _uIFlashMaterial.DiffuseMap2.samplerState.addressU;
	DiffuseMap2.samplerState.addressV = _uIFlashMaterial.DiffuseMap2.samplerState.addressV;
	DiffuseMap2.samplerState.addressW = _uIFlashMaterial.DiffuseMap2.samplerState.addressW;
	DiffuseMap2.texture = _uIFlashMaterial.DiffuseMap2.texture;
	UseDiffuse = _uIFlashMaterial.UseDiffuse;
	UseDiffuse2 = _uIFlashMaterial.UseDiffuse2;
	MorphShapes = _uIFlashMaterial.MorphShapes;
	ShaderForLines = _uIFlashMaterial.ShaderForLines;
	UseColorFilter = _uIFlashMaterial.UseColorFilter;
	Scale9Grid = _uIFlashMaterial.Scale9Grid;
	Scale9GridBitmap = _uIFlashMaterial.Scale9GridBitmap;
	FlashBlendMode = _uIFlashMaterial.FlashBlendMode;
	CXFormMul = _uIFlashMaterial.CXFormMul;
	CXFormAdd = _uIFlashMaterial.CXFormAdd;
	SubPriority = _uIFlashMaterial.SubPriority;
	caption = _uIFlashMaterial.caption;
	renderFlags = _uIFlashMaterial.renderFlags;
	ignoreRenderState = _uIFlashMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIFontMaterial::UIFontMaterial() :
		UseDiffuse( BOOLEANPIN_NONE )
	, DrawContour( BOOLEANPIN_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFontMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &DiffuseMap );
	saver.Add( 3, &UseDiffuse );
	saver.Add( 4, &DrawContour );
	saver.Add( 5, &PrimaryColor );
	saver.Add( 6, &SecondaryColor );
	saver.Add( 7, &renderState );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIFontMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIFontMaterial* parentPtr = (UIFontMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFontMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "UseDiffuse", &UseDiffuse );
	saver.Add( "DrawContour", &DrawContour );
	saver.Add( "PrimaryColor", &PrimaryColor );
	saver.Add( "SecondaryColor", &SecondaryColor );
	saver.Add( "renderState", &renderState );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIFontMaterial::Assign( const UIFontMaterial& _uIFontMaterial )
{
	DiffuseMap.samplerState.minFilter = _uIFontMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _uIFontMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _uIFontMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _uIFontMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _uIFontMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _uIFontMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _uIFontMaterial.DiffuseMap.texture;
	UseDiffuse = _uIFontMaterial.UseDiffuse;
	DrawContour = _uIFontMaterial.DrawContour;
	PrimaryColor = _uIFontMaterial.PrimaryColor;
	SecondaryColor = _uIFontMaterial.SecondaryColor;
	renderState.blendMode = _uIFontMaterial.renderState.blendMode;
	renderState.alphaTest = _uIFontMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _uIFontMaterial.renderState.alphaTestRef;
	renderState.culling = _uIFontMaterial.renderState.culling;
	SubPriority = _uIFontMaterial.SubPriority;
	caption = _uIFontMaterial.caption;
	renderFlags = _uIFontMaterial.renderFlags;
	ignoreRenderState = _uIFontMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIGlassMaterial::UIGlassMaterial() :
		OverlayOpacity( 1.0f )
	, ScreenOpacity( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIGlassMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (BaseUIMaterial*)this );
	saver.Add( 2, &BackgroundMap );
	saver.Add( 3, &DiffuseMap );
	saver.Add( 4, &OverlayMap );
	saver.Add( 5, &ScreenMap );
	saver.Add( 6, &OverlayOpacity );
	saver.Add( 7, &ScreenOpacity );
	saver.Add( 8, &renderState );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UIGlassMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			UIGlassMaterial* parentPtr = (UIGlassMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIGlassMaterial::SerializeSelf( IXmlSaver &saver )
{
	BaseUIMaterial::SerializeSelf( saver );
	saver.Add( "BackgroundMap", &BackgroundMap );
	saver.Add( "DiffuseMap", &DiffuseMap );
	saver.Add( "OverlayMap", &OverlayMap );
	saver.Add( "ScreenMap", &ScreenMap );
	saver.Add( "OverlayOpacity", &OverlayOpacity );
	saver.Add( "ScreenOpacity", &ScreenOpacity );
	saver.Add( "renderState", &renderState );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIGlassMaterial::Assign( const UIGlassMaterial& _uIGlassMaterial )
{
	BackgroundMap.samplerState.minFilter = _uIGlassMaterial.BackgroundMap.samplerState.minFilter;
	BackgroundMap.samplerState.magFilter = _uIGlassMaterial.BackgroundMap.samplerState.magFilter;
	BackgroundMap.samplerState.mipFilter = _uIGlassMaterial.BackgroundMap.samplerState.mipFilter;
	BackgroundMap.samplerState.addressU = _uIGlassMaterial.BackgroundMap.samplerState.addressU;
	BackgroundMap.samplerState.addressV = _uIGlassMaterial.BackgroundMap.samplerState.addressV;
	BackgroundMap.samplerState.addressW = _uIGlassMaterial.BackgroundMap.samplerState.addressW;
	BackgroundMap.texture = _uIGlassMaterial.BackgroundMap.texture;
	DiffuseMap.samplerState.minFilter = _uIGlassMaterial.DiffuseMap.samplerState.minFilter;
	DiffuseMap.samplerState.magFilter = _uIGlassMaterial.DiffuseMap.samplerState.magFilter;
	DiffuseMap.samplerState.mipFilter = _uIGlassMaterial.DiffuseMap.samplerState.mipFilter;
	DiffuseMap.samplerState.addressU = _uIGlassMaterial.DiffuseMap.samplerState.addressU;
	DiffuseMap.samplerState.addressV = _uIGlassMaterial.DiffuseMap.samplerState.addressV;
	DiffuseMap.samplerState.addressW = _uIGlassMaterial.DiffuseMap.samplerState.addressW;
	DiffuseMap.texture = _uIGlassMaterial.DiffuseMap.texture;
	OverlayMap.samplerState.minFilter = _uIGlassMaterial.OverlayMap.samplerState.minFilter;
	OverlayMap.samplerState.magFilter = _uIGlassMaterial.OverlayMap.samplerState.magFilter;
	OverlayMap.samplerState.mipFilter = _uIGlassMaterial.OverlayMap.samplerState.mipFilter;
	OverlayMap.samplerState.addressU = _uIGlassMaterial.OverlayMap.samplerState.addressU;
	OverlayMap.samplerState.addressV = _uIGlassMaterial.OverlayMap.samplerState.addressV;
	OverlayMap.samplerState.addressW = _uIGlassMaterial.OverlayMap.samplerState.addressW;
	OverlayMap.texture = _uIGlassMaterial.OverlayMap.texture;
	ScreenMap.samplerState.minFilter = _uIGlassMaterial.ScreenMap.samplerState.minFilter;
	ScreenMap.samplerState.magFilter = _uIGlassMaterial.ScreenMap.samplerState.magFilter;
	ScreenMap.samplerState.mipFilter = _uIGlassMaterial.ScreenMap.samplerState.mipFilter;
	ScreenMap.samplerState.addressU = _uIGlassMaterial.ScreenMap.samplerState.addressU;
	ScreenMap.samplerState.addressV = _uIGlassMaterial.ScreenMap.samplerState.addressV;
	ScreenMap.samplerState.addressW = _uIGlassMaterial.ScreenMap.samplerState.addressW;
	ScreenMap.texture = _uIGlassMaterial.ScreenMap.texture;
	OverlayOpacity = _uIGlassMaterial.OverlayOpacity;
	ScreenOpacity = _uIGlassMaterial.ScreenOpacity;
	renderState.blendMode = _uIGlassMaterial.renderState.blendMode;
	renderState.alphaTest = _uIGlassMaterial.renderState.alphaTest;
	renderState.alphaTestRef = _uIGlassMaterial.renderState.alphaTestRef;
	renderState.culling = _uIGlassMaterial.renderState.culling;
	horizontalDrawMode = _uIGlassMaterial.horizontalDrawMode;
	verticalDrawMode = _uIGlassMaterial.verticalDrawMode;
	textureShift = _uIGlassMaterial.textureShift;
	imageSize = _uIGlassMaterial.imageSize;
	imageTileShift = _uIGlassMaterial.imageTileShift;
	imageTileSize = _uIGlassMaterial.imageTileSize;
	UseAutosize = _uIGlassMaterial.UseAutosize;
	SubPriority = _uIGlassMaterial.SubPriority;
	caption = _uIGlassMaterial.caption;
	renderFlags = _uIGlassMaterial.renderFlags;
	ignoreRenderState = _uIGlassMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WaterDummyMaterial::WaterDummyMaterial()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WaterDummyMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WaterDummyMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			WaterDummyMaterial* parentPtr = (WaterDummyMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterDummyMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterDummyMaterial::Assign( const WaterDummyMaterial& _waterDummyMaterial )
{
	SubPriority = _waterDummyMaterial.SubPriority;
	caption = _waterDummyMaterial.caption;
	renderFlags = _waterDummyMaterial.renderFlags;
	ignoreRenderState = _waterDummyMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WaterMapMaterial::WaterMapMaterial()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WaterMapMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WaterMapMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			WaterMapMaterial* parentPtr = (WaterMapMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterMapMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterMapMaterial::Assign( const WaterMapMaterial& _waterMapMaterial )
{
	SubPriority = _waterMapMaterial.SubPriority;
	caption = _waterMapMaterial.caption;
	renderFlags = _waterMapMaterial.renderFlags;
	ignoreRenderState = _waterMapMaterial.ignoreRenderState;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WaterMaterial::WaterMaterial() :
		CausticsTexturePinValue( BOOLEANPIN_NONE )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WaterMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (Material*)this );
	saver.Add( 2, &CausticsTexturePinValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int WaterMaterial::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			WaterMaterial* parentPtr = (WaterMaterial*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterMaterial::SerializeSelf( IXmlSaver &saver )
{
	Material::SerializeSelf( saver );
	saver.Add( "CausticsTexturePinValue", &CausticsTexturePinValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WaterMaterial::Assign( const WaterMaterial& _waterMaterial )
{
	CausticsTexturePinValue = _waterMaterial.CausticsTexturePinValue;
	SubPriority = _waterMaterial.SubPriority;
	caption = _waterMaterial.caption;
	renderFlags = _waterMaterial.renderFlags;
	ignoreRenderState = _waterMaterial.ignoreRenderState;
}
}; // namespace NDb
