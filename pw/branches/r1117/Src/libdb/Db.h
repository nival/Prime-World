#ifndef DB_H_B7A11851_D523_4251_BD8A_136
#define DB_H_B7A11851_D523_4251_BD8A_136

#include "dbid.h"
#include "../System/Notifier.h"
#include "XmlSaver.h"

struct IFileSystem;

namespace NDb
{

class DbResource;
struct SAccessToDBResource;
typedef Notifier<DBID> TDBResourceNotifier;



struct DBResourceStateManager
{
  typedef hash_map<string, DbResource*> TStates;
  TStates states;

  typedef hash_map<DWORD, unsigned int> TStatesHashKeys;
  TStatesHashKeys statesHashKeys;
  DbResource* GetState( const string& stateName );
  const string& GetStateName( const DbResource* ptr );
  unsigned int GetStateHashKey( const DbResource* ptr  );
  DBResourceStateManager() {}
  ~DBResourceStateManager(); 
};


class DbResource;

_interface IResourcesProcessor
{
  virtual bool Call( const DBID& dbid, const DbResource* pResource ) = 0;
  virtual bool LoadResources() = 0;
};



typedef DbResource* (*DbResourceNewFunc)( const DBID &dbid ); 
void RegisterResoruceType( const char *typeName, DbResourceNewFunc pDbResourceNewFunc );


template<class TDbResource>
class Ptr
{
	mutable const TDbResource *pResource;
  mutable const TDbResource *pActiveState;
	static void AddRef( const TDbResource *_p );
	static void ReleaseRef( const TDbResource *_p );

  void SetPtrInternal( const TDbResource * p, const TDbResource * newActiveState );

public:
	Ptr() : pResource( 0 ), pActiveState( 0 ) {}
	Ptr( const TDbResource *p ) : pResource( 0 ), pActiveState( 0 ) { SetPtr( p ); }
	Ptr( const Ptr &ptr ) : pResource( 0 ), pActiveState( 0 ) { SetPtr( ptr ); }

	~Ptr() { ReleaseRef( pResource ); }

	const TDbResource* operator->() const { return GetPtr(); }
	operator const TDbResource*() const { return GetPtr(); }

	bool IsEmpty() const { return ( pResource == 0 ); }

  void SetPtr( const TDbResource *p );
  void SetPtr( const Ptr & ptr );
	
  const TDbResource* GetPtr() const;

  const TDbResource* GetRawResourcePtr() const { return pResource; }

  void SetState( const string& stateName );
  void ChangeState( const string& stateName ) const;
  unsigned int GetStateDependentHashKey() const;
  const string& GetCurrentStateName();
  

  void Traverse( int depth, IResourcesProcessor* pProcessor );

	Ptr& operator= ( const TDbResource *p ) { SetPtr( p ); return *this; }
	Ptr& operator= ( const Ptr &ptr ) { SetPtr( ptr ); return *this; }

	template<class TDbResource2>
	bool operator==( const TDbResource2 *p ) const;
	
	void Load();
	
	int operator&( IBinSaver &saver );
  int operator&( IXmlSaver &saver );
};


// create resource and cache it. when creating inlined resources dbid show pointed to parent resource
Ptr<DbResource> Create( const string &fileName, const char *typeName, const bool inlined );


} //namespace NDb



#define BASIC_REGISTER_DBRESOURCE( name )																																											\
	template<> NDb::DbResource *CastToDBResourceImpl<NDb::name>( NDb::name *p, void* ) { return dynamic_cast<NDb::name*>( p ); }	\
	template<> const NDb::DbResource *CastToDBResourceImpl<NDb::name>( const NDb::name *p, const void* ) { return p; }				\
	template<> const NDb::name *CastToDBUserResourceImpl<NDb::name>( const NDb::DbResource *p, const NDb::name*, const void* ) { return dynamic_cast<const NDb::name*>( p ); }


