#pragma once

namespace Render
{

class Blur9
{
public :
  Blur9(){}
  Blur9(unsigned texWidth, unsigned texHeight);

  void Init(unsigned texWidth, unsigned texHeight);
  void Apply(Render::Texture2DRef const& pSrc, Render::Texture2DRef const& pDst, char const* pShaderName = 0);

private :
  static const int FILTER_SIDE = 3;
  CVec4 filterKernel[1 + FILTER_SIDE * FILTER_SIDE / 2];
};

} // namespace Render
