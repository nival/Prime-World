#ifndef FOUNDATION_ENUMTOSTRING_H_INCLUDED
#define FOUNDATION_ENUMTOSTRING_H_INCLUDED


#define NI_ENUM_DECL( enumType ) const char * ToString( enumType value, const char * defaultString ); const char * ToString( enumType value );

#define NI_ENUM_BEGIN( enumType ) \
  const char * ToString( enumType value, const char * defaultString ); \
  const char * ToString( enumType value ) { return ToString( value, "<Unknown>" ); } \
  const char * ToString( enumType value, const char * defaultString ) { switch ( value ) { default: return defaultString;

#define NI_ENUM_ITEM( value ) case value: return #value;

#define NI_ENUM_END }}

#define NI_ENUM_BEGIN_NM( nmspace, enumType ) namespace nmspace { NI_ENUM_BEGIN( enumType )
#define NI_ENUM_END_NM }}}

#define NI_ENUM_DECL_STD  NI_ENUM_DECL( Enum )
#define NI_ENUM_BEGIN_STD( nmspace )  namespace nmspace { NI_ENUM_BEGIN( Enum )
#define NI_ENUM_END_STD  NI_ENUM_END_NM

#endif //FOUNDATION_ENUMTOSTRING_H_INCLUDED
