#include "stdafx.h"

#include "SingleFlyText.h"
#include "PFClientBaseUnit.h"

#include "ClientVisibilityHelper.h"

#include "../UI/Resolution.h"
#include "../UI/ImageLabel.h"

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlyText::FlyText( const CVec3 & pos, const NDb::FlyOffText * dbFlyDesc, UI::Window * window )
{
  m_position = pos;
  m_owner    = NULL;
  m_window   = window;

  init( dbFlyDesc );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlyText::FlyText( const NWorld::PFBaseUnit * owner, const NDb::FlyOffText * dbFlyDesc, UI::Window * window )
{
  m_position = VNULL3;
  m_owner    = owner;
  m_window   = window;

  init( dbFlyDesc );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlyText::init(NDb::FlyOffText const *dbFlyDesc)
{
  m_time   = 0.0f;
  m_offset = dbFlyDesc->offset;
  m_lifeTime = dbFlyDesc->lifeTime;

  m_velocity = dbFlyDesc->velocity;
  m_acceleration = dbFlyDesc->acceleration;
  m_startOpacity = dbFlyDesc->startOpacity;
  m_endOpacity   = dbFlyDesc->endOpacity;

  m_align = dbFlyDesc->align;

  if (m_window)
  {
    if (UI::ImageLabel *pImageLabel = dynamic_cast<UI::ImageLabel*>(m_window.Get()))
    {
      pImageLabel->FixWidthToFitCaption( 0, 1 );
      pImageLabel->FixHeightToFitCaption( 0, 1 );
    }

    UI::Rect const &rect = m_window->GetWindowRect();

    if ( m_align == NDb::FLYOFFALIGN_CENTER )
      m_offset.x -= rect.Width() / 2;
    else if ( m_align == NDb::FLYOFFALIGN_RIGHT )
      m_offset.x -= rect.Width();

    m_window->Show(true);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FlyText::IsVisible() const
{
  if (m_time > m_lifeTime)
    return false;

  UI::Rect const &rect  = m_window->GetWindowRect();
  UI::Rect const &prect = m_window->GetParent()->GetWindowRect();

  bool bIsVisible = prect.IsIntersect(rect);

  return bIsVisible;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlyText::Update(float deltaTime, SHMatrix const &proj)
{
  const bool firstUpdate = !(m_time > 0.f);

  m_time += deltaTime;

  CVec2 initPos;

  if (CalculatePosition(firstUpdate, proj, initPos))
    m_pos2d = initPos + m_velocity * m_time + m_acceleration * m_time * m_time * 0.5f;

  const float t = m_time / m_lifeTime;
  const float opacity =  m_startOpacity * (1.0f - t) + t * m_endOpacity;

  m_window->SetOpacity(opacity);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlyText::UpdatePosition()
{
  int x = m_pos2d.x + m_offset.x;
  int y = m_pos2d.y + m_offset.y;

  m_window->SetLocation(x, y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UI::Rect FlyText::GetRect() const
{
  UI::Rect rect = m_window->GetWindowRect();
  rect.bottom += m_offset.y;
  rect.top    += m_offset.y;
  rect.left   += m_offset.x;
  rect.right  += m_offset.x;

  return rect;
}

bool FlyText::CalculatePosition(const bool firstUpdate, const SHMatrix& proj, CVec2& pos)
{
  if (IsValid(m_owner))
  {
    return DoCalculatePosition(firstUpdate, proj, pos);
  }

  return DoCalculateOrphanPosition(proj, pos);
}

bool FlyText::DoCalculatePosition(const bool firstUpdate, const SHMatrix& proj, CVec2& pos)
{
  NI_ASSERT(IsValid(m_owner), "Invalid owner!");

  const bool ownerInvisible = m_owner->CheckFlagType(NDb::UNITFLAGTYPE_INVISIBLE);

  if (ownerInvisible && !firstUpdate)
  {
    if (!NGameX::ClientVisibilityHelper::IsVisibleForPlayer(m_owner))
    {
      pos = m_lastOwnerPos2D;
      return true;
    }
  }

  const NGameX::PFClientBaseUnit* const ownerClientObject = m_owner->ClientObject();

  if (!ownerClientObject)
    return false;

  const NScene::SceneObject* const ownerSceneObject = ownerClientObject->GetSceneObject();

  if (!ownerSceneObject)
    return false;

  CVec3 worldPos = m_position;

  if (ownerSceneObject->GetCollision())
  {
    const Placement& placement = ownerSceneObject->GetPosition();
    const SBound& bounds = ownerSceneObject->GetCollision()->GetBounds();

    worldPos = placement.pos;
    worldPos.z = bounds.s.ptCenter.z;
    worldPos.z += bounds.s.fRadius / sqrtf( 3.0f );
  }
  else
  {
    Render::AABB const &aabb = ownerSceneObject->GetRootComponent()->GetWorldAABB();
    worldPos = aabb.center;
    worldPos.z += aabb.halfSize.z;
  }

  worldPos.z += m_owner->DbUnitDesc()->overtipVerticalOffset;

  UI::Point point;

  UI::GetWindowPlacement(&point, NULL, worldPos, 0, proj);

  pos.x = point.x;
  pos.y = point.y;

  m_lastOwnerPos2D = pos;

  return true;
}

bool FlyText::DoCalculateOrphanPosition(const SHMatrix& proj, CVec2& pos) const
{
  UI::LinearCoord size = 0;
  UI::Point p;

  UI::GetWindowPlacement(&p, &size, m_position, 0, proj);

  pos.x = p.x;
  pos.y = p.y;
  
  return true;
}

} //namespace NGameX
