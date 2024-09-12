#ifndef SYSTEM_WEAK_H_INCLUDED
#define SYSTEM_WEAK_H_INCLUDED

#include "BaseObjectST.h"


template <class T>
class Weak
{
  WeakPointerProxyST * proxy;

public:
  Weak() : proxy( 0 ) {}

  ~Weak()
  {
    ImplementationRelease( proxy );
  }

  Weak( T * p )
  {
    WeakPointerProxyST * _proxy = p ? ni_detail::AcquireWeakProxy<WeakPointerProxyST>( p ) : 0;
    ImplementationAddRef( _proxy );
    proxy = _proxy;
  }

  Weak( const Weak & other )
  {
    ImplementationAddRef( other.proxy );
    proxy = other.proxy;
  }

  Weak & operator = ( T * p )
  {
    Set( p );
    return *this;
  }

  Weak & operator = ( const Weak & other )
  {
    Set( other.proxy );
    return *this;
  }

  void Set( T * p )
  {
    WeakPointerProxyST * _proxy = p ? ni_detail::AcquireWeakProxy<WeakPointerProxyST>( p ) : 0;
    Set( _proxy );
  }

  void Set( WeakPointerProxyST * _proxy )
  {
    ImplementationAddRef( _proxy );
    ImplementationRelease( proxy );
    proxy = _proxy;
  }

  T * Get()
  {
    if ( proxy )
    {
      BaseObjectST * obj = proxy->Object();
      if ( obj )
      {
#ifdef NI_POINTERS_DBG_USE_DYNCAST
        return dynamic_cast<T *>( obj );
#else //NI_POINTERS_DBG_USE_DYNCAST
        IBaseInterfaceST * iobj = obj; //Resolve ambiguity of BasicType
        return ni_detail::GetDerivedObjectImpl2( iobj, (T *)0, (T *)0 );
#endif //NI_POINTERS_DBG_USE_DYNCAST
      }
    }
    return 0;
  }

  T * Get() const
  {
    return const_cast<Weak<T> *>( this )->Get();
  }

  bool Valid() const
  {
    if ( proxy )
      return proxy->Object() ? true : false;
    return false;
  }

  BaseObjectST * GetBaseObject() { return proxy ? proxy->Object() : 0; }

  T * GetSafe() { T * p = Get(); NI_ASSERT( p, "Null pointer" ); return p; }
  T * GetSafe() const { T * p = Get(); NI_ASSERT( p, "Null pointer" ); return p; }

  T * operator -> () { return GetSafe(); }
  T * operator -> () const { return GetSafe(); }

  operator T * () { return Get(); }
  operator T * () const { return Get(); }

  int operator & ( IBinSaver & f );

private:
  static void ImplementationAddRef( WeakPointerProxyST * _proxy )
  {
    if ( _proxy )
      _proxy->WeakAddRef();
  }

  static void ImplementationRelease( WeakPointerProxyST * _proxy )
  {
    if ( _proxy )
      _proxy->WeakRelease();
  }
};

#endif //SYSTEM_WEAK_H_INCLUDED
