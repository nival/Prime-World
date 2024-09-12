#ifndef SAFETEXTFORMATEX_H_INCLUDED
#define SAFETEXTFORMATEX_H_INCLUDED

#include "SafeTextFormatBuffers.h"

#define NI_STRFMT text::Fmt

namespace text
{

const static size_t THREAD_BUFF_SZ = 4096;

char (&GetThreadBuffer())[THREAD_BUFF_SZ];

inline const char * Fmt( const char * fmt ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt );
  return B.c_str();
}

template<class T0>
inline const char * Fmt( const char * fmt, const T0 & a0 ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt, a0 );
  return B.c_str();
}

template<class T0, class T1>
inline const char * Fmt( const char * fmt, const T0 & a0, const T1 & a1 ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt, a0, a1 );
  return B.c_str();
}

template<class T0, class T1, class T2>
inline const char * Fmt( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2 ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt, a0, a1, a2 );
  return B.c_str();
}

template<class T0, class T1, class T2, class T3>
inline const char * Fmt( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3 ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt, a0, a1, a2, a3 );
  return B.c_str();
}

template<class T0, class T1, class T2, class T3, class T4>
inline const char * Fmt( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4 ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt, a0, a1, a2, a3, a4 );
  return B.c_str();
}

template<class T0, class T1, class T2, class T3, class T4, class T5>
inline const char * Fmt( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4, const T5 & a5 ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt, a0, a1, a2, a3, a4, a5 );
  return B.c_str();
}

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline const char * Fmt( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4, const T5 & a5, const T6 & a6 ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt, a0, a1, a2, a3, a4, a5, a6 );
  return B.c_str();
}

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
inline const char * Fmt( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4, const T5 & a5, const T6 & a6, const T7 & a7 ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt, a0, a1, a2, a3, a4, a5, a6, a7 );
  return B.c_str();
}

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
inline const char * Fmt( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4, const T5 & a5, const T6 & a6, const T7 & a7, const T8 & a8 ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt, a0, a1, a2, a3, a4, a5, a6, a7, a8 );
  return B.c_str();
}

template<class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
inline const char * Fmt( const char * fmt, const T0 & a0, const T1 & a1, const T2 & a2, const T3 & a3, const T4 & a4, const T5 & a5, const T6 & a6, const T7 & a7, const T8 & a8, const T9 & a9 ) {
  ExternalBuffer B( GetThreadBuffer() );
  PrintfFormatterBufferPtr fmtr( &B );
  fmtr.Trace( fmt, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9 );
  return B.c_str();
}

} //namespace text

#endif //SAFETEXTFORMATEX_H_INCLUDED
