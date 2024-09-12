#pragma once

#include "../Render/FullscreenFX.h"

namespace PF_Render
{

  class PostFXFader 
  {
  public:
    PostFXFader();
    ~PostFXFader();

    void FadeTo( int brightness, float time );
    void Tick( float deltaTime );
    bool IsActive() const { return curVal >= 255; }
  private:

    Render::FullScreenFX::Params cur;
    float curVal;
    float step;
    int endVal;
    float timeLeft;

    void SetValue( float value );
  };
}