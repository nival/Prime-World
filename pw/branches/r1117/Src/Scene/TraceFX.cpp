#include "stdafx.h"
#include "TraceFX.h"
#include "../System/Spline.h"
#include "../System/DebugVar.h"
#include "../Render/batch.h"
#include "../Render/renderer.h"
#include "../Render/debugrenderer.h"
#include "../Render/GlobalMasks.h"

#include "../System/InlineProfiler.h"

//#define TRACE_DEBUGVARS_ENABLE

TraceFX::Params const TraceFX::DEFAULT_PARAMS = {
	1.0f,                       // maxLength
  1.0f,                       // maxStepLength
	10.0f, 2.0f,                // speedStart, speedStop
	Render::HDRColor(1.0f, 1.0f, 1.0f, 1.0f), // colorFirst
	Render::HDRColor(1.0f, 1.0f, 1.0f, 1.0f), // colorLast
	0.0f, 0.0f,                 // offsetColor, offsetAlpha
	1.0f,                       // fadeoutSpeed
	0.5f,                       // skewness
};

const CVec3 VINFINITY3 = CVec3(1e10f, 1e10f, 1e10f);

#ifdef TRACE_DEBUGVARS_ENABLE
#define DBGVAR_I(name) NDebug::DebugVar<int> name(#name, "TraceFX")
#define DBGVAR_F(name) NDebug::DebugVar<float> name(#name, "TraceFX")
#define DBGVAR_S(name) NDebug::StringDebugVar name(#name, "TraceFX")
DBGVAR_I(g_state);
DBGVAR_F(g_speed);
DBGVAR_F(g_length);
DBGVAR_F(g_dt);
DBGVAR_S(g_da0);
DBGVAR_S(g_db0);
DBGVAR_S(g_speedTXT);
#endif

