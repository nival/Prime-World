#ifndef SYSTEM_BASICFACTORY_H_INCLUDED
#define SYSTEM_BASICFACTORY_H_INCLUDED

#include "BasicType.h"
#include <assert.h>

struct IBinSaver;


class SerializableBase : public BasicType
{
  NI_DECLARE_CLASS_1( SerializableBase, BasicType )

  static ::ni_detail::ClassTypeId   StaticPersistentClassId() { return 0; }

  virtual ::ni_detail::ClassTypeId  PersistentClassId() const = 0;

  virtual int operator & ( IBinSaver & ) { return 0; }
};



class SerializableObject : public SerializableBase
{
  NI_DECLARE_CLASS_1( SerializableObject, SerializableBase )

    static ::ni_detail::ClassTypeId   StaticPersistentClassId() { return 0; }

  virtual ::ni_detail::ClassTypeId    PersistentClassId() const { return 0; }
};



#define NI_DECLARE_PRODUCIBLE_CLASS( persistentId, classname ) \
  static ::ni_detail::ClassTypeId   StaticPersistentClassId() { return persistentId; } \
  virtual ::ni_detail::ClassTypeId  PersistentClassId() const { return StaticPersistentClassId(); } \
  static SerializableBase *         New_##classname() { \
    SerializableObject * serObj = new classname; /* to resolve ambiguity of multiple SerializableBase */ \
    return serObj; } \


#define NI_DECLARE_NONPRODUCIBLE_CLASS( classname ) \
  static ::ni_detail::ClassTypeId   StaticPersistentClassId() { return 0; } \
  virtual ::ni_detail::ClassTypeId  PersistentClassId() const { return 0; } \


#define NI_REGISTER_IN_FACTORY_NM( nmspace, classname ) \
  namespace ni_detail { \
    static struct Factory_registrator_##nmspace##classname { /*Oh those nasty texty macroses!*/ \
      Factory_registrator_##nmspace##classname() { \
        ni_detail::RegisterInFactory( nmspace::classname::StaticPersistentClassId(), &(nmspace::classname::New_##classname) ); \
      } \
    } Factory_registrator_##nmspace##classname##_instance; \
  } /* namespace ni_detail */ \


namespace ni_detail
{

SerializableBase * ProduceObject( ClassTypeId persistentId );
void RegisterInFactory( ClassTypeId persistentId, SerializableBase * (*constructor)() );

template <class T>
T * ProduceObject()
{
  assert( T::StaticPersistentClassId() ); //Class is not producible!
  if ( !T::StaticPersistentClassId() )
    return 0;
  BasicType * basicObject = ProduceObject( T::StaticPersistentClassId() );
  assert( basicObject );
  if ( basicObject )
  {
    T * object = GetDerivedObjectImpl( basicObject, (T *)0 );
    assert( object ); //NI_STRFMT( "Could not cast object of class '%s' to class '%s' / 0x%08x", basicObject->ClassName(), T::StaticPersistentClassId() );
    return object;
  }
  return 0;
}

} //namespace ni_detail

#endif //SYSTEM_BASICFACTORY_H_INCLUDED
