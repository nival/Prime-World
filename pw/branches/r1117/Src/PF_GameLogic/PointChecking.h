#pragma once

namespace NWorld
{

_interface IPointChecking : public IObjectBase
{
	virtual bool IsGoodTile( const SVector &curTile ) const = 0;
};

} // namespace
