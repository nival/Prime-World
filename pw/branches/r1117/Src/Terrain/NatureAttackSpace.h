#pragma once
#ifndef _NATUREATTACKSPACE_H_
#define _NATUREATTACKSPACE_H_

#include "../System/BilinearSolver.h"

namespace Terrain {

struct NatureMapParams;

class NatureAttackSpace
{
public:
  NatureAttackSpace();
  ~NatureAttackSpace();

  bool Create(const NDb::DBNatureMap& dbNatureMap, CVec3& worldSize);
  bool Load(const NDb::DBNatureMap& dbNatureMap, Stream* pStream);
  bool Save(Stream* pStream) const;

  int GetNumStrips() const { return numStrips; }
  int GetNumSegments() const { return numSegments; }
  CVec2 FindCoordinatesAS(CVec2 const& posWS) const; // WorldSpace -> AttackSpace
  CVec2 FindCoordinatesWS(CVec2 const& posAS) const; // AttackSpace -> WorldSpace

  void RenderDebug();
  void RenderDebugTile(CVec2 const& _attackPos, Render::Color crossColor);

private:
  void InitFields(const NDb::DBNatureMap& dbNatureMap);
  int  TessellateBase(CVec2 const& base, float xLimit, CVec2* pStart);
  int  TessellateByX(vector<CVec2> const& nodes, int idx, float x, float halfwidth, CVec2* pUpper, CVec2* pLower);
  bool TessellateByX(NDb::DBNatureMapRoad const* pRoad, CVec2* pUpperLine, CVec2* pLowerLine);
  int  TessellateByAngle(vector<CVec2> const& nodes, int idx, float phi, float halfwidth, CVec2* pOuter, CVec2* pInner);
  bool TessellateByAngle(NDb::DBNatureMapRoad const* pRoad, CVec2* pOuterLine, CVec2* pInnerLine);
  int FindSegment(CVec2 const& pos) const;
  int FindStrip(CVec2 const& pos, int seg) const;
  
  CVec2* GetNode(int row, int col) { return &pNodes[row * nodesPitch + col]; }
  CVec2 const* GetNode(int row, int col) const { return &pNodes[row * nodesPitch + col]; }
 
  BilinearSolver2D* GetQuad(int row, int col) { return &pSolvers[row * quadsPitch + col]; }
  BilinearSolver2D const* GetQuad(int row, int col) const { return &pSolvers[row * quadsPitch + col]; }

  CVec2 center;
  static const int numRoads = 3;
  int numStrips;
  int numSegments;
  int nodesCount;
  int nodesPitch;
  int quadsCount;
  int quadsPitch;
  ScopedArray<CVec2> pNodes; // [(numStrips+1) * (numSegments+1)]
  ScopedArray<BilinearSolver2D> pSolvers; // [numStrips * numSegments]
};

} // namespace Terrain

#endif /* _NATUREATTACKSPACE_H_ */
