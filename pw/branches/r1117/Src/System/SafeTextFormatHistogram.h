#ifndef SAFETEXTFORMATCYCLICBUFFER_H_INCLUDED
#define SAFETEXTFORMATCYCLICBUFFER_H_INCLUDED

#include "SafeTextFormat.h"
#include "SafeTextFormatBuffers.h"
#include "Histogram.h"


namespace text
{

template<>
struct TArg<HistogramBase> : public BasicArg
{
public:
  TArg( const HistogramBase & h ) : H( h ) {}

  virtual void Format( IBuffer * buffer, const SFormatSpecs & specs ) const
  {
    buffer->WriteZ( "{" );

    {
      TArg<unsigned> a( H.LowerHits() );
      a.Format( buffer, specs );
    }
    buffer->WriteZ( "; " );

    for ( size_t i = 0; i < H.Size(); ++i )
    {
      if ( i )
        buffer->WriteZ( "; " );
      const HistogramBase::Band & band = H.GetBand( i );

      buffer->WriteZ( "[" );
      {
        TArg<HistogramBase::Scalar> a( band.lowerBound );
        a.Format( buffer, specs );
      }
      buffer->WriteZ( ", " );
      {
        TArg<HistogramBase::Scalar> a( band.upperBound );
        a.Format( buffer, specs );
      }
      buffer->WriteZ( "]: " );

      {
        TArg<unsigned> a( band.hits );
        a.Format( buffer, specs );
      }
    }

    buffer->WriteZ( "; " );
    {
      TArg<unsigned> a( H.UpperHits() );
      a.Format( buffer, specs );
    }

    buffer->WriteZ( "}" );
  }

  virtual bool AsInt( int & ) const { return false; }

private:
  const HistogramBase & H;
};



template<>
struct TArg<UniformHistogram> : public TArg<HistogramBase>
{
  TArg( const HistogramBase & h ) : TArg<HistogramBase>( h ) {}
};



template<>
struct TArg<CustomHistogram> : public TArg<HistogramBase>
{
  TArg( const HistogramBase & h ) : TArg<HistogramBase>( h ) {}
};

} //namespace text

#endif //SAFETEXTFORMATCYCLICBUFFER_H_INCLUDED
