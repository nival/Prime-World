#ifndef NAMEMAP_H_INCLUDED
#define NAMEMAP_H_INCLUDED



namespace Loki //http://en.wikipedia.org/wiki/Loki_(C%2B%2B)
{
  template <class U> struct UnConst
  {
      typedef U Result;
      enum { isConst = 0 };
  };

  template <class U> struct UnConst<const U>
  {
      typedef U Result;
      enum { isConst = 1 };
  };

  template <class U> struct UnConst<const U&>
  {
      typedef U& Result;
      enum { isConst = 1 };
  }; 
  
  template <class U> struct ReferenceTraits
  {
      enum { result = false };
      typedef U ReferredType;
  };
  
  template <class U> struct ReferenceTraits<U&>
  {
      enum { result = true };
      typedef U ReferredType;
  };
}


namespace NNameMap
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace VariantType
{
  enum Enum
  {
    None,
    Bool,
    Int,
    Float,
    String,
    WString,
    WStringList
  };
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef list<wstring>  WStringListT;


#ifndef INCLUDE_NAMEMAPIMPLEMENTATION_H_MACRO
#define INCLUDE_NAMEMAPIMPLEMENTATION_H_MACRO
#endif
#include "NameMapImplementation.h"
#undef INCLUDE_NAMEMAPIMPLEMENTATION_H_MACRO



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ReadonlyVariant : public CObjectBase
{
  OBJECT_BASIC_METHODS( ReadonlyVariant )

public:
  ReadonlyVariant() {}

  virtual VariantType::Enum GetType() const { return VariantType::None; }

  virtual bool              IsReadonly() const { return true; }

  virtual bool              GetBool() const { return false; }
  virtual int               GetInt() const { return 0; }
  virtual float             GetFloat() const { return 0.0f; }
  virtual const char *      GetString() const { return 0; }
  virtual const wchar_t *   GetWString() const { return 0; }
  virtual const WStringListT & GetWStringList() const { static WStringListT dumb; return dumb; }

  //format is [[<leading-symbol>]<length>[.[<leading-symbol>]<decimal>]]
  int                       Format( wchar_t * buffer, int size, const wchar_t * format );

  template <size_t BufferSize>
  int                       Format( wchar_t (& buffer)[BufferSize], const wchar_t * format ) { return Format( buffer, BufferSize, format ); }

  wstring                   Format( const wchar_t * format ) { wchar_t buf[256]; Format( buf, format ); return buf; }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Variant : public ReadonlyVariant
{
  OBJECT_BASIC_METHODS(Variant)

public:
  Variant() {}

  virtual bool              IsReadonly() const { return false; }

  virtual void              SetBool( bool value ) { }
  virtual void              SetInt( int value ) { }
  virtual void              SetFloat( float value ) { }
  virtual void              SetString( const char * value ) { }
  virtual void              SetWString( const wchar_t * value ) { }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
class VariableVariant : public Variant
{
public:
  VariableVariant( T & _valueRef, bool _readonly ) : valueRef( _valueRef ), readonly( _readonly ) { }

  virtual VariantType::Enum GetType() const       { return Implementation::GetVariantType<T>(); }

  virtual bool              IsReadonly() const    { return readonly; }

  virtual bool              GetBool() const       { return Implementation::ConvertType < bool, T>             ( valueRef ); }
  virtual int               GetInt() const        { return Implementation::ConvertType < int, T>              ( valueRef ); }
  virtual float             GetFloat() const      { return Implementation::ConvertType < float, T>            ( valueRef ); }
  virtual const char *      GetString() const     { return Implementation::ConvertType < const char *, T>     ( valueRef ); }
  virtual const wchar_t *   GetWString() const    { return Implementation::ConvertType < const wchar_t *, T>  ( valueRef ); }

  virtual void              SetBool( bool value )                 { if(!readonly) valueRef = Implementation::ConvertType < T, bool >            ( value ); }
  virtual void              SetInt( int value )                   { if(!readonly) valueRef = Implementation::ConvertType < T, float >           ( value ); }
  virtual void              SetFloat( float value )               { if(!readonly) valueRef = Implementation::ConvertType < T, int >             ( value ); }
  virtual void              SetString( const char * value )       { if(!readonly) valueRef = Implementation::ConvertType < T, const char * >    ( value ); }
  virtual void              SetWString( const wchar_t * value )   { if(!readonly) valueRef = Implementation::ConvertType < T, const wchar_t * > ( value ); }

protected:
  T & valueRef;
  bool readonly;

private:
  void operator = (VariableVariant &);
};

template <typename T>
VariableVariant<T> * CreateVariableVariant( T & valueRef, bool readonly )
{
  return new VariableVariant<T> ( valueRef, readonly );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template < class TObject, typename TRetVal >
class FunctionVariant : public Variant
{
public:
  typedef typename Loki::ReferenceTraits< typename Loki::UnConst<TRetVal>::Result >::ReferredType T;
  typedef TRetVal (TObject::*TGetterFunc)() const;
  typedef void (TObject::*TSetterFunc)( TRetVal value );
  
  FunctionVariant( TObject * _pOwner, TGetterFunc _getter, TSetterFunc _setter ) : pOwner( _pOwner ), getter( _getter ), setter( _setter ) { }

  virtual VariantType::Enum GetType() const { return Implementation::GetVariantType<T>(); }

  virtual bool              IsReadonly() const { return setter ? false : true; }

  virtual bool              GetBool() const { return getter ? Implementation::ConvertType < bool, T > ( (pOwner->*getter)() ) : 0; }
  virtual int               GetInt() const { return getter ? Implementation::ConvertType < int, T > ( (pOwner->*getter)() ) : 0; }
  virtual float             GetFloat() const { return getter ? Implementation::ConvertType < float, T > ( (pOwner->*getter) () ) : 0.0f; }
  virtual const char *      GetString() const { return getter ? Implementation::ConvertType < const char *, T > ( (pOwner->*getter)() ) : ""; }
  virtual const wchar_t *   GetWString() const { return getter ? Implementation::ConvertType < const wchar_t *, T > ( (pOwner->*getter)() ) : L""; }

  virtual void              SetBool( bool value ) { if(setter) (pOwner->*setter) ( Implementation::ConvertType < T, bool > ( value ) ); }
  virtual void              SetInt( int value ) { if(setter) (pOwner->*setter) ( Implementation::ConvertType < T, int > ( value ) ); }
  virtual void              SetFloat( float value ) { if(setter) (pOwner->*setter) ( Implementation::ConvertType < T, float > ( value ) ); }
  virtual void              SetString( const char * value ) { if(setter) (pOwner->*setter) ( Implementation::ConvertType< T, const char * > ( value ) ); }
  virtual void              SetWString( const wchar_t * value ) { if(setter) (pOwner->*setter) ( Implementation::ConvertType< T, const wchar_t * > ( value ) ); }

protected:
  TObject * pOwner;
  TGetterFunc getter;
  TSetterFunc setter;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TObject, class TFncObject, typename TRetVal>
FunctionVariant < TFncObject, TRetVal > * CreateFunctionVariant( 
  TObject * pOwner,
  TRetVal ( TFncObject::*pGetter ) () const, 
  void ( TFncObject::*pSetter ) ( TRetVal value ) 
)
{
  return new FunctionVariant < TFncObject, TRetVal >( pOwner, pGetter, pSetter );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TObject, class TFncObject, typename TRetVal>
FunctionVariant < TFncObject, TRetVal > * CreateFunctionVariant( 
  TObject * pOwner, TRetVal ( TFncObject::*pGetter ) () const
)
{
  return new FunctionVariant < TFncObject, TRetVal >( pOwner, pGetter, 0 );
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template < class TObject >
class StringListVariant : public Variant
{
public:
  typedef const WStringListT & (TObject::*TGetterFunc)() const;
  
  StringListVariant( TObject * _pOwner, TGetterFunc _getter ) : pOwner( _pOwner ), getter( _getter ) { }

  virtual VariantType::Enum GetType() const { return VariantType::WStringList; }

  virtual bool              IsReadonly() const { return true; }

  virtual const WStringListT & GetWStringList() const { return getter ? (pOwner->*getter) () : Variant::GetWStringList(); }

protected:
  TObject * pOwner;
  TGetterFunc getter;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class TObject >
StringListVariant < TObject > * CreateStringListVariant( TObject * pOwner, const WStringListT & ( TObject::*pGetter ) () const )
{
  return new StringListVariant < TObject >( pOwner, pGetter );
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Map
{
public:
  Map() {}
  ~Map() {}

  Variant * GetVariant( const char * name, void* prms = NULL ) { return GetVariant( name, prms, false ); }
  ReadonlyVariant * GetVariant( const char * name, void* prms = NULL ) const { return const_cast < Map * > ( this ) -> GetVariant( name, prms, true ); }

  int operator&( IBinSaver &f ) { return 0; }

protected:
  Variant * GetVariant( const char * name, void* prms, bool readonly );

  virtual Map * ResolveNameMap( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly ) { return 0; }
  virtual Variant * ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly ) { return 0; }
  virtual bool ResolveName( const char * name, int length, const char * args, int argsLength, Map ** ppMap, Variant ** ppVariant, void* prms, bool readonly );

  virtual bool ResolveNameByMacro( const char * name, int length, const char * args, int argsLength, Map ** ppMap, Variant ** ppVariant, void* prms, bool readonlyNeeded ) = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 'Map' class cannot be derived from IObjectBase due to its static use
// This wrapper class is used to store weak pointers to name-maps
_interface IMap : public IBaseInterfaceST, public Map
{
  NI_DECLARE_CLASS_1( IMap, IBaseInterfaceST );
};


} //namespace NNameMap



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Macroses
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Use this in class body:
#define NAMEMAP_DECLARE \
protected: \
  virtual bool ResolveNameByMacro ( const char * _mapElementName, int _mapElementNameLength, const char * _mapElementArgs, int _mapElementArgsLength, NNameMap::Map ** ppMap, NNameMap::Variant ** ppVariant, void* prms, bool _readonlyNeeded );

//This macro begins namemap definition
#define NAMEMAP_BEGIN( className ) \
  bool className :: ResolveNameByMacro ( const char * _mapElementName, int _mapElementNameLength, const char * _mapElementArgs, int _mapElementArgsLength, NNameMap::Map ** ppMap, NNameMap::Variant ** ppVariant, void* prms, bool _readonlyNeeded ) {

//This end namemap definition
#define NAMEMAP_END \
  return 0; }

//This re-uses (parent) class namemap
#define NAMEMAP_PARENT( parentClassName ) \
  if( parentClassName :: ResolveNameByMacro ( _mapElementName, _mapElementNameLength, _mapElementArgs, _mapElementArgsLength, ppMap, ppVariant, prms, _readonlyNeeded ) ) \
    return true;

#define NAMEMAP_INCLUDE( includingNameMap ) \
  if ((NULL != includingNameMap) && includingNameMap->ResolveNameByMacro ( _mapElementName, _mapElementNameLength, _mapElementArgs, _mapElementArgsLength, ppMap, ppVariant, prms, _readonlyNeeded ) ) \
    return true;

//
//These will define different name-map elements:
//

#define NAMEMAP_CUSTOM_VARIANT( variantName, variantCreationCode, isVariantReadOnly ) \
  if( _readonlyNeeded || ( !_readonlyNeeded && !isVariantReadOnly ) ) \
    if( ppVariant && !strncmp ( _mapElementName, #variantName, _mapElementNameLength ) ) { \
      *ppVariant = (variantCreationCode); \
      return true; }

#define NAMEMAP_CUSTOM_SUBMAP( variantName, submapCreationCode, additionalCondition ) \
  if( ppMap && (additionalCondition) && !strncmp ( _mapElementName, #variantName, _mapElementNameLength ) ) { \
    *ppMap = (submapCreationCode); \
    return true; }

#define NAMEMAP_VAR( variable ) NAMEMAP_CUSTOM_VARIANT( variable, NNameMap::CreateVariableVariant( variable, false ), false )
#define NAMEMAP_VAR_ALIAS( varName, variable ) NAMEMAP_CUSTOM_VARIANT( varName, NNameMap::CreateVariableVariant( variable, false ), false )

#define NAMEMAP_VAR_RO( variable ) NAMEMAP_CUSTOM_VARIANT( variable, NNameMap::CreateVariableVariant( variable, true ), true )
#define NAMEMAP_VAR_ALIAS_RO( varName, variable ) NAMEMAP_CUSTOM_VARIANT( varName, NNameMap::CreateVariableVariant( variable, true ), true )

#define NAMEMAP_FUNC( variable, getter, setter ) NAMEMAP_CUSTOM_VARIANT( variable, NNameMap::CreateFunctionVariant( this, getter, setter ), false )
#define NAMEMAP_FUNC_RO( variable, getter ) NAMEMAP_CUSTOM_VARIANT( variable, NNameMap::CreateFunctionVariant( this, getter ), true )

#define NAMEMAP_STRING_LIST( variable, getter ) NAMEMAP_CUSTOM_VARIANT( variable, NNameMap::CreateStringListVariant( this, getter ), true )

#define NAMEMAP_SUBMAP( submapPtrVariable ) NAMEMAP_CUSTOM_SUBMAP( submapPtrVariable, submapPtrVariable, submapPtrVariable )

#endif //NAMEMAP_H_INCLUDED
