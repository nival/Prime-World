#include "stdafx.h"

#include "TileMap.h"
#include "StandartPath2.h"
#include "StaticPathInternal.h"
#include "PointChecking.h"

#include "../System/Bresenham.h"
#include "../System/InlineProfiler.h"
#include "CommonpathFinder.h"

namespace
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// максимальное количество точек, на которое будет смотреться вперед (в функции PeekPoint)
static const int MAX_LOOK_FORWARD_POINTS = 20;
// максимальная длина короткого пути в тайлах
static const int MAX_PATH_TILES_COUNT = 64;
#define INDEX(n)  ((n) % MAX_PATH_TILES_COUNT)
// а вообще путь будет строиться именно на столько тайлов
static const int SMALL_PATH_TILES_COUNT = MAX_PATH_TILES_COUNT/4;
// стандартный сдвиг точек на статическом пути
static const int STATIC_PATH_SHIFT = 20;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int DIST_SCALE = 10;
// p.s. максимальное количество тайлов, которое можно записать - MAX_PATH_TILES_COUNT - ( 2 x MAX_LOOK_FORWARD_POINTS )
// рабочий буфер для CopyPath()
static vector<SVector> pathBuffer( MAX_PATH_TILES_COUNT );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INVALID_TILE SVector( -1, -1 )
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const bool IsValidTile( const SVector &vTile )
{
	return vTile.x >= 0;
}
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// возвращает true, если vPoint ближе к vEndPoint1, чем к vEndPoint2
inline const bool CompareDistance( const SVector &vEndPoint1, const SVector &vEndPoint2, const SVector &vPoint )
{
	return Distance( vEndPoint1, vPoint ) < Distance( vEndPoint2, vPoint );
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CStandartPath2::CStandartPath2()
  : pMap( 0 )
  , nBoundTileRadius( -1 )
  , nBoundTileRadiusDyn( -1 )
  , pStaticPath( 0 )
  , nCurStaticPathTile( -1 )
  , vStartPoint( VNULL2 )
  , vFinishPoint( VNULL2 )
  , nCurInsTile( 0 )
  , nCurPathTile( 0 )
  , nLastPathTile( -1 )
  , vFinishTile( 0, 0 )
  , remainingLength( 0 )
  , pointChecking( 0 )
{
	pathTiles.resize( MAX_PATH_TILES_COUNT, SVector( 0, 0 ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CStandartPath2::CStandartPath2(Pathfinding::CCommonPathFinder * _pathFinder, int objectTileSize, int objectDynTileSize, CCommonStaticPath *_pStaticPath, IPointChecking *pChecking, const CVec2 &_vStartPoint, const CVec2 &_vFinishPoint, TileMap *_pMap, int numSteps )
: PFWorldObjectBase( _pStaticPath->GetWorld(), 0 )
, pMap( _pMap )
, nBoundTileRadius( Max( (objectTileSize + 1) / 2, 1 ) )
, nBoundTileRadiusDyn( Max( (objectDynTileSize + 1) / 2, 1 ) )
,	nCurInsTile( 0 )
, vFinishTile( 0, 0 )
, pointChecking(pChecking)
, pathFinder(_pathFinder)
{
	pathTiles.resize( MAX_PATH_TILES_COUNT );
	InitByStaticPath( _pStaticPath, _vStartPoint, _vFinishPoint, numSteps );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStandartPath2::InitByStaticPath( CCommonStaticPath* _pStaticPath, const CVec2& _vStartPoint, const CVec2& _vFinishPoint, int numSteps )
{
	pStaticPath = _pStaticPath;
	vStartPoint = _vStartPoint;
	
  nCurPathTile = 0;
	nLastPathTile = 1;
	nCurStaticPathTile = 0;
	pathTiles[1] = pathTiles[0] = pMap->GetTile( vStartPoint );
	remainingLength = pStaticPath->GetLength();

  vFinishPoint = _vFinishPoint;
  vFinishTile  = pMap->GetTile( vFinishPoint );
	if ( pStaticPath == 0 || !CalculatePath( true, INVALID_TILE, 0, numSteps ) )
	  vFinishPoint = vStartPoint;
	else
  {
    if ( pStaticPath->GetFinishTile() != pMap->GetTile( _vFinishPoint ) )
      vFinishPoint = pMap->GetPointByTile( pStaticPath->GetFinishTile() );
    else
	    vFinishPoint = _vFinishPoint;
  }

  vFinishTile  = pMap->GetTile( vFinishPoint );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStandartPath2::SetFinishTile( const SVector &_vFinishTile )
{
	vFinishTile  = _vFinishTile;
	vFinishPoint = pMap->GetPointByTile( vFinishTile );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// вызывается только из CalculatePath()
void CStandartPath2::CopyPath( const int nLength )
{
	if ( nLength <= 0 )
		return;

	pathFinder->GetTiles( &(pathBuffer[0]), nLength );
	// проверка: последний тайл в текущем состоянии буфера может совпадать с первым сайлом
	// копируемого пути - тогда убираем этот последний тайл (чтобы исключить дублирующиеся тайлы)
	if ( (nLastPathTile > 0) && (pathBuffer[0] == pathTiles[nLastPathTile - 1]) )
		nLastPathTile = INDEX(nLastPathTile - 1);
	const int nCopyTiles = Min( nLength, MAX_PATH_TILES_COUNT - nLastPathTile );
	// кольцевой буфер
	memcpy( &(pathTiles[0]) + nLastPathTile, &(pathBuffer[0]), sizeof(SVector) * Min( nLength, MAX_PATH_TILES_COUNT - nLastPathTile ) );
	if ( nLength > nCopyTiles )
		memcpy( &(pathTiles[0]), &(pathBuffer[0]) + nCopyTiles, sizeof(SVector) * ( nLength - nCopyTiles ) );
	nLastPathTile = INDEX(nLastPathTile + nLength);
	Smooth();
	// чтоб можно было спрашивать
	pathTiles[nLastPathTile] = pathBuffer[nLength-1];
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStandartPath2::Smooth()
{
	int nLength = nLastPathTile - nCurPathTile;
	if (nLength < 0)
		nLength += MAX_PATH_TILES_COUNT;

	if (!nLength)
		return;

	nLength = pathFinder->SmoothPath(&pathTiles[0], nLength, nCurPathTile, pathTiles.size());
	nLastPathTile = INDEX(nCurPathTile + nLength);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CStandartPath2::TryUpdatePath(const CVec2 &target)
{
	int oldLen = pStaticPath->GetLength();
	if (oldLen < 2)
		return false;

	SVector vStartTile = pStaticPath->GetTile(oldLen - 1);
	SVector vTarget    = pMap->GetTile(target);

	MapModeChanger mode(MAP_MODE_ALL_STATICS, pMap);

	// similar to CCommonPathFinder::TracePathLine()
	CBres bres;
	bres.InitPoint(vStartTile, vTarget);
	SVector curPoint = vStartTile;

	vector<SVector> pathBuffer;
	pathBuffer.reserve(MAX_PATH_TILES_COUNT);

	while (curPoint != vTarget)
	{
		bres.MakeStep();
		SVector dir = bres.GetDirection();
		if (!pMap->CanUnitGoByDir(nBoundTileRadius, nBoundTileRadiusDyn, curPoint, dir))
			return false;
		curPoint += dir;
		pathBuffer.push_back(curPoint);
	}

	if (pathBuffer.size())
		pStaticPath->MergePath(pathBuffer, 0);

	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bShift всегда true и vLastKnownGoodTile==INVALID_TILE кроме случая вызова из RecalcPath()
// Функция ищет путь по pStaticPath на STATIC_PATH_SHIFT тайлов вперёд. Строит (по-новой, с 
// учётом коллизий?) короткий путь и запоминает его. pStaticPath не меняется.
const bool CStandartPath2::CalculatePath( const bool bShift, const SVector &vLastKnownGoodTile, IPathValidator *pValidator, int numSteps )
{
  NI_PROFILE_FUNCTION
  
	// нечего считать, пора заканчивать
	if ( pathTiles[nLastPathTile] == vFinishTile )
		return false;

	const int nPrevStaticPathTile = nCurStaticPathTile;
	// выбираем точку на текущем статическом пути (сдвигаемся сразу на STATIC_PATH_SHIFT тайлов вперёд)
	if ( bShift )
		nCurStaticPathTile = Min( nCurStaticPathTile + STATIC_PATH_SHIFT, pStaticPath->GetLength()-1 ); // original: -2

	// проверяем текущий тайл по пути
	SVector vNextTile;
	bool tileValid = false;
	// если непроходимый - ищем ближайший проходимый тайл впереди или сзади по пути
	for ( int nShift = 0; nShift < STATIC_PATH_SHIFT; nShift++ )
	{
		// ... впереди
		if ( nCurStaticPathTile + nShift >= pStaticPath->GetLength() )
			break;
		vNextTile = pStaticPath->GetTile( nCurStaticPathTile + nShift );
		if ( IsValidTile( vNextTile ) )
		{
			nCurStaticPathTile += nShift;
			tileValid = true;
			break;
		}
	}
	if (!tileValid)
	{
		// точно такой же цикл, но в обратную сторону
		for ( int nShift = 0; nShift < STATIC_PATH_SHIFT; nShift++ )
		{
			// ... сзади
			if ( nCurStaticPathTile - nShift <= nPrevStaticPathTile )
				break;
			vNextTile = pStaticPath->GetTile( nCurStaticPathTile - nShift );
			if ( IsValidTile( vNextTile ) )
			{
				nCurStaticPathTile -= nShift;
				tileValid = true;
				break;
			}
		}
	}
	// если не нашли подходящий тайл со смещением на расстоянии STATIC_PATH_SHIFT - берём
	// тайл без смещения (все проверенные тайлы неправильные, мы берём "ближайший")
	if ( !tileValid )
		vNextTile = pStaticPath->GetTile( nCurStaticPathTile );

	// а вот теперь считаем маленький путь, конечный тайл - vNextTile, его индекс - nCurStaticPathTile
	//DebugTrace( ">>>> CalculatePath: %d x %d - %d x %d (valid: %d x %d) for unit %d (%d & %d)", pathTiles[nLastPathTile].x, pathTiles[nLastPathTile].y, vNextTile.x, vNextTile.y, vLastKnownGoodTile.x, vLastKnownGoodTile.y, nUnitID, nBoundTileRadius );
	const SVector &startTile = pathTiles[nLastPathTile];
	const SVector &endTile   = vNextTile;

	pathFinder->SetChecking(pointChecking);

  CObj<CCommonStaticPath> pFoundStaticPath;
  if ( pathFinder->CreatePath( nBoundTileRadius, nBoundTileRadiusDyn, startTile, endTile,
    IsValidTile( vLastKnownGoodTile ) ? vLastKnownGoodTile : pathTiles[nLastPathTile], pointChecking, pStaticPath->GetLength(), numSteps ) )
  {
    pFoundStaticPath = new CCommonStaticPath(GetWorld(), pathFinder->GetCurrentPath(), pathFinder->GetPathLength());
  }
	
  // Check again for movement finish. The final point here may differ from the original vFinishTile
  if ( IsValid(pFoundStaticPath) && pStaticPath->GetFinishTile() == pFoundStaticPath->GetFinishTile() && pFoundStaticPath->GetStartTile() == pFoundStaticPath->GetFinishTile())
    return false;

  //попробуем разрешить коллизию просто явным образом
  if ( !IsValid(pFoundStaticPath ) || (mDistance( pStaticPath->GetFinishTile(), pFoundStaticPath->GetFinishTile() ) > 2 && pFoundStaticPath->GetStartTile() == pFoundStaticPath->GetFinishTile()) )
  {
    MapModeChanger mode(MAP_MODE_ALL_STATICS, pMap);

    if ( pathFinder->CreatePath( nBoundTileRadius, nBoundTileRadiusDyn, startTile, endTile,
      IsValidTile( vLastKnownGoodTile ) ? vLastKnownGoodTile : pathTiles[nLastPathTile], pointChecking, pStaticPath->GetLength(), numSteps ) )
    {
      pFoundStaticPath = new CCommonStaticPath(GetWorld(), pathFinder->GetCurrentPath(), pathFinder->GetPathLength());
    }
  }

  if ( !IsValid(pFoundStaticPath ) || (mDistance( pStaticPath->GetFinishTile(), pFoundStaticPath->GetFinishTile() ) > 2 && pFoundStaticPath->GetStartTile() == pFoundStaticPath->GetFinishTile()) )
    return false;

	// проверяем длину пути через pValidator
	if ( pValidator)
	{
		// возможно, обходной путь
		int newPathLen = pFoundStaticPath->GetLength();
		if ( !pValidator->CheckPath( remainingLength, newPathLen ) )
			return false; // не прошло проверку -- не меняем путь
	}

	// если этот путь не слишком длинный - копируем его
	remainingLength = pFoundStaticPath->GetLength();
	if ( remainingLength <= SMALL_PATH_TILES_COUNT )
	{
		CopyPath( remainingLength );
		// если это был последний шаг - корректируем конечную точку
		if ( nCurStaticPathTile >= pStaticPath->GetLength()-2 )
			SetFinishTile( pathTiles[nLastPathTile] );
	}
	else
	{
		// подбираем nCurStaticPathTile и тайл на пути, чтобы они были максимально близки
		int nLength = Min( remainingLength-1, MAX_PATH_TILES_COUNT - 2*MAX_LOOK_FORWARD_POINTS );
		bool bCloseToFinish = false;
		do
		{
			bCloseToFinish = CompareDistance( vFinishTile, vNextTile, pFoundStaticPath->GetTile( nLength ) );
			if ( !bCloseToFinish )
				--nLength;
		} while( nLength > SMALL_PATH_TILES_COUNT && !bCloseToFinish );
		CopyPath( nLength );

		// попалась точка, которая ближе к финишу, чем к желаемой
		if ( bCloseToFinish )
		{
			int nBestStaticPathTile = nCurStaticPathTile;
			int nBestDistance = Distance( pStaticPath->GetTile( nBestStaticPathTile ), pathTiles[nLastPathTile] );
			for ( int i = nCurStaticPathTile+1; i < pStaticPath->GetLength()-1; ++i )
			{
				const int nThisDistance = Distance( pStaticPath->GetTile( i ), pathTiles[nLastPathTile] );
				if ( nThisDistance < nBestDistance )
				{
					nBestDistance = nThisDistance;
					nBestStaticPathTile = i;
				}
			}
			nCurStaticPathTile = nBestStaticPathTile;
		}
		// это был последний шаг - корректируем конечную точку
		if ( nCurStaticPathTile == pStaticPath->GetLength()-2 )
			SetFinishTile( pFoundStaticPath->GetFinishTile() );
	}
	return true;
}

const bool CStandartPath2::CalculateShortPath( const SVector &vDest, const bool bShift, const SVector &vLastKnownGoodTile, IPathValidator *pValidator, int numSteps )
{
  NI_PROFILE_FUNCTION
  
	// нечего считать, пора заканчивать
	if ( pathTiles[nLastPathTile] == vFinishTile )
		return false;

	// выбираем точку на текущем статическом пути (сдвигаемся сразу на STATIC_PATH_SHIFT тайлов вперёд)
	if ( bShift )
		nCurStaticPathTile = Min( nCurStaticPathTile + STATIC_PATH_SHIFT, pStaticPath->GetLength()-1 ); // original: -2

	// а вот теперь считаем маленький путь, конечный тайл - vNextTile, его индекс - nCurStaticPathTile
	const SVector &startTile = pathTiles[nLastPathTile];
  const SVector &endTile   =  vDest;

	pathFinder->SetChecking(pointChecking);

  CObj<CCommonStaticPath> pFoundStaticPath;
  if ( pathFinder->CreatePath( nBoundTileRadius, nBoundTileRadiusDyn, startTile, endTile,
    IsValidTile( vLastKnownGoodTile ) ? vLastKnownGoodTile : pathTiles[nLastPathTile], pointChecking, -1, numSteps ) )
    pFoundStaticPath = new CCommonStaticPath(GetWorld(), pathFinder->GetCurrentPath(), pathFinder->GetPathLength());
	
  //попробуем разрешить коллизию просто явным образом
  if ( !IsValid(pFoundStaticPath ) || (mDistance( pStaticPath->GetFinishTile(), pFoundStaticPath->GetFinishTile() ) > 2 && pFoundStaticPath->GetStartTile() == pFoundStaticPath->GetFinishTile()) )
  {
    MapModeChanger mode(MAP_MODE_ALL_STATICS, pMap);

    if ( pathFinder->CreatePath( nBoundTileRadius, nBoundTileRadiusDyn, startTile, endTile,
      IsValidTile( vLastKnownGoodTile ) ? vLastKnownGoodTile : pathTiles[nLastPathTile], pointChecking, -1, numSteps ) )
      pFoundStaticPath = new CCommonStaticPath(GetWorld(), pathFinder->GetCurrentPath(), pathFinder->GetPathLength());
  }

  if ( !IsValid(pFoundStaticPath ) || (mDistance( pStaticPath->GetFinishTile(), pFoundStaticPath->GetFinishTile() ) > 2 && pFoundStaticPath->GetStartTile() == pFoundStaticPath->GetFinishTile()) )
    return false;

	// проверяем длину пути через pValidator
	if ( pValidator)
	{
		// возможно, обходной путь
		int newPathLen = pFoundStaticPath->GetLength();
		if ( !pValidator->CheckPath( remainingLength, newPathLen ) )
			return false; // не прошло проверку -- не меняем путь
	}

	// если этот путь не слишком длинный - копируем его
	remainingLength = pFoundStaticPath->GetLength();
	if ( remainingLength <= SMALL_PATH_TILES_COUNT )
	{
		CopyPath( remainingLength );
		// если это был последний шаг - корректируем конечную точку
		//if ( nCurStaticPathTile >= pStaticPath->GetLength()-2 )
    if (pStaticPath->GetFinishTile() == pathTiles[nLastPathTile])
			SetFinishTile( pathTiles[nLastPathTile] );
	}
	else
	{
		// подбираем nCurStaticPathTile и тайл на пути, чтобы они были максимально близки
		int nLength = Min( remainingLength-1, MAX_PATH_TILES_COUNT - 2*MAX_LOOK_FORWARD_POINTS );
		bool bCloseToFinish = false;
		do
		{
      //bCloseToFinish = CompareDistance( vFinishTile, vNextTile, pFoundStaticPath->GetTile( nLength ) );
			bCloseToFinish = CompareDistance( vFinishTile, endTile, pFoundStaticPath->GetTile( nLength ) );
			if ( !bCloseToFinish )
				--nLength;
		} while( nLength > SMALL_PATH_TILES_COUNT && !bCloseToFinish );
		CopyPath( nLength );

		// попалась точка, которая ближе к финишу, чем к желаемой
		if ( bCloseToFinish )
		{
			int nBestStaticPathTile = nCurStaticPathTile;
			int nBestDistance = Distance( pStaticPath->GetTile( nBestStaticPathTile ), pathTiles[nLastPathTile] );
			for ( int i = nCurStaticPathTile+1; i < pStaticPath->GetLength()-1; ++i )
			{
				const int nThisDistance = Distance( pStaticPath->GetTile( i ), pathTiles[nLastPathTile] );
				if ( nThisDistance < nBestDistance )
				{
					nBestDistance = nThisDistance;
					nBestStaticPathTile = i;
				}
			}
			nCurStaticPathTile = nBestStaticPathTile;
		}
		// это был последний шаг - корректируем конечную точку
		if ( nCurStaticPathTile == pStaticPath->GetLength()-2 )
			SetFinishTile( pFoundStaticPath->GetFinishTile() );
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CStandartPath2::CanPeek( const int _nShift ) const
{
	if (IsFinished())
		return false;
	if (nCurInsTile + _nShift < insTiles.size())
		return true;
	int nShift = nCurInsTile + _nShift - insTiles.size();
	const int nLastPathTile2 = (nCurPathTile < nLastPathTile) ? nLastPathTile : nLastPathTile + MAX_PATH_TILES_COUNT;
	if (nCurPathTile + nShift >= nLastPathTile2)
		return false;
	if (nShift > MAX_LOOK_FORWARD_POINTS)
		return false;
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Проверка точки, отстоящей от "курсора" на _nShift тайлов вперёд
const CVec2 CStandartPath2::PeekPoint( const int _nShift ) const
{
	if ( IsFinished() )
		return vFinishPoint;

	// первые тайлы берутся из списка insTiles
	if ( nCurInsTile + _nShift < insTiles.size() )
		return pMap->GetPointByTile( insTiles[nCurInsTile+_nShift] );

	// остальные берутся из pathTiles
	int nShift = nCurInsTile + _nShift - insTiles.size();
	NI_VERIFY( nShift <= MAX_LOOK_FORWARD_POINTS, "Cannot predict point. Shift too far", nShift = MAX_LOOK_FORWARD_POINTS );

	// проверка на конец пути
	const int nLastPathTile2 = ( nCurPathTile < nLastPathTile ) ? nLastPathTile : nLastPathTile + MAX_PATH_TILES_COUNT;
	if ( nCurPathTile + nShift > nLastPathTile2 )
		return vFinishPoint;

	const int nTile = INDEX(nCurPathTile + nShift);
	return pMap->GetPointByTile( pathTiles[nTile] );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Смещение "курсора" на _nShift тайлов вперёд
void CStandartPath2::Shift( const int _nShift, int numSteps )
{
	if ( IsFinished() )		// путь пройден?
		return;
	if ( nCurInsTile + _nShift < insTiles.size() )
	{
		nCurInsTile += _nShift;
		return;
	}

	const int nShift = nCurInsTile + _nShift - insTiles.size();
	nCurInsTile = insTiles.size();

	nCurPathTile = INDEX(nCurPathTile + nShift);
	const int nLastPathTile2 = ( nCurPathTile < nLastPathTile ) ? nLastPathTile : nLastPathTile + MAX_PATH_TILES_COUNT;
	remainingLength--;
	if ( nCurPathTile + MAX_LOOK_FORWARD_POINTS >= nLastPathTile2 )
	{
		CalculatePath( true, INVALID_TILE, 0, numSteps );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStandartPath2::InsertTiles( const list<SVector> &tiles )
{
	insTiles.clear();
	for ( list<SVector>::const_iterator it = tiles.begin(); it != tiles.end(); ++it )
		insTiles.push_back( *it );
	nCurInsTile = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//const bool CStandartPath2::CanGoBackward( const PFBaseMovingUnit *pUnit ) const
//{
//	return pUnit->CanGoBackward();//?? && pStaticPath->GetLength() * float( pMap->GetTileSize() ) <= pUnit->GetUnitProfile().GetHalfLength() * 5.0f;
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CStandartPath2::RecoverPath( const CVec2 &vPoint, const SVector &vLastKnownGoodTile, int numSteps )
{
	//DebugTrace( "(%d) CStandartPath2::RecoverPath( %2.3f x %2.3f, %s, %d x %d )", nUnitID, vPoint.x, vPoint.y, bIsPointAtWater ? "true" : "false", vLastKnownGoodTile.x, vLastKnownGoodTile.y );
	CPtr<CCommonStaticPath> pNewStaticPath = 0;
	{
		MapModeChanger mode(MAP_MODE_ALL_STATICS, pMap);
    if ( pathFinder->CreatePath( nBoundTileRadius, nBoundTileRadiusDyn, pMap->GetTile(vPoint), pMap->GetTile(vFinishPoint), vLastKnownGoodTile, pointChecking, -1, numSteps ) )
		  pNewStaticPath = new CCommonStaticPath(GetWorld(), pathFinder->GetCurrentPath(), pathFinder->GetPathLength());
  }
	if ( IsValid( pStaticPath ) && IsValid( pNewStaticPath ) && nCurStaticPathTile < pStaticPath->GetLength()-2 )
	{
	
		MapModeChanger mode(MAP_MODE_ALL_STATICS, pMap);
		
    CPtr<CCommonStaticPath> pBackStaticPath;
    if ( pathFinder->CreatePath( nBoundTileRadius, nBoundTileRadiusDyn, pMap->GetTile(vPoint), pStaticPath->GetTile( nCurStaticPathTile  ),
      vLastKnownGoodTile, pointChecking, -1, numSteps ) )
    {
      pBackStaticPath = new CCommonStaticPath(GetWorld(), pathFinder->GetCurrentPath(), pathFinder->GetPathLength());
    }

		if ( IsValid( pBackStaticPath ) && pBackStaticPath->GetLength() + pStaticPath->GetLength() - nCurStaticPathTile < pNewStaticPath->GetLength()+STATIC_PATH_SHIFT )
		{
			if ( pBackStaticPath->MergePath( pStaticPath, nCurStaticPathTile ) )
				pNewStaticPath = pBackStaticPath;
		}
	}

	InitByStaticPath( pNewStaticPath, vPoint, vFinishPoint, numSteps );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CStandartPath2::RecalcPath( const CVec2 &vPoint, const SVector &vLastKnownGoodTile, IPathValidator *pValidator, int numSteps )
{
	// save path state in a case of fail, to allow call to RecoverPath() again later
	int saveLastPathTile = nLastPathTile;
	int saveCurPathTile  = nCurPathTile;
	int saveCurSPathTile = nCurStaticPathTile;
	SVector tiles[2];
	tiles[0] = pathTiles[0];
	tiles[1] = pathTiles[1];

	// recompute path
	nCurPathTile  = 0;
	nLastPathTile = 1;
	pathTiles[0] = pathTiles[1] = pMap->GetTile( vPoint );
	if ( CalculatePath( false, vLastKnownGoodTile, pValidator, numSteps ) )
	{
		vStartPoint = vPoint;
		return true;
	}
	// failed - restore path state
	nLastPathTile      = saveLastPathTile;
	nCurPathTile       = saveCurPathTile;
	nCurStaticPathTile = saveCurSPathTile;
	pathTiles[0]       = tiles[0];
	pathTiles[1]       = tiles[1];
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CStandartPath2::CalcShortPath( const SVector &vDest, const CVec2 &vPoint, const SVector &vLastKnownGoodTile, IPathValidator *pValidator, int numSteps )
{
	// save path state in a case of fail, to allow call to RecoverPath() again later
	int saveLastPathTile = nLastPathTile;
	int saveCurPathTile  = nCurPathTile;
	int saveCurSPathTile = nCurStaticPathTile;
	SVector tiles[2];
	tiles[0] = pathTiles[0];
	tiles[1] = pathTiles[1];

	// recompute path
	nCurPathTile  = 0;
	nLastPathTile = 1;
	pathTiles[0] = pathTiles[1] = pMap->GetTile( vPoint );
	if ( CalculateShortPath(vDest, false, vLastKnownGoodTile, pValidator, numSteps ) )
	{
		vStartPoint = vPoint;
		return true;
	}
	// failed - restore path state
	nLastPathTile      = saveLastPathTile;
	nCurPathTile       = saveCurPathTile;
	nCurStaticPathTile = saveCurSPathTile;
	pathTiles[0]       = tiles[0];
	pathTiles[1]       = tiles[1];
	return false;
}

void CStandartPath2::Reset()
{
	pMap = GetWorld()->GetTileMap();
	pathFinder = GetWorld()->GetPathFinder();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void CStandartPath2::MarkPath( const int nID, const NDebugInfo::EColor color ) const
{
	vector<SVector> tiles;

	if ( IsFinished() )
		return;

	if ( nCurInsTile < insTiles.size() )
	{
		for ( int i = nCurInsTile; i < insTiles.size(); ++i )
			tiles.push_back( insTiles[i] );
	}

	int i = nCurPathTile;
	while ( i != nLastPathTile )
	{
		tiles.push_back( pathTiles[i] );
		++i;
		if ( i == MAX_PATH_TILES_COUNT )
			i = 0;
	}
	DebugInfoManager()->CreateMarker( nID, tiles, color );
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( NWorld::IPointChecking )
REGISTER_WORLD_OBJECT_NM( CStandartPath2, NWorld );
