#include "PlaneGeometry.h"

// Convert float parameter into (segment, offset) pair.
// In:  global    float   [0, N]
//      numSegments  number of segments (that's what N equals to)
// Out: segment   integer [0..N-1]
//      offset    float   [0, 1]
inline void _SegmentAndOffset(float global, int numSegments, int &segment, float &offset)
{
  NI_ASSERT(0.f <= global && global <= (float)(numSegments), "Parameter out of bounds");

  float s = floor(global);
  segment = (int)s;

  if (segment == numSegments)
  {
    --segment;
    offset = 1.f;
  }
  else
  {
    offset = global - s;
  }
}

template <class POINT>
inline void _BSplineControlPointsToBezier(POINT const *bspline, POINT *bezier)
{
  bezier[0] = (bspline[0] + 4.f * bspline[1] + bspline[2]) / 6;
  bezier[1] = (2.f * bspline[1] + bspline[2]) / 3;
  bezier[2] = (bspline[1] + 2.f * bspline[2]) / 3;
  bezier[3] = (bspline[1] + 4.f * bspline[2] + bspline[3]) / 6;
}

template <class POINT>
bool IsBezierPolygonFlat(POINT const &p0, POINT const &p1, POINT const &p2, POINT const &p3, float epsilon);

template <class POINT, class LEAFPROC>
class BezierSubdivision : public NonCopyable
{
public:
  LEAFPROC &leafProc;
  float flatness;
  float maxDepth;
  float maxDistSq;

  BezierSubdivision(POINT const *points, LEAFPROC &lp)
    : leafProc(lp)
    , flatness(1e-2f)
    , maxDistSq(FP_MAX_VALUE)
    , maxDepth(5)
  {
    SplitUntilFlat(points[0], points[1], points[2], points[3], 0.f, 1.f, 0);
  }

  BezierSubdivision(POINT const *points, LEAFPROC &lp, float flatness, float maxDistance)
    : leafProc(lp)
    , flatness(flatness)
    , maxDepth(5)
  {
    NI_ASSERT(maxDistance < 1e17f, "Distance limit is too large number");
    maxDistSq = maxDistance * maxDistance;
    SplitUntilFlat(points[0], points[1], points[2], points[3], 0.f, 1.f, 0);
  }

protected:
  void SplitUntilFlat(POINT const &p0, POINT const &p1, POINT const &p2, POINT const &p3, float left, float right, int depth)
  {
    if ( right - left < 1e-5f ||
         depth > maxDepth ||
         ( IsBezierPolygonFlat(p0, p1, p2, p3, flatness) &&
           fabs2(p3-p0) < maxDistSq ) )
    {
      // no further subdivision -- call leaf processor
      leafProc(p0, p1, p2, p3, left, right);
      return;
    }

    // subdivide bezier curve in two
    POINT a[3], b[2], c;
    a[0] = 0.5f * (p0 + p1);
    a[1] = 0.5f * (p1 + p2);
    a[2] = 0.5f * (p2 + p3);
    b[0] = 0.5f * (a[0] + a[1]);
    b[1] = 0.5f * (a[1] + a[2]);
    c    = 0.5f * (b[0] + b[1]);

    float center = 0.5f * (left + right);
    SplitUntilFlat(p0, a[0], b[0], c, left, center, depth+1);
    SplitUntilFlat(c, b[1], a[2], p3, center, right, depth+1);
  }
};

template <class POINT>
CCompositeBSpline<POINT>::CCompositeBSpline(POINT const &start, POINT const &end)
  : validFlags(0)
{
  SetupBy2Points(start, end);
}

template <class POINT>
CCompositeBSpline<POINT>::CCompositeBSpline(nstl::vector<POINT> const &points)
: validFlags(0)
{
  switch (points.size())
  {
    case 0: SetupBy2Points(POINT(), POINT()); break;
    case 1: SetupBy2Points(points[0], points[0]); break;
    case 2: SetupBy2Points(points[0], points[1]); break;
    case 3:
    {
      controlPoints.push_back(points[0]);
      controlPoints.push_back(points[1]);
      controlPoints.push_back(points[1]);
      controlPoints.push_back(points[2]);
      break;
    }
    default:
      controlPoints = points;
  }
}

