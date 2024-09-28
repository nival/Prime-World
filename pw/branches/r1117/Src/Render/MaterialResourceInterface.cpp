// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "../Scripts/TypeWrapper.h"

#include "MaterialResourceInterface.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( GrassMaterial );
REGISTER_DBRESOURCE( VertexDisplacementMaterial );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GrassMaterial::GrassMaterial() :
		ShadowReciverPinValue( SHADOWRECIVERPIN_SHADOWRECIVER )
	, elasticity( 0.75f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GrassMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MaterialType*)this );
	saver.Add( 2, &default_BlendState );
	saver.Add( 3, &default_AlphaState );
	saver.Add( 4, &default_CullingState );
	saver.Add( 5, &FrozenDiffuseMap );
	saver.Add( 6, &NormalDiffuseMap );
	saver.Add( 7, &BurnedDiffuseMap );
	saver.Add( 8, &ShadowReciverPinValue );
	saver.Add( 9, &bladeSize );
	saver.Add( 10, &elasticity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GrassMaterial::operator&( IXmlSaver &saver )
{
	saver.AddTypedSuper( (MaterialType*)this );
	saver.Add( "default_BlendState", &default_BlendState );
	saver.Add( "default_AlphaState", &default_AlphaState );
	saver.Add( "default_CullingState", &default_CullingState );
	saver.Add( "FrozenDiffuseMap", &FrozenDiffuseMap );
	saver.Add( "NormalDiffuseMap", &NormalDiffuseMap );
	saver.Add( "BurnedDiffuseMap", &BurnedDiffuseMap );
	saver.Add( "ShadowReciverPinValue", &ShadowReciverPinValue );
	saver.Add( "bladeSize", &bladeSize );
	saver.Add( "elasticity", &elasticity );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GrassMaterial::GetVariantValue( NScript::VariantValue & value, const char *key ) const
{
	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VertexDisplacementMaterial::VertexDisplacementMaterial() :
		ShadowReciverPinValue( SHADOWRECIVERPIN_SHADOWRECIVER )
	, DiffuseMapPinValue( DIFFUSEMAPPIN_DIFFUSEMAPPRESENT )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VertexDisplacementMaterial::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MaterialType*)this );
	saver.Add( 2, &default_BlendState );
	saver.Add( 3, &default_AlphaState );
	saver.Add( 4, &default_CullingState );
	saver.Add( 5, &ShadowReciverPinValue );
	saver.Add( 6, &DiffuseMapPinValue );
	saver.Add( 7, &diffuseMap );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VertexDisplacementMaterial::operator&( IXmlSaver &saver )
{
	saver.AddTypedSuper( (MaterialType*)this );
	saver.Add( "default_BlendState", &default_BlendState );
	saver.Add( "default_AlphaState", &default_AlphaState );
	saver.Add( "default_CullingState", &default_CullingState );
	saver.Add( "ShadowReciverPinValue", &ShadowReciverPinValue );
	saver.Add( "DiffuseMapPinValue", &DiffuseMapPinValue );
	saver.Add( "diffuseMap", &diffuseMap );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool VertexDisplacementMaterial::GetVariantValue( NScript::VariantValue & value, const char *key ) const
{
	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NDb
