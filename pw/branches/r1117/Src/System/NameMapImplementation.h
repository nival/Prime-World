#ifndef NAMEMAPIMPLEMENTATION_H_INCLUDED
#define NAMEMAPIMPLEMENTATION_H_INCLUDED

#ifndef INCLUDE_NAMEMAPIMPLEMENTATION_H_MACRO
#error This file should be included from NameMap.h only
#endif //INCLUDE_NAMEMAPIMPLEMENTATION_H_MACRO

namespace Implementation {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pre-defined variant types
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using Meta::Type2Type;

inline VariantType::Enum GetVariantTypeImpl( Type2Type< bool > ) { return VariantType::Bool; }
inline VariantType::Enum GetVariantTypeImpl( Type2Type< int >) { return VariantType::Int; }
inline VariantType::Enum GetVariantTypeImpl( Type2Type< float > ) { return VariantType::Float; }
inline VariantType::Enum GetVariantTypeImpl( Type2Type< string > ) { return VariantType::String; }
inline VariantType::Enum GetVariantTypeImpl( Type2Type< char * > ) { return VariantType::String; }
inline VariantType::Enum GetVariantTypeImpl( Type2Type< wstring > ) { return VariantType::WString; }
inline VariantType::Enum GetVariantTypeImpl( Type2Type< wchar_t * > ) { return VariantType::WString; }
inline VariantType::Enum GetVariantTypeImpl( Type2Type< WStringListT > ) { return VariantType::WStringList; }


template <typename T>
Type2Type<T> GetRealType( Type2Type<T> )
{
  return Type2Type<T>();
}

template <typename T>
inline VariantType::Enum GetVariantType()
{
  return GetVariantTypeImpl( GetRealType( Type2Type<T>() ) ); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variant type-casting constrictions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//We DO NOT define any implicit value-text converters

template < typename TTo, typename TFrom >
inline TTo ConvertTypeImpl( const TFrom &, Type2Type<TTo> )
{
  NI_ALWAYS_ASSERT( "These types cannot be casted!" );
  return TTo();
}

inline const wchar_t * ConvertTypeImpl( const wstring & str, Type2Type<const wchar_t *> )
{
  return str.c_str();
}

inline const char * ConvertTypeImpl( const string & str, Type2Type<const char *> )
{
  return str.c_str();
}


inline wstring ConvertTypeImpl( const wchar_t * const & str, Type2Type<wstring> )
{
  return str;
}


inline string ConvertTypeImpl( const char * const & str, Type2Type<string> )
{
  return str;
}


inline int ConvertTypeImpl( const float & x, Type2Type<int> )
{
  return (int)x;
}


inline float ConvertTypeImpl( const int & i, Type2Type<float> )
{
  return (float)i;
}

inline bool ConvertTypeImpl( const bool & x, Type2Type<bool> ) { return x; }
inline int ConvertTypeImpl( const int & x, Type2Type<int> ) { return x; }
inline float ConvertTypeImpl( const float & x, Type2Type<float> ) { return x; }
inline wstring ConvertTypeImpl( const wstring & x, Type2Type<wstring> ) { return x; }
inline string ConvertTypeImpl( const string & x, Type2Type<string> ) { return x; }
inline const char * ConvertTypeImpl( const char *x, Type2Type<const char *> ) { return x; }
inline const wchar_t * ConvertTypeImpl( const wchar_t *x, Type2Type<const wchar_t *> ) { return x; }


template < typename TTo, typename TFrom >
inline TTo ConvertToReal( const TFrom &from, Type2Type<TTo> )
{
  return from;
}

template < typename TTo >
inline const TTo &ConvertToReal( const TTo &from, Type2Type<TTo> )
{
  return from;
}


template < typename TTo, typename TFrom >
inline TTo ConvertType( const TFrom &from )
{
  return ConvertTypeImpl( ConvertToReal( from, GetRealType(Type2Type<TFrom>()) ), Type2Type<TTo>() );
}


} //namespace Implementation

#endif //NAMEMAPIMPLEMENTATION_H_INCLUDED
