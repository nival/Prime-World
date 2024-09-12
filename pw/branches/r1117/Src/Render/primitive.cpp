#include "stdafx.h"
#include "primitive.h"
#include "DebugLocks.h"

namespace Render
{

bool Primitive::useHiddenIndices = false;

void Primitive::UseHiddenIndices(bool use)
{
  useHiddenIndices = use;
}

bool Primitive::UseHiddenIndices()
{
  return useHiddenIndices;
}

void Primitive::Bind() const
{
  NI_ASSERT( Get(pIndexBuffer), "no indexbuffer" );
  SmartRenderer::BindVertexDeclaration(pVertexFormatDeclaration);
  SmartRenderer::BindIndexBuffer(pIndexBuffer);
  SmartRenderer::BindVertexStream(0, baseVertexStream);
}

void Primitive::Draw() const
{
  NI_ASSERT( Get(baseVertexStream.pVertexBuffer), "no vertexbuffer" );
  NI_ASSERT( Get(pIndexBuffer), "no indexbuffer" );

#ifdef _DEBUG_LOCKS
  uint const lockID = GetLockCall( Get(baseVertexStream.pVertexBuffer) );
  lockID;
#endif // _DEBUG_LOCKS

  if (hasHiddenIndices && UseHiddenIndices())
  {
    NI_ASSERT(dipDescriptor.primitiveType == RENDERPRIMITIVE_TRIANGLELIST, "Unexpected primitive type");
    DipDescriptor dipDescriptorCopy = dipDescriptor;
    dipDescriptorCopy.startIndex += dipDescriptorCopy.primitiveCount * 3;
    SmartRenderer::DrawIndexedPrimitive(dipDescriptorCopy);
  }
  else
    SmartRenderer::DrawIndexedPrimitive(dipDescriptor);
}

GeometryBuffers Primitive::GetBuffers() const
{ 
  GeometryBuffers result = { { Get(baseVertexStream.pVertexBuffer), 0 }, Get(pIndexBuffer) };
  return result; 
}

GeometryStatistics Primitive::GetStats() const
{ 
  return GeometryStatistics(dipDescriptor.primitiveCount, dipDescriptor.numVertices); 
}

} // namespace Render
