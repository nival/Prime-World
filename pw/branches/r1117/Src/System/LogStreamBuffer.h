#ifndef LOGSTREAMBUFFER_H_INCLUDED
#define LOGSTREAMBUFFER_H_INCLUDED

#include "ChannelLogger.h"
#include "StrFormatter.h"
#include "SafeTextFormatEx.h"
#include "SafeTextFormatNstl.h"
#include "System/nfixed_string.h"


namespace NLogg
{

class StreamBuffer : public text::PrintfFormatterStaticBuffer<4096>
{
public:
  StreamBuffer( CChannelLogger & _logger, const SEntryInfo & _info ) :
  logger( _logger ),
  entryInfo( _info ),
  textStart( Buffer().c_str() )
  {
    WriteHeader( logger.HeaderFormat() );
    textStart = Buffer().c_str() + Buffer().Length();
  }

  ~StreamBuffer() {
    Push( "\r\n" );
    logger.Log( entryInfo, Buffer().c_str(), textStart );
  }

  NLogg::CChannelLogger & GetLog() { return logger; }

  StreamBuffer &operator<<( StreamBuffer &(*pFunc)(StreamBuffer &) ) { return *this; }

  StreamBuffer &operator<<( const char *szString ) { Push( szString ); return *this; }
  StreamBuffer &operator<<( const string &szString ) { Push( szString.c_str() ); return *this; }
  StreamBuffer &operator<<( string &szString ) { Push( szString.c_str() ); return *this; }

  StreamBuffer &operator<<( const wstring &wszString ) { Push( NStr::ToMBCS( wszString ).c_str() ); return *this; }
  StreamBuffer &operator<<( wstring &wszString ) { Push( NStr::ToMBCS( wszString ).c_str() ); return *this; }

  template <size_t N>
  StreamBuffer &operator<<( const nstl::fixed_string<char, N> &szString ) { Push( szString.c_str() ); return *this; }
  template <size_t N>
  StreamBuffer &operator<<( nstl::fixed_string<char, N> &szString ) { Push( szString.c_str() ); return *this; }

  template <size_t N>
  StreamBuffer &operator<<( const nstl::fixed_string<wchar_t, N> &wszString ) { Push( NStr::ToMBCS( nstl::wstring(wszString) ).c_str() ); return *this; }
  template <size_t N>
  StreamBuffer &operator<<( nstl::fixed_string<wchar_t, N> &wszString ) { Push( NStr::ToMBCS( nstl::wstring(wszString) ).c_str() ); return *this; }

  StreamBuffer &operator<<( const bool bValue ) { Push( valueFormatter.Format( bValue ) ); return *this; }

  StreamBuffer &operator<<( const char cValue ) { Push( valueFormatter.Format( cValue ) ); return *this; }

  StreamBuffer &operator<<( const short nValue ) { Push( valueFormatter.Format( nValue ) ); return *this; }
  StreamBuffer &operator<<( const unsigned short nValue ) { Push( valueFormatter.Format( nValue ) ); return *this; }

  StreamBuffer &operator<<( const int nValue ) { Push( valueFormatter.Format( (long)nValue ) ); return *this; }
  StreamBuffer &operator<<( const unsigned int nValue ) { Push( valueFormatter.Format( (unsigned long)nValue ) ); return *this; }
  StreamBuffer &operator<<( const long nValue ) { Push( valueFormatter.Format( nValue ) ); return *this; }
  StreamBuffer &operator<<( const unsigned long nValue ) { Push( valueFormatter.Format( nValue ) ); return *this; }
  StreamBuffer &operator<<( const long long nValue ) { Push( valueFormatter.Format( nValue ) ); return *this; }
  StreamBuffer &operator<<( const unsigned long long nValue ) { Push( valueFormatter.Format( nValue ) ); return *this; }

  StreamBuffer &operator<<( const float fValue ) { Push( valueFormatter.Format( fValue ) ); return *this; }
  StreamBuffer &operator<<( const double fValue ) { Push( valueFormatter.Format( fValue ) ); return *this; }
  StreamBuffer &operator<<( const long double fValue ) { Push( valueFormatter.Format( fValue ) ); return *this; }

  StreamBuffer &operator<<( const void *pValue ) { Push( valueFormatter.Format( pValue ) ); return *this; }

private:
  CChannelLogger &      logger;
  const SEntryInfo &    entryInfo;
  const char *          textStart;
  NStr::CStrFormatter   valueFormatter;

  void Push( const char * str ) {
    Buffer().WriteZ( str );
    Buffer().Finish();
  }

  void WriteHeader( unsigned headerFormat );
};

} //namespace NLogg

inline NLogg::StreamBuffer &endl( NLogg::StreamBuffer & buffer ) { return buffer; }

#endif //LOGSTREAMBUFFER_H_INCLUDED
