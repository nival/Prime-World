#pragma once

#include "../System/AutoPtr.h"
#include "../System/Ring.h"
#include "../System/Commands.h"

namespace Render
{
  _interface IDebugRender;
}

namespace NDebug
{ 

class DebugUser;
typedef void ( DebugUser::* callback_t )( Render::IDebugRender* pRender ) const;

_interface ICondintion
{
  virtual bool IsTrue( DebugUser const* pObject ) const = 0;
};

class AlwaysChecker : public ICondintion
{
public:
  virtual bool IsTrue( DebugUser const* pObject ) const { return true; }
};

inline NDebug::ICondintion* CreateAlwaysChecker()
{
  return new AlwaysChecker();
}

template<typename T>
class VarValueChecker : public ICondintion
{
  T const*   pValue;
  T const    desiredValue;
  const bool equal;
  VarValueChecker( VarValueChecker const& );
  VarValueChecker& operator = (VarValueChecker const&) ;
public:
  explicit VarValueChecker(T const* pValue, T const desiredValue, bool equal) : pValue(pValue), desiredValue(desiredValue), equal(equal) {} 
  virtual bool IsTrue( DebugUser const* /*pObject*/ ) const { return equal == (desiredValue == *pValue); }
};

template< typename T >
NDebug::ICondintion* CreateValueChecker( T const* pVar, T value, bool equal)
{
  return new VarValueChecker<T>(pVar, value, equal);
}

template<typename T>
class VarValueRangeChecker : public ICondintion
{
  T const* pValue;
  T const  minValue;
  T const  maxValue;
  VarValueRangeChecker( VarValueRangeChecker const& );
  VarValueRangeChecker& operator = (VarValueRangeChecker const&) ;
public:
  explicit VarValueRangeChecker(T const* pValue, T const minValue, T const maxValue) : pValue(pValue), minValue(minValue), maxValue(maxValue) {} 
  virtual bool IsTrue( DebugUser const* /*pObject*/ ) const { return  minValue <= *pValue && *pValue <= maxValue; }
};

template< typename T >
NDebug::ICondintion* CreateValueRangeChecker( T const* pVar, T minValue, T maxValue)
{
  return new VarValueRangeChecker<T>(pVar, minValue, maxValue);
}

namespace VariantHelpers
{
  template<typename T>
  inline void ExtractValue( NGlobal::VariantValue const&, T&)
  {
    int compile_error_type_doesnt_fit[0];
    compile_error_type_doesnt_fit;
  }

  inline void ExtractValue( NGlobal::VariantValue const& var, float& result ) { result = var.GetFloat(); }
  inline void ExtractValue( NGlobal::VariantValue const& var, int& result) { result = static_cast<int>( var.GetInt64() ); }
  inline void ExtractValue( NGlobal::VariantValue const& var, unsigned int& result ) { result = static_cast<unsigned int>( var.GetUInt64() ); }
  inline void ExtractValue( NGlobal::VariantValue const& var, long& result) { result = static_cast<long>( var.GetInt64() ); }
  inline void ExtractValue( NGlobal::VariantValue const& var, unsigned long& result ) { result = static_cast<unsigned long>( var.GetUInt64() ); } 
  inline void ExtractValue( NGlobal::VariantValue const& var, wstring& result ) { result = var.GetString(); }   

  template<typename T>
  struct ValueHolder
  {
    typedef T type;
    static type Construct( T const& value ) { return value; }
  };

  template<>
  struct ValueHolder<string>
  {
    typedef wstring type;
    static wstring Construct( string const& value ) { return NStr::StrFmtW(L"%S", value.c_str()); }
  };

  template<>
  struct ValueHolder<char const*>
  {
    typedef wstring type;
    static wstring Construct( char const* value ) { return NStr::StrFmtW(L"%S", value); }
  };

  template<>
  struct ValueHolder<wchar_t const*>
  {
    typedef wstring type;
    static wstring Construct( wchar_t const* value ) { return wstring(value); }
  };
};

template<typename T>
class ConsoleVarValueChecker : public ICondintion
{
  string const                                  name;
  typename VariantHelpers::ValueHolder<T>::type desiredValue;
  bool const                                    equal;

