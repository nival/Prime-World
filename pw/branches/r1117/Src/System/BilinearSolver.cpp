#include "stdafx.h"
#include "BilinearSolver.h"

float BilinearSolver2D::epsilon = 1.0e-5f;//EPS_VALUE;

void BilinearSolver2D::SetEpsilon(float eps)
{
  epsilon = eps;
}

BilinearSolver2D::BilinearSolver2D(CVec2 const& p0, CVec2 const& p1, CVec2 const& p2, CVec2 const& p3)
  : o(p0)
  , a(p1 - p0)
  , b(p2 - p0)
  , c(p0 + p3 - p1 - p2)
  , ab(Cross(a, b))
  , ac(Cross(a, c))
  , bc(Cross(b, c))
  , formula(-1)
{
  if (fabs2(c) < epsilon)
    formula = 0;
  else if (fabs(ac) < epsilon)
    formula = 1;
  else if (fabs(bc) < epsilon)
    formula = 2;
  else
    formula = 3;

  NI_ASSERT(fabs(bc) >= epsilon || formula != 1, "C must be zero if AC and BC both zero!");
}

BilinearSolver2D::~BilinearSolver2D()
{
}

CVec2 BilinearSolver2D::Solve(CVec2 const& p) const
{
  CVec2 res(0.5f, 0.5f);
  CVec2 d(o - p);
  float ad = Cross(a, d);
  float bd = Cross(b, d);
  float cd = Cross(c, d);
  float det = 0.0f;

  switch (formula)
  {
  case 0:
    res.x = bd / ab;
    res.y = -ad / ab;
    break;

  case 1:
    res.x = bd / (ab - cd);
    res.y = cd / bc;
    break;

  case 2:
    res.x = cd / ac;
    res.y = -ad / (ab + cd);
    break;

  case 3:
    det = (ab + cd) * (ab + cd) + 4.0f * ad * bc;
    if (det >= 0)
    {
      det = sqrtf(det);
      res.x = 0.5f * (cd - ab + det) / ac;
      res.y = 0.5f * (cd + ab - det) / bc;
    }
    else
    {
      NI_ALWAYS_ASSERT("Unsupported case");
    }
    break;

  default:
    NI_ALWAYS_ASSERT("Unsupported case");
  }

  return res;
}

CVec2 BilinearSolver2D::Restore(CVec2 const& k) const
{
  CVec2 p(o);
  p.Displace(a, k.x);
  p.Displace(b, k.y);
  p.Displace(c, k.x * k.y);
  return p;
}

// end of BilinearSolver.cpp
