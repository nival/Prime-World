#include "stdafx.h"
#include "Color.h"
#include "lerp.h"

namespace 
{
  inline void NormalizeTColor(float& t)
  {
    if( t < 0.0f )
      t += 1.0f;  
    if( 1.0f < t)
      t -= 1.0f;
  }

  inline float CalculateColor(const float p, const float q, const float t)
  {
    if( t < 1.0f / 6.0f)
      return p + ( q - p) * 6 * t;
    if( t < 0.5f )
      return q;
    if( t < 2.0f / 3.0f )
      return p + ( q - p) * 6 * ( 2.0f / 3.0f - t );
    return p;
  }
};


namespace Render
{
  const HDRColor& HDRColor::WHITE()
  {
    static const HDRColor color(1.0f, 1.0f, 1.0f);
    return color;
  }

  const HDRColor& HDRColor::BLACK()
  {
    static const HDRColor color(0.0f, 0.0f, 0.0f);
    return color;
  }

  HDRColor HSL2RGB(const float h, const float s, const float l)
  {
    const float hk = Clamp(h, 0.0f, 360.0f) / 360.0f;

    float tr = hk + 1.0f / 3.0f;
    float tg = hk;
    float tb = hk - 1.0f / 3.0f;

    NormalizeTColor(tr);
    NormalizeTColor(tg);
    NormalizeTColor(tb);

    const float q = (l < 0.5f) ? l * ( 1.0f + s ) : ( l + s - l * s );
    const float p = 2 * l - q;

    return HDRColor( CalculateColor(p, q, tr), CalculateColor(p, q, tg), CalculateColor(p, q, tb) );
  }

  HDRColor HSV2RGB(const float h, const float s, const float v)
  {
    if(EPS_VALUE < s )
    {
      float hValue = h;

      while(hValue < 0.0f)
        hValue += 360.0f;
      while(360.0f < hValue)
        hValue -= 360.0f;   

      hValue /= 60.0;

      const int   i = floor(hValue);
      const float f = hValue - i, p = v * ( 1 - s ),  q = v * ( 1 - s * f ), t = v * ( 1 - s * ( 1 - f ) );
      
      switch( i )
      {
      case 0:
        return HDRColor(v, t, p);
      case 1:
        return HDRColor(q, v, p);
      case 2:
        return HDRColor(p, v, t);
      case 3:
        return HDRColor(p, q, v);
      case 4:
        return HDRColor(t, p, v);
      case 5:
        return HDRColor(v, p, q);
      }
    }
    
    return HDRColor(v, v, v);
  }

  HDRColor Saturate( const HDRColor& _source, float _sat, const CVec4& _fadeColor )
  {
    const float rLum = 0.2225f;
    const float gLum = 0.7169f;
    const float bLum = 0.0606f;

    HDRColor result;

    float grayScale = _source.R * rLum + _source.G * gLum + _source.B * bLum;

    result.R = grayScale * _fadeColor.r;
    result.G = grayScale * _fadeColor.g;
    result.B = grayScale * _fadeColor.b;
    result.A = 1.f;

    return Lerp<HDRColor,float>( result, _source, _sat );
  }
}

