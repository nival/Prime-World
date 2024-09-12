#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "AutoPtr.h"
#include "RefCntObject.h"
#include "ProfileManager.h"

namespace NProfile
{
  enum EProfileFolder;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EStorageClass
{
  STORAGE_DONT_CARE  = -1,
  STORAGE_NONE      = 0,
  STORAGE_GLOBAL    = 1,
  STORAGE_USER      = 2,
  STORAGE_PLAYER    = 3,
  STORAGE_SAVE      = 4,
};

#ifndef NV_WIN_PLATFORM
float _wtof( const wchar_t *str);
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NGlobal
{

  const wstring DEFAULT_COMMAND_CONTEXT = L"global";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class VariantValue
{
  //this is so called non cached VARIANT. It has cheap Set with expensive Get with type miss. It tuned not for conversion but for storage.
  // there is also a cached VARIANT where is conversion of data is done once only, which is tuned for data conversion.
  enum Type
  {
    UNDEF  = 0,
    FLOAT  = 1 << 0,
    STRING = 1 << 1,
    INT    = 1 << 2,
    UINT   = 1 << 3
  };

  ZDATA
    float           fVal;
    mutable wstring szVal;
    int64           nSIntVal;
    uint64          nUIntVal;
    Type            type;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&fVal); f.Add(3,&szVal); f.Add(4,&nSIntVal); f.Add(5,&nUIntVal); f.Add(6,&type); return 0; }

private:
  //
  void InitVars()
  {
    fVal     = 0.0f;
    szVal    = L"";
    nSIntVal = 0;
    nUIntVal = 0;
    type     = UNDEF;
  }

public:
  VariantValue(){InitVars();}
  VariantValue( float _fVal )            {InitVars(); fVal = _fVal;                                 type = FLOAT ;}
  VariantValue( int   _n )               {InitVars(); nSIntVal = _n;                                type = INT   ;}
  VariantValue( unsigned int _n )        {InitVars(); nUIntVal = _n;                                type = UINT  ;}
  VariantValue( int64 _n )               {InitVars(); nSIntVal = _n;                                type = INT   ;}
  VariantValue( uint64 _n )              {InitVars(); nUIntVal = _n;                                type = UINT  ;}
  VariantValue( const wstring &_szVal )  {InitVars(); szVal = _szVal;                               type = STRING;}
  VariantValue( const wchar_t *pszVal )  {InitVars(); szVal = pszVal;                               type = STRING;}
#if defined( NV_WIN_PLATFORM )
  VariantValue( const string  &_szVal )  {InitVars(); szVal = NStr::StrFmtW(L"%S", _szVal.c_str()); type = STRING;}
  VariantValue( const char    *pszVal )  {InitVars(); szVal = NStr::StrFmtW(L"%S", pszVal);         type = STRING;}
#elif defined( NV_LINUX_PLATFORM )
  VariantValue( const string  &_szVal )  {InitVars(); szVal = NStr::StrFmtW(L"%s", _szVal.c_str()); type = STRING;}
  VariantValue( const char    *pszVal )  {InitVars(); szVal = NStr::StrFmtW(L"%s", pszVal);         type = STRING;}
#endif

