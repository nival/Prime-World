#ifndef SINGLEFLYTEXT_H_INCLUDED
#define SINGLEFLYTEXT_H_INCLUDED

#include "../UI/Window.h"

namespace NWorld
{
  class PFBaseUnit;
}


namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FlyText : public CObjectBase
{
  OBJECT_BASIC_METHODS( FlyText );

  FlyText() {};

public:
  FlyText( const CVec3 & pos, const NDb::FlyOffText * dbFlyDesc, UI::Window * window );
  FlyText( const NWorld::PFBaseUnit * owner, const NDb::FlyOffText * dbFlyDesc, UI::Window * window );

  bool IsVisible() const;

  void Update(float deltaTime, SHMatrix const &proj);
  void UpdatePosition();

  const CVec2 & GetPos2D() const { return m_pos2d; }
  CVec2 & GetOffset() { return m_offset; } //UGLY: returning non-constant ref!!
  UI::Rect GetRect() const;
  const CVec2 & GetVelocity() const { return m_velocity; }
  const NWorld::PFBaseUnit * GetOwner() const { return m_owner; }

  UI::Window *GetWindow() const { return m_window; }
  float GetTime() const { return m_time; }

protected:
  void init( const NDb::FlyOffText * dbFlyDesc );

  float                     m_time;
  CVec2                     m_offset;
  CVec2                     m_pos2d;
  CVec3                     m_position;
  ConstPtr<NWorld::PFBaseUnit>  m_owner;
  Weak<UI::Window>          m_window;

  float                     m_lifeTime;
  float                     m_startOpacity;
  float                     m_endOpacity;
  CVec2                     m_velocity;
  CVec2                     m_acceleration;
  NDb::EFlyOffAlign         m_align;

  CVec2                     m_lastOwnerPos2D;
private:
  bool CalculatePosition(const bool firstUpdate, const SHMatrix& proj, CVec2& pos);
  bool DoCalculatePosition(const bool firstUpdate, const SHMatrix& proj, CVec2& pos);
  bool DoCalculateOrphanPosition(const SHMatrix& proj, CVec2& pos) const;
};


} //namespace NGameX

#endif //SINGLEFLYTEXT_H_INCLUDED
