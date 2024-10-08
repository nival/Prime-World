
#ifndef _ASSERTS_H_
#define _ASSERTS_H_

#include "LogLevel.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ASSERT macros.
// For showing calling stack when errors occur in major functions.
// Meant to be enabled in release builds.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DO_ASSERT
#define NI_ASSERT( expr, user_text ) NI_FORCE_ASSERT( expr, NLogg::LEVEL_ASSERT, #expr, user_text )
#define NI_ALWAYS_ASSERT( user_text ) NI_FORCE_ALWAYS_ASSERT( NLogg::LEVEL_ASSERT, user_text )
#define NI_VERIFY( expr, user_text, statement ) { const bool bCheck = (expr); NI_FORCE_ASSERT( bCheck, NLogg::LEVEL_ASSERT, #expr, user_text ); if ( !bCheck ) { statement; } }
#define NI_VERIFY_NO_RET( expr, user_text ) NI_ASSERT( (expr), user_text )

#define NI_ASSERT_TRACE( expr, user_text ) NI_ASSERT( expr, user_text )
#define NI_ALWAYS_ASSERT_TRACE( user_text ) NI_ALWAYS_ASSERT( user_text )
#define NI_VERIFY_TRACE( expr, user_text, statement ) NI_VERIFY( expr, user_text, statement )

#define NI_DATA_ASSERT( expr, user_text ) NI_FORCE_ASSERT( expr, NLogg::LEVEL_ASSERT, user_text, #expr )
#define NI_DATA_ALWAYS_ASSERT( user_text ) NI_FORCE_ALWAYS_ASSERT( NLogg::LEVEL_ASSERT, user_text )
#define NI_DATA_VERIFY( expr, user_text, statement ) { const bool bCheck = (expr); NI_FORCE_ASSERT( bCheck, NLogg::LEVEL_ASSERT, user_text, #expr ); if ( !bCheck ) { statement; } }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#else

#ifdef WIN32
  #pragma warning( disable: 4616 )
  #pragma warning( disable: 4189 )
#endif



#define NI_ASSERT( expr, user_text ) ((void)0);
#define NI_ALWAYS_ASSERT( user_text ) ((void)0);
#define NI_VERIFY( expr, user_text, statement ) { const bool bCheck = (expr); if ( !bCheck ) { statement; } }
#define NI_VERIFY_NO_RET( expr, user_text ) (expr)

#define NI_ASSERT_TRACE( expr, user_text ) { const bool bCheck = (expr); if ( !bCheck ) { TRACE_MSG( user_text ); } }
#define NI_ALWAYS_ASSERT_TRACE( user_text ) { TRACE_MSG( user_text ); }
#define NI_VERIFY_TRACE( expr, user_text, statement ) { const bool bCheck = (expr); if ( !bCheck ) { TRACE_MSG( user_text ); statement; } }

#define NI_DATA_ASSERT( expr, user_text ) ((void)0);
#define NI_DATA_ALWAYS_ASSERT( user_text ) ((void)0);
#define NI_DATA_VERIFY( expr, user_text, statement ) { const bool bCheck = (expr); if ( !bCheck ) { statement; } }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //_DO_ASSERT
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
  #define NI_STOP() { __debugbreak(); }
#else
  #define NI_STOP() { asm volatile ("int3;"); }
#endif


inline bool NiIsDebuggerPresent();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main ASSERT macros
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EnableDebugAsserts();
void DisableDebugAsserts();

bool TraceAssertMsg( NLogg::ELevel level, const char* msg, const char* user_text, const char *szFileName, const unsigned long dwLine );

#define NI_FORCE_ASSERT( expr, level, msg, user_text )	 \
{	\
  if ( !( expr ) )	\
  {	\
  bool needBreak = TraceAssertMsg( level, msg, user_text, __FILE__, __LINE__ ); \
  static bool ignore = false; \
  const bool *pIgnore = &ignore;  \
  if ( ( !ignore || !*pIgnore ) && needBreak ) \
    NI_STOP()  \
  } \
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NI_FORCE_ALWAYS_ASSERT( level, user_text )	 \
{	\
  bool needBreak = TraceAssertMsg( level, 0, user_text, __FILE__, __LINE__ ); \
  static bool ignore = false; \
  const bool *pIgnore = &ignore;  \
  if ( ( !ignore || !*pIgnore ) && needBreak) \
    NI_STOP()  \
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TraceMsg( const char * msg );

#define TRACE_MSG( user_text )  \
  TraceMsg( user_text );


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// static assert
template<bool>
struct StaticAssert;

template<>
struct StaticAssert<true> {};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NI_STATIC_ASSERT( expr, msg )	\
{	\
    StaticAssert<((expr) != 0)> ERROR_##msg; (void)ERROR_##msg;	\
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TOut, class TPtr>
inline TOut static_cast_ptr( TPtr &ptr )
{
    return static_cast<TOut>( ptr.GetPtr() );
}

template <class TOut, class T>
inline TOut static_cast_ptr(T *ptr)
{
  return static_cast<TOut>(ptr);
}

template <class TOut, class TPtr>
inline TOut dynamic_cast_ptr(TPtr &ptr)
{
  return dynamic_cast<TOut>( ptr.GetPtr() );
}

template <class TOut, class T>
inline TOut dynamic_cast_ptr(T *ptr)
{
  return dynamic_cast<TOut>(ptr);
}

// checked_cast, the same as static_cast, but with run-time type checking
#ifdef _DO_ASSERT
template <class TOut, class TIn>
inline TOut checked_cast( TIn obj )
{
    NI_ASSERT( !((obj != 0) && (dynamic_cast<TOut>(obj) == 0)), "Wrong checked cast" );
    return static_cast<TOut>( obj );
}
template <class TOut, class TIn>
inline TOut checked_cast_ptr( TIn ptr )
{
    NI_ASSERT( !((ptr.GetPtr() != 0) && (dynamic_cast<TOut>(ptr.GetPtr()) == 0)), "Wrong checked cast" );
    return static_cast<TOut>( ptr.GetPtr() );
}
#else
#define checked_cast static_cast
#define checked_cast_ptr static_cast_ptr
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT( expr ) NI_ASSERT( expr, #expr )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