template <class POINT>
void CCompositeBSpline<POINT>::InsertPoint(int index, POINT const &p)
{
  NI_ASSERT(0 <= index && index <= controlPoints.size(), "Index out of bounds");
  controlPoints.insert(controlPoints.begin() + index, p);
  validFlags = 0;
}

template <class POINT>
void CCompositeBSpline<POINT>::RemovePoint(int index)
{
  NI_ASSERT(0 <= index && index < controlPoints.size(), "Index out of bounds");
  controlPoints.eraseByIndex(index);
  validFlags = 0;
}

template <class POINT>
void CCompositeBSpline<POINT>::UpdatePoint(int index, POINT const &p)
{
  NI_ASSERT(0 <= index && index < controlPoints.size(), "Index out of bounds");
  controlPoints[index] = p;
  validFlags = 0;
}

// Setup B-spline from scratch as a straight line, using two end points.
// (will get basic 4-point spline as a result)
template <class POINT>
void CCompositeBSpline<POINT>::SetupBy2Points(POINT const &start, POINT const &end)
{
  controlPoints.push_back(start);
  controlPoints.push_back( (2.f/3) * start + (1.f/3) * end );
  controlPoints.push_back( (1.f/3) * start + (2.f/3) * end );
  controlPoints.push_back(end);
  validFlags = 0;
}

// Convert float spline parameter into (segment, offset) pair.
template <class POINT>
void CCompositeBSpline<POINT>::SegmentAndOffset(float global, int &segment, float &offset)
{
  return _SegmentAndOffset(global, GetNumSegments(), segment, offset);
}

// Compute and store inside a block of data that will be used for faster processing
// in GetClosestPoint(), GetLength(), etc.
template <class POINT>
void CCompositeBSpline<POINT>::PrecomputeSegments()
{
  if (validFlags & VALID_SEGMENTS)
    return;

  segments.resize(GetNumSegments());
  float totalLength = 0.f;
  for (int i = 0; i < segments.size(); ++i)
  {
    PrecomputeSegment(i);
    Segment &s = segments[i];
    s.integralLength = totalLength;
    totalLength += s.GetTotalLength();
  }

  validFlags |= VALID_SEGMENTS;
}

// Returns index of quantum containing given parameter
template <class POINT>
int CCompositeBSpline<POINT>::Segment::FindQuantum(float t)
{
  NI_ASSERT(0.f <= t && t <= 1.f, "Parameter out of bounds");

  if (quants.size() <= 0)
    return -1;

  int left = 0, right = quants.size()-1;

  if (t >= quants[right].param)
    return right;

  // t is bounded by starting params of "left" and "right" quants
  // perform dichotomical search
  while (true)
  {
    if (right - left <= 1)
      break;

    int center = (left + right) / 2;
    if (t < quants[center].param)
    {
      right = center;
    }
    else
    {
      left = center;
    }
  }

  return left;
}

// Returns length in metric units for the part of the spline segment
// from t = 0 to specified value.
template <class POINT>
float CCompositeBSpline<POINT>::Segment::GetLength(float t)
{
  int q = FindQuantum(t);
  float left  = quants[q].param;
  float right = (q == quants.size() - 1) ? 1.f : quants[q+1].param;
  float a = (t - left) / (right - left);
  return (quants[q].integralLength + a * quants[q].length);
}

// Returns length in metric units for the part of the spline
// from start point to specified parameter.
template <class POINT>
float CCompositeBSpline<POINT>::GetLength(float t)
{
  if (!(validFlags & VALID_SEGMENTS))
    PrecomputeSegments();

  // get spline segment/offset
  int idx;
  float offs;
  SegmentAndOffset(t, idx, offs);
  Segment &s = segments[idx];
  return (s.integralLength + s.GetLength(offs));
}

