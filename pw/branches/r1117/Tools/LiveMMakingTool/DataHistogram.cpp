#include "stdafx.h"
#include "DataHistogram.h"
#include "atlimage.h"

const static float Eps = 1e-3f;

namespace nutils
{

DataHistogram::DataHistogram( Scalar _bandWidth ) :
type( EType::Linear ),
bandWidth( _bandWidth ),
logBandGrouth( 0 ),
sum( 0 ),
minVal( 0 ),
maxVal( 0 )
{
  dataLog.reserve( 100 );

  bands.push_back( SBandDescr( 0, bandWidth, 0 ) );
}



DataHistogram::DataHistogram( Scalar _bandWidth, Scalar _bandGrouth ) :
type( EType::Log ),
bandWidth( _bandWidth ),
logBandGrouth( _bandGrouth ),
sum( 0 ),
minVal( 0 ),
maxVal( 0 )
{
  dataLog.reserve( 100 );

  bands.push_back( SBandDescr( -bandWidth, 0, 0 ) );
  bands.push_back( SBandDescr( 0, bandWidth, 0 ) );
}



DataHistogram::DataHistogram( const std::vector<Scalar> & _points ) :
type( EType::Fixed ),
bandWidth( 0 ),
logBandGrouth( 0 ),
sum( 0 ),
minVal( 0 ),
maxVal( 0 )
{
  NI_VERIFY( _points.size() > 2, "", return );
  for ( size_t i = 0; i < _points.size() - 1; ++i )
    AddFixedBand( _points[i], _points[i + 1] );
}



void DataHistogram::AddFixedBand( Scalar _from, Scalar _to )
{
  bands.push_back( SBandDescr( _from, _to, 0 ) );
}



void DataHistogram::AddValue( Scalar _val, int _count )
{
  if ( type != EType::Fixed )
  {
    ExpandDown( _val );
    ExpandUp( _val );
  }

  bool ok = false;
  for ( TBands::iterator it = bands.begin(); it != bands.end(); ++it )
    if ( ( _val > it->from - Eps ) && ( _val < it->to + Eps ) ) {
      it->hits += _count;
      ok = true;
      break;
    }

  sum += _val;

  if ( dataLog.empty() || ( _val < minVal ) )
    minVal = _val;
  if ( dataLog.empty() || ( _val > maxVal ) )
    maxVal = _val;

  dataLog.push_back( _val );
}



void DataHistogram::ExpandDown( Scalar _val )
{
  while ( true )
  {
    if ( !bands.empty() )
      if ( _val > bands.front().from - Eps )
        break;

    Scalar left = bands.empty() ? 0 : bands.front().from;

    if ( type == EType::Linear )
      bands.push_front( SBandDescr( left - bandWidth, left, 0 ) );
    else if ( type == EType::Log )
    {
      if ( _val >= 0 )
        return;
      Scalar newLeft = bandWidth;
      if ( !bands.empty() )
        newLeft = -fabs( left ) * logBandGrouth;

      bands.push_front( SBandDescr( newLeft, left, 0 ) );
    }
    else
      break;
  }
}



void DataHistogram::ExpandUp( Scalar _val )
{
  while ( true )
  {
    if ( !bands.empty() )
      if ( _val < bands.back().to + Eps )
        break;

    Scalar right = bands.empty() ? 0 : bands.back().to;

    if ( type == EType::Linear )
      bands.push_back( SBandDescr( right, right + bandWidth, 0 ) );
    else if ( type == EType::Log )
    {
      if ( _val < 0 )
        return;
      Scalar newRight = bandWidth;
      if ( !bands.empty() )
        newRight = +fabs( right ) * logBandGrouth;

      bands.push_back( SBandDescr( right, newRight, 0 ) );
    }
    else
      break;
  }
}



int DataHistogram::BandsCount() const
{
  return bands.size();
}



bool DataHistogram::GetBand( SBandDescr & _band, int _index ) const
{
  if ( ( _index < 0 ) || ( _index >= (int)bands.size() ) )
    return false;

  TBands::const_iterator it = bands.begin();
  std::advance( it, _index );
  _band = *it;
  return true;
}



void DataHistogram::ToVector( vector<SBandDescr> & _vec ) const
{
  _vec.resize( bands.size() );
  std::copy( bands.begin(), bands.end(), _vec.begin() );
}



void DataHistogram::DumpInfo( const string & title ) const
{
  MessageTrace( "Hystogram '%s' info:", title );

  MessageTrace( "Total values: %d", dataLog.size() );

  if ( dataLog.empty() ) {
    MessageTrace( "No data!" );
    return;
  }

  MessageTrace( "Min: %.3f", minVal );
  MessageTrace( "Max: %.3f", maxVal );
  MessageTrace( "Avg: %.3f", sum / (Scalar)dataLog.size() );
}



void DataHistogram::DumpFreq( const string & filename ) const
{
  FILE * f = fopen( filename.c_str(), "wt" );
  if ( !f )
    return;

  fprintf( f, "Range; Hits\n" );
  int count = BandsCount();
  for ( int i = 0; i < count; ++i )
  {
    SBandDescr b;
    GetBand( b, i );
    fprintf( f, "[%.3f, %.3f]; %d\n", b.from, b.to, b.hits );
  }

  fclose( f );
}



static std::string Flt2Csv( double f )
{
  char buf[128]="";
  _gcvt( f, 6, buf );
  for ( int j = 0; buf[j]; ++j )
    if ( buf[j] == '.' )
      buf[j] = ',';
  return buf;
}



void DataHistogram::DumpValues( const string & filename ) const
{
  FILE * f = fopen( filename.c_str(), "wt" );
  if ( !f )
    return;

  for ( size_t i = 0; i < dataLog.size(); ++i ) {
    fprintf( f, "%s\n", Flt2Csv( dataLog[i] ).c_str() );
  }

  fclose( f );
}



void DataHistogram::Draw( const string & filename, const string & title, int width, int height, int precision ) const
{
  const int margin = 4;
  const int textMargin = 2;
  const int fontHeight = 12;
  const int titleHeight = 32;
  const int bottomMargin = 100;

  CImage img;
  img.Create( width, height, 24 );

  HDC dc = img.GetDC();

  HBRUSH backBrush = CreateSolidBrush( RGB( 255, 255, 255 ) );
  HBRUSH barBrush = CreateSolidBrush( RGB( 73, 146, 255 ) );
  HPEN nullPen = CreatePen( PS_NULL, 0, RGB( 0, 0, 0 ) );
  HPEN pen = CreatePen( PS_SOLID, 0, RGB( 0, 0, 0 ) );
  HFONT vertFont = ::CreateFont( fontHeight, fontHeight/2, 900, 900, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE, "Arial" );
  HFONT horFont = ::CreateFont( fontHeight, fontHeight/2, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE, "Arial" );
  HFONT titleFont = ::CreateFont( titleHeight, titleHeight/2, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE, "Arial" );

  HGDIOBJ prevPen = SelectObject( dc, nullPen );

  //Draw background
  HGDIOBJ prevBrush = SelectObject( dc, backBrush );
  Rectangle( dc, 0, 0, width, height );

  SelectObject( dc, pen );

  SetBkMode( dc, TRANSPARENT );

  HGDIOBJ prevFont = SelectObject( dc, vertFont );

  SetTextColor( dc, RGB( 0, 0, 0 ) );

  if ( !IsEmpty() )
  {
    vector<SBandDescr> vec;
    ToVector( vec );
    NI_ASSERT( !vec.empty(), "" );

    int maxHits = 0;
    for ( int i = 0; i < vec.size(); ++i )
      maxHits = Max( maxHits, vec[i].hits );

    int usableBars = 0;
    for ( int i = 0; i < vec.size(); ++i )
      //if ( vec[i].hits )
      ++usableBars;

    int barsHeight = height - margin - bottomMargin - titleHeight - fontHeight - 2 * textMargin;

    SelectObject( dc, barBrush );
    for ( int index = 0, i = 0; i < vec.size(); ++i )
    {
      //if ( !vec[i].hits )
      //  continue;

      int x0 = margin + ( width - margin ) * index / usableBars;
      int x1 = ( width - margin ) * ( index + 1 ) / usableBars;
      int y1 = height - bottomMargin - textMargin - fontHeight;
      int y0 = y1 - ( maxHits ? ( barsHeight * vec[i].hits / maxHits ) : 0 );
      if ( y1 == y0 )
        --y0;
      Rectangle( dc, x0, y0, x1, y1 );

      RECT rect;
      SetRect( &rect, x0, y0, x1, y1 );
      DrawFlipText( dc, NI_STRFMT( "[%.*f, %.*f]", precision, vec[i].from, precision, vec[i].to ), false, horFont, vertFont, rect, textMargin, fontHeight, bottomMargin );

      SetRect( &rect, x0, y0, x1, y1 );
      DrawFlipText( dc, NI_STRFMT( "%d", vec[i].hits ), true, horFont, vertFont, rect, textMargin, fontHeight, bottomMargin );

      ++index;
    }
  }
  else {
    SelectObject( dc, titleFont );
    RECT R;
    SetRect( &R, margin, 2 * margin + titleHeight, width - margin, height - margin );
    SetTextColor( dc, RGB( 255, 0, 0 ) );
    DrawText( dc, "No data!", -1, &R, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
    SetTextColor( dc, RGB( 0, 0, 0 ) );
  }

  {
    SelectObject( dc, titleFont );
    RECT R;
    SetRect( &R, margin, margin, width - margin, margin + titleHeight );
    DrawText( dc, title.c_str(), -1, &R, 0 );
  }

  //restore GDI objects
  SelectObject( dc, prevBrush );
  SelectObject( dc, prevPen );
  SelectObject( dc, prevFont );

  //Cleanup
  DeleteObject( titleFont );
  DeleteObject( horFont );
  DeleteObject( vertFont );
  DeleteObject( pen );
  DeleteObject( nullPen );
  DeleteObject( barBrush );
  DeleteObject( backBrush );

  img.ReleaseDC();
  img.Save( filename.c_str(), Gdiplus::ImageFormatPNG );
}



void DataHistogram::DrawFlipText( HDC dc, const char * text, bool ontop, HGDIOBJ horFont, HGDIOBJ vertFont, const RECT & rect, int margin, int fontHeight, int bottomMargin ) const
{
  RECT r;
  SetRect( &r, 0, 0, 0, 0 );

  SelectObject( dc, horFont );
  DrawText( dc, text, -1, &r, DT_SINGLELINE | DT_CALCRECT );
  int textWidth = r.right - r.left;

  if ( textWidth + margin < ( rect.right - rect.left ) ) {
    if ( ontop )
      SetRect( &r, rect.left, rect.bottom - margin, rect.right, rect.bottom - margin );
    else
      SetRect( &r, rect.left, rect.bottom + margin, rect.right, rect.bottom + margin );
    
    DrawText( dc, text, -1, &r, DT_NOCLIP | DT_SINGLELINE | ( ontop ? DT_BOTTOM : DT_TOP ) | DT_CENTER );
    return;
  }
  
  SelectObject( dc, vertFont );
  int x = ( rect.left + rect.right - fontHeight - margin ) / 2;

  if ( ontop )
    SetRect( &r, x, rect.bottom - margin, x + fontHeight + margin, rect.bottom - margin );
  else {
    SetRect( &r, 0, 0, 0, 0 );
    DrawText( dc, text, -1, &r, DT_SINGLELINE | DT_CALCRECT );
    int textWidthH = r.right - r.left;

    SetRect( &r, x, rect.bottom + margin + textWidthH, x + fontHeight + margin, rect.bottom + margin + textWidthH );
  }

  DrawText( dc, text, -1, &r, DT_NOCLIP | DT_SINGLELINE | DT_LEFT | DT_TOP );
}



void DataHistogram::Output( const string & subfolder, const string & title, int width, int height, int precision ) const
{
  string sep = subfolder.empty() ? "" : "/";
  DumpInfo( title );
  DumpValues( subfolder + sep + title + ".csv"  );
  DumpFreq( subfolder + sep + title + ".freq.csv" );
  Draw( subfolder + sep + title + ".png", title, width, height, precision );
}



DataHistogram::SInfo DataHistogram::Info() const
{
  return SInfo( (int)dataLog.size(), minVal, maxVal, dataLog.empty() ? 0 : ( sum / (Scalar)dataLog.size() ) );
}



void DataHistogram::WritePackAsCsv( const THistogramsPack & pack, const string & id, const string & subfolder )
{
  if ( pack.size() < 2 )
    return;

  for ( int i = 1; i < pack.size(); ++i )
    NI_VERIFY( pack[i].second->BandsCount() == pack[0].second->BandsCount(), "", return );

  int bands = pack[0].second->BandsCount();

  string filename = subfolder;
  if ( !filename.empty() )
    filename += "/";
  filename += id;
  filename += ".freq.csv";

  FILE * f = fopen( filename.c_str(), "wt" );
  if ( !f )
    return;

  fprintf( f, "Range" );
  for ( int i = 0; i < pack.size(); ++i )
    fprintf( f, ";%s", pack[i].first.c_str() );
  fprintf( f, "\n" );

  for ( int i = 0; i < bands; ++i ) {
    nutils::DataHistogram::SBandDescr b;
    pack[0].second->GetBand( b, i );
    fprintf( f, "[%.3f, %.3f]", b.from, b.to, b.hits );

    for ( int j = 0; j < pack.size(); ++j ) {
      pack[j].second->GetBand( b, i );
      fprintf( f, ";%d", b.hits );
    }
    fprintf( f, "\n" );
  }

  fclose( f );
}



DataHistogram2D::DataHistogram2D( const std::vector<Scalar> & _xscale, const std::vector<Scalar> & _yscale ) :
xscale( _xscale ), yscale( _yscale ),
xs( 0 ), ys( 0 ),
hits( 0 )
{
  NI_VERIFY( xscale.size() > 1, "", return );
  NI_VERIFY( yscale.size() > 1, "", return );

  xs = _xscale.size() - 1;
  ys = _yscale.size() - 1;

  for ( size_t ix = 0; ix < xs; ++ix )
    NI_VERIFY( xscale[ix] < xscale[ix + 1], "", return );
  
  for ( size_t iy = 0; iy < ys; ++iy )
    NI_VERIFY( yscale[iy] < yscale[iy + 1], "", return );

  bars.resize( xs * ys );

  for ( size_t iy = 0; iy < ys; ++iy )
    for ( size_t ix = 0; ix < xs; ++ix )
      bars[ iy * xs + ix ] = new Bar( xscale[ix], xscale[ix + 1], yscale[iy], yscale[iy + 1] );
}



DataHistogram2D::Bar * DataHistogram2D::GetBar( size_t ix, size_t iy ) const
{
  NI_VERIFY( ( ix >= 0 ) && ( ix < xs ), "", return bars[0] );
  NI_VERIFY( ( iy >= 0 ) && ( iy < ys ), "", return bars[0] );
  return bars[iy * xs + ix];
}



void DataHistogram2D::AddValue( Scalar _x, Scalar _y, int _count )
{
  for ( size_t iy = 0; iy < ys; ++iy )
    if ( ( _y > yscale[iy] - Eps ) && ( _y < yscale[iy + 1] + Eps ) )
      for ( size_t ix = 0; ix < xs; ++ix )
        if ( ( _x > xscale[ix] - Eps ) && ( _x < xscale[ix + 1] + Eps ) )
        {
          Bar * bar = GetBar( ix, iy );
          bar->hits += _count;
          hits += _count;
          return;
        }
}



void DataHistogram2D::DumpFreq( const string & title, const string & subfolder ) const
{
  string filename = subfolder;
  if ( !filename.empty() )
    filename += "/";
  filename += title;
  filename += ".freq.csv";

  FILE * f = fopen( filename.c_str(), "wt" );
  if ( !f )
    return;

  fprintf( f, "Raw data:\n" );
  DumpFreqImpl( f, NormalizeNone );

  fprintf( f, "\nGlobal normalization:\n" );
  DumpFreqImpl( f, NormalizeAll );

  fprintf( f, "\nNormalized by rows:\n" );
  DumpFreqImpl( f, NormalizeByRow );

  fprintf( f, "\nNormalized by columns:\n" );
  DumpFreqImpl( f, NormalizeByColumn );

  fclose( f );
}



void DataHistogram2D::DumpFreqImpl( FILE * f, ENormalization norm ) const
{
  for ( size_t ix = 0; ix < xs; ++ix )
    fprintf( f, ";[%g, %g]", xscale[ix], xscale[ix+1] );
  fprintf( f, "\n" );

  double total = 0;
  if ( norm == NormalizeAll )
    for ( size_t iy = 0; iy < ys; ++iy )
      for ( size_t ix = 0; ix < xs; ++ix )
        total += GetBar( ix, iy )->hits;

  for ( size_t iy = 0; iy < ys; ++iy )
  {
    fprintf( f, "[%g, %g]", yscale[iy], yscale[iy+1] );

    double rowTotal = 0;
    if ( norm == NormalizeByRow )
      for ( size_t ix = 0; ix < xs; ++ix )
        rowTotal += GetBar( ix, iy )->hits;

    for ( size_t ix = 0; ix < xs; ++ix ) {
      Bar * bar = GetBar( ix, iy );

      double columnTotal = 0;
      for ( size_t iyy = 0; iyy < ys; ++iyy )
        columnTotal += GetBar( ix, iyy )->hits;

      if ( norm == NormalizeNone )
        fprintf( f, ";%d", bar->hits );
      else if ( norm == NormalizeAll )
        fprintf( f, ";%s", bar->hits ? Flt2Csv( bar->hits / total ).c_str() : "0" );
      else if ( norm == NormalizeByRow )
        fprintf( f, ";%s", bar->hits ? Flt2Csv( bar->hits / rowTotal ).c_str() : "0" );
      else if ( norm == NormalizeByColumn )
        fprintf( f, ";%s", bar->hits ? Flt2Csv( bar->hits / columnTotal ).c_str() : "0" );
    }
    fprintf( f, "\n" );
  }
}

} //namespace nutils
