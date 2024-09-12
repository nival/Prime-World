#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../Scripts/lua.hpp"
#include "../Render/MaterialSpec.h"
#include "ProgressBar.h"

LUA_ENUM_TRANSFER(NDb::EUIProgressBarType);

namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO(ProgressBar, ImageLabel)
  LUA_METHOD(SetProgressBarType)
  LUA_METHOD(SetProgressMaskGradientItems)
  LUA_METHOD(SetProgressValue)
  LUA_METHOD(SetProgressMinMax)
END_LUA_TYPEINFO(ProgressBar)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProgressBar::OnInit()
{
  ImageLabel::OnInit();

  minValue = 0;
  maxValue = 1;
  currentValue = 0.5f;

  NDb::UIProgressBarLayout *pLayout = GetProgressBarLayout();
  SetProgressMaterial( pLayout->progressMaterial );
  SetEffectMaterial ( pLayout->rotationEffectMaterial );

  needUpdateBar = true;
  Invalidate();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProgressBar::OnRefresh( float deltaTime )
{
  if ( needUpdateBar )
  {
    float progress = ( currentValue - minValue ) / ( maxValue - minValue );

    NI_VERIFY( progress >= 0.0f, "Invalid progress bar value!", progress = 0.0f );
    NI_VERIFY( progress <= 1.0f, "Invalid progress bar value!", progress = 1.0f );
    NI_VERIFY( !_isnan( progress ), "Invalid progress bar value!", progress = 0.0f );

    NDb::UIProgressBarLayout *pLayout = GetProgressBarLayout();
    switch( pLayout->progressBarType )
    {
    case NDb::UIPROGRESSBARTYPE_TEXTUREMASKEDPROGRESS:
      {
        Progress.SetDrawRect( GetWindowRect() );
        Progress.SetCropRect( GetCropRect() );

        Effect.SetDrawRect( GetWindowRect() );
        Effect.SetCropRect( GetCropRect() );

        Progress.SetMaterialCoef3( -Clamp( progress * 256.0f, 0.0f, 256.0f ) / 256.0f );
        Progress.SetMaterialCoef4( ( pLayout->maskGradientItems < 1 ? 1 : pLayout->maskGradientItems ) / 256.0f );

        if( Effect.GetMaterial() )
        {
          CTPoint<int> imsize = Effect.GetMaterial()->imageSize;
          NI_VERIFY(imsize.x > 0, "invalid image sizeX", { imsize.x = (pLayout->rotationEffectPivot.x > 0) ? pLayout->rotationEffectPivot.x*2 : 1; } );
          NI_VERIFY(imsize.y > 0, "invalid image sizeY", { imsize.y = (pLayout->rotationEffectPivot.y > 0) ? pLayout->rotationEffectPivot.y*2 : 1; } );
          Rect wr = GetWindowRect();
          CTPoint<int> pivot;

          if( pLayout->rotationEffectPivot.x == -1 )
            pivot.x = (float)wr.x1 + ((float)wr.x2-wr.x1)/2.0f;
          else
            pivot.x = (float)wr.x1 + ((float)wr.x2-wr.x1) * ((float)pLayout->rotationEffectPivot.x/imsize.x);

          if( pLayout->rotationEffectPivot.y == -1 )
            pivot.y = (float)wr.y1 + ((float)wr.y2-wr.y1)/2.0f;
          else
            pivot.y = (float)wr.y1 + ((float)wr.y2-wr.y1) * ((float)pLayout->rotationEffectPivot.y/imsize.y);

          float sign = (pLayout->effectRotationType == NDb::UIROTATIONTYPE_CW) ? -1.0f : 1.0f;
          Effect.SetExtended( pivot, sign * progress * FP_2PI, 1.0f );
        }

        break;
      }
    case NDb::UIPROGRESSBARTYPE_HORIZONTALSCALINGBAR:
    default:
      {
        Rect rect = GetWindowRect();

        rect.x2 = rect.x1 + (int)( rect.GetSizeX() * progress + 0.5f );
        Progress.SetDrawRect( rect );
        Progress.SetCropRect( GetCropRect() );
        Progress.SetMaterialCoef3( -Clamp( progress * 256.0f, 0.0f, 256.0f ) / 256.0f );
        Progress.SetMaterialCoef4( 1.0f );
        break;
      }
    }

    needUpdateBar = false;
  }

  Progress.SetMaterialOpacity( GetOpacity() );
  Effect.SetMaterialOpacity( GetOpacity() );

  //Progress.Update();

  ImageLabel::OnRefresh( deltaTime );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProgressBar::RenderBetweenBackgroundAndText()
{
  Progress.Render();
  if ( Effect.GetMaterial() && GetProgressBarLayout()->progressBarType == NDb::UIPROGRESSBARTYPE_TEXTUREMASKEDPROGRESS )
    Effect.Render();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProgressBar::SetProgressValue( float value )
{
  NI_VERIFY( !_isnan( value ), "Invalid progress bar value!", value = 0.0f );

  currentValue = value;
  if ( value < minValue )
    currentValue = minValue;
  if ( value > maxValue )
    currentValue = maxValue;
  needUpdateBar = true;
  Invalidate();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProgressBar::SetProgressMinMax( float min, float max )
{
  NI_VERIFY( !_isnan( min ), "Invalid progress bar min value!", min = 0.0f );
  NI_VERIFY( !_isnan( max ), "Invalid progress bar max value!", max = 1.0f );

  if (min < max)
  {
    minValue = min;
    maxValue = max;
  }
  else if (min > max)
  {
    minValue = max;
    maxValue = min;
  }
  else
  {
    minValue = min;
    maxValue = max + 0.000001f;
  }
  SetProgressValue(currentValue);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProgressBar::ShowStripes( bool show, float start, float step1, float step2, const Render::HDRColor &col100, const Render::HDRColor &col1000 )
{
  Render::BaseMaterial* renderMaterial = Progress.GetRenderMaterial().GetRenderMaterial();

  if ( renderMaterial )
  {
    const float blendFactor1 = Clamp((8.f - step1) / 5.f, 0.f, 1.f);

    renderMaterial->SetStripes( show ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE );
    renderMaterial->ModifyStripesConstants( start, step1, step2, blendFactor1 );
    renderMaterial->ModifyStripesColor( col100, col1000 );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ProgressBar::SetEffectMaterial(  const NDb::BaseUIMaterial* _material  )
{
  return Effect.SetImageMaterial( _material, GetContext() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ProgressBar::SetProgressMaterial(  const NDb::BaseUIMaterial* _material  )
{
  return Progress.SetImageMaterial( _material, GetContext() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ProgressBar::SetProgressBarType( NDb::EUIProgressBarType eType )
{
  GetProgressBarLayout()->progressBarType = eType;
  needUpdateBar = true;
  Invalidate();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ProgressBar::SetProgressMaskGradientItems( int items )
{
  GetProgressBarLayout()->maskGradientItems = items;
  needUpdateBar = true;
  Invalidate();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_CONTROLTYPE( NDb::UIProgressBarLayout, ProgressBar );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

NI_DEFINE_REFCOUNT( UI::ProgressBar );
