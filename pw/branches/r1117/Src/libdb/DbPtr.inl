//NDb::Ptr<> implementation inline file
//We are in namespace 'NDb'


template<class TDbResource>
inline
void Ptr<TDbResource>::SetPtrInternal( const TDbResource * p, const TDbResource * newActiveState )
{
  const TDbResource * pOldResource = pResource;
  pResource = p;
  AddRef( pResource );
  ReleaseRef( pOldResource );

  pActiveState = newActiveState;
}




template<class TDbResource>
inline
void Ptr<TDbResource>::SetPtr( const TDbResource * p )
{
  const TDbResource * orgPtr = (const TDbResource *)( DbResource::GetMainResource( CastToDBResource( p ) ) );
  SetPtrInternal( orgPtr, p );
}




template<class TDbResource>
inline
void Ptr<TDbResource>::SetPtr( const Ptr & ptr )
{
  SetPtrInternal( ptr.pResource, ptr.pActiveState );
}




template<class TDbResource>
inline
const TDbResource * Ptr<TDbResource>::GetPtr() const 
{ 
  const_cast<Ptr<TDbResource> *>(this)->Load(); 
  if ( !pResource ) 
    return 0;

  return pActiveState;
}

template<class TDbResource>
inline
unsigned int Ptr<TDbResource>::GetStateDependentHashKey() const
{
  const DbResource* p = CastToDBResource( pResource );
  unsigned int resKey = p->GetDBID().GetHashKey();
    DBResourceStateManager *pMan = SAccessToDBResource::GetStatesManager( p );
  if (!pMan || !pActiveState)
    return resKey;

  unsigned int stateKey = pMan->GetStateHashKey(pActiveState);
  if (stateKey == 0)
    return resKey;

  return stateKey;
}


template<class TDbResource>
inline
void Ptr<TDbResource>::ChangeState( const string& stateName ) const 
{
  const DbResource* p = CastToDBResource( pResource );
  DBResourceStateManager *pMan = SAccessToDBResource::GetStatesManager( p );
  if ( !pMan )
  {
    pActiveState = pResource;
    return; 
  }

  const DbResource* pState = pMan->GetState( stateName );
  if ( !pState )
    pState = pResource;

  if ( pState != pActiveState )
    pActiveState = (const TDbResource*)pState;
}

template<class TDbResource>
inline
void Ptr<TDbResource>::SetState( const string& stateName )  
{
  Load(); 
  ChangeState(stateName);
}


template<class TDbResource>
inline
const string& Ptr<TDbResource>::GetCurrentStateName()  
{
  static const string emptyStr;
  const DbResource* p = CastToDBResource( pResource );
  DBResourceStateManager *pMan = SAccessToDBResource::GetStatesManager( p );
  if ( !pMan || !pActiveState )
    return emptyStr;
  
  return pMan->GetStateName(pActiveState);  
}




template<class TDbResource>
inline
void Ptr<TDbResource>::Traverse( int depth, IResourcesProcessor* pProcessor )
{
  const DbResource* p = CastToDBResource( pResource );
  NDb::Traverse( p, depth, pProcessor );
}




template<class TDbResource>
template<class TDbResource2>
inline
bool Ptr<TDbResource>::operator == ( const TDbResource2 *p ) const
{
  NI_ALWAYS_ASSERT("Direct resource comparison detected!");

	if ( !p || !GetPtr() )
		return false;
	if ( p->GetDBID() != pResource->GetDBID() )
    return false;
  return p == pActiveState;
}




template<class TDbResource>
inline
void Ptr<TDbResource>::Load()
{
	if ( IsEmpty() )
		return;

  const NDb::DbResource* pRes = CastToDBResource( pResource ); 
  //>WTF?  акой мусор вал€етс€ в pResource, если IsEmpty не помогает?!
  if( pRes == NULL )
  {
    return;
  }
  //<WTF

	if ( pRes->NeedReload() && !pRes->GetDBID().IsEmpty() )
	{
    string activeStateName;
    if ( pActiveState != pResource )
    {
      const DbResource* p = CastToDBResource( pResource );
      const DbResource* pS = CastToDBResource( pActiveState );
      DBResourceStateManager *pMan = SAccessToDBResource::GetStatesManager( p );
      if ( pMan )
        activeStateName = pMan->GetStateName( pS );
    }

    SetPtr( Get<TDbResource>( CastToDBResource( pResource )->GetDBID() ) );

    if ( !activeStateName.empty() )
    {
      const DbResource* p = CastToDBResource( pResource );
      DBResourceStateManager *pMan = SAccessToDBResource::GetStatesManager( p );
      if ( pMan )
      {
        const DbResource* pState = pMan->GetState( activeStateName );
        if ( pState )
          pActiveState = (const TDbResource*)pState;
      }
    }
	}
}




template<class TDbResource>
inline
int Ptr<TDbResource>::operator&( IBinSaver &saver )
{
	if ( saver.IsChecksum() )
	{
		int hashValue = IsEmpty() ? 0 : CastToDBResource(pResource)->GetDBID().GetHashKey();
		saver.Add( 3, &hashValue );
	}
	else if ( saver.IsReading() )
	{
		string str;
		saver.Add( 3, &str );
		if ( str.empty() || str == "[db:empty]" )
			pResource = 0;
		else
    {
			SetPtr( NDb::Get<TDbResource>( DBID( str ) ) );
      pActiveState = pResource;
    }
	}
	else
	{
		string str;
		if ( IsEmpty() )
			str = "[db:empty]";
		else
			str = GetFormattedDbId( CastToDBResource(pResource)->GetDBID() );

		saver.Add( 3, &str );
	}
	return 0;
}




template<class TDbResource>
inline
int Ptr<TDbResource>::operator&( IXmlSaver &saver )
{
  if ( saver.IsReading() )
  {
    Ptr<DbResource> result = ReadResource( saver );
    SetPtr( dynamic_cast<const TDbResource*>( result.GetRawResourcePtr() ) );
    pActiveState = pResource;
  }
  else
  {
    if ( saver.GetResourceReader() && !saver.GetResourceReader()->LoadResources() && pResource )
    {
      saver.GetResourceReader()->Write( pResource->GetDBID(), pResource, saver );
    }
    else
    {
      WriteResource( saver, GetPtr() );
    }
  }

  return 0;
}