  const float GetFloat() const 
  { 
    switch(type)
    {
      case FLOAT:  return fVal;
      case INT:    return (float)(nSIntVal); 
      case UINT:   return (float)(nUIntVal);
      case STRING: return wcstod(szVal.c_str(), NULL);
      default:     break;
    }
    return fVal; 
  }
  const int64 GetInt64() const 
  { 
    switch(type)
    {
      case FLOAT:  return (int64)fVal;
      case INT:    return nSIntVal; 
      case UINT:   return nUIntVal;
      case STRING: return
#if defined( NV_WIN_PLATFORM )
                     _wcstoi64(szVal.c_str(), NULL, 10);
#elif defined( NV_LINUX_PLATFORM )
                     wcstoll(szVal.c_str(), NULL, 10);
#endif
      default:     break;
    }
    return nSIntVal; 
  }
  const uint64 GetUInt64() const 
  { 
    switch(type)
    {
      case FLOAT:  return (uint64)fVal;
      case INT:    return nSIntVal; 
      case UINT:   return nUIntVal;
      case STRING: return
#if defined( NV_WIN_PLATFORM )
                     _wcstoui64(szVal.c_str(), NULL, 10);
#elif defined( NV_LINUX_PLATFORM )
                     wcstoull(szVal.c_str(), NULL, 10);
#endif
      default:     break;
    }
    return nUIntVal; 
  }
  const wstring &GetString() const 
  {
    switch(type)
    {
      case FLOAT:  return (szVal = NStr::StrFmtW(L"%g", fVal));
      case INT:    return (szVal = NStr::StrFmtW(L"%I64d", nSIntVal)); 
      case UINT:   return (szVal = NStr::StrFmtW(L"%I64u", nUIntVal)); 
      case STRING: return szVal;
      default:     break;
    }
    return szVal; 
  }
  
private:
  template<class T>
  struct RetValConvert
  {
    typedef const T ResultType;
  };  
  
  template<class T> T GetImpl() const;
  
  static bool IsConvertibleImpl( Type toType, const VariantValue &from ); 
  
public:
  template<class T>
  const typename RetValConvert<T>::ResultType Get() const
  {
    return GetImpl<typename RetValConvert<T>::ResultType>();
  }
    
  template<class ToType>
  friend bool IsConvertible( const VariantValue &from )
  {
    const VariantValue valForTypeId( ( ToType() ) );
    return IsConvertibleImpl( valForTypeId.type, from );
  }
};

template<>
struct VariantValue::RetValConvert< wstring >
{
	typedef const wstring &ResultType;
};

template<> inline const bool VariantValue::GetImpl() const
{
	return GetInt64() != 0;
}

template<> inline const int VariantValue::GetImpl() const
{
	return GetInt64();
}

template<> inline const unsigned int VariantValue::GetImpl() const
{
	return GetUInt64();
}

template<> inline const int64 VariantValue::GetImpl() const
{
	return GetInt64();
}

template<> inline const uint64 VariantValue::GetImpl() const
{
	return GetUInt64();
}

template<> inline const float VariantValue::GetImpl() const
{
	return GetFloat();
}

template<> inline const string VariantValue::GetImpl() const
{
	return NStr::ToMBCS( GetString() );
}

