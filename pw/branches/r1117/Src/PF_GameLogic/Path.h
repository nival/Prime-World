#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//??#include "AIClasses.h"
//??#include "../DebugTools/DebugInfoManager.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EPathRestriction; // declared in CommonPathFinder.h

namespace NWorld
{

class TileMap;
class PFBaseMovingUnit;

_interface IPathValidator
{
	// проверка пути; если вернёт false - путь проверку не прошёл
	virtual bool CheckPath( int prevPathLen, int newPathLen ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! путь юнита
_interface IPath
{
	virtual bool IsFinished() const = 0;

	virtual bool CanPeek( int nShift ) const = 0;
	// Проверка точки, отстоящей от "курсора" на nShift тайлов вперёд
	virtual const CVec2 PeekPoint( const int nShift ) const = 0;
	// Смещение "курсора" на _nShift тайлов вперёд
	virtual void Shift( const int nShift, int numSteps ) = 0;

	virtual const CVec2& GetFinishPoint() const = 0;
	virtual const CVec2& GetStartPoint() const = 0;

	//! восстановить путь из новой точки ( vPoint )
	virtual void RecoverPath( const CVec2 &vPoint, const SVector &vLastKnownGoodTile, int numSteps ) = 0;
	//! пересчитать путь из новой точки ( vPoint )
	virtual bool RecalcPath( const CVec2 &vPoint, const SVector &vLastKnownGoodTile, IPathValidator *pValidator, int numSteps ) = 0;
	//! добавить тайлы в начало пути
	virtual void InsertTiles( const list<SVector> &tiles ) = 0;
	//! можно ли проехать весь путь задом
//	virtual const bool CanGoBackward( const NWorld::PFBaseMovingUnit *pUnit ) const = 0;
	virtual const bool ShouldCheckTurn() const = 0;
	//! можно ли для этого пути построить сложный разворот
	virtual const bool CanBuildComplexTurn() const = 0;
//??	virtual void MarkPath( const int nID, const NDebugInfo::EColor color ) const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace
