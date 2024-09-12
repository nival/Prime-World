#include "stdafx.h"

#include "Render/MaterialSpec.h"
#include "HealthBar.h"

NI_DEFINE_REFCOUNT( UI::HealthBar );

#define ROUNDING_DENOMINATOR 100.f
#define ROUND(x) (floor((x) * ROUNDING_DENOMINATOR) / ROUNDING_DENOMINATOR)

namespace
{
  template <typename T>
  struct Threshold;

  template <>
  struct Threshold<float>
  {
    static inline float Get()
    {
      return FLT_EPSILON;
    }
  };

  template <typename T>
  static inline bool IsNear(const T a, const T b, const T threshold = Threshold<T>::Get())
  {
    return !(abs(b - a) > threshold);
  }

  struct TextureLocker
    : Render::LockedRect
    , NonCopyable
  {
    explicit TextureLocker(Render::Texture2DRef _texture)
      : texture(_texture)
    {
      if (!IsValid(texture))
        return;

      Render::LockedRect& r = *this;

      r = texture->LockRect(0, Render::LOCK_DEFAULT);

      NI_VERIFY(!!r.data, "Failed to lock texture!", texture = NULL);
    }

    ~TextureLocker()
    {
      if (!IsValid(texture))
        return;

      texture->UnlockRect(0);
    }
  private:
    Render::Texture2DRef texture;
  };

  inline bool operator==(const Render::HDRColor& lhs, const Render::HDRColor& rhs)
  {
    return
      IsNear(lhs.R, rhs.R) &&
      IsNear(lhs.G, rhs.G) &&
      IsNear(lhs.B, rhs.B) &&
      IsNear(lhs.A, rhs.A);
  }
}

namespace UI
{
  REGISTER_CONTROLTYPE( NDb::UIHealthBarLayout, HealthBar );

  const Render::Color HealthBar::s_defaultColor;

  HealthBar::HealthBar()
    : healthSprite()
    , shieldSprite()
    , healthMax(1.f)
    , healthValue(0.5f)
    , shieldValue(0.25f)
    , needUpdate(false)
    , needUpdateStripes(false)
    , showShield(true)
    , showStripes(true)
  {

  }

  HealthBar::~HealthBar()
  {

  }

  bool HealthBar::SetHealthMaterial(const NDb::BaseUIMaterial* _material)
  {
    return healthSprite.SetImageMaterial(_material, GetContext());
  }

  bool HealthBar::SetShieldMaterial(const NDb::BaseUIMaterial* _material)
  {
    return shieldSprite.SetImageMaterial(_material, GetContext());
  }

  void HealthBar::SetStripes(const NDb::UIHealthStripes& desc, const bool enemy)
  {
    if (!showStripes)
      return;

    const bool changed =
      !IsNear(stripes.stripe1Step, desc.stripe1Step) ||
      !IsNear(stripes.stripe2Step, desc.stripe2Step) ||
      !(stripes.allyColor100 == desc.allyColor100) ||
      !(stripes.allyColor1000 == desc.allyColor1000) ||
      !(stripes.enemyColor100 == desc.enemyColor100) ||
      !(stripes.enemyColor1000 == desc.enemyColor1000);

    if (changed)
    {
      stripes = desc;

      needUpdateStripes = true;
    }

    if (enemy)
      ApplyStripesColors(stripes.enemyColor100, stripes.enemyColor1000);
    else
      ApplyStripesColors(stripes.allyColor100, stripes.allyColor1000);
  }

  void HealthBar::OnInit()
  {
    ImageLabel::OnInit();

    NDb::UIHealthBarLayout* layout = GetHealthBarLayout();

    SetHealthMaterial(layout->healthMaterial);
    SetShieldMaterial(layout->shieldMaterial);

    showShield = layout->showShield;
    showStripes = layout->showStripes;

    ApplyStripesVisibility();

    healthMax = 1.f;
    healthValue = 0.5f;
    shieldValue = showShield ? 0.25f : 0.f;

    needUpdate = true;
    needUpdateStripes = showStripes;

    Invalidate();
  }

  void HealthBar::OnRefresh(float dt)
  {
    if (needUpdateStripes)
    {
      DoUpdateStripes();

      needUpdateStripes = false;
    }

    if (needUpdate)
    {
      DoUpdate();

      needUpdate = false;
    }

    healthSprite.SetMaterialOpacity(GetOpacity());
    shieldSprite.SetMaterialOpacity(GetOpacity());

    ImageLabel::OnRefresh(dt);
  }

  void HealthBar::OnMovedSized()
  {
    needUpdate = true;
    needUpdateStripes = showStripes;

    ImageLabel::OnMovedSized();
  }

  void HealthBar::OnDataChanged()
  {
    ImageLabel::OnDataChanged();

    needUpdate = true;
  }

  void HealthBar::RenderBetweenBackgroundAndText()
  {
    if (showShield && (shieldValue > 0.f))
    {
      shieldSprite.Render();
    }

    {
      healthSprite.Render();
    }
  }

