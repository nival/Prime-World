#pragma once
#include "ImmediateRenderer.h"

namespace Render
{

class VShaderInit : public IntrusivePtrDeleter
{
  const char* name;
public:
  typedef DXVertexShaderRef Type;

  VShaderInit(const char* _name) : name(_name) {}

  void Init(DXVertexShaderRef& _result)
  {
    _result = ImmRenderer::Get()->GetVShader(name);
  }
};

class PShaderInit : public IntrusivePtrDeleter 
{
  const char* name;
public:
  typedef DXPixelShaderRef Type;

  PShaderInit(const char* _name) : name(_name) {}

  void Init(DXPixelShaderRef& _result)
  {
    _result = ImmRenderer::Get()->GetPShader(name);
  }
};

}