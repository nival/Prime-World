#include "stdafx.h"
#include "debugmesh.h"

namespace Render
{
	namespace DebugRenderer
	{
		DebugMesh* CreateCustomStaticMesh( const vector<CVec3> points, const vector<unsigned int> indices )
		{
			ASSERT( points.size() && indices.size() && ((indices.size() % 3) == 0) );
			return 0;
		}
	}
}