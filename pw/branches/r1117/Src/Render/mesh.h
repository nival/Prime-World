#pragma once

#include "submesh.h"

namespace Render
{
	class Mesh
	{
		nstl::vector<SubMesh*> subMeshes;


	public:
		virtual ~Mesh()
		{ 
			for( nstl::vector<SubMesh*>::iterator it = subMeshes.begin(); it != subMeshes.end(); ++it )
				delete *it;
		}

		void LoadFromFile(const nstl::string& file);
		unsigned int GetSubMeshesCount() const { return subMeshes.size(); }
		SubMesh* GetSubMesh(unsigned int i) const { return subMeshes[i]; }

		void AddSubMeshDeprecated( SubMesh* _subMesh )
		{
			subMeshes.push_back(_subMesh);
		}
		

		

	};
}; // namespace Render