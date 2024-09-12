#include "stdafx.h"
#include "BasicType.h"
#include "System/SyncPrimitives.h"


namespace ni_detail
{

typedef map<ClassTypeId, string> THashes;

struct SHashes
{
  THashes           hashes;
  threading::Mutex  mutex;
};

static SHashes & AccessHashes()
{
  static SHashes hashes;
  return hashes;
}



int InitPointersStatics( ClassTypeId fakeKey )
{
  threading::MutexLock lock( AccessHashes().mutex );
  THashes & hashes = AccessHashes().hashes;
  return ( hashes.find( fakeKey ) == hashes.end() ) ? 0 : 1;
}



TypeNameHashBase::TypeNameHashBase( const char * typeName )
{
  hash = (ClassTypeId)nstl::hash<const char *>()( typeName );

  threading::MutexLock lock( AccessHashes().mutex );

  THashes & hashes = AccessHashes().hashes;

  {
    pair<THashes::iterator, bool> result =
      hashes.insert( THashes::value_type( hash, typeName ) );

    //New hash, just return it
    if ( result.second )
      return;

    //Hash already present, check if it for the same string
    if ( result.first->second == typeName )
      return;
  }

  //OMG! We got identical hashes for two different strings.
  //We'll run through hashes and search for unoccupied slot
  for ( ClassTypeId i = hash + 1; i != hash; ++i )
  {
    pair<THashes::iterator, bool> result =
      hashes.insert( THashes::value_type( i, typeName ) );
    if ( result.second )
    {
      hash = i;
      return;
    }
  }

  assert( !"Internal hash calculation failure!" );
  hash = 0;
}

} //namespace ni_detail
