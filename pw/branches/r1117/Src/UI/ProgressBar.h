#pragma once
#include "ImageLabel.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ProgressBar : public ImageLabel
{
  NI_DECLARE_REFCOUNT_CLASS_1( ProgressBar, ImageLabel );

public:
  ProgressBar() : needUpdateBar( true ), minValue( 0.f ), maxValue( 1.f ), currentValue( 0.5f ) {}

  virtual void OnDataChanged() { ImageLabel::OnDataChanged(); needUpdateBar = true; }
  virtual void OnRefresh( float deltaTime );
  virtual void OnMovedSized() { needUpdateBar = true; ImageLabel::OnMovedSized(); }
  virtual void OnInit();

  bool SetEffectMaterial( const NDb::BaseUIMaterial* _material );
  bool SetProgressMaterial( const NDb::BaseUIMaterial* _material );

  bool SetProgressBarType( NDb::EUIProgressBarType eType );
  bool SetEffectStyle( const char *styleName );
  bool SetProgressMaskGradientItems( int items );

  void SetProgressValue( float value );
  void SetProgressMinMax( float min, float max );

  void ShowStripes( bool show, float start, float step1, float step2, const Render::HDRColor &col100, const Render::HDRColor &col1000 );

  virtual void RenderBetweenBackgroundAndText();

  DECLARE_LUA_TYPEINFO(ProgressBar);

private:
  //@iA@TODO: эти пол€ инициализируютс€ по pProBarLayout->progressStyle и pProBarLayout->rotationEffectStyle
  //Ќа их изменение нужно будет переинициализировать Progress и Effect
  ImageComponent	Progress;
  ImageComponent	Effect;
  bool needUpdateBar;
  float maxValue, minValue, currentValue;

  NDb::UIProgressBarLayout * GetProgressBarLayout() { return GetLayoutClone<NDb::UIProgressBarLayout>(); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
