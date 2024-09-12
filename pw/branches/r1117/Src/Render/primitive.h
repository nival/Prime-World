#pragma once

#include "dipdescriptor.h"
#include "smartrenderer.h"

#include "renderer.h"
#include "renderableprimitive.h"
#include "../System/fixedvector.h"

namespace Render
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Primitive : public IRenderablePrimitive
{
	DipDescriptor          dipDescriptor;
	DXVertexDeclarationRef pVertexFormatDeclaration;
	VertexStream           baseVertexStream;
	DXIndexBufferRef       pIndexBuffer;
  bool                   hasHiddenIndices;
  static bool            useHiddenIndices;
public:
  Primitive() : hasHiddenIndices(false) {}
	~Primitive()  {}

	const DXIndexBufferRef & GetIndexBuffer() const { return pIndexBuffer; }
	void SetIndexBuffer( DXIndexBufferRef pIB ) { pIndexBuffer = pIB; }

	void SetVertexStream( DXVertexBufferRef pVB, unsigned int stride, unsigned int offset = 0) 
	{
		baseVertexStream.Set(pVB, stride, offset); 
	}
	const DXVertexBufferRef & GetVertexBuffer() const { return baseVertexStream.pVertexBuffer; }

	DXVertexDeclarationRef GetVertexDeclaration() { return pVertexFormatDeclaration; }
  void SetVertexDeclaration( DXVertexDeclarationRef pVFD ) { pVertexFormatDeclaration = pVFD; }

	const DipDescriptor& GetDipDescriptor() const { return dipDescriptor; }
	DipDescriptor& GetDipDescriptor() { return dipDescriptor; }

  unsigned int GetVBStride() const { return baseVertexStream.stride; }

  void HasHiddenIndices(bool has) { hasHiddenIndices = has; }
  bool HasHiddenIndices() const { return hasHiddenIndices; }
  static void UseHiddenIndices(bool use);
  static bool UseHiddenIndices();

	virtual void Bind() const;
  virtual void Draw() const;
  virtual GeometryBuffers GetBuffers() const;
  virtual GeometryStatistics GetStats() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PrimitiveWithAddonStream : public Render::Primitive
{
	Render::VertexStream addonVertexStream;

public:
	void SetAdditionalVertexStream( DXVertexBufferRef pVB, unsigned int stride, unsigned int offset = 0) 
	{
		addonVertexStream.Set(pVB, stride, offset); 
	}

	const DXVertexBufferRef & GetAdditionalVertexBuffer() const { return addonVertexStream.pVertexBuffer; }

	virtual void Bind() const
	{
		Render::Primitive::Bind();
		Render::SmartRenderer::BindVertexStream(1, addonVertexStream);
	}

  virtual GeometryBuffers GetBuffers() const
  { 
    GeometryBuffers result = Render::Primitive::GetBuffers();
    result.pVB[1] = Get(addonVertexStream.pVertexBuffer);
    return result; 
  }
};

}