// get spline length in metric units from start point to end point
template <class POINT>
float CCompositeBSpline<POINT>::GetTotalLength()
{
  if (!(validFlags & VALID_SEGMENTS))
    PrecomputeSegments();

  return segments[GetNumSegments()-1].integralLength + segments[GetNumSegments()-1].GetTotalLength();
}

// Returns length in metric units for the part of the spline
// from start point to specified parameter.
template <class POINT>
float CCompositeBSpline<POINT>::GetLengthExt(float t)
{
  if (!(validFlags & VALID_SEGMENTS))
    PrecomputeSegments();

  if (t < 0.f)
  {
    POINT tg = GetDiff1(0.f);
    return t * fabs(tg);
  }

  if (t > GetNumSegments())
  {
    POINT tg = GetDiff1(GetNumSegments());
    return GetTotalLength() + (t - GetNumSegments()) * fabs(tg);
  }

  return GetLength(t);
}

// Calculate bezier bounding polygons' corners for each segment.
// (on segment boundaries these points coincide)
template <class POINT>
void CCompositeBSpline<POINT>::PrecomputeBounds()
{
  if (validFlags & VALID_BOUNDS)
    return;

  bezierPoints.resize(3 * controlPoints.size() - 8);
  int segm;
  for (segm = 0; segm < controlPoints.size() - 3; ++segm)
  {
    bezierPoints[3 * segm]     = (controlPoints[segm] + 4.f * controlPoints[segm + 1] + controlPoints[segm + 2]) / 6;
    bezierPoints[3 * segm + 1] = (2.f * controlPoints[segm + 1] + controlPoints[segm + 2]) / 3;
    bezierPoints[3 * segm + 2] = (controlPoints[segm + 1] + 2.f * controlPoints[segm + 2]) / 3;
  }
  bezierPoints[3 * segm] = (controlPoints[segm] + 4.f * controlPoints[segm + 1] + controlPoints[segm + 2]) / 6;

  validFlags |= VALID_BOUNDS;
}

// get coordinates for point on spline at specified parameter value
template <class POINT>
POINT CCompositeBSpline<POINT>::GetExt(float t)
{
  if (t < 0.f)
  {
    // use start extension
    POINT tg = GetDiff1(0.f);
    return bezierPoints[0] + t * tg;
  }

  if (t > GetNumSegments())
  {
    // use end extension
    POINT tg = GetDiff1(GetNumSegments());
    return bezierPoints[3 * GetNumSegments()] + (t - GetNumSegments()) * tg;
  }

  return Get(t);
}

// get first derivative (tangent) at specified parameter value
template <class POINT>
POINT CCompositeBSpline<POINT>::GetDiff1Ext(float t)
{
  if (t < 0.f)
  {
    return GetDiff1(0.f);
  }

  if (t > GetNumSegments())
  {
    return GetDiff1(GetNumSegments());
  }

  return GetDiff1(t);
}

// Returns parameter for the point on spline closest to the specified arbitrary point.
template <class POINT>
float CCompositeBSpline<POINT>::GetClosestPoint(POINT const &p)
{
  if (!(validFlags & VALID_BOUNDS))
    PrecomputeBounds();

  // find closest bezier knot
  int closestKnot = 0;
  {
    float minSqDist = fabs2(p - bezierPoints[0]);
    for (int i = 1; i < controlPoints.size() - 2; ++i)
    {
      float sqDist = fabs2(p - bezierPoints[3*i]);
      if (sqDist < minSqDist)
      {
        minSqDist = sqDist;
        closestKnot = i;
      }
    }
  }

  float minSqDist = FP_MAX_VALUE;
  float param = 0.f;
  // try preceding segment
  if ( closestKnot > 0 )
  {
    float t = (float)(closestKnot-1) + GetSegmentClosestPoint(closestKnot - 1, p);
    float sqDist = fabs2(Get(t) - p);
    if (sqDist < minSqDist)
    {
      minSqDist = sqDist;
      param = t;
    }
  }
  // try following segment
  if ( closestKnot < controlPoints.size() - 3 )
  {
    float t = (float)(closestKnot) + GetSegmentClosestPoint(closestKnot, p);
    float sqDist = fabs2(Get(t) - p);
    if (sqDist < minSqDist)
    {
      minSqDist = sqDist;
      param = t;
    }
  }

  return param;
}