  void HealthBar::DoUpdate()
  {
    const float denominator = 1.f / Max(healthMax, healthValue + shieldValue);

    const float healthRatio = healthValue * denominator;
    const float shieldRatio = shieldValue * denominator;

    UI::Rect rect = GetWindowRect();

    const float x1 = floor(rect.x1);
    const float dx = floor(rect.Width());

    rect.x1 = x1 - 0.5f;
    rect.x2 = x1 + dx * (healthRatio) + 0.5f;

    healthSprite.SetDrawRect(rect);
    healthSprite.SetCropRect(GetCropRect());
    healthSprite.SetMaterialCoef3(-Clamp(healthRatio, 0.f, 1.f));
    healthSprite.SetMaterialCoef4(1.f);

    rect.x1 = x1 + dx * (healthRatio) - 2.f - 0.5f;
    rect.x2 = x1 + dx * (healthRatio + shieldRatio) + 0.5f;

    shieldSprite.SetDrawRect(rect);
    shieldSprite.SetCropRect(GetCropRect());
    shieldSprite.SetMaterialCoef3(-Clamp(shieldRatio, 0.f, 1.f));
    shieldSprite.SetMaterialCoef4(1.f);
  }

  void HealthBar::DoUpdateStripes()
  {
    NI_VERIFY(showStripes, "Check logic", return);

    const float scale = Render::GetUIRenderer()->GetResolutionCoefs().z;

    const UI::Rect& rect = GetWindowRect();

    const float x1 = floor(scale * rect.x1);
    const float dx = floor(scale * rect.Width());

    const float denominator = 1.f / Max(healthMax, healthValue + shieldValue);

    const float step1 = (dx * stripes.stripe1Step * denominator);
    const float step2 = (dx * stripes.stripe2Step * denominator);

    // это раньше было в шейдере
    const float blendFactor1 = Clamp((8.f - step1) / 5.f, 0.f, 1.f);

    ApplyStripesConstants(x1, ROUND(step1), ROUND(step2), blendFactor1);
  }

  void HealthBar::ApplyStripesVisibility()
  {
    {
      Render::BaseMaterial* const material = healthSprite.GetRenderMaterial().GetRenderMaterial();

      if (material)
      {
        material->SetStripes(showStripes ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE);
      }
    }

    if (showShield)
    {
      Render::BaseMaterial* const material = shieldSprite.GetRenderMaterial().GetRenderMaterial();

      if (material)
      {
        material->SetStripes(showStripes ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE);
      }
    }
  }

  void HealthBar::ApplyStripesColors(const Render::HDRColor& color1, const Render::HDRColor& color2)
  {
    NI_VERIFY(showStripes, "Check logic", return);

    {
      Render::BaseMaterial* const material = healthSprite.GetRenderMaterial().GetRenderMaterial();

      if (material)
      {
        material->ModifyStripesColor(color1, color2);
      }
    }

    if (showShield)
    {
      Render::BaseMaterial* const material = shieldSprite.GetRenderMaterial().GetRenderMaterial();

      if (material)
      {
        material->ModifyStripesColor(color1, color2);
      }
    }
  }

  void HealthBar::ApplyStripesConstants(const float start, const float step1, const float step2, const float blendFactor1 /*= 0.f*/)
  {
    NI_VERIFY(showStripes, "Check logic", return);

    {
      Render::BaseMaterial* const material = healthSprite.GetRenderMaterial().GetRenderMaterial();

      if (material)
      {
        material->ModifyStripesConstants(start, step1, step2, blendFactor1);
      }
    }

    if (showShield)
    {
      Render::BaseMaterial* const material = shieldSprite.GetRenderMaterial().GetRenderMaterial();

      if (material)
      {
        material->ModifyStripesConstants(start, step1, step2, blendFactor1);
      }
    }
  }

  void HealthBar::SetHealthMax(float value)
  {
    NI_VERIFY( !_isnan( value ), "Invalid health bar max health value!", value = 1.f );

    value = ceil(Max(1.f, value));

    if (IsNear(value, healthMax))
      return;

    healthMax = value;
    healthValue = Clamp(healthValue, 0.f, healthMax);

    needUpdate = true;
    needUpdateStripes = showStripes;

    Invalidate();
  }

  void HealthBar::SetHealthValue(float value)
  {
    NI_VERIFY( !_isnan( value ), "Invalid health bar health value!", value = 0.f );

    value = ceil(Clamp(value, 0.f, healthMax));

    if (IsNear(value, healthValue))
      return;

    healthValue = value;

    needUpdate = true;
    needUpdateStripes = showStripes;

    Invalidate();
  }

  void HealthBar::SetShieldValue(float value)
  {
    NI_VERIFY( !_isnan( value ), "Invalid health bar shield value!", value = 0.f );

    if (!showShield)
      value = 0.f;
    else
      value = ceil(Max(0.f, value));

    if (IsNear(value, shieldValue))
      return;

    shieldValue = value;

    if (!showShield)
      return;

    needUpdate = true;
    needUpdateStripes = showStripes;

    Invalidate();
  }

}
