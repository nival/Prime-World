#pragma once

namespace Render
{
  class ShadowMap
  {
  public:
    ShadowMap(void);
    virtual ~ShadowMap(void);
    virtual bool Init(unsigned int _width, unsigned int _height, float _depthBias, float _biasSlope) = 0;
    virtual void PreRender(void);
    virtual bool PostRender(void);
    virtual bool Apply(const SHMatrix& _viewToLightSpace, CVec4 (&_constants)[4], const Texture2DRef& _depthTex) = 0;
    virtual bool ShowTexture(const CTRect<float> &_rect) const { return false; }
  };

  ShadowMap* CreateShadowMap(NDb::ShadowMode _shadowMode);

};  //namespace Render