template <class POINT>
float CCompositeBSpline<POINT>::GetClosestPointExt(POINT const &p)
{
  float t = GetClosestPoint(p);

  // if point falls out off the start line
  if (t == 0.f)
  {
    // project point onto start extension
    POINT d = p - bezierPoints[0];
    POINT tg = GetDiff1(0.f);
    float tgabs2 = fabs2(tg);
    if (tgabs2 > 0.f)
    {
      // parameter is calculated so that being multiplied by tangent vector at start point it gives delta vector in meters
      return tg.Dot(d) / tgabs2;
    }
    else
    {
      return 0.f;
    }
  }

  // if point falls out off the finish line
  if (t == (float)GetNumSegments())
  {
    // project point onto end extension
    POINT d = p - bezierPoints[3 * GetNumSegments()];
    POINT tg = GetDiff1(GetNumSegments());
    float tgabs2 = fabs2(tg);
    if (tgabs2 > 0.f)
    {
      // parameter is calculated so that being multiplied by tangent vector at end point it gives delta vector in meters
      return GetNumSegments() + tg.Dot(d) / tgabs2;
    }
    else
    {
      return GetNumSegments();
    }
  }

  // projected point lies inside range
  return t;
}

template <class POINT>
void CCompositeBSpline<POINT>::Sample(float flatness, float maxLength, nstl::vector<POINT> &points)
{
  // leaf procedure for bezier subdivision algorithm that stores start point of leaf element as a sample
  struct LeafProc : public NonCopyable
  {
    nstl::vector<POINT> &samples;

    LeafProc(nstl::vector<POINT> &s) : samples(s) {}

    void operator()(POINT const &p0, POINT const &p1, POINT const &p2, POINT const &p3, float left, float right)
    {
      // store point
      samples.push_back(p0);
    }
  };

  if (!(validFlags & VALID_BOUNDS))
    PrecomputeBounds();


  points.clear();
  LeafProc lp(points);

  // build adaptive subdivision for each segment, adding sample points to array
  for (int i = 0; i < GetNumSegments(); ++i)
  {
    BezierSubdivision<POINT, LeafProc> bs(&bezierPoints[3*i], lp, flatness, maxLength);
  }

  // add end point to array
  points.push_back( bezierPoints[ 3 * GetNumSegments() ] );
}