template<class TUserObj> NDb::DbResource *CastToDBResourceImpl( TUserObj *p, void* );
template<class TUserObj> const NDb::DbResource *CastToDBResourceImpl( const TUserObj *p, const void* );
template<> inline const NDb::DbResource *CastToDBResourceImpl( const NDb::DbResource *p, const void* ) { return p; }
//template<class TUserObj> inline NDb::DbResource *CastToDBResource( TUserObj *p ) { return CastToDBResourceImpl( p, p ); }
//template<class TUserObj> inline const NDb::DbResource *CastToDBResource( const TUserObj *p ) { return CastToDBResourceImpl( p, p ); }
template<class TUserObj> inline NDb::DbResource *CastToDBResource( TUserObj *p ) { return (NDb::DbResource*)p; } // { return CastToDBResourceImpl( p, p ); }
template<class TUserObj> inline const NDb::DbResource *CastToDBResource( const TUserObj *p ) { return (const NDb::DbResource*)p; } //{ return CastToDBResourceImpl( p, p ); }

template<class TUserObj> const TUserObj *CastToDBUserResourceImpl( const NDb::DbResource *p, const TUserObj*, const void * );
template<class TUserObj> const TUserObj *CastToDBUserResourceImpl( const NDb::DbResource *p, const TUserObj*, const NDb::DbResource* ) { return dynamic_cast<const TUserObj*>( p ); }
template<class TUserObj> inline const TUserObj *CastToDBUserResource( const NDb::DbResource *p, const TUserObj *pu ) { return CastToDBUserResourceImpl( p, pu, pu ); }



namespace NDb
{

//Initialization
class DbResourceCache;
void SetResourceCache( DbResourceCache* pCache );
DbResourceCache* CreateGameResourceCache( IFileSystem* fileSystem, FileSystemChangesProcessor* changesProcessor );

void Traverse( const DbResource *pResource, const int depth, IResourcesProcessor* proc );

Ptr<DbResource> PrecacheResource( const DBID& dbid, const int depth, const bool force );
Ptr<DbResource> GetResource( const DBID &dbid );


Ptr<DbResource> ReadResource( IXmlSaver &saver );
Ptr<DbResource> ReadResource( IXmlSaver &saver, const DBID& dbid );
void WriteResource( IXmlSaver &saver, const DbResource *pResource );

TDBResourceNotifier& NeedChangeNotifier( const DBID &dbid );
TDBResourceNotifier* GetChangeNotifier( const DBID &dbid );




template< class TDbResource >
class ChangeablePtr
{
public:
  template<class T, typename P>
  ChangeablePtr( T* pThis, P handler )
  {
    pCallback = new MethodNotifyCallback<T,DBID,false>( pThis, handler );
  }
  ~ChangeablePtr() { Unsubscribe(); delete pCallback; }

  const TDbResource* operator->() const { return GetPtr(); }
  operator const TDbResource*() const { return GetPtr(); }
  ChangeablePtr& operator=( const TDbResource *p ) { SetPtr( p ); return *this; }
  ChangeablePtr& operator=( const Ptr<TDbResource> &ptr ) { SetPtr( ptr.GetPtr() ); return *this; }
  ChangeablePtr& operator=( const ChangeablePtr<TDbResource> &ptr ) 
  { 
    SetPtr( ptr.GetPtr() ); 
    return *this; 
  }

  bool IsEmpty() const { return ptr.IsEmpty(); }

  template<class TDbResource2>
  bool operator==( const TDbResource2 *p ) const { return ptr == p; }

  void SetState( const string& stateName ) 
  {
    ptr.SetState( stateName );
  }

  const TDbResource* GetPtr() const 
  {
    return ptr.GetPtr();
  }

private:
  void Unsubscribe() const;
  void Subscribe() const;

  void SetPtr( const TDbResource *p )  
  { 
    Unsubscribe();
    ptr = p;
    Subscribe();
  }

  mutable INotifyCallback<DBID>* pCallback;
  Ptr<TDbResource> ptr;
};




class DbResource
{
  friend class DbTypesRegistrator;
	friend class DbResourceCache;
  friend struct SAccessToDBResource;

public:
  typedef unsigned long checksum_type;

public:
	DbResource();
	DbResource( const DBID &_dbid );

	virtual ~DbResource() { }

  bool NeedReload() const { return !loaded || outdated; }
	bool HasReference() const { return refCount > 0; }

	const DBID &GetDBID() const { return dbid; }
	
	bool operator==( const DbResource &resource ) const { return this == &resource || GetDBID() == resource.GetDBID(); }
	bool operator!=( const DbResource &resource ) const { return this != &resource && GetDBID() != resource.GetDBID(); }
	
	virtual int operator&( IXmlSaver &saver ) = 0;
	virtual checksum_type CalcCheckSum() const = 0;

	virtual void DeleteThis() = 0;

