#pragma once

#include <list>
#include <vector>
#include <string>
#include "System/LogFileName.h"

#pragma warning( disable : 4996 )

namespace nutils {

class DataHistogram : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( DataHistogram, BaseObjectST );

public:
  typedef double Scalar;

  struct SBandDescr
  {
    Scalar  from, to;
    int     hits;

    SBandDescr() : from( 0 ), to( 0 ), hits( 0 ) {}
    SBandDescr( Scalar _from, Scalar _to, int _hits ) : from( _from ), to( _to ), hits( _hits ) {}
  };


  struct SInfo
  {
    int     count;
    Scalar  minVal, maxVal, average;
    SInfo() : count( 0 ), minVal( 0 ), maxVal( 0 ), average( 0 ) {}
    SInfo( int cnt, Scalar minv, Scalar maxv, Scalar avg ) : count( cnt ), minVal( minv ), maxVal( maxv ), average( avg ) {}
  };

  DataHistogram( Scalar _bandWidth ); //Linear
  DataHistogram( Scalar _bandWidth, Scalar _bandGrouth ); //Logarithmic
  DataHistogram( const std::vector<Scalar> & _points );

public:
  void AddValue( Scalar _val, int _count = 1 );
  bool IsEmpty() const { return bands.empty(); }
  int BandsCount() const;
  bool GetBand( SBandDescr & _band, int _index ) const;
  void ToVector( vector<SBandDescr> & _vec ) const;

  void DumpInfo( const string & title ) const;
  void DumpFreq( const string & filename ) const;
  void DumpValues( const string & filename ) const;
  void Draw( const string & filename, const string & title, int width, int height, int precision ) const;
  void DrawFlipText( HDC dc, const char * text, bool ontop, HGDIOBJ horFont, HGDIOBJ verFont, const RECT & rect, int margin, int fontHeight, int bottomMargin ) const;

  void Output( const string & subfolder, const string & title, int width, int height, int precision ) const;
  SInfo Info() const;

  typedef vector<pair<string, Strong<DataHistogram>>> THistogramsPack;
  static void WritePackAsCsv( const THistogramsPack & pack, const string & id, const string & subfolder );

private:
  struct EType
  {
    enum Enum { Linear, Log, Fixed };
  };

  typedef std::list<SBandDescr> TBands;
  typedef std::vector<Scalar> TDataLog;

  EType::Enum       type;
  Scalar            bandWidth, logBandGrouth;
  TBands            bands;
  Scalar            sum;
  Scalar            minVal, maxVal;
  TDataLog          dataLog;

  void AddFixedBand( Scalar _from, Scalar _to );
  void ExpandDown( Scalar _val );
  void ExpandUp( Scalar _val );
};



class DataHistogram2D : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( DataHistogram2D, BaseObjectST );

public:
  typedef double Scalar;

  struct Bar : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( Bar, BaseObjectST );

    Scalar  x0, x1, y0, y1;
    int     hits;

    Bar( Scalar _x0, Scalar _x1, Scalar _y0, Scalar _y1 ) :
    x0( _x0 ), x1( _x1 ), y0( _y0 ), y1( _y1 ),
    hits( 0 )
    {}
  };

  DataHistogram2D( const std::vector<Scalar> & _xscale, const std::vector<Scalar> & _yscale );

  void AddValue( Scalar _x, Scalar _y, int _count = 1 );
  void DumpFreq( const string & title, const string & subfolder ) const;

private:
  typedef std::vector<Strong<Bar>> TBars;

  std::vector<Scalar>   xscale, yscale;
  size_t                xs, ys;
  TBars                 bars;
  unsigned              hits;

  enum ENormalization { NormalizeNone, NormalizeAll, NormalizeByRow, NormalizeByColumn };

  Bar * GetBar( size_t ix, size_t iy ) const;
  void DumpFreqImpl( FILE * f, ENormalization norm ) const;
};



template<typename T>
class EasyVector : public std::vector<T>
{
public:
  explicit EasyVector( T _x0 ) {
    push_back( _x0 );
  }

  EasyVector( T _x0, T _x1 ) {
    reserve( 2 );
    push_back( _x0 );
    push_back( _x1 );
  }

  EasyVector( T _x0, T _x1, T _x2 ) {
    reserve( 3 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3 ) {
    reserve( 4 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4 ) {
    reserve( 5 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5 ) {
    reserve( 6 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6 ) {
    reserve( 7 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7 ) {
    reserve( 8 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8 ) {
    reserve( 9 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9 ) {
    reserve( 10 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9, T _x10 ) {
    reserve( 11 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
    push_back( _x10 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9, T _x10, T _x11 ) {
    reserve( 12 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
    push_back( _x10 );
    push_back( _x11 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9, T _x10, T _x11, T _x12 ) {
    reserve( 13 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
    push_back( _x10 );
    push_back( _x11 );
    push_back( _x12 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9, T _x10, T _x11, T _x12, T _x13 ) {
    reserve( 14 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
    push_back( _x10 );
    push_back( _x11 );
    push_back( _x12 );
    push_back( _x13 );
  }

  EasyVector( T _x0, T _x1, T _x2, T _x3, T _x4, T _x5, T _x6, T _x7, T _x8, T _x9, T _x10, T _x11, T _x12, T _x13, T _x14 ) {
    reserve( 15 );
    push_back( _x0 );
    push_back( _x1 );
    push_back( _x2 );
    push_back( _x3 );
    push_back( _x4 );
    push_back( _x5 );
    push_back( _x6 );
    push_back( _x7 );
    push_back( _x8 );
    push_back( _x9 );
    push_back( _x10 );
    push_back( _x11 );
    push_back( _x12 );
    push_back( _x13 );
    push_back( _x14 );
  }
};

} //namespace nutils
