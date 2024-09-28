#ifndef STRCONVERT_H_INCLUDED
#define STRCONVERT_H_INCLUDED

//TODO: iA: templatize both char and wchar_t versions

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NStr
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ToWString - format wstring to buffer
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
int ToWString( const T& value, wchar_t *pBuffer, const int bufferLen );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
int ToWString<int>( const int& value, wchar_t *pBuffer, const int bufferLen );

template<>
int ToWString<unsigned int>( const unsigned int& value, wchar_t *pBuffer, const int bufferLen );

template<>
int ToWString<float>( const float& value, wchar_t *pBuffer, const int bufferLen );

template<>
int ToWString<char const *>( char const* const& value, wchar_t *pBuffer, const int bufferLen );

template<>
int ToWString<wchar_t const*>( wchar_t const* const& value, wchar_t *pBuffer, const int bufferLen );

template<>
int ToWString<CVec2>( const CVec2& value, wchar_t *pBuffer, const int bufferLen );

template<>
int ToWString<CVec3>( const CVec3& value, wchar_t *pBuffer, const int bufferLen );

template<>
int ToWString<CVec4>( const CVec4& value, wchar_t *pBuffer, const int bufferLen );

template<>
int ToWString<CQuat>( const CQuat& value, wchar_t *pBuffer, const int bufferLen );

template<>
int ToWString<bool>( const bool& value, wchar_t *pBuffer, const int bufferLen );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert - convert char * to differrent types and vice versa
// If it returns const char *, then it is STATIC buffer
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Format value to const char *

template < typename T >
const char * Convert( const T & value );

template <>
inline const char * Convert < const char * > ( const char * const & value ) { return value; }

template <>
inline const char * Convert<string>( const string & str ) { return str.c_str(); }

template <>
const char * Convert < bool > ( const bool & value );

template <>
const char * Convert < int > ( const int & value );

template <>
const char * Convert < float > ( const float & value );

template <>
const char * Convert < double > ( const double & value );

template <>
const char * Convert < CTPoint < int > > ( const CTPoint < int > & value );

template <>
const char * Convert < CTRect < int > > ( const CTRect < int > & value );

template <>
const char * Convert < CVec2 > ( const CVec2 & value );

template <>
const char * Convert < CVec3 > ( const CVec3 & value );

template <>
const char * Convert < CVec4 > ( const CVec4 & value );

template <>
const char * Convert < CQuat > ( const CQuat & value );

//parse const char * to value
template < typename T >
T Convert ( const char * str );

template <>
inline const char * Convert < const char * > ( const char * value ) { return value; }

template <>
inline string Convert < string > ( const char * str ) { return str; }

template <>
bool Convert < bool > ( const char * str );

template <>
int Convert < int > ( const char * str );

template <>
float Convert < float > ( const char * str );

template <>
double Convert < double > ( const char * str );

template <>
CTPoint < int > Convert < CTPoint < int > > ( const char * str );

template <>
CTRect < int > Convert < CTRect < int > > ( const char * str );

template <>
CVec2 Convert < CVec2 > ( const char * str );

template <>
CVec3 Convert < CVec3 > ( const char * str );

template <>
CVec4 Convert < CVec4 > ( const char * str );

template <>
CQuat Convert < CQuat > ( const char * str );

template <>
wstring Convert < wstring > ( const char * str );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //namespace NStr

#endif //STRCONVERT_H_INCLUDED