  ConsoleVarValueChecker( ConsoleVarValueChecker const& );
  ConsoleVarValueChecker& operator = (ConsoleVarValueChecker const&) ;
public:
  explicit ConsoleVarValueChecker(string const& name, T const desiredValue, bool equal) 
    : name(name)
    , desiredValue( VariantHelpers::ValueHolder<T>::Construct(desiredValue) )
    , equal(equal) 
  {
  }

  virtual bool IsTrue( DebugUser const* /*pObject*/ ) const 
  {
    typename VariantHelpers::ValueHolder<T>::type value;
    VariantHelpers::ExtractValue( NGlobal::GetVar( name ), value);

    return equal == ( desiredValue == value ); 
  }
};

template< typename T >
NDebug::ICondintion* CreateConsoleValueChecker( string const& name, T value, bool equal)
{
  return new ConsoleVarValueChecker<T>(name, value, equal);
}

template<typename T>
class ConsoleVarValueRangeChecker : public ICondintion
{
  string const                                  name;
  typename VariantHelpers::ValueHolder<T>::type minValue;
  typename VariantHelpers::ValueHolder<T>::type maxValue;

  ConsoleVarValueRangeChecker( ConsoleVarValueRangeChecker const& );
  ConsoleVarValueRangeChecker& operator = (ConsoleVarValueRangeChecker const&) ;
public:
  explicit ConsoleVarValueRangeChecker(string const& name, T minValue, T maxValue) 
    : name(name)
    , minValue( VariantHelpers::ValueHolder<T>::Construct(minValue) )
    , maxValue( VariantHelpers::ValueHolder<T>::Construct(maxValue) ) 
  {
  }

  virtual bool IsTrue( DebugUser const* /*pObject*/ ) const 
  {
    typename VariantHelpers::ValueHolder<T>::type value;
    VariantHelpers::ExtractValue( NGlobal::GetVar( name ), value);

    return minValue <= value && value <= maxValue; 
  }
};

template< typename T >
NDebug::ICondintion* CreateConsoleValueRangeChecker( string const& name, T minValue, T maxValue)
{
  return new ConsoleVarValueRangeChecker<T>(name, minValue, maxValue);
}

template< typename T>
class MemFunCondition : public ICondintion
{
public:
  typedef bool (T::* mem_fun_t)() const;
  typedef T concrete_type_t;

  explicit MemFunCondition( mem_fun_t pCallback ) : pCallback( pCallback ) {}

  virtual bool IsTrue( DebugUser const* pObject ) const 
  {
    if( pObject && pCallback )
      return ( (dynamic_cast<concrete_type_t const*>(pObject))->*pCallback)();

    return false;
  }
private:
  mem_fun_t pCallback;
};

template< typename T >
NDebug::ICondintion* CreateMemFunChecker( bool (T::* pChecker)() const )
{
  return new MemFunCondition<T>( pChecker );
}

template< typename T>
class FunCondition : public ICondintion
{
public:
  typedef bool (* fun_t )(T* const);
  typedef T user_type_t;

  explicit FunCondition( fun_t pFunction ) : pFunction(pFunction) {}

  virtual bool IsTrue( DebugUser const* pObject ) const 
  {
    user_type_t const* pConcrete = dynamic_cast<user_type_t const*>( pObject );
    if( pConcrete && pFunction )
      return pFunction(pConcrete);

    return false;
  }

private:
  fun_t pFunction;
};

template< typename T >
NDebug::ICondintion* CreateFunChecker( bool (* pFunction )(T* const) )
{
  return new FunCondition<T>( pFunction );
}

struct CallbackDesc
{
  AutoPtr<ICondintion> pCondition;
  callback_t           pCallback; 

  bool IsValid() const { return pCondition && pCallback; }
};

struct DebugTableEntry
{
  enum Type { Callback, Table, Terminator};

  Type                   type;
  CallbackDesc           callback; 
  DebugTableEntry const* pTable;
};

}; // namespace NDebug