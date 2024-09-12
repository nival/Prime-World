#pragma once


namespace Render
{
  struct GeometryBuffers
  {
    IDirect3DVertexBuffer9* pVB[2];
    IDirect3DIndexBuffer9*  pIB;
  };

  struct GeometryStatistics
  {
    UINT numTriangles;
    UINT numVertices;

    GeometryStatistics(UINT _numTriangles, UINT _numVertices) : numTriangles(_numTriangles), numVertices(_numVertices) {}
  };

	class IRenderablePrimitive
	{
	public:
		virtual void Bind() const = 0;
    virtual void Draw() const = 0;
    virtual GeometryBuffers  GetBuffers() const = 0;  // return managed buffers reference here (for DXManager)
    virtual GeometryStatistics GetStats() const = 0;

		virtual ~IRenderablePrimitive() {}
	};
};