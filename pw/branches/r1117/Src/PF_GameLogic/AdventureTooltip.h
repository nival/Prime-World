#pragma once

#include "UI/Defines.h"

namespace UI
{
	class ImageLabel;
}

namespace NGameX
{

class AdventureTooltip: public CObjectBase
{
  OBJECT_BASIC_METHODS( AdventureTooltip );

public:
  explicit AdventureTooltip(UI::ImageLabel *pTooltipWindow);

  ~AdventureTooltip();
  bool IsVisible() const;
  void Show(bool bShow);
  void SetText( const wstring & text, float minimalWidthDownScale = -1 );
  void SetLocation(int x, int y);

  UI::ImageLabel * GetWindow() const { return window; }

  static void HideCurrentTooltip();

private:
  Weak<UI::ImageLabel> window;
  int initialWindowWidth;
  int posX;
  int posY;

  AdventureTooltip(){};
  void GetTooltipPlacement(int x, int y, UI::Point & newPos);

  friend class AdventureTooltipManager;
};

}