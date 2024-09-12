#pragma once

#include "../System/BitData.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{

class BitMap
{
  ZDATA
		CArray2D1Bit mask;
		CVec2 mult;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&mask); f.Add(3,&mult); return 0; }

private:
	int GetX( const float x ) const { return Clamp( (int)floor( x * mult.x ), 0, mask.GetSizeX() ); }
	int GetY( const float y ) const { return Clamp( (int)floor( y * mult.y ), 0, mask.GetSizeY() ); }
	BitMap( const char* data, float mapSizeX, float mapSizeY, int maskSize );

public:
  BitMap() : mult( VNULL2 ) {}

  BitMap( bool water, const CVec2& mapSize )
  {
    mask.SetSizes( 1, 1 );

    if ( water )
      mask.Set1();
    else
      mask.FillZero();

    mult.x = 1.0f/mapSize.x;
    mult.y = 1.0f/mapSize.y;
  }

  bool CheckPos( const CVec2& pos ) const
  {
		NI_VERIFY( !mask.IsEmpty(), "BitMap not initialized", return false );
		return mask.GetData( GetX( pos.x ), GetY( pos.y ) ) > 0;
  }

	static void Store( const char* data, float mapSizeX, float mapSizeY, int maskSize, const string& fileName );
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}