template <class POINT>
void CCompositeBSpline<POINT>::PrecomputeSegment(int index)
{
  // leaf procedure for bezier subdivision algorithm that stores leaf elements as segment quants
  struct LeafProc : public NonCopyable
  {
    typedef vector<typename CCompositeBSpline<POINT>::SegmentQuantum> QuantumList;

    QuantumList  &quants;

    LeafProc(QuantumList &q) : quants(q) {}

    void operator()(POINT const &p0, POINT const &p1, POINT const &p2, POINT const &p3, float left, float right)
    {
      // store quantum
      CCompositeBSpline<POINT>::SegmentQuantum q;
      q.param = left;
      q.length = fabs(p3 - p0);
      quants.push_back(q);
    }
  };

  
  Segment &s = segments[index];
  
  // convert B-spline control points to bezier control points
  POINT bezier[4];
  _BSplineControlPointsToBezier(&controlPoints[index], bezier);
  
  // build adaptive subdivision
  s.quants.clear();
  LeafProc lp(s.quants);
  BezierSubdivision<POINT, LeafProc> bs(bezier, lp);

  // calculate integral length for quants
  float length = 0.f;
  for (int i = 0; i < s.quants.size(); ++i)
  {
    s.quants[i].integralLength = length;
    length += s.quants[i].length;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CCompositeBSplineWidth
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class POINT>
float CCompositeBSplineWidth<POINT>::GetWidth(float at)
{
  int s;
  float offs;
  this -> SegmentAndOffset(at, s, offs);
  NI_ASSERT(0 <= s && s < this -> GetNumSegments(), "Rebuild spline");
  return (1.f - offs) * width[s] + offs * width[s + 1];
}

template <class POINT>
float CCompositeBSplineWidth<POINT>::GetWidthExt(float at)
{
  if (at < 0.f)
    return width[0];
  
  if (at > this -> GetNumSegments())
    return width[this -> GetNumSegments()];

  int s;
  float offs;
  this -> SegmentAndOffset(at, s, offs);
  NI_ASSERT(0 <= s && s < this -> GetNumSegments(), "Rebuild spline");
  return (1.f - offs) * width[s] + offs * width[s + 1];
}

template <class POINT>
bool CCompositeBSplineWidth<POINT>::IsInside(POINT const &p)
{
  // find closest point on spline
  float t = GetClosestPointExt(p);
  
  if (t < 0.f)
    return false;
  
  if (t > this -> GetNumSegments())
    return false;

  POINT sp = this -> Get(t);
  return (fabs(p-sp) < GetWidth(t));
}

template <class POINT>
bool CCompositeBSplineWidth<POINT>::EdgeIntersectsBounds(POINT const &p0, POINT const &p1)
{
// This code was not tested!
/*
  if (!(validFlags & VALID_SEGMENTS))
    PrecomputeSegments();

  POINT start[2];
  POINT end[2];
  EClassifyIntersection c;

  GetSection(0.f, start[0], start[1]);

  // check intersection with start line
  c = ClassifyIntersect(p0, p1, start[0], start[1], NULL);
  if (c == CI_SKEW_CROSS)
    return true;

  // check intersection with edges of each segment quantum
  for (int i = 0; i < GetNumSegments(); ++i)
  {
    Segment &s = segments[i];
    
    for (int j = 0; j < s.quants.size(); ++j)
    {
      SegmentQuantum &q = s.quants[j];
      float endParam = (j == s.quants.size()-1) ? 1.f : s.quants[j+1].param;

      GetSection(endParam, end[0], end[1]);
      
      c = ClassifyIntersect(p0, p1, start[0], end[0], NULL);
      if (c == CI_SKEW_CROSS)
        return true;

      c = ClassifyIntersect(p0, p1, start[1], end[1], NULL);
      if (c == CI_SKEW_CROSS)
        return true;

      start[0] = end[0];
      start[1] = end[1];
    }
  }

  // check intersection with finish line
  c = ClassifyIntersect(p0, p1, start[0], start[1], NULL);
  if (c == CI_SKEW_CROSS)
    return true;
*/

  return false;
}

template <class POINT>
bool CCompositeBSplineWidth<POINT>::ClassifyConvexPolygon(nstl::vector<POINT> const &v)
{
  // This code was not tested!
/*
  NI_ASSERT(v.size() >= 3, "Invalid polygon");

  // first, check each edge of the polygon for intersection with spline boundaries
  POINT const *p0 = &v[v.size() - 1];
  int i;
  for (i = 0; i < v.size(); ++i)
  {
    POINT const *p1 = &v[i];
    if (EdgeIntersectsBounds(*p0, *p1))
      break;
    p0 = p1;
  }

  if (i < v.size())
    return true;

  // check if single polygon vertex belongs to the spline area
  // (it will mean that whole oplygon belongs to the spline area)
  if (IsInside(v[0]))
    return true;
*/
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CVec2 specialization
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <> bool IsBezierPolygonFlat<CVec2>(CVec2 const &p0, CVec2 const &p1, CVec2 const &p2, CVec2 const &p3, float epsilon);

template <> float CCompositeBSpline<CVec2>::GetSegmentClosestPoint(int index, CVec2 const &p);
template <> CVec2 CCompositeBSpline<CVec2>::Get(float t);
template <> CVec2 CCompositeBSpline<CVec2>::GetDiff1(float t);
//template <> void  CCompositeBSpline<CVec2>::PrecomputeSegment(int index);

template <> CVec2 CCompositeBSplineWidth<CVec2>::GetSection(float at, CVec2 &p0, CVec2 &p1);