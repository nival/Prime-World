#ifndef SYSTEM_POINTERSDETAIL_H_INCLUDED
#define SYSTEM_POINTERSDETAIL_H_INCLUDED

//#define NI_POINTERS_DBG_USE_DYNCAST

#include "System/Pointers/BasicType.h"

class BaseObjectST;
class BaseObjectMT;
_interface IBaseInterfaceST;
_interface IBaseInterfaceMT;
class WeakPointerProxyST;
class WeakPointerProxyMT;

namespace ni_detail
{

//Some special template-function-override magic

//Static version, used when no class definition is visible
template<class TBaseObject, class T> TBaseObject * CastToBaseObjectImpl( T * p, void * );

//Can be casted to BaseObject, no virtual call
template<class TBaseObject, class T> inline TBaseObject * CastToBaseObjectImpl( T * p, TBaseObject * ) { return p; }

//Can only be casted to IBaseInterface, use virtual call
template<class TBaseObject, class T> inline TBaseObject * CastToBaseObjectImpl( T * p, IBaseInterfaceST * ) { return p->CastToBaseObject(); }
template<class TBaseObject, class T> inline TBaseObject * CastToBaseObjectImpl( T * p, IBaseInterfaceMT * ) { return p->CastToBaseObject(); }

//'Interface' function
template<class TBaseObject, class T> inline TBaseObject *  CastToBaseObject( T * p ) { return CastToBaseObjectImpl<TBaseObject>( p, p ); }



//The same pattern for proxy access
template<class TProxyObject, class T> TProxyObject * AcquireWeakProxyImpl( T * p, void * );

template<class TProxyObject, class T> inline TProxyObject * AcquireWeakProxyImpl( T * p, BaseObjectST * ) { return p->AcquireWeakProxyInternal(); }
template<class TProxyObject, class T> inline TProxyObject * AcquireWeakProxyImpl( T * p, BaseObjectMT * ) { return p->AcquireWeakProxyInternal(); }

template<class TProxyObject, class T> inline TProxyObject * AcquireWeakProxyImpl( T * p, IBaseInterfaceST * ) { return p->AcquireWeakProxy(); }
template<class TProxyObject, class T> inline TProxyObject * AcquireWeakProxyImpl( T * p, IBaseInterfaceMT * ) { return p->AcquireWeakProxy(); }

template<class TProxyObject, class T> inline TProxyObject * AcquireWeakProxy( T * p ) { return AcquireWeakProxyImpl<TProxyObject>( p, p ); }



// Stuff to enable up-casts on forwarded objects

template<class T> T* GetDerivedObjectImpl2( BasicType * p, T *, void * );
template<class T> T* GetDerivedObjectImpl2( BasicType * p, T *, BaseObjectST * ) { return GetDerivedObjectImpl( p, (T *)0 ); }

template<class T> T* GetDerivedObjectImpl2( BasicType * p, T *, IBaseInterfaceST * ) { return GetDerivedObjectImpl( p, (T *)0 ); }

template<class T> T* GetDerivedObjectImpl2( BasicType * p, T *, BaseObjectMT * ) { return GetDerivedObjectImpl( p, (T *)0 ); }
template<class T> T* GetDerivedObjectImpl2( BasicType * p, T *, IBaseInterfaceMT * ) { return GetDerivedObjectImpl( p, (T *)0 ); }


} //namespace ni_detail

#endif //SYSTEM_POINTERSDETAIL_H_INCLUDED
