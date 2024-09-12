#include "stdafx.h"

#include "CommonPathFinder.h"
#include "ImportedStruct.h"
#include "PointChecking.h"
#include "TileMap.h"
#include "../System/Bresenham.h"
#include "../System/InlineProfiler.h"
#include "../System/LogFileName.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int LONG_PATH_LENGTH = 5000;
static const int STEP_LENGTH_THERE = 30;
static const int MAX_NUM_OF_ATTEMPTS_THERE = 4;
static const int STEP_LENGTH_BACK = 10;
static const int MAX_NUM_OF_ATTEMPTS_BACK = 12;
static const int STEP_LENGTH_THERE_SHORT = 5;
static const int MAX_NUM_OF_ATTEMPTS_THERE_SHORT = 4;
static const int STEP_LENGTH_BACK_SHORT = 2;
static const int MAX_NUM_OF_ATTEMPTS_BACK_SHORT = 12;
static const int TOLERANCE = 64;
static const int TOLERANCE_SHORT = 16;
static const int MAX_MAPBUFINDEX = 254;

static const int DIST_SCALE = 10;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static float fWarFogBoundWidth = 256.0f;
static float g_pathUpperLimitFactor = 5.0f;
REGISTER_DEV_VAR("path_upper_limit_factor", g_pathUpperLimitFactor, STORAGE_NONE);

namespace
{
  //path len calculation
  const int TILE_LEN = 10;
  const int TILE_DIAG_LEN = 14;
  const int TILE_DIAG_LEN2 = 22;  // TILE_DIAG_LEN2 is for right calculation, when we get hole in the 
                                  // path and bigger distance between two tiles
  const int LENGHS[] = {0,TILE_LEN, TILE_DIAG_LEN, TILE_DIAG_LEN2};
  static const SVector NOWAY_POINT = SVector(-1, -1);
}

