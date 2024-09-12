#include "stdafx.h"
#include "AdventureTooltip.h"
#include <UI/ImageLabel.h>
#include "../ui/Cursor.h"
#include "../ui/Resolution.h"

namespace NGameX
{
//***************************************************************************
// 

class AdventureTooltipManager
{
protected:
  AdventureTooltipManager();
  ~AdventureTooltipManager();
private:
  vector<AdventureTooltip*>::iterator FindTooltip(AdventureTooltip *pTooltip);
  static void Show(AdventureTooltip * pTooltip, bool bShow);
  static void AddTooltip(AdventureTooltip * pTooltip);
  static void RemoveTooltip(AdventureTooltip * pTooltip);
  static bool IsVisible(AdventureTooltip const * pTooltip) { return s_instance && pTooltip == s_instance->m_currentVisible; }
  static void HideCurrentTooltip();

  AdventureTooltip           *m_currentVisible;
  vector <AdventureTooltip*> m_tooltips;

  static AdventureTooltipManager * s_instance;
  static int                       s_counter;

  friend class AdventureTooltip;
};

AdventureTooltipManager * AdventureTooltipManager::s_instance = NULL;
int AdventureTooltipManager::s_counter = 0;

AdventureTooltipManager::AdventureTooltipManager()
{
  NI_ASSERT(NULL == s_instance, "This is singleton!");
  s_counter        = 0;
  m_currentVisible = NULL;
}

AdventureTooltipManager::~AdventureTooltipManager()
{
  s_instance = NULL;
}

void AdventureTooltipManager::AddTooltip(AdventureTooltip * pTooltip)
{
  if (NULL == s_instance)
    s_instance = new AdventureTooltipManager();

  s_instance->m_tooltips.push_back(pTooltip);

  s_counter++;
}

vector<AdventureTooltip*>::iterator AdventureTooltipManager::FindTooltip(AdventureTooltip *pTooltip)
{
  for (vector<AdventureTooltip*>::iterator it = s_instance->m_tooltips.begin(); it < s_instance->m_tooltips.end(); ++it)
  {
    if (*it == pTooltip)
    {
      return it;
    }
  }
  return m_tooltips.end();
}

void AdventureTooltipManager::RemoveTooltip(AdventureTooltip * pTooltip)
{
  if (NULL == s_instance)
    return;
  vector<AdventureTooltip*>::iterator const it = s_instance->FindTooltip(pTooltip);
  if (it != s_instance->m_tooltips.end())
  {
    if (s_instance->m_currentVisible == pTooltip)
    {
      s_instance->m_currentVisible->window->Show(false);
      s_instance->m_currentVisible = NULL;
    }
    s_instance->m_tooltips.erase(it, it + 1);
    s_counter--;
    if (0 == s_counter)
      delete s_instance;
    return;
  }
  NI_ALWAYS_ASSERT("Tooltips should exists");
}

void AdventureTooltipManager::Show(AdventureTooltip * tooltip, bool show)
{
  NI_VERIFY(NULL != tooltip, "Tooltip should exists", return );

  if (NULL == s_instance)
    return;

  if (show)
  {
    if (s_instance->m_currentVisible == tooltip) // This tooltip is already on screen
    {
      return;
    }
    if (s_instance->m_currentVisible != NULL && s_instance->m_currentVisible->window )
    {      
      s_instance->m_currentVisible->window->Show(false);
    }
    s_instance->m_currentVisible = tooltip;
    s_instance->m_currentVisible->window->Show(true);
  }
  else
  {
    if (NULL == s_instance->m_currentVisible)
      return;

    if (s_instance->m_currentVisible != tooltip)
      return;

    if (s_instance->m_currentVisible->window)
      s_instance->m_currentVisible->window->Show(false);
    s_instance->m_currentVisible = NULL;
  }
}

void AdventureTooltipManager::HideCurrentTooltip()
{
  if (NULL == s_instance)
    return;

  if (s_instance->m_currentVisible)
  {
    Show(s_instance->m_currentVisible, false);
  }
}

//***************************************************************************

AdventureTooltip::AdventureTooltip(UI::ImageLabel *pTooltipWindow) :
window(pTooltipWindow),
initialWindowWidth( -1 ),
posX(-1), posY(-1)
{
  AdventureTooltipManager::AddTooltip(this);

  if ( window )
    initialWindowWidth = window->GetSize().x;
}

AdventureTooltip::~AdventureTooltip()
{
  AdventureTooltipManager::RemoveTooltip(this);
}

void AdventureTooltip::Show(bool bShow)
{
  AdventureTooltipManager::Show(this, bShow);
}



void AdventureTooltip::SetText( const wstring & text, float minimalWidthDownScale )
{
  if ( !window )
    return;

  if ( initialWindowWidth < 0 )
    initialWindowWidth = window->GetSize().x;

  window->SetSize( initialWindowWidth, -1, false );
  window->SetCaptionTextW( text );
  window->FixHeightToFitCaption( 0, 2 );

  if ( minimalWidthDownScale >= 0 )
  {
    int minWidth = window->GetSize().x * minimalWidthDownScale;
    window->FixWidthToFitCaption( minWidth, 2 );
  }
}



bool AdventureTooltip::IsVisible() const
{
  return AdventureTooltipManager::IsVisible(this);
}

void AdventureTooltip::SetLocation( int x, int y)
{
	if ( !window )
		return;
	
	if (posX == x && posY == y)
		return;
	
	UI::Point pos;
	GetTooltipPlacement(x, y, pos);

	posX = x;
	posY = y;

	window->SetLocation(pos.x, pos.y);

}

void AdventureTooltip::GetTooltipPlacement( int x, int y, UI::Point & newPos)
{

	CVec2 uiScale( (float)UI::GetUIScreenResolution().x / UI::GetScreenResolution().x, (float)UI::GetUIScreenResolution().y / UI::GetScreenResolution().y );

	UI::Point cursorSize( (int)( NCursor::GetCurrentSize().x * uiScale.x + 0.5f ), (int)( NCursor::GetCurrentSize().y * uiScale.y + 0.5f ) );
	UI::Point cursorHotSpot( (int)( NCursor::GetCurrentHotSpot().x * uiScale.x + 0.5f ), (int)( NCursor::GetCurrentHotSpot().y * uiScale.y + 0.5f ) );

	/*UI::Point cursorSize = NCursor::GetCurrentSize();
	UI::Point cursorHotSpot = NCursor::GetCurrentHotSpot();*/

	UI::Point screenResolution = UI::GetUIScreenResolution();

	int rightOffset = cursorSize.x - cursorHotSpot.x;
	int leftOffset  = cursorHotSpot.x;
	//int downOffset  = cursorSize.y - cursorHotSpot.y;
	int upOffset	= cursorHotSpot.y;

	int width  = window->GetSize().x;
	int height = window->GetSize().y;


	//TODO refactor this

	//try to place right
	if ((x+ rightOffset + width < screenResolution.x) &&  (y + height - upOffset<screenResolution.y))
	{
		newPos.x = x+ rightOffset;
		newPos.y = y - upOffset;
		return;
	}

	//try to place left
	if ((x - leftOffset - width >0) &&  (y + height - upOffset<screenResolution.y))
	{
		newPos.x = x - leftOffset - width;
		newPos.y = y - upOffset;
		return;
	}

	//try to place up right
	if ((x+ rightOffset+ width < screenResolution.x) &&  (y - height - upOffset>0))
	{
		newPos.x = x + rightOffset;
		newPos.y = y - height - upOffset;
		return;
	}

	//try to place up left
	if ((x - leftOffset - width >0 ) &&  (y - height - upOffset>0))
	{
		newPos.x = x - leftOffset - width;
		newPos.y = y - height - upOffset;
		return;
	}
}

void AdventureTooltip::HideCurrentTooltip()
{
  AdventureTooltipManager::HideCurrentTooltip();
}

}

BASIC_REGISTER_CLASS(NGameX::AdventureTooltip)