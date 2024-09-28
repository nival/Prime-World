#ifndef STRFORMATTER_H__
#define STRFORMATTER_H__

namespace NStr
{

class CStrFormatter
{
  enum { FORMATTER_LENGTH = 32 };
  char szBuffer[FORMATTER_LENGTH];

  bool bBoolAlpha;
  bool bHexInteger;
  bool bSciFloat;

public:
  CStrFormatter() : bBoolAlpha( true ), bHexInteger( false ), bSciFloat( false ) {}

  const char *Format( const bool bValue );

  const char *Format( const char cValue );

  const char *Format( const short nValue );
  const char *Format( const unsigned short nValue );

  const char *Format( const long nValue );
  const char *Format( const unsigned long nValue );
  const char *Format( const long long nValue );
  const char *Format( const unsigned long long nValue );

  const char *Format( const float fValue );
  const char *Format( const double fValue );
  const char *Format( const long double fValue );

  const char *Format( const void *pValue );

  const char *GetBuffer() const { return szBuffer; }
};

} //namespace NStr

#endif //STRFORMATTER_H__
