#pragma once
#ifndef _BILINEARSOLVER_H_
#define _BILINEARSOLVER_H_

/*
 * Solve equation: bilerp({p0, p1, p2, p3}, {x, y}) == p,
 * i.e. find interpolation coefficients {x, y} in [0, 1] such that
 * p == lerp(lerp(p0, p1, x), lerp(p2, p3, x), y);
 */
class BilinearSolver2D
{
public:
  BilinearSolver2D() {}
  BilinearSolver2D(CVec2 const& p0, CVec2 const& p1, CVec2 const& p2, CVec2 const& p3);
  ~BilinearSolver2D();

  // Set precision
  static void SetEpsilon(float eps);

  // Find interpolation coefficients for given world point
  CVec2 Solve(CVec2 const& p) const;

  // Find world point by given interpolation coefficients
  CVec2 Restore(CVec2 const& k) const;

private:
  CVec2 o, a, b, c;
  float ab;
  float ac;
  float bc;
  int formula;
  static float epsilon;
};

#endif /* _BILINEARSOLVER_H_ */
