#include "stdafx.h"
#include "RpcDataFactory.h"

namespace rpc
{ 

void DataFactory::RegisterInFactory( int type, Data::CreateFun fun, int realSize )
{
  //TODO
  hash_map<int, Data::CreateFun>::iterator it = messagesMap.find( type );
  //NI_VERIFY( it == messagesMap.end(), NI_STRFMT( "RPC data type id=%d is already registred", type ), return );
  messagesMap[type] = fun;

  hash_map<int, int>::iterator itRealSize = realSizeMap.find( type );
  //NI_VERIFY( itRealSize == realSizeMap.end(), NI_STRFMT( "RPC data type id=%d is already registred", type ), return );
  realSizeMap[type] = realSize;
}



int DataFactory::GetRealSize( int type )
{
  hash_map<int, int>::iterator it = realSizeMap.find( type );

  if ( it != realSizeMap.end() )
    return it->second;

  systemLog(NLogg::LEVEL_MESSAGE ) << "Unknown type of data: " << type << endl;
  NI_ALWAYS_ASSERT( NI_STRFMT( "Unknown type of data: %d", type ) );
  return 0;
}



Data* DataFactory::Create( int type, void* inplaceMemoryForCreation )
{
  hash_map<int, Data::CreateFun>::iterator it = messagesMap.find( type );

  if ( it != messagesMap.end() )
    return it->second(type, inplaceMemoryForCreation);

  systemLog(NLogg::LEVEL_MESSAGE ) << "Unknown type of data: " << type << endl;
  NI_ALWAYS_ASSERT( NI_STRFMT( "Unknown type of data: %d", type ) );
  return 0;
}



class DataFactoryGuard
{
  DataFactory* factory;

public:
  DataFactoryGuard() : factory(0) {}
  ~DataFactoryGuard() { delete factory; }

  DataFactory* Get()
  {
    if ( !factory )
      factory = new DataFactory();

    return factory; 
  }
};



DataFactory* GetGlobalDataFactory()
{
  static DataFactoryGuard dataFactoryGuard;
  return dataFactoryGuard.Get();
}

} //namespace rpc