template<> inline const wstring & VariantValue::GetImpl() const
{
	return GetString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class VariantVariable
{
  string szName;
  VariantValue value;
public:
  VariantVariable( const VariantVariable &var ) : szName( var.szName ), value( var.value ) {}
  VariantVariable( const string &_szName, const VariantValue &_value ) : szName( _szName ), value( _value ) {}
  VariantVariable &operator=( const VariantVariable &var ) { szName = var.szName; value = var.value; return *this; }

  const string &GetName() const { return szName; }
  const VariantValue &GetValue() const { return value; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct IVariable: public IObjectBase
{
  virtual ~IVariable() {}
  virtual VariantValue Get() = 0;
  virtual void Set( const VariantValue &val ) = 0;
  virtual void Apply() {}
  virtual bool VerifyValue( const VariantValue &val ) const { return true; } 
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T, class VerifyPred>
class TypedVariable: public IVariable, public CObjectBase, private VerifyPred
{
  OBJECT_BASIC_METHODS( TypedVariable );
public:
  TypedVariable(): pVar(0) {}
  TypedVariable(T *pVar, const VerifyPred &pred): VerifyPred(pred), pVar(pVar) {}
  virtual VariantValue Get() { NI_ASSERT(pVar != 0, ""); return VariantValue(*pVar); }
  virtual void Set( const VariantValue &val ){  NI_ASSERT(pVar != 0, ""); *pVar = val.Get<T>(); }
  virtual bool VerifyValue( const VariantValue &val ) const { return static_cast<const VerifyPred &>(*this)(val); } 

private:
  T *pVar;            
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
struct StdVerifyPred
{
  bool operator()( const VariantValue &val ) const { return IsConvertible<T>(val); }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
class MinMaxVerifyPred: StdVerifyPred<T>
{
public:
  MinMaxVerifyPred(): minValue(), maxValue() {}
  MinMaxVerifyPred( const T &minValue, const T &maxValue ): 
    minValue(minValue), maxValue(maxValue) {}

  bool operator()( const VariantValue &val ) const
  { 
    return static_cast<const StdVerifyPred<T> &>(*this)(val) &&
      val.Get<T>() >= minValue && val.Get<T>() <= maxValue; 
  }

private:
  T minValue, maxValue;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
MinMaxVerifyPred<T> MakeMinMaxVerifyPred( const T &minValue, const T &maxValue )
{
  return MinMaxVerifyPred<T>( minValue, maxValue );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
class ProxyTypedVariable: public IVariable, public CObjectBase
{
  OBJECT_BASIC_METHODS( ProxyTypedVariable );
public:
  ProxyTypedVariable(): pVar(0), proxyVal(), isSynchronized(true)  {}
  ProxyTypedVariable(T *pVar): pVar(pVar), proxyVal(*pVar), isSynchronized(true) {}
  virtual VariantValue Get() { NI_ASSERT(pVar != 0, ""); return VariantValue(isSynchronized ? *pVar : proxyVal); }
  virtual void Set( const VariantValue &val ){ NI_ASSERT(pVar != 0, ""); proxyVal = val.Get<T>(); isSynchronized = *pVar == proxyVal; }
  virtual void Apply() { NI_ASSERT(pVar != 0, "");  if( !isSynchronized ) { *pVar = proxyVal; isSynchronized = true; }  }

private:
  T *pVar;
  T proxyVal;
  bool isSynchronized;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
ProxyTypedVariable<T> *MakeVarProxy( T *pVar ) { return new ProxyTypedVariable<T>(pVar); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IContextFunctor : public IObjectBase
{
  virtual bool operator() ( const char *name, const vector<wstring> &args ) = 0;

  bool operator == ( const IContextFunctor& otherFunctor ) const
  {
    return getObjectPointer() == otherFunctor.getObjectPointer();
  }

private:
  virtual const void* getObjectPointer() const = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
class ContextFunctor : public IContextFunctor, public CObjectBase
{
  OBJECT_BASIC_METHODS( ContextFunctor );
public:
  ContextFunctor( T* _object, bool (T::*_func)( const char *name, const nstl::vector<nstl::wstring> &args ) )  :
    object(_object),
    func(_func)
  {
  }

  virtual bool operator() ( const char *name, const vector<wstring> &args )
  {
    return (object->*func)( name, args );
  }

private:
  ContextFunctor() {}

  virtual const void* getObjectPointer() const { return object; }

  T* object;
  bool (T::*func)( const char *name, const nstl::vector<nstl::wstring> &args );
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RegisterContextFunctor( const string &szID, IContextFunctor* _functor );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// handler should return false only if command execution is deferred
typedef bool (*TCmdHandler)( const char *name, const vector<wstring> &args );
typedef bool (*TCmdHandlerEx)( const char *name, const vector<wstring> &args, const wstring &ctx );
bool RegisterCmd( const string &szID, TCmdHandler pHandler );
bool RegisterCmdEx( const string &szID, TCmdHandlerEx pHandler );
bool UnregisterCmd( const string &szID );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool RegisterContextCmd( const string &szID, T* object, bool (T::*func)(const char *name, const vector<wstring> &args) )
{
  IContextFunctor* newFunctor = new ContextFunctor<T>( object, func );
  return RegisterContextFunctor( szID, newFunctor );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RegisterVar( const string &szID, CObj<IVariable> pVar, EStorageClass storage );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename VerifyPred>
bool RegisterTypedVar( const string &szID, T *pContext, EStorageClass storage, const VerifyPred &pred )
{
  return RegisterVar( szID, new TypedVariable<T, VerifyPred>(pContext, pred), storage );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
bool RegisterTypedVar( const string &szID, T *pContext, EStorageClass storage )
{
  return RegisterTypedVar( szID, pContext, storage, StdVerifyPred<T>() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool UnregisterVar( const string &szID );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const VariantValue GetVar( const string &szName, const VariantValue &defValue = VariantValue() );
void SetVar( const string &szName, const VariantValue &sValue, const EStorageClass newStorage );
void ResetVars( const EStorageClass storage );

int GetVarsByStorage( vector<VariantVariable> *pVariables, const EStorageClass storage );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RunCommand( const wstring &szCommand, const wstring &szContext = DEFAULT_COMMAND_CONTEXT );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility
const wstring &GetCommandHistory( int &index );
void MatchCommands( vector<wstring> *pRes, const wstring &match );
bool IsCommand( const string &szName );
bool IsCommandRegistred( const string &szName );
void PrintVarWithValue( const string &szName );
void PrintVarsWithValueByPrefix( const string &szPrefix );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int    g_commandLineArgc;
extern char **g_commandLineArgv;


} // name space

/////////////////////////////////////////////////////////////////////////////
#define STATIC_CTOR_BEGIN()                                                 \
namespace { static struct BOOST_JOIN(StaticConstructorImpl, __LINE__) {     \
  BOOST_JOIN(StaticConstructorImpl, __LINE__)()                             \
/////////////////////////////////////////////////////////////////////////////
#define STATIC_CTOR_END()                                                   \
} BOOST_JOIN(registerStaticConstructorImpl, __LINE__) ; }                   \
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
#define REGISTER_CMD( command, function )                                   \
  STATIC_CTOR_BEGIN() {                                                     \
    NGlobal::RegisterCmd( #command , function );                            \
  } STATIC_CTOR_END()                                                       \
/////////////////////////////////////////////////////////////////////////////
#define REGISTER_CMD_EX( command, function )                                   \
  STATIC_CTOR_BEGIN() {                                                     \
  NGlobal::RegisterCmdEx( #command , function );                            \
} STATIC_CTOR_END()                                                       \
/////////////////////////////////////////////////////////////////////////////
#define REGISTER_VAR( name, variable, storage )                             \
  STATIC_CTOR_BEGIN() {                                                     \
    NGlobal::RegisterTypedVar( name, &variable, storage );                  \
  } STATIC_CTOR_END()                                                       \
/////////////////////////////////////////////////////////////////////////////
#define REGISTER_VAR_INTERFACE( name, variable, storage )                   \
  STATIC_CTOR_BEGIN() {                                                     \
    NGlobal::RegisterVar( name, variable, storage );                        \
  } STATIC_CTOR_END()                                                       \
/////////////////////////////////////////////////////////////////////////////
#define REGISTER_VAR_PRED( name, variable, storage, pred )                  \
  STATIC_CTOR_BEGIN() {                                                     \
    NGlobal::RegisterTypedVar( name, &variable, storage, pred );            \
  } STATIC_CTOR_END()                                                       \


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Uncomment USE_DEVELOPER_COMMANDS to use developers commands even in shipping build
//#define USE_DEVELOPER_COMMANDS
#if !defined( _SHIPPING ) || defined( _RELEASE ) || defined( USE_DEVELOPER_COMMANDS )
#define REGISTER_DEV_CMD REGISTER_CMD
#define REGISTER_DEV_VAR REGISTER_VAR
#define REGISTER_DEV_VAR_INTERFACE REGISTER_VAR_INTERFACE
#define DEV_VAR_STATIC static 
#define DEFINE_DEV_VAR(_var, _default_val, _name, _storage) static int _var=_default_val; \
                                                                REGISTER_VAR(_name, _var, _storage)
#else
#define REGISTER_DEV_CMD( command, function ) ;
#define REGISTER_DEV_VAR( name, variable, storage ) ;
#define REGISTER_DEV_VAR_INTERFACE ;
#define DEV_VAR_STATIC const static 
#define DEFINE_DEV_VAR(_var, _default_val, _name, _storage) namespace { enum {_var=_default_val}; }
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

