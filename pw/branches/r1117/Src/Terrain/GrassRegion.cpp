#include "stdafx.h"

#include "GrassRegion.h"
#include "../Render/material.h"
#include "../Render/batch.h"
#include "../Render/smartrenderer.h"
#include "../Render/GlobalMasks.h"

namespace
{
	float grassFadeDistance = 10.0f;
	float grassFadeLength = 100.f;

	REGISTER_VAR( "grass_fade_distance", grassFadeDistance, STORAGE_USER );
	REGISTER_VAR( "grass_fade_length", grassFadeLength, STORAGE_USER );
}

namespace Grass
{
	DECLARE_INSTANCE_COUNTER( GrassRegion );

	DXVertexDeclarationRef GrassRegion::VertexStride::GetVertexFormatDeclaration()
	{
		Render::VertexFormatDescriptor descriptor;

		const unsigned int streamId = 0;
		descriptor.AddVertexElement( Render::VertexElementDescriptor( streamId,  0, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_POSITION, 0 ) );
		descriptor.AddVertexElement( Render::VertexElementDescriptor( streamId, 12, Render::VERTEXELEMENTTYPE_FLOAT3, Render::VERETEXELEMENTUSAGE_NORMAL, 0 ) );
		descriptor.AddVertexElement( Render::VertexElementDescriptor( streamId, 24, Render::VERTEXELEMENTTYPE_FLOAT2, Render::VERETEXELEMENTUSAGE_TEXCOORD, 0 ) );
		descriptor.AddVertexElement( Render::VertexElementDescriptor( streamId, 32, Render::VERTEXELEMENTTYPE_FLOAT4, Render::VERETEXELEMENTUSAGE_TEXCOORD, 1 ) );
	
		return Render::SmartRenderer::GetVertexFormatDeclaration( descriptor );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GrassRegion::GrassRegion( DXVertexBufferRef const & _pVB, DXIndexBufferRef const & _pIB, const Render::DipDescriptor& _dipDescriptor,
		Render::BaseMaterial* _pMaterial, const Matrix43& basis )
		: pMaterial( _pMaterial )
		, worldMatrix( basis )
	{
		ChangeGeometry(_pVB, _pIB, _dipDescriptor);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GrassRegion::ChangeGeometry( DXVertexBufferRef const & _pVB, DXIndexBufferRef const & _pIB, const Render::DipDescriptor& _dipDescriptor )
	{
		SetVertexStream(_pVB, VertexStride::GetVertexStreamStride());
		SetIndexBuffer(_pIB);
		GetDipDescriptor() = _dipDescriptor;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GrassRegion::UpdateWorldAABB()
	{
		worldAABB.Transform( worldMatrix, localAABB );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GrassRegion::SetWorldMatrix( const Matrix43 &_worldMatrix )
	{
		worldMatrix = _worldMatrix;
		UpdateWorldAABB();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GrassRegion::Render( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int /*groupFlagsFilter = 0*/ )
	{
		if( !pMaterial )
			return;

		queue.SetCurrentSortingValue( 0.0f );
		queue.Push( NDb::MATERIALPRIORITY_MESHESOPAQUE, this, this, ELEMENT_ID, pMaterial );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GrassRegion::PrepareRendererAfterMaterial( unsigned int ) const
	{
		SHMatrix world;
		Copy( &world, worldMatrix );
		Render::GetRenderer()->SetVertexShaderConstantsMatrix( WORLD, world );

		const CVec4 lodParameters( grassFadeDistance, grassFadeLength, 0.f, 0.f );
		Render::GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST0, lodParameters );
	}
}