	virtual DbResource *CastToDbResource() = 0;
	virtual const DbResource *CastToDbResource() const = 0;

	virtual const char *GetObjectTypeName() const = 0;

	static void AddRef( DbResource *pResource ) { if ( pResource ) pResource->AddRef(); }
	static void ReleaseRef( DbResource *pResource ) { if ( pResource ) pResource->ReleaseRef(); }

  static const DbResource* GetMainResource( const DbResource * resource );

  void SetOriginalResource( DbResource * res ) { originalResource = res; }
  DbResource * GetOriginalResource() const { return originalResource; }

protected:
	volatile LONG refCount;

 	void SetDbId( const DBID &_dbid ) { dbid = _dbid; } 	   
 	void SetNotLoaded() { loaded = false; }

  virtual DBResourceStateManager* GetStatesManager() const { return 0; }

  void OnParentChanged( const NDb::DBID& );

  NDb::ChangeablePtr<DbResource> __parent;

private:

	DBID dbid;
	bool loaded;
  bool outdated;

  DbResource * originalResource; //If this resource is a state, this points to original resource

  void AddRef() { nival::interlocked_increment( refCount ); }
	void ReleaseRef();
  
  virtual void DestroyContents() = 0;
};



template<typename TDbResource>
Ptr<TDbResource> Create( const string &fileName, const bool inlined )
{
	Ptr<DbResource> result = Create( fileName, TDbResource::GetTypeName(), inlined );
	if ( !result )
		return 0;
		
  Ptr<TDbResource> castedResult = dynamic_cast<TDbResource*>( result.GetPtr() );
  NI_ASSERT( castedResult,
		NI_STRFMT( "Resource \"%s\" has type \"%s\" and cannot be casted to \"%s\"", GetFormattedDbId( result->GetDBID() ), result->GetObjectTypeName(), TDbResource::GetTypeName() ) );
	
	return castedResult;
}



template<class TDbResource>
void Ptr<TDbResource>::AddRef( const TDbResource *_p )
{
  DbResource::AddRef( const_cast<DbResource *>( CastToDBResource( _p ) ) ); 
}
template<class TDbResource>
void Ptr<TDbResource>::ReleaseRef( const TDbResource *_p ) 
{ 
  DbResource::ReleaseRef( const_cast<DbResource *>( CastToDBResource( _p ) ) ); 
}


template< class TDbResource >
void ChangeablePtr< TDbResource >::Subscribe() const
{
  const DbResource* res = CastToDBResource( ptr.GetRawResourcePtr() );
  if ( res == 0 )
    return;
  TDBResourceNotifier& notifier = NDb::NeedChangeNotifier( res->GetDBID() );
  notifier.Subscribe_( pCallback );
}


template< class TDbResource >
void ChangeablePtr< TDbResource >::Unsubscribe() const
{
  const DbResource* res = CastToDBResource( ptr.GetRawResourcePtr() );
  if ( res == 0 )
    return;
  TDBResourceNotifier* pNotifier = NDb::GetChangeNotifier( res->GetDBID() );
  if ( pNotifier )
    pNotifier->Unsubscribe_( pCallback );
}



template<typename TDbResource>
Ptr<TDbResource> Get( const DBID &dbid )
{
	Ptr<DbResource > result = GetResource( dbid );
	if ( result )
	{
    Ptr<TDbResource> castedResult = const_cast<TDbResource*>( CastToDBUserResource( CastToDBResource( result.GetPtr() ), (const TDbResource*)0 ) );
		return castedResult;
	}
	else
		return 0;
}



template<typename TDbResource>
Ptr<TDbResource> Precache( const DBID &dbid, int depth, const bool force = false )
{
  Ptr<DbResource> result = PrecacheResource( dbid, depth, force );
  if ( !result )
    return 0;

  Ptr<TDbResource> castedResult = const_cast<TDbResource*>( CastToDBUserResource( CastToDBResource( result.GetPtr() ), (const TDbResource*)0 ) );
  return castedResult;
}



struct SAccessToDBResource
{
  static DBResourceStateManager* GetStatesManager( const DbResource* res ) { return res == 0 ? 0 : res->GetStatesManager(); }
};



template <class T>
struct KnownEnum
{
	enum { isKnown = 0 };
};



template<class TObj>
struct StateSerializeHelper
{
  typedef DbResource* (*TNewFunc)( const DBID & );

