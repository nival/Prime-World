#pragma once

#include "PFWorldObjectBase.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// большой статический путь, вдоль которого идут юниты
class CCommonStaticPath : public NWorld::PFWorldObjectBase
{
	WORLD_OBJECT_METHODS( 0x3008CB00, CCommonStaticPath );

public:
	CCommonStaticPath( NWorld::PFWorld* world, const vector<SVector>& tiles, int _length );

	const int GetLength() const	{ return length; }

	const SVector& GetTile( const int n ) const { return path[n]; }

	const SVector& GetStartTile() const	{ return GetTile( 0 ); }
	const SVector& GetFinishTile() const	{ return GetTile( GetLength() - 1 ); }

  bool MergePath( const CCommonStaticPath* pAppendant, int startIndex ) { return MergePath( pAppendant->path, startIndex ); }
	bool MergePath( const vector<SVector> &tiles, int startIndex );

  void ReversePath() { reverse( path.begin(), path.end() ); }

private:
  CCommonStaticPath() : length( -1 ) { }

  ZDATA_(NWorld::PFWorldObjectBase)
  ZNOCRC
	vector<SVector>  path;
	int length;
  ZNOCRCEND
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(NWorld::PFWorldObjectBase*)this);  if(!f.IsChecksum()){ f.Add(2,&path); f.Add(3,&length);  } return 0; }
	virtual bool NeedToBeStepped() { return false; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
