#ifndef FOUNDATION_HISTOGRAM_H_INCLUDED
#define FOUNDATION_HISTOGRAM_H_INCLUDED

#include <vector>

class HistogramBase : public NonCopyable
{
public:
  typedef double Scalar;

  struct Band
  {
    Scalar    lowerBound, upperBound;
    unsigned  hits;
    Scalar    avg, minValue, maxValue, sum;

    Band() :
    lowerBound( 0 ), upperBound( 0 ),
    hits( 0 ),
    avg( 0 ), minValue( 0 ), maxValue( 0 ), sum( 0 )
    {}
  };

  HistogramBase();

  void AddData( Scalar _x );

  void ResetData();

  size_t Size() const { return bands.size(); }
  const Band & GetBand( size_t _idx ) const;
  const Band & GetTotal() const { return total; }
  unsigned LowerHits() const { return lowerHits; }
  unsigned UpperHits() const { return upperHits; }

protected:
  std::vector<Band>   bands;
  Scalar              bandWidth;
  unsigned            lowerHits, upperHits;
  Band                total;

  virtual Band * FindBand( Scalar _x ) = 0;

  void UpdateBand( Band & _band, Scalar _x );
  void ResetBand( Band & _band );
};



class UniformHistogram : public HistogramBase
{
public:
  UniformHistogram( Scalar _lowerBound, Scalar _upperBound, Scalar _width );

protected:
  Scalar              bandWidth;

  virtual Band * FindBand( Scalar _x );
};



class CustomHistogram : public HistogramBase
{
public:
  CustomHistogram( const std::vector<Scalar> & _bands );

protected:
  virtual Band * FindBand( Scalar _x );
};

#endif //FOUNDATION_HISTOGRAM_H_INCLUDED
