#pragma once

#include "../UI/ScreenLogicBase.h"
#include "../UI/Window.h"
#include "../UI/ImageLabel.h"
#include "../UI/Button.h"

#include "../System/NameMap.h"

#include "PFHero.h"
#include "PrecompiledTooltips.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NGameX
{

class AdventureScreenBase;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PauseTimer : public NNameMap::Map
{
  NAMEMAP_DECLARE;
public:
  explicit PauseTimer( UI::Window * pWindow );

  void Update(float dT);
  void Show( bool bShow, const NWorld::PFBaseHero * pWho );
private:
  Weak<UI::Window>      m_window;
  Weak<UI::Button>      m_button;
  Weak<UI::ImageLabel>  m_caption;
  ConstPtr<NWorld::PFBaseHero> m_who;
  
  PrecompiledTooltip m_captionText;

  bool m_visible;

  wstring teamName;
  
  float maxSeconds;
  float currentSeconds;
};

} //namespace NGameX
