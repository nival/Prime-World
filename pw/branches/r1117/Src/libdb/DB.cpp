#include "stdafx.h"

#undef _interface

#if defined( NV_WIN_PLATFORM )
#include <comutil.h>
#endif
#include "Db.h"
#include "XmlSaver.h"
#include "DbResourceCache.h"
#include "IDbTypesRegistrator.h"
#include "System/DarkSide.h"


namespace NDb
{

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

DbResource::DbResource() :
refCount( 0 ),
loaded(false),
outdated(false),
originalResource( 0 ),
__parent( this, &DbResource::OnParentChanged )
{}



DbResource::DbResource( const DBID &_dbid ) :
refCount( 0 ),
dbid( _dbid ),
loaded(false),
outdated(false),
originalResource( 0 ),
__parent( this, &DbResource::OnParentChanged )
{}



void RegisterResoruceType( const char *typeName, DbResourceNewFunc pDbResourceNewFunc )
{
	GetDbTypesRegistrator().RegisterResoruceType( typeName, pDbResourceNewFunc );
}



void DbResource::ReleaseRef()
{
  GetDbResourceCache().ReleaseResourceRef( this );
}



void DbResource::OnParentChanged( const NDb::DBID& )
{
  GetDbResourceCache().SetNeedReload( dbid );
}



Ptr<DbResource> Create( const string &fileName, const char *typeName, const bool inlined )
{
	if ( inlined )
	{
		char randString[64];
		NStr::GenerateUUID(randString, sizeof(randString));
		string id(randString);
		
		return GetDbResourceCache().Create( DBID( fileName, id ), typeName );
	}
	else
	{
		return GetDbResourceCache().Create( DBID( fileName ), typeName );
	}
}



Ptr<DbResource> ReadResource( IXmlSaver &saver )
{
	if ( !saver.HasHRefAttr() )
		return 0;
		
	string href;
	NStr::UTF8ToMBCS( &href, saver.GetHRefAttrValue() );
  if ( href.empty() )
		return 0;
	else 
  {
    DBID dbid(href, saver.GetIdAttrValue());
    return ReadResource( saver, dbid );
  }
}



Ptr<DbResource> ReadResource( IXmlSaver &saver, const DBID& dbid )
{
  if ( saver.GetResourceReader() )
  {
    return saver.GetResourceReader()->Read( dbid, saver );
  }
  return GetDbResourceCache().Get(dbid, &saver, saver.HasIdAttr() );
}



void WriteResource( IXmlSaver &saver, const DbResource *pResource )
{
	if ( !pResource )
		return;

  if ( saver.GetResourceReader() )
  {
    saver.GetResourceReader()->Write( pResource->GetDBID(), pResource, saver );
  }
  else
  {
	  saver.SetHrefIdAttributes( pResource->GetDBID().GetFileName(), pResource->GetDBID().GetId() );
	  if ( pResource->GetDBID().IsInlined() )
	  {
		  saver.StartChunk( pResource->GetObjectTypeName(), 0 );
		  saver.AddPolymorphicBase( 0, const_cast<DbResource *>( pResource ) );
		  saver.FinishChunk();
	  }
  }
}



Ptr<DbResource> GetResource( const DBID &dbid )
{
	return GetDbResourceCache().Get( dbid, 0, true );
}



Ptr<DbResource> PrecacheResource( const DBID& dbid, const int depth, const bool force )
{
  if ( force )
    return GetDbResourceCache().PrecacheForce( dbid, depth );
  else
    return GetDbResourceCache().Precache( dbid, depth );

}



void Traverse( const DbResource *pResource, const int depth, IResourcesProcessor* proc )
{
  return GetDbResourceCache().Traverse( pResource, depth, proc );
}



TDBResourceNotifier* GetChangeNotifier( const DBID &dbid )
{
  return GetDbResourceCache().GetChangeNotifier( dbid );
}



TDBResourceNotifier& NeedChangeNotifier( const DBID &dbid )
{
  return GetDbResourceCache().NeedChangeNotifier( dbid );
}



const DbResource* DbResource::GetMainResource( const DbResource * resource )
{
  if ( resource )
    if ( resource->GetOriginalResource() )
      return resource->GetOriginalResource();

  return resource;
}



DbResource* DBResourceStateManager::GetState( const string& stateName )
{
  DbResource* result = 0;
  if ( !stateName.empty() )
  {
    TStates::iterator it = states.find( stateName );
    if ( it != states.end() )
      result = it->second;
  }
  return result;
}

unsigned int DBResourceStateManager::GetStateHashKey( const DbResource* ptr ) 
{
  unsigned int hashKey = 0;
  //if ( !stateName.empty() )
  {
    TStatesHashKeys::iterator it = statesHashKeys.find( DarkSide::ptr2int< TStatesHashKeys::key_type >( ptr ) );
    if ( it != statesHashKeys.end() )
      hashKey = it->second;
    else
    {
      hash<string> hasher;

      const string& stateName = GetStateName(ptr);

      if (stateName.empty())
        return 0;
      
      hashKey = hasher( NStr::GetLower(ptr->GetDBID().GetFileName()) ) ^ hasher( NStr::GetLower(stateName) );
      statesHashKeys[DarkSide::ptr2int< TStatesHashKeys::key_type >( ptr )] = hashKey;
    }
  }

  return hashKey;
}

const string& DBResourceStateManager::GetStateName( const DbResource* ptr )
{
  static string emptyString;
  for ( TStates::iterator it = states.begin(); it != states.end(); ++it )
  {
    if ( it->second == ptr )
      return it->first;
  }
  return emptyString;
}



DBResourceStateManager::~DBResourceStateManager()
{
  for ( TStates::iterator it = states.begin(); it != states.end(); ++it )
    delete it->second;
}

}	// namespace NDb
