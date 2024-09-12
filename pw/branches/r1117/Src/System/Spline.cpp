#include "stdafx.h"

#include "Spline.h"

namespace
{

const int MAXDEPTH = 64; // Maximum depth for recursion
const float EPSILON = pow(2.f, -MAXDEPTH-1);  // Flatness control value
const int DEGREE = 3;    // Cubic Bezier curve
const int W_DEGREE = 5;  // Degree of eqn to find roots of

const float cubicZ[3][4] = {  
  /* Precomputed "z" for cubics   */
  {1.0f, 0.6f, 0.3f, 0.1f},
  {0.4f, 0.6f, 0.6f, 0.4f},
  {0.1f, 0.3f, 0.6f, 1.0f},
};


/***
*  ConvertToBezierForm :
*      Given a point and a Bezier curve, generate a 5th-degree
*      Bezier-format equation whose solution finds the point on the
*      curve nearest the user-defined point.
*/
void convertToBezierForm(CVec2 const *v, CVec2 const &pa, CVec2 *out)
{

  CVec2 c[DEGREE+1];   // v(i) - pa
  CVec2 d[DEGREE];     // v(i+1) - v(i)
  float cdTable[3][4]; // Dot product of c, d
  int i;

  // Determine the c's -- these are vectors created by subtracting
  // point pa from each of the control points
  for (i = 0; i <= DEGREE; i++)
  {
    c[i] = v[i] - pa;
  }

  // Determine the d's -- these are vectors created by subtracting
  // each control point from the next
  const float s = 3.f;
  for (i = 0; i <= DEGREE - 1; i++)
  {       
    d[i] = s * (v[i+1] - v[i]);
  }

  // Create the c,d table -- this is a table of dot products of the
  // c's and d's
  for (int row = 0; row <= DEGREE - 1; row++) {
    for (int column = 0; column <= DEGREE; column++) {
      cdTable[row][column] = d[row].Dot(c[column]);
    }
  }

  // Now, apply the z's to the dot products, on the skew diagonal
  // Also, set up the x-values, making these "points"
  for (i = 0; i <= W_DEGREE; i++)
  {
    out[i] = CVec2((float)(i) / W_DEGREE, 0.0);
  }

  const int n = DEGREE;
  const int m = DEGREE-1;
  for (int k = 0; k <= n + m; k++)
  {
    int lb = max(0, k - m);
    int ub = min(k, n);
    for (i = lb; i <= ub; i++)
    {
      int j = k - i;
      out[i+j] = CVec2(out[i+j].x, out[i+j].y + cdTable[j][i] * cubicZ[j][i]);
    }
  }
}

/***
* CrossingCount :
*  Count the number of times a Bezier control polygon 
*  crosses the 0-axis. This number is >= the number of roots.
*
*/
int crossingCount(CVec2 *v, int degree)
{
  int nCrossings = 0;
  int sign = v[0].y < 0.f ? -1 : 1;
  int oldSign = sign;
  for (int i = 1; i <= degree; i++)
  {
    sign = v[i].y < 0.f ? -1 : 1;
    if (sign != oldSign) nCrossings++;
    oldSign = sign;
  }
  return nCrossings;
}

/*
*  ControlPolygonFlatEnough :
*  Check if the control polygon of a Bezier curve is flat enough
*  for recursive subdivision to bottom out.
*
*/
bool controlPolygonFlatEnough(CVec2 const *v, int degree, float epsilon)
{
  // Find the  perpendicular distance
  // from each interior control point to
  // line connecting v[0] and v[degree]

  // Derive the implicit equation for line connecting first
  // and last control points
  float a = v[0].y - v[degree].y;
  float b = v[degree].x - v[0].x;
  float c = v[0].x * v[degree].y - v[degree].x * v[0].y;

  float abSquared = (a * a) + (b * b);
  float distance[W_DEGREE+1]; // Distances from pts to line

  int i;
  for (i = 1; i < degree; i++)
  {
    // Compute distance from each of the points to that line
    distance[i] = a * v[i].x + b * v[i].y + c;
    if (distance[i] > 0.f) {
      distance[i] = (distance[i] * distance[i]) / abSquared;
    }
    if (distance[i] < 0.f) {
      distance[i] = -((distance[i] * distance[i]) / abSquared);
    }
  }


  // Find the largest distance
  float maxDistanceAbove = 0.0;
  float maxDistanceBelow = 0.0;
  for (i = 1; i < degree; i++) {
    if (distance[i] < 0.f) {
      maxDistanceBelow = min(maxDistanceBelow, distance[i]);
    }
    if (distance[i] > 0.f) {
      maxDistanceAbove = max(maxDistanceAbove, distance[i]);
    }
  }

  // Implicit equation for zero line
  float a1 = 0.f;
  float b1 = 1.f;
  float c1 = 0.f;

  // Implicit equation for "above" line
  float a2 = a;
  float b2 = b;
  float c2 = c + maxDistanceAbove;

  float det = a1 * b2 - a2 * b1;
  float dInv = 1.f / det;

  float intercept1 = (b1 * c2 - b2 * c1) * dInv;

  //  Implicit equation for "below" line
  a2 = a;
  b2 = b;
  c2 = c + maxDistanceBelow;

  det = a1 * b2 - a2 * b1;
  dInv = 1.0 / det;

  float intercept2 = (b1 * c2 - b2 * c1) * dInv;

  // Compute intercepts of bounding box
  float leftIntercept = min(intercept1, intercept2);
  float rightIntercept = max(intercept1, intercept2);

  float error = 0.5f * (rightIntercept-leftIntercept);    

  return error < epsilon;
}

/*
*  ComputeXIntercept :
*  Compute intersection of chord from first control point to last
*      with 0-axis.
* 
*/
float computeXIntercept(CVec2 *v, int degree)
{
  float XNM = v[degree].x - v[0].x;
  float YNM = v[degree].y - v[0].y;
  float XMK = v[0].x;
  float YMK = v[0].y;

  float detInv = - 1.f / YNM;

  return (XNM*YMK - YNM*XMK) * detInv;
}

CVec2 bezier(CVec2 *c, int degree, float t, CVec2 *left, CVec2 *right)
{
  // FIXME WIRED-252, move outside the method and make static
  CVec2 p[W_DEGREE+1][W_DEGREE+1];

  /* Copy control points  */
  for (int j=0; j <= degree; j++)
  {
    p[0][j] = c[j];
  }

  /* Triangle computation */
  for (int i = 1; i <= degree; i++)
  {
    for (int j = 0 ; j <= degree - i; j++)
    {
      p[i][j] = (1.0 - t) * p[i-1][j] + t * p[i-1][j+1];
    }
  }

  if (left)
  {
    for (int j = 0; j <= degree; j++)
    {
      left[j]  = p[j][0];
    }
  }

  if (right)
  {
    for (int j = 0; j <= degree; j++)
    {
      right[j] = p[degree-j][j];
    }
  }

  return p[degree][0];
}

/***
*  FindRoots :
*  Given a 5th-degree equation in Bernstein-Bezier form, find
*  all of the roots in the interval [0, 1].  Return the number
*  of roots found.
*/
int findRoots(CVec2 *w, int degree, float *t, int depth)
{
  int cc = crossingCount(w, degree);

  if (cc == 0)
    return 0; // No solutions here

  if (cc == 1)
  {
    // Unique solution
    // Stop recursion when the tree is deep enough
    // if deep enough, return 1 solution at midpoint
    if (depth >= MAXDEPTH)
    {
      t[0] = (w[0].x + w[W_DEGREE].x) / 2.f;
      return 1;
    }
    if (controlPolygonFlatEnough(w, degree, EPSILON))
    {
      t[0] = computeXIntercept(w, degree);
      return 1;
    }
  }

  // Otherwise, solve recursively after
  // subdividing control polygon
  CVec2 left[W_DEGREE+1];    // New left and right
  CVec2 right[W_DEGREE+1];   // control polygons
  float leftT[W_DEGREE+1];   // Solutions from kids
  float rightT[W_DEGREE+1];

  bezier(w, degree, 0.5, left, right);
  int leftCount  = findRoots(left,  degree, leftT, depth+1);
  int rightCount = findRoots(right, degree, rightT, depth+1);

  // Gather solutions together
  int i;
  for (i = 0; i < leftCount; i++)
  {
    t[i] = leftT[i];
  }
  for (i = 0; i < rightCount; i++) {
    t[i+leftCount] = rightT[i];
  }

  // Send back total number of solutions
  return leftCount + rightCount;
}

}


