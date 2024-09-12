#pragma once

#include "DeviceLost.h"

namespace Render
{

float Lanczos2(float _arg);

class StretcherTwoPass
{
  Render::Texture2DRef pTableTex;
  ScopedArray<CVec4>   pTable;

  bool SetTableTex();

public:
  typedef float (*Func)(float);

  StretcherTwoPass( float (*func)(float) );

  HRESULT Stretch(const Render::Texture2DRef& _src, const CTRect<int> *_srcRect,
                  const Render::Texture2DRef& _dest, const Render::Texture2DRef& _scratch);
};

}; // namespace PF_Render
