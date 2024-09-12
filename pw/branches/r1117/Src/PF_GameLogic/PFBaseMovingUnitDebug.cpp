#include "stdafx.h"
#include "PFBaseMovingUnit.h"
#include "PFHero.h"
#include "StaticPathInternal.h"
#include "StandartPath2.h"
#include "TileMap.h"
#include "CollisionResolver.h"
#include "AdventureScreen.h"

//#define DEBUG_COLLISION_PREDICTION

#ifndef _SHIPPING

namespace
{
  static const int g_showSpeedNoDead = 0x00000002;
  static int g_showPaths        = 0;
  static int g_showSpeed        = 0;
  static int g_showSectors      = 0;
#ifdef DEBUG_COLLISION_PREDICTION
  static int g_showPredict      = 0;
#endif // DEBUG_COLLISION_PREDICTION
  static int g_showUnit         = 0;

} // namespace


namespace NWorld
{

#define HEIGHT(v)  heights.GetHeight(v.x, v.y, 1, &v.z, NULL)

///////////////////////////////////////////////////////////////////////////////

void PFBaseMovingUnit::ShowPaths(Render::IDebugRender* pRender) const
{
	const MovingUnit* unit  = &world;
	const NScene::IHeightsController& heights = GetWorld()->GetScene()->GetHeightsController();

	static const Render::Color color1(192, 32, 96);  // static path
	static const Render::Color color2(0, 0, 0);      // spline control points
	static const Render::Color color3(96, 192, 32);  // spline tiles
	static const Render::Color color31(192, 96, 32);  // spline tiles
	static const Render::Color color4(192, 192, 32); // dynamic path
  static const Render::Color color5(192, 0, 192); // spline point

	const CCommonStaticPath* path = unit->pStaticPath;
	if (!path)
		return;

	CVec3 p1, p2;

	if (g_showPaths == 2)	// special case: draw straight line to target
	{
		// colorize faction
		static const Render::Color colors[] =
		{
			Render::Color( 96,  96,  96),
			Render::Color(255,   0,   0),
			Render::Color(  0,   0, 255)
		};
		const Render::Color &color = colors[GetFaction() % ARRAY_SIZE(colors)];
		// get points
		p1 = CVec3(unit->GetCenter(), 0.0f);
		p2 = CVec3(unit->GetCenter(unit->vFarTarget), 0.0f);
		HEIGHT(p1);
		HEIGHT(p2);
    // draw
		pRender->DrawLine3D(p1, p2, color, color, false);
		return;
	}

  int i;
  // display unit's static path
  for (i = 0; i < path->GetLength(); i++)
  {
    p2 = p1;
    p1 = CVec3(unit->pMap->GetPointByTile(path->GetTile(i)), 0);
    HEIGHT(p1);
    if (i == 0)
      continue;
    pRender->DrawLine3D(p1, p2, color1, color1, false);
  }
  if (g_showPaths == 3)
  {
		// display unit's dynamic path
		CStandartPath2* spath = unit->pPath;
		for (i = 0; spath->CanPeek(i); i++)
		{
			p2 = p1;
			p1 = CVec3(spath->PeekPoint(i), 0);
			HEIGHT(p1);
			if (i == 0)
				continue;
			pRender->DrawLine3D(p1, p2, color4, color4, false);
		}
  }
  // display spline control points
  for (i = 0; i < MovingUnit::NUM_SPLINE_POINTS; i++)
  {
		p2 = p1;
    p1 = CVec3(unit->splinePoint[i], 0);
    HEIGHT(p1);
    pRender->DrawPoint3D(p1, 0.25f, color2, false);
  }
  // display spline tiles
  for (i = 0; i < unit->numSplineTiles; i++)
  {
    p1 = CVec3(unit->splineTiles[i], 0);
    HEIGHT(p1);
    pRender->DrawPoint3D(p1, 0.15f, IsValid( unit->pPath ) && unit->pPath->IsFinished() ? color31 : color3, false);
  }

  p1 = CVec3( unit->spline.GetPoint(), 0.0f );
  HEIGHT(p1);
  pRender->DrawPoint3D(p1, 0.25f, color5, false);
}

///////////////////////////////////////////////////////////////////////////////

void PFBaseMovingUnit::ShowSpeed(Render::IDebugRender* pRender) const
{
	const NScene::IHeightsController& heights = GetWorld()->GetScene()->GetHeightsController();

	static const Render::Color colorDead     (255,   0,   0);		// red
	static const Render::Color colorIdle     (  0,   0, 255);		// blue
	static const Render::Color colorMoving   (  0, 255,   0);		// green
	static const Render::Color colorBypassing( 96, 192, 192);		// light-cyan
	static const Render::Color colorBlocked  (128,   0, 255);		// magenta
	static const Render::Color colorCollided (192,  96,  96);		// pink
	static const Render::Color colorNoPath   (255, 128,   0);		// orange
	static const Render::Color colorWaiting  (255, 255,   0);		// yellow
	static const Render::Color colorOther    (  0,   0,   0);		// black

  if (world.moveState == MOVE_STATE_MOUNTED
      || world.moveState == MOVE_STATE_DEAD && g_showSpeed & g_showSpeedNoDead)
    return;

	const Render::Color* color;
	switch (world.moveState)
	{
#define COLOR(Enum, Value)  case Enum: color = &Value; break;
	COLOR(MOVE_STATE_DEAD,      colorDead);
	COLOR(MOVE_STATE_IDLE,      colorIdle);
	COLOR(MOVE_STATE_MOVING,    colorMoving);
	COLOR(MOVE_STATE_NO_PATH,   colorNoPath);
	COLOR(MOVE_STATE_BYPASSING, colorBypassing);
	COLOR(MOVE_STATE_BLOCKED,   colorBlocked);
	COLOR(MOVE_STATE_WAITING,   colorWaiting);
#undef COLOR
	default:
		if (world.IsColliding())
			color = &colorCollided;
		else
			color = &colorOther;
	}

	CVec3 v[4];
	SRect rect = GetWorld()->GetCollisionResolver()->GetSpeedRect(&world);

	v[0].Set(rect.v1); HEIGHT(v[0]);
	v[1].Set(rect.v2); HEIGHT(v[1]);
	v[2].Set(rect.v3); HEIGHT(v[2]);
	v[3].Set(rect.v4); HEIGHT(v[3]);
	// draw rect
	pRender->DrawLine3D(v[0], v[1], *color, *color, false);
	pRender->DrawLine3D(v[1], v[2], *color, *color, false);
	pRender->DrawLine3D(v[2], v[3], *color, *color, false);
	pRender->DrawLine3D(v[3], v[0], *color, *color, false);
}


void PFBaseMovingUnit::ShowSectors(Render::IDebugRender* pRender) const
{
  if (IsDead())
    return;

  const NScene::IHeightsController& heights = GetWorld()->GetScene()->GetHeightsController();

  static const Render::Color color1(  0, 255,   0);  // green
  static const Render::Color color2(255, 255,   0);  // yellow
  static const Render::Color color3(255,   0,   0);  // red

  if (g_showSectors == 2)
  {
    NGameX::AdventureScreen const * adventureScreen = NGameX::AdventureScreen::Instance();
    if (!adventureScreen || this != adventureScreen->GetHero())
      return;
  }
  else if (g_showSectors == 3)
  {
    NGameX::AdventureScreen const * adventureScreen = NGameX::AdventureScreen::Instance();
    if (!adventureScreen || this != adventureScreen->GetCurrentSelectedObject())
      return;
  }

  for (int i = 0, max = GetAttackSectorsCount(); i < max; ++i)
  {
    CPtr<PFBaseMovingUnit> pUnit;
    pUnit.SetPtr(const_cast<PFBaseMovingUnit*>(this));
    CVec3 center;
    center.Set(GetPosition().AsVec2D() + GetAttackSectorOffset(pUnit, i)); HEIGHT(center);

    const Render::Color* color;
    switch (GetAttackSectorOccupies(i))
    {
    case 0:
      color = &color1;
      break;

    case 1:
      color = &color2;
      break;

    default:
      color = &color3;
    }

    pRender->DrawCircle3D(center, 1.0f, 10, *color, false);
  }
}


///////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG_COLLISION_PREDICTION

void PFBaseMovingUnit::ShowPredict(Render::IDebugRender* pRender) const
{
	const NScene::IHeightsController& heights = GetWorld()->GetScene()->GetHeightsController();
	static const Render::Color color(192, 0, 96);

	for (int i = 0; i < predictionPoints.size(); i++)
	{
		CVec3 v(predictionPoints[i], 0.0f);
		HEIGHT(v);
    pRender->DrawPoint3D(v, 0.1f, color, false);
	}
}

#endif // DEBUG_COLLISION_PREDICTION


///////////////////////////////////////////////////////////////////////////////

void PFBaseMovingUnit::ShowUnit(Render::IDebugRender* pRender) const
{
  static const Render::Color color(255,   128,   0);  // Orange
  const NScene::IHeightsController& heights = GetWorld()->GetScene()->GetHeightsController();
  CVec3 center(GetPosition().AsVec2D(), 0.0f);
  HEIGHT(center);
  pRender->DrawCircle3D(center, max(1.0f, GetObjectSize()/2.0f), 10, color, false);
}


class PFBaseMovingUnitDebug : public PFBaseUnitDebug
{
  OBJECT_METHODS(0xB757541, PFBaseMovingUnitDebug);
protected:
  PFBaseMovingUnitDebug() {}
public:
  PFBaseMovingUnitDebug(CPtr<PFBaseUnit> const &pUnit) : PFBaseUnitDebug (pUnit) { }

