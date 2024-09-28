#ifndef SYSTEM_MWEAK_H_INCLUDED
#define SYSTEM_MWEAK_H_INCLUDED

#include "System/SpinLock.h"
#include "System/CustomAtomics.h"
#include "BaseObjectMT.h"


template <class T>
class WeakMT
{
  WeakPointerProxyMT * proxy;

public:
  WeakMT() : proxy( 0 ) {}

  ~WeakMT()
  {
    ImplementationRelease( proxy );
  }

  WeakMT( T * p )
  {
    WeakPointerProxyMT * _proxy = p ? ni_detail::AcquireWeakProxy<WeakPointerProxyMT>( p ) : 0;
    ImplementationAddRef( _proxy );
    proxy = _proxy;
  }

  WeakMT( const WeakMT & other )
  {
    ImplementationAddRef( other.proxy );
    proxy = other.proxy;
  }

  WeakMT & operator = ( T * p )
  {
    Set( p );
    return *this;
  }

  WeakMT & operator = ( const WeakMT & other )
  {
    Set( other.proxy );
    return *this;
  }

  StrongMT<T> Lock() 
  {
    if ( proxy )
    {
      threading::SpinLockGuard lock( proxy->AccessLock() );
      if ( proxy->Object() )
      {
        BaseObjectMT * obj = proxy->Object();
        LONG prevRefCount = threading::InterlockedIncrementNonZero( obj->RefCountPtr() );
        if ( prevRefCount > 0 )
        {
#ifdef NI_POINTERS_DBG_USE_DYNCAST
          T * p = dynamic_cast<T *>( obj );
#else //NI_POINTERS_DBG_USE_DYNCAST
          NI_ASSERT( obj, "Null pointer" );
          IBaseInterfaceMT * iobj = obj; //Resolve ambiguity of BasicType
          T * p = ni_detail::GetDerivedObjectImpl2( iobj, (T *)0, (T *)0 );
#endif //NI_POINTERS_DBG_USE_DYNCAST
          NI_ASSERT( p, "Null pointer" );
          NI_ASSERT( p->AcquireWeakProxy() == proxy, "Wrong pointer proxy" );
          return StrongMT<T>( StrongMT<T>::DoNotIncrementReferenceFlag, p );
        }
        return StrongMT<T>();
      }
    }

    return 0;
  }

  int operator & ( IBinSaver & f ) { NI_ALWAYS_ASSERT( "Serialization of thread-safe weak pointers is not supported" ); return 0; }

private:
  void Set( T * p )
  {
    WeakPointerProxyMT * _proxy = p ? ni_detail::AcquireWeakProxy<WeakPointerProxyMT>( p ) : 0;
    Set( _proxy );
  }

  void Set( WeakPointerProxyMT * _proxy )
  {
    ImplementationAddRef( _proxy );
    ImplementationRelease( proxy );
    proxy = _proxy;
  }

  static void ImplementationAddRef( WeakPointerProxyMT * _proxy )
  {
    if ( _proxy )
      _proxy->WeakAddRef();
  }

  static void ImplementationRelease( WeakPointerProxyMT * _proxy )
  {
    if ( _proxy )
      _proxy->WeakRelease();
  }
};

#endif //SYSTEM_MWEAK_H_INCLUDED
