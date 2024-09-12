#pragma once



namespace Render
{
	namespace DebugRenderer
	{
		// thread-safe

		class DebugMesh
		{
			DebugMesh(const DebugMesh&);
			DebugMesh& operator=(const DebugMesh&);
		protected:
			DebugMesh();
			virtual ~DebugMesh() {}
		public:
			
			virtual void SetTransform(const Matrix43& worldMatrix ) = 0;
			virtual void SetRotation(const CQuat& quat ) = 0;
			virtual void SetPosition(const CVec3& position) = 0;
			virtual void SetColor( Color color ) = 0;
			virtual void SetZTest( bool enableZTest ) = 0;
			virtual void SetHide( bool hide ) = 0;
			virtual void SetBlendState( bool enableBlending ) = 0;
			virtual void SetWireframeMode( bool wireframe ) = 0;
		};

		DebugMesh* CreateCustomStaticMesh( const vector<CVec3> points, const vector<unsigned int> indices );
	}
}