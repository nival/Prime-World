#pragma once

#include "../Render/dipdescriptor.h"
#include "../Render/primitive.h"
#include "../Render/RenderComponent.h"
#include "../Render/MaterialSpec.h"
#include "../Scene/RenderableScene.h"

namespace Render
{
	class IVertexFormatDeclaration;
}

namespace Grass
{
	struct GrassRegion
		: public Render::Primitive
		, public Render::RenderComponent
    , public RenderableSceneObj
	{
		REPLACE_DEFAULT_NEW_DELETE( GrassRegion );
	public:

		struct VertexStride
		{
			CVec3 position;
			CVec3 normal;
			CVec2 uv;
			CVec4 params;

			static DXVertexDeclarationRef GetVertexFormatDeclaration();
			static int GetVertexStreamStride() { return sizeof(VertexStride); }
		};

		///< render primitive id
		const static unsigned int ELEMENT_ID = 0;

		Render::AABB                  worldAABB;
		Render::AABB                  localAABB;
		Matrix43                      worldMatrix;
		Render::BaseMaterial* pMaterial;

    // dummy constructor for CObjectBase, should never call this
    GrassRegion() { ASSERT(false); }

		GrassRegion( DXVertexBufferRef const &, DXIndexBufferRef const &, const Render::DipDescriptor&, Render::BaseMaterial*, const Matrix43& );
		
		void ChangeGeometry( DXVertexBufferRef const &, DXIndexBufferRef const &, const Render::DipDescriptor& );

		void UpdateWorldAABB();
		void SetWorldMatrix( const Matrix43 &_worldMatrix );

		virtual const Render::AABB &GetWorldAABB() const { return worldAABB; }

		// From RenderableSceneObj
		void Render( Render::BatchQueue& queue, const Render::SceneConstants& sceneConstants, int groupFlagsFilter = GROUPFLAGS_ALL );

		// From Render::RenderComponent
		virtual void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;
    Render::OcclusionQueries* GetQueries() const { return 0; }

    virtual void DebugDraw( Render::IDebugRender* _debugRenderer ) {}
	};
}