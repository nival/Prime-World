#include "stdafx.h"

#include "BasicFactory.h"
#include "System/SimpleObjectsFactory.h"


namespace ni_detail
{


static SimpleObjectsFactory<SerializableBase> & AccessFactory()
{
  static SimpleObjectsFactory<SerializableBase> fac;
  return fac;
}



SerializableBase * ProduceObject( ClassTypeId persistentId )
{
  return AccessFactory().CreateObject( persistentId );
}



void RegisterInFactory( ClassTypeId persistentId, SerializableBase * (*constructor)() )
{
  AccessFactory().RegisterType( persistentId, constructor );
}

} //namespace ni_detail
