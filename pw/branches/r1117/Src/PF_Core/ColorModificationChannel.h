#pragma once

#include "../System/Ring.h"

namespace PF_Core
{

enum ColorModificationPriority
{
  CMC_SELECTION, 
  CMC_INVISIBILITY,
  CMC_EFFECT1, 
  CMC_EFFECT2,
  CMC_EFFECT3
};

enum ColorBlendMode
{
  CBM_Normal,       // newColor = current * (1 - opacity) + previous * opacity
  CBM_Multiply,     // newColor = current * previous
  CBM_FullPrevious, // newColor = current * (1 - opacity) + previous
};

class ColorModificationChannel : public CObjectBase
{
	OBJECT_METHODS(0x8D83C3C0, ColorModificationChannel);

public:
  void SetAddColor( Render::HDRColor const& color)
  {
    addColor = color;
    if (pChanged)
      *pChanged = true;
  }

  void SetMulColor( Render::HDRColor const& color)
  {
    mulColor = color;
    if (pChanged)
      *pChanged = true;
  }

  void SetOpacity( float value, bool specialTransparency_ = true )
  {
    opacity = Clamp(value, 0.f, 1.f);
    if (pChanged)
      *pChanged = true;
    specialTransparency = specialTransparency_;
  }

  void SetMixMode( ColorBlendMode mode )
  {
    mixMode = mode;
    if (pChanged)
      *pChanged = true;
  }
 
  Render::HDRColor const&   GetAddColor() const { return addColor; }
  Render::HDRColor const&   GetMulColor() const { return mulColor; }
  float                     GetOpacity()  const { return opacity;  } 
  bool                      IsSpecialTransparency() const { return specialTransparency; }

  ColorModificationPriority GetPriority() const { return priority; }
  ColorBlendMode            GetMixMode()const { return mixMode; }

  NDb::BlendMode GetBlendMode() const 
  { 
    return blendMode;
  }
  void SetBlendMode( NDb::BlendMode mode )
  {
    blendMode = mode;
    isSetBlendMode = true;
  }

  bool IsSetBlendMode()
  {
    return isSetBlendMode;
  }

  void SetFullRecolor( bool _fullRecolor )
  {
    fullRecolor = _fullRecolor;
  }

  bool IsSetFullRecolor()
  {
    return fullRecolor;
  }

  ColorModificationChannel(ColorModificationPriority priority, bool* pChanged ) 
    : priority(priority)
    , pChanged(pChanged)
    , opacity(0.0f)
    , mixMode(CBM_Normal)
    , specialTransparency(false)
    , blendMode(NDb::BLENDMODE_LERPBYALPHA)
    , isSetBlendMode(false)
    , fullRecolor(false)
    {}
	ColorModificationChannel() : pChanged(0) {};
private:
  ColorModificationPriority priority;
  Render::HDRColor          mulColor; 
  Render::HDRColor          addColor; 
  float                     opacity; 
  ColorBlendMode            mixMode;
  NDb::BlendMode            blendMode;
  bool                      isSetBlendMode;
  bool*                     pChanged;
  bool                      specialTransparency;
  bool                      fullRecolor;
};

} // namespace PF_Core