namespace Pathfinding
{

int CalculatePathLen( const vector<SVector> & path, int start, int len, float wieght)
{
  if ( len == 0 )
    return 0;

  NI_VERIFY( len+start <= path.size(), "out of bounds", len = path.size() - start - 1 );

  if (len == 1)
    return TILE_LEN*wieght;

  int totalLen = 0;
  SVector prevPoint = path[start];

  for (int i=start+1; i<start+len; i++)
  {
    SVector delta = path[i] - prevPoint;
    int absDelta= abs(delta.x) + abs(delta.y);
    // absDelta may be up to 3, due to holes, which are buggy-possible
    // in the current version of pathfinder. Normally it should be up to 2.
    NI_ASSERT(absDelta>=1 && absDelta <= 3, "not neighbor tiles");
    totalLen+=LENGHS[absDelta];
    prevPoint = path[i];
  }

  return totalLen*wieght;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommonPathFinder::Init()
{
	bPathFound = false;
	nBoundTileRadius = -1;
  nBoundTileRadiusDyn = -1;
	upperLimit = -1;
	longPath = false;
	lastKnownGoodTile = SVector(-1,-1);
	finishPoint = originalFinishPoint = SVector(-1,-1);
	startPoint  = SVector(-1,-1);
  nLength = nStart = -1;

	minDistance = minPointNum = 1;
	bFinished = false;
	nCyclePoints = 0;

	//mapBufIndex = -1;
	bPathFound = false;
	nBestDist = -1;
	vBestPoint = SVector(-1,-1);

	mapBufIndex = 1;

	cyclePoints.resize( 2*LONG_PATH_LENGTH + 1, 0 );

	stopPoints.resize( LONG_PATH_LENGTH + 1 );
	addPoints.resize( LONG_PATH_LENGTH + 1 );
	segmBegin.resize( LONG_PATH_LENGTH + 1 );
	mapBuf.Clear();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCommonPathFinder::CCommonPathFinder( NWorld::TileMap * _tileMap ) : tileMap(_tileMap)
{
	Init();

  const int nMaxSize = Max( tileMap->GetSizeX(), tileMap->GetSizeY() );
  if ( nMaxSize > mapBuf.GetSizeX() )
  {
    mapBuf.SetSizes( nMaxSize, nMaxSize );
    mapBuf.FillZero();
    mapBufIndex = 1;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommonPathFinder::SetPathParameters( const int _nBoundTileRadius, const int _nBoundTileRadiusDyn, const SVector &_vStartPoint, const SVector &_vFinishPoint,
	const SVector &_lastKnownGoodTile)
{
	
	bFinished    = false;

	startPoint   = _vStartPoint;
	startPoint.x = Clamp( startPoint.x, 0, tileMap->GetSizeX() - 1 );
	startPoint.y = Clamp( startPoint.y, 0, tileMap->GetSizeY() - 1 );

  finishPoint = _vFinishPoint;
  finishPoint.x = Clamp( finishPoint.x, 0, tileMap->GetSizeX() - 1 );
  finishPoint.y = Clamp( finishPoint.y, 0, tileMap->GetSizeY() - 1 );

	originalFinishPoint = finishPoint;

	upperLimit   = LONG_PATH_LENGTH;

	longPath = ( upperLimit == LONG_PATH_LENGTH );
	lastKnownGoodTile = _lastKnownGoodTile;
	nBoundTileRadius  = _nBoundTileRadius;
  nBoundTileRadiusDyn = _nBoundTileRadiusDyn;
	bPathFound        = false;
	pChecking         = NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void CCommonPathFinder::SetMaxLength(int maxLen)
{
  upperLimit  = maxLen;
  longPath    = ( maxLen == LONG_PATH_LENGTH );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const bool CCommonPathFinder::CanUnitGoByDir( const SVector &tile, const SVector &dir )
{
  //return CanUnitGo(tile + dir);
	bool result = tileMap->CanUnitGoByDir( nBoundTileRadius, nBoundTileRadiusDyn, tile, dir );
	return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const bool CCommonPathFinder::CanUnitGo( const SVector &tile )
{
	bool result = tileMap->CanUnitGo( nBoundTileRadius, nBoundTileRadiusDyn, tile );
	return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int Distance(const SVector &p1, const SVector &p2)
{
	int dx = abs(p1.x - p2.x);
	int dy = abs(p1.y - p2.y);
	// 0.41 = sqrt(2) - 1.0f
	if (dx > dy)
		return dx * DIST_SCALE + dy * int(0.41 * DIST_SCALE);
	else
		return dy * DIST_SCALE + dx * int(0.41 * DIST_SCALE);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommonPathFinder::CheckBestPoint( const SVector &point )
{
  //NI_PROFILE_HEAVY_FUNCTION;

	const int nDist = Distance( point, finishPoint );
	if ( (nDist < nBestDist) )
	{
		vBestPoint = point;
		nBestDist  = nDist;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommonPathFinder::AnalyzePoint( const SVector &point, const int num )
{
  //NI_PROFILE_HEAVY_FUNCTION;

	const int mDist = Distance( point, finishPoint );
	if ( mDist < minDistance )
	{
		CheckBestPoint( point );
		minDistance = mDist;
		minPointNum = num;
		if ( !bFinished && pChecking && pChecking->IsGoodTile( point ) )
			bFinished = true;
	}
}

//////////////////////////////////////////////////////////////////////////
int CCommonPathFinder::TurnPoint( const SVector & blockPoint, SVector & turnPoint, bool turnRight )
{
  //NI_PROFILE_HEAVY_FUNCTION;

  int turnCount = 0;
  do
  {
    turnRight? turnPoint.TurnRightUntil45(): turnPoint.TurnLeftUntil45();
    ++turnCount;
  } while ( turnCount < 8 && !CanUnitGoByDir( blockPoint, turnPoint ) );

  return turnCount < 8 ? turnCount : 0;
}

int CCommonPathFinder::TurnRight( const SVector & blockPoint, SVector & turnPoint )
{
  return TurnPoint(blockPoint, turnPoint, true);
}

int CCommonPathFinder::TurnLeft( const SVector & blockPoint, SVector & turnPoint )
{
  return TurnPoint(blockPoint, turnPoint, false);
}

//////////////////////////////////////////////////////////////////////////
bool CCommonPathFinder::SuspectCycle( const SVector & left, const SVector & right )
{
  if (left == right)
    return true;

  leftCyclePoint = left;
  rightCyclePoint = right;

  return false;
}

bool CCommonPathFinder::CheckCycle( const SVector & left, const SVector & right )
{
  return (leftCyclePoint == right && rightCyclePoint == left);
}

//////////////////////////////////////////////////////////////////////////
void CCommonPathFinder::CheckCyclesInPath( int const starttPosition )
{
  for ( int i = starttPosition; i < nLength; ++i )
  {
    SVector &stop = stopPoints[i];

    // проверка на цикл
    if ( mapBuf[stop.x][stop.y] == mapBufIndex )
      cyclePoints[nCyclePoints++] = i;
    else
      mapBuf[stop.x][stop.y] = mapBufIndex;

    AnalyzePoint( stop, i );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SVector CCommonPathFinder::CalculateHandPath( const SVector &blockPoint, const SVector &dir, const SVector &finish)
{
  NI_PROFILE_FUNCTION
  
	CheckBestPoint( blockPoint );

	const CLine blockLine( blockPoint, finish );
	const CLine perpLine( blockLine.GetPerpendicular( blockPoint ) );
	const CLine perpLine1( blockLine.GetPerpendicular( finish) );
	const int startLen = nLength;

	SVector dirLeft = dir, dirRight = dir;
	SVector curRightPoint = blockPoint, curLeftPoint = blockPoint;

  // крутимся влево и вправо, пока не сможем шагнуть вперёд

  if (!TurnLeft(blockPoint, dirRight) || !TurnRight(blockPoint, dirLeft))
    return NOWAY_POINT;

	stopPoints[nLength] = curRightPoint;
	curRightPoint += dirRight;

	addPoints[nLength++] = curLeftPoint;
  curLeftPoint += dirLeft;

  ResetCycleCheck();
  bool cycleSuspected = false;
  
  bool foundAroudPath = false;
  SVector finalPoint = startPoint;

	while ( nCyclePoints < LONG_PATH_LENGTH && nLength < upperLimit )
	{
    cycleSuspected = SuspectCycle(curLeftPoint, curRightPoint);

    foundAroudPath = MoveAroundByDirection(stopPoints, blockLine, perpLine, perpLine1, startLen, blockPoint, finish, curRightPoint, dirRight, true);
    
    if (foundAroudPath)
    {
      finalPoint = curRightPoint;
      break;
    }

    foundAroudPath = MoveAroundByDirection(addPoints, blockLine, perpLine, perpLine1, startLen, blockPoint, finish, curLeftPoint, dirLeft, false);

    if (foundAroudPath)
    {
      memcpy( &(stopPoints[0]) + startLen, &(addPoints[0]) + startLen, sizeof(SVector) * ( nLength - startLen ) );
      finalPoint = curLeftPoint;
      break;
    }
   
    if (cycleSuspected && CheckCycle(curLeftPoint, curRightPoint))
    {
      nLength = startLen;
      return NOWAY_POINT;
    }

		++nLength;
	}

  if (foundAroudPath)
  {
    CheckCyclesInPath(startLen);
    return finalPoint;
  }

  nLength = startLen;
	return NOWAY_POINT;			// путь переполнен
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SVector CCommonPathFinder::CalculateSimplePath( const SVector &blockPoint, const SVector &dir, const SVector &finish, int numSteps )
{
  NI_PROFILE_FUNCTION

  CheckBestPoint( blockPoint );
  const int startLen = nLength;

  SVector dirLeft = dir, dirRight = dir;
  SVector curRightPoint = blockPoint, curLeftPoint = blockPoint;

  if (!TurnLeft(blockPoint, dirRight) || !TurnRight(blockPoint, dirLeft))
    return NOWAY_POINT;

  stopPoints[nLength] = curRightPoint;
  curRightPoint += dirRight;

  addPoints[nLength++] = curLeftPoint;
  curLeftPoint += dirLeft;

  ResetCycleCheck();
  bool cycleSuspected = false;

  bool foundAroudPath = false;
  SVector finalPoint = startPoint;

  while ( nLength < upperLimit )
  {
    cycleSuspected = SuspectCycle(curLeftPoint, curRightPoint);

    foundAroudPath = MoveAround( stopPoints, startLen, finish, curRightPoint, dirRight, true, numSteps );

    if (foundAroudPath)
    {
      finalPoint = curRightPoint;
      break;
    }

    foundAroudPath = MoveAround( addPoints, startLen, finish, curLeftPoint, dirLeft, false, numSteps );

    if (foundAroudPath)
    {
      memcpy( &(stopPoints[0]) + startLen, &(addPoints[0]) + startLen, sizeof(SVector) * ( nLength - startLen ) );
      finalPoint = curLeftPoint;
      break;
    }

    if (cycleSuspected && CheckCycle(curLeftPoint, curRightPoint))
    {
      nLength = startLen;
      return NOWAY_POINT;
    }

    ++nLength;
  }

  if (foundAroudPath)
  {
    CheckCyclesInPath(startLen);
    return finalPoint;
  }

  nLength = startLen;
  return NOWAY_POINT;
}



bool CCommonPathFinder::MoveAroundByDirection(vector<SVector> & points, const CLine & blockLine, const CLine & perpLine, const CLine & perpLine1, const int startLen, 
                                    const SVector &blockPoint, const SVector &finish,  SVector & curPoint, SVector & curDir, bool right)
{
  //This function may be called more than 11000 times. This is too heavy.
  //NI_PROFILE_HEAVY_FUNCTION...

  curDir.x = -curDir.x;
  curDir.y = -curDir.y;

  right? TurnLeft(curPoint, curDir) :  TurnRight(curPoint, curDir);

  points[nLength] = curPoint;
  CheckBestPoint( curPoint );
  SVector nextPoint = curPoint + curDir;

  if ( IsValid(pChecking) && pChecking->IsGoodTile( curPoint ) )
  {
    curPoint = nextPoint;
    return true;
  }

  if ( blockLine.IsSegmIntersectLine( curPoint, nextPoint ) )
  {
    bool betweenBlockFinish;

    bool beforeFinish = perpLine.GetHPLineSign( nextPoint ) * perpLine.GetHPLineSign( finish ) >= 0;
    bool fartherBlock = perpLine1.GetHPLineSign( nextPoint ) * perpLine1.GetHPLineSign( blockPoint ) >= 0;
    betweenBlockFinish = fartherBlock && beforeFinish;

    bool wasStandThere = mapBuf[nextPoint.x][nextPoint.y] == mapBufIndex;

    if ( betweenBlockFinish && nextPoint != blockPoint && (nLength - startLen > 1) && !wasStandThere )
    {
      ++nLength;
    
      curPoint = nextPoint;
      return true;
    }
  }
  curPoint = nextPoint;
  return false;
}

bool CCommonPathFinder::MoveAround( vector<SVector> & points, const int startLen, const SVector & finish, SVector & curPoint, SVector & curDir, bool right, int numSteps )
{
  NI_PROFILE_HEAVY_FUNCTION;

  right? curDir.TurnRightUntil135(): curDir.TurnLeftUntil135();

  int turnCount = right? TurnLeft(curPoint, curDir) : TurnRight(curPoint, curDir );

  //TODO wtf?!
  if ( turnCount<= 4  )
  {
    if ( curDir * (finish-curPoint)>= 0 && CanGoTowardPoint( curPoint, finish, numSteps ) )
      return true;
  }

  if ( IsValid(pChecking) && pChecking->IsGoodTile( curPoint ) )
  {
    return true;
  }

  points[nLength] = curPoint;
  CheckBestPoint( curPoint );
  curPoint += curDir;

  return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CCommonPathFinder::CanGoTowardPoint( const SVector &start, const SVector &finish, int numSteps )
{
  if ( Distance( start, finish ) <= nBoundTileRadius * DIST_SCALE )
    return true;
  CBres bres;
  bres.Init( start, finish );
  bres.MakeStep();

  if ( CanUnitGoByDir( start, bres.GetDirection() ) )
  {
    SVector nextPoint( start + bres.GetDirection() );

    for ( int i = 0; i < numSteps; i++ )
    {
      bres.MakeStep();
      if ( !CanUnitGoByDir( nextPoint, bres.GetDirection() ) )
      {
        return false;
      }
      nextPoint = nextPoint+bres.GetDirection();
    }
    return true;
  }
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CCommonPathFinder::CalculatePath( int numSteps )
{
  NI_PROFILE_FUNCTION
  
  nBestDist = 0x7FFFFFFF;				// просто большое число
	vBestPoint = SVector( -1, -1 );

	nLength = 0;
	nCyclePoints = 1;
	minDistance = Distance( startPoint, finishPoint ) + 1;
	minPointNum = 0;
	bFinished = false;

	// проверим первую точку - может дальше идти и не надо (благодаря pChecking); меняет bFinished
	AnalyzePoint( startPoint, 0 );
	if ( bFinished )
		return true;

	NI_ASSERT( finishPoint.x >= 0 && finishPoint.y >= 0, "Wrong finish point" );

	if ( finishPoint.x < 0 || finishPoint.y < 0 )
	{
		finishPoint = startPoint;
		return false;
	}

	if ( startPoint == finishPoint || bFinished )
	{
		nLength = 1;
		stopPoints[0] = startPoint;
		return true;
	}

	SVector startSearchPoint;
	if ( CanUnitGo( startPoint ) )
		startSearchPoint = startPoint;
	else
	{
		startSearchPoint = lastKnownGoodTile;
		if ( !CanUnitGo( startPoint ) )
		{
			bool canGo = false;
			for ( int i = -1; i <= 1 && !canGo; ++i )
			{
				for ( int j = -1; j <= 1  && !canGo; ++j )
				{
					if ( i != 0 || j != 0 )
					{
						canGo = CanUnitGo( startPoint + SVector( i, j ) );
						if ( canGo )
							startSearchPoint += SVector( i, j );
					}
				}
			}

			if ( !canGo )
			{
				finishPoint = startPoint;
				return false;
			}
		}
	}

	SVector curPoint(startSearchPoint);

	// строим путь по брезенхейму
	CBres bres;
	bres.Init( startSearchPoint, finishPoint );

	while ( curPoint != finishPoint && upperLimit >= 0 )
	{
		// идём по прямой
		bres.MakeStep();

		if ( !CanUnitGoByDir( curPoint, bres.GetDirection() ) )
		{
			// клетка занята
			if ( curPoint + bres.GetDirection() == finishPoint )
			{
				CheckBestPoint( curPoint );
				finishPoint = curPoint;
				return true;
			}

			if ( mapBuf[curPoint.x][curPoint.y] != mapBufIndex )
			{
				// точка ещё не проверялась на данном вызове CreatePath()

        SVector point;
        
        point = CalculateSimplePath( curPoint, bres.GetDirection(), finishPoint, numSteps );

				if ( point.x == -1 )
				{
          point = CalculateHandPath( curPoint, bres.GetDirection(), finishPoint);
					
					if ( point.x == -1  || Distance( point, curPoint ) >= 1 * DIST_SCALE )
						curPoint = point;
					else
					{
						CheckBestPoint( curPoint );
						finishPoint = curPoint;
						return true;
					}
				}
				else
					curPoint = point;
			}
			else
			{
#ifndef _SHIPPING
				NI_VERIFY( nCyclePoints < cyclePoints.size(), "Index out of range", cyclePoints.resize( cyclePoints.size() * 2 ) );
#endif
				cyclePoints[nCyclePoints++] = nLength;

        SVector point;
        point = CalculateHandPath( curPoint, bres.GetDirection(), finishPoint );

				if ( point.x == -1 || (Distance( point, curPoint ) >= 1 * DIST_SCALE) )
					curPoint = point;
				else
				{
					CheckBestPoint( curPoint );
					finishPoint = curPoint;
					return true;
				}
			}
		
			if ( curPoint.x != -1 )
				bres.Init( curPoint, finishPoint );
		}
		else
		{
			// клетка свободна
			mapBuf[curPoint.x][curPoint.y] = mapBufIndex;
			AnalyzePoint( curPoint, nLength );
			stopPoints[nLength++] = curPoint;
			curPoint += bres.GetDirection();
		}

		// дошли до точки, откуда можно производить нужные действия
		if ( bFinished )
		{
			finishPoint = curPoint;
			return true;
		}
		// путь не найден
		if ( curPoint.x == -1 )
		{
			finishPoint = stopPoints[nLength];
			return false;
		}
		if ( nLength >= upperLimit )
		{
			finishPoint = stopPoints[upperLimit];
			return false;
		}
	}

	CheckBestPoint( curPoint );
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommonPathFinder::EraseCycles()
{
	nStart = 0;

	int i = nLength - 1;
	int cycleNum = nCyclePoints - 1;

	// ищем конец ближайшего цикла
	while ( cycleNum > 0 && cyclePoints[cycleNum] > i - nStart )
		--cycleNum;

	while ( i - nStart >= 0  && cycleNum > 0 )
	{
		// сдвигаемся до конца цикла
		while ( i - nStart >= cyclePoints[cycleNum] )
		{
			stopPoints[i] = stopPoints[i - nStart];
			// очистка буфера карты
			// mapBuf[stopPoints[i - nStart].x][stopPoints[i - nStart].y] = 0;
			--i;
		}

		// пропуск цикла
		while ( i - nStart >= 0 && stopPoints[i + 1] != stopPoints[i - nStart] )
		{
			// очистка буфера карты
			// mapBuf[stopPoints[i - nStart].x][stopPoints[i - nStart].y] = 0;
			++nStart;
		}
		++nStart;

		// ищем конец ближайшего цикла
		while ( cycleNum > 0 && cyclePoints[cycleNum] > i - nStart )
			--cycleNum;
	}
	//	--nStart;
	nLength -= nStart;

	while ( i - nStart  >= 0 )
	{
		stopPoints[i] = stopPoints[i - nStart];
		// mapBuf[stopPoints[i - nStart].x][stopPoints[i - nStart].y] = 0;
		--i;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CCommonPathFinder::Walkable( const SVector &start, const SVector &finish )
{
	CBres bres;
	bres.InitPoint( start, finish );
	SVector curPoint = start;

	while (curPoint != finish)
	{
		bres.MakeStep();
		SVector dir = bres.GetDirection();
		if (!CanUnitGoByDir(curPoint, dir))
			return false;
		curPoint += dir;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CCommonPathFinder::Walkable( const SVector &start, const SVector &finish, 
                                  const int _nBoundTileRadius, const int _nBoundTileRadiusDyn )
{
	int nLastBoundTileRadius    = nBoundTileRadius;
	int nLastBoundTileRadiusDyn = nBoundTileRadiusDyn;

	nLastBoundTileRadius    = _nBoundTileRadius;
	nLastBoundTileRadiusDyn = _nBoundTileRadiusDyn;

	bool isWalkable = Walkable(start, finish);

	nBoundTileRadius    = nLastBoundTileRadius;
	nBoundTileRadiusDyn = nLastBoundTileRadiusDyn;

	return isWalkable;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int CCommonPathFinder::SavePathThere( const SVector &start, const SVector &finish, const int nLen )
{
	CBres bres;
	bres.InitPoint( start, finish );

	int res = 0;
	do
	{
		addPoints[nLen+res++] = bres.GetDirection();
		bres.MakePointStep();
	} while ( bres.GetDirection() != finish );

	return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int CCommonPathFinder::SavePathBack( const SVector &start, const SVector &finish, const int nLen )
{
	CBres bres;
	bres.InitPoint( start, finish );

	int res = 0;
	do
	{
		bres.MakePointStep();
		stopPoints[nLen+res++] = bres.GetDirection();
	} while ( bres.GetDirection() != finish );

	return res;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// "Срезание" углов по возможности
void CCommonPathFinder::LineSmoothing( const int STEP_LENGTH_THERE, const int MAX_NUM_OF_ATTEMPTS_THERE,
																			const int STEP_LENGTH_BACK, const int MAX_NUM_OF_ATTEMPTS_BACK )
{

  NI_PROFILE_FUNCTION
	if ( nLength < 2 )
  {
    for( int i = 0; i < nLength; ++i )
      addPoints[i] = stopPoints[i];
		return;
  }

	if (nStart < 0) nStart = 0;
	stopPoints[nStart+nLength++] = finishPoint;

	//for (int ii = 0; ii < nLength; ii++)
	//	addPoints[ii] = stopPoints[nStart + ii];

  // вперёд
	int curNum = 1, i = 1;
	int checkNum = 0, numOfAttempts = 0, addLen = 0;

	while ( i < nLength-1 )
	{
		const int j = Min( i+STEP_LENGTH_THERE, nLength )-1;

		if ( numOfAttempts > MAX_NUM_OF_ATTEMPTS_THERE  ||
			!Walkable( stopPoints[checkNum + nStart], stopPoints[j + nStart] ) )
		{
			addLen += SavePathThere( stopPoints[checkNum + nStart], stopPoints[i + nStart], addLen );

			checkNum = i;
			curNum = ++i;
			numOfAttempts = 0;
		}
		else
		{
			i = j;
			++numOfAttempts;
		}
	}

	addLen += SavePathThere( stopPoints[checkNum + nStart], stopPoints[nStart + nLength - 1], addLen );
	addPoints[addLen] = finishPoint;
	nLength = addLen+1;

	// назад
	i = nLength-2;
	checkNum = nLength-1;
	curNum = nLength-2;
	numOfAttempts = addLen = 0;
	int nSegm = 0;
	while ( i > 0 )
	{
		const int j = Max( i-STEP_LENGTH_BACK, 0 );

		if ( numOfAttempts > MAX_NUM_OF_ATTEMPTS_BACK || !Walkable( addPoints[j], addPoints[checkNum] ) )
		{
			segmBegin[nSegm++] = addLen;
			addLen += SavePathBack( addPoints[i], addPoints[checkNum], addLen );

			checkNum = i;
			curNum = --i;
			numOfAttempts = 0;
		}
		else
		{
			i = j;
			++numOfAttempts;
		}
	}

	// по сегментам
	segmBegin[nSegm++] = addLen;
	addLen += SavePathBack( addPoints[0], addPoints[checkNum], addLen );
	segmBegin[nSegm] = addLen;

	if ( nSegm == 1 )
	{
		addPoints[0] = startPoint;
		memcpy( &(addPoints[0]) + 1, &(stopPoints[0]), nLength * sizeof( SVector ) );
		addPoints[addLen] = finishPoint;
		nLength = addLen + 1;
	}
	else
	{

		// go through control points
		addPoints[0] = startPoint;
		nLength = addLen = 1;
		i = nSegm-1;
		//	int up, down, mid;

		while ( i >= 0 )
		{
			//  simple bisections
			if ( longPath )
			{
				int j = Min( i - 1, (int)TOLERANCE )+1;
				while ( j > 0  &&  !Walkable( stopPoints[segmBegin[i]], stopPoints[segmBegin[i-j+1]-1] ) )
					j >>= 1;

				if ( !j )
				{
					memcpy( &(addPoints[0]) + addLen, &(stopPoints[0]) + segmBegin[i], sizeof(SVector)*(segmBegin[i-j+1]-segmBegin[i]) );
					addLen += segmBegin[i-j+1]-segmBegin[i];
				}
				else
				{
					addLen += SavePathThere( stopPoints[segmBegin[i]], stopPoints[segmBegin[i-j+1]-1], addLen );
					addPoints[addLen++] = stopPoints[segmBegin[i-j+1]-1];
				}

				i -= j+1;
			}
			else
				//	sequential search
			{
				int j = Max(1, i-TOLERANCE);
				while ( j <= i && !Walkable( stopPoints[segmBegin[i]], stopPoints[segmBegin[j]-1] ) )
					++j;

				addLen += SavePathThere( stopPoints[segmBegin[i]], stopPoints[segmBegin[j]-1], addLen );
				addPoints[addLen++] = stopPoints[segmBegin[j]-1];
				i = j-2;
			}
		}

		nLength = addLen;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CCommonPathFinder::DoesPathExist( int numSteps )
{
  NI_PROFILE_FUNCTION

  NextMapBufIndex();
	bPathFound = CalculatePath(numSteps);

  if ( !bFinished && vBestPoint.x != -1 && vBestPoint != originalFinishPoint )
	{
    NI_PROFILE_BLOCK("recalculate path(bestPoint)");
	  finishPoint = vBestPoint;
		NextMapBufIndex();
		bPathFound = CalculatePath(numSteps);
	}

	return bPathFound;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommonPathFinder::AdditionalSmooth()
{
	if (!nLength)
		return;
	nLength = SmoothPath(&addPoints[0], nLength);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Input:  pathTiles - array of tiles
//         firstTile - wrappable (see nWrap) index of first tile
//         nLength   - length of source path
//         nWrap     - size of ring buffer (use very large value for linear buffer)
// Output: length of the resulting path
// Note:   nBoundTileRadius and tileMap should be set
int CCommonPathFinder::SmoothPath(SVector *pathTiles, int nLength, int firstTile, int nWrap)
{
	if (!nLength)
		return nLength; // ignore null paths

#define INDEX(n)		( (n) % nWrap )

	int tries;
	for (tries = 0; tries < 5; tries++)
	{
		int iDst = firstTile;
		for (int i = firstTile; i < firstTile + nLength; i++)
		{
			if (iDst > firstTile && i < firstTile + nLength - 1)
			{
				// detect and erase loops (180-degree angles)
				if (pathTiles[INDEX(iDst-1)] == pathTiles[INDEX(i+1)])	// compare previous and next points
				{
					// next point will be same as previous
					iDst--;
					continue;
				}
			}
			if (iDst > firstTile && i < firstTile + nLength - 1)
			{
				SVector p1 = pathTiles[INDEX(iDst-1)];				// previous point
				SVector p3 = pathTiles[INDEX(i   +1)];				// next point
				// slice 90-degree angles if possible
				if (abs(p1.x - p3.x) == 1 && abs(p1.y - p3.y) == 1)
				{
					// possible diagonal movement, check it; similar to CanUnitGoByDir()
					SVector p2;
					p2.x = p1.x;
					p2.y = p3.y;
					if (tileMap->CanUnitGo(nBoundTileRadius, nBoundTileRadiusDyn, p2))
					{
						p2.x = p3.x;
						p2.y = p1.y;
						if (tileMap->CanUnitGo(nBoundTileRadius, nBoundTileRadiusDyn, p2))
							continue;						// skip current point
					}
				}
				// slice 145-degree angles
				if ((abs(p1.x - p3.x) == 1 && p1.y == p3.y) ||
					(abs(p1.y - p3.y) == 1 && p1.x == p3.x))
				{
					continue;								// skip current point
				}
				// slice -/\- path artifacts
				if ((abs(p1.x - p3.x) == 2 && p1.y == p3.y) ||
					(abs(p1.y - p3.y) == 2 && p1.x == p3.x))
				{
					// compute middle point
					SVector p2;
					p2.x = (p1.x + p3.x) / 2;
					p2.y = (p1.y + p3.y) / 2;
//					if (p2 != addPoints[i])					// middle point is not equals to compute point
					{
						pathTiles[INDEX(iDst++)] = p2;
						continue;
					}
				}
			}
			pathTiles[INDEX(iDst++)] = pathTiles[INDEX(i)];
		}
		if (iDst == firstTile + nLength)
			break;				// path was not shortened on current iteration
		nLength = iDst - firstTile;
	}
#undef INDEX
	return nLength;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommonPathFinder::FindBetterPoint()
{
	if (!nLength || finishPoint == originalFinishPoint)
		return;

	int bestDist  = 0x7FFFFFFF;	// large number
	int bestPoint = -1;
	for (int i = 0; i < nLength; i++)
	{
		const SVector &tile = addPoints[i];
		int dist = Distance(tile, originalFinishPoint);
		if (dist < bestDist)
		{
			bestDist  = dist;
			bestPoint = i;
		}
	}
	if (bestPoint != nLength - 1)
	{
		nLength = bestPoint + 1;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CCommonPathFinder::CreatePathAfterExistCheck()
{
  NI_PROFILE_FUNCTION

	EraseCycles();

	if ( nLength <= 0 )
		return false;
 
	if ( longPath )
		LineSmoothing( STEP_LENGTH_THERE, MAX_NUM_OF_ATTEMPTS_THERE, STEP_LENGTH_BACK, MAX_NUM_OF_ATTEMPTS_BACK );
	else
		LineSmoothing( STEP_LENGTH_THERE_SHORT, MAX_NUM_OF_ATTEMPTS_THERE_SHORT, STEP_LENGTH_BACK_SHORT, MAX_NUM_OF_ATTEMPTS_BACK_SHORT );
 
	FindBetterPoint();
#if !NO_SMOOTHING
	AdditionalSmooth();
#endif

  ///just to be 100% safe. its like safety after safe
  if ( nLength <= 0 )
    return false;

  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CCommonPathFinder::CreatePath( const int tileRadius, const int tileRadiusDyn, const SVector &start, const SVector &finish, const SVector &lastGoodTile, 
                                   NWorld::IPointChecking* checking, const int referenceLength, int numSteps )
{
  NI_PROFILE_FUNCTION

  int maxLength = LONG_PATH_LENGTH;

  if (g_pathUpperLimitFactor > 0.0f && referenceLength > 0)
  {
    // Set max length to be a multiplier of the referenceLength, so we will be able to build a roundabout way.
    // referenceLength is set to a static path length, when we calculate the next path portion, while going.
    // Obviously, the length should be something much shorter than LONG_PATH_LENGTH if our static path is only few tiles long.
    maxLength = Clamp<int>(referenceLength * g_pathUpperLimitFactor, 1, LONG_PATH_LENGTH);
  }

  SetPathParameters(tileRadius, tileRadiusDyn, start, finish, lastGoodTile);
  SetChecking( checking );
  SetMaxLength( maxLength );

  if ( !DoesPathExist( numSteps ) )
    return false;

  if ( nLength <= 0 )
    return false;

	return CreatePathAfterExistCheck();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommonPathFinder::NextMapBufIndex()
{
  NI_PROFILE_FUNCTION
	++mapBufIndex;
	if ( mapBufIndex >= MAX_MAPBUFINDEX )
	{
		mapBuf.FillZero();
		mapBufIndex = 1;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( Pathfinding::CCommonPathFinder );