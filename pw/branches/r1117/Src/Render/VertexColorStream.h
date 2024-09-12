#pragma once

namespace Render
{

struct MeshGeometry;
class  BaseMaterial;

class MeshVertexColors
{
public:
	unsigned numColors;
	DXVertexBufferRef pVB1;
  DXVertexBufferRef pVB2;

	MeshVertexColors() : numColors(0) {}

	void InitializeBuffer(const MeshGeometry &mesh, bool fake);
	void Bind(int primIndex);
};

}
