#include "stdafx.h"
#include "NatureAttackSpace.h"
#include "NatureMap.h"
#include "../System/lerp.h"
#include "../Render/debugrenderer.h"

namespace Terrain {

namespace {

  inline float GetAngle(CVec2 const& pt)
  {
    return atan2f(pt.y, pt.x);
  }

  inline float GetYLerpByX(CVec2 const& a, CVec2 const& b, float x)
  {
    return Lerp(a.y, b.y, (x - a.x) / (b.x - a.x));
  }

  inline float GetXLerpByY(CVec2 const& a, CVec2 const& b, float y)
  {
    return Lerp(a.x, b.x, (y - a.y) / (b.y - a.y));
  }

  // finds the first point index in [idx..count-1] which satisfies predicate, returns count if not found
  template <class PREDICATE>
  int FindPointIndex(PREDICATE const& p, int idx, CVec2 const* pStart, int count, int stride = 1)
  {
    // smirnov [2009/4/14]: could be rewritten as binary search
    pStart += stride * idx;
    while (idx < count && !p(pStart))
    {
      idx++;
      pStart += stride;
    }
    return idx;
  }

  struct ByXCoord {
    float x;
    ByXCoord(float x_) : x(x_) {}
    bool operator()(CVec2 const* pt) const { return x <= pt->x; }
  };

  struct ByYCoord {
    float y;
    ByYCoord(float y_) : y(y_) {}
    bool operator()(CVec2 const* pt) const { return y <= pt->y; }
  };

  struct ByAngle {
    float phi;
    CVec2 const* origin;
    ByAngle(float phi_, CVec2 const* origin_) : phi(phi_), origin(origin_) {}
    bool operator()(CVec2 const* pt) const { return fabs(phi) >= fabs(GetAngle(*pt - *origin)); }
  };

