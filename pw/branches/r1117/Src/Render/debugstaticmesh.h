#pragma once

#include "debugmesh.h"

namespace Render
{
	namespace DebugRenderer
	{

		class DebugStaticMesh : public DebugMesh
		{
		
			
		public:

			
			void SetTransform(const Matrix43& worldMatrix ) { }
			void SetRotation(const CQuat& quat ) { }
			void SetPosition(const CVec3& position) { }
			void SetColor( Color color ) { }
			void SetZTest( bool enableZTest ) { }
			void SetHide( bool hide ) { }
			void SetBlendState( bool enableBlending ) { }
			void SetWireframeMode( bool wireframe ) { }
		};


	}
}