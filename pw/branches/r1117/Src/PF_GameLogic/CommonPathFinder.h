#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../System/2DArray.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CLine;

namespace NWorld
{
	_interface IPointChecking;
	class TileMap;
}

namespace Pathfinding
{

int CalculatePathLen(const vector<SVector> & path, int start, int len, float wieght = 1.0f);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCommonPathFinder: public CObjectBase
{

  OBJECT_METHODS(0x8B786C40, CCommonPathFinder);

	CPtr<NWorld::TileMap> tileMap;

	CPtr<NWorld::IPointChecking> pChecking;
	int              nBoundTileRadius;
  int              nBoundTileRadiusDyn;

	int              upperLimit;
	bool             longPath;
	SVector          startPoint, finishPoint, originalFinishPoint;
	SVector          lastKnownGoodTile;

	int              nLength, nStart;

	int              minDistance, minPointNum;
	// нашли точку
	bool             bFinished;
	int              nCyclePoints;

	vector<SVector>  stopPoints, addPoints;
	int              mapBufIndex;
	CArray2D<BYTE>   mapBuf;
	vector<int>      cyclePoints, segmBegin;
	bool             bPathFound;

	int              nBestDist;
	SVector          vBestPoint;
  SVector leftCyclePoint, rightCyclePoint;
private:

	void LineSmoothing( const int STEP_LENGTH_THERE, const int MAX_NUM_OF_ATTEMPTS_THERE,
		const int STEP_LENGTH_BACK, const int MAX_NUM_OF_ATTEMPTS_BACK );

  void CheckCyclesInPath(int const starttPosition);
	const SVector CalculateHandPath( const SVector &blockPoint, const SVector &dir, const SVector &finish );
	const SVector CalculateSimplePath( const SVector &blockPoint, const SVector &dir, const SVector &finish, int numSteps );
	bool CanGoTowardPoint( const SVector &start, const SVector &finish, int numSteps );

	const int SavePathThere( const SVector &start, const SVector &finish, const int nLen );
	const int SavePathBack( const SVector& start, const SVector& finish, const int nLen );

  void ResetCycleCheck() {leftCyclePoint = rightCyclePoint = SVector(-1, -1);}
  bool SuspectCycle(const SVector & left, const SVector & right);
  bool CheckCycle(const SVector & left, const SVector & right);
	
	void EraseCycles();
	void AnalyzePoint( const SVector &point, const int num );
	// если юнит сейчас на непроходимом тайле, то можно длина пути от pointFrom то lastKnownGoodTile, а потом искать путь
	const int GetAdditionalPathLength( const SVector &pointFrom );

	bool CalculatePath( int numSteps );
	void AdditionalSmooth();
	void FindBetterPoint();

	const SVector GetStopTile( int n ) const { NI_ASSERT( n >= 0 && n < nLength, "Wrong number of stop point" ); return addPoints[n]; }

	void CheckBestPoint( const SVector &point );

	const bool CanUnitGoByDir( const SVector &tile, const SVector &dir );
	const bool CanUnitGo( const SVector &tile );
	void NextMapBufIndex();

  void SetPathParameters(const int nBoundTileRadius, const int nBoundTileRadiusDyn, const SVector &vStartPoint, const SVector &vFinishPoint,
    const SVector &lastKnownGoodTile);

  bool DoesPathExist( int numSteps );
  // Specially to not recalculate path twice. Calculate path after call DoesPathExist
  bool CreatePathAfterExistCheck();

  bool MoveAroundByDirection(vector<SVector> & points, const CLine & blockLine, const CLine & perpLine, const CLine & perpLine1, const int startLen, 
    const SVector &blockPoint, const SVector &finish,  SVector & curPoint, SVector & curDir, bool right);

  bool MoveAround( vector<SVector> & points, const int startLen, const SVector & finish, SVector & curPoint, SVector & curDir, bool right, int numSteps );
  int TurnPoint( const SVector & blockPoint, SVector & turnPoint, bool turnRight );
  int TurnRight( const SVector & blockPoint, SVector & turnPoint);
  int TurnLeft( const SVector & blockPoint, SVector & turnPoint);
  CCommonPathFinder() {}
public:
  CCommonPathFinder( NWorld::TileMap * _tileMap );
	void Init();

	// main setup function, called before CreatePath()
	
	// additional setup functions, should be called after SetPathParameters()
	void SetChecking(NWorld::IPointChecking *_pChecking) { pChecking       = _pChecking; }
	void SetMaxLength(int maxLen);

  bool CreatePath(const int _nBoundTileRadius, const int _nBoundTileRadiusDyn, const SVector &_vStartPoint, const SVector &_vFinishPoint,
    const SVector &_lastKnownGoodTile, NWorld::IPointChecking *_pChecking, const int referenceLength, int numSteps );

	const SVector& GetStartTile() const {  return startPoint; }
	const SVector& GetFinishTile() const { return finishPoint; }

	const int GetPathLength()	const { return nLength; }

  const vector<SVector> & GetCurrentPath() const {return addPoints;}

  void GetTiles( void *pBuf, const int nLen ) const
	{
		NI_ASSERT( nLength > 0 && nLen > 0 && nLen <= nLength, "Wrong number of stop points" );
		memcpy( pBuf, &(addPoints[0]), nLen * sizeof(SVector) );
	}

	int SmoothPath(SVector *pathTiles, int nLength, int firstTile = 0, int nWrap = 0x800000);

	bool Walkable( const SVector &start, const SVector &finish );
	bool Walkable( const SVector &start, const SVector &finish, const int _nBoundTileRadius, const int _nBoundTileRadiusDyn );

	const bool IsPathFound() const { return bPathFound; }

  NWorld::TileMap* GetTileMap() const { return tileMap; }
};
}