  inline bool In01(float x)
  {
    static const float MY_EPS_VALUE = 1e-5f;
    return x >= -MY_EPS_VALUE && x <= 1.0f + MY_EPS_VALUE;
  }

} // anonymous namespace

NatureAttackSpace::NatureAttackSpace() 
  : numStrips(0)
  , numSegments(0)
  , nodesPitch(0)
  , nodesCount(0)
  , quadsPitch(0)
  , quadsCount(0)
{
}

NatureAttackSpace::~NatureAttackSpace()
{
}

void NatureAttackSpace::InitFields(const NDb::DBNatureMap& dbNatureMap)
{
  center.Set(0.5f, 0.5f); // will be overwritten
  numStrips = 2 * numRoads - 1;
  numSegments = dbNatureMap.segmentCount;

  // derivatives
  nodesPitch = (numSegments + 1) + 2; // extra nodes for bases
  nodesCount = (numStrips + 1) * nodesPitch;
  quadsPitch = numSegments + 2; // extra quads for bases
  quadsCount = numStrips * quadsPitch;

  Reset(pNodes, new CVec2[nodesCount]);
  Reset(pSolvers, new BilinearSolver2D[quadsCount]);
}

bool NatureAttackSpace::Create(const NDb::DBNatureMap& dbNatureMap, CVec3& worldSize)
{
  InitFields(dbNatureMap);

  NDb::DBNatureMapRoad const& roadTop = dbNatureMap.attackSpaceRoads[NDb::NATUREROAD_TOP];
  NDb::DBNatureMapRoad const& roadCenter = dbNatureMap.attackSpaceRoads[NDb::NATUREROAD_CENTER];
  NDb::DBNatureMapRoad const& roadBottom = dbNatureMap.attackSpaceRoads[NDb::NATUREROAD_BOTTOM];

  // detect map center
  NI_VERIFY(roadCenter.nodes.size() >= 2, "Road must have at least 2 nodes", return false);
  center = 0.5f * (roadCenter.nodes.front() + roadCenter.nodes.back());

  // tessellate 
  int length = nodesCount;
  ZeroMemory(Get(pNodes), length * sizeof(CVec2));
  bool ok = true;
  ok = ok && TessellateBase(dbNatureMap.baseA, dbNatureMap.baseAOffset, GetNode(0, 0));
  ok = ok && TessellateByAngle(&roadBottom, GetNode(0, 1), GetNode(1, 1));
  ok = ok && TessellateByX(&roadCenter, GetNode(3, 1), GetNode(2, 1));
  ok = ok && TessellateByAngle(&roadTop, GetNode(5, 1), GetNode(4, 1));
  ok = ok && TessellateBase(dbNatureMap.baseB, worldSize.x - dbNatureMap.baseBOffset, GetNode(0, numSegments+2));
  NI_VERIFY(ok, "Road tessellation failed", false);

  length = quadsCount;
  ZeroMemory(Get(pSolvers), length * sizeof(BilinearSolver2D));
  for (int quad = 0; quad < length; quad++)
  {
    int row = quad / quadsPitch, col = quad % quadsPitch;
    CVec2* pBottom = GetNode(row, col);
    CVec2* pTop = GetNode(row + 1, col);
    pSolvers[quad] = BilinearSolver2D(pBottom[0], pBottom[1], pTop[0], pTop[1]);
  }

  return true;
}

bool NatureAttackSpace::Load(const NDb::DBNatureMap& dbNatureMap, Stream* pStream)
{
  InitFields(dbNatureMap);

  int bytesRead = pStream->Read(&center, sizeof(center));
  NI_VERIFY(bytesRead == sizeof(center), "Unable to load origin", return false);

  int length = nodesCount * sizeof(CVec2);
  bytesRead = pStream->Read(Get(pNodes), length);
  NI_VERIFY(bytesRead == length, "Unable to load road node data", return false);

  length = quadsCount * sizeof(BilinearSolver2D);
  bytesRead = pStream->Read(Get(pSolvers), length);
  NI_VERIFY(bytesRead == length, "Unable to load solver data", return false);

  return true;
}

bool NatureAttackSpace::Save(Stream* pStream) const
{
  ASSERT(pStream);

  int bytesWritten = pStream->Write(&center, sizeof(center));
  NI_VERIFY(bytesWritten == sizeof(center), "Unable to save origin", return false);

  int length = nodesCount * sizeof(CVec2);
  bytesWritten = pStream->Write(Get(pNodes), length);
  NI_VERIFY(bytesWritten == length, "Unable to save road node data", return false);

  length = quadsCount * sizeof(BilinearSolver2D);
  bytesWritten = pStream->Write(Get(pSolvers), length);
  NI_VERIFY(bytesWritten == length, "Unable to save solver data", return false);

  return true;
}

int NatureAttackSpace::TessellateBase(CVec2 const& base, float xLimit, CVec2* pStart)
{
  CVec2 limit(xLimit, base.y);
  *pStart = limit;
  pStart += nodesPitch;
  for (int row = 1; row < numStrips; row++, pStart += nodesPitch)
    *pStart = base;
  *pStart = limit;
  return true;
}

int NatureAttackSpace::TessellateByX(vector<CVec2> const& nodes, int idx, float x, float halfwidth, CVec2* pUpper, CVec2* pLower)
{
  ASSERT(idx < nodes.size()); // internal logic error

  // skip to proper line segment
  idx = FindPointIndex(ByXCoord(x), idx, &nodes.front(), nodes.size() - 1);

  // interpolate (or extrapolate)
  CVec2 const& a = nodes[idx-1];
  CVec2 const& b = nodes[idx];
  pUpper->x = pLower->x = x;
  pUpper->y = pLower->y = GetYLerpByX(a, b, x);

  pUpper->y += halfwidth;
  pLower->y -= halfwidth;

  return idx;
}

bool NatureAttackSpace::TessellateByX(NDb::DBNatureMapRoad const* pRoad, CVec2* pUpperLine, CVec2* pLowerLine)
{
  NI_VERIFY(pRoad->nodes.size() >= 2, "Road must have at least 2 nodes", return false);
  CVec2* pUpper = pUpperLine;
  CVec2* pUpperEnd = pUpperLine + numSegments+1; // sic! not nodesPitch
  CVec2* pLower = pLowerLine;
  CVec2* pLowerEnd = pLowerLine + numSegments+1; // sic! not nodesPitch
  int idx = 1;

  // even subdivision
  float x = pRoad->nodes.front().x;
  float span = pRoad->nodes.back().x - x;
  float step = span / (float)numSegments;
  int limit = numSegments;
  for (int i = 0; i <= limit; i++)
  {
    float halfwidth;
    if (x <= center.x)
      halfwidth = 0.5f * Lerp(pRoad->centerWidth, pRoad->leftWidth, 2.0f * (center.x - x) / span);
    else
      halfwidth = 0.5f * Lerp(pRoad->centerWidth, pRoad->rightWidth, 2.0f * (x - center.x) / span);

    ASSERT(pUpper < pUpperEnd && pLower < pLowerEnd);
    idx = TessellateByX(pRoad->nodes, idx, x, halfwidth, pUpper++, pLower++);
    x += step;
  }

  // check that everything is filled
  ASSERT(pUpper == pUpperEnd && pLower == pLowerEnd);
  return true;
}

int NatureAttackSpace::TessellateByAngle(vector<CVec2> const& nodes, int idx, float phi, float halfwidth, CVec2* pOuter, CVec2* pInner)
{
  ASSERT(idx < nodes.size()); // internal logic error

  // skip to proper line segment
  idx = FindPointIndex(ByAngle(phi, &center), idx, &nodes.front(), nodes.size() - 1);

  // interpolate (or extrapolate)
  CVec2 const& a = nodes[idx-1];
  CVec2 const& b = nodes[idx];
  float phiA = GetAngle(a - center);
  float phiB = GetAngle(b - center);
  *pOuter = *pInner = Lerp(a, b, (phi - phiA) / (phiB - phiA));

  CVec2 dir = *pOuter - center;
  Normalize(&dir);

  pOuter->Displace(dir, halfwidth);
  pInner->Displace(dir,-halfwidth);

  return idx;
}

bool NatureAttackSpace::TessellateByAngle(NDb::DBNatureMapRoad const* pRoad, CVec2* pOuterLine, CVec2* pInnerLine)
{
  NI_VERIFY(pRoad->nodes.size() >= 2, "Road must have at least 2 nodes", return false);
  CVec2* pOuter = pOuterLine;
  CVec2* pOuterEnd = pOuterLine + numSegments+1; // sic! not nodesPitch
  CVec2* pInner = pInnerLine;
  CVec2* pInnerEnd = pInnerLine + numSegments+1; // sic! not nodesPitch
  int idx = 1;

  float centerPhi = pRoad->nodes.front().y > center.y ? FP_PI2 : -FP_PI2;

  float phi = GetAngle(pRoad->nodes.front() - center);
  float span = GetAngle(pRoad->nodes.back() - center) - phi;
  float step = span / (float)numSegments;
  int limit = numSegments;
  for (int i = 0; i <= limit; i++)
  {
    float halfwidth;
    if (fabs(phi) >= fabs(centerPhi))
      halfwidth = 0.5f * Lerp(pRoad->centerWidth, pRoad->leftWidth, 2.0f * (centerPhi - phi) / span);
    else
      halfwidth = 0.5f * Lerp(pRoad->centerWidth, pRoad->rightWidth, 2.0f * (phi - centerPhi) / span);

    ASSERT(pOuter < pOuterEnd && pInner < pInnerEnd);
    idx = TessellateByAngle(pRoad->nodes, idx, phi, halfwidth, pOuter++, pInner++);
    phi += step;
  }

  // check that everything is filled
  ASSERT(pOuter == pOuterEnd && pInner == pInnerEnd);
  return true;
}

int NatureAttackSpace::FindSegment(CVec2 const& pos) const
{
  for (int seg = 0; seg <= numSegments; seg++)
  {
    CVec2 const* pStart = GetNode(0, seg + 1);
    int idx = FindPointIndex(ByYCoord(pos.y), 0, pStart, numStrips + 1, nodesPitch);
    idx = ClampFast(idx, 1, numStrips);
    CVec2 const* pB = pStart + idx * nodesPitch;
    CVec2 const* pA = pB - nodesPitch;
    if (pos.x < GetXLerpByY(*pA, *pB, pos.y))
      return seg - 1;
  }
  return numSegments;
}

int NatureAttackSpace::FindStrip(CVec2 const& pos, int seg) const
{
  struct ByYCoordLerp {
    CVec2 pos;
    ByYCoordLerp(CVec2 pos_) : pos(pos_) {}
    bool operator()(CVec2 const* pt) const { return pos.y <= GetYLerpByX(pt[0], pt[1], pos.x); }
  };

  int row = FindPointIndex(ByYCoordLerp(pos), 0, GetNode(0, seg + 1), numStrips + 1, nodesPitch);
  return row - 1;
}

CVec2 NatureAttackSpace::FindCoordinatesAS(CVec2 const& posWS) const
{
  int row = 888888;
  int seg = FindSegment(posWS);
  if (seg < 0)
  {
    CVec2 const* pBase = GetNode(1,0);
    if (posWS.x > pBase->x)
      row = FindStrip(posWS, -1);
    else if (posWS.y < pBase->y)
    {
      CVec2 const* pLine = GetNode(0,0);
      if (posWS.x <= GetXLerpByY(pLine[0], pLine[1], posWS.y))
        row = -1;
      else
        row = 0;
    }
    else
    {
      CVec2 const* pLine = GetNode(numStrips,0);
      if (posWS.x <= GetXLerpByY(pLine[0], pLine[1], posWS.y))
        row = numStrips;
      else
        row = numStrips - 1;
    }
  }
  else if (seg >= numSegments)
  {
    CVec2 const* pBase = GetNode(1,numSegments+2);
    if (posWS.x < pBase->x)
      row = FindStrip(posWS, numSegments);
    else if (posWS.y < pBase->y)
    {
      CVec2 const* pLine = GetNode(0,numSegments+1);
      if (posWS.x >= GetXLerpByY(pLine[0], pLine[1], posWS.y))
        row = -1;
      else
        row = 0;
    }
    else
    {
      CVec2 const* pLine = GetNode(numStrips,numSegments+1);
      if (posWS.x >= GetXLerpByY(pLine[0], pLine[1], posWS.y))
        row = numStrips;
      else
        row = numStrips - 1;
    }
  }
  else
  {
    row = FindStrip(posWS, seg);
  }

  int rowClamped = ClampFast(row, 0, numStrips-1);
  BilinearSolver2D const* pSolver = GetQuad(rowClamped, seg + 1);
  CVec2 coords = pSolver->Solve(posWS);
  NI_ASSERT(In01(coords.x), "Wrong solution, out of bounds");
  NI_ASSERT(In01(coords.y) || row >= numStrips-1 || row <= 0, "Wrong solution, out of bounds");
  coords.x += seg;
  coords.y += row;

  return coords;
}

CVec2 NatureAttackSpace::FindCoordinatesWS(CVec2 const& posAS) const
{
  int row = (int)floor(posAS.y);
  row = ClampFast(row, 0, numStrips - 1);
  //ASSERT(0 <= row && row < numStrips);
  int seg = (int)floor(posAS.x);
  seg = ClampFast(seg, -1, numSegments);
  //ASSERT(0 <= seg && seg < numSegments);

  CVec2 k;
  k.x = posAS.x - seg;
  k.y = posAS.y - row;
  BilinearSolver2D const* pSolver = GetQuad(row, seg + 1);
  return pSolver->Restore(k);
}

void NatureAttackSpace::RenderDebug()
{
#ifndef VISUAL_CUTTED
  float z = 0.0f;
  Render::Color color(0, 255, 0);

  for (int line = 0; line <= numStrips; line++)
  {
    for (int i = 0; i < nodesPitch-1; i++)
    {
      CVec3 a(*GetNode(line, i), z);
      CVec3 b(*GetNode(line, i+1), z);
      Render::DebugRenderer::DrawLine3D(a, b, color, color, false);
    }
  }

  for (int i = 0; i < nodesPitch; i++)
  {
    for (int line = 0; line < numStrips; line++)
    {
      CVec3 a(*GetNode(line,   i), z);
      CVec3 b(*GetNode(line+1, i), z);
      Render::DebugRenderer::DrawLine3D(a, b, color, color, false);
    }
  }
#endif  
}

void NatureAttackSpace::RenderDebugTile(CVec2 const& _attackPos, Render::Color crossColor)
{
#ifndef VISUAL_CUTTED
  float z = 0.0f;
  Render::Color color(255, 0, 0);

  int segment = ClampFast(int(floor(_attackPos.x)), -1, numSegments);
  int strip = ClampFast(int(floor(_attackPos.y)), -1, numStrips);

  CVec2 bilCoeff(_attackPos.x - segment, _attackPos.y - strip);
  strip = ClampFast(strip, 0, numStrips-1);

  CVec3 a(*GetNode(strip, segment+1), z);
  CVec3 b(*GetNode(strip, segment+2), z);
  CVec3 c(*GetNode(strip+1, segment+1), z);
  CVec3 d(*GetNode(strip+1, segment+2), z);

  Render::DebugRenderer::DrawLine3D(a, b, color, color, false);
  Render::DebugRenderer::DrawLine3D(c, d, color, color, false);
  Render::DebugRenderer::DrawLine3D(a, c, color, color, false);
  Render::DebugRenderer::DrawLine3D(b, d, color, color, false);

  Render::DebugRenderer::DrawLine3D( Lerp(a, b, bilCoeff.x), Lerp(c, d, bilCoeff.x), crossColor, crossColor, false);
  Render::DebugRenderer::DrawLine3D( Lerp(a, c, bilCoeff.y), Lerp(b, d, bilCoeff.y), crossColor, crossColor, false);
#endif  
}

} // namespace Terrain

// end of NatureAttackSpace.cpp
