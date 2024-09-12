// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../Render/DBRender.h"
#include "DBRenderResources.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( AnimGraphCreator );
REGISTER_DBRESOURCE( OmniLight );
REGISTER_DBRESOURCE( PaintPackedMasks );
REGISTER_DBRESOURCE( ParticleFX );
REGISTER_DBRESOURCE( Skeleton );
REGISTER_DBRESOURCE( StaticMesh );
REGISTER_DBRESOURCE( Texture );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// includes for factories
#ifndef VISUAL_CUTTED
#include "TextureManager.h"
#endif // #ifndef VISUAL_CUTTED

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAnGrMarkerOwner value )
{
	switch( value )
	{
		case ANGRMARKEROWNER_ANGRM_NODE:
			return "ANGRM_NODE";
		case ANGRMARKEROWNER_ANGRM_TRANSACTION:
			return "ANGRM_TRANSACTION";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAnGrMarkerOwner", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAnGrMarkerOwner StringToEnum_EAnGrMarkerOwner( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAnGrMarkerOwner)(NStr::ToInt( value ));
	if ( strcmp( value, "ANGRM_NODE" ) == 0 || strcmp( value, "ANGRMARKEROWNER_ANGRM_NODE" ) == 0 )
		return ANGRMARKEROWNER_ANGRM_NODE;
	if ( strcmp( value, "ANGRM_TRANSACTION" ) == 0 || strcmp( value, "ANGRMARKEROWNER_ANGRM_TRANSACTION" ) == 0 )
		return ANGRMARKEROWNER_ANGRM_TRANSACTION;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAnGrMarkerOwner", value ) );
	return ANGRMARKEROWNER_ANGRM_NODE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAnGrNodeType value )
{
	switch( value )
	{
		case ANGRNODETYPE_NORMAL:
			return "Normal";
		case ANGRNODETYPE_DISPATCHER:
			return "Dispatcher";
		case ANGRNODETYPE_SUBNODE:
			return "SubNode";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAnGrNodeType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAnGrNodeType StringToEnum_EAnGrNodeType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAnGrNodeType)(NStr::ToInt( value ));
	if ( strcmp( value, "Normal" ) == 0 || strcmp( value, "ANGRNODETYPE_NORMAL" ) == 0 )
		return ANGRNODETYPE_NORMAL;
	if ( strcmp( value, "Dispatcher" ) == 0 || strcmp( value, "ANGRNODETYPE_DISPATCHER" ) == 0 )
		return ANGRNODETYPE_DISPATCHER;
	if ( strcmp( value, "SubNode" ) == 0 || strcmp( value, "ANGRNODETYPE_SUBNODE" ) == 0 )
		return ANGRNODETYPE_SUBNODE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAnGrNodeType", value ) );
	return ANGRNODETYPE_NORMAL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAnGrTransactionKind value )
{
	switch( value )
	{
		case ANGRTRANSACTIONKIND_UNIFORM:
			return "Uniform";
		case ANGRTRANSACTIONKIND_PARABOLIC3:
			return "Parabolic3";
		case ANGRTRANSACTIONKIND_RECPARABOLIC3:
			return "RecParabolic3";
		case ANGRTRANSACTIONKIND_SINE:
			return "Sine";
		case ANGRTRANSACTIONKIND_RECSINE:
			return "RecSine";
		case ANGRTRANSACTIONKIND_SPLINE:
			return "Spline";
		case ANGRTRANSACTIONKIND_RECSPLINE:
			return "RecSpline";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAnGrTransactionKind", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAnGrTransactionKind StringToEnum_EAnGrTransactionKind( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAnGrTransactionKind)(NStr::ToInt( value ));
	if ( strcmp( value, "Uniform" ) == 0 || strcmp( value, "ANGRTRANSACTIONKIND_UNIFORM" ) == 0 )
		return ANGRTRANSACTIONKIND_UNIFORM;
	if ( strcmp( value, "Parabolic3" ) == 0 || strcmp( value, "ANGRTRANSACTIONKIND_PARABOLIC3" ) == 0 )
		return ANGRTRANSACTIONKIND_PARABOLIC3;
	if ( strcmp( value, "RecParabolic3" ) == 0 || strcmp( value, "ANGRTRANSACTIONKIND_RECPARABOLIC3" ) == 0 )
		return ANGRTRANSACTIONKIND_RECPARABOLIC3;
	if ( strcmp( value, "Sine" ) == 0 || strcmp( value, "ANGRTRANSACTIONKIND_SINE" ) == 0 )
		return ANGRTRANSACTIONKIND_SINE;
	if ( strcmp( value, "RecSine" ) == 0 || strcmp( value, "ANGRTRANSACTIONKIND_RECSINE" ) == 0 )
		return ANGRTRANSACTIONKIND_RECSINE;
	if ( strcmp( value, "Spline" ) == 0 || strcmp( value, "ANGRTRANSACTIONKIND_SPLINE" ) == 0 )
		return ANGRTRANSACTIONKIND_SPLINE;
	if ( strcmp( value, "RecSpline" ) == 0 || strcmp( value, "ANGRTRANSACTIONKIND_RECSPLINE" ) == 0 )
		return ANGRTRANSACTIONKIND_RECSPLINE;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAnGrTransactionKind", value ) );
	return ANGRTRANSACTIONKIND_UNIFORM;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EAnGrTransactionUpdate value )
{
	switch( value )
	{
		case ANGRTRANSACTIONUPDATE_POSETOPOSE:
			return "PoseToPose";
		case ANGRTRANSACTIONUPDATE_ANIMTOPOSE:
			return "AnimToPose";
		case ANGRTRANSACTIONUPDATE_POSETOANIM:
			return "PoseToAnim";
		case ANGRTRANSACTIONUPDATE_ANIMTOANIM:
			return "AnimToAnim";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum EAnGrTransactionUpdate", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EAnGrTransactionUpdate StringToEnum_EAnGrTransactionUpdate( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EAnGrTransactionUpdate)(NStr::ToInt( value ));
	if ( strcmp( value, "PoseToPose" ) == 0 || strcmp( value, "ANGRTRANSACTIONUPDATE_POSETOPOSE" ) == 0 )
		return ANGRTRANSACTIONUPDATE_POSETOPOSE;
	if ( strcmp( value, "AnimToPose" ) == 0 || strcmp( value, "ANGRTRANSACTIONUPDATE_ANIMTOPOSE" ) == 0 )
		return ANGRTRANSACTIONUPDATE_ANIMTOPOSE;
	if ( strcmp( value, "PoseToAnim" ) == 0 || strcmp( value, "ANGRTRANSACTIONUPDATE_POSETOANIM" ) == 0 )
		return ANGRTRANSACTIONUPDATE_POSETOANIM;
	if ( strcmp( value, "AnimToAnim" ) == 0 || strcmp( value, "ANGRTRANSACTIONUPDATE_ANIMTOANIM" ) == 0 )
		return ANGRTRANSACTIONUPDATE_ANIMTOANIM;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EAnGrTransactionUpdate", value ) );
	return ANGRTRANSACTIONUPDATE_POSETOPOSE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const EGeometryUsageFlags value )
{
	switch( value )
	{
		case GEOMETRYUSAGEFLAGS_NONE:
			return "None";
		case GEOMETRYUSAGEFLAGS_LIGHTING:
			return "Lighting";
		case GEOMETRYUSAGEFLAGS_NORMALMAPPING:
			return "NormalMapping";
		case GEOMETRYUSAGEFLAGS_VERTEXCOLORS:
			return "VertexColors";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const EGeometryUsageFlags StringToEnum_EGeometryUsageFlags( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (EGeometryUsageFlags)(NStr::ToInt( value ));
	if ( strcmp( value, "None" ) == 0 || strcmp( value, "GEOMETRYUSAGEFLAGS_NONE" ) == 0 )
		return GEOMETRYUSAGEFLAGS_NONE;
	if ( strcmp( value, "Lighting" ) == 0 || strcmp( value, "GEOMETRYUSAGEFLAGS_LIGHTING" ) == 0 )
		return GEOMETRYUSAGEFLAGS_LIGHTING;
	if ( strcmp( value, "NormalMapping" ) == 0 || strcmp( value, "GEOMETRYUSAGEFLAGS_NORMALMAPPING" ) == 0 )
		return GEOMETRYUSAGEFLAGS_NORMALMAPPING;
	if ( strcmp( value, "VertexColors" ) == 0 || strcmp( value, "GEOMETRYUSAGEFLAGS_VERTEXCOLORS" ) == 0 )
		return GEOMETRYUSAGEFLAGS_VERTEXCOLORS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum EGeometryUsageFlags", value ) );
	return GEOMETRYUSAGEFLAGS_NONE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const MipLevel value )
{
	switch( value )
	{
		case MIPLEVEL_AUTOGENERATE:
			return "AutoGenerate";
		case MIPLEVEL_NOMIPS:
			return "NoMips";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum MipLevel", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const MipLevel StringToEnum_MipLevel( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (MipLevel)(NStr::ToInt( value ));
	if ( strcmp( value, "AutoGenerate" ) == 0 || strcmp( value, "MIPLEVEL_AUTOGENERATE" ) == 0 )
		return MIPLEVEL_AUTOGENERATE;
	if ( strcmp( value, "NoMips" ) == 0 || strcmp( value, "MIPLEVEL_NOMIPS" ) == 0 )
		return MIPLEVEL_NOMIPS;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum MipLevel", value ) );
	return MIPLEVEL_AUTOGENERATE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const TextureType value )
{
	switch( value )
	{
		case TEXTURETYPE_COLOR:
			return "Color";
		case TEXTURETYPE_NORMAL:
			return "Normal";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum TextureType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const TextureType StringToEnum_TextureType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (TextureType)(NStr::ToInt( value ));
	if ( strcmp( value, "Color" ) == 0 || strcmp( value, "TEXTURETYPE_COLOR" ) == 0 )
		return TEXTURETYPE_COLOR;
	if ( strcmp( value, "Normal" ) == 0 || strcmp( value, "TEXTURETYPE_NORMAL" ) == 0 )
		return TEXTURETYPE_NORMAL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum TextureType", value ) );
	return TEXTURETYPE_COLOR;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AABB::AABB() :
		minX( 0.0f )
	, maxX( 0.0f )
	, minY( 0.0f )
	, maxY( 0.0f )
	, minZ( 0.0f )
	, maxZ( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AABB::operator&( IBinSaver &saver )
{
	saver.Add( 2, &minX );
	saver.Add( 3, &maxX );
	saver.Add( 4, &minY );
	saver.Add( 5, &maxY );
	saver.Add( 6, &minZ );
	saver.Add( 7, &maxZ );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AABB::operator&( IXmlSaver &saver )
{
	saver.Add( "minX", &minX );
	saver.Add( "maxX", &maxX );
	saver.Add( "minY", &minY );
	saver.Add( "maxY", &maxY );
	saver.Add( "minZ", &minZ );
	saver.Add( "maxZ", &maxZ );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnGrExternalParameter::AnGrExternalParameter() :
		paramName( "CHANGE_NAME!" )
	, defaultValue( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrExternalParameter::operator&( IBinSaver &saver )
{
	saver.Add( 2, &paramName );
	saver.Add( 3, &defaultValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrExternalParameter::operator&( IXmlSaver &saver )
{
	saver.Add( "paramName", &paramName );
	saver.Add( "defaultValue", &defaultValue );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnGrExternalParameterCoeff::AnGrExternalParameterCoeff() :
		value( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrExternalParameterCoeff::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &value );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrExternalParameterCoeff::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "value", &value );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnGrFormula::AnGrFormula() :
		value( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrFormula::operator&( IBinSaver &saver )
{
	saver.Add( 2, &value );
	saver.Add( 3, &coeffs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrFormula::operator&( IXmlSaver &saver )
{
	saver.Add( "value", &value );
	saver.Add( "coeffs", &coeffs );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnGrMarker::AnGrMarker() :
		name( "newmarker" )
	, virtPar( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrMarker::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &virtPar );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrMarker::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "virtPar", &virtPar );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnGrFlTransaction::AnGrFlTransaction() :
		blending( ANGRTRANSACTIONUPDATE_POSETOANIM )
	, kind( ANGRTRANSACTIONKIND_UNIFORM )
	, duration( 0.3f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrFlTransaction::operator&( IBinSaver &saver )
{
	saver.Add( 2, &blending );
	saver.Add( 3, &kind );
	saver.Add( 4, &parA );
	saver.Add( 5, &parB );
	saver.Add( 6, &fromMin );
	saver.Add( 7, &fromMax );
	saver.Add( 8, &toParam );
	saver.Add( 9, &duration );
	saver.Add( 10, &markers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrFlTransaction::operator&( IXmlSaver &saver )
{
	saver.Add( "blending", &blending );
	saver.Add( "kind", &kind );
	saver.Add( "parA", &parA );
	saver.Add( "parB", &parB );
	saver.Add( "fromMin", &fromMin );
	saver.Add( "fromMax", &fromMax );
	saver.Add( "toParam", &toParam );
	saver.Add( "duration", &duration );
	saver.Add( "markers", &markers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnGrFlMultiTransaction::AnGrFlMultiTransaction() :
		probability( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrFlMultiTransaction::operator&( IBinSaver &saver )
{
	saver.Add( 2, &targetNode );
	saver.Add( 3, &probability );
	saver.Add( 4, &parameters );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrFlMultiTransaction::operator&( IXmlSaver &saver )
{
	saver.Add( "targetNode", &targetNode );
	saver.Add( "probability", &probability );
	saver.Add( "parameters", &parameters );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnGrMacronode::AnGrMacronode() :
		nodeType( ANGRNODETYPE_NORMAL )
	, surfSpeedX( 0.0f )
	, surfSpeedY( 0.0f )
	, posX( -1 )
	, posY( -1 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrMacronode::operator&( IBinSaver &saver )
{
	saver.Add( 2, &nodeName );
	saver.Add( 3, &nodeType );
	saver.Add( 4, &nextNode );
	saver.Add( 5, &surfSpeedX );
	saver.Add( 6, &surfSpeedY );
	saver.Add( 7, &sequenceName );
	saver.Add( 8, &startPar );
	saver.Add( 9, &stopPar );
	saver.Add( 10, &speed );
	saver.Add( 11, &simpleTransactions );
	saver.Add( 12, &posX );
	saver.Add( 13, &posY );
	saver.Add( 14, &markers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnGrMacronode::operator&( IXmlSaver &saver )
{
	saver.Add( "nodeName", &nodeName );
	saver.Add( "nodeType", &nodeType );
	saver.Add( "nextNode", &nextNode );
	saver.Add( "surfSpeedX", &surfSpeedX );
	saver.Add( "surfSpeedY", &surfSpeedY );
	saver.Add( "sequenceName", &sequenceName );
	saver.Add( "startPar", &startPar );
	saver.Add( "stopPar", &stopPar );
	saver.Add( "speed", &speed );
	saver.Add( "simpleTransactions", &simpleTransactions );
	saver.Add( "posX", &posX );
	saver.Add( "posY", &posY );
	saver.Add( "markers", &markers );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimKey::AnimKey() :
		time( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimKey::operator&( IBinSaver &saver )
{
	saver.Add( 2, &time );
	saver.Add( 3, &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimKey::operator&( IXmlSaver &saver )
{
	saver.Add( "time", &time );
	saver.Add( "name", &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Animation::Animation()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Animation::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &animkeys );
	saver.Add( 4, &srcFileName );
	saver.Add( 5, &animationFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Animation::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "animkeys", &animkeys );
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "animationFileName", &animationFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FaceFX::FaceFX()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FaceFX::operator&( IBinSaver &saver )
{
	saver.Add( 2, &srcFileName );
	saver.Add( 3, &fxaFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FaceFX::operator&( IXmlSaver &saver )
{
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "fxaFileName", &fxaFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlatSplineControlPointDesc::FlatSplineControlPointDesc() :
		width( 10.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlatSplineControlPointDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &location );
	saver.Add( 3, &width );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlatSplineControlPointDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "location", &location );
	saver.Add( "width", &width );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlatSplineDesc::FlatSplineDesc() :
		HasWidth( false )
	, IsCircle( false )
	, AbsolutePosition( false )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlatSplineDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &points );
	saver.Add( 3, &HasWidth );
	saver.Add( 4, &IsCircle );
	saver.Add( 5, &AbsolutePosition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlatSplineDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "points", &points );
	saver.Add( "HasWidth", &HasWidth );
	saver.Add( "IsCircle", &IsCircle );
	saver.Add( "AbsolutePosition", &AbsolutePosition );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FullScreenFXParams::FullScreenFXParams() :
		ColorCastCoef( 0.0f )
	, SharpPixelSize( 1.0f )
	, SharpCoef( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FullScreenFXParams::operator&( IBinSaver &saver )
{
	saver.Add( 2, &InMin );
	saver.Add( 3, &InMax );
	saver.Add( 4, &OutMin );
	saver.Add( 5, &OutMax );
	saver.Add( 6, &Gamma );
	saver.Add( 7, &Color );
	saver.Add( 8, &ColorCastCoef );
	saver.Add( 9, &SharpPixelSize );
	saver.Add( 10, &SharpCoef );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FullScreenFXParams::operator&( IXmlSaver &saver )
{
	saver.Add( "InMin", &InMin );
	saver.Add( "InMax", &InMax );
	saver.Add( "OutMin", &OutMin );
	saver.Add( "OutMax", &OutMax );
	saver.Add( "Gamma", &Gamma );
	saver.Add( "Color", &Color );
	saver.Add( "ColorCastCoef", &ColorCastCoef );
	saver.Add( "SharpPixelSize", &SharpPixelSize );
	saver.Add( "SharpCoef", &SharpCoef );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SkinPartBase::SkinPartBase()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SkinPartBase::operator&( IBinSaver &saver )
{
	saver.Add( 2, &srcFileName );
	saver.Add( 3, &geometryFileName );
	saver.Add( 4, &skinPartName );
	saver.Add( 5, &materialsReferences );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SkinPartBase::operator&( IXmlSaver &saver )
{
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "geometryFileName", &geometryFileName );
	saver.Add( "skinPartName", &skinPartName );
	saver.Add( "materialsReferences", &materialsReferences );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Spline3DControlPointDesc::Spline3DControlPointDesc() :
		tension( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Spline3DControlPointDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &rotation );
	saver.Add( 3, &position );
	saver.Add( 4, &tension );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Spline3DControlPointDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "rotation", &rotation );
	saver.Add( "position", &position );
	saver.Add( "tension", &tension );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureSize::TextureSize() :
		width( 0 )
	, height( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TextureSize::operator&( IBinSaver &saver )
{
	saver.Add( 2, &width );
	saver.Add( 3, &height );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TextureSize::operator&( IXmlSaver &saver )
{
	saver.Add( "width", &width );
	saver.Add( "height", &height );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TgaTextureName::TgaTextureName()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TgaTextureName::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TgaTextureName::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UVPair::UVPair()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UVPair::operator&( IBinSaver &saver )
{
	saver.Add( 2, &uvTopLeft );
	saver.Add( 3, &uvBottomRight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int UVPair::operator&( IXmlSaver &saver )
{
	saver.Add( "uvTopLeft", &uvTopLeft );
	saver.Add( "uvBottomRight", &uvBottomRight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimGraphCreator::AnimGraphCreator() :
		defaultNode( "idle" )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimGraphCreator::operator&( IBinSaver &saver )
{
	saver.Add( 2, &defaultNode );
	saver.Add( 3, &macroNodes );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AnimGraphCreator::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			AnimGraphCreator* parentPtr = (AnimGraphCreator*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimGraphCreator::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "defaultNode", &defaultNode );
	saver.Add( "macroNodes", &macroNodes );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimGraphCreator::Assign( const AnimGraphCreator& _animGraphCreator )
{
	defaultNode = _animGraphCreator.defaultNode;
	macroNodes = _animGraphCreator.macroNodes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OmniLight::OmniLight() :
		radius( 1.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int OmniLight::operator&( IBinSaver &saver )
{
	saver.Add( 2, &diffuseColor );
	saver.Add( 3, &specularColor );
	saver.Add( 4, &radius );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int OmniLight::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			OmniLight* parentPtr = (OmniLight*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OmniLight::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "diffuseColor", &diffuseColor );
	saver.Add( "specularColor", &specularColor );
	saver.Add( "radius", &radius );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OmniLight::Assign( const OmniLight& _omniLight )
{
	diffuseColor = _omniLight.diffuseColor;
	specularColor = _omniLight.specularColor;
	radius = _omniLight.radius;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PaintPackedMasks::PaintPackedMasks()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PaintPackedMasks::operator&( IBinSaver &saver )
{
	saver.Add( 2, &packedMasks );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PaintPackedMasks::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			PaintPackedMasks* parentPtr = (PaintPackedMasks*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PaintPackedMasks::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "packedMasks", &packedMasks );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PaintPackedMasks::Assign( const PaintPackedMasks& _paintPackedMasks )
{
	packedMasks = _paintPackedMasks.packedMasks;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParticleFX::ParticleFX()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ParticleFX::operator&( IBinSaver &saver )
{
	saver.Add( 2, &srcFileName );
	saver.Add( 3, &fxFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ParticleFX::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			ParticleFX* parentPtr = (ParticleFX*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "fxFileName", &fxFileName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParticleFX::Assign( const ParticleFX& _particleFX )
{
	srcFileName = _particleFX.srcFileName;
	fxFileName = _particleFX.fxFileName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Skeleton::Skeleton()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Skeleton::operator&( IBinSaver &saver )
{
	saver.Add( 2, &srcFileName );
	saver.Add( 3, &skeletonFileName );
	saver.Add( 4, &skins );
	saver.Add( 5, &animations );
	saver.Add( 6, &animGraph );
	saver.Add( 7, &additionalGraph );
	saver.Add( 8, &faceFXAnims );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Skeleton::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Skeleton* parentPtr = (Skeleton*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Skeleton::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "skeletonFileName", &skeletonFileName );
	saver.Add( "skins", &skins );
	saver.Add( "animations", &animations );
	saver.Add( "animGraph", &animGraph );
	saver.Add( "additionalGraph", &additionalGraph );
	saver.Add( "faceFXAnims", &faceFXAnims );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Skeleton::Assign( const Skeleton& _skeleton )
{
	srcFileName = _skeleton.srcFileName;
	skeletonFileName = _skeleton.skeletonFileName;
	skins = _skeleton.skins;
	animations = _skeleton.animations;
	animGraph = _skeleton.animGraph;
	additionalGraph = _skeleton.additionalGraph;
	faceFXAnims = _skeleton.faceFXAnims;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StaticMesh::StaticMesh()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StaticMesh::operator&( IBinSaver &saver )
{
	saver.Add( 2, &srcFileName );
	saver.Add( 3, &geometryFileName );
	saver.Add( 4, &materialsReferences );
	saver.Add( 5, &aabb );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StaticMesh::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			StaticMesh* parentPtr = (StaticMesh*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "geometryFileName", &geometryFileName );
	saver.Add( "materialsReferences", &materialsReferences );
	saver.Add( "aabb", &aabb );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticMesh::Assign( const StaticMesh& _staticMesh )
{
	srcFileName = _staticMesh.srcFileName;
	geometryFileName = _staticMesh.geometryFileName;
	materialsReferences = _staticMesh.materialsReferences;
	aabb.minX = _staticMesh.aabb.minX;
	aabb.maxX = _staticMesh.aabb.maxX;
	aabb.minY = _staticMesh.aabb.minY;
	aabb.maxY = _staticMesh.aabb.maxY;
	aabb.minZ = _staticMesh.aabb.minZ;
	aabb.maxZ = _staticMesh.aabb.maxZ;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Texture::Texture()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Texture::operator&( IBinSaver &saver )
{
	saver.Add( 1, (TextureBase*)this );
	saver.Add( 2, &srcFileName );
	saver.Add( 3, &textureFileName );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Texture::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			Texture* parentPtr = (Texture*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Texture::SerializeSelf( IXmlSaver &saver )
{
	TextureBase::SerializeSelf( saver );
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "textureFileName", &textureFileName );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Texture::Assign( const Texture& _texture )
{
	srcFileName = _texture.srcFileName;
	textureFileName = _texture.textureFileName;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef VISUAL_CUTTED
CObj<Render::Texture> Texture::Load() const
{
	return (Render::Texture *)Render::LoadTexture2D( *this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObj<Render::Texture> Texture::LoadInPool( bool canBeVisualDegrade, void * texturePoolId ) const
{
	return (Render::Texture *)Render::LoadTexture2DIntoPool( *this, canBeVisualDegrade, texturePoolId );
}
#endif // #ifndef VISUAL_CUTTED
}; // namespace NDb