  typedef hash_map<string, DbResource*> TStates; 
  TStates& states;
  TNewFunc newFunc;
  TObj* defaultState;

  struct SingleStateReader
  {
    TObj* defaultState;
    TNewFunc newFunc;

    string stateName;
    TObj* pState;

    SingleStateReader( TObj* _defaultState, TNewFunc _newFunc ) 
      : defaultState( _defaultState ), newFunc( _newFunc ), pState( 0 ) {}

    int operator&( IXmlSaver &saver )
    {
      if ( !saver.IsReading() )
        return 0;

      stateName = saver.GetStateNameAttrValue();
      if( stateName.empty() )
        return 0;
      pState = (TObj*)( (*newFunc)( defaultState->GetDBID() ) );
      pState->SetOriginalResource( defaultState );
      pState->Assign( *defaultState );
      pState->SerializeSelf( saver );

      return 0;
    }

  };
  StateSerializeHelper( TObj* _defaultState, TStates& _states, TNewFunc _newFunc )
    : states( _states ), newFunc( _newFunc ), defaultState( _defaultState )
  {
  }

  int operator&( IXmlSaver &saver )
  {
    if ( saver.IsReading() )
    {
      int nSize = saver.CountChunks();
      for ( int i = 0; i < nSize; ++i )
      {
        SingleStateReader reader( defaultState, newFunc );

        saver.Add( "state", &reader, i + 1 );

        if ( reader.pState != 0 && !reader.stateName.empty() )
          states.insert( make_pair<string, DbResource*>( reader.stateName, reader.pState ) );
      }
    }
    else
    {
      // Only for Traverse of Precache
      TStates::iterator it = states.begin();
      TStates::iterator last = states.end();

      for ( int i = 0; it != last; ++it, ++i )
      {
        saver.Add( "state", it->second, i + 1 );
      }
    }

    return 0;
  }

  void InheritStates( TObj* parent, TStates& parentStates, IXmlSaver &saver )
  {
    string stateName;
    TObj* pState;
    TObj* pParentState;
    for( TStates::iterator it = parentStates.begin(); it != parentStates.end(); ++it )
    {
      stateName = it->first;
      pParentState = (TObj*)it->second;
      pState = (TObj*)( (*newFunc)( defaultState->GetDBID() ) );
      pState->Assign( *pParentState );
      pState->SerializeSelf( saver );
      states.insert( make_pair<string, DbResource*>( stateName, pState ) );
    }
  }

private:
  StateSerializeHelper& operator=( const StateSerializeHelper & ) {}
};

#include "DbPtr.inl"

} //namespace NDb;



#define DBRESOURCE_METHODS( name )																																														\
public:																																																												\
	virtual ~name() {}																																																					\
	void DeleteThis() { delete this; }																																													\
	DbResource *CastToDbResource() { return (DbResource*)this; }																																\
	const DbResource *CastToDbResource() const { return (DbResource*)this; }																										\
	const char *GetObjectTypeName() const { return GetTypeName(); }																															\
	static const char *GetTypeName() { return #name; }																																					\
	static bool SameType( const NDb::DbResource *pRes ) { return GetTypeName() == pRes->GetObjectTypeName(); }									\
	static DbResource* New##name( const DBID &dbid ) { name *pResult = new name(); pResult->SetDbId( dbid ); return pResult; }  \
protected:                                                                                                                    \
  virtual void DestroyContents()                                                                                              \
	{																																																  	 												\
		this->~name();																																						  												    	\
		long refCountOld = refCount;																																	  													\
		new(this) name();																																				  										      			\
		refCount += refCountOld;																																			  													\
	}																																																  													\
public:



template<class TDbResource> inline bool IsValid( const NDb::Ptr<TDbResource> &p ) { return !p.IsEmpty(); }
template<class TDbResource> inline bool IsValid( const NDb::ChangeablePtr<TDbResource> &p ) { return !p.IsEmpty(); }



#define REGISTER_DBRESOURCE( name )																																														\
BASIC_REGISTER_DBRESOURCE( name )																																															\
static struct SRegister_##name##DBRegister																																										\
{																																																															\
	SRegister_##name##DBRegister()																																															\
	{																																																														\
		NDb::RegisterResoruceType( #name, NDb::name::New##name );																															\
	}																																																														\
} dbinit##name;

#endif //#define DB_H_B7A11851_D523_4251_BD8A_136
