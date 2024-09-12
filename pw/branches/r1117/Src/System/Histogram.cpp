#include "stdafx.h"
#include "Histogram.h"

HistogramBase::HistogramBase() :
lowerHits( 0 ), upperHits( 0 )
{
}



void HistogramBase::AddData( Scalar _x )
{
  UpdateBand( total, _x );

  if ( _x < total.lowerBound )
  {
    ++lowerHits;
    return;
  }

  if ( _x > total.upperBound )
  {
    ++upperHits;
    return;
  }

  Band * band = FindBand( _x );
  NI_VERIFY( band, "", return );

  UpdateBand( *band, _x );
}



void HistogramBase::ResetData()
{
  lowerHits = upperHits = 0;

  for ( size_t i = 0; i < bands.size(); ++i )
    ResetBand( bands[i] );
  ResetBand( total );
}



void HistogramBase::UpdateBand( Band & _band, Scalar _x )
{
  if ( !_band.hits )
  {
    _band.minValue = _x;
    _band.maxValue = _x;
  }
  else
  {
    if ( _x < _band.minValue )
      _band.minValue = _x;
    else if ( _x > _band.maxValue )
      _band.maxValue = _x;
  }

  ++_band.hits;
  _band.sum += _x;

  _band.avg = _band.sum / _band.hits;
}



void HistogramBase::ResetBand( Band & _band )
{
  _band.hits = 0;
  _band.minValue = 0;
  _band.maxValue = 0;
  _band.avg = 0;
  _band.sum = 0;
}



const HistogramBase::Band & HistogramBase::GetBand( size_t _idx ) const
{
  NI_VERIFY( _idx <= bands.size(), "", return total );
  return bands[_idx];
}







UniformHistogram::UniformHistogram( Scalar _lowerBound, Scalar _upperBound, Scalar _width ) :
HistogramBase(),
bandWidth( 0 )
{
  total.lowerBound = _lowerBound;
  total.upperBound = _upperBound;

  size_t size = (int)( 0.5 + ( total.upperBound - total.lowerBound ) / _width );
  if ( size < 1 )
    size = 1;
  bandWidth = ( total.upperBound - total.lowerBound ) / size;

  bands.resize( size );

  for ( size_t i = 0; i < bands.size(); ++i )
  {
    bands[i].lowerBound = total.lowerBound + bandWidth * i;
    bands[i].upperBound = total.lowerBound + bandWidth * ( i + 1 );
  }
}


HistogramBase::Band * UniformHistogram::FindBand( Scalar _x )
{
  if ( bands.empty() )
    return 0;

  int index = (int)( _x - total.lowerBound ) / bandWidth;
  index = Clamp( index, 0, (int)( bands.size() - 1 ) );

  return &bands[index];
}









CustomHistogram::CustomHistogram( const std::vector<Scalar> & _bands ) :
HistogramBase()
{
  NI_VERIFY( _bands.size() >= 2, "", return );

  total.lowerBound = _bands.front();
  total.upperBound = _bands.back();

  bands.resize( _bands.size() - 1 );

  for ( size_t i = 0; i + 1 < _bands.size(); ++i )
  {
    bands[i].lowerBound = _bands[i];
    bands[i].upperBound = _bands[i + 1];
  }
}



HistogramBase::Band * CustomHistogram::FindBand( Scalar _x )
{
  if ( bands.empty() )
    return 0;

  const Scalar eps = 1e-6 * ( total.upperBound - total.lowerBound );
  for ( size_t i = 0; i < bands.size(); ++i )
  {
    Band & band = bands[i];
    if ( ( _x > band.lowerBound - eps ) && ( _x < band.upperBound + eps ) )
      return &band;
  }

  return &bands.front();
}