/***
* Calculates the nearest point on a spline.
*
* Calculations for the Bezier parts come from:
* "Solving the Nearest Point-on-Curve Problem" and "A Bezier Curve-Based Root-Finder"
* by Philip J. Schneider from "Graphics Gems", Academic Press, 1990.
*/ 
float CAnalyticBSpline2::GetClosestPoint(const CVec2 &vPoint)
{
  float tCandidate[W_DEGREE];     // Possible roots
  
  // calculate bezier curve control points from B-spline control points
  CVec2 bscp[] = {GetCtrlPoint(1), GetCtrlPoint(2)};
  CVec2 v[] = {
    Get(0.f),
    0.66666f * bscp[0] + 0.33333f * bscp[1],
    0.33333f * bscp[0] + 0.66666f * bscp[1],
    Get(1.f)
  };

  // Convert problem to 5th-degree Bezier form
  CVec2 w[W_DEGREE+1]; // Ctl pts of 5th-degree curve
  convertToBezierForm(v, vPoint, w);

  // Find all possible roots of 5th-degree equation
  int nSolutions = findRoots(w, W_DEGREE, tCandidate, 0);

  // Compare distances of P5 to all candidates, and to t=0, and t=1
  // Check distance to beginning of curve, where t = 0
  float minDistance = fabs2(vPoint - Get(0.f));
  float t = 0.f;

  // Find distances for candidate points
  for (int i = 0; i < nSolutions; i++)
  {
    CVec2 p = bezier(v, DEGREE, tCandidate[i], NULL, NULL);
    float distance = fabs2(vPoint - p);
    if (distance < minDistance)
    {
      minDistance = distance;
      t = tCandidate[i];
    }
  }

  // Finally, look at distance to end point, where t = 1.0
  float distance = fabs2(vPoint - Get(1.f));
  if (distance < minDistance)
  {
    minDistance = distance;
    t = 1.f;
  }

  return t;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CCompositeBSpline specialization
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
bool IsBezierPolygonFlat<CVec2>(CVec2 const &p0, CVec2 const &p1, CVec2 const &p2, CVec2 const &p3, float epsilon)
{
  CVec2 p[] = {p0, p1, p2, p3};
  return controlPolygonFlatEnough(p, DEGREE, epsilon);
}

template<>
float CCompositeBSpline<CVec2>::GetSegmentClosestPoint(int index, CVec2 const &p)
{
  NI_ASSERT(0 <= index && index < controlPoints.size() - 3, "Index out of bounds");
  CAnalyticBSpline2 segment(controlPoints[index], controlPoints[index+1], controlPoints[index+2], controlPoints[index+3]);
  return segment.GetClosestPoint(p);
}

template<>
CVec2 CCompositeBSpline<CVec2>::Get(float t)
{
  NI_ASSERT(0.f <= t && t <= (float)(controlPoints.size()-3), "Parameter out of bounds");
  int s;
  float offs;
  SegmentAndOffset(t, s, offs);
  CAnalyticBSpline2 segment(controlPoints[s], controlPoints[s+1], controlPoints[s+2], controlPoints[s+3]);
  return segment.Get(offs);
}

template<>
CVec2 CCompositeBSpline<CVec2>::GetDiff1(float t)
{
  NI_ASSERT(0.f <= t && t <= (float)(controlPoints.size()-3), "Parameter out of bounds");
  int s;
  float offs;
  SegmentAndOffset(t, s, offs);
  CAnalyticBSpline2 segment(controlPoints[s], controlPoints[s+1], controlPoints[s+2], controlPoints[s+3]);
  return segment.GetDiff1(offs);
}

/*
template<>
void CCompositeBSpline<CVec2>::PrecomputeSegment(int index)
{
  CAnalyticBSpline2 segment(controlPoints[index], controlPoints[index+1], controlPoints[index+2], controlPoints[index+3]);

  Segment &s = segments[index];
  int numSteps = 100;
  s.quants.resize(numSteps);

  CVec2 start = segment.Get(0.f);
  CVec2 end;
  float length = 0.f;
  for (int j = 0; j < numSteps; ++j)
  {
    end = segment.Get((float)j / numSteps);
    s.quants[j].length = fabs(end - start);
    length += s.quants[j].length;
    s.quants[j].integralLength = length;
    start = end;
  }
}
*/

template<>
CVec2 CCompositeBSplineWidth<CVec2>::GetSection(float at, CVec2 &p0, CVec2 &p1)
{
  CVec2 p = Get(at);
  CVec2 tan = GetDiff1(at);
  CVec2 n(-tan.y, tan.x);
  Normalize(&n);
  
  float w = /*0.5f **/ GetWidth(at);
  p0 = p + w * n;
  p1 = p - w * n;

  return p;
}

void CubicSpline::Build( const nstl::vector<CVec2>& points )
{
  nodesCount = points.size();
 
  // Инициализация массива сплайнов
  splines = nstl::vector<SplineTuple>( nodesCount );
  for ( int i = 0; i < nodesCount; i++ )
  {
    splines[i].x  = points[i].x;
    splines[i].a0 = points[i].y;
  }
  splines[0].a2 = splines[nodesCount - 1].a2 = 0.0f;
 
  // Решение СЛАУ относительно коэффициентов сплайнов c[i] методом прогонки для трехдиагональных матриц
  // Вычисление прогоночных коэффициентов - прямой ход метода прогонки
  nstl::vector<float> alpha( nodesCount - 1 );
  nstl::vector<float> beta ( nodesCount - 1 );

  alpha[0] = beta[0] = 0.0f;

  for ( int i = 1; i < nodesCount - 1; i++ )
  {
    float x1 = points[i].x - points[i-1].x;
    float x2 = points[i+1].x - points[i].x;
    float y1 = points[i].y - points[i-1].y;
    float y2 = points[i+1].y - points[i].y;

    float A = x1;
    float C = 2.0f * ( x1 + x2 );
    float B = x2;
    float F = 6.0f * ( y2/x2 - y1/x1 );

    float z = ( A * alpha[i-1] + C );

    alpha[i] = -B / z;
    beta[i]  = ( F - A*beta[i-1] ) / z;
  }

  // Нахождение решения - обратный ход метода прогонки
  for ( int i = nodesCount - 2; i > 0; i-- )
  {
    splines[i].a2 = alpha[i] * splines[i+1].a2 + beta[i];
  }

  // Освобождение памяти, занимаемой прогоночными коэффициентами
  alpha.clear();
  beta.clear();

  // По известным коэффициентам c[i] находим значения b[i] и d[i]
  for ( int i = nodesCount - 1; i > 0; i-- )
  {
    float x1 = points[i].x - points[i-1].x;
    float y1 = points[i].y - points[i-1].y;
    splines[i].a3 = ( splines[i].a2 - splines[i-1].a2 ) / x1;
    splines[i].a1 = x1 * ( 2.0f * splines[i].a2 + splines[i-1].a2 ) / 6.0f + y1 / x1;
  }
}
 
float CubicSpline::Get( float x ) const
{
  NI_VERIFY( splines.size() > 0, "Spline wasn't build!", return 0.0f );

  nstl::vector<SplineTuple>::const_iterator s = splines.begin();

  if ( x <= splines[0].x ) // Если x меньше точки сетки x[0] - пользуемся первым эл-том массива
  {
    x = splines[0].x;
    s = splines.begin();
  }
  else if ( x >= splines[nodesCount - 1].x ) // Если x больше точки сетки x[n - 1] - пользуемся последним эл-том массива
  {
    x = splines[nodesCount - 1].x;
    s = splines.end() - 1;
  }
  else // Иначе x лежит между граничными точками сетки - производим бинарный поиск нужного эл-та массива
  {
    int i = 0;
    int j = nodesCount - 1;
    while ( i + 1 < j )
    {
      int k = i + ( j - i ) / 2;
      if ( x <= splines[k].x )
      {
        j = k;
      }
      else
      {
        i = k;
      }
     }
     s = splines.begin() + j;
   }

  x -= s->x;

  float a0 = s->a0;
  float a1 = s->a1;
  float a2 = s->a2;
  float a3 = s->a3;

  // Вычисляем значение сплайна в заданной точке по схеме Горнера
  // (в принципе, "умный" компилятор применил бы схему Горнера сам, но ведь не все так умны, как кажутся)

  return a3 * x*x*x / 6.0f + a2 * x*x / 2.0f + a1 * x + a0;
}

float CubicSpline::GetDiff( float x ) const
{
  NI_VERIFY( splines.size() > 0, "Spline wasn't build!", return 0.0f );

  nstl::vector<SplineTuple>::const_iterator s = splines.begin();

  if ( x <= splines[0].x ) // Если x меньше точки сетки x[0] - пользуемся первым эл-том массива
  {
    x = splines[0].x;
    s = splines.begin();
  }
  else if ( x >= splines[nodesCount - 1].x ) // Если x больше точки сетки x[n - 1] - пользуемся последним эл-том массива
  {
    x = splines[nodesCount - 1].x;
    s = splines.end() - 1;
  }
  else // Иначе x лежит между граничными точками сетки - производим бинарный поиск нужного эл-та массива
  {
    int i = 0;
    int j = nodesCount - 1;
    while ( i + 1 < j )
    {
      int k = i + ( j - i ) / 2;
      if ( x <= splines[k].x )
      {
        j = k;
      }
      else
      {
        i = k;
      }
     }
     s = splines.begin() + j;
   }

  x -= s->x;

  float a1 = s->a1;
  float a2 = s->a2;
  float a3 = s->a3;

  // Вычисляем значение сплайна в заданной точке по схеме Горнера
  // (в принципе, "умный" компилятор применил бы схему Горнера сам, но ведь не все так умны, как кажутся)

  return a3 * x*x / 2.0f + a2 * x + a1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** beta spline surface
// ** Источник: "Начала компьютерной графики" под редакцией Шикина Е. В.
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// вычисление постоянных коэффицентов
// fBeta1, fBeta2 задают форму кривой
void CBetaSpline3D::Init( float _fBeta1, float _fBeta2 )
{
	fBeta1 = _fBeta1;
	fBeta2 = _fBeta2;
	invdelta = 1.0f / ( 2.0f * fBeta1 * fBeta1 * fBeta1
		+ 4.0f * fBeta1 * fBeta1
		+ 4.0f * fBeta1 + fBeta2 + 2.0f );

	VolumeCoeffs( _fBeta1, _fBeta2 );
	fBeta1_3 = 2 * fBeta1 * fBeta1 * fBeta1 * invdelta;
	fBeta1_2 = 2 * fBeta1 * fBeta1 * invdelta;

	fBeta1 *= 2 * invdelta;
	fBeta2 *= invdelta;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// весовые функциональные коэффициенты
inline float CBetaSpline3D::b_2( const float t[3] ) const
{
	return fBeta1_3 * sqr( 1 - t[0] ) * ( 1 - t[0] );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::b_1( const float t[3] ) const
{
	return fBeta1_3 * t[0] * ( t[1] - 3*t[0] + 3 ) + 
		fBeta1_2 * ( t[2] - 3*t[1] + 2 ) + 
		fBeta1 * ( t[2] - 3*t[0] + 2 ) + 
		fBeta2 * ( 2 * t[2] - 3 * t[1] + 1);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::b0( const float t[3] ) const
{
	return fBeta1_2 * t[1] * ( 3 - t[0] ) + fBeta1 * t[0] * ( 3 - t[1] ) + fBeta2 * t[1] * ( 3 - 2*t[0] ) + invdelta * 2 * ( 1 - t[2] );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::b1( const float t[3] ) const
{
	return 2 * t[2] * invdelta;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// производные функциональных коэффициентов
inline float CBetaSpline3D::db_2( const float t[3] ) const
{
	return -3.0f * fBeta1_3 * sqr( 1 - t[0] );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::db_1( const float t[3] ) const
{
	return 3.0f * (fBeta1_3 * sqr( t[0] - 1 ) + fBeta1_2 * (t[0] - 2) * t[0] 
	+ fBeta1 * (t[1] - 1) + fBeta2 * 2 * (t[0] - 1) * t[0]);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::db0( const float t[3] ) const
{
	return 3.0f * (fBeta1 + (fBeta1_2 * 2 + fBeta2 * 2) * t[0] - (invdelta * 2 + fBeta1 + fBeta1_2 + fBeta2 * 2) * t[1] );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::db1( const float t[3] ) const
{
	return 6 * t[1] * invdelta;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Вычисление интерполированного значения для параметров 0<= u,v <= 1
// ptControls - массив контрольных точек
// в строке вершины вдоль параметра u; считается, что точки расположены в след. порядке: 
// v(-2, l), v(-1, l), v(0, l), (1, l)
// в столбце вдоль параметра v; в следующем порядке v(j, -2), v(j, -1), v(j, -0), (j, 1)
// Полученное интерполированное значение принадлежит интервалу v1( -1, -1 ) - v2( 0, 0 )
// ( v1 соответствует u=v=0,  v2  u=v=1 - "элементарная поверхность" ) 
const float CBetaSpline3D::Value( float u, float v, const float ptCtrls[16] ) const
{
	float t[3];
	t[0] = u;
	t[1] = u * u;
	t[2] = t[1] * u;
	const float bj[4] = { b_2( t ), b_1( t ), b0( t ), b1( t ) };

	t[0] = v;
	t[1] = v * v;
	t[2] = t[1] * v;
	float bl[4] = { b_2( t ), b_1( t ), b0( t ), b1( t ) };

	// внутреннее суммирование по параметру v
	return	
		bj[0] * ( bl[0] * ptCtrls[0] + bl[1] * ptCtrls[4] + bl[2] * ptCtrls[8]	+ bl[3] * ptCtrls[12] ) +
		bj[1] * ( bl[0] * ptCtrls[1] + bl[1] * ptCtrls[5] + bl[2] * ptCtrls[9]  + bl[3] * ptCtrls[13] ) +
		bj[2] * ( bl[0] * ptCtrls[2] + bl[1] * ptCtrls[6] + bl[2] * ptCtrls[10] + bl[3] * ptCtrls[14] ) +
		bj[3] * ( bl[0] * ptCtrls[3] + bl[1] * ptCtrls[7] + bl[2] * ptCtrls[11] + bl[3] * ptCtrls[15] );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CBetaSpline3D::GetNormal( CVec3 *pvNormal, float u, float v, const float ptCtrls[16] ) const
{
	float t[3];
	t[0] = u;
	t[1] = u * u;
	t[2] = t[1] * u;
	const float bj[4]  = { b_2( t ), b_1( t ), b0( t ), b1( t ) };
	const float dbj[4] = { db_2( t ), db_1( t ), db0( t ), db1( t ) };

	t[0] = v;
	t[1] = v * v;
	t[2] = t[1] * v;
	const float bl[4] = { b_2( t ), b_1( t ), b0( t ), b1( t ) };
	const float dbl[4] = { db_2( t ), db_1( t ), db0( t ), db1( t ) };

	const float z1 = 
		dbj[0] * ( bl[0] * ptCtrls[0] + bl[1] * ptCtrls[4] + bl[2] * ptCtrls[8]  + bl[3] * ptCtrls[12] ) +
		dbj[1] * ( bl[0] * ptCtrls[1] + bl[1] * ptCtrls[5] + bl[2] * ptCtrls[9]  + bl[3] * ptCtrls[13] ) +
		dbj[2] * ( bl[0] * ptCtrls[2] + bl[1] * ptCtrls[6] + bl[2] * ptCtrls[10] + bl[3] * ptCtrls[14] ) +
		dbj[3] * ( bl[0] * ptCtrls[3] + bl[1] * ptCtrls[7] + bl[2] * ptCtrls[11] + bl[3] * ptCtrls[15] );
	const float x1 = (  bl[0] +  bl[1] +  bl[2] +  bl[3] ) * ( -2 * dbj[0] - dbj[1] + dbj[3] );
	const float y1 = ( dbj[0] + dbj[1] + dbj[2] + dbj[3] ) * ( -2 *  bl[0] -  bl[1] +  bl[3] );

	const float z2 = 
		bj[0] * ( dbl[0] * ptCtrls[0] + dbl[1] * ptCtrls[4] + dbl[2] * ptCtrls[8]  + dbl[3] * ptCtrls[12] ) +
		bj[1] * ( dbl[0] * ptCtrls[1] + dbl[1] * ptCtrls[5] + dbl[2] * ptCtrls[9]  + dbl[3] * ptCtrls[13] ) +
		bj[2] * ( dbl[0] * ptCtrls[2] + dbl[1] * ptCtrls[6] + dbl[2] * ptCtrls[10] + dbl[3] * ptCtrls[14] ) +
		bj[3] * ( dbl[0] * ptCtrls[3] + dbl[1] * ptCtrls[7] + dbl[2] * ptCtrls[11] + dbl[3] * ptCtrls[15] );
	const float x2 = ( dbl[0] + dbl[1] + dbl[2] + dbl[3] ) * ( -2 *  bj[0] -  bj[1] +  bj[3] );
	const float y2 = (  bj[0] +  bj[1] +  bj[2] +  bj[3] ) * ( -2 * dbl[0] - dbl[1] + dbl[3] );

	pvNormal->x = y1 * z2 - y2 * z1;
	pvNormal->y = x2 * z1 - z2 * x1;
	pvNormal->z = x1 * y2 - y1 * x2;

	Normalize( pvNormal );
	/*
	// внутреннее суммирование по параметру v
	CVec3 ptDU, ptDV;
	ptDU  = dbj[0] * ( bl[0] * ptCtrls1[0] + bl[1] * ptCtrls1[4] + bl[2] * ptCtrls1[8] + bl[3] * ptCtrls1[12] );
	ptDU += dbj[1] * ( bl[0] * ptCtrls1[1] + bl[1] * ptCtrls1[5] + bl[2] * ptCtrls1[9]  + bl[3] * ptCtrls1[13] );
	ptDU += dbj[2] * ( bl[0] * ptCtrls1[2] + bl[1] * ptCtrls1[6] + bl[2] * ptCtrls1[10] + bl[3] * ptCtrls1[14] );
	ptDU += dbj[3] * ( bl[0] * ptCtrls1[3] + bl[1] * ptCtrls1[7] + bl[2] * ptCtrls1[11] + bl[3] * ptCtrls1[15] );

	ptDV  = bj[0] * ( dbl[0] * ptCtrls1[0] + dbl[1] * ptCtrls1[4] + dbl[2] * ptCtrls1[8] + dbl[3] * ptCtrls1[12] );
	ptDV += bj[1] * ( dbl[0] * ptCtrls1[1] + dbl[1] * ptCtrls1[5] + dbl[2] * ptCtrls1[9]  + dbl[3] * ptCtrls1[13] );
	ptDV += bj[2] * ( dbl[0] * ptCtrls1[2] + dbl[1] * ptCtrls1[6] + dbl[2] * ptCtrls1[10] + dbl[3] * ptCtrls1[14] );
	ptDV += bj[3] * ( dbl[0] * ptCtrls1[3] + dbl[1] * ptCtrls1[7] + dbl[2] * ptCtrls1[11] + dbl[3] * ptCtrls1[15] );

	*pvNormal = -( ptDU ^ ptDV );
	*/
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CBetaSpline3D::VolumeCoeffs( float b1, float b2 )
{
	float d = sqr( invdelta ) / 4.0f;
	float b12 = b1  * b1;
	float b13 = b12 * b1;
	float b14 = b13 * b1;
	float b15 = b14 * b1;
	float b16 = b15 * b1;

	fVolCoeffs[0] = d * b16;
	fVolCoeffs[1] = d * ( 3*b16 + 5*b15 + 3*b14 + b2*b13 );
	fVolCoeffs[2] = d * ( 3*b15 + 5*b14 + b2*b13 + 3*b13 );
	fVolCoeffs[3] = d * b13;

	fVolCoeffs[4 + 0] = fVolCoeffs[1];
	fVolCoeffs[4 + 1] = d * ( 9*b16 + 30*b15 + 43*b14 + 6*b2*b13 + 30*b13 + 10*b2*b12 + 9*b12 + 6*b2*b1 + b2*b2 );
	fVolCoeffs[4 + 2] = d * ( 9*b15 + 30*b14 + 3*b2*b13 + 43*b13 + 8*b2*b12 + 30*b12 + 8*b2*b1 + 9*b1 + b2*b2 + 3*b2 );
	fVolCoeffs[4 + 3] = d * ( 3*b13 + 5*b12 + 3*b1 + b2 );

	fVolCoeffs[8 + 0] = fVolCoeffs[2];
	fVolCoeffs[8 + 1] = fVolCoeffs[4 + 2];
	fVolCoeffs[8 + 2] = d * ( 9*b14 + 30*b13 + 6*b2*b12 + 43*b12 + 10*b2*b1 + 30*b1 + b2*b2 + 6*b2 + 9 );
	fVolCoeffs[8 + 3] = d * ( 3*b12 + 5*b1 + b2 + 3 );

	fVolCoeffs[12 + 0] = fVolCoeffs[3];
	fVolCoeffs[12 + 1] = fVolCoeffs[4 + 3];
	fVolCoeffs[12 + 2] = fVolCoeffs[8 + 3];
	fVolCoeffs[12 + 3] = d;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Вспомогательные функции для вычисления средней высоты
// t[0] - степени коэффициента t0  ( первая-4тая степень )
// t[1] - степени коэффициента t1  ( первая-4тая степень )
inline float CBetaSpline3D::F00( const float t[2][4] ) const
{
	return -4*t[0][0] + 6*t[0][1] - 4*t[0][2] + t[0][3] - t[1][0]*(-4 + 6*t[1][0] - 4*t[1][1] + t[1][2]);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::F11( const float t[2][4] ) const
{
	return 9*t[0][0] - 5*t[0][2] + 2*t[0][3] - 9*t[1][0] + 5*t[1][2] - 2*t[1][3];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::F22( const float t[2][4] ) const
{
	return 2*t[0][3] - 3*t[0][2] - 3*t[0][1] - 2*t[0][0] + t[1][0]*(-2*t[1][2] + 3*t[1][1] + 3*t[1][0] + 2);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::F33( const float t[2][4] ) const
{
	return t[0][3] - t[1][3];
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::F01( const float s[2][4], const float t[2][4] ) const
{
	return (9*s[0][0] - 5*s[0][2] + 2*s[0][3] - 9*s[1][0] + 5*s[1][2] - 2*s[1][3]) * 
		(-4*t[0][0] + 6*t[0][1] - 4*t[0][2] + t[0][3] - t[1][0] * (-4 + 6*t[1][0] - 4*t[1][1] + t[1][2]) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::F02( const float s[2][4], const float t[2][4] ) const
{
	return (-2*s[0][0] - 3*s[0][1] - 3*s[0][2] + 2*s[0][3] + s[1][0] * (2 + 3*s[1][0] + 3*s[1][1] - 2*s[1][2])) * 
		(-4*t[0][0] + 6*t[0][1] - 4*t[0][2] + t[0][3] - t[1][0] * (-4 + 6*t[1][0] - 4*t[1][1] + t[1][2]));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::F03( const float s[2][4], const float t[2][4] ) const
{
	return (s[0][3] - s[1][3]) * 
		(-4*t[0][0] + 6*t[0][1] - 4*t[0][2] + t[0][3] - t[1][0]*(-4 + 6*t[1][0] - 4*t[1][1] + t[1][2]));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::F12( const float s[2][4], const float t[2][4] ) const
{
	return (-2*s[0][0] - 3*s[0][1] - 3*s[0][2] + 2*s[0][3] + s[1][0] * (2 + 3*s[1][0] + 3*s[1][1] - 2*s[1][2])) 
		* (9*t[0][0] - 5*t[0][2] + 2*t[0][3] - 9*t[1][0] + 5*t[1][2] - 2*t[1][3]);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::F13( const float s[2][4], const float t[2][4] ) const
{
	return (s[0][3] - s[1][3]) * (9*t[0][0] - 5*t[0][2] + 2*t[0][3] - 9*t[1][0] + 5*t[1][2] - 2*t[1][3]);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float CBetaSpline3D::F23( const float s[2][4], const float t[2][4] ) const
{
	return (s[0][3] - s[1][3]) * 
		(-2*t[0][0] - 3*t[0][1] - 3*t[0][2] + 2*t[0][3] + t[1][0] * (2 + 3*t[1][0] + 3*t[1][1] - 2*t[1][2]));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////