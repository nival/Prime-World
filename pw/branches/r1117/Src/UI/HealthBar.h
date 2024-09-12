#pragma once

#include "ImageLabel.h"

namespace UI
{
  class HealthBar : public ImageLabel
  {
    NI_DECLARE_REFCOUNT_CLASS_1(HealthBar, ImageLabel);

    static const Render::Color s_defaultColor;
  public:
    HealthBar();
    virtual ~HealthBar();

    void SetHealthMax(float value);
    void SetHealthValue(float value);
    void SetShieldValue(float value);

    void SetStripes(const float step1 = 0.f, const float step2 = 0.f, const Render::Color& color1 = s_defaultColor, const Render::Color& color2 = s_defaultColor);
    void SetStripes(const NDb::UIHealthStripes& desc, const bool enemy);

    bool CanShowStripes() const { return showStripes; }
    bool CanShowShield() const { return showShield; }
  protected:
    bool SetHealthMaterial( const NDb::BaseUIMaterial* _material );
    bool SetShieldMaterial( const NDb::BaseUIMaterial* _material );

    virtual void OnInit();
    virtual void OnRefresh(float dt);
    virtual void OnMovedSized();
    virtual void OnDataChanged();

    virtual void RenderBetweenBackgroundAndText();
  private:
    void DoUpdate();
    void DoUpdateStripes();
    bool DoCreateStripesTexture(const unsigned width);

    void ApplyStripesVisibility();
    void ApplyStripesColors(const Render::HDRColor& color1, const Render::HDRColor& color2);
    void ApplyStripesConstants(const float start, const float step1, const float step2, const float blendFactor1 = 0.f);

    NDb::UIHealthBarLayout* GetHealthBarLayout()
    {
      return GetLayoutClone<NDb::UIHealthBarLayout>();
    }

    ImageComponent healthSprite;
    ImageComponent shieldSprite;

    float healthMax;
    float healthValue;
    float shieldValue;

    bool needUpdate;
    bool needUpdateStripes;

    bool showShield;
    bool showStripes;

    NDb::UIHealthStripes stripes;
  };
}
