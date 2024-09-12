#ifndef SYSTEM_POINTERSMACROSES_H_INCLUDED
#define SYSTEM_POINTERSMACROSES_H_INCLUDED

#include "BasicFactory.h"


#define NII_DECLARE_REFCOUNT_CLASS( classname ) \
public: \
  virtual BaseObjectType *        CastToBaseObject() { return this; } \
  virtual WeakPointerProxyType *  AcquireWeakProxy() { return BaseObjectType::AcquireWeakProxyInternal(); } \


#define NI_DECLARE_SERIALIZABLE_CLASS( persistentId, classname ) \
  NII_DECLARE_REFCOUNT_CLASS( classname ) \
  NI_DECLARE_PRODUCIBLE_CLASS( persistentId, classname ) \
  NI_DECLARE_CLASS( classname ) \


#define NI_DECLARE_REFCOUNT_CLASS( classname ) \
  NII_DECLARE_REFCOUNT_CLASS( classname ) \
  NI_DECLARE_NONPRODUCIBLE_CLASS( classname ) \
  NI_DECLARE_CLASS( classname ) \


#if defined( NV_WIN_PLATFORM )

#define NI_DEFINE_REFCOUNT( classname ) \
  template<> classname::BaseObjectType *       ::ni_detail::CastToBaseObjectImpl<classname::BaseObjectType>( classname * p, void * ) { return p->CastToBaseObject(); } \
  template<> classname::WeakPointerProxyType * ::ni_detail::AcquireWeakProxyImpl<classname::WeakPointerProxyType>( classname * p, void * ) { return p->AcquireWeakProxy(); } \
  template<> classname *                       ::ni_detail::GetDerivedObjectImpl2( BasicType * p, classname *, void * ) { return GetDerivedObjectImpl( p, (classname *)0 ); } \

#elif defined( NV_LINUX_PLATFORM )

#define NI_DEFINE_REFCOUNT( classname ) \
  namespace ni_detail { \
    template<> classname::BaseObjectType *       CastToBaseObjectImpl<classname::BaseObjectType>( classname * p, void * ) { return p->CastToBaseObject(); } \
    template<> classname::WeakPointerProxyType * AcquireWeakProxyImpl<classname::WeakPointerProxyType>( classname * p, void * ) { return p->AcquireWeakProxy(); } \
    template<> classname *                       GetDerivedObjectImpl2( BasicType * p, classname *, void * ) { return GetDerivedObjectImpl( p, (classname *)0 ); } \
  }

#endif

#define NI_DEFINE_SERIALIZABLE( classname ) \
  NI_DEFINE_REFCOUNT( classname ) \
  NI_REGISTER_IN_FACTORY_NM( , classname ) \


#define NI_DEFINE_SERIALIZABLE_NM( nmspace, classname ) \
  NI_DEFINE_REFCOUNT( nmspace::classname ) \
  NI_REGISTER_IN_FACTORY_NM( nmspace, classname ) \







////////// Macro Shortcuts //////////

#define NI_DECLARE_REFCOUNT_CLASS_1( classname, baseclass ) \
  NI_DECLARE_REFCOUNT_CLASS( classname ) \
    NI_DECLARE_BASE( baseclass ) \
  NI_DECLARE_END \

#define NI_DECLARE_REFCOUNT_CLASS_2( classname, baseclass1, baseclass2 ) \
  NI_DECLARE_REFCOUNT_CLASS( classname ) \
    NI_DECLARE_BASE( baseclass1 ) \
    NI_DECLARE_BASE( baseclass2 ) \
  NI_DECLARE_END \

#define NI_DECLARE_REFCOUNT_CLASS_3( classname, baseclass1, baseclass2, baseclass3 ) \
  NI_DECLARE_REFCOUNT_CLASS( classname ) \
    NI_DECLARE_BASE( baseclass1 ) \
    NI_DECLARE_BASE( baseclass2 ) \
    NI_DECLARE_BASE( baseclass3 ) \
  NI_DECLARE_END \

#define NI_DECLARE_REFCOUNT_CLASS_4( classname, baseclass1, baseclass2, baseclass3, baseclass4 ) \
  NI_DECLARE_REFCOUNT_CLASS( classname ) \
  NI_DECLARE_BASE( baseclass1 ) \
  NI_DECLARE_BASE( baseclass2 ) \
  NI_DECLARE_BASE( baseclass3 ) \
  NI_DECLARE_BASE( baseclass4 ) \
  NI_DECLARE_END \

#define NI_DECLARE_REFCOUNT_CLASS_5( classname, baseclass1, baseclass2, baseclass3, baseclass4, baseclass5 ) \
  NI_DECLARE_REFCOUNT_CLASS( classname ) \
  NI_DECLARE_BASE( baseclass1 ) \
  NI_DECLARE_BASE( baseclass2 ) \
  NI_DECLARE_BASE( baseclass3 ) \
  NI_DECLARE_BASE( baseclass4 ) \
  NI_DECLARE_BASE( baseclass5 ) \
  NI_DECLARE_END \

#define NI_DECLARE_REFCOUNT_CLASS_6( classname, baseclass1, baseclass2, baseclass3, baseclass4, baseclass5, baseclass6 ) \
  NI_DECLARE_REFCOUNT_CLASS( classname ) \
  NI_DECLARE_BASE( baseclass1 ) \
  NI_DECLARE_BASE( baseclass2 ) \
  NI_DECLARE_BASE( baseclass3 ) \
  NI_DECLARE_BASE( baseclass4 ) \
  NI_DECLARE_BASE( baseclass5 ) \
  NI_DECLARE_BASE( baseclass6 ) \
  NI_DECLARE_END \


#define NI_DECLARE_SERIALIZABLE_CLASS_1( persistentId, classname, baseclass ) \
  NI_DECLARE_SERIALIZABLE_CLASS( persistentId, classname ) \
    NI_DECLARE_BASE( baseclass ) \
  NI_DECLARE_END \

#define NI_DECLARE_SERIALIZABLE_CLASS_2( persistentId, classname, baseclass1, baseclass2 ) \
  NI_DECLARE_SERIALIZABLE_CLASS( persistentId, classname ) \
    NI_DECLARE_BASE( baseclass1 ) \
    NI_DECLARE_BASE( baseclass2 ) \
  NI_DECLARE_END \

#define NI_DECLARE_SERIALIZABLE_CLASS_3( persistentId, classname, baseclass1, baseclass2, baseclass3 ) \
  NI_DECLARE_SERIALIZABLE_CLASS( persistentId, classname ) \
    NI_DECLARE_BASE( baseclass1 ) \
    NI_DECLARE_BASE( baseclass2 ) \
    NI_DECLARE_BASE( baseclass3 ) \
  NI_DECLARE_END \

#define NI_DECLARE_SERIALIZABLE_CLASS_4( persistentId, classname, baseclass1, baseclass2, baseclass3, baseclass4 ) \
  NI_DECLARE_SERIALIZABLE_CLASS( persistentId, classname ) \
    NI_DECLARE_BASE( baseclass1 ) \
    NI_DECLARE_BASE( baseclass2 ) \
    NI_DECLARE_BASE( baseclass3 ) \
    NI_DECLARE_BASE( baseclass4 ) \
  NI_DECLARE_END \

#endif //SYSTEM_POINTERSMACROSES_H_INCLUDED