namespace
{

static float g_linearParam = 0.05f;

// calculate point lying right in the middle between two straight lines
// (half distance along common perpendicular)
// returns false if lines are parallel
bool GetMiddlePoint(CVec3 const &pointA, CVec3 const &dirA, CVec3 const &pointB, CVec3 const &dirB, CVec3 &p)
{
  float c = dirA.Dot(dirB);
  float d = c * c - 1.f;
  if (fabs(d) < 1e-5f)
    return false;

  float tA = (pointA - pointB).Dot(dirA - c * dirB) / d;
  float tB = (pointB - pointA).Dot(dirB - c * dirA) / d;
  
  p = 0.5f * (pointA + tA * dirA + pointB + tB * dirB);
  return true;
}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TraceFX::TraceFX()
	: params(TraceFX::DEFAULT_PARAMS)
	, enabled(true)
	, state(STATE_OFF)
	, length(0.0f)
	, fadeout(0.0f)
	, worldMatrix(IDENTITY_MATRIX)
	, pGeometry(new TraceFXGeo())
	, pMaterial(NULL)
  , a1(VINFINITY3)
  , a2(VINFINITY3)
  , b1(VINFINITY3)
  , b2(VINFINITY3)
  , da1(VNULL3)
  , db1(VNULL3)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TraceFX::~TraceFX()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFX::SetMaterial(NDb::TraceMaterial const* pDBMaterial)
{
	if (pDBMaterial)
		Reset(pMaterial, static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial(pDBMaterial)));
	else
		Reset(pMaterial, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFX::SetParameters(Params const& newParams)
{
	params = newParams;
	pGeometry->SetOffsets(params.offsetColor, params.offsetAlpha);
	state = STATE_OFF; // abort current effect
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFX::RenderToQueue( Render::BatchQueue &queue )
{
	if (state == STATE_OFF || !pMaterial)
		return;

	queue.Push(NDb::MATERIALPRIORITY_TRANSPARENT, this, Get(pGeometry), 0, Get(pMaterial));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFX::PrepareRendererAfterMaterial( unsigned int elementNumber ) const
{
	Render::Renderer* renderer = Render::GetRenderer();
	
	SHMatrix world;
	Copy( &world, worldMatrix );
	renderer->SetVertexShaderConstantsMatrix( WORLD, world );
	renderer->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST0, pGeometry->GetScaleOffset() * ClampFast(1.0f-fadeout, 0.0f, 1.0f) );
	renderer->SetVertexShaderConstantsColor( VSHADER_LOCALCONST1, params.colorFirst );
	renderer->SetVertexShaderConstantsColor( VSHADER_LOCALCONST2, params.colorLast );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFX::Reinit()
{
  enabled = true;
  state = STATE_OFF;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFX::Enable(bool onoff)
{
	if (onoff == enabled)
		return;

	enabled = onoff;
	if (enabled) // allow trace
	{
		NI_ASSERT(state != STATE_ON, "TraceFX FSM logic failure");
    a2 = a1 = VINFINITY3;
    b2 = b1 = VINFINITY3;
		state = STATE_OFF;
	}
	else // fade out trace
	{
		if (state == STATE_ON) {
			state = STATE_FADEOUT;
			fadeout = 0.0f;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TraceFX::Update(CVec3 const& a0, CVec3 const& b0, float dt)
{
  NI_PROFILE_FUNCTION

  if (dt <= 0.0f)
		return;

	// current distance parameter
  float delta = 0.5f * (fabs(a0 - a1) + fabs(b0 - b1)); // take the average of endpoints
	length += delta;
	float maxLength = min(params.maxLength, length);

  // prevent teleporting problems and artifacts on the first update
  if (delta > params.maxStepLength)
  {
    a2 = a1 = a0;
    b2 = b1 = b0;
    da1 = db1 = VNULL3;
    length = 0.0f;
    delta = 0.0f;
    maxLength = 0.0f;
    pGeometry->Clear();
//    Render::DebugRenderer::DrawPoint3D(a0, 1.0f, Render::Color(0,0,0), false);
  }

//  Render::Color c[] = {Render::Color(0,255,0), Render::Color(255,255,0), Render::Color(255,0,0)};
//  Render::DebugRenderer::DrawLine3D(a0, b0, c[0],c[0], false);
//  Render::DebugRenderer::DrawLine3D(a1, b1, c[1],c[1], false);
//  Render::DebugRenderer::DrawLine3D(a2, b2, c[2],c[2], false);
//  Render::DebugRenderer::DrawPoint3D(a0, 0.25f * state, c[(2+state)%3], false);

	// current velocities
	CVec3 da0 = 0.5f * (3.0f * a0 - 4.0f * a1 + a2);
	CVec3 db0 = 0.5f * (3.0f * b0 - 4.0f * b1 + b2);
	float speed = max(fabs(da0), fabs(db0)) / dt;

	// determine state transitions
	State nextState = state;
	if (state == STATE_ON && speed < params.speedStop)
	{
		nextState = STATE_FADEOUT;
		fadeout = 0.0f;
	}
	else if (state != STATE_ON && speed > params.speedStart && enabled)
	{
		nextState = STATE_ON;
		length = 0.0f;
    fadeout = 0.0f;
		pGeometry->Clear();
	}
	else if (state == STATE_FADEOUT)
	{
		fadeout += params.fadeoutSpeed * dt;
// 		maxLength -= fadeout;
// 		if (maxLength < 0.0f)
		if (fadeout > 1.0f)
		{
			nextState = STATE_OFF;
		}
	}

	// update geometry
  bool replaced = false;
	if (state != STATE_OFF)
	{
    pGeometry->Begin(length, maxLength);
    if (maxLength > 0.0f)
    {
      replaced = UpdateGeometry(a0, b0);
    }
    pGeometry->End();
	}

#ifdef TRACE_DEBUGVARS_ENABLE
	g_state.SetValue((int)state);
	g_speed.SetValue(speed);
	g_length.SetValue(length);
	g_dt.SetValue(dt);
	g_da0.SetValue("{%.2f, %.2f, %.2f}", da0.x, da0.y, da0.z);
	g_db0.SetValue("{%.2f, %.2f, %.2f}", db0.x, db0.y, db0.z);
	float const dbg_xRange = 100.0f;
	int const dbg_fRange = 50;
	int dbg_f = 1 + ClampFast((int)(speed * dbg_fRange / dbg_xRange), 0, dbg_fRange - 1);
	g_speedTXT.SetValue("[%*c%*c", dbg_f, 'X', dbg_fRange - dbg_f + 1, ']');
#endif

	state = nextState;
  if (replaced)
  {
    // move points
    da1 = da1 + 1.5f * (a0 - a1);
    db1 = db1 + 1.5f * (b0 - b1);
    a1 = a0;
    b1 = b0;
  }
  else
  {
    // shift points
    da1 = da0;
    db1 = db0;
    a2 = a1;
    b2 = b1;
    a1 = a0;
    b1 = b0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SlerpVec
{
  CVec3 start;
  CVec3 end;
  float startLen;
  float endLen;
  CQuat fullRot;

public:
  SlerpVec(CVec3 const &start, CVec3 const &end) : start(start), end(end)
  {
    startLen = fabs(start);
    endLen = fabs(end);
    fullRot = ShortestArc(start, end);
  }

  CVec3 Get(float t)
  {
    CQuat curRot;
    curRot.Slerp(t, QNULL, fullRot);

    CVec3 cur;
    curRot.Rotate(&cur, start);

    float len = fabs(cur);
    if (len < 1e-5f)
      return cur;

    float targetLen = (1-t) * startLen + t * endLen;
    return cur * (targetLen / len);
  }
};

bool TraceFX::UpdateGeometry(CVec3 const& a0, CVec3 const& b0)
{
  NI_PROFILE_FUNCTION

  bool replaced = false;
  float skew = params.maxLength * params.skewness;
  float delta = 0.5f * (fabs(a0 - a1) + fabs(b0 - b1)); // take the average of endpoints
  float minDelta = 0.95f * params.maxLength / TraceFXGeo::MAX_SEGMENTS;
  float maxDelta = 1.25f * params.maxLength / TraceFXGeo::MAX_SEGMENTS;
  int n = max(1, int(delta / maxDelta));

  float delta2 = 0.5f * (fabs(a0 - a2) + fabs(b0 - b2));
  if (delta < minDelta && delta2 < maxDelta)
  {
    replaced = pGeometry->ReplaceLast(a0, length - skew, b0, length);
  }
  else if (n == 1)
  {
    pGeometry->Append(a0, length - skew, b0, length);
  }
  else
  {
/*
    // Hermite interpolation
    {
      CTHermiteSegment<CVec3> a(a1, da1, a0, da0);
      CTHermiteSegment<CVec3> b(b1, db1, b0, db0);
      for (int i = 1; i <= n; ++i)
      {
        float t = float(i) / float(n);
        float x = length - (1.0f - t) * delta;
        pGeometry->Append(a.Get(t), x - skew, b.Get(t), x);
      }
    }
*/
    CVec3 dir1(b1 - a1), dir0(b0 - a0), c;
    if ( Normalize(&dir0) &&
         Normalize(&dir1) &&
         GetMiddlePoint(a1, dir1, a0, dir0, c) &&
         fabs( 1.0f - dir1.Dot( dir0 ) ) > g_linearParam
         )
    {
      // slerp
      SlerpVec sva(a1-c, a0-c);
      SlerpVec svb(b1-c, b0-c);

      for (int i = 1; i <= n; ++i)
      {
        float t = float(i) / float(n);
        float x = length - (1.0f - t) * delta;
        pGeometry->Append(c + sva.Get(t), x - skew, c + svb.Get(t), x);
      }
    }
    else
    {
      // parallel lines or other bad case -- fallback to lerp
      for (int i = 1; i <= n; ++i)
      {
        float t = float(i) / float(n);
        float x = length - (1.0f - t) * delta;
        pGeometry->Append((1-t) * a1 + t * a0, x - skew, (1-t) * b1 + t * b0, x);
      }
    }
  }

  return replaced;
}

REGISTER_DEV_VAR( "trailLinearParam", g_linearParam, STORAGE_NONE );

// end of TraceFX.cpp