  virtual bool Process(Render::IDebugRender* pRender)
  {
    if ( PFBaseUnitDebug::Process(pRender) )
      return true;
    CPtr<PFBaseMovingUnit> pUnit = static_cast<PFBaseMovingUnit*>(pOwner.GetPtr());

    if (g_showPaths)
      pUnit->ShowPaths(pRender);
    if (g_showSpeed)
      pUnit->ShowSpeed(pRender);
    if (g_showSectors)
      pUnit->ShowSectors(pRender);
#ifdef DEBUG_COLLISION_PREDICTION
    if (g_showPredict)
      pUnit->ShowPredict(pRender);
#endif // DEBUG_COLLISION_PREDICTION

    if (pUnit->GetObjectId() == g_showUnit)
      pUnit->ShowUnit(pRender);

    return false;
  }
};

CObj<NDebug::DebugObject> PFBaseMovingUnit::CreateDebugObject()
{
  return CObj<NDebug::DebugObject>(new PFBaseMovingUnitDebug(this)) ;
}

REGISTER_DEV_VAR("show_paths",   g_showPaths,   STORAGE_NONE);
REGISTER_DEV_VAR("show_speed",   g_showSpeed,   STORAGE_NONE);
REGISTER_DEV_VAR("show_sectors", g_showSectors, STORAGE_NONE);
#if DEBUG_COLLISION_PREDICTION
REGISTER_DEV_VAR("show_predict", g_showPredict, STORAGE_NONE);
#endif
REGISTER_DEV_VAR("show_unit",    g_showUnit,    STORAGE_NONE);

} // namespace NWorld

#endif // _SHIPPING
