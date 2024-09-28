#include "StdAfx.h"

#include "AdventureScreen.h"
#include "DieTimer.h"
#include "PFAIWorld.h"

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN(PauseTimer)
  NAMEMAP_VAR_RO(teamName)
NAMEMAP_END

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PauseTimer::PauseTimer(UI::Window *pWindow) :
m_window(pWindow),
m_visible(false)
{
  m_caption = UI::GetChildChecked<UI::ImageLabel>(pWindow, "caption", true);
  m_button  = UI::GetChildChecked<UI::Button>(pWindow, "BTN_remove_pause", true);
  
  maxSeconds = AdventureScreen::Instance()->GetWorld()->GetAIWorld()->GetAIParameters().pauseSeconds + 1.0f;

  currentSeconds = maxSeconds + 1.0f;
  
  if (m_caption)
    m_captionText.Init(this, m_caption->GetCaptionTextW());
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PauseTimer::Show( bool bShow, NWorld::PFBaseHero const *pWho )
{
  m_who = pWho;
  m_window->Show( bShow );
  m_visible = bShow;

  if ( bShow && IsValid( m_who ) )
  {
    currentSeconds = maxSeconds;
    teamName = m_who->GetTeamName();
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PauseTimer::Update( float dT )
{
  if ( !m_visible )
  {
    return;
  }

  bool const bSameFaction = m_who->GetFaction() == AdventureScreen::Instance()->GetHero()->GetFaction();
  m_button->Show( bSameFaction );

  if (m_captionText.HasChanged())
  {
    wstring buffer;
    m_captionText.MakeText(buffer);
    m_caption->SetCaptionTextW(buffer);
  }
}

} //namespace NGameX
