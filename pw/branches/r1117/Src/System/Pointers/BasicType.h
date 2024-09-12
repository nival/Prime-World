#ifndef SYSTEM_BASICTYPE_H_INCLUDED
#define SYSTEM_BASICTYPE_H_INCLUDED

#include <typeinfo>
//TODO: сделать альтернативный "ускоренный" каст на основе простого static_cast-а
//Он должен включатся неявно через шаблоны, если видны и исходный, и желаемый тип, и если они являются прямыми наследниками


namespace ni_detail
{

typedef int ClassTypeId;

class TypeNameHashBase
{
protected:
  explicit TypeNameHashBase( const char * typeName );

public:
  ClassTypeId Get() const { return hash; }

private:
  ClassTypeId  hash;
};


template<class T>
class TypeNameHash : public TypeNameHashBase
{
public:
  #if defined( NV_WIN_PLATFORM )
    explicit TypeNameHash( const T & object ) : TypeNameHashBase( typeid( object ).raw_name() ) {}
    explicit TypeNameHash() : TypeNameHashBase( typeid( T ).raw_name() ) {}
  #elif defined( NV_LINUX_PLATFORM )
    explicit TypeNameHash( const T & object ) : TypeNameHashBase::TypeNameHashBase( typeid( T ).name() ) {}
    explicit TypeNameHash() : TypeNameHashBase::TypeNameHashBase( typeid( T ).name() ) {}
  #endif
};


//Function to call in main thread BEFORE using pointers from parallel threads
//Just ignore the return value
int InitPointersStatics( ClassTypeId fakeKey = 0 );

} //namespace ni_detail





#define NI_DECLARE_CLASS( classname ) \
public: \
  static ::ni_detail::ClassTypeId   StaticRuntimeClassId() { static ::ni_detail::TypeNameHash<classname> typeHash; return typeHash.Get(); } \
  static const char * StaticClassName() { return #classname; } \
  virtual const char *              ClassName() const { return #classname; } \
  virtual ::ni_detail::ClassTypeId  RuntimeClassId() const { return StaticRuntimeClassId(); } \
  virtual void *                    GetRawClassPointer( ::ni_detail::ClassTypeId ctid ) { return StaticGetRawClassPointer( ctid ); } \
  void *                            StaticGetRawClassPointer( ::ni_detail::ClassTypeId ctid ) { \
    if ( ctid == classname::StaticRuntimeClassId() ) return this; \


#define NI_DECLARE_BASE( baseclass ) \
    if ( void * ptr = baseclass::GetRawClassPointer( ctid ) ) return ptr; \


#define NI_DECLARE_END \
    return 0; } \





//Basic type for custom RTTI
class BasicType
{
public:
  virtual ~BasicType() {}

  NI_DECLARE_CLASS( BasicType )
  NI_DECLARE_END
                                                              
//Defined in macro:
//virtual const char *              ClassName() const;
//virtual ::ni_detail::ClassTypeId  RuntimeClassId() const;
//virtual void *                    GetRawClassPointer( ::ni_detail::ClassTypeId ctid );
};



namespace ni_detail
{

template<class T> T * GetDerivedObjectImpl( BasicType * p, T * )
{
  ClassTypeId ctid = T::StaticRuntimeClassId();
  void * ptr = p->GetRawClassPointer( ctid );
  return (T *)ptr;
}

} //namespace ni_detail




template<class TDest>
TDest * nival_cast( BasicType * object )
{
  if ( object )
    return ::ni_detail::GetDerivedObjectImpl( object, (TDest *)0 );
  return 0;
}



template<class TDest>
const TDest * nival_cast( const BasicType * object )
{
  if ( object )
    return ::ni_detail::GetDerivedObjectImpl( const_cast<BasicType *>( object ), (TDest *)0 );
  return 0;
}




////////// Macro Shortcuts //////////

#define NI_DECLARE_CLASS_1( classname, baseclass ) \
  NI_DECLARE_CLASS( classname ) \
    NI_DECLARE_BASE( baseclass ) \
  NI_DECLARE_END \

#define NI_DECLARE_CLASS_2( classname, baseclass1, baseclass2 ) \
  NI_DECLARE_CLASS( classname ) \
    NI_DECLARE_BASE( baseclass1 ) \
    NI_DECLARE_BASE( baseclass2 ) \
  NI_DECLARE_END \

#define NI_DECLARE_CLASS_3( classname, baseclass1, baseclass2, baseclass3 ) \
  NI_DECLARE_CLASS( classname ) \
    NI_DECLARE_BASE( baseclass1 ) \
    NI_DECLARE_BASE( baseclass2 ) \
    NI_DECLARE_BASE( baseclass3 ) \
  NI_DECLARE_END \

#define NI_DECLARE_CLASS_4( classname, baseclass1, baseclass2, baseclass3, baseclass4 ) \
  NI_DECLARE_CLASS( classname ) \
    NI_DECLARE_BASE( baseclass1 ) \
    NI_DECLARE_BASE( baseclass2 ) \
    NI_DECLARE_BASE( baseclass3 ) \
    NI_DECLARE_BASE( baseclass4 ) \
  NI_DECLARE_END \

#endif //SYSTEM_BASICTYPE_H_INCLUDED
