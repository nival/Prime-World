#ifndef SAFETEXTFORMATCYCLICBUFFER_H_INCLUDED
#define SAFETEXTFORMATCYCLICBUFFER_H_INCLUDED

#include "SafeTextFormat.h"
#include "SafeTextFormatBuffers.h"
#include "CyclicBuffer.h"


namespace text
{

template<class T, class TCopyPolicy>
struct TArg<CyclicBuffer<T, TCopyPolicy> > : public BasicArg
{
public:
  typedef CyclicBuffer<T, TCopyPolicy> TCyclicBuffer;

  TArg( const TCyclicBuffer & cb ) : CB( cb ) {}

  virtual void Format( IBuffer * buffer, const SFormatSpecs & specs ) const
  {
    buffer->WriteZ( "[" );
    for ( size_t i = 0; i < CB.Size(); ++i )
    {
      if ( i )
        buffer->WriteZ( ", " );
      if ( i < 16 )
      {
        TArg<T> a( CB.AtHead( i ) );
        a.Format( buffer, specs );
      }
      else
      {
        buffer->WriteZ( "..." );
        break;
      }
    }
    buffer->WriteZ( "]" );
  }

  virtual bool AsInt( int & ) const { return false; }

private:
  const TCyclicBuffer & CB;
};

} //namespace text

#endif //SAFETEXTFORMATCYCLICBUFFER_H_INCLUDED
