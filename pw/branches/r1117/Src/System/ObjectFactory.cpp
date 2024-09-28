#include "stdafx.h"
#include "ObjectFactory.h"

namespace NObjectFactory
{

struct TypeToCheck
{
  int typeId;
  const char* type;
  const char* file;
  int line;

  ObjectFactoryNewFunc pfnNewFunc;
};


static vector<TypeToCheck> typesToCheck;



// class factory
static CClassFactory<CObjectBase> *pSSClasses = 0;


struct SBasicChunkInit
{
  ~SBasicChunkInit() { if ( pSSClasses ) delete pSSClasses; }
} init;



void StartRegister()
{
  if ( !pSSClasses )
    pSSClasses = new CClassFactory<CObjectBase>;
}



// создать объект по его typeID
CObjectBase *MakeObject( int nTypeID )
{
  // TODO: Check why this assert have been commented
  //NI_ASSERT( pSSClasses->IsRegistered( nTypeID ), NI_STRFMT("Unregistered object of type 0x%x - no new-function", nTypeID) );
  return pSSClasses->CreateObject( nTypeID );
}



void RegisterType( int nObjectTypeID, ObjectFactoryNewFunc pfnNewFunc, const std::type_info *pTypeInfo )
{
  pSSClasses->RegisterTypeBase( nObjectTypeID, pfnNewFunc, pTypeInfo );
  //CheckNewDeleteStatistic( nObjectTypeID, pfnNewFunc );
}



void RegisterType( int nObjectTypeID, ObjectFactoryNewFunc pfnNewFunc, const std::type_info *pTypeInfo, const char* type )
{
  if ( nObjectTypeID != -1 )
    pSSClasses->RegisterTypeBase( nObjectTypeID, pfnNewFunc, pTypeInfo );
}



void UnRegisterType( int nObjectTypeID, const std::type_info *pObjectTypeInfo )
{
  if ( pSSClasses )
    pSSClasses->UnregisterTypeBase( nObjectTypeID, pObjectTypeInfo );
}



int GetObjectTypeID( const CObjectBase *pObj )
{
  return pSSClasses->GetObjectTypeID( pObj );
}



bool IsRegistered( int nObjectTypeID )
{
  return pSSClasses ? pSSClasses->IsRegistered( nObjectTypeID ) : false;
}

} //namespace NObjectFactory
